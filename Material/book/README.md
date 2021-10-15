![PDF Build Status](https://github.com/yossigil/safot/workflows/PDF/badge.svg)
# Programming Language Course Text Book Tex Sources

## Clone and Compile

### Prerequesites

To clone the repository you'd need `git` installed on your computer. You _should_ probably use a POSIX system. Either Linux or Mac OS.

This project was not tested to compile successfully on Microsoft Windows.

On OSX, it was tested that `MacPorts` works well for installing `tex` related packages.

#### Tex Packages

1. `git`
2. `make`
3. `texlive-extra-utils` 
4. `texlive-lang-arabic`
5. `texlive-fonts-extra`
6. `texlive-xetex`
7. `texlive-science`

#### Fonts 

1. `ttf-mscorefonts-installer` (available with `apt`. Solves the `font "Times New Roman" cannot be found` issue, don't think it's needed on Mac)
2. You also need to install the fonts in [this zip file](https://drive.google.com/file/d/1y9sTd3x2OzyUanRpMJxpUXaa4D1ofB6l/view?usp=sharing)

##### Linux

Extracting the zip's contents to `~/.local/share/fonts` then running `fc-cache -f -v` should do the trick.

##### OSX

You need to:

1.  Download and extract the zip
2. Open `Font Book`
3. Click on the `+` to add new fonts
4. Locate the extracted folder
5. Double click it to install all the fonts it contains

### Cloning

Clone the repo from master (see [GitHub repo](https://github.com/yossigil/safot/))

### Compiling

After having all the fonts installed, you can compile the project by typing `make` to a terminal inside the project's root directory.

It is possible you will need to remove the short `\bash` section from the file `00.tex`.

## Editing

The majority of the document was editted using `gvim`.

Personally, I recommend editing using `kile`. It handles the Hebrew/English switches well enough.
