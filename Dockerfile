FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++\
    boost-all-dev\
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /OK

COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --config Release -- -j$(nproc)

CMD ["./build/OK"]