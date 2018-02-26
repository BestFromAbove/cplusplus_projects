/*
 Kristjan von Bulow
 CSE 232
 Project 09 TriMap
 Description:
 This program works with a STL-like data structure called TriMap, calls in Elements, which consist of a key, value, and index. TriMap is a vector<Element> with a sz (size). You can insert elements, remove elements, find element by key,
 index, and value.
 */
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

/*
 This is the non-default constructor for a TriMap, it takes in class Element as an arg (arg1). Will add Element to vec_ and determine size of vector with method size().
 */
TriMap::TriMap(const Element& arg1){
    vec_.push_back(arg1); // pushes back Element in vec_
    sz_ = vec_.size(); // Determines size of vec_ from size() method.
}
/*
 This is a non-default constructor for a TriMap, it takes in a initializer list and back inserts values into vec_. Also determines size of vector with size() method.
 */
TriMap::TriMap(initializer_list<Element> arg1){
    copy(arg1.begin(),arg1.end(),back_inserter(vec_)); // uses copy method to insert Element into TriMap
    sz_ = vec_.size(); // Determines size of vec_ from size() method.
}
/*
 This is a ostream operator that will take in method of ostream (out) and class Element (e). Will use ostringstream to format a string for printing. Returns ostream (out).
 */
ostream& operator<<(ostream& out, const Element& e){
    ostringstream oss;
    oss << e.key_ << ":" << e.value_ << ":" << e.index_; //formatting for mimir.
    string s = oss.str();
    out << s;
    return out;
    /*
     This is an ostream operator that will take in method of ostream (out) and class TriMap (t). Will use ostringstream to format a string for printing. Returns ostream (out).
     */
}
ostream& operator<<(ostream& out , const TriMap& t){
    ostringstream oss;
    copy(t.vec_.begin(), t.vec_.end(), ostream_iterator<Element>(oss, ", ")); // uses copy method to make string formatting for mimir.
    string s = oss.str();
    out << s.substr(0, s.size()-2); // remove trailing ", "
    return out;
    
}
/*
 Method for TriMap class that takes the size of current vec_.
 Returns size with type size_t.
 */
size_t TriMap::size(){
    return vec_.size();
}
/*
 This is a TriMap method that will insert a new Element into the TriMap vector. Takes 2 args, string key and string value. Will first check if the Element already exist, if it does, will return false. Then will use upper_bound method to find the index where to place new Element. If new Element is inserted, will return true.
 Returns true or false.
 */
bool TriMap::insert(string key,string value){
    for(size_t i = 0; i < sz_; ++i){ // searches to find a duplicate of Element
        if (vec_[i].key_ == key){ // if key already exists
            return false;
        }
    }
    size_t indx = vec_.size();
    Element temp(key, value, indx); // creates new element for inserting
    vector<Element>::iterator pos;
    pos = upper_bound(vec_.begin(),vec_.end(), key,[](const string& key, const Element& e){ // compares two keys to figure out where to put new key.
        return key < e.key_;
    });
    vec_.insert(pos,temp); // inserts new Element in right position (pos)
    return true;
}
/*
 This method of TriMap will remove an Element in the vector. It does this by looking for the key. arg is string key. Uses find_if method to look for key, if it doesn't find key, returns false. Else, will remove Element, then sort indexes to adjust from removal of Element.
 Returns true or false.
 */
bool TriMap::remove(string key){
    auto pos = find_if(vec_.begin(),vec_.end(),[&key](Element& e){
        return key == e.key_; // find matching key from arg
    });
    if (pos == vec_.end()){ // if cant find key
        return false;
    }
    else{
        vec_.erase(pos); // remove Element
        for (size_t i = 0; i < vec_.size(); ++i){ // adjusts other indexes
            if (vec_[i].index_ != 0){ // if not 0 index
                vec_[i].index_ -= 1; // decrease index by 1
            }
        }
        return true;
    }
}
/*
 This method of TriMap find a key by using binary search (upper_bound). First takes care of front and back of vector, then uses upper_bound to check the rest.
 Arg is string key. If the iter doesn't reach end, will return Element in TriMap. Else, will return nullptr.
 */
Element* TriMap::find_key(const string& key){
    if (vec_.front().key_ == key){ // checks front of vector
        return &(vec_.front());
    }
    else if (vec_.back().key_ == key){ // checks back of vector
        return &(vec_.back());
    }
    else{
        
        auto pos = upper_bound(vec_.begin(),vec_.end(),key,[](string key, Element& e){ // uses binary serach to find key in TriMap vector (vec_)
            return key == e.key_;
        });
        if (pos != vec_.end()){ // if iter finds key
            return &(*pos); // returns Element
        }
        else{
            return nullptr; // can't find key
        }
    }
    
}
/*
 Method of Trimap that will find the Element in a TriMap by using the value. Arg is string value. uses find_if method to find Element in TriMap. Returns position if found Element, returns nullptr if not.
 */
Element* TriMap::find_value(const string& value){
    auto pos = find_if(vec_.begin(),vec_.end(),[&value](Element& e){
        return value == e.value_; // finds matching value from arg
    });
    if (pos != vec_.end()){ // if can find value
        return &(*pos);
    }
    else{
        return nullptr; // returns no matching position
    }
}
/*
 Method of Trimap that will find the Element in a TriMap by using the index. Arg is string index. uses find_if method to find Element in TriMap. Returns position if found Element, returns nullptr if not.
 */
Element* TriMap::find_index(size_t index){
    auto pos = find_if(vec_.begin(),vec_.end(),[&index](Element& e){
        return index == e.index_; // if index matches from arg
    });
    if (pos != vec_.end()){ // if can find index
        return &(*pos); // returns Element
    }
    else{
        return nullptr; // returns if can't find index
    }
}
