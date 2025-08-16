import torch

def main():
    cuda_available = torch.cuda.is_available()
    print(f"CUDA available: {cuda_available}")
    if cuda_available:
        num_devices = torch.cuda.device_count()
        print(f"Number of CUDA devices: {num_devices}")
        for i in range(num_devices):
            print(f"Device {i}: {torch.cuda.get_device_name(i)}")
    else:
        print("No CUDA devices found.")

if __name__ == "__main__":
    main()    