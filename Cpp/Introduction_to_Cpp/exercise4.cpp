/*

Exercise: write a program that asks the user to enter an integer and determines whether the number is even or odd; use the % operator, implementing two functions that print different messages to the screen in the two cases.

*/

#include <iostream>

#define EXIT 1

// Prototipes declaration
void even (int a);
void odd  (int a);

int main () {

    int i;

    while (true) {

        std::cout << "Write a number: (" << EXIT << " to EXIT): ";
        std::cin >> i;
        if (i == EXIT) break;
        else if (i%2 == 0) even i);
        else odd(i);
    }

    return 0;
}

// Functions definition
void odd (int a) {
    std::cout << "The number is odd.\n";
}

void even (int a) {
    std::cout << "The number is even n";
}
