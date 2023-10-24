#pragma once

#include <string>

using std::string;

class Ejercicio03
{
public:
	int calculate(string s) {
        std::stack<int> nums;
        std::stack<char> ops;

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];

            if (c == ' ') {
                continue;
            }
            else if (isdigit(c)) {
                int num = 0;
                while (i < s.length() && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                i--;
                if (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
                    int prev_num = nums.top();
                    nums.pop();
                    if (ops.top() == '*') {
                        nums.push(prev_num * num);
                    }
                    else {
                        nums.push(prev_num / num);
                    }
                    ops.pop();
                }
                else {
                    nums.push(num);
                }
            }
            else if (c == '+' || c == '-') {
                while (!ops.empty() && (ops.top() == '+' || ops.top() == '-' || ops.top() == '*' || ops.top() == '/')) {
                    calculateTop(nums, ops);
                }
                ops.push(c);
            }
            else if (c == '*' || c == '/') {
                ops.push(c);
            }
        }

        while (!ops.empty()) {
            calculateTop(nums, ops);
        }

        return nums.top();
    }

private:
    void calculateTop(std::stack<int>& nums, std::stack<char>& ops) {
        int num2 = nums.top();
        nums.pop();
        int num1 = nums.top();
        nums.pop();
        char op = ops.top();
        ops.pop();

        if (op == '+') {
            nums.push(num1 + num2);
        }
        else if (op == '-') {
            nums.push(num1 - num2);
        }
    }
};

