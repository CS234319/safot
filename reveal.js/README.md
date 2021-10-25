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

npm install --production
```

## update

when in `safot/reveal.js` run:

```bash
git fetch
git pull
npm update .
```

## run

run the following commands:

```bash
npm start &
npm run jupyter-server &
```

### note

* `&` moves a process (job) to the background
* to handle these jobs use `bg`, `fg`, `jobs` and `CTRL+Z`
* see [this](https://www.thegeekdiary.com/understanding-the-job-control-commands-in-linux-bg-fg-and-ctrlz/) for a simple guide

## open slides

go to <http://localhost:16788/>

## TODO

* [ ] thebe: call `Reveal.layout()` when the output changes
