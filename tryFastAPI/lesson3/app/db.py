from sqlalchemy.engine import create_engine
from sqlalchemy.engine.base import Engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from sqlalchemy_utils import database_exists, create_database

from config import cfg

url = cfg.db_url
# connect_args = {"connect_timeout": cfg.db_connect_timeout}

engine: Engine = create_engine(
    url,
    echo=True,
    pool_size=cfg.db_pool_size,
    pool_recycle=cfg.db_pool_recycle,
    pool_timeout=cfg.db_pool_timeout,
    max_overflow=cfg.db_max_overflow,
    # connect_args=connect_args,
)

if not database_exists(engine.url):
    create_database(engine.url)

SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

Base = declarative_base()

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
