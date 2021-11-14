FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y curl
RUN curl -sL https://deb.nodesource.com/setup_14.x | bash -
RUN apt update
RUN apt install -y nodejs smlnj ipython3 jupyter jupyter-notebook git python3-pip
RUN pip3 install jupyter-server jupyterlab
RUN npm install -g npm@latest
RUN npm install -g ijavascript
RUN ijsinstall
RUN git clone https://github.com/twyair/simple-ismlnj.git /usr/share/jupyter/kernels/smlnj

EXPOSE 16788 16789

RUN useradd -ms /bin/bash safot
USER safot:safot
WORKDIR /home/safot
