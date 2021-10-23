// FIXME: slow! calls lots of callbacks to refresh a single cm instance
// use the `auto_refresh` addon when it becomes available
CodeMirror.defineOption("autoRefresh", false, function (cm, val) {
    Reveal.on("slidechanged", event => {
        cm.refresh();
    });
});

CodeMirror.defineOption("blurOnExecute", false, function (cm, val) {
    cm.on("keydown", (cm, event) => {
        if (event.code == "Enter" && event.shiftKey) {
            cm.display.input.blur();
        }
    });
});

function thebe_init(kernel, selector) {
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
            theme: "idea",
            autoRefresh: true,
            blurOnExecute: true,
        },
    });
}

function thebe_init_all(sub) {
    if (sub === "sml") {
        thebe_init("smlnj", "sml");
    } else if (sub === "theory") {
        thebe_init("python3", "python");
        thebe_init("javascript", "javascript");
    }
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

