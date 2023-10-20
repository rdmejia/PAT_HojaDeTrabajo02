#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "../PAT_HojaDeTrabajo02/Ejercicio04.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;
using ::std::unordered_map;

namespace HT02Tests {

	static const char VOID_FUNC = 'V';
	static const char INT_FUNC = 'F';

	struct QueueOperation {
		string funcName;
		int param;
		int expected;
		char type; // V: void, F: function with return value
	};

	int pushFront(FrontMiddleBackQueue* queue, int value) {
		queue->pushFront(value);
		return -1;
	}

	int pushMiddle(FrontMiddleBackQueue* queue, int value) {
		queue->pushMiddle(value);
		return -1;
	}

	int pushBack(FrontMiddleBackQueue* queue, int value) {
		queue->pushBack(value);
		return -1;
	}

	int popFront(FrontMiddleBackQueue* queue, int value) {
		return queue->popFront();
	}

	int popMiddle(FrontMiddleBackQueue* queue, int value) {
		return queue->popMiddle();
	}

	int popBack(FrontMiddleBackQueue* queue, int value) {
		return queue->popBack();
	}

	static const unordered_map<string, int (*)(FrontMiddleBackQueue*, int)> queueOps = {
		{"pushFront", pushFront},
		{"pushMiddle", pushMiddle},
		{"pushBack", pushBack},
		{"popFront", popFront},
		{"popMiddle", popMiddle},
		{"popBack", popBack}
	};

	class E04Tests : public TestWithParam<vector<QueueOperation*>*> {
	protected:
		FrontMiddleBackQueue* queue;
		vector<QueueOperation*>* operations;

		void SetUp() override {
			queue = new FrontMiddleBackQueue();
			operations = GetParam();
		}

		void TearDown() override {
			delete queue;
			queue = nullptr;
		}

	public:
		static vector<vector<QueueOperation*>*> GetParams() {
			vector<vector<QueueOperation*>*> params;
			std::ifstream paramsFile("e04.csv");
			string line;

			vector<QueueOperation*>* ops = new vector<QueueOperation*>();

			while (std::getline(paramsFile, line)) {
				if (line.length() == 0) {
					params.push_back(ops);
					ops = new vector<QueueOperation*>();
					continue;
				}

				std::stringstream strStream(line);

				string op;
				std::getline(strStream, op, ',');

				string ps;
				std::getline(strStream, ps, ',');
				int p = (ps.length() != 0 ? std::stoi(ps) : -2);

				string rs;
				std::getline(strStream, rs, ',');
				int r = (rs.length() != 0 ? std::stoi(rs) : -2);

				char type;

				if (op == "popFront" || op == "popMiddle" || op == "popBack") 
					type = INT_FUNC;
				else 
					type = VOID_FUNC;

				ops->push_back(new QueueOperation{op, p, r, type});
			}

			return params;
		}
	};

	TEST_P(E04Tests, E04HandlingQueue) {
		int i = 0;
		for (QueueOperation* op : *operations) {
			int r = queueOps.at(op->funcName)(queue, op->param);

			if (op->type == INT_FUNC) {
				EXPECT_EQ(r, op->expected) << "Error al llamar la instruccion [" << i <<"] -> " << op->funcName << "(" << op->param 
					<< ").\nSe esperaba [" << op->expected << "], pero se encontro [" << r << "]";
			}

			++i;
		}
	}

	INSTANTIATE_TEST_CASE_P(E04Queue, E04Tests, ::testing::ValuesIn(E04Tests::GetParams()));
	
}