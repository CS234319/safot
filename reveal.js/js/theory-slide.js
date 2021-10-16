function thebe_init() {
    thebelab.bootstrap({
        bootstrap: true,
        requestKernel: true,
        outputSelector: '[data-output]',
        kernelOptions: {
            name: "python3",
            kernelName: "python3",
            path: ".",
            serverSettings: {
                "baseUrl": "http://localhost:16789",
                "wsUrl": "ws://localhost:16789"
            }
        },
        selector: "[data-thebe-executable-python]",
        mathjaxUrl: "https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js",
        mathjaxConfig: "TeX-AMS_CHTML-full,Safe",
        codeMirrorConfig: {
            mode: "text/x-python",
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