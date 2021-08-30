const TextHighlighter = require('./TextHighlighter')
const primitives = require('./PrimitiveKeywords')
const config = require('./Configuration').format
const delegate = require('./FormatterDelegate')
require('./ArrayExtension')

const highlighter = new TextHighlighter()

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
		return highlighter.apply(this.value.buildText(), Format.DefaultColor)
	}

	static DefaultColor = config.color.default
}

class Comment extends Element {
	buildText() {
		return highlighter.applyWithStyle(this.value, Comment.Style, Comment.Color)
	}

	static Style = config.style.comment
	static Color = config.color.comment
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

		return color ? highlighter.apply(this.value, color) : this.value
	}

	predefineSymbolsColor(color, symbolValues) {
		if (symbolValues?.includes(this.value) ?? true) {
			this.predefinedColor = color
		}
	}

	cancelMatchedParentheses() {}

	_isGlobal() {
		return delegate.getGlobals()?.includes(this.value.toUpperCase())
	}

	_isPrimitive() {
		return primitives.includes(this.value.toLowerCase())
	}

	static Colors = config.color.symbol
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
		return highlighter.apply(this.mark + text, Quote.Color)
	}

	cancelMatchedParentheses() {
		this.value.cancelMatchedParentheses()
	}

	static Color = config.color.quote
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

		if (this.rparen && !this.didMatchParentheses) {
			this._tryMatchParentheses(location)
		}
	}

	buildText() {
		return this.lparen + this.value.buildText() + (this.rparen ?? '')
	}

	getSymbolsOfList() {
		return this.value.getSymbolsOfList()
	}

	cancelMatchedParentheses() {
		if (!this.rparen) {
			return
		}

		this.lparen = highlighter.remove(this.lparen)
		this.rparen = highlighter.remove(this.rparen)
	}

	_tryMatchParentheses(location) {
		const lparenPos = location.start.offset
		const rparenPos = location.end.offset
		const result = delegate.matchParentheses(lparenPos, rparenPos)
		
		if (!result) {
			return
		}

		this.didMatchParentheses = true
		this._highlightParentheses(result.isInner)
	}

	_highlightParentheses(isInner) {
		const spanClass = isInner
			? Complex.ParenthesesClasses.highlightInner
			: Complex.ParenthesesClasses.highlighted

		this.lparen = highlighter.applyWithClass(this.lparen, spanClass)
		this.rparen = highlighter.applyWithClass(this.rparen, spanClass)
	}

	static ParenthesesClasses = {
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

	static Color = config.color.defunName
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

	static Color = config.color.formals
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
