/*******************************************************************************
 * Name    : student.cpp
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : September 14, 2020
 * Description : Sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
	const int max_prime_width = num_digits(max_prime_),
			primes_per_row = 80 / (max_prime_width + 1);
	if (num_primes_ < primes_per_row){
		for (int i=0; i<=limit_; i++){
				if (i == max_prime_){
					cout << i;
				}
				else if(is_prime_[i] == true){
					cout << i << " ";
				}
			}
	}
	else{
		int count = 0;
		for (int i=0; i<=limit_; i++){
			if(i == max_prime_){
			cout << setw(max_prime_width) << i;
			}
			else if (is_prime_[i] == true){
				if (count == primes_per_row) {
				      cout << endl;
				      count=0;
				    }
				if (count == primes_per_row - 1) {
				    cout << setw(max_prime_width) << i;
				   } else {
				    cout << setw(max_prime_width) << i << " ";
				   }
				count++;
			}

		}

	}


}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
	int num_primes_ = 0;
	for (int i=2; i<=limit_; i++){
		if (is_prime_[i] == true){
			num_primes_++;
		}
	}
	return num_primes_;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
	for(int i=2; i<=limit_; i++){
	    	is_prime_[i] = true;
	}
	//Sieve Algorithm
	for(int i=2; i <= sqrt(limit_); ++i){
		if(is_prime_[i] == true){
			for(int j=i*i; j<= limit_; j = j + i){
				is_prime_[j] = false;
			}
		}
	}

	num_primes_ = count_num_primes();

	bool *end = &is_prime_[limit_];
	int max = limit_;
	while(*end != true){
		end--;
		max--;
	}
	max_prime_= max;




}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	int digits = 0;
	while (num != 0){
		num = num / 10;
		digits++;
	}
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve const primes(limit);
        cout << endl;
        cout << "Number of primes found: " << primes.num_primes() << endl;
        cout << "Primes up to " << limit << ":" << endl;
        primes.display_primes();
        return 0;
}



