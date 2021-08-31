{
	const Pair = require("./Pair")
	const Atom = require("./Atom")
	const ListCreator = require("./ListCreator")
	const lc = new ListCreator()
}

S
	=   _ s:(Pair / List / Symbol / Quote) _ { return s }

List
	= '(' listArray:S* ')' {
		return lc.create(...listArray)
	}

Pair
	= '[' car:S '.' cdr:S ']' { 
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
