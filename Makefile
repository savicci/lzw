#MAKEFILE
.PHONY: all clean tar checkInOut checkFilesSizes badExample

all: lzw.x

lzw.x: lzwcheck.cxx LZW.hxx LZW.cxx
	g++ -o lzwcheck.x lzwcheck.cxx LZW.cxx

clean:
	rm -f *.x *.lzw

tar:
	tar -zcvf ../GrzegorzKoziolProjekt.tar.gz ../LZWproject



#sprawdza poprawnosc zapisu i odczytu do plikow
#oraz rozmiar poczatkowego i skompresowanego pliku
checkCompression: all
	./lzwcheck.x -c < $(file).txt > $(file).lzw
	./lzwcheck.x -d < $(file).lzw > out$(file).txt
	diff -s $(file).txt out$(file).txt
	wc $(file).txt
	wc $(file).lzw

