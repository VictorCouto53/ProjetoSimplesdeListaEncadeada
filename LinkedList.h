#ifndef __LinkedList_H__
#define __LinkedList_H__

#include <iostream>
#include <string>

using namespace std;

struct Node
{
	string disciplina, isbn, titulo, autor, cidade, editora;
	int edicao, ano;
	bool complementar;
	Node* next;
	Node* previous;
};

Node* CreateNode(string disciplina, string isbn, string titulo, string autor, int edicao, string cidade,
	string editora, int ano, bool complementar, Node* next, Node* previous);

void DestroyNode(Node* node);

struct LinkedList
{
	int count;
	Node* head;
	Node* tail;
};

LinkedList* Create();

void Destroy(LinkedList* list);

void Append(LinkedList* list, string disciplina, string isbn, string titulo, string autor, int edicao, string cidade,
	string editora, int ano, bool complementar);

int Count(LinkedList* list);

bool IsEmpty(const LinkedList* list);

void Clear(LinkedList* list);

#endif