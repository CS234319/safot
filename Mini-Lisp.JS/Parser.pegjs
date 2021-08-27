{
	const Pair = require("./Pair")
	const Atom = require("./Atom")
	const ListCreator = require("./ListCreator")
	const lc = new ListCreator()
}

S
	=   _ s:(Complex / Symbol / Quote) _ { return s }

Complex
	= '(' complex:(Pair / List) ')' { 
		return complex
	}

List
	= listArray:S* {
		return lc.create(...listArray)
	}

Pair
	= car:S '.' cdr:S { 
		return new Pair(car, cdr)
	}

Symbol
	= [^()'.;\[\]\x00-\x20\x7F-\uFFFF]+ { 
		return new Atom(text().toUpperCase())
	}

Quote
	= "'" s:S { 
		return lc.create(Atom.quote, s)
	}

Comment
	= ';' [^\n\r]*

_
	= ([\x00-\x20\x7F-\uFFFF] / Comment)*
