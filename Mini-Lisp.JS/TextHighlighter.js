module.exports = class TextHighlighter {
	_genericHighlight(str, style, color, spanClass) {	
		return `[[${style};${color};;${spanClass};]${str}]`
	}

	highlight(str, color) {
		return this._genericHighlight(str, '', color, '')
	}

	highlightWithStyle(str, style, color) {
		return this._genericHighlight(str, style, color, '')
	}

	highlightWithClass(str, spanClass) {
		return this._genericHighlight(str, '', '', spanClass)
	}

	removeHighlight(str) {
		return str.replace(/\[\[([^;]*;)+\]([^\]]+)\]/g, '$2')
	}
}