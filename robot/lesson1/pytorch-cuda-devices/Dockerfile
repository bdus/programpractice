FROM pytorch/pytorch:2.8.0-cuda12.9-cudnn9-runtime

WORKDIR /app

COPY print_cuda_devices.py .


RUN pip install --no-cache-dir torch

CMD ["python", "print_cuda_devices.py"]