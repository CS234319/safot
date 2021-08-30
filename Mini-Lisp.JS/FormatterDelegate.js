const browserTerminal = require('./BrowserTerminalInitiator')

const getGlobals = () => browserTerminal.getGlobals?.()
const matchParentheses = (lparenPos, rparenPos) => {
	return browserTerminal.matchParentheses?.(lparenPos, rparenPos)
}

module.exports = {
	getGlobals: getGlobals,
	matchParentheses: matchParentheses
}