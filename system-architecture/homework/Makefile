
TEXCC = pdflatex -interaction=nonstopmode -halt-on-error

hw1 hw2 hw3 hw4 hw5 hw6:
	$(TEXCC) $@.tex

clean:
	rm *.aux *.log *.pdf *.dvi *.fls *.fdb_latexmk -f

