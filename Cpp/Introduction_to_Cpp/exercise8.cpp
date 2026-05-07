/*

Exercise: write a program that assigns the value of one variable to another using a pointer. Also print to the terminal the values and memory addresses of each variable before and after the assignment.

*/

#include <iostream>

int main() {
    
    int balance;      // Dichiara un int
    int value;        // Dichiara altro int
    int* balance_ptr; // Dichiara un puntatore ad un int

    balance = 3200;         // Assegna un valore a balance
    balance_ptr = &balance; // Assegna come valore a balance_ptr l'indirizzo della variabile balance
    value = *balance_ptr;   // Assegna il valore del puntatore balance_ptr alla variabile value

    std::cout << "balance is: " << balance << '\n';
    std::cout << "balance_ptr is: " << balance_ptr << '\n';
    std::cout << "value is: " << value << '\n';

    return 0;
}
