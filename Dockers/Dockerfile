FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# 🛠️ Actualiza e instala dependencias base
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    gdb \
    python3 \
    python3-pip \
    python3-dev \
    python3-venv \
    git \
    curl \
    wget \
    nano \
    vim \
    netcat \
    socat \
    file \
    unzip \
    tmux \
    pwgen \
    libssl-dev \
    libffi-dev \
    cmake \
    pkg-config \
    autoconf \
    automake \
    libtool-bin \
    libzip-dev \
    libcapstone-dev \
    zsh \
    locales \
    xz-utils \
    ca-certificates \
    iputils-ping

# 🧠 Configura locale
RUN locale-gen en_US.UTF-8

# 🧠 Instala herramientas de exploit en Python
RUN pip3 install --upgrade pip setuptools wheel
RUN pip3 install pwntools ropper one_gadget

# 🐍 Instala GEF para GDB
RUN bash -c "$(curl -fsSL https://gef.blah.cat/sh)"

# 🔍 Instala radare2 desde fuente (versión más reciente)
RUN git clone --depth=1 https://github.com/radareorg/radare2 /opt/radare2 && \
    /opt/radare2/sys/install.sh && \
    rm -rf /opt/radare2

# 📁 Carpeta de trabajo
WORKDIR /ctf
CMD ["/bin/bash"]
