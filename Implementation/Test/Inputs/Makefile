all: .extract

INPUTS=../../../mini-lisp*.tex

.PHONY: all

.extract: ./00.awk $(INPUTS)
	gawk -f $^
	@touch $@ 

clean:
	rm -f *.lisp *~ .extract

