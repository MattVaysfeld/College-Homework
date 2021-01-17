/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author1  : Lukasz Asztemborski
 * Author2  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : October 5, 2020
 * Description : Water Jug Puzzle
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct State {
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
		a{ _a }, b{ _b }, c{ _c }, directions{ _directions }, parent{ nullptr } { }

	State(int _a, int _b, int _c, string _directions, State *_parent) :
		a{ _a }, b{ _b }, c{ _c }, directions{ _directions }, parent{_parent } { }

	~State();

	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}

};

State::~State() {
	// IDK
}

void get_possibilities(State *&currState, const int caps[], State*** &matrix, queue<State *>& todo) {
	vector<State *> sol;
	int A = currState->a, B = currState->b, C = currState->c;
	ostringstream oss;

	// C -> A
	while (true) {
		if (C == 0) break;
		else if (A == caps[0]) break;
		else {
			if (C + A <= caps[0]) {
				oss << "Pour " << C << " gallon"  << (C > 1 ? "s" : "") << " from C to A. ";
				A += C;
				C = 0;
			}
			else {
				oss << "Pour " << (caps[0] - A) << " gallon" << ((caps[0]-A) > 1 ? "s" : "") <<  " from C to A. ";
				C = C - (caps[0] - A);
				A = caps[0];
			}
			if (!matrix[A][B]) {
				State *temp = new State(A, B, C,  oss.str(), currState);
				matrix[A][B] = temp;
				todo.push(temp);
			}
			oss.str("");
			break;
		}
	}

	A = currState->a, B = currState->b, C = currState->c;
	// B -> A
	while (true) {
		if (B == 0) break;
		else if (A == caps[0]) break;
		else {
			if (B + A <= caps[0]) {
				oss << "Pour " << B << " gallon"  << (B > 1 ? "s" : "") << " from B to A. ";
				A += B;
				B = 0;
			}
			else {
				oss << "Pour " << (caps[0] - A) << " gallon"  << ((caps[0]-A) > 1 ? "s" : "") << " from B to A. ";
				B = B - (caps[0] - A);
				A = caps[0];
			}
			if (!matrix[A][B]) {
				State *temp = new State(A, B, C, oss.str(), currState);
				matrix[A][B] = temp;
				todo.push(temp);
			}
			oss.str("");
			break;
		}
	}

	A = currState->a, B = currState->b, C = currState->c;
	// C -> B
	while (true) {
		if (C == 0) break;
		else if (B == caps[1]) break;
		else {
			if (C + B <= caps[1]) {
				oss << "Pour " << C << " gallon"  << (C > 1 ? "s" : "") << " from C to B. ";
				B += C;
				C = 0;
			}
			else {
				oss << "Pour " << (caps[1] - B) << " gallon"  << ((caps[1]-B) > 1 ? "s" : "") << " from C to B. ";
				C = C - (caps[1] - B);
				B = caps[1];
			}
			if (!matrix[A][B]) {
				State *temp = new State(A, B, C, oss.str(), currState);
				matrix[A][B] = temp;
				todo.push(temp);
			}
			oss.str("");
			break;
		}
	}

	A = currState->a, B = currState->b, C = currState->c;
	// A -> B
	while (true) {
		if (A == 0) break;
		else if (B == caps[1]) break;
		else {
			if (A + B <= caps[1]) {
				oss << "Pour " << A << " gallon"  << (A > 1 ? "s" : "") << " from A to B. ";
				B += A;
				A = 0;
			}
			else {
				oss << "Pour " << (caps[1] - B) << " gallon" << ((caps[1]-B) > 1 ? "s" : "") <<  " from A to B. ";
				A = A - (caps[1] - B);
				B = caps[1];
			}
			if (!matrix[A][B]) {
				State *temp = new State(A, B, C, oss.str(), currState);
				matrix[A][B] = temp;
				todo.push(temp);
			}
			oss.str("");
			break;
		}
	}

	A = currState->a, B = currState->b, C = currState->c;
	// B -> C
	while (true) {
		if (B == 0) break;
		else if (C == caps[2]) break;
		else {
			if (B + C <= caps[2]) {
				oss << "Pour " << B << " gallon"  << (B > 1 ? "s" : "") << " from B to C. ";
				C += B;
				B = 0;
			}
			else {
				oss << "Pour " << (caps[2] - C) << " gallon"  << ((caps[2]-C)>1 ? "s" : "") <<  " from B to C. ";
				B = B - (caps[2] - C);
				C = caps[2];
			}
			if (!matrix[A][B]) {
				State *temp = new State(A, B, C, oss.str(), currState);
				matrix[A][B] = temp;
				todo.push(temp);
			}
			oss.str("");
			break;
		}
	}

	A = currState->a, B = currState->b, C = currState->c;
	// A -> C
	while (true) {
		if (A == 0) break;
		else if (A == caps[2]) break;
		else {
			if (A + C <= caps[2]) {
				oss << "Pour " << A << " gallon" << (A > 1 ? "s" : "") << " from A to C. ";
				C += A;
				A = 0;
			}
			else {
				oss << "Pour " << (caps[2] - C) << " gallon"  << ((caps[2]-C) > 1 ? "s" : "") << " from A to C. ";
				A = A - (caps[2] - C);
				C = caps[2];
			}
			if (!matrix[A][B]) {
				State *temp = new State(A, B, C, oss.str(), currState);
				matrix[A][B] = temp;
				todo.push(temp);
			}
			oss.str("");
			break;
		}
	}

	return;
}


