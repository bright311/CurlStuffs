FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    wget \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /deps

# Install Boost 1.84 from GitHub (contains Boost.JSON)
RUN wget https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.gz && \
    tar -xzf boost-1.84.0.tar.gz && \
    cd boost-1.84.0 && \
    ./bootstrap.sh && \
    ./b2 install

WORKDIR /app

COPY . .

RUN cmake -B build -S . && cmake --build build

EXPOSE 10000

CMD ["./build/OK"]



