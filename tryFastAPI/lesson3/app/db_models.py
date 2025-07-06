from datetime import datetime

import enum
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, String, DateTime, Integer, Enum, VARCHAR
# 得到默认Base基类
from db import Base

class TaskStatus(enum.Enum):
    analyzing = "进行中"
    finished = "已完成"
    archived = "已归档"
    committed= "待审核"

class Task(Base):
    __tablename__ = "task"    
    id = Column(Integer, autoincrement=True)
    uuid = Column(VARCHAR(128), nullable=False, primary_key=True, index=True)
    name = Column(String(60), comment="名称", nullable=False)
    description = Column(String(200), comment="描述", nullable=True)
    file_path = Column(String(200), comment="路径", nullable=False)
    size = Column(Integer, comment="大小", nullable=False)
    create_at = Column(DateTime, default=datetime.now, comment="创建时间")
    status = Column(Enum(TaskStatus), nullable=False)