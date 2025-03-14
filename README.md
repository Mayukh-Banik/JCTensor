JCTensor

Requirements:

SYCL:

```
sudo -i

apt upgrade && apt upgrade -y

apt-get update && apt-get install -y \
    git \
    cmake \
    g++ \
    make \
    libboost-all-dev \
    ninja-build \
    python3 \
    python3-pip \
    wget \
    curl \
    lsb-release \
    gnupg \
    software-properties-common \
    llvm \
    clang \
    libclang-dev

git clone https://github.com/AdaptiveCpp/AdaptiveCpp.git

cd AdaptiveCpp

mkdir build && cd build

cmake ..

make install -j ${nproc}
```
