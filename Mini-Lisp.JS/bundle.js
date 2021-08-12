(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
const S = require('./S')

module.exports = class Atom extends S {
	constructor(value) {
		super()
		this._value = value
	}

	atom() {
		return true
	}

	car() {
		return this.error(Atom.car)
	}

	cdr() {
		return this.error(Atom.cdr)
	}	

	eq(s) {
		return s.atom() && this._value === s._value}

	equals(s) {
		return this.eq(s)
	}

	isList() {
		return this.null()
	}

	getListAsArray() {
		return this.null() ? [] : null
	}

	toString() {
		return this._value.toString()
	}

	static nil 			= new Atom('NIL')
	static t 			= new Atom('T')
	static quote 		= new Atom('QUOTE')
	static lambda 		= new Atom('LAMBDA')
	static nlambda 		= new Atom('NLAMBDA')
	static SET 			= new Atom('SET')
	static defun 		= new Atom('DEFUN')
	static ndefun 		= new Atom('NDEFUN')
	static atom 		= new Atom('ATOM')
	static car 			= new Atom('CAR')
	static cdr 			= new Atom('CDR')
	static cond 		= new Atom('COND')
	static cons 		= new Atom('CONS')
	static error 		= new Atom('ERROR')
	static eval 		= new Atom('EVAL')
	static eq 			= new Atom('EQ')
	static undefined 	= new Atom('UNDEFINED')
	static invalid 		= new Atom('INVALID')
	static bug 			= new Atom('BUG')
	static missing 		= new Atom('MISSING')
	static redundant 	= new Atom('REDUNDANT')
}

},{"./S":10}],2:[function(require,module,exports){
const Environment = require('./Environment')
const Atom = require('./Atom')
const Primitive = require('./Primitive')
const ListCreator = require('./ListCreator')
const parse = require('./Parser').parse

module.exports = class Engine {		
	constructor() {
		this._env = new Environment()

		this._initPrimitives()
		this._initPredefinedFunctions()
	}

	_initPrimitives() {
		const lc = new ListCreator()
		
		this._primitives = [
			[Atom.car,			1, s => s.car()],
			[Atom.cdr,			1, s => s.cdr()],
			[Atom.atom,			1, s => Engine._boolToS(s.atom())],
			[Atom.eval,			1, s => this._evaluate(s)],
			[Atom.cons,			2, (s, t) => s.cons(t)],
			[Atom.eq,			2, (s, t) => Engine._boolToS(s.eq(t))],
			[Atom.SET,			2, (s, t) => this._env.set(s, t)],
			[Atom.lambda,		2, (s, t) => lc.create(Atom.lambda, s, t)],
			[Atom.nlambda,		2, (s, t) => lc.create(Atom.nlambda, s, t)],
			[Atom.defun,		3, (s, t, u) => this._env.defun(s, t, u)],
			[Atom.ndefun,		3, (s, t, u) => this._env.ndefun(s, t, u)],
			[Atom.cond,			undefined, s => this._evaluateCond(s)],
		].map(tup => new Primitive(tup[0], tup[1], tup[2]))
	}

	_initPredefinedFunctions() {
		this._env.set(Atom.nil, Atom.nil)
		this._env.set(Atom.t, Atom.t)
		this.evaluate(parse("(ndefun quote (x) x)"))
		this.evaluate(parse("(defun null (x) (eq x nil))"))
	}

	evaluate(s) {
		this._env.backup()

		try {
			return this._evaluate(s)		
		} catch (e) {
			this._env.restore()
			throw e
		}
	}

	_evaluate(s) {
		if (s.atom()) {
			return this._env.lookup(s)
		}

		if (!s.isList()) {
			return s.error(Atom.invalid)
		}

		const primitive = this._primitives.find(p => p.isWithName(s.car()))
		if (primitive) {
			return this._applyPrimitive(primitive, s.cdr())
		}

		if (s.car().eq(Atom.error)) {
			return s.error(this._evaluateList(s.cdr()))
		}

		return this._apply(this._evaluate(s.car()), s.cdr())
	}

	_evaluateList(list) {
		if (list.null()) {
			return Atom.nil
		}

		return this._evaluate(list.car()).cons(this._evaluateList(list.cdr()))
	}

	_evaluateCond(testForms) {
		if (testForms.null()) {
			return Atom.nil
		}

		const currPair = testForms.car()
			
		if (currPair.atom()) {
			return currPair.error(Atom.cond)
		}

		if (this._evaluate(currPair.car()).t()) {
			return this._evaluate(currPair.cdr().car())
		}

		return this._evaluateCond(testForms.cdr())
	}

	_applyPrimitive(primitive, args) {
		primitive.checkNumberOfArgs(args)
		const actuals = primitive.isNormal() ? args : this._evaluateList(args)	
		return primitive.run(actuals)
	}

	_apply(lambda, args) {
		if (lambda.getListLength() !== 3) {
			return this._throwInvalidLambdaError(lambda)
		}

		const tag = lambda.car()
		const formals = lambda.cdr().car()

		if ((!tag.eq(Atom.lambda) && !tag.eq(Atom.nlambda)) ||
			(!formals.isList())) {
			return this._throwInvalidLambdaError(lambda)
		}

		this._checkArgsInLambdaCall(lambda, args)

		const actuals = tag.eq(Atom.lambda) ? this._evaluateList(args) : args
		const body = lambda.cdr().cdr().car()
		
		this._env.bind(formals, actuals)

		try {
			return this._evaluate(body)
		} finally {
			this._env.unbind(formals.getListLength())	
		}
	}

	_checkArgsInLambdaCall(lambda, args) {
		const argsLength = args.getListLength()
		
		if (argsLength === undefined) {
			return lambda.cons(args).error(Atom.invalid)
		}

		const formalsLength = lambda.cdr().car().getListLength()

		if (argsLength < formalsLength) {
			return lambda.cons(args).error(Atom.missing)
		}

		if (argsLength > formalsLength) {
			return lambda.cons(args).error(Atom.redundant)
		}
	}

	_throwInvalidLambdaError(lambda) {
		return lambda.error(Atom.invalid)
	}

	static _boolToS(bool) {
		return bool ? Atom.t : Atom.nil
	}
}

},{"./Atom":1,"./Environment":3,"./ListCreator":5,"./Parser":7,"./Primitive":9}],3:[function(require,module,exports){
const Atom = require('./Atom')
const ListCreator = require('./ListCreator')
const EvaluationError = require('./EvaluationError')

module.exports = class Environment {
	constructor() {
		this._alist = Atom.nil
		this._backupAList = Atom.nil
		this._formalsAList = Atom.nil
	}

	getAList() {
		return this._alist
	}

	getFormalsAList() {
		return this._formalsAList
	}

	set(key, value) {
		this._alist = key.cons(value).cons(this._alist)
		return value
	}

	defun(name, formals, body) {
		return this._genericDefun(name, formals, body, Atom.lambda)
	}

	ndefun(name, formals, body) {
		return this._genericDefun(name, formals, body, Atom.nlambda)
	}

	_genericDefun(name, formals, body, tag) {
		const lc = new ListCreator()
		const lambda = lc.create(tag, formals, body)
		return this.set(name, lambda)	
	}

	lookup(s) {
		for (const list of [this._formalsAList, this._alist]) {
			const result = Environment._lookup(s, list)
			if (result !== null) {
				return result
			}
		}
	
		return s.error(Atom.undefined)
	}

	static _lookup(s, list) {
		if (list.null()) {
			return null
		}

		const currPair = list.car()
		return s.eq(currPair.car())
			? currPair.cdr()
			: Environment._lookup(s, list.cdr()) 
	}

	backup() {
		this._backupAList = this._alist
	}

	restore() {
		this._alist = this._backupAList
		this._backupAList = Atom.nil
	}

	bind(formals, actuals) {
		if (formals.null() && actuals.null()) {
			return
		}

		this._formalsAList = formals.car()
									.cons(actuals.car())
									.cons(this._formalsAList)

		this.bind(formals.cdr(), actuals.cdr())
	}

	unbind(numFormals) {
		for (var i = 0; i < numFormals; i++) {
			this._formalsAList = this._formalsAList.cdr()
		}
	}
}

},{"./Atom":1,"./EvaluationError":4,"./ListCreator":5}],4:[function(require,module,exports){
module.exports = class EvaluationError extends Error {
	constructor(s) {
		super(s.toString())
		this.name = this.constructor.name
		this.s = s
	}
}
},{}],5:[function(require,module,exports){
const Atom = require('./Atom')

module.exports = class ListCreator {
	create() {		
		const args = Array.from(arguments)
		
		if (args.length === 0) {
			return Atom.nil
		}

		const carArg = args[0]
		const cdrArgs = args.slice(1)

		return carArg.cons(this.create(...cdrArgs))
	}	

	ofAtoms() {
		const atomsArray = Array.from(arguments).map(val => new Atom(val))
		return this.create(...atomsArray)
	}
}

},{"./Atom":1}],6:[function(require,module,exports){
const S = require('./S')
const Atom = require('./Atom')

module.exports = class Pair extends S {
		
	constructor(car, cdr) {
		super() 
		this._car = car
		this._cdr = cdr
	}

	atom() {
		return false
	}

	car() {
		return this._car
	}

	cdr() {
		return this._cdr
	}

	eq(s) {
    	return false
	}

	equals(s) {
		return !s.atom() &&
				this._car.equals(s._car) && 
				this._cdr.equals(s._cdr)
	}

	isList() {
		return this._cdr.isList()
	}

	getListAsArray() {
		var list = this._cdr.getListAsArray()
		list?.unshift(this._car)
		return list
	}

	toString() {
		const list = this.getListAsArray()
		if (list) {
			return '(' + list.join(' ') + ')'
		}

		return '(' + [this._car, this._cdr].join(' . ') + ')'
	}
}

},{"./Atom":1,"./S":10}],7:[function(require,module,exports){
/*
 * Generated by PEG.js 0.10.0.
 *
 * http://pegjs.org/
 */

"use strict";

function peg$subclass(child, parent) {
  function ctor() { this.constructor = child; }
  ctor.prototype = parent.prototype;
  child.prototype = new ctor();
}

function peg$SyntaxError(message, expected, found, location) {
  this.message  = message;
  this.expected = expected;
  this.found    = found;
  this.location = location;
  this.name     = "SyntaxError";

  if (typeof Error.captureStackTrace === "function") {
    Error.captureStackTrace(this, peg$SyntaxError);
  }
}

peg$subclass(peg$SyntaxError, Error);

peg$SyntaxError.buildMessage = function(expected, found) {
  var DESCRIBE_EXPECTATION_FNS = {
        literal: function(expectation) {
          return "\"" + literalEscape(expectation.text) + "\"";
        },

        "class": function(expectation) {
          var escapedParts = "",
              i;

          for (i = 0; i < expectation.parts.length; i++) {
            escapedParts += expectation.parts[i] instanceof Array
              ? classEscape(expectation.parts[i][0]) + "-" + classEscape(expectation.parts[i][1])
              : classEscape(expectation.parts[i]);
          }

          return "[" + (expectation.inverted ? "^" : "") + escapedParts + "]";
        },

        any: function(expectation) {
          return "any character";
        },

        end: function(expectation) {
          return "end of input";
        },

        other: function(expectation) {
          return expectation.description;
        }
      };

  function hex(ch) {
    return ch.charCodeAt(0).toString(16).toUpperCase();
  }

  function literalEscape(s) {
    return s
      .replace(/\\/g, '\\\\')
      .replace(/"/g,  '\\"')
      .replace(/\0/g, '\\0')
      .replace(/\t/g, '\\t')
      .replace(/\n/g, '\\n')
      .replace(/\r/g, '\\r')
      .replace(/[\x00-\x0F]/g,          function(ch) { return '\\x0' + hex(ch); })
      .replace(/[\x10-\x1F\x7F-\x9F]/g, function(ch) { return '\\x'  + hex(ch); });
  }

  function classEscape(s) {
    return s
      .replace(/\\/g, '\\\\')
      .replace(/\]/g, '\\]')
      .replace(/\^/g, '\\^')
      .replace(/-/g,  '\\-')
      .replace(/\0/g, '\\0')
      .replace(/\t/g, '\\t')
      .replace(/\n/g, '\\n')
      .replace(/\r/g, '\\r')
      .replace(/[\x00-\x0F]/g,          function(ch) { return '\\x0' + hex(ch); })
      .replace(/[\x10-\x1F\x7F-\x9F]/g, function(ch) { return '\\x'  + hex(ch); });
  }

  function describeExpectation(expectation) {
    return DESCRIBE_EXPECTATION_FNS[expectation.type](expectation);
  }

  function describeExpected(expected) {
    var descriptions = new Array(expected.length),
        i, j;

    for (i = 0; i < expected.length; i++) {
      descriptions[i] = describeExpectation(expected[i]);
    }

    descriptions.sort();

    if (descriptions.length > 0) {
      for (i = 1, j = 1; i < descriptions.length; i++) {
        if (descriptions[i - 1] !== descriptions[i]) {
          descriptions[j] = descriptions[i];
          j++;
        }
      }
      descriptions.length = j;
    }

    switch (descriptions.length) {
      case 1:
        return descriptions[0];

      case 2:
        return descriptions[0] + " or " + descriptions[1];

      default:
        return descriptions.slice(0, -1).join(", ")
          + ", or "
          + descriptions[descriptions.length - 1];
    }
  }

  function describeFound(found) {
    return found ? "\"" + literalEscape(found) + "\"" : "end of input";
  }

  return "Expected " + describeExpected(expected) + " but " + describeFound(found) + " found.";
};

function peg$parse(input, options) {
  options = options !== void 0 ? options : {};

  var peg$FAILED = {},

      peg$startRuleFunctions = { S: peg$parseS },
      peg$startRuleFunction  = peg$parseS,

      peg$c0 = "(",
      peg$c1 = peg$literalExpectation("(", false),
      peg$c2 = ")",
      peg$c3 = peg$literalExpectation(")", false),
      peg$c4 = function(complex) { return complex },
      peg$c5 = function(sym) { return new Atom(sym) },
      peg$c6 = function(s) { return s },
      peg$c7 = function(listArray) {
      		return lc.create(...listArray)
      	},
      peg$c8 = ".",
      peg$c9 = peg$literalExpectation(".", false),
      peg$c10 = function(car, cdr) { 
      		return new Pair(car, cdr)
      	},
      peg$c11 = /^[^()'.;[\]\0- \x7F-\uFFFF]/,
      peg$c12 = peg$classExpectation(["(", ")", "'", ".", ";", "[", "]", ["\0", " "], ["\x7F", "\uFFFF"]], true, false),
      peg$c13 = function() { 
      		return text().toUpperCase()
      	},
      peg$c14 = "'",
      peg$c15 = peg$literalExpectation("'", false),
      peg$c16 = function(s) { 
      		return lc.create(quote, s)
      	},
      peg$c17 = ";",
      peg$c18 = peg$literalExpectation(";", false),
      peg$c19 = /^[^\n\r]/,
      peg$c20 = peg$classExpectation(["\n", "\r"], true, false),
      peg$c21 = /^[\0- \x7F-\uFFFF]/,
      peg$c22 = peg$classExpectation([["\0", " "], ["\x7F", "\uFFFF"]], false, false),

      peg$currPos          = 0,
      peg$savedPos         = 0,
      peg$posDetailsCache  = [{ line: 1, column: 1 }],
      peg$maxFailPos       = 0,
      peg$maxFailExpected  = [],
      peg$silentFails      = 0,

      peg$result;

  if ("startRule" in options) {
    if (!(options.startRule in peg$startRuleFunctions)) {
      throw new Error("Can't start parsing from rule \"" + options.startRule + "\".");
    }

    peg$startRuleFunction = peg$startRuleFunctions[options.startRule];
  }

  function text() {
    return input.substring(peg$savedPos, peg$currPos);
  }

  function location() {
    return peg$computeLocation(peg$savedPos, peg$currPos);
  }

  function expected(description, location) {
    location = location !== void 0 ? location : peg$computeLocation(peg$savedPos, peg$currPos)

    throw peg$buildStructuredError(
      [peg$otherExpectation(description)],
      input.substring(peg$savedPos, peg$currPos),
      location
    );
  }

  function error(message, location) {
    location = location !== void 0 ? location : peg$computeLocation(peg$savedPos, peg$currPos)

    throw peg$buildSimpleError(message, location);
  }

  function peg$literalExpectation(text, ignoreCase) {
    return { type: "literal", text: text, ignoreCase: ignoreCase };
  }

  function peg$classExpectation(parts, inverted, ignoreCase) {
    return { type: "class", parts: parts, inverted: inverted, ignoreCase: ignoreCase };
  }

  function peg$anyExpectation() {
    return { type: "any" };
  }

  function peg$endExpectation() {
    return { type: "end" };
  }

  function peg$otherExpectation(description) {
    return { type: "other", description: description };
  }

  function peg$computePosDetails(pos) {
    var details = peg$posDetailsCache[pos], p;

    if (details) {
      return details;
    } else {
      p = pos - 1;
      while (!peg$posDetailsCache[p]) {
        p--;
      }

      details = peg$posDetailsCache[p];
      details = {
        line:   details.line,
        column: details.column
      };

      while (p < pos) {
        if (input.charCodeAt(p) === 10) {
          details.line++;
          details.column = 1;
        } else {
          details.column++;
        }

        p++;
      }

      peg$posDetailsCache[pos] = details;
      return details;
    }
  }

  function peg$computeLocation(startPos, endPos) {
    var startPosDetails = peg$computePosDetails(startPos),
        endPosDetails   = peg$computePosDetails(endPos);

    return {
      start: {
        offset: startPos,
        line:   startPosDetails.line,
        column: startPosDetails.column
      },
      end: {
        offset: endPos,
        line:   endPosDetails.line,
        column: endPosDetails.column
      }
    };
  }

  function peg$fail(expected) {
    if (peg$currPos < peg$maxFailPos) { return; }

    if (peg$currPos > peg$maxFailPos) {
      peg$maxFailPos = peg$currPos;
      peg$maxFailExpected = [];
    }

    peg$maxFailExpected.push(expected);
  }

  function peg$buildSimpleError(message, location) {
    return new peg$SyntaxError(message, null, null, location);
  }

  function peg$buildStructuredError(expected, found, location) {
    return new peg$SyntaxError(
      peg$SyntaxError.buildMessage(expected, found),
      expected,
      found,
      location
    );
  }

  function peg$parseS() {
    var s0, s1, s2, s3, s4, s5, s6, s7;

    s0 = peg$currPos;
    s1 = peg$parse_();
    if (s1 !== peg$FAILED) {
      s2 = peg$currPos;
      if (input.charCodeAt(peg$currPos) === 40) {
        s3 = peg$c0;
        peg$currPos++;
      } else {
        s3 = peg$FAILED;
        if (peg$silentFails === 0) { peg$fail(peg$c1); }
      }
      if (s3 !== peg$FAILED) {
        s4 = peg$parse_();
        if (s4 !== peg$FAILED) {
          s5 = peg$parsePair();
          if (s5 === peg$FAILED) {
            s5 = peg$parseList();
          }
          if (s5 !== peg$FAILED) {
            s6 = peg$parse_();
            if (s6 !== peg$FAILED) {
              if (input.charCodeAt(peg$currPos) === 41) {
                s7 = peg$c2;
                peg$currPos++;
              } else {
                s7 = peg$FAILED;
                if (peg$silentFails === 0) { peg$fail(peg$c3); }
              }
              if (s7 !== peg$FAILED) {
                peg$savedPos = s2;
                s3 = peg$c4(s5);
                s2 = s3;
              } else {
                peg$currPos = s2;
                s2 = peg$FAILED;
              }
            } else {
              peg$currPos = s2;
              s2 = peg$FAILED;
            }
          } else {
            peg$currPos = s2;
            s2 = peg$FAILED;
          }
        } else {
          peg$currPos = s2;
          s2 = peg$FAILED;
        }
      } else {
        peg$currPos = s2;
        s2 = peg$FAILED;
      }
      if (s2 === peg$FAILED) {
        s2 = peg$currPos;
        s3 = peg$parseSymbol();
        if (s3 !== peg$FAILED) {
          peg$savedPos = s2;
          s3 = peg$c5(s3);
        }
        s2 = s3;
        if (s2 === peg$FAILED) {
          s2 = peg$parseQuote();
        }
      }
      if (s2 !== peg$FAILED) {
        s3 = peg$parse_();
        if (s3 !== peg$FAILED) {
          peg$savedPos = s0;
          s1 = peg$c6(s2);
          s0 = s1;
        } else {
          peg$currPos = s0;
          s0 = peg$FAILED;
        }
      } else {
        peg$currPos = s0;
        s0 = peg$FAILED;
      }
    } else {
      peg$currPos = s0;
      s0 = peg$FAILED;
    }

    return s0;
  }

  function peg$parseList() {
    var s0, s1, s2, s3;

    s0 = peg$currPos;
    s1 = [];
    s2 = peg$currPos;
    s3 = peg$parseS();
    if (s3 !== peg$FAILED) {
      peg$savedPos = s2;
      s3 = peg$c6(s3);
    }
    s2 = s3;
    while (s2 !== peg$FAILED) {
      s1.push(s2);
      s2 = peg$currPos;
      s3 = peg$parseS();
      if (s3 !== peg$FAILED) {
        peg$savedPos = s2;
        s3 = peg$c6(s3);
      }
      s2 = s3;
    }
    if (s1 !== peg$FAILED) {
      peg$savedPos = s0;
      s1 = peg$c7(s1);
    }
    s0 = s1;

    return s0;
  }

  function peg$parsePair() {
    var s0, s1, s2, s3;

    s0 = peg$currPos;
    s1 = peg$parseS();
    if (s1 !== peg$FAILED) {
      if (input.charCodeAt(peg$currPos) === 46) {
        s2 = peg$c8;
        peg$currPos++;
      } else {
        s2 = peg$FAILED;
        if (peg$silentFails === 0) { peg$fail(peg$c9); }
      }
      if (s2 !== peg$FAILED) {
        s3 = peg$parseS();
        if (s3 !== peg$FAILED) {
          peg$savedPos = s0;
          s1 = peg$c10(s1, s3);
          s0 = s1;
        } else {
          peg$currPos = s0;
          s0 = peg$FAILED;
        }
      } else {
        peg$currPos = s0;
        s0 = peg$FAILED;
      }
    } else {
      peg$currPos = s0;
      s0 = peg$FAILED;
    }

    return s0;
  }

  function peg$parseSymbol() {
    var s0, s1, s2;

    s0 = peg$currPos;
    s1 = [];
    if (peg$c11.test(input.charAt(peg$currPos))) {
      s2 = input.charAt(peg$currPos);
      peg$currPos++;
    } else {
      s2 = peg$FAILED;
      if (peg$silentFails === 0) { peg$fail(peg$c12); }
    }
    if (s2 !== peg$FAILED) {
      while (s2 !== peg$FAILED) {
        s1.push(s2);
        if (peg$c11.test(input.charAt(peg$currPos))) {
          s2 = input.charAt(peg$currPos);
          peg$currPos++;
        } else {
          s2 = peg$FAILED;
          if (peg$silentFails === 0) { peg$fail(peg$c12); }
        }
      }
    } else {
      s1 = peg$FAILED;
    }
    if (s1 !== peg$FAILED) {
      peg$savedPos = s0;
      s1 = peg$c13();
    }
    s0 = s1;

    return s0;
  }

  function peg$parseQuote() {
    var s0, s1, s2;

    s0 = peg$currPos;
    if (input.charCodeAt(peg$currPos) === 39) {
      s1 = peg$c14;
      peg$currPos++;
    } else {
      s1 = peg$FAILED;
      if (peg$silentFails === 0) { peg$fail(peg$c15); }
    }
    if (s1 !== peg$FAILED) {
      s2 = peg$parseS();
      if (s2 !== peg$FAILED) {
        peg$savedPos = s0;
        s1 = peg$c16(s2);
        s0 = s1;
      } else {
        peg$currPos = s0;
        s0 = peg$FAILED;
      }
    } else {
      peg$currPos = s0;
      s0 = peg$FAILED;
    }

    return s0;
  }

  function peg$parseComment() {
    var s0, s1, s2, s3;

    s0 = peg$currPos;
    if (input.charCodeAt(peg$currPos) === 59) {
      s1 = peg$c17;
      peg$currPos++;
    } else {
      s1 = peg$FAILED;
      if (peg$silentFails === 0) { peg$fail(peg$c18); }
    }
    if (s1 !== peg$FAILED) {
      s2 = [];
      if (peg$c19.test(input.charAt(peg$currPos))) {
        s3 = input.charAt(peg$currPos);
        peg$currPos++;
      } else {
        s3 = peg$FAILED;
        if (peg$silentFails === 0) { peg$fail(peg$c20); }
      }
      while (s3 !== peg$FAILED) {
        s2.push(s3);
        if (peg$c19.test(input.charAt(peg$currPos))) {
          s3 = input.charAt(peg$currPos);
          peg$currPos++;
        } else {
          s3 = peg$FAILED;
          if (peg$silentFails === 0) { peg$fail(peg$c20); }
        }
      }
      if (s2 !== peg$FAILED) {
        s1 = [s1, s2];
        s0 = s1;
      } else {
        peg$currPos = s0;
        s0 = peg$FAILED;
      }
    } else {
      peg$currPos = s0;
      s0 = peg$FAILED;
    }

    return s0;
  }

  function peg$parse_() {
    var s0, s1;

    s0 = [];
    if (peg$c21.test(input.charAt(peg$currPos))) {
      s1 = input.charAt(peg$currPos);
      peg$currPos++;
    } else {
      s1 = peg$FAILED;
      if (peg$silentFails === 0) { peg$fail(peg$c22); }
    }
    if (s1 === peg$FAILED) {
      s1 = peg$parseComment();
    }
    while (s1 !== peg$FAILED) {
      s0.push(s1);
      if (peg$c21.test(input.charAt(peg$currPos))) {
        s1 = input.charAt(peg$currPos);
        peg$currPos++;
      } else {
        s1 = peg$FAILED;
        if (peg$silentFails === 0) { peg$fail(peg$c22); }
      }
      if (s1 === peg$FAILED) {
        s1 = peg$parseComment();
      }
    }

    return s0;
  }


  	const Pair = require("./Pair")
  	const Atom = require("./Atom")
  	const ListCreator = require("./ListCreator")
  	const lc = new ListCreator()
  	const quote = Atom.quote


  peg$result = peg$startRuleFunction();

  if (peg$result !== peg$FAILED && peg$currPos === input.length) {
    return peg$result;
  } else {
    if (peg$result !== peg$FAILED && peg$currPos < input.length) {
      peg$fail(peg$endExpectation());
    }

    throw peg$buildStructuredError(
      peg$maxFailExpected,
      peg$maxFailPos < input.length ? input.charAt(peg$maxFailPos) : null,
      peg$maxFailPos < input.length
        ? peg$computeLocation(peg$maxFailPos, peg$maxFailPos + 1)
        : peg$computeLocation(peg$maxFailPos, peg$maxFailPos)
    );
  }
}

module.exports = {
  SyntaxError: peg$SyntaxError,
  parse:       peg$parse
};

},{"./Atom":1,"./ListCreator":5,"./Pair":6}],8:[function(require,module,exports){
const parse = require('./Parser').parse
const ParserSyntaxError = require('./Parser').SyntaxError

module.exports = class ParserStateWrapper {
	static Accept = "ACCEPT"
	static ExpectMore = "EXPECT_MORE"
	static Reject = "REJECT"

	parse(str) {
		try {
			return { output: parse(str), type: ParserStateWrapper.Accept }
		} catch (e) {
			if (!(e instanceof ParserSyntaxError)) {
				throw e
			}

			return { 
				output: e.found, 
				type: e.found ? ParserStateWrapper.Reject : ParserStateWrapper.ExpectMore
			}
		}
	}
}
},{"./Parser":7}],9:[function(require,module,exports){
const Atom = require('./Atom')

module.exports = class Primitive {		
	constructor(name, expectedNumArgs, closure) {
		this._name = name
		this._expectedNumArgs = expectedNumArgs
		this._closure = closure
	}

	checkNumberOfArgs(args) {
		const s = this._name.cons(args)
		const argsArray = args.getListAsArray()

		if (argsArray === undefined) {
			return s.error(Atom.invalid)
		}		

		if (this._expectedNumArgs === undefined) {
			return
		}

		const recievedNumArgs = argsArray.length

		if (recievedNumArgs < this._expectedNumArgs) {
			return s.error(Atom.missing)
		}

		if (recievedNumArgs > this._expectedNumArgs) {
			return s.error(Atom.redundant)
		}
	}

	run(actuals) {
		try {
			this.checkNumberOfArgs(actuals)
		} catch {
			throw this._name.cons(actuals).error(Atom.bug)
		}

		if (this._expectedNumArgs) {
			return this._closure(...actuals.getListAsArray())
		}

		return this._closure(actuals)
	}

	isWithName(name) {
		return this._name.eq(name)
	}

	isNormal() {
		return 	[
					Atom.cond, Atom.lambda, Atom.nlambda, Atom.defun, Atom.ndefun
				].some(name => this.isWithName(name))
	}
}

},{"./Atom":1}],10:[function(require,module,exports){
module.exports = class S {
	atom() {
		return this._errorNotImplemented()
	}

	car() {
		return this._errorNotImplemented()
	}

	cdr() {
		return this._errorNotImplemented()
	}

	cons(s) {
		const Pair = require('./Pair')
		return new Pair(this, s)
	}

	eq(s) {
		return this._errorNotImplemented()
	}

	equals(s) {
		return this._errorNotImplemented()
	}

	null() {
		const Atom = require('./Atom')
		return this.eq(Atom.nil)
	}

	t() {
		return !this.null()	
	}

	error(kind) {
		const EvaluationError = require('./EvaluationError')
		throw new EvaluationError(kind ? this.cons(kind) : this)
	}

	isList() {
		return this._errorNotImplemented()
	}

	getListAsArray() {
		return this._errorNotImplemented()
	}

	getListLength() {
		return this.getListAsArray()?.length
	}

	toString() {
		return this._errorNotImplemented()
	}

	_errorNotImplemented() {
		return this.error(Atom.bug)		
	}
}

},{"./Atom":1,"./EvaluationError":4,"./Pair":6}],11:[function(require,module,exports){
const ParserStateWrapper = require('./ParserStateWrapper.js')
const Engine = require('./Engine.js')
window.$ = require('jquery')
const terminal = require('jquery.terminal')($)

const e = new Engine()
const pw = new ParserStateWrapper()

$('head').append('<link rel="stylesheet" type="text/css" \
		href="./node_modules/jquery.terminal/css/jquery.terminal.min.css"/>')
$('body').append('<p id="repl"></p>')
	
$(function($, undefined) {
	var buffer = ''
	$('#repl').terminal(function(line) {
    	buffer += line
    	const parseResult = pw.parse(buffer)
    	switch (parseResult.type) {
			case ParserStateWrapper.Accept:
				try {
					this.echo(e.evaluate(parseResult.output).toString())	
				} catch (e) {
					this.echo(`Error: ${e.s.car()} - ${e.s.cdr()}`)
				}
				this.set_prompt('> ')
				buffer = ''
				break

			case ParserStateWrapper.ExpectMore:
				this.set_prompt(buffer.length === 0 ? '> ' : '- ')
				break

			case ParserStateWrapper.Reject:
				this.echo('?')
				buffer = ''
				break
		}
	}, {
        greetings: 'Mini-LISP REPL',
        name: 'Mini-LISP',
        height: 500,
        width: 400,
        prompt: '> '
	})
})

},{"./Engine.js":2,"./ParserStateWrapper.js":8,"jquery":15,"jquery.terminal":14}],12:[function(require,module,exports){
(function (Buffer){(function (){
var clone = (function() {
'use strict';

/**
 * Clones (copies) an Object using deep copying.
 *
 * This function supports circular references by default, but if you are certain
 * there are no circular references in your object, you can save some CPU time
 * by calling clone(obj, false).
 *
 * Caution: if `circular` is false and `parent` contains circular references,
 * your program may enter an infinite loop and crash.
 *
 * @param `parent` - the object to be cloned
 * @param `circular` - set to true if the object to be cloned may contain
 *    circular references. (optional - true by default)
 * @param `depth` - set to a number if the object is only to be cloned to
 *    a particular depth. (optional - defaults to Infinity)
 * @param `prototype` - sets the prototype to be used when cloning an object.
 *    (optional - defaults to parent prototype).
*/
function clone(parent, circular, depth, prototype) {
  var filter;
  if (typeof circular === 'object') {
    depth = circular.depth;
    prototype = circular.prototype;
    filter = circular.filter;
    circular = circular.circular
  }
  // maintain two arrays for circular references, where corresponding parents
  // and children have the same index
  var allParents = [];
  var allChildren = [];

  var useBuffer = typeof Buffer != 'undefined';

  if (typeof circular == 'undefined')
    circular = true;

  if (typeof depth == 'undefined')
    depth = Infinity;

  // recurse this function so we don't reset allParents and allChildren
  function _clone(parent, depth) {
    // cloning null always returns null
    if (parent === null)
      return null;

    if (depth == 0)
      return parent;

    var child;
    var proto;
    if (typeof parent != 'object') {
      return parent;
    }

    if (clone.__isArray(parent)) {
      child = [];
    } else if (clone.__isRegExp(parent)) {
      child = new RegExp(parent.source, __getRegExpFlags(parent));
      if (parent.lastIndex) child.lastIndex = parent.lastIndex;
    } else if (clone.__isDate(parent)) {
      child = new Date(parent.getTime());
    } else if (useBuffer && Buffer.isBuffer(parent)) {
      if (Buffer.allocUnsafe) {
        // Node.js >= 4.5.0
        child = Buffer.allocUnsafe(parent.length);
      } else {
        // Older Node.js versions
        child = new Buffer(parent.length);
      }
      parent.copy(child);
      return child;
    } else {
      if (typeof prototype == 'undefined') {
        proto = Object.getPrototypeOf(parent);
        child = Object.create(proto);
      }
      else {
        child = Object.create(prototype);
        proto = prototype;
      }
    }

    if (circular) {
      var index = allParents.indexOf(parent);

      if (index != -1) {
        return allChildren[index];
      }
      allParents.push(parent);
      allChildren.push(child);
    }

    for (var i in parent) {
      var attrs;
      if (proto) {
        attrs = Object.getOwnPropertyDescriptor(proto, i);
      }

      if (attrs && attrs.set == null) {
        continue;
      }
      child[i] = _clone(parent[i], depth - 1);
    }

    return child;
  }

  return _clone(parent, depth);
}

/**
 * Simple flat clone using prototype, accepts only objects, usefull for property
 * override on FLAT configuration object (no nested props).
 *
 * USE WITH CAUTION! This may not behave as you wish if you do not know how this
 * works.
 */
clone.clonePrototype = function clonePrototype(parent) {
  if (parent === null)
    return null;

  var c = function () {};
  c.prototype = parent;
  return new c();
};

// private utility functions

function __objToStr(o) {
  return Object.prototype.toString.call(o);
};
clone.__objToStr = __objToStr;

function __isDate(o) {
  return typeof o === 'object' && __objToStr(o) === '[object Date]';
};
clone.__isDate = __isDate;

function __isArray(o) {
  return typeof o === 'object' && __objToStr(o) === '[object Array]';
};
clone.__isArray = __isArray;

function __isRegExp(o) {
  return typeof o === 'object' && __objToStr(o) === '[object RegExp]';
};
clone.__isRegExp = __isRegExp;

function __getRegExpFlags(re) {
  var flags = '';
  if (re.global) flags += 'g';
  if (re.ignoreCase) flags += 'i';
  if (re.multiline) flags += 'm';
  return flags;
};
clone.__getRegExpFlags = __getRegExpFlags;

return clone;
})();

if (typeof module === 'object' && module.exports) {
  module.exports = clone;
}

}).call(this)}).call(this,require("buffer").Buffer)
},{"buffer":19}],13:[function(require,module,exports){
var clone = require('clone');

module.exports = function(options, defaults) {
  options = options || {};

  Object.keys(defaults).forEach(function(key) {
    if (typeof options[key] === 'undefined') {
      options[key] = clone(defaults[key]);
    }
  });

  return options;
};
},{"clone":12}],14:[function(require,module,exports){
(function (global,setImmediate){(function (){
/**@license
 *       __ _____                     ________                              __
 *      / // _  /__ __ _____ ___ __ _/__  ___/__ ___ ______ __ __  __ ___  / /
 *  __ / // // // // // _  // _// // / / // _  // _//     // //  \/ // _ \/ /
 * /  / // // // // // ___// / / // / / // ___// / / / / // // /\  // // / /__
 * \___//____ \\___//____//_/ _\_  / /_//____//_/ /_/ /_//_//_/ /_/ \__\_\___/
 *           \/              /____/                              version 2.28.1
 *
 * This file is part of jQuery Terminal. https://terminal.jcubic.pl
 *
 * Copyright (c) 2010-2021 Jakub T. Jankiewicz <https://jcubic.pl/me>
 * Released under the MIT license
 *
 * Contains:
 *
 * Storage plugin Distributed under the MIT License
 * modified to work from Data URIs that block storage and cookies in Chrome
 * Copyright (c) 2010 Dave Schindler
 *
 * jQuery Timers licenced with the WTFPL
 * <http://jquery.offput.ca/timers/>
 *
 * Cross-Browser Split 1.1.1
 * Copyright 2007-2012 Steven Levithan <stevenlevithan.com>
 * Available under the MIT License
 *
 * jQuery Caret
 * Copyright (c) 2009, Gideon Sireling
 * 3 clause BSD License
 *
 * sprintf.js
 * Copyright (c) 2007-2013 Alexandru Marasteanu <hello at alexei dot ro>
 * licensed under 3 clause BSD license
 *
 * debounce function from Lodash
 * Copyright JS Foundation and other contributors <https://js.foundation/>
 * The MIT License
 *
 * emoji regex v9.0.0 by Mathias Bynens
 * MIT license
 *
 * broken image by Sophia Bai from the Noun Project (CC-BY)
 *
 * Date: Wed, 04 Aug 2021 06:57:27 +0000
 */
/* global define, Map */
/* eslint-disable */
/* istanbul ignore next */
(function(ctx) {
    var sprintf = function() {
        if (!sprintf.cache.hasOwnProperty(arguments[0])) {
            sprintf.cache[arguments[0]] = sprintf.parse(arguments[0]);
        }
        return sprintf.format.call(null, sprintf.cache[arguments[0]], arguments);
    };
    sprintf.format = function(parse_tree, argv) {
        var cursor = 1, tree_length = parse_tree.length, node_type = '', arg, output = [], i, k, match, pad, pad_character, pad_length;
        for (i = 0; i < tree_length; i++) {
            node_type = get_type(parse_tree[i]);
            if (node_type === 'string') {
                output.push(parse_tree[i]);
            }
            else if (node_type === 'array') {
                match = parse_tree[i]; // convenience purposes only
                if (match[2]) { // keyword argument
                    arg = argv[cursor];
                    for (k = 0; k < match[2].length; k++) {
                        if (!arg.hasOwnProperty(match[2][k])) {
                            throw(sprintf('[sprintf] property "%s" does not exist', match[2][k]));
                        }
                        arg = arg[match[2][k]];
                    }
                }
                else if (match[1]) { // positional argument (explicit)
                    arg = argv[match[1]];
                }
                else { // positional argument (implicit)
                    arg = argv[cursor++];
                }

                if (/[^s]/.test(match[8]) && (get_type(arg) !== 'number')) {
                    throw(sprintf('[sprintf] expecting number but found %s', get_type(arg)));
                }
                switch (match[8]) {
                    case 'b': arg = arg.toString(2); break;
                    case 'c': arg = String.fromCharCode(arg); break;
                    case 'd': arg = parseInt(arg, 10); break;
                    case 'e': arg = match[7] ? arg.toExponential(match[7]) : arg.toExponential(); break;
                    case 'f': arg = match[7] ? parseFloat(arg).toFixed(match[7]) : parseFloat(arg); break;
                    case 'o': arg = arg.toString(8); break;
                    case 's': arg = ((arg = String(arg)) && match[7] ? arg.slice(0, match[7]) : arg); break;
                    case 'u': arg = arg >>> 0; break;
                    case 'x': arg = arg.toString(16); break;
                    case 'X': arg = arg.toString(16).toUpperCase(); break;
                }
                arg = (/[def]/.test(match[8]) && match[3] && arg >= 0 ? ' +' + arg : arg);
                pad_character = match[4] ? match[4] === '0' ? '0' : match[4].charAt(1) : ' ';
                pad_length = match[6] - String(arg).length;
                pad = match[6] ? str_repeat(pad_character, pad_length) : '';
                output.push(match[5] ? arg + pad : pad + arg);
            }
        }
        return output.join('');
    };

    sprintf.cache = {};

    sprintf.parse = function(fmt) {
        var _fmt = fmt, match = [], parse_tree = [], arg_names = 0;
        while (_fmt) {
            if ((match = /^[^\x25]+/.exec(_fmt)) !== null) {
                parse_tree.push(match[0]);
            }
            else if ((match = /^\x25{2}/.exec(_fmt)) !== null) {
                parse_tree.push('%');
            }
            else if ((match = /^\x25(?:([1-9]\d*)\$|\(([^\)]+)\))?(\+)?(0|'[^$])?(-)?(\d+)?(?:\.(\d+))?([b-fosuxX])/.exec(_fmt)) !== null) {
                if (match[2]) {
                    arg_names |= 1;
                    var field_list = [], replacement_field = match[2], field_match = [];
                    if ((field_match = /^([a-z_][a-z_\d]*)/i.exec(replacement_field)) !== null) {
                        field_list.push(field_match[1]);
                        while ((replacement_field = replacement_field.slice(field_match[0].length)) !== '') {
                            if ((field_match = /^\.([a-z_][a-z_\d]*)/i.exec(replacement_field)) !== null) {
                                field_list.push(field_match[1]);
                            }
                            else if ((field_match = /^\[(\d+)\]/.exec(replacement_field)) !== null) {
                                field_list.push(field_match[1]);
                            }
                            else {
                                throw('[sprintf] huh?');
                            }
                        }
                    }
                    else {
                        throw('[sprintf] huh?');
                    }
                    match[2] = field_list;
                }
                else {
                    arg_names |= 2;
                }
                if (arg_names === 3) {
                    throw('[sprintf] mixing positional and named placeholders is not (yet) supported');
                }
                parse_tree.push(match);
            }
            else {
                throw('[sprintf] huh?');
            }
            _fmt = _fmt.slice(match[0].length);
        }
        return parse_tree;
    };

    var vsprintf = function(fmt, argv, _argv) {
        _argv = argv.slice(0);
        _argv.splice(0, 0, fmt);
        return sprintf.apply(null, _argv);
    };

    /**
     * helpers
     */
    function get_type(variable) {
        return Object.prototype.toString.call(variable).slice(8, -1).toLowerCase();
    }

    function str_repeat(input, multiplier) {
        for (var output = []; multiplier > 0; output[--multiplier] = input) {/* do nothing */}
        return output.join('');
    }

    /**
     * export to either browser or node.js
     */
    ctx.sprintf = sprintf;
    ctx.vsprintf = vsprintf;
})(typeof global !== "undefined" ? global : self || window);
// -----------------------------------------------------------------------
/* eslint-enable */
// UMD taken from https://github.com/umdjs/umd
(function(factory, undefined) {
    var root;
    if (typeof window !== 'undefined') {
        root = window;
    } else if (typeof self !== 'undefined') {
        root = self;
    } else if (typeof global !== 'undefined') {
        root = global;
    } else {
        throw new Error('Unknow context');
    }
    if (typeof define === 'function' && define.amd) {
        // AMD. Register as an anonymous module.
        // istanbul ignore next
        define(['jquery', 'wcwidth'], function(jquery, wcwidth) {
            factory(jquery, wcwidth, root);
            return jquery;
        });
    } else if (typeof module === 'object' && module.exports) {
        // Node/CommonJS
        module.exports = function(root, jQuery, wcwidth) {
            if (jQuery === undefined) {
                // require('jQuery') returns a factory that requires window to
                // build a jQuery instance, we normalize how we use modules
                // that require this pattern but the window provided is a noop
                // if it's defined (how jquery works)
                if (typeof window !== 'undefined') {
                    jQuery = require('jquery');
                } else {
                    jQuery = require('jquery')(root);
                }
            }
            if (wcwidth === undefined) {
                wcwidth = require('wcwidth');
            }
            factory(jQuery, wcwidth, root);
            return jQuery;
        };
    } else {
        // Browser
        // istanbul ignore next
        factory(root.jQuery, root.wcwidth, root);
    }
})(function($, wcwidth, root, undefined) {
    'use strict';
    // -----------------------------------------------------------------------
    // :: debug functions
    // -----------------------------------------------------------------------
    /* eslint-disable */
    /* istanbul ignore next */
    function debug(str) {
        if (false) {
            console.log(str);
            //$.terminal.active().echo(str);
        }
    }
    /* eslint-enable */
    // -----------------------------------------------------------------------
    // :: Replacemenet for jQuery 2 deferred objects
    // -----------------------------------------------------------------------
    function DelayQueue() {
        var callbacks = $.Callbacks();
        var resolved = false;
        this.resolve = function() {
            callbacks.fire();
            resolved = true;
        };
        this.add = function(fn) {
            if (resolved) {
                fn();
            } else {
                callbacks.add(fn);
            }
        };
    }
    // -----------------------------------------------------------------------
    // :: map object to object
    // -----------------------------------------------------------------------
    $.omap = function(o, fn) {
        var result = {};
        $.each(o, function(k, v) {
            result[k] = fn.call(o, k, v);
        });
        return result;
    };
    $.fn.text_length = function() {
        return this.map(function() {
            return $(this).text().length;
        }).get().reduce(function(a, b) {
            return a + b;
        }, 0);
    };
    // -----------------------------------------------------------------------
    // :: Deep clone of objects and arrays
    // -----------------------------------------------------------------------
    var Clone = {
        clone_object: function(object) {
            var tmp = {};
            if (typeof object === 'object') {
                if ($.isArray(object)) {
                    return this.clone_array(object);
                } else if (object === null) {
                    return object;
                } else {
                    for (var key in object) {
                        if ($.isArray(object[key])) {
                            tmp[key] = this.clone_array(object[key]);
                        } else if (typeof object[key] === 'object') {
                            tmp[key] = this.clone_object(object[key]);
                        } else {
                            tmp[key] = object[key];
                        }
                    }
                }
            }
            return tmp;
        },
        clone_array: function(array) {
            if (!is_function(Array.prototype.map)) {
                throw new Error("Your browser don't support ES5 array map " +
                                'use es5-shim');
            }
            return array.slice(0).map(function(item) {
                if (typeof item === 'object') {
                    return this.clone_object(item);
                } else {
                    return item;
                }
            }.bind(this));
        }
    };
    var clone = function(object) {
        return Clone.clone_object(object);
    };
    // -----------------------------------------------------------------------
    // IE11 polyfill
    // -----------------------------------------------------------------------
    /* eslint-disable */
    if ('Map' in root && !('clear' in Map.prototype)) {
        Map.prototype.clear = function() {
            this.forEach(function(value, key, map) {
                map.delete(key);
            });
        };
    }
    // -----------------------------------------------------------------------
    // :: Storage plugin
    // -----------------------------------------------------------------------
    var localStorage;
    /* istanbul ignore next */
    (function() {
        var hasLS = function() {
            try {
                var testKey = 'test', storage = window.localStorage;
                storage.setItem(testKey, '1');
                storage.removeItem(testKey);
                return true;
            } catch (error) {
                return false;
            }
        };
        var hasCookies = function() {
            try {
                document.cookie.split(';');
                return true;
            } catch (e) {
                return false;
            }
        };
        // Private data
        var isLS = hasLS();
        // Private functions
        function wls(n, v) {
            var c;
            if (typeof n === 'string' && typeof v === 'string') {
                localStorage[n] = v;
                return true;
            } else if (typeof n === 'object' && typeof v === 'undefined') {
                for (c in n) {
                    if (n.hasOwnProperty(c)) {
                        localStorage[c] = n[c];
                    }
                }
                return true;
            }
            return false;
        }
        function wc(n, v) {
            var dt, e, c;
            dt = new Date();
            dt.setTime(dt.getTime() + 31536000000);
            e = '; expires=' + dt.toGMTString();
            if (typeof n === 'string' && typeof v === 'string') {
                document.cookie = n + '=' + v + e + '; path=/';
                return true;
            } else if (typeof n === 'object' && typeof v === 'undefined') {
                for (c in n) {
                    if (n.hasOwnProperty(c)) {
                        document.cookie = c + '=' + n[c] + e + '; path=/';
                    }
                }
                return true;
            }
            return false;
        }
        function rls(n) {
            return localStorage[n];
        }
        function rc(n) {
            var nn, ca, i, c;
            nn = n + '=';
            ca = document.cookie.split(';');
            for (i = 0; i < ca.length; i++) {
                c = ca[i];
                while (c.charAt(0) === ' ') {
                    c = c.slice(1, c.length);
                }
                if (c.indexOf(nn) === 0) {
                    return c.slice(nn.length, c.length);
                }
            }
            return null;
        }
        function dls(n) {
            return delete localStorage[n];
        }
        function dc(n) {
            return wc(n, '', -1);
        }
        /**
         * Public API
         * $.Storage.set("name", "value")
         * $.Storage.set({"name1":"value1", "name2":"value2", etc})
         * $.Storage.get("name")
         * $.Storage.remove("name")
         */
        if (!hasCookies() && !isLS) {
            localStorage = {};
            $.extend({
                Storage: {
                    set: wls,
                    get: rls,
                    remove: dls
                }
            });
        } else {
            if (isLS) {
                localStorage = window.localStorage;
            }
            $.extend({
                Storage: {
                    set: isLS ? wls : wc,
                    get: isLS ? rls : rc,
                    remove: isLS ? dls : dc
                }
            });
        }
    })();
    // -----------------------------------------------------------------------
    // :: Debounce from Lodash
    // -----------------------------------------------------------------------
    /* istanbul ignore next */
    var debounce = (function() {
        var FUNC_ERROR_TEXT = 'Expected a function';
        function isObject(value) {
            var type = typeof value;
            return value != null && (type == 'object' || type == 'function');
        }
        function now() {
            return Date.now();
        }
        return function debounce(func, wait, options) {
            var nativeMax = Math.max,
                nativeMin = Math.min;

            var lastArgs,
                lastThis,
                maxWait,
                result,
                timerId,
                lastCallTime,
                lastInvokeTime = 0,
                leading = false,
                maxing = false,
                trailing = true;

            if (typeof func != 'function') {
                throw new TypeError(FUNC_ERROR_TEXT);
            }
            wait = wait || 0;
            if (isObject(options)) {
                leading = !!options.leading;
                maxing = 'maxWait' in options;
                maxWait = maxing ? nativeMax(options.maxWait || 0, wait) : maxWait;
                trailing = 'trailing' in options ? !!options.trailing : trailing;
            }

            function invokeFunc(time) {
                var args = lastArgs,
                    thisArg = lastThis;

                lastArgs = lastThis = undefined;
                lastInvokeTime = time;
                result = func.apply(thisArg, args);
                return result;
            }

            function leadingEdge(time) {
                // Reset any `maxWait` timer.
                lastInvokeTime = time;
                // Start the timer for the trailing edge.
                timerId = setTimeout(timerExpired, wait);
                // Invoke the leading edge.
                return leading ? invokeFunc(time) : result;
            }

            function remainingWait(time) {
                var timeSinceLastCall = time - lastCallTime,
                    timeSinceLastInvoke = time - lastInvokeTime,
                    timeWaiting = wait - timeSinceLastCall;

                return maxing
                    ? nativeMin(timeWaiting, maxWait - timeSinceLastInvoke)
                    : timeWaiting;
            }

            function shouldInvoke(time) {
                var timeSinceLastCall = time - lastCallTime,
                    timeSinceLastInvoke = time - lastInvokeTime;

                // Either this is the first call, activity has stopped and we're at the
                // trailing edge, the system time has gone backwards and we're treating
                // it as the trailing edge, or we've hit the `maxWait` limit.
                return (lastCallTime === undefined || (timeSinceLastCall >= wait) ||
                        (timeSinceLastCall < 0) || (maxing && timeSinceLastInvoke >= maxWait));
            }

            function timerExpired() {
                var time = now();
                if (shouldInvoke(time)) {
                    return trailingEdge(time);
                }
                // Restart the timer.
                timerId = setTimeout(timerExpired, remainingWait(time));
            }

            function trailingEdge(time) {
                timerId = undefined;

                // Only invoke if we have `lastArgs` which means `func` has been
                // debounced at least once.
                if (trailing && lastArgs) {
                    return invokeFunc(time);
                }
                lastArgs = lastThis = undefined;
                return result;
            }

            function cancel() {
                if (timerId !== undefined) {
                    clearTimeout(timerId);
                }
                lastInvokeTime = 0;
                lastArgs = lastCallTime = lastThis = timerId = undefined;
            }

            function flush() {
                return timerId === undefined ? result : trailingEdge(now());
            }

            function debounced() {
                var time = now(),
                    isInvoking = shouldInvoke(time);

                lastArgs = arguments;
                lastThis = this;
                lastCallTime = time;

                if (isInvoking) {
                    if (timerId === undefined) {
                        return leadingEdge(lastCallTime);
                    }
                    if (maxing) {
                        // Handle invocations in a tight loop.
                        timerId = setTimeout(timerExpired, wait);
                        return invokeFunc(lastCallTime);
                    }
                }
                if (timerId === undefined) {
                    timerId = setTimeout(timerExpired, wait);
                }
                return result;
            }
            debounced.cancel = cancel;
            debounced.flush = flush;
            return debounced;
        };
    })();
    // -----------------------------------------------------------------------
    // :: jQuery Timers
    // -----------------------------------------------------------------------
    var jQuery = $;
    /* istanbul ignore next */
    (function($) {
        jQuery.fn.extend({
            everyTime: function(interval, label, fn, times, belay) {
                return this.each(function() {
                    jQuery.timer.add(this, interval, label, fn, times, belay);
                });
            },
            oneTime: function(interval, label, fn) {
                return this.each(function() {
                    jQuery.timer.add(this, interval, label, fn, 1);
                });
            },
            stopTime: function(label, fn) {
                return this.each(function() {
                    jQuery.timer.remove(this, label, fn);
                });
            }
        });

        jQuery.extend({
            timer: {
                guid: 1,
                global: {},
                regex: /^([0-9]+)\s*(.*s)?$/,
                powers: {
                    // Yeah this is major overkill...
                    'ms': 1,
                    'cs': 10,
                    'ds': 100,
                    's': 1000,
                    'das': 10000,
                    'hs': 100000,
                    'ks': 1000000
                },
                timeParse: function(value) {
                    if (value === undefined || value === null) {
                        return null;
                    }
                    var result = this.regex.exec(jQuery.trim(value.toString()));
                    if (result[2]) {
                        var num = parseInt(result[1], 10);
                        var mult = this.powers[result[2]] || 1;
                        return num * mult;
                    } else {
                        return value;
                    }
                },
                add: function(element, interval, label, fn, times, belay) {
                    var counter = 0;

                    if (jQuery.isFunction(label)) {
                        if (!times) {
                            times = fn;
                        }
                        fn = label;
                        label = interval;
                    }

                    interval = jQuery.timer.timeParse(interval);

                    if (typeof interval !== 'number' ||
                        isNaN(interval) ||
                        interval <= 0) {
                        return;
                    }
                    if (times && times.constructor !== Number) {
                        belay = !!times;
                        times = 0;
                    }

                    times = times || 0;
                    belay = belay || false;

                    if (!element.$timers) {
                        element.$timers = {};
                    }
                    if (!element.$timers[label]) {
                        element.$timers[label] = {};
                    }
                    fn.$timerID = fn.$timerID || this.guid++;

                    var handler = function() {
                        if (belay && handler.inProgress) {
                            return;
                        }
                        handler.inProgress = true;
                        if ((++counter > times && times !== 0) ||
                            fn.call(element, counter) === false) {
                            jQuery.timer.remove(element, label, fn);
                        }
                        handler.inProgress = false;
                    };

                    handler.$timerID = fn.$timerID;

                    if (!element.$timers[label][fn.$timerID]) {
                        element.$timers[label][fn.$timerID] = setInterval(handler, interval);
                    }

                    if (!this.global[label]) {
                        this.global[label] = [];
                    }
                    this.global[label].push(element);

                },
                remove: function(element, label, fn) {
                    var timers = element.$timers, ret;

                    if (timers) {

                        if (!label) {
                            for (var lab in timers) {
                                if (timers.hasOwnProperty(lab)) {
                                    this.remove(element, lab, fn);
                                }
                            }
                        } else if (timers[label]) {
                            if (fn) {
                                if (fn.$timerID) {
                                    clearInterval(timers[label][fn.$timerID]);
                                    delete timers[label][fn.$timerID];
                                }
                            } else {
                                for (var _fn in timers[label]) {
                                    if (timers[label].hasOwnProperty(_fn)) {
                                        clearInterval(timers[label][_fn]);
                                        delete timers[label][_fn];
                                    }
                                }
                            }

                            for (ret in timers[label]) {
                                if (timers[label].hasOwnProperty(ret)) {
                                    break;
                                }
                            }
                            if (!ret) {
                                ret = null;
                                delete timers[label];
                            }
                        }

                        for (ret in timers) {
                            if (timers.hasOwnProperty(ret)) {
                                break;
                            }
                        }
                        if (!ret) {
                            element.$timers = null;
                        }
                    }
                }
            }
        });
        if (/(msie) ([\w.]+)/.exec(navigator.userAgent.toLowerCase())) {
            $(window).one('unload', function() {
                var global = jQuery.timer.global;
                for (var label in global) {
                    if (global.hasOwnProperty(label)) {
                        var els = global[label], i = els.length;
                        while (--i) {
                            jQuery.timer.remove(els[i], label);
                        }
                    }
                }
            });
        }
    })(jQuery);
    // -----------------------------------------------------------------------
    // :: CROSS BROWSER SPLIT
    // -----------------------------------------------------------------------
    /* istanbul ignore next */
    (function(undef) {
        // prevent double include

        if (!String.prototype.split.toString().match(/\[native/)) {
            return;
        }

        var nativeSplit = String.prototype.split,
        compliantExecNpcg = /()??/.exec("")[1] === undef, // NPCG: nonparticipating capturing group
        self;

        self = function(str, separator, limit) {
            // If `separator` is not a regex, use `nativeSplit`
            if (Object.prototype.toString.call(separator) !== "[object RegExp]") {
                return nativeSplit.call(str, separator, limit);
            }
            var output = [],
            flags = (separator.ignoreCase ? "i" : "") +
                (separator.multiline  ? "m" : "") +
                (separator.extended   ? "x" : "") + // Proposed for ES6
                (separator.sticky     ? "y" : ""), // Firefox 3+
                lastLastIndex = 0,
            // Make `global` and avoid `lastIndex` issues by working with a copy
            separator2, match, lastIndex, lastLength;
            separator = new RegExp(separator.source, flags + "g");
            str += ""; // Type-convert
            if (!compliantExecNpcg) {
                // Doesn't need flags gy, but they don't hurt
                separator2 = new RegExp("^" + separator.source + "$(?!\\s)", flags);
            }
            /* Values for `limit`, per the spec:
             * If undefined: 4294967295 // Math.pow(2, 32) - 1
             * If 0, Infinity, or NaN: 0
             * If positive number: limit = Math.floor(limit); if (limit > 4294967295) limit -= 4294967296;
             * If negative number: 4294967296 - Math.floor(Math.abs(limit))
             * If other: Type-convert, then use the above rules
             */
            // ? Math.pow(2, 32) - 1 : ToUint32(limit)
            limit = limit === undef ? -1 >>> 0 : limit >>> 0;
            while (match = separator.exec(str)) {
                    // `separator.lastIndex` is not reliable cross-browser
                    lastIndex = match.index + match[0].length;
                    if (lastIndex > lastLastIndex) {
                        output.push(str.slice(lastLastIndex, match.index));
                        // Fix browsers whose `exec` methods don't consistently return `undefined` for
                        // nonparticipating capturing groups
                        if (!compliantExecNpcg && match.length > 1) {
                            match[0].replace(separator2, function() {
                                for (var i = 1; i < arguments.length - 2; i++) {
                                    if (arguments[i] === undef) {
                                        match[i] = undef;
                                    }
                                }
                            });
                        }
                        if (match.length > 1 && match.index < str.length) {
                            Array.prototype.push.apply(output, match.slice(1));
                        }
                        lastLength = match[0].length;
                        lastLastIndex = lastIndex;
                        if (output.length >= limit) {
                            break;
                        }
                    }
                    if (separator.lastIndex === match.index) {
                        separator.lastIndex++; // Avoid an infinite loop
                    }
                }
            if (lastLastIndex === str.length) {
                if (lastLength || !separator.test("")) {
                    output.push("");
                }
            } else {
                output.push(str.slice(lastLastIndex));
            }
            return output.length > limit ? output.slice(0, limit) : output;
        };

        // For convenience
        String.prototype.split = function(separator, limit) {
            return self(this, separator, limit);
        };

        return self;

    })();
    // -----------------------------------------------------------------------
    // :: jQuery Caret
    // -----------------------------------------------------------------------
    /* istanbul ignore next */
    $.fn.caret = function(pos) {
        var target = this[0];
        var isContentEditable = target.contentEditable === 'true';
        //get
        if (arguments.length === 0) {
            //HTML5
            if (window.getSelection) {
                //contenteditable
                if (isContentEditable) {
                    if (!this.is(':focus')) {
                        target.focus();
                    }
                    var range1 = window.getSelection().getRangeAt(0),
                    range2 = range1.cloneRange();
                    range2.selectNodeContents(target);
                    range2.setEnd(range1.endContainer, range1.endOffset);
                    return range2.toString().length;
                }
                //textarea
                return target.selectionStart;
            }
            //IE<9
            if (document.selection) {
                target.focus();
                //contenteditable
                if (isContentEditable) {
                    var range1 = document.selection.createRange(),
                    range2 = document.body.createTextRange();
                    range2.moveToElementText(target);
                    range2.setEndPoint('EndToEnd', range1);
                    return range2.text.length;
                }
                //textarea
                var pos = 0,
                range = target.createTextRange(),
                range2 = document.selection.createRange().duplicate(),
                bookmark = range2.getBookmark();
                range.moveToBookmark(bookmark);
                while (range.moveStart('character', -1) !== 0) pos++;
                return pos;
            }
            //not supported
            return 0;
        }
        //set
        if (pos === -1)
            pos = this[isContentEditable? 'text' : 'val']().length;
        //HTML5
        if (window.getSelection) {
            //contenteditable
            if (isContentEditable) {
                if (!this.is(':focus')) {
                    target.focus();
                }
                var selection = window.getSelection();
                selection.collapse(selection.focusNode, pos);
            }
            //textarea
            else
                target.setSelectionRange(pos, pos);
        }
        //IE<9
        else if (document.body.createTextRange) {
            var range = document.body.createTextRange();
            range.moveToElementText(target);
            range.moveStart('character', pos);
            range.collapse(true);
            range.select();
        }
        if (!isContentEditable && !this.is(':focus')) {
            target.focus();
        }
        return pos;
    };
    /* eslint-enable */
    // -----------------------------------------------------------------------
    // :: callback based event handler plugin generator
    // -----------------------------------------------------------------------
    function make_callback_plugin(options) {
        var factory_settings = $.extend({
            init: $.noop,
            destroy: $.noop,
            name: 'event'
        }, options);
        return function(callback, options) {
            var trigger = arguments.length === 0;
            var unbind = arguments[0] === "unbind";
            if (!trigger && !unbind && !is_function(callback)) {
                throw new Error('Invalid argument, it need to a function or string ' +
                                '"unbind" or no arguments.');
            }
            if (unbind) {
                callback = is_function(arguments[1]) ? arguments[1] : null;
            }
            var data_name = 'callbacks_' + factory_settings.name;
            return this.each(function() {
                var $this = $(this);
                var callbacks;
                function handler(arg) {
                    callbacks.fireWith($this, [arg]);
                }
                if (trigger || unbind) {
                    callbacks = $this.data(data_name);
                    if (trigger) {
                        callbacks && callbacks.fire();
                    } else {
                        if (callback && callbacks) {
                            callbacks.remove(callback);
                            if (!callbacks.has()) {
                                callbacks = null;
                            }
                        } else {
                            callbacks = null;
                        }
                        if (!callbacks) {
                            $this.removeData(data_name);
                            factory_settings.destroy.call(this, handler, options);
                        }
                    }
                } else if ($this.data(data_name)) {
                    $(this).data(data_name).add(callback);
                } else {
                    callbacks = $.Callbacks();
                    callbacks.add(callback);
                    $this.data(data_name, callbacks);
                    factory_settings.init.call(this, handler, options);
                }
            });
        };
    }
    // -----------------------------------------------------------------------
    // :: Cross-browser resize element plugin using sentinel iframe or
    // :: resizeObserver
    // -----------------------------------------------------------------------
    $.fn.resizer = make_callback_plugin({
        name: 'resize',
        init: function(handler, options) {
            var settings = $.extend({
                prefix: ''
            }, options);
            var $this = $(this);
            var resizer;
            var first = true;
            if ($this.is('body')) {
                $(window).on('resize.resizer', handler);
            } else if (window.ResizeObserver) {
                resizer = new ResizeObserver(function() {
                    if (!first) {
                        handler();
                    }
                    first = false;
                });
                resizer.observe(this);
                $this.data('observer', resizer);
            } else {
                var iframe = $('<iframe/>').addClass(settings.prefix + 'resizer')
                    .appendTo(this)[0];
                $(iframe.contentWindow).on('resize', handler);
            }
        },
        destroy: function() {
            var $this = $(this);
            if (window.ResizeObserver) {
                var observer = $this.data('observer');
                if (observer) {
                    observer.unobserve(this);
                    $this.removeData('observer');
                }
            } else {
                var iframe = $this.find('> iframe[class$="resizer"]');
                if (iframe.length) {
                    // just in case of memory leaks in IE
                    $(iframe[0].contentWindow).off('resize').remove();
                    iframe.remove();
                } else if ($this.is('body')) {
                    $(window).off('resize.resizer');
                }
            }
        }
    });
    // -----------------------------------------------------------------------
    // :: Mobile friendly scroll that work without scrollbar (for less)
    // -----------------------------------------------------------------------
    $.fn.touch_scroll = make_callback_plugin({
        name: 'touch',
        init: function(handler) {
            var origin;
            var previous;
            $(this).on('touchstart.scroll', function(e) {
                e = e.originalEvent;
                if (e.target.tagName.toLowerCase() !== 'a' && e.touches.length === 1) {
                    previous = origin = e.touches[0];
                }
            }).on('touchmove.scroll', function(e) {
                e = e.originalEvent;
                if (origin && e.touches.length === 1) {
                    var current = e.touches[0];
                    var ret = handler({
                        origin: origin,
                        previous: previous,
                        current: current
                    });
                    if (ret === false) {
                        e.preventDefault();
                    }
                    previous = current;
                }
            }).on('touchend.scroll', function() {
                if (origin || previous) {
                    origin = previous = null;
                }
            });
        },
        destroy: function() {
            $(this).off('touchstart.scroll touchmove.scroll touchend.scroll');
        }
    });
    // -----------------------------------------------------------------------
    function jquery_resolve(value) {
        var defer = jQuery.Deferred();
        defer.resolve(value);
        return defer.promise();
    }
    // -----------------------------------------------------------------------
    function unpromise(value, callback, error) {
        if (value !== undefined) {
            if (is_function(value.catch)) {
                value.catch(error);
            }
            if (is_function(value.done)) {
                return value.done(callback);
            } else if (is_function(value.then)) {
                return value.then(callback);
            } else if (value instanceof Array) {
                var promises = value.filter(function(value) {
                    return value && (is_function(value.done) || is_function(value.then));
                });
                if (promises.length) {
                    var result = $.when.apply($, value).then(callback);
                    if (is_function(value.catch)) {
                        result.catch(error);
                    }
                    return result;
                }
            }
            return callback(value);
        }
    }
    // -----------------------------------------------------------------------
    // :: based on https://github.com/zeusdeux/isInViewport
    // :: work only vertically and on dom elements
    // -----------------------------------------------------------------------
    $.fn.is_fully_in_viewport = (function() {
        function is_visible(node, container) {
            var box = node.getBoundingClientRect();
            var viewport = container[0].getBoundingClientRect();
            var top = box.top - viewport.top;
            var bottom = box.bottom - viewport.top;
            var height = container.height();
            return bottom > 0 && top <= height;
        }
        if (root.IntersectionObserver) {
            return function(container) {
                var node = this[0];
                var defer = jQuery.Deferred();
                var item_observer = new root.IntersectionObserver(function(entries) {
                    defer.resolve(entries[0].isIntersecting && entries[0].ratio === 1);
                    item_observer.unobserve(node);
                }, {
                    root: container[0]
                });
                item_observer.observe(node);
                return defer.promise();
            };
        } else {
            return function(container) {
                return jquery_resolve(is_visible(this[0], container));
            };
        }
    })();
    // -------------------------------------------------------------------------
    /* eslint-disable */
    var entity_re = /(&(?:[a-z\d]+|#\d+|#x[a-f\d]+);)/i;
    // regex that match single character at begining and folowing combine character
    // https://en.wikipedia.org/wiki/Combining_character
    var combine_chr_re = /(.(?:[\u0300-\u036F]|[\u1AB0-\u1abE]|[\u1DC0-\u1DF9]|[\u1DFB-\u1DFF]|[\u20D0-\u20F0]|[\uFE20-\uFE2F])+)/;
    // source: https://mathiasbynens.be/notes/javascript-unicode
    var astral_symbols_re = /([\uD800-\uDBFF][\uDC00-\uDFFF])/;
    // source: https://github.com/mathiasbynens/emoji-regex
    var emoji_re = /(\uD83C\uDFF4\uDB40\uDC67\uDB40\uDC62(?:\uDB40\uDC77\uDB40\uDC6C\uDB40\uDC73|\uDB40\uDC73\uDB40\uDC63\uDB40\uDC74|\uDB40\uDC65\uDB40\uDC6E\uDB40\uDC67)\uDB40\uDC7F|\uD83D\uDC69\u200D\uD83D\uDC69\u200D(?:\uD83D\uDC66\u200D\uD83D\uDC66|\uD83D\uDC67\u200D(?:\uD83D[\uDC66\uDC67]))|\uD83D\uDC68(?:\uD83C\uDFFF\u200D(?:\uD83E\uDD1D\u200D\uD83D\uDC68(?:\uD83C[\uDFFB-\uDFFE])|\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFE\u200D(?:\uD83E\uDD1D\u200D\uD83D\uDC68(?:\uD83C[\uDFFB-\uDFFD\uDFFF])|\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFD\u200D(?:\uD83E\uDD1D\u200D\uD83D\uDC68(?:\uD83C[\uDFFB\uDFFC\uDFFE\uDFFF])|\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFC\u200D(?:\uD83E\uDD1D\u200D\uD83D\uDC68(?:\uD83C[\uDFFB\uDFFD-\uDFFF])|\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFB\u200D(?:\uD83E\uDD1D\u200D\uD83D\uDC68(?:\uD83C[\uDFFC-\uDFFF])|\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\u200D(?:\u2764\uFE0F\u200D(?:\uD83D\uDC8B\u200D)?\uD83D\uDC68|(?:\uD83D[\uDC68\uDC69])\u200D(?:\uD83D\uDC66\u200D\uD83D\uDC66|\uD83D\uDC67\u200D(?:\uD83D[\uDC66\uDC67]))|\uD83D\uDC66\u200D\uD83D\uDC66|\uD83D\uDC67\u200D(?:\uD83D[\uDC66\uDC67])|(?:\uD83D[\uDC68\uDC69])\u200D(?:\uD83D[\uDC66\uDC67])|[\u2695\u2696\u2708]\uFE0F|\uD83D[\uDC66\uDC67]|\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|(?:\uD83C\uDFFF\u200D[\u2695\u2696\u2708]|\uD83C\uDFFE\u200D[\u2695\u2696\u2708]|\uD83C\uDFFD\u200D[\u2695\u2696\u2708]|\uD83C\uDFFC\u200D[\u2695\u2696\u2708]|\uD83C\uDFFB\u200D[\u2695\u2696\u2708])\uFE0F|\uD83C[\uDFFB-\uDFFF])|\uD83E\uDDD1(?:(?:\uD83C[\uDFFB-\uDFFF])\u200D(?:\uD83E\uDD1D\u200D\uD83E\uDDD1(?:\uD83C[\uDFFB-\uDFFF])|\uD83C[\uDF3E\uDF73\uDF7C\uDF84\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\u200D(?:\uD83E\uDD1D\u200D\uD83E\uDDD1|\uD83C[\uDF3E\uDF73\uDF7C\uDF84\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD]))|\uD83D\uDC69(?:\u200D(?:\u2764\uFE0F\u200D(?:\uD83D\uDC8B\u200D(?:\uD83D[\uDC68\uDC69])|\uD83D[\uDC68\uDC69])|\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFF\u200D(?:\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFE\u200D(?:\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFD\u200D(?:\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFC\u200D(?:\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD])|\uD83C\uDFFB\u200D(?:\uD83C[\uDF3E\uDF73\uDF7C\uDF93\uDFA4\uDFA8\uDFEB\uDFED]|\uD83D[\uDCBB\uDCBC\uDD27\uDD2C\uDE80\uDE92]|\uD83E[\uDDAF-\uDDB3\uDDBC\uDDBD]))|\uD83D\uDC69\uD83C\uDFFF\u200D\uD83E\uDD1D\u200D(?:\uD83D[\uDC68\uDC69])(?:\uD83C[\uDFFB-\uDFFE])|\uD83D\uDC69\uD83C\uDFFE\u200D\uD83E\uDD1D\u200D(?:\uD83D[\uDC68\uDC69])(?:\uD83C[\uDFFB-\uDFFD\uDFFF])|\uD83D\uDC69\uD83C\uDFFD\u200D\uD83E\uDD1D\u200D(?:\uD83D[\uDC68\uDC69])(?:\uD83C[\uDFFB\uDFFC\uDFFE\uDFFF])|\uD83D\uDC69\uD83C\uDFFC\u200D\uD83E\uDD1D\u200D(?:\uD83D[\uDC68\uDC69])(?:\uD83C[\uDFFB\uDFFD-\uDFFF])|\uD83D\uDC69\uD83C\uDFFB\u200D\uD83E\uDD1D\u200D(?:\uD83D[\uDC68\uDC69])(?:\uD83C[\uDFFC-\uDFFF])|\uD83D\uDC69\u200D\uD83D\uDC66\u200D\uD83D\uDC66|\uD83D\uDC69\u200D\uD83D\uDC69\u200D(?:\uD83D[\uDC66\uDC67])|(?:\uD83D\uDC41\uFE0F\u200D\uD83D\uDDE8|\uD83D\uDC69(?:\uD83C\uDFFF\u200D[\u2695\u2696\u2708]|\uD83C\uDFFE\u200D[\u2695\u2696\u2708]|\uD83C\uDFFD\u200D[\u2695\u2696\u2708]|\uD83C\uDFFC\u200D[\u2695\u2696\u2708]|\uD83C\uDFFB\u200D[\u2695\u2696\u2708]|\u200D[\u2695\u2696\u2708])|\uD83C\uDFF3\uFE0F\u200D\u26A7|\uD83E\uDDD1(?:(?:\uD83C[\uDFFB-\uDFFF])\u200D[\u2695\u2696\u2708]|\u200D[\u2695\u2696\u2708])|\uD83D\uDC3B\u200D\u2744|(?:\uD83C[\uDFC3\uDFC4\uDFCA]|\uD83D[\uDC6E\uDC70\uDC71\uDC73\uDC77\uDC81\uDC82\uDC86\uDC87\uDE45-\uDE47\uDE4B\uDE4D\uDE4E\uDEA3\uDEB4-\uDEB6]|\uD83E[\uDD26\uDD35\uDD37-\uDD39\uDD3D\uDD3E\uDDB8\uDDB9\uDDCD-\uDDCF\uDDD6-\uDDDD])(?:\uD83C[\uDFFB-\uDFFF])\u200D[\u2640\u2642]|(?:\u26F9|\uD83C[\uDFCB\uDFCC]|\uD83D\uDD75)(?:\uFE0F\u200D[\u2640\u2642]|(?:\uD83C[\uDFFB-\uDFFF])\u200D[\u2640\u2642])|\uD83C\uDFF4\u200D\u2620|(?:\uD83C[\uDFC3\uDFC4\uDFCA]|\uD83D[\uDC6E-\uDC71\uDC73\uDC77\uDC81\uDC82\uDC86\uDC87\uDE45-\uDE47\uDE4B\uDE4D\uDE4E\uDEA3\uDEB4-\uDEB6]|\uD83E[\uDD26\uDD35\uDD37-\uDD39\uDD3C-\uDD3E\uDDB8\uDDB9\uDDCD-\uDDCF\uDDD6-\uDDDF])\u200D[\u2640\u2642])\uFE0F|\uD83D\uDC69\u200D\uD83D\uDC67\u200D(?:\uD83D[\uDC66\uDC67])|\uD83C\uDFF3\uFE0F\u200D\uD83C\uDF08|\uD83D\uDC69\u200D\uD83D\uDC67|\uD83D\uDC69\u200D\uD83D\uDC66|\uD83D\uDC15\u200D\uD83E\uDDBA|\uD83C\uDDFD\uD83C\uDDF0|\uD83C\uDDF6\uD83C\uDDE6|\uD83C\uDDF4\uD83C\uDDF2|\uD83D\uDC08\u200D\u2B1B|\uD83E\uDDD1(?:\uD83C[\uDFFB-\uDFFF])|\uD83D\uDC69(?:\uD83C[\uDFFB-\uDFFF])|\uD83C\uDDFF(?:\uD83C[\uDDE6\uDDF2\uDDFC])|\uD83C\uDDFE(?:\uD83C[\uDDEA\uDDF9])|\uD83C\uDDFC(?:\uD83C[\uDDEB\uDDF8])|\uD83C\uDDFB(?:\uD83C[\uDDE6\uDDE8\uDDEA\uDDEC\uDDEE\uDDF3\uDDFA])|\uD83C\uDDFA(?:\uD83C[\uDDE6\uDDEC\uDDF2\uDDF3\uDDF8\uDDFE\uDDFF])|\uD83C\uDDF9(?:\uD83C[\uDDE6\uDDE8\uDDE9\uDDEB-\uDDED\uDDEF-\uDDF4\uDDF7\uDDF9\uDDFB\uDDFC\uDDFF])|\uD83C\uDDF8(?:\uD83C[\uDDE6-\uDDEA\uDDEC-\uDDF4\uDDF7-\uDDF9\uDDFB\uDDFD-\uDDFF])|\uD83C\uDDF7(?:\uD83C[\uDDEA\uDDF4\uDDF8\uDDFA\uDDFC])|\uD83C\uDDF5(?:\uD83C[\uDDE6\uDDEA-\uDDED\uDDF0-\uDDF3\uDDF7-\uDDF9\uDDFC\uDDFE])|\uD83C\uDDF3(?:\uD83C[\uDDE6\uDDE8\uDDEA-\uDDEC\uDDEE\uDDF1\uDDF4\uDDF5\uDDF7\uDDFA\uDDFF])|\uD83C\uDDF2(?:\uD83C[\uDDE6\uDDE8-\uDDED\uDDF0-\uDDFF])|\uD83C\uDDF1(?:\uD83C[\uDDE6-\uDDE8\uDDEE\uDDF0\uDDF7-\uDDFB\uDDFE])|\uD83C\uDDF0(?:\uD83C[\uDDEA\uDDEC-\uDDEE\uDDF2\uDDF3\uDDF5\uDDF7\uDDFC\uDDFE\uDDFF])|\uD83C\uDDEF(?:\uD83C[\uDDEA\uDDF2\uDDF4\uDDF5])|\uD83C\uDDEE(?:\uD83C[\uDDE8-\uDDEA\uDDF1-\uDDF4\uDDF6-\uDDF9])|\uD83C\uDDED(?:\uD83C[\uDDF0\uDDF2\uDDF3\uDDF7\uDDF9\uDDFA])|\uD83C\uDDEC(?:\uD83C[\uDDE6\uDDE7\uDDE9-\uDDEE\uDDF1-\uDDF3\uDDF5-\uDDFA\uDDFC\uDDFE])|\uD83C\uDDEB(?:\uD83C[\uDDEE-\uDDF0\uDDF2\uDDF4\uDDF7])|\uD83C\uDDEA(?:\uD83C[\uDDE6\uDDE8\uDDEA\uDDEC\uDDED\uDDF7-\uDDFA])|\uD83C\uDDE9(?:\uD83C[\uDDEA\uDDEC\uDDEF\uDDF0\uDDF2\uDDF4\uDDFF])|\uD83C\uDDE8(?:\uD83C[\uDDE6\uDDE8\uDDE9\uDDEB-\uDDEE\uDDF0-\uDDF5\uDDF7\uDDFA-\uDDFF])|\uD83C\uDDE7(?:\uD83C[\uDDE6\uDDE7\uDDE9-\uDDEF\uDDF1-\uDDF4\uDDF6-\uDDF9\uDDFB\uDDFC\uDDFE\uDDFF])|\uD83C\uDDE6(?:\uD83C[\uDDE8-\uDDEC\uDDEE\uDDF1\uDDF2\uDDF4\uDDF6-\uDDFA\uDDFC\uDDFD\uDDFF])|[#\*0-9]\uFE0F\u20E3|(?:\uD83C[\uDFC3\uDFC4\uDFCA]|\uD83D[\uDC6E\uDC70\uDC71\uDC73\uDC77\uDC81\uDC82\uDC86\uDC87\uDE45-\uDE47\uDE4B\uDE4D\uDE4E\uDEA3\uDEB4-\uDEB6]|\uD83E[\uDD26\uDD35\uDD37-\uDD39\uDD3D\uDD3E\uDDB8\uDDB9\uDDCD-\uDDCF\uDDD6-\uDDDD])(?:\uD83C[\uDFFB-\uDFFF])|(?:\u26F9|\uD83C[\uDFCB\uDFCC]|\uD83D\uDD75)(?:\uD83C[\uDFFB-\uDFFF])|(?:[\u261D\u270A-\u270D]|\uD83C[\uDF85\uDFC2\uDFC7]|\uD83D[\uDC42\uDC43\uDC46-\uDC50\uDC66\uDC67\uDC6B-\uDC6D\uDC72\uDC74-\uDC76\uDC78\uDC7C\uDC83\uDC85\uDCAA\uDD74\uDD7A\uDD90\uDD95\uDD96\uDE4C\uDE4F\uDEC0\uDECC]|\uD83E[\uDD0C\uDD0F\uDD18-\uDD1C\uDD1E\uDD1F\uDD30-\uDD34\uDD36\uDD77\uDDB5\uDDB6\uDDBB\uDDD2-\uDDD5])(?:\uD83C[\uDFFB-\uDFFF])|(?:[\u231A\u231B\u23E9-\u23EC\u23F0\u23F3\u25FD\u25FE\u2614\u2615\u2648-\u2653\u267F\u2693\u26A1\u26AA\u26AB\u26BD\u26BE\u26C4\u26C5\u26CE\u26D4\u26EA\u26F2\u26F3\u26F5\u26FA\u26FD\u2705\u270A\u270B\u2728\u274C\u274E\u2753-\u2755\u2757\u2795-\u2797\u27B0\u27BF\u2B1B\u2B1C\u2B50\u2B55]|\uD83C[\uDC04\uDCCF\uDD8E\uDD91-\uDD9A\uDDE6-\uDDFF\uDE01\uDE1A\uDE2F\uDE32-\uDE36\uDE38-\uDE3A\uDE50\uDE51\uDF00-\uDF20\uDF2D-\uDF35\uDF37-\uDF7C\uDF7E-\uDF93\uDFA0-\uDFCA\uDFCF-\uDFD3\uDFE0-\uDFF0\uDFF4\uDFF8-\uDFFF]|\uD83D[\uDC00-\uDC3E\uDC40\uDC42-\uDCFC\uDCFF-\uDD3D\uDD4B-\uDD4E\uDD50-\uDD67\uDD7A\uDD95\uDD96\uDDA4\uDDFB-\uDE4F\uDE80-\uDEC5\uDECC\uDED0-\uDED2\uDED5-\uDED7\uDEEB\uDEEC\uDEF4-\uDEFC\uDFE0-\uDFEB]|\uD83E[\uDD0C-\uDD3A\uDD3C-\uDD45\uDD47-\uDD78\uDD7A-\uDDCB\uDDCD-\uDDFF\uDE70-\uDE74\uDE78-\uDE7A\uDE80-\uDE86\uDE90-\uDEA8\uDEB0-\uDEB6\uDEC0-\uDEC2\uDED0-\uDED6])|(?:[#\*0-9\xA9\xAE\u203C\u2049\u2122\u2139\u2194-\u2199\u21A9\u21AA\u231A\u231B\u2328\u23CF\u23E9-\u23F3\u23F8-\u23FA\u24C2\u25AA\u25AB\u25B6\u25C0\u25FB-\u25FE\u2600-\u2604\u260E\u2611\u2614\u2615\u2618\u261D\u2620\u2622\u2623\u2626\u262A\u262E\u262F\u2638-\u263A\u2640\u2642\u2648-\u2653\u265F\u2660\u2663\u2665\u2666\u2668\u267B\u267E\u267F\u2692-\u2697\u2699\u269B\u269C\u26A0\u26A1\u26A7\u26AA\u26AB\u26B0\u26B1\u26BD\u26BE\u26C4\u26C5\u26C8\u26CE\u26CF\u26D1\u26D3\u26D4\u26E9\u26EA\u26F0-\u26F5\u26F7-\u26FA\u26FD\u2702\u2705\u2708-\u270D\u270F\u2712\u2714\u2716\u271D\u2721\u2728\u2733\u2734\u2744\u2747\u274C\u274E\u2753-\u2755\u2757\u2763\u2764\u2795-\u2797\u27A1\u27B0\u27BF\u2934\u2935\u2B05-\u2B07\u2B1B\u2B1C\u2B50\u2B55\u3030\u303D\u3297\u3299]|\uD83C[\uDC04\uDCCF\uDD70\uDD71\uDD7E\uDD7F\uDD8E\uDD91-\uDD9A\uDDE6-\uDDFF\uDE01\uDE02\uDE1A\uDE2F\uDE32-\uDE3A\uDE50\uDE51\uDF00-\uDF21\uDF24-\uDF93\uDF96\uDF97\uDF99-\uDF9B\uDF9E-\uDFF0\uDFF3-\uDFF5\uDFF7-\uDFFF]|\uD83D[\uDC00-\uDCFD\uDCFF-\uDD3D\uDD49-\uDD4E\uDD50-\uDD67\uDD6F\uDD70\uDD73-\uDD7A\uDD87\uDD8A-\uDD8D\uDD90\uDD95\uDD96\uDDA4\uDDA5\uDDA8\uDDB1\uDDB2\uDDBC\uDDC2-\uDDC4\uDDD1-\uDDD3\uDDDC-\uDDDE\uDDE1\uDDE3\uDDE8\uDDEF\uDDF3\uDDFA-\uDE4F\uDE80-\uDEC5\uDECB-\uDED2\uDED5-\uDED7\uDEE0-\uDEE5\uDEE9\uDEEB\uDEEC\uDEF0\uDEF3-\uDEFC\uDFE0-\uDFEB]|\uD83E[\uDD0C-\uDD3A\uDD3C-\uDD45\uDD47-\uDD78\uDD7A-\uDDCB\uDDCD-\uDDFF\uDE70-\uDE74\uDE78-\uDE7A\uDE80-\uDE86\uDE90-\uDEA8\uDEB0-\uDEB6\uDEC0-\uDEC2\uDED0-\uDED6])\uFE0F?|(?:[\u261D\u26F9\u270A-\u270D]|\uD83C[\uDF85\uDFC2-\uDFC4\uDFC7\uDFCA-\uDFCC]|\uD83D[\uDC42\uDC43\uDC46-\uDC50\uDC66-\uDC78\uDC7C\uDC81-\uDC83\uDC85-\uDC87\uDC8F\uDC91\uDCAA\uDD74\uDD75\uDD7A\uDD90\uDD95\uDD96\uDE45-\uDE47\uDE4B-\uDE4F\uDEA3\uDEB4-\uDEB6\uDEC0\uDECC]|\uD83E[\uDD0C\uDD0F\uDD18-\uDD1F\uDD26\uDD30-\uDD39\uDD3C-\uDD3E\uDD77\uDDB5\uDDB6\uDDB8\uDDB9\uDDBB\uDDCD-\uDDCF\uDDD1-\uDDDD]))/;
    // https://stackoverflow.com/questions/11381673/detecting-a-mobile-browser
    var mobile_re = /(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino|android|ipad|playbook|silk/i;
    var tablet_re = /1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i;
    var format_split_re = /(\[\[(?:-?[@!gbiuso])*;[^;]*;[^\]]*\](?:[^\]\\]*(?:\\\\)*\\\][^\]]*|[^\]]*|[^[]*\[[^\]]*)\]?)/i;
    var format_parts_re = /\[\[((?:-?[@!gbiuso])*);([^;]*);([^;\]]*);?([^;\]]*);?([^\]]*)\]([^\]\\]*\\\][^\]]*|[^\]]*|[^[]*\[[^\]]+)\]?/gi;
    var format_re = /\[\[((?:-?[@!gbiuso])*;[^;\]]*;[^;\]]*(?:;|[^\]()]*);?[^\]]*)\]([^\]]*\\\][^\]]*|[^\]]*|[^[]*\[[^\]]*)\]?/gi;
    var format_exist_re = /\[\[((?:-?[@!gbiuso])*;[^;\]]*;[^;\]]*(?:;|[^\]()]*);?[^\]]*)\]([^\]]*\\\][^\]]*|[^\]]*|[^[]*\[[^\]]*)\]/gi;
    var format_full_re = /^(\[\[(?:(?:-?[@!gbiuso])*;[^;\]]*;[^;\]]*(?:;|[^\]()]*);?[^\]]*)\])([^\]]*\\\][^\]]*|[^\]]*|[^[]*\[[^\]]*)(\])$/i;
    var format_begin_re = /(\[\[(?:-?[@!gbiuso])*;[^;]*;[^\]]*\])/i;
    var format_start_re = /^(\[\[(?:-?[@!gbiuso])*;[^;]*;[^\]]*\])/i;
    var format_end_re = /\[\[(?:-?[@!gbiuso])*;[^;]*;[^\]]*\]?$/i;
    var self_closing_re = /^(?:\[\[)?[^;]*@[^;]*;/;
    var color_re = /^(?:#([0-9a-f]{3}|[0-9a-f]{4}|[0-9a-f]{6}|[0-9a-f]{8})|rgba?\([^)]+\)|hsla?\([^)]+\))$/i;
    var url_re = /(\bhttps?:\/\/(?:(?:(?!&[^;]+;)|(?=&amp;))[^\s"'<>\][)])+)/gi;
    var url_nf_re = /\b(?![^"\s[\]]*])(https?:\/\/(?:(?:(?!&[^;]+;)|(?=&amp;))[^\s"'<>\][)])+)/gi;
    var email_re = /((([^<>('")[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,})))/g;
    var url_full_re = /^(https?:\/\/(?:(?:(?!&[^;]+;)|(?=&amp;))[^\s"'<>\][)])+)$/gi;
    var email_full_re = /^((([^<>('")[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,})))$/g;
    var command_re = /((?:"[^"\\]*(?:\\[\S\s][^"\\]*)*"|'[^'\\]*(?:\\[\S\s][^'\\]*)*'|`[^`\\]*(?:\\[\S\s][^`\\]*)*`|\/[^\/\\]*(?:\\[\S\s][^\/\\]*)*\/[gimsuy]*(?=\s|$)|(?:\\\s|\S))+)(?=\s|$)/gi;
    var extended_command_re = /^\s*((terminal|cmd)::([a-z_]+)\(([\s\S]*)\))\s*$/;
    var format_exec_re = /(\[\[(?:[^\][]|\\\])+\]\])/;
    var float_re = /^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$/;
    var re_re = /^\/((?:\\\/|[^/]|\[[^\]]*\/[^\]]*\])+)\/([gimsuy]*)$/;
    var string_re = /("(?:[^"\\]|\\(?:\\\\)*"|\\\\)*"|'(?:[^'\\]|\\(?:\\\\)*'|\\\\)*'|`(?:[^`\\]|\\(?:\\\\)*`|\\\\)*`)/;
    var unclosed_strings_re = /^(?=((?:[^"']+|"[^"\\]*(?:\\[^][^"\\]*)*"|'[^'\\]*(?:\\[^][^'\\]*)*')*))\1./;
    var broken_image = '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 14"><title id="title2">rounded</title><path id="terminal-broken-image" d="m 14,10 h 2 v 1 a 3,3 0 0 1 -3,3 H 3 A 3,3 0 0 1 0,11 H 4.5 A 1.00012,1.00012 0 0 0 5.207,10.707 L 6.5,9.414 7.793,10.707 a 0.99963,0.99963 0 0 0 1.41406,0 l 2.36719,-2.36719 1.80127,1.44092 A 0.99807,0.99807 0 0 0 14,10 Z M 16,3 V 8 H 14.35059 L 12.12451,6.21924 A 0.99846,0.99846 0 0 0 10.793,6.293 L 8.5,8.586 7.207,7.293 a 0.99962,0.99962 0 0 0 -1.41406,0 L 4.08594,9 H 0 V 3 A 3,3 0 0 1 3,0 h 10 a 3,3 0 0 1 3,3 z M 6,4.5 A 1.5,1.5 0 1 0 4.5,6 1.5,1.5 0 0 0 6,4.5 Z" /></svg>';
    var use_broken_image = '<svg class="terminal-broken-image" role="presentation" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 14" xmlns:xlink="http://www.w3.org/1999/xlink"><use xlink:href="#terminal-broken-image"/></svg>';
    /* eslint-enable */
    // -------------------------------------------------------------------------
    // :: features flags
    // -------------------------------------------------------------------------
    // taken from https://hacks.mozilla.org/2011/09/detecting-and-generating-
    // css-animations-in-javascript/
    var animation_supported = (function() {
        if (typeof document === 'undefined') {
            return false;
        }
        var animation = false,
            domPrefixes = 'Webkit Moz O ms Khtml'.split(' '),
            elm = document.createElement('div');
        if (elm.style.animationName) {
            animation = true;
        }
        if (animation === false) {
            for (var i = 0; i < domPrefixes.length; i++) {
                var name = domPrefixes[i] + 'AnimationName';
                if (elm.style[name] !== undefined) {
                    animation = true;
                    break;
                }
            }
        }
        elm = null;
        return animation;
    })();
    // -------------------------------------------------------------------------
    var agent = (root.navigator || window.navigator).userAgent;
    var is_IE = /MSIE|Trident/.test(agent) || /rv:11.0/i.test(agent);
    var is_IEMobile = /IEMobile/.test(agent);
    // -------------------------------------------------------------------------
    var is_ch_unit_supported = (function() {
        if (is_IE && !is_IEMobile) {
            return false;
        }
        if (typeof document === 'undefined') {
            return true; // run without browser context
        }
        var div = document.createElement('div');
        div.style.width = '1ch';
        return div.style.width === '1ch';
    })();
    // -------------------------------------------------------------------------
    var is_css_variables_supported = root.CSS && root.CSS.supports &&
            root.CSS.supports('--fake-var', 0);
    // -------------------------------------------------------------------------
    var is_android = navigator.userAgent.toLowerCase().indexOf('android') !== -1;
    // -------------------------------------------------------------------------
    var is_key_native = (function is_key_native() {
        if (!('KeyboardEvent' in root && 'key' in root.KeyboardEvent.prototype)) {
            return false;
        }
        var proto = root.KeyboardEvent.prototype;
        var get = Object.getOwnPropertyDescriptor(proto, 'key').get;
        return !!get.toString().match(/\[native code\]/);
    })();
    // -------------------------------------------------------------------------
    var is_browser = (function() {
        try {
            return this === window;
        } catch (e) {
            return false;
        }
    })();
    // -------------------------------------------------------------------------
    var is_mobile = (function(a) {
        var check = false;
        if (mobile_re.test(a) || tablet_re.test(a.substr(0, 4))) {
            check = true;
        }
        // detect iPad 13
        // ref: https://stackoverflow.com/a/57924983/387194s
        if (navigator.platform === 'MacIntel' && navigator.maxTouchPoints > 1) {
            return true;
        }
        return check;
    })(navigator.userAgent || navigator.vendor || root.opera);
    // -------------------------------------------------------------------------
    // IE ch unit bug detection - better that UserAgent that can be changed
    // -------------------------------------------------------------------------
    var ch_unit_bug = false;
    if (is_browser) {
        $(function() {
            function width(e) {
                return e[0].getBoundingClientRect().width;
            }
            var base = '<span style="font-family: monospace;visibility:hidden;';
            var ch = $(base + 'width:1ch;overflow: hidden">&nbsp;</span>');
            ch.appendTo('body');
            var space = $(base + '">&nbsp;</span>').appendTo('body');
            // in FireFox the size of space is fraction larger #579
            ch_unit_bug = Math.abs(width(ch) - width(space)) > 0.0001;
            ch.remove();
            space.remove();
        });
    }
    // -----------------------------------------------------------------------
    // :: css helper that work with css variables
    // :: jQuery css method from 3.4 support them by default
    // -----------------------------------------------------------------------
    function css(node, obj, value) {
        if (node instanceof $.fn.init) {
            node.each(function() {
                css(this, obj, value);
            });
        } else if ($.isPlainObject(obj)) {
            Object.keys(obj).forEach(function(key) {
                node.style.setProperty(key, obj[key]);
            });
        } else if (typeof value === 'undefined') {
            return node.style.getPropertyValue(obj);
        } else {
            node.style.setProperty(obj, value);
        }
    }
    // -----------------------------------------------------------------------
    // :: hide elements from screen readers
    // -----------------------------------------------------------------------
    function a11y_hide(element) {
        element.attr({
            role: 'presentation',
            'aria-hidden': 'true'
        });
    }
    // ---------------------------------------------------------------------
    // :: alert only first exception of type
    // ---------------------------------------------------------------------
    var excepctions = [];
    function alert_exception(label, e) {
        if (arguments[0] instanceof $.terminal.Exception) {
            label = arguments[0].type;
            e = arguments[0];
        }
        var message = (label ? label + ': ' : '') + exception_message(e);
        if (excepctions.indexOf(message) === -1) {
            excepctions.push(message);
            setTimeout(function() {
                throw e;
            }, 0);
            //alert(message + (e.stack ? '\n' + e.stack : ''));
        }
    }
    // ---------------------------------------------------------------------
    // :; detect if mouse event happen on scrollbar
    // ---------------------------------------------------------------------
    function scrollbar_event(e, node) {
        var left = node.offset().left;
        return node.outerWidth() <= e.clientX - left;
    }
    // ---------------------------------------------------------------------
    // :: Return exception message as string
    // ---------------------------------------------------------------------
    function exception_message(e) {
        if (typeof e === 'string') {
            return e;
        } else if (typeof e.fileName === 'string') {
            return e.fileName + ': ' + e.message;
        } else {
            return e.message;
        }
    }
    // -----------------------------------------------------------------------
    // :: CYCLE DATA STRUCTURE
    // -----------------------------------------------------------------------
    function Cycle() {
        var data = [].slice.call(arguments);
        var pos = 0;
        $.extend(this, {
            get: function() {
                return data;
            },
            index: function() {
                return pos;
            },
            rotate: function(skip, init) {
                if (init === undefined) {
                    init = pos;
                } else if (init === pos) {
                    return;
                }
                if (!skip) {
                    var defined = data.filter(function(item) {
                        return typeof item !== 'undefined';
                    });
                    if (!defined.length) {
                        return;
                    }
                }
                if (!data.length) {
                    return;
                }
                if (data.length === 1) {
                    return data[0];
                } else {
                    if (pos === data.length - 1) {
                        pos = 0;
                    } else {
                        ++pos;
                    }
                    if (typeof data[pos] !== 'undefined') {
                        return data[pos];
                    } else {
                        return this.rotate(true, init);
                    }
                }
            },
            length: function() {
                return data.length;
            },
            remove: function(index) {
                delete data[index];
            },
            set: function(item) {
                for (var i = data.length; i--;) {
                    if (data[i] === item) {
                        pos = i;
                        return;
                    }
                }
                this.append(item);
                pos = data.length - 1;
            },
            front: function() {
                if (data.length) {
                    var index = pos;
                    var restart = false;
                    while (!data[index]) {
                        index++;
                        if (index > data.length) {
                            if (restart) {
                                break;
                            }
                            index = 0;
                            restart = true;
                        }
                    }
                    return data[index];
                }
            },
            map: function(fn) {
                return data.map(function(item, i) {
                    if (typeof item !== 'undefined') {
                        return fn(item, i);
                    }
                    return null;
                }).filter(Boolean);
            },
            forEach: function(fn) {
                return data.forEach(function(item, i) {
                    if (typeof item !== 'undefined') {
                        fn(item, i);
                    }
                });
            },
            append: function(item) {
                data.push(item);
            }
        });
    }
    /*
    function time() {
        // performance.now almost equal Date.now()- performance.timing.navigationStart
        // the difference check should be almost the same
        return performance ? performance.now() : Date.now();
    }
    */
    // -----------------------------------------------------------------------
    // :: STACK DATA STRUCTURE
    // -----------------------------------------------------------------------
    function Stack(init) {
        var data = is_array(init) ? init : init ? [init] : [];
        $.extend(this, {
            data: function() {
                return data;
            },
            map: function(fn) {
                return $.map(data, fn);
            },
            size: function() {
                return data.length;
            },
            pop: function() {
                if (data.length === 0) {
                    return null;
                } else {
                    var value = data[data.length - 1];
                    data = data.slice(0, data.length - 1);
                    return value;
                }
            },
            push: function(value) {
                data = data.concat([value]);
                return value;
            },
            top: function() {
                return data.length > 0 ? data[data.length - 1] : null;
            },
            clone: function() {
                return new Stack(data.slice(0));
            }
        });
    }
    // -------------------------------------------------------------------------
    // :: Class for Worker that do some computation when needed
    // :: if validation function return false it mean that condition changed
    // :: and cache need to be cleared. If value was not prcessed it will run
    // :: the action
    // -------------------------------------------------------------------------
    function WorkerCache(options) {
        var settings = $.extend({
            validation: $.noop,
            action: $.noop,
            onCache: $.noop
        }, options);
        this._onCache = settings.onCache.bind(this);
        this._action = settings.action.bind(this);
        this._validation = settings.validation.bind(this);
        if ('Map' in root) {
            this._cache = new Map();
        }
    }
    // -------------------------------------------------------------------------
    WorkerCache.prototype.validate = function(key) {
        var valid = this._validation(key);
        var test = valid === undefined || valid === true;
        if (!test) {
            this._cache.clear();
        }
        return test;
    };
    // -------------------------------------------------------------------------
    WorkerCache.prototype.get = function(key) {
        if (!this._cache) {
            return this._action(key);
        }
        var value;
        if (this.validate(key) && this._cache.has(key)) {
            value = this._cache.get(key);
            this._onCache({cache: value});
            return value;
        }
        value = this._action(key);
        this._cache.set(key, value);
        return value;
    };
    // -------------------------------------------------------------------------
    // :: HISTORY CLASS
    // -------------------------------------------------------------------------
    function History(name, size, memory) {
        var enabled = true;
        var storage_key = '';
        if (typeof name === 'string' && name !== '') {
            storage_key = name + '_';
        }
        storage_key += 'commands';
        var data;
        if (memory) {
            data = [];
        } else {
            data = $.Storage.get(storage_key);
            data = data ? JSON.parse(data) : [];
        }
        var pos = data.length - 1;
        $.extend(this, {
            append: function(item) {
                if (enabled) {
                    if (data[data.length - 1] !== item) {
                        data.push(item);
                        if (size && data.length > size) {
                            data = data.slice(-size);
                        }
                        pos = data.length - 1;
                        if (!memory) {
                            $.Storage.set(storage_key, JSON.stringify(data));
                        }
                    }
                }
            },
            set: function(new_data) {
                if (is_array(new_data)) {
                    data = new_data;
                    if (!memory) {
                        $.Storage.set(storage_key, JSON.stringify(data));
                    }
                }
            },
            data: function() {
                return data;
            },
            reset: function() {
                pos = data.length - 1;
            },
            last: function() {
                return data[data.length - 1];
            },
            end: function() {
                return pos === data.length - 1;
            },
            position: function() {
                return pos;
            },
            current: function() {
                return data[pos];
            },
            next: function() {
                var old = pos;
                if (pos < data.length - 1) {
                    ++pos;
                }
                if (old !== pos) {
                    return data[pos];
                }
            },
            previous: function() {
                var old = pos;
                if (pos > 0) {
                    --pos;
                }
                if (old !== pos) {
                    return data[pos];
                }
            },
            clear: function() {
                data = [];
                this.purge();
            },
            enabled: function() {
                return enabled;
            },
            enable: function() {
                enabled = true;
            },
            purge: function() {
                if (!memory) {
                    $.Storage.remove(storage_key);
                }
            },
            disable: function() {
                enabled = false;
            },
            toggle: function(value) {
                if (typeof value === 'undefined') {
                    enabled = !enabled;
                } else {
                    enabled = value;
                }
            }
        });
    }
    // -------------------------------------------------------------------------
    // :: COMMAND LINE PLUGIN
    // -------------------------------------------------------------------------
    var cmd_index = 0;
    $.cmd = {
        defaults: {
            mask: false,
            caseSensitiveSearch: true,
            historySize: 60,
            prompt: '> ',
            enabled: true,
            history: true,
            onPositionChange: $.noop,
            onCommandChange: $.noop,
            inputStyle: 'textarea',
            mobileDelete: is_mobile,
            onPaste: $.noop,
            clickTimeout: 200,
            holdTimeout: 400,
            holdRepeatTimeout: 200,
            mobileIngoreAutoSpace: [],
            repeatTimeoutKeys: [],
            tabindex: 1,
            tabs: 4
        }
    };
    $.fn.cmd = function(options) {
        var settings = $.extend({}, $.cmd.defaults, options);
        function mobile_ignore_key(key) {
            return settings.mobileIngoreAutoSpace.length &&
                settings.mobileIngoreAutoSpace.indexOf(key) !== -1 && is_android;
        }
        var self = this;
        var maybe_data = self.data('cmd');
        if (maybe_data) {
            return maybe_data;
        }
        var id = cmd_index++;
        self.addClass('cmd');
        var wrapper = $('<div class="cmd-wrapper"/>').appendTo(self);
        wrapper.append('<span class="cmd-prompt"></span>');
        wrapper.append('<div class="cmd-cursor-line">' +
                       '<span></span>' +
                       '<span class="cmd-cursor">' +
                       '<span data-text class="end"><span>&nbsp;</span></span>' +
                       '</span>' +
                       '<span></span>' +
                       '</div>');
        var cursor_line = wrapper.find('.cmd-cursor-line');
        // a11y: don't read command it's in textarea that's in focus
        a11y_hide(cursor_line);
        // on mobile the only way to hide textarea on desktop it's needed because
        // textarea show up after focus
        //self.append('<span class="mask"></mask>');
        var clip;
        if (is_mobile) {
            clip = (function() {
                var $node = $('<div class="cmd-editable" contenteditable/>').attr({
                    autocapitalize: 'off',
                    autocorrect: 'off',
                    spellcheck: 'false',
                    tabindex: settings.tabindex
                }).insertAfter(self);
                $node.on('focus', function() {
                    self.enable();
                }).on('blur', function() {
                    self.disable();
                });
                var timer;
                var clip = {
                    $node: $node,
                    val: function(value) {
                        if (typeof value === 'undefined') {
                            return $node.text();
                        } else {
                            $node.html(value);
                        }
                    },
                    reset: function() {
                        clearTimeout(timer);
                        timer = setTimeout(function() {
                            $node.css({
                                top: '',
                                bottom: ''
                            });
                        }, 400);
                    },
                    focus: function() {
                        css($node[0], {
                            top: 'calc(var(--terminal-scroll, 0) * 1px)'
                        });
                        clip.reset();
                    },
                    blur: function() {
                        $node.css({
                            top: '100%',
                            bottom: 0
                        }).blur();
                        // just in case of Webkit bug
                        window.getSelection().removeAllRanges();
                        clip.reset();
                    }
                };
                return clip;
            })();
            self.addClass('cmd-mobile');
        } else {
            clip = (function() {
                var $node = $('<textarea>').attr({
                    autocapitalize: 'off',
                    spellcheck: 'false',
                    tabindex: settings.tabindex
                }).addClass('cmd-clipboard').appendTo(self);
                return {
                    $node: $node,
                    val: function(value) {
                        // even if value is undeifned
                        // when calling val(value) it return jQuery object
                        if (typeof value === 'undefined') {
                            return $node.val();
                        } else {
                            return $node.val(value);
                        }
                    }
                };
            })();
            clip.val(' ');
        }
        if (settings.width) {
            self.width(settings.width);
        }
        var num_chars; // calculated by resize
        var char_width;
        var last_rendered_prompt;
        var prompt_last_line;
        var just_prompt_len;
        var extra_prompt_margin = 0;
        var prompt_len;
        var prompt_node = self.find('.cmd-prompt');
        var reverse_search = false;
        var rev_search_str = '';
        var reverse_search_position = null;
        var backup_prompt;
        var command = '';
        var last_command;
        // text from selection using CTRL+SHIFT+C (as in Xterm)
        var kill_text = ''; // text from command that kill part of the command
        var position = 0;
        var prompt;
        var enabled;
        var formatted_position = 0;
        var name, history;
        var cursor = self.find('.cmd-cursor');
        var animation;
        var restart_animation;
        var paste_count = 0;
        // use \uFFFF to mark newline extra character
        // so we can hide it by css when using text selection
        var line_marker = '\uFFFF';
        var line_marker_re = /\uFFFF$/;
        var empty_marker_re = /^\uFFFF$/;
        function get_char_pos(e) {
            var node = $(e.target);
            if (node.is('span,img,a')) {
                node = node.closest('[data-text]');
                return node.index() +
                    node.parent('span').prevAll().find('[data-text]').length +
                    node.closest('[role="presentation"]')
                        .prevUntil('.cmd-prompt').find('[data-text]').length;
            } else if (node.is('div[role="presentation"]')) {
                var last = !node.next().length;
                return node.find('[data-text]').length +
                    node.prevUntil('.cmd-prompt').find('[data-text]').length -
                    (last ? 0 : 1);
            }
        }
        // IE mapping
        var key_mapping = {
            'SPACEBAR': ' ',
            'UP': 'ArrowUP',
            'DOWN': 'ArrowDown',
            'LEFT': 'ArrowLeft',
            'RIGHT': 'ArrowRight',
            'DEL': 'Delete',
            'MULTIPLY': '*',
            'DIVIDE': '/',
            'SUBTRACT': '-',
            'ADD': '+'
        };
        function ie_key_fix(e) {
            var key = e.key.toUpperCase();
            if (key_mapping[key]) {
                return key_mapping[key];
            }
            return key;
        }
        function get_key(e) {
            if (e.key) {
                var key = ie_key_fix(e).toUpperCase();
                if (key === 'CONTROL') {
                    return 'CTRL';
                } else {
                    var combo = [];
                    if (e.ctrlKey) {
                        combo.push('CTRL');
                    }
                    if (e.metaKey && key !== 'META') {
                        combo.push('META');
                    }
                    if (e.shiftKey && key !== 'SHIFT') {
                        combo.push('SHIFT');
                    }
                    if (e.altKey && key !== 'ALT') {
                        combo.push('ALT');
                    }
                    if (combo.length && key === ' ') {
                        key = 'SPACEBAR';
                    }
                    if (e.key) {
                        combo.push(key);
                    }
                    return combo.join('+');
                }
            }
        }
        // -----------------------------------------------------------------
        // for invoking shortcuts using terminal::keydown
        // taken from https://github.com/cvan/keyboardevent-key-polyfill/
        var keycodes = {
            3: 'Cancel',
            6: 'Help',
            8: 'Backspace',
            9: 'Tab',
            12: 'Clear',
            13: 'Enter',
            16: 'Shift',
            17: 'Control',
            18: 'Alt',
            19: 'Pause',
            20: 'CapsLock',
            27: 'Escape',
            28: 'Convert',
            29: 'NonConvert',
            30: 'Accept',
            31: 'ModeChange',
            32: ' ',
            33: 'PageUp',
            34: 'PageDown',
            35: 'End',
            36: 'Home',
            37: 'ArrowLeft',
            38: 'ArrowUp',
            39: 'ArrowRight',
            40: 'ArrowDown',
            41: 'Select',
            42: 'Print',
            43: 'Execute',
            44: 'PrintScreen',
            45: 'Insert',
            46: 'Delete',
            48: ['0', ')'],
            49: ['1', '!'],
            50: ['2', '@'],
            51: ['3', '#'],
            52: ['4', '$'],
            53: ['5', '%'],
            54: ['6', '^'],
            55: ['7', '&'],
            56: ['8', '*'],
            57: ['9', '('],
            91: 'OS',
            93: 'ContextMenu',
            144: 'NumLock',
            145: 'ScrollLock',
            181: 'VolumeMute',
            182: 'VolumeDown',
            183: 'VolumeUp',
            186: [';', ':'],
            187: ['=', '+'],
            188: [',', '<'],
            189: ['-', '_'],
            190: ['.', '>'],
            191: ['/', '?'],
            192: ['`', '~'],
            219: ['[', '{'],
            220: ['\\', '|'],
            221: [']', '}'],
            222: ["'", '"'],
            224: 'Meta',
            225: 'AltGraph',
            246: 'Attn',
            247: 'CrSel',
            248: 'ExSel',
            249: 'EraseEof',
            250: 'Play',
            251: 'ZoomOut'
        };
        var i;
        // Function keys (F1-24).
        for (i = 1; i < 25; i++) {
            keycodes[111 + i] = 'F' + i;
        }
        // Printable ASCII characters.
        var letter = '';
        for (i = 65; i < 91; i++) {
            letter = String.fromCharCode(i);
            keycodes[i] = [letter.toLowerCase(), letter.toUpperCase()];
        }
        var reversed_keycodes = {};
        Object.keys(keycodes).forEach(function(which) {
            if (is_array(keycodes[which])) {
                keycodes[which].forEach(function(key) {
                    reversed_keycodes[key.toUpperCase()] = which;
                });
            } else {
                reversed_keycodes[keycodes[which].toUpperCase()] = which;
            }
        });
        // -----------------------------------------------------------------
        var keymap;
        var default_keymap = {
            'ALT+D': delete_forward({clipboard: true}),
            'HOLD+ALT+D': delete_forward({clipboard: true, hold: true}),
            'HOLD+DELETE': delete_forward({clipboard: false, hold: true}),
            'HOLD+SHIFT+DELETE': delete_forward({clipboard: false, hold: true}),
            'ENTER': function() {
                if (history && command && !settings.mask &&
                    ((is_function(settings.historyFilter) &&
                      settings.historyFilter(command)) ||
                     (settings.historyFilter instanceof RegExp &&
                      command.match(settings.historyFilter)) ||
                     !settings.historyFilter)) {
                    history.append(command);
                }
                var tmp = command;
                // fix scroll the page where there is no scrollbar
                clip.$node.blur();
                history.reset();

                // for next input event on firefox/android with google keyboard
                prev_command = '';
                no_keydown = true;

                self.set('');
                var promise;
                if (settings.commands) {
                    promise = settings.commands.call(self, tmp);
                }
                if (is_function(prompt)) {
                    if (promise && is_function(promise.then)) {
                        promise.then(draw_prompt);
                    } else {
                        draw_prompt();
                    }
                }
                clip.val('');
                clip.$node.focus();
                return false;
            },
            'SHIFT+ENTER': function() {
                self.insert('\n');
                return true;
            },
            'BACKSPACE': backspace_key,
            'SHIFT+BACKSPACE': backspace_key,
            'TAB': function() {
                self.insert('\t');
            },
            'CTRL+D': function() {
                self['delete'](1);
                return false;
            },
            'DELETE': function() {
                self['delete'](1);
                return true;
            },
            'HOLD+ARROWUP': up_arrow,
            'ARROWUP': up_arrow,
            'CTRL+ARROWUP': prev_history,
            'CTRL+P': prev_history,
            'ARROWDOWN': down_arrow,
            'HOLD+ARROWDOWN': down_arrow,
            'CTRL+N': next_history,
            'CTRL+ARROWDOWN': next_history,
            'ARROWLEFT': left,
            'HOLD+ARROWLEFT': debounce(left, 10),
            'CTRL+B': left,
            'CTRL+ARROWLEFT': function() {
                // jump to one character after last space before prevoius word
                var len = position - 1;
                var pos = 0;
                if (command[len] === ' ') {
                    --len;
                }
                for (var i = len; i > 0; --i) {
                    if (command[i] === ' ' && command[i + 1] !== ' ') {
                        pos = i + 1;
                        break;
                    } else if (command[i] === '\n' &&
                               command[i + 1] !== '\n') {
                        pos = i;
                        break;
                    }
                }
                self.position(pos);
            },
            'CTRL+R': function() {
                if (reverse_search) {
                    reverse_history_search(true);
                } else {
                    backup_prompt = prompt;
                    draw_reverse_prompt();
                    last_command = command;
                    self.set('');
                    redraw();
                    reverse_search = true;
                }
                return false;
            },
            'CTRL+G': function() {
                if (reverse_search) {
                    prompt = backup_prompt;
                    draw_prompt();
                    self.set(last_command);
                    redraw();
                    reverse_search = false;
                    rev_search_str = '';
                    return false;
                }
            },
            'ARROWRIGHT': right,
            'HOLD+ARROWRIGHT': debounce(right, 10),
            'CTRL+F': right,
            'CTRL+ARROWRIGHT': function() {
                // jump to beginning or end of the word
                if (command[position] === ' ') {
                    ++position;
                }
                var re = /\S[\n\s]{2,}|[\n\s]+\S?/;
                var match = command.slice(position).match(re);
                if (!match || match[0].match(/^\s+$/)) {
                    self.position(bare_text(command).length);
                } else if (match[0][0] !== ' ') {
                    position += match.index + 1;
                } else {
                    position += match.index + match[0].length - 1;
                    if (match[0][match[0].length - 1] !== ' ') {
                        --position;
                    }
                }
                redraw();
            },
            'F12': return_true, // Allow Firebug
            'END': end(true),
            'CTRL+END': end(),
            'CTRL+E': end(),
            'HOME': home(true),
            'CTRL+HOME': home(),
            'CTRL+A': home(),
            'SHIFT+INSERT': paste_event,
            'CTRL+SHIFT+T': return_true, // open closed tab
            'CTRL+W': delete_backward({clipboard: true, hold: false}),
            'HOLD+BACKSPACE': delete_backward({clipboard: false, hold: true}),
            'HOLD+SHIFT+BACKSPACE': delete_backward({clipboard: false, hold: true}),
            'CTRL+H': function() {
                if (command !== '' && position > 0) {
                    self['delete'](-1);
                }
                return false;
            },
            'CTRL+X': return_true,
            'CTRL+C': function() {
                return get_selected_html() === '';
            },
            'CTRL+T': return_true,
            'CTRL+Y': function() {
                if (kill_text !== '') {
                    self.insert(kill_text);
                }
            },
            'CTRL+V': paste_event,
            'META+V': paste_event,
            'CTRL+K': function() {
                var len = text(command).length;
                if (len > position) {
                    kill_text = self['delete'](len - position);
                    text_to_clipboard(clip.$node, kill_text);
                }
                return false;
            },
            'CTRL+U': function() {
                if (command !== '' && position !== 0) {
                    kill_text = self['delete'](-position);
                    text_to_clipboard(clip.$node, kill_text);
                }
                return false;
            },
            'CTRL+TAB': function() {
                return false;
            },
            'META+`': return_true, // CMD+` switch browser window on Mac
            'META+R': return_true, // CMD+R page reload in Chrome Mac
            'META+L': return_true // CLD+L jump into Ominbox on Chrome Mac
        };
        // -------------------------------------------------------------------------------
        function delete_forward(options) {
            options = options || {};
            if (options.hold && !settings.mobileDelete) {
                return function delete_character_forward() {
                    self['delete'](1);
                    return false;
                };
            }
            return function delete_word_forward() {
                var re = / *[^ ]+ *(?= )|[^ ]+$/;
                var substring = command.slice(position);
                var m = substring.match(re);
                if (m) {
                    kill_text = m[0];
                    if (options.clipboard) {
                        text_to_clipboard(clip.$node, kill_text);
                    }
                }
                self.set(
                    command.slice(0, position) +
                        command.slice(position).replace(re, ''),
                    true
                );
                // chrome jump to address bar
                return false;
            };
        }
        // -------------------------------------------------------------------------------
        function delete_backward(options) {
            options = options || {};
            if (options.hold && !settings.mobileDelete) {
                return function delete_character_backward() {
                    self['delete'](-1);
                };
            }
            return function delete_word_backward() {
                // don't work in Chromium (can't prevent close tab)
                if (command !== '' && position !== 0) {
                    var m = command.slice(0, position).match(/([^ ]* *$)/);
                    if (m[0].length) {
                        kill_text = self['delete'](-m[0].length);
                        if (options.clipboard) {
                            text_to_clipboard(clip.$node, kill_text);
                        }
                    }
                }
                return false;
            };
        }
        // -------------------------------------------------------------------------------
        function return_true() {
            return true;
        }
        // -------------------------------------------------------------------------------
        function paste_event() {
            clip.val('');
            paste_count = 0;
            if (self.isenabled() && !clip.$node.is(':focus')) {
                clip.$node.trigger('focus', [true]);
            }
            clip.$node.one('input', paste);
            return true;
        }
        // ---------------------------------------------------------------------
        // :: Paste content to terminal using hidden textarea
        // ---------------------------------------------------------------------
        function paste() {
            if (paste_count++ > 0) {
                return;
            }
            function set() {
                clip.val(command);
                fix_textarea();
            }
            function insert(text) {
                self.insert(text);
                set();
            }
            if (self.isenabled()) {
                //wait until Browser insert text to textarea
                self.oneTime(100, function() {
                    var value = clip.val().replace(/\r/g, '');
                    if (is_function(settings.onPaste)) {
                        var ret = settings.onPaste.call(self, {
                            target: self,
                            text: value
                        });
                        if (ret !== undefined) {
                            if (ret && is_function(ret.then || ret.done)) {
                                (ret.then || ret.done).call(ret, insert);
                            } else if (typeof ret === 'string') {
                                insert(ret);
                            } else if (ret === false) {
                                set();
                            }
                            return;
                        }
                    }
                    insert(value);
                });
            }
        }
        // -------------------------------------------------------------------------------
        function prev_history() {
            if (first_up_history) {
                last_command = command;
                self.set(history.current());
            } else {
                self.set(history.previous());
            }
            first_up_history = false;
            return false;
        }
        // -------------------------------------------------------------------------------
        function next_history() {
            if (history.end()) {
                first_up_history = true;
                self.set(last_command);
            } else {
                self.set(history.next());
            }
            return false;
        }
        // -------------------------------------------------------------------------------
        function have_newlines(string) {
            return string.match(/\n/);
        }
        // -------------------------------------------------------------------------------
        function have_wrapping(string, prompt_len) {
            var lengths = string.split('\n').map(function(line) {
                return $.terminal.length(line);
            });
            if (prompt_len) {
                lengths[0] += prompt_len;
            }
            var wrap = lengths.filter(function(len) {
                return len >= num_chars;
            });
            return !!wrap.length;
        }
        // -------------------------------------------------------------------------------
        function simple_split_command_line(formatted) {
            var prompt = last_rendered_prompt;
            var lines = $.terminal.split_equal(prompt + formatted, num_chars);
            var re = new RegExp('^' + $.terminal.escape_regex(prompt));
            lines = lines.map($.terminal.unescape_brackets);
            lines[0] = lines[0].replace(re, '');
            return lines;
        }
        // -------------------------------------------------------------------------------
        function up_arrow() {
            var formatted = formatting(command);
            formatted = $.terminal.strip(formatted);
            var before = $.terminal.substring(formatted, 0, position);
            var col = self.column();
            var cursor_line = self.find('.cmd-cursor-line');
            var line = cursor_line.prevUntil('span').length;
            // case when line is wrapped and we are below prompt
            if (line === 1 && col <= prompt_len) {
                self.position(0);
                return false;
            }
            if (line === 0) {
                return prev_history();
            }
            if (have_newlines(before) || have_wrapping(before, prompt_len)) {
                var prev = cursor_line.prev();
                var splitted = prev.is('.cmd-end-line');
                var lines = simple_split_command_line(formatted);
                prev = lines[line - 1];
                var left_over = lines[line].substring(col).length;
                var diff;
                if (left_over > 0) {
                    diff = col;
                    if (line - 1 === 0) {
                        diff -= prompt_len;
                    }
                    diff = col + prev.substring(diff).length;
                    if (splitted) {
                        ++diff;
                    }
                } else {
                    diff = col + 1;
                }
                self.position(-diff, true);
                return false;
            } else {
                return prev_history();
            }
        }
        // -------------------------------------------------------------------------------
        function down_arrow() {
            // use format and strip so we get visual strings (formatting can change text)
            var formatted = formatting(command);
            formatted = $.terminal.strip(formatted);
            var after = $.terminal.substring(formatted, position);
            if (have_newlines(after) || have_wrapping(after)) {
                var lines = simple_split_command_line(formatted);
                var col = self.column();
                var cursor_line = self.find('.cmd-cursor-line');
                var $line = cursor_line.prevUntil('span');
                var line = $line.length;
                var ending = cursor_line.is('.cmd-end-line');
                var next_broken = cursor_line.next().is('.cmd-end-line');
                var next = lines[line + 1];
                if (!next) {
                    return next_history();
                }
                var left_over = lines[line].substring(col).length;
                var diff;
                // move to next line if at the end move to end of next line
                if (left_over === 0) {
                    diff = next.length;
                    if (next_broken) {
                        diff++;
                    }
                } else {
                    diff = Math.min(col, next.length) + left_over;
                    if (line === 0) {
                        diff += prompt_len;
                    }
                    if (ending) {
                        // correction for splitted line that don't have extra space
                        diff += 1;
                    }
                }
                self.position(diff, true);
                return false;
            } else {
                return next_history();
            }
        }
        // -------------------------------------------------------------------------------
        function backspace_key() {
            if (reverse_search) {
                rev_search_str = rev_search_str.slice(0, -1);
                draw_reverse_prompt();
            } else if (command !== '' && position > 0) {
                self['delete'](-1);
            }
            // for next input after naitve backspace
            // we need timeout because we don't want it to trigger
            // for current input but next one
            self.oneTime(1, function() {
                no_keydown = true;
            });
        }
        // -------------------------------------------------------------------------------
        function left() {
            if (position > 0) {
                self.position(-1, true);
            }
        }
        // -------------------------------------------------------------------------------
        function right() {
            if (position < bare_text(command).length) {
                self.position(1, true);
            }
            return false;
        }
        // -------------------------------------------------------------------------------
        function home(line) {
            function home() {
                self.position(0);
            }
            if (line) {
                return function() {
                    if (command.match(/\n/)) {
                        var string = command.substring(0, self.position());
                        self.position(string.lastIndexOf('\n') + 1);
                    } else {
                        home();
                    }
                };
            } else {
                return home;
            }
        }
        // -------------------------------------------------------------------------------
        function end(line) {
            function end() {
                self.position(text(command).length);
            }
            if (line) {
                return function() {
                    if (command.match(/\n/)) {
                        var lines = command.split('\n');
                        var pos = self.position();
                        var sum = 0;
                        for (var i = 0; i < lines.length; ++i) {
                            sum += lines[i].length;
                            if (sum > pos) {
                                self.position(sum + i);
                                return;
                            }
                        }
                    }
                    end();
                };
            } else {
                return end;
            }
        }
        // -------------------------------------------------------------------------------
        function mobile_focus() {
            //if (is_touch) {
            var $clip = clip.$node;
            var focus = $clip.is(':focus');
            if (enabled) {
                if (!focus) {
                    //clip.trigger('focus', [true]);
                }
                self.oneTime(10, function() {
                    if (!$clip.is(':focus') && enabled) {
                        $clip.trigger('focus', [true]);
                    }
                });
            } else if (focus && !enabled) {
                $clip.trigger('blur', [true]);
            }
        }
        // -------------------------------------------------------------------------------
        // fix for .cursor span animation that should only be applied when
        // animation is equal to terminal-blink
        // -------------------------------------------------------------------------------
        function fix_cursor() {
            if (animation_supported) {
                var style = window.getComputedStyle(cursor[0]);
                var animationName = style.getPropertyValue('--animation');
                animationName = animationName.replace(/^\s*|\s*$/g, '');
                var _class = self.attr('class');
                if (_class.match(/-animation/)) {
                    _class = _class.replace(/[a-z]+-animation/g, '');
                }
                if (animationName && !animationName.match(/blink/)) {
                    var className = animationName.replace(/terminal-/, '') + '-animation';
                    if (!_class.match(className)) {
                        _class += ' ' + className;
                    }
                }
                _class = _class.replace(/\s+/g, ' ');
                if (_class !== self.attr('class').replace(/\s+/g, ' ')) {
                    self.attr('class', _class);
                }
            }
        }
        // -------------------------------------------------------------------------------
        // on mobile you can't delete character if input is empty (event
        // will not fire) so we fake text entry, we could just put dummy
        // data but we put real command and position
        // -------------------------------------------------------------------------------
        function fix_textarea(position_only) {
            if (!self.isenabled()) {
                return;
            }
            // delay worked while experimenting
            self.oneTime(10, function() {
                // we use space before command to show select all context menu
                // idea taken from CodeMirror
                if (!is_mobile && clip.val() !== command && !position_only) {
                    clip.val(' ' + command);
                }
                if (enabled) {
                    self.oneTime(10, function() {
                        try {
                            var pos = !is_mobile ? position + 1 : position;
                            // we check first to improve performance
                            if (clip.$node.caret() !== pos) {
                                clip.$node.caret(pos);
                            }
                        } catch (e) {
                            // firefox throw NS_ERROR_FAILURE ignore
                        }
                    });
                }
            });
        }
        // -------------------------------------------------------------------------------
        // terminal animation don't work on android because they animate
        // 2 properties
        // -------------------------------------------------------------------------------
        if (animation_supported && !is_android) {
            animation = function(toggle) {
                if (toggle) {
                    cursor.addClass('cmd-blink');
                } else {
                    cursor.removeClass('cmd-blink');
                }
            };
            restart_animation = function() {
                var new_cursor = cursor.clone();
                new_cursor.insertBefore(cursor);
                cursor.remove();
                cursor = new_cursor;
            };
        } else {
            var animating = false;
            animation = function(toggle) {
                if (toggle && !animating) {
                    animating = true;
                    cursor.addClass('cmd-inverted cmd-blink');
                    self.everyTime(500, 'blink', blink);
                } else if (animating && !toggle) {
                    animating = false;
                    self.stopTime('blink', blink);
                    cursor.removeClass('cmd-inverted cmd-blink');
                }
            };
            restart_animation = function() {
                animation(false);
                animation(true);
            };
        }
        // ---------------------------------------------------------------------
        // :: Blinking cursor function
        // ---------------------------------------------------------------------
        function blink() {
            cursor.toggleClass('cmd-inverted');
        }
        // ---------------------------------------------------------------------
        // :: Set prompt for reverse search
        // ---------------------------------------------------------------------
        function draw_reverse_prompt() {
            prompt = '(reverse-i-search)`' + rev_search_str + "': ";
            draw_prompt();
        }
        // ---------------------------------------------------------------------
        // :: Disable reverse search
        // ---------------------------------------------------------------------
        function clear_reverse_state() {
            prompt = backup_prompt;
            reverse_search = false;
            reverse_search_position = null;
            rev_search_str = '';
        }
        // ---------------------------------------------------------------------
        // :: Search through command line history. If next is not defined or
        // :: false it searches for the first item from the end. If true it
        // :: search for the next item
        // ---------------------------------------------------------------------
        function reverse_history_search(next) {
            var history_data = history.data();
            var regex, save_string;
            var len = history_data.length;
            if (next && reverse_search_position > 0) {
                len -= reverse_search_position;
            }
            if (rev_search_str.length > 0) {
                for (var j = rev_search_str.length; j > 0; j--) {
                    save_string = $.terminal.escape_regex(rev_search_str.slice(0, j));
                    if (settings.caseSensitiveSearch) {
                        regex = new RegExp(save_string);
                    } else {
                        regex = new RegExp(save_string, 'i');
                    }
                    for (var i = len; i--;) {
                        if (regex.test(history_data[i])) {
                            reverse_search_position = history_data.length - i;
                            self.position(history_data[i].indexOf(save_string));
                            self.set(history_data[i], true);
                            redraw();
                            if (rev_search_str.length !== j) {
                                rev_search_str = rev_search_str.slice(0, j);
                                draw_reverse_prompt();
                            }
                            return;
                        }
                    }
                }
            }
            rev_search_str = ''; // clear if not found any
        }
        // ---------------------------------------------------------------------
        // :: calculate width of hte character
        // ---------------------------------------------------------------------
        function get_char_width() {
            var $prompt = self.find('.cmd-prompt');
            var html = $prompt.html();
            $prompt.html('<span>&nbsp;</span>');
            var width = $prompt.find('span')[0].getBoundingClientRect().width;
            $prompt.html(html);
            return width;
        }
        // ---------------------------------------------------------------------
        // :: return number of characters in command line
        // ---------------------------------------------------------------------
        function get_num_chars(char_width) {
            var width = self.width();
            return Math.floor(width / char_width);
        }
        // ---------------------------------------------------------------------
        // :: Split String that fit into command line where first line need to
        // :: fit next to prompt (need to have less characters)
        // ---------------------------------------------------------------------
        function process_cmd_line(string) {
            function split(string) {
                return $.terminal.split_equal(string, num_chars);
            }
            // -----------------------------------------------------------------
            function skip_empty(array) {
                // we remove lines that are leftovers after adding space at the end
                var result = [];
                array.forEach(function(line, i) {
                    if ($.terminal.strip(line).match(empty_marker_re)) {
                        result[i] = false;
                        // lines that will get removed need line ending on previos
                        // line so code that check that marker works correctly
                        if (i > 0) {
                            result[i - 1] += line_marker;
                        }
                    } else {
                        result[i] = array[i];
                    }
                });
                return result.filter(function(line) {
                    return line !== false;
                });
            }
            // -----------------------------------------------------------------
            var line = prompt_node.find('.cmd-line');
            var prompt;
            if (line.length) {
                prompt = line.nextUntil('.cmd-line').text();
            } else {
                prompt = prompt_node.text();
            }
            prompt = $.terminal.escape_brackets(prompt);
            var re = new RegExp('^' + $.terminal.escape_regex(prompt));
            var array;
            if (string.match(/\n/)) {
                var tmp = string.split('\n');
                var first_len = num_chars - prompt_len - 1;
                for (var i = 0; i < tmp.length - 1; ++i) {
                    tmp[i] += line_marker;
                }
                // split first line
                if (strlen(tmp[0]) > first_len) {
                    array = split(prompt + tmp[0]);
                    array[0] = array[0].replace(re, '');
                    array = skip_empty(array);
                } else {
                    array = [tmp[0]];
                }
                // process rest of the lines
                for (i = 1; i < tmp.length; ++i) {
                    if (strlen(tmp[i]) > num_chars) {
                        var splitted = split(tmp[i]);
                        if (i < tmp.length - 1) {
                            splitted = skip_empty(splitted);
                        }
                        array = array.concat(splitted);
                    } else {
                        array.push(tmp[i]);
                    }
                }
            } else {
                array = split(prompt + string, num_chars);
                array[0] = array[0].replace(re, '');
            }
            // fix issue with cursor that was cut off #379
            if (array.length > 1) {
                var len = $.terminal.length(array[array.length - 1]);
                if (len === num_chars) {
                    array.push('');
                }
            }
            return array;
        }
        // ---------------------------------------------------------------------
        var cmd_line_worker = new WorkerCache({
            validation: function(key) {
                var result = false;
                if ((!this._previous_value || this._previous_value === key) &&
                    (!this._cols || this._cols === num_chars)) {
                    result = true;
                }
                this._previous_value = key;
                this._cols = num_chars;
                return result;
            },
            action: process_cmd_line
        });
        // ---------------------------------------------------------------------
        function split_command_line(string) {
            return cmd_line_worker.get(string);
        }
        // ---------------------------------------------------------------------
        // :: use custom formatting
        // ---------------------------------------------------------------------
        function formatting(string, skip_formatted_position) {
            // we don't want to format command when user type formatting in
            try {
                string = $.terminal.escape_formatting(string);
                var format_options = $.extend({}, settings, {
                    unixFormattingEscapeBrackets: true,
                    position: position,
                    command: true
                });
                var formatted = $.terminal.apply_formatters(string, format_options);
                var output = $.terminal.normalize(formatted[0]);
                var max = $.terminal.length(output);
                if (!skip_formatted_position) {
                    formatted_position = formatted[1];
                    // fix issue with nested formatting where max length
                    // is checked before nested_formatting flatten formatting
                    if (formatted_position > max) {
                        formatted_position = max;
                    }
                }
                return output;
            } catch (e) {
                alert_exception('[Formatting]', e.stack);
                return string;
            }
        }
        // ---------------------------------------------------------------------
        // :: format and encode the string
        // ---------------------------------------------------------------------
        function format(string, before) {
            //string = $.terminal.normalize(string);
            var encoded = $.terminal.encode(wrap(string), {
                tabs: settings.tabs,
                before: before
            });
            return $.terminal.format(encoded, {
                char_width: settings.char_width,
                allowedAttributes: settings.allowedAttributes || []
            });
        }
        // ---------------------------------------------------------------------
        // :: function create new string with all characters in it's own
        // :: formatting - it will only have style if the input is formatting
        // :: this function is not very usefull so it's not in $.terminal
        // ---------------------------------------------------------------------
        function wrap(string) {
            return $.terminal.partition(string).join('');
        }
        // ---------------------------------------------------------------------
        // :: shortcut helpers
        // ---------------------------------------------------------------------
        function length(str, raw) {
            return $.terminal.length(str, raw);
        }
        // ---------------------------------------------------------------------
        function is_multiline(str) {
            return strlen(text(str)) > num_chars - prompt_len - 1 ||
                str.match(/\n/);
        }
        // ---------------------------------------------------------------------
        function substring(str, start, end) {
            return $.terminal.substring(str, start, end);
        }
        // ---------------------------------------------------------------------
        // :: helper function that check if string is valid emoji formatting
        // ---------------------------------------------------------------------
        function is_emoji_formatting(str) {
            if ($.terminal.is_formatting(str)) {
                return str.replace(format_parts_re, '$4').match(/^emoji /);
            }
            return false;
        }
        // ---------------------------------------------------------------------
        // :: Function that displays the command line. Split long lines and
        // :: place cursor in the right place
        // ---------------------------------------------------------------------
        var redraw = (function() {
            var before = cursor.prev();
            var after = cursor.next();
            var cursor_line = cursor.parent();
            // -----------------------------------------------------------------
            // :: Draw line with the cursor
            // -----------------------------------------------------------------
            function draw_cursor_line(string, options) {
                var end_line = string.match(line_marker_re);
                if (end_line) {
                    string = string.replace(line_marker_re, ' ');
                }
                cursor_line.toggleClass('cmd-end-line', !!end_line);
                var cursor_end_line = false;
                var settings = $.extend({
                    prompt: '',
                    last: false
                }, options);
                var position = settings.position;
                var len = length(string);
                var prompt = settings.prompt;
                var c;
                if (position === len) {
                    before.html(format(string));
                    c = '&nbsp;';
                    empty_cursor();
                    after.html('');
                } else if (position === 0) {
                    before.html('');
                    c = substring(string, 0, 1);
                    cursor.html(format(c));
                    after.html(format(substring(string, 1), prompt + c));
                } else {
                    var before_str = $.terminal.substring(string, 0, position);
                    before.html(format(before_str, prompt));
                    c = substring(string, position, position + 1);
                    var c_before = (prompt + before_str).replace(/^.*\t/, '');
                    cursor.html(format(c, c_before));
                    if (position === len - 1) {
                        cursor_end_line = true;
                        after.html('');
                    } else {
                        if (c.match(/\t/)) {
                            c_before = '';
                        } else {
                            c_before += c;
                        }
                        after.html(format(substring(string, position + 1), c_before));
                    }
                }
                if (ch_unit_bug) {
                    if (typeof wcwidth !== 'undefined') {
                        // handle emoji and wide characters in IE or
                        // other possible browsers that don't have valid ch unit
                        var size = strlen(text(c));
                        if (size === 1 && is_emoji_formatting(c)) {
                            size = 2;
                        }
                        cursor.width(char_width * size);
                    } else {
                        cursor.width(char_width);
                    }
                }
                cursor.toggleClass('cmd-end-line', cursor_end_line);
                // fix for animation when changing --animation dynamically
                fix_cursor();
                var cursor_len = $.terminal.length(cursor.text());
                if (cursor_len > 1) {
                    var node = cursor.find('[data-text]')[0];
                    node.style.setProperty('--length', cursor_len);
                }
                // synchronize css animations (it's not that important because if user
                // will change animation she should disable animation on span, but it
                // looks nicer until she disable that inner animation)
                restart_animation();
            }
            // -----------------------------------------------------------------
            function div(string, before) {
                var end_line = string.match(line_marker_re);
                var result = '<div role="presentation" aria-hidden="true"';
                if (end_line) {
                    string = string.replace(line_marker_re, ' ');
                    result += ' class="cmd-end-line"';
                }
                result += '>' + format(string, before || '') + '</div>';
                return result;
            }
            // -----------------------------------------------------------------
            function empty_cursor() {
                // data-text is for consistency in CSS and end class is for unit tests
                cursor.html('<span data-text class="end"><span>&nbsp;<span></span>');
            }
            // -----------------------------------------------------------------
            // :: Display lines after the cursor
            // -----------------------------------------------------------------
            function lines_after(lines) {
                var last_ins = cursor_line;
                $.each(lines, function(i, line) {
                    last_ins = $(div(line)).insertAfter(last_ins);
                });
            }
            // -----------------------------------------------------------------
            // :: Display lines before the cursor
            // -----------------------------------------------------------------
            function lines_before(lines) {
                $.each(lines, function(i, line) {
                    cursor_line.before(div(line, i === 0 ? prompt_last_line : ''));
                });
            }
            // -----------------------------------------------------------------
            // :: Redraw function
            // -----------------------------------------------------------------
            return function() {
                var string;
                switch (typeof settings.mask) {
                    case 'boolean':
                        string = settings.mask ? command.replace(/./g, '*') : command;
                        break;
                    case 'string':
                        string = command.replace(/./g, settings.mask);
                        break;
                }
                var formatted = formatting(string);
                var pos;
                if (length(formatted) === text(string).length) {
                    pos = position;
                } else {
                    pos = formatted_position;
                }
                var i;
                wrapper.css({
                    display: 'none'
                });
                wrapper.find('div:not(.cmd-cursor-line)').remove();
                before.html('');
                if (is_multiline(formatted)) {
                    var tabs = formatted.match(/\t/g);
                    var original_string = formatted;
                    //quick tabulation hack
                    if (tabs) {
                        formatted = formatted.replace(/\t/g, '\x00\x00\x00\x00');
                    }
                    var array = split_command_line(formatted);
                    if (tabs) {
                        array = $.map(array, function(line) {
                            return line.replace(/\x00\x00\x00\x00/g, '\t');
                        });
                    }
                    var first_len = length(array[0]);
                    //cursor in first line
                    if (first_len === 0 && array.length === 1) {
                        // skip empty line
                    } else if (pos < first_len) {
                        draw_cursor_line(array[0], {
                            length: array.length,
                            position: pos,
                            prompt: prompt_last_line
                        });
                        lines_after(array.slice(1));
                    } else if (pos === first_len) {
                        // first char acter of second line
                        cursor_line.before(div(array[0], prompt_last_line));
                        draw_cursor_line(array[1] || '', {
                            length: array.length,
                            position: 0,
                            last: array.length <= 2
                        });
                        if (array.length > 2) {
                            lines_after(array.slice(2));
                        }
                    } else {
                        var last = array.slice(-1)[0];
                        var len = length(original_string);
                        var from_last = len - pos;
                        var last_len = length(last);
                        var new_pos = 0;
                        if (from_last === -1) {
                            from_last = 0;
                        }
                        if (from_last <= last_len) { // in last line
                            lines_before(array.slice(0, -1));
                            if (last_len === from_last) {
                                new_pos = 0;
                            } else {
                                new_pos = last_len - from_last;
                            }
                            draw_cursor_line(last, {
                                length: array.length,
                                position: new_pos,
                                last: true
                            });
                        } else {
                            // more lines, cursor in the middle
                            var line_index;
                            var current;
                            new_pos = pos;
                            for (i = 0; i < array.length; ++i) {
                                var current_len = $.terminal.length(array[i]);
                                if (new_pos > current_len) {
                                    new_pos -= current_len;
                                } else {
                                    break;
                                }
                            }
                            current = array[i];
                            line_index = i;
                            // cursor on first character in line
                            if (new_pos === length(current)) {
                                new_pos = 0;
                                current = array[++line_index];
                                if (current === undefined) {
                                    //should never happen
                                    var msg = $.terminal.defaults.strings.redrawError;
                                    throw new Error(msg);
                                }
                            }
                            draw_cursor_line(current, {
                                length: array.length,
                                position: new_pos
                            });
                            lines_before(array.slice(0, line_index));
                            lines_after(array.slice(line_index + 1));
                        }
                    }
                    self.find('.cmd-cursor-line ~ div:last-of-type')
                        .append('<span></span>');
                } else if (formatted === '') {
                    before.html('');
                    empty_cursor();
                    after.html('');
                } else {
                    draw_cursor_line(formatted, {
                        length: 1,
                        position: pos
                    });
                }
                var in_line = cursor_line.prevUntil('.cmd-prompt').length;
                if (is_css_variables_supported) {
                    self[0].style.setProperty('--cursor-line', in_line);
                } else {
                    clip.$node.css('top', in_line * 14 + 'px');
                }
                wrapper.css({
                    display: ''
                });
            };
        })();
        // ---------------------------------------------------------------------
        // :: find position that match display position for commands that
        // :: change length by formatters
        // ---------------------------------------------------------------------
        var find_position = (function() {
            function make_guess(string, position) {
                var opts = $.extend({}, settings, {
                    position: position,
                    command: true
                });
                return $.terminal.apply_formatters(string, opts)[1];
            }
            function cmp(search_pos, pos, string) {
                var guess = make_guess(string, pos);
                if (guess === search_pos) {
                    var next_guess = make_guess(string, pos + 1);
                    if (next_guess > search_pos) {
                        return 0;
                    }
                    return 1;
                } else if (guess < search_pos) {
                    return 1;
                } else {
                    return -1;
                }
            }
            return function(string, formatted_position) {
                if (formatted_position === 0) {
                    return 0;
                }
                string = bare_text(string);
                var codepoint_len = string.length;
                var str = $.terminal.escape_brackets(command);
                var pos = binary_search(0, codepoint_len, formatted_position, cmp, [str]);
                var chars = $.terminal.split_characters(string);
                if (codepoint_len > chars.length) {
                    var len = 0;
                    for (var i = 0; i < chars.length; ++i) {
                        len += chars[i].length;
                        if (len >= pos) {
                            return len;
                        }
                    }
                }
                return pos;
            };
        })();
        // ---------------------------------------------------------------------
        // :: Draw prompt that can be a function or a string
        // ---------------------------------------------------------------------
        var prev_prompt_data;
        var draw_prompt = (function() {
            function format_prompt(prompt) {
                if (!prompt) {
                    just_prompt_len = 0;
                    prompt_len = just_prompt_len + extra_prompt_margin;
                    return prompt;
                }
                var lines = $.terminal.split_equal(prompt, num_chars).map(function(line) {
                    if (!$.terminal.have_formatting(line)) {
                        return '[[;;]' + $.terminal.escape_brackets(line) + ']';
                    }
                    return $.terminal.format_split(line).map(function(str) {
                        if ($.terminal.is_formatting(str)) {
                            return str;
                        }
                        return '[[;;]' + $.terminal.escape_brackets(str) + ']';
                    }).join('');
                });
                var options = {
                    char_width: settings.char_width
                };
                prompt_last_line = lines[lines.length - 1];
                var encoded_last_line = $.terminal.encode(lines[lines.length - 1], {
                    tabs: settings.tabs
                });
                var last_line = $.terminal.format(encoded_last_line, options);
                just_prompt_len = strlen(text(encoded_last_line));
                prompt_len = just_prompt_len + extra_prompt_margin;
                return lines.slice(0, -1).map(function(line) {
                    line = $.terminal.encode(line, {
                        tabs: settings.tabs
                    });
                    return '<span class="cmd-line">' +
                           $.terminal.format(line, options) +
                           '</span>';
                }).concat([last_line]).join('\n');
            }
            function set(prompt) {
                if (prompt) {
                    prompt = $.terminal.apply_formatters(prompt, {prompt: true});
                    prompt = $.terminal.normalize(prompt);
                    prompt = crlf(prompt);
                }
                var formatted = format_prompt(prompt);
                last_rendered_prompt = prompt;
                // zero width space to make sure prompt margin takes up space,
                // so that echo with newline: false works when prompt is empty
                formatted = formatted || $.terminal.format('\u200b');
                // update prompt if changed
                if (prompt_node.html() !== formatted) {
                    prompt_node.html(formatted);
                    // fix for Chrome bug width selection
                    // https://bugs.chromium.org/p/chromium/issues/detail?id=1087787
                    var spans = prompt_node.find('> span span');
                    clip.$node.attr('data-cmd-prompt', prompt_node.text());
                    if (is_ch_unit_supported) {
                        prompt_node.hide();
                        spans.each(function() {
                            var self = $(this);
                            var len = strlen(self.text());
                            self.css('width', len + 'ch');
                        });
                        prompt_node.show();
                    }
                }
            }
            return function() {
                // the data is used as cancelable reference because we have ref
                // data object that is hold in closure and we remove `set` function
                // so previous call to function prompt will be ignored
                if (prev_prompt_data && prev_prompt_data.set) {
                    prev_prompt_data.set = $.noop;
                    // remove reference for garbage collector
                    prev_prompt_data = null;
                }
                switch (typeof prompt) {
                    case 'string':
                        set(prompt);
                        break;
                    case 'function':
                        var data = prev_prompt_data = {
                            set: set
                        };
                        var ret = prompt.call(self, function(string) {
                            data.set(string);
                        });
                        if (typeof ret === 'string') {
                            data.set(ret);
                        }
                        if (ret && ret.then) {
                            ret.then(data.set).catch(function(e) {
                                var prompt = $.terminal.escape_brackets('[ERR]> ');
                                data.set('[[;red;]' + prompt + ']');
                                alert_exception('Prompt', e);
                            });
                        }
                        break;
                }
            };
        })();
        // ---------------------------------------------------------------------
        function fire_change_command() {
            if (is_function(settings.onCommandChange)) {
                settings.onCommandChange.call(self, command);
            }
        }
        // ---------------------------------------------------------------------
        // :: Command Line Methods
        // ---------------------------------------------------------------------
        $.extend(self, {
            option: function(name, value) {
                if (typeof value === 'undefined') {
                    return settings[name];
                } else {
                    settings[name] = value;
                }
                return self;
            },
            name: function(string) {
                if (string !== undefined) {
                    name = string;
                    var enabled = history && history.enabled() || !history;
                    history = new History(
                        name,
                        settings.historySize,
                        settings.history === 'memory'
                    );
                    // disable new history if old was disabled
                    if (!enabled) {
                        history.disable();
                    }
                    return self;
                } else {
                    return name;
                }
            },
            purge: function() {
                history.clear();
                return self;
            },
            history: function() {
                return history;
            },
            'delete': function(n, stay) {
                var removed, string;
                if (n === 0) {
                    return "";
                } else if (n < 0) {
                    if (position > 0) {
                        // this may look weird but if n is negative we need
                        // to use +
                        removed = command.slice(0, position).slice(n);
                        string = bare_text(command);
                        string = string.slice(0, position + n) +
                            string.slice(position, string.length);
                        if (!stay) {
                            self.position(position + n);
                        }
                    }
                } else if (command !== '') {
                    string = text(command);
                    if (position < string.length) {
                        removed = string.slice(position).slice(0, n);
                        string = string.slice(0, position) +
                            string.slice(position + n, string.length);
                    }
                }
                if (removed) {
                    command = string;
                }
                redraw();
                fix_textarea();
                fire_change_command();
                return removed;
            },
            set: function(string, stay, silent) {
                if (string !== undefined) {
                    command = string;
                    if (!stay) {
                        self.position(bare_text(command).length);
                    }
                    redraw();
                    fix_textarea();
                    if (!silent) {
                        fire_change_command();
                    }
                }
                return self;
            },
            keymap: function(new_keymap, value) {
                function wrap(key, fn) {
                    var original = default_keymap[key];
                    if (is_function(original)) {
                        original = original.bind(self);
                    }
                    return function(e) {
                        // new keymap function will get default as 2nd argument
                        return fn.call(self, e, original);
                    };
                }
                if (new_keymap === null) {
                    keymap = default_keymap;
                    return self;
                } else if (typeof new_keymap === 'undefined') {
                    return keymap;
                } else if (typeof new_keymap === 'string') {
                    if (typeof value === 'undefined') {
                        if (keymap[new_keymap]) {
                            return keymap[new_keymap];
                        } else if (default_keymap[new_keymap]) {
                            return default_keymap[new_keymap];
                        }
                    } else {
                        keymap[new_keymap] = wrap(new_keymap, value);
                    }
                } else {
                    keymap = $.extend(
                        {},
                        keymap ? keymap : default_keymap,
                        $.omap(new_keymap || {}, wrap)
                    );
                    return self;
                }
            },
            insert: function(string, stay) {
                var bare_command = bare_text(command);
                var len = bare_text(string).length;
                if (position === bare_command.length) {
                    string = bare_command + string;
                } else if (position === 0) {
                    string = string + bare_command;
                } else {
                    string = bare_command.slice(0, position) +
                        string + bare_command.slice(position);
                }
                command = string;
                if (!stay) {
                    self.position(len, true, true);
                }
                fix_textarea();
                redraw();
                fire_change_command();
                return self;
            },
            get: function() {
                return command;
            },
            commands: function(commands) {
                if (commands) {
                    settings.commands = commands;
                    return self;
                } else {
                    return commands;
                }
            },
            destroy: function() {
                doc.unbind('keypress.cmd', keypress_event);
                doc.unbind('keydown.cmd', keydown_event);
                doc.unbind('input.cmd', input_event);
                self.stopTime('blink', blink);
                self.find('.cmd-wrapper').remove();
                self.find('.cmd-prompt, .cmd-clipboard, .cmd-editable').remove();
                self.removeClass('cmd').removeData('cmd').off('.cmd');
                return self;
            },
            column: function(include_prompt) {
                var before = command.substring(0, position);
                if (position === 0 || !command.length) {
                    return 0;
                }
                var re = /\n?([^\n]*)$/;
                var match = before.match(re);
                var col = match[1].length;
                if (!have_newlines(before) &&
                    (include_prompt || have_wrapping(before, prompt_len))) {
                    col += prompt_len;
                }
                if (col === 0) {
                    return col;
                }
                col %= num_chars;
                if (col === 0) {
                    return num_chars;
                }
                return col;
            },
            line: function() {
                var before = command.substring(0, position);
                if (position === 0 || !command.length) {
                    return 0;
                }
                return before.split(/\n/).length - 1;
            },
            // inform cursor about size of partial output line
            __set_prompt_margin: function(len) {
                extra_prompt_margin = len;
                prompt_len = just_prompt_len + extra_prompt_margin;
            },
            prompt: function(user_prompt) {
                if (user_prompt === true) {
                    return last_rendered_prompt;
                } else if (user_prompt === undefined) {
                    return prompt;
                } else {
                    var should_redraw = user_prompt !== prompt;
                    if (typeof user_prompt === 'string' ||
                        typeof user_prompt === 'function') {
                        prompt = user_prompt;
                    } else {
                        throw new Error('prompt must be a function or string');
                    }
                    if (should_redraw) {
                        draw_prompt();
                        // we could check if command is longer then numchars-new
                        // prompt
                        redraw();
                    }
                    return self;
                }
            },
            kill_text: function() {
                return kill_text;
            },
            position: function(n, relative, silent) {
                if (typeof n === 'number') {
                    var pos = position;
                    var len = bare_text(command).length;
                    if (relative) {
                        position += n;
                    } else if (n < 0) {
                        position = 0;
                    } else if (n > len) {
                        position = len;
                    } else {
                        position = n;
                    }
                    if (pos !== position) {
                        redraw();
                        if (!silent && is_function(settings.onPositionChange)) {
                            settings.onPositionChange(position, formatted_position);
                        }
                        fix_textarea(true);
                    }
                    return self;
                } else {
                    return position;
                }
            },
            refresh: function() {
                draw_prompt();
                redraw();
                fix_textarea(true);
                return self;
            },
            // if formatter change length of the strings (like emoji demo) we need to keep
            // track of two different positions one for command and one for display
            display_position: function(n, relative) {
                if (n === undefined) {
                    return formatted_position;
                } else {
                    // double escape
                    var string = formatting($.terminal.escape_formatting(command), true);
                    var len = length(string);
                    var command_len = bare_text(command).length;
                    var new_formatted_pos;
                    if (relative) {
                        new_formatted_pos = formatted_position + n;
                    } else if (n > len) {
                        new_formatted_pos = len;
                    } else {
                        new_formatted_pos = n;
                    }
                    if (len === command_len) {
                        formatted_position = new_formatted_pos;
                        return self.position(new_formatted_pos);
                    }
                    if (len === new_formatted_pos) {
                        formatted_position = new_formatted_pos;
                        return self.position(command_len);
                    }
                    var pos = find_position(command, new_formatted_pos);
                    if (pos !== -1) {
                        formatted_position = new_formatted_pos;
                        self.position(pos);
                    }
                    return self;
                }
            },
            visible: (function() {
                var visible = self.visible;
                return function() {
                    visible.apply(self, []);
                    redraw();
                    draw_prompt();
                    return self;
                };
            })(),
            show: (function() {
                var show = self.show;
                return function() {
                    show.apply(self, []);
                    redraw();
                    draw_prompt();
                    return self;
                };
            })(),
            resize: function(num) {
                char_width = get_char_width();
                var new_num_chars;
                if (typeof num === 'number') {
                    new_num_chars = num;
                } else {
                    new_num_chars = get_num_chars(char_width);
                }
                if (num_chars !== new_num_chars || arguments[0] === true) {
                    num_chars = new_num_chars;
                    redraw();
                    draw_prompt();
                }
                return self;
            },
            invoke_key: function(shortcut) {
                var keys = shortcut.toUpperCase().split('+');
                var key = keys.pop();
                var ctrl = keys.indexOf('CTRL') !== -1;
                var shift = keys.indexOf('SHIFT') !== -1;
                var alt = keys.indexOf('ALT') !== -1;
                var meta = keys.indexOf('META') !== -1;
                var e = $.Event("keydown", {
                    ctrlKey: ctrl,
                    shiftKey: shift,
                    altKey: alt,
                    metaKey: meta,
                    which: reversed_keycodes[key],
                    key: key
                });
                var doc = $(document.documentElement || window);
                doc.trigger(e);
                e = $.Event("keypress");
                e.key = key;
                e.which = e.keyCode = 0;
                doc.trigger(e);
                return self;
            },
            clip: function() {
                return clip;
            },
            enable: function(silent) {
                if (!enabled) {
                    enabled = true;
                    self.addClass('enabled');
                    try {
                        if (!clip.$node.is(':focus')) {
                            clip.$node.focus();
                        }
                        clip.$node.caret(position);
                    } catch (e) {
                        // firefox throw NS_ERROR_FAILURE - ignore
                    }
                    animation(true);
                    if (!silent && is_function(prompt)) {
                        draw_prompt();
                    }
                    fix_cursor();
                    fix_textarea();
                }
                mobile_focus();
                return self;
            },
            isenabled: function() {
                return enabled;
            },
            disable: function(focus) {
                enabled = false;
                self.removeClass('enabled');
                animation(false);
                if (!focus) {
                    mobile_focus();
                }
                return self;
            },
            mask: function(new_mask) {
                if (typeof new_mask === 'undefined') {
                    return settings.mask;
                } else {
                    settings.mask = new_mask;
                    redraw();
                    return self;
                }
            }
        });
        // ---------------------------------------------------------------------
        // :: INIT
        // ---------------------------------------------------------------------
        self.name(settings.name || settings.prompt || '');
        if (settings.prompt !== false) {
            prompt = settings.prompt;
            draw_prompt();
        }
        if (settings.enabled === true) {
            self.enable();
        }
        char_width = get_char_width();
        num_chars = get_num_chars(char_width);
        if (!settings.history) {
            history.disable();
        }
        var first_up_history = true;
        // skip_keypress - hack for Android that was inserting characters on
        // backspace
        var skip_keypress = false;
        var dead_key = false;
        var single_key = false;
        var no_keypress = false;
        var no_key = false;
        var no_keydown = true;
        var backspace = false;
        var process = false;
        var hold = false;
        var hold_pause = false;
        var skip_insert;
        // we hold text before keydown to fix backspace for Android/Chrome/SwiftKey
        // keyboard that generate keycode 229 for all keys #296
        var prev_command = '';
        var prev_key;
        // ---------------------------------------------------------------------
        // :: Keydown Event Handler
        // ---------------------------------------------------------------------
        function is_backspace(e) {
            return e.key.toUpperCase() === 'BACKSPACE' || e.which === 8;
        }
        // ---------------------------------------------------------------------
        function is_single(e) {
            return e.key && e.key.length === 1 && !e.ctrlKey;
        }
        // ---------------------------------------------------------------------
        function is_delay_key(key) {
            var specials = ['HOLD+SHIFT+BACKSPACE', 'HOLD+BACKSPACE'];
            return specials.indexOf(key) !== -1 && settings.mobileDelete ||
                settings.repeatTimeoutKeys.indexOf(key) !== -1;
        }
        // ---------------------------------------------------------------------
        function clear_reverse_search_key(e) {
            // arrows / Home / End / ENTER
            return e.which === 35 || e.which === 36 ||
                e.which === 37 || e.which === 38 ||
                e.which === 39 || e.which === 40 ||
                e.which === 13 || e.which === 27;
        }
        var skip_keydown = false;
        // ---------------------------------------------------------------------
        // function complexicity is 35 when adding this exception
        // eslint-disable-next-line complexity
        function keydown_event(e) {
            debug('keydown "' + e.key + '" ' + e.fake + ' ' + e.which);
            var result;
            process = (e.key || '').toLowerCase() === 'process' || e.which === 0;
            dead_key = no_keypress && single_key && !is_backspace(e);
            // special keys don't trigger keypress fix #293
            try {
                if (!e.fake) {
                    single_key = is_single(e);
                    // chrome on android support key property but it's "Unidentified"
                    no_key = String(e.key).toLowerCase() === 'unidentified';
                    backspace = is_backspace(e);
                }
            } catch (exception) {}
            // keydown created in input will have text already inserted and we
            // want text before input
            if (e.key === "Unidentified") {
                no_keydown = true;
                // android swift keyboard have always which == 229 we will triger proper
                // event in input with e.fake == true
                return;
            }
            // meta and os are special keydown triggered by Emoji picker on Windows 10
            // meta is in Google Chrome is is in Firefox
            if (!e.fake && ['meta', 'os'].indexOf(e.key.toLowerCase()) === -1) {
                no_keydown = false;
            }
            no_keypress = true;
            // Meta+V did bind input but it didin't happen because terminal paste
            // prevent native insert action
            clip.$node.off('input', paste);
            var key = get_key(e);
            if (is_function(settings.keydown)) {
                e.key = ie_key_fix(e);
                result = settings.keydown.call(self, e);
                if (result !== undefined) {
                    //skip_keypress = true;
                    if (!result) {
                        skip_insert = true;
                    }
                    return result;
                }
            }
            if (key !== prev_key) {
                clear_hold();
            }
            // CTRL+C hanlding is only exception of cmd aware terminal logic
            // cmd need to call CTRL+C keymap when terminal is not enabled
            if (enabled || (key === 'CTRL+C' && is_terminal_selected(self))) {
                if (hold) {
                    prev_key = key;
                    key = 'HOLD+' + key;
                    if (hold_pause) {
                        return;
                    }
                    if (settings.holdRepeatTimeout > 0 && is_delay_key(key)) {
                        hold_pause = true;
                        self.oneTime(settings.holdRepeatTimeout, 'delay', function() {
                            hold_pause = false;
                        });
                    }
                } else {
                    self.oneTime(settings.holdTimeout, 'hold', function() {
                        hold = true;
                    });
                    prev_key = key;
                }
                // if e.fake ignore of space is handled in input and next keydown
                // is not triggered this is just in case code since on Android
                // keydown is not triggered only input so event is always fake on Android
                if (!e.fake && is_android) {
                    if (skip_keydown) {
                        clear_hold();
                        skip_keydown = false;
                        return false;
                    }
                    if (mobile_ignore_key(key)) {
                        skip_keydown = true;
                    } else if (mobile_ignore_key(prev_key)) {
                        // just in case next key is different then space
                        skip_keydown = false;
                    }
                }
                restart_animation();
                // CTRL+V don't fire keypress in IE11
                skip_insert = ['CTRL+V', 'META+V'].indexOf(key) !== -1;
                // only enter will reset history (and down arrow on last command)
                if (key.toLowerCase() === 'enter') {
                    first_up_history = true;
                }
                if (reverse_search && clear_reverse_search_key(e)) {
                    clear_reverse_state();
                    draw_prompt();
                    if (e.which === 27) { // ESC
                        self.set('');
                    }
                    redraw();
                    if (e.which === 13) {
                        keydown_event.call(this, e);
                    }
                } else if (is_function(keymap[key])) {
                    result = keymap[key](e);
                    if (result === true) {
                        return;
                    }
                    if (result !== undefined) {
                        return result;
                    }
                } else if (e.altKey) {
                    return;
                } else {
                    skip_keypress = false;
                    return;
                }
                // this will prevent for instance backspace to go back one page
                //skip_keypress = true;
                //e.preventDefault();
            }
        }
        function clear_hold() {
            self.stopTime('hold');
            self.stopTime('delay');
            hold_pause = hold = false;
        }
        var doc = $(document.documentElement || window);
        self.keymap(settings.keymap || {});
        function keypress_event(e) {
            debug('keypress "' + e.key + '" ' + e.fake);
            clear_hold();
            var result;
            if (!e.fake) {
                no_keypress = false;
            }
            if ((e.ctrlKey || e.metaKey) && !e.altKey) {
                return;
            }
            if (skip_keypress) {
                return;
            }
            if (is_function(settings.keypress)) {
                result = settings.keypress.call(self, e);
                if (result !== undefined) {
                    if (!result) {
                        skip_insert = true;
                    }
                    return result;
                }
            }
            if (enabled) {
                if (e.fake) {
                    // event created in input, we prevent inserting text
                    // in different interpreter when keydown called pop
                    return;
                }
                // key polyfill is not correct for keypress
                // https://github.com/cvan/keyboardevent-key-polyfill/issues/15
                var key;
                if (is_key_native) {
                    key = e.key;
                    // fixing IE inconsistency #362
                    var normalized = key.toUpperCase();
                    if (key_mapping[normalized]) {
                        key = key_mapping[normalized];
                    }
                }
                if (!key || no_key) {
                    key = String.fromCharCode(e.which);
                }
                if ($.inArray(e.which, [13, 0, 8]) > -1) {
                    if (e.keyCode === 123) { // for F12 which === 0
                        return;
                    }
                    return false;
                    // which === 100 - d
                } else if (key && (!e.ctrlKey || (e.ctrlKey && e.ctrlKey)) &&
                           (!(e.altKey && e.which === 100) || e.altKey) &&
                           !dead_key) {
                    // dead_key are handled by input event
                    if (reverse_search) {
                        rev_search_str += key;
                        reverse_history_search();
                        draw_reverse_prompt();
                    } else if (key.length === 1) {
                        self.insert(key);
                    }
                }
            }
        }
        function event(type, chr, which) {
            var event = $.Event(type);
            event.which = which;
            event.key = chr;
            event.fake = true;
            doc.trigger(event);
        }
        var skip_input = false;
        function input_event() {
            debug('input ' + no_keydown + ' || ' + process + ' ((' + no_keypress +
                  ' || ' + dead_key + ') && !' + skip_insert + ' && (' + single_key +
                  ' || ' + no_key + ') && !' + backspace + ')');
            // correct for fake space used for select all context menu hack
            var val = clip.val();
            if (!is_mobile) {
                val = val.replace(/^ /, '');
            }
            // Some Androids don't fire keypress - #39
            // if there is dead_key we also need to grab real character #158
            // Firefox/Android with google keyboard don't fire keydown and keyup #319
            if ((no_keydown || process || ((no_keypress || dead_key) && !skip_insert &&
                                          (single_key || no_key) && !backspace)) &&
                val !== command) {
                var pos = position;
                // backspace is set in keydown if no keydown we need to get new one
                if (no_keydown) {
                    var cmd = prev_command;
                    backspace = cmd.slice(0, cmd.length - 1).length === val.length;
                }
                if (skip_input) {
                    skip_input = false;
                    clip.val(command);
                    return;
                }
                if (reverse_search) {
                    rev_search_str = val;
                    reverse_history_search();
                    draw_reverse_prompt();
                } else {
                    var str = val.slice(position);
                    if (str.length === 1 || backspace) {
                        // original not optimized function called once
                        var chr = get_next_character(str);
                        if (mobile_ignore_key(chr)) {
                            skip_input = true;
                        }
                        // we trigger events so keypress and keydown callback work
                        if (no_keydown) {
                            var keycode;
                            if (backspace) {
                                keycode = 8;
                            } else {
                                keycode = str.toUpperCase().charCodeAt(0);
                            }
                            event('keydown', backspace ? 'Backspace' : str, keycode);
                        }
                        if (no_keypress && !backspace) {
                            event('keypress', chr, str.charCodeAt(0));
                        }
                    }
                    if (backspace) {
                        prev_command = command;
                        return;
                    }
                    // if user return false in keydown we don't want to insert text
                    if (skip_insert) {
                        skip_insert = false;
                        return;
                    }
                    self.set(val);
                }
                if (backspace) {
                    self.position(pos - 1);
                } else {
                    // user enter more then one character if click on complete word
                    // on android
                    self.position(pos + Math.abs(val.length - prev_command.length));
                }
            }
            prev_command = command;
            skip_insert = false;
            no_keydown = true;
        }
        doc.bind('keypress.cmd', keypress_event);
        doc.bind('keydown.cmd', keydown_event);
        doc.bind('keyup.cmd', clear_hold);
        doc.bind('input.cmd', input_event);
        (function() {
            if (is_mobile) {
                $(self[0]).add(clip.$node).on('touchstart.cmd', function() {
                    if (!self.isenabled()) {
                        clip.focus();
                    } else {
                        clip.blur();
                    }
                });
                self.disable();
                return;
            }
            var was_down = false;
            var count = 0;
            self.on('mousedown.cmd', function() {
                was_down = true;
            }).on('mouseup.cmd', function(e) {
                function trigger() {
                    var $target = $(e.target);
                    var is_prompt = $target.is('.cmd-prompt');
                    if (!is_prompt && down && get_selected_html() === '') {
                        if (enabled) {
                            if ($target.is('.cmd')) {
                                self.position(text(command).length);
                            } else {
                                self.display_position(get_char_pos(e));
                            }
                        }
                    }
                    count = 0;
                }
                // we get button from event for testing normally it's on originalEvent
                var button;
                if (e.originalEvent === undefined) {
                    button = e.button;
                } else {
                    button = e.originalEvent.button;
                }
                if (button === 0 && get_selected_html() === '') {
                    var name = 'click_' + id;
                    if (++count === 1) {
                        var down = was_down;
                        if (enabled) {
                            if (settings.clickTimeout === 0) {
                                trigger();
                            } else {
                                self.oneTime(settings.clickTimeout, name, trigger);
                            }
                        } else {
                            count = 0;
                        }
                    } else {
                        self.stopTime(name);
                        count = 0;
                    }
                }
                was_down = false;
            });
        })();
        self.data('cmd', self);
        if (!('KeyboardEvent' in window && 'key' in window.KeyboardEvent.prototype)) {
            setTimeout(function() {
                throw new Error('key event property not supported try https://github.' +
                                'com/inexorabletash/polyfill/blob/master/keyboard.js');
            }, 0);
        }
        return self;
    }; // cmd plugin
    // -------------------------------------------------------------------------
    var strlen = (function() {
        if (typeof wcwidth === 'undefined') {
            return function(string) {
                return $.terminal.length(string);
            };
        } else {
            return wcwidth;
        }
    })();
    // -------------------------------------------------------------------------
    function count_selfclosing_formatting(string) {
        var count = 0;
        if ($.terminal.have_formatting(string)) {
            var re = new RegExp(format_parts_re.source, 'i'); // without g flag
            $.terminal.format_split(string).forEach(function(str) {
                if ($.terminal.is_formatting(str)) {
                    var m = str.match(re);
                    if (m && m[1].match(/@/) && m[6] === '') {
                        count++;
                    }
                }
            });
        }
        return count;
    }
    // -------------------------------------------------------------------------
    // entiteis are case sensitive
    // generated from https://www.freeformatter.com/html-entities.html
    // -------------------------------------------------------------------------
    var entities = {
        "&amp;": "&",
        "&lt;": "<",
        "&gt;": ">",
        "&Agrave;": "À",
        "&Aacute;": "Á",
        "&Acirc;": "Â",
        "&Atilde;": "Ã",
        "&Auml;": "Ä",
        "&Aring;": "Å",
        "&AElig;": "Æ",
        "&Ccedil;": "Ç",
        "&Egrave;": "È",
        "&Eacute;": "É",
        "&Ecirc;": "Ê",
        "&Euml;": "Ë",
        "&Igrave;": "Ì",
        "&Iacute;": "Í",
        "&Icirc;": "Î",
        "&Iuml;": "Ï",
        "&ETH;": "Ð",
        "&Ntilde;": "Ñ",
        "&Ograve;": "Ò",
        "&Oacute;": "Ó",
        "&Ocirc;": "Ô",
        "&Otilde;": "Õ",
        "&Ouml;": "Ö",
        "&Oslash;": "Ø",
        "&Ugrave;": "Ù",
        "&Uacute;": "Ú",
        "&Ucirc;": "Û",
        "&Uuml;": "Ü",
        "&Yacute;": "Ý",
        "&THORN;": "Þ",
        "&szlig;": "ß",
        "&agrave;": "à",
        "&aacute;": "á",
        "&acirc;": "â",
        "&atilde;": "ã",
        "&auml;": "ä",
        "&aring;": "å",
        "&aelig;": "æ",
        "&ccedil;": "ç",
        "&egrave;": "è",
        "&eacute;": "é",
        "&ecirc;": "ê",
        "&euml;": "ë",
        "&igrave;": "ì",
        "&iacute;": "í",
        "&icirc;": "î",
        "&iuml;": "ï",
        "&eth;": "ð",
        "&ntilde;": "ñ",
        "&ograve;": "ò",
        "&oacute;": "ó",
        "&ocirc;": "ô",
        "&otilde;": "õ",
        "&ouml;": "ö",
        "&oslash;": "ø",
        "&ugrave;": "ù",
        "&uacute;": "ú",
        "&ucirc;": "û",
        "&uuml;": "ü",
        "&yacute;": "ý",
        "&thorn;": "þ",
        "&yuml;": "ÿ",
        "&nbsp;": " ",
        "&iexcl;": "¡",
        "&cent;": "¢",
        "&pound;": "£",
        "&curren;": "¤",
        "&yen;": "¥",
        "&brvbar;": "¦",
        "&sect;": "§",
        "&uml;": "¨",
        "&copy;": "©",
        "&ordf;": "ª",
        "&laquo;": "«",
        "&not;": "¬",
        "&shy;": "­",
        "&reg;": "®",
        "&macr;": "¯",
        "&deg;": "°",
        "&plusmn;": "±",
        "&sup2;": "²",
        "&sup3;": "³",
        "&acute;": "´",
        "&micro;": "µ",
        "&para;": "¶",
        "&cedil;": "¸",
        "&sup1;": "¹",
        "&ordm;": "º",
        "&raquo;": "»",
        "&frac14;": "¼",
        "&frac12;": "½",
        "&frac34;": "¾",
        "&iquest;": "¿",
        "&times;": "×",
        "&divide;": "÷",
        "&forall;": "∀",
        "&part;": "∂",
        "&exist;": "∃",
        "&empty;": "∅",
        "&nabla;": "∇",
        "&isin;": "∈",
        "&notin;": "∉",
        "&ni;": "∋",
        "&prod;": "∏",
        "&sum;": "∑",
        "&minus;": "−",
        "&lowast;": "∗",
        "&radic;": "√",
        "&prop;": "∝",
        "&infin;": "∞",
        "&ang;": "∠",
        "&and;": "∧",
        "&or;": "∨",
        "&cap;": "∩",
        "&cup;": "∪",
        "&int;": "∫",
        "&there4;": "∴",
        "&sim;": "∼",
        "&cong;": "≅",
        "&asymp;": "≈",
        "&ne;": "≠",
        "&equiv;": "≡",
        "&le;": "≤",
        "&ge;": "≥",
        "&sub;": "⊂",
        "&sup;": "⊃",
        "&nsub;": "⊄",
        "&sube;": "⊆",
        "&supe;": "⊇",
        "&oplus;": "⊕",
        "&otimes;": "⊗",
        "&perp;": "⊥",
        "&sdot;": "⋅",
        "&Alpha;": "Α",
        "&Beta;": "Β",
        "&Gamma;": "Γ",
        "&Delta;": "Δ",
        "&Epsilon;": "Ε",
        "&Zeta;": "Ζ",
        "&Eta;": "Η",
        "&Theta;": "Θ",
        "&Iota;": "Ι",
        "&Kappa;": "Κ",
        "&Lambda;": "Λ",
        "&Mu;": "Μ",
        "&Nu;": "Ν",
        "&Xi;": "Ξ",
        "&Omicron;": "Ο",
        "&Pi;": "Π",
        "&Rho;": "Ρ",
        "&Sigma;": "Σ",
        "&Tau;": "Τ",
        "&Upsilon;": "Υ",
        "&Phi;": "Φ",
        "&Chi;": "Χ",
        "&Psi;": "Ψ",
        "&Omega;": "Ω",
        "&alpha;": "α",
        "&beta;": "β",
        "&gamma;": "γ",
        "&delta;": "δ",
        "&epsilon;": "ε",
        "&zeta;": "ζ",
        "&eta;": "η",
        "&theta;": "θ",
        "&iota;": "ι",
        "&kappa;": "κ",
        "&lambda;": "λ",
        "&mu;": "μ",
        "&nu;": "ν",
        "&xi;": "ξ",
        "&omicron;": "ο",
        "&pi;": "π",
        "&rho;": "ρ",
        "&sigmaf;": "ς",
        "&sigma;": "σ",
        "&tau;": "τ",
        "&upsilon;": "υ",
        "&phi;": "φ",
        "&chi;": "χ",
        "&psi;": "ψ",
        "&omega;": "ω",
        "&thetasym;": "ϑ",
        "&upsih;": "ϒ",
        "&piv;": "ϖ",
        "&OElig;": "Œ",
        "&oelig;": "œ",
        "&Scaron;": "Š",
        "&scaron;": "š",
        "&Yuml;": "Ÿ",
        "&fnof;": "ƒ",
        "&circ;": "ˆ",
        "&tilde;": "˜",
        "&ensp;": " ",
        "&emsp;": " ",
        "&thinsp;": " ",
        "&zwnj;": "‌",
        "&zwj;": "‍",
        "&lrm;": "‎",
        "&rlm;": "‏",
        "&ndash;": "–",
        "&mdash;": "—",
        "&lsquo;": "‘",
        "&rsquo;": "’",
        "&sbquo;": "‚",
        "&ldquo;": "“",
        "&rdquo;": "”",
        "&bdquo;": "„",
        "&dagger;": "†",
        "&Dagger;": "‡",
        "&bull;": "•",
        "&hellip;": "…",
        "&permil;": "‰",
        "&prime;": "′",
        "&Prime;": "″",
        "&lsaquo;": "‹",
        "&rsaquo;": "›",
        "&oline;": "‾",
        "&euro;": "€",
        "&trade;": "™",
        "&larr;": "←",
        "&uarr;": "↑",
        "&rarr;": "→",
        "&darr;": "↓",
        "&harr;": "↔",
        "&crarr;": "↵",
        "&lceil;": "⌈",
        "&rceil;": "⌉",
        "&lfloor;": "⌊",
        "&rfloor;": "⌋",
        "&loz;": "◊",
        "&spades;": "♠",
        "&clubs;": "♣",
        "&hearts;": "♥",
        "&diams;": "♦"
    };
    // -------------------------------------------------------------------------
    function render_entities(str) {
        return str.replace(/&#(x?)([0-9]+);/g, function(_, hex, code) {
            code = parseInt(code, hex ? 16 : 10);
            return String.fromCharCode(code);
        }).replace(/(&[^;]+;)/g, function(_, entity) {
            return entities[entity] || entity;
        });
    }
    // -------------------------------------------------------------------------
    function bare_text(string) {
        if (!string.match(/&/)) {
            return string;
        }
        return render_entities(safe(string));
    }
    // -------------------------------------------------------------------------
    function text(string) {
        return bare_text($.terminal.strip(string));
    }
    // -------------------------------------------------------------------------
    function safe(string) {
        if (!string.match(/[<>&]/)) {
            return string;
        }
        return string.replace(/&(?![^;]+;)/g, '&amp;')
            .replace(/>/g, '&gt;').replace(/</g, '&lt;');
    }
    // -------------------------------------------------------------------------
    function crlf(string) {
        return string.replace(/\r/g, '');
    }
    // -------------------------------------------------------------------------
    function char_len(chr) {
        return entity_re.test(chr) ? 1 : chr.length;
    }
    // -------------------------------------------------------------------------
    function make_re_fn(re) {
        return function(string) {
            var m = string.match(re);
            if (starts_with(m)) {
                return m[1];
            }
        };
    }
    // -------------------------------------------------------------------------
    function starts_with(match) {
        return match && match.index === 0;
    }
    // -------------------------------------------------------------------------
    // :: optimized higher order function that it check complex regexes
    // :: only when bigger string match those regexes, function is always
    // :: used in loop when you process whole string, it's used to create local
    // :: get_next_character function only cmd in input use original
    // :: not optimized function
    // -------------------------------------------------------------------------
    function make_next_char_fun(string) {
        var tests = [];
        [
            entity_re,
            emoji_re,
            combine_chr_re
        ].forEach(function(re) {
            if (string.match(re)) {
                tests.push(make_re_fn(re));
            }
        });
        if (string.match(astral_symbols_re)) {
            tests.push(function(string) {
                var m1 = string.match(astral_symbols_re);
                if (starts_with(m1)) {
                    var m2 = string.match(combine_chr_re);
                    if (m2 && m2.index === 1) {
                        return string.slice(0, 3);
                    }
                    return m1[1];
                }
            });
        }
        return function(string) {
            for (var i = 0; i < tests.length; ++i) {
                var test = tests[i];
                var ret = test(string);
                if (ret) {
                    return ret;
                }
            }
            return string[0];
        };
    }
    // -------------------------------------------------------------------------
    // :: function that return character from beginning of the string
    // :: counting emoji, suroggate pairs and combine characters
    // -------------------------------------------------------------------------
    function get_next_character(string) {
        var match_entity = string.match(entity_re);
        if (starts_with(match_entity)) {
            return match_entity[1];
        }
        var match_combo = string.match(combine_chr_re);
        if (starts_with(match_combo)) {
            return match_combo[1];
        }
        var match_emoji = string.match(emoji_re);
        if (starts_with(match_emoji)) {
            return match_emoji[1];
        } else if (string.charCodeAt(0) < 255) {
            return string[0];
        } else {
            var astral_match = string.match(astral_symbols_re);
            if (starts_with(astral_match)) {
                match_combo = string.match(combine_chr_re);
                if (match_combo && match_combo.index === 1) {
                    return string.slice(0, 3);
                }
                return string.slice(0, 2);
            } else {
                return string[0];
            }
        }
    }
    // -------------------------------------------------------------------------
    // normalize position for counting emoji and extra chars
    // -------------------------------------------------------------------------
    function normalize_position(string, position) {
        if (position === 0) {
            return position;
        }
        string = $.terminal.strip(string);
        var result = $.terminal.split_characters(string).reduce(function(acc, chr) {
            if (typeof acc === 'number') {
                return acc;
            }
            var length = acc.length + char_len(chr);
            if (length >= position) {
                return acc.position + 1;
            }
            return {
                position: acc.position + 1,
                length: length
            };
        }, {position: 0, length: 0});
        if (typeof result === 'number') {
            return result;
        } else {
            return result.position;
        }
    }
    // -------------------------------------------------------------------------
    function char_width_prop(len, options) {
        if (is_ch_unit_supported) {
            return 'width: ' + len + 'ch';
        } else if (!is_css_variables_supported) {
            if (options.char_width) {
                return 'width: ' + (options.char_width * len) + 'px';
            }
        } else {
            return '--length: ' + len;
        }
        return '';
    }
    // -------------------------------------------------------------------------
    // options {char_width}
    function extra_css(text, options) {
        if (typeof wcwidth !== 'undefined') {
            var bare = bare_text(text);
            var len = strlen(bare);
            if (len > 1 && len !== $.terminal.length(bare)) {
                return char_width_prop(len, options);
            }
        }
        return '';
    }
    // -------------------------------------------------------------------------
    function wide_characters(text, options) {
        if (typeof wcwidth !== 'undefined') {
            var bare = bare_text(text);
            var chars = $.terminal.split_characters(bare);
            if (chars.length === 1) {
                return text;
            }
            var specs = chars.map(function(chr) {
                return {
                    len: strlen(chr),
                    chr: chr
                };
            }).reduce(function(arr, spec) {
                var last = arr[arr.length - 1];
                if (last) {
                    if (last.len !== spec.len) {
                        return arr.concat([{
                            sum: spec.len,
                            len: spec.len,
                            specs: [spec]
                        }]);
                    } else {
                        arr.pop();
                        return arr.concat([{
                            sum: last.sum + spec.len,
                            len: last.len,
                            specs: last.specs.concat(spec)
                        }]);
                    }
                }
                return [{
                    sum: spec.len,
                    specs: [spec],
                    len: spec.len
                }];
            }, []);
            return specs.map(function(spec) {
                if (spec.len === 1) {
                    return make_string(spec);
                }
                var style = char_width_prop(spec.sum, options);
                if (spec.sum === chars.length || !style.length) {
                    return '<span>' + make_string(spec) + '</span>';
                } else if (spec.specs.length > 1) {
                    return wrap(style, spec.specs.map(function(spec) {
                        return wrap(char_width_prop(spec.len), spec.chr);
                    }).join(''));
                } else {
                    return wrap(style, make_string(spec));
                }
            }).join('');
        }
        function make_string(spec) {
            return spec.specs.map(function(spec) {
                return spec.chr;
            }).join('');
        }
        function wrap(style, str) {
            return '<span style="' + style + '">' + str + '</span>';
        }
        return text;
    }
    // ---------------------------------------------------------------------
    // :: Binary search utility
    // ---------------------------------------------------------------------
    function binary_search(start, end, search_pos, compare_fn, more_args) {
        var len = end - start;
        var mid = start + Math.floor(len / 2);
        var args = [search_pos, mid].concat(more_args);
        var cmp = compare_fn.apply(null, args);
        if (cmp === 0) {
            return mid;
        } else if (cmp > 0 && len > 1) {
            return binary_search(
                mid,
                end,
                search_pos,
                compare_fn,
                more_args
            );
        } else if (cmp < 0 && len > 1) {
            return binary_search(
                start,
                mid,
                search_pos,
                compare_fn,
                more_args
            );
        } else {
            return -1;
        }
    }
    // -----------------------------------------------------------------
    // :: selection utilities - should work in modern browser including IE9
    // -----------------------------------------------------------------
    function is_terminal_selected(cmd) {
        if (is_function(window.getSelection)) {
            var selection = window.getSelection();
            if (selection.toString()) {
                var node = selection.getRangeAt(0).startContainer.parentNode;
                var term = $(node).closest('.terminal');
                return term.length && (cmd && term.find('.cmd').is(cmd) || !cmd);
            }
        }
    }
    // -----------------------------------------------------------------
    function get_selected_html() {
        var html = '';
        if (is_function(window.getSelection)) {
            var sel = window.getSelection();
            if (sel.rangeCount) {
                var container = document.createElement('div');
                for (var i = 0, len = sel.rangeCount; i < len; ++i) {
                    container.appendChild(sel.getRangeAt(i).cloneContents());
                }
                html = container.innerHTML;
            }
        }
        return html;
    }
    // -----------------------------------------------------------------
    function with_selection(fn) {
        var html = '';
        var ranges = [];
        if (is_function(window.getSelection)) {
            var selection = window.getSelection();
            if (selection.rangeCount) {
                var container = document.createElement("div");
                for (var i = 0, len = selection.rangeCount; i < len; ++i) {
                    var range = selection.getRangeAt(i).cloneRange();
                    ranges.push(range);
                    container.appendChild(range.cloneContents());
                }
                html = container.innerHTML;
            }
        }
        fn(html);
        if (ranges.length) {
            selection.removeAllRanges();
            ranges.forEach(function(range) {
                selection.addRange(range);
            });
        }
        return html !== '';
    }
    // -----------------------------------------------------------------
    function process_selected_line() {
        var $self = $(this);
        var result = $self.text();
        if ($self.hasClass('cmd-end-line')) {
            result += '\n';
        }
        return result;
    }
    // -----------------------------------------------------------------
    function process_div(element) {
        // span is empty line, div is default case with text
        return $(element).find('> div, > span')
            .map(process_selected_line).get().join('\n').replace(/\n$/, '');
    }
    // -----------------------------------------------------------------
    function process_selected_html(html) {
        var stdout;
        var text = '';
        var $html = $('<div>' + html + '</div>');
        if (html.match(/<\/div>/)) {
            // match multiple echo output
            stdout = $html.find('div[data-index]').map(function() {
                return process_div(this);
            }).get().join('\n');
            // match inside single echo output
            if (!stdout && html.match(/style="width: 100%;?"/)) {
                stdout = process_div($html);
            }
            text = stdout;
        }
        var $prompt = $html.find('.cmd-prompt');
        if ($prompt.length) {
            if (text.length) {
                text += '\n';
            }
            text += $prompt.text();
        }
        var $cmd_lines = $html.find('[role="presentation"]');
        if ($cmd_lines.length) {
            text += $cmd_lines.map(process_selected_line).get().join('');
        }
        if (!text.length && html) {
            text = $html.text();
        }
        return text.replace(/\xA0/g, ' '); // fix &nbsp; space
    }
    // ---------------------------------------------------------------------
    // :: copy given DOM element text to clipboard
    // ---------------------------------------------------------------------
    var support_copy = (function() {
        if (typeof document === 'undefined') {
            return false;
        }
        if (!is_function(document.queryCommandSupported)) {
            return false;
        }
        return document.queryCommandSupported('copy');
    })();
    // ---------------------------------------------------------------------
    var text_to_clipboard;
    if (support_copy) {
        text_to_clipboard = function text_to_clipboard($textarea, text) {
            var val = $textarea.val();
            var had_focus = $textarea.is(':focus');
            var pos = $textarea.caret();
            if (window.navigator && window.navigator.clipboard) {
                navigator.clipboard.writeText(text);
            } else if (had_focus) {
                $textarea.val(text).focus();
                $textarea[0].select();
                document.execCommand('copy');
                $textarea.val(val);
                $textarea.caret(pos);
            } else {
                var $text = $('<textarea/>').css({
                    position: 'fixed',
                    top: 0,
                    left: 0
                }).appendTo('body');
                $text.val(text).focus();
                $text[0].select();
                document.execCommand('copy');
                $text.blur();
                $text.remove();
            }
            return true;
        };
    } else {
        text_to_clipboard = $.noop;
    }
    // ---------------------------------------------------------------------
    var get_textarea_selection = (function() {
        function noop() {
            return '';
        }
        if (typeof document === 'undefined') {
            return noop;
        }
        var textarea = document.createElement('textarea');
        var selectionStart = 'selectionStart' in textarea;
        textarea = null;
        if (selectionStart) {
            return function(textarea) {
                var length = textarea.selectionEnd - textarea.selectionStart;
                return textarea.value.substr(textarea.selectionStart, length);
            };
        } else if (document.selection) {
            return function() {
                var range = document.selection.createRange();
                return range.text();
            };
        } else {
            return noop;
        }
    })();
    // ---------------------------------------------------------------------
    function clear_textarea_selection(textarea) {
        textarea.selectionStart = textarea.selectionEnd = 0;
    }
    // ---------------------------------------------------------------------
    // :: return string that are common in all elements of the array
    // ---------------------------------------------------------------------
    function common_string(string, array, matchCase) {
        if (!array.length) {
            return '';
        }
        var type = string_case(string);
        var result = [];
        for (var j = string.length; j < array[0].length; ++j) {
            var push = false;
            var candidate = array[0].charAt(j),
                candidateLower = candidate.toLowerCase();
            for (var i = 1; i < array.length; ++i) {
                push = true;
                var current = array[i].charAt(j),
                    currentLower = current.toLowerCase();
                if (candidate !== current) {
                    if (matchCase || type === 'mixed') {
                        push = false;
                        break;
                    } else if (candidateLower === currentLower) {
                        if (type === 'lower') {
                            candidate = candidate.toLowerCase();
                        } else if (type === 'upper') {
                            candidate = candidate.toUpperCase();
                        } else {
                            push = false;
                            break;
                        }
                    } else {
                        push = false;
                        break;
                    }
                }
            }
            if (push) {
                result.push(candidate);
            } else {
                break;
            }
        }
        return string + result.join('');
    }
    // ---------------------------------------------------------------------
    function trigger_terminal_change(next) {
        terminals.forEach(function(term) {
            term.settings().onTerminalChange.call(term, next);
        });
    }
    // ---------------------------------------------------------------------
    var select = (function() {
        if (root.getSelection) {
            var selection = root.getSelection();
            if (selection.setBaseAndExtent) {
                return function(start, end) {
                    var selection = root.getSelection();
                    selection.setBaseAndExtent(start, 0, end, 1);
                };
            } else {
                return function(start, end) {
                    var selection = root.getSelection();
                    var range = document.createRange();
                    range.setStart(start, 0);
                    range.setEnd(end, end.childNodes.length);
                    selection.removeAllRanges();
                    selection.addRange(range);
                };
            }
        } else {
            return $.noop;
        }
    })();
    // -------------------------------------------------------------------------
    function process_command(string, fn) {
        var array = string.match(command_re) || [];
        if (array.length) {
            var name = array.shift();
            var args = $.map(array, function(arg) {
                if (arg.match(/^["']/)) {
                    arg = arg.replace(/\n/g, '\\u0000\\u0000\\u0000\\u0000');
                    arg = fn(arg);
                    return arg.replace(/\x00\x00\x00\x00/g, '\n');
                }
                return fn(arg);
            });
            var quotes = $.map(array, function(arg) {
                var m = arg.match(/^(['"`]).*\1$/);
                return m && m[1] || '';
            });
            var rest = string.slice(name.length).trim();
            return {
                command: string,
                name: name,
                args: args,
                args_quotes: quotes,
                rest: rest
            };
        } else {
            return {
                command: string,
                name: '',
                args: [],
                args_quotes: [],
                rest: ''
            };
        }
    }
    // -------------------------------------------------------------------------
    $.terminal = {
        version: '2.28.1',
        date: 'Wed, 04 Aug 2021 06:57:27 +0000',
        // colors from https://www.w3.org/wiki/CSS/Properties/color/keywords
        color_names: [
            'transparent', 'currentcolor', 'black', 'silver', 'gray', 'white',
            'maroon', 'red', 'purple', 'fuchsia', 'green', 'lime', 'olive',
            'yellow', 'navy', 'blue', 'teal', 'aqua', 'aliceblue',
            'antiquewhite', 'aqua', 'aquamarine', 'azure', 'beige', 'bisque',
            'black', 'blanchedalmond', 'blue', 'blueviolet', 'brown',
            'burlywood', 'cadetblue', 'chartreuse', 'chocolate', 'coral',
            'cornflowerblue', 'cornsilk', 'crimson', 'cyan', 'darkblue',
            'darkcyan', 'darkgoldenrod', 'darkgray', 'darkgreen', 'darkgrey',
            'darkkhaki', 'darkmagenta', 'darkolivegreen', 'darkorange',
            'darkorchid', 'darkred', 'darksalmon', 'darkseagreen',
            'darkslateblue', 'darkslategray', 'darkslategrey', 'darkturquoise',
            'darkviolet', 'deeppink', 'deepskyblue', 'dimgray', 'dimgrey',
            'dodgerblue', 'firebrick', 'floralwhite', 'forestgreen', 'fuchsia',
            'gainsboro', 'ghostwhite', 'gold', 'goldenrod', 'gray', 'green',
            'greenyellow', 'grey', 'honeydew', 'hotpink', 'indianred', 'indigo',
            'ivory', 'khaki', 'lavender', 'lavenderblush', 'lawngreen',
            'lemonchiffon', 'lightblue', 'lightcoral', 'lightcyan',
            'lightgoldenrodyellow', 'lightgray', 'lightgreen', 'lightgrey',
            'lightpink', 'lightsalmon', 'lightseagreen', 'lightskyblue',
            'lightslategray', 'lightslategrey', 'lightsteelblue', 'lightyellow',
            'lime', 'limegreen', 'linen', 'magenta', 'maroon',
            'mediumaquamarine', 'mediumblue', 'mediumorchid', 'mediumpurple',
            'mediumseagreen', 'mediumslateblue', 'mediumspringgreen',
            'mediumturquoise', 'mediumvioletred', 'midnightblue', 'mintcream',
            'mistyrose', 'moccasin', 'navajowhite', 'navy', 'oldlace', 'olive',
            'olivedrab', 'orange', 'orangered', 'orchid', 'palegoldenrod',
            'palegreen', 'paleturquoise', 'palevioletred', 'papayawhip',
            'peachpuff', 'peru', 'pink', 'plum', 'powderblue', 'purple', 'red',
            'rosybrown', 'royalblue', 'saddlebrown', 'salmon', 'sandybrown',
            'seagreen', 'seashell', 'sienna', 'silver', 'skyblue', 'slateblue',
            'slategray', 'slategrey', 'snow', 'springgreen', 'steelblue', 'tan',
            'teal', 'thistle', 'tomato', 'turquoise', 'violet', 'wheat',
            'white', 'whitesmoke', 'yellow', 'yellowgreen', 'rebeccapurple'],
        // for unit tests
        Cycle: Cycle,
        History: History,
        Stack: Stack,
        // ---------------------------------------------------------------------
        // :: Validate html color (it can be name or hex)
        // ---------------------------------------------------------------------
        valid_color: function valid_color(color) {
            if (color.match(color_re)) {
                return true;
            } else {
                return $.inArray(color.toLowerCase(), $.terminal.color_names) !== -1;
            }
        },
        // ---------------------------------------------------------------------
        // :: function check if given string contain invalid strings
        // ---------------------------------------------------------------------
        unclosed_strings: function unclosed_strings(string) {
            return !!string.match(unclosed_strings_re);
        },
        // ---------------------------------------------------------------------
        // :: Escape all special regex characters, so it can be use as regex to
        // :: match exact string that contain those characters
        // ---------------------------------------------------------------------
        escape_regex: function escape_regex(str) {
            if (typeof str === 'string') {
                var special = /([-\\^$[\]()+{}?*.|])/g;
                return str.replace(special, '\\$1');
            }
        },
        // ---------------------------------------------------------------------
        // :: test if string contain formatting
        // ---------------------------------------------------------------------
        have_formatting: function have_formatting(str) {
            return typeof str === 'string' && !!str.match(format_exist_re);
        },
        is_formatting: function is_formatting(str) {
            return typeof str === 'string' && !!str.match(format_full_re);
        },
        // ---------------------------------------------------------------------
        // :: return array of formatting and text between them
        // ---------------------------------------------------------------------
        format_split: function format_split(str) {
            return str.split(format_split_re).filter(Boolean);
        },
        // ---------------------------------------------------------------------
        // :: replace that return position after replace for working with
        // :: replacement that change length of the string
        // :: source https://stackoverflow.com/a/46756077/387194
        // ---------------------------------------------------------------------
        tracking_replace: function tracking_replace(string, rex, replacement, position) {
            if (!(rex instanceof RegExp)) {
                throw new Error('tracking_replace: Second argument need to be RegExp');
            }
            function substring(string, start, end) {
                return string.slice(start, end);
            }
            function length(string) {
                return $.terminal.strip(string).length;
            }
            var new_string = "";
            var match;
            var index = 0;
            var rep_string;
            var new_position = position;
            var start;
            rex.lastIndex = 0; // Just to be sure
            while ((match = rex.exec(string))) {
                // if regex don't have g flag lastIndex will not work
                if (rex.global) {
                    // Add any of the original string we just skipped
                    var last_index = length(substring(string, 0, rex.lastIndex));
                    start = last_index - length(match[0]);
                } else {
                    start = match.index;
                    last_index = start + length(match[0]);
                }
                if (index < start) {
                    new_string += substring(string, index, start);
                }
                index = last_index;
                // Build the replacement string. This just handles $$ and $n,
                // you may want to add handling for $`, $', and $&.
                if (typeof replacement === 'function') {
                    rep_string = replacement.apply(null, match);
                } else {
                    rep_string = replacement.replace(/\$(\$|\d)/g, function(m, c0) {
                        if (c0 === "$") {
                            return "$";
                        }
                        return match[c0];
                    });
                }
                // Add on the replacement
                new_string += rep_string;
                // If the position is affected...
                if (start < position) {
                    // ... update it:
                    var rep_len = length(rep_string);
                    rep_len += count_selfclosing_formatting(rep_string);
                    if (last_index < position) {
                        // It's after the replacement, move it
                        new_position = Math.max(
                            0,
                            new_position +
                            rep_len -
                            length(match[0])
                        );
                    } else {
                        // It's *in* the replacement, put it just after
                        new_position += rep_len - (position - start);
                    }
                }
                // If the regular expression doesn't have the g flag, break here so
                // we do just one replacement (and so we don't have an endless loop!)
                if (!rex.global) {
                    break;
                }
            }
            // Add on any trailing text in the string
            if (index < length(string)) {
                new_string += substring(string, index);
            }
            // Return the string and the updated position
            if (string === new_string) {
                return [string, position];
            }
            return [new_string, new_position];
        },
        // ---------------------------------------------------------------------
        // :: helper function used by substring and split_equal it loop over
        // :: string and execute callback with text count and other data
        // ---------------------------------------------------------------------
        iterate_formatting: function iterate_formatting(string, callback) {
            function is_space(i) {
                return string.slice(i - 6, i) === '&nbsp;' ||
                    string.slice(i - 1, i).match(/\s/);
            }
            // ----------------------------------------------------------------
            function match_entity(index) {
                return string.slice(index).match(entity_re);
            }
            // ----------------------------------------------------------------
            function is_open_formatting(i) {
                return string[i] === '[' && string[i + 1] === '[';
            }
            // ----------------------------------------------------------------
            function is_escape_bracket(i) {
                return string[i - 1] !== '\\' && string[i] === '\\' &&
                    string[i + 1] === ']';
            }
            // ----------------------------------------------------------------
            function is_text(i) {
                return not_formatting && (string[i] !== ']' || !have_formatting)
                    && !opening;
            }
            // ----------------------------------------------------------------
            // :: function will skip to next character in main loop
            // :: TODO: improve performance of emoji regex and check whole
            // :: string it's complex string if not use simple function
            // ----------------------------------------------------------------
            var get_next_character = make_next_char_fun(string);
            function next_iteration() {
                var char = get_next_character(substring);
                if (char.length > 1 && $.terminal.length(substring) > 1) {
                    return char.length - 1;
                }
                return 0;
            }
            // ----------------------------------------------------------------
            function is_next_space() {
                return (is_space(i) && (not_formatting || opening)) &&
                    (space === -1 && prev_space !== i || space !== -1);
            }
            // ----------------------------------------------------------------
            // :: last iteration or one before closing formatting
            // ----------------------------------------------------------------
            var last = false;
            function is_last() {
                if (i === string.length - 1 && !last) {
                    last = true;
                } else {
                    last = formatting && !!substring.match(/^.]$/);
                }
                return last;
            }
            // ----------------------------------------------------------------
            var have_formatting = $.terminal.have_formatting(string);
            var formatting = '';
            var in_text = false;
            var count = 0;
            var match;
            var space = -1;
            var space_count = -1;
            var prev_space;
            var length = 0;
            var offset = 0;
            var re_ent = /(&[^;]+);$/;
            for (var i = 0; i < string.length; i++) {
                var substring = string.slice(i);
                match = substring.match(format_start_re);
                if (match) {
                    formatting = match[1];
                    in_text = false;
                } else if (formatting) {
                    if (string[i] === ']') {
                        if (in_text) {
                            formatting = '';
                            in_text = false;
                        } else {
                            in_text = true;
                        }
                    }
                } else {
                    in_text = true;
                }
                var not_formatting = (formatting && in_text) || !formatting;
                var opening = is_open_formatting(i);
                if (is_next_space()) {
                    space = i;
                    space_count = count;
                }
                var braket = string[i].match(/[[\]]/);
                offset = 0;
                if (not_formatting) {
                    // treat entity as one character
                    if (string[i] === '&') {
                        match = match_entity(i);
                        if (match) {
                            i += match[1].length - 2; // 2 because continue adds 1 to i
                            continue;
                        }
                        ++count;
                        ++length;
                    } else if (is_escape_bracket(i)) {
                        // escape \] and \\ counts as one character
                        ++count;
                        ++length;
                        offset = 1;
                        i += 1;
                    } else if (!braket || !have_formatting) {
                        ++count;
                        ++length;
                    }
                }
                if (is_text(i)) {
                    if (strlen(string[i]) === 2) {
                        length++;
                    }
                    var char = get_next_character(substring);
                    var size = char.length;
                    // begining of enity that we've skipped, we are at the end
                    if (char === ';') {
                        match = string.slice(0, i + 1).match(re_ent);
                        if (match) {
                            offset = match[1].length;
                            size = offset + 1;
                        }
                    }
                    var data = {
                        last: is_last(),
                        count: count,
                        index: i - offset,
                        formatting: formatting,
                        length: length,
                        text: in_text,
                        size: size,
                        space: space,
                        space_count: space_count
                    };
                    var ret = callback(data);
                    if (ret === false) {
                        break;
                    } else if (ret) {
                        if (ret.count !== undefined) {
                            count = ret.count;
                        }
                        if (ret.length !== undefined) {
                            length = ret.length;
                        }
                        if (ret.space !== undefined) {
                            prev_space = space;
                            space = ret.space;
                        }
                        if (ret.index !== undefined) {
                            i = ret.index;
                            continue;
                        }
                    }
                } else if (i === string.length - 1 && !last) {
                    // last iteration, if formatting have last bracket,
                    // from formatting, then last iteration
                    // was already called (in if) #550
                    callback({
                        last: true,
                        count: count + 1,
                        index: i,
                        formatting: formatting,
                        length: 0,
                        text: in_text,
                        space: space
                    });
                }
                // handle emoji, suroggate pairs and combine characters
                if (in_text) {
                    i += next_iteration();
                }
            }
        },
        // ---------------------------------------------------------------------
        // :: function return string splitted into single characters
        // :: each character is wrapped into formatting from input string
        // :: or empty formatting so it will create span when using with ::format
        // ---------------------------------------------------------------------
        partition: function partition(string) {
            if (!$.terminal.have_formatting(string)) {
                var chars = $.terminal.split_characters(string);
                return chars.map(wrap);
            }
            var result = [];
            function wrap(string) {
                if (string.match(/\\$/)) {
                    string += '\\';
                }
                return '[[;;]' + string + ']';
            }
            function formatting(string) {
                if ($.terminal.is_formatting(string)) {
                    if (string.match(/\\]$/)) {
                        string = string.replace(/\\]/g, '\\\\]');
                    }
                } else {
                    string = wrap(string);
                }
                return string;
            }
            $.terminal.iterate_formatting(string, function(data) {
                if (data.text) {
                    var text = [];
                    if (data.formatting) {
                        text.push(data.formatting);
                    }
                    text.push(string.substring(data.index, data.index + data.size));
                    if (data.formatting) {
                        text.push(']');
                    }
                    result.push(formatting(text.join('')));
                }
            });
            return result;
        },
        // ---------------------------------------------------------------------
        // :: formatting aware substring function
        // ---------------------------------------------------------------------
        substring: function substring(string, start_index, end_index) {
            var chars = $.terminal.split_characters(string);
            if (!chars.slice(start_index, end_index).length) {
                return '';
            }
            if (!$.terminal.have_formatting(string)) {
                return chars.slice(start_index, end_index).join('');
            }
            var start = 0;
            var end;
            var start_formatting = '';
            var end_formatting = '';
            var prev_index;
            var offset = 1;
            $.terminal.iterate_formatting(string, function(data) {
                if (start_index && data.count === start_index + 1) {
                    start = data.index;
                    if (data.formatting) {
                        start_formatting = data.formatting;
                    }
                }
                if (end_index && data.count === end_index) {
                    end_formatting = data.formatting;
                    prev_index = data.index;
                    offset = data.size;
                }
                if (data.count === end_index + 1) {
                    end = data.index;
                    if (data.formatting) {
                        end = prev_index + offset;
                    }
                }
            });
            if (start_index && !start) {
                return '';
            }
            if (end === undefined) {
                end = string.length;
            }
            string = start_formatting + string.slice(start, end);
            if (end_formatting) {
                string = string.replace(/(\[\[^\]]+)?\]$/, '');
                string += ']';
            }
            return string;
        },
        // ---------------------------------------------------------------------
        // :: add format text as 5th paramter to formatting it's used for
        // :: data attribute in format function - and fix unclosed &
        // ---------------------------------------------------------------------
        normalize: function normalize(string) {
            string = string.replace(format_re, function(_, format, text) {
                if (format.match(self_closing_re) && text === '') {
                    return '[[' + format + '] ]';
                }
                if (text === '') {
                    return '';
                }
                function safe(string) {
                    return string.replace(/\\\]/g, '&#93;').replace(/\n/g, '\\n')
                        .replace(/&nbsp;/g, ' ');
                }
                format = safe(format);
                var semicolons = format.match(/;/g).length;
                // missing semicolons
                if (semicolons >= 4) {
                    var args = format.split(/;/);
                    var start = args.slice(0, 4).join(';');
                    var arg = args.slice(4).join(';');
                    return '[[' + start + ';' + (arg || text) + ']' + text + ']';
                } else if (semicolons === 2) {
                    semicolons = ';;';
                } else if (semicolons === 3) {
                    semicolons = ';';
                }
                // return '[[' + format + ']' + text + ']';
                // closing braket will break formatting so we need to escape
                // those using html entity equvalent
                // space is hack for images that break iterate_formatting
                format += semicolons + safe(text);
                return '[[' + format + ']' + text + ']';
            });
            return $.terminal.amp(string);
        },
        // ---------------------------------------------------------------------
        // :: split text into lines with equal length so each line can be
        // :: rendered separately (text formatting can be longer then a line).
        // ---------------------------------------------------------------------
        split_equal: function split_equal(str, length, keep_words) {
            var prev_format = '';
            var result = [];
            var array = $.terminal.normalize(str).split(/\n/g);
            for (var i = 0, len = array.length; i < len; ++i) {
                if (array[i] === '') {
                    result.push('');
                    continue;
                }
                var line = array[i];
                var get_next_character = make_next_char_fun(line);
                var first_index = 0;
                var output;
                var line_length = line.length;
                var last_bracket = !!line.match(/\[\[[^\]]+\](?:[^\][]|\\\])+\]$/);
                $.terminal.iterate_formatting(line, function(data) {
                    var chr, substring;
                    if (data.length >= length || data.last ||
                        (data.length === length - 1 &&
                         strlen(line[data.index + 1]) === 2)) {
                        var can_break = false;
                        // TODO: this need work
                        if (keep_words && data.space !== -1) {
                            // replace html entities with characters
                            var stripped = text(line).substring(data.space_count);
                            // real length, not counting formatting
                            stripped = stripped.slice(0, length).trim();
                            var text_len = strlen(stripped);
                            if (stripped.match(/\s/) || text_len < length) {
                                can_break = true;
                            }
                        }
                        // if words is true we split at last space and make next loop
                        // continue where the space where located
                        var after_index = data.index + data.size;
                        if (last_bracket) {
                            after_index += 1;
                        }
                        var new_index;
                        if (keep_words && data.space !== -1 &&
                            after_index !== line_length && can_break) {
                            output = line.slice(first_index, data.space);
                            new_index = data.space - 1;
                        } else {
                            substring = line.slice(data.index);
                            chr = get_next_character(substring);
                            output = line.slice(first_index, data.index) + chr;
                            if (data.last && last_bracket && chr !== ']') {
                                output += ']';
                            }
                            new_index = data.index + chr.length - 1;
                        }
                        if (keep_words) {
                            output = output.replace(/^(&nbsp;|\s)+|(&nbsp;|\s)+$/g, '');
                        }
                        first_index = (new_index || data.index) + 1;
                        if (prev_format) {
                            var closed_formatting = output.match(/^[^\]]*\]/);
                            output = prev_format + output;
                            if (closed_formatting) {
                                prev_format = '';
                            }
                        }
                        var matched = output.match(format_re);
                        if (matched) {
                            var last = matched[matched.length - 1];
                            if (last[last.length - 1] !== ']') {
                                prev_format = last.match(format_begin_re)[1];
                                output += ']';
                            } else if (output.match(format_end_re)) {
                                output = output.replace(format_end_re, '');
                                prev_format = last.match(format_begin_re)[1];
                            }
                        }
                        result.push(output);
                        // modify loop by returing new data
                        return {index: new_index, length: 0, space: -1};
                    }
                });
            }
            return result;
        },
        // ---------------------------------------------------------------------
        // :: Escape & that's not part of entity
        // ---------------------------------------------------------------------
        amp: function amp(str) {
            return str.replace(/&(?!#[0-9]+;|#x[0-9a-f]+;|[a-z]+;)/gi, '&amp;');
        },
        // ---------------------------------------------------------------------
        // :: Encode formating as html for insertion into DOM
        // ---------------------------------------------------------------------
        encode: function encode(str, options) {
            var settings = $.extend({
                tabs: 4,
                before: ''
            }, options);
            return $.terminal.amp(str).replace(/</g, '&lt;').replace(/>/g, '&gt;')
                .replace(/ /g, '&nbsp;').split('\n').map(function(line) {
                    var splitted = line.split(/((?:\[\[[^\]]+\])?\t(?:\])?)/);
                    splitted = splitted.filter(Boolean);
                    return splitted.map(function(str, i) {
                        if (str.match(/\t/)) {
                            return str.replace(/\t([^\t]*)$/, function(_, end) {
                                if (i !== 0 && splitted[i - 1].match(/\t\]?$/)) {
                                    var sp = new Array(settings.tabs + 1).join('&nbsp;');
                                    return sp + end;
                                } else {
                                    var before = splitted.slice(i - 1, i).join('');
                                    if (settings.before && i <= 1) {
                                        before = settings.before + before;
                                    }
                                    var len = $.terminal.length(before);
                                    var chars = settings.tabs - (len % settings.tabs);
                                    if (chars === 0) {
                                        chars = 4;
                                    }
                                    return new Array(chars + 1).join('&nbsp;') + end;
                                }
                            });
                        }
                        return str;
                    }).join('');
                }).join('\n');
        },
        // -----------------------------------------------------------------------
        // :: Default formatter that allow for nested formatting, example:
        // :: [[;;#000]hello [[;#f00;]red] world]
        // -----------------------------------------------------------------------
        nested_formatting: function nested_formatting(string) {
            if (!$.terminal.have_formatting(string)) {
                return string;
            }
            var stack = [];
            var re = /((?:\[\[(?:[^\][]|\\\])+\])?(?:[^\][]|\\\])*\]?)/;
            var format_re = /\[\[([^\][]+)\][\s\S]*/;
            var format_split_re = /^\[\[([^;]*);([^;]*);([^\]]*)\]/;
            var class_i = 3; // index of the class in formatting
            var attrs_i = 5; // index of attributes in formatting
            // ---------------------------------------------------------------------------
            function unique(value, index, self) {
                return self.indexOf(value) === index;
            }
            // ---------------------------------------------------------------------------
            function update_style(new_style, old_style) {
                new_style = parse_style(new_style);
                if (!old_style) {
                    return new_style;
                }
                return $.extend(old_style, new_style);
            }
            // ---------------------------------------------------------------------------
            function parse_style(string) {
                var style = {};
                string.split(/\s*;\s*/).forEach(function(string) {
                    var parts = string.split(':').map(function(string) {
                        return string.trim();
                    });
                    var prop = parts[0];
                    var value = parts[1];
                    style[prop] = value;
                });
                return style;
            }
            // ---------------------------------------------------------------------------
            function stringify_formatting(input) {
                var result = input.slice();
                if (input[attrs_i]) {
                    result[attrs_i] = stringify_attrs(input[attrs_i]);
                }
                if (input[class_i]) {
                    result[class_i] = stringify_class(input[class_i]);
                }
                result[0] = stringify_styles(input[0]);
                return result.join(';');
            }
            // ---------------------------------------------------------------------------
            function stringify_styles(input) {
                var ignore = input.filter(function(s) {
                    return s[0] === '-';
                }).map(function(s) {
                    return s[1];
                });
                return input.filter(function(s) {
                    return ignore.indexOf(s) === -1 && ignore.indexOf(s[1]) === -1;
                }).join('');
            }
            // ---------------------------------------------------------------------------
            function stringify_attrs(attrs) {
                return JSON.stringify(attrs, function(key, value) {
                    if (key === 'style') {
                        return stringify_style(value);
                    }
                    return value;
                });
            }
            // ---------------------------------------------------------------------------
            function stringify_class(klass) {
                return klass.filter(unique).join(' ');
            }
            // ---------------------------------------------------------------------------
            function stringify_style(style) {
                return Object.keys(style).map(function(prop) {
                    return prop + ':' + style[prop];
                }).join(';');
            }
            // ---------------------------------------------------------------------------
            function get_inherit_style(stack) {
                function update_attrs(value) {
                    if (!output[attrs_i]) {
                        output[attrs_i] = {};
                    }
                    try {
                        var new_attrs = JSON.parse(value);
                        if (new_attrs.style) {
                            var new_style = new_attrs.style;
                            var old_style = output[attrs_i].style;
                            new_attrs.style = update_style(new_style, old_style);
                            output[attrs_i] = $.extend(
                                new_attrs,
                                output[attrs_i],
                                {
                                    style: update_style(new_style, old_style)
                                }
                            );
                        } else {
                            output[attrs_i] = $.extend(
                                new_attrs,
                                output[attrs_i]
                            );
                        }
                    } catch (e) {
                        warn('Invalid JSON ' + value);
                    }
                }
                var output = [[], '', ''];
                if (!stack.length) {
                    return output;
                }
                for (var i = stack.length; i--;) {
                    var formatting = stack[i].split(';');
                    if (formatting.length > 5) {
                        var last = formatting.slice(5).join(';');
                        formatting = formatting.slice(0, 5).concat(last);
                    }
                    var style = formatting[0].split(/(-?[@!gbiuso])/g).filter(Boolean);
                    style.forEach(function(s) {
                        if (output[0].indexOf(s) === -1) {
                            output[0].push(s);
                        }
                    });
                    for (var j = 1; j < formatting.length; ++j) {
                        var value = formatting[j].trim();
                        if (value) {
                            if (j === class_i) {
                                if (!output[class_i]) {
                                    output[class_i] = [];
                                }
                                var classes = value.split(/\s+/);
                                output[class_i] = output[class_i].concat(classes);
                            } else if (j === attrs_i) {
                                update_attrs(value);
                            } else if (!output[j]) {
                                output[j] = value;
                            }
                        }
                    }
                }
                return stringify_formatting(output);
            }
            return string.split(re).filter(Boolean).map(function(string) {
                var style;
                if (string.match(/^\[\[/)) {
                    var formatting = string.replace(format_re, '$1');
                    var is_formatting = $.terminal.is_formatting(string);
                    string = string.replace(format_split_re, '');
                    stack.push(formatting);
                    if ($.terminal.nested_formatting.__inherit__) {
                        style = get_inherit_style(stack);
                    } else {
                        style = formatting;
                    }
                    if (!is_formatting) {
                        string += ']';
                    } else {
                        stack.pop();
                    }
                    string = '[[' + style + ']' + string;
                } else {
                    var pop = false;
                    if (string.match(/\]/)) {
                        pop = true;
                    }
                    if (stack.length) {
                        if ($.terminal.nested_formatting.__inherit__) {
                            style = get_inherit_style(stack);
                        } else {
                            style = stack[stack.length - 1];
                        }
                        string = '[[' + style + ']' + string;
                    }
                    if (pop) {
                        stack.pop();
                    } else if (stack.length) {
                        string += ']';
                    }
                }
                return string;
            }).join('');
        },
        // ---------------------------------------------------------------------
        // :: safe function that will render text as it is
        // ---------------------------------------------------------------------
        escape_formatting: function escape_formatting(string) {
            return $.terminal.escape_brackets(string);
        },
        // ---------------------------------------------------------------------
        // :: apply custom formatters only to text
        // ---------------------------------------------------------------------
        apply_formatters: function apply_formatters(string, settings) {
            if (string === "") {
                if (settings && typeof settings.position === 'number') {
                    return ["", settings.position];
                } else {
                    return "";
                }
            }
            function test_lengths(formatter, index, ret, string) {
                if (!formatter.__no_warn__ &&
                    $.terminal.length(ret) !== $.terminal.length(string)) {
                    warn('Your formatter[' + index + '] change length of the string, ' +
                         'you should use [regex, replacement] formatter or function ' +
                         ' that return [replacement, position] instead');
                }
            }
            function should_format(options) {
                if (!settings || !options) {
                    return true;
                }
                var props = ['echo', 'command', 'prompt'];
                var have_any = props.some(function(name) {
                    return options[name] === true;
                });
                if (!have_any) {
                    return true;
                }
                for (var i = props.length; i--;) {
                    var prop = props[i];
                    if (options[prop] === true && settings[prop] === true) {
                        return true;
                    }
                }
                return false;
            }
            settings = settings || {};
            var formatters = settings.formatters || $.terminal.defaults.formatters;
            var i = 0;
            function apply_function_formatter(formatter, input) {
                var options = $.extend({}, settings, {
                    position: input[1]
                });
                var ret = formatter(input[0], options);
                if (typeof ret === 'string') {
                    test_lengths(formatter, i - 1, ret, input[0]);
                    if (typeof ret === 'string') {
                        return [ret, options.position];
                    }
                    return input;
                } else if (is_array(ret) && ret.length === 2) {
                    return ret;
                } else {
                    return input;
                }
            }
            var input;
            if (typeof settings.position === 'number') {
                input = [string, settings.position];
            } else {
                input = [string, 0];
            }
            try {
                var result = formatters.reduce(function(input, formatter) {
                    i++;
                    // __meta__ is for safe formatter that can handle formatters
                    // inside formatters. for other usage we use format_split so one
                    // formatter don't mess with formatter that was previous
                    // on the list
                    if (typeof formatter === 'function' && formatter.__meta__) {
                        return apply_function_formatter(formatter, input);
                    } else {
                        var length = 0;
                        var found_position = false;
                        var splitted = $.terminal.format_split(input[0]);
                        var partials = splitted.map(function(string) {
                            var position;
                            var this_len = text(string).length;
                            // first position that match is used for this partial
                            if (input[1] < length + this_len && !found_position) {
                                position = input[1] - length;
                                found_position = true;
                            } else if (found_position) {
                                // -1 indicate that we will not track position because it
                                // was in one of the previous parial strings
                                position = -1;
                            } else {
                                // initial position for replacers
                                position = input[1];
                            }
                            // length is used to correct position after replace
                            var length_before = length;
                            var result;
                            length += this_len;
                            if ($.terminal.is_formatting(string)) {
                                if (found_position) {
                                    return [string, position];
                                }
                                return [string, -1];
                            } else {
                                if (is_array(formatter)) {
                                    var options = formatter[2] || {};
                                    result = [string, position < 0 ? 0 : position];
                                    if (result[0].match(formatter[0]) &&
                                        should_format(formatter[2])) {
                                        if (options.loop) {
                                            while (result[0].match(formatter[0])) {
                                                result = $.terminal.tracking_replace(
                                                    result[0],
                                                    formatter[0],
                                                    formatter[1],
                                                    result[1]
                                                );
                                            }
                                        } else {
                                            result = $.terminal.tracking_replace(
                                                result[0],
                                                formatter[0],
                                                formatter[1],
                                                result[1]
                                            );
                                        }
                                    }
                                    if (position < 0) {
                                        return [result[0], -1];
                                    }
                                } else if (typeof formatter === 'function') {
                                    result = apply_function_formatter(formatter, [
                                        string, position
                                    ]);
                                }
                                if (typeof result !== 'undefined') {
                                    // correct position becuase it's relative
                                    // to partial and we need global for whole string
                                    if (result[1] !== -1) {
                                        result[1] += length_before;
                                    }
                                    var after_len = text(result[0]).length;
                                    if (after_len !== this_len) {
                                    }
                                    return result;
                                }
                                return [string, -1];
                            }
                        });
                        var position_partial = partials.filter(function(partial) {
                            return partial[1] !== -1;
                        })[0];
                        var string = partials.map(function(partial) {
                            return partial[0];
                        }).join('');
                        var position;
                        if (typeof position_partial === 'undefined') {
                            position = input[1];
                        } else {
                            position = position_partial[1];
                        }
                        // to make sure that output position is not outside the string
                        var max = text(string).length;
                        max += count_selfclosing_formatting(string);
                        if (position > max) {
                            position = max;
                        }
                        if (string === input[0]) {
                            return input;
                        }
                        var before = $.terminal.strip(input[0]);
                        var after = $.terminal.strip(string);
                        if (before === after) {
                            return [string, input[1]];
                        }
                        return [string, position];
                    }
                }, input);
                if (typeof settings.position === 'number') {
                    var codepoint_len = $.terminal.strip(result[0]).length;
                    if ($.terminal.length(result[0]) < codepoint_len) {
                        var position = result[1];
                        position = normalize_position(result[0], position);
                        var max = $.terminal.length(result[0]);
                        if (position > max) {
                            position = max;
                        }
                        result[1] = position;
                    }
                    return result;
                } else {
                    return result[0];
                }
            } catch (e) {
                var msg = 'Error in formatter [' + (i - 1) + ']';
                formatters.splice(i - 1);
                throw new $.terminal.Exception('formatting', msg, e.stack);
            }
        },
        // ---------------------------------------------------------------------
        // :: Replace terminal formatting with html
        // ---------------------------------------------------------------------
        format: function format(str, options) {
            var settings = $.extend({}, {
                linksNoReferrer: false,
                linksNoFollow: false,
                allowedAttributes: [],
                char_width: undefined,
                escape: true,
                anyLinks: false
            }, options || {});
            // -----------------------------------------------------------------
            function filter_attr_names(names) {
                if (names.length && settings.allowedAttributes.length) {
                    return names.filter(function(name) {
                        if (name === 'data-text') {
                            return false;
                        }
                        var allowed = false;
                        var filters = settings.allowedAttributes;
                        for (var i = 0; i < filters.length; ++i) {
                            if (filters[i] instanceof RegExp) {
                                if (filters[i].test(name)) {
                                    allowed = true;
                                    break;
                                }
                            } else if (filters[i] === name) {
                                allowed = true;
                                break;
                            }
                        }
                        return allowed;
                    });
                }
                return [];
            }
            // -----------------------------------------------------------------
            function clean_data(data, text) {
                if (data === '') {
                    return text;
                } else {
                    return data.replace(/&#93;/g, ']')
                        .replace(/>/g, '&gt;').replace(/</g, '&lt;');
                }
            }
            // -----------------------------------------------------------------
            function add_attrs(attrs) {
                if (attrs) {
                    var keys = filter_attr_names(Object.keys(attrs));
                    if (keys.length) {
                        return ' ' + keys.map(function(name) {
                            var value = attrs[name].replace(/"/g, '&quot;');
                            return name + '="' + value + '"';
                        }).join(' ');
                    }
                }
                return '';
            }
            // -----------------------------------------------------------------
            function rel_attr() {
                var rel = ["noopener"];
                if (settings.linksNoReferrer) {
                    rel.unshift("noreferrer");
                }
                if (settings.linksNoFollow) {
                    rel.unshift("nofollow");
                }
                return rel;
            }
            // -----------------------------------------------------------------
            // test if this is valid Path
            // -----------------------------------------------------------------
            function is_path(url) {
                return url.match(/^\.{1,2}\//) ||
                    url.match(/^\//) ||
                    !(url.match(/\//) || url.match(/^[^:]+:/));
            }
            // -----------------------------------------------------------------
            function with_url_validation(fn) {
                return function(url) {
                    if (settings.anyLinks) {
                        return true;
                    }
                    var test = fn(url);
                    if (!test) {
                        warn('Invalid URL ' + url + ' only http(s) ftp and Path ' +
                             'are allowed');
                    }
                    return test;
                };
            }
            // -----------------------------------------------------------------
            var valid_href = with_url_validation(function(url) {
                return url.match(/^((https?|ftp):\/\/|\.{0,2}\/)/) || is_path(url);
            });
            // -----------------------------------------------------------------
            var valid_src = with_url_validation(function(url) {
                return url.match(/^(https?:|blob:|data:)/) || is_path(url);
            });
            // -----------------------------------------------------------------
            function format(s, style, color, background, _class, data_text, text) {
                function pre_process_link() {
                    var result;
                    if (data.match(email_re)) {
                        result = '<a href="mailto:' + data + '"';
                    } else {
                        // only http and ftp links (prevent javascript)
                        // unless user force it with anyLinks option
                        if (!valid_href(data)) {
                            data = '';
                        }
                        result = '<a target="_blank"';
                        if (data) {
                            result += ' href="' + data + '"';
                        }
                        result += ' rel="' + rel_attr().join(' ') + '"';
                    }
                    // make focus to terminal textarea that will enable
                    // terminal when pressing tab and terminal is disabled
                    result += ' tabindex="1000"';
                    return result;
                }
                function pre_process_image() {
                    var result = '<img';
                    if (valid_src(data)) {
                        result += ' src="' + data + '"';
                        if (text) {
                            result += ' alt="' + text + '"';
                        }
                    }
                    return result;
                }
                var attrs;
                if (data_text.match(/;/)) {
                    try {
                        var splitted = data_text.split(';');
                        var str = splitted.slice(1).join(';')
                            .replace(/&nbsp;/g, ' ')
                            .replace(/&lt;/g, '<')
                            .replace(/&gt;/g, '>');
                        if (str.match(/^\s*\{[^}]*\}\s*$/)) {
                            attrs = JSON.parse(str);
                            data_text = splitted[0];
                        }
                    } catch (e) {
                    }
                }
                if (text === '' && !style.match(/@/)) {
                    return ''; //'<span>&nbsp;</span>';
                }
                text = safe(text);
                text = text.replace(/\\\]/g, '&#93;');
                if (settings.escape) {
                    // inside formatting we need to unescape escaped slashes
                    // but this escape is not needed when echo - don't know why
                    text = text.replace(/\\\\/g, '\\');
                }
                var style_str = '';
                if (style.indexOf('b') !== -1) {
                    style_str += 'font-weight:bold;';
                }
                var text_decoration = [];
                if (style.indexOf('u') !== -1) {
                    text_decoration.push('underline');
                }
                if (style.indexOf('s') !== -1) {
                    text_decoration.push('line-through');
                }
                if (style.indexOf('o') !== -1) {
                    text_decoration.push('overline');
                }
                if (text_decoration.length) {
                    style_str += 'text-decoration:' +
                        text_decoration.join(' ') + ';';
                }
                if (style.indexOf('i') !== -1) {
                    style_str += 'font-style:italic;';
                }
                if ($.terminal.valid_color(color)) {
                    style_str += [
                        'color:' + color,
                        '--color:' + color,
                        '--original-color:' + color
                    ].join(';') + ';';
                    if (style.indexOf('!') !== -1) {
                        style_str += '--link-color:' + color + ';';
                    }
                    if (style.indexOf('g') !== -1) {
                        style_str += 'text-shadow:0 0 5px ' + color + ';';
                    }
                }
                if ($.terminal.valid_color(background)) {
                    style_str += [
                        'background-color:' + background,
                        '--background:' + background
                    ].join(';') + ';';
                }
                var data = clean_data(data_text, text);
                var extra = extra_css(text, settings);
                if (extra) {
                    text = wide_characters(text, settings);
                    style_str += extra;
                }
                var result;
                if (style.indexOf('!') !== -1) {
                    result = pre_process_link();
                } else if (style.indexOf('@') !== -1) {
                    result = pre_process_image();
                } else {
                    result = '<span';
                }
                if (attrs && attrs.style) {
                    // merge style attr and colors #617
                    attrs.style = style_str + attrs.style;
                    style_str = '';
                }
                result += add_attrs(attrs);
                if (style_str !== '') {
                    result += ' style="' + style_str + '"';
                }
                if (_class !== '') {
                    result += ' class="' + _class + '"';
                }
                // links and image need data-text attribute cmd click behavior
                // formatter can return links.
                if (style.indexOf('!') !== -1) {
                    result += ' data-text>' + text + '</a>';
                } else if (style.indexOf('@') !== -1) {
                    result += ' data-text/>';
                } else {
                    result += ' data-text="' + data.replace(/"/g, '&quot;') + '">' +
                        '<span>' + text + '</span></span>';
                }
                return result;
            }
            if (typeof str === 'string') {
                // support for formating foo[[u;;]bar]baz[[b;#fff;]quux]zzz
                var splitted = $.terminal.format_split(str);
                str = $.map(splitted, function(text) {
                    if (text === '') {
                        return text;
                    } else if ($.terminal.is_formatting(text)) {
                        // fix &nbsp; inside formatting because encode is called
                        // before format
                        text = text.replace(/\[\[[^\]]+\]/, function(text) {
                            return text.replace(/&nbsp;/g, ' ');
                        });
                        return text.replace(format_parts_re, format);
                    } else {
                        text = safe(text);
                        text = text.replace(/\\\]/, '&#93;');
                        var data = text;
                        var extra = extra_css(text, settings);
                        var prefix;
                        if (extra.length) {
                            text = wide_characters(text, settings);
                            prefix = '<span style="' + extra + '"';
                        } else {
                            prefix = '<span';
                        }
                        return prefix + ' data-text="' + data + '">' + text + '</span>';
                    }
                }).join('');
                return str.replace(/<span><br\s*\/?><\/span>/gi, '<br/>');
            } else {
                return '';
            }
        },
        // ---------------------------------------------------------------------
        // :: Replace brackets with html entities
        // ---------------------------------------------------------------------
        escape_brackets: function escape_brackets(string) {
            return string.replace(/\[/g, '&#91;')
                .replace(/\]/g, '&#93;')
                .replace(/\\/g, '&#92;');
        },
        // ---------------------------------------------------------------------
        // :: complmentary function
        // ---------------------------------------------------------------------
        unescape_brackets: function unescape_brackets(string) {
            return string.replace(/&#91;/g, '[')
                .replace(/&#93;/g, ']')
                .replace(/&#92;/g, '\\');
        },
        // ---------------------------------------------------------------------
        // :: return number of characters without formatting
        // ---------------------------------------------------------------------
        length: function(string, raw) {
            return $.terminal.split_characters(raw ? string : text(string)).length;
        },
        // ---------------------------------------------------------------------
        // :: split characters handling emoji, surogate pairs and combine chars
        // ---------------------------------------------------------------------
        split_characters: function split_characters(string) {
            var result = [];
            var get_next_character = make_next_char_fun(string);
            while (string.length) {
                var chr = get_next_character(string);
                string = string.slice(chr.length);
                result.push(chr);
            }
            return result;
        },
        // ---------------------------------------------------------------------
        // :: return string where array items are in columns padded spaces
        // :: after adding align tabs arr.join('\t\t') looks much better
        // ---------------------------------------------------------------------
        columns: function(array, cols, space) {
            var no_formatting = array.map(function(string) {
                return $.terminal.strip(string);
            });
            var lengths = no_formatting.map(function(string) {
                return strlen(string);
            });
            if (typeof space === 'undefined') {
                space = 4;
            }
            var length = Math.max.apply(null, lengths) + space;
            // we need value - 1 because index starts from 0
            var column_limit = Math.floor(cols / length) - 1;
            if (column_limit < 1) {
                return array.join('\n');
            }
            var lines = [];
            for (var i = 0, len = array.length; i < len; i += column_limit) {
                var line = array.slice(i, i + column_limit);
                var last = line.pop();
                lines.push(line.reduce(function(acc, string) {
                    var stripped = $.terminal.strip(string);
                    var pad = new Array(length - stripped.length + 1).join(' ');
                    acc.push(string + pad);
                    return acc;
                }, []).join('') + last);
            }
            return lines.join('\n');
        },
        // ---------------------------------------------------------------------
        // :: Remove formatting from text
        // ---------------------------------------------------------------------
        strip: function strip(str) {
            if (!$.terminal.have_formatting(str)) {
                return str;
            }
            return $.terminal.format_split(str).map(function(str) {
                if ($.terminal.is_formatting(str)) {
                    str = str.replace(format_parts_re, '$6');
                    return str.replace(/\\([[\]])/g, function(whole, bracket) {
                        return bracket;
                    });
                }
                return str;
            }).join('');
        },
        // ---------------------------------------------------------------------
        // :: Return active terminal
        // ---------------------------------------------------------------------
        active: function active() {
            return terminals.front();
        },
        // ---------------------------------------------------------------------
        // :: Implmentation detail id is always length of terminals Cycle
        // ---------------------------------------------------------------------
        last_id: function last_id() {
            var len = terminals.length();
            return len - 1;
        },
        // ---------------------------------------------------------------------
        // :: Function that works with strings like 'asd' 'asd\' asd' "asd asd"
        // :: asd\ 123 -n -b / [^ ]+ / /\s+/ asd\ a it creates a regex and
        // :: numbers and replaces escape characters in double quotes
        // :: if strict is set to false it only strips single and double quotes
        // :: and escapes spaces
        // ---------------------------------------------------------------------
        parse_argument: function parse_argument(arg, strict) {
            function parse_string(string) {
                // split string to string literals and non-strings
                return string.split(string_re).map(function(string) {
                    // remove quotes if before are even number of slashes
                    // we don't remove slases becuase they are handled by JSON.parse
                    if (string.match(/^['"`]/)) {
                        // fixing regex to match empty string is not worth it
                        if (string === '""' || string === "''" || string === "``") {
                            return '';
                        }
                        var quote = string[0];
                        var re = new RegExp("(\\\\\\\\(?:\\\\\\\\)*)" + quote, "g");
                        string = string.replace(re, '$1').replace(/^[`'"]|[`'"]$/g, '');
                        if (quote === "'") {
                            string = string.replace(/"/g, '\\"');
                        }
                    }
                    string = '"' + string + '"';
                    // use build in function to parse rest of escaped characters
                    return JSON.parse(string);
                }).join('');
            }
            if (strict === false) {
                if (arg[0] === "'" && arg[arg.length - 1] === "'") {
                    return arg.replace(/^'|'$/g, '');
                } else if (arg[0] === "`" && arg[arg.length - 1] === "`") {
                    return arg.replace(/^`|`$/g, '');
                } else if (arg[0] === '"' && arg[arg.length - 1] === '"') {
                    return arg.replace(/^"|"$/g, '').replace(/\\([" ])/g, '$1');
                } else if (arg.match(/\/.*\/[gimy]*$/)) {
                    return arg;
                } else if (arg.match(/['"`]]/)) {
                    // part of arg is in quote
                    return parse_string(arg);
                } else {
                    return arg.replace(/\\ /g, ' ');
                }
            }
            if (arg === 'true') {
                return true;
            } else if (arg === 'false') {
                return false;
            }
            var regex = arg.match(re_re);
            if (regex) {
                return new RegExp(regex[1], regex[2]);
            } else if (arg.match(/['"`]/)) {
                return parse_string(arg);
            } else if (arg.match(/^-?[0-9]+$/)) {
                return parseInt(arg, 10);
            } else if (arg.match(float_re)) {
                return parseFloat(arg);
            } else {
                return arg.replace(/\\(['"() ])/g, '$1');
            }
        },
        // ---------------------------------------------------------------------
        // :: function split and parse arguments
        // ---------------------------------------------------------------------
        parse_arguments: function parse_arguments(string) {
            return $.map(string.match(command_re) || [], $.terminal.parse_argument);
        },
        // ---------------------------------------------------------------------
        // :: Function split and strips single and double quotes
        // :: and escapes spaces
        // ---------------------------------------------------------------------
        split_arguments: function split_arguments(string) {
            return $.map(string.match(command_re) || [], function(arg) {
                return $.terminal.parse_argument(arg, false);
            });
        },
        // ---------------------------------------------------------------------
        // :: Function that returns an object {name,args}. Arguments are parsed
        // :: using the function parse_arguments
        // ---------------------------------------------------------------------
        parse_command: function parse_command(string) {
            return process_command(string, $.terminal.parse_argument);
        },
        // ---------------------------------------------------------------------
        // :: Same as parse_command but arguments are parsed using split_arguments
        // ---------------------------------------------------------------------
        split_command: function split_command(string) {
            return process_command(string, function(arg) {
                return $.terminal.parse_argument(arg, false);
            });
        },
        // ---------------------------------------------------------------------
        // :; function that parse arguments like yargs library
        // ---------------------------------------------------------------------
        parse_options: function parse_options(arg, options) {
            var settings = $.extend({}, {
                boolean: []
            }, options);
            if (typeof arg === 'string') {
                return parse_options($.terminal.split_arguments(arg), options);
            }
            var result = {
                _: []
            };
            function token(value) {
                this.value = value;
            }
            var rest = arg.reduce(function(acc, arg) {
                var str = typeof arg === 'string' ? arg : '';
                if (str.match(/^--?[^-]/) && acc instanceof token) {
                    result[acc.value] = true;
                }
                if (str.match(/^--[^-]/)) {
                    var name = str.replace(/^--/, '');
                    if (settings.boolean.indexOf(name) === -1) {
                        return new token(name);
                    } else {
                        result[name] = true;
                    }
                } else if (str.match(/^-[^-]/)) {
                    var single = str.replace(/^-/, '').split('');
                    if (settings.boolean.indexOf(single.slice(-1)[0]) === -1) {
                        var last = single.pop();
                    }
                    single.forEach(function(single) {
                        result[single] = true;
                    });
                    if (last) {
                        return new token(last);
                    }
                } else if (acc instanceof token) {
                    result[acc.value] = arg;
                } else if (arg) {
                    result._.push(arg);
                }
                return null;
            }, null);
            if (rest instanceof token) {
                result[rest.value] = true;
            }
            return result;
        },
        // ---------------------------------------------------------------------
        // :: function executed for each text inside [[ .... ]] in echo
        // ---------------------------------------------------------------------
        extended_command: function extended_command(term, string, options) {
            var settings = $.extend({
                invokeMethods: false
            }, options);
            var deferred = new $.Deferred();
            try {
                change_hash = false;
                var m = string.match(extended_command_re);
                if (m) {
                    if (!settings.invokeMethods) {
                        warn('To invoke terminal or cmd methods you need to enable ' +
                             'invokeMethods option');
                        deferred.reject();
                    } else {
                        string = m[1];
                        var obj = m[2] === 'terminal' ? term : term.cmd();
                        var fn = m[3];
                        try {
                            var args = eval('[' + m[4] + ']');
                            if (!obj[fn]) {
                                term.error('Unknow function ' + fn);
                            } else {
                                var ret = obj[fn].apply(term, args);
                                if (ret && ret.then) {
                                    return ret;
                                }
                            }
                            deferred.resolve();
                        } catch (e) {
                            term.error('Invalid invocation in ' +
                                       $.terminal.escape_brackets(string));
                            deferred.reject();
                        }
                    }
                } else {
                    return term.exec(string, true).done(function() {
                        change_hash = true;
                    });
                }
            } catch (e) {
                // error is process in exec
                deferred.reject();
            }
            return deferred.promise();
        },
        // ---------------------------------------------------------------------
        // :: ES6 iterator for a given string that handle emoji and formatting
        // ---------------------------------------------------------------------
        iterator: function(string) {
            function formatting(string) {
                if ($.terminal.is_formatting(string)) {
                    if (string.match(/\]\\\]/)) {
                        string = string.replace(/\]\\\]/g, ']\\\\]');
                    }
                }
                return string;
            }
            if (typeof Symbol === 'function' && typeof Symbol.iterator === 'symbol') {
                var len = $.terminal.length(string);
                var i = 0;
                var obj = {};
                obj[Symbol.iterator] = function() {
                    return {
                        next: function() {
                            if (i < len) {
                                var text = $.terminal.substring(string, i, i + 1);
                                i++;
                                return {
                                    value: formatting(text)
                                };
                            } else {
                                return {
                                    done: true
                                };
                            }
                        }
                    };
                };
                return obj;
            }
        },
        // ---------------------------------------------------------------------
        // :: object that can be used in string methods intead of regex
        // ---------------------------------------------------------------------
        formatter: new (function() {
            try {
                this[Symbol.split] = function(string) {
                    return $.terminal.format_split(string);
                };
                this[Symbol.match] = function(string) {
                    return string.match(format_re);
                };
                this[Symbol.replace] = function(string, replacer) {
                    return string.replace(format_parts_re, replacer);
                };
                this[Symbol.search] = function(string) {
                    return string.search(format_re);
                };
            } catch (e) {
            }
        })(),
        // ---------------------------------------------------------------------
        // :: helper function that add formatter before nested_formatting
        // ---------------------------------------------------------------------
        new_formatter: function(formatter) {
            var formatters = $.terminal.defaults.formatters;
            for (var i = 0; i < formatters.length; ++i) {
                if (formatters[i] === $.terminal.nested_formatting) {
                    formatters.splice(i, 0, formatter);
                    return;
                }
            }
            formatters.push(formatter);
        }
    };
    // -------------------------------------------------------------------------
    $.terminal.Exception = function Terminal_Exception(type, message, stack) {
        if (arguments.length === 1) {
            this.message = arguments[0];
            this.type = 'TERMINAL';
        } else {
            this.type = type;
            this.message = message;
            if (stack) {
                this.stack = stack;
            }
        }
    };
    $.terminal.Exception.prototype = new Error();
    $.terminal.Exception.prototype.toString = function() {
        return this.message + '\n' + this.stack;
    };
    // -----------------------------------------------------------------------
    // Helper plugins and functions
    // -----------------------------------------------------------------------
    $.fn.visible = function() {
        return this.css('visibility', 'visible');
    };
    $.fn.hidden = function() {
        return this.css('visibility', 'hidden');
    };
    // -----------------------------------------------------------------------
    var warnings = [];
    function warn(msg) {
        msg = '[jQuery Terminal] ' + msg;
        if (warnings.indexOf(msg) === -1) {
            warnings.push(msg);
            /* eslint-disable */
            if (console) {
                if (console.warn) {
                    console.warn(msg);
                } else if (console.log) {
                    console.log(msg);
                }
                /* eslint-enable */
            } else {
                // prevent catching in outer try..catch
                setTimeout(function() {
                    throw new Error('WARN: ' + msg);
                }, 0);
            }
        }
    }
    // -----------------------------------------------------------------------
    // JSON-RPC CALL
    // -----------------------------------------------------------------------
    var ids = {}; // list of url based ids of JSON-RPC
    $.jrpc = function(url, method, params, success, error) {
        var deferred = new $.Deferred();
        var options;
        if ($.isPlainObject(url)) {
            options = url;
        } else {
            options = {
                url: url,
                method: method,
                params: params,
                success: success,
                error: error
            };
        }
        function validJSONRPC(response) {
            return $.isNumeric(response.id) &&
                (typeof response.result !== 'undefined' ||
                 typeof response.error !== 'undefined');
        }
        ids[options.url] = ids[options.url] || 0;
        var request = {
            'jsonrpc': '2.0',
            'method': options.method,
            'params': options.params,
            'id': ++ids[options.url]
        };
        $.ajax({
            url: options.url,
            beforeSend: function beforeSend(jxhr, settings) {
                if (is_function(options.request)) {
                    options.request(jxhr, request);
                }
                settings.data = JSON.stringify(request);
            },
            success: function success(response, status, jqXHR) {
                var content_type = jqXHR.getResponseHeader('Content-Type');
                if (!content_type.match(/(application|text)\/json/)) {
                    warn('Response Content-Type is neither application/json' +
                         ' nor text/json');
                }
                var json;
                try {
                    json = JSON.parse(response);
                } catch (e) {
                    if (options.error) {
                        options.error(jqXHR, 'Invalid JSON', e);
                    } else {
                        throw new $.terminal.Exception('JSON', 'Invalid JSON', e.stack);
                    }
                    deferred.reject({message: 'Invalid JSON', response: response});
                    return;
                }
                if (is_function(options.response)) {
                    options.response(jqXHR, json);
                }
                if (validJSONRPC(json) || options.method === 'system.describe') {
                    // don't catch errors in success callback
                    if (options.success) {
                        options.success(json, status, jqXHR);
                    }
                    deferred.resolve(json);
                } else {
                    if (options.error) {
                        options.error(jqXHR, 'Invalid JSON-RPC');
                    }
                    deferred.reject({message: 'Invalid JSON-RPC', response: response});
                }
            },
            error: options.error,
            contentType: 'application/json',
            dataType: 'text',
            async: true,
            cache: false,
            // timeout: 1,
            type: 'POST'
        });
        return deferred.promise();
    };
    // -----------------------------------------------------------------------
    $.rpc = function(url, method, params) {
        var deferred = new $.Deferred();
        function success(res) {
            if (res.error) {
                deferred.reject(res.error);
            } else {
                deferred.resolve(res.result);
            }
        }
        function error(jqXHR, status, message) {
            deferred.reject({message: message});
        }
        $.jrpc(url, method, params, success, error);
        return deferred.promise();
    };
    // -----------------------------------------------------------------------
    function terminal_ready(term) {
        return !!(term.closest('body').length &&
                  term.is(':visible') &&
                  term.find('.cmd-prompt').length);
    }
    // -----------------------------------------------------------------------
    // :: Create fake terminal to calcualte the dimention of one character
    // :: this will make terminal work if terminal div is not added to the
    // :: DOM at init like with:
    // :: $('<div/>').terminal().echo('foo bar').appendTo('body');
    // -----------------------------------------------------------------------
    function get_char_size(term) {
        var rect;
        if (terminal_ready(term)) {
            var $prompt = term.find('.cmd-prompt').clone().css({
                visiblity: 'hidden',
                position: 'absolute'
            });
            $prompt.appendTo(term.find('.cmd')).html('&nbsp;');
            rect = $prompt[0].getBoundingClientRect();
            $prompt.remove();
        } else {
            var temp = $('<div class="terminal terminal-temp"><div class="terminal-' +
                         'wrapper"><div class="terminal-output"><div><div class="te' +
                         'rminal-line" style="float: left"><span>&nbsp;</span></div' +
                         '></div></div></div>').appendTo('body');
            temp.addClass(term.attr('class')).attr('id', term.attr('id'));
            if (term) {
                var style = term.attr('style');
                if (style) {
                    style = style.split(/\s*;\s*/).filter(function(s) {
                        return !s.match(/display\s*:\s*none/i);
                    }).join(';');
                    temp.attr('style', style);
                }
            }
            rect = temp.find('.terminal-line')[0].getBoundingClientRect();
        }
        var result = {
            width: rect.width,
            height: rect.height
        };
        if (temp) {
            temp.remove();
        }
        return result;
    }
    // -----------------------------------------------------------------------
    // :: calculate numbers of characters
    // -----------------------------------------------------------------------
    function get_num_chars(terminal, char_size) {
        var width = terminal.find('.terminal-fill').width();
        var result = Math.floor(width / char_size.width);
        // random number to not get NaN in node.js but big enough to
        // not wrap exception
        return result || 1000;
    }
    // -----------------------------------------------------------------------
    // :: Calculate number of lines that fit without scroll
    // -----------------------------------------------------------------------
    function get_num_rows(terminal, char_size) {
        var height = terminal.find('.terminal-fill').height();
        return Math.floor(height / char_size.height);
    }
    // -----------------------------------------------------------------------
    function all(array, fn) {
        var same = array.filter(function(item) {
            return item[fn]() === item;
        });
        return same.length === array.length;
    }
    // -----------------------------------------------------------------------
    function string_case(string) {
        var array = string.split('');
        if (all(array, 'toLowerCase')) {
            return 'lower';
        } else if (all(array, 'toUpperCase')) {
            return 'upper';
        } else {
            return 'mixed';
        }
    }
    // -----------------------------------------------------------------------
    function same_case(string) {
        return string_case(string) !== 'mixed';
    }
    // -----------------------------------------------------------------------
    // fix for jQuery bug
    function is_function(object) {
        return get_type(object) === 'function';
    }
    // -----------------------------------------------------------------------
    function is_promise(object) {
        return is_function(object && (object.then || object.done));
    }
    // -----------------------------------------------------------------------
    if (!Array.isArray) {
        Array.isArray = function(arg) {
            return Object.prototype.toString.call(arg) === '[object Array]';
        };
    }
    // -----------------------------------------------------------------------
    function is_array(object) {
        return Array.isArray(object);
    }
    // -----------------------------------------------------------------------
    function get_type(object) {
        if (typeof object === 'function') {
            return 'function';
        }
        if (object === null) {
            return object + '';
        }
        if (Array.isArray(object)) {
            return 'array';
        }
        if (typeof object === 'object') {
            return 'object';
        }
        return typeof object;
    }
    // -----------------------------------------------------------------------
    // :: TERMINAL PLUGIN CODE
    // -----------------------------------------------------------------------
    var version_set = !$.terminal.version.match(/^\{\{/);
    var copyright = 'Copyright (c) 2011-2021 Jakub T. Jankiewicz ' +
        '<https://jcubic.pl/me>';
    var version_string = version_set ? ' v. ' + $.terminal.version : ' ';
    // regex is for placing version string aligned to the right
    var reg = new RegExp(' {' + version_string.length + '}$');
    var name_ver = 'jQuery Terminal Emulator' +
        (version_set ? version_string : '');
    // -----------------------------------------------------------------------
    // :: Terminal Signatures
    // -----------------------------------------------------------------------
    var signatures = [
        ['jQuery Terminal', '(c) 2011-2021 jcubic'],
        [name_ver, copyright.replace(/^Copyright | *<.*>/g, '')],
        [name_ver, copyright.replace(/^Copyright /, '')],
        [
            '      _______                 ________                        __',
            '     / / _  /_ ____________ _/__  ___/______________  _____  / /',
            ' __ / / // / // / _  / _/ // / / / _  / _/     / /  \\/ / _ \\/ /',
            '/  / / // / // / ___/ // // / / / ___/ // / / / / /\\  / // / /__',
            '\\___/____ \\\\__/____/_/ \\__ / /_/____/_//_/_/_/_/_/  \\/\\__\\_\\___/',
            '         \\/          /____/                                   '
                .replace(reg, ' ') + version_string,
            copyright
        ],
        [
            '      __ _____                     ________                            ' +
                '  __',
            '     / // _  /__ __ _____ ___ __ _/__  ___/__ ___ ______ __ __  __ ___ ' +
                ' / /',
            ' __ / // // // // // _  // _// // / / // _  // _//     // //  \\/ // _ ' +
                '\\/ /',
            '/  / // // // // // ___// / / // / / // ___// / / / / // // /\\  // // ' +
                '/ /__',
            '\\___//____ \\\\___//____//_/ _\\_  / /_//____//_/ /_/ /_//_//_/ /_/ \\' +
                '__\\_\\___/',
            ('          \\/              /____/                                     ' +
             '     ').replace(reg, '') + version_string,
            copyright
        ]
    ];
    // -----------------------------------------------------------------------
    // :: Default options
    // -----------------------------------------------------------------------
    $.terminal.nested_formatting.__meta__ = true;
    // if set to false nested formatting will not inherit styles colors and attribues
    $.terminal.nested_formatting.__inherit__ = true;
    // nested formatting will always return different length so we silent the warning
    $.terminal.nested_formatting.__no_warn__ = true;
    $.terminal.defaults = {
        prompt: '> ',
        history: true,
        exit: true,
        clear: true,
        enabled: true,
        maskChar: '*',
        wrap: true,
        checkArity: true,
        raw: false,
        tabindex: 1,
        invokeMethods: false,
        exceptionHandler: null,
        pauseEvents: true,
        softPause: false,
        mousewheel: null,
        touchscroll: null,
        memory: false,
        cancelableAjax: true,
        processArguments: true,
        linksNoReferrer: false,
        useCache: true,
        anyLinks: false,
        linksNoFollow: false,
        processRPCResponse: null,
        completionEscape: true,
        onCommandChange: null,
        mobileDelete: is_mobile,
        onPositionChange: null,
        convertLinks: true,
        extra: {},
        tabs: 4,
        historySize: 60,
        scrollObject: null,
        historyState: false,
        importHistory: false,
        historyFilter: null,
        echoCommand: true,
        scrollOnEcho: true,
        login: null,
        outputLimit: -1,
        formatters: [$.terminal.nested_formatting],
        unixFormatting: {
            escapeBrackets: false,
            ansiParser: {},
            ansiArt: false
        },
        onAjaxError: null,
        pasteImage: true,
        scrollBottomOffset: 20,
        wordAutocomplete: true,
        caseSensitiveAutocomplete: true,
        caseSensitiveSearch: true,
        clickTimeout: 200,
        holdTimeout: 400,
        holdRepeatTimeout: 200,
        repeatTimeoutKeys: [],
        mobileIngoreAutoSpace: [],
        request: $.noop,
        response: $.noop,
        describe: 'procs',
        onRPCError: null,
        keymap: null,
        doubleTab: null,
        doubleTabEchoCommand: false,
        completion: false,
        onInit: $.noop,
        onClear: $.noop,
        onBlur: $.noop,
        onFocus: $.noop,
        onTerminalChange: $.noop,
        onExit: $.noop,
        onPush: $.noop,
        onPop: $.noop,
        keypress: $.noop,
        keydown: $.noop,
        renderHandler: null,
        onAfterRedraw: $.noop,
        onEchoCommand: $.noop,
        onPaste: $.noop,
        onFlush: $.noop,
        onBeforeCommand: null,
        onAfterCommand: null,
        onBeforeEcho: null,
        onAfterEcho: null,
        onBeforeLogin: null,
        onAfterLogout: null,
        onBeforeLogout: null,
        allowedAttributes: ['title', /^aria-/, 'id', /^data-/],
        strings: {
            comletionParameters: 'From version 1.0.0 completion function need to' +
                ' have two arguments',
            wrongPasswordTryAgain: 'Wrong username or password try again!',
            wrongPassword: 'Wrong username or password!',
            ajaxAbortError: 'Error while aborting ajax call!',
            wrongArity: "Wrong number of arguments. Function '%s' expects %s got" +
                ' %s!',
            commandNotFound: "Command '%s' Not Found!",
            oneRPCWithIgnore: 'You can use only one rpc with describe == false ' +
                'or rpc without system.describe',
            oneInterpreterFunction: "You can't use more than one function (rpc " +
                'without system.describe or with option describe == false count' +
                 's as one)',
            loginFunctionMissing: "You didn't specify a login function",
            noTokenError: 'Access denied (no token)',
            serverResponse: 'Server responded',
            wrongGreetings: 'Wrong value of greetings parameter',
            notWhileLogin: "You can't call `%s' function while in login",
            loginIsNotAFunction: 'Authenticate must be a function',
            canExitError: "You can't exit from main interpreter",
            invalidCompletion: 'Invalid completion',
            invalidSelector: 'Sorry, but terminal said that you use invalid ' +
                'selector!',
            invalidTerminalId: 'Invalid Terminal ID',
            login: 'login',
            password: 'password',
            recursiveLoop: 'Recursive loop in echo detected, skip',
            notAString: '%s function: argument is not a string',
            redrawError: 'Internal error, wrong position in cmd redraw',
            invalidStrings: 'Command %s have unclosed strings',
            defunctTerminal: "You can't call method on terminal that was destroyed"
        }
    };
    // -------------------------------------------------------------------------
    // :: All terminal globals
    // -------------------------------------------------------------------------
    var requests = []; // for canceling on CTRL+D
    var terminals = new Cycle(); // list of terminals global in this scope
    // state for all terminals, terminals can't have own array fo state because
    // there is only one popstate event
    var save_state = []; // hold objects returned by export_view by history API
    var hash_commands;
    var change_hash = false; // don't change hash on Init
    var fire_hash_change = true;
    var first_instance = true; // used by history state
    $.fn.terminal = function(init_interpreter, options) {
        function StorageHelper(memory) {
            if (memory) {
                this.storage = {};
            }
            this.set = function(key, value) {
                if (memory) {
                    this.storage[key] = value;
                } else {
                    $.Storage.set(key, value);
                }
            };
            this.get = function(key) {
                if (memory) {
                    return this.storage[key];
                } else {
                    return $.Storage.get(key);
                }
            };
            this.remove = function(key) {
                if (memory) {
                    delete this.storage[key];
                } else {
                    $.Storage.remove(key);
                }
            };
        }
        // ---------------------------------------------------------------------
        // :: helper function
        // ---------------------------------------------------------------------
        function get_processed_command(command) {
            if ($.terminal.unclosed_strings(command)) {
                var string = $.terminal.escape_brackets(command);
                var message = sprintf(strings().invalidStrings, "`" + string + "`");
                throw new $.terminal.Exception(message);
            } else if (is_function(settings.processArguments)) {
                return process_command(command, settings.processArguments);
            } else if (settings.processArguments) {
                return $.terminal.parse_command(command);
            } else {
                return $.terminal.split_command(command);
            }
        }
        // ---------------------------------------------------------------------
        // :: helper function that use option to render objects
        // ---------------------------------------------------------------------
        function preprocess_value(value, options) {
            if ($.terminal.Animation && value instanceof $.terminal.Animation) {
                value.start(self);
                return false;
            }
            if (is_function(settings.renderHandler)) {
                var ret = settings.renderHandler.call(self, value, options, self);
                if (ret === false) {
                    return false;
                }
                if (typeof ret === 'string' || is_node(ret) || is_promise(ret)) {
                    return ret;
                } else {
                    return value;
                }
            }
            return value;
        }
        // ---------------------------------------------------------------------
        // :: call when line is out of view when outputLimit is used
        // :: NOTE: it's not called when less plugin is used onClear is called
        // :: instead because less call term::clear() after export old view
        // ---------------------------------------------------------------------
        function unmount(node) {
            var index = node.data('index');
            var line = lines[index];
            var options = line[1];
            if (is_function(options.unmount)) {
                options.unmount.call(self, node);
            }
        }
        // ---------------------------------------------------------------------
        // :: helper function used in render and in update
        // ---------------------------------------------------------------------
        function prepare_render(value, options) {
            if (is_node(value)) {
                var settings = $.extend({}, options, {
                    raw: true,
                    finalize: function(div) {
                        div.find('.terminal-render-item').replaceWith(value);
                        if (options && is_function(options.finalize)) {
                            options.finalize(div, self);
                        }
                    }
                });
                return ['<div class="terminal-render-item"/>', settings];
            }
        }
        // ---------------------------------------------------------------------
        // :: helper function that renders DOM nodes and jQuery objects
        // ---------------------------------------------------------------------
        function render(value, options) {
            var ret = prepare_render(value, options);
            if (ret) {
                self.echo.apply(self, ret);
                return true;
            }
        }
        // ---------------------------------------------------------------------
        function get_node(index) {
            return output.find('[data-index=' + index + ']');
        }
        // ---------------------------------------------------------------------
        // :: test if object can be rendered
        // ---------------------------------------------------------------------
        function is_node(object) {
            return object instanceof $.fn.init || object instanceof Element;
        }
        // ---------------------------------------------------------------------
        // :: Display object on terminal
        // ---------------------------------------------------------------------
        function display_object(object) {
            object = preprocess_value(object);
            if (object === false) {
                return;
            }
            if (render(object)) {
                return;
            }
            if (typeof object === 'string') {
                self.echo(object);
            } else if (is_array(object)) {
                self.echo($.map(object, function(object) {
                    return JSON.stringify(object);
                }).join(' '));
            } else if (typeof object === 'object') {
                self.echo(JSON.stringify(object));
            } else {
                self.echo(object);
            }
        }
        // ---------------------------------------------------------------------
        // :: Display line code in the file if line numbers are present
        // ---------------------------------------------------------------------
        function print_line(url_spec, cols) {
            var re = /(.*):([0-9]+):([0-9]+)$/;
            // google chrome have line and column after filename
            var m = url_spec.match(re);
            if (m) {
                // TODO: do we need to call pause/resume or return promise?
                self.pause(settings.softPause);
                $.get(m[1], function(response) {
                    var file = m[1];
                    var code = response.split('\n');
                    var n = +m[2] - 1;
                    var start = n > 2 ? n - 2 : 0;
                    var lines = code.slice(start, n + 3).map(function(line, i) {
                        var prefix = '[' + (n + i - 1) + ']: ';
                        var limit = cols - prefix.length - 4;
                        if (line.length > limit) {
                            line = line.substring(0, limit) + '...';
                        }
                        if (n > 2 ? i === 2 : i === n) {
                            line = '[[;#f00;]' +
                                $.terminal.escape_brackets(line) + ']';
                        }
                        return prefix + line;
                    }).filter(Boolean).join('\n');
                    if (lines.length) {
                        self.echo('[[b;white;]' + file + ']');
                        self.echo(lines).resume();
                    }
                }, 'text');
            }
        }
        // ---------------------------------------------------------------------
        // :: Helper function
        // ---------------------------------------------------------------------
        function display_json_rpc_error(error) {
            if (is_function(settings.onRPCError)) {
                settings.onRPCError.call(self, error);
            } else {
                self.error('&#91;RPC&#93; ' + error.message);
                if (error.error && error.error.message) {
                    error = error.error;
                    // more detailed error message
                    var msg = '\t' + error.message;
                    if (error.file) {
                        msg += ' in file "' + error.file.replace(/.*\//, '') + '"';
                    }
                    if (error.at) {
                        msg += ' at line ' + error.at;
                    }
                    self.error(msg);
                }
            }
        }
        // ---------------------------------------------------------------------
        // :: Create interpreter function from url string
        // ---------------------------------------------------------------------
        function make_basic_json_rpc(url, auth) {
            var interpreter = function(method, params) {
                self.pause(settings.softPause);
                $.jrpc({
                    url: url,
                    method: method,
                    params: params,
                    request: function(jxhr, request) {
                        try {
                            settings.request.call(self, jxhr, request, self);
                        } catch (e) {
                            display_exception(e, 'USER');
                        }
                    },
                    response: function(jxhr, response) {
                        try {
                            settings.response.call(self, jxhr, response, self);
                        } catch (e) {
                            display_exception(e, 'USER');
                        }
                    },
                    success: function success(json) {
                        if (json.error) {
                            display_json_rpc_error(json.error);
                        } else if (is_function(settings.processRPCResponse)) {
                            settings.processRPCResponse.call(self, json.result, self);
                        } else if (json.result !== null) {
                            display_object(json.result);
                        }
                        self.resume();
                    },
                    error: ajax_error
                });
            };
            // this is the interpreter function
            return function(command, terminal) {
                if (command === '') {
                    return;
                }
                try {
                    command = get_processed_command(command);
                } catch (e) {
                    // exception can be thrown on invalid regex
                    display_exception(e, 'TERMINAL (get_processed_command)');
                    return;
                    // throw e; // this will show stack in other try..catch
                }
                if (!auth || command.name === 'help') {
                    // allows to call help without a token
                    interpreter(command.name, command.args);
                } else {
                    var token = terminal.token(true);
                    if (token) {
                        interpreter(command.name, [token].concat(command.args));
                    } else {
                        // should never happen
                        terminal.error('&#91;AUTH&#93; ' + strings().noTokenError);
                    }
                }
            };
        }
        // ---------------------------------------------------------------------
        // :: Create interpreter function from Object. If the value is object
        // :: it will create nested interpreters
        // ---------------------------------------------------------------------
        function make_object_interpreter(object, arity, login, fallback) {
            // function that maps commands to object methods
            // it keeps terminal context
            return function(user_command, terminal) {
                if (user_command === '') {
                    return;
                }
                var command;
                try {
                    command = get_processed_command(user_command);
                } catch (e) {
                    // exception can be thrown on invalid regex
                    if (is_function(settings.exception)) {
                        settings.exception(e, self);
                    } else {
                        self.error('Error: ' + (e.message || e));
                    }
                    return;
                    // throw e; // this will show stack in other try..catch
                }
                var val = object[command.name];
                var type = get_type(val);
                if (type === 'function') {
                    if (arity && val.length !== command.args.length) {
                        self.error(
                            '&#91;Arity&#93; ' +
                                sprintf(
                                    strings().wrongArity,
                                    command.name,
                                    val.length,
                                    command.args.length
                                )
                        );
                    } else {
                        return val.apply(self, command.args);
                    }
                } else if (type === 'object' || type === 'string') {
                    var commands = [];
                    if (type === 'object') {
                        commands = Object.keys(val);
                        val = make_object_interpreter(
                            val,
                            arity,
                            login
                        );
                    }
                    terminal.push(val, {
                        prompt: command.name + '> ',
                        name: command.name,
                        completion: type === 'object' ? commands : undefined
                    });
                } else if (is_function(fallback)) {
                    fallback(user_command, self);
                } else if (is_function(settings.onCommandNotFound)) {
                    settings.onCommandNotFound.call(self, user_command, self);
                } else {
                    terminal.error(sprintf(strings().commandNotFound, command.name));
                }
            };
        }
        // ---------------------------------------------------------------------
        function ajax_error(xhr, status, error) {
            self.resume(); // onAjaxError can use pause/resume call it first
            if (is_function(settings.onAjaxError)) {
                settings.onAjaxError.call(self, xhr, status, error);
            } else if (status !== 'abort') {
                self.error('&#91;AJAX&#93; ' + status + ' - ' +
                           strings().serverResponse + ':\n' +
                           $.terminal.escape_brackets(xhr.responseText));
            }
        }
        // ---------------------------------------------------------------------
        // :: function create interpreter object based on JSON-RPC meta data
        // ---------------------------------------------------------------------
        function make_json_rpc_object(url, auth, success) {
            function jrpc_success(json) {
                if (json.error) {
                    display_json_rpc_error(json.error);
                } else if (is_function(settings.processRPCResponse)) {
                    settings.processRPCResponse.call(self, json.result, self);
                } else {
                    display_object(json.result);
                }
                self.resume();
            }
            function jrpc_request(jxhr, request) {
                try {
                    settings.request.call(self, jxhr, request, self);
                } catch (e) {
                    display_exception(e, 'USER');
                }
            }
            function jrpc_response(jxhr, response) {
                try {
                    settings.response.call(self, jxhr, response, self);
                } catch (e) {
                    display_exception(e, 'USER');
                }
            }
            function response(response) {
                var procs = response;
                // we check if it's false before we call this function but
                // it don't hurt to be explicit here
                if (settings.describe !== false && settings.describe !== '') {
                    settings.describe.split('.').forEach(function(field) {
                        procs = procs[field];
                    });
                }
                if (procs && procs.length) {
                    var interpreter_object = {};
                    $.each(procs, function(_, proc) {
                        if ($.isPlainObject(proc) && typeof proc.name === 'string') {
                            interpreter_object[proc.name] = function() {
                                var append = auth && proc.name !== 'help';
                                var args = Array.prototype.slice.call(arguments);
                                var args_len = args.length + (append ? 1 : 0);
                                if (settings.checkArity && proc.params &&
                                    proc.params.length !== args_len) {
                                    self.error(
                                        '&#91;Arity&#93; ' +
                                            sprintf(
                                                strings().wrongArity,
                                                proc.name,
                                                proc.params.length,
                                                args_len
                                            )
                                    );
                                } else {
                                    self.pause(settings.softPause);
                                    if (append) {
                                        var token = self.token(true);
                                        if (token) {
                                            args = [token].concat(args);
                                        } else {
                                            self.error('&#91;AUTH&#93; ' +
                                                       strings().noTokenError);
                                        }
                                    }
                                    $.jrpc({
                                        url: url,
                                        method: proc.name,
                                        params: args,
                                        request: jrpc_request,
                                        response: jrpc_response,
                                        success: jrpc_success,
                                        error: ajax_error
                                    });
                                }
                            };
                        }
                    });
                    var login = typeof auth === 'string' ? auth : 'login';
                    interpreter_object.help = interpreter_object.help || function(fn) {
                        if (typeof fn === 'undefined') {
                            var names = procs.map(function(proc) {
                                return proc.name;
                            }).join(', ') + ', help';
                            self.echo('Available commands: ' + names);
                        } else {
                            var found = false;
                            $.each(procs, function(_, proc) {
                                if (proc.name === fn) {
                                    found = true;
                                    var msg = '';
                                    msg += '[[bu;;]' + proc.name + ']';
                                    if (proc.params) {
                                        var params = proc.params;
                                        if (auth && proc.name !== login) {
                                            params = params.slice(1);
                                        }
                                        msg += ' ' + params.join(' ');
                                    }
                                    if (proc.help) {
                                        msg += '\n' + proc.help;
                                    }
                                    self.echo(msg);
                                    return false;
                                }
                            });
                            if (!found) {
                                if (fn === 'help') {
                                    self.echo('[[bu;;]help] [method]\ndisplay help ' +
                                              'for the method or list of methods if not' +
                                              ' specified');
                                } else {
                                    var msg = 'Method `' + fn + "' not found ";
                                    self.error(msg);
                                }
                            }
                        }
                    };
                    success(interpreter_object);
                } else {
                    success(null);
                }
            }
            return $.jrpc({
                url: url,
                method: 'system.describe',
                params: [],
                success: response,
                request: jrpc_request,
                response: jrpc_response,
                error: function error() {
                    success(null);
                }
            });
        }
        // ---------------------------------------------------------------------
        // :: function create interpeter function and call finalize with
        // :: interpreter and optional completion
        // ---------------------------------------------------------------------
        function make_interpreter(user_intrp, login, finalize) {
            finalize = finalize || $.noop;
            var type = get_type(user_intrp);
            var object;
            var result = {};
            var rpc_count = 0; // only one rpc can be use for array
            var fn_interpreter;
            if (type === 'array') {
                object = {};
                // recur will be called when previous acync call is finished
                (function recur(interpreters, success) {
                    if (interpreters.length) {
                        var first = interpreters[0];
                        var rest = interpreters.slice(1);
                        var type = get_type(first);
                        if (type === 'string') {
                            self.pause(settings.softPause);
                            if (settings.describe === false) {
                                if (++rpc_count === 1) {
                                    fn_interpreter = make_basic_json_rpc(first, login);
                                } else {
                                    self.error(strings().oneRPCWithIgnore);
                                }
                                recur(rest, success);
                            } else {
                                make_json_rpc_object(first, login, function(new_obj) {
                                    if (new_obj) {
                                        $.extend(object, new_obj);
                                    } else if (++rpc_count === 1) {
                                        fn_interpreter = make_basic_json_rpc(
                                            first,
                                            login
                                        );
                                    } else {
                                        self.error(strings().oneRPCWithIgnore);
                                    }
                                    self.resume();
                                    recur(rest, success);
                                });
                            }
                        } else if (type === 'function') {
                            if (fn_interpreter) {
                                self.error(strings().oneInterpreterFunction);
                            } else {
                                fn_interpreter = first;
                            }
                            recur(rest, success);
                        } else if (type === 'object') {
                            $.extend(object, first);
                            recur(rest, success);
                        }
                    } else {
                        success();
                    }
                })(user_intrp, function() {
                    finalize({
                        interpreter: make_object_interpreter(
                            object,
                            false,
                            login,
                            fn_interpreter && fn_interpreter.bind(self)
                        ),
                        completion: Object.keys(object)
                    });
                });
            } else if (type === 'string') {
                if (settings.describe === false) {
                    object = {
                        interpreter: make_basic_json_rpc(user_intrp, login)
                    };
                    if ($.isArray(settings.completion)) {
                        object.completion = settings.completion;
                    }
                    finalize(object);
                } else {
                    self.pause(settings.softPause);
                    make_json_rpc_object(user_intrp, login, function(object) {
                        if (object) {
                            result.interpreter = make_object_interpreter(
                                object,
                                false,
                                login
                            );
                            result.completion = Object.keys(object);
                        } else {
                            // no procs in system.describe
                            result.interpreter = make_basic_json_rpc(user_intrp, login);
                        }
                        finalize(result);
                        self.resume();
                    });
                }
            } else if (type === 'object') {
                finalize({
                    interpreter: make_object_interpreter(
                        user_intrp,
                        settings.checkArity,
                        login
                    ),
                    completion: Object.keys(user_intrp)
                });
            } else {
                // allow $('<div/>').terminal();
                if (type === 'undefined') {
                    user_intrp = $.noop;
                } else if (type !== 'function') {
                    var msg = type + ' is invalid interpreter value';
                    throw new $.terminal.Exception(msg);
                }
                // single function don't need bind
                finalize({
                    interpreter: user_intrp,
                    completion: settings.completion
                });
            }
        }
        // ---------------------------------------------------------------------
        // :: Create JSON-RPC authentication function
        // ---------------------------------------------------------------------
        function make_json_rpc_login(url, login) {
            var method = get_type(login) === 'boolean' ? 'login' : login;
            return function(user, passwd, callback) {
                self.pause(settings.softPause);
                $.jrpc({
                    url: url,
                    method: method,
                    params: [user, passwd],
                    request: function(jxhr, request) {
                        try {
                            settings.request.call(self, jxhr, request, self);
                        } catch (e) {
                            display_exception(e, 'USER');
                        }
                    },
                    response: function(jxhr, response) {
                        try {
                            settings.response.call(self, jxhr, response, self);
                        } catch (e) {
                            display_exception(e, 'USER');
                        }
                    },
                    success: function success(response) {
                        if (!response.error && response.result) {
                            callback(response.result);
                        } else {
                            // null will trigger message that login fail
                            callback(null);
                        }
                        self.resume();
                    },
                    error: ajax_error
                });
            };
            // default name is login so you can pass true
        }
        // ---------------------------------------------------------------------
        // :: display Exception on terminal
        // ---------------------------------------------------------------------
        function display_exception(e, label, silent) {
            if (is_function(settings.exceptionHandler)) {
                settings.exceptionHandler.call(self, e, label);
            } else {
                self.exception(e, label);
                if (!silent) {
                    setTimeout(function() {
                        throw e;
                    }, 0);
                }
            }
        }
        // ---------------------------------------------------------------------
        // :: Draw line - can have line breaks and be longer than the width of
        // :: the terminal, there are 2 options raw and finalize
        // :: raw - will not encode the string and finalize if a function that
        // :: will have div container of the line as first argument
        // :: NOTE: it formats and appends lines to output_buffer. The actual
        // :: append to terminal output happens in the flush function
        // ---------------------------------------------------------------------
        var output_buffer = [];
        var NEW_LINE = 1;
        var format_cache;
        if ('Map' in root) {
            format_cache = new Map();
        }
        function buffer_line(arg, index, options) {
            // urls should always have formatting to keep url if split
            var i, len;
            output_buffer.push(NEW_LINE);
            var format_options = {
                linksNoReferrer: settings.linksNoReferrer,
                linksNoFollow: settings.linksNoFollow,
                anyLinks: settings.anyLinks,
                char_width: char_size.width,
                escape: false,
                allowedAttributes: options.allowedAttributes || []
            };
            var use_cache = settings.useCache && format_cache;
            function format_buff(arg, newline) {
                var args = JSON.stringify([arg, format_options]);
                if (use_cache) {
                    if (format_cache.has(args)) {
                        return format_cache.get(args);
                    }
                }
                var data = {
                    line: $.terminal.format(
                        arg,
                        format_options
                    ),
                    newline: newline
                };
                if (use_cache) {
                    format_cache.set(args, data);
                }
                return data;
            }
            if (arg instanceof Array) {
                for (i = 0, len = arg.length; i < len; ++i) {
                    if (arg[i] === '' || arg[i] === '\r') {
                        output_buffer.push({line: '<span></span>'});
                    } else {
                        output_buffer.push(format_buff(arg[i], i === len - 1));
                    }
                }
            } else if (!options.raw) {
                output_buffer.push(format_buff(arg));
            } else {
                output_buffer.push({line: arg});
            }
            output_buffer.push({
                finalize: options.finalize,
                index: index,
                newline: options.newline
            });
        }
        // ---------------------------------------------------------------------
        function links(string) {
            function format(_, style, color, background, _class, data, text) {
                function formatting(s, text) {
                    return '[[' + [
                        style + (s || ''),
                        color,
                        background,
                        _class,
                        text || data
                    ].join(';') + ']';
                }
                function escaped(_) {
                    return ']' + formatting('!', _) + _ + ']' + formatting();
                }
                if (!style.match(/!/)) {
                    var m = text.match(email_full_re) || text.match(url_full_re);
                    if (m) {
                        return formatting('!', m[1]) + text + ']';
                    } else if (text.match(email_re) || text.match(url_nf_re)) {
                        var output = text.replace(email_re, escaped)
                            .replace(url_nf_re, escaped);
                        return formatting('', data) + output + ']';
                    }
                }
                return _;
            }
            if (!$.terminal.have_formatting(string)) {
                return string.replace(email_re, '[[!;;]$1]').
                    replace(url_nf_re, '[[!;;]$1]');
            }
            return $.terminal.format_split(string).map(function(str) {
                if ($.terminal.is_formatting(str)) {
                    return str.replace(format_parts_re, format);
                } else {
                    return str.replace(email_re, '[[!;;]$1]').
                        replace(url_nf_re, '[[!;;]$1]');
                }
            }).join('');
        }
        // ---------------------------------------------------------------------
        function should_wrap(string, options) {
            return (strlen(text(string)) > options.cols ||
                    string.match(/\n/)) &&
                ((settings.wrap === true &&
                  options.wrap === undefined) ||
                 settings.wrap === false &&
                 options.wrap === true);
        }
        // ---------------------------------------------------------------------
        var string_cache;
        if ('Map' in root) {
            string_cache = new Map();
        }
        function process_line(line) {
            // prevent exception in display exception
            try {
                var line_settings = $.extend({
                    exec: true,
                    raw: false,
                    finalize: $.noop,
                    invokeMethods: false,
                    formatters: true,
                    convertLinks: settings.convertLinks
                }, line.options || {});
                var string = stringify_value(line.value);
                if (string && is_function(string.then)) {
                    // handle function that return a promise #629
                    return string.then(function(string) {
                        process_line($.extend(line, {
                            value: string
                        }));
                    });
                }
                if (string !== '') {
                    if (!line_settings.raw) {
                        if (settings.useCache) {
                            var key = string;
                            if (string_cache && string_cache.has(key)) {
                                string = string_cache.get(key);
                                buffer_line(string, line.index, line_settings);
                                return true;
                            }
                        }
                        if (line_settings.formatters) {
                            try {
                                string = $.terminal.apply_formatters(
                                    string,
                                    $.extend(settings, {echo: true})
                                );
                            } catch (e) {
                                display_exception(e, 'FORMATTING');
                            }
                        }
                        if (line_settings.exec) {
                            var parts = string.split(format_exec_re);
                            string = $.map(parts, function(string) {
                                if (string && string.match(format_exec_re) &&
                                    !$.terminal.is_formatting(string)) {
                                    // redraw should not execute commands and it have
                                    // and lines variable have all extended commands
                                    string = string.replace(/^\[\[|\]\]$/g, '');
                                    if (line_settings.exec) {
                                        line.options.exec = false;
                                        var trim = string.trim();
                                        if (prev_exec_cmd && prev_exec_cmd === trim) {
                                            prev_exec_cmd = '';
                                            self.error(strings().recursiveLoop);
                                        } else {
                                            prev_exec_cmd = trim;
                                            $.terminal.extended_command(self, string, {
                                                invokeMethods: line_settings.invokeMethods
                                            }).then(function() {
                                                prev_exec_cmd = '';
                                            });
                                        }
                                    }
                                    return '';
                                } else {
                                    return string;
                                }
                            }).join('');
                        }
                        if (string === '') {
                            return;
                        }
                        if (line_settings.convertLinks) {
                            string = links(string);
                        }
                        string = crlf($.terminal.normalize(string));
                        string = $.terminal.encode(string, {
                            tabs: settings.tabs
                        });
                        //string = $.terminal.normalize(string);
                        var array;
                        var cols = line_settings.cols = self.cols();
                        if (should_wrap(string, line_settings)) {
                            var words = line_settings.keepWords;
                            array = $.terminal.split_equal(string, cols, words);
                        } else if (string.match(/\n/)) {
                            array = string.split(/\n/);
                        }
                    }
                }
                var arg = array || string;
                if (string_cache && key) {
                    string_cache.set(key, arg);
                }
                buffer_line(arg, line.index, line_settings);
            } catch (e) {
                output_buffer = [];
                // don't display exception if exception throw in terminal
                if (is_function(settings.exceptionHandler)) {
                    settings.exceptionHandler.call(self, e, 'TERMINAL');
                } else {
                    alert_exception('[Internal Exception(process_line)]', e);
                }
            }
            // is it work with unpromise that ignore undefined
            return true;
        }
        // ---------------------------------------------------------------------
        // :: Update terminal lines
        // ---------------------------------------------------------------------
        function redraw(options) {
            options = $.extend({}, {
                // should be used when single line is updated
                update: false,
                // should be used if you want to scroll to bottom after redraw
                scroll: true
            }, options || {});
            if (!options.update) {
                command_line.resize(num_chars);
                // we don't want reflow while processing lines
                var detached_output = output.empty().detach();
            }
            var lines_to_show = [];
            // Dead code
            if (settings.outputLimit >= 0) {
                // flush will limit lines but if there is lot of
                // lines we don't need to show them and then remove
                // them from terminal
                var limit;
                if (settings.outputLimit === 0) {
                    limit = self.rows();
                } else {
                    limit = settings.outputLimit;
                }
                lines.forEach(function(line, index) {
                    var value = line[0];
                    var options = line[1];
                    lines_to_show.push({
                        value: value,
                        index: index,
                        options: options
                    });
                });
                var pivot = lines_to_show.length - limit - 1;
                lines_to_show = lines_to_show.slice(pivot);
            } else {
                lines_to_show = lines.map(function(line, index) {
                    return {
                        value: line[0],
                        index: index,
                        options: line[1]
                    };
                });
            }
            try {
                output_buffer = [];
                unpromise(lines_to_show.map(function(line) {
                    return process_line(line);
                }), function() {
                    if (!options.update) {
                        command_line.before(detached_output); // reinsert output
                    }
                    self.flush(options);
                    fire_event('onAfterRedraw');
                });
            } catch (e) {
                if (is_function(settings.exceptionHandler)) {
                    settings.exceptionHandler.call(self, e, 'TERMINAL (redraw)');
                } else {
                    alert_exception('[redraw]', e);
                }
            }
        }
        // ---------------------------------------------------------------------
        // :: Function limit output lines based on outputLimit option
        // ---------------------------------------------------------------------
        function limit_lines() {
            if (settings.outputLimit >= 0) {
                var limit;
                if (settings.outputLimit === 0) {
                    limit = self.rows();
                } else {
                    limit = settings.outputLimit;
                }
                var $lines = output.find('> div > div');
                if ($lines.length + 1 > limit) {
                    var max = $lines.length - limit + 1;
                    var for_remove = $lines.slice(0, max);
                    // you can't get parent if you remove the
                    // element so we first get the parent
                    var parents = for_remove.parent();
                    for_remove.remove();
                    parents.each(function() {
                        var $self = $(this);
                        if ($self.is(':empty')) {
                            unmount($self);
                            // there can be divs inside parent that
                            // was not removed
                            $self.remove();
                        }
                    });
                }
            }
        }
        // ---------------------------------------------------------------------
        // :: Display user greetings or terminal signature
        // ---------------------------------------------------------------------
        function show_greetings() {
            if (settings.greetings === undefined) {
                // signature have ascii art so it's not suite for screen readers
                self.echo(self.signature, {finalize: a11y_hide, formatters: false});
            } else if (settings.greetings) {
                var type = typeof settings.greetings;
                if (type === 'string') {
                    self.echo(settings.greetings);
                } else if (type === 'function') {
                    try {
                        var ret = settings.greetings.call(self, self.echo);
                        var error = make_label_error('Greetings');
                        unpromise(ret, self.echo, function(e) {
                            error(e);
                            settings.greetings = null;
                        });
                    } catch (e) {
                        settings.greetings = null;
                        display_exception(e, 'greetings');
                    }
                } else {
                    self.error(strings().wrongGreetings);
                }
            }
        }
        // ---------------------------------------------------------------------
        // :: Display prompt and last command
        // ---------------------------------------------------------------------
        function echo_command(command) {
            if (typeof command === 'undefined') {
                command = self.get_command();
            }
            // true will return last rendered string
            var prompt = command_line.prompt(true);
            var mask = command_line.mask();
            switch (typeof mask) {
                case 'string':
                    command = command.replace(/./g, mask);
                    break;
                case 'boolean':
                    if (mask) {
                        command = command.replace(/./g, settings.maskChar);
                    } else {
                        command = $.terminal.escape_formatting(command);
                    }
                    break;
            }
            var options = {
                convertLinks: false,
                exec: false,
                formatters: false,
                finalize: function finalize(div) {
                    a11y_hide(div.addClass('terminal-command'));
                    fire_event('onEchoCommand', [div, command]);
                }
            };
            command = $.terminal.apply_formatters(command, {command: true});
            self.echo(prompt + command, options);
        }
        // ---------------------------------------------------------------------
        function have_scrollbar() {
            return fill.outerWidth() !== self.outerWidth();
        }
        // ---------------------------------------------------------------------
        // :: Helper function that restore state. Call import_view or exec
        // ---------------------------------------------------------------------
        function restore_state(spec) {
            // spec [terminal_id, state_index, command]
            var terminal = terminals.get()[spec[0]];
            if (!terminal) {
                throw new $.terminal.Exception(strings().invalidTerminalId);
            }
            var command_idx = spec[1];
            if (save_state[command_idx]) { // state exists
                terminal.import_view(save_state[command_idx]);
            } else {
                // restore state
                change_hash = false;
                var command = spec[2];
                if (command) {
                    terminal.exec(command).done(function() {
                        change_hash = true;
                        save_state[command_idx] = terminal.export_view();
                    });
                }
            }
            /*if (spec[3].length) {
                restore_state(spec[3]);
            }*/
        }
        // ---------------------------------------------------------------------
        function make_label_error(label) {
            return function(e) {
                self.error('[' + label + '] ' + (e.message || e)).resume();
            };
        }
        // ---------------------------------------------------------------------
        // :: Helper function
        // ---------------------------------------------------------------------
        function maybe_update_hash() {
            if (change_hash) {
                fire_hash_change = false;
                location.hash = '#' + JSON.stringify(hash_commands);
                setTimeout(function() {
                    fire_hash_change = true;
                }, 100);
            }
        }
        // ---------------------------------------------------------------------
        // :: Wrapper over interpreter, it implements exit and catches all
        // :: exeptions from user code and displays them on the terminal
        // ---------------------------------------------------------------------
        var first_command = true;
        var resume_callbacks = [];
        function commands(command, silent, exec) {
            function init_state() {
                // execHash need first empty command too
                if (settings.historyState || settings.execHash && exec) {
                    if (!save_state.length) {
                        // first command in first terminal don't have hash
                        self.save_state();
                    } else {
                        self.save_state(null);
                    }
                }
            }
            // -----------------------------------------------------------------
            function after_exec() {
                // variables defined later in commands
                if (!exec) {
                    change_hash = true;
                    if (settings.historyState) {
                        self.save_state(command, false);
                    }
                    change_hash = saved_change_hash;
                }
                deferred.resolve();
                fire_event('onAfterCommand', [command]);
            }
            // -----------------------------------------------------------------
            function show(result) {
                if (typeof result !== 'undefined') {
                    display_object(result);
                }
                after_exec();
                self.resume();
            }
            // -----------------------------------------------------------------

            // -----------------------------------------------------------------
            function invoke() {
                // Call user interpreter function
                var result = interpreter.interpreter.call(self, command, self);
                if (result) {
                    // auto pause/resume when user return promises
                    // it should not pause when user return promise from read()
                    if (!force_awake) {
                        self.pause(settings.softPause);
                    }
                    force_awake = false;
                    var error = make_label_error('Command');
                    // when for native Promise object work only in jQuery 3.x
                    if (is_function(result.done || result.then)) {
                        return unpromise(result, show, error);
                    } else {
                        return $.when(result).done(show).catch(error);
                    }
                } else if (paused) {
                    resume_callbacks.push(function() {
                        // exec with resume/pause in user code
                        after_exec();
                    });
                } else {
                    after_exec();
                }
            }
            // -----------------------------------------------------------------
            // first command store state of the terminal before the command get
            // executed
            if (first_command) {
                first_command = false;
                init_state();
            }
            try {
                // this callback can disable commands
                if (fire_event('onBeforeCommand', [command]) === false) {
                    return;
                }
                if (exec) {
                    prev_exec_cmd = command.trim();
                    prev_command = $.terminal.split_command(prev_exec_cmd);
                } else {
                    prev_command = $.terminal.split_command(command);
                }
                if (!ghost()) {
                    // exec execute this function wihout the help of cmd plugin
                    // that add command to history on enter
                    if (exec && (is_function(settings.historyFilter) &&
                                 settings.historyFilter(command) ||
                                 command.match(settings.historyFilter))) {
                        command_line.history().append(command);
                    }
                }
                var interpreter = interpreters.top();
                if (!silent && settings.echoCommand) {
                    echo_command(command);
                }
                // new promise will be returned to exec that will resolve his
                // returned promise
                var deferred = new $.Deferred();
                // we need to save sate before commands is deleyd because
                // execute_extended_command disable it and it can be executed
                // after delay
                var saved_change_hash = change_hash;
                if (command.match(/^\s*login\s*$/) && self.token(true)) {
                    if (self.level() > 1) {
                        self.logout(true);
                    } else {
                        self.logout();
                    }
                    after_exec();
                } else if (settings.exit && command.match(/^\s*exit\s*$/) &&
                           !in_login) {
                    var level = self.level();
                    if (level === 1 && self.get_token() || level > 1) {
                        if (self.get_token(true)) {
                            self.set_token(undefined, true);
                        }
                        self.pop();
                    }
                    after_exec();
                } else if (settings.clear && command.match(/^\s*clear\s*$/) &&
                           !in_login) {
                    self.clear();
                    after_exec();
                } else {
                    var ret = invoke();
                    if (ret) {
                        return ret;
                    }
                }
                return deferred.promise();
            } catch (e) {
                display_exception(e, 'USER', exec);
                self.resume();
                if (exec) {
                    throw e;
                }
            }
        }
        // ---------------------------------------------------------------------
        // :: The logout function removes Storage, disables history and runs
        // :: the login function. This function is called only when options.login
        // :: function is defined. The check for this is in the self.pop method
        // ---------------------------------------------------------------------
        function global_logout() {
            if (fire_event('onBeforeLogout', [], true) === false) {
                return;
            }
            clear_loging_storage();
            fire_event('onAfterlogout', [], true);
            self.login(global_login_fn, true, initialize);
        }
        // ---------------------------------------------------------------------
        function clear_loging_storage() {
            var name = self.prefix_name(true) + '_';
            storage.remove(name + 'token');
            storage.remove(name + 'login');
        }
        // ---------------------------------------------------------------------
        // :: Save the interpreter name for use with purge
        // ---------------------------------------------------------------------
        function maybe_append_name(interpreter_name) {
            var storage_key = self.prefix_name() + '_interpreters';
            var names = storage.get(storage_key);
            if (names) {
                names = JSON.parse(names);
            } else {
                names = [];
            }
            if ($.inArray(interpreter_name, names) === -1) {
                names.push(interpreter_name);
                storage.set(storage_key, JSON.stringify(names));
            }
        }
        // ---------------------------------------------------------------------
        // :: Function enables history, sets prompt, runs interpreter function
        // ---------------------------------------------------------------------
        function prepare_top_interpreter(silent) {
            var interpreter = interpreters.top();
            var name = self.prefix_name(true);
            if (!ghost()) {
                maybe_append_name(name);
            }
            var login = self.login_name(true);
            command_line.name(name + (login ? '_' + login : ''));
            var prompt = interpreter.prompt;
            if (is_function(prompt)) {
                prompt = context_callback_proxy(prompt);
            }
            if (prompt !== command_line.prompt()) {
                if (is_function(interpreter.prompt)) {
                    // prevent flicker of old prompt until async prompt finishes
                    command_line.prompt('');
                }
                command_line.prompt(interpreter.prompt);
            }
            if (typeof interpreter.history !== 'undefined') {
                self.history().toggle(interpreter.history);
            }
            if ($.isPlainObject(interpreter.keymap)) {
                command_line.keymap(null).keymap($.extend(
                    {},
                    terminal_init_keymap,
                    $.omap(interpreter.keymap, function(name, fun) {
                        return function() {
                            var args = [].slice.call(arguments);
                            try {
                                return fun.apply(self, args);
                            } catch (e) {
                                display_exception(e, 'USER KEYMAP');
                            }
                        };
                    })
                ));
            }
            command_line.set('');
            init_queue.resolve();
            if (!silent && is_function(interpreter.onStart)) {
                interpreter.onStart.call(self, self);
            }
        }
        // ---------------------------------------------------------------------
        function fire_event(name, args, skip_local) {
            args = (args || []).concat([self]); // create new array
            // even can be fired before interpreters is created
            var top = interpreters && interpreters.top();
            if (top && is_function(top[name]) && !skip_local) {
                try {
                    return top[name].apply(self, args);
                } catch (e) {
                    delete top[name];
                    display_exception(e, name);
                }
            } else if (is_function(settings[name])) {
                try {
                    return settings[name].apply(self, args);
                } catch (e) {
                    settings[name] = null;
                    display_exception(e, name);
                }
            }
        }
        var scroll_to_view = (function() {
            function scroll_to_view(visible) {
                if (!visible) {
                    // try catch for Node.js unit tests
                    try {
                        self.scroll_to(self.find('.cmd-cursor-line'));
                        return true;
                    } catch (e) {
                        return true;
                    }
                }
            }
            // we don't want debounce in Unit Tests
            if (typeof global !== 'undefined' && typeof global.it === 'function') {
                return scroll_to_view;
            }
            return debounce(scroll_to_view, 100, {
                leading: true,
                trailing: false
            });
        })();
        // ---------------------------------------------------------------------
        function make_cursor_visible() {
            var cursor = self.find('.cmd-cursor-line');
            return cursor.is_fully_in_viewport(self).then(scroll_to_view);
        }
        // ---------------------------------------------------------------------
        function hashchange() {
            if (fire_hash_change && settings.execHash) {
                try {
                    if (location.hash) {
                        var hash = location.hash.replace(/^#/, '');
                        hash_commands = JSON.parse(decodeURIComponent(hash));
                    } else {
                        hash_commands = [];
                    }
                    if (hash_commands.length) {
                        restore_state(hash_commands[hash_commands.length - 1]);
                    } else if (save_state[0]) {
                        self.import_view(save_state[0]);
                    }
                } catch (e) {
                    display_exception(e, 'TERMINAL');
                }
            }
        }
        // ---------------------------------------------------------------------
        function initialize() {
            prepare_top_interpreter();
            show_greetings();
            if (lines.length) {
                self.refresh(); // for case when showing long error before init
            }
            // was_paused flag is workaround for case when user call exec before
            // login and pause in onInit, 3rd exec will have proper timing (will
            // execute after onInit resume)
            var was_paused = false;
            if (is_function(settings.onInit)) {
                onPause = function() { // local in terminal
                    was_paused = true;
                };
                try {
                    settings.onInit.call(self, self);
                } catch (e) {
                    display_exception(e, 'OnInit');
                    // throw e; // it will be catched by terminal
                } finally {
                    onPause = $.noop;
                    if (!was_paused && self.enabled()) {
                        // resume login if user didn't call pause in onInit
                        // if user pause in onInit wait with exec until it
                        // resume
                        self.resume(true);
                    }
                }
            }
            if (first_instance) {
                first_instance = false;
                $(window).on('hashchange', hashchange);
            }
        }
        // ---------------------------------------------------------------------
        // :: If Ghost don't store anything in localstorage
        // ---------------------------------------------------------------------
        function ghost() {
            return in_login || command_line.mask() !== false;
        }
        // ---------------------------------------------------------------------
        // :: Keydown event handler
        // ---------------------------------------------------------------------
        function user_key_down(e) {
            var result, top = interpreters.top();
            if (is_function(top.keydown)) {
                result = top.keydown.call(self, e, self);
                if (result !== undefined) {
                    return result;
                }
            } else if (is_function(settings.keydown)) {
                result = settings.keydown.call(self, e, self);
                if (result !== undefined) {
                    return result;
                }
            }
        }
        var keymap = {
            'CTRL+D': function(e, original) {
                if (!in_login) {
                    if (command_line.get() === '') {
                        if (interpreters.size() > 1 ||
                            is_function(global_login_fn)) {
                            self.pop('');
                        } else {
                            self.resume();
                        }
                    } else {
                        original();
                    }
                }
                return false;
            },
            'CTRL+C': function() {
                with_selection(function(html) {
                    if (html === '') {
                        var command = self.get_command();
                        var position = self.get_position();
                        command = command.slice(0, position) + '^C' +
                            command.slice(position + 2);
                        echo_command(command);
                        self.set_command('');
                    } else {
                        var clip = self.find('textarea');
                        text_to_clipboard(clip, process_selected_html(html));
                    }
                });
                return false;
            },
            'CTRL+L': function() {
                self.clear();
                return false;
            },
            'TAB': function(e, orignal) {
                // TODO: move this to cmd plugin
                //       add completion = array | function
                //       !!! Problem complete more then one key need terminal
                var top = interpreters.top(), completion, caseSensitive;
                if (typeof top.caseSensitiveAutocomplete !== 'undefined') {
                    caseSensitive = top.caseSensitiveAutocomplete;
                } else {
                    caseSensitive = settings.caseSensitiveAutocomplete;
                }
                if (settings.completion &&
                    get_type(settings.completion) !== 'boolean' &&
                    top.completion === undefined) {
                    completion = settings.completion;
                } else {
                    completion = top.completion;
                }
                if (completion === 'settings') {
                    completion = settings.completion;
                }
                function resolve(commands) {
                    // local copy
                    commands = commands.slice();
                    // default commands should not match for arguments
                    if (!self.before_cursor(false).match(/\s/)) {
                        if (settings.clear && $.inArray('clear', commands) === -1) {
                            commands.push('clear');
                        }
                        if (settings.exit && $.inArray('exit', commands) === -1) {
                            commands.push('exit');
                        }
                    }
                    self.complete(commands, {
                        echo: true,
                        word: settings.wordAutocomplete,
                        escape: settings.completionEscape,
                        caseSensitive: caseSensitive,
                        echoCommand: settings.doubleTabEchoCommand,
                        doubleTab: settings.doubleTab
                    });
                }
                if (completion) {
                    switch (get_type(completion)) {
                        case 'function':
                            var string = self.before_cursor(settings.wordAutocomplete);
                            if (completion.length === 3) {
                                var error = new Error(strings().comletionParameters);
                                display_exception(error, 'USER');
                                return false;
                            }
                            var result = completion.call(self, string, resolve);
                            unpromise(result, resolve, make_label_error('Completion'));
                            break;
                        case 'array':
                            resolve(completion);
                            break;
                        default:
                            throw new $.terminal.Exception(strings().invalidCompletion);
                    }
                } else {
                    orignal();
                }
                return false;
            },
            'CTRL+V': function(e, original) {
                original(e);
                self.oneTime(200, function() {
                    self.scroll_to_bottom();
                });
                return true;
            },
            'CTRL+TAB': function() {
                if (terminals.length() > 1) {
                    self.focus(false);
                    return false;
                }
            },
            'PAGEDOWN': function() {
                self.scroll(self.height());
            },
            'PAGEUP': function() {
                self.scroll(-self.height());
            }
        };
        // ---------------------------------------------------------------------
        function key_down(e) {
            // Prevent to be executed by cmd: CTRL+D, TAB, CTRL+TAB (if more
            // then one terminal)
            var result, i;
            if (animating) {
                return false;
            }
            if (self.enabled()) {
                if (!self.paused()) {
                    result = user_key_down(e);
                    if (result !== undefined) {
                        return result;
                    }
                    if (e.which !== 9) { // not a TAB
                        tab_count = 0;
                    }
                } else {
                    if (!settings.pauseEvents) {
                        result = user_key_down(e);
                        if (result !== undefined) {
                            return result;
                        }
                    }
                    if (e.which === 68 && e.ctrlKey) { // CTRL+D (if paused)
                        if (settings.pauseEvents) {
                            result = user_key_down(e);
                            if (result !== undefined) {
                                return result;
                            }
                        }
                        if (requests.length) {
                            for (i = requests.length; i--;) {
                                var r = requests[i];
                                if (r.readyState !== 4) {
                                    try {
                                        r.abort();
                                    } catch (error) {
                                        if (is_function(settings.exceptionHandler)) {
                                            settings.exceptionHandler.call(
                                                self,
                                                e,
                                                'AJAX ABORT'
                                            );
                                        } else {
                                            self.error(strings().ajaxAbortError);
                                        }
                                    }
                                }
                            }
                            requests = [];
                        }
                        self.resume();
                    }
                    return false;
                }
            }
        }
        // ---------------------------------------------------------------------
        function key_press(e) {
            var top = interpreters.top();
            if (enabled && (!paused || !settings.pauseEvents)) {
                if (is_function(top.keypress)) {
                    return top.keypress.call(self, e, self);
                } else if (is_function(settings.keypress)) {
                    return settings.keypress.call(self, e, self);
                }
            }
        }
        // ---------------------------------------------------------------------
        // :: Typing animation generator
        // ---------------------------------------------------------------------
        function typed(finish_typing_fn) {
            return function typing_animation(message, options) {
                animating = true;
                var prompt = self.get_prompt();
                var char_i = 0;
                var len = $.terminal.length(message);
                if (message.length > 0) {
                    var new_prompt = '';
                    if (options.prompt) {
                        new_prompt = options.prompt;
                    } else {
                        self.set_prompt('');
                    }
                    var interval = setInterval(function() {
                        var chr = $.terminal.substring(message, char_i, char_i + 1);
                        new_prompt += chr;
                        self.set_prompt(new_prompt);
                        char_i++;
                        if (char_i === len) {
                            clearInterval(interval);
                            setTimeout(function() {
                                // swap command with prompt
                                finish_typing_fn(message, prompt, options);
                                animating = false;
                            }, options.delay);
                        }
                    }, options.delay);
                }
            };
        }
        // ---------------------------------------------------------------------
        var typed_prompt = typed(function(message, _, options) {
            self.set_prompt(message);
            options.finalize();
        });
        // ---------------------------------------------------------------------
        var typed_message = typed(function(message, prompt, options) {
            self.set_prompt(prompt);
            self.echo(message, $.extend({}, options, {typing: false}));
        });
        // ---------------------------------------------------------------------
        var typed_enter = (function() {
            var helper = typed(function(message, prompt, options) {
                self.set_prompt(prompt);
                self.echo(prompt + message, $.extend({}, options, {typing: false}));
            });
            return function(prompt, message, options) {
                return helper(message, $.extend({}, options, {prompt: prompt}));
            };
        })();
        // ---------------------------------------------------------------------
        function ready(queue) {
            return function(fun) {
                queue.add(fun);
            };
        }
        // ---------------------------------------------------------------------
        function strings() {
            return $.extend(
                {},
                $.terminal.defaults.strings,
                settings && settings.strings || {}
            );
        }
        // ---------------------------------------------------------------------
        var self = this;
        if (this.length > 1) {
            return this.each(function() {
                $.fn.terminal.call(
                    $(this),
                    init_interpreter,
                    $.extend({name: self.selector}, options)
                );
            });
        }
        var body_terminal;
        if (self.is('body,html')) {
            // terminal already exists on body
            if (self.hasClass('full-screen-terminal')) {
                var data = self.find('> .terminal').data('terminal');
                if (data) {
                    return data;
                }
            }
            body_terminal = self;
            self = $('<div/>').appendTo('body');
            $('body').addClass('full-screen-terminal');
        } else if (self.data('terminal')) {
            // terminal already exists
            return self.data('terminal');
        }
        // -----------------------------------------------------------------
        // TERMINAL METHODS
        // -----------------------------------------------------------------
        $.extend(self, $.omap({
            id: function() {
                return terminal_id;
            },
            // -------------------------------------------------------------
            // :: Clear the output
            // -------------------------------------------------------------
            clear: function() {
                if (fire_event('onClear') !== false) {
                    lines.forEach(function(line, i) {
                        var options = line[1];
                        if (is_function(options.onClear)) {
                            options.onClear.call(self, get_node(i));
                        }
                    });
                    lines = [];
                    output[0].innerHTML = '';
                    self.prop({scrollTop: 0});
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Return an object that can be used with import_view to
            // :: restore the state
            // -------------------------------------------------------------
            export_view: function() {
                var user_export = fire_event('onExport');
                user_export = user_export || {};
                return $.extend({}, {
                    focus: enabled,
                    mask: command_line.mask(),
                    prompt: self.get_prompt(),
                    command: self.get_command(),
                    position: command_line.position(),
                    lines: clone(lines),
                    interpreters: interpreters.clone(),
                    history: command_line.history().data
                }, user_export);
            },
            // -------------------------------------------------------------
            // :: Restore the state of the previous exported view
            // -------------------------------------------------------------
            import_view: function(view) {
                if (in_login) {
                    throw new Error(sprintf(strings().notWhileLogin, 'import_view'));
                }
                fire_event('onImport', [view]);
                when_ready(function ready() {
                    self.set_prompt(view.prompt);
                    self.set_command(view.command);
                    command_line.position(view.position);
                    command_line.mask(view.mask);
                    if (view.focus) {
                        self.focus();
                    }
                    lines = clone(view.lines).filter(function(line) {
                        return line[0];
                    });
                    if (view.interpreters instanceof Stack) {
                        interpreters = view.interpreters;
                    }
                    if (settings.importHistory) {
                        command_line.history().set(view.history);
                    }
                    redraw();
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Store current terminal state
            // -------------------------------------------------------------
            save_state: function(command, ignore_hash, index) {
                // save_state.push({view:self.export_view(), join:[]});
                if (typeof index !== 'undefined') {
                    save_state[index] = self.export_view();
                } else {
                    save_state.push(self.export_view());
                }
                if (!$.isArray(hash_commands)) {
                    hash_commands = [];
                }
                if (command !== undefined && !ignore_hash) {
                    var state = [
                        terminal_id,
                        save_state.length - 1,
                        command
                    ];
                    hash_commands.push(state);
                    maybe_update_hash();
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Execute a command, it will handle commands that do AJAX
            // :: calls and have delays, if the second argument is set to
            // :: true it will not echo executed command
            // -------------------------------------------------------------
            exec: function(command, silent, deferred) {
                var d = deferred || new $.Deferred();
                cmd_ready(function ready() {
                    if ($.isArray(command)) {
                        (function recur() {
                            var cmd = command.shift();
                            if (cmd) {
                                self.exec(cmd, silent).done(recur);
                            } else {
                                d.resolve();
                            }
                        })();
                    } else if (paused) {
                        // both commands executed here (resume will call Term::exec)
                        // delay command multiple time
                        delayed_commands.push([command, silent, d]);
                    } else {
                        // commands may return promise from user code
                        // it will resolve exec promise when user promise
                        // is resolved
                        var ret = commands(command, silent, true);
                        unpromise(ret, function() {
                            // reset prev command for push called after exec
                            // so push didn't get name/prompt from exec command
                            prev_command = null;
                            d.resolve();
                        }, function() {
                            prev_command = null;
                            d.reject();
                        });
                    }
                });
                // while testing it didn't executed last exec when using this
                // for resolved deferred
                return d.promise();
            },
            // -------------------------------------------------------------
            // :: bypass login function that wait untill you type user/pass
            // :: it hide implementation detail
            // -------------------------------------------------------------
            autologin: function(user, token, silent) {
                self.trigger('terminal.autologin', [user, token, silent]);
                return self;
            },
            // -------------------------------------------------------------
            // :: Function changes the prompt of the command line to login
            // :: with a password and calls the user login function with
            // :: the callback that expects a token. The login is successful
            // :: if the user calls it with value that is truthy
            // -------------------------------------------------------------
            login: function(auth, infinite, success, error) {
                logins.push([].slice.call(arguments));
                if (in_login) {
                    throw new Error(sprintf(strings().notWhileLogin, 'login'));
                }
                if (!is_function(auth)) {
                    throw new Error(strings().loginIsNotAFunction);
                }
                in_login = true;
                if (self.token() && self.level() === 1 && !autologin) {
                    in_login = false; // logout will call login
                    self.logout(true);
                } else if (self.token(true) && self.login_name(true)) {
                    in_login = false;
                    if (is_function(success)) {
                        success();
                    }
                    return self;
                }
                // don't store login data in history
                if (settings.history) {
                    command_line.history().disable();
                }
                function popUserPass() {
                    while (self.level() > level) {
                        self.pop(undefined, true);
                    }
                    if (settings.history) {
                        command_line.history().enable();
                    }
                }
                // so we know how many times call pop
                var level = self.level();
                function login_callback(user, token, silent) {
                    if (token) {
                        popUserPass();
                        var name = self.prefix_name(true) + '_';
                        storage.set(name + 'token', token);
                        storage.set(name + 'login', user);
                        in_login = false;
                        fire_event('onAfterLogin', [user, token]);
                        if (is_function(success)) {
                            // will be used internaly since users know
                            // when login success (they decide when
                            // it happen by calling the callback -
                            // this funtion)
                            success();
                        }
                    } else {
                        if (infinite) {
                            if (!silent) {
                                self.error(strings().wrongPasswordTryAgain);
                            }
                            self.pop(undefined, true).set_mask(false);
                        } else {
                            in_login = false;
                            if (!silent) {
                                self.error(strings().wrongPassword);
                            }
                            self.pop(undefined, true).pop(undefined, true);
                        }
                        // used only to call pop in push
                        if (is_function(error)) {
                            error();
                        }
                    }
                    if (self.paused()) {
                        self.resume();
                    }
                    self.off('terminal.autologin');
                }
                self.on('terminal.autologin', function(event, user, token, silent) {
                    if (fire_event('onBeforeLogin', [user, token]) === false) {
                        return;
                    }
                    login_callback(user, token, silent);
                });
                self.push(function(user) {
                    self.set_mask(settings.maskChar).push(function(pass) {
                        try {
                            if (fire_event('onBeforeLogin', [user, pass]) === false) {
                                popUserPass();
                                return;
                            }
                            self.pause();
                            var ret = auth.call(self, user, pass, function(
                                token,
                                silent) {
                                login_callback(user, token, silent);
                            });
                            if (ret && is_function(ret.then || ret.done)) {
                                (ret.then || ret.done).call(ret, function(token) {
                                    login_callback(user, token);
                                }).catch(function(err) {
                                    self.pop(undefined, true).pop(undefined, true);
                                    self.error(err.message);
                                    if (is_function(error)) {
                                        error();
                                    }
                                    if (self.paused()) {
                                        self.resume();
                                    }
                                    self.off('terminal.autologin');
                                });
                            }
                        } catch (e) {
                            display_exception(e, 'AUTH');
                        }
                    }, {
                        prompt: strings().password + ': ',
                        name: 'password'
                    });
                }, {
                    prompt: strings().login + ': ',
                    name: 'login'
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: User defined settings and defaults as well
            // -------------------------------------------------------------
            settings: function() {
                return settings;
            },
            // -------------------------------------------------------------
            // :: Get string before cursor
            // -------------------------------------------------------------
            before_cursor: function(word) {
                var pos = command_line.position();
                var command = command_line.get().slice(0, pos);
                var cmd_strings = command.split(' ');
                var string; // string before cursor that will be completed
                if (word) {
                    if (cmd_strings.length === 1) {
                        string = cmd_strings[0];
                    } else {
                        var m = command.match(/(\\?")/g);
                        var double_quotes = m ? m.filter(function(chr) {
                            return !chr.match(/^\\/);
                        }).length : 0;
                        m = command.match(/'/g);
                        var single_quote = m ? m.length : 0;
                        if (single_quote % 2 === 1) {
                            string = command.match(/('[^']*)$/)[0];
                        } else if (double_quotes % 2 === 1) {
                            string = command.match(/("(?:[^"]|\\")*)$/)[0];
                        } else {
                            string = cmd_strings[cmd_strings.length - 1];
                            for (i = cmd_strings.length - 1; i > 0; i--) {
                                // treat escape space as part of the string
                                var prev_string = cmd_strings[i - 1];
                                if (prev_string[prev_string.length - 1] === '\\') {
                                    string = cmd_strings[i - 1] + ' ' + string;
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                } else {
                    string = command;
                }
                return string;
            },
            // -------------------------------------------------------------
            // :: complete word or command based on array of words
            // -------------------------------------------------------------
            complete: function(commands, options) {
                options = $.extend({
                    word: true,
                    echo: false,
                    escape: true,
                    echoCommand: false,
                    caseSensitive: true,
                    doubleTab: null
                }, options || {});
                var sensitive = options.caseSensitive;
                // cursor can be in the middle of the command
                // so we need to get the text before the cursor
                var string = self.before_cursor(options.word).replace(/\\"/g, '"');
                var quote = false;
                if (options.word) {
                    if (string.match(/^"/)) {
                        quote = '"';
                    } else if (string.match(/^'/)) {
                        quote = "'";
                    }
                    if (quote) {
                        string = string.replace(/^["']/, '');
                    }
                }
                if (tab_count % 2 === 0) {
                    command = self.before_cursor(options.word);
                } else {
                    var test = self.before_cursor(options.word);
                    if (test !== command) {
                        // command line changed between TABS - ignore
                        return;
                    }
                }
                var safe = $.terminal.escape_regex(string);
                if (options.escape) {
                    safe = safe.replace(/(\\+)(["'() ])/g, function(_, slash, chr) {
                        if (chr.match(/[()]/)) {
                            return slash + '\\?\\' + chr;
                        } else {
                            return slash + '?' + chr;
                        }
                    });
                }
                function escape(string) {
                    if (quote === '"') {
                        string = string.replace(/"/g, '\\"');
                    }
                    if (!quote && options.escape) {
                        string = string.replace(/(["'() ])/g, '\\$1');
                    }
                    return string;
                }
                function matched_strings() {
                    var matched = [];
                    for (var i = commands.length; i--;) {
                        if (commands[i].match(/\n/) && options.word) {
                            warn('If you use commands with newlines you ' +
                                 'should use word option for complete or' +
                                 ' wordAutocomplete terminal option');
                        }
                        if (regex.test(commands[i])) {
                            var match = escape(commands[i]);
                            if (!sensitive && same_case(match)) {
                                if (string.toLowerCase() === string) {
                                    match = match.toLowerCase();
                                } else if (string.toUpperCase() === string) {
                                    match = match.toUpperCase();
                                }
                            }
                            matched.push(match);
                        }
                    }
                    return matched;
                }
                var flags = sensitive ? '' : 'i';
                var regex = new RegExp('^' + safe, flags);
                var matched = matched_strings();
                function replace(input, replacement) {
                    var text = self.get_command();
                    var pos = self.get_position();
                    var re = new RegExp('^' + input, 'i');
                    var pre = text.slice(0, pos);
                    var post = text.slice(pos);
                    var to_insert = replacement.replace(re, '') + (quote || '');
                    self.set_command(pre + to_insert + post);
                    self.set_position((pre + to_insert).length);
                }
                if (matched.length === 1) {
                    if (options.escape) {
                        replace(safe, matched[0]);
                    } else {
                        self.insert(matched[0].replace(regex, '') + (quote || ''));
                    }
                    command = self.before_cursor(options.word);
                    return true;
                } else if (matched.length > 1) {
                    if (++tab_count >= 2) {
                        tab_count = 0;
                        if (options.echo) {
                            if (is_function(options.doubleTab)) {
                                // new API old is keep for backward compatibility
                                if (options.echoCommand) {
                                    echo_command();
                                }
                                var ret = options.doubleTab.call(
                                    self,
                                    string,
                                    matched,
                                    echo_command
                                );
                                if (typeof ret === 'undefined') {
                                    return true;
                                } else {
                                    return ret;
                                }
                            } else if (options.doubleTab !== false) {
                                echo_command();
                                var text = matched.slice().reverse().join('\t\t');
                                self.echo($.terminal.escape_brackets(text), {
                                    keepWords: true,
                                    formatters: false
                                });
                            }
                            return true;
                        }
                    } else {
                        var common = common_string(escape(string), matched, sensitive);
                        if (common) {
                            replace(safe, common);
                            command = self.before_cursor(options.word);
                            return true;
                        }
                    }
                }
            },
            // -------------------------------------------------------------
            // :: Return commands function from top interpreter
            // -------------------------------------------------------------
            commands: function() {
                return interpreters.top().interpreter;
            },
            // -------------------------------------------------------------
            // :: Low Level method that overwrites interpreter
            // -------------------------------------------------------------
            set_interpreter: function(user_intrp, login) {
                var defer = $.Deferred();
                function overwrite_interpreter() {
                    self.pause(settings.softPause);
                    make_interpreter(user_intrp, login, function(result) {
                        self.resume();
                        var top = interpreters.top();
                        $.extend(top, result);
                        prepare_top_interpreter(true);
                        defer.resolve();
                    });
                }
                if (is_function(login)) {
                    self.login(login, true, overwrite_interpreter);
                } else if (get_type(user_intrp) === 'string' && login) {
                    self.login(
                        make_json_rpc_login(user_intrp, login),
                        true,
                        overwrite_interpreter
                    );
                } else {
                    overwrite_interpreter();
                }
                return defer.promise();
            },
            // -------------------------------------------------------------
            // :: Show user greetings or terminal signature
            // -------------------------------------------------------------
            greetings: function() {
                show_greetings();
                return self;
            },
            // -------------------------------------------------------------
            // :: Return true if terminal is paused false otherwise
            // -------------------------------------------------------------
            paused: function() {
                return paused;
            },
            // -------------------------------------------------------------
            // :: Pause the terminal, it should be used for ajax calls
            // -------------------------------------------------------------
            pause: function(visible) {
                cmd_ready(function ready() {
                    onPause();
                    paused = true;
                    command_line.disable(visible || is_android);
                    if (!visible) {
                        command_line.find('.cmd-prompt').hidden();
                    }
                    fire_event('onPause');
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Resume the previously paused terminal
            // -------------------------------------------------------------
            resume: function(silent) {
                cmd_ready(function ready() {
                    paused = false;
                    if (enabled && terminals.front() === self) {
                        command_line.enable(silent);
                    }
                    command_line.find('.cmd-prompt').visible();
                    var original = delayed_commands;
                    delayed_commands = [];
                    for (var i = 0; i < original.length; ++i) {
                        self.exec.apply(self, original[i]);
                    }
                    self.trigger('resume');
                    var fn = resume_callbacks.shift();
                    if (fn) {
                        fn();
                    }
                    self.scroll_to_bottom();
                    fire_event('onResume');
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Return the number of characters that fit into the width of
            // :: the terminal
            // -------------------------------------------------------------
            cols: function() {
                if (settings.numChars) {
                    return settings.numChars;
                }
                if (!num_chars || num_chars === 1000) {
                    num_chars = get_num_chars(self, char_size);
                }
                return num_chars;
            },
            // -------------------------------------------------------------
            // :: Return the number of lines that fit into the height of the
            // :: terminal
            // -------------------------------------------------------------
            rows: function() {
                if (settings.numRows) {
                    return settings.numRows;
                }
                if (!num_rows) {
                    num_rows = get_num_rows(self, char_size);
                }
                return num_rows;
            },
            // -------------------------------------------------------------
            // :: Return the History object
            // -------------------------------------------------------------
            history: function() {
                return command_line.history();
            },
            // -------------------------------------------------------------
            // :: Return size of the terminal instance
            // -------------------------------------------------------------
            geometry: function() {
                return {
                    terminal: {
                        width: old_width,
                        height: old_height
                    },
                    char: char_size,
                    cols: this.cols(),
                    rows: this.rows()
                };
            },
            // -------------------------------------------------------------
            // :: toggle recording of history state
            // -------------------------------------------------------------
            history_state: function(toggle) {
                function run() {
                    settings.historyState = true;
                    if (!save_state.length) {
                        self.save_state();
                    } else if (terminals.length() > 1) {
                        self.save_state(null);
                    }
                }
                if (toggle) {
                    // if set to true and if set from user command we need
                    // not to include the command
                    if (typeof window.setImmediate === 'undefined') {
                        setTimeout(run, 0);
                    } else {
                        setImmediate(run);
                    }
                } else {
                    settings.historyState = false;
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: clear the history state
            // -------------------------------------------------------------
            clear_history_state: function() {
                hash_commands = [];
                save_state = [];
                return self;
            },
            // -------------------------------------------------------------
            // :: Switch to the next terminal
            // -------------------------------------------------------------
            next: function() {
                if (terminals.length() === 1) {
                    return self;
                } else {
                    terminals.front().disable();
                    var next = terminals.rotate().enable();
                    // 50 provides buffer in viewport
                    var x = next.offset().top - 50;
                    $('html,body').animate({scrollTop: x}, 500);
                    try {
                        trigger_terminal_change(next);
                    } catch (e) {
                        display_exception(e, 'onTerminalChange');
                    }
                    return next;
                }
            },
            // -------------------------------------------------------------
            // :: Make the terminal in focus or blur depending on the first
            // :: argument. If there is more then one terminal it will
            // :: switch to next one, if the second argument is set to true
            // :: the events will be not fired. Used on init
            // -------------------------------------------------------------
            focus: function(toggle, silent) {
                cmd_ready(function ready() {
                    if (terminals.length() === 1) {
                        if (toggle === false) {
                            self.disable(silent);
                        } else {
                            self.enable(silent);
                        }
                    } else if (toggle === false) {
                        self.next();
                    } else {
                        var front = terminals.front();
                        if (front !== self) {
                            // there should be only from terminal enabled but tests
                            // sometime fail because there where more them one
                            // where cursor have blink class
                            terminals.forEach(function(terminal) {
                                if (terminal !== self && terminal.enabled()) {
                                    terminal.disable(silent);
                                }
                            });
                            if (!silent) {
                                try {
                                    trigger_terminal_change(self);
                                } catch (e) {
                                    display_exception(e, 'onTerminalChange');
                                }
                            }
                        }
                        terminals.set(self);
                        self.enable(silent);
                    }
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Disable/Enable terminal that can be enabled by click
            // -------------------------------------------------------------
            freeze: function(freeze) {
                when_ready(function ready() {
                    if (freeze) {
                        self.disable();
                        frozen = true;
                    } else {
                        frozen = false;
                        self.enable();
                    }
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: check if terminal is frozen
            // -------------------------------------------------------------
            frozen: function() {
                return frozen;
            },
            // -------------------------------------------------------------
            // :: Enable the terminal
            // -------------------------------------------------------------
            enable: function(silent) {
                if (!enabled && !frozen) {
                    if (num_chars === undefined) {
                        // enabling first time
                        self.resize();
                    }
                    cmd_ready(function ready() {
                        var ret;
                        if (!silent && !enabled) {
                            fire_event('onFocus');
                        }
                        if (!silent && ret === undefined || silent) {
                            enabled = true;
                            if (!self.paused()) {
                                command_line.enable(true);
                            }
                        }
                    });
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: function clear formatting cache if you don't longer need it
            // :: cache is used if option useCache is set to true
            // -------------------------------------------------------------
            clear_cache: 'Map' in root ? function() {
                format_cache.clear();
                string_cache.clear();
                return self;
            } : function() {
                return self;
            },
            // -------------------------------------------------------------
            // :: Disable the terminal
            // -------------------------------------------------------------
            disable: function(silent) {
                cmd_ready(function ready() {
                    var ret;
                    if (!silent && enabled) {
                        ret = fire_event('onBlur');
                    }
                    if (!silent && ret === undefined || silent) {
                        enabled = false;
                        command_line.disable();
                    }
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: return true if the terminal is enabled
            // -------------------------------------------------------------
            enabled: function() {
                return enabled;
            },
            // -------------------------------------------------------------
            // :: Return the terminal signature depending on the size of the terminal
            // -------------------------------------------------------------
            signature: function() {
                var cols = self.cols();
                for (var i = signatures.length; i--;) {
                    var lengths = signatures[i].map(function(line) {
                        return line.length;
                    });
                    if (Math.max.apply(null, lengths) <= cols) {
                        return signatures[i].join('\n') + '\n';
                    }
                }
                return '';
            },
            // -------------------------------------------------------------
            // :: Return the version number
            // -------------------------------------------------------------
            version: function() {
                return $.terminal.version;
            },
            // -------------------------------------------------------------
            // :: Return actual command line object (jquery object with cmd
            // :: methods)
            // -------------------------------------------------------------
            cmd: function() {
                return command_line;
            },
            // -------------------------------------------------------------
            // :: Return the current command entered by terminal
            // -------------------------------------------------------------
            get_command: function() {
                return command_line.get();
            },
            // -------------------------------------------------------------
            // :: echo command and previous prompt (used by echo_newline.js)
            // -------------------------------------------------------------
            echo_command: function(command) {
                return echo_command(command);
            },
            // -------------------------------------------------------------
            // :: Change the command line to the new one
            // -------------------------------------------------------------
            set_command: function(command, silent) {
                when_ready(function ready() {
                    // TODO: refactor to use options - breaking change
                    if (typeof command !== 'string') {
                        command = JSON.stringify(command);
                    }
                    command_line.set(command, undefined, silent);
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Change position of the command line
            // -------------------------------------------------------------
            set_position: function(position, relative) {
                when_ready(function ready() {
                    command_line.position(position, relative);
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Return position of the command line
            // -------------------------------------------------------------
            get_position: function() {
                return command_line.position();
            },
            // -------------------------------------------------------------
            // :: Insert text into the command line after the cursor
            // -------------------------------------------------------------
            insert: function(string, stay) {
                if (typeof string === 'string') {
                    when_ready(function ready() {
                        var bottom = self.is_bottom();
                        command_line.insert(string, stay);
                        if (settings.scrollOnEcho || bottom) {
                            self.scroll_to_bottom();
                        }
                    });
                    return self;
                } else {
                    throw new Error(sprintf(strings().notAString, 'insert'));
                }
            },
            // -------------------------------------------------------------
            // :: Set the prompt of the command line
            // -------------------------------------------------------------
            set_prompt: function(prompt, options) {
                var d = new $.Deferred();
                when_ready(function ready() {
                    var settings = $.extend({
                        typing: false,
                        delay: 100
                    }, options);
                    if (settings.typing) {
                        if (typeof prompt !== 'string') {
                            return d.reject('prompt: Typing animation require string');
                        }
                        if (typeof settings.delay !== 'number' || isNaN(settings.delay)) {
                            return d.reject('echo: Invalid argument, delay need to' +
                                            ' be a number');
                        }
                        var p = self.typing('prompt', settings.delay, prompt, settings);
                        p.then(function() {
                            d.resolve();
                        });
                    } else if (is_function(prompt)) {
                        command_line.prompt(function(callback) {
                            prompt.call(self, callback, self);
                        });
                    } else {
                        command_line.prompt(prompt);
                    }
                    interpreters.top().prompt = prompt;
                });
                if (options && options.typing) {
                    return d.promise();
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Return the prompt used by the terminal
            // -------------------------------------------------------------
            get_prompt: function() {
                return interpreters.top().prompt;
                // command_line.prompt(); - can be a wrapper
                //return command_line.prompt();
            },
            // -------------------------------------------------------------
            // :: Enable or Disable mask depedning on the passed argument
            // :: the mask can also be character (in fact it will work with
            // :: strings longer then one)
            // -------------------------------------------------------------
            set_mask: function(mask) {
                when_ready(function ready() {
                    command_line.mask(mask === true ? settings.maskChar : mask);
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Return the ouput of the terminal as text
            // -------------------------------------------------------------
            get_output: function(raw) {
                if (raw) {
                    return lines;
                } else {
                    return $.map(lines, function(item) {
                        return is_function(item[0]) ? item[0]() : item[0];
                    }).join('\n');
                }
            },
            // -------------------------------------------------------------
            // :: Recalculate and redraw everything
            // -------------------------------------------------------------
            resize: function(width, height) {
                if (!self.is(':visible')) {
                    // delay resize if terminal not visible
                    self.stopTime('resize');
                    self.oneTime(500, 'resize', function() {
                        self.resize(width, height);
                    });
                } else {
                    if (width && height) {
                        self.width(width);
                        self.height(height);
                    }
                    width = self.width();
                    height = self.height();
                    if (typeof settings.numChars !== 'undefined' ||
                        typeof settings.numRows !== 'undefined') {
                        command_line.resize(settings.numChars);
                        self.refresh();
                        fire_event('onResize');
                        return;
                    }
                    var new_num_chars = get_num_chars(self, char_size);
                    var new_num_rows = get_num_rows(self, char_size);
                    // only if number of chars changed
                    if (new_num_chars !== num_chars ||
                        new_num_rows !== num_rows) {
                        self.clear_cache();
                        num_chars = new_num_chars;
                        num_rows = new_num_rows;
                        command_line.resize(num_chars);
                        self.refresh();
                        fire_event('onResize');
                    }
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: redraw the terminal
            // -------------------------------------------------------------
            refresh: function() {
                if (char_size.width !== 0) {
                    self[0].style.setProperty('--char-width', char_size.width);
                }
                redraw({
                    scroll: false,
                    update: true
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Flush the output to the terminal
            // -------------------------------------------------------------
            flush: function(options) {
                options = $.extend({}, {
                    update: false,
                    scroll: true
                }, options || {});
                try {
                    var bottom = self.is_bottom();
                    var wrapper;
                    // print all lines
                    var first = true;
                    var appending_to_partial = false;
                    var partial = $();
                    if (!options.update) {
                        partial = self.find('.partial');
                    }
                    while (output_buffer.length) {
                        var data = output_buffer.shift();
                        if (data === NEW_LINE) {
                            if (!partial.length) {
                                wrapper = $('<div/>');
                            } else if (first) {
                                appending_to_partial = true;
                                wrapper = partial;
                            }
                            first = false;
                        } else if ($.isPlainObject(data) && is_function(data.finalize)) {
                            // this is finalize function from echo
                            if (options.update) {
                                var selector = '> div[data-index=' + data.index + ']';
                                var node = output.find(selector);
                                if (node.html() !== wrapper.html()) {
                                    node.replaceWith(wrapper);
                                }
                            } else {
                                wrapper.appendTo(output);
                            }
                            wrapper.attr('data-index', data.index);
                            appending_to_partial = !data.newline;
                            wrapper.toggleClass('partial', appending_to_partial);
                            data.finalize(wrapper);
                        } else {
                            var line = data.line;
                            var div;
                            if (appending_to_partial) {
                                div = wrapper.children().last().append(line);
                                appending_to_partial = false;
                            } else {
                                div = $('<div/>').html(line);
                                if (data.newline) {
                                    div.addClass('cmd-end-line');
                                }
                                wrapper.append(div);
                            }
                            // width = '100%' does some weird extra magic
                            // that makes the height correct. Any other
                            // value doesn't work.
                            div.css('width', '100%');
                        }
                    }
                    var cmd_prompt = self.find('.cmd-prompt');
                    var cmd_outer = self.find('.cmd');
                    partial = self.find('.partial');
                    if (partial.length === 0) {
                        cmd_prompt.css('margin-left', 0);
                        cmd_outer.css('top', 0);
                        command_line.__set_prompt_margin(0);
                    } else {
                        var last_row = partial.children().last();
                        // Remove width='100%' for two reasons:
                        // 1. so we can measure the width right here
                        // 2. so that the background of this last line of output
                        //    doesn't occlude the first line of input to the right
                        last_row.css('width', '');
                        var last_row_rect = last_row[0].getBoundingClientRect();
                        var partial_width = last_row_rect.width;
                        // Shift command prompt up one line and to the right
                        // enough so that it appears directly next to the
                        // partially constructed output line
                        cmd_prompt.css('margin-left', partial_width);
                        cmd_outer.css('top', -last_row_rect.height);
                        // Measure length of partial line in characters
                        var char_width = self.geometry().char.width;
                        var prompt_margin = Math.round(partial_width / char_width);
                        command_line.__set_prompt_margin(prompt_margin);
                    }
                    limit_lines();
                    fire_event('onFlush');
                    var cmd_cursor = self.find('.cmd-cursor');
                    var offset = self.find('.cmd').offset();
                    var self_offset = self.offset();
                    setTimeout(function() {
                        css(self[0], {
                            '--terminal-height': self.height(),
                            '--terminal-x': offset.left - self_offset.left,
                            '--terminal-y': offset.top - self_offset.top,
                            '--terminal-scroll': self.prop('scrollTop')
                        });
                        // Firefox won't reflow the cursor automatically, so
                        // hide it briefly then reshow it
                        cmd_cursor.hide();
                        setTimeout(function() {
                            cmd_cursor.show();
                        }, 0);
                    }, 0);
                    if ((settings.scrollOnEcho && options.scroll) || bottom) {
                        self.scroll_to_bottom();
                    }
                } catch (e1) {
                    if (is_function(settings.exceptionHandler)) {
                        try {
                            settings.exceptionHandler.call(self, e1, 'TERMINAL (Flush)');
                        } catch (e2) {
                            settings.exceptionHandler = $.noop;
                            alert_exception('[exceptionHandler]', e2);
                        }
                    } else {
                        alert_exception('[Flush]', e1);
                    }
                } finally {
                    output_buffer = [];
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Update the output line - line number can be negative
            // -------------------------------------------------------------
            update: function(line, value, options) {
                when_ready(function ready() {
                    if (line < 0) {
                        line = lines.length + line; // yes +
                    }
                    if (!lines[line]) {
                        self.error('Invalid line number ' + line);
                    } else if (value === null) {
                        lines.splice(line, 1);
                        output.find('[data-index=' + line + ']').remove();
                    } else {
                        value = preprocess_value(value, {
                            update: true,
                            line: line
                        });
                        if (value === false) {
                            return self;
                        }
                        unpromise(value, function(value) {
                            var ret = prepare_render(value, options);
                            if (ret) {
                                value = ret[0];
                                options = ret[1];
                            }
                            lines[line][0] = value;
                            if (options) {
                                lines[line][1] = $.extend(lines[line][1], options);
                            }
                            var next = process_line({
                                value: value,
                                index: line,
                                options: lines[line][1]
                            });
                            // process_line can return a promise
                            // value is function that resolve to promise
                            unpromise(next, function() {
                                // trigger flush even if next is undefined
                                self.flush({
                                    scroll: false,
                                    update: true
                                });
                            });
                        });
                    }
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: convenience method for removing selected line
            // -------------------------------------------------------------
            remove_line: function(line) {
                return self.update(line, null);
            },
            // -------------------------------------------------------------
            // :: return index of last line in case when you need to update
            // :: after something is echo on the terminal
            // -------------------------------------------------------------
            last_index: function() {
                return lines.length - 1;
            },
            // -------------------------------------------------------------
            // :: Print data to the terminal output. It can have options
            // :: * flush - indicate that arg should be send to DOM
            // :: * raw - indicate if it should handle input as html
            // :: * finalize - function call with container div
            // :: * keepWords - inform how to wrap text
            // :: * formatters - inform function if it should use formatters
            // ::   on input string - good to prevent XSS when you want
            // ::   advanced server side controling of terminal
            // :: you can echo: promise, function, strings array or string
            // -------------------------------------------------------------
            echo: function(arg, options) {
                var arg_defined = arguments.length > 0;
                var d = new $.Deferred();
                function echo(arg) {
                    try {
                        var locals = $.extend({
                            flush: true,
                            exec: true,
                            raw: settings.raw,
                            finalize: $.noop,
                            unmount: $.noop,
                            delay: 100,
                            ansi: false,
                            typing: false,
                            keepWords: false,
                            invokeMethods: settings.invokeMethods,
                            onClear: null,
                            formatters: true,
                            allowedAttributes: settings.allowedAttributes,
                            newline: true
                        }, options || {});
                        // finalize function is passed around and invoked
                        // in terminal::flush after content is added to DOM
                        (function(finalize) {
                            locals.finalize = function(div) {
                                if (locals.raw) {
                                    div.addClass('raw');
                                }
                                if (locals.ansi) {
                                    div.addClass('ansi');
                                }
                                try {
                                    if (is_function(finalize)) {
                                        finalize.call(self, div);
                                    }
                                    div.find('img').each(function() {
                                        var self = $(this);
                                        var img = new Image();
                                        img.onerror = function() {
                                            self.replaceWith(use_broken_image);
                                        };
                                        img.src = this.src;
                                    });
                                } catch (e) {
                                    display_exception(e, 'USER:echo(finalize)');
                                    finalize = null;
                                }
                            };
                        })(locals.finalize);
                        if (locals.flush) {
                            // flush buffer if there was no flush after previous echo
                            if (output_buffer.length) {
                                self.flush();
                            }
                        }
                        if (fire_event('onBeforeEcho', [arg]) === false) {
                            return;
                        }
                        if (locals.typing) {
                            if (typeof arg !== 'string') {
                                return d.reject('echo: Typing animation require string' +
                                                ' or promise that resolve to string');
                            }
                            if (typeof locals.delay !== 'number' || isNaN(locals.delay)) {
                                return d.reject('echo: Invalid argument, delay need to' +
                                                ' be a number');
                            }
                            var p = self.typing('echo', locals.delay, arg, locals);
                            p.then(function() {
                                d.resolve();
                            });
                            return;
                        }
                        var value;
                        if (typeof arg === 'function') {
                            value = arg.bind(self);
                        } else if (typeof arg === 'undefined') {
                            if (arg_defined) {
                                value = String(arg);
                            } else {
                                value = '';
                            }
                        } else {
                            var ret = preprocess_value(arg, {});
                            if (ret === false) {
                                return self;
                            }
                            value = ret;
                        }
                        unpromise(value, function(value) {
                            if (render(value, locals)) {
                                return self;
                            }
                            var last_line = lines[lines.length - 1];
                            var last_newline = lines.length === 0 || last_line[1].newline;
                            var index = lines.length;
                            if (!last_newline) {
                                index--;
                            }
                            if (!locals.newline && value[value.length - 1] === '\n') {
                                // This adjusts the value, so that when it updates or
                                // refresh the lines list it does the right thing.
                                value = value.slice(0, -1);
                                locals.newline = true;
                            }
                            var next = process_line({
                                value: value,
                                options: locals,
                                index: index
                            });
                            // queue async functions in echo
                            if (next && next.then) {
                                var defer = new DelayQueue();
                                echo_ready = ready(defer);
                            }
                            // Did previous value end in newline?
                            if (last_newline) {
                                lines.push([value, locals]);
                            } else {
                                // If not append current value to it
                                var old_value = last_line[0];
                                var string_old_val = stringify_value(old_value);
                                var string_val = stringify_value(value);
                                last_line[0] = string_old_val + string_val;
                                // Update newline field
                                last_line[1].newline = locals.newline;
                            }
                            unpromise(next, function() {
                                // extended commands should be processed only
                                // once in echo and not on redraw
                                if (locals.flush) {
                                    self.flush();
                                    fire_event('onAfterEcho', [arg]);
                                }
                                if (defer) {
                                    defer.resolve();
                                    echo_ready = null;
                                }
                            });
                        });
                    } catch (e) {
                        // if echo throw exception we can't use error to
                        // display that exception
                        if (is_function(settings.exceptionHandler)) {
                            settings.exceptionHandler.call(self, e, 'TERMINAL (echo)');
                        } else {
                            alert_exception('[Terminal.echo]', e);
                        }
                    }
                }
                if (arg !== undefined && is_function(arg.then)) {
                    $.when(arg).done(echo).catch(make_label_error('Echo'));
                } else if (echo_ready) {
                    echo_ready(function() {
                        echo(arg);
                    });
                } else {
                    echo(arg);
                }
                if (options && options.typing) {
                    return d.promise();
                }
                return self;
            },
            // -------------------------------------------------------------
            typing: function(type, delay, string, options) {
                var d = new $.Deferred();
                var settings;
                var finish;
                if (typeof options === 'object') {
                    finish = options.finalize || $.noop;
                    settings = $.extend({}, options, {
                        delay: delay,
                        finalize: done
                    });
                } else {
                    finish = options || $.noop;
                    settings = {
                        delay: delay,
                        finalize: done
                    };
                }
                function done() {
                    d.resolve();
                    if (is_function(finish)) {
                        finish.apply(self, arguments);
                    }
                }
                when_ready(function ready() {
                    if (['prompt', 'echo', 'enter'].indexOf(type) >= 0) {
                        if (type === 'prompt') {
                            typed_prompt(string, settings);
                        } else if (type === 'echo') {
                            typed_message(string, settings);
                        } else if (type === 'enter') {
                            var prompt = self.get_prompt();
                            if (typeof prompt === 'function') {
                                prompt(function(prompt) {
                                    typed_enter(prompt, string, settings);
                                });
                            } else {
                                typed_enter(prompt, string, settings);
                            }
                        }
                    } else {
                        d.reject('Invalid type only `echo` and `prompt` are supported');
                    }
                });
                return d.promise();
            },
            // -------------------------------------------------------------
            // :: echo red text
            // -------------------------------------------------------------
            error: function(message, options) {
                options = $.extend({}, options, {raw: false, formatters: false});
                function format(string) {
                    if (typeof string !== 'string') {
                        string = String(string);
                    }
                    // quick hack to fix trailing backslash
                    var str = $.terminal.escape_brackets(string).
                        replace(/\\$/, '&#92;').
                        replace(url_re, ']$1[[;;;terminal-error]');
                    return '[[;;;terminal-error]' + str + ']';
                }
                if (typeof message === 'function') {
                    return self.echo(function() {
                        return format(message.call(self));
                    }, options);
                }
                if (message && message.then) {
                    message.then(function(string) {
                        self.echo(format(string));
                    }).catch(make_label_error('Echo Error'));
                    return self;
                }
                return self.echo(format(message), options);
            },
            // -------------------------------------------------------------
            // :: Display Exception on terminal
            // -------------------------------------------------------------
            exception: function(e, label) {
                var message = exception_message(e);
                if (label) {
                    message = '&#91;' + label + '&#93;: ' + message;
                }
                if (message) {
                    self.error(message, {
                        finalize: function(div) {
                            div.addClass('terminal-exception terminal-message');
                        },
                        keepWords: true
                    });
                }
                if (typeof e.fileName === 'string') {
                    // display filename and line which throw exeption
                    self.pause(settings.softPause);
                    $.get(e.fileName, function(file) {
                        var num = e.lineNumber - 1;
                        var line = file.split('\n')[num];
                        if (line) {
                            self.error('[' + e.lineNumber + ']: ' + line);
                        }
                        self.resume();
                    }, 'text');
                }
                if (e.stack) {
                    var stack = $.terminal.escape_brackets(e.stack);
                    self.echo(stack.split(/\n/g).map(function(trace) {
                        // nested formatting will handle urls but that formatting
                        // can be removed - this code was created before
                        // that formatting existed (see commit ce01c3f5)
                        return '[[;;;terminal-error]' +
                            trace.replace(url_re, function(url) {
                                return ']' + url + '[[;;;terminal-error]';
                            }) + ']';
                    }).join('\n'), {
                        finalize: function(div) {
                            div.addClass('terminal-exception terminal-stack-trace');
                        },
                        formatters: false
                    });
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Scroll Div that holds the terminal
            // -------------------------------------------------------------
            scroll: function(amount) {
                var pos;
                amount = Math.round(amount);
                if (self.prop) { // work with jQuery > 1.6
                    if (amount > self.prop('scrollTop') && amount > 0) {
                        self.prop('scrollTop', 0);
                    }
                    pos = self.prop('scrollTop');
                    self.scrollTop(pos + amount);
                } else {
                    if (amount > self.prop('scrollTop') && amount > 0) {
                        self.prop('scrollTop', 0);
                    }
                    pos = self.prop('scrollTop');
                    self.scrollTop(pos + amount);
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Exit all interpreters and logout. The function will throw
            // :: exception if there is no login provided
            // -------------------------------------------------------------
            logout: function(local) {
                if (in_login) {
                    throw new Error(sprintf(strings().notWhileLogin, 'logout'));
                }
                when_ready(function ready() {
                    if (local) {
                        var login = logins.pop();
                        self.set_token(undefined, true);
                        self.login.apply(self, login);
                    } else if (interpreters.size() === 1 && self.token()) {
                        self.logout(true);
                    } else {
                        while (interpreters.size() > 1) {
                            // pop will call global_logout that will call login
                            // and size will be > 0; this is workaround the problem
                            if (self.token()) {
                                self.logout(true).pop().pop();
                            } else {
                                self.pop();
                            }
                        }
                    }
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Function returns the token returned by callback function
            // :: in login function. It does nothing (return undefined) if
            // :: there is no login
            // -------------------------------------------------------------
            token: function(local) {
                return storage.get(self.prefix_name(local) + '_token');
            },
            // -------------------------------------------------------------
            // :: Function sets the token to the supplied value. This function
            // :: works regardless of wherer settings.login is supplied
            // -------------------------------------------------------------
            set_token: function(token, local) {
                var name = self.prefix_name(local) + '_token';
                if (typeof token === 'undefined') {
                    storage.remove(name);
                } else {
                    storage.set(name, token);
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Function get the token either set by the login method or
            // :: by the set_token method.
            // -------------------------------------------------------------
            get_token: function(local) {
                return self.token(local);
            },
            // -------------------------------------------------------------
            // :: Function return Login name entered by the user
            // -------------------------------------------------------------
            login_name: function(local) {
                return storage.get(self.prefix_name(local) + '_login');
            },
            // -------------------------------------------------------------
            // :: Function returns the name of current interpreter
            // -------------------------------------------------------------
            name: function() {
                return interpreters.top().name;
            },
            // -------------------------------------------------------------
            // :: Function return prefix name for login/token
            // -------------------------------------------------------------
            prefix_name: function(local) {
                var name = (settings.name ? settings.name + '_' : '') +
                    terminal_id;
                if (local && interpreters.size() > 1) {
                    var local_name = interpreters.map(function(intrp) {
                        return intrp.name || '';
                    }).slice(1).join('_');
                    if (local_name) {
                        name += '_' + local_name;
                    }
                }
                return name;
            },
            // -------------------------------------------------------------
            // :: wrapper for common use case
            // -------------------------------------------------------------
            read: function(message, success, cancel) {
                var options;
                if (typeof arguments[1] === 'object') {
                    options = $.extend({
                        typing: false,
                        delay: 100,
                        success: $.noop,
                        cancel: $.noop
                    }, arguments[1]);
                } else {
                    options = {
                        typing: false,
                        success: success || $.noop,
                        cancel: cancel || $.noop
                    };
                }
                if (options.typing) {
                    var prompt = self.get_prompt();
                    options.typing = false;
                    return self.typing('prompt', options.delay, message).then(function() {
                        return self.set_prompt(prompt).read(message, options);
                    });
                }
                // return from read() should not pause terminal
                force_awake = true;
                var defer = jQuery.Deferred();
                var read = false;
                self.push(function(string) {
                    read = true;
                    defer.resolve(string);
                    if (is_function(options.success)) {
                        options.success(string);
                    }
                    self.pop();
                    if (settings.history) {
                        command_line.history().enable();
                    }
                }, {
                    name: 'read',
                    history: false,
                    prompt: message || '',
                    onExit: function() {
                        if (!read) {
                            defer.reject();
                            if (is_function(options.cancel)) {
                                options.cancel();
                            }
                        }
                    }
                });
                if (settings.history) {
                    command_line.history().disable();
                }
                return defer.promise();
            },
            // -------------------------------------------------------------
            // :: Push a new interenter on the Stack
            // -------------------------------------------------------------
            push: function(interpreter, options) {
                cmd_ready(function ready() {
                    options = options || {};
                    var defaults = {
                        infiniteLogin: false
                    };
                    var push_settings = $.extend({}, defaults, options);
                    if (!push_settings.name && prev_command) {
                        // name the interpreter from last command
                        push_settings.name = prev_command.name;
                    }
                    if (push_settings.prompt === undefined) {
                        push_settings.prompt = (push_settings.name || '>') + ' ';
                    }
                    // names.push(options.name);
                    var top = interpreters.top();
                    if (top) {
                        top.mask = command_line.mask();
                    }
                    var was_paused = paused;
                    function init() {
                        fire_event('onPush', [top, interpreters.top()]);
                        prepare_top_interpreter();
                    }
                    //self.pause();
                    make_interpreter(interpreter, options.login, function(ret) {
                        // result is object with interpreter and completion properties
                        interpreters.push($.extend({}, ret, push_settings));
                        if (push_settings.completion === true) {
                            if ($.isArray(ret.completion)) {
                                interpreters.top().completion = ret.completion;
                            } else if (!ret.completion) {
                                interpreters.top().completion = false;
                            }
                        }
                        if (push_settings.login) {
                            var error;
                            var type = get_type(push_settings.login);
                            if (type === 'function') {
                                error = push_settings.infiniteLogin ? $.noop : self.pop;
                                self.login(
                                    push_settings.login,
                                    push_settings.infiniteLogin,
                                    init,
                                    error
                                );
                            } else if (get_type(interpreter) === 'string' &&
                                       type === 'string' || type === 'boolean') {
                                error = push_settings.infiniteLogin ? $.noop : self.pop;
                                self.login(
                                    make_json_rpc_login(
                                        interpreter,
                                        push_settings.login
                                    ),
                                    push_settings.infiniteLogin,
                                    init,
                                    error
                                );
                            }
                        } else {
                            init();
                        }
                        if (!was_paused && self.enabled()) {
                            self.resume();
                        }
                    });
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Remove the last interpreter from the Stack
            // -------------------------------------------------------------
            pop: function(string, silent) {
                if (string !== undefined) {
                    echo_command(string);
                }
                var token = self.token(true);
                var top;
                if (interpreters.size() === 1) {
                    top = interpreters.top();
                    if (settings.login) {
                        if (!silent) {
                            fire_event('onPop', [top, null]);
                        }
                        global_logout();
                        fire_event('onExit');
                    } else {
                        self.error(strings().canExitError);
                    }
                } else {
                    if (token) {
                        clear_loging_storage();
                    }
                    var current = interpreters.pop();
                    top = interpreters.top();
                    prepare_top_interpreter();
                    // restore mask
                    self.set_mask(top.mask);
                    if (!silent) {
                        fire_event('onPop', [current, top]);
                    }
                    // we check in case if you don't pop from password interpreter
                    if (in_login && self.get_prompt() !== strings().login + ': ') {
                        in_login = false;
                    }
                    if (is_function(current.onExit)) {
                        try {
                            current.onExit.call(self, self);
                        } catch (e) {
                            current.onExit = $.noop;
                            display_exception(e, 'onExit');
                        }
                    }
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: Change terminal option(s) at runtime
            // -------------------------------------------------------------
            option: function(object_or_name, value) {
                if (typeof value === 'undefined') {
                    if (typeof object_or_name === 'string') {
                        return settings[object_or_name];
                    } else if (typeof object_or_name === 'object') {
                        $.each(object_or_name, function(key, value) {
                            settings[key] = value;
                        });
                    }
                } else {
                    settings[object_or_name] = value;
                    if (object_or_name.match(/^num(Chars|Rows)$/)) {
                        redraw();
                    }
                }
                return self;
            },
            // -------------------------------------------------------------
            // :: invoke keydown shorcut
            // -------------------------------------------------------------
            invoke_key: function(shortcut) {
                command_line.invoke_key(shortcut);
                return self;
            },
            // -------------------------------------------------------------
            // :: change terminal keymap at runtime
            // -------------------------------------------------------------
            keymap: function(keymap, fn) {
                if (arguments.length === 0) {
                    return command_line.keymap();
                }
                if (typeof fn === 'undefined') {
                    if (typeof keymap === 'string') {
                        return command_line.keymap(keymap);
                    } else if ($.isPlainObject(keymap)) {
                        // argument is an object
                        keymap = $.extend(
                            {},
                            terminal_init_keymap,
                            $.omap(keymap || {}, function(key, fn) {
                                if (!terminal_init_keymap[key]) {
                                    return fn.bind(self);
                                }
                                return function(e, original) {
                                    // new keymap function will get default as 2nd arg
                                    return fn.call(self, e, function() {
                                        return terminal_init_keymap[key](e, original);
                                    });
                                };
                            })
                        );
                        command_line.keymap(null).keymap(keymap);
                    }
                } else if (typeof fn === 'function') {
                    var key = keymap;
                    if (!terminal_init_keymap[key]) {
                        command_line.keymap(key, fn.bind(self));
                    } else {
                        command_line.keymap(key, function(e, original) {
                            return fn.call(self, e, function() {
                                return terminal_init_keymap[key](e, original);
                            });
                        });
                    }
                }
            },
            // -------------------------------------------------------------
            // :: Return how deep you are in nested interpreters
            // -------------------------------------------------------------
            level: function() {
                return interpreters.size();
            },
            // -------------------------------------------------------------
            // :: Reinitialize the terminal
            // -------------------------------------------------------------
            reset: function() {
                when_ready(function ready() {
                    self.clear();
                    while (interpreters.size() > 1) {
                        interpreters.pop();
                    }
                    initialize();
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Remove all local storage left by terminal, it will not
            // :: logout you until you refresh the browser
            // -------------------------------------------------------------
            purge: function() {
                when_ready(function ready() {
                    var prefix = self.prefix_name() + '_';
                    var names = storage.get(prefix + 'interpreters');
                    if (names) {
                        $.each(JSON.parse(names), function(_, name) {
                            storage.remove(name + '_commands');
                            storage.remove(name + '_token');
                            storage.remove(name + '_login');
                        });
                    }
                    command_line.purge();
                    storage.remove(prefix + 'interpreters');
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: Remove all events and DOM nodes left by terminal, it will
            // :: not purge the terminal so you will have the same state
            // :: when you refresh the browser
            // -------------------------------------------------------------
            destroy: function() {
                when_ready(function ready() {
                    command_line.destroy().remove();
                    self.resizer('unbind');
                    self.touch_scroll('unbind');
                    font_resizer.resizer('unbind').remove();
                    $(document).unbind('.terminal_' + self.id());
                    $(window).unbind('.terminal_' + self.id());
                    self.unbind('click wheel mousewheel mousedown mouseup');
                    self.removeData('terminal').removeClass('terminal').
                        unbind('.terminal');
                    if (settings.width) {
                        self.css('width', '');
                    }
                    if (settings.height) {
                        self.css('height', '');
                    }
                    $(window).off('blur', blur_terminal).
                        off('focus', focus_terminal);
                    self.find('.terminal-fill, .terminal-font').remove();
                    self.stopTime();
                    terminals.remove(terminal_id);
                    if (visibility_observer) {
                        if (visibility_observer.unobserve) {
                            visibility_observer.unobserve(self[0]);
                        } else {
                            clearInterval(visibility_observer);
                        }
                    }
                    var scroll_marker = self.find('.terminal-scroll-marker');
                    if (is_bottom_observer) {
                        is_bottom_observer.unobserve(scroll_marker[0]);
                    }
                    scroll_marker.remove();
                    if (mutation_observer) {
                        mutation_observer.disconnect();
                    }
                    if (!terminals.length()) {
                        $(window).off('hashchange');
                    }
                    if (is_mobile) {
                        self.off([
                            'touchstart.terminal',
                            'touchmove.terminal',
                            'touchend.terminal'
                        ].join(' '));
                    }
                    output.remove();
                    wrapper.remove();
                    if (body_terminal) {
                        var $body = $(body_terminal);
                        if ($body.attr('class') === 'full-screen-terminal') {
                            $body.removeAttr('class');
                        } else {
                            $body.removeClass('full-screen-terminal');
                        }
                        self.remove();
                    }
                    defunct = true;
                });
                return self;
            },
            // -------------------------------------------------------------
            // :: ref: https://stackoverflow.com/a/18927969/387194
            // -------------------------------------------------------------
            scroll_to: function(elem) {
                var scroll = self.scrollTop() - self.offset().top + $(elem).offset().top;
                self.scrollTop(scroll);
                return self;
            },
            // -------------------------------------------------------------
            scroll_to_bottom: function() {
                var scrollHeight;
                if (self.prop) {
                    scrollHeight = self.prop('scrollHeight');
                } else {
                    scrollHeight = self.attr('scrollHeight');
                }
                self.scrollTop(scrollHeight);
                return self;
            },
            // -------------------------------------------------------------
            // :: return true if terminal div or body is at the bottom
            // :: is use scrollBottomOffset option as margin for the check
            // -------------------------------------------------------------
            is_bottom: function() {
                if (settings.scrollBottomOffset === -1) {
                    return false;
                } else if (typeof is_bottom_detected === 'boolean') {
                    return is_bottom_detected;
                } else {
                    var scroll_height, scroll_top, height;
                    scroll_height = self[0].scrollHeight;
                    scroll_top = self[0].scrollTop;
                    height = self[0].offsetHeight;
                    var limit = scroll_height - settings.scrollBottomOffset;
                    return scroll_top + height > limit;
                }
            }
        }, function(name, fun) {
            // wrap all functions and display execptions
            return function() {
                if (defunct) {
                    if (!settings.exceptionHandler) {
                        throw new $.terminal.Exception(strings().defunctTerminal);
                    }
                }
                try {
                    return fun.apply(self, [].slice.apply(arguments));
                } catch (e) {
                    // exec catch by command (resume call exec)
                    if (name !== 'exec' && name !== 'resume') {
                        display_exception(e, e.type || 'TERMINAL', true);
                    }
                    if (!settings.exceptionHandler) {
                        throw e;
                    }
                }
            };
        }));
        // -----------------------------------------------------------------
        // :: INIT CODE
        // -----------------------------------------------------------------
        if (self.length === 0) {
            var msg = sprintf(strings().invalidSelector);
            throw new $.terminal.Exception(msg);
        }
        self.data('terminal', self);
        // synchronize the echo calls (used for async functions) that need
        // to be called in order
        var echo_ready;
        // var names = []; // stack if interpreter names
        var prev_command; // used for name on the terminal if not defined
        var prev_exec_cmd;
        var tab_count = 0; // for tab completion
        var output; // .terminal-output jquery object
        var terminal_id = terminals.length();
        var force_awake = false; // flag used to don't pause when user return read() call
        var num_chars; // numer of chars in line
        var num_rows; // number of lines that fit without scrollbar
        var command; // for tab completion
        var logins = new Stack(); // stack of logins
        var command_queue = new DelayQueue();
        var animating = false; // true on typing animation
        var init_queue = new DelayQueue();
        var when_ready = ready(init_queue);
        var cmd_ready = ready(command_queue);
        var is_bottom_detected;
        var is_bottom_observer;
        var in_login = false;// some Methods should not be called when login
        // TODO: Try to use mutex like counter for pause/resume
        var onPause = $.noop;// used to indicate that user call pause onInit
        var old_width, old_height;
        var delayed_commands = []; // used when exec commands while paused
        var settings = $.extend(
            {},
            $.terminal.defaults,
            {
                name: self.selector,
                exit: !!(options && options.login || !options)
            },
            options || {}
        );
        if (typeof settings.width === 'number') {
            self.width(settings.width);
        }
        if (typeof settings.height === 'number') {
            self.height(settings.height);
        }
        var char_size = get_char_size(self);
        // this is needed when terminal have selector with --size that is not
        // bare .terminal so fake terminal will not get the proper size #602
        var need_char_size_recalculate = !terminal_ready(self);
        // so it's the same as in TypeScript definition for options
        delete settings.formatters;
        // used to throw error when calling methods on destroyed terminal
        var defunct = false;
        var lines = [];
        var storage = new StorageHelper(settings.memory);
        var enabled = settings.enabled;
        var frozen = false;
        var paused = false;
        var autologin = true; // set to false if onBeforeLogin return false
        var interpreters;
        var command_line;
        var old_enabled;
        var visibility_observer;
        var mutation_observer;
        // backward compatibility
        if (settings.ignoreSystemDescribe === true) {
            settings.describe = false;
        }
        // register ajaxSend for cancel requests on CTRL+D
        $(document).bind('ajaxSend.terminal_' + self.id(), function(e, xhr) {
            requests.push(xhr);
        });
        var wrapper = $('<div class="terminal-wrapper"/>').appendTo(self);
        $(broken_image).hide().appendTo(wrapper);
        var font_resizer = $('<div class="terminal-font">&nbsp;</div>').appendTo(self);
        var fill = $('<div class="terminal-fill"/>').appendTo(self);
        output = $('<div>').addClass('terminal-output').attr('role', 'log')
            .appendTo(wrapper);
        self.addClass('terminal');
        // before login event
        if (settings.login && fire_event('onBeforeLogin') === false) {
            autologin = false;
        }
        // create json-rpc authentication function
        var base_interpreter;
        if (typeof init_interpreter === 'string') {
            base_interpreter = init_interpreter;
        } else if (is_array(init_interpreter)) {
            // first JSON-RPC
            for (var i = 0, len = init_interpreter.length; i < len; ++i) {
                if (typeof init_interpreter[i] === 'string') {
                    base_interpreter = init_interpreter[i];
                    break;
                }
            }
        }
        var global_login_fn;
        if (is_function(settings.login)) {
            global_login_fn = settings.login;
        } else if (base_interpreter &&
            (typeof settings.login === 'string' || settings.login === true)) {
            global_login_fn = make_json_rpc_login(base_interpreter, settings.login);
        }
        terminals.append(self);
        function focus_terminal() {
            if (old_enabled) {
                self.focus();
                self.scroll_to_bottom();
            }
        }
        // -------------------------------------------------------------------------------
        function blur_terminal() {
            old_enabled = enabled;
            self.disable().find('.cmd textarea').trigger('blur', [true]);
        }
        // -------------------------------------------------------------------------------
        function stringify_value(value) {
            if (is_function(value)) {
                value = value();
            }
            if (value && is_function(value.then)) {
                return value.then(stringify_value);
            }
            if (get_type(value) !== 'string') {
                if (is_function(settings.parseObject)) {
                    var ret = settings.parseObject(value);
                    if (get_type(ret) === 'string') {
                        value = ret;
                    }
                } else if (is_array(value)) {
                    value = $.terminal.columns(value, self.cols(), settings.tabs);
                } else {
                    value = String(value);
                }
            }
            return value;
        }
        // -------------------------------------------------------------------------------
        function context_callback_proxy(fn) {
            if (fn.proxy) {
                return fn;
            }
            var wrapper = function(callback) {
                return fn.call(self, callback, self);
            };
            wrapper.proxy = true;
            return wrapper;
        }
        // -------------------------------------------------------------------------------
        // paste event is not testable in node
        // istanbul ignore next
        function paste_event(e) {
            e = e.originalEvent;
            // we don't care about browser that don't support clipboard data
            // those browser simple will not have this feature normal paste
            // is cross-browser and it's handled by cmd plugin
            function is_type(item, type) {
                return item.type.indexOf(type) !== -1;
            }
            function echo_image(image) {
                self.echo('<img src="' + image + '"/>', {raw: true});
            }
            function data_uri(blob) {
                var URL = window.URL || window.webkitURL;
                return URL.createObjectURL(blob);
            }
            function echo(object, ignoreEvents) {
                if (!ignoreEvents) {
                    var event = {
                        target: self
                    };
                    if (typeof object === 'string') {
                        event.text = object;
                    } else if (object instanceof Blob) {
                        event.image = data_uri(object);
                    }
                    var ret = fire_event('onPaste', [event]);
                    if (ret) {
                        if (is_function(ret.then || ret.done)) {
                            return (ret.then || ret.done).call(ret, function(ret) {
                                echo(ret, true);
                            });
                        } else {
                            echo(ret, true);
                        }
                    } else if (ret !== false) {
                        echo(event.image || event.text, true);
                    }
                } else if (object instanceof Blob) {
                    echo_image(data_uri(object));
                } else if (typeof object === 'string') {
                    if (object.match(/^(data:|blob:)/)) {
                        echo_image(object);
                    } else {
                        self.insert(object);
                    }
                }
            }
            if (e.clipboardData) {
                if (self.enabled()) {
                    var items = e.clipboardData.items;
                    if (items) {
                        for (var i = 0; i < items.length; i++) {
                            if (is_type(items[i], 'image') && settings.pasteImage) {
                                var blob = items[i].getAsFile();
                                echo(blob);
                            } else if (is_type(items[i], 'text/plain')) {
                                items[i].getAsString(function(text) {
                                    echo(text.replace(/\r/g, ''));
                                });
                            }
                        }
                    } else if (e.clipboardData.getData) {
                        var text = e.clipboardData.getData('text/plain');
                        echo(text.replace(/\r/g, ''));
                    }
                    return false;
                }
            }
        }
        $(document).on('paste.terminal_' + self.id(), paste_event);
        var terminal_init_keymap = $.extend(
            {},
            keymap,
            $.omap(settings.keymap || {}, function(key, fn) {
                if (!keymap[key]) {
                    return fn.bind(self);
                }
                return function(e, original) {
                    // new keymap function will get default as 2nd argument
                    return fn.call(self, e, function() {
                        return keymap[key](e, original);
                    });
                };
            })
        );
        make_interpreter(init_interpreter, settings.login, function(interpreter) {
            if (settings.completion && typeof settings.completion !== 'boolean' ||
                !settings.completion) {
                // overwrite interpreter completion by global setting #224
                // we use string to indicate that it need to be taken from settings
                // so we are able to change it using option API method
                interpreter.completion = 'settings';
            }
            var prompt = settings.prompt;
            if (is_function(prompt)) {
                prompt = context_callback_proxy(prompt);
            }
            interpreters = new Stack($.extend({}, settings.extra, {
                name: settings.name,
                prompt: prompt,
                keypress: settings.keypress,
                keydown: settings.keydown,
                resize: settings.onResize,
                greetings: settings.greetings,
                mousewheel: settings.mousewheel,
                history: settings.history,
                keymap: terminal_init_keymap
            }, interpreter));
            // CREATE COMMAND LINE
            command_line = $('<div/>').appendTo(wrapper).cmd({
                tabindex: settings.tabindex,
                mobileDelete: settings.mobileDelete,
                mobileIngoreAutoSpace: settings.mobileIngoreAutoSpace,
                prompt: global_login_fn ? false : prompt,
                history: settings.memory ? 'memory' : settings.history,
                historyFilter: settings.historyFilter,
                historySize: settings.historySize,
                caseSensitiveSearch: settings.caseSensitiveSearch,
                onPaste: settings.onPaste,
                width: '100%',
                enabled: false,
                char_width: char_size.width,
                keydown: key_down,
                keymap: terminal_init_keymap,
                clickTimeout: settings.clickTimeout,
                holdTimeout: settings.holdTimeout,
                holdRepeatTimeout: settings.holdRepeatTimeout,
                repeatTimeoutKeys: settings.repeatTimeoutKeys,
                allowedAttributes: settings.allowedAttributes,
                keypress: key_press,
                tabs: settings.tabs,
                onPositionChange: function() {
                    var args = [].slice.call(arguments);
                    make_cursor_visible();
                    fire_event('onPositionChange', args);
                },
                onCommandChange: function(command) {
                    // resize is not triggered when insert called just after init
                    //  and scrollbar appear
                    if (old_width !== fill.width()) {
                        // resizer handler will update old_width
                        self.resizer();
                    }
                    fire_event('onCommandChange', [command]);
                    make_cursor_visible();
                },
                commands: commands
            });
            function disable(e) {
                if (is_mobile) {
                    return;
                }
                e = e.originalEvent;
                if (e) {
                    // e.terget is body when click outside of context menu to close it
                    // even if you click on terminal
                    var node = document.elementFromPoint(e.clientX, e.clientY);
                    if (!$(node).closest('.terminal').length && self.enabled()) {
                        // we only need to disable when click outside of terminal
                        // click on other terminal is handled by focus event
                        self.disable();
                    }
                }
            }
            self.oneTime(100, function() {
                $(document).bind('click.terminal_' + self.id(), disable).
                    bind('contextmenu.terminal_' + self.id(), disable);
            });
            var $win = $(window);
            // cordova application, if keyboard was open and we resume, it will be
            // closed so we need to disable terminal so you can enable it with tap
            document.addEventListener("resume", function() {
                self.disable();
            });
            // istanbul ignore next
            if (is_mobile) {
                (function() {
                    self.addClass('terminal-mobile');
                    var start;
                    var move;
                    var enabled;
                    var SENSITIVITY = 3;
                    var clip = command_line.clip();
                    var HOLD_TIME = 200;
                    var timer;
                    clip.$node.off('touchstart.cmd');
                    self.on('touchstart.terminal', function(e) {
                        e = e.originalEvent;
                        window.touch_event = e;
                        if (e.target.tagName.toLowerCase() === 'a') {
                            return;
                        }
                        if (!frozen && e.touches.length === 1) {
                            enabled = self.enabled();
                            var point = e.touches[0];
                            start = {
                                x: point.clientX,
                                y: point.clientY
                            };
                            timer = setTimeout(function() {
                                start = null;
                            }, HOLD_TIME);
                        }
                    }).on('touchmove.terminal', function(e) {
                        if (e.touches.length === 1 && start) {
                            var point = e.touches[0];
                            var diff_x = Math.abs(point.clientX - start.x);
                            var diff_y = Math.abs(point.clientY - start.y);
                            if (diff_x > SENSITIVITY || diff_y > SENSITIVITY) {
                                move = true;
                            }
                        }
                    }).on('touchend.terminal', function() {
                        if (start) {
                            clearTimeout(timer);
                            if (!move) {
                                if (!enabled) {
                                    clip.focus();
                                    self.focus();
                                } else {
                                    clip.blur();
                                    self.disable();
                                }
                            }
                        }
                        move = false;
                        start = null;
                    });
                })();
            } else {
                // work weird on mobile
                $win.on('focus.terminal_' + self.id(), focus_terminal).
                    on('blur.terminal_' + self.id(), blur_terminal);
                // context is used to check if terminal should not scroll to bottom
                // after right click on  e.g. img, canvas, a and then click to hide
                // the menu. The problem is that right click on those elements don't
                // move the textarea to show proper context menu like save as on images
                // or open on links. See #644 bug
                var was_ctx_event;
                // detect mouse drag
                (function() {
                    var count = 0;
                    var $target;
                    var name = 'click_' + self.id();
                    var textarea = self.find('.cmd textarea');
                    function click() {
                        if ($target.is('.terminal') ||
                            $target.is('.terminal-wrapper')) {
                            var len = self.get_command().length;
                            self.set_position(len);
                        } else if ($target.closest('.cmd-prompt').length) {
                            self.set_position(0);
                        }
                        if (!textarea.is(':focus')) {
                            textarea.focus();
                        }
                        reset();
                    }
                    function reset() {
                        count = 0;
                        $target = null;
                    }
                    var ignore_elements = '.terminal-output textarea,' +
                        '.terminal-output input';
                    self.mousedown(function(e) {
                        if (!scrollbar_event(e, fill)) {
                            $target = $(e.target);
                        }
                    }).mouseup(function() {
                        if (was_ctx_event) {
                            was_ctx_event = false;
                            return;
                        }
                        if ($target && $target.closest(ignore_elements).length) {
                            if (enabled) {
                                self.disable();
                            }
                        } else if (get_selected_html() === '' && $target) {
                            if (++count === 1) {
                                if (!frozen) {
                                    if (!enabled) {
                                        self.focus();
                                        self.scroll_to_bottom();
                                    } else {
                                        var timeout = settings.clickTimeout;
                                        self.oneTime(timeout, name, click);
                                        return;
                                    }
                                }
                            } else {
                                self.stopTime(name);
                            }
                        }
                        reset();
                    }).dblclick(function() {
                        reset();
                        self.stopTime(name);
                    });
                })();
                (function() {
                    var $clip = command_line.clip().$node;
                    function is_context_event(e) {
                        return e.type === 'mousedown' && e.buttons === 2 ||
                            e.type === 'contextmenu';
                    }
                    var event_name;
                    if ('oncontextmenu' in window) {
                        event_name = 'contextmenu.terminal';
                    } else {
                        event_name = 'mousedown.terminal';
                    }
                    self.on(event_name, function(e) {
                        was_ctx_event = get_selected_html() === '' && is_context_event(e);
                        if (was_ctx_event) {
                            var $target = $(e.target);
                            if ($target.is('img,value,audio,object,canvas,a')) {
                                return;
                            }
                            if (!self.enabled()) {
                                self.enable();
                            }
                            var cmd_offset = command_line.offset();
                            var cmd_rect = command_line[0].getBoundingClientRect();
                            var self_offset = self.offset();
                            var top_limit = self_offset.top - cmd_offset.top;
                            var top = Math.max(e.pageY - cmd_offset.top - 20, top_limit);
                            var left = e.pageX - cmd_offset.left - 20;
                            var height = 4 * 14;
                            var width = 5 * 14;
                            var rect = self[0].getBoundingClientRect();
                            // we need width without scrollbar
                            var content_width = fill.outerWidth();
                            // fix jumping when click near bottom or left edge #592
                            var diff_h = (top + cmd_rect.top + height);
                            diff_h = diff_h - rect.height - rect.top;
                            var diff_w = (left + cmd_rect.left + width);
                            // in Chrome scrollbar is added even when width
                            // of textarea is smaller, adding 1px solved the issue
                            diff_w = diff_w - content_width - rect.left;
                            if (diff_h > 0) {
                                height -= Math.ceil(diff_h);
                            }
                            if (diff_w > 0) {
                                width -= Math.ceil(diff_w);
                            }
                            $clip.attr('style', [
                                'left:' + left + 'px !important',
                                'top:' + top + 'px !important',
                                'width:' + width + 'px !important',
                                'height:' + height + 'px !important'
                            ].join(';'));
                            if (!$clip.is(':focus')) {
                                $clip.focus();
                            }
                            self.stopTime('textarea');
                            self.oneTime(100, 'textarea', function() {
                                var props = {
                                    left: '',
                                    top: '',
                                    width: '',
                                    height: ''
                                };
                                if (!is_css_variables_supported) {
                                    var in_line = self.find('.cmd .cmd-cursor-line')
                                        .prevUntil('.cmd-prompt').length;
                                    props.top = in_line * 14 + 'px';
                                }
                                $clip.css(props);
                            });
                            self.stopTime('selection');
                            self.everyTime(20, 'selection', function() {
                                if ($clip[0].selection !== $clip[0].value) {
                                    if (get_textarea_selection($clip[0])) {
                                        clear_textarea_selection($clip[0]);
                                        select(
                                            self.find('.terminal-output')[0],
                                            self.find('.cmd div:last-of-type')[0]
                                        );
                                        self.stopTime('selection');
                                    }
                                }
                            });
                        }
                    });
                })();
                self.on('scroll', function() {
                    var $textarea = self.find('textarea');
                    var rect = self[0].getBoundingClientRect();
                    var height = self[0].scrollHeight;
                    var scrollTop = self.scrollTop();
                    var diff = height - (scrollTop + rect.height);
                    // if scrolled to bottom top need to be aligned with cursor line
                    // done by CSS file using css variables
                    if (diff === 0) {
                        $textarea.css('top', '');
                    } else {
                        $textarea.css('top', -diff);
                    }
                });
            }
            self.on('click', 'a', function(e) {
                var $this = $(this);
                if ($this.closest('.terminal-exception').length) {
                    var href = $this.attr('href');
                    if (href.match(/:[0-9]+$/)) { // display line if specified
                        e.preventDefault();
                        print_line(href, self.cols());
                    }
                }
                // refocus because links have tabindex in case where user want
                // tab change urls, we can ignore this function on click
                if (enabled) {
                    self.find('.cmd textarea').focus();
                }
            });
            function calculate_char_size() {
                var width = char_size.width;
                char_size = get_char_size(self);
                if (width !== char_size.width) {
                    command_line.option('char_width', char_size.width).refresh();
                }
            }
            resize();
            function resize() {
                if (self.is(':visible')) {
                    var width = fill.width();
                    var height = fill.height();
                    if (need_char_size_recalculate) {
                        need_char_size_recalculate = !terminal_ready(self);
                        calculate_char_size();
                    }
                    // prevent too many calculations in IE
                    if (old_height !== height || old_width !== width) {
                        self.resize();
                    }
                    old_height = height;
                    old_width = width;
                }
            }
            function create_resizers() {
                var options = {
                    prefix: 'terminal-'
                };
                self.resizer('unbind').resizer(resize, options);
                font_resizer.resizer('unbind').resizer(function() {
                    calculate_char_size();
                    self.resize();
                }, options);
            }
            function bottom_detect(intersections) {
                is_bottom_detected = intersections[0].intersectionRatio === 1;
            }
            function create_bottom_detect() {
                if (window.IntersectionObserver) {
                    var top = $('<div class="terminal-scroll-marker"/>').appendTo(self);
                    var marker = top;
                    if (settings.scrollBottomOffset !== -1) {
                        marker = $('<div/>').css({
                            height: settings.scrollBottomOffset
                        }).appendTo(top);
                    }
                    is_bottom_observer = new IntersectionObserver(bottom_detect, {
                        root: self[0]
                    });
                    is_bottom_observer.observe(marker[0]);
                }
            }
            // this observer can be added imedietely even if terminal is not in the DOM
            // because both of the elements (root and target) are in same fragment
            create_bottom_detect();
            if (self.is(':visible')) {
                create_resizers();
            }
            function observe_visibility() {
                if (visibility_observer) {
                    if (visibility_observer.unobserve) {
                        visibility_observer.unobserve(self[0]);
                    } else {
                        clearInterval(visibility_observer);
                    }
                }
                var was_enabled = self.enabled();
                var visible = self.is(':visible');
                if (was_enabled && !visible) {
                    self.disable();
                }
                if (visible) {
                    create_resizers();
                } else {
                    // hide terminal content until it's resized (and num chars calculated)
                    wrapper.css('visibility', 'hidden');
                }
                function visibility_checker() {
                    if (self.is(':visible') && !visible) {
                        visible = true;
                        create_resizers();
                        calculate_char_size();
                        resize();
                        if (was_enabled) {
                            self.enable();
                        }
                        wrapper.css('visibility', '');
                    } else if (visible && !self.is(':visible')) {
                        visible = false;
                        was_enabled = $.terminal.active() === self && self.enabled();
                        self.disable();
                        wrapper.css('visibility', 'hidden');
                    }
                }
                if (window.IntersectionObserver && self.css('position') !== 'fixed') {
                    visibility_observer = new IntersectionObserver(visibility_checker, {
                        root: null
                    });
                    visibility_observer.observe(self[0]);
                } else {
                    visibility_observer = setInterval(visibility_checker, 100);
                }
            }
            var in_dom = !!self.closest('body').length;
            var MutationObsrv = window.MutationObserver || window.WebKitMutationObserver;
            if (MutationObsrv) {
                mutation_observer = new MutationObsrv(function() {
                    if (self.closest('body').length) {
                        if (!in_dom) {
                            self.scroll_to_bottom();
                            // this observer need to be added when terminal is in the DOM
                            observe_visibility();
                            resize();
                        }
                        in_dom = true;
                    } else if (in_dom) {
                        in_dom = false;
                    }
                });
                mutation_observer.observe(document.body, {childList: true});
            }
            if (in_dom) {
                // check if element is in the DOM if not running IntersectionObserver
                // don't make sense
                observe_visibility();
            }
            command_queue.resolve();
            // touch devices need touch event to get virtual keyboard
            if (enabled && self.is(':visible') && !is_mobile) {
                self.focus(undefined, true);
            } else {
                self.disable();
            }
            // -------------------------------------------------------------
            // Run Login
            if (is_function(global_login_fn)) {
                self.login(global_login_fn, true, initialize);
            } else {
                initialize();
            }
            // -------------------------------------------------------------
            // :: helper
            function exec_spec(spec) {
                var terminal = terminals.get()[spec[0]];
                // execute if belong to this terminal
                var defer = $.Deferred();
                if (terminal && terminal_id === terminal.id()) {
                    if (!spec[2]) {
                        defer.resolve();
                        return defer.promise();
                    } else if (paused) {
                        resume_callbacks.push(function() {
                            return terminal.exec(spec[2]).done(function() {
                                terminal.save_state(spec[2], true, spec[1]);
                                defer.resolve();
                            });
                        });
                        return defer.promise();
                    } else {
                        return terminal.exec(spec[2]).done(function() {
                            terminal.save_state(spec[2], true, spec[1]);
                        });
                    }
                }
            }
            // exec from hash called in each terminal instance
            if (settings.execHash) {
                if (location.hash) {
                    // wait until login is initialized
                    setTimeout(function() {
                        try {
                            var hash = location.hash.replace(/^#/, '');
                            // yes no var - local inside terminal
                            hash_commands = JSON.parse(decodeURIComponent(hash));
                            var i = 0;
                            (function recur() {
                                var spec = hash_commands[i++];
                                if (spec) {
                                    exec_spec(spec).done(recur);
                                } else {
                                    change_hash = true;
                                }
                            })();// */
                        } catch (e) {
                            // invalid json - ignore
                        }
                    });
                } else {
                    change_hash = true;
                }
            } else {
                change_hash = true; // if enabled later
            }
            // change_hash = true; // exec can now change hash
            // -------------------------------------------------------------
            /* istanbul ignore next */
            (function() {
                var shift = false;
                $(document).bind('keydown.terminal_' + self.id(), function(e) {
                    if (e.shiftKey) {
                        shift = true;
                    }
                }).bind('keyup.terminal_' + self.id(), function(e) {
                    // in Google Chromium/Linux shiftKey is false
                    if (e.shiftKey || e.which === 16) {
                        shift = false;
                    }
                });
                // this could work without calling scroll on wheel event but we
                // need it for cases where you have mouse wheel work differently
                // like with less command that scroll text
                function mousewheel(event, delta) {
                    if (!shift) {
                        var interpreter = interpreters.top();
                        var ret;
                        if (is_function(interpreter.mousewheel)) {
                            ret = interpreter.mousewheel(event, delta, self);
                        } else if (is_function(settings.mousewheel)) {
                            ret = settings.mousewheel(event, delta, self);
                        }
                        if (ret === true) {
                            return;
                        }
                        if ((have_scrollbar() || ret === false) && !event.ctrlKey) {
                            event.stopPropagation();
                            event.preventDefault();
                        }
                        if (ret === false) {
                            return false;
                        }
                        if (delta > 0) {
                            self.scroll(-40);
                        } else {
                            self.scroll(40);
                        }
                    }
                }
                if ($.event.special.mousewheel) {
                    // we keep mousewheel plugin just in case
                    self.on('mousewheel', mousewheel);
                } else {
                    // detection take from:
                    // https://developer.mozilla.org/en-US/docs/Web/Events/wheel
                    var event;
                    var div = document.createElement("div");
                    if ("onwheel" in div) {
                        event = "wheel"; // Modern browsers support "wheel"
                    } else if (document.onmousewheel !== undefined) {
                        // Webkit and IE support at least "mousewheel"
                        event = "mousewheel";
                    } else {
                        // let's assume that remaining browsers are older Firefox
                        event = "DOMMouseScroll";
                    }
                    div = null;
                    self.on(event, function(e) {
                        var delta;
                        if (event === 'mousewheel') {
                            delta = - 1 / 40 * e.originalEvent.wheelDelta;
                        } else {
                            delta = e.originalEvent.deltaY || e.originalEvent.detail;
                        }
                        mousewheel(e, -delta);
                    });
                }
                self.touch_scroll(function(event) {
                    var delta = event.current.clientY - event.previous.clientY;
                    var ret;
                    var interpreter = interpreters.top();
                    if (is_function(interpreter.touchscroll)) {
                        ret = interpreter.touchscroll(event, delta, self);
                    } else if (is_function(settings.touchscroll)) {
                        ret = settings.touchscroll(event, delta, self);
                    }
                    css(self[0], {
                        '--terminal-scroll': self.prop('scrollTop')
                    });
                    if (ret === true) {
                        return;
                    }
                    return false;
                });
            })();
        }); // make_interpreter
        return self;
    }; // terminal plugin
});

}).call(this)}).call(this,typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {},require("timers").setImmediate)
},{"jquery":15,"timers":22,"wcwidth":17}],15:[function(require,module,exports){
/*!
 * jQuery JavaScript Library v3.6.0
 * https://jquery.com/
 *
 * Includes Sizzle.js
 * https://sizzlejs.com/
 *
 * Copyright OpenJS Foundation and other contributors
 * Released under the MIT license
 * https://jquery.org/license
 *
 * Date: 2021-03-02T17:08Z
 */
( function( global, factory ) {

	"use strict";

	if ( typeof module === "object" && typeof module.exports === "object" ) {

		// For CommonJS and CommonJS-like environments where a proper `window`
		// is present, execute the factory and get jQuery.
		// For environments that do not have a `window` with a `document`
		// (such as Node.js), expose a factory as module.exports.
		// This accentuates the need for the creation of a real `window`.
		// e.g. var jQuery = require("jquery")(window);
		// See ticket #14549 for more info.
		module.exports = global.document ?
			factory( global, true ) :
			function( w ) {
				if ( !w.document ) {
					throw new Error( "jQuery requires a window with a document" );
				}
				return factory( w );
			};
	} else {
		factory( global );
	}

// Pass this if window is not defined yet
} )( typeof window !== "undefined" ? window : this, function( window, noGlobal ) {

// Edge <= 12 - 13+, Firefox <=18 - 45+, IE 10 - 11, Safari 5.1 - 9+, iOS 6 - 9.1
// throw exceptions when non-strict code (e.g., ASP.NET 4.5) accesses strict mode
// arguments.callee.caller (trac-13335). But as of jQuery 3.0 (2016), strict mode should be common
// enough that all such attempts are guarded in a try block.
"use strict";

var arr = [];

var getProto = Object.getPrototypeOf;

var slice = arr.slice;

var flat = arr.flat ? function( array ) {
	return arr.flat.call( array );
} : function( array ) {
	return arr.concat.apply( [], array );
};


var push = arr.push;

var indexOf = arr.indexOf;

var class2type = {};

var toString = class2type.toString;

var hasOwn = class2type.hasOwnProperty;

var fnToString = hasOwn.toString;

var ObjectFunctionString = fnToString.call( Object );

var support = {};

var isFunction = function isFunction( obj ) {

		// Support: Chrome <=57, Firefox <=52
		// In some browsers, typeof returns "function" for HTML <object> elements
		// (i.e., `typeof document.createElement( "object" ) === "function"`).
		// We don't want to classify *any* DOM node as a function.
		// Support: QtWeb <=3.8.5, WebKit <=534.34, wkhtmltopdf tool <=0.12.5
		// Plus for old WebKit, typeof returns "function" for HTML collections
		// (e.g., `typeof document.getElementsByTagName("div") === "function"`). (gh-4756)
		return typeof obj === "function" && typeof obj.nodeType !== "number" &&
			typeof obj.item !== "function";
	};


var isWindow = function isWindow( obj ) {
		return obj != null && obj === obj.window;
	};


var document = window.document;



	var preservedScriptAttributes = {
		type: true,
		src: true,
		nonce: true,
		noModule: true
	};

	function DOMEval( code, node, doc ) {
		doc = doc || document;

		var i, val,
			script = doc.createElement( "script" );

		script.text = code;
		if ( node ) {
			for ( i in preservedScriptAttributes ) {

				// Support: Firefox 64+, Edge 18+
				// Some browsers don't support the "nonce" property on scripts.
				// On the other hand, just using `getAttribute` is not enough as
				// the `nonce` attribute is reset to an empty string whenever it
				// becomes browsing-context connected.
				// See https://github.com/whatwg/html/issues/2369
				// See https://html.spec.whatwg.org/#nonce-attributes
				// The `node.getAttribute` check was added for the sake of
				// `jQuery.globalEval` so that it can fake a nonce-containing node
				// via an object.
				val = node[ i ] || node.getAttribute && node.getAttribute( i );
				if ( val ) {
					script.setAttribute( i, val );
				}
			}
		}
		doc.head.appendChild( script ).parentNode.removeChild( script );
	}


function toType( obj ) {
	if ( obj == null ) {
		return obj + "";
	}

	// Support: Android <=2.3 only (functionish RegExp)
	return typeof obj === "object" || typeof obj === "function" ?
		class2type[ toString.call( obj ) ] || "object" :
		typeof obj;
}
/* global Symbol */
// Defining this global in .eslintrc.json would create a danger of using the global
// unguarded in another place, it seems safer to define global only for this module



var
	version = "3.6.0",

	// Define a local copy of jQuery
	jQuery = function( selector, context ) {

		// The jQuery object is actually just the init constructor 'enhanced'
		// Need init if jQuery is called (just allow error to be thrown if not included)
		return new jQuery.fn.init( selector, context );
	};

jQuery.fn = jQuery.prototype = {

	// The current version of jQuery being used
	jquery: version,

	constructor: jQuery,

	// The default length of a jQuery object is 0
	length: 0,

	toArray: function() {
		return slice.call( this );
	},

	// Get the Nth element in the matched element set OR
	// Get the whole matched element set as a clean array
	get: function( num ) {

		// Return all the elements in a clean array
		if ( num == null ) {
			return slice.call( this );
		}

		// Return just the one element from the set
		return num < 0 ? this[ num + this.length ] : this[ num ];
	},

	// Take an array of elements and push it onto the stack
	// (returning the new matched element set)
	pushStack: function( elems ) {

		// Build a new jQuery matched element set
		var ret = jQuery.merge( this.constructor(), elems );

		// Add the old object onto the stack (as a reference)
		ret.prevObject = this;

		// Return the newly-formed element set
		return ret;
	},

	// Execute a callback for every element in the matched set.
	each: function( callback ) {
		return jQuery.each( this, callback );
	},

	map: function( callback ) {
		return this.pushStack( jQuery.map( this, function( elem, i ) {
			return callback.call( elem, i, elem );
		} ) );
	},

	slice: function() {
		return this.pushStack( slice.apply( this, arguments ) );
	},

	first: function() {
		return this.eq( 0 );
	},

	last: function() {
		return this.eq( -1 );
	},

	even: function() {
		return this.pushStack( jQuery.grep( this, function( _elem, i ) {
			return ( i + 1 ) % 2;
		} ) );
	},

	odd: function() {
		return this.pushStack( jQuery.grep( this, function( _elem, i ) {
			return i % 2;
		} ) );
	},

	eq: function( i ) {
		var len = this.length,
			j = +i + ( i < 0 ? len : 0 );
		return this.pushStack( j >= 0 && j < len ? [ this[ j ] ] : [] );
	},

	end: function() {
		return this.prevObject || this.constructor();
	},

	// For internal use only.
	// Behaves like an Array's method, not like a jQuery method.
	push: push,
	sort: arr.sort,
	splice: arr.splice
};

jQuery.extend = jQuery.fn.extend = function() {
	var options, name, src, copy, copyIsArray, clone,
		target = arguments[ 0 ] || {},
		i = 1,
		length = arguments.length,
		deep = false;

	// Handle a deep copy situation
	if ( typeof target === "boolean" ) {
		deep = target;

		// Skip the boolean and the target
		target = arguments[ i ] || {};
		i++;
	}

	// Handle case when target is a string or something (possible in deep copy)
	if ( typeof target !== "object" && !isFunction( target ) ) {
		target = {};
	}

	// Extend jQuery itself if only one argument is passed
	if ( i === length ) {
		target = this;
		i--;
	}

	for ( ; i < length; i++ ) {

		// Only deal with non-null/undefined values
		if ( ( options = arguments[ i ] ) != null ) {

			// Extend the base object
			for ( name in options ) {
				copy = options[ name ];

				// Prevent Object.prototype pollution
				// Prevent never-ending loop
				if ( name === "__proto__" || target === copy ) {
					continue;
				}

				// Recurse if we're merging plain objects or arrays
				if ( deep && copy && ( jQuery.isPlainObject( copy ) ||
					( copyIsArray = Array.isArray( copy ) ) ) ) {
					src = target[ name ];

					// Ensure proper type for the source value
					if ( copyIsArray && !Array.isArray( src ) ) {
						clone = [];
					} else if ( !copyIsArray && !jQuery.isPlainObject( src ) ) {
						clone = {};
					} else {
						clone = src;
					}
					copyIsArray = false;

					// Never move original objects, clone them
					target[ name ] = jQuery.extend( deep, clone, copy );

				// Don't bring in undefined values
				} else if ( copy !== undefined ) {
					target[ name ] = copy;
				}
			}
		}
	}

	// Return the modified object
	return target;
};

jQuery.extend( {

	// Unique for each copy of jQuery on the page
	expando: "jQuery" + ( version + Math.random() ).replace( /\D/g, "" ),

	// Assume jQuery is ready without the ready module
	isReady: true,

	error: function( msg ) {
		throw new Error( msg );
	},

	noop: function() {},

	isPlainObject: function( obj ) {
		var proto, Ctor;

		// Detect obvious negatives
		// Use toString instead of jQuery.type to catch host objects
		if ( !obj || toString.call( obj ) !== "[object Object]" ) {
			return false;
		}

		proto = getProto( obj );

		// Objects with no prototype (e.g., `Object.create( null )`) are plain
		if ( !proto ) {
			return true;
		}

		// Objects with prototype are plain iff they were constructed by a global Object function
		Ctor = hasOwn.call( proto, "constructor" ) && proto.constructor;
		return typeof Ctor === "function" && fnToString.call( Ctor ) === ObjectFunctionString;
	},

	isEmptyObject: function( obj ) {
		var name;

		for ( name in obj ) {
			return false;
		}
		return true;
	},

	// Evaluates a script in a provided context; falls back to the global one
	// if not specified.
	globalEval: function( code, options, doc ) {
		DOMEval( code, { nonce: options && options.nonce }, doc );
	},

	each: function( obj, callback ) {
		var length, i = 0;

		if ( isArrayLike( obj ) ) {
			length = obj.length;
			for ( ; i < length; i++ ) {
				if ( callback.call( obj[ i ], i, obj[ i ] ) === false ) {
					break;
				}
			}
		} else {
			for ( i in obj ) {
				if ( callback.call( obj[ i ], i, obj[ i ] ) === false ) {
					break;
				}
			}
		}

		return obj;
	},

	// results is for internal usage only
	makeArray: function( arr, results ) {
		var ret = results || [];

		if ( arr != null ) {
			if ( isArrayLike( Object( arr ) ) ) {
				jQuery.merge( ret,
					typeof arr === "string" ?
						[ arr ] : arr
				);
			} else {
				push.call( ret, arr );
			}
		}

		return ret;
	},

	inArray: function( elem, arr, i ) {
		return arr == null ? -1 : indexOf.call( arr, elem, i );
	},

	// Support: Android <=4.0 only, PhantomJS 1 only
	// push.apply(_, arraylike) throws on ancient WebKit
	merge: function( first, second ) {
		var len = +second.length,
			j = 0,
			i = first.length;

		for ( ; j < len; j++ ) {
			first[ i++ ] = second[ j ];
		}

		first.length = i;

		return first;
	},

	grep: function( elems, callback, invert ) {
		var callbackInverse,
			matches = [],
			i = 0,
			length = elems.length,
			callbackExpect = !invert;

		// Go through the array, only saving the items
		// that pass the validator function
		for ( ; i < length; i++ ) {
			callbackInverse = !callback( elems[ i ], i );
			if ( callbackInverse !== callbackExpect ) {
				matches.push( elems[ i ] );
			}
		}

		return matches;
	},

	// arg is for internal usage only
	map: function( elems, callback, arg ) {
		var length, value,
			i = 0,
			ret = [];

		// Go through the array, translating each of the items to their new values
		if ( isArrayLike( elems ) ) {
			length = elems.length;
			for ( ; i < length; i++ ) {
				value = callback( elems[ i ], i, arg );

				if ( value != null ) {
					ret.push( value );
				}
			}

		// Go through every key on the object,
		} else {
			for ( i in elems ) {
				value = callback( elems[ i ], i, arg );

				if ( value != null ) {
					ret.push( value );
				}
			}
		}

		// Flatten any nested arrays
		return flat( ret );
	},

	// A global GUID counter for objects
	guid: 1,

	// jQuery.support is not used in Core but other projects attach their
	// properties to it so it needs to exist.
	support: support
} );

if ( typeof Symbol === "function" ) {
	jQuery.fn[ Symbol.iterator ] = arr[ Symbol.iterator ];
}

// Populate the class2type map
jQuery.each( "Boolean Number String Function Array Date RegExp Object Error Symbol".split( " " ),
	function( _i, name ) {
		class2type[ "[object " + name + "]" ] = name.toLowerCase();
	} );

function isArrayLike( obj ) {

	// Support: real iOS 8.2 only (not reproducible in simulator)
	// `in` check used to prevent JIT error (gh-2145)
	// hasOwn isn't used here due to false negatives
	// regarding Nodelist length in IE
	var length = !!obj && "length" in obj && obj.length,
		type = toType( obj );

	if ( isFunction( obj ) || isWindow( obj ) ) {
		return false;
	}

	return type === "array" || length === 0 ||
		typeof length === "number" && length > 0 && ( length - 1 ) in obj;
}
var Sizzle =
/*!
 * Sizzle CSS Selector Engine v2.3.6
 * https://sizzlejs.com/
 *
 * Copyright JS Foundation and other contributors
 * Released under the MIT license
 * https://js.foundation/
 *
 * Date: 2021-02-16
 */
( function( window ) {
var i,
	support,
	Expr,
	getText,
	isXML,
	tokenize,
	compile,
	select,
	outermostContext,
	sortInput,
	hasDuplicate,

	// Local document vars
	setDocument,
	document,
	docElem,
	documentIsHTML,
	rbuggyQSA,
	rbuggyMatches,
	matches,
	contains,

	// Instance-specific data
	expando = "sizzle" + 1 * new Date(),
	preferredDoc = window.document,
	dirruns = 0,
	done = 0,
	classCache = createCache(),
	tokenCache = createCache(),
	compilerCache = createCache(),
	nonnativeSelectorCache = createCache(),
	sortOrder = function( a, b ) {
		if ( a === b ) {
			hasDuplicate = true;
		}
		return 0;
	},

	// Instance methods
	hasOwn = ( {} ).hasOwnProperty,
	arr = [],
	pop = arr.pop,
	pushNative = arr.push,
	push = arr.push,
	slice = arr.slice,

	// Use a stripped-down indexOf as it's faster than native
	// https://jsperf.com/thor-indexof-vs-for/5
	indexOf = function( list, elem ) {
		var i = 0,
			len = list.length;
		for ( ; i < len; i++ ) {
			if ( list[ i ] === elem ) {
				return i;
			}
		}
		return -1;
	},

	booleans = "checked|selected|async|autofocus|autoplay|controls|defer|disabled|hidden|" +
		"ismap|loop|multiple|open|readonly|required|scoped",

	// Regular expressions

	// http://www.w3.org/TR/css3-selectors/#whitespace
	whitespace = "[\\x20\\t\\r\\n\\f]",

	// https://www.w3.org/TR/css-syntax-3/#ident-token-diagram
	identifier = "(?:\\\\[\\da-fA-F]{1,6}" + whitespace +
		"?|\\\\[^\\r\\n\\f]|[\\w-]|[^\0-\\x7f])+",

	// Attribute selectors: http://www.w3.org/TR/selectors/#attribute-selectors
	attributes = "\\[" + whitespace + "*(" + identifier + ")(?:" + whitespace +

		// Operator (capture 2)
		"*([*^$|!~]?=)" + whitespace +

		// "Attribute values must be CSS identifiers [capture 5]
		// or strings [capture 3 or capture 4]"
		"*(?:'((?:\\\\.|[^\\\\'])*)'|\"((?:\\\\.|[^\\\\\"])*)\"|(" + identifier + "))|)" +
		whitespace + "*\\]",

	pseudos = ":(" + identifier + ")(?:\\((" +

		// To reduce the number of selectors needing tokenize in the preFilter, prefer arguments:
		// 1. quoted (capture 3; capture 4 or capture 5)
		"('((?:\\\\.|[^\\\\'])*)'|\"((?:\\\\.|[^\\\\\"])*)\")|" +

		// 2. simple (capture 6)
		"((?:\\\\.|[^\\\\()[\\]]|" + attributes + ")*)|" +

		// 3. anything else (capture 2)
		".*" +
		")\\)|)",

	// Leading and non-escaped trailing whitespace, capturing some non-whitespace characters preceding the latter
	rwhitespace = new RegExp( whitespace + "+", "g" ),
	rtrim = new RegExp( "^" + whitespace + "+|((?:^|[^\\\\])(?:\\\\.)*)" +
		whitespace + "+$", "g" ),

	rcomma = new RegExp( "^" + whitespace + "*," + whitespace + "*" ),
	rcombinators = new RegExp( "^" + whitespace + "*([>+~]|" + whitespace + ")" + whitespace +
		"*" ),
	rdescend = new RegExp( whitespace + "|>" ),

	rpseudo = new RegExp( pseudos ),
	ridentifier = new RegExp( "^" + identifier + "$" ),

	matchExpr = {
		"ID": new RegExp( "^#(" + identifier + ")" ),
		"CLASS": new RegExp( "^\\.(" + identifier + ")" ),
		"TAG": new RegExp( "^(" + identifier + "|[*])" ),
		"ATTR": new RegExp( "^" + attributes ),
		"PSEUDO": new RegExp( "^" + pseudos ),
		"CHILD": new RegExp( "^:(only|first|last|nth|nth-last)-(child|of-type)(?:\\(" +
			whitespace + "*(even|odd|(([+-]|)(\\d*)n|)" + whitespace + "*(?:([+-]|)" +
			whitespace + "*(\\d+)|))" + whitespace + "*\\)|)", "i" ),
		"bool": new RegExp( "^(?:" + booleans + ")$", "i" ),

		// For use in libraries implementing .is()
		// We use this for POS matching in `select`
		"needsContext": new RegExp( "^" + whitespace +
			"*[>+~]|:(even|odd|eq|gt|lt|nth|first|last)(?:\\(" + whitespace +
			"*((?:-\\d)?\\d*)" + whitespace + "*\\)|)(?=[^-]|$)", "i" )
	},

	rhtml = /HTML$/i,
	rinputs = /^(?:input|select|textarea|button)$/i,
	rheader = /^h\d$/i,

	rnative = /^[^{]+\{\s*\[native \w/,

	// Easily-parseable/retrievable ID or TAG or CLASS selectors
	rquickExpr = /^(?:#([\w-]+)|(\w+)|\.([\w-]+))$/,

	rsibling = /[+~]/,

	// CSS escapes
	// http://www.w3.org/TR/CSS21/syndata.html#escaped-characters
	runescape = new RegExp( "\\\\[\\da-fA-F]{1,6}" + whitespace + "?|\\\\([^\\r\\n\\f])", "g" ),
	funescape = function( escape, nonHex ) {
		var high = "0x" + escape.slice( 1 ) - 0x10000;

		return nonHex ?

			// Strip the backslash prefix from a non-hex escape sequence
			nonHex :

			// Replace a hexadecimal escape sequence with the encoded Unicode code point
			// Support: IE <=11+
			// For values outside the Basic Multilingual Plane (BMP), manually construct a
			// surrogate pair
			high < 0 ?
				String.fromCharCode( high + 0x10000 ) :
				String.fromCharCode( high >> 10 | 0xD800, high & 0x3FF | 0xDC00 );
	},

	// CSS string/identifier serialization
	// https://drafts.csswg.org/cssom/#common-serializing-idioms
	rcssescape = /([\0-\x1f\x7f]|^-?\d)|^-$|[^\0-\x1f\x7f-\uFFFF\w-]/g,
	fcssescape = function( ch, asCodePoint ) {
		if ( asCodePoint ) {

			// U+0000 NULL becomes U+FFFD REPLACEMENT CHARACTER
			if ( ch === "\0" ) {
				return "\uFFFD";
			}

			// Control characters and (dependent upon position) numbers get escaped as code points
			return ch.slice( 0, -1 ) + "\\" +
				ch.charCodeAt( ch.length - 1 ).toString( 16 ) + " ";
		}

		// Other potentially-special ASCII characters get backslash-escaped
		return "\\" + ch;
	},

	// Used for iframes
	// See setDocument()
	// Removing the function wrapper causes a "Permission Denied"
	// error in IE
	unloadHandler = function() {
		setDocument();
	},

	inDisabledFieldset = addCombinator(
		function( elem ) {
			return elem.disabled === true && elem.nodeName.toLowerCase() === "fieldset";
		},
		{ dir: "parentNode", next: "legend" }
	);

// Optimize for push.apply( _, NodeList )
try {
	push.apply(
		( arr = slice.call( preferredDoc.childNodes ) ),
		preferredDoc.childNodes
	);

	// Support: Android<4.0
	// Detect silently failing push.apply
	// eslint-disable-next-line no-unused-expressions
	arr[ preferredDoc.childNodes.length ].nodeType;
} catch ( e ) {
	push = { apply: arr.length ?

		// Leverage slice if possible
		function( target, els ) {
			pushNative.apply( target, slice.call( els ) );
		} :

		// Support: IE<9
		// Otherwise append directly
		function( target, els ) {
			var j = target.length,
				i = 0;

			// Can't trust NodeList.length
			while ( ( target[ j++ ] = els[ i++ ] ) ) {}
			target.length = j - 1;
		}
	};
}

function Sizzle( selector, context, results, seed ) {
	var m, i, elem, nid, match, groups, newSelector,
		newContext = context && context.ownerDocument,

		// nodeType defaults to 9, since context defaults to document
		nodeType = context ? context.nodeType : 9;

	results = results || [];

	// Return early from calls with invalid selector or context
	if ( typeof selector !== "string" || !selector ||
		nodeType !== 1 && nodeType !== 9 && nodeType !== 11 ) {

		return results;
	}

	// Try to shortcut find operations (as opposed to filters) in HTML documents
	if ( !seed ) {
		setDocument( context );
		context = context || document;

		if ( documentIsHTML ) {

			// If the selector is sufficiently simple, try using a "get*By*" DOM method
			// (excepting DocumentFragment context, where the methods don't exist)
			if ( nodeType !== 11 && ( match = rquickExpr.exec( selector ) ) ) {

				// ID selector
				if ( ( m = match[ 1 ] ) ) {

					// Document context
					if ( nodeType === 9 ) {
						if ( ( elem = context.getElementById( m ) ) ) {

							// Support: IE, Opera, Webkit
							// TODO: identify versions
							// getElementById can match elements by name instead of ID
							if ( elem.id === m ) {
								results.push( elem );
								return results;
							}
						} else {
							return results;
						}

					// Element context
					} else {

						// Support: IE, Opera, Webkit
						// TODO: identify versions
						// getElementById can match elements by name instead of ID
						if ( newContext && ( elem = newContext.getElementById( m ) ) &&
							contains( context, elem ) &&
							elem.id === m ) {

							results.push( elem );
							return results;
						}
					}

				// Type selector
				} else if ( match[ 2 ] ) {
					push.apply( results, context.getElementsByTagName( selector ) );
					return results;

				// Class selector
				} else if ( ( m = match[ 3 ] ) && support.getElementsByClassName &&
					context.getElementsByClassName ) {

					push.apply( results, context.getElementsByClassName( m ) );
					return results;
				}
			}

			// Take advantage of querySelectorAll
			if ( support.qsa &&
				!nonnativeSelectorCache[ selector + " " ] &&
				( !rbuggyQSA || !rbuggyQSA.test( selector ) ) &&

				// Support: IE 8 only
				// Exclude object elements
				( nodeType !== 1 || context.nodeName.toLowerCase() !== "object" ) ) {

				newSelector = selector;
				newContext = context;

				// qSA considers elements outside a scoping root when evaluating child or
				// descendant combinators, which is not what we want.
				// In such cases, we work around the behavior by prefixing every selector in the
				// list with an ID selector referencing the scope context.
				// The technique has to be used as well when a leading combinator is used
				// as such selectors are not recognized by querySelectorAll.
				// Thanks to Andrew Dupont for this technique.
				if ( nodeType === 1 &&
					( rdescend.test( selector ) || rcombinators.test( selector ) ) ) {

					// Expand context for sibling selectors
					newContext = rsibling.test( selector ) && testContext( context.parentNode ) ||
						context;

					// We can use :scope instead of the ID hack if the browser
					// supports it & if we're not changing the context.
					if ( newContext !== context || !support.scope ) {

						// Capture the context ID, setting it first if necessary
						if ( ( nid = context.getAttribute( "id" ) ) ) {
							nid = nid.replace( rcssescape, fcssescape );
						} else {
							context.setAttribute( "id", ( nid = expando ) );
						}
					}

					// Prefix every selector in the list
					groups = tokenize( selector );
					i = groups.length;
					while ( i-- ) {
						groups[ i ] = ( nid ? "#" + nid : ":scope" ) + " " +
							toSelector( groups[ i ] );
					}
					newSelector = groups.join( "," );
				}

				try {
					push.apply( results,
						newContext.querySelectorAll( newSelector )
					);
					return results;
				} catch ( qsaError ) {
					nonnativeSelectorCache( selector, true );
				} finally {
					if ( nid === expando ) {
						context.removeAttribute( "id" );
					}
				}
			}
		}
	}

	// All others
	return select( selector.replace( rtrim, "$1" ), context, results, seed );
}

/**
 * Create key-value caches of limited size
 * @returns {function(string, object)} Returns the Object data after storing it on itself with
 *	property name the (space-suffixed) string and (if the cache is larger than Expr.cacheLength)
 *	deleting the oldest entry
 */
function createCache() {
	var keys = [];

	function cache( key, value ) {

		// Use (key + " ") to avoid collision with native prototype properties (see Issue #157)
		if ( keys.push( key + " " ) > Expr.cacheLength ) {

			// Only keep the most recent entries
			delete cache[ keys.shift() ];
		}
		return ( cache[ key + " " ] = value );
	}
	return cache;
}

/**
 * Mark a function for special use by Sizzle
 * @param {Function} fn The function to mark
 */
function markFunction( fn ) {
	fn[ expando ] = true;
	return fn;
}

/**
 * Support testing using an element
 * @param {Function} fn Passed the created element and returns a boolean result
 */
function assert( fn ) {
	var el = document.createElement( "fieldset" );

	try {
		return !!fn( el );
	} catch ( e ) {
		return false;
	} finally {

		// Remove from its parent by default
		if ( el.parentNode ) {
			el.parentNode.removeChild( el );
		}

		// release memory in IE
		el = null;
	}
}

/**
 * Adds the same handler for all of the specified attrs
 * @param {String} attrs Pipe-separated list of attributes
 * @param {Function} handler The method that will be applied
 */
function addHandle( attrs, handler ) {
	var arr = attrs.split( "|" ),
		i = arr.length;

	while ( i-- ) {
		Expr.attrHandle[ arr[ i ] ] = handler;
	}
}

/**
 * Checks document order of two siblings
 * @param {Element} a
 * @param {Element} b
 * @returns {Number} Returns less than 0 if a precedes b, greater than 0 if a follows b
 */
function siblingCheck( a, b ) {
	var cur = b && a,
		diff = cur && a.nodeType === 1 && b.nodeType === 1 &&
			a.sourceIndex - b.sourceIndex;

	// Use IE sourceIndex if available on both nodes
	if ( diff ) {
		return diff;
	}

	// Check if b follows a
	if ( cur ) {
		while ( ( cur = cur.nextSibling ) ) {
			if ( cur === b ) {
				return -1;
			}
		}
	}

	return a ? 1 : -1;
}

/**
 * Returns a function to use in pseudos for input types
 * @param {String} type
 */
function createInputPseudo( type ) {
	return function( elem ) {
		var name = elem.nodeName.toLowerCase();
		return name === "input" && elem.type === type;
	};
}

/**
 * Returns a function to use in pseudos for buttons
 * @param {String} type
 */
function createButtonPseudo( type ) {
	return function( elem ) {
		var name = elem.nodeName.toLowerCase();
		return ( name === "input" || name === "button" ) && elem.type === type;
	};
}

/**
 * Returns a function to use in pseudos for :enabled/:disabled
 * @param {Boolean} disabled true for :disabled; false for :enabled
 */
function createDisabledPseudo( disabled ) {

	// Known :disabled false positives: fieldset[disabled] > legend:nth-of-type(n+2) :can-disable
	return function( elem ) {

		// Only certain elements can match :enabled or :disabled
		// https://html.spec.whatwg.org/multipage/scripting.html#selector-enabled
		// https://html.spec.whatwg.org/multipage/scripting.html#selector-disabled
		if ( "form" in elem ) {

			// Check for inherited disabledness on relevant non-disabled elements:
			// * listed form-associated elements in a disabled fieldset
			//   https://html.spec.whatwg.org/multipage/forms.html#category-listed
			//   https://html.spec.whatwg.org/multipage/forms.html#concept-fe-disabled
			// * option elements in a disabled optgroup
			//   https://html.spec.whatwg.org/multipage/forms.html#concept-option-disabled
			// All such elements have a "form" property.
			if ( elem.parentNode && elem.disabled === false ) {

				// Option elements defer to a parent optgroup if present
				if ( "label" in elem ) {
					if ( "label" in elem.parentNode ) {
						return elem.parentNode.disabled === disabled;
					} else {
						return elem.disabled === disabled;
					}
				}

				// Support: IE 6 - 11
				// Use the isDisabled shortcut property to check for disabled fieldset ancestors
				return elem.isDisabled === disabled ||

					// Where there is no isDisabled, check manually
					/* jshint -W018 */
					elem.isDisabled !== !disabled &&
					inDisabledFieldset( elem ) === disabled;
			}

			return elem.disabled === disabled;

		// Try to winnow out elements that can't be disabled before trusting the disabled property.
		// Some victims get caught in our net (label, legend, menu, track), but it shouldn't
		// even exist on them, let alone have a boolean value.
		} else if ( "label" in elem ) {
			return elem.disabled === disabled;
		}

		// Remaining elements are neither :enabled nor :disabled
		return false;
	};
}

/**
 * Returns a function to use in pseudos for positionals
 * @param {Function} fn
 */
function createPositionalPseudo( fn ) {
	return markFunction( function( argument ) {
		argument = +argument;
		return markFunction( function( seed, matches ) {
			var j,
				matchIndexes = fn( [], seed.length, argument ),
				i = matchIndexes.length;

			// Match elements found at the specified indexes
			while ( i-- ) {
				if ( seed[ ( j = matchIndexes[ i ] ) ] ) {
					seed[ j ] = !( matches[ j ] = seed[ j ] );
				}
			}
		} );
	} );
}

/**
 * Checks a node for validity as a Sizzle context
 * @param {Element|Object=} context
 * @returns {Element|Object|Boolean} The input node if acceptable, otherwise a falsy value
 */
function testContext( context ) {
	return context && typeof context.getElementsByTagName !== "undefined" && context;
}

// Expose support vars for convenience
support = Sizzle.support = {};

/**
 * Detects XML nodes
 * @param {Element|Object} elem An element or a document
 * @returns {Boolean} True iff elem is a non-HTML XML node
 */
isXML = Sizzle.isXML = function( elem ) {
	var namespace = elem && elem.namespaceURI,
		docElem = elem && ( elem.ownerDocument || elem ).documentElement;

	// Support: IE <=8
	// Assume HTML when documentElement doesn't yet exist, such as inside loading iframes
	// https://bugs.jquery.com/ticket/4833
	return !rhtml.test( namespace || docElem && docElem.nodeName || "HTML" );
};

/**
 * Sets document-related variables once based on the current document
 * @param {Element|Object} [doc] An element or document object to use to set the document
 * @returns {Object} Returns the current document
 */
setDocument = Sizzle.setDocument = function( node ) {
	var hasCompare, subWindow,
		doc = node ? node.ownerDocument || node : preferredDoc;

	// Return early if doc is invalid or already selected
	// Support: IE 11+, Edge 17 - 18+
	// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
	// two documents; shallow comparisons work.
	// eslint-disable-next-line eqeqeq
	if ( doc == document || doc.nodeType !== 9 || !doc.documentElement ) {
		return document;
	}

	// Update global variables
	document = doc;
	docElem = document.documentElement;
	documentIsHTML = !isXML( document );

	// Support: IE 9 - 11+, Edge 12 - 18+
	// Accessing iframe documents after unload throws "permission denied" errors (jQuery #13936)
	// Support: IE 11+, Edge 17 - 18+
	// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
	// two documents; shallow comparisons work.
	// eslint-disable-next-line eqeqeq
	if ( preferredDoc != document &&
		( subWindow = document.defaultView ) && subWindow.top !== subWindow ) {

		// Support: IE 11, Edge
		if ( subWindow.addEventListener ) {
			subWindow.addEventListener( "unload", unloadHandler, false );

		// Support: IE 9 - 10 only
		} else if ( subWindow.attachEvent ) {
			subWindow.attachEvent( "onunload", unloadHandler );
		}
	}

	// Support: IE 8 - 11+, Edge 12 - 18+, Chrome <=16 - 25 only, Firefox <=3.6 - 31 only,
	// Safari 4 - 5 only, Opera <=11.6 - 12.x only
	// IE/Edge & older browsers don't support the :scope pseudo-class.
	// Support: Safari 6.0 only
	// Safari 6.0 supports :scope but it's an alias of :root there.
	support.scope = assert( function( el ) {
		docElem.appendChild( el ).appendChild( document.createElement( "div" ) );
		return typeof el.querySelectorAll !== "undefined" &&
			!el.querySelectorAll( ":scope fieldset div" ).length;
	} );

	/* Attributes
	---------------------------------------------------------------------- */

	// Support: IE<8
	// Verify that getAttribute really returns attributes and not properties
	// (excepting IE8 booleans)
	support.attributes = assert( function( el ) {
		el.className = "i";
		return !el.getAttribute( "className" );
	} );

	/* getElement(s)By*
	---------------------------------------------------------------------- */

	// Check if getElementsByTagName("*") returns only elements
	support.getElementsByTagName = assert( function( el ) {
		el.appendChild( document.createComment( "" ) );
		return !el.getElementsByTagName( "*" ).length;
	} );

	// Support: IE<9
	support.getElementsByClassName = rnative.test( document.getElementsByClassName );

	// Support: IE<10
	// Check if getElementById returns elements by name
	// The broken getElementById methods don't pick up programmatically-set names,
	// so use a roundabout getElementsByName test
	support.getById = assert( function( el ) {
		docElem.appendChild( el ).id = expando;
		return !document.getElementsByName || !document.getElementsByName( expando ).length;
	} );

	// ID filter and find
	if ( support.getById ) {
		Expr.filter[ "ID" ] = function( id ) {
			var attrId = id.replace( runescape, funescape );
			return function( elem ) {
				return elem.getAttribute( "id" ) === attrId;
			};
		};
		Expr.find[ "ID" ] = function( id, context ) {
			if ( typeof context.getElementById !== "undefined" && documentIsHTML ) {
				var elem = context.getElementById( id );
				return elem ? [ elem ] : [];
			}
		};
	} else {
		Expr.filter[ "ID" ] =  function( id ) {
			var attrId = id.replace( runescape, funescape );
			return function( elem ) {
				var node = typeof elem.getAttributeNode !== "undefined" &&
					elem.getAttributeNode( "id" );
				return node && node.value === attrId;
			};
		};

		// Support: IE 6 - 7 only
		// getElementById is not reliable as a find shortcut
		Expr.find[ "ID" ] = function( id, context ) {
			if ( typeof context.getElementById !== "undefined" && documentIsHTML ) {
				var node, i, elems,
					elem = context.getElementById( id );

				if ( elem ) {

					// Verify the id attribute
					node = elem.getAttributeNode( "id" );
					if ( node && node.value === id ) {
						return [ elem ];
					}

					// Fall back on getElementsByName
					elems = context.getElementsByName( id );
					i = 0;
					while ( ( elem = elems[ i++ ] ) ) {
						node = elem.getAttributeNode( "id" );
						if ( node && node.value === id ) {
							return [ elem ];
						}
					}
				}

				return [];
			}
		};
	}

	// Tag
	Expr.find[ "TAG" ] = support.getElementsByTagName ?
		function( tag, context ) {
			if ( typeof context.getElementsByTagName !== "undefined" ) {
				return context.getElementsByTagName( tag );

			// DocumentFragment nodes don't have gEBTN
			} else if ( support.qsa ) {
				return context.querySelectorAll( tag );
			}
		} :

		function( tag, context ) {
			var elem,
				tmp = [],
				i = 0,

				// By happy coincidence, a (broken) gEBTN appears on DocumentFragment nodes too
				results = context.getElementsByTagName( tag );

			// Filter out possible comments
			if ( tag === "*" ) {
				while ( ( elem = results[ i++ ] ) ) {
					if ( elem.nodeType === 1 ) {
						tmp.push( elem );
					}
				}

				return tmp;
			}
			return results;
		};

	// Class
	Expr.find[ "CLASS" ] = support.getElementsByClassName && function( className, context ) {
		if ( typeof context.getElementsByClassName !== "undefined" && documentIsHTML ) {
			return context.getElementsByClassName( className );
		}
	};

	/* QSA/matchesSelector
	---------------------------------------------------------------------- */

	// QSA and matchesSelector support

	// matchesSelector(:active) reports false when true (IE9/Opera 11.5)
	rbuggyMatches = [];

	// qSa(:focus) reports false when true (Chrome 21)
	// We allow this because of a bug in IE8/9 that throws an error
	// whenever `document.activeElement` is accessed on an iframe
	// So, we allow :focus to pass through QSA all the time to avoid the IE error
	// See https://bugs.jquery.com/ticket/13378
	rbuggyQSA = [];

	if ( ( support.qsa = rnative.test( document.querySelectorAll ) ) ) {

		// Build QSA regex
		// Regex strategy adopted from Diego Perini
		assert( function( el ) {

			var input;

			// Select is set to empty string on purpose
			// This is to test IE's treatment of not explicitly
			// setting a boolean content attribute,
			// since its presence should be enough
			// https://bugs.jquery.com/ticket/12359
			docElem.appendChild( el ).innerHTML = "<a id='" + expando + "'></a>" +
				"<select id='" + expando + "-\r\\' msallowcapture=''>" +
				"<option selected=''></option></select>";

			// Support: IE8, Opera 11-12.16
			// Nothing should be selected when empty strings follow ^= or $= or *=
			// The test attribute must be unknown in Opera but "safe" for WinRT
			// https://msdn.microsoft.com/en-us/library/ie/hh465388.aspx#attribute_section
			if ( el.querySelectorAll( "[msallowcapture^='']" ).length ) {
				rbuggyQSA.push( "[*^$]=" + whitespace + "*(?:''|\"\")" );
			}

			// Support: IE8
			// Boolean attributes and "value" are not treated correctly
			if ( !el.querySelectorAll( "[selected]" ).length ) {
				rbuggyQSA.push( "\\[" + whitespace + "*(?:value|" + booleans + ")" );
			}

			// Support: Chrome<29, Android<4.4, Safari<7.0+, iOS<7.0+, PhantomJS<1.9.8+
			if ( !el.querySelectorAll( "[id~=" + expando + "-]" ).length ) {
				rbuggyQSA.push( "~=" );
			}

			// Support: IE 11+, Edge 15 - 18+
			// IE 11/Edge don't find elements on a `[name='']` query in some cases.
			// Adding a temporary attribute to the document before the selection works
			// around the issue.
			// Interestingly, IE 10 & older don't seem to have the issue.
			input = document.createElement( "input" );
			input.setAttribute( "name", "" );
			el.appendChild( input );
			if ( !el.querySelectorAll( "[name='']" ).length ) {
				rbuggyQSA.push( "\\[" + whitespace + "*name" + whitespace + "*=" +
					whitespace + "*(?:''|\"\")" );
			}

			// Webkit/Opera - :checked should return selected option elements
			// http://www.w3.org/TR/2011/REC-css3-selectors-20110929/#checked
			// IE8 throws error here and will not see later tests
			if ( !el.querySelectorAll( ":checked" ).length ) {
				rbuggyQSA.push( ":checked" );
			}

			// Support: Safari 8+, iOS 8+
			// https://bugs.webkit.org/show_bug.cgi?id=136851
			// In-page `selector#id sibling-combinator selector` fails
			if ( !el.querySelectorAll( "a#" + expando + "+*" ).length ) {
				rbuggyQSA.push( ".#.+[+~]" );
			}

			// Support: Firefox <=3.6 - 5 only
			// Old Firefox doesn't throw on a badly-escaped identifier.
			el.querySelectorAll( "\\\f" );
			rbuggyQSA.push( "[\\r\\n\\f]" );
		} );

		assert( function( el ) {
			el.innerHTML = "<a href='' disabled='disabled'></a>" +
				"<select disabled='disabled'><option/></select>";

			// Support: Windows 8 Native Apps
			// The type and name attributes are restricted during .innerHTML assignment
			var input = document.createElement( "input" );
			input.setAttribute( "type", "hidden" );
			el.appendChild( input ).setAttribute( "name", "D" );

			// Support: IE8
			// Enforce case-sensitivity of name attribute
			if ( el.querySelectorAll( "[name=d]" ).length ) {
				rbuggyQSA.push( "name" + whitespace + "*[*^$|!~]?=" );
			}

			// FF 3.5 - :enabled/:disabled and hidden elements (hidden elements are still enabled)
			// IE8 throws error here and will not see later tests
			if ( el.querySelectorAll( ":enabled" ).length !== 2 ) {
				rbuggyQSA.push( ":enabled", ":disabled" );
			}

			// Support: IE9-11+
			// IE's :disabled selector does not pick up the children of disabled fieldsets
			docElem.appendChild( el ).disabled = true;
			if ( el.querySelectorAll( ":disabled" ).length !== 2 ) {
				rbuggyQSA.push( ":enabled", ":disabled" );
			}

			// Support: Opera 10 - 11 only
			// Opera 10-11 does not throw on post-comma invalid pseudos
			el.querySelectorAll( "*,:x" );
			rbuggyQSA.push( ",.*:" );
		} );
	}

	if ( ( support.matchesSelector = rnative.test( ( matches = docElem.matches ||
		docElem.webkitMatchesSelector ||
		docElem.mozMatchesSelector ||
		docElem.oMatchesSelector ||
		docElem.msMatchesSelector ) ) ) ) {

		assert( function( el ) {

			// Check to see if it's possible to do matchesSelector
			// on a disconnected node (IE 9)
			support.disconnectedMatch = matches.call( el, "*" );

			// This should fail with an exception
			// Gecko does not error, returns false instead
			matches.call( el, "[s!='']:x" );
			rbuggyMatches.push( "!=", pseudos );
		} );
	}

	rbuggyQSA = rbuggyQSA.length && new RegExp( rbuggyQSA.join( "|" ) );
	rbuggyMatches = rbuggyMatches.length && new RegExp( rbuggyMatches.join( "|" ) );

	/* Contains
	---------------------------------------------------------------------- */
	hasCompare = rnative.test( docElem.compareDocumentPosition );

	// Element contains another
	// Purposefully self-exclusive
	// As in, an element does not contain itself
	contains = hasCompare || rnative.test( docElem.contains ) ?
		function( a, b ) {
			var adown = a.nodeType === 9 ? a.documentElement : a,
				bup = b && b.parentNode;
			return a === bup || !!( bup && bup.nodeType === 1 && (
				adown.contains ?
					adown.contains( bup ) :
					a.compareDocumentPosition && a.compareDocumentPosition( bup ) & 16
			) );
		} :
		function( a, b ) {
			if ( b ) {
				while ( ( b = b.parentNode ) ) {
					if ( b === a ) {
						return true;
					}
				}
			}
			return false;
		};

	/* Sorting
	---------------------------------------------------------------------- */

	// Document order sorting
	sortOrder = hasCompare ?
	function( a, b ) {

		// Flag for duplicate removal
		if ( a === b ) {
			hasDuplicate = true;
			return 0;
		}

		// Sort on method existence if only one input has compareDocumentPosition
		var compare = !a.compareDocumentPosition - !b.compareDocumentPosition;
		if ( compare ) {
			return compare;
		}

		// Calculate position if both inputs belong to the same document
		// Support: IE 11+, Edge 17 - 18+
		// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
		// two documents; shallow comparisons work.
		// eslint-disable-next-line eqeqeq
		compare = ( a.ownerDocument || a ) == ( b.ownerDocument || b ) ?
			a.compareDocumentPosition( b ) :

			// Otherwise we know they are disconnected
			1;

		// Disconnected nodes
		if ( compare & 1 ||
			( !support.sortDetached && b.compareDocumentPosition( a ) === compare ) ) {

			// Choose the first element that is related to our preferred document
			// Support: IE 11+, Edge 17 - 18+
			// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
			// two documents; shallow comparisons work.
			// eslint-disable-next-line eqeqeq
			if ( a == document || a.ownerDocument == preferredDoc &&
				contains( preferredDoc, a ) ) {
				return -1;
			}

			// Support: IE 11+, Edge 17 - 18+
			// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
			// two documents; shallow comparisons work.
			// eslint-disable-next-line eqeqeq
			if ( b == document || b.ownerDocument == preferredDoc &&
				contains( preferredDoc, b ) ) {
				return 1;
			}

			// Maintain original order
			return sortInput ?
				( indexOf( sortInput, a ) - indexOf( sortInput, b ) ) :
				0;
		}

		return compare & 4 ? -1 : 1;
	} :
	function( a, b ) {

		// Exit early if the nodes are identical
		if ( a === b ) {
			hasDuplicate = true;
			return 0;
		}

		var cur,
			i = 0,
			aup = a.parentNode,
			bup = b.parentNode,
			ap = [ a ],
			bp = [ b ];

		// Parentless nodes are either documents or disconnected
		if ( !aup || !bup ) {

			// Support: IE 11+, Edge 17 - 18+
			// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
			// two documents; shallow comparisons work.
			/* eslint-disable eqeqeq */
			return a == document ? -1 :
				b == document ? 1 :
				/* eslint-enable eqeqeq */
				aup ? -1 :
				bup ? 1 :
				sortInput ?
				( indexOf( sortInput, a ) - indexOf( sortInput, b ) ) :
				0;

		// If the nodes are siblings, we can do a quick check
		} else if ( aup === bup ) {
			return siblingCheck( a, b );
		}

		// Otherwise we need full lists of their ancestors for comparison
		cur = a;
		while ( ( cur = cur.parentNode ) ) {
			ap.unshift( cur );
		}
		cur = b;
		while ( ( cur = cur.parentNode ) ) {
			bp.unshift( cur );
		}

		// Walk down the tree looking for a discrepancy
		while ( ap[ i ] === bp[ i ] ) {
			i++;
		}

		return i ?

			// Do a sibling check if the nodes have a common ancestor
			siblingCheck( ap[ i ], bp[ i ] ) :

			// Otherwise nodes in our document sort first
			// Support: IE 11+, Edge 17 - 18+
			// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
			// two documents; shallow comparisons work.
			/* eslint-disable eqeqeq */
			ap[ i ] == preferredDoc ? -1 :
			bp[ i ] == preferredDoc ? 1 :
			/* eslint-enable eqeqeq */
			0;
	};

	return document;
};

Sizzle.matches = function( expr, elements ) {
	return Sizzle( expr, null, null, elements );
};

Sizzle.matchesSelector = function( elem, expr ) {
	setDocument( elem );

	if ( support.matchesSelector && documentIsHTML &&
		!nonnativeSelectorCache[ expr + " " ] &&
		( !rbuggyMatches || !rbuggyMatches.test( expr ) ) &&
		( !rbuggyQSA     || !rbuggyQSA.test( expr ) ) ) {

		try {
			var ret = matches.call( elem, expr );

			// IE 9's matchesSelector returns false on disconnected nodes
			if ( ret || support.disconnectedMatch ||

				// As well, disconnected nodes are said to be in a document
				// fragment in IE 9
				elem.document && elem.document.nodeType !== 11 ) {
				return ret;
			}
		} catch ( e ) {
			nonnativeSelectorCache( expr, true );
		}
	}

	return Sizzle( expr, document, null, [ elem ] ).length > 0;
};

Sizzle.contains = function( context, elem ) {

	// Set document vars if needed
	// Support: IE 11+, Edge 17 - 18+
	// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
	// two documents; shallow comparisons work.
	// eslint-disable-next-line eqeqeq
	if ( ( context.ownerDocument || context ) != document ) {
		setDocument( context );
	}
	return contains( context, elem );
};

Sizzle.attr = function( elem, name ) {

	// Set document vars if needed
	// Support: IE 11+, Edge 17 - 18+
	// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
	// two documents; shallow comparisons work.
	// eslint-disable-next-line eqeqeq
	if ( ( elem.ownerDocument || elem ) != document ) {
		setDocument( elem );
	}

	var fn = Expr.attrHandle[ name.toLowerCase() ],

		// Don't get fooled by Object.prototype properties (jQuery #13807)
		val = fn && hasOwn.call( Expr.attrHandle, name.toLowerCase() ) ?
			fn( elem, name, !documentIsHTML ) :
			undefined;

	return val !== undefined ?
		val :
		support.attributes || !documentIsHTML ?
			elem.getAttribute( name ) :
			( val = elem.getAttributeNode( name ) ) && val.specified ?
				val.value :
				null;
};

Sizzle.escape = function( sel ) {
	return ( sel + "" ).replace( rcssescape, fcssescape );
};

Sizzle.error = function( msg ) {
	throw new Error( "Syntax error, unrecognized expression: " + msg );
};

/**
 * Document sorting and removing duplicates
 * @param {ArrayLike} results
 */
Sizzle.uniqueSort = function( results ) {
	var elem,
		duplicates = [],
		j = 0,
		i = 0;

	// Unless we *know* we can detect duplicates, assume their presence
	hasDuplicate = !support.detectDuplicates;
	sortInput = !support.sortStable && results.slice( 0 );
	results.sort( sortOrder );

	if ( hasDuplicate ) {
		while ( ( elem = results[ i++ ] ) ) {
			if ( elem === results[ i ] ) {
				j = duplicates.push( i );
			}
		}
		while ( j-- ) {
			results.splice( duplicates[ j ], 1 );
		}
	}

	// Clear input after sorting to release objects
	// See https://github.com/jquery/sizzle/pull/225
	sortInput = null;

	return results;
};

/**
 * Utility function for retrieving the text value of an array of DOM nodes
 * @param {Array|Element} elem
 */
getText = Sizzle.getText = function( elem ) {
	var node,
		ret = "",
		i = 0,
		nodeType = elem.nodeType;

	if ( !nodeType ) {

		// If no nodeType, this is expected to be an array
		while ( ( node = elem[ i++ ] ) ) {

			// Do not traverse comment nodes
			ret += getText( node );
		}
	} else if ( nodeType === 1 || nodeType === 9 || nodeType === 11 ) {

		// Use textContent for elements
		// innerText usage removed for consistency of new lines (jQuery #11153)
		if ( typeof elem.textContent === "string" ) {
			return elem.textContent;
		} else {

			// Traverse its children
			for ( elem = elem.firstChild; elem; elem = elem.nextSibling ) {
				ret += getText( elem );
			}
		}
	} else if ( nodeType === 3 || nodeType === 4 ) {
		return elem.nodeValue;
	}

	// Do not include comment or processing instruction nodes

	return ret;
};

Expr = Sizzle.selectors = {

	// Can be adjusted by the user
	cacheLength: 50,

	createPseudo: markFunction,

	match: matchExpr,

	attrHandle: {},

	find: {},

	relative: {
		">": { dir: "parentNode", first: true },
		" ": { dir: "parentNode" },
		"+": { dir: "previousSibling", first: true },
		"~": { dir: "previousSibling" }
	},

	preFilter: {
		"ATTR": function( match ) {
			match[ 1 ] = match[ 1 ].replace( runescape, funescape );

			// Move the given value to match[3] whether quoted or unquoted
			match[ 3 ] = ( match[ 3 ] || match[ 4 ] ||
				match[ 5 ] || "" ).replace( runescape, funescape );

			if ( match[ 2 ] === "~=" ) {
				match[ 3 ] = " " + match[ 3 ] + " ";
			}

			return match.slice( 0, 4 );
		},

		"CHILD": function( match ) {

			/* matches from matchExpr["CHILD"]
				1 type (only|nth|...)
				2 what (child|of-type)
				3 argument (even|odd|\d*|\d*n([+-]\d+)?|...)
				4 xn-component of xn+y argument ([+-]?\d*n|)
				5 sign of xn-component
				6 x of xn-component
				7 sign of y-component
				8 y of y-component
			*/
			match[ 1 ] = match[ 1 ].toLowerCase();

			if ( match[ 1 ].slice( 0, 3 ) === "nth" ) {

				// nth-* requires argument
				if ( !match[ 3 ] ) {
					Sizzle.error( match[ 0 ] );
				}

				// numeric x and y parameters for Expr.filter.CHILD
				// remember that false/true cast respectively to 0/1
				match[ 4 ] = +( match[ 4 ] ?
					match[ 5 ] + ( match[ 6 ] || 1 ) :
					2 * ( match[ 3 ] === "even" || match[ 3 ] === "odd" ) );
				match[ 5 ] = +( ( match[ 7 ] + match[ 8 ] ) || match[ 3 ] === "odd" );

				// other types prohibit arguments
			} else if ( match[ 3 ] ) {
				Sizzle.error( match[ 0 ] );
			}

			return match;
		},

		"PSEUDO": function( match ) {
			var excess,
				unquoted = !match[ 6 ] && match[ 2 ];

			if ( matchExpr[ "CHILD" ].test( match[ 0 ] ) ) {
				return null;
			}

			// Accept quoted arguments as-is
			if ( match[ 3 ] ) {
				match[ 2 ] = match[ 4 ] || match[ 5 ] || "";

			// Strip excess characters from unquoted arguments
			} else if ( unquoted && rpseudo.test( unquoted ) &&

				// Get excess from tokenize (recursively)
				( excess = tokenize( unquoted, true ) ) &&

				// advance to the next closing parenthesis
				( excess = unquoted.indexOf( ")", unquoted.length - excess ) - unquoted.length ) ) {

				// excess is a negative index
				match[ 0 ] = match[ 0 ].slice( 0, excess );
				match[ 2 ] = unquoted.slice( 0, excess );
			}

			// Return only captures needed by the pseudo filter method (type and argument)
			return match.slice( 0, 3 );
		}
	},

	filter: {

		"TAG": function( nodeNameSelector ) {
			var nodeName = nodeNameSelector.replace( runescape, funescape ).toLowerCase();
			return nodeNameSelector === "*" ?
				function() {
					return true;
				} :
				function( elem ) {
					return elem.nodeName && elem.nodeName.toLowerCase() === nodeName;
				};
		},

		"CLASS": function( className ) {
			var pattern = classCache[ className + " " ];

			return pattern ||
				( pattern = new RegExp( "(^|" + whitespace +
					")" + className + "(" + whitespace + "|$)" ) ) && classCache(
						className, function( elem ) {
							return pattern.test(
								typeof elem.className === "string" && elem.className ||
								typeof elem.getAttribute !== "undefined" &&
									elem.getAttribute( "class" ) ||
								""
							);
				} );
		},

		"ATTR": function( name, operator, check ) {
			return function( elem ) {
				var result = Sizzle.attr( elem, name );

				if ( result == null ) {
					return operator === "!=";
				}
				if ( !operator ) {
					return true;
				}

				result += "";

				/* eslint-disable max-len */

				return operator === "=" ? result === check :
					operator === "!=" ? result !== check :
					operator === "^=" ? check && result.indexOf( check ) === 0 :
					operator === "*=" ? check && result.indexOf( check ) > -1 :
					operator === "$=" ? check && result.slice( -check.length ) === check :
					operator === "~=" ? ( " " + result.replace( rwhitespace, " " ) + " " ).indexOf( check ) > -1 :
					operator === "|=" ? result === check || result.slice( 0, check.length + 1 ) === check + "-" :
					false;
				/* eslint-enable max-len */

			};
		},

		"CHILD": function( type, what, _argument, first, last ) {
			var simple = type.slice( 0, 3 ) !== "nth",
				forward = type.slice( -4 ) !== "last",
				ofType = what === "of-type";

			return first === 1 && last === 0 ?

				// Shortcut for :nth-*(n)
				function( elem ) {
					return !!elem.parentNode;
				} :

				function( elem, _context, xml ) {
					var cache, uniqueCache, outerCache, node, nodeIndex, start,
						dir = simple !== forward ? "nextSibling" : "previousSibling",
						parent = elem.parentNode,
						name = ofType && elem.nodeName.toLowerCase(),
						useCache = !xml && !ofType,
						diff = false;

					if ( parent ) {

						// :(first|last|only)-(child|of-type)
						if ( simple ) {
							while ( dir ) {
								node = elem;
								while ( ( node = node[ dir ] ) ) {
									if ( ofType ?
										node.nodeName.toLowerCase() === name :
										node.nodeType === 1 ) {

										return false;
									}
								}

								// Reverse direction for :only-* (if we haven't yet done so)
								start = dir = type === "only" && !start && "nextSibling";
							}
							return true;
						}

						start = [ forward ? parent.firstChild : parent.lastChild ];

						// non-xml :nth-child(...) stores cache data on `parent`
						if ( forward && useCache ) {

							// Seek `elem` from a previously-cached index

							// ...in a gzip-friendly way
							node = parent;
							outerCache = node[ expando ] || ( node[ expando ] = {} );

							// Support: IE <9 only
							// Defend against cloned attroperties (jQuery gh-1709)
							uniqueCache = outerCache[ node.uniqueID ] ||
								( outerCache[ node.uniqueID ] = {} );

							cache = uniqueCache[ type ] || [];
							nodeIndex = cache[ 0 ] === dirruns && cache[ 1 ];
							diff = nodeIndex && cache[ 2 ];
							node = nodeIndex && parent.childNodes[ nodeIndex ];

							while ( ( node = ++nodeIndex && node && node[ dir ] ||

								// Fallback to seeking `elem` from the start
								( diff = nodeIndex = 0 ) || start.pop() ) ) {

								// When found, cache indexes on `parent` and break
								if ( node.nodeType === 1 && ++diff && node === elem ) {
									uniqueCache[ type ] = [ dirruns, nodeIndex, diff ];
									break;
								}
							}

						} else {

							// Use previously-cached element index if available
							if ( useCache ) {

								// ...in a gzip-friendly way
								node = elem;
								outerCache = node[ expando ] || ( node[ expando ] = {} );

								// Support: IE <9 only
								// Defend against cloned attroperties (jQuery gh-1709)
								uniqueCache = outerCache[ node.uniqueID ] ||
									( outerCache[ node.uniqueID ] = {} );

								cache = uniqueCache[ type ] || [];
								nodeIndex = cache[ 0 ] === dirruns && cache[ 1 ];
								diff = nodeIndex;
							}

							// xml :nth-child(...)
							// or :nth-last-child(...) or :nth(-last)?-of-type(...)
							if ( diff === false ) {

								// Use the same loop as above to seek `elem` from the start
								while ( ( node = ++nodeIndex && node && node[ dir ] ||
									( diff = nodeIndex = 0 ) || start.pop() ) ) {

									if ( ( ofType ?
										node.nodeName.toLowerCase() === name :
										node.nodeType === 1 ) &&
										++diff ) {

										// Cache the index of each encountered element
										if ( useCache ) {
											outerCache = node[ expando ] ||
												( node[ expando ] = {} );

											// Support: IE <9 only
											// Defend against cloned attroperties (jQuery gh-1709)
											uniqueCache = outerCache[ node.uniqueID ] ||
												( outerCache[ node.uniqueID ] = {} );

											uniqueCache[ type ] = [ dirruns, diff ];
										}

										if ( node === elem ) {
											break;
										}
									}
								}
							}
						}

						// Incorporate the offset, then check against cycle size
						diff -= last;
						return diff === first || ( diff % first === 0 && diff / first >= 0 );
					}
				};
		},

		"PSEUDO": function( pseudo, argument ) {

			// pseudo-class names are case-insensitive
			// http://www.w3.org/TR/selectors/#pseudo-classes
			// Prioritize by case sensitivity in case custom pseudos are added with uppercase letters
			// Remember that setFilters inherits from pseudos
			var args,
				fn = Expr.pseudos[ pseudo ] || Expr.setFilters[ pseudo.toLowerCase() ] ||
					Sizzle.error( "unsupported pseudo: " + pseudo );

			// The user may use createPseudo to indicate that
			// arguments are needed to create the filter function
			// just as Sizzle does
			if ( fn[ expando ] ) {
				return fn( argument );
			}

			// But maintain support for old signatures
			if ( fn.length > 1 ) {
				args = [ pseudo, pseudo, "", argument ];
				return Expr.setFilters.hasOwnProperty( pseudo.toLowerCase() ) ?
					markFunction( function( seed, matches ) {
						var idx,
							matched = fn( seed, argument ),
							i = matched.length;
						while ( i-- ) {
							idx = indexOf( seed, matched[ i ] );
							seed[ idx ] = !( matches[ idx ] = matched[ i ] );
						}
					} ) :
					function( elem ) {
						return fn( elem, 0, args );
					};
			}

			return fn;
		}
	},

	pseudos: {

		// Potentially complex pseudos
		"not": markFunction( function( selector ) {

			// Trim the selector passed to compile
			// to avoid treating leading and trailing
			// spaces as combinators
			var input = [],
				results = [],
				matcher = compile( selector.replace( rtrim, "$1" ) );

			return matcher[ expando ] ?
				markFunction( function( seed, matches, _context, xml ) {
					var elem,
						unmatched = matcher( seed, null, xml, [] ),
						i = seed.length;

					// Match elements unmatched by `matcher`
					while ( i-- ) {
						if ( ( elem = unmatched[ i ] ) ) {
							seed[ i ] = !( matches[ i ] = elem );
						}
					}
				} ) :
				function( elem, _context, xml ) {
					input[ 0 ] = elem;
					matcher( input, null, xml, results );

					// Don't keep the element (issue #299)
					input[ 0 ] = null;
					return !results.pop();
				};
		} ),

		"has": markFunction( function( selector ) {
			return function( elem ) {
				return Sizzle( selector, elem ).length > 0;
			};
		} ),

		"contains": markFunction( function( text ) {
			text = text.replace( runescape, funescape );
			return function( elem ) {
				return ( elem.textContent || getText( elem ) ).indexOf( text ) > -1;
			};
		} ),

		// "Whether an element is represented by a :lang() selector
		// is based solely on the element's language value
		// being equal to the identifier C,
		// or beginning with the identifier C immediately followed by "-".
		// The matching of C against the element's language value is performed case-insensitively.
		// The identifier C does not have to be a valid language name."
		// http://www.w3.org/TR/selectors/#lang-pseudo
		"lang": markFunction( function( lang ) {

			// lang value must be a valid identifier
			if ( !ridentifier.test( lang || "" ) ) {
				Sizzle.error( "unsupported lang: " + lang );
			}
			lang = lang.replace( runescape, funescape ).toLowerCase();
			return function( elem ) {
				var elemLang;
				do {
					if ( ( elemLang = documentIsHTML ?
						elem.lang :
						elem.getAttribute( "xml:lang" ) || elem.getAttribute( "lang" ) ) ) {

						elemLang = elemLang.toLowerCase();
						return elemLang === lang || elemLang.indexOf( lang + "-" ) === 0;
					}
				} while ( ( elem = elem.parentNode ) && elem.nodeType === 1 );
				return false;
			};
		} ),

		// Miscellaneous
		"target": function( elem ) {
			var hash = window.location && window.location.hash;
			return hash && hash.slice( 1 ) === elem.id;
		},

		"root": function( elem ) {
			return elem === docElem;
		},

		"focus": function( elem ) {
			return elem === document.activeElement &&
				( !document.hasFocus || document.hasFocus() ) &&
				!!( elem.type || elem.href || ~elem.tabIndex );
		},

		// Boolean properties
		"enabled": createDisabledPseudo( false ),
		"disabled": createDisabledPseudo( true ),

		"checked": function( elem ) {

			// In CSS3, :checked should return both checked and selected elements
			// http://www.w3.org/TR/2011/REC-css3-selectors-20110929/#checked
			var nodeName = elem.nodeName.toLowerCase();
			return ( nodeName === "input" && !!elem.checked ) ||
				( nodeName === "option" && !!elem.selected );
		},

		"selected": function( elem ) {

			// Accessing this property makes selected-by-default
			// options in Safari work properly
			if ( elem.parentNode ) {
				// eslint-disable-next-line no-unused-expressions
				elem.parentNode.selectedIndex;
			}

			return elem.selected === true;
		},

		// Contents
		"empty": function( elem ) {

			// http://www.w3.org/TR/selectors/#empty-pseudo
			// :empty is negated by element (1) or content nodes (text: 3; cdata: 4; entity ref: 5),
			//   but not by others (comment: 8; processing instruction: 7; etc.)
			// nodeType < 6 works because attributes (2) do not appear as children
			for ( elem = elem.firstChild; elem; elem = elem.nextSibling ) {
				if ( elem.nodeType < 6 ) {
					return false;
				}
			}
			return true;
		},

		"parent": function( elem ) {
			return !Expr.pseudos[ "empty" ]( elem );
		},

		// Element/input types
		"header": function( elem ) {
			return rheader.test( elem.nodeName );
		},

		"input": function( elem ) {
			return rinputs.test( elem.nodeName );
		},

		"button": function( elem ) {
			var name = elem.nodeName.toLowerCase();
			return name === "input" && elem.type === "button" || name === "button";
		},

		"text": function( elem ) {
			var attr;
			return elem.nodeName.toLowerCase() === "input" &&
				elem.type === "text" &&

				// Support: IE<8
				// New HTML5 attribute values (e.g., "search") appear with elem.type === "text"
				( ( attr = elem.getAttribute( "type" ) ) == null ||
					attr.toLowerCase() === "text" );
		},

		// Position-in-collection
		"first": createPositionalPseudo( function() {
			return [ 0 ];
		} ),

		"last": createPositionalPseudo( function( _matchIndexes, length ) {
			return [ length - 1 ];
		} ),

		"eq": createPositionalPseudo( function( _matchIndexes, length, argument ) {
			return [ argument < 0 ? argument + length : argument ];
		} ),

		"even": createPositionalPseudo( function( matchIndexes, length ) {
			var i = 0;
			for ( ; i < length; i += 2 ) {
				matchIndexes.push( i );
			}
			return matchIndexes;
		} ),

		"odd": createPositionalPseudo( function( matchIndexes, length ) {
			var i = 1;
			for ( ; i < length; i += 2 ) {
				matchIndexes.push( i );
			}
			return matchIndexes;
		} ),

		"lt": createPositionalPseudo( function( matchIndexes, length, argument ) {
			var i = argument < 0 ?
				argument + length :
				argument > length ?
					length :
					argument;
			for ( ; --i >= 0; ) {
				matchIndexes.push( i );
			}
			return matchIndexes;
		} ),

		"gt": createPositionalPseudo( function( matchIndexes, length, argument ) {
			var i = argument < 0 ? argument + length : argument;
			for ( ; ++i < length; ) {
				matchIndexes.push( i );
			}
			return matchIndexes;
		} )
	}
};

Expr.pseudos[ "nth" ] = Expr.pseudos[ "eq" ];

// Add button/input type pseudos
for ( i in { radio: true, checkbox: true, file: true, password: true, image: true } ) {
	Expr.pseudos[ i ] = createInputPseudo( i );
}
for ( i in { submit: true, reset: true } ) {
	Expr.pseudos[ i ] = createButtonPseudo( i );
}

// Easy API for creating new setFilters
function setFilters() {}
setFilters.prototype = Expr.filters = Expr.pseudos;
Expr.setFilters = new setFilters();

tokenize = Sizzle.tokenize = function( selector, parseOnly ) {
	var matched, match, tokens, type,
		soFar, groups, preFilters,
		cached = tokenCache[ selector + " " ];

	if ( cached ) {
		return parseOnly ? 0 : cached.slice( 0 );
	}

	soFar = selector;
	groups = [];
	preFilters = Expr.preFilter;

	while ( soFar ) {

		// Comma and first run
		if ( !matched || ( match = rcomma.exec( soFar ) ) ) {
			if ( match ) {

				// Don't consume trailing commas as valid
				soFar = soFar.slice( match[ 0 ].length ) || soFar;
			}
			groups.push( ( tokens = [] ) );
		}

		matched = false;

		// Combinators
		if ( ( match = rcombinators.exec( soFar ) ) ) {
			matched = match.shift();
			tokens.push( {
				value: matched,

				// Cast descendant combinators to space
				type: match[ 0 ].replace( rtrim, " " )
			} );
			soFar = soFar.slice( matched.length );
		}

		// Filters
		for ( type in Expr.filter ) {
			if ( ( match = matchExpr[ type ].exec( soFar ) ) && ( !preFilters[ type ] ||
				( match = preFilters[ type ]( match ) ) ) ) {
				matched = match.shift();
				tokens.push( {
					value: matched,
					type: type,
					matches: match
				} );
				soFar = soFar.slice( matched.length );
			}
		}

		if ( !matched ) {
			break;
		}
	}

	// Return the length of the invalid excess
	// if we're just parsing
	// Otherwise, throw an error or return tokens
	return parseOnly ?
		soFar.length :
		soFar ?
			Sizzle.error( selector ) :

			// Cache the tokens
			tokenCache( selector, groups ).slice( 0 );
};

function toSelector( tokens ) {
	var i = 0,
		len = tokens.length,
		selector = "";
	for ( ; i < len; i++ ) {
		selector += tokens[ i ].value;
	}
	return selector;
}

function addCombinator( matcher, combinator, base ) {
	var dir = combinator.dir,
		skip = combinator.next,
		key = skip || dir,
		checkNonElements = base && key === "parentNode",
		doneName = done++;

	return combinator.first ?

		// Check against closest ancestor/preceding element
		function( elem, context, xml ) {
			while ( ( elem = elem[ dir ] ) ) {
				if ( elem.nodeType === 1 || checkNonElements ) {
					return matcher( elem, context, xml );
				}
			}
			return false;
		} :

		// Check against all ancestor/preceding elements
		function( elem, context, xml ) {
			var oldCache, uniqueCache, outerCache,
				newCache = [ dirruns, doneName ];

			// We can't set arbitrary data on XML nodes, so they don't benefit from combinator caching
			if ( xml ) {
				while ( ( elem = elem[ dir ] ) ) {
					if ( elem.nodeType === 1 || checkNonElements ) {
						if ( matcher( elem, context, xml ) ) {
							return true;
						}
					}
				}
			} else {
				while ( ( elem = elem[ dir ] ) ) {
					if ( elem.nodeType === 1 || checkNonElements ) {
						outerCache = elem[ expando ] || ( elem[ expando ] = {} );

						// Support: IE <9 only
						// Defend against cloned attroperties (jQuery gh-1709)
						uniqueCache = outerCache[ elem.uniqueID ] ||
							( outerCache[ elem.uniqueID ] = {} );

						if ( skip && skip === elem.nodeName.toLowerCase() ) {
							elem = elem[ dir ] || elem;
						} else if ( ( oldCache = uniqueCache[ key ] ) &&
							oldCache[ 0 ] === dirruns && oldCache[ 1 ] === doneName ) {

							// Assign to newCache so results back-propagate to previous elements
							return ( newCache[ 2 ] = oldCache[ 2 ] );
						} else {

							// Reuse newcache so results back-propagate to previous elements
							uniqueCache[ key ] = newCache;

							// A match means we're done; a fail means we have to keep checking
							if ( ( newCache[ 2 ] = matcher( elem, context, xml ) ) ) {
								return true;
							}
						}
					}
				}
			}
			return false;
		};
}

function elementMatcher( matchers ) {
	return matchers.length > 1 ?
		function( elem, context, xml ) {
			var i = matchers.length;
			while ( i-- ) {
				if ( !matchers[ i ]( elem, context, xml ) ) {
					return false;
				}
			}
			return true;
		} :
		matchers[ 0 ];
}

function multipleContexts( selector, contexts, results ) {
	var i = 0,
		len = contexts.length;
	for ( ; i < len; i++ ) {
		Sizzle( selector, contexts[ i ], results );
	}
	return results;
}

function condense( unmatched, map, filter, context, xml ) {
	var elem,
		newUnmatched = [],
		i = 0,
		len = unmatched.length,
		mapped = map != null;

	for ( ; i < len; i++ ) {
		if ( ( elem = unmatched[ i ] ) ) {
			if ( !filter || filter( elem, context, xml ) ) {
				newUnmatched.push( elem );
				if ( mapped ) {
					map.push( i );
				}
			}
		}
	}

	return newUnmatched;
}

function setMatcher( preFilter, selector, matcher, postFilter, postFinder, postSelector ) {
	if ( postFilter && !postFilter[ expando ] ) {
		postFilter = setMatcher( postFilter );
	}
	if ( postFinder && !postFinder[ expando ] ) {
		postFinder = setMatcher( postFinder, postSelector );
	}
	return markFunction( function( seed, results, context, xml ) {
		var temp, i, elem,
			preMap = [],
			postMap = [],
			preexisting = results.length,

			// Get initial elements from seed or context
			elems = seed || multipleContexts(
				selector || "*",
				context.nodeType ? [ context ] : context,
				[]
			),

			// Prefilter to get matcher input, preserving a map for seed-results synchronization
			matcherIn = preFilter && ( seed || !selector ) ?
				condense( elems, preMap, preFilter, context, xml ) :
				elems,

			matcherOut = matcher ?

				// If we have a postFinder, or filtered seed, or non-seed postFilter or preexisting results,
				postFinder || ( seed ? preFilter : preexisting || postFilter ) ?

					// ...intermediate processing is necessary
					[] :

					// ...otherwise use results directly
					results :
				matcherIn;

		// Find primary matches
		if ( matcher ) {
			matcher( matcherIn, matcherOut, context, xml );
		}

		// Apply postFilter
		if ( postFilter ) {
			temp = condense( matcherOut, postMap );
			postFilter( temp, [], context, xml );

			// Un-match failing elements by moving them back to matcherIn
			i = temp.length;
			while ( i-- ) {
				if ( ( elem = temp[ i ] ) ) {
					matcherOut[ postMap[ i ] ] = !( matcherIn[ postMap[ i ] ] = elem );
				}
			}
		}

		if ( seed ) {
			if ( postFinder || preFilter ) {
				if ( postFinder ) {

					// Get the final matcherOut by condensing this intermediate into postFinder contexts
					temp = [];
					i = matcherOut.length;
					while ( i-- ) {
						if ( ( elem = matcherOut[ i ] ) ) {

							// Restore matcherIn since elem is not yet a final match
							temp.push( ( matcherIn[ i ] = elem ) );
						}
					}
					postFinder( null, ( matcherOut = [] ), temp, xml );
				}

				// Move matched elements from seed to results to keep them synchronized
				i = matcherOut.length;
				while ( i-- ) {
					if ( ( elem = matcherOut[ i ] ) &&
						( temp = postFinder ? indexOf( seed, elem ) : preMap[ i ] ) > -1 ) {

						seed[ temp ] = !( results[ temp ] = elem );
					}
				}
			}

		// Add elements to results, through postFinder if defined
		} else {
			matcherOut = condense(
				matcherOut === results ?
					matcherOut.splice( preexisting, matcherOut.length ) :
					matcherOut
			);
			if ( postFinder ) {
				postFinder( null, results, matcherOut, xml );
			} else {
				push.apply( results, matcherOut );
			}
		}
	} );
}

function matcherFromTokens( tokens ) {
	var checkContext, matcher, j,
		len = tokens.length,
		leadingRelative = Expr.relative[ tokens[ 0 ].type ],
		implicitRelative = leadingRelative || Expr.relative[ " " ],
		i = leadingRelative ? 1 : 0,

		// The foundational matcher ensures that elements are reachable from top-level context(s)
		matchContext = addCombinator( function( elem ) {
			return elem === checkContext;
		}, implicitRelative, true ),
		matchAnyContext = addCombinator( function( elem ) {
			return indexOf( checkContext, elem ) > -1;
		}, implicitRelative, true ),
		matchers = [ function( elem, context, xml ) {
			var ret = ( !leadingRelative && ( xml || context !== outermostContext ) ) || (
				( checkContext = context ).nodeType ?
					matchContext( elem, context, xml ) :
					matchAnyContext( elem, context, xml ) );

			// Avoid hanging onto element (issue #299)
			checkContext = null;
			return ret;
		} ];

	for ( ; i < len; i++ ) {
		if ( ( matcher = Expr.relative[ tokens[ i ].type ] ) ) {
			matchers = [ addCombinator( elementMatcher( matchers ), matcher ) ];
		} else {
			matcher = Expr.filter[ tokens[ i ].type ].apply( null, tokens[ i ].matches );

			// Return special upon seeing a positional matcher
			if ( matcher[ expando ] ) {

				// Find the next relative operator (if any) for proper handling
				j = ++i;
				for ( ; j < len; j++ ) {
					if ( Expr.relative[ tokens[ j ].type ] ) {
						break;
					}
				}
				return setMatcher(
					i > 1 && elementMatcher( matchers ),
					i > 1 && toSelector(

					// If the preceding token was a descendant combinator, insert an implicit any-element `*`
					tokens
						.slice( 0, i - 1 )
						.concat( { value: tokens[ i - 2 ].type === " " ? "*" : "" } )
					).replace( rtrim, "$1" ),
					matcher,
					i < j && matcherFromTokens( tokens.slice( i, j ) ),
					j < len && matcherFromTokens( ( tokens = tokens.slice( j ) ) ),
					j < len && toSelector( tokens )
				);
			}
			matchers.push( matcher );
		}
	}

	return elementMatcher( matchers );
}

function matcherFromGroupMatchers( elementMatchers, setMatchers ) {
	var bySet = setMatchers.length > 0,
		byElement = elementMatchers.length > 0,
		superMatcher = function( seed, context, xml, results, outermost ) {
			var elem, j, matcher,
				matchedCount = 0,
				i = "0",
				unmatched = seed && [],
				setMatched = [],
				contextBackup = outermostContext,

				// We must always have either seed elements or outermost context
				elems = seed || byElement && Expr.find[ "TAG" ]( "*", outermost ),

				// Use integer dirruns iff this is the outermost matcher
				dirrunsUnique = ( dirruns += contextBackup == null ? 1 : Math.random() || 0.1 ),
				len = elems.length;

			if ( outermost ) {

				// Support: IE 11+, Edge 17 - 18+
				// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
				// two documents; shallow comparisons work.
				// eslint-disable-next-line eqeqeq
				outermostContext = context == document || context || outermost;
			}

			// Add elements passing elementMatchers directly to results
			// Support: IE<9, Safari
			// Tolerate NodeList properties (IE: "length"; Safari: <number>) matching elements by id
			for ( ; i !== len && ( elem = elems[ i ] ) != null; i++ ) {
				if ( byElement && elem ) {
					j = 0;

					// Support: IE 11+, Edge 17 - 18+
					// IE/Edge sometimes throw a "Permission denied" error when strict-comparing
					// two documents; shallow comparisons work.
					// eslint-disable-next-line eqeqeq
					if ( !context && elem.ownerDocument != document ) {
						setDocument( elem );
						xml = !documentIsHTML;
					}
					while ( ( matcher = elementMatchers[ j++ ] ) ) {
						if ( matcher( elem, context || document, xml ) ) {
							results.push( elem );
							break;
						}
					}
					if ( outermost ) {
						dirruns = dirrunsUnique;
					}
				}

				// Track unmatched elements for set filters
				if ( bySet ) {

					// They will have gone through all possible matchers
					if ( ( elem = !matcher && elem ) ) {
						matchedCount--;
					}

					// Lengthen the array for every element, matched or not
					if ( seed ) {
						unmatched.push( elem );
					}
				}
			}

			// `i` is now the count of elements visited above, and adding it to `matchedCount`
			// makes the latter nonnegative.
			matchedCount += i;

			// Apply set filters to unmatched elements
			// NOTE: This can be skipped if there are no unmatched elements (i.e., `matchedCount`
			// equals `i`), unless we didn't visit _any_ elements in the above loop because we have
			// no element matchers and no seed.
			// Incrementing an initially-string "0" `i` allows `i` to remain a string only in that
			// case, which will result in a "00" `matchedCount` that differs from `i` but is also
			// numerically zero.
			if ( bySet && i !== matchedCount ) {
				j = 0;
				while ( ( matcher = setMatchers[ j++ ] ) ) {
					matcher( unmatched, setMatched, context, xml );
				}

				if ( seed ) {

					// Reintegrate element matches to eliminate the need for sorting
					if ( matchedCount > 0 ) {
						while ( i-- ) {
							if ( !( unmatched[ i ] || setMatched[ i ] ) ) {
								setMatched[ i ] = pop.call( results );
							}
						}
					}

					// Discard index placeholder values to get only actual matches
					setMatched = condense( setMatched );
				}

				// Add matches to results
				push.apply( results, setMatched );

				// Seedless set matches succeeding multiple successful matchers stipulate sorting
				if ( outermost && !seed && setMatched.length > 0 &&
					( matchedCount + setMatchers.length ) > 1 ) {

					Sizzle.uniqueSort( results );
				}
			}

			// Override manipulation of globals by nested matchers
			if ( outermost ) {
				dirruns = dirrunsUnique;
				outermostContext = contextBackup;
			}

			return unmatched;
		};

	return bySet ?
		markFunction( superMatcher ) :
		superMatcher;
}

compile = Sizzle.compile = function( selector, match /* Internal Use Only */ ) {
	var i,
		setMatchers = [],
		elementMatchers = [],
		cached = compilerCache[ selector + " " ];

	if ( !cached ) {

		// Generate a function of recursive functions that can be used to check each element
		if ( !match ) {
			match = tokenize( selector );
		}
		i = match.length;
		while ( i-- ) {
			cached = matcherFromTokens( match[ i ] );
			if ( cached[ expando ] ) {
				setMatchers.push( cached );
			} else {
				elementMatchers.push( cached );
			}
		}

		// Cache the compiled function
		cached = compilerCache(
			selector,
			matcherFromGroupMatchers( elementMatchers, setMatchers )
		);

		// Save selector and tokenization
		cached.selector = selector;
	}
	return cached;
};

/**
 * A low-level selection function that works with Sizzle's compiled
 *  selector functions
 * @param {String|Function} selector A selector or a pre-compiled
 *  selector function built with Sizzle.compile
 * @param {Element} context
 * @param {Array} [results]
 * @param {Array} [seed] A set of elements to match against
 */
select = Sizzle.select = function( selector, context, results, seed ) {
	var i, tokens, token, type, find,
		compiled = typeof selector === "function" && selector,
		match = !seed && tokenize( ( selector = compiled.selector || selector ) );

	results = results || [];

	// Try to minimize operations if there is only one selector in the list and no seed
	// (the latter of which guarantees us context)
	if ( match.length === 1 ) {

		// Reduce context if the leading compound selector is an ID
		tokens = match[ 0 ] = match[ 0 ].slice( 0 );
		if ( tokens.length > 2 && ( token = tokens[ 0 ] ).type === "ID" &&
			context.nodeType === 9 && documentIsHTML && Expr.relative[ tokens[ 1 ].type ] ) {

			context = ( Expr.find[ "ID" ]( token.matches[ 0 ]
				.replace( runescape, funescape ), context ) || [] )[ 0 ];
			if ( !context ) {
				return results;

			// Precompiled matchers will still verify ancestry, so step up a level
			} else if ( compiled ) {
				context = context.parentNode;
			}

			selector = selector.slice( tokens.shift().value.length );
		}

		// Fetch a seed set for right-to-left matching
		i = matchExpr[ "needsContext" ].test( selector ) ? 0 : tokens.length;
		while ( i-- ) {
			token = tokens[ i ];

			// Abort if we hit a combinator
			if ( Expr.relative[ ( type = token.type ) ] ) {
				break;
			}
			if ( ( find = Expr.find[ type ] ) ) {

				// Search, expanding context for leading sibling combinators
				if ( ( seed = find(
					token.matches[ 0 ].replace( runescape, funescape ),
					rsibling.test( tokens[ 0 ].type ) && testContext( context.parentNode ) ||
						context
				) ) ) {

					// If seed is empty or no tokens remain, we can return early
					tokens.splice( i, 1 );
					selector = seed.length && toSelector( tokens );
					if ( !selector ) {
						push.apply( results, seed );
						return results;
					}

					break;
				}
			}
		}
	}

	// Compile and execute a filtering function if one is not provided
	// Provide `match` to avoid retokenization if we modified the selector above
	( compiled || compile( selector, match ) )(
		seed,
		context,
		!documentIsHTML,
		results,
		!context || rsibling.test( selector ) && testContext( context.parentNode ) || context
	);
	return results;
};

// One-time assignments

// Sort stability
support.sortStable = expando.split( "" ).sort( sortOrder ).join( "" ) === expando;

// Support: Chrome 14-35+
// Always assume duplicates if they aren't passed to the comparison function
support.detectDuplicates = !!hasDuplicate;

// Initialize against the default document
setDocument();

// Support: Webkit<537.32 - Safari 6.0.3/Chrome 25 (fixed in Chrome 27)
// Detached nodes confoundingly follow *each other*
support.sortDetached = assert( function( el ) {

	// Should return 1, but returns 4 (following)
	return el.compareDocumentPosition( document.createElement( "fieldset" ) ) & 1;
} );

// Support: IE<8
// Prevent attribute/property "interpolation"
// https://msdn.microsoft.com/en-us/library/ms536429%28VS.85%29.aspx
if ( !assert( function( el ) {
	el.innerHTML = "<a href='#'></a>";
	return el.firstChild.getAttribute( "href" ) === "#";
} ) ) {
	addHandle( "type|href|height|width", function( elem, name, isXML ) {
		if ( !isXML ) {
			return elem.getAttribute( name, name.toLowerCase() === "type" ? 1 : 2 );
		}
	} );
}

// Support: IE<9
// Use defaultValue in place of getAttribute("value")
if ( !support.attributes || !assert( function( el ) {
	el.innerHTML = "<input/>";
	el.firstChild.setAttribute( "value", "" );
	return el.firstChild.getAttribute( "value" ) === "";
} ) ) {
	addHandle( "value", function( elem, _name, isXML ) {
		if ( !isXML && elem.nodeName.toLowerCase() === "input" ) {
			return elem.defaultValue;
		}
	} );
}

// Support: IE<9
// Use getAttributeNode to fetch booleans when getAttribute lies
if ( !assert( function( el ) {
	return el.getAttribute( "disabled" ) == null;
} ) ) {
	addHandle( booleans, function( elem, name, isXML ) {
		var val;
		if ( !isXML ) {
			return elem[ name ] === true ? name.toLowerCase() :
				( val = elem.getAttributeNode( name ) ) && val.specified ?
					val.value :
					null;
		}
	} );
}

return Sizzle;

} )( window );



jQuery.find = Sizzle;
jQuery.expr = Sizzle.selectors;

// Deprecated
jQuery.expr[ ":" ] = jQuery.expr.pseudos;
jQuery.uniqueSort = jQuery.unique = Sizzle.uniqueSort;
jQuery.text = Sizzle.getText;
jQuery.isXMLDoc = Sizzle.isXML;
jQuery.contains = Sizzle.contains;
jQuery.escapeSelector = Sizzle.escape;




var dir = function( elem, dir, until ) {
	var matched = [],
		truncate = until !== undefined;

	while ( ( elem = elem[ dir ] ) && elem.nodeType !== 9 ) {
		if ( elem.nodeType === 1 ) {
			if ( truncate && jQuery( elem ).is( until ) ) {
				break;
			}
			matched.push( elem );
		}
	}
	return matched;
};


var siblings = function( n, elem ) {
	var matched = [];

	for ( ; n; n = n.nextSibling ) {
		if ( n.nodeType === 1 && n !== elem ) {
			matched.push( n );
		}
	}

	return matched;
};


var rneedsContext = jQuery.expr.match.needsContext;



function nodeName( elem, name ) {

	return elem.nodeName && elem.nodeName.toLowerCase() === name.toLowerCase();

}
var rsingleTag = ( /^<([a-z][^\/\0>:\x20\t\r\n\f]*)[\x20\t\r\n\f]*\/?>(?:<\/\1>|)$/i );



// Implement the identical functionality for filter and not
function winnow( elements, qualifier, not ) {
	if ( isFunction( qualifier ) ) {
		return jQuery.grep( elements, function( elem, i ) {
			return !!qualifier.call( elem, i, elem ) !== not;
		} );
	}

	// Single element
	if ( qualifier.nodeType ) {
		return jQuery.grep( elements, function( elem ) {
			return ( elem === qualifier ) !== not;
		} );
	}

	// Arraylike of elements (jQuery, arguments, Array)
	if ( typeof qualifier !== "string" ) {
		return jQuery.grep( elements, function( elem ) {
			return ( indexOf.call( qualifier, elem ) > -1 ) !== not;
		} );
	}

	// Filtered directly for both simple and complex selectors
	return jQuery.filter( qualifier, elements, not );
}

jQuery.filter = function( expr, elems, not ) {
	var elem = elems[ 0 ];

	if ( not ) {
		expr = ":not(" + expr + ")";
	}

	if ( elems.length === 1 && elem.nodeType === 1 ) {
		return jQuery.find.matchesSelector( elem, expr ) ? [ elem ] : [];
	}

	return jQuery.find.matches( expr, jQuery.grep( elems, function( elem ) {
		return elem.nodeType === 1;
	} ) );
};

jQuery.fn.extend( {
	find: function( selector ) {
		var i, ret,
			len = this.length,
			self = this;

		if ( typeof selector !== "string" ) {
			return this.pushStack( jQuery( selector ).filter( function() {
				for ( i = 0; i < len; i++ ) {
					if ( jQuery.contains( self[ i ], this ) ) {
						return true;
					}
				}
			} ) );
		}

		ret = this.pushStack( [] );

		for ( i = 0; i < len; i++ ) {
			jQuery.find( selector, self[ i ], ret );
		}

		return len > 1 ? jQuery.uniqueSort( ret ) : ret;
	},
	filter: function( selector ) {
		return this.pushStack( winnow( this, selector || [], false ) );
	},
	not: function( selector ) {
		return this.pushStack( winnow( this, selector || [], true ) );
	},
	is: function( selector ) {
		return !!winnow(
			this,

			// If this is a positional/relative selector, check membership in the returned set
			// so $("p:first").is("p:last") won't return true for a doc with two "p".
			typeof selector === "string" && rneedsContext.test( selector ) ?
				jQuery( selector ) :
				selector || [],
			false
		).length;
	}
} );


// Initialize a jQuery object


// A central reference to the root jQuery(document)
var rootjQuery,

	// A simple way to check for HTML strings
	// Prioritize #id over <tag> to avoid XSS via location.hash (#9521)
	// Strict HTML recognition (#11290: must start with <)
	// Shortcut simple #id case for speed
	rquickExpr = /^(?:\s*(<[\w\W]+>)[^>]*|#([\w-]+))$/,

	init = jQuery.fn.init = function( selector, context, root ) {
		var match, elem;

		// HANDLE: $(""), $(null), $(undefined), $(false)
		if ( !selector ) {
			return this;
		}

		// Method init() accepts an alternate rootjQuery
		// so migrate can support jQuery.sub (gh-2101)
		root = root || rootjQuery;

		// Handle HTML strings
		if ( typeof selector === "string" ) {
			if ( selector[ 0 ] === "<" &&
				selector[ selector.length - 1 ] === ">" &&
				selector.length >= 3 ) {

				// Assume that strings that start and end with <> are HTML and skip the regex check
				match = [ null, selector, null ];

			} else {
				match = rquickExpr.exec( selector );
			}

			// Match html or make sure no context is specified for #id
			if ( match && ( match[ 1 ] || !context ) ) {

				// HANDLE: $(html) -> $(array)
				if ( match[ 1 ] ) {
					context = context instanceof jQuery ? context[ 0 ] : context;

					// Option to run scripts is true for back-compat
					// Intentionally let the error be thrown if parseHTML is not present
					jQuery.merge( this, jQuery.parseHTML(
						match[ 1 ],
						context && context.nodeType ? context.ownerDocument || context : document,
						true
					) );

					// HANDLE: $(html, props)
					if ( rsingleTag.test( match[ 1 ] ) && jQuery.isPlainObject( context ) ) {
						for ( match in context ) {

							// Properties of context are called as methods if possible
							if ( isFunction( this[ match ] ) ) {
								this[ match ]( context[ match ] );

							// ...and otherwise set as attributes
							} else {
								this.attr( match, context[ match ] );
							}
						}
					}

					return this;

				// HANDLE: $(#id)
				} else {
					elem = document.getElementById( match[ 2 ] );

					if ( elem ) {

						// Inject the element directly into the jQuery object
						this[ 0 ] = elem;
						this.length = 1;
					}
					return this;
				}

			// HANDLE: $(expr, $(...))
			} else if ( !context || context.jquery ) {
				return ( context || root ).find( selector );

			// HANDLE: $(expr, context)
			// (which is just equivalent to: $(context).find(expr)
			} else {
				return this.constructor( context ).find( selector );
			}

		// HANDLE: $(DOMElement)
		} else if ( selector.nodeType ) {
			this[ 0 ] = selector;
			this.length = 1;
			return this;

		// HANDLE: $(function)
		// Shortcut for document ready
		} else if ( isFunction( selector ) ) {
			return root.ready !== undefined ?
				root.ready( selector ) :

				// Execute immediately if ready is not present
				selector( jQuery );
		}

		return jQuery.makeArray( selector, this );
	};

// Give the init function the jQuery prototype for later instantiation
init.prototype = jQuery.fn;

// Initialize central reference
rootjQuery = jQuery( document );


var rparentsprev = /^(?:parents|prev(?:Until|All))/,

	// Methods guaranteed to produce a unique set when starting from a unique set
	guaranteedUnique = {
		children: true,
		contents: true,
		next: true,
		prev: true
	};

jQuery.fn.extend( {
	has: function( target ) {
		var targets = jQuery( target, this ),
			l = targets.length;

		return this.filter( function() {
			var i = 0;
			for ( ; i < l; i++ ) {
				if ( jQuery.contains( this, targets[ i ] ) ) {
					return true;
				}
			}
		} );
	},

	closest: function( selectors, context ) {
		var cur,
			i = 0,
			l = this.length,
			matched = [],
			targets = typeof selectors !== "string" && jQuery( selectors );

		// Positional selectors never match, since there's no _selection_ context
		if ( !rneedsContext.test( selectors ) ) {
			for ( ; i < l; i++ ) {
				for ( cur = this[ i ]; cur && cur !== context; cur = cur.parentNode ) {

					// Always skip document fragments
					if ( cur.nodeType < 11 && ( targets ?
						targets.index( cur ) > -1 :

						// Don't pass non-elements to Sizzle
						cur.nodeType === 1 &&
							jQuery.find.matchesSelector( cur, selectors ) ) ) {

						matched.push( cur );
						break;
					}
				}
			}
		}

		return this.pushStack( matched.length > 1 ? jQuery.uniqueSort( matched ) : matched );
	},

	// Determine the position of an element within the set
	index: function( elem ) {

		// No argument, return index in parent
		if ( !elem ) {
			return ( this[ 0 ] && this[ 0 ].parentNode ) ? this.first().prevAll().length : -1;
		}

		// Index in selector
		if ( typeof elem === "string" ) {
			return indexOf.call( jQuery( elem ), this[ 0 ] );
		}

		// Locate the position of the desired element
		return indexOf.call( this,

			// If it receives a jQuery object, the first element is used
			elem.jquery ? elem[ 0 ] : elem
		);
	},

	add: function( selector, context ) {
		return this.pushStack(
			jQuery.uniqueSort(
				jQuery.merge( this.get(), jQuery( selector, context ) )
			)
		);
	},

	addBack: function( selector ) {
		return this.add( selector == null ?
			this.prevObject : this.prevObject.filter( selector )
		);
	}
} );

function sibling( cur, dir ) {
	while ( ( cur = cur[ dir ] ) && cur.nodeType !== 1 ) {}
	return cur;
}

jQuery.each( {
	parent: function( elem ) {
		var parent = elem.parentNode;
		return parent && parent.nodeType !== 11 ? parent : null;
	},
	parents: function( elem ) {
		return dir( elem, "parentNode" );
	},
	parentsUntil: function( elem, _i, until ) {
		return dir( elem, "parentNode", until );
	},
	next: function( elem ) {
		return sibling( elem, "nextSibling" );
	},
	prev: function( elem ) {
		return sibling( elem, "previousSibling" );
	},
	nextAll: function( elem ) {
		return dir( elem, "nextSibling" );
	},
	prevAll: function( elem ) {
		return dir( elem, "previousSibling" );
	},
	nextUntil: function( elem, _i, until ) {
		return dir( elem, "nextSibling", until );
	},
	prevUntil: function( elem, _i, until ) {
		return dir( elem, "previousSibling", until );
	},
	siblings: function( elem ) {
		return siblings( ( elem.parentNode || {} ).firstChild, elem );
	},
	children: function( elem ) {
		return siblings( elem.firstChild );
	},
	contents: function( elem ) {
		if ( elem.contentDocument != null &&

			// Support: IE 11+
			// <object> elements with no `data` attribute has an object
			// `contentDocument` with a `null` prototype.
			getProto( elem.contentDocument ) ) {

			return elem.contentDocument;
		}

		// Support: IE 9 - 11 only, iOS 7 only, Android Browser <=4.3 only
		// Treat the template element as a regular one in browsers that
		// don't support it.
		if ( nodeName( elem, "template" ) ) {
			elem = elem.content || elem;
		}

		return jQuery.merge( [], elem.childNodes );
	}
}, function( name, fn ) {
	jQuery.fn[ name ] = function( until, selector ) {
		var matched = jQuery.map( this, fn, until );

		if ( name.slice( -5 ) !== "Until" ) {
			selector = until;
		}

		if ( selector && typeof selector === "string" ) {
			matched = jQuery.filter( selector, matched );
		}

		if ( this.length > 1 ) {

			// Remove duplicates
			if ( !guaranteedUnique[ name ] ) {
				jQuery.uniqueSort( matched );
			}

			// Reverse order for parents* and prev-derivatives
			if ( rparentsprev.test( name ) ) {
				matched.reverse();
			}
		}

		return this.pushStack( matched );
	};
} );
var rnothtmlwhite = ( /[^\x20\t\r\n\f]+/g );



// Convert String-formatted options into Object-formatted ones
function createOptions( options ) {
	var object = {};
	jQuery.each( options.match( rnothtmlwhite ) || [], function( _, flag ) {
		object[ flag ] = true;
	} );
	return object;
}

/*
 * Create a callback list using the following parameters:
 *
 *	options: an optional list of space-separated options that will change how
 *			the callback list behaves or a more traditional option object
 *
 * By default a callback list will act like an event callback list and can be
 * "fired" multiple times.
 *
 * Possible options:
 *
 *	once:			will ensure the callback list can only be fired once (like a Deferred)
 *
 *	memory:			will keep track of previous values and will call any callback added
 *					after the list has been fired right away with the latest "memorized"
 *					values (like a Deferred)
 *
 *	unique:			will ensure a callback can only be added once (no duplicate in the list)
 *
 *	stopOnFalse:	interrupt callings when a callback returns false
 *
 */
jQuery.Callbacks = function( options ) {

	// Convert options from String-formatted to Object-formatted if needed
	// (we check in cache first)
	options = typeof options === "string" ?
		createOptions( options ) :
		jQuery.extend( {}, options );

	var // Flag to know if list is currently firing
		firing,

		// Last fire value for non-forgettable lists
		memory,

		// Flag to know if list was already fired
		fired,

		// Flag to prevent firing
		locked,

		// Actual callback list
		list = [],

		// Queue of execution data for repeatable lists
		queue = [],

		// Index of currently firing callback (modified by add/remove as needed)
		firingIndex = -1,

		// Fire callbacks
		fire = function() {

			// Enforce single-firing
			locked = locked || options.once;

			// Execute callbacks for all pending executions,
			// respecting firingIndex overrides and runtime changes
			fired = firing = true;
			for ( ; queue.length; firingIndex = -1 ) {
				memory = queue.shift();
				while ( ++firingIndex < list.length ) {

					// Run callback and check for early termination
					if ( list[ firingIndex ].apply( memory[ 0 ], memory[ 1 ] ) === false &&
						options.stopOnFalse ) {

						// Jump to end and forget the data so .add doesn't re-fire
						firingIndex = list.length;
						memory = false;
					}
				}
			}

			// Forget the data if we're done with it
			if ( !options.memory ) {
				memory = false;
			}

			firing = false;

			// Clean up if we're done firing for good
			if ( locked ) {

				// Keep an empty list if we have data for future add calls
				if ( memory ) {
					list = [];

				// Otherwise, this object is spent
				} else {
					list = "";
				}
			}
		},

		// Actual Callbacks object
		self = {

			// Add a callback or a collection of callbacks to the list
			add: function() {
				if ( list ) {

					// If we have memory from a past run, we should fire after adding
					if ( memory && !firing ) {
						firingIndex = list.length - 1;
						queue.push( memory );
					}

					( function add( args ) {
						jQuery.each( args, function( _, arg ) {
							if ( isFunction( arg ) ) {
								if ( !options.unique || !self.has( arg ) ) {
									list.push( arg );
								}
							} else if ( arg && arg.length && toType( arg ) !== "string" ) {

								// Inspect recursively
								add( arg );
							}
						} );
					} )( arguments );

					if ( memory && !firing ) {
						fire();
					}
				}
				return this;
			},

			// Remove a callback from the list
			remove: function() {
				jQuery.each( arguments, function( _, arg ) {
					var index;
					while ( ( index = jQuery.inArray( arg, list, index ) ) > -1 ) {
						list.splice( index, 1 );

						// Handle firing indexes
						if ( index <= firingIndex ) {
							firingIndex--;
						}
					}
				} );
				return this;
			},

			// Check if a given callback is in the list.
			// If no argument is given, return whether or not list has callbacks attached.
			has: function( fn ) {
				return fn ?
					jQuery.inArray( fn, list ) > -1 :
					list.length > 0;
			},

			// Remove all callbacks from the list
			empty: function() {
				if ( list ) {
					list = [];
				}
				return this;
			},

			// Disable .fire and .add
			// Abort any current/pending executions
			// Clear all callbacks and values
			disable: function() {
				locked = queue = [];
				list = memory = "";
				return this;
			},
			disabled: function() {
				return !list;
			},

			// Disable .fire
			// Also disable .add unless we have memory (since it would have no effect)
			// Abort any pending executions
			lock: function() {
				locked = queue = [];
				if ( !memory && !firing ) {
					list = memory = "";
				}
				return this;
			},
			locked: function() {
				return !!locked;
			},

			// Call all callbacks with the given context and arguments
			fireWith: function( context, args ) {
				if ( !locked ) {
					args = args || [];
					args = [ context, args.slice ? args.slice() : args ];
					queue.push( args );
					if ( !firing ) {
						fire();
					}
				}
				return this;
			},

			// Call all the callbacks with the given arguments
			fire: function() {
				self.fireWith( this, arguments );
				return this;
			},

			// To know if the callbacks have already been called at least once
			fired: function() {
				return !!fired;
			}
		};

	return self;
};


function Identity( v ) {
	return v;
}
function Thrower( ex ) {
	throw ex;
}

function adoptValue( value, resolve, reject, noValue ) {
	var method;

	try {

		// Check for promise aspect first to privilege synchronous behavior
		if ( value && isFunction( ( method = value.promise ) ) ) {
			method.call( value ).done( resolve ).fail( reject );

		// Other thenables
		} else if ( value && isFunction( ( method = value.then ) ) ) {
			method.call( value, resolve, reject );

		// Other non-thenables
		} else {

			// Control `resolve` arguments by letting Array#slice cast boolean `noValue` to integer:
			// * false: [ value ].slice( 0 ) => resolve( value )
			// * true: [ value ].slice( 1 ) => resolve()
			resolve.apply( undefined, [ value ].slice( noValue ) );
		}

	// For Promises/A+, convert exceptions into rejections
	// Since jQuery.when doesn't unwrap thenables, we can skip the extra checks appearing in
	// Deferred#then to conditionally suppress rejection.
	} catch ( value ) {

		// Support: Android 4.0 only
		// Strict mode functions invoked without .call/.apply get global-object context
		reject.apply( undefined, [ value ] );
	}
}

jQuery.extend( {

	Deferred: function( func ) {
		var tuples = [

				// action, add listener, callbacks,
				// ... .then handlers, argument index, [final state]
				[ "notify", "progress", jQuery.Callbacks( "memory" ),
					jQuery.Callbacks( "memory" ), 2 ],
				[ "resolve", "done", jQuery.Callbacks( "once memory" ),
					jQuery.Callbacks( "once memory" ), 0, "resolved" ],
				[ "reject", "fail", jQuery.Callbacks( "once memory" ),
					jQuery.Callbacks( "once memory" ), 1, "rejected" ]
			],
			state = "pending",
			promise = {
				state: function() {
					return state;
				},
				always: function() {
					deferred.done( arguments ).fail( arguments );
					return this;
				},
				"catch": function( fn ) {
					return promise.then( null, fn );
				},

				// Keep pipe for back-compat
				pipe: function( /* fnDone, fnFail, fnProgress */ ) {
					var fns = arguments;

					return jQuery.Deferred( function( newDefer ) {
						jQuery.each( tuples, function( _i, tuple ) {

							// Map tuples (progress, done, fail) to arguments (done, fail, progress)
							var fn = isFunction( fns[ tuple[ 4 ] ] ) && fns[ tuple[ 4 ] ];

							// deferred.progress(function() { bind to newDefer or newDefer.notify })
							// deferred.done(function() { bind to newDefer or newDefer.resolve })
							// deferred.fail(function() { bind to newDefer or newDefer.reject })
							deferred[ tuple[ 1 ] ]( function() {
								var returned = fn && fn.apply( this, arguments );
								if ( returned && isFunction( returned.promise ) ) {
									returned.promise()
										.progress( newDefer.notify )
										.done( newDefer.resolve )
										.fail( newDefer.reject );
								} else {
									newDefer[ tuple[ 0 ] + "With" ](
										this,
										fn ? [ returned ] : arguments
									);
								}
							} );
						} );
						fns = null;
					} ).promise();
				},
				then: function( onFulfilled, onRejected, onProgress ) {
					var maxDepth = 0;
					function resolve( depth, deferred, handler, special ) {
						return function() {
							var that = this,
								args = arguments,
								mightThrow = function() {
									var returned, then;

									// Support: Promises/A+ section 2.3.3.3.3
									// https://promisesaplus.com/#point-59
									// Ignore double-resolution attempts
									if ( depth < maxDepth ) {
										return;
									}

									returned = handler.apply( that, args );

									// Support: Promises/A+ section 2.3.1
									// https://promisesaplus.com/#point-48
									if ( returned === deferred.promise() ) {
										throw new TypeError( "Thenable self-resolution" );
									}

									// Support: Promises/A+ sections 2.3.3.1, 3.5
									// https://promisesaplus.com/#point-54
									// https://promisesaplus.com/#point-75
									// Retrieve `then` only once
									then = returned &&

										// Support: Promises/A+ section 2.3.4
										// https://promisesaplus.com/#point-64
										// Only check objects and functions for thenability
										( typeof returned === "object" ||
											typeof returned === "function" ) &&
										returned.then;

									// Handle a returned thenable
									if ( isFunction( then ) ) {

										// Special processors (notify) just wait for resolution
										if ( special ) {
											then.call(
												returned,
												resolve( maxDepth, deferred, Identity, special ),
												resolve( maxDepth, deferred, Thrower, special )
											);

										// Normal processors (resolve) also hook into progress
										} else {

											// ...and disregard older resolution values
											maxDepth++;

											then.call(
												returned,
												resolve( maxDepth, deferred, Identity, special ),
												resolve( maxDepth, deferred, Thrower, special ),
												resolve( maxDepth, deferred, Identity,
													deferred.notifyWith )
											);
										}

									// Handle all other returned values
									} else {

										// Only substitute handlers pass on context
										// and multiple values (non-spec behavior)
										if ( handler !== Identity ) {
											that = undefined;
											args = [ returned ];
										}

										// Process the value(s)
										// Default process is resolve
										( special || deferred.resolveWith )( that, args );
									}
								},

								// Only normal processors (resolve) catch and reject exceptions
								process = special ?
									mightThrow :
									function() {
										try {
											mightThrow();
										} catch ( e ) {

											if ( jQuery.Deferred.exceptionHook ) {
												jQuery.Deferred.exceptionHook( e,
													process.stackTrace );
											}

											// Support: Promises/A+ section 2.3.3.3.4.1
											// https://promisesaplus.com/#point-61
											// Ignore post-resolution exceptions
											if ( depth + 1 >= maxDepth ) {

												// Only substitute handlers pass on context
												// and multiple values (non-spec behavior)
												if ( handler !== Thrower ) {
													that = undefined;
													args = [ e ];
												}

												deferred.rejectWith( that, args );
											}
										}
									};

							// Support: Promises/A+ section 2.3.3.3.1
							// https://promisesaplus.com/#point-57
							// Re-resolve promises immediately to dodge false rejection from
							// subsequent errors
							if ( depth ) {
								process();
							} else {

								// Call an optional hook to record the stack, in case of exception
								// since it's otherwise lost when execution goes async
								if ( jQuery.Deferred.getStackHook ) {
									process.stackTrace = jQuery.Deferred.getStackHook();
								}
								window.setTimeout( process );
							}
						};
					}

					return jQuery.Deferred( function( newDefer ) {

						// progress_handlers.add( ... )
						tuples[ 0 ][ 3 ].add(
							resolve(
								0,
								newDefer,
								isFunction( onProgress ) ?
									onProgress :
									Identity,
								newDefer.notifyWith
							)
						);

						// fulfilled_handlers.add( ... )
						tuples[ 1 ][ 3 ].add(
							resolve(
								0,
								newDefer,
								isFunction( onFulfilled ) ?
									onFulfilled :
									Identity
							)
						);

						// rejected_handlers.add( ... )
						tuples[ 2 ][ 3 ].add(
							resolve(
								0,
								newDefer,
								isFunction( onRejected ) ?
									onRejected :
									Thrower
							)
						);
					} ).promise();
				},

				// Get a promise for this deferred
				// If obj is provided, the promise aspect is added to the object
				promise: function( obj ) {
					return obj != null ? jQuery.extend( obj, promise ) : promise;
				}
			},
			deferred = {};

		// Add list-specific methods
		jQuery.each( tuples, function( i, tuple ) {
			var list = tuple[ 2 ],
				stateString = tuple[ 5 ];

			// promise.progress = list.add
			// promise.done = list.add
			// promise.fail = list.add
			promise[ tuple[ 1 ] ] = list.add;

			// Handle state
			if ( stateString ) {
				list.add(
					function() {

						// state = "resolved" (i.e., fulfilled)
						// state = "rejected"
						state = stateString;
					},

					// rejected_callbacks.disable
					// fulfilled_callbacks.disable
					tuples[ 3 - i ][ 2 ].disable,

					// rejected_handlers.disable
					// fulfilled_handlers.disable
					tuples[ 3 - i ][ 3 ].disable,

					// progress_callbacks.lock
					tuples[ 0 ][ 2 ].lock,

					// progress_handlers.lock
					tuples[ 0 ][ 3 ].lock
				);
			}

			// progress_handlers.fire
			// fulfilled_handlers.fire
			// rejected_handlers.fire
			list.add( tuple[ 3 ].fire );

			// deferred.notify = function() { deferred.notifyWith(...) }
			// deferred.resolve = function() { deferred.resolveWith(...) }
			// deferred.reject = function() { deferred.rejectWith(...) }
			deferred[ tuple[ 0 ] ] = function() {
				deferred[ tuple[ 0 ] + "With" ]( this === deferred ? undefined : this, arguments );
				return this;
			};

			// deferred.notifyWith = list.fireWith
			// deferred.resolveWith = list.fireWith
			// deferred.rejectWith = list.fireWith
			deferred[ tuple[ 0 ] + "With" ] = list.fireWith;
		} );

		// Make the deferred a promise
		promise.promise( deferred );

		// Call given func if any
		if ( func ) {
			func.call( deferred, deferred );
		}

		// All done!
		return deferred;
	},

	// Deferred helper
	when: function( singleValue ) {
		var

			// count of uncompleted subordinates
			remaining = arguments.length,

			// count of unprocessed arguments
			i = remaining,

			// subordinate fulfillment data
			resolveContexts = Array( i ),
			resolveValues = slice.call( arguments ),

			// the primary Deferred
			primary = jQuery.Deferred(),

			// subordinate callback factory
			updateFunc = function( i ) {
				return function( value ) {
					resolveContexts[ i ] = this;
					resolveValues[ i ] = arguments.length > 1 ? slice.call( arguments ) : value;
					if ( !( --remaining ) ) {
						primary.resolveWith( resolveContexts, resolveValues );
					}
				};
			};

		// Single- and empty arguments are adopted like Promise.resolve
		if ( remaining <= 1 ) {
			adoptValue( singleValue, primary.done( updateFunc( i ) ).resolve, primary.reject,
				!remaining );

			// Use .then() to unwrap secondary thenables (cf. gh-3000)
			if ( primary.state() === "pending" ||
				isFunction( resolveValues[ i ] && resolveValues[ i ].then ) ) {

				return primary.then();
			}
		}

		// Multiple arguments are aggregated like Promise.all array elements
		while ( i-- ) {
			adoptValue( resolveValues[ i ], updateFunc( i ), primary.reject );
		}

		return primary.promise();
	}
} );


// These usually indicate a programmer mistake during development,
// warn about them ASAP rather than swallowing them by default.
var rerrorNames = /^(Eval|Internal|Range|Reference|Syntax|Type|URI)Error$/;

jQuery.Deferred.exceptionHook = function( error, stack ) {

	// Support: IE 8 - 9 only
	// Console exists when dev tools are open, which can happen at any time
	if ( window.console && window.console.warn && error && rerrorNames.test( error.name ) ) {
		window.console.warn( "jQuery.Deferred exception: " + error.message, error.stack, stack );
	}
};




jQuery.readyException = function( error ) {
	window.setTimeout( function() {
		throw error;
	} );
};




// The deferred used on DOM ready
var readyList = jQuery.Deferred();

jQuery.fn.ready = function( fn ) {

	readyList
		.then( fn )

		// Wrap jQuery.readyException in a function so that the lookup
		// happens at the time of error handling instead of callback
		// registration.
		.catch( function( error ) {
			jQuery.readyException( error );
		} );

	return this;
};

jQuery.extend( {

	// Is the DOM ready to be used? Set to true once it occurs.
	isReady: false,

	// A counter to track how many items to wait for before
	// the ready event fires. See #6781
	readyWait: 1,

	// Handle when the DOM is ready
	ready: function( wait ) {

		// Abort if there are pending holds or we're already ready
		if ( wait === true ? --jQuery.readyWait : jQuery.isReady ) {
			return;
		}

		// Remember that the DOM is ready
		jQuery.isReady = true;

		// If a normal DOM Ready event fired, decrement, and wait if need be
		if ( wait !== true && --jQuery.readyWait > 0 ) {
			return;
		}

		// If there are functions bound, to execute
		readyList.resolveWith( document, [ jQuery ] );
	}
} );

jQuery.ready.then = readyList.then;

// The ready event handler and self cleanup method
function completed() {
	document.removeEventListener( "DOMContentLoaded", completed );
	window.removeEventListener( "load", completed );
	jQuery.ready();
}

// Catch cases where $(document).ready() is called
// after the browser event has already occurred.
// Support: IE <=9 - 10 only
// Older IE sometimes signals "interactive" too soon
if ( document.readyState === "complete" ||
	( document.readyState !== "loading" && !document.documentElement.doScroll ) ) {

	// Handle it asynchronously to allow scripts the opportunity to delay ready
	window.setTimeout( jQuery.ready );

} else {

	// Use the handy event callback
	document.addEventListener( "DOMContentLoaded", completed );

	// A fallback to window.onload, that will always work
	window.addEventListener( "load", completed );
}




// Multifunctional method to get and set values of a collection
// The value/s can optionally be executed if it's a function
var access = function( elems, fn, key, value, chainable, emptyGet, raw ) {
	var i = 0,
		len = elems.length,
		bulk = key == null;

	// Sets many values
	if ( toType( key ) === "object" ) {
		chainable = true;
		for ( i in key ) {
			access( elems, fn, i, key[ i ], true, emptyGet, raw );
		}

	// Sets one value
	} else if ( value !== undefined ) {
		chainable = true;

		if ( !isFunction( value ) ) {
			raw = true;
		}

		if ( bulk ) {

			// Bulk operations run against the entire set
			if ( raw ) {
				fn.call( elems, value );
				fn = null;

			// ...except when executing function values
			} else {
				bulk = fn;
				fn = function( elem, _key, value ) {
					return bulk.call( jQuery( elem ), value );
				};
			}
		}

		if ( fn ) {
			for ( ; i < len; i++ ) {
				fn(
					elems[ i ], key, raw ?
						value :
						value.call( elems[ i ], i, fn( elems[ i ], key ) )
				);
			}
		}
	}

	if ( chainable ) {
		return elems;
	}

	// Gets
	if ( bulk ) {
		return fn.call( elems );
	}

	return len ? fn( elems[ 0 ], key ) : emptyGet;
};


// Matches dashed string for camelizing
var rmsPrefix = /^-ms-/,
	rdashAlpha = /-([a-z])/g;

// Used by camelCase as callback to replace()
function fcamelCase( _all, letter ) {
	return letter.toUpperCase();
}

// Convert dashed to camelCase; used by the css and data modules
// Support: IE <=9 - 11, Edge 12 - 15
// Microsoft forgot to hump their vendor prefix (#9572)
function camelCase( string ) {
	return string.replace( rmsPrefix, "ms-" ).replace( rdashAlpha, fcamelCase );
}
var acceptData = function( owner ) {

	// Accepts only:
	//  - Node
	//    - Node.ELEMENT_NODE
	//    - Node.DOCUMENT_NODE
	//  - Object
	//    - Any
	return owner.nodeType === 1 || owner.nodeType === 9 || !( +owner.nodeType );
};




function Data() {
	this.expando = jQuery.expando + Data.uid++;
}

Data.uid = 1;

Data.prototype = {

	cache: function( owner ) {

		// Check if the owner object already has a cache
		var value = owner[ this.expando ];

		// If not, create one
		if ( !value ) {
			value = {};

			// We can accept data for non-element nodes in modern browsers,
			// but we should not, see #8335.
			// Always return an empty object.
			if ( acceptData( owner ) ) {

				// If it is a node unlikely to be stringify-ed or looped over
				// use plain assignment
				if ( owner.nodeType ) {
					owner[ this.expando ] = value;

				// Otherwise secure it in a non-enumerable property
				// configurable must be true to allow the property to be
				// deleted when data is removed
				} else {
					Object.defineProperty( owner, this.expando, {
						value: value,
						configurable: true
					} );
				}
			}
		}

		return value;
	},
	set: function( owner, data, value ) {
		var prop,
			cache = this.cache( owner );

		// Handle: [ owner, key, value ] args
		// Always use camelCase key (gh-2257)
		if ( typeof data === "string" ) {
			cache[ camelCase( data ) ] = value;

		// Handle: [ owner, { properties } ] args
		} else {

			// Copy the properties one-by-one to the cache object
			for ( prop in data ) {
				cache[ camelCase( prop ) ] = data[ prop ];
			}
		}
		return cache;
	},
	get: function( owner, key ) {
		return key === undefined ?
			this.cache( owner ) :

			// Always use camelCase key (gh-2257)
			owner[ this.expando ] && owner[ this.expando ][ camelCase( key ) ];
	},
	access: function( owner, key, value ) {

		// In cases where either:
		//
		//   1. No key was specified
		//   2. A string key was specified, but no value provided
		//
		// Take the "read" path and allow the get method to determine
		// which value to return, respectively either:
		//
		//   1. The entire cache object
		//   2. The data stored at the key
		//
		if ( key === undefined ||
				( ( key && typeof key === "string" ) && value === undefined ) ) {

			return this.get( owner, key );
		}

		// When the key is not a string, or both a key and value
		// are specified, set or extend (existing objects) with either:
		//
		//   1. An object of properties
		//   2. A key and value
		//
		this.set( owner, key, value );

		// Since the "set" path can have two possible entry points
		// return the expected data based on which path was taken[*]
		return value !== undefined ? value : key;
	},
	remove: function( owner, key ) {
		var i,
			cache = owner[ this.expando ];

		if ( cache === undefined ) {
			return;
		}

		if ( key !== undefined ) {

			// Support array or space separated string of keys
			if ( Array.isArray( key ) ) {

				// If key is an array of keys...
				// We always set camelCase keys, so remove that.
				key = key.map( camelCase );
			} else {
				key = camelCase( key );

				// If a key with the spaces exists, use it.
				// Otherwise, create an array by matching non-whitespace
				key = key in cache ?
					[ key ] :
					( key.match( rnothtmlwhite ) || [] );
			}

			i = key.length;

			while ( i-- ) {
				delete cache[ key[ i ] ];
			}
		}

		// Remove the expando if there's no more data
		if ( key === undefined || jQuery.isEmptyObject( cache ) ) {

			// Support: Chrome <=35 - 45
			// Webkit & Blink performance suffers when deleting properties
			// from DOM nodes, so set to undefined instead
			// https://bugs.chromium.org/p/chromium/issues/detail?id=378607 (bug restricted)
			if ( owner.nodeType ) {
				owner[ this.expando ] = undefined;
			} else {
				delete owner[ this.expando ];
			}
		}
	},
	hasData: function( owner ) {
		var cache = owner[ this.expando ];
		return cache !== undefined && !jQuery.isEmptyObject( cache );
	}
};
var dataPriv = new Data();

var dataUser = new Data();



//	Implementation Summary
//
//	1. Enforce API surface and semantic compatibility with 1.9.x branch
//	2. Improve the module's maintainability by reducing the storage
//		paths to a single mechanism.
//	3. Use the same single mechanism to support "private" and "user" data.
//	4. _Never_ expose "private" data to user code (TODO: Drop _data, _removeData)
//	5. Avoid exposing implementation details on user objects (eg. expando properties)
//	6. Provide a clear path for implementation upgrade to WeakMap in 2014

var rbrace = /^(?:\{[\w\W]*\}|\[[\w\W]*\])$/,
	rmultiDash = /[A-Z]/g;

function getData( data ) {
	if ( data === "true" ) {
		return true;
	}

	if ( data === "false" ) {
		return false;
	}

	if ( data === "null" ) {
		return null;
	}

	// Only convert to a number if it doesn't change the string
	if ( data === +data + "" ) {
		return +data;
	}

	if ( rbrace.test( data ) ) {
		return JSON.parse( data );
	}

	return data;
}

function dataAttr( elem, key, data ) {
	var name;

	// If nothing was found internally, try to fetch any
	// data from the HTML5 data-* attribute
	if ( data === undefined && elem.nodeType === 1 ) {
		name = "data-" + key.replace( rmultiDash, "-$&" ).toLowerCase();
		data = elem.getAttribute( name );

		if ( typeof data === "string" ) {
			try {
				data = getData( data );
			} catch ( e ) {}

			// Make sure we set the data so it isn't changed later
			dataUser.set( elem, key, data );
		} else {
			data = undefined;
		}
	}
	return data;
}

jQuery.extend( {
	hasData: function( elem ) {
		return dataUser.hasData( elem ) || dataPriv.hasData( elem );
	},

	data: function( elem, name, data ) {
		return dataUser.access( elem, name, data );
	},

	removeData: function( elem, name ) {
		dataUser.remove( elem, name );
	},

	// TODO: Now that all calls to _data and _removeData have been replaced
	// with direct calls to dataPriv methods, these can be deprecated.
	_data: function( elem, name, data ) {
		return dataPriv.access( elem, name, data );
	},

	_removeData: function( elem, name ) {
		dataPriv.remove( elem, name );
	}
} );

jQuery.fn.extend( {
	data: function( key, value ) {
		var i, name, data,
			elem = this[ 0 ],
			attrs = elem && elem.attributes;

		// Gets all values
		if ( key === undefined ) {
			if ( this.length ) {
				data = dataUser.get( elem );

				if ( elem.nodeType === 1 && !dataPriv.get( elem, "hasDataAttrs" ) ) {
					i = attrs.length;
					while ( i-- ) {

						// Support: IE 11 only
						// The attrs elements can be null (#14894)
						if ( attrs[ i ] ) {
							name = attrs[ i ].name;
							if ( name.indexOf( "data-" ) === 0 ) {
								name = camelCase( name.slice( 5 ) );
								dataAttr( elem, name, data[ name ] );
							}
						}
					}
					dataPriv.set( elem, "hasDataAttrs", true );
				}
			}

			return data;
		}

		// Sets multiple values
		if ( typeof key === "object" ) {
			return this.each( function() {
				dataUser.set( this, key );
			} );
		}

		return access( this, function( value ) {
			var data;

			// The calling jQuery object (element matches) is not empty
			// (and therefore has an element appears at this[ 0 ]) and the
			// `value` parameter was not undefined. An empty jQuery object
			// will result in `undefined` for elem = this[ 0 ] which will
			// throw an exception if an attempt to read a data cache is made.
			if ( elem && value === undefined ) {

				// Attempt to get data from the cache
				// The key will always be camelCased in Data
				data = dataUser.get( elem, key );
				if ( data !== undefined ) {
					return data;
				}

				// Attempt to "discover" the data in
				// HTML5 custom data-* attrs
				data = dataAttr( elem, key );
				if ( data !== undefined ) {
					return data;
				}

				// We tried really hard, but the data doesn't exist.
				return;
			}

			// Set the data...
			this.each( function() {

				// We always store the camelCased key
				dataUser.set( this, key, value );
			} );
		}, null, value, arguments.length > 1, null, true );
	},

	removeData: function( key ) {
		return this.each( function() {
			dataUser.remove( this, key );
		} );
	}
} );


jQuery.extend( {
	queue: function( elem, type, data ) {
		var queue;

		if ( elem ) {
			type = ( type || "fx" ) + "queue";
			queue = dataPriv.get( elem, type );

			// Speed up dequeue by getting out quickly if this is just a lookup
			if ( data ) {
				if ( !queue || Array.isArray( data ) ) {
					queue = dataPriv.access( elem, type, jQuery.makeArray( data ) );
				} else {
					queue.push( data );
				}
			}
			return queue || [];
		}
	},

	dequeue: function( elem, type ) {
		type = type || "fx";

		var queue = jQuery.queue( elem, type ),
			startLength = queue.length,
			fn = queue.shift(),
			hooks = jQuery._queueHooks( elem, type ),
			next = function() {
				jQuery.dequeue( elem, type );
			};

		// If the fx queue is dequeued, always remove the progress sentinel
		if ( fn === "inprogress" ) {
			fn = queue.shift();
			startLength--;
		}

		if ( fn ) {

			// Add a progress sentinel to prevent the fx queue from being
			// automatically dequeued
			if ( type === "fx" ) {
				queue.unshift( "inprogress" );
			}

			// Clear up the last queue stop function
			delete hooks.stop;
			fn.call( elem, next, hooks );
		}

		if ( !startLength && hooks ) {
			hooks.empty.fire();
		}
	},

	// Not public - generate a queueHooks object, or return the current one
	_queueHooks: function( elem, type ) {
		var key = type + "queueHooks";
		return dataPriv.get( elem, key ) || dataPriv.access( elem, key, {
			empty: jQuery.Callbacks( "once memory" ).add( function() {
				dataPriv.remove( elem, [ type + "queue", key ] );
			} )
		} );
	}
} );

jQuery.fn.extend( {
	queue: function( type, data ) {
		var setter = 2;

		if ( typeof type !== "string" ) {
			data = type;
			type = "fx";
			setter--;
		}

		if ( arguments.length < setter ) {
			return jQuery.queue( this[ 0 ], type );
		}

		return data === undefined ?
			this :
			this.each( function() {
				var queue = jQuery.queue( this, type, data );

				// Ensure a hooks for this queue
				jQuery._queueHooks( this, type );

				if ( type === "fx" && queue[ 0 ] !== "inprogress" ) {
					jQuery.dequeue( this, type );
				}
			} );
	},
	dequeue: function( type ) {
		return this.each( function() {
			jQuery.dequeue( this, type );
		} );
	},
	clearQueue: function( type ) {
		return this.queue( type || "fx", [] );
	},

	// Get a promise resolved when queues of a certain type
	// are emptied (fx is the type by default)
	promise: function( type, obj ) {
		var tmp,
			count = 1,
			defer = jQuery.Deferred(),
			elements = this,
			i = this.length,
			resolve = function() {
				if ( !( --count ) ) {
					defer.resolveWith( elements, [ elements ] );
				}
			};

		if ( typeof type !== "string" ) {
			obj = type;
			type = undefined;
		}
		type = type || "fx";

		while ( i-- ) {
			tmp = dataPriv.get( elements[ i ], type + "queueHooks" );
			if ( tmp && tmp.empty ) {
				count++;
				tmp.empty.add( resolve );
			}
		}
		resolve();
		return defer.promise( obj );
	}
} );
var pnum = ( /[+-]?(?:\d*\.|)\d+(?:[eE][+-]?\d+|)/ ).source;

var rcssNum = new RegExp( "^(?:([+-])=|)(" + pnum + ")([a-z%]*)$", "i" );


var cssExpand = [ "Top", "Right", "Bottom", "Left" ];

var documentElement = document.documentElement;



	var isAttached = function( elem ) {
			return jQuery.contains( elem.ownerDocument, elem );
		},
		composed = { composed: true };

	// Support: IE 9 - 11+, Edge 12 - 18+, iOS 10.0 - 10.2 only
	// Check attachment across shadow DOM boundaries when possible (gh-3504)
	// Support: iOS 10.0-10.2 only
	// Early iOS 10 versions support `attachShadow` but not `getRootNode`,
	// leading to errors. We need to check for `getRootNode`.
	if ( documentElement.getRootNode ) {
		isAttached = function( elem ) {
			return jQuery.contains( elem.ownerDocument, elem ) ||
				elem.getRootNode( composed ) === elem.ownerDocument;
		};
	}
var isHiddenWithinTree = function( elem, el ) {

		// isHiddenWithinTree might be called from jQuery#filter function;
		// in that case, element will be second argument
		elem = el || elem;

		// Inline style trumps all
		return elem.style.display === "none" ||
			elem.style.display === "" &&

			// Otherwise, check computed style
			// Support: Firefox <=43 - 45
			// Disconnected elements can have computed display: none, so first confirm that elem is
			// in the document.
			isAttached( elem ) &&

			jQuery.css( elem, "display" ) === "none";
	};



function adjustCSS( elem, prop, valueParts, tween ) {
	var adjusted, scale,
		maxIterations = 20,
		currentValue = tween ?
			function() {
				return tween.cur();
			} :
			function() {
				return jQuery.css( elem, prop, "" );
			},
		initial = currentValue(),
		unit = valueParts && valueParts[ 3 ] || ( jQuery.cssNumber[ prop ] ? "" : "px" ),

		// Starting value computation is required for potential unit mismatches
		initialInUnit = elem.nodeType &&
			( jQuery.cssNumber[ prop ] || unit !== "px" && +initial ) &&
			rcssNum.exec( jQuery.css( elem, prop ) );

	if ( initialInUnit && initialInUnit[ 3 ] !== unit ) {

		// Support: Firefox <=54
		// Halve the iteration target value to prevent interference from CSS upper bounds (gh-2144)
		initial = initial / 2;

		// Trust units reported by jQuery.css
		unit = unit || initialInUnit[ 3 ];

		// Iteratively approximate from a nonzero starting point
		initialInUnit = +initial || 1;

		while ( maxIterations-- ) {

			// Evaluate and update our best guess (doubling guesses that zero out).
			// Finish if the scale equals or crosses 1 (making the old*new product non-positive).
			jQuery.style( elem, prop, initialInUnit + unit );
			if ( ( 1 - scale ) * ( 1 - ( scale = currentValue() / initial || 0.5 ) ) <= 0 ) {
				maxIterations = 0;
			}
			initialInUnit = initialInUnit / scale;

		}

		initialInUnit = initialInUnit * 2;
		jQuery.style( elem, prop, initialInUnit + unit );

		// Make sure we update the tween properties later on
		valueParts = valueParts || [];
	}

	if ( valueParts ) {
		initialInUnit = +initialInUnit || +initial || 0;

		// Apply relative offset (+=/-=) if specified
		adjusted = valueParts[ 1 ] ?
			initialInUnit + ( valueParts[ 1 ] + 1 ) * valueParts[ 2 ] :
			+valueParts[ 2 ];
		if ( tween ) {
			tween.unit = unit;
			tween.start = initialInUnit;
			tween.end = adjusted;
		}
	}
	return adjusted;
}


var defaultDisplayMap = {};

function getDefaultDisplay( elem ) {
	var temp,
		doc = elem.ownerDocument,
		nodeName = elem.nodeName,
		display = defaultDisplayMap[ nodeName ];

	if ( display ) {
		return display;
	}

	temp = doc.body.appendChild( doc.createElement( nodeName ) );
	display = jQuery.css( temp, "display" );

	temp.parentNode.removeChild( temp );

	if ( display === "none" ) {
		display = "block";
	}
	defaultDisplayMap[ nodeName ] = display;

	return display;
}

function showHide( elements, show ) {
	var display, elem,
		values = [],
		index = 0,
		length = elements.length;

	// Determine new display value for elements that need to change
	for ( ; index < length; index++ ) {
		elem = elements[ index ];
		if ( !elem.style ) {
			continue;
		}

		display = elem.style.display;
		if ( show ) {

			// Since we force visibility upon cascade-hidden elements, an immediate (and slow)
			// check is required in this first loop unless we have a nonempty display value (either
			// inline or about-to-be-restored)
			if ( display === "none" ) {
				values[ index ] = dataPriv.get( elem, "display" ) || null;
				if ( !values[ index ] ) {
					elem.style.display = "";
				}
			}
			if ( elem.style.display === "" && isHiddenWithinTree( elem ) ) {
				values[ index ] = getDefaultDisplay( elem );
			}
		} else {
			if ( display !== "none" ) {
				values[ index ] = "none";

				// Remember what we're overwriting
				dataPriv.set( elem, "display", display );
			}
		}
	}

	// Set the display of the elements in a second loop to avoid constant reflow
	for ( index = 0; index < length; index++ ) {
		if ( values[ index ] != null ) {
			elements[ index ].style.display = values[ index ];
		}
	}

	return elements;
}

jQuery.fn.extend( {
	show: function() {
		return showHide( this, true );
	},
	hide: function() {
		return showHide( this );
	},
	toggle: function( state ) {
		if ( typeof state === "boolean" ) {
			return state ? this.show() : this.hide();
		}

		return this.each( function() {
			if ( isHiddenWithinTree( this ) ) {
				jQuery( this ).show();
			} else {
				jQuery( this ).hide();
			}
		} );
	}
} );
var rcheckableType = ( /^(?:checkbox|radio)$/i );

var rtagName = ( /<([a-z][^\/\0>\x20\t\r\n\f]*)/i );

var rscriptType = ( /^$|^module$|\/(?:java|ecma)script/i );



( function() {
	var fragment = document.createDocumentFragment(),
		div = fragment.appendChild( document.createElement( "div" ) ),
		input = document.createElement( "input" );

	// Support: Android 4.0 - 4.3 only
	// Check state lost if the name is set (#11217)
	// Support: Windows Web Apps (WWA)
	// `name` and `type` must use .setAttribute for WWA (#14901)
	input.setAttribute( "type", "radio" );
	input.setAttribute( "checked", "checked" );
	input.setAttribute( "name", "t" );

	div.appendChild( input );

	// Support: Android <=4.1 only
	// Older WebKit doesn't clone checked state correctly in fragments
	support.checkClone = div.cloneNode( true ).cloneNode( true ).lastChild.checked;

	// Support: IE <=11 only
	// Make sure textarea (and checkbox) defaultValue is properly cloned
	div.innerHTML = "<textarea>x</textarea>";
	support.noCloneChecked = !!div.cloneNode( true ).lastChild.defaultValue;

	// Support: IE <=9 only
	// IE <=9 replaces <option> tags with their contents when inserted outside of
	// the select element.
	div.innerHTML = "<option></option>";
	support.option = !!div.lastChild;
} )();


// We have to close these tags to support XHTML (#13200)
var wrapMap = {

	// XHTML parsers do not magically insert elements in the
	// same way that tag soup parsers do. So we cannot shorten
	// this by omitting <tbody> or other required elements.
	thead: [ 1, "<table>", "</table>" ],
	col: [ 2, "<table><colgroup>", "</colgroup></table>" ],
	tr: [ 2, "<table><tbody>", "</tbody></table>" ],
	td: [ 3, "<table><tbody><tr>", "</tr></tbody></table>" ],

	_default: [ 0, "", "" ]
};

wrapMap.tbody = wrapMap.tfoot = wrapMap.colgroup = wrapMap.caption = wrapMap.thead;
wrapMap.th = wrapMap.td;

// Support: IE <=9 only
if ( !support.option ) {
	wrapMap.optgroup = wrapMap.option = [ 1, "<select multiple='multiple'>", "</select>" ];
}


function getAll( context, tag ) {

	// Support: IE <=9 - 11 only
	// Use typeof to avoid zero-argument method invocation on host objects (#15151)
	var ret;

	if ( typeof context.getElementsByTagName !== "undefined" ) {
		ret = context.getElementsByTagName( tag || "*" );

	} else if ( typeof context.querySelectorAll !== "undefined" ) {
		ret = context.querySelectorAll( tag || "*" );

	} else {
		ret = [];
	}

	if ( tag === undefined || tag && nodeName( context, tag ) ) {
		return jQuery.merge( [ context ], ret );
	}

	return ret;
}


// Mark scripts as having already been evaluated
function setGlobalEval( elems, refElements ) {
	var i = 0,
		l = elems.length;

	for ( ; i < l; i++ ) {
		dataPriv.set(
			elems[ i ],
			"globalEval",
			!refElements || dataPriv.get( refElements[ i ], "globalEval" )
		);
	}
}


var rhtml = /<|&#?\w+;/;

function buildFragment( elems, context, scripts, selection, ignored ) {
	var elem, tmp, tag, wrap, attached, j,
		fragment = context.createDocumentFragment(),
		nodes = [],
		i = 0,
		l = elems.length;

	for ( ; i < l; i++ ) {
		elem = elems[ i ];

		if ( elem || elem === 0 ) {

			// Add nodes directly
			if ( toType( elem ) === "object" ) {

				// Support: Android <=4.0 only, PhantomJS 1 only
				// push.apply(_, arraylike) throws on ancient WebKit
				jQuery.merge( nodes, elem.nodeType ? [ elem ] : elem );

			// Convert non-html into a text node
			} else if ( !rhtml.test( elem ) ) {
				nodes.push( context.createTextNode( elem ) );

			// Convert html into DOM nodes
			} else {
				tmp = tmp || fragment.appendChild( context.createElement( "div" ) );

				// Deserialize a standard representation
				tag = ( rtagName.exec( elem ) || [ "", "" ] )[ 1 ].toLowerCase();
				wrap = wrapMap[ tag ] || wrapMap._default;
				tmp.innerHTML = wrap[ 1 ] + jQuery.htmlPrefilter( elem ) + wrap[ 2 ];

				// Descend through wrappers to the right content
				j = wrap[ 0 ];
				while ( j-- ) {
					tmp = tmp.lastChild;
				}

				// Support: Android <=4.0 only, PhantomJS 1 only
				// push.apply(_, arraylike) throws on ancient WebKit
				jQuery.merge( nodes, tmp.childNodes );

				// Remember the top-level container
				tmp = fragment.firstChild;

				// Ensure the created nodes are orphaned (#12392)
				tmp.textContent = "";
			}
		}
	}

	// Remove wrapper from fragment
	fragment.textContent = "";

	i = 0;
	while ( ( elem = nodes[ i++ ] ) ) {

		// Skip elements already in the context collection (trac-4087)
		if ( selection && jQuery.inArray( elem, selection ) > -1 ) {
			if ( ignored ) {
				ignored.push( elem );
			}
			continue;
		}

		attached = isAttached( elem );

		// Append to fragment
		tmp = getAll( fragment.appendChild( elem ), "script" );

		// Preserve script evaluation history
		if ( attached ) {
			setGlobalEval( tmp );
		}

		// Capture executables
		if ( scripts ) {
			j = 0;
			while ( ( elem = tmp[ j++ ] ) ) {
				if ( rscriptType.test( elem.type || "" ) ) {
					scripts.push( elem );
				}
			}
		}
	}

	return fragment;
}


var rtypenamespace = /^([^.]*)(?:\.(.+)|)/;

function returnTrue() {
	return true;
}

function returnFalse() {
	return false;
}

// Support: IE <=9 - 11+
// focus() and blur() are asynchronous, except when they are no-op.
// So expect focus to be synchronous when the element is already active,
// and blur to be synchronous when the element is not already active.
// (focus and blur are always synchronous in other supported browsers,
// this just defines when we can count on it).
function expectSync( elem, type ) {
	return ( elem === safeActiveElement() ) === ( type === "focus" );
}

// Support: IE <=9 only
// Accessing document.activeElement can throw unexpectedly
// https://bugs.jquery.com/ticket/13393
function safeActiveElement() {
	try {
		return document.activeElement;
	} catch ( err ) { }
}

function on( elem, types, selector, data, fn, one ) {
	var origFn, type;

	// Types can be a map of types/handlers
	if ( typeof types === "object" ) {

		// ( types-Object, selector, data )
		if ( typeof selector !== "string" ) {

			// ( types-Object, data )
			data = data || selector;
			selector = undefined;
		}
		for ( type in types ) {
			on( elem, type, selector, data, types[ type ], one );
		}
		return elem;
	}

	if ( data == null && fn == null ) {

		// ( types, fn )
		fn = selector;
		data = selector = undefined;
	} else if ( fn == null ) {
		if ( typeof selector === "string" ) {

			// ( types, selector, fn )
			fn = data;
			data = undefined;
		} else {

			// ( types, data, fn )
			fn = data;
			data = selector;
			selector = undefined;
		}
	}
	if ( fn === false ) {
		fn = returnFalse;
	} else if ( !fn ) {
		return elem;
	}

	if ( one === 1 ) {
		origFn = fn;
		fn = function( event ) {

			// Can use an empty set, since event contains the info
			jQuery().off( event );
			return origFn.apply( this, arguments );
		};

		// Use same guid so caller can remove using origFn
		fn.guid = origFn.guid || ( origFn.guid = jQuery.guid++ );
	}
	return elem.each( function() {
		jQuery.event.add( this, types, fn, data, selector );
	} );
}

/*
 * Helper functions for managing events -- not part of the public interface.
 * Props to Dean Edwards' addEvent library for many of the ideas.
 */
jQuery.event = {

	global: {},

	add: function( elem, types, handler, data, selector ) {

		var handleObjIn, eventHandle, tmp,
			events, t, handleObj,
			special, handlers, type, namespaces, origType,
			elemData = dataPriv.get( elem );

		// Only attach events to objects that accept data
		if ( !acceptData( elem ) ) {
			return;
		}

		// Caller can pass in an object of custom data in lieu of the handler
		if ( handler.handler ) {
			handleObjIn = handler;
			handler = handleObjIn.handler;
			selector = handleObjIn.selector;
		}

		// Ensure that invalid selectors throw exceptions at attach time
		// Evaluate against documentElement in case elem is a non-element node (e.g., document)
		if ( selector ) {
			jQuery.find.matchesSelector( documentElement, selector );
		}

		// Make sure that the handler has a unique ID, used to find/remove it later
		if ( !handler.guid ) {
			handler.guid = jQuery.guid++;
		}

		// Init the element's event structure and main handler, if this is the first
		if ( !( events = elemData.events ) ) {
			events = elemData.events = Object.create( null );
		}
		if ( !( eventHandle = elemData.handle ) ) {
			eventHandle = elemData.handle = function( e ) {

				// Discard the second event of a jQuery.event.trigger() and
				// when an event is called after a page has unloaded
				return typeof jQuery !== "undefined" && jQuery.event.triggered !== e.type ?
					jQuery.event.dispatch.apply( elem, arguments ) : undefined;
			};
		}

		// Handle multiple events separated by a space
		types = ( types || "" ).match( rnothtmlwhite ) || [ "" ];
		t = types.length;
		while ( t-- ) {
			tmp = rtypenamespace.exec( types[ t ] ) || [];
			type = origType = tmp[ 1 ];
			namespaces = ( tmp[ 2 ] || "" ).split( "." ).sort();

			// There *must* be a type, no attaching namespace-only handlers
			if ( !type ) {
				continue;
			}

			// If event changes its type, use the special event handlers for the changed type
			special = jQuery.event.special[ type ] || {};

			// If selector defined, determine special event api type, otherwise given type
			type = ( selector ? special.delegateType : special.bindType ) || type;

			// Update special based on newly reset type
			special = jQuery.event.special[ type ] || {};

			// handleObj is passed to all event handlers
			handleObj = jQuery.extend( {
				type: type,
				origType: origType,
				data: data,
				handler: handler,
				guid: handler.guid,
				selector: selector,
				needsContext: selector && jQuery.expr.match.needsContext.test( selector ),
				namespace: namespaces.join( "." )
			}, handleObjIn );

			// Init the event handler queue if we're the first
			if ( !( handlers = events[ type ] ) ) {
				handlers = events[ type ] = [];
				handlers.delegateCount = 0;

				// Only use addEventListener if the special events handler returns false
				if ( !special.setup ||
					special.setup.call( elem, data, namespaces, eventHandle ) === false ) {

					if ( elem.addEventListener ) {
						elem.addEventListener( type, eventHandle );
					}
				}
			}

			if ( special.add ) {
				special.add.call( elem, handleObj );

				if ( !handleObj.handler.guid ) {
					handleObj.handler.guid = handler.guid;
				}
			}

			// Add to the element's handler list, delegates in front
			if ( selector ) {
				handlers.splice( handlers.delegateCount++, 0, handleObj );
			} else {
				handlers.push( handleObj );
			}

			// Keep track of which events have ever been used, for event optimization
			jQuery.event.global[ type ] = true;
		}

	},

	// Detach an event or set of events from an element
	remove: function( elem, types, handler, selector, mappedTypes ) {

		var j, origCount, tmp,
			events, t, handleObj,
			special, handlers, type, namespaces, origType,
			elemData = dataPriv.hasData( elem ) && dataPriv.get( elem );

		if ( !elemData || !( events = elemData.events ) ) {
			return;
		}

		// Once for each type.namespace in types; type may be omitted
		types = ( types || "" ).match( rnothtmlwhite ) || [ "" ];
		t = types.length;
		while ( t-- ) {
			tmp = rtypenamespace.exec( types[ t ] ) || [];
			type = origType = tmp[ 1 ];
			namespaces = ( tmp[ 2 ] || "" ).split( "." ).sort();

			// Unbind all events (on this namespace, if provided) for the element
			if ( !type ) {
				for ( type in events ) {
					jQuery.event.remove( elem, type + types[ t ], handler, selector, true );
				}
				continue;
			}

			special = jQuery.event.special[ type ] || {};
			type = ( selector ? special.delegateType : special.bindType ) || type;
			handlers = events[ type ] || [];
			tmp = tmp[ 2 ] &&
				new RegExp( "(^|\\.)" + namespaces.join( "\\.(?:.*\\.|)" ) + "(\\.|$)" );

			// Remove matching events
			origCount = j = handlers.length;
			while ( j-- ) {
				handleObj = handlers[ j ];

				if ( ( mappedTypes || origType === handleObj.origType ) &&
					( !handler || handler.guid === handleObj.guid ) &&
					( !tmp || tmp.test( handleObj.namespace ) ) &&
					( !selector || selector === handleObj.selector ||
						selector === "**" && handleObj.selector ) ) {
					handlers.splice( j, 1 );

					if ( handleObj.selector ) {
						handlers.delegateCount--;
					}
					if ( special.remove ) {
						special.remove.call( elem, handleObj );
					}
				}
			}

			// Remove generic event handler if we removed something and no more handlers exist
			// (avoids potential for endless recursion during removal of special event handlers)
			if ( origCount && !handlers.length ) {
				if ( !special.teardown ||
					special.teardown.call( elem, namespaces, elemData.handle ) === false ) {

					jQuery.removeEvent( elem, type, elemData.handle );
				}

				delete events[ type ];
			}
		}

		// Remove data and the expando if it's no longer used
		if ( jQuery.isEmptyObject( events ) ) {
			dataPriv.remove( elem, "handle events" );
		}
	},

	dispatch: function( nativeEvent ) {

		var i, j, ret, matched, handleObj, handlerQueue,
			args = new Array( arguments.length ),

			// Make a writable jQuery.Event from the native event object
			event = jQuery.event.fix( nativeEvent ),

			handlers = (
				dataPriv.get( this, "events" ) || Object.create( null )
			)[ event.type ] || [],
			special = jQuery.event.special[ event.type ] || {};

		// Use the fix-ed jQuery.Event rather than the (read-only) native event
		args[ 0 ] = event;

		for ( i = 1; i < arguments.length; i++ ) {
			args[ i ] = arguments[ i ];
		}

		event.delegateTarget = this;

		// Call the preDispatch hook for the mapped type, and let it bail if desired
		if ( special.preDispatch && special.preDispatch.call( this, event ) === false ) {
			return;
		}

		// Determine handlers
		handlerQueue = jQuery.event.handlers.call( this, event, handlers );

		// Run delegates first; they may want to stop propagation beneath us
		i = 0;
		while ( ( matched = handlerQueue[ i++ ] ) && !event.isPropagationStopped() ) {
			event.currentTarget = matched.elem;

			j = 0;
			while ( ( handleObj = matched.handlers[ j++ ] ) &&
				!event.isImmediatePropagationStopped() ) {

				// If the event is namespaced, then each handler is only invoked if it is
				// specially universal or its namespaces are a superset of the event's.
				if ( !event.rnamespace || handleObj.namespace === false ||
					event.rnamespace.test( handleObj.namespace ) ) {

					event.handleObj = handleObj;
					event.data = handleObj.data;

					ret = ( ( jQuery.event.special[ handleObj.origType ] || {} ).handle ||
						handleObj.handler ).apply( matched.elem, args );

					if ( ret !== undefined ) {
						if ( ( event.result = ret ) === false ) {
							event.preventDefault();
							event.stopPropagation();
						}
					}
				}
			}
		}

		// Call the postDispatch hook for the mapped type
		if ( special.postDispatch ) {
			special.postDispatch.call( this, event );
		}

		return event.result;
	},

	handlers: function( event, handlers ) {
		var i, handleObj, sel, matchedHandlers, matchedSelectors,
			handlerQueue = [],
			delegateCount = handlers.delegateCount,
			cur = event.target;

		// Find delegate handlers
		if ( delegateCount &&

			// Support: IE <=9
			// Black-hole SVG <use> instance trees (trac-13180)
			cur.nodeType &&

			// Support: Firefox <=42
			// Suppress spec-violating clicks indicating a non-primary pointer button (trac-3861)
			// https://www.w3.org/TR/DOM-Level-3-Events/#event-type-click
			// Support: IE 11 only
			// ...but not arrow key "clicks" of radio inputs, which can have `button` -1 (gh-2343)
			!( event.type === "click" && event.button >= 1 ) ) {

			for ( ; cur !== this; cur = cur.parentNode || this ) {

				// Don't check non-elements (#13208)
				// Don't process clicks on disabled elements (#6911, #8165, #11382, #11764)
				if ( cur.nodeType === 1 && !( event.type === "click" && cur.disabled === true ) ) {
					matchedHandlers = [];
					matchedSelectors = {};
					for ( i = 0; i < delegateCount; i++ ) {
						handleObj = handlers[ i ];

						// Don't conflict with Object.prototype properties (#13203)
						sel = handleObj.selector + " ";

						if ( matchedSelectors[ sel ] === undefined ) {
							matchedSelectors[ sel ] = handleObj.needsContext ?
								jQuery( sel, this ).index( cur ) > -1 :
								jQuery.find( sel, this, null, [ cur ] ).length;
						}
						if ( matchedSelectors[ sel ] ) {
							matchedHandlers.push( handleObj );
						}
					}
					if ( matchedHandlers.length ) {
						handlerQueue.push( { elem: cur, handlers: matchedHandlers } );
					}
				}
			}
		}

		// Add the remaining (directly-bound) handlers
		cur = this;
		if ( delegateCount < handlers.length ) {
			handlerQueue.push( { elem: cur, handlers: handlers.slice( delegateCount ) } );
		}

		return handlerQueue;
	},

	addProp: function( name, hook ) {
		Object.defineProperty( jQuery.Event.prototype, name, {
			enumerable: true,
			configurable: true,

			get: isFunction( hook ) ?
				function() {
					if ( this.originalEvent ) {
						return hook( this.originalEvent );
					}
				} :
				function() {
					if ( this.originalEvent ) {
						return this.originalEvent[ name ];
					}
				},

			set: function( value ) {
				Object.defineProperty( this, name, {
					enumerable: true,
					configurable: true,
					writable: true,
					value: value
				} );
			}
		} );
	},

	fix: function( originalEvent ) {
		return originalEvent[ jQuery.expando ] ?
			originalEvent :
			new jQuery.Event( originalEvent );
	},

	special: {
		load: {

			// Prevent triggered image.load events from bubbling to window.load
			noBubble: true
		},
		click: {

			// Utilize native event to ensure correct state for checkable inputs
			setup: function( data ) {

				// For mutual compressibility with _default, replace `this` access with a local var.
				// `|| data` is dead code meant only to preserve the variable through minification.
				var el = this || data;

				// Claim the first handler
				if ( rcheckableType.test( el.type ) &&
					el.click && nodeName( el, "input" ) ) {

					// dataPriv.set( el, "click", ... )
					leverageNative( el, "click", returnTrue );
				}

				// Return false to allow normal processing in the caller
				return false;
			},
			trigger: function( data ) {

				// For mutual compressibility with _default, replace `this` access with a local var.
				// `|| data` is dead code meant only to preserve the variable through minification.
				var el = this || data;

				// Force setup before triggering a click
				if ( rcheckableType.test( el.type ) &&
					el.click && nodeName( el, "input" ) ) {

					leverageNative( el, "click" );
				}

				// Return non-false to allow normal event-path propagation
				return true;
			},

			// For cross-browser consistency, suppress native .click() on links
			// Also prevent it if we're currently inside a leveraged native-event stack
			_default: function( event ) {
				var target = event.target;
				return rcheckableType.test( target.type ) &&
					target.click && nodeName( target, "input" ) &&
					dataPriv.get( target, "click" ) ||
					nodeName( target, "a" );
			}
		},

		beforeunload: {
			postDispatch: function( event ) {

				// Support: Firefox 20+
				// Firefox doesn't alert if the returnValue field is not set.
				if ( event.result !== undefined && event.originalEvent ) {
					event.originalEvent.returnValue = event.result;
				}
			}
		}
	}
};

// Ensure the presence of an event listener that handles manually-triggered
// synthetic events by interrupting progress until reinvoked in response to
// *native* events that it fires directly, ensuring that state changes have
// already occurred before other listeners are invoked.
function leverageNative( el, type, expectSync ) {

	// Missing expectSync indicates a trigger call, which must force setup through jQuery.event.add
	if ( !expectSync ) {
		if ( dataPriv.get( el, type ) === undefined ) {
			jQuery.event.add( el, type, returnTrue );
		}
		return;
	}

	// Register the controller as a special universal handler for all event namespaces
	dataPriv.set( el, type, false );
	jQuery.event.add( el, type, {
		namespace: false,
		handler: function( event ) {
			var notAsync, result,
				saved = dataPriv.get( this, type );

			if ( ( event.isTrigger & 1 ) && this[ type ] ) {

				// Interrupt processing of the outer synthetic .trigger()ed event
				// Saved data should be false in such cases, but might be a leftover capture object
				// from an async native handler (gh-4350)
				if ( !saved.length ) {

					// Store arguments for use when handling the inner native event
					// There will always be at least one argument (an event object), so this array
					// will not be confused with a leftover capture object.
					saved = slice.call( arguments );
					dataPriv.set( this, type, saved );

					// Trigger the native event and capture its result
					// Support: IE <=9 - 11+
					// focus() and blur() are asynchronous
					notAsync = expectSync( this, type );
					this[ type ]();
					result = dataPriv.get( this, type );
					if ( saved !== result || notAsync ) {
						dataPriv.set( this, type, false );
					} else {
						result = {};
					}
					if ( saved !== result ) {

						// Cancel the outer synthetic event
						event.stopImmediatePropagation();
						event.preventDefault();

						// Support: Chrome 86+
						// In Chrome, if an element having a focusout handler is blurred by
						// clicking outside of it, it invokes the handler synchronously. If
						// that handler calls `.remove()` on the element, the data is cleared,
						// leaving `result` undefined. We need to guard against this.
						return result && result.value;
					}

				// If this is an inner synthetic event for an event with a bubbling surrogate
				// (focus or blur), assume that the surrogate already propagated from triggering the
				// native event and prevent that from happening again here.
				// This technically gets the ordering wrong w.r.t. to `.trigger()` (in which the
				// bubbling surrogate propagates *after* the non-bubbling base), but that seems
				// less bad than duplication.
				} else if ( ( jQuery.event.special[ type ] || {} ).delegateType ) {
					event.stopPropagation();
				}

			// If this is a native event triggered above, everything is now in order
			// Fire an inner synthetic event with the original arguments
			} else if ( saved.length ) {

				// ...and capture the result
				dataPriv.set( this, type, {
					value: jQuery.event.trigger(

						// Support: IE <=9 - 11+
						// Extend with the prototype to reset the above stopImmediatePropagation()
						jQuery.extend( saved[ 0 ], jQuery.Event.prototype ),
						saved.slice( 1 ),
						this
					)
				} );

				// Abort handling of the native event
				event.stopImmediatePropagation();
			}
		}
	} );
}

jQuery.removeEvent = function( elem, type, handle ) {

	// This "if" is needed for plain objects
	if ( elem.removeEventListener ) {
		elem.removeEventListener( type, handle );
	}
};

jQuery.Event = function( src, props ) {

	// Allow instantiation without the 'new' keyword
	if ( !( this instanceof jQuery.Event ) ) {
		return new jQuery.Event( src, props );
	}

	// Event object
	if ( src && src.type ) {
		this.originalEvent = src;
		this.type = src.type;

		// Events bubbling up the document may have been marked as prevented
		// by a handler lower down the tree; reflect the correct value.
		this.isDefaultPrevented = src.defaultPrevented ||
				src.defaultPrevented === undefined &&

				// Support: Android <=2.3 only
				src.returnValue === false ?
			returnTrue :
			returnFalse;

		// Create target properties
		// Support: Safari <=6 - 7 only
		// Target should not be a text node (#504, #13143)
		this.target = ( src.target && src.target.nodeType === 3 ) ?
			src.target.parentNode :
			src.target;

		this.currentTarget = src.currentTarget;
		this.relatedTarget = src.relatedTarget;

	// Event type
	} else {
		this.type = src;
	}

	// Put explicitly provided properties onto the event object
	if ( props ) {
		jQuery.extend( this, props );
	}

	// Create a timestamp if incoming event doesn't have one
	this.timeStamp = src && src.timeStamp || Date.now();

	// Mark it as fixed
	this[ jQuery.expando ] = true;
};

// jQuery.Event is based on DOM3 Events as specified by the ECMAScript Language Binding
// https://www.w3.org/TR/2003/WD-DOM-Level-3-Events-20030331/ecma-script-binding.html
jQuery.Event.prototype = {
	constructor: jQuery.Event,
	isDefaultPrevented: returnFalse,
	isPropagationStopped: returnFalse,
	isImmediatePropagationStopped: returnFalse,
	isSimulated: false,

	preventDefault: function() {
		var e = this.originalEvent;

		this.isDefaultPrevented = returnTrue;

		if ( e && !this.isSimulated ) {
			e.preventDefault();
		}
	},
	stopPropagation: function() {
		var e = this.originalEvent;

		this.isPropagationStopped = returnTrue;

		if ( e && !this.isSimulated ) {
			e.stopPropagation();
		}
	},
	stopImmediatePropagation: function() {
		var e = this.originalEvent;

		this.isImmediatePropagationStopped = returnTrue;

		if ( e && !this.isSimulated ) {
			e.stopImmediatePropagation();
		}

		this.stopPropagation();
	}
};

// Includes all common event props including KeyEvent and MouseEvent specific props
jQuery.each( {
	altKey: true,
	bubbles: true,
	cancelable: true,
	changedTouches: true,
	ctrlKey: true,
	detail: true,
	eventPhase: true,
	metaKey: true,
	pageX: true,
	pageY: true,
	shiftKey: true,
	view: true,
	"char": true,
	code: true,
	charCode: true,
	key: true,
	keyCode: true,
	button: true,
	buttons: true,
	clientX: true,
	clientY: true,
	offsetX: true,
	offsetY: true,
	pointerId: true,
	pointerType: true,
	screenX: true,
	screenY: true,
	targetTouches: true,
	toElement: true,
	touches: true,
	which: true
}, jQuery.event.addProp );

jQuery.each( { focus: "focusin", blur: "focusout" }, function( type, delegateType ) {
	jQuery.event.special[ type ] = {

		// Utilize native event if possible so blur/focus sequence is correct
		setup: function() {

			// Claim the first handler
			// dataPriv.set( this, "focus", ... )
			// dataPriv.set( this, "blur", ... )
			leverageNative( this, type, expectSync );

			// Return false to allow normal processing in the caller
			return false;
		},
		trigger: function() {

			// Force setup before trigger
			leverageNative( this, type );

			// Return non-false to allow normal event-path propagation
			return true;
		},

		// Suppress native focus or blur as it's already being fired
		// in leverageNative.
		_default: function() {
			return true;
		},

		delegateType: delegateType
	};
} );

// Create mouseenter/leave events using mouseover/out and event-time checks
// so that event delegation works in jQuery.
// Do the same for pointerenter/pointerleave and pointerover/pointerout
//
// Support: Safari 7 only
// Safari sends mouseenter too often; see:
// https://bugs.chromium.org/p/chromium/issues/detail?id=470258
// for the description of the bug (it existed in older Chrome versions as well).
jQuery.each( {
	mouseenter: "mouseover",
	mouseleave: "mouseout",
	pointerenter: "pointerover",
	pointerleave: "pointerout"
}, function( orig, fix ) {
	jQuery.event.special[ orig ] = {
		delegateType: fix,
		bindType: fix,

		handle: function( event ) {
			var ret,
				target = this,
				related = event.relatedTarget,
				handleObj = event.handleObj;

			// For mouseenter/leave call the handler if related is outside the target.
			// NB: No relatedTarget if the mouse left/entered the browser window
			if ( !related || ( related !== target && !jQuery.contains( target, related ) ) ) {
				event.type = handleObj.origType;
				ret = handleObj.handler.apply( this, arguments );
				event.type = fix;
			}
			return ret;
		}
	};
} );

jQuery.fn.extend( {

	on: function( types, selector, data, fn ) {
		return on( this, types, selector, data, fn );
	},
	one: function( types, selector, data, fn ) {
		return on( this, types, selector, data, fn, 1 );
	},
	off: function( types, selector, fn ) {
		var handleObj, type;
		if ( types && types.preventDefault && types.handleObj ) {

			// ( event )  dispatched jQuery.Event
			handleObj = types.handleObj;
			jQuery( types.delegateTarget ).off(
				handleObj.namespace ?
					handleObj.origType + "." + handleObj.namespace :
					handleObj.origType,
				handleObj.selector,
				handleObj.handler
			);
			return this;
		}
		if ( typeof types === "object" ) {

			// ( types-object [, selector] )
			for ( type in types ) {
				this.off( type, selector, types[ type ] );
			}
			return this;
		}
		if ( selector === false || typeof selector === "function" ) {

			// ( types [, fn] )
			fn = selector;
			selector = undefined;
		}
		if ( fn === false ) {
			fn = returnFalse;
		}
		return this.each( function() {
			jQuery.event.remove( this, types, fn, selector );
		} );
	}
} );


var

	// Support: IE <=10 - 11, Edge 12 - 13 only
	// In IE/Edge using regex groups here causes severe slowdowns.
	// See https://connect.microsoft.com/IE/feedback/details/1736512/
	rnoInnerhtml = /<script|<style|<link/i,

	// checked="checked" or checked
	rchecked = /checked\s*(?:[^=]|=\s*.checked.)/i,
	rcleanScript = /^\s*<!(?:\[CDATA\[|--)|(?:\]\]|--)>\s*$/g;

// Prefer a tbody over its parent table for containing new rows
function manipulationTarget( elem, content ) {
	if ( nodeName( elem, "table" ) &&
		nodeName( content.nodeType !== 11 ? content : content.firstChild, "tr" ) ) {

		return jQuery( elem ).children( "tbody" )[ 0 ] || elem;
	}

	return elem;
}

// Replace/restore the type attribute of script elements for safe DOM manipulation
function disableScript( elem ) {
	elem.type = ( elem.getAttribute( "type" ) !== null ) + "/" + elem.type;
	return elem;
}
function restoreScript( elem ) {
	if ( ( elem.type || "" ).slice( 0, 5 ) === "true/" ) {
		elem.type = elem.type.slice( 5 );
	} else {
		elem.removeAttribute( "type" );
	}

	return elem;
}

function cloneCopyEvent( src, dest ) {
	var i, l, type, pdataOld, udataOld, udataCur, events;

	if ( dest.nodeType !== 1 ) {
		return;
	}

	// 1. Copy private data: events, handlers, etc.
	if ( dataPriv.hasData( src ) ) {
		pdataOld = dataPriv.get( src );
		events = pdataOld.events;

		if ( events ) {
			dataPriv.remove( dest, "handle events" );

			for ( type in events ) {
				for ( i = 0, l = events[ type ].length; i < l; i++ ) {
					jQuery.event.add( dest, type, events[ type ][ i ] );
				}
			}
		}
	}

	// 2. Copy user data
	if ( dataUser.hasData( src ) ) {
		udataOld = dataUser.access( src );
		udataCur = jQuery.extend( {}, udataOld );

		dataUser.set( dest, udataCur );
	}
}

// Fix IE bugs, see support tests
function fixInput( src, dest ) {
	var nodeName = dest.nodeName.toLowerCase();

	// Fails to persist the checked state of a cloned checkbox or radio button.
	if ( nodeName === "input" && rcheckableType.test( src.type ) ) {
		dest.checked = src.checked;

	// Fails to return the selected option to the default selected state when cloning options
	} else if ( nodeName === "input" || nodeName === "textarea" ) {
		dest.defaultValue = src.defaultValue;
	}
}

function domManip( collection, args, callback, ignored ) {

	// Flatten any nested arrays
	args = flat( args );

	var fragment, first, scripts, hasScripts, node, doc,
		i = 0,
		l = collection.length,
		iNoClone = l - 1,
		value = args[ 0 ],
		valueIsFunction = isFunction( value );

	// We can't cloneNode fragments that contain checked, in WebKit
	if ( valueIsFunction ||
			( l > 1 && typeof value === "string" &&
				!support.checkClone && rchecked.test( value ) ) ) {
		return collection.each( function( index ) {
			var self = collection.eq( index );
			if ( valueIsFunction ) {
				args[ 0 ] = value.call( this, index, self.html() );
			}
			domManip( self, args, callback, ignored );
		} );
	}

	if ( l ) {
		fragment = buildFragment( args, collection[ 0 ].ownerDocument, false, collection, ignored );
		first = fragment.firstChild;

		if ( fragment.childNodes.length === 1 ) {
			fragment = first;
		}

		// Require either new content or an interest in ignored elements to invoke the callback
		if ( first || ignored ) {
			scripts = jQuery.map( getAll( fragment, "script" ), disableScript );
			hasScripts = scripts.length;

			// Use the original fragment for the last item
			// instead of the first because it can end up
			// being emptied incorrectly in certain situations (#8070).
			for ( ; i < l; i++ ) {
				node = fragment;

				if ( i !== iNoClone ) {
					node = jQuery.clone( node, true, true );

					// Keep references to cloned scripts for later restoration
					if ( hasScripts ) {

						// Support: Android <=4.0 only, PhantomJS 1 only
						// push.apply(_, arraylike) throws on ancient WebKit
						jQuery.merge( scripts, getAll( node, "script" ) );
					}
				}

				callback.call( collection[ i ], node, i );
			}

			if ( hasScripts ) {
				doc = scripts[ scripts.length - 1 ].ownerDocument;

				// Reenable scripts
				jQuery.map( scripts, restoreScript );

				// Evaluate executable scripts on first document insertion
				for ( i = 0; i < hasScripts; i++ ) {
					node = scripts[ i ];
					if ( rscriptType.test( node.type || "" ) &&
						!dataPriv.access( node, "globalEval" ) &&
						jQuery.contains( doc, node ) ) {

						if ( node.src && ( node.type || "" ).toLowerCase()  !== "module" ) {

							// Optional AJAX dependency, but won't run scripts if not present
							if ( jQuery._evalUrl && !node.noModule ) {
								jQuery._evalUrl( node.src, {
									nonce: node.nonce || node.getAttribute( "nonce" )
								}, doc );
							}
						} else {
							DOMEval( node.textContent.replace( rcleanScript, "" ), node, doc );
						}
					}
				}
			}
		}
	}

	return collection;
}

function remove( elem, selector, keepData ) {
	var node,
		nodes = selector ? jQuery.filter( selector, elem ) : elem,
		i = 0;

	for ( ; ( node = nodes[ i ] ) != null; i++ ) {
		if ( !keepData && node.nodeType === 1 ) {
			jQuery.cleanData( getAll( node ) );
		}

		if ( node.parentNode ) {
			if ( keepData && isAttached( node ) ) {
				setGlobalEval( getAll( node, "script" ) );
			}
			node.parentNode.removeChild( node );
		}
	}

	return elem;
}

jQuery.extend( {
	htmlPrefilter: function( html ) {
		return html;
	},

	clone: function( elem, dataAndEvents, deepDataAndEvents ) {
		var i, l, srcElements, destElements,
			clone = elem.cloneNode( true ),
			inPage = isAttached( elem );

		// Fix IE cloning issues
		if ( !support.noCloneChecked && ( elem.nodeType === 1 || elem.nodeType === 11 ) &&
				!jQuery.isXMLDoc( elem ) ) {

			// We eschew Sizzle here for performance reasons: https://jsperf.com/getall-vs-sizzle/2
			destElements = getAll( clone );
			srcElements = getAll( elem );

			for ( i = 0, l = srcElements.length; i < l; i++ ) {
				fixInput( srcElements[ i ], destElements[ i ] );
			}
		}

		// Copy the events from the original to the clone
		if ( dataAndEvents ) {
			if ( deepDataAndEvents ) {
				srcElements = srcElements || getAll( elem );
				destElements = destElements || getAll( clone );

				for ( i = 0, l = srcElements.length; i < l; i++ ) {
					cloneCopyEvent( srcElements[ i ], destElements[ i ] );
				}
			} else {
				cloneCopyEvent( elem, clone );
			}
		}

		// Preserve script evaluation history
		destElements = getAll( clone, "script" );
		if ( destElements.length > 0 ) {
			setGlobalEval( destElements, !inPage && getAll( elem, "script" ) );
		}

		// Return the cloned set
		return clone;
	},

	cleanData: function( elems ) {
		var data, elem, type,
			special = jQuery.event.special,
			i = 0;

		for ( ; ( elem = elems[ i ] ) !== undefined; i++ ) {
			if ( acceptData( elem ) ) {
				if ( ( data = elem[ dataPriv.expando ] ) ) {
					if ( data.events ) {
						for ( type in data.events ) {
							if ( special[ type ] ) {
								jQuery.event.remove( elem, type );

							// This is a shortcut to avoid jQuery.event.remove's overhead
							} else {
								jQuery.removeEvent( elem, type, data.handle );
							}
						}
					}

					// Support: Chrome <=35 - 45+
					// Assign undefined instead of using delete, see Data#remove
					elem[ dataPriv.expando ] = undefined;
				}
				if ( elem[ dataUser.expando ] ) {

					// Support: Chrome <=35 - 45+
					// Assign undefined instead of using delete, see Data#remove
					elem[ dataUser.expando ] = undefined;
				}
			}
		}
	}
} );

jQuery.fn.extend( {
	detach: function( selector ) {
		return remove( this, selector, true );
	},

	remove: function( selector ) {
		return remove( this, selector );
	},

	text: function( value ) {
		return access( this, function( value ) {
			return value === undefined ?
				jQuery.text( this ) :
				this.empty().each( function() {
					if ( this.nodeType === 1 || this.nodeType === 11 || this.nodeType === 9 ) {
						this.textContent = value;
					}
				} );
		}, null, value, arguments.length );
	},

	append: function() {
		return domManip( this, arguments, function( elem ) {
			if ( this.nodeType === 1 || this.nodeType === 11 || this.nodeType === 9 ) {
				var target = manipulationTarget( this, elem );
				target.appendChild( elem );
			}
		} );
	},

	prepend: function() {
		return domManip( this, arguments, function( elem ) {
			if ( this.nodeType === 1 || this.nodeType === 11 || this.nodeType === 9 ) {
				var target = manipulationTarget( this, elem );
				target.insertBefore( elem, target.firstChild );
			}
		} );
	},

	before: function() {
		return domManip( this, arguments, function( elem ) {
			if ( this.parentNode ) {
				this.parentNode.insertBefore( elem, this );
			}
		} );
	},

	after: function() {
		return domManip( this, arguments, function( elem ) {
			if ( this.parentNode ) {
				this.parentNode.insertBefore( elem, this.nextSibling );
			}
		} );
	},

	empty: function() {
		var elem,
			i = 0;

		for ( ; ( elem = this[ i ] ) != null; i++ ) {
			if ( elem.nodeType === 1 ) {

				// Prevent memory leaks
				jQuery.cleanData( getAll( elem, false ) );

				// Remove any remaining nodes
				elem.textContent = "";
			}
		}

		return this;
	},

	clone: function( dataAndEvents, deepDataAndEvents ) {
		dataAndEvents = dataAndEvents == null ? false : dataAndEvents;
		deepDataAndEvents = deepDataAndEvents == null ? dataAndEvents : deepDataAndEvents;

		return this.map( function() {
			return jQuery.clone( this, dataAndEvents, deepDataAndEvents );
		} );
	},

	html: function( value ) {
		return access( this, function( value ) {
			var elem = this[ 0 ] || {},
				i = 0,
				l = this.length;

			if ( value === undefined && elem.nodeType === 1 ) {
				return elem.innerHTML;
			}

			// See if we can take a shortcut and just use innerHTML
			if ( typeof value === "string" && !rnoInnerhtml.test( value ) &&
				!wrapMap[ ( rtagName.exec( value ) || [ "", "" ] )[ 1 ].toLowerCase() ] ) {

				value = jQuery.htmlPrefilter( value );

				try {
					for ( ; i < l; i++ ) {
						elem = this[ i ] || {};

						// Remove element nodes and prevent memory leaks
						if ( elem.nodeType === 1 ) {
							jQuery.cleanData( getAll( elem, false ) );
							elem.innerHTML = value;
						}
					}

					elem = 0;

				// If using innerHTML throws an exception, use the fallback method
				} catch ( e ) {}
			}

			if ( elem ) {
				this.empty().append( value );
			}
		}, null, value, arguments.length );
	},

	replaceWith: function() {
		var ignored = [];

		// Make the changes, replacing each non-ignored context element with the new content
		return domManip( this, arguments, function( elem ) {
			var parent = this.parentNode;

			if ( jQuery.inArray( this, ignored ) < 0 ) {
				jQuery.cleanData( getAll( this ) );
				if ( parent ) {
					parent.replaceChild( elem, this );
				}
			}

		// Force callback invocation
		}, ignored );
	}
} );

jQuery.each( {
	appendTo: "append",
	prependTo: "prepend",
	insertBefore: "before",
	insertAfter: "after",
	replaceAll: "replaceWith"
}, function( name, original ) {
	jQuery.fn[ name ] = function( selector ) {
		var elems,
			ret = [],
			insert = jQuery( selector ),
			last = insert.length - 1,
			i = 0;

		for ( ; i <= last; i++ ) {
			elems = i === last ? this : this.clone( true );
			jQuery( insert[ i ] )[ original ]( elems );

			// Support: Android <=4.0 only, PhantomJS 1 only
			// .get() because push.apply(_, arraylike) throws on ancient WebKit
			push.apply( ret, elems.get() );
		}

		return this.pushStack( ret );
	};
} );
var rnumnonpx = new RegExp( "^(" + pnum + ")(?!px)[a-z%]+$", "i" );

var getStyles = function( elem ) {

		// Support: IE <=11 only, Firefox <=30 (#15098, #14150)
		// IE throws on elements created in popups
		// FF meanwhile throws on frame elements through "defaultView.getComputedStyle"
		var view = elem.ownerDocument.defaultView;

		if ( !view || !view.opener ) {
			view = window;
		}

		return view.getComputedStyle( elem );
	};

var swap = function( elem, options, callback ) {
	var ret, name,
		old = {};

	// Remember the old values, and insert the new ones
	for ( name in options ) {
		old[ name ] = elem.style[ name ];
		elem.style[ name ] = options[ name ];
	}

	ret = callback.call( elem );

	// Revert the old values
	for ( name in options ) {
		elem.style[ name ] = old[ name ];
	}

	return ret;
};


var rboxStyle = new RegExp( cssExpand.join( "|" ), "i" );



( function() {

	// Executing both pixelPosition & boxSizingReliable tests require only one layout
	// so they're executed at the same time to save the second computation.
	function computeStyleTests() {

		// This is a singleton, we need to execute it only once
		if ( !div ) {
			return;
		}

		container.style.cssText = "position:absolute;left:-11111px;width:60px;" +
			"margin-top:1px;padding:0;border:0";
		div.style.cssText =
			"position:relative;display:block;box-sizing:border-box;overflow:scroll;" +
			"margin:auto;border:1px;padding:1px;" +
			"width:60%;top:1%";
		documentElement.appendChild( container ).appendChild( div );

		var divStyle = window.getComputedStyle( div );
		pixelPositionVal = divStyle.top !== "1%";

		// Support: Android 4.0 - 4.3 only, Firefox <=3 - 44
		reliableMarginLeftVal = roundPixelMeasures( divStyle.marginLeft ) === 12;

		// Support: Android 4.0 - 4.3 only, Safari <=9.1 - 10.1, iOS <=7.0 - 9.3
		// Some styles come back with percentage values, even though they shouldn't
		div.style.right = "60%";
		pixelBoxStylesVal = roundPixelMeasures( divStyle.right ) === 36;

		// Support: IE 9 - 11 only
		// Detect misreporting of content dimensions for box-sizing:border-box elements
		boxSizingReliableVal = roundPixelMeasures( divStyle.width ) === 36;

		// Support: IE 9 only
		// Detect overflow:scroll screwiness (gh-3699)
		// Support: Chrome <=64
		// Don't get tricked when zoom affects offsetWidth (gh-4029)
		div.style.position = "absolute";
		scrollboxSizeVal = roundPixelMeasures( div.offsetWidth / 3 ) === 12;

		documentElement.removeChild( container );

		// Nullify the div so it wouldn't be stored in the memory and
		// it will also be a sign that checks already performed
		div = null;
	}

	function roundPixelMeasures( measure ) {
		return Math.round( parseFloat( measure ) );
	}

	var pixelPositionVal, boxSizingReliableVal, scrollboxSizeVal, pixelBoxStylesVal,
		reliableTrDimensionsVal, reliableMarginLeftVal,
		container = document.createElement( "div" ),
		div = document.createElement( "div" );

	// Finish early in limited (non-browser) environments
	if ( !div.style ) {
		return;
	}

	// Support: IE <=9 - 11 only
	// Style of cloned element affects source element cloned (#8908)
	div.style.backgroundClip = "content-box";
	div.cloneNode( true ).style.backgroundClip = "";
	support.clearCloneStyle = div.style.backgroundClip === "content-box";

	jQuery.extend( support, {
		boxSizingReliable: function() {
			computeStyleTests();
			return boxSizingReliableVal;
		},
		pixelBoxStyles: function() {
			computeStyleTests();
			return pixelBoxStylesVal;
		},
		pixelPosition: function() {
			computeStyleTests();
			return pixelPositionVal;
		},
		reliableMarginLeft: function() {
			computeStyleTests();
			return reliableMarginLeftVal;
		},
		scrollboxSize: function() {
			computeStyleTests();
			return scrollboxSizeVal;
		},

		// Support: IE 9 - 11+, Edge 15 - 18+
		// IE/Edge misreport `getComputedStyle` of table rows with width/height
		// set in CSS while `offset*` properties report correct values.
		// Behavior in IE 9 is more subtle than in newer versions & it passes
		// some versions of this test; make sure not to make it pass there!
		//
		// Support: Firefox 70+
		// Only Firefox includes border widths
		// in computed dimensions. (gh-4529)
		reliableTrDimensions: function() {
			var table, tr, trChild, trStyle;
			if ( reliableTrDimensionsVal == null ) {
				table = document.createElement( "table" );
				tr = document.createElement( "tr" );
				trChild = document.createElement( "div" );

				table.style.cssText = "position:absolute;left:-11111px;border-collapse:separate";
				tr.style.cssText = "border:1px solid";

				// Support: Chrome 86+
				// Height set through cssText does not get applied.
				// Computed height then comes back as 0.
				tr.style.height = "1px";
				trChild.style.height = "9px";

				// Support: Android 8 Chrome 86+
				// In our bodyBackground.html iframe,
				// display for all div elements is set to "inline",
				// which causes a problem only in Android 8 Chrome 86.
				// Ensuring the div is display: block
				// gets around this issue.
				trChild.style.display = "block";

				documentElement
					.appendChild( table )
					.appendChild( tr )
					.appendChild( trChild );

				trStyle = window.getComputedStyle( tr );
				reliableTrDimensionsVal = ( parseInt( trStyle.height, 10 ) +
					parseInt( trStyle.borderTopWidth, 10 ) +
					parseInt( trStyle.borderBottomWidth, 10 ) ) === tr.offsetHeight;

				documentElement.removeChild( table );
			}
			return reliableTrDimensionsVal;
		}
	} );
} )();


function curCSS( elem, name, computed ) {
	var width, minWidth, maxWidth, ret,

		// Support: Firefox 51+
		// Retrieving style before computed somehow
		// fixes an issue with getting wrong values
		// on detached elements
		style = elem.style;

	computed = computed || getStyles( elem );

	// getPropertyValue is needed for:
	//   .css('filter') (IE 9 only, #12537)
	//   .css('--customProperty) (#3144)
	if ( computed ) {
		ret = computed.getPropertyValue( name ) || computed[ name ];

		if ( ret === "" && !isAttached( elem ) ) {
			ret = jQuery.style( elem, name );
		}

		// A tribute to the "awesome hack by Dean Edwards"
		// Android Browser returns percentage for some values,
		// but width seems to be reliably pixels.
		// This is against the CSSOM draft spec:
		// https://drafts.csswg.org/cssom/#resolved-values
		if ( !support.pixelBoxStyles() && rnumnonpx.test( ret ) && rboxStyle.test( name ) ) {

			// Remember the original values
			width = style.width;
			minWidth = style.minWidth;
			maxWidth = style.maxWidth;

			// Put in the new values to get a computed value out
			style.minWidth = style.maxWidth = style.width = ret;
			ret = computed.width;

			// Revert the changed values
			style.width = width;
			style.minWidth = minWidth;
			style.maxWidth = maxWidth;
		}
	}

	return ret !== undefined ?

		// Support: IE <=9 - 11 only
		// IE returns zIndex value as an integer.
		ret + "" :
		ret;
}


function addGetHookIf( conditionFn, hookFn ) {

	// Define the hook, we'll check on the first run if it's really needed.
	return {
		get: function() {
			if ( conditionFn() ) {

				// Hook not needed (or it's not possible to use it due
				// to missing dependency), remove it.
				delete this.get;
				return;
			}

			// Hook needed; redefine it so that the support test is not executed again.
			return ( this.get = hookFn ).apply( this, arguments );
		}
	};
}


var cssPrefixes = [ "Webkit", "Moz", "ms" ],
	emptyStyle = document.createElement( "div" ).style,
	vendorProps = {};

// Return a vendor-prefixed property or undefined
function vendorPropName( name ) {

	// Check for vendor prefixed names
	var capName = name[ 0 ].toUpperCase() + name.slice( 1 ),
		i = cssPrefixes.length;

	while ( i-- ) {
		name = cssPrefixes[ i ] + capName;
		if ( name in emptyStyle ) {
			return name;
		}
	}
}

// Return a potentially-mapped jQuery.cssProps or vendor prefixed property
function finalPropName( name ) {
	var final = jQuery.cssProps[ name ] || vendorProps[ name ];

	if ( final ) {
		return final;
	}
	if ( name in emptyStyle ) {
		return name;
	}
	return vendorProps[ name ] = vendorPropName( name ) || name;
}


var

	// Swappable if display is none or starts with table
	// except "table", "table-cell", or "table-caption"
	// See here for display values: https://developer.mozilla.org/en-US/docs/CSS/display
	rdisplayswap = /^(none|table(?!-c[ea]).+)/,
	rcustomProp = /^--/,
	cssShow = { position: "absolute", visibility: "hidden", display: "block" },
	cssNormalTransform = {
		letterSpacing: "0",
		fontWeight: "400"
	};

function setPositiveNumber( _elem, value, subtract ) {

	// Any relative (+/-) values have already been
	// normalized at this point
	var matches = rcssNum.exec( value );
	return matches ?

		// Guard against undefined "subtract", e.g., when used as in cssHooks
		Math.max( 0, matches[ 2 ] - ( subtract || 0 ) ) + ( matches[ 3 ] || "px" ) :
		value;
}

function boxModelAdjustment( elem, dimension, box, isBorderBox, styles, computedVal ) {
	var i = dimension === "width" ? 1 : 0,
		extra = 0,
		delta = 0;

	// Adjustment may not be necessary
	if ( box === ( isBorderBox ? "border" : "content" ) ) {
		return 0;
	}

	for ( ; i < 4; i += 2 ) {

		// Both box models exclude margin
		if ( box === "margin" ) {
			delta += jQuery.css( elem, box + cssExpand[ i ], true, styles );
		}

		// If we get here with a content-box, we're seeking "padding" or "border" or "margin"
		if ( !isBorderBox ) {

			// Add padding
			delta += jQuery.css( elem, "padding" + cssExpand[ i ], true, styles );

			// For "border" or "margin", add border
			if ( box !== "padding" ) {
				delta += jQuery.css( elem, "border" + cssExpand[ i ] + "Width", true, styles );

			// But still keep track of it otherwise
			} else {
				extra += jQuery.css( elem, "border" + cssExpand[ i ] + "Width", true, styles );
			}

		// If we get here with a border-box (content + padding + border), we're seeking "content" or
		// "padding" or "margin"
		} else {

			// For "content", subtract padding
			if ( box === "content" ) {
				delta -= jQuery.css( elem, "padding" + cssExpand[ i ], true, styles );
			}

			// For "content" or "padding", subtract border
			if ( box !== "margin" ) {
				delta -= jQuery.css( elem, "border" + cssExpand[ i ] + "Width", true, styles );
			}
		}
	}

	// Account for positive content-box scroll gutter when requested by providing computedVal
	if ( !isBorderBox && computedVal >= 0 ) {

		// offsetWidth/offsetHeight is a rounded sum of content, padding, scroll gutter, and border
		// Assuming integer scroll gutter, subtract the rest and round down
		delta += Math.max( 0, Math.ceil(
			elem[ "offset" + dimension[ 0 ].toUpperCase() + dimension.slice( 1 ) ] -
			computedVal -
			delta -
			extra -
			0.5

		// If offsetWidth/offsetHeight is unknown, then we can't determine content-box scroll gutter
		// Use an explicit zero to avoid NaN (gh-3964)
		) ) || 0;
	}

	return delta;
}

function getWidthOrHeight( elem, dimension, extra ) {

	// Start with computed style
	var styles = getStyles( elem ),

		// To avoid forcing a reflow, only fetch boxSizing if we need it (gh-4322).
		// Fake content-box until we know it's needed to know the true value.
		boxSizingNeeded = !support.boxSizingReliable() || extra,
		isBorderBox = boxSizingNeeded &&
			jQuery.css( elem, "boxSizing", false, styles ) === "border-box",
		valueIsBorderBox = isBorderBox,

		val = curCSS( elem, dimension, styles ),
		offsetProp = "offset" + dimension[ 0 ].toUpperCase() + dimension.slice( 1 );

	// Support: Firefox <=54
	// Return a confounding non-pixel value or feign ignorance, as appropriate.
	if ( rnumnonpx.test( val ) ) {
		if ( !extra ) {
			return val;
		}
		val = "auto";
	}


	// Support: IE 9 - 11 only
	// Use offsetWidth/offsetHeight for when box sizing is unreliable.
	// In those cases, the computed value can be trusted to be border-box.
	if ( ( !support.boxSizingReliable() && isBorderBox ||

		// Support: IE 10 - 11+, Edge 15 - 18+
		// IE/Edge misreport `getComputedStyle` of table rows with width/height
		// set in CSS while `offset*` properties report correct values.
		// Interestingly, in some cases IE 9 doesn't suffer from this issue.
		!support.reliableTrDimensions() && nodeName( elem, "tr" ) ||

		// Fall back to offsetWidth/offsetHeight when value is "auto"
		// This happens for inline elements with no explicit setting (gh-3571)
		val === "auto" ||

		// Support: Android <=4.1 - 4.3 only
		// Also use offsetWidth/offsetHeight for misreported inline dimensions (gh-3602)
		!parseFloat( val ) && jQuery.css( elem, "display", false, styles ) === "inline" ) &&

		// Make sure the element is visible & connected
		elem.getClientRects().length ) {

		isBorderBox = jQuery.css( elem, "boxSizing", false, styles ) === "border-box";

		// Where available, offsetWidth/offsetHeight approximate border box dimensions.
		// Where not available (e.g., SVG), assume unreliable box-sizing and interpret the
		// retrieved value as a content box dimension.
		valueIsBorderBox = offsetProp in elem;
		if ( valueIsBorderBox ) {
			val = elem[ offsetProp ];
		}
	}

	// Normalize "" and auto
	val = parseFloat( val ) || 0;

	// Adjust for the element's box model
	return ( val +
		boxModelAdjustment(
			elem,
			dimension,
			extra || ( isBorderBox ? "border" : "content" ),
			valueIsBorderBox,
			styles,

			// Provide the current computed size to request scroll gutter calculation (gh-3589)
			val
		)
	) + "px";
}

jQuery.extend( {

	// Add in style property hooks for overriding the default
	// behavior of getting and setting a style property
	cssHooks: {
		opacity: {
			get: function( elem, computed ) {
				if ( computed ) {

					// We should always get a number back from opacity
					var ret = curCSS( elem, "opacity" );
					return ret === "" ? "1" : ret;
				}
			}
		}
	},

	// Don't automatically add "px" to these possibly-unitless properties
	cssNumber: {
		"animationIterationCount": true,
		"columnCount": true,
		"fillOpacity": true,
		"flexGrow": true,
		"flexShrink": true,
		"fontWeight": true,
		"gridArea": true,
		"gridColumn": true,
		"gridColumnEnd": true,
		"gridColumnStart": true,
		"gridRow": true,
		"gridRowEnd": true,
		"gridRowStart": true,
		"lineHeight": true,
		"opacity": true,
		"order": true,
		"orphans": true,
		"widows": true,
		"zIndex": true,
		"zoom": true
	},

	// Add in properties whose names you wish to fix before
	// setting or getting the value
	cssProps: {},

	// Get and set the style property on a DOM Node
	style: function( elem, name, value, extra ) {

		// Don't set styles on text and comment nodes
		if ( !elem || elem.nodeType === 3 || elem.nodeType === 8 || !elem.style ) {
			return;
		}

		// Make sure that we're working with the right name
		var ret, type, hooks,
			origName = camelCase( name ),
			isCustomProp = rcustomProp.test( name ),
			style = elem.style;

		// Make sure that we're working with the right name. We don't
		// want to query the value if it is a CSS custom property
		// since they are user-defined.
		if ( !isCustomProp ) {
			name = finalPropName( origName );
		}

		// Gets hook for the prefixed version, then unprefixed version
		hooks = jQuery.cssHooks[ name ] || jQuery.cssHooks[ origName ];

		// Check if we're setting a value
		if ( value !== undefined ) {
			type = typeof value;

			// Convert "+=" or "-=" to relative numbers (#7345)
			if ( type === "string" && ( ret = rcssNum.exec( value ) ) && ret[ 1 ] ) {
				value = adjustCSS( elem, name, ret );

				// Fixes bug #9237
				type = "number";
			}

			// Make sure that null and NaN values aren't set (#7116)
			if ( value == null || value !== value ) {
				return;
			}

			// If a number was passed in, add the unit (except for certain CSS properties)
			// The isCustomProp check can be removed in jQuery 4.0 when we only auto-append
			// "px" to a few hardcoded values.
			if ( type === "number" && !isCustomProp ) {
				value += ret && ret[ 3 ] || ( jQuery.cssNumber[ origName ] ? "" : "px" );
			}

			// background-* props affect original clone's values
			if ( !support.clearCloneStyle && value === "" && name.indexOf( "background" ) === 0 ) {
				style[ name ] = "inherit";
			}

			// If a hook was provided, use that value, otherwise just set the specified value
			if ( !hooks || !( "set" in hooks ) ||
				( value = hooks.set( elem, value, extra ) ) !== undefined ) {

				if ( isCustomProp ) {
					style.setProperty( name, value );
				} else {
					style[ name ] = value;
				}
			}

		} else {

			// If a hook was provided get the non-computed value from there
			if ( hooks && "get" in hooks &&
				( ret = hooks.get( elem, false, extra ) ) !== undefined ) {

				return ret;
			}

			// Otherwise just get the value from the style object
			return style[ name ];
		}
	},

	css: function( elem, name, extra, styles ) {
		var val, num, hooks,
			origName = camelCase( name ),
			isCustomProp = rcustomProp.test( name );

		// Make sure that we're working with the right name. We don't
		// want to modify the value if it is a CSS custom property
		// since they are user-defined.
		if ( !isCustomProp ) {
			name = finalPropName( origName );
		}

		// Try prefixed name followed by the unprefixed name
		hooks = jQuery.cssHooks[ name ] || jQuery.cssHooks[ origName ];

		// If a hook was provided get the computed value from there
		if ( hooks && "get" in hooks ) {
			val = hooks.get( elem, true, extra );
		}

		// Otherwise, if a way to get the computed value exists, use that
		if ( val === undefined ) {
			val = curCSS( elem, name, styles );
		}

		// Convert "normal" to computed value
		if ( val === "normal" && name in cssNormalTransform ) {
			val = cssNormalTransform[ name ];
		}

		// Make numeric if forced or a qualifier was provided and val looks numeric
		if ( extra === "" || extra ) {
			num = parseFloat( val );
			return extra === true || isFinite( num ) ? num || 0 : val;
		}

		return val;
	}
} );

jQuery.each( [ "height", "width" ], function( _i, dimension ) {
	jQuery.cssHooks[ dimension ] = {
		get: function( elem, computed, extra ) {
			if ( computed ) {

				// Certain elements can have dimension info if we invisibly show them
				// but it must have a current display style that would benefit
				return rdisplayswap.test( jQuery.css( elem, "display" ) ) &&

					// Support: Safari 8+
					// Table columns in Safari have non-zero offsetWidth & zero
					// getBoundingClientRect().width unless display is changed.
					// Support: IE <=11 only
					// Running getBoundingClientRect on a disconnected node
					// in IE throws an error.
					( !elem.getClientRects().length || !elem.getBoundingClientRect().width ) ?
					swap( elem, cssShow, function() {
						return getWidthOrHeight( elem, dimension, extra );
					} ) :
					getWidthOrHeight( elem, dimension, extra );
			}
		},

		set: function( elem, value, extra ) {
			var matches,
				styles = getStyles( elem ),

				// Only read styles.position if the test has a chance to fail
				// to avoid forcing a reflow.
				scrollboxSizeBuggy = !support.scrollboxSize() &&
					styles.position === "absolute",

				// To avoid forcing a reflow, only fetch boxSizing if we need it (gh-3991)
				boxSizingNeeded = scrollboxSizeBuggy || extra,
				isBorderBox = boxSizingNeeded &&
					jQuery.css( elem, "boxSizing", false, styles ) === "border-box",
				subtract = extra ?
					boxModelAdjustment(
						elem,
						dimension,
						extra,
						isBorderBox,
						styles
					) :
					0;

			// Account for unreliable border-box dimensions by comparing offset* to computed and
			// faking a content-box to get border and padding (gh-3699)
			if ( isBorderBox && scrollboxSizeBuggy ) {
				subtract -= Math.ceil(
					elem[ "offset" + dimension[ 0 ].toUpperCase() + dimension.slice( 1 ) ] -
					parseFloat( styles[ dimension ] ) -
					boxModelAdjustment( elem, dimension, "border", false, styles ) -
					0.5
				);
			}

			// Convert to pixels if value adjustment is needed
			if ( subtract && ( matches = rcssNum.exec( value ) ) &&
				( matches[ 3 ] || "px" ) !== "px" ) {

				elem.style[ dimension ] = value;
				value = jQuery.css( elem, dimension );
			}

			return setPositiveNumber( elem, value, subtract );
		}
	};
} );

jQuery.cssHooks.marginLeft = addGetHookIf( support.reliableMarginLeft,
	function( elem, computed ) {
		if ( computed ) {
			return ( parseFloat( curCSS( elem, "marginLeft" ) ) ||
				elem.getBoundingClientRect().left -
					swap( elem, { marginLeft: 0 }, function() {
						return elem.getBoundingClientRect().left;
					} )
			) + "px";
		}
	}
);

// These hooks are used by animate to expand properties
jQuery.each( {
	margin: "",
	padding: "",
	border: "Width"
}, function( prefix, suffix ) {
	jQuery.cssHooks[ prefix + suffix ] = {
		expand: function( value ) {
			var i = 0,
				expanded = {},

				// Assumes a single number if not a string
				parts = typeof value === "string" ? value.split( " " ) : [ value ];

			for ( ; i < 4; i++ ) {
				expanded[ prefix + cssExpand[ i ] + suffix ] =
					parts[ i ] || parts[ i - 2 ] || parts[ 0 ];
			}

			return expanded;
		}
	};

	if ( prefix !== "margin" ) {
		jQuery.cssHooks[ prefix + suffix ].set = setPositiveNumber;
	}
} );

jQuery.fn.extend( {
	css: function( name, value ) {
		return access( this, function( elem, name, value ) {
			var styles, len,
				map = {},
				i = 0;

			if ( Array.isArray( name ) ) {
				styles = getStyles( elem );
				len = name.length;

				for ( ; i < len; i++ ) {
					map[ name[ i ] ] = jQuery.css( elem, name[ i ], false, styles );
				}

				return map;
			}

			return value !== undefined ?
				jQuery.style( elem, name, value ) :
				jQuery.css( elem, name );
		}, name, value, arguments.length > 1 );
	}
} );


function Tween( elem, options, prop, end, easing ) {
	return new Tween.prototype.init( elem, options, prop, end, easing );
}
jQuery.Tween = Tween;

Tween.prototype = {
	constructor: Tween,
	init: function( elem, options, prop, end, easing, unit ) {
		this.elem = elem;
		this.prop = prop;
		this.easing = easing || jQuery.easing._default;
		this.options = options;
		this.start = this.now = this.cur();
		this.end = end;
		this.unit = unit || ( jQuery.cssNumber[ prop ] ? "" : "px" );
	},
	cur: function() {
		var hooks = Tween.propHooks[ this.prop ];

		return hooks && hooks.get ?
			hooks.get( this ) :
			Tween.propHooks._default.get( this );
	},
	run: function( percent ) {
		var eased,
			hooks = Tween.propHooks[ this.prop ];

		if ( this.options.duration ) {
			this.pos = eased = jQuery.easing[ this.easing ](
				percent, this.options.duration * percent, 0, 1, this.options.duration
			);
		} else {
			this.pos = eased = percent;
		}
		this.now = ( this.end - this.start ) * eased + this.start;

		if ( this.options.step ) {
			this.options.step.call( this.elem, this.now, this );
		}

		if ( hooks && hooks.set ) {
			hooks.set( this );
		} else {
			Tween.propHooks._default.set( this );
		}
		return this;
	}
};

Tween.prototype.init.prototype = Tween.prototype;

Tween.propHooks = {
	_default: {
		get: function( tween ) {
			var result;

			// Use a property on the element directly when it is not a DOM element,
			// or when there is no matching style property that exists.
			if ( tween.elem.nodeType !== 1 ||
				tween.elem[ tween.prop ] != null && tween.elem.style[ tween.prop ] == null ) {
				return tween.elem[ tween.prop ];
			}

			// Passing an empty string as a 3rd parameter to .css will automatically
			// attempt a parseFloat and fallback to a string if the parse fails.
			// Simple values such as "10px" are parsed to Float;
			// complex values such as "rotate(1rad)" are returned as-is.
			result = jQuery.css( tween.elem, tween.prop, "" );

			// Empty strings, null, undefined and "auto" are converted to 0.
			return !result || result === "auto" ? 0 : result;
		},
		set: function( tween ) {

			// Use step hook for back compat.
			// Use cssHook if its there.
			// Use .style if available and use plain properties where available.
			if ( jQuery.fx.step[ tween.prop ] ) {
				jQuery.fx.step[ tween.prop ]( tween );
			} else if ( tween.elem.nodeType === 1 && (
				jQuery.cssHooks[ tween.prop ] ||
					tween.elem.style[ finalPropName( tween.prop ) ] != null ) ) {
				jQuery.style( tween.elem, tween.prop, tween.now + tween.unit );
			} else {
				tween.elem[ tween.prop ] = tween.now;
			}
		}
	}
};

// Support: IE <=9 only
// Panic based approach to setting things on disconnected nodes
Tween.propHooks.scrollTop = Tween.propHooks.scrollLeft = {
	set: function( tween ) {
		if ( tween.elem.nodeType && tween.elem.parentNode ) {
			tween.elem[ tween.prop ] = tween.now;
		}
	}
};

jQuery.easing = {
	linear: function( p ) {
		return p;
	},
	swing: function( p ) {
		return 0.5 - Math.cos( p * Math.PI ) / 2;
	},
	_default: "swing"
};

jQuery.fx = Tween.prototype.init;

// Back compat <1.8 extension point
jQuery.fx.step = {};




var
	fxNow, inProgress,
	rfxtypes = /^(?:toggle|show|hide)$/,
	rrun = /queueHooks$/;

function schedule() {
	if ( inProgress ) {
		if ( document.hidden === false && window.requestAnimationFrame ) {
			window.requestAnimationFrame( schedule );
		} else {
			window.setTimeout( schedule, jQuery.fx.interval );
		}

		jQuery.fx.tick();
	}
}

// Animations created synchronously will run synchronously
function createFxNow() {
	window.setTimeout( function() {
		fxNow = undefined;
	} );
	return ( fxNow = Date.now() );
}

// Generate parameters to create a standard animation
function genFx( type, includeWidth ) {
	var which,
		i = 0,
		attrs = { height: type };

	// If we include width, step value is 1 to do all cssExpand values,
	// otherwise step value is 2 to skip over Left and Right
	includeWidth = includeWidth ? 1 : 0;
	for ( ; i < 4; i += 2 - includeWidth ) {
		which = cssExpand[ i ];
		attrs[ "margin" + which ] = attrs[ "padding" + which ] = type;
	}

	if ( includeWidth ) {
		attrs.opacity = attrs.width = type;
	}

	return attrs;
}

function createTween( value, prop, animation ) {
	var tween,
		collection = ( Animation.tweeners[ prop ] || [] ).concat( Animation.tweeners[ "*" ] ),
		index = 0,
		length = collection.length;
	for ( ; index < length; index++ ) {
		if ( ( tween = collection[ index ].call( animation, prop, value ) ) ) {

			// We're done with this property
			return tween;
		}
	}
}

function defaultPrefilter( elem, props, opts ) {
	var prop, value, toggle, hooks, oldfire, propTween, restoreDisplay, display,
		isBox = "width" in props || "height" in props,
		anim = this,
		orig = {},
		style = elem.style,
		hidden = elem.nodeType && isHiddenWithinTree( elem ),
		dataShow = dataPriv.get( elem, "fxshow" );

	// Queue-skipping animations hijack the fx hooks
	if ( !opts.queue ) {
		hooks = jQuery._queueHooks( elem, "fx" );
		if ( hooks.unqueued == null ) {
			hooks.unqueued = 0;
			oldfire = hooks.empty.fire;
			hooks.empty.fire = function() {
				if ( !hooks.unqueued ) {
					oldfire();
				}
			};
		}
		hooks.unqueued++;

		anim.always( function() {

			// Ensure the complete handler is called before this completes
			anim.always( function() {
				hooks.unqueued--;
				if ( !jQuery.queue( elem, "fx" ).length ) {
					hooks.empty.fire();
				}
			} );
		} );
	}

	// Detect show/hide animations
	for ( prop in props ) {
		value = props[ prop ];
		if ( rfxtypes.test( value ) ) {
			delete props[ prop ];
			toggle = toggle || value === "toggle";
			if ( value === ( hidden ? "hide" : "show" ) ) {

				// Pretend to be hidden if this is a "show" and
				// there is still data from a stopped show/hide
				if ( value === "show" && dataShow && dataShow[ prop ] !== undefined ) {
					hidden = true;

				// Ignore all other no-op show/hide data
				} else {
					continue;
				}
			}
			orig[ prop ] = dataShow && dataShow[ prop ] || jQuery.style( elem, prop );
		}
	}

	// Bail out if this is a no-op like .hide().hide()
	propTween = !jQuery.isEmptyObject( props );
	if ( !propTween && jQuery.isEmptyObject( orig ) ) {
		return;
	}

	// Restrict "overflow" and "display" styles during box animations
	if ( isBox && elem.nodeType === 1 ) {

		// Support: IE <=9 - 11, Edge 12 - 15
		// Record all 3 overflow attributes because IE does not infer the shorthand
		// from identically-valued overflowX and overflowY and Edge just mirrors
		// the overflowX value there.
		opts.overflow = [ style.overflow, style.overflowX, style.overflowY ];

		// Identify a display type, preferring old show/hide data over the CSS cascade
		restoreDisplay = dataShow && dataShow.display;
		if ( restoreDisplay == null ) {
			restoreDisplay = dataPriv.get( elem, "display" );
		}
		display = jQuery.css( elem, "display" );
		if ( display === "none" ) {
			if ( restoreDisplay ) {
				display = restoreDisplay;
			} else {

				// Get nonempty value(s) by temporarily forcing visibility
				showHide( [ elem ], true );
				restoreDisplay = elem.style.display || restoreDisplay;
				display = jQuery.css( elem, "display" );
				showHide( [ elem ] );
			}
		}

		// Animate inline elements as inline-block
		if ( display === "inline" || display === "inline-block" && restoreDisplay != null ) {
			if ( jQuery.css( elem, "float" ) === "none" ) {

				// Restore the original display value at the end of pure show/hide animations
				if ( !propTween ) {
					anim.done( function() {
						style.display = restoreDisplay;
					} );
					if ( restoreDisplay == null ) {
						display = style.display;
						restoreDisplay = display === "none" ? "" : display;
					}
				}
				style.display = "inline-block";
			}
		}
	}

	if ( opts.overflow ) {
		style.overflow = "hidden";
		anim.always( function() {
			style.overflow = opts.overflow[ 0 ];
			style.overflowX = opts.overflow[ 1 ];
			style.overflowY = opts.overflow[ 2 ];
		} );
	}

	// Implement show/hide animations
	propTween = false;
	for ( prop in orig ) {

		// General show/hide setup for this element animation
		if ( !propTween ) {
			if ( dataShow ) {
				if ( "hidden" in dataShow ) {
					hidden = dataShow.hidden;
				}
			} else {
				dataShow = dataPriv.access( elem, "fxshow", { display: restoreDisplay } );
			}

			// Store hidden/visible for toggle so `.stop().toggle()` "reverses"
			if ( toggle ) {
				dataShow.hidden = !hidden;
			}

			// Show elements before animating them
			if ( hidden ) {
				showHide( [ elem ], true );
			}

			/* eslint-disable no-loop-func */

			anim.done( function() {

				/* eslint-enable no-loop-func */

				// The final step of a "hide" animation is actually hiding the element
				if ( !hidden ) {
					showHide( [ elem ] );
				}
				dataPriv.remove( elem, "fxshow" );
				for ( prop in orig ) {
					jQuery.style( elem, prop, orig[ prop ] );
				}
			} );
		}

		// Per-property setup
		propTween = createTween( hidden ? dataShow[ prop ] : 0, prop, anim );
		if ( !( prop in dataShow ) ) {
			dataShow[ prop ] = propTween.start;
			if ( hidden ) {
				propTween.end = propTween.start;
				propTween.start = 0;
			}
		}
	}
}

function propFilter( props, specialEasing ) {
	var index, name, easing, value, hooks;

	// camelCase, specialEasing and expand cssHook pass
	for ( index in props ) {
		name = camelCase( index );
		easing = specialEasing[ name ];
		value = props[ index ];
		if ( Array.isArray( value ) ) {
			easing = value[ 1 ];
			value = props[ index ] = value[ 0 ];
		}

		if ( index !== name ) {
			props[ name ] = value;
			delete props[ index ];
		}

		hooks = jQuery.cssHooks[ name ];
		if ( hooks && "expand" in hooks ) {
			value = hooks.expand( value );
			delete props[ name ];

			// Not quite $.extend, this won't overwrite existing keys.
			// Reusing 'index' because we have the correct "name"
			for ( index in value ) {
				if ( !( index in props ) ) {
					props[ index ] = value[ index ];
					specialEasing[ index ] = easing;
				}
			}
		} else {
			specialEasing[ name ] = easing;
		}
	}
}

function Animation( elem, properties, options ) {
	var result,
		stopped,
		index = 0,
		length = Animation.prefilters.length,
		deferred = jQuery.Deferred().always( function() {

			// Don't match elem in the :animated selector
			delete tick.elem;
		} ),
		tick = function() {
			if ( stopped ) {
				return false;
			}
			var currentTime = fxNow || createFxNow(),
				remaining = Math.max( 0, animation.startTime + animation.duration - currentTime ),

				// Support: Android 2.3 only
				// Archaic crash bug won't allow us to use `1 - ( 0.5 || 0 )` (#12497)
				temp = remaining / animation.duration || 0,
				percent = 1 - temp,
				index = 0,
				length = animation.tweens.length;

			for ( ; index < length; index++ ) {
				animation.tweens[ index ].run( percent );
			}

			deferred.notifyWith( elem, [ animation, percent, remaining ] );

			// If there's more to do, yield
			if ( percent < 1 && length ) {
				return remaining;
			}

			// If this was an empty animation, synthesize a final progress notification
			if ( !length ) {
				deferred.notifyWith( elem, [ animation, 1, 0 ] );
			}

			// Resolve the animation and report its conclusion
			deferred.resolveWith( elem, [ animation ] );
			return false;
		},
		animation = deferred.promise( {
			elem: elem,
			props: jQuery.extend( {}, properties ),
			opts: jQuery.extend( true, {
				specialEasing: {},
				easing: jQuery.easing._default
			}, options ),
			originalProperties: properties,
			originalOptions: options,
			startTime: fxNow || createFxNow(),
			duration: options.duration,
			tweens: [],
			createTween: function( prop, end ) {
				var tween = jQuery.Tween( elem, animation.opts, prop, end,
					animation.opts.specialEasing[ prop ] || animation.opts.easing );
				animation.tweens.push( tween );
				return tween;
			},
			stop: function( gotoEnd ) {
				var index = 0,

					// If we are going to the end, we want to run all the tweens
					// otherwise we skip this part
					length = gotoEnd ? animation.tweens.length : 0;
				if ( stopped ) {
					return this;
				}
				stopped = true;
				for ( ; index < length; index++ ) {
					animation.tweens[ index ].run( 1 );
				}

				// Resolve when we played the last frame; otherwise, reject
				if ( gotoEnd ) {
					deferred.notifyWith( elem, [ animation, 1, 0 ] );
					deferred.resolveWith( elem, [ animation, gotoEnd ] );
				} else {
					deferred.rejectWith( elem, [ animation, gotoEnd ] );
				}
				return this;
			}
		} ),
		props = animation.props;

	propFilter( props, animation.opts.specialEasing );

	for ( ; index < length; index++ ) {
		result = Animation.prefilters[ index ].call( animation, elem, props, animation.opts );
		if ( result ) {
			if ( isFunction( result.stop ) ) {
				jQuery._queueHooks( animation.elem, animation.opts.queue ).stop =
					result.stop.bind( result );
			}
			return result;
		}
	}

	jQuery.map( props, createTween, animation );

	if ( isFunction( animation.opts.start ) ) {
		animation.opts.start.call( elem, animation );
	}

	// Attach callbacks from options
	animation
		.progress( animation.opts.progress )
		.done( animation.opts.done, animation.opts.complete )
		.fail( animation.opts.fail )
		.always( animation.opts.always );

	jQuery.fx.timer(
		jQuery.extend( tick, {
			elem: elem,
			anim: animation,
			queue: animation.opts.queue
		} )
	);

	return animation;
}

jQuery.Animation = jQuery.extend( Animation, {

	tweeners: {
		"*": [ function( prop, value ) {
			var tween = this.createTween( prop, value );
			adjustCSS( tween.elem, prop, rcssNum.exec( value ), tween );
			return tween;
		} ]
	},

	tweener: function( props, callback ) {
		if ( isFunction( props ) ) {
			callback = props;
			props = [ "*" ];
		} else {
			props = props.match( rnothtmlwhite );
		}

		var prop,
			index = 0,
			length = props.length;

		for ( ; index < length; index++ ) {
			prop = props[ index ];
			Animation.tweeners[ prop ] = Animation.tweeners[ prop ] || [];
			Animation.tweeners[ prop ].unshift( callback );
		}
	},

	prefilters: [ defaultPrefilter ],

	prefilter: function( callback, prepend ) {
		if ( prepend ) {
			Animation.prefilters.unshift( callback );
		} else {
			Animation.prefilters.push( callback );
		}
	}
} );

jQuery.speed = function( speed, easing, fn ) {
	var opt = speed && typeof speed === "object" ? jQuery.extend( {}, speed ) : {
		complete: fn || !fn && easing ||
			isFunction( speed ) && speed,
		duration: speed,
		easing: fn && easing || easing && !isFunction( easing ) && easing
	};

	// Go to the end state if fx are off
	if ( jQuery.fx.off ) {
		opt.duration = 0;

	} else {
		if ( typeof opt.duration !== "number" ) {
			if ( opt.duration in jQuery.fx.speeds ) {
				opt.duration = jQuery.fx.speeds[ opt.duration ];

			} else {
				opt.duration = jQuery.fx.speeds._default;
			}
		}
	}

	// Normalize opt.queue - true/undefined/null -> "fx"
	if ( opt.queue == null || opt.queue === true ) {
		opt.queue = "fx";
	}

	// Queueing
	opt.old = opt.complete;

	opt.complete = function() {
		if ( isFunction( opt.old ) ) {
			opt.old.call( this );
		}

		if ( opt.queue ) {
			jQuery.dequeue( this, opt.queue );
		}
	};

	return opt;
};

jQuery.fn.extend( {
	fadeTo: function( speed, to, easing, callback ) {

		// Show any hidden elements after setting opacity to 0
		return this.filter( isHiddenWithinTree ).css( "opacity", 0 ).show()

			// Animate to the value specified
			.end().animate( { opacity: to }, speed, easing, callback );
	},
	animate: function( prop, speed, easing, callback ) {
		var empty = jQuery.isEmptyObject( prop ),
			optall = jQuery.speed( speed, easing, callback ),
			doAnimation = function() {

				// Operate on a copy of prop so per-property easing won't be lost
				var anim = Animation( this, jQuery.extend( {}, prop ), optall );

				// Empty animations, or finishing resolves immediately
				if ( empty || dataPriv.get( this, "finish" ) ) {
					anim.stop( true );
				}
			};

		doAnimation.finish = doAnimation;

		return empty || optall.queue === false ?
			this.each( doAnimation ) :
			this.queue( optall.queue, doAnimation );
	},
	stop: function( type, clearQueue, gotoEnd ) {
		var stopQueue = function( hooks ) {
			var stop = hooks.stop;
			delete hooks.stop;
			stop( gotoEnd );
		};

		if ( typeof type !== "string" ) {
			gotoEnd = clearQueue;
			clearQueue = type;
			type = undefined;
		}
		if ( clearQueue ) {
			this.queue( type || "fx", [] );
		}

		return this.each( function() {
			var dequeue = true,
				index = type != null && type + "queueHooks",
				timers = jQuery.timers,
				data = dataPriv.get( this );

			if ( index ) {
				if ( data[ index ] && data[ index ].stop ) {
					stopQueue( data[ index ] );
				}
			} else {
				for ( index in data ) {
					if ( data[ index ] && data[ index ].stop && rrun.test( index ) ) {
						stopQueue( data[ index ] );
					}
				}
			}

			for ( index = timers.length; index--; ) {
				if ( timers[ index ].elem === this &&
					( type == null || timers[ index ].queue === type ) ) {

					timers[ index ].anim.stop( gotoEnd );
					dequeue = false;
					timers.splice( index, 1 );
				}
			}

			// Start the next in the queue if the last step wasn't forced.
			// Timers currently will call their complete callbacks, which
			// will dequeue but only if they were gotoEnd.
			if ( dequeue || !gotoEnd ) {
				jQuery.dequeue( this, type );
			}
		} );
	},
	finish: function( type ) {
		if ( type !== false ) {
			type = type || "fx";
		}
		return this.each( function() {
			var index,
				data = dataPriv.get( this ),
				queue = data[ type + "queue" ],
				hooks = data[ type + "queueHooks" ],
				timers = jQuery.timers,
				length = queue ? queue.length : 0;

			// Enable finishing flag on private data
			data.finish = true;

			// Empty the queue first
			jQuery.queue( this, type, [] );

			if ( hooks && hooks.stop ) {
				hooks.stop.call( this, true );
			}

			// Look for any active animations, and finish them
			for ( index = timers.length; index--; ) {
				if ( timers[ index ].elem === this && timers[ index ].queue === type ) {
					timers[ index ].anim.stop( true );
					timers.splice( index, 1 );
				}
			}

			// Look for any animations in the old queue and finish them
			for ( index = 0; index < length; index++ ) {
				if ( queue[ index ] && queue[ index ].finish ) {
					queue[ index ].finish.call( this );
				}
			}

			// Turn off finishing flag
			delete data.finish;
		} );
	}
} );

jQuery.each( [ "toggle", "show", "hide" ], function( _i, name ) {
	var cssFn = jQuery.fn[ name ];
	jQuery.fn[ name ] = function( speed, easing, callback ) {
		return speed == null || typeof speed === "boolean" ?
			cssFn.apply( this, arguments ) :
			this.animate( genFx( name, true ), speed, easing, callback );
	};
} );

// Generate shortcuts for custom animations
jQuery.each( {
	slideDown: genFx( "show" ),
	slideUp: genFx( "hide" ),
	slideToggle: genFx( "toggle" ),
	fadeIn: { opacity: "show" },
	fadeOut: { opacity: "hide" },
	fadeToggle: { opacity: "toggle" }
}, function( name, props ) {
	jQuery.fn[ name ] = function( speed, easing, callback ) {
		return this.animate( props, speed, easing, callback );
	};
} );

jQuery.timers = [];
jQuery.fx.tick = function() {
	var timer,
		i = 0,
		timers = jQuery.timers;

	fxNow = Date.now();

	for ( ; i < timers.length; i++ ) {
		timer = timers[ i ];

		// Run the timer and safely remove it when done (allowing for external removal)
		if ( !timer() && timers[ i ] === timer ) {
			timers.splice( i--, 1 );
		}
	}

	if ( !timers.length ) {
		jQuery.fx.stop();
	}
	fxNow = undefined;
};

jQuery.fx.timer = function( timer ) {
	jQuery.timers.push( timer );
	jQuery.fx.start();
};

jQuery.fx.interval = 13;
jQuery.fx.start = function() {
	if ( inProgress ) {
		return;
	}

	inProgress = true;
	schedule();
};

jQuery.fx.stop = function() {
	inProgress = null;
};

jQuery.fx.speeds = {
	slow: 600,
	fast: 200,

	// Default speed
	_default: 400
};


// Based off of the plugin by Clint Helfers, with permission.
// https://web.archive.org/web/20100324014747/http://blindsignals.com/index.php/2009/07/jquery-delay/
jQuery.fn.delay = function( time, type ) {
	time = jQuery.fx ? jQuery.fx.speeds[ time ] || time : time;
	type = type || "fx";

	return this.queue( type, function( next, hooks ) {
		var timeout = window.setTimeout( next, time );
		hooks.stop = function() {
			window.clearTimeout( timeout );
		};
	} );
};


( function() {
	var input = document.createElement( "input" ),
		select = document.createElement( "select" ),
		opt = select.appendChild( document.createElement( "option" ) );

	input.type = "checkbox";

	// Support: Android <=4.3 only
	// Default value for a checkbox should be "on"
	support.checkOn = input.value !== "";

	// Support: IE <=11 only
	// Must access selectedIndex to make default options select
	support.optSelected = opt.selected;

	// Support: IE <=11 only
	// An input loses its value after becoming a radio
	input = document.createElement( "input" );
	input.value = "t";
	input.type = "radio";
	support.radioValue = input.value === "t";
} )();


var boolHook,
	attrHandle = jQuery.expr.attrHandle;

jQuery.fn.extend( {
	attr: function( name, value ) {
		return access( this, jQuery.attr, name, value, arguments.length > 1 );
	},

	removeAttr: function( name ) {
		return this.each( function() {
			jQuery.removeAttr( this, name );
		} );
	}
} );

jQuery.extend( {
	attr: function( elem, name, value ) {
		var ret, hooks,
			nType = elem.nodeType;

		// Don't get/set attributes on text, comment and attribute nodes
		if ( nType === 3 || nType === 8 || nType === 2 ) {
			return;
		}

		// Fallback to prop when attributes are not supported
		if ( typeof elem.getAttribute === "undefined" ) {
			return jQuery.prop( elem, name, value );
		}

		// Attribute hooks are determined by the lowercase version
		// Grab necessary hook if one is defined
		if ( nType !== 1 || !jQuery.isXMLDoc( elem ) ) {
			hooks = jQuery.attrHooks[ name.toLowerCase() ] ||
				( jQuery.expr.match.bool.test( name ) ? boolHook : undefined );
		}

		if ( value !== undefined ) {
			if ( value === null ) {
				jQuery.removeAttr( elem, name );
				return;
			}

			if ( hooks && "set" in hooks &&
				( ret = hooks.set( elem, value, name ) ) !== undefined ) {
				return ret;
			}

			elem.setAttribute( name, value + "" );
			return value;
		}

		if ( hooks && "get" in hooks && ( ret = hooks.get( elem, name ) ) !== null ) {
			return ret;
		}

		ret = jQuery.find.attr( elem, name );

		// Non-existent attributes return null, we normalize to undefined
		return ret == null ? undefined : ret;
	},

	attrHooks: {
		type: {
			set: function( elem, value ) {
				if ( !support.radioValue && value === "radio" &&
					nodeName( elem, "input" ) ) {
					var val = elem.value;
					elem.setAttribute( "type", value );
					if ( val ) {
						elem.value = val;
					}
					return value;
				}
			}
		}
	},

	removeAttr: function( elem, value ) {
		var name,
			i = 0,

			// Attribute names can contain non-HTML whitespace characters
			// https://html.spec.whatwg.org/multipage/syntax.html#attributes-2
			attrNames = value && value.match( rnothtmlwhite );

		if ( attrNames && elem.nodeType === 1 ) {
			while ( ( name = attrNames[ i++ ] ) ) {
				elem.removeAttribute( name );
			}
		}
	}
} );

// Hooks for boolean attributes
boolHook = {
	set: function( elem, value, name ) {
		if ( value === false ) {

			// Remove boolean attributes when set to false
			jQuery.removeAttr( elem, name );
		} else {
			elem.setAttribute( name, name );
		}
		return name;
	}
};

jQuery.each( jQuery.expr.match.bool.source.match( /\w+/g ), function( _i, name ) {
	var getter = attrHandle[ name ] || jQuery.find.attr;

	attrHandle[ name ] = function( elem, name, isXML ) {
		var ret, handle,
			lowercaseName = name.toLowerCase();

		if ( !isXML ) {

			// Avoid an infinite loop by temporarily removing this function from the getter
			handle = attrHandle[ lowercaseName ];
			attrHandle[ lowercaseName ] = ret;
			ret = getter( elem, name, isXML ) != null ?
				lowercaseName :
				null;
			attrHandle[ lowercaseName ] = handle;
		}
		return ret;
	};
} );




var rfocusable = /^(?:input|select|textarea|button)$/i,
	rclickable = /^(?:a|area)$/i;

jQuery.fn.extend( {
	prop: function( name, value ) {
		return access( this, jQuery.prop, name, value, arguments.length > 1 );
	},

	removeProp: function( name ) {
		return this.each( function() {
			delete this[ jQuery.propFix[ name ] || name ];
		} );
	}
} );

jQuery.extend( {
	prop: function( elem, name, value ) {
		var ret, hooks,
			nType = elem.nodeType;

		// Don't get/set properties on text, comment and attribute nodes
		if ( nType === 3 || nType === 8 || nType === 2 ) {
			return;
		}

		if ( nType !== 1 || !jQuery.isXMLDoc( elem ) ) {

			// Fix name and attach hooks
			name = jQuery.propFix[ name ] || name;
			hooks = jQuery.propHooks[ name ];
		}

		if ( value !== undefined ) {
			if ( hooks && "set" in hooks &&
				( ret = hooks.set( elem, value, name ) ) !== undefined ) {
				return ret;
			}

			return ( elem[ name ] = value );
		}

		if ( hooks && "get" in hooks && ( ret = hooks.get( elem, name ) ) !== null ) {
			return ret;
		}

		return elem[ name ];
	},

	propHooks: {
		tabIndex: {
			get: function( elem ) {

				// Support: IE <=9 - 11 only
				// elem.tabIndex doesn't always return the
				// correct value when it hasn't been explicitly set
				// https://web.archive.org/web/20141116233347/http://fluidproject.org/blog/2008/01/09/getting-setting-and-removing-tabindex-values-with-javascript/
				// Use proper attribute retrieval(#12072)
				var tabindex = jQuery.find.attr( elem, "tabindex" );

				if ( tabindex ) {
					return parseInt( tabindex, 10 );
				}

				if (
					rfocusable.test( elem.nodeName ) ||
					rclickable.test( elem.nodeName ) &&
					elem.href
				) {
					return 0;
				}

				return -1;
			}
		}
	},

	propFix: {
		"for": "htmlFor",
		"class": "className"
	}
} );

// Support: IE <=11 only
// Accessing the selectedIndex property
// forces the browser to respect setting selected
// on the option
// The getter ensures a default option is selected
// when in an optgroup
// eslint rule "no-unused-expressions" is disabled for this code
// since it considers such accessions noop
if ( !support.optSelected ) {
	jQuery.propHooks.selected = {
		get: function( elem ) {

			/* eslint no-unused-expressions: "off" */

			var parent = elem.parentNode;
			if ( parent && parent.parentNode ) {
				parent.parentNode.selectedIndex;
			}
			return null;
		},
		set: function( elem ) {

			/* eslint no-unused-expressions: "off" */

			var parent = elem.parentNode;
			if ( parent ) {
				parent.selectedIndex;

				if ( parent.parentNode ) {
					parent.parentNode.selectedIndex;
				}
			}
		}
	};
}

jQuery.each( [
	"tabIndex",
	"readOnly",
	"maxLength",
	"cellSpacing",
	"cellPadding",
	"rowSpan",
	"colSpan",
	"useMap",
	"frameBorder",
	"contentEditable"
], function() {
	jQuery.propFix[ this.toLowerCase() ] = this;
} );




	// Strip and collapse whitespace according to HTML spec
	// https://infra.spec.whatwg.org/#strip-and-collapse-ascii-whitespace
	function stripAndCollapse( value ) {
		var tokens = value.match( rnothtmlwhite ) || [];
		return tokens.join( " " );
	}


function getClass( elem ) {
	return elem.getAttribute && elem.getAttribute( "class" ) || "";
}

function classesToArray( value ) {
	if ( Array.isArray( value ) ) {
		return value;
	}
	if ( typeof value === "string" ) {
		return value.match( rnothtmlwhite ) || [];
	}
	return [];
}

jQuery.fn.extend( {
	addClass: function( value ) {
		var classes, elem, cur, curValue, clazz, j, finalValue,
			i = 0;

		if ( isFunction( value ) ) {
			return this.each( function( j ) {
				jQuery( this ).addClass( value.call( this, j, getClass( this ) ) );
			} );
		}

		classes = classesToArray( value );

		if ( classes.length ) {
			while ( ( elem = this[ i++ ] ) ) {
				curValue = getClass( elem );
				cur = elem.nodeType === 1 && ( " " + stripAndCollapse( curValue ) + " " );

				if ( cur ) {
					j = 0;
					while ( ( clazz = classes[ j++ ] ) ) {
						if ( cur.indexOf( " " + clazz + " " ) < 0 ) {
							cur += clazz + " ";
						}
					}

					// Only assign if different to avoid unneeded rendering.
					finalValue = stripAndCollapse( cur );
					if ( curValue !== finalValue ) {
						elem.setAttribute( "class", finalValue );
					}
				}
			}
		}

		return this;
	},

	removeClass: function( value ) {
		var classes, elem, cur, curValue, clazz, j, finalValue,
			i = 0;

		if ( isFunction( value ) ) {
			return this.each( function( j ) {
				jQuery( this ).removeClass( value.call( this, j, getClass( this ) ) );
			} );
		}

		if ( !arguments.length ) {
			return this.attr( "class", "" );
		}

		classes = classesToArray( value );

		if ( classes.length ) {
			while ( ( elem = this[ i++ ] ) ) {
				curValue = getClass( elem );

				// This expression is here for better compressibility (see addClass)
				cur = elem.nodeType === 1 && ( " " + stripAndCollapse( curValue ) + " " );

				if ( cur ) {
					j = 0;
					while ( ( clazz = classes[ j++ ] ) ) {

						// Remove *all* instances
						while ( cur.indexOf( " " + clazz + " " ) > -1 ) {
							cur = cur.replace( " " + clazz + " ", " " );
						}
					}

					// Only assign if different to avoid unneeded rendering.
					finalValue = stripAndCollapse( cur );
					if ( curValue !== finalValue ) {
						elem.setAttribute( "class", finalValue );
					}
				}
			}
		}

		return this;
	},

	toggleClass: function( value, stateVal ) {
		var type = typeof value,
			isValidValue = type === "string" || Array.isArray( value );

		if ( typeof stateVal === "boolean" && isValidValue ) {
			return stateVal ? this.addClass( value ) : this.removeClass( value );
		}

		if ( isFunction( value ) ) {
			return this.each( function( i ) {
				jQuery( this ).toggleClass(
					value.call( this, i, getClass( this ), stateVal ),
					stateVal
				);
			} );
		}

		return this.each( function() {
			var className, i, self, classNames;

			if ( isValidValue ) {

				// Toggle individual class names
				i = 0;
				self = jQuery( this );
				classNames = classesToArray( value );

				while ( ( className = classNames[ i++ ] ) ) {

					// Check each className given, space separated list
					if ( self.hasClass( className ) ) {
						self.removeClass( className );
					} else {
						self.addClass( className );
					}
				}

			// Toggle whole class name
			} else if ( value === undefined || type === "boolean" ) {
				className = getClass( this );
				if ( className ) {

					// Store className if set
					dataPriv.set( this, "__className__", className );
				}

				// If the element has a class name or if we're passed `false`,
				// then remove the whole classname (if there was one, the above saved it).
				// Otherwise bring back whatever was previously saved (if anything),
				// falling back to the empty string if nothing was stored.
				if ( this.setAttribute ) {
					this.setAttribute( "class",
						className || value === false ?
							"" :
							dataPriv.get( this, "__className__" ) || ""
					);
				}
			}
		} );
	},

	hasClass: function( selector ) {
		var className, elem,
			i = 0;

		className = " " + selector + " ";
		while ( ( elem = this[ i++ ] ) ) {
			if ( elem.nodeType === 1 &&
				( " " + stripAndCollapse( getClass( elem ) ) + " " ).indexOf( className ) > -1 ) {
				return true;
			}
		}

		return false;
	}
} );




var rreturn = /\r/g;

jQuery.fn.extend( {
	val: function( value ) {
		var hooks, ret, valueIsFunction,
			elem = this[ 0 ];

		if ( !arguments.length ) {
			if ( elem ) {
				hooks = jQuery.valHooks[ elem.type ] ||
					jQuery.valHooks[ elem.nodeName.toLowerCase() ];

				if ( hooks &&
					"get" in hooks &&
					( ret = hooks.get( elem, "value" ) ) !== undefined
				) {
					return ret;
				}

				ret = elem.value;

				// Handle most common string cases
				if ( typeof ret === "string" ) {
					return ret.replace( rreturn, "" );
				}

				// Handle cases where value is null/undef or number
				return ret == null ? "" : ret;
			}

			return;
		}

		valueIsFunction = isFunction( value );

		return this.each( function( i ) {
			var val;

			if ( this.nodeType !== 1 ) {
				return;
			}

			if ( valueIsFunction ) {
				val = value.call( this, i, jQuery( this ).val() );
			} else {
				val = value;
			}

			// Treat null/undefined as ""; convert numbers to string
			if ( val == null ) {
				val = "";

			} else if ( typeof val === "number" ) {
				val += "";

			} else if ( Array.isArray( val ) ) {
				val = jQuery.map( val, function( value ) {
					return value == null ? "" : value + "";
				} );
			}

			hooks = jQuery.valHooks[ this.type ] || jQuery.valHooks[ this.nodeName.toLowerCase() ];

			// If set returns undefined, fall back to normal setting
			if ( !hooks || !( "set" in hooks ) || hooks.set( this, val, "value" ) === undefined ) {
				this.value = val;
			}
		} );
	}
} );

jQuery.extend( {
	valHooks: {
		option: {
			get: function( elem ) {

				var val = jQuery.find.attr( elem, "value" );
				return val != null ?
					val :

					// Support: IE <=10 - 11 only
					// option.text throws exceptions (#14686, #14858)
					// Strip and collapse whitespace
					// https://html.spec.whatwg.org/#strip-and-collapse-whitespace
					stripAndCollapse( jQuery.text( elem ) );
			}
		},
		select: {
			get: function( elem ) {
				var value, option, i,
					options = elem.options,
					index = elem.selectedIndex,
					one = elem.type === "select-one",
					values = one ? null : [],
					max = one ? index + 1 : options.length;

				if ( index < 0 ) {
					i = max;

				} else {
					i = one ? index : 0;
				}

				// Loop through all the selected options
				for ( ; i < max; i++ ) {
					option = options[ i ];

					// Support: IE <=9 only
					// IE8-9 doesn't update selected after form reset (#2551)
					if ( ( option.selected || i === index ) &&

							// Don't return options that are disabled or in a disabled optgroup
							!option.disabled &&
							( !option.parentNode.disabled ||
								!nodeName( option.parentNode, "optgroup" ) ) ) {

						// Get the specific value for the option
						value = jQuery( option ).val();

						// We don't need an array for one selects
						if ( one ) {
							return value;
						}

						// Multi-Selects return an array
						values.push( value );
					}
				}

				return values;
			},

			set: function( elem, value ) {
				var optionSet, option,
					options = elem.options,
					values = jQuery.makeArray( value ),
					i = options.length;

				while ( i-- ) {
					option = options[ i ];

					/* eslint-disable no-cond-assign */

					if ( option.selected =
						jQuery.inArray( jQuery.valHooks.option.get( option ), values ) > -1
					) {
						optionSet = true;
					}

					/* eslint-enable no-cond-assign */
				}

				// Force browsers to behave consistently when non-matching value is set
				if ( !optionSet ) {
					elem.selectedIndex = -1;
				}
				return values;
			}
		}
	}
} );

// Radios and checkboxes getter/setter
jQuery.each( [ "radio", "checkbox" ], function() {
	jQuery.valHooks[ this ] = {
		set: function( elem, value ) {
			if ( Array.isArray( value ) ) {
				return ( elem.checked = jQuery.inArray( jQuery( elem ).val(), value ) > -1 );
			}
		}
	};
	if ( !support.checkOn ) {
		jQuery.valHooks[ this ].get = function( elem ) {
			return elem.getAttribute( "value" ) === null ? "on" : elem.value;
		};
	}
} );




// Return jQuery for attributes-only inclusion


support.focusin = "onfocusin" in window;


var rfocusMorph = /^(?:focusinfocus|focusoutblur)$/,
	stopPropagationCallback = function( e ) {
		e.stopPropagation();
	};

jQuery.extend( jQuery.event, {

	trigger: function( event, data, elem, onlyHandlers ) {

		var i, cur, tmp, bubbleType, ontype, handle, special, lastElement,
			eventPath = [ elem || document ],
			type = hasOwn.call( event, "type" ) ? event.type : event,
			namespaces = hasOwn.call( event, "namespace" ) ? event.namespace.split( "." ) : [];

		cur = lastElement = tmp = elem = elem || document;

		// Don't do events on text and comment nodes
		if ( elem.nodeType === 3 || elem.nodeType === 8 ) {
			return;
		}

		// focus/blur morphs to focusin/out; ensure we're not firing them right now
		if ( rfocusMorph.test( type + jQuery.event.triggered ) ) {
			return;
		}

		if ( type.indexOf( "." ) > -1 ) {

			// Namespaced trigger; create a regexp to match event type in handle()
			namespaces = type.split( "." );
			type = namespaces.shift();
			namespaces.sort();
		}
		ontype = type.indexOf( ":" ) < 0 && "on" + type;

		// Caller can pass in a jQuery.Event object, Object, or just an event type string
		event = event[ jQuery.expando ] ?
			event :
			new jQuery.Event( type, typeof event === "object" && event );

		// Trigger bitmask: & 1 for native handlers; & 2 for jQuery (always true)
		event.isTrigger = onlyHandlers ? 2 : 3;
		event.namespace = namespaces.join( "." );
		event.rnamespace = event.namespace ?
			new RegExp( "(^|\\.)" + namespaces.join( "\\.(?:.*\\.|)" ) + "(\\.|$)" ) :
			null;

		// Clean up the event in case it is being reused
		event.result = undefined;
		if ( !event.target ) {
			event.target = elem;
		}

		// Clone any incoming data and prepend the event, creating the handler arg list
		data = data == null ?
			[ event ] :
			jQuery.makeArray( data, [ event ] );

		// Allow special events to draw outside the lines
		special = jQuery.event.special[ type ] || {};
		if ( !onlyHandlers && special.trigger && special.trigger.apply( elem, data ) === false ) {
			return;
		}

		// Determine event propagation path in advance, per W3C events spec (#9951)
		// Bubble up to document, then to window; watch for a global ownerDocument var (#9724)
		if ( !onlyHandlers && !special.noBubble && !isWindow( elem ) ) {

			bubbleType = special.delegateType || type;
			if ( !rfocusMorph.test( bubbleType + type ) ) {
				cur = cur.parentNode;
			}
			for ( ; cur; cur = cur.parentNode ) {
				eventPath.push( cur );
				tmp = cur;
			}

			// Only add window if we got to document (e.g., not plain obj or detached DOM)
			if ( tmp === ( elem.ownerDocument || document ) ) {
				eventPath.push( tmp.defaultView || tmp.parentWindow || window );
			}
		}

		// Fire handlers on the event path
		i = 0;
		while ( ( cur = eventPath[ i++ ] ) && !event.isPropagationStopped() ) {
			lastElement = cur;
			event.type = i > 1 ?
				bubbleType :
				special.bindType || type;

			// jQuery handler
			handle = ( dataPriv.get( cur, "events" ) || Object.create( null ) )[ event.type ] &&
				dataPriv.get( cur, "handle" );
			if ( handle ) {
				handle.apply( cur, data );
			}

			// Native handler
			handle = ontype && cur[ ontype ];
			if ( handle && handle.apply && acceptData( cur ) ) {
				event.result = handle.apply( cur, data );
				if ( event.result === false ) {
					event.preventDefault();
				}
			}
		}
		event.type = type;

		// If nobody prevented the default action, do it now
		if ( !onlyHandlers && !event.isDefaultPrevented() ) {

			if ( ( !special._default ||
				special._default.apply( eventPath.pop(), data ) === false ) &&
				acceptData( elem ) ) {

				// Call a native DOM method on the target with the same name as the event.
				// Don't do default actions on window, that's where global variables be (#6170)
				if ( ontype && isFunction( elem[ type ] ) && !isWindow( elem ) ) {

					// Don't re-trigger an onFOO event when we call its FOO() method
					tmp = elem[ ontype ];

					if ( tmp ) {
						elem[ ontype ] = null;
					}

					// Prevent re-triggering of the same event, since we already bubbled it above
					jQuery.event.triggered = type;

					if ( event.isPropagationStopped() ) {
						lastElement.addEventListener( type, stopPropagationCallback );
					}

					elem[ type ]();

					if ( event.isPropagationStopped() ) {
						lastElement.removeEventListener( type, stopPropagationCallback );
					}

					jQuery.event.triggered = undefined;

					if ( tmp ) {
						elem[ ontype ] = tmp;
					}
				}
			}
		}

		return event.result;
	},

	// Piggyback on a donor event to simulate a different one
	// Used only for `focus(in | out)` events
	simulate: function( type, elem, event ) {
		var e = jQuery.extend(
			new jQuery.Event(),
			event,
			{
				type: type,
				isSimulated: true
			}
		);

		jQuery.event.trigger( e, null, elem );
	}

} );

jQuery.fn.extend( {

	trigger: function( type, data ) {
		return this.each( function() {
			jQuery.event.trigger( type, data, this );
		} );
	},
	triggerHandler: function( type, data ) {
		var elem = this[ 0 ];
		if ( elem ) {
			return jQuery.event.trigger( type, data, elem, true );
		}
	}
} );


// Support: Firefox <=44
// Firefox doesn't have focus(in | out) events
// Related ticket - https://bugzilla.mozilla.org/show_bug.cgi?id=687787
//
// Support: Chrome <=48 - 49, Safari <=9.0 - 9.1
// focus(in | out) events fire after focus & blur events,
// which is spec violation - http://www.w3.org/TR/DOM-Level-3-Events/#events-focusevent-event-order
// Related ticket - https://bugs.chromium.org/p/chromium/issues/detail?id=449857
if ( !support.focusin ) {
	jQuery.each( { focus: "focusin", blur: "focusout" }, function( orig, fix ) {

		// Attach a single capturing handler on the document while someone wants focusin/focusout
		var handler = function( event ) {
			jQuery.event.simulate( fix, event.target, jQuery.event.fix( event ) );
		};

		jQuery.event.special[ fix ] = {
			setup: function() {

				// Handle: regular nodes (via `this.ownerDocument`), window
				// (via `this.document`) & document (via `this`).
				var doc = this.ownerDocument || this.document || this,
					attaches = dataPriv.access( doc, fix );

				if ( !attaches ) {
					doc.addEventListener( orig, handler, true );
				}
				dataPriv.access( doc, fix, ( attaches || 0 ) + 1 );
			},
			teardown: function() {
				var doc = this.ownerDocument || this.document || this,
					attaches = dataPriv.access( doc, fix ) - 1;

				if ( !attaches ) {
					doc.removeEventListener( orig, handler, true );
					dataPriv.remove( doc, fix );

				} else {
					dataPriv.access( doc, fix, attaches );
				}
			}
		};
	} );
}
var location = window.location;

var nonce = { guid: Date.now() };

var rquery = ( /\?/ );



// Cross-browser xml parsing
jQuery.parseXML = function( data ) {
	var xml, parserErrorElem;
	if ( !data || typeof data !== "string" ) {
		return null;
	}

	// Support: IE 9 - 11 only
	// IE throws on parseFromString with invalid input.
	try {
		xml = ( new window.DOMParser() ).parseFromString( data, "text/xml" );
	} catch ( e ) {}

	parserErrorElem = xml && xml.getElementsByTagName( "parsererror" )[ 0 ];
	if ( !xml || parserErrorElem ) {
		jQuery.error( "Invalid XML: " + (
			parserErrorElem ?
				jQuery.map( parserErrorElem.childNodes, function( el ) {
					return el.textContent;
				} ).join( "\n" ) :
				data
		) );
	}
	return xml;
};


var
	rbracket = /\[\]$/,
	rCRLF = /\r?\n/g,
	rsubmitterTypes = /^(?:submit|button|image|reset|file)$/i,
	rsubmittable = /^(?:input|select|textarea|keygen)/i;

function buildParams( prefix, obj, traditional, add ) {
	var name;

	if ( Array.isArray( obj ) ) {

		// Serialize array item.
		jQuery.each( obj, function( i, v ) {
			if ( traditional || rbracket.test( prefix ) ) {

				// Treat each array item as a scalar.
				add( prefix, v );

			} else {

				// Item is non-scalar (array or object), encode its numeric index.
				buildParams(
					prefix + "[" + ( typeof v === "object" && v != null ? i : "" ) + "]",
					v,
					traditional,
					add
				);
			}
		} );

	} else if ( !traditional && toType( obj ) === "object" ) {

		// Serialize object item.
		for ( name in obj ) {
			buildParams( prefix + "[" + name + "]", obj[ name ], traditional, add );
		}

	} else {

		// Serialize scalar item.
		add( prefix, obj );
	}
}

// Serialize an array of form elements or a set of
// key/values into a query string
jQuery.param = function( a, traditional ) {
	var prefix,
		s = [],
		add = function( key, valueOrFunction ) {

			// If value is a function, invoke it and use its return value
			var value = isFunction( valueOrFunction ) ?
				valueOrFunction() :
				valueOrFunction;

			s[ s.length ] = encodeURIComponent( key ) + "=" +
				encodeURIComponent( value == null ? "" : value );
		};

	if ( a == null ) {
		return "";
	}

	// If an array was passed in, assume that it is an array of form elements.
	if ( Array.isArray( a ) || ( a.jquery && !jQuery.isPlainObject( a ) ) ) {

		// Serialize the form elements
		jQuery.each( a, function() {
			add( this.name, this.value );
		} );

	} else {

		// If traditional, encode the "old" way (the way 1.3.2 or older
		// did it), otherwise encode params recursively.
		for ( prefix in a ) {
			buildParams( prefix, a[ prefix ], traditional, add );
		}
	}

	// Return the resulting serialization
	return s.join( "&" );
};

jQuery.fn.extend( {
	serialize: function() {
		return jQuery.param( this.serializeArray() );
	},
	serializeArray: function() {
		return this.map( function() {

			// Can add propHook for "elements" to filter or add form elements
			var elements = jQuery.prop( this, "elements" );
			return elements ? jQuery.makeArray( elements ) : this;
		} ).filter( function() {
			var type = this.type;

			// Use .is( ":disabled" ) so that fieldset[disabled] works
			return this.name && !jQuery( this ).is( ":disabled" ) &&
				rsubmittable.test( this.nodeName ) && !rsubmitterTypes.test( type ) &&
				( this.checked || !rcheckableType.test( type ) );
		} ).map( function( _i, elem ) {
			var val = jQuery( this ).val();

			if ( val == null ) {
				return null;
			}

			if ( Array.isArray( val ) ) {
				return jQuery.map( val, function( val ) {
					return { name: elem.name, value: val.replace( rCRLF, "\r\n" ) };
				} );
			}

			return { name: elem.name, value: val.replace( rCRLF, "\r\n" ) };
		} ).get();
	}
} );


var
	r20 = /%20/g,
	rhash = /#.*$/,
	rantiCache = /([?&])_=[^&]*/,
	rheaders = /^(.*?):[ \t]*([^\r\n]*)$/mg,

	// #7653, #8125, #8152: local protocol detection
	rlocalProtocol = /^(?:about|app|app-storage|.+-extension|file|res|widget):$/,
	rnoContent = /^(?:GET|HEAD)$/,
	rprotocol = /^\/\//,

	/* Prefilters
	 * 1) They are useful to introduce custom dataTypes (see ajax/jsonp.js for an example)
	 * 2) These are called:
	 *    - BEFORE asking for a transport
	 *    - AFTER param serialization (s.data is a string if s.processData is true)
	 * 3) key is the dataType
	 * 4) the catchall symbol "*" can be used
	 * 5) execution will start with transport dataType and THEN continue down to "*" if needed
	 */
	prefilters = {},

	/* Transports bindings
	 * 1) key is the dataType
	 * 2) the catchall symbol "*" can be used
	 * 3) selection will start with transport dataType and THEN go to "*" if needed
	 */
	transports = {},

	// Avoid comment-prolog char sequence (#10098); must appease lint and evade compression
	allTypes = "*/".concat( "*" ),

	// Anchor tag for parsing the document origin
	originAnchor = document.createElement( "a" );

originAnchor.href = location.href;

// Base "constructor" for jQuery.ajaxPrefilter and jQuery.ajaxTransport
function addToPrefiltersOrTransports( structure ) {

	// dataTypeExpression is optional and defaults to "*"
	return function( dataTypeExpression, func ) {

		if ( typeof dataTypeExpression !== "string" ) {
			func = dataTypeExpression;
			dataTypeExpression = "*";
		}

		var dataType,
			i = 0,
			dataTypes = dataTypeExpression.toLowerCase().match( rnothtmlwhite ) || [];

		if ( isFunction( func ) ) {

			// For each dataType in the dataTypeExpression
			while ( ( dataType = dataTypes[ i++ ] ) ) {

				// Prepend if requested
				if ( dataType[ 0 ] === "+" ) {
					dataType = dataType.slice( 1 ) || "*";
					( structure[ dataType ] = structure[ dataType ] || [] ).unshift( func );

				// Otherwise append
				} else {
					( structure[ dataType ] = structure[ dataType ] || [] ).push( func );
				}
			}
		}
	};
}

// Base inspection function for prefilters and transports
function inspectPrefiltersOrTransports( structure, options, originalOptions, jqXHR ) {

	var inspected = {},
		seekingTransport = ( structure === transports );

	function inspect( dataType ) {
		var selected;
		inspected[ dataType ] = true;
		jQuery.each( structure[ dataType ] || [], function( _, prefilterOrFactory ) {
			var dataTypeOrTransport = prefilterOrFactory( options, originalOptions, jqXHR );
			if ( typeof dataTypeOrTransport === "string" &&
				!seekingTransport && !inspected[ dataTypeOrTransport ] ) {

				options.dataTypes.unshift( dataTypeOrTransport );
				inspect( dataTypeOrTransport );
				return false;
			} else if ( seekingTransport ) {
				return !( selected = dataTypeOrTransport );
			}
		} );
		return selected;
	}

	return inspect( options.dataTypes[ 0 ] ) || !inspected[ "*" ] && inspect( "*" );
}

// A special extend for ajax options
// that takes "flat" options (not to be deep extended)
// Fixes #9887
function ajaxExtend( target, src ) {
	var key, deep,
		flatOptions = jQuery.ajaxSettings.flatOptions || {};

	for ( key in src ) {
		if ( src[ key ] !== undefined ) {
			( flatOptions[ key ] ? target : ( deep || ( deep = {} ) ) )[ key ] = src[ key ];
		}
	}
	if ( deep ) {
		jQuery.extend( true, target, deep );
	}

	return target;
}

/* Handles responses to an ajax request:
 * - finds the right dataType (mediates between content-type and expected dataType)
 * - returns the corresponding response
 */
function ajaxHandleResponses( s, jqXHR, responses ) {

	var ct, type, finalDataType, firstDataType,
		contents = s.contents,
		dataTypes = s.dataTypes;

	// Remove auto dataType and get content-type in the process
	while ( dataTypes[ 0 ] === "*" ) {
		dataTypes.shift();
		if ( ct === undefined ) {
			ct = s.mimeType || jqXHR.getResponseHeader( "Content-Type" );
		}
	}

	// Check if we're dealing with a known content-type
	if ( ct ) {
		for ( type in contents ) {
			if ( contents[ type ] && contents[ type ].test( ct ) ) {
				dataTypes.unshift( type );
				break;
			}
		}
	}

	// Check to see if we have a response for the expected dataType
	if ( dataTypes[ 0 ] in responses ) {
		finalDataType = dataTypes[ 0 ];
	} else {

		// Try convertible dataTypes
		for ( type in responses ) {
			if ( !dataTypes[ 0 ] || s.converters[ type + " " + dataTypes[ 0 ] ] ) {
				finalDataType = type;
				break;
			}
			if ( !firstDataType ) {
				firstDataType = type;
			}
		}

		// Or just use first one
		finalDataType = finalDataType || firstDataType;
	}

	// If we found a dataType
	// We add the dataType to the list if needed
	// and return the corresponding response
	if ( finalDataType ) {
		if ( finalDataType !== dataTypes[ 0 ] ) {
			dataTypes.unshift( finalDataType );
		}
		return responses[ finalDataType ];
	}
}

/* Chain conversions given the request and the original response
 * Also sets the responseXXX fields on the jqXHR instance
 */
function ajaxConvert( s, response, jqXHR, isSuccess ) {
	var conv2, current, conv, tmp, prev,
		converters = {},

		// Work with a copy of dataTypes in case we need to modify it for conversion
		dataTypes = s.dataTypes.slice();

	// Create converters map with lowercased keys
	if ( dataTypes[ 1 ] ) {
		for ( conv in s.converters ) {
			converters[ conv.toLowerCase() ] = s.converters[ conv ];
		}
	}

	current = dataTypes.shift();

	// Convert to each sequential dataType
	while ( current ) {

		if ( s.responseFields[ current ] ) {
			jqXHR[ s.responseFields[ current ] ] = response;
		}

		// Apply the dataFilter if provided
		if ( !prev && isSuccess && s.dataFilter ) {
			response = s.dataFilter( response, s.dataType );
		}

		prev = current;
		current = dataTypes.shift();

		if ( current ) {

			// There's only work to do if current dataType is non-auto
			if ( current === "*" ) {

				current = prev;

			// Convert response if prev dataType is non-auto and differs from current
			} else if ( prev !== "*" && prev !== current ) {

				// Seek a direct converter
				conv = converters[ prev + " " + current ] || converters[ "* " + current ];

				// If none found, seek a pair
				if ( !conv ) {
					for ( conv2 in converters ) {

						// If conv2 outputs current
						tmp = conv2.split( " " );
						if ( tmp[ 1 ] === current ) {

							// If prev can be converted to accepted input
							conv = converters[ prev + " " + tmp[ 0 ] ] ||
								converters[ "* " + tmp[ 0 ] ];
							if ( conv ) {

								// Condense equivalence converters
								if ( conv === true ) {
									conv = converters[ conv2 ];

								// Otherwise, insert the intermediate dataType
								} else if ( converters[ conv2 ] !== true ) {
									current = tmp[ 0 ];
									dataTypes.unshift( tmp[ 1 ] );
								}
								break;
							}
						}
					}
				}

				// Apply converter (if not an equivalence)
				if ( conv !== true ) {

					// Unless errors are allowed to bubble, catch and return them
					if ( conv && s.throws ) {
						response = conv( response );
					} else {
						try {
							response = conv( response );
						} catch ( e ) {
							return {
								state: "parsererror",
								error: conv ? e : "No conversion from " + prev + " to " + current
							};
						}
					}
				}
			}
		}
	}

	return { state: "success", data: response };
}

jQuery.extend( {

	// Counter for holding the number of active queries
	active: 0,

	// Last-Modified header cache for next request
	lastModified: {},
	etag: {},

	ajaxSettings: {
		url: location.href,
		type: "GET",
		isLocal: rlocalProtocol.test( location.protocol ),
		global: true,
		processData: true,
		async: true,
		contentType: "application/x-www-form-urlencoded; charset=UTF-8",

		/*
		timeout: 0,
		data: null,
		dataType: null,
		username: null,
		password: null,
		cache: null,
		throws: false,
		traditional: false,
		headers: {},
		*/

		accepts: {
			"*": allTypes,
			text: "text/plain",
			html: "text/html",
			xml: "application/xml, text/xml",
			json: "application/json, text/javascript"
		},

		contents: {
			xml: /\bxml\b/,
			html: /\bhtml/,
			json: /\bjson\b/
		},

		responseFields: {
			xml: "responseXML",
			text: "responseText",
			json: "responseJSON"
		},

		// Data converters
		// Keys separate source (or catchall "*") and destination types with a single space
		converters: {

			// Convert anything to text
			"* text": String,

			// Text to html (true = no transformation)
			"text html": true,

			// Evaluate text as a json expression
			"text json": JSON.parse,

			// Parse text as xml
			"text xml": jQuery.parseXML
		},

		// For options that shouldn't be deep extended:
		// you can add your own custom options here if
		// and when you create one that shouldn't be
		// deep extended (see ajaxExtend)
		flatOptions: {
			url: true,
			context: true
		}
	},

	// Creates a full fledged settings object into target
	// with both ajaxSettings and settings fields.
	// If target is omitted, writes into ajaxSettings.
	ajaxSetup: function( target, settings ) {
		return settings ?

			// Building a settings object
			ajaxExtend( ajaxExtend( target, jQuery.ajaxSettings ), settings ) :

			// Extending ajaxSettings
			ajaxExtend( jQuery.ajaxSettings, target );
	},

	ajaxPrefilter: addToPrefiltersOrTransports( prefilters ),
	ajaxTransport: addToPrefiltersOrTransports( transports ),

	// Main method
	ajax: function( url, options ) {

		// If url is an object, simulate pre-1.5 signature
		if ( typeof url === "object" ) {
			options = url;
			url = undefined;
		}

		// Force options to be an object
		options = options || {};

		var transport,

			// URL without anti-cache param
			cacheURL,

			// Response headers
			responseHeadersString,
			responseHeaders,

			// timeout handle
			timeoutTimer,

			// Url cleanup var
			urlAnchor,

			// Request state (becomes false upon send and true upon completion)
			completed,

			// To know if global events are to be dispatched
			fireGlobals,

			// Loop variable
			i,

			// uncached part of the url
			uncached,

			// Create the final options object
			s = jQuery.ajaxSetup( {}, options ),

			// Callbacks context
			callbackContext = s.context || s,

			// Context for global events is callbackContext if it is a DOM node or jQuery collection
			globalEventContext = s.context &&
				( callbackContext.nodeType || callbackContext.jquery ) ?
				jQuery( callbackContext ) :
				jQuery.event,

			// Deferreds
			deferred = jQuery.Deferred(),
			completeDeferred = jQuery.Callbacks( "once memory" ),

			// Status-dependent callbacks
			statusCode = s.statusCode || {},

			// Headers (they are sent all at once)
			requestHeaders = {},
			requestHeadersNames = {},

			// Default abort message
			strAbort = "canceled",

			// Fake xhr
			jqXHR = {
				readyState: 0,

				// Builds headers hashtable if needed
				getResponseHeader: function( key ) {
					var match;
					if ( completed ) {
						if ( !responseHeaders ) {
							responseHeaders = {};
							while ( ( match = rheaders.exec( responseHeadersString ) ) ) {
								responseHeaders[ match[ 1 ].toLowerCase() + " " ] =
									( responseHeaders[ match[ 1 ].toLowerCase() + " " ] || [] )
										.concat( match[ 2 ] );
							}
						}
						match = responseHeaders[ key.toLowerCase() + " " ];
					}
					return match == null ? null : match.join( ", " );
				},

				// Raw string
				getAllResponseHeaders: function() {
					return completed ? responseHeadersString : null;
				},

				// Caches the header
				setRequestHeader: function( name, value ) {
					if ( completed == null ) {
						name = requestHeadersNames[ name.toLowerCase() ] =
							requestHeadersNames[ name.toLowerCase() ] || name;
						requestHeaders[ name ] = value;
					}
					return this;
				},

				// Overrides response content-type header
				overrideMimeType: function( type ) {
					if ( completed == null ) {
						s.mimeType = type;
					}
					return this;
				},

				// Status-dependent callbacks
				statusCode: function( map ) {
					var code;
					if ( map ) {
						if ( completed ) {

							// Execute the appropriate callbacks
							jqXHR.always( map[ jqXHR.status ] );
						} else {

							// Lazy-add the new callbacks in a way that preserves old ones
							for ( code in map ) {
								statusCode[ code ] = [ statusCode[ code ], map[ code ] ];
							}
						}
					}
					return this;
				},

				// Cancel the request
				abort: function( statusText ) {
					var finalText = statusText || strAbort;
					if ( transport ) {
						transport.abort( finalText );
					}
					done( 0, finalText );
					return this;
				}
			};

		// Attach deferreds
		deferred.promise( jqXHR );

		// Add protocol if not provided (prefilters might expect it)
		// Handle falsy url in the settings object (#10093: consistency with old signature)
		// We also use the url parameter if available
		s.url = ( ( url || s.url || location.href ) + "" )
			.replace( rprotocol, location.protocol + "//" );

		// Alias method option to type as per ticket #12004
		s.type = options.method || options.type || s.method || s.type;

		// Extract dataTypes list
		s.dataTypes = ( s.dataType || "*" ).toLowerCase().match( rnothtmlwhite ) || [ "" ];

		// A cross-domain request is in order when the origin doesn't match the current origin.
		if ( s.crossDomain == null ) {
			urlAnchor = document.createElement( "a" );

			// Support: IE <=8 - 11, Edge 12 - 15
			// IE throws exception on accessing the href property if url is malformed,
			// e.g. http://example.com:80x/
			try {
				urlAnchor.href = s.url;

				// Support: IE <=8 - 11 only
				// Anchor's host property isn't correctly set when s.url is relative
				urlAnchor.href = urlAnchor.href;
				s.crossDomain = originAnchor.protocol + "//" + originAnchor.host !==
					urlAnchor.protocol + "//" + urlAnchor.host;
			} catch ( e ) {

				// If there is an error parsing the URL, assume it is crossDomain,
				// it can be rejected by the transport if it is invalid
				s.crossDomain = true;
			}
		}

		// Convert data if not already a string
		if ( s.data && s.processData && typeof s.data !== "string" ) {
			s.data = jQuery.param( s.data, s.traditional );
		}

		// Apply prefilters
		inspectPrefiltersOrTransports( prefilters, s, options, jqXHR );

		// If request was aborted inside a prefilter, stop there
		if ( completed ) {
			return jqXHR;
		}

		// We can fire global events as of now if asked to
		// Don't fire events if jQuery.event is undefined in an AMD-usage scenario (#15118)
		fireGlobals = jQuery.event && s.global;

		// Watch for a new set of requests
		if ( fireGlobals && jQuery.active++ === 0 ) {
			jQuery.event.trigger( "ajaxStart" );
		}

		// Uppercase the type
		s.type = s.type.toUpperCase();

		// Determine if request has content
		s.hasContent = !rnoContent.test( s.type );

		// Save the URL in case we're toying with the If-Modified-Since
		// and/or If-None-Match header later on
		// Remove hash to simplify url manipulation
		cacheURL = s.url.replace( rhash, "" );

		// More options handling for requests with no content
		if ( !s.hasContent ) {

			// Remember the hash so we can put it back
			uncached = s.url.slice( cacheURL.length );

			// If data is available and should be processed, append data to url
			if ( s.data && ( s.processData || typeof s.data === "string" ) ) {
				cacheURL += ( rquery.test( cacheURL ) ? "&" : "?" ) + s.data;

				// #9682: remove data so that it's not used in an eventual retry
				delete s.data;
			}

			// Add or update anti-cache param if needed
			if ( s.cache === false ) {
				cacheURL = cacheURL.replace( rantiCache, "$1" );
				uncached = ( rquery.test( cacheURL ) ? "&" : "?" ) + "_=" + ( nonce.guid++ ) +
					uncached;
			}

			// Put hash and anti-cache on the URL that will be requested (gh-1732)
			s.url = cacheURL + uncached;

		// Change '%20' to '+' if this is encoded form body content (gh-2658)
		} else if ( s.data && s.processData &&
			( s.contentType || "" ).indexOf( "application/x-www-form-urlencoded" ) === 0 ) {
			s.data = s.data.replace( r20, "+" );
		}

		// Set the If-Modified-Since and/or If-None-Match header, if in ifModified mode.
		if ( s.ifModified ) {
			if ( jQuery.lastModified[ cacheURL ] ) {
				jqXHR.setRequestHeader( "If-Modified-Since", jQuery.lastModified[ cacheURL ] );
			}
			if ( jQuery.etag[ cacheURL ] ) {
				jqXHR.setRequestHeader( "If-None-Match", jQuery.etag[ cacheURL ] );
			}
		}

		// Set the correct header, if data is being sent
		if ( s.data && s.hasContent && s.contentType !== false || options.contentType ) {
			jqXHR.setRequestHeader( "Content-Type", s.contentType );
		}

		// Set the Accepts header for the server, depending on the dataType
		jqXHR.setRequestHeader(
			"Accept",
			s.dataTypes[ 0 ] && s.accepts[ s.dataTypes[ 0 ] ] ?
				s.accepts[ s.dataTypes[ 0 ] ] +
					( s.dataTypes[ 0 ] !== "*" ? ", " + allTypes + "; q=0.01" : "" ) :
				s.accepts[ "*" ]
		);

		// Check for headers option
		for ( i in s.headers ) {
			jqXHR.setRequestHeader( i, s.headers[ i ] );
		}

		// Allow custom headers/mimetypes and early abort
		if ( s.beforeSend &&
			( s.beforeSend.call( callbackContext, jqXHR, s ) === false || completed ) ) {

			// Abort if not done already and return
			return jqXHR.abort();
		}

		// Aborting is no longer a cancellation
		strAbort = "abort";

		// Install callbacks on deferreds
		completeDeferred.add( s.complete );
		jqXHR.done( s.success );
		jqXHR.fail( s.error );

		// Get transport
		transport = inspectPrefiltersOrTransports( transports, s, options, jqXHR );

		// If no transport, we auto-abort
		if ( !transport ) {
			done( -1, "No Transport" );
		} else {
			jqXHR.readyState = 1;

			// Send global event
			if ( fireGlobals ) {
				globalEventContext.trigger( "ajaxSend", [ jqXHR, s ] );
			}

			// If request was aborted inside ajaxSend, stop there
			if ( completed ) {
				return jqXHR;
			}

			// Timeout
			if ( s.async && s.timeout > 0 ) {
				timeoutTimer = window.setTimeout( function() {
					jqXHR.abort( "timeout" );
				}, s.timeout );
			}

			try {
				completed = false;
				transport.send( requestHeaders, done );
			} catch ( e ) {

				// Rethrow post-completion exceptions
				if ( completed ) {
					throw e;
				}

				// Propagate others as results
				done( -1, e );
			}
		}

		// Callback for when everything is done
		function done( status, nativeStatusText, responses, headers ) {
			var isSuccess, success, error, response, modified,
				statusText = nativeStatusText;

			// Ignore repeat invocations
			if ( completed ) {
				return;
			}

			completed = true;

			// Clear timeout if it exists
			if ( timeoutTimer ) {
				window.clearTimeout( timeoutTimer );
			}

			// Dereference transport for early garbage collection
			// (no matter how long the jqXHR object will be used)
			transport = undefined;

			// Cache response headers
			responseHeadersString = headers || "";

			// Set readyState
			jqXHR.readyState = status > 0 ? 4 : 0;

			// Determine if successful
			isSuccess = status >= 200 && status < 300 || status === 304;

			// Get response data
			if ( responses ) {
				response = ajaxHandleResponses( s, jqXHR, responses );
			}

			// Use a noop converter for missing script but not if jsonp
			if ( !isSuccess &&
				jQuery.inArray( "script", s.dataTypes ) > -1 &&
				jQuery.inArray( "json", s.dataTypes ) < 0 ) {
				s.converters[ "text script" ] = function() {};
			}

			// Convert no matter what (that way responseXXX fields are always set)
			response = ajaxConvert( s, response, jqXHR, isSuccess );

			// If successful, handle type chaining
			if ( isSuccess ) {

				// Set the If-Modified-Since and/or If-None-Match header, if in ifModified mode.
				if ( s.ifModified ) {
					modified = jqXHR.getResponseHeader( "Last-Modified" );
					if ( modified ) {
						jQuery.lastModified[ cacheURL ] = modified;
					}
					modified = jqXHR.getResponseHeader( "etag" );
					if ( modified ) {
						jQuery.etag[ cacheURL ] = modified;
					}
				}

				// if no content
				if ( status === 204 || s.type === "HEAD" ) {
					statusText = "nocontent";

				// if not modified
				} else if ( status === 304 ) {
					statusText = "notmodified";

				// If we have data, let's convert it
				} else {
					statusText = response.state;
					success = response.data;
					error = response.error;
					isSuccess = !error;
				}
			} else {

				// Extract error from statusText and normalize for non-aborts
				error = statusText;
				if ( status || !statusText ) {
					statusText = "error";
					if ( status < 0 ) {
						status = 0;
					}
				}
			}

			// Set data for the fake xhr object
			jqXHR.status = status;
			jqXHR.statusText = ( nativeStatusText || statusText ) + "";

			// Success/Error
			if ( isSuccess ) {
				deferred.resolveWith( callbackContext, [ success, statusText, jqXHR ] );
			} else {
				deferred.rejectWith( callbackContext, [ jqXHR, statusText, error ] );
			}

			// Status-dependent callbacks
			jqXHR.statusCode( statusCode );
			statusCode = undefined;

			if ( fireGlobals ) {
				globalEventContext.trigger( isSuccess ? "ajaxSuccess" : "ajaxError",
					[ jqXHR, s, isSuccess ? success : error ] );
			}

			// Complete
			completeDeferred.fireWith( callbackContext, [ jqXHR, statusText ] );

			if ( fireGlobals ) {
				globalEventContext.trigger( "ajaxComplete", [ jqXHR, s ] );

				// Handle the global AJAX counter
				if ( !( --jQuery.active ) ) {
					jQuery.event.trigger( "ajaxStop" );
				}
			}
		}

		return jqXHR;
	},

	getJSON: function( url, data, callback ) {
		return jQuery.get( url, data, callback, "json" );
	},

	getScript: function( url, callback ) {
		return jQuery.get( url, undefined, callback, "script" );
	}
} );

jQuery.each( [ "get", "post" ], function( _i, method ) {
	jQuery[ method ] = function( url, data, callback, type ) {

		// Shift arguments if data argument was omitted
		if ( isFunction( data ) ) {
			type = type || callback;
			callback = data;
			data = undefined;
		}

		// The url can be an options object (which then must have .url)
		return jQuery.ajax( jQuery.extend( {
			url: url,
			type: method,
			dataType: type,
			data: data,
			success: callback
		}, jQuery.isPlainObject( url ) && url ) );
	};
} );

jQuery.ajaxPrefilter( function( s ) {
	var i;
	for ( i in s.headers ) {
		if ( i.toLowerCase() === "content-type" ) {
			s.contentType = s.headers[ i ] || "";
		}
	}
} );


jQuery._evalUrl = function( url, options, doc ) {
	return jQuery.ajax( {
		url: url,

		// Make this explicit, since user can override this through ajaxSetup (#11264)
		type: "GET",
		dataType: "script",
		cache: true,
		async: false,
		global: false,

		// Only evaluate the response if it is successful (gh-4126)
		// dataFilter is not invoked for failure responses, so using it instead
		// of the default converter is kludgy but it works.
		converters: {
			"text script": function() {}
		},
		dataFilter: function( response ) {
			jQuery.globalEval( response, options, doc );
		}
	} );
};


jQuery.fn.extend( {
	wrapAll: function( html ) {
		var wrap;

		if ( this[ 0 ] ) {
			if ( isFunction( html ) ) {
				html = html.call( this[ 0 ] );
			}

			// The elements to wrap the target around
			wrap = jQuery( html, this[ 0 ].ownerDocument ).eq( 0 ).clone( true );

			if ( this[ 0 ].parentNode ) {
				wrap.insertBefore( this[ 0 ] );
			}

			wrap.map( function() {
				var elem = this;

				while ( elem.firstElementChild ) {
					elem = elem.firstElementChild;
				}

				return elem;
			} ).append( this );
		}

		return this;
	},

	wrapInner: function( html ) {
		if ( isFunction( html ) ) {
			return this.each( function( i ) {
				jQuery( this ).wrapInner( html.call( this, i ) );
			} );
		}

		return this.each( function() {
			var self = jQuery( this ),
				contents = self.contents();

			if ( contents.length ) {
				contents.wrapAll( html );

			} else {
				self.append( html );
			}
		} );
	},

	wrap: function( html ) {
		var htmlIsFunction = isFunction( html );

		return this.each( function( i ) {
			jQuery( this ).wrapAll( htmlIsFunction ? html.call( this, i ) : html );
		} );
	},

	unwrap: function( selector ) {
		this.parent( selector ).not( "body" ).each( function() {
			jQuery( this ).replaceWith( this.childNodes );
		} );
		return this;
	}
} );


jQuery.expr.pseudos.hidden = function( elem ) {
	return !jQuery.expr.pseudos.visible( elem );
};
jQuery.expr.pseudos.visible = function( elem ) {
	return !!( elem.offsetWidth || elem.offsetHeight || elem.getClientRects().length );
};




jQuery.ajaxSettings.xhr = function() {
	try {
		return new window.XMLHttpRequest();
	} catch ( e ) {}
};

var xhrSuccessStatus = {

		// File protocol always yields status code 0, assume 200
		0: 200,

		// Support: IE <=9 only
		// #1450: sometimes IE returns 1223 when it should be 204
		1223: 204
	},
	xhrSupported = jQuery.ajaxSettings.xhr();

support.cors = !!xhrSupported && ( "withCredentials" in xhrSupported );
support.ajax = xhrSupported = !!xhrSupported;

jQuery.ajaxTransport( function( options ) {
	var callback, errorCallback;

	// Cross domain only allowed if supported through XMLHttpRequest
	if ( support.cors || xhrSupported && !options.crossDomain ) {
		return {
			send: function( headers, complete ) {
				var i,
					xhr = options.xhr();

				xhr.open(
					options.type,
					options.url,
					options.async,
					options.username,
					options.password
				);

				// Apply custom fields if provided
				if ( options.xhrFields ) {
					for ( i in options.xhrFields ) {
						xhr[ i ] = options.xhrFields[ i ];
					}
				}

				// Override mime type if needed
				if ( options.mimeType && xhr.overrideMimeType ) {
					xhr.overrideMimeType( options.mimeType );
				}

				// X-Requested-With header
				// For cross-domain requests, seeing as conditions for a preflight are
				// akin to a jigsaw puzzle, we simply never set it to be sure.
				// (it can always be set on a per-request basis or even using ajaxSetup)
				// For same-domain requests, won't change header if already provided.
				if ( !options.crossDomain && !headers[ "X-Requested-With" ] ) {
					headers[ "X-Requested-With" ] = "XMLHttpRequest";
				}

				// Set headers
				for ( i in headers ) {
					xhr.setRequestHeader( i, headers[ i ] );
				}

				// Callback
				callback = function( type ) {
					return function() {
						if ( callback ) {
							callback = errorCallback = xhr.onload =
								xhr.onerror = xhr.onabort = xhr.ontimeout =
									xhr.onreadystatechange = null;

							if ( type === "abort" ) {
								xhr.abort();
							} else if ( type === "error" ) {

								// Support: IE <=9 only
								// On a manual native abort, IE9 throws
								// errors on any property access that is not readyState
								if ( typeof xhr.status !== "number" ) {
									complete( 0, "error" );
								} else {
									complete(

										// File: protocol always yields status 0; see #8605, #14207
										xhr.status,
										xhr.statusText
									);
								}
							} else {
								complete(
									xhrSuccessStatus[ xhr.status ] || xhr.status,
									xhr.statusText,

									// Support: IE <=9 only
									// IE9 has no XHR2 but throws on binary (trac-11426)
									// For XHR2 non-text, let the caller handle it (gh-2498)
									( xhr.responseType || "text" ) !== "text"  ||
									typeof xhr.responseText !== "string" ?
										{ binary: xhr.response } :
										{ text: xhr.responseText },
									xhr.getAllResponseHeaders()
								);
							}
						}
					};
				};

				// Listen to events
				xhr.onload = callback();
				errorCallback = xhr.onerror = xhr.ontimeout = callback( "error" );

				// Support: IE 9 only
				// Use onreadystatechange to replace onabort
				// to handle uncaught aborts
				if ( xhr.onabort !== undefined ) {
					xhr.onabort = errorCallback;
				} else {
					xhr.onreadystatechange = function() {

						// Check readyState before timeout as it changes
						if ( xhr.readyState === 4 ) {

							// Allow onerror to be called first,
							// but that will not handle a native abort
							// Also, save errorCallback to a variable
							// as xhr.onerror cannot be accessed
							window.setTimeout( function() {
								if ( callback ) {
									errorCallback();
								}
							} );
						}
					};
				}

				// Create the abort callback
				callback = callback( "abort" );

				try {

					// Do send the request (this may raise an exception)
					xhr.send( options.hasContent && options.data || null );
				} catch ( e ) {

					// #14683: Only rethrow if this hasn't been notified as an error yet
					if ( callback ) {
						throw e;
					}
				}
			},

			abort: function() {
				if ( callback ) {
					callback();
				}
			}
		};
	}
} );




// Prevent auto-execution of scripts when no explicit dataType was provided (See gh-2432)
jQuery.ajaxPrefilter( function( s ) {
	if ( s.crossDomain ) {
		s.contents.script = false;
	}
} );

// Install script dataType
jQuery.ajaxSetup( {
	accepts: {
		script: "text/javascript, application/javascript, " +
			"application/ecmascript, application/x-ecmascript"
	},
	contents: {
		script: /\b(?:java|ecma)script\b/
	},
	converters: {
		"text script": function( text ) {
			jQuery.globalEval( text );
			return text;
		}
	}
} );

// Handle cache's special case and crossDomain
jQuery.ajaxPrefilter( "script", function( s ) {
	if ( s.cache === undefined ) {
		s.cache = false;
	}
	if ( s.crossDomain ) {
		s.type = "GET";
	}
} );

// Bind script tag hack transport
jQuery.ajaxTransport( "script", function( s ) {

	// This transport only deals with cross domain or forced-by-attrs requests
	if ( s.crossDomain || s.scriptAttrs ) {
		var script, callback;
		return {
			send: function( _, complete ) {
				script = jQuery( "<script>" )
					.attr( s.scriptAttrs || {} )
					.prop( { charset: s.scriptCharset, src: s.url } )
					.on( "load error", callback = function( evt ) {
						script.remove();
						callback = null;
						if ( evt ) {
							complete( evt.type === "error" ? 404 : 200, evt.type );
						}
					} );

				// Use native DOM manipulation to avoid our domManip AJAX trickery
				document.head.appendChild( script[ 0 ] );
			},
			abort: function() {
				if ( callback ) {
					callback();
				}
			}
		};
	}
} );




var oldCallbacks = [],
	rjsonp = /(=)\?(?=&|$)|\?\?/;

// Default jsonp settings
jQuery.ajaxSetup( {
	jsonp: "callback",
	jsonpCallback: function() {
		var callback = oldCallbacks.pop() || ( jQuery.expando + "_" + ( nonce.guid++ ) );
		this[ callback ] = true;
		return callback;
	}
} );

// Detect, normalize options and install callbacks for jsonp requests
jQuery.ajaxPrefilter( "json jsonp", function( s, originalSettings, jqXHR ) {

	var callbackName, overwritten, responseContainer,
		jsonProp = s.jsonp !== false && ( rjsonp.test( s.url ) ?
			"url" :
			typeof s.data === "string" &&
				( s.contentType || "" )
					.indexOf( "application/x-www-form-urlencoded" ) === 0 &&
				rjsonp.test( s.data ) && "data"
		);

	// Handle iff the expected data type is "jsonp" or we have a parameter to set
	if ( jsonProp || s.dataTypes[ 0 ] === "jsonp" ) {

		// Get callback name, remembering preexisting value associated with it
		callbackName = s.jsonpCallback = isFunction( s.jsonpCallback ) ?
			s.jsonpCallback() :
			s.jsonpCallback;

		// Insert callback into url or form data
		if ( jsonProp ) {
			s[ jsonProp ] = s[ jsonProp ].replace( rjsonp, "$1" + callbackName );
		} else if ( s.jsonp !== false ) {
			s.url += ( rquery.test( s.url ) ? "&" : "?" ) + s.jsonp + "=" + callbackName;
		}

		// Use data converter to retrieve json after script execution
		s.converters[ "script json" ] = function() {
			if ( !responseContainer ) {
				jQuery.error( callbackName + " was not called" );
			}
			return responseContainer[ 0 ];
		};

		// Force json dataType
		s.dataTypes[ 0 ] = "json";

		// Install callback
		overwritten = window[ callbackName ];
		window[ callbackName ] = function() {
			responseContainer = arguments;
		};

		// Clean-up function (fires after converters)
		jqXHR.always( function() {

			// If previous value didn't exist - remove it
			if ( overwritten === undefined ) {
				jQuery( window ).removeProp( callbackName );

			// Otherwise restore preexisting value
			} else {
				window[ callbackName ] = overwritten;
			}

			// Save back as free
			if ( s[ callbackName ] ) {

				// Make sure that re-using the options doesn't screw things around
				s.jsonpCallback = originalSettings.jsonpCallback;

				// Save the callback name for future use
				oldCallbacks.push( callbackName );
			}

			// Call if it was a function and we have a response
			if ( responseContainer && isFunction( overwritten ) ) {
				overwritten( responseContainer[ 0 ] );
			}

			responseContainer = overwritten = undefined;
		} );

		// Delegate to script
		return "script";
	}
} );




// Support: Safari 8 only
// In Safari 8 documents created via document.implementation.createHTMLDocument
// collapse sibling forms: the second one becomes a child of the first one.
// Because of that, this security measure has to be disabled in Safari 8.
// https://bugs.webkit.org/show_bug.cgi?id=137337
support.createHTMLDocument = ( function() {
	var body = document.implementation.createHTMLDocument( "" ).body;
	body.innerHTML = "<form></form><form></form>";
	return body.childNodes.length === 2;
} )();


// Argument "data" should be string of html
// context (optional): If specified, the fragment will be created in this context,
// defaults to document
// keepScripts (optional): If true, will include scripts passed in the html string
jQuery.parseHTML = function( data, context, keepScripts ) {
	if ( typeof data !== "string" ) {
		return [];
	}
	if ( typeof context === "boolean" ) {
		keepScripts = context;
		context = false;
	}

	var base, parsed, scripts;

	if ( !context ) {

		// Stop scripts or inline event handlers from being executed immediately
		// by using document.implementation
		if ( support.createHTMLDocument ) {
			context = document.implementation.createHTMLDocument( "" );

			// Set the base href for the created document
			// so any parsed elements with URLs
			// are based on the document's URL (gh-2965)
			base = context.createElement( "base" );
			base.href = document.location.href;
			context.head.appendChild( base );
		} else {
			context = document;
		}
	}

	parsed = rsingleTag.exec( data );
	scripts = !keepScripts && [];

	// Single tag
	if ( parsed ) {
		return [ context.createElement( parsed[ 1 ] ) ];
	}

	parsed = buildFragment( [ data ], context, scripts );

	if ( scripts && scripts.length ) {
		jQuery( scripts ).remove();
	}

	return jQuery.merge( [], parsed.childNodes );
};


/**
 * Load a url into a page
 */
jQuery.fn.load = function( url, params, callback ) {
	var selector, type, response,
		self = this,
		off = url.indexOf( " " );

	if ( off > -1 ) {
		selector = stripAndCollapse( url.slice( off ) );
		url = url.slice( 0, off );
	}

	// If it's a function
	if ( isFunction( params ) ) {

		// We assume that it's the callback
		callback = params;
		params = undefined;

	// Otherwise, build a param string
	} else if ( params && typeof params === "object" ) {
		type = "POST";
	}

	// If we have elements to modify, make the request
	if ( self.length > 0 ) {
		jQuery.ajax( {
			url: url,

			// If "type" variable is undefined, then "GET" method will be used.
			// Make value of this field explicit since
			// user can override it through ajaxSetup method
			type: type || "GET",
			dataType: "html",
			data: params
		} ).done( function( responseText ) {

			// Save response for use in complete callback
			response = arguments;

			self.html( selector ?

				// If a selector was specified, locate the right elements in a dummy div
				// Exclude scripts to avoid IE 'Permission Denied' errors
				jQuery( "<div>" ).append( jQuery.parseHTML( responseText ) ).find( selector ) :

				// Otherwise use the full result
				responseText );

		// If the request succeeds, this function gets "data", "status", "jqXHR"
		// but they are ignored because response was set above.
		// If it fails, this function gets "jqXHR", "status", "error"
		} ).always( callback && function( jqXHR, status ) {
			self.each( function() {
				callback.apply( this, response || [ jqXHR.responseText, status, jqXHR ] );
			} );
		} );
	}

	return this;
};




jQuery.expr.pseudos.animated = function( elem ) {
	return jQuery.grep( jQuery.timers, function( fn ) {
		return elem === fn.elem;
	} ).length;
};




jQuery.offset = {
	setOffset: function( elem, options, i ) {
		var curPosition, curLeft, curCSSTop, curTop, curOffset, curCSSLeft, calculatePosition,
			position = jQuery.css( elem, "position" ),
			curElem = jQuery( elem ),
			props = {};

		// Set position first, in-case top/left are set even on static elem
		if ( position === "static" ) {
			elem.style.position = "relative";
		}

		curOffset = curElem.offset();
		curCSSTop = jQuery.css( elem, "top" );
		curCSSLeft = jQuery.css( elem, "left" );
		calculatePosition = ( position === "absolute" || position === "fixed" ) &&
			( curCSSTop + curCSSLeft ).indexOf( "auto" ) > -1;

		// Need to be able to calculate position if either
		// top or left is auto and position is either absolute or fixed
		if ( calculatePosition ) {
			curPosition = curElem.position();
			curTop = curPosition.top;
			curLeft = curPosition.left;

		} else {
			curTop = parseFloat( curCSSTop ) || 0;
			curLeft = parseFloat( curCSSLeft ) || 0;
		}

		if ( isFunction( options ) ) {

			// Use jQuery.extend here to allow modification of coordinates argument (gh-1848)
			options = options.call( elem, i, jQuery.extend( {}, curOffset ) );
		}

		if ( options.top != null ) {
			props.top = ( options.top - curOffset.top ) + curTop;
		}
		if ( options.left != null ) {
			props.left = ( options.left - curOffset.left ) + curLeft;
		}

		if ( "using" in options ) {
			options.using.call( elem, props );

		} else {
			curElem.css( props );
		}
	}
};

jQuery.fn.extend( {

	// offset() relates an element's border box to the document origin
	offset: function( options ) {

		// Preserve chaining for setter
		if ( arguments.length ) {
			return options === undefined ?
				this :
				this.each( function( i ) {
					jQuery.offset.setOffset( this, options, i );
				} );
		}

		var rect, win,
			elem = this[ 0 ];

		if ( !elem ) {
			return;
		}

		// Return zeros for disconnected and hidden (display: none) elements (gh-2310)
		// Support: IE <=11 only
		// Running getBoundingClientRect on a
		// disconnected node in IE throws an error
		if ( !elem.getClientRects().length ) {
			return { top: 0, left: 0 };
		}

		// Get document-relative position by adding viewport scroll to viewport-relative gBCR
		rect = elem.getBoundingClientRect();
		win = elem.ownerDocument.defaultView;
		return {
			top: rect.top + win.pageYOffset,
			left: rect.left + win.pageXOffset
		};
	},

	// position() relates an element's margin box to its offset parent's padding box
	// This corresponds to the behavior of CSS absolute positioning
	position: function() {
		if ( !this[ 0 ] ) {
			return;
		}

		var offsetParent, offset, doc,
			elem = this[ 0 ],
			parentOffset = { top: 0, left: 0 };

		// position:fixed elements are offset from the viewport, which itself always has zero offset
		if ( jQuery.css( elem, "position" ) === "fixed" ) {

			// Assume position:fixed implies availability of getBoundingClientRect
			offset = elem.getBoundingClientRect();

		} else {
			offset = this.offset();

			// Account for the *real* offset parent, which can be the document or its root element
			// when a statically positioned element is identified
			doc = elem.ownerDocument;
			offsetParent = elem.offsetParent || doc.documentElement;
			while ( offsetParent &&
				( offsetParent === doc.body || offsetParent === doc.documentElement ) &&
				jQuery.css( offsetParent, "position" ) === "static" ) {

				offsetParent = offsetParent.parentNode;
			}
			if ( offsetParent && offsetParent !== elem && offsetParent.nodeType === 1 ) {

				// Incorporate borders into its offset, since they are outside its content origin
				parentOffset = jQuery( offsetParent ).offset();
				parentOffset.top += jQuery.css( offsetParent, "borderTopWidth", true );
				parentOffset.left += jQuery.css( offsetParent, "borderLeftWidth", true );
			}
		}

		// Subtract parent offsets and element margins
		return {
			top: offset.top - parentOffset.top - jQuery.css( elem, "marginTop", true ),
			left: offset.left - parentOffset.left - jQuery.css( elem, "marginLeft", true )
		};
	},

	// This method will return documentElement in the following cases:
	// 1) For the element inside the iframe without offsetParent, this method will return
	//    documentElement of the parent window
	// 2) For the hidden or detached element
	// 3) For body or html element, i.e. in case of the html node - it will return itself
	//
	// but those exceptions were never presented as a real life use-cases
	// and might be considered as more preferable results.
	//
	// This logic, however, is not guaranteed and can change at any point in the future
	offsetParent: function() {
		return this.map( function() {
			var offsetParent = this.offsetParent;

			while ( offsetParent && jQuery.css( offsetParent, "position" ) === "static" ) {
				offsetParent = offsetParent.offsetParent;
			}

			return offsetParent || documentElement;
		} );
	}
} );

// Create scrollLeft and scrollTop methods
jQuery.each( { scrollLeft: "pageXOffset", scrollTop: "pageYOffset" }, function( method, prop ) {
	var top = "pageYOffset" === prop;

	jQuery.fn[ method ] = function( val ) {
		return access( this, function( elem, method, val ) {

			// Coalesce documents and windows
			var win;
			if ( isWindow( elem ) ) {
				win = elem;
			} else if ( elem.nodeType === 9 ) {
				win = elem.defaultView;
			}

			if ( val === undefined ) {
				return win ? win[ prop ] : elem[ method ];
			}

			if ( win ) {
				win.scrollTo(
					!top ? val : win.pageXOffset,
					top ? val : win.pageYOffset
				);

			} else {
				elem[ method ] = val;
			}
		}, method, val, arguments.length );
	};
} );

// Support: Safari <=7 - 9.1, Chrome <=37 - 49
// Add the top/left cssHooks using jQuery.fn.position
// Webkit bug: https://bugs.webkit.org/show_bug.cgi?id=29084
// Blink bug: https://bugs.chromium.org/p/chromium/issues/detail?id=589347
// getComputedStyle returns percent when specified for top/left/bottom/right;
// rather than make the css module depend on the offset module, just check for it here
jQuery.each( [ "top", "left" ], function( _i, prop ) {
	jQuery.cssHooks[ prop ] = addGetHookIf( support.pixelPosition,
		function( elem, computed ) {
			if ( computed ) {
				computed = curCSS( elem, prop );

				// If curCSS returns percentage, fallback to offset
				return rnumnonpx.test( computed ) ?
					jQuery( elem ).position()[ prop ] + "px" :
					computed;
			}
		}
	);
} );


// Create innerHeight, innerWidth, height, width, outerHeight and outerWidth methods
jQuery.each( { Height: "height", Width: "width" }, function( name, type ) {
	jQuery.each( {
		padding: "inner" + name,
		content: type,
		"": "outer" + name
	}, function( defaultExtra, funcName ) {

		// Margin is only for outerHeight, outerWidth
		jQuery.fn[ funcName ] = function( margin, value ) {
			var chainable = arguments.length && ( defaultExtra || typeof margin !== "boolean" ),
				extra = defaultExtra || ( margin === true || value === true ? "margin" : "border" );

			return access( this, function( elem, type, value ) {
				var doc;

				if ( isWindow( elem ) ) {

					// $( window ).outerWidth/Height return w/h including scrollbars (gh-1729)
					return funcName.indexOf( "outer" ) === 0 ?
						elem[ "inner" + name ] :
						elem.document.documentElement[ "client" + name ];
				}

				// Get document width or height
				if ( elem.nodeType === 9 ) {
					doc = elem.documentElement;

					// Either scroll[Width/Height] or offset[Width/Height] or client[Width/Height],
					// whichever is greatest
					return Math.max(
						elem.body[ "scroll" + name ], doc[ "scroll" + name ],
						elem.body[ "offset" + name ], doc[ "offset" + name ],
						doc[ "client" + name ]
					);
				}

				return value === undefined ?

					// Get width or height on the element, requesting but not forcing parseFloat
					jQuery.css( elem, type, extra ) :

					// Set width or height on the element
					jQuery.style( elem, type, value, extra );
			}, type, chainable ? margin : undefined, chainable );
		};
	} );
} );


jQuery.each( [
	"ajaxStart",
	"ajaxStop",
	"ajaxComplete",
	"ajaxError",
	"ajaxSuccess",
	"ajaxSend"
], function( _i, type ) {
	jQuery.fn[ type ] = function( fn ) {
		return this.on( type, fn );
	};
} );




jQuery.fn.extend( {

	bind: function( types, data, fn ) {
		return this.on( types, null, data, fn );
	},
	unbind: function( types, fn ) {
		return this.off( types, null, fn );
	},

	delegate: function( selector, types, data, fn ) {
		return this.on( types, selector, data, fn );
	},
	undelegate: function( selector, types, fn ) {

		// ( namespace ) or ( selector, types [, fn] )
		return arguments.length === 1 ?
			this.off( selector, "**" ) :
			this.off( types, selector || "**", fn );
	},

	hover: function( fnOver, fnOut ) {
		return this.mouseenter( fnOver ).mouseleave( fnOut || fnOver );
	}
} );

jQuery.each(
	( "blur focus focusin focusout resize scroll click dblclick " +
	"mousedown mouseup mousemove mouseover mouseout mouseenter mouseleave " +
	"change select submit keydown keypress keyup contextmenu" ).split( " " ),
	function( _i, name ) {

		// Handle event binding
		jQuery.fn[ name ] = function( data, fn ) {
			return arguments.length > 0 ?
				this.on( name, null, data, fn ) :
				this.trigger( name );
		};
	}
);




// Support: Android <=4.0 only
// Make sure we trim BOM and NBSP
var rtrim = /^[\s\uFEFF\xA0]+|[\s\uFEFF\xA0]+$/g;

// Bind a function to a context, optionally partially applying any
// arguments.
// jQuery.proxy is deprecated to promote standards (specifically Function#bind)
// However, it is not slated for removal any time soon
jQuery.proxy = function( fn, context ) {
	var tmp, args, proxy;

	if ( typeof context === "string" ) {
		tmp = fn[ context ];
		context = fn;
		fn = tmp;
	}

	// Quick check to determine if target is callable, in the spec
	// this throws a TypeError, but we will just return undefined.
	if ( !isFunction( fn ) ) {
		return undefined;
	}

	// Simulated bind
	args = slice.call( arguments, 2 );
	proxy = function() {
		return fn.apply( context || this, args.concat( slice.call( arguments ) ) );
	};

	// Set the guid of unique handler to the same of original handler, so it can be removed
	proxy.guid = fn.guid = fn.guid || jQuery.guid++;

	return proxy;
};

jQuery.holdReady = function( hold ) {
	if ( hold ) {
		jQuery.readyWait++;
	} else {
		jQuery.ready( true );
	}
};
jQuery.isArray = Array.isArray;
jQuery.parseJSON = JSON.parse;
jQuery.nodeName = nodeName;
jQuery.isFunction = isFunction;
jQuery.isWindow = isWindow;
jQuery.camelCase = camelCase;
jQuery.type = toType;

jQuery.now = Date.now;

jQuery.isNumeric = function( obj ) {

	// As of jQuery 3.0, isNumeric is limited to
	// strings and numbers (primitives or objects)
	// that can be coerced to finite numbers (gh-2662)
	var type = jQuery.type( obj );
	return ( type === "number" || type === "string" ) &&

		// parseFloat NaNs numeric-cast false positives ("")
		// ...but misinterprets leading-number strings, particularly hex literals ("0x...")
		// subtraction forces infinities to NaN
		!isNaN( obj - parseFloat( obj ) );
};

jQuery.trim = function( text ) {
	return text == null ?
		"" :
		( text + "" ).replace( rtrim, "" );
};



// Register as a named AMD module, since jQuery can be concatenated with other
// files that may use define, but not via a proper concatenation script that
// understands anonymous AMD modules. A named AMD is safest and most robust
// way to register. Lowercase jquery is used because AMD module names are
// derived from file names, and jQuery is normally delivered in a lowercase
// file name. Do this after creating the global so that if an AMD module wants
// to call noConflict to hide this version of jQuery, it will work.

// Note that for maximum portability, libraries that are not jQuery should
// declare themselves as anonymous modules, and avoid setting a global if an
// AMD loader is present. jQuery is a special case. For more information, see
// https://github.com/jrburke/requirejs/wiki/Updating-existing-libraries#wiki-anon

if ( typeof define === "function" && define.amd ) {
	define( "jquery", [], function() {
		return jQuery;
	} );
}




var

	// Map over jQuery in case of overwrite
	_jQuery = window.jQuery,

	// Map over the $ in case of overwrite
	_$ = window.$;

jQuery.noConflict = function( deep ) {
	if ( window.$ === jQuery ) {
		window.$ = _$;
	}

	if ( deep && window.jQuery === jQuery ) {
		window.jQuery = _jQuery;
	}

	return jQuery;
};

// Expose jQuery and $ identifiers, even in AMD
// (#7102#comment:10, https://github.com/jquery/jquery/pull/557)
// and CommonJS for browser emulators (#13566)
if ( typeof noGlobal === "undefined" ) {
	window.jQuery = window.$ = jQuery;
}




return jQuery;
} );

},{}],16:[function(require,module,exports){
module.exports = [
    [ 0x0300, 0x036F ], [ 0x0483, 0x0486 ], [ 0x0488, 0x0489 ],
    [ 0x0591, 0x05BD ], [ 0x05BF, 0x05BF ], [ 0x05C1, 0x05C2 ],
    [ 0x05C4, 0x05C5 ], [ 0x05C7, 0x05C7 ], [ 0x0600, 0x0603 ],
    [ 0x0610, 0x0615 ], [ 0x064B, 0x065E ], [ 0x0670, 0x0670 ],
    [ 0x06D6, 0x06E4 ], [ 0x06E7, 0x06E8 ], [ 0x06EA, 0x06ED ],
    [ 0x070F, 0x070F ], [ 0x0711, 0x0711 ], [ 0x0730, 0x074A ],
    [ 0x07A6, 0x07B0 ], [ 0x07EB, 0x07F3 ], [ 0x0901, 0x0902 ],
    [ 0x093C, 0x093C ], [ 0x0941, 0x0948 ], [ 0x094D, 0x094D ],
    [ 0x0951, 0x0954 ], [ 0x0962, 0x0963 ], [ 0x0981, 0x0981 ],
    [ 0x09BC, 0x09BC ], [ 0x09C1, 0x09C4 ], [ 0x09CD, 0x09CD ],
    [ 0x09E2, 0x09E3 ], [ 0x0A01, 0x0A02 ], [ 0x0A3C, 0x0A3C ],
    [ 0x0A41, 0x0A42 ], [ 0x0A47, 0x0A48 ], [ 0x0A4B, 0x0A4D ],
    [ 0x0A70, 0x0A71 ], [ 0x0A81, 0x0A82 ], [ 0x0ABC, 0x0ABC ],
    [ 0x0AC1, 0x0AC5 ], [ 0x0AC7, 0x0AC8 ], [ 0x0ACD, 0x0ACD ],
    [ 0x0AE2, 0x0AE3 ], [ 0x0B01, 0x0B01 ], [ 0x0B3C, 0x0B3C ],
    [ 0x0B3F, 0x0B3F ], [ 0x0B41, 0x0B43 ], [ 0x0B4D, 0x0B4D ],
    [ 0x0B56, 0x0B56 ], [ 0x0B82, 0x0B82 ], [ 0x0BC0, 0x0BC0 ],
    [ 0x0BCD, 0x0BCD ], [ 0x0C3E, 0x0C40 ], [ 0x0C46, 0x0C48 ],
    [ 0x0C4A, 0x0C4D ], [ 0x0C55, 0x0C56 ], [ 0x0CBC, 0x0CBC ],
    [ 0x0CBF, 0x0CBF ], [ 0x0CC6, 0x0CC6 ], [ 0x0CCC, 0x0CCD ],
    [ 0x0CE2, 0x0CE3 ], [ 0x0D41, 0x0D43 ], [ 0x0D4D, 0x0D4D ],
    [ 0x0DCA, 0x0DCA ], [ 0x0DD2, 0x0DD4 ], [ 0x0DD6, 0x0DD6 ],
    [ 0x0E31, 0x0E31 ], [ 0x0E34, 0x0E3A ], [ 0x0E47, 0x0E4E ],
    [ 0x0EB1, 0x0EB1 ], [ 0x0EB4, 0x0EB9 ], [ 0x0EBB, 0x0EBC ],
    [ 0x0EC8, 0x0ECD ], [ 0x0F18, 0x0F19 ], [ 0x0F35, 0x0F35 ],
    [ 0x0F37, 0x0F37 ], [ 0x0F39, 0x0F39 ], [ 0x0F71, 0x0F7E ],
    [ 0x0F80, 0x0F84 ], [ 0x0F86, 0x0F87 ], [ 0x0F90, 0x0F97 ],
    [ 0x0F99, 0x0FBC ], [ 0x0FC6, 0x0FC6 ], [ 0x102D, 0x1030 ],
    [ 0x1032, 0x1032 ], [ 0x1036, 0x1037 ], [ 0x1039, 0x1039 ],
    [ 0x1058, 0x1059 ], [ 0x1160, 0x11FF ], [ 0x135F, 0x135F ],
    [ 0x1712, 0x1714 ], [ 0x1732, 0x1734 ], [ 0x1752, 0x1753 ],
    [ 0x1772, 0x1773 ], [ 0x17B4, 0x17B5 ], [ 0x17B7, 0x17BD ],
    [ 0x17C6, 0x17C6 ], [ 0x17C9, 0x17D3 ], [ 0x17DD, 0x17DD ],
    [ 0x180B, 0x180D ], [ 0x18A9, 0x18A9 ], [ 0x1920, 0x1922 ],
    [ 0x1927, 0x1928 ], [ 0x1932, 0x1932 ], [ 0x1939, 0x193B ],
    [ 0x1A17, 0x1A18 ], [ 0x1B00, 0x1B03 ], [ 0x1B34, 0x1B34 ],
    [ 0x1B36, 0x1B3A ], [ 0x1B3C, 0x1B3C ], [ 0x1B42, 0x1B42 ],
    [ 0x1B6B, 0x1B73 ], [ 0x1DC0, 0x1DCA ], [ 0x1DFE, 0x1DFF ],
    [ 0x200B, 0x200F ], [ 0x202A, 0x202E ], [ 0x2060, 0x2063 ],
    [ 0x206A, 0x206F ], [ 0x20D0, 0x20EF ], [ 0x302A, 0x302F ],
    [ 0x3099, 0x309A ], [ 0xA806, 0xA806 ], [ 0xA80B, 0xA80B ],
    [ 0xA825, 0xA826 ], [ 0xFB1E, 0xFB1E ], [ 0xFE00, 0xFE0F ],
    [ 0xFE20, 0xFE23 ], [ 0xFEFF, 0xFEFF ], [ 0xFFF9, 0xFFFB ],
    [ 0x10A01, 0x10A03 ], [ 0x10A05, 0x10A06 ], [ 0x10A0C, 0x10A0F ],
    [ 0x10A38, 0x10A3A ], [ 0x10A3F, 0x10A3F ], [ 0x1D167, 0x1D169 ],
    [ 0x1D173, 0x1D182 ], [ 0x1D185, 0x1D18B ], [ 0x1D1AA, 0x1D1AD ],
    [ 0x1D242, 0x1D244 ], [ 0xE0001, 0xE0001 ], [ 0xE0020, 0xE007F ],
    [ 0xE0100, 0xE01EF ]
]

},{}],17:[function(require,module,exports){
"use strict"

var defaults = require('defaults')
var combining = require('./combining')

var DEFAULTS = {
  nul: 0,
  control: 0
}

module.exports = function wcwidth(str) {
  return wcswidth(str, DEFAULTS)
}

module.exports.config = function(opts) {
  opts = defaults(opts || {}, DEFAULTS)
  return function wcwidth(str) {
    return wcswidth(str, opts)
  }
}

/*
 *  The following functions define the column width of an ISO 10646
 *  character as follows:
 *  - The null character (U+0000) has a column width of 0.
 *  - Other C0/C1 control characters and DEL will lead to a return value
 *    of -1.
 *  - Non-spacing and enclosing combining characters (general category
 *    code Mn or Me in the
 *    Unicode database) have a column width of 0.
 *  - SOFT HYPHEN (U+00AD) has a column width of 1.
 *  - Other format characters (general category code Cf in the Unicode
 *    database) and ZERO WIDTH
 *    SPACE (U+200B) have a column width of 0.
 *  - Hangul Jamo medial vowels and final consonants (U+1160-U+11FF)
 *    have a column width of 0.
 *  - Spacing characters in the East Asian Wide (W) or East Asian
 *    Full-width (F) category as
 *    defined in Unicode Technical Report #11 have a column width of 2.
 *  - All remaining characters (including all printable ISO 8859-1 and
 *    WGL4 characters, Unicode control characters, etc.) have a column
 *    width of 1.
 *  This implementation assumes that characters are encoded in ISO 10646.
*/

function wcswidth(str, opts) {
  if (typeof str !== 'string') return wcwidth(str, opts)

  var s = 0
  for (var i = 0; i < str.length; i++) {
    var n = wcwidth(str.charCodeAt(i), opts)
    if (n < 0) return -1
    s += n
  }

  return s
}

function wcwidth(ucs, opts) {
  // test for 8-bit control characters
  if (ucs === 0) return opts.nul
  if (ucs < 32 || (ucs >= 0x7f && ucs < 0xa0)) return opts.control

  // binary search in table of non-spacing characters
  if (bisearch(ucs)) return 0

  // if we arrive here, ucs is not a combining or C0/C1 control character
  return 1 +
      (ucs >= 0x1100 &&
       (ucs <= 0x115f ||                       // Hangul Jamo init. consonants
        ucs == 0x2329 || ucs == 0x232a ||
        (ucs >= 0x2e80 && ucs <= 0xa4cf &&
         ucs != 0x303f) ||                     // CJK ... Yi
        (ucs >= 0xac00 && ucs <= 0xd7a3) ||    // Hangul Syllables
        (ucs >= 0xf900 && ucs <= 0xfaff) ||    // CJK Compatibility Ideographs
        (ucs >= 0xfe10 && ucs <= 0xfe19) ||    // Vertical forms
        (ucs >= 0xfe30 && ucs <= 0xfe6f) ||    // CJK Compatibility Forms
        (ucs >= 0xff00 && ucs <= 0xff60) ||    // Fullwidth Forms
        (ucs >= 0xffe0 && ucs <= 0xffe6) ||
        (ucs >= 0x20000 && ucs <= 0x2fffd) ||
        (ucs >= 0x30000 && ucs <= 0x3fffd)));
}

function bisearch(ucs) {
  var min = 0
  var max = combining.length - 1
  var mid

  if (ucs < combining[0][0] || ucs > combining[max][1]) return false

  while (max >= min) {
    mid = Math.floor((min + max) / 2)
    if (ucs > combining[mid][1]) min = mid + 1
    else if (ucs < combining[mid][0]) max = mid - 1
    else return true
  }

  return false
}

},{"./combining":16,"defaults":13}],18:[function(require,module,exports){
'use strict'

exports.byteLength = byteLength
exports.toByteArray = toByteArray
exports.fromByteArray = fromByteArray

var lookup = []
var revLookup = []
var Arr = typeof Uint8Array !== 'undefined' ? Uint8Array : Array

var code = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
for (var i = 0, len = code.length; i < len; ++i) {
  lookup[i] = code[i]
  revLookup[code.charCodeAt(i)] = i
}

// Support decoding URL-safe base64 strings, as Node.js does.
// See: https://en.wikipedia.org/wiki/Base64#URL_applications
revLookup['-'.charCodeAt(0)] = 62
revLookup['_'.charCodeAt(0)] = 63

function getLens (b64) {
  var len = b64.length

  if (len % 4 > 0) {
    throw new Error('Invalid string. Length must be a multiple of 4')
  }

  // Trim off extra bytes after placeholder bytes are found
  // See: https://github.com/beatgammit/base64-js/issues/42
  var validLen = b64.indexOf('=')
  if (validLen === -1) validLen = len

  var placeHoldersLen = validLen === len
    ? 0
    : 4 - (validLen % 4)

  return [validLen, placeHoldersLen]
}

// base64 is 4/3 + up to two characters of the original data
function byteLength (b64) {
  var lens = getLens(b64)
  var validLen = lens[0]
  var placeHoldersLen = lens[1]
  return ((validLen + placeHoldersLen) * 3 / 4) - placeHoldersLen
}

function _byteLength (b64, validLen, placeHoldersLen) {
  return ((validLen + placeHoldersLen) * 3 / 4) - placeHoldersLen
}

function toByteArray (b64) {
  var tmp
  var lens = getLens(b64)
  var validLen = lens[0]
  var placeHoldersLen = lens[1]

  var arr = new Arr(_byteLength(b64, validLen, placeHoldersLen))

  var curByte = 0

  // if there are placeholders, only get up to the last complete 4 chars
  var len = placeHoldersLen > 0
    ? validLen - 4
    : validLen

  var i
  for (i = 0; i < len; i += 4) {
    tmp =
      (revLookup[b64.charCodeAt(i)] << 18) |
      (revLookup[b64.charCodeAt(i + 1)] << 12) |
      (revLookup[b64.charCodeAt(i + 2)] << 6) |
      revLookup[b64.charCodeAt(i + 3)]
    arr[curByte++] = (tmp >> 16) & 0xFF
    arr[curByte++] = (tmp >> 8) & 0xFF
    arr[curByte++] = tmp & 0xFF
  }

  if (placeHoldersLen === 2) {
    tmp =
      (revLookup[b64.charCodeAt(i)] << 2) |
      (revLookup[b64.charCodeAt(i + 1)] >> 4)
    arr[curByte++] = tmp & 0xFF
  }

  if (placeHoldersLen === 1) {
    tmp =
      (revLookup[b64.charCodeAt(i)] << 10) |
      (revLookup[b64.charCodeAt(i + 1)] << 4) |
      (revLookup[b64.charCodeAt(i + 2)] >> 2)
    arr[curByte++] = (tmp >> 8) & 0xFF
    arr[curByte++] = tmp & 0xFF
  }

  return arr
}

function tripletToBase64 (num) {
  return lookup[num >> 18 & 0x3F] +
    lookup[num >> 12 & 0x3F] +
    lookup[num >> 6 & 0x3F] +
    lookup[num & 0x3F]
}

function encodeChunk (uint8, start, end) {
  var tmp
  var output = []
  for (var i = start; i < end; i += 3) {
    tmp =
      ((uint8[i] << 16) & 0xFF0000) +
      ((uint8[i + 1] << 8) & 0xFF00) +
      (uint8[i + 2] & 0xFF)
    output.push(tripletToBase64(tmp))
  }
  return output.join('')
}

function fromByteArray (uint8) {
  var tmp
  var len = uint8.length
  var extraBytes = len % 3 // if we have 1 byte left, pad 2 bytes
  var parts = []
  var maxChunkLength = 16383 // must be multiple of 3

  // go through the array every three bytes, we'll deal with trailing stuff later
  for (var i = 0, len2 = len - extraBytes; i < len2; i += maxChunkLength) {
    parts.push(encodeChunk(uint8, i, (i + maxChunkLength) > len2 ? len2 : (i + maxChunkLength)))
  }

  // pad the end with zeros, but make sure to not forget the extra bytes
  if (extraBytes === 1) {
    tmp = uint8[len - 1]
    parts.push(
      lookup[tmp >> 2] +
      lookup[(tmp << 4) & 0x3F] +
      '=='
    )
  } else if (extraBytes === 2) {
    tmp = (uint8[len - 2] << 8) + uint8[len - 1]
    parts.push(
      lookup[tmp >> 10] +
      lookup[(tmp >> 4) & 0x3F] +
      lookup[(tmp << 2) & 0x3F] +
      '='
    )
  }

  return parts.join('')
}

},{}],19:[function(require,module,exports){
(function (Buffer){(function (){
/*!
 * The buffer module from node.js, for the browser.
 *
 * @author   Feross Aboukhadijeh <https://feross.org>
 * @license  MIT
 */
/* eslint-disable no-proto */

'use strict'

var base64 = require('base64-js')
var ieee754 = require('ieee754')

exports.Buffer = Buffer
exports.SlowBuffer = SlowBuffer
exports.INSPECT_MAX_BYTES = 50

var K_MAX_LENGTH = 0x7fffffff
exports.kMaxLength = K_MAX_LENGTH

/**
 * If `Buffer.TYPED_ARRAY_SUPPORT`:
 *   === true    Use Uint8Array implementation (fastest)
 *   === false   Print warning and recommend using `buffer` v4.x which has an Object
 *               implementation (most compatible, even IE6)
 *
 * Browsers that support typed arrays are IE 10+, Firefox 4+, Chrome 7+, Safari 5.1+,
 * Opera 11.6+, iOS 4.2+.
 *
 * We report that the browser does not support typed arrays if the are not subclassable
 * using __proto__. Firefox 4-29 lacks support for adding new properties to `Uint8Array`
 * (See: https://bugzilla.mozilla.org/show_bug.cgi?id=695438). IE 10 lacks support
 * for __proto__ and has a buggy typed array implementation.
 */
Buffer.TYPED_ARRAY_SUPPORT = typedArraySupport()

if (!Buffer.TYPED_ARRAY_SUPPORT && typeof console !== 'undefined' &&
    typeof console.error === 'function') {
  console.error(
    'This browser lacks typed array (Uint8Array) support which is required by ' +
    '`buffer` v5.x. Use `buffer` v4.x if you require old browser support.'
  )
}

function typedArraySupport () {
  // Can typed array instances can be augmented?
  try {
    var arr = new Uint8Array(1)
    arr.__proto__ = { __proto__: Uint8Array.prototype, foo: function () { return 42 } }
    return arr.foo() === 42
  } catch (e) {
    return false
  }
}

Object.defineProperty(Buffer.prototype, 'parent', {
  enumerable: true,
  get: function () {
    if (!Buffer.isBuffer(this)) return undefined
    return this.buffer
  }
})

Object.defineProperty(Buffer.prototype, 'offset', {
  enumerable: true,
  get: function () {
    if (!Buffer.isBuffer(this)) return undefined
    return this.byteOffset
  }
})

function createBuffer (length) {
  if (length > K_MAX_LENGTH) {
    throw new RangeError('The value "' + length + '" is invalid for option "size"')
  }
  // Return an augmented `Uint8Array` instance
  var buf = new Uint8Array(length)
  buf.__proto__ = Buffer.prototype
  return buf
}

/**
 * The Buffer constructor returns instances of `Uint8Array` that have their
 * prototype changed to `Buffer.prototype`. Furthermore, `Buffer` is a subclass of
 * `Uint8Array`, so the returned instances will have all the node `Buffer` methods
 * and the `Uint8Array` methods. Square bracket notation works as expected -- it
 * returns a single octet.
 *
 * The `Uint8Array` prototype remains unmodified.
 */

function Buffer (arg, encodingOrOffset, length) {
  // Common case.
  if (typeof arg === 'number') {
    if (typeof encodingOrOffset === 'string') {
      throw new TypeError(
        'The "string" argument must be of type string. Received type number'
      )
    }
    return allocUnsafe(arg)
  }
  return from(arg, encodingOrOffset, length)
}

// Fix subarray() in ES2016. See: https://github.com/feross/buffer/pull/97
if (typeof Symbol !== 'undefined' && Symbol.species != null &&
    Buffer[Symbol.species] === Buffer) {
  Object.defineProperty(Buffer, Symbol.species, {
    value: null,
    configurable: true,
    enumerable: false,
    writable: false
  })
}

Buffer.poolSize = 8192 // not used by this implementation

function from (value, encodingOrOffset, length) {
  if (typeof value === 'string') {
    return fromString(value, encodingOrOffset)
  }

  if (ArrayBuffer.isView(value)) {
    return fromArrayLike(value)
  }

  if (value == null) {
    throw TypeError(
      'The first argument must be one of type string, Buffer, ArrayBuffer, Array, ' +
      'or Array-like Object. Received type ' + (typeof value)
    )
  }

  if (isInstance(value, ArrayBuffer) ||
      (value && isInstance(value.buffer, ArrayBuffer))) {
    return fromArrayBuffer(value, encodingOrOffset, length)
  }

  if (typeof value === 'number') {
    throw new TypeError(
      'The "value" argument must not be of type number. Received type number'
    )
  }

  var valueOf = value.valueOf && value.valueOf()
  if (valueOf != null && valueOf !== value) {
    return Buffer.from(valueOf, encodingOrOffset, length)
  }

  var b = fromObject(value)
  if (b) return b

  if (typeof Symbol !== 'undefined' && Symbol.toPrimitive != null &&
      typeof value[Symbol.toPrimitive] === 'function') {
    return Buffer.from(
      value[Symbol.toPrimitive]('string'), encodingOrOffset, length
    )
  }

  throw new TypeError(
    'The first argument must be one of type string, Buffer, ArrayBuffer, Array, ' +
    'or Array-like Object. Received type ' + (typeof value)
  )
}

/**
 * Functionally equivalent to Buffer(arg, encoding) but throws a TypeError
 * if value is a number.
 * Buffer.from(str[, encoding])
 * Buffer.from(array)
 * Buffer.from(buffer)
 * Buffer.from(arrayBuffer[, byteOffset[, length]])
 **/
Buffer.from = function (value, encodingOrOffset, length) {
  return from(value, encodingOrOffset, length)
}

// Note: Change prototype *after* Buffer.from is defined to workaround Chrome bug:
// https://github.com/feross/buffer/pull/148
Buffer.prototype.__proto__ = Uint8Array.prototype
Buffer.__proto__ = Uint8Array

function assertSize (size) {
  if (typeof size !== 'number') {
    throw new TypeError('"size" argument must be of type number')
  } else if (size < 0) {
    throw new RangeError('The value "' + size + '" is invalid for option "size"')
  }
}

function alloc (size, fill, encoding) {
  assertSize(size)
  if (size <= 0) {
    return createBuffer(size)
  }
  if (fill !== undefined) {
    // Only pay attention to encoding if it's a string. This
    // prevents accidentally sending in a number that would
    // be interpretted as a start offset.
    return typeof encoding === 'string'
      ? createBuffer(size).fill(fill, encoding)
      : createBuffer(size).fill(fill)
  }
  return createBuffer(size)
}

/**
 * Creates a new filled Buffer instance.
 * alloc(size[, fill[, encoding]])
 **/
Buffer.alloc = function (size, fill, encoding) {
  return alloc(size, fill, encoding)
}

function allocUnsafe (size) {
  assertSize(size)
  return createBuffer(size < 0 ? 0 : checked(size) | 0)
}

/**
 * Equivalent to Buffer(num), by default creates a non-zero-filled Buffer instance.
 * */
Buffer.allocUnsafe = function (size) {
  return allocUnsafe(size)
}
/**
 * Equivalent to SlowBuffer(num), by default creates a non-zero-filled Buffer instance.
 */
Buffer.allocUnsafeSlow = function (size) {
  return allocUnsafe(size)
}

function fromString (string, encoding) {
  if (typeof encoding !== 'string' || encoding === '') {
    encoding = 'utf8'
  }

  if (!Buffer.isEncoding(encoding)) {
    throw new TypeError('Unknown encoding: ' + encoding)
  }

  var length = byteLength(string, encoding) | 0
  var buf = createBuffer(length)

  var actual = buf.write(string, encoding)

  if (actual !== length) {
    // Writing a hex string, for example, that contains invalid characters will
    // cause everything after the first invalid character to be ignored. (e.g.
    // 'abxxcd' will be treated as 'ab')
    buf = buf.slice(0, actual)
  }

  return buf
}

function fromArrayLike (array) {
  var length = array.length < 0 ? 0 : checked(array.length) | 0
  var buf = createBuffer(length)
  for (var i = 0; i < length; i += 1) {
    buf[i] = array[i] & 255
  }
  return buf
}

function fromArrayBuffer (array, byteOffset, length) {
  if (byteOffset < 0 || array.byteLength < byteOffset) {
    throw new RangeError('"offset" is outside of buffer bounds')
  }

  if (array.byteLength < byteOffset + (length || 0)) {
    throw new RangeError('"length" is outside of buffer bounds')
  }

  var buf
  if (byteOffset === undefined && length === undefined) {
    buf = new Uint8Array(array)
  } else if (length === undefined) {
    buf = new Uint8Array(array, byteOffset)
  } else {
    buf = new Uint8Array(array, byteOffset, length)
  }

  // Return an augmented `Uint8Array` instance
  buf.__proto__ = Buffer.prototype
  return buf
}

function fromObject (obj) {
  if (Buffer.isBuffer(obj)) {
    var len = checked(obj.length) | 0
    var buf = createBuffer(len)

    if (buf.length === 0) {
      return buf
    }

    obj.copy(buf, 0, 0, len)
    return buf
  }

  if (obj.length !== undefined) {
    if (typeof obj.length !== 'number' || numberIsNaN(obj.length)) {
      return createBuffer(0)
    }
    return fromArrayLike(obj)
  }

  if (obj.type === 'Buffer' && Array.isArray(obj.data)) {
    return fromArrayLike(obj.data)
  }
}

function checked (length) {
  // Note: cannot use `length < K_MAX_LENGTH` here because that fails when
  // length is NaN (which is otherwise coerced to zero.)
  if (length >= K_MAX_LENGTH) {
    throw new RangeError('Attempt to allocate Buffer larger than maximum ' +
                         'size: 0x' + K_MAX_LENGTH.toString(16) + ' bytes')
  }
  return length | 0
}

function SlowBuffer (length) {
  if (+length != length) { // eslint-disable-line eqeqeq
    length = 0
  }
  return Buffer.alloc(+length)
}

Buffer.isBuffer = function isBuffer (b) {
  return b != null && b._isBuffer === true &&
    b !== Buffer.prototype // so Buffer.isBuffer(Buffer.prototype) will be false
}

Buffer.compare = function compare (a, b) {
  if (isInstance(a, Uint8Array)) a = Buffer.from(a, a.offset, a.byteLength)
  if (isInstance(b, Uint8Array)) b = Buffer.from(b, b.offset, b.byteLength)
  if (!Buffer.isBuffer(a) || !Buffer.isBuffer(b)) {
    throw new TypeError(
      'The "buf1", "buf2" arguments must be one of type Buffer or Uint8Array'
    )
  }

  if (a === b) return 0

  var x = a.length
  var y = b.length

  for (var i = 0, len = Math.min(x, y); i < len; ++i) {
    if (a[i] !== b[i]) {
      x = a[i]
      y = b[i]
      break
    }
  }

  if (x < y) return -1
  if (y < x) return 1
  return 0
}

Buffer.isEncoding = function isEncoding (encoding) {
  switch (String(encoding).toLowerCase()) {
    case 'hex':
    case 'utf8':
    case 'utf-8':
    case 'ascii':
    case 'latin1':
    case 'binary':
    case 'base64':
    case 'ucs2':
    case 'ucs-2':
    case 'utf16le':
    case 'utf-16le':
      return true
    default:
      return false
  }
}

Buffer.concat = function concat (list, length) {
  if (!Array.isArray(list)) {
    throw new TypeError('"list" argument must be an Array of Buffers')
  }

  if (list.length === 0) {
    return Buffer.alloc(0)
  }

  var i
  if (length === undefined) {
    length = 0
    for (i = 0; i < list.length; ++i) {
      length += list[i].length
    }
  }

  var buffer = Buffer.allocUnsafe(length)
  var pos = 0
  for (i = 0; i < list.length; ++i) {
    var buf = list[i]
    if (isInstance(buf, Uint8Array)) {
      buf = Buffer.from(buf)
    }
    if (!Buffer.isBuffer(buf)) {
      throw new TypeError('"list" argument must be an Array of Buffers')
    }
    buf.copy(buffer, pos)
    pos += buf.length
  }
  return buffer
}

function byteLength (string, encoding) {
  if (Buffer.isBuffer(string)) {
    return string.length
  }
  if (ArrayBuffer.isView(string) || isInstance(string, ArrayBuffer)) {
    return string.byteLength
  }
  if (typeof string !== 'string') {
    throw new TypeError(
      'The "string" argument must be one of type string, Buffer, or ArrayBuffer. ' +
      'Received type ' + typeof string
    )
  }

  var len = string.length
  var mustMatch = (arguments.length > 2 && arguments[2] === true)
  if (!mustMatch && len === 0) return 0

  // Use a for loop to avoid recursion
  var loweredCase = false
  for (;;) {
    switch (encoding) {
      case 'ascii':
      case 'latin1':
      case 'binary':
        return len
      case 'utf8':
      case 'utf-8':
        return utf8ToBytes(string).length
      case 'ucs2':
      case 'ucs-2':
      case 'utf16le':
      case 'utf-16le':
        return len * 2
      case 'hex':
        return len >>> 1
      case 'base64':
        return base64ToBytes(string).length
      default:
        if (loweredCase) {
          return mustMatch ? -1 : utf8ToBytes(string).length // assume utf8
        }
        encoding = ('' + encoding).toLowerCase()
        loweredCase = true
    }
  }
}
Buffer.byteLength = byteLength

function slowToString (encoding, start, end) {
  var loweredCase = false

  // No need to verify that "this.length <= MAX_UINT32" since it's a read-only
  // property of a typed array.

  // This behaves neither like String nor Uint8Array in that we set start/end
  // to their upper/lower bounds if the value passed is out of range.
  // undefined is handled specially as per ECMA-262 6th Edition,
  // Section 13.3.3.7 Runtime Semantics: KeyedBindingInitialization.
  if (start === undefined || start < 0) {
    start = 0
  }
  // Return early if start > this.length. Done here to prevent potential uint32
  // coercion fail below.
  if (start > this.length) {
    return ''
  }

  if (end === undefined || end > this.length) {
    end = this.length
  }

  if (end <= 0) {
    return ''
  }

  // Force coersion to uint32. This will also coerce falsey/NaN values to 0.
  end >>>= 0
  start >>>= 0

  if (end <= start) {
    return ''
  }

  if (!encoding) encoding = 'utf8'

  while (true) {
    switch (encoding) {
      case 'hex':
        return hexSlice(this, start, end)

      case 'utf8':
      case 'utf-8':
        return utf8Slice(this, start, end)

      case 'ascii':
        return asciiSlice(this, start, end)

      case 'latin1':
      case 'binary':
        return latin1Slice(this, start, end)

      case 'base64':
        return base64Slice(this, start, end)

      case 'ucs2':
      case 'ucs-2':
      case 'utf16le':
      case 'utf-16le':
        return utf16leSlice(this, start, end)

      default:
        if (loweredCase) throw new TypeError('Unknown encoding: ' + encoding)
        encoding = (encoding + '').toLowerCase()
        loweredCase = true
    }
  }
}

// This property is used by `Buffer.isBuffer` (and the `is-buffer` npm package)
// to detect a Buffer instance. It's not possible to use `instanceof Buffer`
// reliably in a browserify context because there could be multiple different
// copies of the 'buffer' package in use. This method works even for Buffer
// instances that were created from another copy of the `buffer` package.
// See: https://github.com/feross/buffer/issues/154
Buffer.prototype._isBuffer = true

function swap (b, n, m) {
  var i = b[n]
  b[n] = b[m]
  b[m] = i
}

Buffer.prototype.swap16 = function swap16 () {
  var len = this.length
  if (len % 2 !== 0) {
    throw new RangeError('Buffer size must be a multiple of 16-bits')
  }
  for (var i = 0; i < len; i += 2) {
    swap(this, i, i + 1)
  }
  return this
}

Buffer.prototype.swap32 = function swap32 () {
  var len = this.length
  if (len % 4 !== 0) {
    throw new RangeError('Buffer size must be a multiple of 32-bits')
  }
  for (var i = 0; i < len; i += 4) {
    swap(this, i, i + 3)
    swap(this, i + 1, i + 2)
  }
  return this
}

Buffer.prototype.swap64 = function swap64 () {
  var len = this.length
  if (len % 8 !== 0) {
    throw new RangeError('Buffer size must be a multiple of 64-bits')
  }
  for (var i = 0; i < len; i += 8) {
    swap(this, i, i + 7)
    swap(this, i + 1, i + 6)
    swap(this, i + 2, i + 5)
    swap(this, i + 3, i + 4)
  }
  return this
}

Buffer.prototype.toString = function toString () {
  var length = this.length
  if (length === 0) return ''
  if (arguments.length === 0) return utf8Slice(this, 0, length)
  return slowToString.apply(this, arguments)
}

Buffer.prototype.toLocaleString = Buffer.prototype.toString

Buffer.prototype.equals = function equals (b) {
  if (!Buffer.isBuffer(b)) throw new TypeError('Argument must be a Buffer')
  if (this === b) return true
  return Buffer.compare(this, b) === 0
}

Buffer.prototype.inspect = function inspect () {
  var str = ''
  var max = exports.INSPECT_MAX_BYTES
  str = this.toString('hex', 0, max).replace(/(.{2})/g, '$1 ').trim()
  if (this.length > max) str += ' ... '
  return '<Buffer ' + str + '>'
}

Buffer.prototype.compare = function compare (target, start, end, thisStart, thisEnd) {
  if (isInstance(target, Uint8Array)) {
    target = Buffer.from(target, target.offset, target.byteLength)
  }
  if (!Buffer.isBuffer(target)) {
    throw new TypeError(
      'The "target" argument must be one of type Buffer or Uint8Array. ' +
      'Received type ' + (typeof target)
    )
  }

  if (start === undefined) {
    start = 0
  }
  if (end === undefined) {
    end = target ? target.length : 0
  }
  if (thisStart === undefined) {
    thisStart = 0
  }
  if (thisEnd === undefined) {
    thisEnd = this.length
  }

  if (start < 0 || end > target.length || thisStart < 0 || thisEnd > this.length) {
    throw new RangeError('out of range index')
  }

  if (thisStart >= thisEnd && start >= end) {
    return 0
  }
  if (thisStart >= thisEnd) {
    return -1
  }
  if (start >= end) {
    return 1
  }

  start >>>= 0
  end >>>= 0
  thisStart >>>= 0
  thisEnd >>>= 0

  if (this === target) return 0

  var x = thisEnd - thisStart
  var y = end - start
  var len = Math.min(x, y)

  var thisCopy = this.slice(thisStart, thisEnd)
  var targetCopy = target.slice(start, end)

  for (var i = 0; i < len; ++i) {
    if (thisCopy[i] !== targetCopy[i]) {
      x = thisCopy[i]
      y = targetCopy[i]
      break
    }
  }

  if (x < y) return -1
  if (y < x) return 1
  return 0
}

// Finds either the first index of `val` in `buffer` at offset >= `byteOffset`,
// OR the last index of `val` in `buffer` at offset <= `byteOffset`.
//
// Arguments:
// - buffer - a Buffer to search
// - val - a string, Buffer, or number
// - byteOffset - an index into `buffer`; will be clamped to an int32
// - encoding - an optional encoding, relevant is val is a string
// - dir - true for indexOf, false for lastIndexOf
function bidirectionalIndexOf (buffer, val, byteOffset, encoding, dir) {
  // Empty buffer means no match
  if (buffer.length === 0) return -1

  // Normalize byteOffset
  if (typeof byteOffset === 'string') {
    encoding = byteOffset
    byteOffset = 0
  } else if (byteOffset > 0x7fffffff) {
    byteOffset = 0x7fffffff
  } else if (byteOffset < -0x80000000) {
    byteOffset = -0x80000000
  }
  byteOffset = +byteOffset // Coerce to Number.
  if (numberIsNaN(byteOffset)) {
    // byteOffset: it it's undefined, null, NaN, "foo", etc, search whole buffer
    byteOffset = dir ? 0 : (buffer.length - 1)
  }

  // Normalize byteOffset: negative offsets start from the end of the buffer
  if (byteOffset < 0) byteOffset = buffer.length + byteOffset
  if (byteOffset >= buffer.length) {
    if (dir) return -1
    else byteOffset = buffer.length - 1
  } else if (byteOffset < 0) {
    if (dir) byteOffset = 0
    else return -1
  }

  // Normalize val
  if (typeof val === 'string') {
    val = Buffer.from(val, encoding)
  }

  // Finally, search either indexOf (if dir is true) or lastIndexOf
  if (Buffer.isBuffer(val)) {
    // Special case: looking for empty string/buffer always fails
    if (val.length === 0) {
      return -1
    }
    return arrayIndexOf(buffer, val, byteOffset, encoding, dir)
  } else if (typeof val === 'number') {
    val = val & 0xFF // Search for a byte value [0-255]
    if (typeof Uint8Array.prototype.indexOf === 'function') {
      if (dir) {
        return Uint8Array.prototype.indexOf.call(buffer, val, byteOffset)
      } else {
        return Uint8Array.prototype.lastIndexOf.call(buffer, val, byteOffset)
      }
    }
    return arrayIndexOf(buffer, [ val ], byteOffset, encoding, dir)
  }

  throw new TypeError('val must be string, number or Buffer')
}

function arrayIndexOf (arr, val, byteOffset, encoding, dir) {
  var indexSize = 1
  var arrLength = arr.length
  var valLength = val.length

  if (encoding !== undefined) {
    encoding = String(encoding).toLowerCase()
    if (encoding === 'ucs2' || encoding === 'ucs-2' ||
        encoding === 'utf16le' || encoding === 'utf-16le') {
      if (arr.length < 2 || val.length < 2) {
        return -1
      }
      indexSize = 2
      arrLength /= 2
      valLength /= 2
      byteOffset /= 2
    }
  }

  function read (buf, i) {
    if (indexSize === 1) {
      return buf[i]
    } else {
      return buf.readUInt16BE(i * indexSize)
    }
  }

  var i
  if (dir) {
    var foundIndex = -1
    for (i = byteOffset; i < arrLength; i++) {
      if (read(arr, i) === read(val, foundIndex === -1 ? 0 : i - foundIndex)) {
        if (foundIndex === -1) foundIndex = i
        if (i - foundIndex + 1 === valLength) return foundIndex * indexSize
      } else {
        if (foundIndex !== -1) i -= i - foundIndex
        foundIndex = -1
      }
    }
  } else {
    if (byteOffset + valLength > arrLength) byteOffset = arrLength - valLength
    for (i = byteOffset; i >= 0; i--) {
      var found = true
      for (var j = 0; j < valLength; j++) {
        if (read(arr, i + j) !== read(val, j)) {
          found = false
          break
        }
      }
      if (found) return i
    }
  }

  return -1
}

Buffer.prototype.includes = function includes (val, byteOffset, encoding) {
  return this.indexOf(val, byteOffset, encoding) !== -1
}

Buffer.prototype.indexOf = function indexOf (val, byteOffset, encoding) {
  return bidirectionalIndexOf(this, val, byteOffset, encoding, true)
}

Buffer.prototype.lastIndexOf = function lastIndexOf (val, byteOffset, encoding) {
  return bidirectionalIndexOf(this, val, byteOffset, encoding, false)
}

function hexWrite (buf, string, offset, length) {
  offset = Number(offset) || 0
  var remaining = buf.length - offset
  if (!length) {
    length = remaining
  } else {
    length = Number(length)
    if (length > remaining) {
      length = remaining
    }
  }

  var strLen = string.length

  if (length > strLen / 2) {
    length = strLen / 2
  }
  for (var i = 0; i < length; ++i) {
    var parsed = parseInt(string.substr(i * 2, 2), 16)
    if (numberIsNaN(parsed)) return i
    buf[offset + i] = parsed
  }
  return i
}

function utf8Write (buf, string, offset, length) {
  return blitBuffer(utf8ToBytes(string, buf.length - offset), buf, offset, length)
}

function asciiWrite (buf, string, offset, length) {
  return blitBuffer(asciiToBytes(string), buf, offset, length)
}

function latin1Write (buf, string, offset, length) {
  return asciiWrite(buf, string, offset, length)
}

function base64Write (buf, string, offset, length) {
  return blitBuffer(base64ToBytes(string), buf, offset, length)
}

function ucs2Write (buf, string, offset, length) {
  return blitBuffer(utf16leToBytes(string, buf.length - offset), buf, offset, length)
}

Buffer.prototype.write = function write (string, offset, length, encoding) {
  // Buffer#write(string)
  if (offset === undefined) {
    encoding = 'utf8'
    length = this.length
    offset = 0
  // Buffer#write(string, encoding)
  } else if (length === undefined && typeof offset === 'string') {
    encoding = offset
    length = this.length
    offset = 0
  // Buffer#write(string, offset[, length][, encoding])
  } else if (isFinite(offset)) {
    offset = offset >>> 0
    if (isFinite(length)) {
      length = length >>> 0
      if (encoding === undefined) encoding = 'utf8'
    } else {
      encoding = length
      length = undefined
    }
  } else {
    throw new Error(
      'Buffer.write(string, encoding, offset[, length]) is no longer supported'
    )
  }

  var remaining = this.length - offset
  if (length === undefined || length > remaining) length = remaining

  if ((string.length > 0 && (length < 0 || offset < 0)) || offset > this.length) {
    throw new RangeError('Attempt to write outside buffer bounds')
  }

  if (!encoding) encoding = 'utf8'

  var loweredCase = false
  for (;;) {
    switch (encoding) {
      case 'hex':
        return hexWrite(this, string, offset, length)

      case 'utf8':
      case 'utf-8':
        return utf8Write(this, string, offset, length)

      case 'ascii':
        return asciiWrite(this, string, offset, length)

      case 'latin1':
      case 'binary':
        return latin1Write(this, string, offset, length)

      case 'base64':
        // Warning: maxLength not taken into account in base64Write
        return base64Write(this, string, offset, length)

      case 'ucs2':
      case 'ucs-2':
      case 'utf16le':
      case 'utf-16le':
        return ucs2Write(this, string, offset, length)

      default:
        if (loweredCase) throw new TypeError('Unknown encoding: ' + encoding)
        encoding = ('' + encoding).toLowerCase()
        loweredCase = true
    }
  }
}

Buffer.prototype.toJSON = function toJSON () {
  return {
    type: 'Buffer',
    data: Array.prototype.slice.call(this._arr || this, 0)
  }
}

function base64Slice (buf, start, end) {
  if (start === 0 && end === buf.length) {
    return base64.fromByteArray(buf)
  } else {
    return base64.fromByteArray(buf.slice(start, end))
  }
}

function utf8Slice (buf, start, end) {
  end = Math.min(buf.length, end)
  var res = []

  var i = start
  while (i < end) {
    var firstByte = buf[i]
    var codePoint = null
    var bytesPerSequence = (firstByte > 0xEF) ? 4
      : (firstByte > 0xDF) ? 3
        : (firstByte > 0xBF) ? 2
          : 1

    if (i + bytesPerSequence <= end) {
      var secondByte, thirdByte, fourthByte, tempCodePoint

      switch (bytesPerSequence) {
        case 1:
          if (firstByte < 0x80) {
            codePoint = firstByte
          }
          break
        case 2:
          secondByte = buf[i + 1]
          if ((secondByte & 0xC0) === 0x80) {
            tempCodePoint = (firstByte & 0x1F) << 0x6 | (secondByte & 0x3F)
            if (tempCodePoint > 0x7F) {
              codePoint = tempCodePoint
            }
          }
          break
        case 3:
          secondByte = buf[i + 1]
          thirdByte = buf[i + 2]
          if ((secondByte & 0xC0) === 0x80 && (thirdByte & 0xC0) === 0x80) {
            tempCodePoint = (firstByte & 0xF) << 0xC | (secondByte & 0x3F) << 0x6 | (thirdByte & 0x3F)
            if (tempCodePoint > 0x7FF && (tempCodePoint < 0xD800 || tempCodePoint > 0xDFFF)) {
              codePoint = tempCodePoint
            }
          }
          break
        case 4:
          secondByte = buf[i + 1]
          thirdByte = buf[i + 2]
          fourthByte = buf[i + 3]
          if ((secondByte & 0xC0) === 0x80 && (thirdByte & 0xC0) === 0x80 && (fourthByte & 0xC0) === 0x80) {
            tempCodePoint = (firstByte & 0xF) << 0x12 | (secondByte & 0x3F) << 0xC | (thirdByte & 0x3F) << 0x6 | (fourthByte & 0x3F)
            if (tempCodePoint > 0xFFFF && tempCodePoint < 0x110000) {
              codePoint = tempCodePoint
            }
          }
      }
    }

    if (codePoint === null) {
      // we did not generate a valid codePoint so insert a
      // replacement char (U+FFFD) and advance only 1 byte
      codePoint = 0xFFFD
      bytesPerSequence = 1
    } else if (codePoint > 0xFFFF) {
      // encode to utf16 (surrogate pair dance)
      codePoint -= 0x10000
      res.push(codePoint >>> 10 & 0x3FF | 0xD800)
      codePoint = 0xDC00 | codePoint & 0x3FF
    }

    res.push(codePoint)
    i += bytesPerSequence
  }

  return decodeCodePointsArray(res)
}

// Based on http://stackoverflow.com/a/22747272/680742, the browser with
// the lowest limit is Chrome, with 0x10000 args.
// We go 1 magnitude less, for safety
var MAX_ARGUMENTS_LENGTH = 0x1000

function decodeCodePointsArray (codePoints) {
  var len = codePoints.length
  if (len <= MAX_ARGUMENTS_LENGTH) {
    return String.fromCharCode.apply(String, codePoints) // avoid extra slice()
  }

  // Decode in chunks to avoid "call stack size exceeded".
  var res = ''
  var i = 0
  while (i < len) {
    res += String.fromCharCode.apply(
      String,
      codePoints.slice(i, i += MAX_ARGUMENTS_LENGTH)
    )
  }
  return res
}

function asciiSlice (buf, start, end) {
  var ret = ''
  end = Math.min(buf.length, end)

  for (var i = start; i < end; ++i) {
    ret += String.fromCharCode(buf[i] & 0x7F)
  }
  return ret
}

function latin1Slice (buf, start, end) {
  var ret = ''
  end = Math.min(buf.length, end)

  for (var i = start; i < end; ++i) {
    ret += String.fromCharCode(buf[i])
  }
  return ret
}

function hexSlice (buf, start, end) {
  var len = buf.length

  if (!start || start < 0) start = 0
  if (!end || end < 0 || end > len) end = len

  var out = ''
  for (var i = start; i < end; ++i) {
    out += toHex(buf[i])
  }
  return out
}

function utf16leSlice (buf, start, end) {
  var bytes = buf.slice(start, end)
  var res = ''
  for (var i = 0; i < bytes.length; i += 2) {
    res += String.fromCharCode(bytes[i] + (bytes[i + 1] * 256))
  }
  return res
}

Buffer.prototype.slice = function slice (start, end) {
  var len = this.length
  start = ~~start
  end = end === undefined ? len : ~~end

  if (start < 0) {
    start += len
    if (start < 0) start = 0
  } else if (start > len) {
    start = len
  }

  if (end < 0) {
    end += len
    if (end < 0) end = 0
  } else if (end > len) {
    end = len
  }

  if (end < start) end = start

  var newBuf = this.subarray(start, end)
  // Return an augmented `Uint8Array` instance
  newBuf.__proto__ = Buffer.prototype
  return newBuf
}

/*
 * Need to make sure that buffer isn't trying to write out of bounds.
 */
function checkOffset (offset, ext, length) {
  if ((offset % 1) !== 0 || offset < 0) throw new RangeError('offset is not uint')
  if (offset + ext > length) throw new RangeError('Trying to access beyond buffer length')
}

Buffer.prototype.readUIntLE = function readUIntLE (offset, byteLength, noAssert) {
  offset = offset >>> 0
  byteLength = byteLength >>> 0
  if (!noAssert) checkOffset(offset, byteLength, this.length)

  var val = this[offset]
  var mul = 1
  var i = 0
  while (++i < byteLength && (mul *= 0x100)) {
    val += this[offset + i] * mul
  }

  return val
}

Buffer.prototype.readUIntBE = function readUIntBE (offset, byteLength, noAssert) {
  offset = offset >>> 0
  byteLength = byteLength >>> 0
  if (!noAssert) {
    checkOffset(offset, byteLength, this.length)
  }

  var val = this[offset + --byteLength]
  var mul = 1
  while (byteLength > 0 && (mul *= 0x100)) {
    val += this[offset + --byteLength] * mul
  }

  return val
}

Buffer.prototype.readUInt8 = function readUInt8 (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 1, this.length)
  return this[offset]
}

Buffer.prototype.readUInt16LE = function readUInt16LE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 2, this.length)
  return this[offset] | (this[offset + 1] << 8)
}

Buffer.prototype.readUInt16BE = function readUInt16BE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 2, this.length)
  return (this[offset] << 8) | this[offset + 1]
}

Buffer.prototype.readUInt32LE = function readUInt32LE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 4, this.length)

  return ((this[offset]) |
      (this[offset + 1] << 8) |
      (this[offset + 2] << 16)) +
      (this[offset + 3] * 0x1000000)
}

Buffer.prototype.readUInt32BE = function readUInt32BE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 4, this.length)

  return (this[offset] * 0x1000000) +
    ((this[offset + 1] << 16) |
    (this[offset + 2] << 8) |
    this[offset + 3])
}

Buffer.prototype.readIntLE = function readIntLE (offset, byteLength, noAssert) {
  offset = offset >>> 0
  byteLength = byteLength >>> 0
  if (!noAssert) checkOffset(offset, byteLength, this.length)

  var val = this[offset]
  var mul = 1
  var i = 0
  while (++i < byteLength && (mul *= 0x100)) {
    val += this[offset + i] * mul
  }
  mul *= 0x80

  if (val >= mul) val -= Math.pow(2, 8 * byteLength)

  return val
}

Buffer.prototype.readIntBE = function readIntBE (offset, byteLength, noAssert) {
  offset = offset >>> 0
  byteLength = byteLength >>> 0
  if (!noAssert) checkOffset(offset, byteLength, this.length)

  var i = byteLength
  var mul = 1
  var val = this[offset + --i]
  while (i > 0 && (mul *= 0x100)) {
    val += this[offset + --i] * mul
  }
  mul *= 0x80

  if (val >= mul) val -= Math.pow(2, 8 * byteLength)

  return val
}

Buffer.prototype.readInt8 = function readInt8 (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 1, this.length)
  if (!(this[offset] & 0x80)) return (this[offset])
  return ((0xff - this[offset] + 1) * -1)
}

Buffer.prototype.readInt16LE = function readInt16LE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 2, this.length)
  var val = this[offset] | (this[offset + 1] << 8)
  return (val & 0x8000) ? val | 0xFFFF0000 : val
}

Buffer.prototype.readInt16BE = function readInt16BE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 2, this.length)
  var val = this[offset + 1] | (this[offset] << 8)
  return (val & 0x8000) ? val | 0xFFFF0000 : val
}

Buffer.prototype.readInt32LE = function readInt32LE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 4, this.length)

  return (this[offset]) |
    (this[offset + 1] << 8) |
    (this[offset + 2] << 16) |
    (this[offset + 3] << 24)
}

Buffer.prototype.readInt32BE = function readInt32BE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 4, this.length)

  return (this[offset] << 24) |
    (this[offset + 1] << 16) |
    (this[offset + 2] << 8) |
    (this[offset + 3])
}

Buffer.prototype.readFloatLE = function readFloatLE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 4, this.length)
  return ieee754.read(this, offset, true, 23, 4)
}

Buffer.prototype.readFloatBE = function readFloatBE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 4, this.length)
  return ieee754.read(this, offset, false, 23, 4)
}

Buffer.prototype.readDoubleLE = function readDoubleLE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 8, this.length)
  return ieee754.read(this, offset, true, 52, 8)
}

Buffer.prototype.readDoubleBE = function readDoubleBE (offset, noAssert) {
  offset = offset >>> 0
  if (!noAssert) checkOffset(offset, 8, this.length)
  return ieee754.read(this, offset, false, 52, 8)
}

function checkInt (buf, value, offset, ext, max, min) {
  if (!Buffer.isBuffer(buf)) throw new TypeError('"buffer" argument must be a Buffer instance')
  if (value > max || value < min) throw new RangeError('"value" argument is out of bounds')
  if (offset + ext > buf.length) throw new RangeError('Index out of range')
}

Buffer.prototype.writeUIntLE = function writeUIntLE (value, offset, byteLength, noAssert) {
  value = +value
  offset = offset >>> 0
  byteLength = byteLength >>> 0
  if (!noAssert) {
    var maxBytes = Math.pow(2, 8 * byteLength) - 1
    checkInt(this, value, offset, byteLength, maxBytes, 0)
  }

  var mul = 1
  var i = 0
  this[offset] = value & 0xFF
  while (++i < byteLength && (mul *= 0x100)) {
    this[offset + i] = (value / mul) & 0xFF
  }

  return offset + byteLength
}

Buffer.prototype.writeUIntBE = function writeUIntBE (value, offset, byteLength, noAssert) {
  value = +value
  offset = offset >>> 0
  byteLength = byteLength >>> 0
  if (!noAssert) {
    var maxBytes = Math.pow(2, 8 * byteLength) - 1
    checkInt(this, value, offset, byteLength, maxBytes, 0)
  }

  var i = byteLength - 1
  var mul = 1
  this[offset + i] = value & 0xFF
  while (--i >= 0 && (mul *= 0x100)) {
    this[offset + i] = (value / mul) & 0xFF
  }

  return offset + byteLength
}

Buffer.prototype.writeUInt8 = function writeUInt8 (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 1, 0xff, 0)
  this[offset] = (value & 0xff)
  return offset + 1
}

Buffer.prototype.writeUInt16LE = function writeUInt16LE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 2, 0xffff, 0)
  this[offset] = (value & 0xff)
  this[offset + 1] = (value >>> 8)
  return offset + 2
}

Buffer.prototype.writeUInt16BE = function writeUInt16BE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 2, 0xffff, 0)
  this[offset] = (value >>> 8)
  this[offset + 1] = (value & 0xff)
  return offset + 2
}

Buffer.prototype.writeUInt32LE = function writeUInt32LE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 4, 0xffffffff, 0)
  this[offset + 3] = (value >>> 24)
  this[offset + 2] = (value >>> 16)
  this[offset + 1] = (value >>> 8)
  this[offset] = (value & 0xff)
  return offset + 4
}

Buffer.prototype.writeUInt32BE = function writeUInt32BE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 4, 0xffffffff, 0)
  this[offset] = (value >>> 24)
  this[offset + 1] = (value >>> 16)
  this[offset + 2] = (value >>> 8)
  this[offset + 3] = (value & 0xff)
  return offset + 4
}

Buffer.prototype.writeIntLE = function writeIntLE (value, offset, byteLength, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) {
    var limit = Math.pow(2, (8 * byteLength) - 1)

    checkInt(this, value, offset, byteLength, limit - 1, -limit)
  }

  var i = 0
  var mul = 1
  var sub = 0
  this[offset] = value & 0xFF
  while (++i < byteLength && (mul *= 0x100)) {
    if (value < 0 && sub === 0 && this[offset + i - 1] !== 0) {
      sub = 1
    }
    this[offset + i] = ((value / mul) >> 0) - sub & 0xFF
  }

  return offset + byteLength
}

Buffer.prototype.writeIntBE = function writeIntBE (value, offset, byteLength, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) {
    var limit = Math.pow(2, (8 * byteLength) - 1)

    checkInt(this, value, offset, byteLength, limit - 1, -limit)
  }

  var i = byteLength - 1
  var mul = 1
  var sub = 0
  this[offset + i] = value & 0xFF
  while (--i >= 0 && (mul *= 0x100)) {
    if (value < 0 && sub === 0 && this[offset + i + 1] !== 0) {
      sub = 1
    }
    this[offset + i] = ((value / mul) >> 0) - sub & 0xFF
  }

  return offset + byteLength
}

Buffer.prototype.writeInt8 = function writeInt8 (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 1, 0x7f, -0x80)
  if (value < 0) value = 0xff + value + 1
  this[offset] = (value & 0xff)
  return offset + 1
}

Buffer.prototype.writeInt16LE = function writeInt16LE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 2, 0x7fff, -0x8000)
  this[offset] = (value & 0xff)
  this[offset + 1] = (value >>> 8)
  return offset + 2
}

Buffer.prototype.writeInt16BE = function writeInt16BE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 2, 0x7fff, -0x8000)
  this[offset] = (value >>> 8)
  this[offset + 1] = (value & 0xff)
  return offset + 2
}

Buffer.prototype.writeInt32LE = function writeInt32LE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 4, 0x7fffffff, -0x80000000)
  this[offset] = (value & 0xff)
  this[offset + 1] = (value >>> 8)
  this[offset + 2] = (value >>> 16)
  this[offset + 3] = (value >>> 24)
  return offset + 4
}

Buffer.prototype.writeInt32BE = function writeInt32BE (value, offset, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) checkInt(this, value, offset, 4, 0x7fffffff, -0x80000000)
  if (value < 0) value = 0xffffffff + value + 1
  this[offset] = (value >>> 24)
  this[offset + 1] = (value >>> 16)
  this[offset + 2] = (value >>> 8)
  this[offset + 3] = (value & 0xff)
  return offset + 4
}

function checkIEEE754 (buf, value, offset, ext, max, min) {
  if (offset + ext > buf.length) throw new RangeError('Index out of range')
  if (offset < 0) throw new RangeError('Index out of range')
}

function writeFloat (buf, value, offset, littleEndian, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) {
    checkIEEE754(buf, value, offset, 4, 3.4028234663852886e+38, -3.4028234663852886e+38)
  }
  ieee754.write(buf, value, offset, littleEndian, 23, 4)
  return offset + 4
}

Buffer.prototype.writeFloatLE = function writeFloatLE (value, offset, noAssert) {
  return writeFloat(this, value, offset, true, noAssert)
}

Buffer.prototype.writeFloatBE = function writeFloatBE (value, offset, noAssert) {
  return writeFloat(this, value, offset, false, noAssert)
}

function writeDouble (buf, value, offset, littleEndian, noAssert) {
  value = +value
  offset = offset >>> 0
  if (!noAssert) {
    checkIEEE754(buf, value, offset, 8, 1.7976931348623157E+308, -1.7976931348623157E+308)
  }
  ieee754.write(buf, value, offset, littleEndian, 52, 8)
  return offset + 8
}

Buffer.prototype.writeDoubleLE = function writeDoubleLE (value, offset, noAssert) {
  return writeDouble(this, value, offset, true, noAssert)
}

Buffer.prototype.writeDoubleBE = function writeDoubleBE (value, offset, noAssert) {
  return writeDouble(this, value, offset, false, noAssert)
}

// copy(targetBuffer, targetStart=0, sourceStart=0, sourceEnd=buffer.length)
Buffer.prototype.copy = function copy (target, targetStart, start, end) {
  if (!Buffer.isBuffer(target)) throw new TypeError('argument should be a Buffer')
  if (!start) start = 0
  if (!end && end !== 0) end = this.length
  if (targetStart >= target.length) targetStart = target.length
  if (!targetStart) targetStart = 0
  if (end > 0 && end < start) end = start

  // Copy 0 bytes; we're done
  if (end === start) return 0
  if (target.length === 0 || this.length === 0) return 0

  // Fatal error conditions
  if (targetStart < 0) {
    throw new RangeError('targetStart out of bounds')
  }
  if (start < 0 || start >= this.length) throw new RangeError('Index out of range')
  if (end < 0) throw new RangeError('sourceEnd out of bounds')

  // Are we oob?
  if (end > this.length) end = this.length
  if (target.length - targetStart < end - start) {
    end = target.length - targetStart + start
  }

  var len = end - start

  if (this === target && typeof Uint8Array.prototype.copyWithin === 'function') {
    // Use built-in when available, missing from IE11
    this.copyWithin(targetStart, start, end)
  } else if (this === target && start < targetStart && targetStart < end) {
    // descending copy from end
    for (var i = len - 1; i >= 0; --i) {
      target[i + targetStart] = this[i + start]
    }
  } else {
    Uint8Array.prototype.set.call(
      target,
      this.subarray(start, end),
      targetStart
    )
  }

  return len
}

// Usage:
//    buffer.fill(number[, offset[, end]])
//    buffer.fill(buffer[, offset[, end]])
//    buffer.fill(string[, offset[, end]][, encoding])
Buffer.prototype.fill = function fill (val, start, end, encoding) {
  // Handle string cases:
  if (typeof val === 'string') {
    if (typeof start === 'string') {
      encoding = start
      start = 0
      end = this.length
    } else if (typeof end === 'string') {
      encoding = end
      end = this.length
    }
    if (encoding !== undefined && typeof encoding !== 'string') {
      throw new TypeError('encoding must be a string')
    }
    if (typeof encoding === 'string' && !Buffer.isEncoding(encoding)) {
      throw new TypeError('Unknown encoding: ' + encoding)
    }
    if (val.length === 1) {
      var code = val.charCodeAt(0)
      if ((encoding === 'utf8' && code < 128) ||
          encoding === 'latin1') {
        // Fast path: If `val` fits into a single byte, use that numeric value.
        val = code
      }
    }
  } else if (typeof val === 'number') {
    val = val & 255
  }

  // Invalid ranges are not set to a default, so can range check early.
  if (start < 0 || this.length < start || this.length < end) {
    throw new RangeError('Out of range index')
  }

  if (end <= start) {
    return this
  }

  start = start >>> 0
  end = end === undefined ? this.length : end >>> 0

  if (!val) val = 0

  var i
  if (typeof val === 'number') {
    for (i = start; i < end; ++i) {
      this[i] = val
    }
  } else {
    var bytes = Buffer.isBuffer(val)
      ? val
      : Buffer.from(val, encoding)
    var len = bytes.length
    if (len === 0) {
      throw new TypeError('The value "' + val +
        '" is invalid for argument "value"')
    }
    for (i = 0; i < end - start; ++i) {
      this[i + start] = bytes[i % len]
    }
  }

  return this
}

// HELPER FUNCTIONS
// ================

var INVALID_BASE64_RE = /[^+/0-9A-Za-z-_]/g

function base64clean (str) {
  // Node takes equal signs as end of the Base64 encoding
  str = str.split('=')[0]
  // Node strips out invalid characters like \n and \t from the string, base64-js does not
  str = str.trim().replace(INVALID_BASE64_RE, '')
  // Node converts strings with length < 2 to ''
  if (str.length < 2) return ''
  // Node allows for non-padded base64 strings (missing trailing ===), base64-js does not
  while (str.length % 4 !== 0) {
    str = str + '='
  }
  return str
}

function toHex (n) {
  if (n < 16) return '0' + n.toString(16)
  return n.toString(16)
}

function utf8ToBytes (string, units) {
  units = units || Infinity
  var codePoint
  var length = string.length
  var leadSurrogate = null
  var bytes = []

  for (var i = 0; i < length; ++i) {
    codePoint = string.charCodeAt(i)

    // is surrogate component
    if (codePoint > 0xD7FF && codePoint < 0xE000) {
      // last char was a lead
      if (!leadSurrogate) {
        // no lead yet
        if (codePoint > 0xDBFF) {
          // unexpected trail
          if ((units -= 3) > -1) bytes.push(0xEF, 0xBF, 0xBD)
          continue
        } else if (i + 1 === length) {
          // unpaired lead
          if ((units -= 3) > -1) bytes.push(0xEF, 0xBF, 0xBD)
          continue
        }

        // valid lead
        leadSurrogate = codePoint

        continue
      }

      // 2 leads in a row
      if (codePoint < 0xDC00) {
        if ((units -= 3) > -1) bytes.push(0xEF, 0xBF, 0xBD)
        leadSurrogate = codePoint
        continue
      }

      // valid surrogate pair
      codePoint = (leadSurrogate - 0xD800 << 10 | codePoint - 0xDC00) + 0x10000
    } else if (leadSurrogate) {
      // valid bmp char, but last char was a lead
      if ((units -= 3) > -1) bytes.push(0xEF, 0xBF, 0xBD)
    }

    leadSurrogate = null

    // encode utf8
    if (codePoint < 0x80) {
      if ((units -= 1) < 0) break
      bytes.push(codePoint)
    } else if (codePoint < 0x800) {
      if ((units -= 2) < 0) break
      bytes.push(
        codePoint >> 0x6 | 0xC0,
        codePoint & 0x3F | 0x80
      )
    } else if (codePoint < 0x10000) {
      if ((units -= 3) < 0) break
      bytes.push(
        codePoint >> 0xC | 0xE0,
        codePoint >> 0x6 & 0x3F | 0x80,
        codePoint & 0x3F | 0x80
      )
    } else if (codePoint < 0x110000) {
      if ((units -= 4) < 0) break
      bytes.push(
        codePoint >> 0x12 | 0xF0,
        codePoint >> 0xC & 0x3F | 0x80,
        codePoint >> 0x6 & 0x3F | 0x80,
        codePoint & 0x3F | 0x80
      )
    } else {
      throw new Error('Invalid code point')
    }
  }

  return bytes
}

function asciiToBytes (str) {
  var byteArray = []
  for (var i = 0; i < str.length; ++i) {
    // Node's code seems to be doing this and not & 0x7F..
    byteArray.push(str.charCodeAt(i) & 0xFF)
  }
  return byteArray
}

function utf16leToBytes (str, units) {
  var c, hi, lo
  var byteArray = []
  for (var i = 0; i < str.length; ++i) {
    if ((units -= 2) < 0) break

    c = str.charCodeAt(i)
    hi = c >> 8
    lo = c % 256
    byteArray.push(lo)
    byteArray.push(hi)
  }

  return byteArray
}

function base64ToBytes (str) {
  return base64.toByteArray(base64clean(str))
}

function blitBuffer (src, dst, offset, length) {
  for (var i = 0; i < length; ++i) {
    if ((i + offset >= dst.length) || (i >= src.length)) break
    dst[i + offset] = src[i]
  }
  return i
}

// ArrayBuffer or Uint8Array objects from other contexts (i.e. iframes) do not pass
// the `instanceof` check but they should be treated as of that type.
// See: https://github.com/feross/buffer/issues/166
function isInstance (obj, type) {
  return obj instanceof type ||
    (obj != null && obj.constructor != null && obj.constructor.name != null &&
      obj.constructor.name === type.name)
}
function numberIsNaN (obj) {
  // For IE11 support
  return obj !== obj // eslint-disable-line no-self-compare
}

}).call(this)}).call(this,require("buffer").Buffer)
},{"base64-js":18,"buffer":19,"ieee754":20}],20:[function(require,module,exports){
/*! ieee754. BSD-3-Clause License. Feross Aboukhadijeh <https://feross.org/opensource> */
exports.read = function (buffer, offset, isLE, mLen, nBytes) {
  var e, m
  var eLen = (nBytes * 8) - mLen - 1
  var eMax = (1 << eLen) - 1
  var eBias = eMax >> 1
  var nBits = -7
  var i = isLE ? (nBytes - 1) : 0
  var d = isLE ? -1 : 1
  var s = buffer[offset + i]

  i += d

  e = s & ((1 << (-nBits)) - 1)
  s >>= (-nBits)
  nBits += eLen
  for (; nBits > 0; e = (e * 256) + buffer[offset + i], i += d, nBits -= 8) {}

  m = e & ((1 << (-nBits)) - 1)
  e >>= (-nBits)
  nBits += mLen
  for (; nBits > 0; m = (m * 256) + buffer[offset + i], i += d, nBits -= 8) {}

  if (e === 0) {
    e = 1 - eBias
  } else if (e === eMax) {
    return m ? NaN : ((s ? -1 : 1) * Infinity)
  } else {
    m = m + Math.pow(2, mLen)
    e = e - eBias
  }
  return (s ? -1 : 1) * m * Math.pow(2, e - mLen)
}

exports.write = function (buffer, value, offset, isLE, mLen, nBytes) {
  var e, m, c
  var eLen = (nBytes * 8) - mLen - 1
  var eMax = (1 << eLen) - 1
  var eBias = eMax >> 1
  var rt = (mLen === 23 ? Math.pow(2, -24) - Math.pow(2, -77) : 0)
  var i = isLE ? 0 : (nBytes - 1)
  var d = isLE ? 1 : -1
  var s = value < 0 || (value === 0 && 1 / value < 0) ? 1 : 0

  value = Math.abs(value)

  if (isNaN(value) || value === Infinity) {
    m = isNaN(value) ? 1 : 0
    e = eMax
  } else {
    e = Math.floor(Math.log(value) / Math.LN2)
    if (value * (c = Math.pow(2, -e)) < 1) {
      e--
      c *= 2
    }
    if (e + eBias >= 1) {
      value += rt / c
    } else {
      value += rt * Math.pow(2, 1 - eBias)
    }
    if (value * c >= 2) {
      e++
      c /= 2
    }

    if (e + eBias >= eMax) {
      m = 0
      e = eMax
    } else if (e + eBias >= 1) {
      m = ((value * c) - 1) * Math.pow(2, mLen)
      e = e + eBias
    } else {
      m = value * Math.pow(2, eBias - 1) * Math.pow(2, mLen)
      e = 0
    }
  }

  for (; mLen >= 8; buffer[offset + i] = m & 0xff, i += d, m /= 256, mLen -= 8) {}

  e = (e << mLen) | m
  eLen += mLen
  for (; eLen > 0; buffer[offset + i] = e & 0xff, i += d, e /= 256, eLen -= 8) {}

  buffer[offset + i - d] |= s * 128
}

},{}],21:[function(require,module,exports){
// shim for using process in browser
var process = module.exports = {};

// cached from whatever global is present so that test runners that stub it
// don't break things.  But we need to wrap it in a try catch in case it is
// wrapped in strict mode code which doesn't define any globals.  It's inside a
// function because try/catches deoptimize in certain engines.

var cachedSetTimeout;
var cachedClearTimeout;

function defaultSetTimout() {
    throw new Error('setTimeout has not been defined');
}
function defaultClearTimeout () {
    throw new Error('clearTimeout has not been defined');
}
(function () {
    try {
        if (typeof setTimeout === 'function') {
            cachedSetTimeout = setTimeout;
        } else {
            cachedSetTimeout = defaultSetTimout;
        }
    } catch (e) {
        cachedSetTimeout = defaultSetTimout;
    }
    try {
        if (typeof clearTimeout === 'function') {
            cachedClearTimeout = clearTimeout;
        } else {
            cachedClearTimeout = defaultClearTimeout;
        }
    } catch (e) {
        cachedClearTimeout = defaultClearTimeout;
    }
} ())
function runTimeout(fun) {
    if (cachedSetTimeout === setTimeout) {
        //normal enviroments in sane situations
        return setTimeout(fun, 0);
    }
    // if setTimeout wasn't available but was latter defined
    if ((cachedSetTimeout === defaultSetTimout || !cachedSetTimeout) && setTimeout) {
        cachedSetTimeout = setTimeout;
        return setTimeout(fun, 0);
    }
    try {
        // when when somebody has screwed with setTimeout but no I.E. maddness
        return cachedSetTimeout(fun, 0);
    } catch(e){
        try {
            // When we are in I.E. but the script has been evaled so I.E. doesn't trust the global object when called normally
            return cachedSetTimeout.call(null, fun, 0);
        } catch(e){
            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error
            return cachedSetTimeout.call(this, fun, 0);
        }
    }


}
function runClearTimeout(marker) {
    if (cachedClearTimeout === clearTimeout) {
        //normal enviroments in sane situations
        return clearTimeout(marker);
    }
    // if clearTimeout wasn't available but was latter defined
    if ((cachedClearTimeout === defaultClearTimeout || !cachedClearTimeout) && clearTimeout) {
        cachedClearTimeout = clearTimeout;
        return clearTimeout(marker);
    }
    try {
        // when when somebody has screwed with setTimeout but no I.E. maddness
        return cachedClearTimeout(marker);
    } catch (e){
        try {
            // When we are in I.E. but the script has been evaled so I.E. doesn't  trust the global object when called normally
            return cachedClearTimeout.call(null, marker);
        } catch (e){
            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error.
            // Some versions of I.E. have different rules for clearTimeout vs setTimeout
            return cachedClearTimeout.call(this, marker);
        }
    }



}
var queue = [];
var draining = false;
var currentQueue;
var queueIndex = -1;

function cleanUpNextTick() {
    if (!draining || !currentQueue) {
        return;
    }
    draining = false;
    if (currentQueue.length) {
        queue = currentQueue.concat(queue);
    } else {
        queueIndex = -1;
    }
    if (queue.length) {
        drainQueue();
    }
}

function drainQueue() {
    if (draining) {
        return;
    }
    var timeout = runTimeout(cleanUpNextTick);
    draining = true;

    var len = queue.length;
    while(len) {
        currentQueue = queue;
        queue = [];
        while (++queueIndex < len) {
            if (currentQueue) {
                currentQueue[queueIndex].run();
            }
        }
        queueIndex = -1;
        len = queue.length;
    }
    currentQueue = null;
    draining = false;
    runClearTimeout(timeout);
}

process.nextTick = function (fun) {
    var args = new Array(arguments.length - 1);
    if (arguments.length > 1) {
        for (var i = 1; i < arguments.length; i++) {
            args[i - 1] = arguments[i];
        }
    }
    queue.push(new Item(fun, args));
    if (queue.length === 1 && !draining) {
        runTimeout(drainQueue);
    }
};

// v8 likes predictible objects
function Item(fun, array) {
    this.fun = fun;
    this.array = array;
}
Item.prototype.run = function () {
    this.fun.apply(null, this.array);
};
process.title = 'browser';
process.browser = true;
process.env = {};
process.argv = [];
process.version = ''; // empty string to avoid regexp issues
process.versions = {};

function noop() {}

process.on = noop;
process.addListener = noop;
process.once = noop;
process.off = noop;
process.removeListener = noop;
process.removeAllListeners = noop;
process.emit = noop;
process.prependListener = noop;
process.prependOnceListener = noop;

process.listeners = function (name) { return [] }

process.binding = function (name) {
    throw new Error('process.binding is not supported');
};

process.cwd = function () { return '/' };
process.chdir = function (dir) {
    throw new Error('process.chdir is not supported');
};
process.umask = function() { return 0; };

},{}],22:[function(require,module,exports){
(function (setImmediate,clearImmediate){(function (){
var nextTick = require('process/browser.js').nextTick;
var apply = Function.prototype.apply;
var slice = Array.prototype.slice;
var immediateIds = {};
var nextImmediateId = 0;

// DOM APIs, for completeness

exports.setTimeout = function() {
  return new Timeout(apply.call(setTimeout, window, arguments), clearTimeout);
};
exports.setInterval = function() {
  return new Timeout(apply.call(setInterval, window, arguments), clearInterval);
};
exports.clearTimeout =
exports.clearInterval = function(timeout) { timeout.close(); };

function Timeout(id, clearFn) {
  this._id = id;
  this._clearFn = clearFn;
}
Timeout.prototype.unref = Timeout.prototype.ref = function() {};
Timeout.prototype.close = function() {
  this._clearFn.call(window, this._id);
};

// Does not start the time, just sets up the members needed.
exports.enroll = function(item, msecs) {
  clearTimeout(item._idleTimeoutId);
  item._idleTimeout = msecs;
};

exports.unenroll = function(item) {
  clearTimeout(item._idleTimeoutId);
  item._idleTimeout = -1;
};

exports._unrefActive = exports.active = function(item) {
  clearTimeout(item._idleTimeoutId);

  var msecs = item._idleTimeout;
  if (msecs >= 0) {
    item._idleTimeoutId = setTimeout(function onTimeout() {
      if (item._onTimeout)
        item._onTimeout();
    }, msecs);
  }
};

// That's not how node.js implements it but the exposed api is the same.
exports.setImmediate = typeof setImmediate === "function" ? setImmediate : function(fn) {
  var id = nextImmediateId++;
  var args = arguments.length < 2 ? false : slice.call(arguments, 1);

  immediateIds[id] = true;

  nextTick(function onNextTick() {
    if (immediateIds[id]) {
      // fn.call() is faster so we optimize for the common use-case
      // @see http://jsperf.com/call-apply-segu
      if (args) {
        fn.apply(null, args);
      } else {
        fn.call(null);
      }
      // Prevent ids from leaking
      exports.clearImmediate(id);
    }
  });

  return id;
};

exports.clearImmediate = typeof clearImmediate === "function" ? clearImmediate : function(id) {
  delete immediateIds[id];
};
}).call(this)}).call(this,require("timers").setImmediate,require("timers").clearImmediate)
},{"process/browser.js":21,"timers":22}]},{},[11]);
