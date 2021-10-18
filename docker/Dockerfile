FROM ubuntu:20.04

WORKDIR /usr/src/app

COPY docker.sh .

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y curl
RUN curl -sL https://deb.nodesource.com/setup_14.x | bash -
RUN apt update
RUN apt install -y nodejs smlnj ipython3 jupyter-notebook zlib1g-dev libgmp-dev libzmq5-dev git python3-pip
RUN pip3 install jupyter-server
RUN git clone https://github.com/CS234319/safot.git
RUN cd safot/reveal.js; npm install

EXPOSE 16788
EXPOSE 16789

CMD ["bash", "docker.sh"]