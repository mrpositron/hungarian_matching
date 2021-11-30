#include <iostream>
#include <vector>
#include "helper.h"

using namespace std;


int main() {
    vector<vector<float>> mat = {
        {3, 7, 5, 11},
        {5, 4, 6, 3},
        {6, 10, 1, 1},
    };

    // --------------------------------------------------
    // 1. Lets find the minimal cost
    // --------------------------------------------------
    vector <int> min_indexes;
    int min_cost = solve(mat, min_indexes, 0);
    cout << "Minimal cost: " << min_cost << endl;
    // print min_indexes
    cout << "Minimal indexes: ";
    for (int i = 0; i < min_indexes.size(); i++) {
        cout << min_indexes[i] << " ";
    }
    cout << endl << endl;

    // --------------------------------------------------
    // 2. Lets find the maximal cost
    // --------------------------------------------------
    vector <int> max_indexes;
    int max_cost = solve(mat, max_indexes, 1);
    cout << "Maximal cost: " << max_cost << endl;
    // print max_indexes
    cout << "Maximal indexes: ";
    for (int i = 0; i < max_indexes.size(); i++) {
        cout << max_indexes[i] << " ";
    }
    cout << endl;

    return 0;
}