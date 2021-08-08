function thebe_init() {
    thebelab.bootstrap({
        bootstrap: true,
        requestKernel: true,
        outputSelector: '[data-output]',
        kernelOptions: {
            name: "ocaml-jupyter-4.12.0",
            kernelName: "ocaml-jupyter-4.12.0",
            path: ".",
            serverSettings: {
                "baseUrl": "http://localhost:16789",
                "wsUrl": "ws://localhost:16789"
            }
        },
        selector: "[data-thebe-executable-ocaml]",
        mathjaxUrl: "https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js",
        mathjaxConfig: "TeX-AMS_CHTML-full,Safe",
        codeMirrorConfig: {
            mode: "text/x-ocaml",
            theme: "monokai"
        },
        on_output_change: () => { Reveal.layout(); },
        on_execute: (cm) => {
            cm.display.input.blur();
        },
    });
}

Reveal.initialize({
    hash: true,
    slideNumber: true,
    plugins: [ RevealMarkdown, RevealHighlight, RevealNotes, RevealMath ],
    keyboard: {
        39: 'next',
        37: 'prev'
    }
}).then(thebe_init);