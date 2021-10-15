# programming languages slides

## install dependencies

```bash
sudo apt install nodejs npm jupyter-notebook zlib1g-dev libgmp-dev libzmq5-dev git
```

## sml jupyter kernel

install the kernel from <https://github.com/twyair/simple-ismlnj>

it is used for executing the sml code embedded in the slides

## install

```bash
git clone https://github.com/yossigil/safot.git

cd safot/reveal.js

npm install
```

## run

```bash
npm start
```

and on a different terminal:

```bash
npm run jupyter-server
```

go to <http://localhost:16788/>
