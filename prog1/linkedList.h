#ifndef LINKEDLIST_
#define LINKEDLIST_

#include "node.h"
#include<iostream>
using std::string;
using std::fstream;

template<class T>
class linkedList {
    private:
        node<T> * head;
        int size;
        long long int goodCompares;
        long long int badCompares;
        int inDict;
        int notInDict;
        int notChecked;
    public:
        linkedList() {
            head = nullptr; size = 0; goodCompares = 0; badCompares=0; inDict = 0; notInDict = 0; notChecked = 0;
            }
        ~linkedList();

        // USE RECURSION FOR INSERTION IN NON-FRONT LOCATIONS
        void insert_front(T item); // Update for last ptr
        void insert_before_node(node<T> * location, T data);
        void remove_front(); // Update for last ptr
        void remove_last(); // update for last ptr
        void set_head(node<T> * head);
        T return_front();
        void print();
        string clean_word(string word);
        int get_size() {return size;}
        long int get_compares(int check) {if (check) {return goodCompares;} else {return badCompares;}}
        int get_in_dict(int check) {if (check) {return inDict;} else {return notInDict;}}
        int get_not_checked() {return notChecked;}
        node<T> * get_head() {return head;}

        int find(T item, fstream &file); // This is the time bitch :(
        void sort(T item);

};

#endif