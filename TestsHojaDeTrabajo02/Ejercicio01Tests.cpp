#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_HojaDeTrabajo02/Node.h"
#include "../PAT_HojaDeTrabajo02/Ejercicio01.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace HT02Tests {
	class E01Tests : public TestWithParam<tuple<string, int, string>> {
	protected:
		Ejercicio01* e01;
		string list;
		int k;
		string rotatedList;

		void SetUp() override {
			e01 = new Ejercicio01();
			std::tie(list, k, rotatedList) = GetParam();
		}

		void TearDown() override{
			delete e01;
			e01 = nullptr;
		}

	public:

		static vector<tuple<string, int, string>> GetParams() {
			vector<tuple<string, int, string>> params;

			std::ifstream paramsFile("e01lists.csv");
			string line;

			while (std::getline(paramsFile, line)) {
				std::stringstream strStream(line);

				string p;
				std::getline(strStream, p, ',');

				string s;
				std::getline(strStream, s, ',');
				int k = std::stoi(s);

				string e;
				std::getline(strStream, e, ',');

				params.push_back(tuple<string, int, string>(p, k, e));
			}

			return params;
		}
	};

	Node<char>* buildList(string& list) {
		Node<char>* head = nullptr;
		Node<char>** it = &head;

		for (char c : list) {
			*it = new Node<char>{ c };
			it = &((*it)->next);
		}

		return head;
	}

	string buildFromList(Node<char>* head) {
		string r = "";
		r.reserve(500);

		while (head) {
			r += head->value;
			head = head->next;
		}

		return r;
	}

	TEST_P(E01Tests, E01RotacionDeLista) {
		Node<char>* head = buildList(list);
		Node<char>* expectedHead = buildList(rotatedList);

		head = e01->rotateRight(head, k);

		string actual = buildFromList(head);
		string expected = buildFromList(expectedHead);

		int i = 0;
		while (head && expectedHead) {
			EXPECT_EQ(expectedHead->value, head->value) << "Error en la posicion [" << i << "] de la lista"
				<< ". Se esperaba [" << expectedHead->value << "], pero se encontro [" << head->value
				<< "]\nLista esperada: [" << expected << "]\nLista obtenida: [" << actual << "]";
			
			++i;
			head = head->next;
			expectedHead = expectedHead->next;
		}

		EXPECT_TRUE(head == nullptr && expectedHead == nullptr) << "La cantidad de nodos no es la esperada." 
			<< "\nLista esperada: [" << expected << "]\nLista obtenida: [" << actual << "]";
	}

	INSTANTIATE_TEST_CASE_P(E01RotacionDeLista, E01Tests, ValuesIn(E01Tests::GetParams()));
}