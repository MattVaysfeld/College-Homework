/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Lukas Asztemborski
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : December 4, 2020
 * Description : Find all shortest paths using Floyd's Algorithm
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <limits.h>
#include <sstream>
#include <stack>
#include <iomanip>
#include <string>
#include <assert.h>

using namespace std;

const long INF = numeric_limits<long>::max();
int num_vertices;

int len(const long &t){
    long s = t;
    int ans = 1;
    while ( s>9 ){
        s = s/10;
        ans++;
    }
    return ans;
}


long ** initialize_matrix(int N, const bool flag = true) {
    long ** matrix = new long*[N];
    for (int i =0 ; i < N; i++) {
        matrix[i] = new long[N];
        for (int j = 0; j < N; j++) {
            if (j==i && flag) matrix[i][j] = 0;
            else matrix[i][j] = INF;
        }
    }
    return matrix;
}


void delete_matrix(long ** &matrix, int N) {
    for (int i = 0 ; i < N; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
}


void display_table(long ** const matrix, const string & label, const bool use_letters = false) {
    cout << label << endl;
    long max_val =0;
    for ( int i= 0; i < num_vertices; i++){
        for (int j= 0; j < num_vertices; j++){
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val){
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) :
            len(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j= 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for ( int i = 0; i < num_vertices; i++){
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if(matrix[i][j] == INF) {
                cout << "-";
            } else if(use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}


void generate_string(string * str, long ** &intermediates, int end, int start) {
    const string arrow = " -> ";
    stack< pair<int, int> > s;
    pair<int, int> curr;
    s.push( make_pair(start, end) );
    while (!s.empty()) {
        curr = s.top();
        s.pop();

        if (intermediates[curr.first][curr.second]!=INF) {
            s.push( make_pair(intermediates[curr.first][curr.second],curr.second) );
            s.push( make_pair(curr.first, intermediates[curr.first][curr.second]) );
        } else {
            str->append(arrow);
            str->push_back((char)(curr.second + 'A'));
        }
    }
}


void floyds(long ** &matrix, long ** &intermediates, const int & N = num_vertices) {
    for ( int rowcol = 0; rowcol < N; rowcol++ ) {
        for ( int y = 0; y < N; y++ ) {
            for ( int x = 0; x < N; x++ ) {
                if (matrix[y][x] - matrix[y][rowcol] > matrix[rowcol][x] ) {
                    matrix[y][x] = matrix[y][rowcol] + matrix[rowcol][x];
                    intermediates[y][x] = rowcol;
                }
            }
        }
    }
    display_table(matrix, "Path lengths:");
    display_table(intermediates,"Intermediate vertices:", 1);
    vector<vector<string> > sol;
    vector<string> x(N, "");
    sol.resize(N, x);
    const string temp = " -> ";
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            sol[i][j] = (char)('A' + i);
            if (i==j) continue;
            else if (intermediates[i][j]==INF) {
                sol[i][j] += temp;
                sol[i][j] += (char)('A' + j);
            }
            else {
                generate_string(&sol[i][j], intermediates, j, i);
            }
        }
    }
    for ( int i = 0; i < num_vertices; i++ ) {
        for ( int j = 0; j < num_vertices; j++ ) {
            if (matrix[i][j]==INF) {
                cout << (char)('A' + i) << temp << (char)('A' + j) << ", distance: infinity, path: none\n";
            }
            else cout << (char)('A' + i) << temp << (char)('A' + j) << ", distance: " << matrix[i][j] << ", path: " << sol[i][j] << "\n";
        }
    }
}


int main(int argc, const char * argv[]){
    if (argc!=2) {
        cerr << "Usage: ./shortestpaths <filename>\n";
        return 1;
    }
    string line, filename = argv[1];
    istringstream iss;
    long ** matrix;
    ifstream myfile(filename);
    if (!myfile) {
        cerr << "Error: Cannot open file '" << filename << "'.\n";
        return 1;
    }
    myfile.exceptions(ifstream::badbit);
    try {
        unsigned int linecount = 0;

        while (getline(myfile, line)) {
            linecount++;
            if ( linecount == 1 ) {
                iss.str(line);
                if(!(iss >> num_vertices) || num_vertices > 26 || num_vertices < 1){
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1.\n";
                    return 1;
                }
                iss.clear();
                matrix = initialize_matrix(num_vertices);
            }
            else {
                const int len = line.length();
                long parsed;
                if (len < 5) {
                    cerr << "Error: Invalid edge data '" << line << "' on line " << linecount << ".\n";
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }
                if (line[0] >= ('A' + num_vertices) || line[0] < 'A' || line[1]!=' ') {
                    if (line[1]!=' ') {
                        int i = 0;
                        while(i < len && line[i]!=' ') {
                            i++;
                        }
                        cerr << "Error: Starting vertex '" << line.substr(0,i) << "' on line " << linecount << " is not among valid values A-" << (char)('A' + (num_vertices-1)) << ".\n";
                        delete_matrix(matrix, num_vertices);
                        return 1;
                    }
                    cerr << "Error: Starting vertex '" << line[0] << "' on line " << linecount << " is not among valid values A-" << (char)('A' + (num_vertices-1)) << ".\n";
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }
                if (line[2] >= ('A' + num_vertices) || line[2] < 'A' || line[3]!=' ') {
                    if (line[3]!=' ') {
                        int i = 2;
                        while( i < len && line[i]!=' ') {
                            i++;
                        }
                        cerr << "Error: Ending vertex '" << line.substr(2,i-2) << "' on line " << linecount << " is not among valid values A-" << (char)('A' + (num_vertices-1)) << ".\n";
                        delete_matrix(matrix, num_vertices);
                        return 1;
                    }
                    cerr << "Error: Ending vertex '" << line[2] << "' on line " << linecount << " is not among valid values A-" << (char)('A' + (num_vertices-1)) << ".\n";
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }
                iss.str(&line[4]);
                if (!(iss >> parsed) || parsed < 1) {
                    cerr << "Error: Invalid edge weight '" << &line[4] << "' on line " << linecount << ".\n";
                    delete_matrix(matrix, num_vertices);
                    return 1;
                }
                iss.clear();
                matrix[(line[0]-'A')][(line[2]-'A')] = parsed;
            }

        }
        myfile.close();
    }
    catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return 1;
    }


    display_table(matrix, "Distance matrix:");

    long ** intermediates = initialize_matrix(num_vertices, false);
    floyds(matrix, intermediates, num_vertices);

    delete_matrix(intermediates, num_vertices);
    delete_matrix(matrix, num_vertices);

    return 0;
}
