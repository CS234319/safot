const TextHighlighter = require('./TextHighlighter')
const replDelegate = require('./REPLDelegate')
const primitives = require('./PrimitiveKeywords')
require('./ArrayExtension')

const th = new TextHighlighter()

class Element {
	constructor(value) {
		this.value = value
	}

	buildText() {
		return this.value
	}

	predefineSymbolsColor(color, symbolValues) {
		this.value.predefineSymbolsColor(color, symbolValues)
	}

	cancelSymbolsPredefinedColor() {
		this.predefineSymbolsColor()
	}

	getSymbolsOfList() {}
}

class Format extends Element {
	buildText() {
		return th.highlight(this.value.buildText(), Format.DefaultColor)
	}

	static DefaultColor = '#d7deea'
}

class Comment extends Element {
	buildText() {
		return th.highlightWithStyle(this.value, Comment.Style, Comment.Color)
	}

	static Style = 'i'
	static Color = '#296d98'
}

class Padding extends Element {
	buildText() {
		return this.value.map(o => o.buildText?.() ?? o).join('')
	}
}

class SSymbol extends Element {
	buildText() {
		const color = 
			this.predefinedColor ? this.predefinedColor :
			this._isGlobal() ? SSymbol.Colors.global :
			this._isPrimitive() ? SSymbol.Colors.primitive :
			undefined

		return color ? th.highlight(this.value, color) : this.value
	}

	predefineSymbolsColor(color, symbolValues) {
		if (symbolValues?.includes(this.value) ?? true) {
			this.predefinedColor = color
		}
	}

	cancelMatchedParentheses() {}

	_isGlobal() {
		return replDelegate.getGlobals().includes(this.value.toUpperCase())
	}

	_isPrimitive() {
		return primitives.includes(this.value.toLowerCase())
	}

	static Colors = {
		global: '#ff5261',
		primitive: '#39b6b5'
	}
}

class Nil extends SSymbol {
	getSymbolsOfList() {
		return []
	}
}

class Quote extends Element {
	constructor(mark, value) {
		super(value)
		this.mark = mark
		this.didMatchParentheses = value?.didMatchParentheses
		value?.predefineSymbolsColor(Quote.Color)
	}

	predefineSymbolsColor() {
		return
	}

	buildText() {
		const text = this.value?.buildText() ?? ''
		return th.highlight(this.mark + text, Quote.Color)
	}

	cancelMatchedParentheses() {
		this.value.cancelMatchedParentheses()
	}

	static Color = '#ffab42'
}

class SArrayElement extends Element {
	constructor(sArray) {
		super(sArray)
		this.didMatchParentheses = this.value.some(s => s.didMatchParentheses)
		this.value.findSecondLast()?.cancelMatchedParentheses()
	}

	predefineSymbolsColor(color, symbolValues) {
		this.value.forEach(s => s.predefineSymbolsColor(color, symbolValues))
	}
}

class Pair extends SArrayElement {
	constructor(car, dot, cdr) {
		super([car, cdr].filterNullish())
		this.car = car
		this.dot = dot
		this.cdr = cdr
	}

	buildText() {
		return this.car.buildText() + this.dot + (this.cdr?.buildText() ?? '')
	}

	getSymbolsOfList() {
		let list = this.cdr ? this.cdr.value.getSymbolsOfList() : []

		if (this.car.value instanceof SSymbol) {
			list?.unshift(this.car.value)
		}

		return list
	}
}

class List extends SArrayElement {
	constructor(sArray) {
		super(sArray)
	}

	buildText() {
		return this.value.map(s => s.buildText()).join('')
	}

	getSymbolsOfList() {
		return this.value
			.map(s => s.value)
			.filter(v => v instanceof SSymbol)
	}
}

class Complex extends Element {
	constructor(location, lparen, value, rparen) {
		super(value)
		this.lparen = lparen
		this.rparen = rparen
		this.didMatchParentheses = value.didMatchParentheses

		if (location && this.lparen && this.rparen && !this.didMatchParentheses) {
			this._tryMatchParentheses(location)
		}
	}

	buildText() {
		return (this.lparen ?? '') + this.value.buildText() + (this.rparen ?? '')
	}

	getSymbolsOfList() {
		return this.value.getSymbolsOfList()
	}

	cancelMatchedParentheses() {
		if (!this.lparen || !this.rparen) {
			return
		}

		this.lparen = th.removeHighlight(this.lparen)
		this.rparen = th.removeHighlight(this.rparen)
	}

	_tryMatchParentheses(location) {
		const lparenPos = location.start.offset
		const rparenPos = location.end.offset
		const cursorPos = replDelegate.getCursorPosition()

		if (cursorPos < lparenPos || cursorPos > rparenPos) {
			return
		}
		
		this.didMatchParentheses = true
		this._highlightParentheses(lparenPos, rparenPos, cursorPos)
	}

	_highlightParentheses(lparenPos, rparenPos, cursorPos) {
		const spanClass =  [
			lparenPos - 1, lparenPos, rparenPos, lparenPos + 1
		].includes(cursorPos)
			? Complex.parenClasses.highlighted
			: Complex.parenClasses.highlightInner

		this.lparen = th.highlightWithClass(this.lparen, spanClass)
		this.rparen = th.highlightWithClass(this.rparen, spanClass)
	}

	static parenClasses = {
		highlighted: 'parenHighlight',
		highlightInner: 'parenHighlightInner'
	}
}

class S extends Element {
	constructor(lPadding, value, rPadding) {
		super(value)
		this.lPadding = lPadding
		this.rPadding = rPadding
		this.didMatchParentheses = value.didMatchParentheses
	}

	buildText() {
		return 	this.lPadding.buildText() + 
				this.value.buildText() +
				this.rPadding.buildText()
	}

	cancelMatchedParentheses() {
		this.value.cancelMatchedParentheses()
	}
}

class DefunName extends S {
	constructor(lPadding, symbol, rPadding) {
		super(lPadding, symbol, rPadding)
		symbol.predefinedColor = DefunName.Color
	}

	static Color = '#ff724c'
}

class Formals extends S {
	constructor(lPadding, complex, rPadding) {
		super(lPadding, complex, rPadding)

		complex.cancelSymbolsPredefinedColor()
		
		complex.getSymbolsOfList()?.forEach(sym => {
			sym.predefinedColor = Formals.Color
		})
	}

	getSymbolValues() {
		return this.value.getSymbolsOfList()?.map(sym => sym.value) ?? []
	}

	static Color = '#cf91c9'
}

class Body extends S {
	constructor(s, formals) {
		super(s.lPadding, s.value, s.rPadding)
		s.predefineSymbolsColor(Formals.Color, formals.getSymbolValues())
	}
}

module.exports = {
	Format: 		 	Format,
	Comment: 		 	Comment,
	Padding: 		 	Padding,
	SSymbol: 		 	SSymbol,
	Quote: 			 	Quote,
	Pair: 			 	Pair,
	List: 			 	List,
	Nil: 			 	Nil,
	Complex: 			Complex,
	S: 					S,
	DefunName:  		DefunName,
	Formals: 			Formals,
	Body:		 		Body
}
