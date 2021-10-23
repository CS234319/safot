# programming languages slides

## install dependencies

```bash
sudo apt install smlnj ipython3 nodejs npm jupyter-notebook zlib1g-dev libgmp-dev libzmq5-dev git
sudo pip3 install jupyter-server
```

## sml jupyter kernel

install the kernel from <https://github.com/twyair/simple-ismlnj>

## javascript jupyter kernel

install the kernel from <https://github.com/n-riesco/ijavascript>

## install

```bash
git clone https://github.com/CS234319/safot.git

cd safot/reveal.js

npm install
```

## update

when in `safot/reveal.js` run:

```bash
git fetch
git pull
npm update .
```

## run

run the following commands on separate terminals:

```bash
npm start
```

```bash
npm run jupyter-server
```

go to <http://localhost:16788/>
