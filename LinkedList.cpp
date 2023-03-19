#include "LinkedList.h"
#include <string>

using namespace std;

Node* CreateNode(string disciplina, string isbn, string titulo, string autor, int edicao, string cidade,
	string editora, int ano, bool complementar, Node* next, Node* previous) {
	Node* node = new Node();

	node->disciplina = disciplina;
	node->isbn = isbn;
	node->titulo = titulo;
	node->autor = autor;
	node->edicao = edicao;
	node->cidade = cidade;
	node->editora = editora;
	node->ano = ano;
	node->complementar = complementar;

	node->next = next;
	node->previous = previous;
	return node;
}

void DestroyNode(Node* node) {
	delete node;
	node = nullptr;
}

LinkedList* Create() {
	LinkedList* list = new LinkedList();
	list->count = 0;
	list->head = nullptr;
	list->tail = nullptr;
	return list;
}

void Destroy(LinkedList* list) {
	Clear(list);
	delete list;
	list = nullptr;
}

void Append(LinkedList* list, string disciplina, string isbn, string titulo, string autor, int edicao, string cidade,
	string editora, int ano, bool complementar) {
	Node* node = CreateNode(disciplina, isbn, titulo, autor, edicao, editora,
		cidade, ano, complementar,  nullptr, list->tail);

	if (list->count == 0) {
		list->head = node;
	}
	else
		list->tail->next = node;
	list->tail = node;
	list->count++;
}

int Count(LinkedList* list) {
	return list->count;
}

bool IsEmpty(const LinkedList* list) {
	return list->count == 0;
}

void Clear(LinkedList* list) {
	Node* temp = list->head;

	Node* next = nullptr;

	while (temp != nullptr) {
		next = temp->next;
		delete temp;
		temp = next;
	}
	DestroyNode(temp);
	list->head = list->tail = nullptr;
	list->count = 0;
}