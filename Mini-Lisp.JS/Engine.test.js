const p = require('./Parser')
const Engine = require('./Engine')
const TestUtils = require('./TestUtils')
const Atom = require('./Atom')

const utils = new TestUtils()

var e = new Engine()

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
const primitiveArgsException = (callStr, kindStr) => {
	parseEvaluateException(callStr, callStr, kindStr)
}
const primitiveArgsMissingException = (callStr) => {
	primitiveArgsException(callStr, "missing")
}
const primitiveArgsRedundantException = (callStr) => {
	primitiveArgsException(callStr, "redundant")
}
const lambdaArgsException = (callStr, kindStr, extractLambda) => {
	const call = p.parse(callStr)
	const lambda = extractLambda(call.car())
	const args = call.cdr()
	parseEvaluateException(callStr, lambda.cons(args).toString(), kindStr) 
}
const namedLambdaArgsException = (callStr, kindStr) => {
	lambdaArgsException(callStr, kindStr, name => e.evaluate(name))
}
const anonymousLambdaArgsException = (callStr, kindStr) => {
	lambdaArgsException(callStr, kindStr, lambda => lambda)
}

const clear = () => e = new Engine()

test('evaluate atoms', () => {
	parseEvaluateEquals("t", "t")
	parseEvaluateEquals("nil", "nil")
})

test('evaluate car', () => {	
	parseEvaluateEquals("(car '(a . b))", "a")
	parseEvaluateEquals("(car '(b a x y z))", "b")
	parseEvaluateException("(car 'a)", "a", "car")
	primitiveArgsMissingException("(car)")
	primitiveArgsRedundantException("(car 'a 'b)")
	primitiveArgsRedundantException("(car a b)")
})

test('evaluate cdr', () => {
	parseEvaluateEquals("(cdr '(a . b))", "b")
	parseEvaluateEquals("(cdr '(b a x y z))", '(a x y z)')
	parseEvaluateException("(cdr 'a)", "a", "cdr")
	primitiveArgsMissingException("(cdr)")
	primitiveArgsRedundantException("(cdr 'a 'b)")
})

test('evaluate quote', () => {
	parseEvaluateEquals("(quote a)", "a")
	primitiveArgsMissingException("(quote)")
	primitiveArgsRedundantException("(quote a b)")
})

test('evaluate atom', () => {
	parseEvaluateEquals("(atom 'a)", "t")
	parseEvaluateEquals("(atom '(a . b))", "nil")
	parseEvaluateEquals("(atom '(a b c))", "nil")
	primitiveArgsMissingException("(atom)")
	primitiveArgsRedundantException("(atom 'a 'b)")
})
	
test('evaluate null', () => {
	parseEvaluateEquals("(null nil)", "t")
	parseEvaluateEquals("(null 'a)", "nil")
	parseEvaluateEquals("(null '(a b))", "nil")
	parseEvaluateEquals("(null '(a b))", "nil")
	namedLambdaArgsException("(null)", "missing")
	namedLambdaArgsException("(null 'a 'b)", "redundant")
})

test('evaluate cond', () => {
	parseEvaluateEquals("(cond)", "nil")
	parseEvaluateEquals("(cond (t 'a))", "a")
	parseEvaluateEquals("(cond ((eq 'a 'b) '(a b c)) ((eq 'a 'a) '(a a a)))", "(a a a)")
	parseEvaluateEquals("(cond ((eq 'a 'b) '(a b c)) ((set 'b 'c) '(a a a)))", "(a a a)")
	// parseEvaluateEquals("(eval b)", "c")
	parseEvaluateEquals("(cond ((eq 'a 'a) '(a b c)) ((set 'a 'c) '(a a a)))", "(a b c)")
	// parseEvaluateException("(eval a)", "a", "undefined")
	parseEvaluateException("(cond ((eq 'a 'b) '(a b c)) a)", "a", "cond")
	parseEvaluateException("(cond ((eq 'a 'b) '(a b c)) 'a)", "quote", "undefined")
	clear()
})

test('evaluate eq', () => {
	parseEvaluateEquals("(eq 'a 'a)", "t")
	parseEvaluateEquals("(eq 'a 'b)", "nil")
	parseEvaluateEquals("(eq 'a '(a . b))", "nil")
	parseEvaluateEquals("(eq '(a . b) '(a . b))", "nil")
	primitiveArgsMissingException("(eq 'a)")
	primitiveArgsRedundantException("(eq 'a 'b 'c)")
})

