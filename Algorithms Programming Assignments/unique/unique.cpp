/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Matthew Vaysfeld
 * Date        : September 21, 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	int length = s.length();
	for (int i=0; i < length ; i++){
		if(! islower(s[i])){
			return false;
		}
	}
	return true;

}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	int length = s.length();
	unsigned int vector = 0;
	unsigned int setter;
	for (int i=0; i < length; i++){
		setter = 1 << (s[i] - s[0]);
		if ((vector & setter) != 0){
			return false;
		}
		vector = vector | setter;
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.


	//Case 1: No input arguments


	//Case2: many input arguments
	if (argc != 2){
		cerr << "Usage: ./unique <string>" << endl;
		return 1;
	}
	string s = argv[1];

	if(is_all_lowercase(s) == false){
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	else if(all_unique_letters(s) == true){
		cout<< "All letters are unique." << endl;
		return 0;
	}
	else{
		cout<< "Duplicate letters found." << endl;
		return 0;
	}
}
