#pragma once

#include <cstdlib>
#include <string.h>
#include <mbstring.h>
#include <locale.h>
#include <stdio.h>
#include <stack>
#include <windows.h>

using namespace std;

const int Nmax = 10;

enum Commands1 { CMD_QUICK_SORT = 1, CMD_TREE_SORT };
enum Commands2 { CMD_STANDART_SEARCH = 1, CMD_BINARY_SEARCH };

struct elem
{
	UCHAR key[9];
	char name[21];
	int amount;
	int price;
};

struct tree
{
	elem el;
	tree *left, *right;
	tree(elem _el, tree *_left = NULL, tree *_right = NULL) :
		el(_el), left(_left), right(_right) {}
};

struct table
{
	elem cont[Nmax];
	int n = 0;
};

void search(elem x, table *t, int a);

void finaltable(table *t, table pt, int a);

void buildtree(tree **t, table p);

void treeadd(tree **t, elem x);

void buildtable(table *t);

void buildptable(table *t);

void add(table *t, elem e);

void addp(table *pt, elem e);

void quicksort(table *t, int m, int n);

void treesort(table *t, tree *tree);

void showtable(table t);