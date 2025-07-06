from fastapi import FastAPI, HTTPException, Query, Depends
from fastapi.middleware.cors import CORSMiddleware
from sqlalchemy.orm import Session
from pydantic import BaseModel
import time, random, threading
from typing import List, Dict

import crud, api_schemas
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

def process_tasks(db: SessionLocal):
    while True:
        try:
            # 获取所有进行中的任务
            tasks = db.query(Task)\
                .filter(Task.status == TaskStatus.analyzing)\
                .all()            
            for task in tasks:
                # 模拟处理时间
                process_time = random.uniform(1.0, 3.0)
                time.sleep(process_time)                
                # 更新任务状态
                task.status =TaskStatus.finished
                db.commit()
                print(f"任务 {task.uuid} 处理完成, 耗时: {process_time:.2f}秒")                
        except Exception as e:
            print(f"任务处理出错: {str(e)}")
            db.rollback()            
        time.sleep(5)  # 每5秒检查一次新任务


@app.get("/tasks/", response_model=list[api_schemas.Task])
def list_tasks(skip: int = 0, limit: int = 100, db: Session = Depends(get_db)):
    tasks = crud.get_tasks(db, skip=skip, limit=limit)
    return tasks


@app.get("/tasks/{task_uuid}", response_model= api_schemas.Task)
def get_item_by_uuid(task_uuid: str, db : Session = Depends(get_db)):
    entity = crud.get_task_by_uuid(db, task_uuid)     
    if entity is None:
        raise HTTPException(status_code=404, detail="Item not found")   
    return entity


@app.post("/tasks/")
def create_task(task: api_schemas.TaskCreate, db : Session = Depends(get_db)):
    new_task = crud.create_task(db, task)
    return {
        "uuid": new_task.uuid,
        "message": "项目创建成功，已加入处理队列",
        "status": "进行中"
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
    # 启动后台线程
    db = SessionLocal()
    processing_thread = threading.Thread(target=process_tasks, args=(db,), daemon=True)
    processing_thread.start()    


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)