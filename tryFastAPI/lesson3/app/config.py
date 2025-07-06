import os
from pydantic_settings import BaseSettings, SettingsConfigDict

env = os.getenv("ENV", "lcx_local")

class Settings(BaseSettings):
    db_url: str
    db_pool_size: int
    db_pool_recycle: int
    db_pool_timeout: int
    db_max_overflow: int
    db_connect_timeout: int
  
    model_config = SettingsConfigDict(env_file=f"config.{env}.env")


cfg = Settings()

print(cfg)

__all__ = ["cfg"]
