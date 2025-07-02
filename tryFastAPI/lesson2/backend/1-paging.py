from fastapi import FastAPI, HTTPException, Query
from fastapi.middleware.cors import CORSMiddleware
import uuid
from typing import List, Dict
import time
import random
import json

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

# 生成示例数据
def generate_sample_data(num=100):
    projects = []
    for i in range(1, num + 1):
        item_id = str(uuid.uuid4())
        project = {
            "name": f"项目{i}",
            "description": f"这是项目{i}的详细描述",
            "file_path": f"/files/project_{i}.zip",
            "size": round(random.uniform(1.0, 100.0)),  # MB
            "created_at": int(time.time()) - random.randint(0, 1000000),
            "status": random.choice(["进行中", "已完成", "已归档", "待审核"])
        }
        storage[item_id] = project
        all_items.append({
            "uuid": item_id,
            "name": project["name"]
        })
    return projects

# 生成100个示例项目
generate_sample_data(100)

@app.get("/items")
def get_items(page: int = Query(1, ge=1), page_size: int = Query(10, ge=1, le=100)):
    start = (page - 1) * page_size
    end = start + page_size
    total = len(all_items)
    
    # 分页返回数据
    paginated_items = all_items[start:end]
    
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
        raise HTTPException(status_code=404, detail="Item not found")
    return storage[item_uuid]

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)