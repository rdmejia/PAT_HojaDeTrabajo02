#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_HojaDeTrabajo02/Ejercicio03.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace HT02Tests {
	
	class E03Tests : public TestWithParam<tuple<string, int>> {
	protected:
		Ejercicio03* e03;
		string s;
		int expectedResult;

		void SetUp() override {
			e03 = new Ejercicio03();
			std::tie(s, expectedResult) = GetParam();
		}

		void TearDown() override {
			delete e03;
			e03 = nullptr;
		}

	public:
		static vector<tuple<string, int>> GetParams() {
			vector<tuple<string, int>> params;

			std::ifstream paramsFile("e03.csv");
			string line;

			while (std::getline(paramsFile, line)) {
				std::stringstream strStream(line);

				string s;
				std::getline(strStream, s, ',');

				string rs;
				std::getline(strStream, rs, ',');
				int er = std::stoi(rs);

				params.push_back(tuple<string, int>(s, er));
			}

			return params;
		}
	};

	TEST_P(E03Tests, E03Calculando) {
		int actualResult = e03->calculate(s);
		EXPECT_EQ(actualResult, expectedResult) << "El resultado obtenido no es el esperado [" << actualResult << "].\n"
			<< " Se esperaba: " << s << " = [" << expectedResult << "]";
	}

	INSTANTIATE_TEST_CASE_P(E03Calculadora, E03Tests, ValuesIn(E03Tests::GetParams()));
}