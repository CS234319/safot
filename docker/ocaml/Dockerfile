FROM ubuntu:20.04

WORKDIR /workspace

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y software-properties-common
RUN add-apt-repository ppa:avsm/ppa
RUN apt update
RUN apt install -y opam git zip unzip build-essential
RUN apt install -y libgmp-dev libzmq3-dev pkg-config zlib1g-dev
RUN apt install -y python3 python3-pip
RUN pip install jupyterlab

RUN sysctl kernel.unprivileged_userns_clone=1
RUN useradd -ms /bin/bash safot
USER safot:safot
WORKDIR /home/safot

RUN opam init --bare -a -y
RUN opam update
RUN opam switch create safot ocaml-base-compiler.4.12.0
RUN opam switch safot
RUN eval $(opam env)

RUN opam install -y jupyter dune utop merlin odoc ounit2 qcheck bisect_ppx menhir ocaml-lsp-server ocamlformat ocamlformat-rpc

RUN eval $(opam env); ocaml-jupyter-opam-genspec
RUN jupyter kernelspec install --user --name ocaml-jupyter "$(opam var share)/jupyter"
RUN echo 'eval $(opam env)' >> .bashrc

EXPOSE 8888
