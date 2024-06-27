# 使用基础镜像
FROM ubuntu:20.04

# 设置环境变量
ENV DEBIAN_FRONTEND=noninteractive

# 更换为中科大源
RUN sed -i 's|http://archive.ubuntu.com/ubuntu/|http://mirrors.ustc.edu.cn/ubuntu/|g' /etc/apt/sources.list

# 更新软件包列表并安装所需的软件
RUN apt-get update && \
    apt-get install -y \
    git \
    build-essential \
    gdb-multiarch \
    qemu-system-misc \
    gcc-riscv64-linux-gnu \
    binutils-riscv64-linux-gnu && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# 创建用户
RUN useradd -ms /bin/bash shuaikai
RUN echo 'shuaikai:123456' | chpasswd
RUN usermod -aG sudo shuaikai

USER shuaikai
WORKDIR /home/shuaikai/

# 设置默认命令行
CMD ["/bin/bash"]