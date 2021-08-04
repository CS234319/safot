const p = require('./Parser')
const Engine = require('./Engine')
const TestUtils = require('./TestUtils')
const Atom = require('./Atom')

const utils = new TestUtils()

const t = p.parse('t')
const nil = p.parse('nil')

var e = new Engine()
const evaluateEquals = (s1, s2) => utils.expectEquals(e.evaluate(s1), s2)
const parseEvaluate = str => e.evaluate(p.parse(str))
const parseEvaluateEquals = (str1, str2) => {
	utils.expectEquals(parseEvaluate(str1), p.parse(str2))
}
const parseEvaluateException = (str1, str2, kindStr) => {
	utils.expectException(() => parseEvaluate(str1), p.parse(str2), p.parse(kindStr))
}
const parseEvaluateError = (errorStr, kindStr) => {
	parseEvaluateException(errorStr, errorStr, kindStr)
}

const clear = () => e = new Engine()

test('evaluate atoms', () => {
	evaluateEquals(t, t)
	evaluateEquals(nil, nil)
})

test('evaluate car', () => {	
	parseEvaluateEquals("(car '(a . b))", "a")
	parseEvaluateEquals("(car '(a . b))", "a")
	parseEvaluateEquals("(car '(b a x y z))", "b")
	parseEvaluateException("(car 'a)", "a", "car")
})

test('evaluate cdr', () => {
	parseEvaluateEquals("(cdr '(a . b))", "b")
	parseEvaluateEquals("(cdr '(b a x y z))", '(a x y z)')
	parseEvaluateException("(cdr 'a)", "a", "cdr")
})

test('evaluate quote', () => {
	parseEvaluateEquals("(quote a)", "a")
})

test('evaluate atom', () => {
	parseEvaluateEquals("(atom 'a)", "t")
	parseEvaluateEquals("(atom '(a . b))", "nil")
	parseEvaluateEquals("(atom '(a b c))", "nil")
})
	
test('evaluate null', () => {
	parseEvaluateEquals("(null nil)", "t")
	parseEvaluateEquals("(null 'a)", "nil")
	parseEvaluateEquals("(null '(a b))", "nil")
})

test('evaluate cond', () => {
	parseEvaluateEquals("(cond)", "nil")
	parseEvaluateEquals("(cond (t 'a))", "a")
	parseEvaluateEquals("(cond ((eq 'a 'b) '(a b c)) ((eq 'a 'a) '(a a a)))", "(a a a)")
	parseEvaluateEquals("(cond ((eq 'a 'b) '(a b c)) ((set 'b 'c) '(a a a)))", "(a a a)")
	parseEvaluateEquals("(eval b)", "c")
	parseEvaluateEquals("(cond ((eq 'a 'a) '(a b c)) ((set 'a 'c) '(a a a)))", "(a b c)")
	parseEvaluateException("(eval a)", "a", "undefined")
	parseEvaluateException("(cond ((eq 'a 'b) '(a b c)) a)", "a", "cond")
	parseEvaluateException("(cond ((eq 'a 'b) '(a b c)) 'a)", "quote", "undefined")
	clear()
})

test('evaluate eq', () => {
	parseEvaluateEquals("(eq 'a 'a)", "t")
	parseEvaluateEquals("(eq 'a 'b)", "nil")
	parseEvaluateEquals("(eq 'a '(a . b))", "nil")
	parseEvaluateEquals("(eq '(a . b) '(a . b))", "nil")
})

test('evaluate set', () => {
	parseEvaluateException("(set a '(a . a))", "a", "undefined")
	parseEvaluateEquals("(set 'a '(a . a))", "(a . a)")
	clear()
})	

test('evaluate eval', () => {
	parseEvaluate("(set 'a '(a . a))")
	parseEvaluate("(set 'b 'c)")	
	parseEvaluateEquals("(eval t)", "t")
	parseEvaluateEquals("(eval nil)", "nil")
	parseEvaluateEquals("(eval a)", '(a . a)')
	parseEvaluateEquals("(eval b)", 'c')
	parseEvaluateEquals("(eval (cond ((eq a 'a) 'c) ((eq a 'b) 'd)))", "nil")
	parseEvaluateException("(eval c)", "c", "undefined")
	clear()
})

