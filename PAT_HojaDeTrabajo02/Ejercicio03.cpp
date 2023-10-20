#include "Ejercicio03.h"
#include <stack>

using std::stack;
using std::isdigit;

int Ejercicio03::calculate(string s)
{
    stack<int> stack;
    int currentNumber = 0;
    char sign = '+';

    for(int i = 0; i < s.size(); ++i) {
        if(isdigit(s[i])) {
            currentNumber = 10 * currentNumber + (s[i] - '0');
        }
        if(!isdigit(s[i]) && s[i] != ' ' || i == s.size() - 1) {
            if(sign == '+') {
                stack.push(currentNumber);
            }
            else if(sign == '-') {
                stack.push(-currentNumber);
            }
            else {
                int num;
                if(sign == '*') {
                    num = stack.top() * currentNumber;
                }
                else {
                    num = stack.top() / currentNumber;
                }
                stack.pop();
                stack.push(num);
            }
            sign = s[i];
            currentNumber = 0; 
        }
        
    }

    int result = 0;
    while(!stack.empty()) {
        result += stack.top();
        stack.pop();
    }

    return result;
}
