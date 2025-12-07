FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    wget \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /deps

# Install Boost manually (with Boost.JSON)
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.84.0/source/boost_1_84_0.tar.gz && \
    tar xf boost_1_84_0.tar.gz && \
    cd boost_1_84_0 && \
    ./bootstrap.sh && \
    ./b2 install

WORKDIR /app

COPY . .

RUN cmake -B build -S . && cmake --build build

EXPOSE 5000

CMD ["./build/OK"]

