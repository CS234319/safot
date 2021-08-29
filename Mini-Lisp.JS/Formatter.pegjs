{
	require('./ArrayExtension')

	const {
		Format, Comment, Padding, SSymbol, Quote, Pair, List, 
		Nil, Complex, S, DefunName, Formals, Body
	} = require('./FormatterElements')

	const createComplex = (lparen, value, rparen) => {
		return new Complex(location(), lparen, value, rparen)
	}

	const createLambdaArray = (t, f, b, n) => {
		const body = (b ? new Body(b, f) : undefined)
		return [t, n, f, body].filterNullish()
	}
}

Format
	= v:(PartialS / S / _) {
		return (new Format(v)).buildText()
	}

S
	=   s:(_
			(Complex / Quote / Nil / Symbol)
		_) { return new S(...s) }

PartialS
	= 	ps:(_
			(PartialNil / PartialComplex / PartialQuote)
		_) { return new S(...ps) }

Complex
	= c:('(' (Pair / List) ')') { 
		return createComplex(...c) 	
	}

PartialComplex
	= pc:('(' (PartialPair / PartialList / Pair / List) !')') { 
		return createComplex(...pc) 
	}

List
	= l:(Lambda / Defun / S*) { return new List(l) }

PartialList
	= pl:(PartialLambda / PartialDefun / S* PartialS) { return new List(pl.flat()) }

Nil
	= n:'nil'i { return new Nil(n) }

PartialNil
	= pn:$('n'i 'i'i? !'l'i) { return new Nil(pn) }

Pair
	= p:(S '.' S) { return new Pair(...p) }

PartialPair
	= car:S dot:'.' !S cdr:PartialS? { return new Pair(car, dot, cdr) }

Formals
	= f:(_ Complex _) { return new Formals(...f) }

PartialFormals
	= f:(_ PartialComplex _) { return new Formals(...f) }

LambdaTagSymbol
	= lts:$('n'i? 'lambda'i) { return new SSymbol(lts) }

LambdaTag
	= lt:(_ LambdaTagSymbol _) { return new S(...lt) }

Lambda
	= t:LambdaTag f:Formals b:S !S {
		return createLambdaArray(t, f, b)
	}

PartialLambda
	= t:LambdaTag
		pl:(
			pf:PartialFormals !'.' { return [t, pf] } / 
			f:Formals !S b:PartialS? { return createLambdaArray(t, f, b) }
		) { return pl }

DefunTagSymbol
	= dts:$('n'i? 'defun'i) { return new SSymbol(dts) }

DefunTag
	= dt:(_ DefunTagSymbol StrongPadding) { return new S(...dt) }

DefunName
	= dn:(_ Symbol _) { return new DefunName(...dn) }

Defun
	= t:DefunTag n:DefunName 
		d:(
			f:Formals b:S { return createLambdaArray(t, f, b, n) } / 
			s1:S s2:S { return [t, n, s1, s2] }
		) !S { return d }

PartialDefun
	= t:DefunTag n:DefunName
		pd:(
			pf:PartialFormals? b:!(Formals / S) { 
				return createLambdaArray(t, pf, b, n) 
			} / 
			f:Formals !S b:PartialS? { return createLambdaArray(t, f, b, n) } /
			s1:S !S s2:PartialS? { return [t, n, s1, s2].filterNullish() }
		) { return pd }

Symbol
	= s:$(!PartialNil [^()'.;\[\]\x00-\x20\x7F-\uFFFF]+) { return new SSymbol(s) }

Quote
	= m:"'" s:S { return new Quote(m, s) }

PartialQuote
	= m:"'" !S ps:PartialS? { return new Quote(m, ps) }

_ 	// Weak padding
	= p:PaddingItem* { 
		return new Padding(p)
	}

StrongPadding
	= sp:PaddingItem+ { 
		return new Padding(sp)
	}

PaddingItem
	= $([\x00-\x20\x7F-\uFFFF]+) / Comment

Comment
	= c:$(';' [^\n\r]*) { return new Comment(c) }
