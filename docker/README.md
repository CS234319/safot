# dockerized slides

## install docker

### windows

follow the instructions [here](https://docs.docker.com/desktop/windows/install/)

you will install both the docker engine and an easy to use gui for it (Docker Desktop)

### ubuntu

follow the instructions [here](https://docs.docker.com/engine/install/ubuntu/)

## usage

### start the container

the following command pulls the image and runs it interactively

fire up powershell(windows) or bash(linux) and execute it (you may need to use `sudo` on linux)

```bash
docker run --pull="always" -p 127.0.0.1:16788:16788 -p 127.0.0.1:16789:16789 -it twyair/safot-revealjs:latest bash
```

### in the container

run:

```bash
source start.sh
```

### open slides

go to <http://127.0.0.1:16788/slides>
