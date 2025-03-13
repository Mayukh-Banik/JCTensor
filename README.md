JCTensor

Requirements:

OpenCL -> Just for hardware identification 

Intel/Nvidia use default OpenCL implementations

AMD: use POCL, 
```
sudo apt install pocl-opencl-icd pocl-opencl-dev python3-dev libpython3-dev build-essential ocl-icd-libopencl1 cmake git pkg-config libclang-dev clang llvm make ninja-build ocl-icd-libopencl1 ocl-icd-dev ocl-icd-opencl-dev libhwloc-dev zlib1g zlib1g-dev clinfo dialog apt-utils libxml2-dev libclang-cpp-dev libclang-cpp llvm-dev
```