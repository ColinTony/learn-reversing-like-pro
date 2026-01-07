FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# 🛠️ Actualiza e instala dependencias base
RUN dpkg --add-architecture i386 && \
    apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    gdb \
    gdb-doc \
    gdbserver \
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
    sudo \
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
    iputils-ping \
    libc6:i386 \
    libstdc++6:i386

# 🧠 Configura locale
RUN locale-gen en_US.UTF-8

# 🧠 Instala herramientas de exploit en Python
RUN pip3 install --upgrade pip setuptools wheel
RUN pip3 install pwntools ropper one_gadget

# 🐍 Instala GEF para GDB
RUN bash -c "$(curl -fsSL https://gef.blah.cat/sh)"

# 🔍 Instala radare2 desde fuente (versión más reciente)
# 🔍 Instala radare2 desde fuente (versión más reciente, git + meson)
RUN pip3 install meson ninja
RUN git clone https://github.com/radareorg/radare2 /tmp/radare2 && \
    cd /tmp/radare2 && \
    meson setup build && \
    sed -i 's/unsigned short cw;/; unsigned short cw;/g' subprojects/qjs/cutils.h && \
    ninja -C build && \
    ninja -C build install && \
    ldconfig && \
    rm -rf /tmp/radare2
RUN useradd -m -s /bin/bash testing
RUN echo "testing ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
# instalando pwndbg
RUN curl -qsL 'https://install.pwndbg.re' | sh -s -- -t pwndbg-gdb

# === Protostar stack binaries with SUID ===
RUN mkdir -p /opt/protostar/bin
RUN mkdir -p /opt/ejercicios/bin

COPY ./WarGames/protostar_build/protostar/bin/stack* /opt/protostar/bin/
COPY ./WarGames/ejercicios/*.c /opt/ejercicios/bin/

# Compilacion de ejericcios
RUN cd /opt/ejercicios/bin/ && gcc -fno-stack-protector -z execstack ./p100.c -o ./p100

# Propietario root y SUID (rws para root)
RUN chown root:root /opt/protostar/bin/
RUN chmod 4755 /opt/protostar/bin/stack*
RUN chmod 4755 /opt/ejercicios/bin/*
RUN chmod 600 /opt/ejercicios/bin/*.c


# 📁 Carpeta de trabajo
WORKDIR /share
USER testing
CMD ["/bin/bash"]
