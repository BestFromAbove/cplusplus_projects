//
//  proj07_functions.cpp
//
//  Created by Kristjan von Bulow.
//  Copyright © 2018 Kristjan von Bulow. All rights reserved.
//

#include<string>
using std::string;
using std::getline;
using std::stod;
using std::to_string;
#include<vector>
using std::vector;
#include<map>
using std::map;
#include<fstream>
using std::ifstream;
#include<utility>
using std::pair;
using std::make_pair;
#include <iostream>
#include <math.h>
using std::ostream;
using std::endl;
using std::cout;
using std::fixed;
#include <sstream>
using std::stringstream;
using std::ostringstream;
#include <algorithm>
using std::sort;
using std::transform;
using std::copy;
using std::back_inserter;
#include <iomanip>
using std::setprecision;
#include <iterator>
using std::ostream_iterator;
#include "proj07_functions.h"

/*
 Input string s, char delim
 Outputs vector<string>
 Will split string into vector according to delim
 */
vector<string> split(const string &s, char delim){
    vector<string> result_v;
    string temp;
    stringstream sstream;
    sstream.str(s);
    while (getline(sstream,temp,delim)){ // this splits from delim
        result_v.push_back(temp);
    }
    return result_v;
}
/*
 Takes input stream and converts into map
 */
void read_data(map<vector<double>, string> &m, unsigned int feature_count, ifstream &inf){
    string temp_s;
    string temp_last_s;
    vector<string> string_v;
    vector<double> temp_d;
    char delim = ',';
    while (getline(inf,temp_s)){
        string_v = split(temp_s,delim); // uses function to convert string to vector<string>
        temp_last_s = string_v.back(); // saves last element to temp string
        string_v.pop_back(); // removes last element
        transform(string_v.begin(), string_v.end(),back_inserter(temp_d), // lambda function converts string to double
                  [](const string& iter){
                      return stod(iter);
                  });
        m.insert(make_pair(temp_d,temp_last_s)); // inserts pair into map
        temp_d.clear();
        temp_last_s.clear();
    }
}
/*
 Takes a pair and converts it to string
 */
string pair_to_string(const pair<vector<double>, string> &p){
    ostringstream oss; // declares ostringstream
    oss << fixed << setprecision(3); // for precision
    copy(p.first.begin(), p.first.end(), ostream_iterator<double>(oss, " "));
    oss << p.second;
    return oss.str(); // returns ostringstream as string
}
/*
 Takes a map and prints according to ostream
 */
void print_map(const map<vector<double>, string> &m,ostream &out){
    transform(m.begin(),m.end(),ostream_iterator<string>(out, "\n"), pair_to_string); // uses transform function to print according to &
}
/*
 Uses the Euclidean distance in order to figure out distance between two vectors
 */
double distance(const vector<double> &v1, const vector<double> &v2, unsigned int feature_count){
    double answer;
    double temp;
    int j = v1.size();
    for(int i = 0; i < j; ++i){ // part of Euclidean distance formula
        double temp_2 = v2[i] - v1[i];
        temp = pow(temp_2, 2);
        answer += temp;
    }
    answer = sqrt(answer);
    return answer; // Returns distance
}
/*
 This will determine the closest k neighbors to test vector<double>
 */
map<vector<double>, string> k_neighbors(const map<vector<double>, string> &m, const vector<double> &test, int k){
    map<vector<double>,string> map_answer;
    map<double,vector<double>> new_map_key;
    vector<double> temp_v;
    vector<double> temp_v_final;
    for(auto iter = m.cbegin(); iter != m.cend(); ++iter){ //goes through map
        double distance_final =  distance(test,iter->first,0); // determines distance between test vector and vector of iteration
        new_map_key[distance_final] = iter->first; // makes new map to use distance as keys, helps for later on
        if (distance_final > 0.000002){ // makes sure test isn't referenced
            temp_v.push_back(distance_final);
        }
    }
    sort(temp_v.begin(), temp_v.end()); // sorts according to lowest value of distance
    for (int i = 0; i < k; i++){
        vector<double> temp_double;
        string temp_string;
        temp_double = new_map_key.find(temp_v[i])->second; // uses distance as key in new map to find original vector<double>
        temp_string = m.find(temp_double)->second; // uses original vector<double> as key to find string associated
        map_answer[temp_double] = temp_string; // new map with only k-nearest neighbors
    }
    
    return map_answer; // returns new map
}
/*
 This will take one pair and use k_neighbor function to get closet neighbors. Will check how close function worked from 0.0 to 1.0. Return answer as double
 */
double test_one(const map<vector<double>, string> &m, pair<vector<double>, string> test, int k){
    double answer = 0.0;
    double answer_int = 0.0;
    double counter = 0.0;
    map<vector<double>, string> comparison_map = k_neighbors(m,test.first,k);
    for(auto iter = comparison_map.cbegin(); iter != comparison_map.cend(); ++iter){ // iterates throughout new map to compare with test
        if (iter->second == test.second){ // if the strings from key are equal, they are equal
            answer_int += 1.0;
        }
        counter += 1.0;
    }
    answer = answer_int/counter; // this will find the double of how accurate the function was
    return answer;
}
/*
 This goes through the whole map and uses each iteration as a pair for test_one function. This will test whole map for accuracy. Each double from test_one will return and be added up to calculate total accuracy.
 */
double test_all(const map<vector<double>, string> &m, int k){
    double input;
    double count = 0.0;
    for(auto iter = m.cbegin(); iter != m.cend(); ++iter){ // iterates through map
        input += test_one(m,*iter,k); // takes pair of *iter and compares with rest of map
        count += 1.0;
    }
    input = input/count; // compares total accuracy with each test to count
    return input; // returns total accuracy
}
