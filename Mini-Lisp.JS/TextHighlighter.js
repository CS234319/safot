module.exports = class TextHighlighter {
	_genericHighlight(str, style, color, spanClass) {	
		// return `««${style};${color};;${spanClass};»${str}»`
		return `[[${style};${color};;${spanClass};]${str}]`
	}

	apply(str, color) {
		return this._genericHighlight(str, '', color, '')
	}

	applyWithStyle(str, style, color) {
		return this._genericHighlight(str, style, color, '')
	}

	applyWithClass(str, spanClass) {
		return this._genericHighlight(str, '', '', spanClass)
	}

	remove(str) {
		// return str.replace(/««([^;]*;)+»([^»]+)»/g, '$2')
		return str.replace(/\[\[([^;]*;)+\]([^\]]+)\]/g, '$2')
	}
}