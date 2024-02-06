#ifndef BINARYSEARCHTREE_
#define BINARYSEARCHTREE_

#include "binaryNode.h"
#include<fstream>
using std::fstream;

template <class T>
    class binarySearchTree {
        private:
            binaryNode<T> * root;
            binaryNode<T> * shallowNode;
            int size;
            int depth; // depth represents the MINIMUM depth. (useful for AVL)
            int localDepth; // used in find and get_min_depth to track the depth of a singular path
            int lR_1; // left-right -1 and -2 track the previous two moves
            int lR_2; // 1 is a move right, 0 is a move left
            int goodCompares;
            int badCompares;
            int localCompares;
            int inDict;
            int notInDict;
            int notChecked;

            binaryNode<T> * misspelled;

            void insert(T item, binaryNode<T> *&t, binaryNode<T> *p);
            binaryNode<T> * find(T item, binaryNode<T> *t);
            binaryNode<T> * get_shallow_node(binaryNode<T> *t);
            
        public:
            binarySearchTree() {root=nullptr; shallowNode=nullptr; misspelled=nullptr; size=0; depth=0; 
                                goodCompares=0; badCompares=0; localCompares=0; 
                                inDict=0; notInDict=0; notChecked=0;}
            ~binarySearchTree() {clear();}

            void insert(T item);
            binaryNode<T> * find(T item);
            binaryNode<T> * find_common_ancestor(binaryNode<T> *&t1, binaryNode<T> *t2);
            binaryNode<T> * get_shallow_node();

            void clear();
            int is_empty() {if (size == 0) {return 1;} else {return 0;}};
            void print_misspelled(fstream &file);
            void insert_misspelled(T item);

            int get_depth() {return depth;}
            int get_size() {return size;}
            int get_compares(int check) {if (check) {return goodCompares;} else {return badCompares;}}
            int get_in_dict(int check) {if (check) {return inDict;} else {return notInDict;}}
            int get_not_checked() {return notChecked;}
            int get_root() {return root;}

            void single_rotate_left(binaryNode<T> *t);
            void single_rotate_right(binaryNode<T> *t);
            void double_rotate_left(binaryNode<T> *t);
            void double_rotate_right(binaryNode<T> *t);
            void change_node_depth(binaryNode<T> *t, int change);


    };

#endif