FROM python:3.9

WORKDIR /code

COPY ./requirements.txt /code/requirements.txt

RUN python3 -m pip install --no-cache-dir  --no-color --no-python-version-warning \
    --disable-pip-version-check --upgrade -r /code/requirements.txt

# 
COPY ./backend /code/backend
COPY ./frontend /code/frontend

EXPOSE 80
EXPOSE 443

CMD ["uvicorn", "backend.2-queue:app", "--host", "0.0.0.0", "--port", "80"]