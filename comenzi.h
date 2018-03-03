#include "prelucrare_siruri.h"


// Initializarea unei liste
void init ( node** head )
{
	*head = NULL;
}


//Eliminarea unui element dintr-o coada
node* dequeue ( node** head )
{
	node* as;
	as = *head;
	*head = (*head)->next;
	return as;
}


// Inserarea unui element intr-o lista
// In funtie de planificare inserarea se face in fata sau in interiorul listei
// Ultimul argument specifica tipul de planificare
void add ( node** head, process ps, int planificare )
{
	node* new = ( node* ) malloc ( sizeof ( node ) );

	new->val = ps;

	// Daca lista este goala
	if ( *head == NULL )
	{
		new->next = NULL;
		*head = new;
	}
	else
	{
		node* current;
		current = *head;
		switch ( planificare )
		{
			// Inserarea se face in functie de durata de executie (SJF)
			case 2:
				if ( current->val.x > ps.x )
				{
					new->next = current;
					*head = new;
				}
				else
				{
					while ( current->next != NULL && current->next->val.x < ps.x )
						current = current->next;
					new->next = current->next;
					current->next = new;
				}
				break;

			// Inserarea se face in functie de prioritate ( PP si BONUS )
			case 5:
			case 4:
				if ( current->val.y < ps.y )
				{
					new->next = current;
					*head = new;
				}
				else
				{
					while ( current->next != NULL && current->next->val.y >= ps.y )
						current = current->next;
					new->next = current->next;
					current->next = new;
				}
				break;

			// Pentru FCFS si RR inserarea se face in fata
			default:
				new->next = NULL;
				while ( current->next != NULL )
					current = current->next;
				current->next = new;
				break;
		}
	}
}

// Inserarea mai multor elemente intr-o lista
void madd ( node** ready, char* s, int planificare )
{
	// Elimin primele trei caractere din sir ( "ma " ), pentru a ramane doar procesele
	s = s + 3;

	int n = 0, i;

	for ( i = 0; i < strlen ( s ); i++ )
	{
		// Daca caracterul curent este spatiu sau '\n' maresc n
		// Deoarece citirea s-a facut cu fgets, s-a citi si '\n' de la sfarsitul liniei
		if ( s[i] == ' ' || s[i] == '\n' )
			n++;
		if ( n == 3 )
		{
			// Resetez n
			n = 0;
			// Adaug terminatorul de sir dupa procesul curent
			s[i] = '\0';
			process ps;
			// Fac conversia unui string intr-un proces
			ps = convert ( s );
			// Adaug procesul in coada ready
			add ( ready, ps, planificare );
			// Pointez spre inceputul urmatorului proces
			s = s + strlen(s) + 1;
			// Resetez i pentru a face parcurgerea de la inceputul noului proces
			i = 0;
		}

	}
} 


// Ultimul argument zice tipul planificarii
void tick ( liste* state, process* running, int cuanta, int planificare )
{
	// Daca in starea running se afla un proces
	if ( running->x != GOL )
	{
		// Scad durata de viata
		running->x--;
		// Timpul in care procesul a fost in executie creste
		running->elapsed++;
		// Daca procesul si-a terminat esecutia,
		// adaug alt proces in running (daca exista)
		if ( running->x == 0 )
		{
			running->x = GOL;
			if ( state->ready != NULL )
			{
				node* head;
				head = dequeue ( &state->ready );
				*running = head->val;
				running->elapsed = 0;
				free (head);
			}
		}


		// Daca un proces si-a atins cuanta, este scos din running ( pentru RR si PP )
		if ( planificare >= 3 && running->x != GOL && running->elapsed >= cuanta )
		{
			running->decrease --;
			running->increase = 0;
			if ( planificare == 5 && running->decrease == -2 )
			{
				running->y--;
				running->decrease = 0;
			}
			// Se adauga alt proces
			add ( &state->ready, *running, planificare );
			running->x = GOL;
			if ( state->ready != NULL )
			{
				node* head;
				head = dequeue ( &state->ready );
				*running = head->val;
				running->elapsed = 0;
				free (head);
			}
		}

		// Daca in coada ready este un proces cu o prioritate mai mare decat a procesului
		// din running, atunci, acest proces, se trece in starea de running ( PP )
		if ( planificare >= 4 && state->ready != NULL && running->y < state->ready->val.y )
		{
			running->decrease --;
			running->increase = 0;
			if ( planificare == 5 && running->decrease == -2 )
			{
				running->y--;
				running->decrease = 0;
			}

			add ( &state->ready, *running, planificare );
			node* head;
			head = dequeue ( &state->ready );
			*running = head->val;
			running->elapsed = 0;
			free (head);
		}
	}
	else   // Daca in starea running nu se afla niciun proces
	{
		// Daca exista cel putin un proces in coada ready, se adauga
		if ( state->ready != NULL )
		{
			node* head;
			head = dequeue ( &state->ready );
			*running = head->val;
			running->elapsed = 0;
			free (head);
		}
	}
}


// Trece un proces din running in waiting
void wait ( liste* state, process* running, int planificare )
{
	if ( running->x != GOL )
	{
		running->increase++;
		if ( planificare == 5 && running->increase == 2 )
		{
			running->y++;
			running->increase = 0;
		}
		
		add ( &state->waiting, *running, 1 );
		running->x = GOL;
	}
}


// Scoate un proces din waiting
// Functia cauta procesul in lista waiting, daca exista il adauga in lista ready
void event ( liste* state, char* nume, int planificare )
{
	node* current;
	current = state->waiting;
	// Se verifica daca elementul cautat este chiar primul
	if ( strcmp ( state->waiting->val.nume, nume ) == 0 )
	{
		// Daca da se adauga procesul in lista ready
		add ( &state->ready, state->waiting->val, planificare );
		node* head;
		head = dequeue ( &state->waiting );
		free ( head );
	}
	else
	{
		// Se parcurge fiecare nod al listei waiting, pana cand se gaseste elementul cautat
		while ( current->next != NULL && strcmp ( current->next->val.nume, nume ) != 0 )
			current = current->next;
		if ( current->next != NULL )
		{
			// Se adauga procesul in lista ready, daca s-a gasit
			add ( &state->ready, current->next->val, planificare );
			node* head;
			head = dequeue ( &current->next );
			free ( head );
		}
	}
}


// Afisare informatii despre un proces
void show ( FILE* output, process ps )
{
	if ( ps.x != GOL )
		fprintf( output, "%s %d\n", ps.nume, ps.x );
	else
		fprintf( output, "\n" );
}