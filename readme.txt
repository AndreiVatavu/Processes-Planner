								
								  Planificator
								 --------------

Timp alocat rezolvarii: 10 ore

Explicatia algoritmului
-----------------------
	Pentru rezolvarea problemei am creat la incput 3 structuri:
		- o structura pentru a descrie un proces ( nume, timp de executie,
		  prioritatea, timpul in care a fost in executie, increase ( cand se
		  face 2, prioritate procesului creste cu 1 ), decrease ( cand se face
		  -2 prioritatea procesului scade cu 1 )
		- o structura ce descrie nodul unei liste de procese
		- o structura ce contine doua liste ( ready si waiting ), pentru un apel
		  mai usor al listelor

Comanda a ( add )
-----------------
	Pentru aceasta comanda am creat functia add, care primeste ca parametri o
lista, un proces si tipul planificarii. Daca lista este goala, atunci primul
element din lista va fi procesul primit ca parametru, daca lista nu este goala
atunci, in functie de tipul planificarii, adaugarea procesului in coada ready se
va face la inceput sau in interior. Pentru FCFS si RR inserarea se va face in
fata, pentru SJF inserarea se va face dupa timpul de executie, astfel fiecare
proces se va adauga inainte de primul proces cu o durata de executie mai mare,
iar pentru PP si BONUS inserarea se va face tot in interior in functie de
permisiunea procesului, fiecare proces nou adaugat se va adauga inainte de
primul proces cu o permisiune mai mica.

Comanda ma ( multiple add )
---------------------------
	Pentru aceasta comanda am creat functia madd, care primeste ca parametri o
lista, un sir de caractere care contine toate procesele ce trebuie adaugate si
tipul planificarii. Parcurg sirul de caractere caracter cu caracter, iar cand am
gasit 3 spatii in sir, inseamna ca am parcurs un proces. Pe cel de-al treilea
spatiu pun terminatorul de sir NULL pentru a imi ramane un singur proces in
sirul de caractere, apoi cu ajutorul functiei "convert" transform stringul
intr-o variabila de tip proces, si adaug procesul obtinut in coada ready. Dupa
ce am adaugat procesul, mut pointer-ul siului catre inceputul urmatorului proces
si repet pasii anteriori, pana cand adaug toate procesele.

Functia convert
---------------
	Aceasta functie primeste ca argument un sir de caractere si-l transforma
intr-o variabila de tip proces. Pentru a face asta se parcurge sirul caracter
cu caracter si se construieste numele procesului pana cand se ajunge la primul
spatiu. Daca am ajuns la primul spatiu, dupa stiu ca urmeaza timpul de executie
a procesului si incep sa-l construiesc si pe acesta pana la urmatorul spatiu
de unde incepe prioritatea procesului.

Comanda tick
------------
	Am creat functia tick care primeste ca parametri listele ready si waiting
starea de running, cuanta si tipul planificarii. Se verifica daca se afla
vreun proces, daca nu se afla se adauga primul proces din coada ready. Daca in
running se afla deja un proces, atunci i se scade durata de viata cu 1 si
actualizez timpul in care procesul s-a aflat in executie, daca dupa ce am
scazut durata de viata a procesului acesta devine 0, atunci adaug un nou proces
in running. Pentru planificarile 3, 4 si 5 verific daca procesul si-a atins
cuanta, daca da, acesta este mutat in coada ready, iar in running se adauga un
nou proces, de asemenea variabila increase devine 0, iar increase creste cu 1
( am explicat la inceput ce fac aceste doua variabile ), daca decrease devine
-2, atunci scad prioritate procesului cu 1 ( doar pentru bonus ).
Daca tipul planificarii este 4 sau 5 atunci verific daca in coada ready exista
un proces cu o prioritate mai mare, daca da atunci adaug procesul din running in
ready, iar in running adaug procesul cu prioritatea mai mare, de asemenea
variabila increase devine 0, iar decrease scade cu 1, daca decrease devin -2
atunci prioritatea procesului scade cu 1.

Comanda w ( wait )
------------
	Adaug procesul din running in lista waiting, si maresc variabila increase
pentru procesul respectiv, daca increase devine 2, atunci maresc prioritatea
procesului cu 1.

Comanda e ( event )
-------------------
	Am creat functia event care cauta in lista waiting un proces, daca il
gaseste atunci il elimina din waiting si il adauga in ready.

Comanda s ( show )
------------------
	Functia show scrie intr-un fisier numele si durata unui proces primit ca
argument.


Functia planificator
--------------------
	Aceasta functie primeste ca parametri fisierul de intrare, fisierul in care
se vor face afisarile, listele ready si waiting, un buffer in care vor face
citirile si tipul planificarii. In functie de tipul planificarii se vor face
citirile necesare. Se va citi fiecare linie in buffer si se va verifica primul
caracter, iar in functie de acesta se va executa comanda aferenta.


	In functia main, declar listele, le initializez cu NULL, deschid fisierele,
citesc primul numar din fisierul de citire si apelez functia planificator cu
tipul planificarii pe care tocmai l-am citit.
