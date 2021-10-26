const gulp = require("gulp");
const connect = require("gulp-connect");
var fs = require("fs");
var path = require("path");
var Handlebars = require("handlebars");
const yargs = require('yargs/yargs');
const { hideBin } = require('yargs/helpers');
const argv = yargs(hideBin(process.argv)).argv;

function buildHtml(output_dir, renderTemplate, name, dir) {
    var html = renderTemplate({ tutorial_name: name, sub: dir, port: argv.portjupyter, });
    fs.writeFile(`${output_dir}/${dir}-${name}.html`, html, (err) => {
        if (err) {
            console.log(err);
            process.exit(1);
        }
    });
}

const output_dir = path.join(__dirname, "slides");
const md_dir = path.join(__dirname, path.join("material", "Tutorials"));

function generate_slides(template_name, dir) {
    fs.readdir(path.join(md_dir, dir), (err, files) => {
        if (err) {
            console.error("Could not list the directory.", err);
            process.exit(1);
        }

        var template = fs.readFileSync(
            path.resolve(path.join(__dirname, template_name)),
            "utf-8"
        );
        var renderTemplate = Handlebars.compile(template);

        files.forEach((file, _index) => {
            if (file.endsWith(".md")) {
                buildHtml(
                    output_dir,
                    renderTemplate,
                    file.substring(0, file.length - 3),
                    dir
                );
            }
        });
    });
}

gulp.task("reload", () => gulp.src(["*.html", "*.md"]).pipe(connect.reload()));

gulp.task("serve", () => {
    if (!fs.existsSync(output_dir)) {
        fs.mkdirSync(output_dir);
    }
    generate_slides("slide.hbs", "sml");
    generate_slides("slide.hbs", "prolog");
    generate_slides("slide.hbs", "theory");

    const cors = function (req, res, next) {
        res.setHeader("Access-Control-Allow-Private-Network", "true");
        if (req.url.startsWith("/thebe/")) {
            req.url = "/node_modules" + req.url;
        }
        next();
    };

    connect.server({
        root: ".",
        port: argv.port,
        host: argv.ip || "localhost",
        livereload: true,
        middleware: function () {
            return [cors];
        },
    });

    gulp.watch(["material/Tutorials/*/*.md", "index.html"], gulp.series("reload"));
});
