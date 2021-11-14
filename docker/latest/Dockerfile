FROM twyair/safot-revealjs:base

WORKDIR /home/safot

ENV DEBIAN_FRONTEND=noninteractive

COPY start.sh /home/safot
RUN git clone https://github.com/CS234319/safot.git
RUN cd safot/reveal.js; npm install --production
