// Kristjan von Bulow Project 10 11/29/17
/*
 This .cpp handles the package class with its methods.
 */
#include "proj10_package.hpp"
#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;
/*
 This ostream operator takes 2 args. ostream (out) and a package(p). It formats components of Package into a string and returns it to out.
 */
ostream& operator<<(ostream& out, Package& p){
    ostringstream oss;
    oss << p.weight_ << ":" << p.priority_; // formatting for printing
    string s = oss.str();
    out << s;
    return out;
}
/*
 This function compares two arguments, a Package (p1), and a second Package(p2). It will return the package with the better ratio.
 True if p1 has the greater ratio.
 False if p2 h as the greater ratio.
 */
bool package_compare(const Package &p1, const Package &p2){
    float ratio1;
    float ratio2;
    ratio1 = (float)p1.priority_/(float)p1.weight_; // ratio for Package 1
    ratio2 = (float)p2.priority_/(float)p2.weight_; // ratio for Package 2
    if (ratio1 > ratio2){
        return true;
    }
    else{
        return false;
    }
}
