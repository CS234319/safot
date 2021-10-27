FROM twyair/safot-revealjs:base

WORKDIR /usr/src/app

ENV DEBIAN_FRONTEND=noninteractive

COPY start.sh /usr/src/app/
RUN git clone https://github.com/CS234319/safot.git
RUN cd safot/reveal.js; npm install --production
