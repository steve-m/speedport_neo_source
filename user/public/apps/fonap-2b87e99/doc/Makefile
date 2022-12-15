HTML_FILES=reference-implementation.html
PDF_FILES=reference-implementation.pdf
all: $(HTML_FILES) $(PDF_FILES) 
# $(PDF_FILES) $(HTML_FILES)

pdf: $(PDF_FILES)

html: $(HTML_FILES)

reference-implementation.html: reference-implementation.txt
	ln -sf /usr/share/doc/asciidoc/doc/images/ .
	asciidoc -a data-uri -a icons -a toc -a toclevels=4 -a numbered reference-implementation.txt 

reference-implementation.pdf: reference-implementation.txt
	a2x -f pdf reference-implementation.txt

clean-html:
	rm reference-implementation.html
clean-pdf:
	rm reference-implementation.pdf
clean: clean-pdf clean-html
