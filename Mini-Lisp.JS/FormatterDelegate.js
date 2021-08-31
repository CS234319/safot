const browserTerminal = require('./BrowserTerminalInitiator')

const getGlobals = () => browserTerminal.getGlobals?.()
const matchEnclosures = (lEncPos, rEncPos) => {
	return browserTerminal.matchEnclosures?.(lEncPos, rEncPos)
}

module.exports = {
	getGlobals: getGlobals,
	matchEnclosures: matchEnclosures
}