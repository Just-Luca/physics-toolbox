/*

Esercizio: write a program to calculate the arithmetic mean of a series of numbers entered from the keyboard. Entering a specific value equal to "0" indicates the end of data input

*/

#include <iostream>

#define N_ENTRIES 10

double Mean (float array[], int N) {

    double sum = 0.;

    for (int i = 0; i < N; i++) {
        sum += array[i];
    }

    return sum/N;
}

double Variance (float array[], int N) {

    double sum  = 0.;
    double sum2 = 0.;
    for (int i = 0; i < N; i++) {
        sum += array[i];
        sum2 += array[i]*array[i];
    }

    double mean = sum/N;
    double var   = sum2/N - mean * mean;

    var *= N/(N-1);
    return var;
}

int main() {

    float numbers[N_ENTRIES];
    float num;

    std::cout << "Insert " << N_ENTRIES << " random numbers:" << std::endl;
        
    for (int i = 0; i < N_ENTRIES; i++) {

        std::cout << "Number " << i+1 << " = ";
        std::cin >> num;
        numbers[i] = num;
    }

    double mean    = Mean (numbers, N_ENTRIES);
    double variance = Variance (numbers, N_ENTRIES);

    std::cout << "\nMean is: "<< mean << std::endl;
    std::cout << "(un-biased) variance is: " << variance << std::endl;

    return 0;
}
