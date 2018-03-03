#include "comenzi.h"

// Eliberarea memoriei unei liste
void eliberare ( node** head )
{
	if ( (*head) != NULL && (*head)->next != NULL )
		eliberare ( &(*head)->next );
	// free ( (*head)->val.nume );
	free ( *head );
}

// Algoritmul de planificare
// Ultimul argument ne zice tipul de planificare
void planificator ( FILE* input, FILE* output, liste* state, char* buffer, int planificare )
{
	process running;
	running.x = GOL;
	int cuanta, permisiune;

	// Citirea variabilelor in functie de planificare
	switch ( planificare )
	{

		case 3:

			fscanf ( input, "%d\n", &cuanta );
			break;

		case 4:
		case 5:

			fscanf ( input, "%d\n", &cuanta );
			fscanf ( input, "%d\n", &permisiune );
			break;

		default:

			cuanta = 0;

			break;
	}

	// Citeste fiecare comanda si o executa
	while ( fgets ( buffer, 101, input ) )
	{
		switch ( buffer[0] )
		{
			case 't':

				tick ( state, &running, cuanta, planificare );

				break;

			case 'a':

				// Elimin primele 2 caractere din comanda, pentru a ramane doar procesul
				buffer = buffer + 2;
				process ps;
				ps = convert ( buffer );
			 	add ( &state->ready, ps, planificare );
				tick ( state, &running, cuanta, planificare );

				break;

			case 'm':

				madd ( &state->ready, buffer, planificare );
				tick ( state, &running, cuanta, planificare );

				break;

			case 'w':

				wait ( state, &running, planificare );
				tick ( state, &running, cuanta, planificare );

				break;

			case 'e':

				// Elimin primele 2 caractere din comanda, pentru a ramane doar procesul
				buffer = buffer + 2;
				buffer = strtok ( buffer, "\n" );
				event ( state, buffer, planificare );
				tick ( state, &running, cuanta, planificare );

				break;

			case 's':

				show ( output, running );

				break;
		}
		
	}
}


int main ( int argc, char** argv )
{
	// Declar si initializez listele ready si waiting
	liste* state = ( liste* ) malloc ( sizeof ( liste ) );

	init ( &state->ready );
	init ( &state->waiting );

	
	FILE* input;
	input = fopen ( argv[1], "r" );

	if ( !input )
		return 1;

	FILE* output;
	output = fopen ( argv[2], "w" );

	int select;
	fscanf ( input, "%d\n", &select );

	char *buffer;
	buffer = ( char* ) malloc ( 101 * sizeof ( char ) );

	planificator ( input, output, state, buffer, select );

	fclose ( input );
	fclose ( output );


	// Eliberarea memorie
	eliberare ( &state->ready );
	eliberare ( &state->waiting );
	free ( buffer );
	free ( state );

	return 0;
}