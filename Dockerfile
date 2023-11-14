FROM manjarolinux/base:latest

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm \
    base-devel \
    cmake \
    glu \
    freeglut \
    mesa \
    libxrandr \
    libxinerama \
    libxcursor \
    libxi \
    python

# Optionally, install additional dependencies your project may require

# Set the working directory in the container
WORKDIR /app
