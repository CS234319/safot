{
	const FormatterClasses = require('./FormatterElements')
	const Format 		= FormatterClasses.Format
	const Comment 		= FormatterClasses.Comment
	const Padding 		= FormatterClasses.Padding
	const SSymbol 		= FormatterClasses.SSymbol
	const Quote 		= FormatterClasses.Quote
	const Pair 			= FormatterClasses.Pair
	const List 			= FormatterClasses.List
	const Lambda 		= FormatterClasses.Lambda
	const Defun 		= FormatterClasses.Defun
	const Complex 		= FormatterClasses.Complex
	const S 			= FormatterClasses.S
	const Tag 			= FormatterClasses.Tag
	const LambdaName 	= FormatterClasses.LambdaName
	const Formals 		= FormatterClasses.Formals
	const Body 			= FormatterClasses.Body
}

Format
	= v:(PartialS / S / _) {
		return (new Format(v)).buildText()
	}

S
	=   s:(_
			(Complex / Symbol / Quote)
		_) { return new S(...s) }

PartialS
	= 	ps:(_
			(PartialComplex / PartialQuote)
		_) { return new S(...ps) }

Complex
	= c:('(' (Pair / Lambda / Defun / List) ')') {
		return new Complex(location(), ...c)
	}

PartialComplex
	= pc:('(' 
			(PartialLambda / PartialDefun / PartialList / PartialPair /
			 Pair / Lambda / Defun / List) 
		!')') { return new Complex(location(), ...pc) }

List
	= l:S* { return new List(l) }

PartialList
	= pl:(S* PartialS) { return new List(pl) }

Pair
	= p:(S '.' S) { return new Pair(...p) }

PartialPair
	= car:S dot:'.' !S cdr:PartialS? { return new Pair(car, dot, cdr) }

Lambda
	= t:LambdaTag f:Complex b:S !S {
		return new Lambda(t, f, b)
	}

PartialLambda
	= t:LambdaTag r:(PartialComplex / Complex !S PartialS?) {
		const f = r instanceof Array ? r[0] : r
		const b = r?.[2]
		return new Lambda(t, f, b)
	}

LambdaTag
	= lt:(_ 'n'i? 'lambda'i _) {
		const text = lt.slice(1, 3).join('')
		return new Tag(lt[0], text, lt[3])
	}

LambdaName
	= ln:(_ Symbol _) { return new LambdaName(...ln) }

Defun
	= t:DefunTag n:LambdaName f:Complex b:S !S {
		return new Defun(t, n, f, b)
	}

PartialDefun
	= t:DefunTag n:LambdaName r:(PartialComplex? !S / Complex !S PartialS?) {
		const f = r instanceof Array ? r[0] : r
		const b = r?.[2]
		return new Defun(t, n, f, b)
	}

DefunTag
	= dt:(_ 'n'i? 'defun'i _) {
		const text = dt.slice(1, 3).join('')
		return new Tag(dt[0], text, dt[3])
	}

Symbol
	= s:[^()'.;\[\]\x00-\x20\x7F-\uFFFF]+ { 
		return new SSymbol(s.join(''))
	}

Quote
	= m:"'" s:S { return new Quote(m, s) }

PartialQuote
	= m:"'" !S ps:PartialS? { return new Quote(m, ps) }

Comment
	= c:(';' [^\n\r]*) { return new Comment(c[0] + c[1].join('')) }
_
	= i:([\x00-\x20\x7F-\uFFFF] / Comment)* { 
		return new Padding(i)
	}
