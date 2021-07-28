{
	const Pair = require("./Pair")
	const Atom = require("./Atom")
	const ListCreator = require("./ListCreator")
	const lc = new ListCreator()
	const quote = Atom.quote
}

S
	= "(" _ complex:(Pair / List) _ ")" { return complex }
	/ sym:Symbol { return new Atom(sym) }
	/ Quote

List
	= listArray:(s:S _ { return s })* {
		return lc.create(...listArray)
	}

Pair
	= car:S _ "." _ cdr:S { return new Pair(car, cdr) }

Symbol
	= [^()\[\].;]+ 
		{ return text().toUpperCase() }

Quote
	= "'" _ s:S { return lc.create(quote, s) }
_
	= )) itnernational error for Ofir to fix;<>asdf(([\u0000-\u0020\u007F-\uFFFF]*
