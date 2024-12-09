#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Node {
private:
        

public:
    string data;               
    vector<Node> children;
    Node(string s);          
    void addSon(string s);  
    Node& getSon(int i);   
    void print(int lvl, ofstream& outputFile); 
    void print(int lvl); 
};