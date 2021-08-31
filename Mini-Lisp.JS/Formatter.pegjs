{
	require('./ArrayExtension')

	const {
		Format, Comment, Padding, SSymbol, Quote, Pair, 
		List, Nil, Complex, S, DefunName, Formals, Body,
	} = require('./FormatterElements')

	const createComplex = (lEnc, value, rEnc) => {
		return new Complex(location(), lEnc, value, rEnc)
	}

	const createLambdaArray = (t, f, b, n) => {
		const body = (b ? new Body(b, f) : undefined)
		return [t, n, f, body].filter(Boolean)
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
	= c:(ComplexList / ComplexPair) { 
		return createComplex(...c)
	}

PartialComplex
	= pc:(PartialComplexList / PartialComplexPair) { 
		return createComplex(...pc)
	}

ComplexList
	= '(' List ')'

PartialComplexList
	= '(' (PartialList / List) !')'

ComplexPair
	= '[' Pair ']'

PartialComplexPair
	= '[' (PartialPair / Pair) !']'

List
	= l:(Lambda / Defun / S*) { return new List(l) }

PartialList
	= pl:(PartialLambda / PartialDefun / S* PartialS) { return new List(pl.flat()) }

Pair
	= p:(S '.' S) { return new Pair(...p) }

PartialPair
	= pp:(S '.' !S PartialS? / (PartialS / S)? !'.') { 
		return new Pair(...pp.filter(Boolean)) 
	}

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
	= dn:(_ (Nil / PartialNil / Symbol) _) { return new DefunName(...dn) }

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
			s1:S !S s2:PartialS? { return [t, n, s1, s2].filter(Boolean) }
		) { return pd }

Symbol
	= s:$(!PartialNil SymbolItem+) { return new SSymbol(s) }

Nil
	= n:'nil'i { return new Nil(n) }

PartialNil
	= pn:$('n'i 'i'i? !SymbolItem) { return new Nil(pn) }

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

SymbolItem
	= [^()'.;\[\]\x00-\x20\x7F-\uFFFF]

PaddingItem
	= $([\x00-\x20\x7F-\uFFFF]+) / Comment

Comment
	= c:$(';' [^\n\r]*) { return new Comment(c) }
