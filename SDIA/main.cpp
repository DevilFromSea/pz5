#include "table.h"

int main()
{	
	setlocale(LC_CTYPE, "Russian");
	table t;
	tree *tr = NULL;
	int exitFlag = 0, n;
	buildtable(&t);
	printf_s("Which method would you prefer to sort the table?\n"
			"1. Quick sort\n"
			"2. Sort with using binary tree\n");
	while (!exitFlag)
	{
		printf("Enter the command number: ");
		if (!scanf_s("%d", &n))
		{
			printf_s("Error.");
			return 0;
		}
		switch (n)
		{
			printf_s("Sorting table...\n");
		case CMD_QUICK_SORT:		
			quicksort(&t, 0, t.n - 1);
			exitFlag = 1;
			break;
		case CMD_TREE_SORT:
			buildtree(&tr, t);
			treesort(&t, tr);
			exitFlag = 1;
			break;
		default:
			printf_s("Invalid choice.\n");
			break;
		}
	}
	printf_s("Table was successfully sorted.\n");
	showtable(t);
	system ("pause");
}