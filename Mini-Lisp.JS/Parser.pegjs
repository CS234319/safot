{
	const Pair = require("./Pair")
	const Atom = require("./Atom")
	const ListCreator = require("./ListCreator")
	const lc = new ListCreator()
	const quote = Atom.quote
}

S
	=   _
		s:	(
				"(" _ complex:(Pair / List) _ ")" { return complex } 	/
				sym:Symbol { return new Atom(sym) } 					/
				Quote
			)
		_ { return s }

List
	= listArray:(s:S { return s })* {
		return lc.create(...listArray)
	}

Pair
	= car:S "." cdr:S { 
		return new Pair(car, cdr)
	}

Symbol
	= [^()'.;\[\]\x00-\x20\x7F-\uFFFF]+ { 
		return text().toUpperCase()
	}

Quote
	= "'" s:S { 
		return lc.create(quote, s)
	}

Comment
	= ";" [^\n\r]*

_
	= ([\x00-\x20\x7F-\uFFFF] / Comment)*