test('evaluate error', () => {
	parseEvaluateError("(error 'a)", "(a)")
	parseEvaluateError("(error 'a 'b)", "(a b)")
	parseEvaluateError("(error (set 'a 'd) 'b)", "(d b)")
	parseEvaluateException("(error a)", "a", "undefined")
	parseEvaluateException("(cond ((null (set 'b_0 'x)) 'x) " +
								 "((null (set 'b_1 'x)) 'x) " +
								 "((null (error 'b_2 'x)) 'x))",
								 "(error 'b_2 'x)",
								 "(b_2 x)")
	
	parseEvaluateException("(error b_0)", "b_0", "undefined")
	parseEvaluateException("(error b_1)", "b_1", "undefined")
	parseEvaluateException("(error b_2)", "b_2", "undefined")
})

test('evaluate error and restore', () => {
	/* 
	 * Bind A with (A.B), call error with A and repeat one more time
	 * to make sure the first call to error didn't undo the binding.
	 */

	parseEvaluate("(set 'a '(a.b))")
	for (var i = 0; i < 2; i++) {
		parseEvaluateError("(error a)", "((a . b))")
	}

	clear()
})
	
test('evaluate lambda', () => {
	const lambda = p.parse("(lambda () 'a)")
	evaluateEquals(lambda, lambda)
	
	parseEvaluate("(set 'foo (lambda () 'a))")
	parseEvaluateEquals("(foo)", "a")
	
	parseEvaluate("(set 'bar (lambda (xs) (car (cdr xs))))")
	parseEvaluateEquals("(bar (cdr '(c a b)))", "b")
	
	parseEvaluateEquals("((lambda (x xs) (cons x xs)) 'a '(b c))", '(a b c)')
	
	clear()
})

test('evaluate nested lambdas', () => {
	parseEvaluate("(set 'foo (lambda (x xs) (cons x xs)))")
	parseEvaluate("(set 'bar (lambda (x xs) (foo (car xs) (cons x xs))))")
	parseEvaluateEquals("(bar 'a '(b c d))", "(b a b c d)")
	clear()
})

test('evaluate recursive lambdas', () => {
	parseEvaluate("(set 'append (lambda (x xs) " +
					"(cond ((null xs) (cons x nil)) " +
						  "(t (cons (car xs) (append x (cdr xs)))))))")
	parseEvaluateEquals("(append (car '(c d)) '(a b))", '(a b c)')
	clear()
})

test('evaluate nlambda', () => {
	const nlambda = p.parse("(nlambda (x) x)")
	evaluateEquals(nlambda, nlambda)
	
	parseEvaluate("(set 'foo (nlambda () 'a))")
	parseEvaluateEquals("(foo)", "a")

	parseEvaluate("(set 'bar (nlambda (xs) (car (cdr xs))))")
	parseEvaluateEquals("(bar (a b))", "b")
	
	parseEvaluateEquals("((nlambda (x xs) (cons x xs)) a (b c))", '(a b c)')
	
	clear()
})

test('evaluate defun', () => {
	parseEvaluate("(defun foo () 'a)")
	parseEvaluateEquals("(foo)", "a")
	parseEvaluate("(defun bar (xs) (car (cdr xs)))")
	parseEvaluateEquals("(bar (cdr '(c a b)))", "b")
	parseEvaluate("(defun append (x xs) " + 
					"(cond ((null xs) (cons x nil)) " + 
						  "(t (cons (car xs) (append x (cdr xs))))))")
	parseEvaluateEquals("(append (car '(c d)) '(a b))", '(a b c)')

	clear()
})

test('evaluate ndefun', () => {
	parseEvaluate("(ndefun foo () 'a)")
	parseEvaluateEquals("(foo)", "a")
	parseEvaluate("(ndefun bar (xs) (car (cdr xs)))")
	parseEvaluateEquals("(bar (a b))", "b")

	clear()
})
