
geese: miniaudio.h
	# gcc -O3 -Wall main.c -o geese -lSDL2
	gcc -O3 -Wall $$(pkg-config --cflags --libs gtk4) main.c -o geese

miniaudio.h:
	if [[ ! -f miniaudio.h ]]; then curl https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h -o miniaudio.h; fi

.PHONY: clean
clean:
	rm -fr geese 

.PHONY: install
install: geese
	./install.sh
