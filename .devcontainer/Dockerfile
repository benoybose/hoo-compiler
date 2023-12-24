FROM ubuntu:latest
RUN apt update
RUN apt install --yes llvm-15 llvm-15-dev cmake clang-15 \
    libclang-15-dev antlr4 libantlr4-runtime-dev default-jre \
    ninja-build git
RUN apt install --yes uuid uuid-dev zlib1g-dev gdb gdbserver libgtest-dev
RUN apt install --yes pkg-config cmake-data

ENV CC=/usr/bin/clang-15
ENV CXX=/usr/bin/clang++-15
ENV CMAKE_BUILD_TYPE=Debug
ENV CMAKE_GENERATOR=Ninja

# RUN git clone https://github.com/antlr/antlr4.git /tmp/antlr4
# WORKDIR /tmp/antlr4
# RUN git checkout tags/4.7.2
# RUN mkdir -p /tmp/antlr4/runtime/Cpp/build 
# WORKDIR /tmp/antlr4/runtime/Cpp/build
# RUN cmake .. -DANTLR4_INSTALL=ON -DANTLR_JAR_LOCATION=/usr/share/java/antlr4.jar
#RUN make


COPY ./antlr-4.7.2-complete.jar /usr/share/java/antlr-4.7.2-complete.jar
# ENV CC=/usr/bin/clang-15
# ENV CXX=/usr/bin/clang++-15
# ENV CMAKE_BUILD_TYPE=Debug
# ENV CMAKE_GENERATOR=Ninja

# # Dockerfile

# # Use Ubuntu 21.04 as the base image
# FROM ubuntu:latest

# # Install build tools
# RUN apt-get update && \
#     apt-get install -y build-essential cmake

# # Install LLVM and Clang
# RUN apt-get install -y clang-15 llvm-15

# # Install ANTLR4 and runtime
# RUN apt-get install -y antlr4 libantlr4-runtime-dev

# RUN mkdir -p /tmp/libs

# # Clone ANTLR4 C++ runtime repository
# RUN apt-get install -y git
# RUN git clone https://github.com/antlr/antlr4.git /tmp/libs/antlr4
# WORKDIR /tmp/libs/antlr4
# RUN git checkout tags/4.7.2
# WORKDIR /tmp/libs/antlr4/runtime/Cpp
# RUN apt-get install -y pkg-config uuid-dev
# RUN cmake -DANTLR4_INSTALL=ON . && \
#     make && \
#     make install


RUN apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

ENV SHELL /bin/bash
RUN mkdir -p /workspace
WORKDIR /workspace
