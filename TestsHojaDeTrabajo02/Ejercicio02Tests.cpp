#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_HojaDeTrabajo02/Node.h"
#include "../PAT_HojaDeTrabajo02/Ejercicio02.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace HT02Tests {
	class E02Tests : public TestWithParam<tuple<string, string, string>> {
	protected:
		Ejercicio02* e02;
		string n1;
		string n2;
		string expectedResult;

		void SetUp() override {
			e02 = new Ejercicio02();
			std::tie(n1, n2, expectedResult) = GetParam();
		}

		void TearDown() override {
			delete e02;
			e02 = nullptr;
		}

	public:
		static vector<tuple<string, string, string>> GetParams() {
			vector<tuple<string, string, string>> params;

			std::ifstream paramsFile("e02.csv");
			string line;

			while (std::getline(paramsFile, line)) {
				std::stringstream strStream(line);

				string n1;
				std::getline(strStream, n1, ',');

				string n2;
				std::getline(strStream, n2, ',');

				string e;
				std::getline(strStream, e, ',');

				params.push_back(tuple<string, string, string>(n1, n2, e));
			}

			return params;
		}
	};

	Node<int>* buildList(string& n) {
		Node<int>* head = nullptr;
		Node<int>** it = &head;

		for (int i = n.length() - 1; i >= 0; --i) {
			*it = new Node<int>{ n[i] - '0'};
			it = &((*it)->next);
		}

		return head;
	}

	string buildFromList(Node<int>* head) {
		string r = "";
		r.reserve(100);

		while (head) {
			r += (head->value + '0');
			head = head->next;
		}

		std::reverse(r.begin(), r.end());

		return r;
	}

	TEST_P(E02Tests, E02Sumando) {
		Node<int>* l1 = buildList(n1);
		Node<int>* l2 = buildList(n2);

		Node<int>* head = e02->addTwoNumbers(l1, l2);
		Node<int>* expectedHead = buildList(expectedResult);

		string expectedNumber = buildFromList(expectedHead);
		string actualNumber = buildFromList(head);

		int i = 0;
		while (head && expectedHead) {
			EXPECT_EQ(expectedHead->value, head->value) << "Error en la posicion [" << i << "] de la lista"
				<< ". Se esperaba [" << expectedHead->value << "], pero se encontro [" << head->value
				<< "]\nResultado esperado: [" << expectedNumber << "]\nResultado obtenido: [" << actualNumber << "]";

			++i;
			head = head->next;
			expectedHead = expectedHead->next;
		}
		
		EXPECT_TRUE(head == nullptr && expectedHead == nullptr) << "La cantidad de nodos no es la esperada."
			<< "]\nResultado esperado: [" << expectedNumber << "]\nResultado obtenido: [" << actualNumber << "]";
	}

	INSTANTIATE_TEST_CASE_P(E02Sumando, E02Tests, ValuesIn(E02Tests::GetParams()));
}