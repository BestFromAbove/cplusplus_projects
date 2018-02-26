//
//  proj11_main.cpp
//  HelloWorld
//
//  Created by Kristjan von Bulow.
//  Copyright © 2018 Kristjan von Bulow. All rights reserved.
//

#include<sstream>
#include<iostream>
using std::ostringstream;
using std::endl;
using std::cout;
using std::cin;
#include<string>
using std::string;
#include "proj11_trimap.hpp"

int main() {
    cout << std::boolalpha;
    TriMap <long, long>m;
    m.insert(2,20);
    m.insert(1, 10);
    m.insert(4,40);
    m.insert(3,30);
    bool result = m.remove(3);
    cout << result << endl;
    //ASSERT_TRUE(result);
    size_t sz = m.size();
    cout << sz << endl;
    //ASSERT_EQ(sz, 3);
    ostringstream oss;
    oss << m;
    string s = oss.str();
    string ans = "1:10:1, 2:20:0, 4:40:2";
    cout << s << endl;
    //ASSERT_EQ(s,ans);
    
    
}
