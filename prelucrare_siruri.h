#include "headers.h"

process convert ( char* s )
{
	int n = 1, length = 0, i;
	process ps;
	// Initializez timpul de executie, prioritatea, increase si decrease cu 0
	// ( voi explica in readme la ce folosesc ultimele doua variabile)
	ps.x = 0;
	ps.y = 0;
	ps.increase = 0;
	ps.decrease = 0;
	
	for ( i = 0; i < strlen ( s ); i++ )
	{
		if ( s[i] == ' ' )
			n++;
		else
		{
			switch (n)
			{
				// Adaug numele procesului caracter cu caracter
				case 1:
					ps.nume[length] = s[i];
					length++;
					break;

				// Adaug timpul de executie
				case 2:
					ps.x = ps.x * 10 + ( s[i] - 48 );
					break;

				// Prioritatea
				case 3:
					ps.y = ps.y * 10 + ( s[i] - 48 );
					break;
			}
		}
	}

	// Adaug terminatorul de sir NULL
	ps.nume[length] = '\0';
	return ps;
}