FROM ubuntu:20.04

WORKDIR /workspace

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y software-properties-common
RUN add-apt-repository ppa:avsm/ppa
RUN apt update
RUN apt install -y opam git zip unzip build-essential

RUN sysctl kernel.unprivileged_userns_clone=1
RUN useradd -ms /bin/bash safot
USER safot:safot
WORKDIR /home/safot

RUN opam init --bare -a -y
RUN opam update
RUN opam switch create safot ocaml-base-compiler.4.12.0
RUN opam switch safot
RUN eval $(opam env)
RUN opam install -y dune utop merlin odoc ounit2 qcheck bisect_ppx menhir ocaml-lsp-server ocamlformat ocamlformat-rpc
