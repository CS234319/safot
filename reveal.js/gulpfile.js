const gulp = require("gulp");
const connect = require("gulp-connect");
const fs = require("fs");
const path = require("path");
const Handlebars = require("handlebars");
const yargs = require('yargs/yargs');
const { hideBin } = require('yargs/helpers');
const argv = yargs(hideBin(process.argv)).argv;

const OUTPUT_DIR = path.join(__dirname, "slides");
const MD_DIR = path.join(__dirname, "material", "Tutorials");
const TEMPLATE_PATH = path.join(__dirname, "slide.hbs");
const SUBS = ["ocaml", "sml", "prolog", "python", "theory"];

function generate_slides(dir, template) {
    fs.readdir(path.join(MD_DIR, dir), (err, files) => {
        if (err) {
            console.error("Could not list the directory.", err);
            process.exit(1);
        }

        files.forEach((file, _index) => {
            if (file.endsWith(".md")) {
                const name = file.substring(0, file.length - 3);
                const html = template({ tutorial_name: name, sub: dir, port: argv.portjupyter, });
                fs.writeFile(`${OUTPUT_DIR}/${dir}-${name}.html`, html, (err) => {
                    if (err) {
                        console.error(err);
                        process.exit(1);
                    }
                });
            }
        });
    });
}

gulp.task("reload", () => gulp.src(["*.html", "*.md"]).pipe(connect.reload()));

gulp.task("serve", () => {
    if (!fs.existsSync(OUTPUT_DIR)) {
        fs.mkdirSync(OUTPUT_DIR);
    }

    const template = Handlebars.compile(fs.readFileSync(
        path.resolve(TEMPLATE_PATH),
        "utf-8"
    ));
    for (const sub of SUBS) {
        generate_slides(sub, template);
    }

    connect.server({
        root: ".",
        port: argv.port,
        host: argv.ip || "localhost",
        livereload: true,
        middleware: () => {
            return [(req, res, next) => {
                res.setHeader("Access-Control-Allow-Private-Network", "true");
                if (req.url.startsWith("/thebe/")) {
                    req.url = "/node_modules" + req.url;
                }
                next();
            }];
        },
    });

    gulp.watch(["material/Tutorials/*/*.md"], gulp.series("reload"));
});
