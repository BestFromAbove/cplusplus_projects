// Kristjan von Bulow Project 10 11/29/17
/*
 This .cpp handles the Knapsack class and its methods.
 */
#include "proj10_knapsack.h"
#include<iostream>
using std::ostream;
using std::cout;
using std::endl;
#include<string>
using std::string;
#include <utility>
#include<algorithm>
using std::copy;
using std::sort;
#include<sstream>
using std::ostringstream;
#include <fstream>
using std::ifstream;
#include <stdexcept>
using std::runtime_error;
using std::getline;
#include<vector>
using std::vector;
/*
 This is a non-default constructor with argument arg1 as the weight_limit
 */
Knapsack::Knapsack(size_t arg1){
    weight_limit_ = arg1; // sets weight_limit to arg
    capacity_ = 10; // default
    size_ = 0; // default
    data_ = new Package[capacity_]; // Puts data in new package of size capacity_
}
/*
 This is a non-default constructor with arguments arg1 as weight_limit and arg2 as capacity
 */
Knapsack::Knapsack(size_t arg1, size_t arg2){
    weight_limit_ = arg1;
    capacity_ = arg2; // sets capacity_ to arg2
    size_ = 0;
    data_ = new Package[capacity_];
}
/*
 This is the copy ctor with an argument that is a Knapsack (k), takes a copy of arg and returns new knapsack.
 */
Knapsack::Knapsack(const Knapsack& k){ // check other function, same thing
    weight_limit_ = k.weight_limit_;
    capacity_ = k.capacity_;
    size_ = k.size_;
    data_ = new Package[capacity_];
    copy(k.data_, k.data_ + k.size_, data_); // uses copy function to bring the data from argument Package(k) over to new Package
}
/*
 This is the destructor. It deletes a knapsack. no arguments
 */
Knapsack::~Knapsack(){
    if(data_){
        delete[] data_; // removes the Knapsack
    }
}
/*
 This is a method of Knapsack that returns the capacity data member as long. No arguments
 */
long Knapsack::capacity() const{
    long temp;
    temp = capacity_;
    return temp;
}
/*
 This is a method of Knapsack that returns the size data member as long. No arguments
 */
long Knapsack::size() const{
    long temp;
    temp = size_;
    return temp;
}
/*
 This is a getter of Knapsack that returns weight_limit as long. No arguments
 */
long Knapsack::weight_limit() const{
    long temp;
    temp = weight_limit_;
    return temp;
}
/*
 This checks if the Knapsack is empty. No arguments
 */
bool Knapsack::empty() const{
    if (size_ == 0){ // if empty
        return true;
    }
    else{
        return false;
    }
}
/*
 This is a getter that returns the weight of the knapsack into a long.
 */
long Knapsack::weight() const{
    long temp = 0;
    for(int i = 0; i < size_;++i){ // goes through each Package in Knapsack
        temp += data_[i].weight_; // adds each Package.weight_ to a total
    }
    return temp;
}
/*
 This is a getter that returns the priority into a long
 */
long Knapsack::priority() const{
    long temp = 0;
    for(int i = 0; i < size_; ++i){ // goes through each Package in Knapsack
        temp += data_[i].priority_; // adds each Package.priority_ to a total
    }
    return temp;
}
/*
 This operator allows to set two Knapsacks equal to each other, it does this by transferring over values. Argument is a knapsack. Returns a Knapsack
 */
Knapsack& Knapsack::operator=(const Knapsack k){
    weight_limit_ = k.weight_limit_;
    capacity_ = k.capacity_;
    size_ = k.size_;
    data_ = new Package[capacity_];
    copy(k.data_, k.data_ + k.size_, data_); // copies over argument k data_ to new Knapsack that will be returned.
}
/*
 This method of Knapsack allows to add a package to the Knapsack, argument is a package. Returns true if package was added or false if not.
 */
bool Knapsack::add(const Package& p){
    long current_weight;
    current_weight = weight(); // calculates total weight in Knapsack
    if ((p.weight_ + current_weight) > weight_limit_){ // if adding the Package goes over the weight_limit_
        return false;
    }
    else{
        if (size_+1 > capacity_){ // If adding the package goes over the capacity
            Package* new_data = new Package[2*capacity_]; // Doubles the capacity
            copy(data_, data_ + size_, new_data); // copies data from data_ to new_data with double capacity
            std::swap(new_data,data_); // swap pointers
            delete []new_data; // deletes original Knapsack
            capacity_ = capacity_*2;
        }
        // add package under here
        //cout << data_[0];
        data_[size_] = p; // places the new package in Knapsack
        size_ += 1; // adds the current size + 1
        return true; // addition successful
    }
}
/*
 This ostream operator takes 2 args. ostream (out) and a knapsack(k). It formats components of Knapsack into a string and returns it to out.
 */
ostream& operator<<(ostream& out, Knapsack & k){
    ostringstream oss;
    for (int i = 0 ; i < k.size_; ++i){
        oss << k.data_[i] << ", ";  // formatting for printing
    }
    string s = oss.str();
    s.pop_back(); // removing trailing " "
    s.pop_back(); // removing trailing ","
    out << s;
    return out;
}
/*
 This function is an attempt to solve the Knapsack problem. Args are a filename in string form and a Knapsack. This function returns nothing.
 */
void solve_KS(string fstring, Knapsack& k){
    ifstream ifs;
    ifs.open(fstring); // opens file
    long a; // weight
    long b; // priority
    vector<Package> temp_vector; // vector of type Package
    if(ifs.is_open()){
        while (ifs >> a >> b){ // gets both weight and priority
            Package temp_package; // new Package for storing
            temp_package.weight_ = a;
            temp_package.priority_ = b;
            temp_vector.push_back(temp_package); // adds new Package to end
        }
        sort(temp_vector.begin(),temp_vector.end(),package_compare); // sorts the vector of Packages by using package_compare function
        for (size_t i = 0; i < temp_vector.size(); i++){
            if(!k.add(temp_vector[i])){ // if the weight is over weight limit
                break; // stop adding Packages
            }
        }
    }
    else{ // if file cannot be found
        throw runtime_error("badfilename");
    }
    ifs.close(); // closes file
}

