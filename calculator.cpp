#include <iostream>
#include <limits>

using namespace std;

int main() {
    double n1, n2;
    char operation;

    // Getting first and second number as input from user
    cout << "Hello! Welcome to Basic a Calculator!" << endl;
    cout << "Enter first number: ";
    cin >> n1;

    cout << "Enter second number: ";
    cin >> n2;

    // Display the available operations that is addition , substraction , multiplication and division
    cout << "Choose an operation (+, -, *, /): ";
    cin >> operation;

    // Perform the selected operation using switch statement
    switch (operation) {
        //Addition operation
        case '+':
            cout << "Result: " << n1 + n2 << endl;
            break;

        //Substraction operation
        case '-':
            cout << "Result: " << n1 - n2 << endl;
            break;

        // Multiplication operation
        case '*':
            cout << "Result: " << n1 * n2 << endl;
            break;

        //Division operation
        case '/':
            // Check for division by zero if n2==0 error is displayed
            if (n2 == 0) {
                cout << "Error: Division by zero is not allowed!" << endl;
            } else {
                cout << "Result: " << n1 / n2 << endl;
            }
            break;

        //Default operation if entered operation by user is invalid
        default:
            cout << "Error: Invalid operation!" << endl;
            break;
    }

    return 0;
}