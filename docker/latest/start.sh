#!/bin/bash

cd safot/reveal.js
npm run --ip=0.0.0.0 start &
npm run --ip=0.0.0.0 jupyter-server &
