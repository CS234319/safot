FROM ubuntu:20.04

WORKDIR /usr/src/app

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt update
RUN apt install -y smlnj git jupyter python3-pip
RUN pip3 install jupyter-server jupyterlab
RUN git clone https://github.com/twyair/simple-ismlnj.git
RUN ln -s /usr/src/app/simple-ismlnj /usr/share/jupyter/kernels/smlnj

EXPOSE 16788

ENTRYPOINT [ "jupyter-lab", "--allow-root", "--ServerApp.ip='0.0.0.0'", "--ServerApp.token=''", "--ServerApp.password=''", "--ServerApp.allow_origin='*'", "--ServerApp.disable_check_xsrf=True", "--no-browser", "--ServerApp.port=16788" ]