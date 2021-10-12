# programming languages slides

## requirements

- npm
- nodejs
- jupyter-notebook
- ocaml 4.12
- ocaml-merlin <https://github.com/ocaml/merlin>
- ocaml-jupyter <https://github.com/akabe/ocaml-jupyter>

### install dependencies

```bash
sudo apt install nodejs npm opam jupyter-notebook zlib1g-dev libgmp-dev libzmq5-dev git
```

### ocaml + ocaml packages

```bash
opam switch create 4.12.0 ocaml-variants.4.12.0+options
eval $(opam env)
opam install merlin jupyter ocaml-lsp-server 
```

### setup ocaml-jupyter

```bash
ocaml-jupyter-opam-genspec
jupyter kernelspec install [ --user ] --name ocaml-jupyter "$(opam var share)/jupyter"
```

## install

```bash
git clone https://github.com/yossigil/safot.git

cd safot/tutorials

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

## TODO

- [ ] write an OCaml tutorial about:
  - [X] functors
  - [X] imperative features
  - [X] references
  - [ ] labels and optional arguments
  - [ ] polymorphic variants
  - [ ] mutable data structures (`Hashtbl`, `Array`, ...)
  - [ ] objects and classes (?)
  - [ ] standard library modules (?)
- [X] write about the so-called sequencing operator (`;`) of OCaml
- [X] adapt the SML notebooks to OCaml
- [ ] write the prolog tutorials
- [X] autogenerate the files in slides/
- [X] find a way to call `Reveal.layout()` whenever a slide changes
- [ ] feature idea for `thebe`: make the kernel execute certain cells on load or when they first appear
- [ ] in `ocaml-tut3-b.md` replace the `SortedList` example (?)
