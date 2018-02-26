//
//  proj07_main.cpp
//
//  Created by Kristjan von Bulow.
//  Copyright © 2018 Kristjan von Bulow. All rights reserved.
//

#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<map>
using std::map;
#include<fstream>
using std::ifstream;
#include<utility>
using std::pair;

#include "proj07_functions.h"

int main (){
    ifstream f("little.txt"); // little not included in repo, temp file used for testing
    map<vector<double>, string> m;
    map<vector<double>,string> new_map;
    read_data(m, 4, f);
    vector<double> first_d = {4.6,3.1,1.5,0.2};
    vector<double> second_d = {4.7,3.2,1.3,0.2};
    new_map = k_neighbors(m,first_d,4);
    print_map(new_map, cout);
    
    // Below was extra testing, not needed and probably should be deleted
    
    /*map<vector<double>, string> m;
     // ifstream f("little.txt");
     ifstream f("iris.data.txt");
     read_data(m, 4, f);
     print_map(m, cout);
     auto start = m.begin();
     auto follow = next(start, 1);
     cout << distance(start->first, follow->first, 4) << endl;
     auto result = k_neighbors(m, start->first, 3);
     cout << "test: " << pair_to_string(*m.begin() ) << endl;
     print_map(result, cout);
     cout << "Accuracy for first: "<<test_one(m, *(m.begin() ), 3) << endl;
     cout << "Accuracy for all: " << test_all(m, 3) << endl;
     */
}

