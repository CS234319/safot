const term = require('./BrowserREPL').term

const getGlobals = () => {
	return term.getGlobals()
}

const getCursorPosition = () => {
	return term.getCursorPosition()
}

module.exports = {
	getGlobals: getGlobals,
	getCursorPosition: getCursorPosition
}