#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>
#include "eratosthenes.h"

using namespace std;

Eratosthenes::Eratosthenes(bool output) : output(output) {}

// Calculate primes using seive of Eratosthenes
string* Eratosthenes::calculatePrimes(unsigned int m) {
	if(output){
		// Printing prime indexes
		for(unsigned int i = 0; i < m; ++i)	{
			if(i%10 == 0 && i != 0)	{
				cout << i/10;
			} else {
				cout << " ";
			}
		}
		cout << endl;
		for(unsigned int i = 0; i < m; ++i)	{
			cout << i%10;
		}
		cout << endl;
	}

	// Initialization of data structure
	string* prime_numbers = new string(m, 'P');

	// 0 and 1 is not prime numbers
	prime_numbers->replace(0, 1, "C");
	prime_numbers->replace(1, 1, "C");

	// Sieve of Eratosthenes
	for(unsigned int i = 0; i < m; ++i){
		if(prime_numbers->at(i) == 'P'){
			sieveMultiplesOfPrime(i, prime_numbers);
			if(output) cout << *prime_numbers << endl;
		}
	}

	return prime_numbers;
}

// Given prime number. mark every multiple as none prime
void Eratosthenes::sieveMultiplesOfPrime(unsigned int prime, string* prime_numbers) {
	for(unsigned int i = 2; i*prime < prime_numbers->size(); ++i){
		prime_numbers->replace(i*prime, 1, "C");
	}	
}

void Eratosthenes::printPrimes(string* prime_numbers) {
	string::iterator it = prime_numbers->begin();
	for (unsigned int i = 0; it != prime_numbers->end(); ++it, ++i) {
		if (*it == 'P') {
			cout << i << endl;
		}
	}
}

void Eratosthenes::printLargestPrime(string* prime_numbers) {
	string::iterator it = prime_numbers->begin();
	int largest = 0;
	for (unsigned int i = 0; it != prime_numbers->end(); ++it, ++i) {
		if (*it == 'P') {
			largest = i;
		}
	}
	cout << largest << endl;
}

int main() {
	Eratosthenes er(false);
	cout << "200 first primes" << endl;
	Eratosthenes::printPrimes(er.calculatePrimes(1224));
	cout << "Largest prime less than 100 000" << endl;
	Eratosthenes::printLargestPrime(er.calculatePrimes(100000));
}
