//
//  proj09_main.cpp
//
//  Created by Kristjan von Bulow.
//  Copyright © 2018 Kristjan von Bulow. All rights reserved.
//

#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;
#include<iterator>
using std::ostream_iterator; using std::back_inserter;
#include<algorithm>
using std::copy; using std::upper_bound; using std::find;
#include<initializer_list>
using std::initializer_list;
#include "proj09_trimap.h"

int main(){ // used for testing
    TriMap m;
    m.insert("w","x");
    m.insert("c", "d");
    m.insert("a","b");
    m.insert("y","z");
    bool result = m.remove("c");
    ostringstream oss;
    oss << m;
    string s = oss.str();
    cout << s << endl;
    
    
    
    
    
    
    
    
    
    
    return 0;
}
