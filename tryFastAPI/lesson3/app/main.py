from fastapi import FastAPI, HTTPException, Query, Depends
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import uuid
import time
import random
import threading
import queue
import json
from typing import List, Dict


from sqlalchemy.orm import Session
from api_schemas import *
from db_models import Task, TaskStatus
from db import SessionLocal, get_db, Base, engine

app = FastAPI()

# 允许跨域
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

# 内存存储 - 模拟数据库
storage = {}
all_items = []

# 任务队列
task_queue = queue.Queue()
queue_lock = threading.Lock()

# 后台任务处理线程
def process_items():
    while True:
        with queue_lock:
            if not task_queue.empty():
                item_uuid = task_queue.get()
                
                # 处理任务：模拟耗时操作
                process_time = random.uniform(1.0, 3.0)
                time.sleep(process_time)
                
                # 更新项目状态
                if item_uuid in storage:                    
                    update_task_status(task_uuid=item_uuid, status=TaskStatus.finished, db = next(get_db()))
                    print(f"项目 {item_uuid} 处理完成, 耗时: {process_time:.2f}秒")
        time.sleep(0.5)  # 避免空转

# 启动后台线程
processing_thread = threading.Thread(target=process_items, daemon=True)
processing_thread.start()
 
@staticmethod
def update_task_status(task_uuid: str, status: TaskStatus, db):
    # storage[task_uuid].status = status
    db.query(Task).filter(Task.uuid == task_uuid).update({"status": status})
    db.commit()

@app.get("/items")
def get_items(page: int = Query(1, ge=1), page_size: int = Query(10, ge=1, le=100)):
    start = (page - 1) * page_size
    end = start + page_size
    total = len(all_items)
    
    # 分页返回数据
    paginated_items = all_items[start:end]
    
    # 添加状态信息
    for item in paginated_items:
        if item["uuid"] in storage:
            item["status"] = storage[item["uuid"]]["status"]
        else:
            item["status"] = "未知"
    
    return {
        "items": paginated_items,
        "page": page,
        "page_size": page_size,
        "total": total,
        "total_pages": (total + page_size - 1) // page_size
    }

@app.get("/items/{task_uuid}")
def get_item(task_uuid: str, db : Session = Depends(get_db)):
    entity = db.query(Task).filter(Task.uuid == task_uuid).first()
    if not entity:
        raise HTTPException(status_code=404, detail="Item not found")
    
    return {
        "uuid": entity.uuid,
        "name": entity.name,
        "description": entity.description,
        "file_path": entity.file_path,
        "size": entity.size,
        "created_at": entity.create_at,
        "status": entity.status
    }

@app.post("/items/")
def create_item(item: TaskCreate, db : Session = Depends(get_db)):
    item_uuid = str(uuid.uuid4())
    
    # 创建新项目    
    new_task = Task(
        uuid = item_uuid,
        name = item.name,
        description = item.description,
        file_path = item.file_path,
        size = item.size,
        status = TaskStatus.analyzing                        
    )
       
    # 添加到任务队列
    with queue_lock:
        task_queue.put(item_uuid)
        print(f"新项目已创建并添加到队列: {item_uuid}")

    db.add(new_task)
    db.commit()
    
    return {
        "uuid": item_uuid,
        "message": "项目创建成功，已加入处理队列",
        "status": "进行中"
    }

@app.get("/queue/status")
def get_queue_status():
    with queue_lock:
        queue_size = task_queue.qsize()
        queue_items = list(task_queue.queue)
    
    return {
        "queue_size": queue_size,
        "items_in_queue": queue_items
    }


@app.on_event("shutdown")
async def shutdown():
    # 关闭数据库连接池
    print("Application shutdown.")
    engine.dispose()


@app.on_event("startup")
async def startup_enevt():    
    print("Start Application. Welcome to palworld!")
    Base.metadata.create_all(bind=engine)
    # 创建数据库连接池
    engine.connect()


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)