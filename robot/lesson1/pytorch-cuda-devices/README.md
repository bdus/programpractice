# PyTorch CUDA Devices

This project demonstrates how to use PyTorch with CUDA to check the number of available CUDA devices.

## Docker Setup

This project includes a Dockerfile that creates a Docker image based on `pytorch/pytorch:2.8.0-cuda12.9-cudnn9-runtime`. The image is configured to run a Python script that utilizes the PyTorch library to print the number of available CUDA devices.

## Building the Docker Image

To build the Docker image, navigate to the project directory and run the following command:

```bash
docker build -t pytorch-cuda-devices .
```

## Running the Docker Container

After building the image, you can run the Docker container with the following command:

```bash
docker run --rm pytorch-cuda-devices
```

This command will execute the Python script inside the container, which will output the number of available CUDA devices.

## Purpose

The purpose of this project is to provide a simple example of how to set up a Docker environment for PyTorch with CUDA support, allowing users to easily check the availability of CUDA devices on their system.

## Usage Example

Once the container is running, you should see output similar to the following, indicating the number of available CUDA devices:

```
Number of available CUDA devices: X
```

Where `X` is the count of detected CUDA devices.