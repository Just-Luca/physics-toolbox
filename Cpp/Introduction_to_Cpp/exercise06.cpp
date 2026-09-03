/*

Esercizio: write a function which computes the factorial of a non negative integer recursively

*/

#include <iostream>

int fact_rec (int n) {

    if (n == 0) return 1;
    return (n * fact_rec(n-1));
}

int main() {

    int num;

    std::cout << "Insert an integer: ";
    std::cin >> num;

    std::cout << "Inserted number is: " << num << std::endl;

    // Factorial is not defined for negative numbers
    if (num < 0) {

        std::cout << "Negative number" << std::endl;
        return -1;
    }

    std::cout << "IFactorial of inserted value is: " << fact_rec(num) << std::endl;

    return 0;
}
