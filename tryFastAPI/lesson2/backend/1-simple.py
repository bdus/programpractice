from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from typing import List, Dict
import uuid
from datetime import datetime, timedelta

app = FastAPI()

 # 允许跨域
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

# 内存存储
storage = {}

# 预注册一些示例数据
sample_items = [
    {"name": "示例项目1", "file_path": "/files/sample1.txt"},
    {"name": "示例项目2", "file_path": "/files/sample2.txt"},
    {"name": "示例项目3", "file_path": "/files/sample3.txt"}
]

for item in sample_items:
    item_uuid = str(uuid.uuid4())
    storage[item_uuid] = item

@app.get("/items")
def get_items():
    return { 'items': [{"uuid": uuid, "name": data["name"]} for uuid, data in storage.items()] }

@app.get("/items/{item_uuid}")
def get_item(item_uuid: str):
    if item_uuid not in storage:
        raise HTTPException(status_code=404, detail="Item not found")
    return storage[item_uuid]
    
if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)