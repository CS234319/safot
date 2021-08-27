const primitives = require('./PrimitiveKeywords')
const TextHighlighter = require('./TextHighlighter')
const replDelegate = require('./BrowserREPL')

const th = new TextHighlighter()

class Element {
	constructor(value) {
		this.value = value
	}

	buildText() {
		return this.value
	}
}

class Format extends Element {
	constructor(value) {
		super(value)
	}

	buildText() {
		return th.highlight(this.value.buildText(), Format.DefaultColor)
	}

	static DefaultColor = '#d7deea'
}

class Comment extends Element {
	constructor(value) {
		super(value)
	}

	buildText() {
		return th.highlightWithStyle(this.value, Comment.Style, Comment.Color)
	}

	static Style = 'i'
	static Color = '#296d98'
}

class Padding extends Element {
	constructor(array) {
		super(array)
	}

	buildText() {
		return this.value.map(o => {
			return o instanceof Element ? o.buildText() : o
		}).join('')
	}
}

class SSymbol extends Element {
	constructor(value) {
		super(value)
	}

	buildText() {
		const color = 
			this.predefinedColor ? this.predefinedColor :
			this._isGlobal() ? SSymbol.Colors.global :
			this._isPrimitive(this.value) ? SSymbol.Colors.primitive :
			undefined

		return color ? th.highlight(this.value, color) : this.value
	}

	_isGlobal() {
		return replDelegate.getGlobals().includes(this.value.toUpperCase())
	}

	_isPrimitive() {
		return primitives.includes(this.value.toLowerCase())
	}

	static predefineColor(obj, color, symbolValues) {
		if (obj instanceof SSymbol) {
			if (symbolValues?.includes(obj.value) ?? true) {
				obj.predefinedColor = color
			}
			return
		}

		if (obj instanceof Quote) {
			return
		}

		if (obj instanceof Array) {
			obj.forEach(e => {
				SSymbol.predefineColor(e, color, symbolValues)
			})
			return
		}

		if (obj instanceof Element) {
			SSymbol.predefineColor(obj.value, color, symbolValues)	
		}
	}

	static cancelPredefinedColor(obj, symbolValues) {
		SSymbol.predefineColor(obj, undefined, symbolValues)
	}

	static Colors = {
		global: '#ff5261',
		primitive: '#39b6b5'
	}
}

class Quote extends Element {
	constructor(mark, value) {
		super(value)
		this.mark = mark
		this.didMatchParentheses = value?.didMatchParentheses
		SSymbol.predefineColor(value, Quote.Color)
	}

	buildText() {
		const text = this.value?.buildText() ?? ''
		return th.highlight(this.mark + text, Quote.Color)
	}

	static Color = '#ffab42'
}

class Pair extends Element {
	constructor(car, dot, cdr) {
		super([car].concat(cdr ? [cdr] : []))
		this.car = car
		this.dot = dot
		this.cdr = cdr
		this.didMatchParentheses = 
			this.car.didMatchParentheses ||
			this.cdr?.didMatchParentheses
	}

	buildText() {
		return this.car.buildText() + this.dot + (this.cdr?.buildText() ?? '')
	}

	getFirstLayerSymbols() {
		let list = []

		const carValue = this.car.value

		if (carValue instanceof SSymbol) {
			list.push(carValue)
		}	

		if (!this.cdr) {
			return list
		}

		const cdrValue = this.cdr.value

		if (cdrValue instanceof SSymbol) {
			return 'NIL'.startsWith(cdrValue.value.toUpperCase())
				? list
				: undefined
		}

		if (cdrValue instanceof Complex) {
			const cdrSymbols = cdrValue.value.getFirstLayerSymbols()
			return cdrSymbols ? list.concat(cdrSymbols) : undefined
		}
	}
}

class List extends Element {
	constructor(array) {
		super(array.flat())
		this.didMatchParentheses = this.value.some(s => s.didMatchParentheses)
	}

	buildText() {
		return this.value.map(s => s.buildText()).join('')
	}

	getFirstLayerSymbols() {
		return this.value
			.map(s => s.value)
			.filter(v => v instanceof SSymbol)
	}
}

class Lambda extends List {
	constructor(tag, complex, s) {
		const formals = new Formals(complex)
		const symbolValues = formals.getSymbolValues()
		const body = s ? new Body(s, symbolValues) : undefined 
		super([tag, formals, body].filter(e => e))
	}
}

class Defun extends List {
	constructor(tag, name, complex, s) {
		const formals = complex ? new Formals(complex) : undefined
		const symbolValues = formals?.getSymbolValues() ?? []
		const body = s ? new Body(s, symbolValues) : undefined 
		super([tag, name, formals, body].filter(e => e))
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

	static createFromValue(value) {
		return new S(new Element(''), value, new Element(''))
	}
}

class Tag extends S {
	constructor(lPadding, text, rPadding) {
		const symbol = new SSymbol(text)
		super(lPadding, symbol, rPadding)
	}
}

class LambdaName extends S {
	constructor(lPadding, symbol, rPadding) {
		super(lPadding, symbol, rPadding)
		symbol.predefinedColor = LambdaName.Color
	}

	static Color = '#ff724c'
}

class Formals extends S {
	constructor(complex) {
		const s = S.createFromValue(complex)
		super(s.lPadding, s.value, s.rPadding)

		SSymbol.cancelPredefinedColor(complex)
		
		complex.value.getFirstLayerSymbols()?.forEach(sym => {
			sym.predefinedColor = Formals.Color
		})
	}

	getSymbolValues() {
		return this.value.value.getFirstLayerSymbols()
			?.map(sym => sym.value) ?? []
	}

	static isLegal(complex) {
		return complex?.value instanceof List
	}

	static Color = '#cf91c9'
}

class Body extends S {
	constructor(s, formalSymbolValues) {
		super(s.lPadding, s.value, s.rPadding)
		SSymbol.predefineColor(this.value, Formals.Color, formalSymbolValues)
	}
}

module.exports = {
	Element: 	Element,
	Format: 	Format,
	Comment: 	Comment,
	Padding: 	Padding,
	SSymbol: 	SSymbol,
	Quote: 		Quote,
	Pair: 		Pair,
	List: 		List,
	Lambda: 	Lambda,
	Defun: 		Defun,
	Complex: 	Complex,
	S: 			S,
	Tag: 		Tag,
	LambdaName: LambdaName,
	Formals: 	Formals,
	Body:		Body
}
