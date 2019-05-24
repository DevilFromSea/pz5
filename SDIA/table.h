#pragma once
#include <cstdlib>
#include <string.h>
#include <mbstring.h>
#include <locale.h>
#include <stdio.h>
#include <windows.h>

const int Nmax = 10;

enum Commands { CMD_QUICK_SORT = 1, CMD_TREE_SORT };

struct elem
{
	UCHAR key[9];
	char name[21];
	int amount;
};

struct tree
{
	elem el;
	int index;
	tree *left, *right;
	tree(elem _el, int _index, tree *_left = NULL, tree *_right = NULL) :
		el(_el), index(_index), left(_left), right(_right) {}
};

struct table
{
	elem cont[Nmax];
	int n = 0;
};

void buildtree(tree *t, table p);

void treeadd(tree *t, elem x, int i);

void buildtable(table *t);

void add(table *t, elem e);

void quicksort(table *t, int m, int n);

void treesort(table *t, int m, int n, tree *tree);

void showtable(table t);