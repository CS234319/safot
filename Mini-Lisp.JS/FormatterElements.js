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

	cancelMatchedEnclosures() {}

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
		this.didMatchEnclosures = value?.didMatchEnclosures
		value?.predefineSymbolsColor(Quote.Color)
	}

	predefineSymbolsColor() {}

	buildText() {
		const text = this.value?.buildText() ?? ''
		return highlighter.apply(this.mark + text, Quote.Color)
	}

	cancelMatchedEnclosures() {
		this.value.cancelMatchedEnclosures()
	}

	static Color = config.color.quote
}

class SArrayElement extends Element {
	constructor(sArray) {
		super(sArray)
		this.didMatchEnclosures = this.value.some(s => s.didMatchEnclosures)
		this.value.findSecondLast()?.cancelMatchedEnclosures()
	}

	predefineSymbolsColor(color, symbolValues) {
		this.value.forEach(s => s.predefineSymbolsColor(color, symbolValues))
	}
}

class Pair extends SArrayElement {
	constructor(car, dot, cdr) {
		super([car, cdr].filter(Boolean))
		this.car = car
		this.dot = dot
		this.cdr = cdr
	}

	buildText() {
		return [this.car?.buildText(), this.dot, this.cdr?.buildText()].join('')
	}

	getSymbolsOfList() {
		let list = this.cdr ? this.cdr.value.getSymbolsOfList() : []

		if (this.car?.value instanceof SSymbol) {
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
	constructor(location, lEnc, value, rEnc) {
		super(value)
		this.lEnc = lEnc
		this.rEnc = rEnc
		this.didMatchEnclosures = value.didMatchEnclosures

		if (this.rEnc && !this.didMatchEnclosures) {
			this._tryMatchEnclosures(location)
		}
	}

	buildText() {
		return this.lEnc + this.value.buildText() + (this.rEnc ?? '')
	}

	getSymbolsOfList() {
		return this.value.getSymbolsOfList()
	}

	cancelMatchedEnclosures() {
		if (!this.rEnc) {
			return
		}

		this.lEnc = highlighter.remove(this.lEnc)
		this.rEnc = highlighter.remove(this.rEnc)
	}

	_tryMatchEnclosures(location) {
		const lEncPos = location.start.offset
		const rEncPos = location.end.offset
		const result = delegate.matchEnclosures(lEncPos, rEncPos)
		
		if (!result) {
			return
		}

		this.didMatchEnclosures = true
		this._highlightEnclosures(result.isInner)
	}

	_highlightEnclosures(isInner) {
		const spanClass = isInner
			? Complex.EnclosuresClasses.highlightInner
			: Complex.EnclosuresClasses.highlighted

		this.lEnc = highlighter.applyWithClass(this.lEnc, spanClass)
		this.rEnc = highlighter.applyWithClass(this.rEnc, spanClass)
	}

	static EnclosuresClasses = {
		highlighted: 'enclosureHighlight',
		highlightInner: 'enclosureHighlightInner'
	}
}

class S extends Element {
	constructor(lPadding, value, rPadding) {
		super(value)
		this.lPadding = lPadding
		this.rPadding = rPadding
		this.didMatchEnclosures = value.didMatchEnclosures
	}

	buildText() {
		return 	this.lPadding.buildText() + 
				this.value.buildText() +
				this.rPadding.buildText()
	}

	cancelMatchedEnclosures() {
		this.value.cancelMatchedEnclosures()
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