test('evaluate set', () => {
	parseEvaluateException("(set a '(a . a))", "a", "undefined")
	parseEvaluateEquals("(set 'a '(a . a))", "(a . a)")
	parseEvaluateEquals("(set a '(a . b))", "(a . b)")
	primitiveArgsMissingException("(set 'a)")
	primitiveArgsMissingException("(set (error 'c))")
	
	primitiveArgsMissingException("(set (set 'c 'd))")
	parseEvaluateException("(set c 'e)", "c", "undefined")
	
	primitiveArgsRedundantException("(set 'a 'b 'c)")
	primitiveArgsRedundantException("(set 'a 'b (error 'c))")
	
	primitiveArgsRedundantException("(set 'a 'b (set 'c 'd))")
	parseEvaluateException("(set c 'e)", "c", "undefined")
	
	clear()
})	

test('evaluate eval', () => {
	parseEvaluate("(set 'a '(a . a))")
	parseEvaluate("(set 'b 'c)")	
	parseEvaluate("(set 'c 'd)")	
	parseEvaluateEquals("(eval 't)", "t")
	parseEvaluateEquals("(eval 'nil)", "nil")
	parseEvaluateEquals("(eval 'a)", '(a . a)')
	parseEvaluateEquals("(eval 'b)", 'c')
	parseEvaluateEquals("(eval b)", 'd')
	parseEvaluateEquals("(eval '(cond ((eq a 'a) 'c) ((eq a 'b) 'd)))", "nil")
	parseEvaluateException("(eval 'd)", "d", "undefined")
	primitiveArgsMissingException("(eval)")
	primitiveArgsRedundantException("(eval 'a 'b)")
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
	const lambdaStr = "(lambda (x) x)"
	parseEvaluateEquals(lambdaStr, lambdaStr)
	
	primitiveArgsMissingException("(lambda ())")
	primitiveArgsRedundantException("(lambda () () ())")

	parseEvaluate("(set 'foo (lambda () 'a))")
	parseEvaluateEquals("(foo)", "a")
	namedLambdaArgsException("(foo 'a)", "redundant")
	namedLambdaArgsException("(foo (error 'a))", "redundant")
	namedLambdaArgsException("(foo (set 'a 'b))", "redundant")
	parseEvaluateException("(car a)", "a", "undefined")

	parseEvaluate("(set 'bar (lambda (xs) (car (cdr xs))))")
	parseEvaluateEquals("(bar (cdr '(c a b)))", "b")
	namedLambdaArgsException("(bar)", "missing")
	namedLambdaArgsException("(bar '(c a b) 'a)", "redundant")

	parseEvaluate("(set 'vaz (lambda (x xs) (cons x xs)))")
	parseEvaluateEquals("(vaz 'a '(b c))", "(a b c)")
	namedLambdaArgsException("(vaz 'a)", "missing")
	namedLambdaArgsException("(vaz a)", "missing")
	namedLambdaArgsException("(vaz (error 'a))", "missing")
	namedLambdaArgsException("(vaz (set 'a))", "missing")
	parseEvaluateException("(car a)", "a", "undefined")

	parseEvaluateEquals("((lambda (x xs) (cons x xs)) 'a '(b c))", '(a b c)')
	anonymousLambdaArgsException("((lambda (x xs) (cons x xs)) 'a)", "missing")
	anonymousLambdaArgsException("((lambda (x xs) (cons x xs)) 'a '(b c) 'd)", "redundant")

	parseEvaluate("(set 'foo '(lambda () a))")
	parseEvaluateException("(foo)", "a", "undefined")

	parseEvaluate("(set 'foo '(lambda ()))")
	parseEvaluateException("(foo)", "(lambda ())", "invalid")
	parseEvaluateException("(foo 'a)", "(lambda ())", "invalid")

	parseEvaluate("(set 'foo '(lambda () 'a 'b))")
	parseEvaluateException("(foo)", "(lambda () 'a 'b)", "invalid")
	parseEvaluateException("(foo 'a)", "(lambda () 'a 'b)", "invalid")

	parseEvaluate("(set 'foo '(not_lambda () 'a))")
	parseEvaluateException("(foo)", "(not_lambda () 'a)", "invalid")
	parseEvaluateException("(foo 'a)", "(not_lambda () 'a)", "invalid")

	parseEvaluate("(set 'foo (lambda a 'a))")
	parseEvaluateException("(foo)", "(lambda a 'a)", "invalid")

	clear()
})

test('evaluate nested lambdas', () => {
	parseEvaluate("(set 'foo (lambda (x xs) (cons x xs)))")
	parseEvaluate("(set 'bar (lambda (x xs) (foo (car xs) (cons x xs))))")
	parseEvaluateEquals("(bar 'a '(b c d))", "(b a b c d)")
	namedLambdaArgsException("(bar 'a)", "missing")
	namedLambdaArgsException("(bar 'a '(b c d) 'e)", "redundant")
	clear()
})

test('evaluate recursive lambdas', () => {
	parseEvaluate("(set 'append (lambda (x xs) " +
					"(cond ((null xs) (cons x nil)) " +
						  "(t (cons (car xs) (append x (cdr xs)))))))")
	parseEvaluateEquals("(append (car '(c d)) '(a b))", '(a b c)')
	namedLambdaArgsException("(append 'a)", "missing")
	namedLambdaArgsException("(append 'a 'b 'c)", "redundant")
	clear()
})

