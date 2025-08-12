FROM i386/debian:bullseye

# Actualiza e instala solo lo necesario
RUN dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get install -y \
    gcc \
    gdb \
    gdb \
    gdb-doc \ 
    gdbserver \ 
    gdb-peda \
    make \
    binutils \
    libc6-dev \
    build-essential \
    net-tools \
    vim \
    nano \
    file \
    strace \
    sudo \
    wget \
    git \
    curl

#pwndbg
RUN curl -qsL 'https://install.pwndbg.re' | sh -s -- -t pwndbg-gdb

# RADARE
RUN git clone https://github.com/radareorg/radare2
RUN radare2/sys/install.sh
RUN useradd -m -s /bin/bash testing
WORKDIR /share
# Deja listo el contenedor para compilar binarios vulnerables
CMD ["/bin/bash"]
