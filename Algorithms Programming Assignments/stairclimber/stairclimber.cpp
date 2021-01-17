/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Matthew Vaysfeld
 * Date        : September 29, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;
	vector<vector<int>> result;
	if (num_stairs <= 0){
		vector<int> temp;
		vector<vector<int>> empty;
		empty.insert(empty.end(), temp);
		return empty;
	}
	for(int i=1; i<4; i++){
		if (num_stairs >= i){
			result = get_ways(num_stairs - i);
			for (long unsigned int j = 0; j < result.size(); j++){
				result[j].insert(result[j].begin(), i);

			}
				ways.insert(ways.end(),result.begin(),result.end());
				//https://stackoverflow.com/questions/313432/c-extend-a-vector-with-another-vector
			}

		}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int width = 0;
	int size = ways.size();
	while (size != 0){
			size = size / 10;
			width++;
		}
	for (long unsigned int i=0; i < ways.size(); ++i){
			cout << setw(width) << i+1 << ". [";
			for (long unsigned int j= 0; j < ways[i].size(); ++j){
				cout << ways[i][j];
				if (j != ways[i].size()-1){
					cout << ", ";
				}
			}
			cout << "]" << endl;
		}
}

int main(int argc, char * const argv[]) {
	if (argc != 2){
			cerr << "Usage: ./stairclimber <number of stairs>" << endl;
			return 1;
		}
	int num_stairs;
	istringstream iss;

	iss.str(argv[1]);



	if( !(iss>> num_stairs) ){
					cerr << "Error: Number of stairs must be a positive integer." << endl;
					return 1;
	}
	if(num_stairs < 1){
			cerr << "Error: Number of stairs must be a positive integer." << endl;
			return 1;
		}
	vector<vector<int>> ways= get_ways(num_stairs);
	if(num_stairs == 1){
		cout << ways.size() << " way to climb " << num_stairs << " stair." << endl;
	}
	else{cout << ways.size() << " ways to climb " << num_stairs << " stairs." << endl;}
	display_ways(ways);
	return 0;

}