test('evaluate nlambda', () => {
	const nlambdaStr = "(nlambda (x) x)"
	parseEvaluateEquals(nlambdaStr, nlambdaStr)
	
	primitiveArgsMissingException("(nlambda ())")
	primitiveArgsRedundantException("(nlambda () () ())")

	parseEvaluate("(set 'foo (nlambda () 'a))")
	parseEvaluateEquals("(foo)", "a")
	namedLambdaArgsException("(foo a)", "redundant")

	parseEvaluate("(set 'bar (nlambda (xs) (car (cdr xs))))")
	parseEvaluateEquals("(bar (cdr '(c a b)))", "'(c a b)")
	namedLambdaArgsException("(bar)", "missing")
	namedLambdaArgsException("(bar (c a b) a)", "redundant")

	parseEvaluateEquals("((nlambda (x xs) (cons x xs)) a (b c))", '(a b c)')
	anonymousLambdaArgsException("((nlambda (x xs) (cons x xs)) a)", "missing")
	anonymousLambdaArgsException("((nlambda (x xs) (cons x xs)) a (b c) d)", "redundant")

	parseEvaluate("(set 'foo '(nlambda ()))")
	parseEvaluateException("(foo)", "(nlambda ())", "invalid")
	parseEvaluateException("(foo 'a)", "(nlambda ())", "invalid")

	parseEvaluate("(set 'foo '(nlambda () 'a 'b))")
	parseEvaluateException("(foo)", "(nlambda () 'a 'b)", "invalid")
	parseEvaluateException("(foo a)", "(nlambda () 'a 'b)", "invalid")

	parseEvaluate("(set 'foo '(not_nlambda () 'a))")
	parseEvaluateException("(foo)", "(not_nlambda () 'a)", "invalid")
	parseEvaluateException("(foo a)", "(not_nlambda () 'a)", "invalid")

	parseEvaluate("(set 'foo (nlambda a 'a))")
	parseEvaluateException("(foo)", "(nlambda a 'a)", "invalid")
	
	clear()
})

test('evaluate defun', () => {
	primitiveArgsMissingException("(defun foo (x xs))")
	primitiveArgsRedundantException("(defun foo (x xs) (cons x xs) 'a)")

	parseEvaluate("(defun foo () 'a)")
	parseEvaluateEquals("(foo)", "a")

	parseEvaluate("(defun bar (xs) (car (cdr xs)))")
	parseEvaluateEquals("(bar (cdr '(c a b)))", "b")

	parseEvaluate("(defun append (x xs) " + 
					"(cond ((null xs) (cons x nil)) " + 
						  "(t (cons (car xs) (append x (cdr xs))))))")
	parseEvaluateEquals("(append (car '(c d)) '(a b))", '(a b c)')

	parseEvaluate("(defun foo a 'a)")
	parseEvaluateException("(foo)", "(lambda a 'a)", "invalid")
	
	clear()
	
	parseEvaluate("(defun bind (xs ys) " +
						"(cond 	((null xs) (cond ((null ys) nil) " +
													"(t (error ys 'redundant)))) " +
								"((null ys) (cond ((null xs) nil) " +
													"(t (error ys 'missing)))) " +
								"(t (cons " +
									"(set (car xs) (car ys)) " +
									"(bind (cdr xs) (cdr ys))))))")
	
	parseEvaluateEquals("(bind '(a b) '(c d))", "(c d)")
	parseEvaluateEquals("(eval 'a)", "c")
	parseEvaluateEquals("(eval 'b)", "d")
	clear()

	parseEvaluate("(set 'x 'a)")
	parseEvaluate("(defun foo () (cons (set 'x 'b) (eval 'x)))")
	parseEvaluateEquals("(foo)", "(b . b)")
	parseEvaluateEquals("(eval 'x)", "b")
	clear()

	parseEvaluate("(set 'x 'a)")
	parseEvaluate("(defun foo (x) (cons (set 'x 'c) (eval 'x)))")
	parseEvaluateEquals("(foo 'y)", "(c . y)")
	parseEvaluateEquals("(eval 'x)", "c")
	clear()
})

test('evaluate ndefun', () => {
	primitiveArgsMissingException("(ndefun foo (x xs))")
	primitiveArgsRedundantException("(ndefun foo (x xs) (cons x xs) 'a)")

	parseEvaluate("(ndefun foo () 'a)")
	parseEvaluateEquals("(foo)", "a")
	parseEvaluate("(ndefun bar (xs) (car (cdr xs)))")
	parseEvaluateEquals("(bar (a b))", "b")

	parseEvaluate("(ndefun foo a 'a)")
	parseEvaluateException("(foo)", "(nlambda a 'a)", "invalid")

	clear()
})
