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

const int Nmax = 20; // ������������ ����� ��������� � �������
const int Keymax = 9; // ������������ ����� ��������� � �����
const int Namemax = 21; // ������������ ����� ��������� � �������� ������

enum Commands1 { CMD_QUICK_SORT = 1, CMD_TREE_SORT };
enum Commands2 { CMD_STANDART_SEARCH = 1, CMD_BINARY_SEARCH };

struct elem // ���������� ����������� ������� 
{
	UCHAR key[Keymax];
	char name[Namemax];
	int amount;
	int price;
};

struct tree // ���������� ������ (��� ���������� ��� ������ ������)
{
	elem el;
	tree *left, *right;
	tree(elem _el, tree *_left = NULL, tree *_right = NULL) :
		el(_el), left(_left), right(_right) {}
};

struct table // ���������� �������
{
	elem *cont[Nmax];
	int n = 0;
};

int compare(const void *a, const void *b);
void buildptable(table *t); // ������ ������� 2 (� ������)
void buildtable(table *t); // ������ ������� 1 (��������)
void add(table *t, elem *e); // ������ �������� � ������� 1
void padd(table *t, elem *e); // ������ �������� � ������� 2
void buildtree(tree **t, table p); // ������ ������
void treeadd(tree **t, elem x); // �������� ������� � ������
void treesort(table *t, tree *tree); // ���������� ��� ������ ������
void finaltable(table *t, table pt, bool a); // ���������� ��������� ������ �������
void combine(elem x, table *t, bool a);	// ������ � ������ ������� ������� � ������ (���� �� ����� ������� 2 ����� ���������� �� �����)
void showtable(table t); // ����� ����������� �������
#pragma once