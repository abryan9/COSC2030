#include<iostream>
#include<ctype.h>
#include<fstream>
#include "linkedList.h"
#include "timer.h"

using std::cout;
using std::to_string;
using std::fstream;


template<class T>
linkedList<T>::~linkedList() {
    cout << "[Destructor]\n";

    while (size > 0) {
        node<T> * tmp = head -> next;
        delete head;
        head = tmp;
        size--;
    }
        

    /*
    for (node<T> * tmp = head; head; tmp = head) {

        while (tmp -> down != nullptr) {
            node<T> * oldDown = tmp -> down;
            tmp -> down = tmp -> down -> down;
            delete oldDown;
        }

        head = head -> next;
        delete tmp;
    }
    */
}


template<class T>
void linkedList<T>::insert_front(T item) {

    node<T> * tmp = new node<T>(item);

    tmp -> next = head;
    tmp -> prev = nullptr;

    head = tmp;

    size ++;
}


template<class T>
void linkedList<T>::insert_before_node(node<T> * location, T data) {
    node<T> * prevLocat = location -> prev;
    node<T> * insert = new node<T>;

    insert -> data = data;
    insert -> next = location;
    insert -> prev = prevLocat;

    location -> prev = insert;
    prevLocat -> next = insert;

    size ++;
}


template<class T>
void linkedList<T>::remove_front() {
    node<T> * tmp;

    if (head != nullptr) {
        tmp = head;
        head = tmp -> next;
        delete tmp;

        size --;
    }
}


template<class T>
T linkedList<T>::return_front() {
    if (head != nullptr) {
        return head -> data;
    } else {
        return T(0);
    }
}


template<class T>
string linkedList<T>::clean_word(string word) {
    
    for (int i=0; i<word.length(); i++) {
        if (!(isalnum(word[i]) || (word[i] == '\''))) {
            word.erase(word.begin()+i);
            i--;
        }

        if (isupper(word[i])) {
            word[i] = tolower(word[i]);
        }
    }

    return word;
}


template<class T>
void linkedList<T>::print() {
    
    for (node<T> * tmp = head; tmp -> next != nullptr; tmp = tmp -> next) {
        cout << tmp -> data;
        cout << "->";

        if (tmp -> next == nullptr) {
            for (node<T> * tmp; tmp != nullptr; tmp = tmp -> prev) {
                cout << tmp -> data;
                cout << "->";
            }
        }
    }

}


template<class T>
int linkedList<T>::find(T item, fstream &file) {

    item = clean_word(item);

    if (!isalpha(item[0])) {
        //cout << "[+] not checked (starts with " << item[0] << "\n";

        if(!(item[0] == '\0')) {
            notChecked++;
        }
        return 0;
    }

    int compares = 0;
    for (node<T> * tmp = head; tmp != nullptr; tmp = tmp -> next) {
        compares++;
        if (item.compare(tmp -> data) == 0) {
            goodCompares += compares;
            inDict++;
            return 1;
        }
    }
    /*
    for (node<T> * tmp = head; tmp != nullptr; tmp = tmp -> next) {
        if (tmp -> data[0] == item[0]) {

            //cout << "[+] entered next loop\n";

            for (tmp; tmp -> down != nullptr; tmp = tmp -> down) {
                
                compares++;

                if (!item.compare(tmp -> data)) {
                    goodCompares += compares;
                    inDict++;
                    //cout << "[+] found\n";
                    return 1;
                }
            }

            //cout << "[+] ran loop\n";
        }
    }
    */

    badCompares += compares;
    notInDict++;
    file << item << "\n";
    //cout << "[+] not found\n";

    return 0;
}


template<class T>
void linkedList<T>::sort(T item) {

    insert_front(item);

    /*
    bool changed = false;

    for (node<T> * tmp = head; tmp != nullptr; tmp = tmp -> next) {
        if (tmp -> data[0] == item[0]) {
            // cout << "[+] made it here\n";
            if (tmp -> down == nullptr) {
                node<T> * newNode = new node<T>;
                tmp -> down = newNode;
                newNode -> up = tmp;
                tmp -> data = item;
                size++;
            } else {
                bool isInList = false;
                bool exit = false;
                for (tmp; ((tmp -> down != nullptr) and (!exit)); tmp = tmp -> down) {
                    // cout << tmp -> down -> data << "\n";
                    if (!(item.compare(tmp -> data))) {
                        isInList = true;
                        exit = true;}
                    goodCompares++;
                }

                if (!isInList) {
                    node<T> * insert = new node<T>;
                    insert -> data = item;
                    tmp -> down = insert;
                    insert -> up = tmp;
                    size++;
                }
            }
            changed = true;
        } else if (tmp -> next == nullptr && !changed) {
            insert_front(item);
            node<T> * temp = head;
            node<T> * newNode = new node<T>;
            temp -> data = item;
            temp -> down = newNode;
            newNode -> up = temp;
        }
    }
    */
}


int main() {

    fstream dict("dict.txt");
    fstream book("book.txt");
    fstream mispelledTxt("mispelled.txt", std::ios::out | std::ios::trunc);
    Timer time;

    linkedList<string> strTest;

    string in;
    while(dict >> in) {   
        //cout << in << "\n";
        strTest.sort(in);
    }

    cout << "[+]\n";

    time.Start();

    string check;
    while(!book.eof()) {
        book >> check;
        strTest.find(check, mispelledTxt);
    }

    time.Stop();

    dict.close();
    book.close();
    mispelledTxt.close();

    


    // cout << "[+] done\n";

    cout << "dictionary size " << strTest.get_size() << "\nDone checking and these are the results\n";
    cout << "finished in time: " << time.Time() << "\n";
    cout << "There are " << strTest.get_in_dict(1) << " words found in the dictionary\n";
    cout << "\t" << strTest.get_compares(1) << " compares. Average: " << (strTest.get_compares(1) / strTest.get_in_dict(1));
    cout << "\nThere are " << strTest.get_in_dict(0) << " words NOT found in the dictionary\n";
    cout << "\t" << strTest.get_compares(0) << " compares. Average: " << (strTest.get_compares(0) / strTest.get_in_dict(0));
    cout << "\nThere are " << strTest.get_not_checked() << " words not checked.\n";
    
    // strTest.print();

    return 0;
}