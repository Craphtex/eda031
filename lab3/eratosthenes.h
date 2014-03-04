#ifndef ERATOSTHENES_H
#define ERATOSTHENES_H

#include <string>

using namespace std;

class Eratosthenes {
public:
	Eratosthenes(bool output);
	string* calculatePrimes(unsigned int m);
	static void printPrimes(string* prime_numbers);
	static void printLargestPrime(string* prime_numbers);
private:
	bool output;
	void sieveMultiplesOfPrime(unsigned int prime, string* prime_numbers);
};

#endif