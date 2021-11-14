FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y curl
RUN curl -sL https://deb.nodesource.com/setup_14.x | bash -
RUN apt update
RUN apt install -y nodejs opam ipython3 jupyter jupyter-notebook git python3-pip
RUN pip3 install jupyter-server jupyterlab
RUN npm install -g npm@latest
RUN npm install -g ijavascript
RUN ijsinstall
RUN git clone https://github.com/twyair/simple-ismlnj.git /usr/share/jupyter/kernels/smlnj

EXPOSE 16788 16789

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

RUN ocaml-jupyter-opam-genspec
RUN jupyter kernelspec install --user --name ocaml-jupyter "$(opam var share)/jupyter"
