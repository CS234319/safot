const { left, right } = require('./Configuration').highlightingBrackets

module.exports = class TextHighlighter {
	_genericHighlight(str, style, color, spanClass) {
		const l = left
		const r = right
		return `${l}${l}${style};${color};;${spanClass};${r}${str}${r}`
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
			`${l}${l}\(\[^;\]*;\)+${r}\(\[^${r}\]+\)${r}`, 'g'
		)

		return str.replace(re, '$2')
	}
}