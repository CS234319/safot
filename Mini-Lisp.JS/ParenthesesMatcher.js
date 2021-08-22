module.exports = class ParenthesesMatcher { 
	match(text, pos, shouldAllowInner) {
		if (pos < 0 || pos >= text.length) {
			return undefined
		}

		const startPos = this._getSearchStartPosition(text, pos, shouldAllowInner)

		if (startPos === undefined) {
			return undefined
		}

		const charAtPos = text[startPos]

		const endPos = this._iterate(startPos, text.length, charAtPos === '(',
			(counter, i) => {
				const currChar = text[i]
				if (currChar !== '(' && currChar !== ')') {
					return [false, counter]
				}

				counter += (currChar === '(' ? 1 : -1)

				return [counter === 0, counter]
			}
		)

		return endPos === undefined 
			? undefined 
			: 	[
					Math.min(startPos, endPos), 
					Math.max(startPos, endPos), 
					startPos !== pos
				]
	}

	_getSearchStartPosition(text, pos, shouldAllowInner) {
		const charAtPos = text[pos]
		if (charAtPos === '(' || charAtPos === ')') {
			return pos
		}

		if (!shouldAllowInner) {
			return undefined	
		} 

		for (const [isForward, target, stopper] of 
			[[true, ')', '('], [false, '(', ')']]) {
			const startPos = this._iterate(pos, text.length, isForward, 
				(_, i) => {
					return text[i] === stopper 
						? undefined
						: [text[i] === target, 0]
				}
			)
			
			if (startPos !== undefined)	{
				return startPos
			}
		}

		return undefined
	}

	_iterate(pos, textLength, isForward, callback) {
		let [counter, step, end] = isForward ? [1, 1, textLength] : [-1, -1, -1]
			
		for (let i = pos + step; i != end; i += step) {
			const ret = callback(counter, i)
			if (!ret) {
				return undefined
			}

			const [didFind, newCounter] = ret
			if (didFind) {
				return i
			}

			counter = newCounter
		}

		return undefined
	}
}