//
//  proj_04.cpp
//  Created by Kristjan von Bulow
//  Copyright © 2018 Kristjan von Bulow. All rights reserved.
//

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string;

const string base_vals = "0123456789abcdefghijklmnopqrstuvwxyz";

// meta, strictly increase

string remove_duplicates(string s){
    
    string new_string = ""; // new result string
    int n  = s.size();
    int i = 0;
    while (i<n){ // goes through whole string
        if (s[i] == s[i+1]){ // if duplicate
            i++; //continue
        }
        else{
            char temp = s[i]; // set character into temp
            new_string.push_back(temp); // add character to end of new string
            i++;
        }
    }
    return new_string; // return new string
    
}

bool metadrome(string n, int base){
    string copy_base_vals = base_vals.substr(0,base); // takes substring according to base
    if (copy_base_vals.find(n) != string::npos){ // if can find exact input in string, index not equal to max
        return true;
    }
    else{
        return false;
    }
    
    
}
// plain, non-strictly increase
bool plaindrome(string n, int base){
    string copy_base_vals = base_vals.substr(0,base);
    n = remove_duplicates(n);
    if(metadrome(n,base) == true){ // if first test works, its plaindrome
        return true;
    }
    else{
        return false;
    }
    
    
}
// kata, strictly decrease
bool katadrome(string n, int base){
    string copy_base_vals = base_vals.substr(0,base);
    string reverse_base_vals = ""; // creates new string for reverse
    for (long i = copy_base_vals.size()-1; i >= 0; --i ){ // starts at last index and goes backwards to add each index to new reverse string
        reverse_base_vals += copy_base_vals[i]; // adding to new revese string
    }
    if (reverse_base_vals.find(n) != string::npos){ // if input is in reverse string
        return true;
    }
    else{
        return false;
    }
    
    
}
// nialp, non-strictly decrease
bool nialpdrome(string n, int base){
    string copy_base_vals = base_vals.substr(0,base);
    n = remove_duplicates(n);
    if (katadrome(n,base) == true){
        return true;
    }
    else {
        return false;
    }
}
// non, none of the above
string classify(string n, int base){
    string answer = "";
    if (metadrome(n,base) == true){
        answer.append("metadrome");
    }
    else if (plaindrome(n,base) == true){
        answer.append("plaindrome");
    }
    else if(katadrome(n,base) == true){
        answer.append("katadrome");
    }
    else if (nialpdrome(n,base) == true){
        answer.append("nialpdrome");
    }
    else {
        answer.append("nondrome");
    }
    
    return answer;
}




int main (){
    string num;
    long base;
    cout << boolalpha;
    cin >> num >> base;
    cout << metadrome (num, base) << " "
    << plaindrome (num, base) << " "
    << katadrome (num, base) << " "
    << nialpdrome (num, base) << " "
    << classify(num, base) << endl;
}






