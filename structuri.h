// Structura unui proces
typedef struct process
{
	char nume[22];
	int x, y;
	int elapsed, increase, decrease;
}process;

// Structura unui nod dintr-o lista
typedef struct node
{
	process val;
	struct node* next;
}node;

// O structura de liste
typedef struct lists
{
	node* ready;
	node* waiting;
}liste;