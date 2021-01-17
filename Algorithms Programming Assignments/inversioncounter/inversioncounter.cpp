/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Lukasz Asztemborski
 * Author      : Matthew Vaysfeld
 * Version     : 1.0
 * Date        : October 24, 2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for ( int i = 0; i < length; i++ ) {
        for ( int j = i+1; j < length; j++ ) {
            if ( array[i] > array[j] ) count++;
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    /**for ( int i = 0; i < length; i++ ) {
        cout << array[i] << ", ";
    }
    cout << "\n";
    */
    int *scratch = new int[length];
    long ans = mergesort(array, scratch, 0, length-1);
    /**for ( int i = 0; i < length; i++ ) {
        cout << array[i] << ", ";
    }
    cout <<"\n";
    */
    delete [] scratch;
    return ans;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long returnlong=0;
    if ( low < high ) {
        int mid = low + (high - low) / 2;
        returnlong+=mergesort(array, scratch, low, mid);
        returnlong+=mergesort(array, scratch, mid+1, high);
        int L = low, H = mid + 1;
        for ( int k = low; k <= high; ++k ) {
            if ( L<=mid && (H > high || array[L] <= array[H]) ) {
                scratch[k] = array[L++];
            } else {
                scratch[k] = array[H++];
                returnlong+= mid - L + 1;
            }
        }
        for ( int k = low; k <= high; ++k ) {
            array[k] = scratch[k];
        }
    }
    return returnlong;
}


int main(int argc, char *argv[]) {
    if (argc != 1 && argc != 2) {
        cerr << "Usage: ./inversioncounter [slow]\n";
        return 1;
    }
    else if (argc == 2 && (string)argv[1] != "slow") {
        cerr << "Error: Unrecognized option '" << argv[1] << "'.\n";
        return 1;
    }
    
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    const int len = values.size();
    if (len == 0) {
        cerr << "Error: Sequence of integers not received.\n";
        return 1;
    } else {
        cout << "Number of inversions: ";
        switch(argc){
            case 1:
            cout << count_inversions_fast(&values[0], len);
            break;
            case 2:
            cout << count_inversions_slow(&values[0], len);
            break;
        }
    }
    cout << "\n";
    


    return 0;
}

