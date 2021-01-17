/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : September 3, 2020
 * Description : Computes the square root of a number using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <sstream>
using namespace std;


double sqrt(double num, double epsilon){
	if (num<0) {
		return numeric_limits<double>::quiet_NaN();
	}
	if (num == 0 || num==1){
		return num;
	}
	double last_guess = num;
	double next_guess = (last_guess + num/last_guess)/2;
	while (! (abs(last_guess - next_guess) <= epsilon)){
		last_guess = next_guess;
		next_guess = (last_guess + num/last_guess)/2;
	}
	return next_guess;
}

int main(int argc, char* const argv[]){
	double num, epsilon;
	istringstream iss;

	if (argc == 3){
		iss.str(argv[1]);

			if( !(iss>> num) ){
				cerr << "Error: Value argument must be a double." << endl;
				return 1;
			}
			iss.clear();
			iss.str(argv[2]);
			if( !(iss>> epsilon) || epsilon <= 0){
					cerr << "Error: Epsilon argument must be a positive double." << endl;
					return 1;
				}

			cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;
			return 0;
	}
	else if(argc == 2){
		iss.str(argv[1]);

					if( !(iss>> num) ){
						cerr << "Error: Value argument must be a double." << endl;
						return 1;
					}
					iss.clear();
					epsilon = 1e-7;

					cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;
					return 0;
	}
	else{
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
	}
}

