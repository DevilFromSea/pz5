#include "table.h"

void buildtree(tree *t, table p)
{
	for (int i = 0; i < p.n; i++)
	{
		treeadd(t, p.cont[i], 0);
		printf_s("Element was put in tree\n");
	}
}

void treeadd(tree *t, elem x, int i)
{
	tree *b = t;
	if (!b)
	{
		b = new tree(x, i++);
		return;
	}
	if (_mbscmp(x.key, b->el.key) < 0)
	{
		if (b->left)
			treeadd(b->left, x, i);
		else
			b->left = new tree(x, i++);
	}
	if (_mbscmp(x.key, b->el.key) > 0)
	{
		if (b->right)
			treeadd(b->right, x, i);
		else
			b->right = new tree(x, i++);
	}
}

void buildtable(table *t)
{
	elem e;
	t->n = 0;
	FILE *f;
	fopen_s(&f, "WORK.txt", "r");
	while (!feof(f))
	{
		fscanf_s(f, "%s", e.key, 9);
		fscanf_s(f, "%s", e.name, 21);
		fscanf_s(f, "%d", &e.amount);
		add(t, e);
	}
	fclose(f);
	printf_s("Table was successfully built.\n");
	for (int i = 0; i < t->n; i++)
		printf_s("%s	%s	%d\n", t->cont[i].key, t->cont[i].name, t->cont[i].amount);
}

void add(table *t, elem e)
{
	if (t->n < Nmax)
	{
		for (int k = 0; k < t->n; k++)
			if (!_mbscmp(t->cont[k].key, e.key))
			{
				t->cont[k].amount += e.amount;
				return;
			}
		t->cont[t->n] = e;
		t->n++;
	}
}

void quicksort(table *t, int m, int n)
{
	int a = m, b = n;
	elem temp, mid = t->cont[(m + n) / 2];
	while (a <= b)
	{
		while (_mbscmp(t->cont[a].key, mid.key) < 0)
			a++;
		while (_mbscmp(t->cont[b].key, mid.key) > 0)
			b--;
		if (a <= b) {
			temp = t->cont[a];
			t->cont[a] = t->cont[b];
			t->cont[b] = temp;
			a++;
			b--;
		}
	}
	if (m < b)
		quicksort(t, m, b);
	if (n > a)
		quicksort(t, a, n);
}

void treesort(table *t, int m, int n, tree *tree)
{
	int max = m;
	elem temp;
	while (tree->index != max)
	{
		tree->index = max;
		tree->left->index = 2 * tree->index + 1;
		tree->right->index = 2 * (tree->index + 1);
		if (tree->left->index <= n)
			if (_mbscmp(t->cont[tree->left->index].key, t->cont[tree->index].key) > 0)
				max = tree->left->index;
		if (tree->right->index <= n)
			if (_mbscmp(t->cont[tree->right->index].key, t->cont[max].key) > 0)
				max = tree->right->index;
		temp = t->cont[tree->index];
		t->cont[tree->index] = t->cont[max];
		t->cont[max] = temp;
	}
	for (m = (t->n - 1) / 2; m >= 0; m--)
		treesort(t, m, t->n - 1, tree);
	for (m = t->n - 1; m >= 1; m--)
	{
		temp = t->cont[0] = t->cont[m];
		t->cont[m] = temp;
		treesort(t, 0, m - 1, tree);
	}
}

void showtable(table t)
{
	for (int i = 0; i < t.n; i++)
		printf_s("%s	%s	%d\n", t.cont[i].key, t.cont[i].name, t.cont[i].amount);
}