FROM twyair/safot-revealjs:base

WORKDIR /usr/src/app

ENV DEBIAN_FRONTEND=noninteractive

RUN git clone https://github.com/CS234319/safot.git
RUN cd safot/reveal.js; npm install --production
