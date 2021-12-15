all:
	xelatex -shell-escape 00
	cp 00.tex Flue-report.pdf

clean:
	rm -f -d -r `cat .gitignore` 

zip: clean
	zip Flue-report-sources.zip * 
