build: planificator

planificator: headers.h structuri.h prelucrare_siruri.h comenzi.h planificator.c
	gcc -Wall headers.h structuri.h prelucrare_siruri.h comenzi.h planificator.c -o planificator

run:
	./planificator

clean:
	rm -fr planificator
