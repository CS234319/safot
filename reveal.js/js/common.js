// FIXME: slow! calls lots of callbacks to refresh a single cm instance
// use the `auto_refresh` addon when it becomes available
CodeMirror.defineOption("autoRefresh", false, function (cm, val) {
    Reveal.on("slidechanged", event => {
        cm.refresh();
    });
});

function thebe_init(kernel, mode, selector) {
    thebelab.bootstrap({
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
        codeMirrorConfig: {
            mode: mode,
            theme: "idea",
            autoRefresh: true,
        },
        // on_output_change: () => { Reveal.layout(); },
        // on_execute: (cm) => {
        //     cm.display.input.blur();
        // },
    });
}

const REVEAL_PARAMS = {
    hash: true,
    slideNumber: true,
    plugins: [RevealMarkdown, RevealHighlight, RevealNotes, RevealMath],
    keyboard: {
        39: 'next',
        37: 'prev'
    }
};

