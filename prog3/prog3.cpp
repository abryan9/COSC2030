#include<iostream>
#include<string>
#include<fstream>
#include<cstdint>
#include<typeinfo>
#include "hash.h"
#include "timer.h"
#include "binaryNode.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::uint32_t;


#define BIG_CONSTANT(x) (x##LLU) // 


template<class T>
hash<T>::hash() {
    hashArray = new T[HASHSIZE];
    size = 0;
    for (int i=0; i<HASHSIZE; i++) {
        hashArray[i] = "";
    }

    goodCompares=0; badCompares=0;
    inDict=0; notInDict=0; notChecked=0;
    misspelled = nullptr;
}


template<class T>
hash<T>::~hash() {
    delete [] hashArray;
}


template<class T>
void hash<T>::insert(T item) {
    const void * word = item.c_str();
    uint32_t key = findHash(word, item.length(), HASHSIZE);

    if (hashArray[key].empty()) {
        hashArray[key] = item;
    } else {
        int i = (int)item[0];

        bool entered = false;
        while (!entered) {
            key = ((i * (r - (key % r))) % HASHSIZE);
            if (hashArray[key].empty()) {
                hashArray[key] = item;
                entered = true;
            }
        }

        }

    size++;
}


template<class T>
bool hash<T>::find(T item) {

    if (!isalpha(item[0])) {

        if(!(item[0] == '\0')) {
            notChecked++;
        }
        return false;
    }

    const void * word = item.c_str();

    int key = findHash(word, item.length(), HASHSIZE);

    if (hashArray[key].compare(item) == 0) {
        goodCompares++;
        inDict++;
        return true;
    } else if (hashArray[key].empty()) {
        insert_misspelled(item);
        notInDict++;
        return false;
    } else {
        int i = (int)item[0];

        bool found = false;
        while (!found) {
            key = ((i * (r - (key % r))) % HASHSIZE);
            if (hashArray[key].compare(item) == 0) {
                goodCompares++;
                inDict++;
                found = false;
                return true;
            } else if (hashArray[key].empty()) {
                badCompares++;
                notInDict++;
                insert_misspelled(item);
                return false;
            }
        }
    }
    
    badCompares++;
    notInDict++;
    return false;
}


template<class T>
int hash<T>::findHash(const void * word, int len, uint32_t seed) {

    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    uint32_t h = seed ^ len;

    const unsigned char * data = (const unsigned char *)word;

    while (len >= 4) {
        uint32_t k = getBlock((const uint32_t *)data);

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch(len) {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h % HASHSIZE;
}


template<class T>
inline uint32_t hash<T>::getBlock(const uint32_t * p) {

    #if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
        return *p;
    #else
        const uint8_t *c = (const uint8_t *)p;
        return (uint32_t)c[0] |
        (uint32_t)c[1] <<  8 |
	    (uint32_t)c[2] << 16 |
	    (uint32_t)c[3] << 24;
    #endif
}


template<class T>
void hash<T>::insert_misspelled(T item) {
    if (misspelled == nullptr) {
        misspelled = new binaryNode<T>(item);
    } else {
        binaryNode<T> * tmp = new binaryNode<T>(item);
        tmp -> left = misspelled;
        misspelled -> right = tmp;
        misspelled = tmp;
    }
}


template<class T>
void hash<T>::print_misspelled(fstream &file) {
    binaryNode<T> * tmp;
    for (tmp = misspelled; tmp != nullptr; tmp = tmp -> left) {
        
        file << tmp -> data << endl;
        if (tmp -> right != nullptr) {
            delete tmp -> right;
        }
    }

    delete tmp;
}


string clean_word(string word) {
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


int main() {

    fstream dict("dict.txt");
    fstream book("book.txt");
    fstream misspelled("misspelled.txt", std::ios::out | std::ios::trunc);
    Timer time;

    hash<string> hash;

    string in;
    while (dict >> in) {
        in = clean_word(in);
        hash.insert(in);
    }

    time.Start();

    string check;
    while (book >> check) {
        hash.find(clean_word(check));
    }

    time.Stop();

    hash.print_misspelled(misspelled);

    cout << "dictionary size " << hash.getSize() << "\nDone checking and these are the results\n";
    cout << "finished in time: " << time.Time() << "\n";
    cout << "There are " << hash.get_in_dict(1) << " words found in the dictionary\n";
    cout << "\t" << hash.get_compares(1) << " compares. Average: " << (hash.get_compares(1) / hash.get_in_dict(1));
    cout << "\nThere are " << hash.get_in_dict(0) << " words NOT found in the dictionary\n";
    cout << "\t" << hash.get_compares(0) << " compares. Average: " << (hash.get_compares(0) / hash.get_in_dict(0));
    cout << "\nThere are " << hash.get_not_checked() << " words not checked.\n";

    dict.close();
    book.close();
    misspelled.close();

    return 0;
}
