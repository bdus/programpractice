from fastapi import FastAPI, HTTPException, Query
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import uuid
import time
import random
import threading
import queue
import json
from typing import List, Dict

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

# 项目创建模型
class ItemCreate(BaseModel):
    name: str
    description: str
    file_path: str
    size: float

# 后台任务处理线程
def process_items():
    while True:
        with queue_lock:
            if not task_queue.empty():
                item_uuid = task_queue.get()
                
                # 检查项目是否存在
                if item_uuid not in storage:
                    print(f"项目 {item_uuid} 已被删除，跳过处理")
                    continue
                    
                # 处理任务：模拟耗时操作
                process_time = random.uniform(1.0, 3.0)
                time.sleep(process_time)
                
                # 更新项目状态
                if item_uuid in storage:
                    storage[item_uuid]["status"] = "已完成"
                    print(f"项目 {item_uuid} 处理完成, 耗时: {process_time:.2f}秒")
        time.sleep(0.5)  # 避免空转

# 启动后台线程
processing_thread = threading.Thread(target=process_items, daemon=True)
processing_thread.start()

# 生成示例数据
def generate_sample_data(num=100):
    for i in range(1, num + 1):
        item_uuid = str(uuid.uuid4())
        project = {
            "name": f"项目{i}",
            "description": f"这是项目{i}的详细描述",
            "file_path": f"/files/project_{i}.zip",
            "size": round(random.uniform(1.0, 100.0), 2),
            "created_at": int(time.time()) - random.randint(0, 1000000),
            "status": random.choice(["进行中", "已完成", "已归档", "待审核"])
        }
        storage[item_uuid] = project
        all_items.append({
            "uuid": item_uuid,
            "name": project["name"]
        })
    return storage

# 生成100个示例项目
generate_sample_data(1)

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
            item["status"] = "已删除"
    
    return {
        "items": paginated_items,
        "page": page,
        "page_size": page_size,
        "total": total,
        "total_pages": (total + page_size - 1) // page_size
    }

@app.get("/items/{item_uuid}")
def get_item(item_uuid: str):
    if item_uuid not in storage:
        raise HTTPException(status_code=404, detail="项目不存在或已被删除")
    return storage[item_uuid]

@app.post("/items/")
def create_item(item: ItemCreate):
    item_uuid = str(uuid.uuid4())
    
    # 创建新项目
    new_item = {
        "name": item.name,
        "description": item.description,
        "file_path": item.file_path,
        "size": item.size,
        "created_at": int(time.time()),
        "status": "进行中"  # 初始状态
    }
    
    # 存储项目
    storage[item_uuid] = new_item
    all_items.insert(0, {
        "uuid": item_uuid,
        "name": new_item["name"]
    })
    
    # 添加到任务队列
    with queue_lock:
        task_queue.put(item_uuid)
        print(f"新项目已创建并添加到队列: {item_uuid}")
    
    return {
        "uuid": item_uuid,
        "message": "项目创建成功，已加入处理队列",
        "status": "进行中"
    }

@app.delete("/items/{item_uuid}")
def delete_item(item_uuid: str):
    if item_uuid not in storage:
        raise HTTPException(status_code=404, detail="项目不存在或已被删除")
    
    # 从存储中删除
    del storage[item_uuid]
    
    # 从项目列表中删除
    global all_items
    all_items = [item for item in all_items if item["uuid"] != item_uuid]
    
    # 尝试从任务队列中删除（如果存在）
    with queue_lock:
        # 创建一个新队列，排除要删除的项目
        new_queue = queue.Queue()
        while not task_queue.empty():
            queued_uuid = task_queue.get()
            if queued_uuid != item_uuid:
                new_queue.put(queued_uuid)
        
        # 将剩余项目放回原队列
        while not new_queue.empty():
            task_queue.put(new_queue.get())
    
    return {"message": f"项目 {item_uuid} 已成功删除"}

@app.get("/queue/status")
def get_queue_status():
    with queue_lock:
        queue_size = task_queue.qsize()
        queue_items = list(task_queue.queue)
    
    return {
        "queue_size": queue_size,
        "items_in_queue": queue_items
    }

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)