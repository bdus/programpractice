from pydantic import BaseModel
from enum import Enum
from typing import Optional
import uuid

class TaskStatus(str, Enum):
    analyzing = "进行中"
    finished = "已完成"
    archived = "已归档"
    committed= "待审核"

class TaskBase(BaseModel):
    name: str
    description: Optional[str] = None
    file_path: str
    size: int

class TaskCreate(TaskBase):
    pass

class Task(TaskBase):    
    uuid: uuid.UUID
    status: TaskStatus
    
    class Config:
        from_attributes = True