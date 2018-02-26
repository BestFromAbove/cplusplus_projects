//
//  proj_05.cpp
//
//  Created by Kristjan von Bulow.
//  Copyright © 2018 Kristjan von Bulow. All rights reserved.
//

// beaufort cipher, http://practicalcryptography.com/ciphers/classical-era/beaufort/

#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string;
#include<algorithm>

const string alphabet = "abcdefghijklmnopqrstuvwxyz";

/*
 this function uses std:rotate to move each index in string to left
 takes 2 arguments, integer rotations and input string s
 Outputs rotated string.
 */
string rotate_left(int rotations, string s){
    if (rotations < 0){ // error checking
        
        return s;
    }
    
    for(int i = 0; i < rotations; i++){
        std::rotate(s.begin(),s.begin()+1,s.end()); // function that rotates left
    }
    
    return s;
    
}

/*
 This function takes a plain letter, error checks to make sure its alphabet and lowercase, then uses beaufort method to crypt each letter
 Outputs encrypted char.
 */
char beaufort_letter(char plain_letter,char key_letter){
    if (isupper(plain_letter) || isupper(key_letter)){
        return plain_letter; // error checking for capitals
    }
    if (!isalpha(plain_letter) || !isalpha(key_letter)){
        return plain_letter;
    }
    int num = plain_letter - 'a'; // finds out rotation number
    int location;
    string temp_alphabet = rotate_left(num, alphabet); // returns rotated alphabet
    location = temp_alphabet.find(key_letter); // finds location of key letter in alphabet
    return alphabet[location];
}
/*
 This function takes a plain letter, error checks to make sure its alphabet and lowercase, then uses vigenere method to crypt each letter
 Outputs encrypted character.
 */
char vigenere_letter(char plain_letter, char key_letter){
    if (isupper(plain_letter) || isupper(key_letter)){
        return plain_letter;
    }
    if (!isalpha(plain_letter) || !isalpha(key_letter)){
        return plain_letter;
    }
    int num = plain_letter - 'a';
    int location;
    string temp_alphabet = rotate_left(num, alphabet);
    location = alphabet.find(key_letter);
    return temp_alphabet[location];
}
/*
 This function takes both input strings (plain_text and key), and first checks to see if the key string is equal to the plain_text string. If not, key string will repeat through first index to fill rest of string. Then will iterate through each char in string to crypt through beaufort method.
 Outputs encrypted string.
 */
string encode_beaufort(string plain_text, string key){
    int i;
    int j = plain_text.length();
    int b;
    int k;
    string temp_string = "";
    b = plain_text.length() - key.length();
    if (b > 0){
        for (k = 0; k < b; k++){
            key += key[k];
        }
    }
    char temp_char;
    for (i = 0; i < j; i++){
        if (isalpha(plain_text[i])){ // error check
            temp_char = beaufort_letter(plain_text[i], key[i]); // goes through each char
            temp_string += temp_char; // appends character to new string
        }
        else{
            continue;
        }
    }
    
    return temp_string;
}
/*
 This function takes both input strings (plain_text and key), and first checks to see if the key string is equal to the plain_text string. If not, key string will repeat through first index to fill rest of string. Then will iterate through each char in string to crypt through vigenere method.
 Outputs encrypted string.
 */
string encode_vigenere(string plain_text,string key){
    int i;
    int j = plain_text.length();
    int b;
    int k;
    string temp_string = "";
    b = plain_text.length() - key.length(); // this will make key same length as plain_text
    if (b > 0){
        for (k = 0; k < b; k++){
            key += key[k];
        }
    }
    
    char temp_char;
    for (i = 0; i < j; i++){
        if (!isalpha(plain_text[i])){ // error check
            continue;
        }
        temp_char = vigenere_letter(plain_text[i], key[i]);
        temp_string += temp_char;
    }
    return temp_string;
}

int main (){
    int case_number;
    cin >> case_number;
    
    switch (case_number){
            
        case 1: {
            int rotations;
            cin >> rotations;
            string s;
            cin >> s;
            cout << rotate_left(rotations, s) << endl;
            break;
        }
            
        case 2: {
            char plain_letter;
            char key_letter;
            cin >> plain_letter >> key_letter;
            cout << beaufort_letter(plain_letter, key_letter) << endl;
            break;
        }
            
        case 3:{
            char plain_letter;
            char key_letter;
            cin >> plain_letter >> key_letter;
            cout << vigenere_letter(plain_letter, key_letter) << endl;
            break;
        }
            
        case 4:{
            string plain_text;
            string key;
            cin.ignore(100, '\n');
            getline(cin, plain_text);
            getline(cin, key);
            cout << encode_beaufort(plain_text, key) << endl;
            break;
        }
            
        case 5:{
            string plain_text;
            string key;
            cin.ignore(100, '\n');
            getline(cin, plain_text);
            getline(cin, key);
            cout << encode_vigenere(plain_text, key) << endl;
            break;
        }
            
    } // of switch
} // of main
