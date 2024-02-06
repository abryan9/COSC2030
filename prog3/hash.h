#ifndef HASH_
#define HASH_

#include "binaryNode.h"
#include<cstdint>
#include<fstream>

template<class T>
    class hash {
        private:
            const static int HASHSIZE = 266351;
            int r = 66587;
            T * hashArray; // had to change from name "hash" to prevent shadoowing with constructor
            int size;

            int goodCompares;
            int badCompares;
            int inDict;
            int notInDict;
            int notChecked;

            binaryNode<T> * misspelled;
        public:
            hash();
            ~hash();
            void insert(T item);
            bool find(T item);
            int getSize() {return size;}
            int findHash(const void * word, int len, uint32_t seed);
            static inline uint32_t getBlock(const uint32_t * p);

            int get_in_dict(int check) {if (check) {return inDict;} return notInDict;}
            int get_compares(int check) {if (check) {return goodCompares;} return badCompares;}
            int get_not_checked() {return notChecked;}

            void insert_misspelled(T item);
            void print_misspelled(std::fstream &file);
    };


#endif