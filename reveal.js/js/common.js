function thebe_init(kernel, mode, selector) {
    thebelab.bootstrap({
        bootstrap: true,
        requestKernel: true,
        outputSelector: '[data-output]',
        kernelOptions: {
            name: kernel,
            kernelName: kernel,
            path: ".",
            serverSettings: {
                "baseUrl": "http://localhost:16789",
                "wsUrl": "ws://localhost:16789"
            }
        },
        selector: `[data-thebe-executable-${selector}]`,
        mathjaxUrl: "https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js",
        mathjaxConfig: "TeX-AMS_CHTML-full,Safe",
        codeMirrorConfig: {
            mode: mode,
            theme: "monokai"
        },
        on_output_change: () => { Reveal.layout(); },
        on_execute: (cm) => {
            cm.display.input.blur();
        },
    });
}

const REVEAL_PARAMS = {
    hash: true,
    slideNumber: true,
    plugins: [ RevealMarkdown, RevealHighlight, RevealNotes, RevealMath ],
    keyboard: {
        39: 'next',
        37: 'prev'
    }
};

function init(kernel, mode, selector) {
    Reveal.initialize(REVEAL_PARAMS).then(() => thebe_init(kernel, mode, selector));
}