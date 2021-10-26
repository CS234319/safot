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

function thebe_init(kernel, selector, port) {
    thebelab.bootstrap({
        requestKernel: true,
        outputSelector: '[data-output]',
        kernelOptions: {
            name: kernel,
            kernelName: kernel,
            path: ".",
            serverSettings: {
                "baseUrl": `http://localhost:${port}`,
                "wsUrl": `ws://localhost:${port}`
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

function make_codeblock_editable(element) {
    const mode = element.dataset.language;
    const isReadOnly = element.dataset.readonly !== undefined;
    const text = element.innerText.trim();
    const cm = new CodeMirror(elt => {
        element.replaceChildren(elt);
    }, {
        value: text,
        mode: mode,
        theme: "idea",
        readonly: isReadOnly,
    });
    element.codemirror = cm;
}

function thebe_init_all(sub, port) {
    if (sub === "sml") {
        thebe_init("smlnj", "sml", port);
    } else if (sub === "theory") {
        thebe_init("python3", "python", port);
        thebe_init("javascript", "javascript", port);
    }
    for (const cb of document.querySelectorAll("[data-codeblock-editable]")) {
        make_codeblock_editable(cb);
    }
    const observer = new ResizeObserver(entries => {
        Reveal.layout();
        console.log("layout");
    });
    for (const elt of document.querySelectorAll(".jp-OutputArea")) {
        observer.observe(elt);
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

