from sqlalchemy.orm import Session
import uuid
import db_models, api_schemas

@staticmethod
def get_task(db: Session, task_id: int):
    return db.query(db_models.Task).filter(db_models.Task.id == task_id).first()

@staticmethod
def get_task_by_uuid(db: Session, task_uuid: uuid.UUID):
    return db.query(db_models.Task).filter(db_models.Task.uuid == task_uuid).first()

@staticmethod
def get_tasks(db: Session, skip: int = 0, limit: int = 100):
    return db.query(db_models.Task).offset(skip).limit(limit).all()

@staticmethod
def create_task(db: Session, task: api_schemas.TaskCreate):
    db_task = db_models.Task(
        uuid = str(uuid.uuid4()),
        name=task.name,
        description=task.description,
        file_path=task.file_path,
        size=task.size,
        status=db_models.TaskStatus.analyzing
    )
    db.add(db_task)
    db.commit()
    db.refresh(db_task)
    return db_task

@staticmethod
def update_task_status(db: Session, task_uuid: uuid.UUID, new_status: db_models.TaskStatus):
    db_task = get_task_by_uuid(db, task_uuid)
    if db_task:
        db_task.status = new_status
        db.commit()
        db.refresh(db_task)
    return db_task

@staticmethod
def delete_task(db: Session, task_uuid: uuid.UUID):
    db_task = get_task_by_uuid(db, task_uuid)
    if db_task:
        db.delete(db_task)
        db.commit()
    return db_task