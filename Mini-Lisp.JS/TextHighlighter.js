const { left, right } = require('./Configuration').highlightingBrackets

module.exports = class TextHighlighter {
	_genericHighlight(str, style, color, spanClass) {
		return `${left}${left}${style};${color};;${spanClass};${right}${str}${right}`
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
		const re = new RegExp(
			`${left}${left}\(\[^;\]*;\)+${right}\(\[^${right}\]+\)${right}`, 
			'g'
		)

		return str.replace(re, '$2')
	}
}