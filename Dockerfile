# Use a base image with a C++ environment, e.g., Ubuntu
FROM ubuntu:latest

# Install necessary packages
RUN apt-get update
RUN apt-get install -y \
    build-essential \
    cmake \
    libglu1-mesa-dev \
    freeglut3-dev \
    mesa-common-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    python3

# Optionally, install additional dependencies your project may require

# Set the working directory in the container
WORKDIR /app

# Copy your project files into the Docker container
COPY . /app

RUN cmake .
RUN make

CMD ["./rpg"]