/*

Exercise: write a program that assigns the value of one variable to another using a pointer. Also print to the terminal the values and memory addresses of each variable before and after the assignment.

*/

#include <iostream>

int main() {
    
    int balance;      // declare an int
    int value;        // declare another int
    int* balance_ptr; // declare a pointer to an int

    balance = 3200;         // assign a value to balance
    balance_ptr = &balance; // assign the address of the balance variable to balance_ptr
    value = *balance_ptr;   // assign the value of the balance_ptr pointer to the value variable

    std::cout << "balance is: " << balance << '\n';
    std::cout << "balance_ptr is: " << balance_ptr << '\n';
    std::cout << "value is: " << value << '\n';

    return 0;
}
