#include "table.h"

int compare(const void *a, const void *b)
{
	elem* arg1 = *(elem**)a;
	elem* arg2 = *(elem**)b;
	return _mbsicmp(arg1->key, arg2->key);
}

void buildptable(table *t)
{
	t->n = 0;
	FILE *f;
	fopen_s(&f, "PRICES.txt", "r");
	while (!feof(f))
	{
		elem *e = new elem;
		fscanf_s(f, "%s", e->key, Keymax);
		fscanf_s(f, "%d", &e->price);
		padd(t, e);
	}
	fclose(f);
	printf_s("Price table was successfully built.\n");
	for (int i = 0; i < t->n; i++) // Вывод таблицы на экран
		printf_s("%s	%d\n", t->cont[i]->key, t->cont[i]->price);
}

void buildtable(table *t)
{
	t->n = 0;
	FILE *f;
	fopen_s(&f, "WORK.txt", "r");
	while (!feof(f))
	{
		elem *e = new elem;
		fscanf_s(f, "%s", e->key, Keymax);
		fscanf_s(f, "%s", e->name, Namemax);
		fscanf_s(f, "%d", &e->amount);
		add(t, e);
	}
	fclose(f);
	printf_s("Table was successfully built.\n");
	for (int i = 0; i < t->n; i++)
		printf_s("%s	%s	%d\n", t->cont[i]->key, t->cont[i]->name, t->cont[i]->amount);
}

void add(table *t, elem *e)
{
	if (t->n < Nmax)
	{
		for (int k = 0; k < t->n; k++)
			if (!_mbscmp(t->cont[k]->key, e->key))
			{
				t->cont[k]->amount += e->amount;
				return;
			}
		t->cont[t->n] = e;
		t->n++;
	}
}

void padd(table *t, elem *e)
{
	if (t->n < Nmax)
	{
		t->cont[t->n] = e;
		t->n++;
	}
}

void buildtree(tree **t, table p)
{
   for (int i = 0; i < p.n; i++) // Создаём двоичное дерево поиска
	  treeadd(t, *p.cont[i]);
}

void treeadd(tree **t, elem x)
{
   if (!*t)
   {
	  *t = new tree(x);
	  return;
   }
   if (_mbscmp(x.key, (*t)->el.key) < 0)
	  if ((*t)->left)
		 treeadd(&(*t)->left, x);
	  else
		 (*t)->left = new tree(x);
   if (_mbscmp(x.key, (*t)->el.key) > 0)
	  if ((*t)->right)
		 treeadd(&(*t)->right, x);
	  else
		 (*t)->right = new tree(x);
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
		 add(t, &lastn->el);
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

void finaltable(table *t, table pt, bool a)
{
   for (int i = 0; i < pt.n; i++) // Соединяем таблицы
	  combine(*pt.cont[i], t, a);
}

void combine(elem x, table *t, bool a)
{
   if (a) // true или false
   {
	  for (int i = 0; i < t->n; i++) // В первую таблицу записываем столбец с ценами
		 if (!_mbscmp(x.key, t->cont[i]->key))
		 {
			t->cont[i]->price = x.price;
			return;
		 }
   }
   else
   {
	  int k = t->n, l = 0;
	  while (l + 1 != k)
	  {
		 if (!_mbscmp(t->cont[(l + k) / 2]->key, x.key))
		 {
			t->cont[(l + k) / 2]->price = x.price;
			return;
		 }
		 if (_mbscmp(t->cont[(l + k) / 2]->key, x.key) > 0)
			k = (l + k) / 2;
		 else
			l = (l + k) / 2;
	  }
   }
}

void showtable(table t)
{
	for (int i = 0; i < t.n; i++)
	{
		if (t.cont[i]->price < 0)
			printf_s("%s	%s	%d	Unknown\n", t.cont[i]->key, t.cont[i]->name, t.cont[i]->amount);
		else
			printf_s("%s	%s	%d	%d\n", t.cont[i]->key, t.cont[i]->name, t.cont[i]->amount, t.cont[i]->price);
	}
}