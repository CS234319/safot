#!/bin/bash

TITLE="tutorial"
FILE="$1"
# TODO: support latex in markdown
pandoc -t html5 ${FILE} -o $(basename ${FILE}).pdf -s --pdf-engine=wkhtmltopdf --metadata pagetitle="${TITLE}" --highlight-style="pygments"