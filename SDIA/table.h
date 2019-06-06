#pragma once

#include <algorithm>
#include <cstdlib>
#include <string.h>
#include <mbstring.h>
#include <locale.h>
#include <stdio.h>
#include <stack>
#include <windows.h>
#include <stdlib.h>

using namespace std;

const int Nmax = 20; // Максимальное число элементов в таблице
const int Keymax = 9; // Максимальное число элементов в ключе
const int Namemax = 21; // Максимальное число элементов в названии товара

enum Commands1 { CMD_QUICK_SORT = 1, CMD_TREE_SORT };
enum Commands2 { CMD_STANDART_SEARCH = 1, CMD_BINARY_SEARCH };

struct elem // Объявление содержимого таблицы 
{
	UCHAR key[Keymax];
	char name[Namemax];
	int amount;
	int price;
};

struct tree // Объявление дерева (для сортировки при помощи дерева)
{
	elem el;
	tree *left, *right;
	tree(elem _el, tree *_left = NULL, tree *_right = NULL) :
		el(_el), left(_left), right(_right) {}
};

struct table // Объявление таблицы
{
	elem *cont[Nmax];
	int n = 0;
};

int compare(const void *a, const void *b);
void buildptable(table *t); // Создаём таблицу 2 (с ценами)
void buildtable(table *t); // Создаём таблицу 1 (основную)
void add(table *t, elem *e); // Запись элемента в таблицу 1
void padd(table *t, elem *e); // Запись элемента в таблицу 2
void buildtree(tree **t, table p); // Создаём дерево
void treeadd(tree **t, elem x); // Добавить элемент в дерево
void treesort(table *t, tree *tree); // Сортировка при помощи дерева
void finaltable(table *t, table pt, bool a); // Построение финальной версии таблицы
void combine(elem x, table *t, bool a);	// Запись в первую таблицу столбца с ценами (цены из втрой таблицы 2 будем сравнивать по ключу)
void showtable(table t); // Показ содержимого таблицы
#pragma once