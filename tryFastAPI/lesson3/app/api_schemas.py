from pydantic import BaseModel
from enum import Enum
from typing import Optional
import uuid

class TaskStatus(str, Enum):
    PENDING = "pending"
    IN_PROGRESS = "in_progress"
    COMPLETED = "completed"
    FAILED = "failed"

class TaskBase(BaseModel):
    name: str
    description: Optional[str] = None
    file_path: str
    size: float

class TaskCreate(TaskBase):
    pass

class Task(TaskBase):
    id: int
    uuid: uuid.UUID
    status: TaskStatus
    
    class Config:
        from_attributes = True