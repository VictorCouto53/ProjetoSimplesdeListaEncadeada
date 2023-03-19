#include <iostream>
#include <clocale>
#include <string>
#include "LinkedList.h"
#include <fstream>
#include <sstream>

using namespace std;

void Print(const LinkedList* list) {
	Node* node = list->head;

	while (node != nullptr) {
		cout << node->disciplina << " | " <<
			node->isbn << " | " <<
			node->titulo << " | " <<
			node->autor << " | " <<
			node->edicao << " | " <<
			node->cidade << " | " <<
			node->editora << " | " <<
			node->ano << " | " <<
			node->complementar <<
			'\n';
		node = node->next;
	}
}

void PrintListInfo(const LinkedList* list) {
	if (IsEmpty(list)) {
		cout << "\nLista vazia !\n";
	}
	else {
		cout << "Lista : \n";
		Print(list);
	}
}

void OpenFile(LinkedList* list) {
	int ano, edicao, i = 0;
	int j = 0;
	string vetor_string[10];
	bool complementar;
	
	fstream file;
	file.open("bibliografia.csv");
	string line;

	while (getline(file, line, ';'))
	{
		istringstream templine(line); 
		string data;
		while (getline(templine, data, '\n'))
		{
			if (j >= 9) {
				vetor_string[i] = data;
				i++;
				if (i == 5) {
					edicao = stoi(data);
				}
				if (i == 8) {
					ano = stoi(data);
				}
				if (vetor_string[8] == "N") {
					complementar = false;
				}
				else if (vetor_string[8] == "S") {
					complementar = true;
				}
				if (i == 9) {
					Append(list, vetor_string[0], vetor_string[1], vetor_string[2], vetor_string[3], edicao,
						vetor_string[5], vetor_string[6], ano, complementar);
					i = 0;
				}
			}
			j++;
		}
	}

	file.close();
	cout << "\nArquivo lido !\n";
}

void AnaliseA(const LinkedList* list)
{
	int countBR = 0;
	int countINT = 0;
	int	porcentagemBR = 0;
	int	porcentagemINT = 0;

	Node* node = list->head;

	while (node != nullptr)
	{
		if (node->editora == "São Paulo" || node->editora == "Curitiba" || node->editora == "Rio de Janeiro" || node->editora == "Porto Alegre")
		{
			countBR++;
		}
		node = node->next;
	}
	countINT = list->count - countBR;

	porcentagemBR = (countBR * 100) / list->count;
	porcentagemINT = (countINT * 100) / list->count;

	cout << "\nLivros publicados por editora Brasileira : " << countBR <<
		"\nLivros publicados por editora Internacional : " << countINT <<
		"\nPorcentagem Editoras Brasileiras : " << porcentagemBR << "%" <<
		"\nPorcentagem Editoras Internacionais : " << porcentagemINT << "%\n";
}

void AnaliseB(const LinkedList* list) {
	Node* node = list->head;

	int countE = 0;
	int i = 0;

	while (node != nullptr) {
		if (node->edicao > 1) {
			countE++;
		}
		node = node->next;
	}

	cout << countE << "\n";
	node = list->head;

	int size = list->count - countE;

	int* vetorANO = new int[size];

	while (node != nullptr) {
		if (node->edicao == 1) {
			vetorANO[i] = node->ano;
			i++;
		}
		node = node->next;
	}

	for (int j = 0; j < size; j++) {
		cout << vetorANO[j] << " | ";
	}
	delete[] vetorANO;
}

void AnaliseC(const LinkedList* list)
{  
  Node* node = list->head;

  cout << "\nLivros publicados antes de 2005:\n\n";
  while(node != nullptr)
    {
      if(node->ano <= 2005)
      {
        cout << "\nTítulo: " << node->titulo << "\nAutor(es): " << node->autor << "\nAno: " << node->ano;
      }
      node = node->next;
     }
  cout << "\n";
}

void AnaliseD(const LinkedList* list)
{
  string* ArrayOld = new string[3];
  Node* node = list->head;

  int k = node->ano;
  while(node != nullptr)
    {
      if(node->ano < k)
      {
        ArrayOld[0] = node->titulo;
        ArrayOld[1] = node->autor;
        ArrayOld[2] = to_string(node->ano);
        k = node->ano;
      }
      node = node->next;
    }
  cout << "\nLivro mais antigo: " << "\nTítulo: " << ArrayOld[0] << "\n" << "Autor: " << ArrayOld[1] << "\n" << "Ano: " << ArrayOld[2] << "\n\n";

  delete[] ArrayOld;
}

int main() 
{
	setlocale(LC_CTYPE, "Portuguese");

	LinkedList* list = Create();

	string input;
	int option = 0;

	do {
		cout << "\n *** MENU DE OPÇÕES ***\n"
			<< "[1] Ler Dados.\n"
			<< "[2] Exibir Dados.\n"
			<< "[3] Análise de Dados A.\n"
			<< "[4] Análise de Dados B.\n"
			<< "[5] Análise de Dados C.\n"
			<< "[6] Análise de Dados D.\n"
			<< "[8] Encerrar.\n"
			<< "Escolha uma opção: ";
		cin >> input;

		try {
			option = stoi(input);
		}
		catch (const exception& e) {
			option = -1;
		}

		switch (option) 
    {
		case 1: OpenFile(list); break;
		case 2: PrintListInfo(list); break;
		case 3: AnaliseA(list); break;
		case 4: AnaliseB(list); break;
		case 5: AnaliseC(list); break;
		case 6: AnaliseD(list); break;
		default:
			if (option != 8)
				cout << "\n*** OPÇÃO INVÁLIDA! ***\n";
			break;
		}
	} while (option != 8);

	return 0;
}