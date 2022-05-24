//-----------------------------------------------------------------------------
//  Dmitrius Agoston
//  Dagoston
//  pa7
//
//  DictionaryTest.cpp 
//  A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main() {
    string s;
    string S[] = {"f", "e", "d", "c", "b", "a", "Hello", "World", "Bye", "Thank", "You", "AAA", "aaa", "aab", "aac"};

    Dictionary A;

    for (int i = 0; i < 15; i++) {
        A.setValue(S[i], i+1);
    }

    cout << "A" << endl;
    cout << A << endl;
    cout << A.pre_string() << endl;

    Dictionary B = A;

    cout << "B" << endl;
    cout << B << endl;
    cout << B.pre_string() << endl;

    B.clear();

    cout << "B" << endl;
    cout << B << endl;
    cout << B.pre_string() << endl;

    cout << "A Size(): " << A.size() << " B Size(): " << B.size() << endl;

    cout << "A contains 'f'?" << endl;
    if (A.contains("f")) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    cout << "B contains 'f'?" << endl;
    if (B.contains("f")) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    cout << "A==B is " << (A==B?"true":"false") << endl;

    A.getValue("Hello") *= 7;
    A.setValue("World", 720);
    cout << A.getValue("Hello") << " " << A.getValue("World") << endl;

    int x = 0;
    for(A.begin(); A.hasCurrent(); A.next()){
        s = A.currentKey();
        x = A.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl;

    for(A.end(); A.hasCurrent(); A.prev()){
        s = A.currentKey();
        x = A.currentVal();
        cout << "("+s+", " << x << ") ";
    }
    cout << endl;


    try{
    A.getValue("blah");
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.remove("blah");
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentKey();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentVal();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }  
    try{
        A.next();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.prev();
    }catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    return 0;
}
