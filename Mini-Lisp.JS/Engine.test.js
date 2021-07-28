const p = require('./Parser')
const Engine = require('./Engine')

const t = p.parse('t')
const nil = p.parse('nil')
const a = p.parse('a')
const b = p.parse('b')

var e = new Engine()
const evaluateParse = str => e.evaluate(p.parse(str))
const clear = () => e = new Engine()

test('evaluate atoms', () => {
	expect(e.evaluate(t)).toStrictEqual(t)
	expect(e.evaluate(nil)).toStrictEqual(nil)
})

test('evaluate car', () => {	
	expect(evaluateParse("(car '(a . b))")).toStrictEqual(a)
	expect(evaluateParse("(car '(b a x y z))")).toStrictEqual(b)
})

test('evaluate cdr', () => {
	expect(evaluateParse("(cdr '(a . b))")).toStrictEqual(b)
	expect(evaluateParse("(cdr '(b a x y z))")).toStrictEqual(p.parse('(a x y z)'))
})

test('evaluate quote', () => {
	expect(evaluateParse("(quote a)")).toStrictEqual(a)
})

test('evaluate atom', () => {
	expect(evaluateParse("(atom 'a)")).toStrictEqual(t)
	expect(evaluateParse("(atom '(a . b))")).toStrictEqual(nil)
})
	
test('evaluate null', () => {
	expect(evaluateParse("(null nil)")).toStrictEqual(t)
	expect(evaluateParse("(null 'a)")).toStrictEqual(nil)
	expect(evaluateParse("(null '(a b))")).toStrictEqual(nil)
})

test('evaluate cond', () => {
	expect(evaluateParse("(cond)")).toStrictEqual(nil)
	expect(evaluateParse("(cond (t 'a))")).toStrictEqual(a)
	expect(evaluateParse("(cond ((eq 'a 'b) '(a b c)) ((eq 'a 'a) '(a a a)))"))
		.toStrictEqual(p.parse("(a a a)"))
	expect(evaluateParse("(cond ((eq 'a 'b) '(a b c)) ((set 'b 'c) '(a a a)))"))
		.toStrictEqual(p.parse("(a a a)"))
})

test('evaluate eq', () => {
	expect(evaluateParse("(eq 'a 'a)")).toStrictEqual(t)
	expect(evaluateParse("(eq 'a 'b)")).toStrictEqual(nil)
	expect(evaluateParse("(eq 'a '(a . b))")).toStrictEqual(nil)
})

test('evaluate set', () => {
	expect(evaluateParse("(set 'a '(a . a))")).toStrictEqual(p.parse('(a . a)'))
	clear()
})	

test('evaluate eval', () => {
	evaluateParse("(set 'a '(a . a))")
	evaluateParse("(set 'b 'c)")	
	expect(evaluateParse("(eval t)")).toStrictEqual(t)
	expect(evaluateParse("(eval nil)")).toStrictEqual(nil)
	expect(evaluateParse("(eval a)")).toStrictEqual(p.parse('(a . a)'))
	expect(evaluateParse("(eval b)")).toStrictEqual(p.parse('c'))
	expect(evaluateParse("(eval (cond ((eq a 'a) 'c) ((eq a 'b) 'd)))"))
		.toStrictEqual(nil)
	clear()
})
	
test('evaluate lambda', () => {
	const lambda = p.parse("(lambda () 'a)")
	expect(e.evaluate(lambda)).toStrictEqual(lambda)
	evaluateParse("(set 'foo (lambda () 'a))")
	expect(evaluateParse("(foo)")).toStrictEqual(a)
	evaluateParse("(set 'bar (lambda (xs) (car (cdr xs))))")
	expect(evaluateParse("(bar (cdr '(c a b)))")).toStrictEqual(b)
	expect(evaluateParse("((lambda (x xs) (cons x xs)) 'a '(b c))"))
		.toStrictEqual(p.parse('(a b c)'))
	evaluateParse("(set 'append (lambda (x xs) " + 
					"(cond ((null xs) (cons x nil)) " + 
						  "(t (cons (car xs) (append x (cdr xs)))))))")
	expect(evaluateParse("(append (car '(c d)) '(a b))"))
		.toStrictEqual(p.parse('(a b c)'))
	clear()
})

test('evaluate nlambda', () => {
	const nlambda = p.parse("(nlambda (x) x)")
	expect(nlambda).toStrictEqual(nlambda)
		evaluateParse("(set 'foo (nlambda () 'a))")
	expect(evaluateParse("(foo)")).toStrictEqual(a)
	evaluateParse("(set 'bar (nlambda (xs) (car (cdr xs))))")
	expect(evaluateParse("(bar (a b))")).toStrictEqual(b)
	expect(evaluateParse("((nlambda (x xs) (cons x xs)) a (b c))"))
		.toStrictEqual(p.parse('(a b c)'))
	clear()
})

test('evaluate defun', () => {
	evaluateParse("(defun foo () 'a)").toString()
	expect(evaluateParse("(foo)")).toStrictEqual(a)
	evaluateParse("(defun bar (xs) (car (cdr xs)))")
	expect(evaluateParse("(bar (cdr '(c a b)))")).toStrictEqual(b)
	evaluateParse("(defun append (x xs) " + 
					"(cond ((null xs) (cons x nil)) " + 
						  "(t (cons (car xs) (append x (cdr xs))))))")
	expect(evaluateParse("(append (car '(c d)) '(a b))"))
		.toStrictEqual(p.parse('(a b c)'))
})

test('evaluate ndefun', () => {
	evaluateParse("(ndefun foo () 'a)").toString()
	expect(evaluateParse("(foo)")).toStrictEqual(a)
	evaluateParse("(ndefun bar (xs) (car (cdr xs)))")
	expect(evaluateParse("(bar (a b))")).toStrictEqual(b)
})
