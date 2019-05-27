#include "table.h"

void buildtree(tree **t, table p)
{
	for (int i = 0; i < p.n; i++)
		treeadd(t, p.cont[i]);
}

void treeadd(tree **t, elem x)
{
	if (!*t)
	{
		*t = new tree(x);
		return;
	}
	if (_mbscmp(x.key, (*t)->el.key) < 0)
	{
		if ((*t)->left)
			treeadd(&(*t)->left, x);
		else
			(*t)->left = new tree(x);
	}
	if (_mbscmp(x.key, (*t)->el.key) > 0)
	{
		if ((*t)->right)
			treeadd(&(*t)->right, x);
		else
			(*t)->right = new tree(x);
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

void treesort(table *t, tree *tr)
{
	t->n = 0;
	stack <tree *> s;
	bool toleft = true;
	tree *lastn = tr;
	if (tr)
	{
		s.push(lastn);
		while (!empty(s))
		{
			if (toleft)
			{
				while (lastn->left)
				{
					s.push(lastn);
					lastn = lastn->left;
				}
			}
			printf_s("%s\n", lastn->el.key);
			if (lastn->right)
			{
				lastn = lastn->right;
				toleft = true;
			}
			else
			{
				lastn = s.top();
				s.pop();
				toleft = false;
			}
		}
	}
}

void showtable(table t)
{
	for (int i = 0; i < t.n; i++)
		printf_s("%s	%s	%d\n", t.cont[i].key, t.cont[i].name, t.cont[i].amount);
}