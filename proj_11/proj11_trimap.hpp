/*
 Kristjan von Bulow CSE 232 Project 11
 This project deals with linked lists
 */

#ifndef SINGLELINK_H
#define SINGLELINK_H

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<sstream>
using std::ostringstream;
#include<utility>
using std::swap;
#include<string>
using std::string;

// forward declaration so we can make Element a friend of TriMap
template<typename K, typename V>
class TriMap;

// private Element, friend of TriMap class
template <typename K, typename V>
class Element{
    
private:
    K key_;
    size_t index_ = 0;
    Element *next_ = nullptr;
    
public:
    V value_;
    
    Element() = default;
    Element(K key, V val, size_t i) : key_(key),index_(i), next_(nullptr), value_(val) {};
    
    // *defined* in the class, makes templating easier.
    friend ostream& operator<<(ostream& out, Element& e){
        out << e.key_ << ":" << e.value_ << ":" << e.index_;
        return out;
    }
    friend class TriMap<K,V>;
};


template<typename K, typename V>
class TriMap{
    
private:
    Element<K,V> *head_ = nullptr;
    Element<K,V> *tail_ = nullptr;
    size_t size_ = 0;
    
    // a private function, used by operator<<
    void print_list(ostream& out);
    
public:
    TriMap() = default;
    TriMap(K, V);
    TriMap(const TriMap&);
    TriMap& operator=(TriMap);
    ~TriMap();
    long size();
    bool insert(K,V);
    bool remove(K);
    Element<K,V>* find_key(K);
    Element<K,V>* find_value(V);
    Element<K,V>* find_index(size_t);
    
    // *defined* in the class, makes templating easier.
    // uses private method print_list
    // you can remove print_list and just do it here if you
    // prefer. I won't test print_list
    friend ostream& operator<<(ostream& out, TriMap<K,V>& sl){
        sl.print_list(out);
        return out;
    };
};

template<typename K, typename V>
TriMap<K,V>::TriMap(K key, V value){
    head_ = tail_ = new Element<K,V>(key,value,size_);
    size_ += 1;
};

/*
 This construction takes a Trimap as a argument, returns a new Trimap
 */
template<typename K, typename V>
TriMap<K,V>::TriMap(const TriMap& tm){
    bool checker = true;
    if (tm.head_ != nullptr){ // if empty Trimap
        Element<K,V>* tm_ptr = tm.head_; // this will walk down list
        for(; tm_ptr != nullptr; tm_ptr = tm_ptr->next_){ //running through TriMap
            Element<K,V>* new_element = new Element<K,V>;
            *new_element = *tm_ptr; // copies new_element to tm_ptr
            if (checker == true){ // if its the first element to be copied
                head_ = new_element;
                tail_ = new_element;
                checker = false;
            }
            else{
                tail_->next_ = new_element; // next element is added from tail
                tail_ = new_element;
            }
        }
        tail_->next_ = nullptr; // ends the copying
        size_ = tm.size_; // copies over size
        
    }
}
template<typename K, typename V>
TriMap<K,V>& TriMap<K,V>::operator=(TriMap tm){
    swap(head_,tm.head_); // swaps both addresses
    swap(tail_,tm.tail_);
    return *this;
}


/*
 This method deletes a trimap, no arguments, no returns
 */
template<typename K, typename V>
TriMap<K,V>::~TriMap(){
    Element<K,V>* to_del = head_;
    while(to_del != nullptr){ // while Trimap is not empty
        head_ = head_->next_;
        delete to_del;
        to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
}
/*
 Method that returns size_ of TriMap
 */
template<typename K, typename V>
long TriMap<K,V>::size(){
    return size_;
}
/*
 Method that inserts a Element into a TriMap, args is a key and value
 return is a boolean
 */
template<typename K, typename V>
bool TriMap<K,V>::insert(K key, V value){
    Element<K,V> *ptr = nullptr;
    for(ptr = head_; ptr != nullptr; ptr = ptr->next_){
        if (ptr->key_ == key){ // if the key is already there
            return false;
        }
    }
    Element<K,V> *inserted_element = new Element<K,V>(key,value,size_);
    if (head_ == nullptr){ // if there is a empty TriMap
        head_ = tail_ = new Element<K,V>(key,value,size_);
        size_ += 1; // adds one to size of TriMap
        return true;
    }
    
    for(ptr = head_; ptr != nullptr; ptr = ptr->next_){
        if(key < ptr->key_){ // compares sizes of key
            inserted_element->next_ = head_; // switches next_ of both Elements
            head_ = inserted_element;
            size_ += 1;
            return true;
        }
        
        else{
            if(ptr->next_ != nullptr){ // if there isn't anything next to ptr
                if(inserted_element->key_ < ptr->next_->key_){
                    inserted_element->next_ = ptr->next_;
                    ptr->next_ = inserted_element;
                    size_+=1;
                    return true;
                }
            }
            else{
                tail_->next_ = inserted_element; // puts new element next to tail
                tail_ = inserted_element;
                size_ += 1;
                return true;
            }
        }
    }
}
/*
 This method removes an Element from a TriMap, key is searched to find Element, return is boolean
 */
template<typename K, typename V>
bool TriMap<K,V>::remove(K key){
    bool boolean = false; // starts false in case cannot find key
    int removed_index = 0; // this will be used to lower following indexes
    Element<K,V> *previous_element = nullptr; // used to remove Element
    for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
        if (n->key_ == key){ // if key is found
            previous_element->next_ = n->next_; // removes the Element in between
            removed_index = n->index_; // puts index into removed_index
            size_ -= 1; // lowers size by one
            boolean = true; // found the key and removed the Element
            break;
        }
        previous_element = n; // this sets to previous Element address
    }
    if (boolean == true){ // if found key
        for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
            if (n->index_ > removed_index){ // indexes higher than removed index
                n->index_ -= 1; // index is lower than 1
            }
        }
    }
    return boolean;
}

/*
 This method searches the TriMap for a key, argument is key, returns an Elements address
 */
template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_key(K key){
    Element<K,V>* result = nullptr;
    for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
        if (n->key_ == key){
            result = n;
            break;
        }
    }
    return result;
}

template<typename K, typename V>
/*
 Finds an Element by using an arg value. Returns an address of Element
 */
Element<K,V>* TriMap<K,V>::find_value(V val){
    Element<K,V>* result = nullptr;
    for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
        if (n->value_ == val){ // finds value
            result = n;
            break;
        }
    }
    return result;
}
/*
 Method that finds an Element by using the index. Arg is index, return is element address
 */
template<typename K, typename V>
Element<K,V>* TriMap<K,V>::find_index(size_t i){
    Element<K,V>* result = nullptr;
    for(Element<K,V> *n = head_; n != nullptr; n = n->next_){
        if (n->index_ == i){ // finds index
            result = n;
            break;
        }
    }
    return result;
    
}
/*
 This method will print the list in a TriMap, args is out
 */
template<typename K, typename V>
void TriMap<K,V>::print_list(ostream &out){
    // this is a class member function, has access
    // to private data. Called by operator<<
    ostringstream oss;
    Element<K,V> *ptr;
    for(ptr = head_; ptr != nullptr; ptr = ptr->next_){
        oss << *ptr << ", "; // prints out each Element
    }
    string s = oss.str();
    out << s.substr(0,s.size()-2); // removes trailing ", "
};


#endif
