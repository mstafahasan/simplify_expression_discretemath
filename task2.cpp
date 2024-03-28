// READ BEFORE RUN 
/*note here we implement this program which allow user to passed  an expressions  
ORIGINAL:(A & C ) | ( ( ~(A & B) | ~C ) & ( (A & B) & C))
and the simplified is: A & C 
so if you want to run the the program to check functioality copy this inputs and paste this in terminal 
NOTE: it was more easier  for me  to implement it using builtin original and simplified expressions 
but thats more logical to implement it with that way */
// team 22 
//discrete project 
// TASK:2

#include <iostream>

using namespace std;

bool EvaluateExpression(const string& expression, bool A, bool B, bool C) {
    char operators[100];
    bool operands[100];
    int topOp = -1;
    int topOperand = -1;

    for (char token : expression) {
        if (token == 'A' || token == 'B' || token == 'C') {
            operands[++topOperand] = (token == 'A' && A) || (token == 'B' && B) || (token == 'C' && C);
        } else if (token == '&' || token == '|') {
            while (topOp != -1 && operators[topOp] != '(' && operators[topOp] != '~') {
                char op = operators[topOp--];

                bool operand1 = operands[topOperand--];
                bool operand2 = operands[topOperand--];

                if (op == '&') {
                    operands[++topOperand] = operand1 && operand2;
                } else if (op == '|') {
                    operands[++topOperand] = operand1 || operand2;
                }
            }
            operators[++topOp] = token;
        } else if (token == '~') {
            operators[++topOp] = token;
        } else if (token == '(') {
            operators[++topOp] = token;
        } else if (token == ')') {
            while (topOp != -1 && operators[topOp] != '(') {
                char op = operators[topOp--];

                if (op == '~') {
                    bool operand1 = operands[topOperand--];
                    operands[++topOperand] = !operand1;
                } else {
                    bool operand1 = operands[topOperand--];
                    bool operand2 = operands[topOperand--];

                    if (op == '&') {
                        operands[++topOperand] = operand1 && operand2;
                    } else if (op == '|') {
                        operands[++topOperand] = operand1 || operand2;
                    }
                }
            }
            --topOp; // Remove the '('
        }
    }

    while (topOp != -1) {
        char op = operators[topOp--];

        if (op == '~') {
            bool operand1 = operands[topOperand--];
            operands[++topOperand] = !operand1;
        } else {
            bool operand1 = operands[topOperand--];
            bool operand2 = operands[topOperand--];

            if (op == '&') {
                operands[++topOperand] = operand1 && operand2;
            } else if (op == '|') {
                operands[++topOperand] = operand1 || operand2;
            }
        }
    }

    return operands[topOperand];
}

void generateTruthTableAndCheckEquivalence(const string& original_expr, const string& simplified_expr) {
    cout << "Truth Table:\n";
    cout << "A | B | C | Original Expression | Simplified Expression\n";
    cout << "-----------------------------------------------------\n";

    bool equivalent = true;

    for (int i = 0; i < 8; ++i) {
        bool A = i & 0b100;
        bool B = i & 0b010;
        bool C = i & 0b001;

        bool originalResult = EvaluateExpression(original_expr, A, B, C);
        bool simplifiedResult = EvaluateExpression(simplified_expr, A, B, C);

        cout << A << " | " << B << " | " << C << " | " << originalResult << "                   | " << simplifiedResult << endl;

        if (originalResult != simplifiedResult) {
            equivalent = false;
        }
    }

    if (equivalent) {
        cout << "\nThe original expression is equivalent to the simplified expression.\n";
    } else {
        cout << "\nThe original expression is not equivalent to the simplified expression.\n";
    }
}

void findSatisfiableInputs(const string& expression) {
    cout << "\nSatisfiable Inputs for Expression:\n";

    for (int i = 0; i < 8; ++i) {
        bool A = i & 0b100;
        bool B = i & 0b010;
        bool C = i & 0b001;

        bool result = EvaluateExpression(expression, A, B, C);

        if (result) {
            cout << "A=" << A << ", B=" << B << ", C=" << C << " satisfies the expression.\n";
            return;
        }
    }
}

int main() {
    string original_expr, simplified_expr;
    cout <<"       << YOUR EXPRESSIONS SHOULD BE LESS THAN 100 CHARACKER                  >>      "<<endl ;
    cout <<"       <<NOTE: if you want to not before any input make input between bracket >>"<<endl;
    cout <<"       <<    if you want to calculate A&~B&~c enter it like that A&(~B)&C     >>"<<endl;
    cout << "Enter the original logical expression: ";
    string input;
    getline(cin, input);
    original_expr = input;

    cout << "Enter the simplified logical expression: ";
    getline(cin, input);
    simplified_expr = input;

    generateTruthTableAndCheckEquivalence(original_expr, simplified_expr);

    findSatisfiableInputs(original_expr);
    findSatisfiableInputs(simplified_expr);

    return 0;
}