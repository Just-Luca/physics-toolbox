/*

Exercise: write a function which for computing the factorial of a non negative integer

*/

#include <iostream>

int fact_val (int n) {

    if (n == 0 || n == 1) return 1;

    int factorial = 1;
    for(int i = 1; i <= n; ++i) {
        factorial *= i;
    }

    return factorial;
}

int main() {

    int num;

    std::cout << "Insert an integer: ";
    std::cin >> num;

    std::cout << "Inserted number is:" << num << std::endl;

    // Factorial is not defined for negative numbers
    if (num < 0) {

        std::cout << "Negative number" << std::endl;
        return -1;
    }

    std::cout << "Factorial of inserted value is: "
        << fact_val(num) << std::endl;

    return 0;
}