void create_graph(const int inputs[]) {
	//int* myMax = max_element(inputs, inputs+3);
	int caps[3] = { inputs[0], inputs[1], inputs[2] };
	//int Acap = inputs[0], Bcap = inputs[1], Ccap = inputs[2];
	int Aend = inputs[3], Bend = inputs[4];
	State ***matrix = new State**[caps[0] + 1];
	for (int i = 0; i < caps[0] + 1; i++) {
		matrix[i] = new State*[caps[1] + 1];
		//fill(matrix[i], matrix[i] + caps[1], nullptr);
		for(int j = 0; j < caps[1]+1; j++){
			matrix[i][j] = nullptr;
		}
	}

	State *start_state = new State(0, 0, caps[2], "Initial state. ");
	matrix[0][0] = start_state;

	queue<State *> todo;
	todo.push(start_state);

	State *currState = start_state;
	// algorithm
	bool haveto = true;
	if (currState->a == Aend && currState->b == Bend){
		haveto = false;
	}
	while (haveto) {
		get_possibilities(currState, caps, matrix, todo);

		// todelete.push_back(todo.front());
		todo.pop();

		if (todo.empty()) {
			cout << "No solution.\n";
			for ( int i = 0; i<caps[0] +1; ++i){
				for (int k = 0; k < caps[1] + 1; ++k) {
					if(matrix[i][k] != nullptr) delete matrix[i][k];
				}
				delete [] matrix[i];
			}
			delete [] matrix;
			return;
		}
		else currState = todo.front();
		if (currState->a == Aend && currState->b == Bend){
			break;
		}
		//cout << currState->to_string() << endl;
	}
//label:;

	// curr_state will == accept_state here.


	stack<State *> back;
	back.push(currState);
	while (currState->parent != nullptr) {
		back.push(currState->parent);
		currState = currState->parent;
	}

	while (!back.empty()) {
		cout << back.top()->directions << back.top()->to_string() << endl;
		//delete back.top();
		back.pop();
	}

	for (int i = 0; i < caps[0] + 1; ++i) {
		for (int k = 0; k < caps[1] + 1; ++k) {
			if(matrix[i][k] != nullptr) delete matrix[i][k];
		}
		delete[] matrix[i];
	}
	delete[] matrix;

	return;
}



int main(int argc, const char *argv[]) {
	istringstream iss;
	//int capA, capB, capC, goalA, goalB, goalC;
	int inputs[6];

	if (argc != 7) { //not 7 arguments
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>\n";
		return 1;
	}
	int goalsum = 0;
	for (int i = 4; i < 7; i++) {
		iss.str(argv[i]);
		int x;
		iss >> x;
		if(x < 0){
			cerr << "Error: Invalid goal '" << x <<  "' for jug " << (char)('@' + i - 3) << "." << endl;
			return 1;
		}
		iss.clear();
	}
	for (int i = 1; i < 7; i++) {
		iss.str(argv[i]);
		int *temp = &inputs[i - 1];
		if (!(iss >> *temp)) { // if its not an integer

			if (i > 3) { //if its a goal
				printf("Error: Invalid goal '%s' for jug %c.\n", argv[i], (char)('@' + i - 3));
				return 1;
			}
			else { //if its a capacity
				printf("Error: Invalid capacity '%s' for jug %c.\n", argv[i], (char)('@' + i));
				return 1;
			}

		}
		if (i <= 3){
		     if (*temp < 1) {
		        cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char)('@' + i) << ".";
		        return 1;
		       }
		   }
		if (i > 3) { //if its a goal
			if (*temp > inputs[i - 4]) { // Goal is greater than the capacity
				//printf("i:%d,temp:%d,inputs:%d\n",i,*temp,inputs[i-4]);
				cerr << "Error: Goal cannot exceed capacity of jug " << (char)('@' + i - 3) << "." << endl;
				return 1;
			}
			goalsum += *temp;
		}
		iss.clear();
	}

	if (inputs[2] != goalsum) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	create_graph(inputs);

	//delete sol;


	return 0;
}
