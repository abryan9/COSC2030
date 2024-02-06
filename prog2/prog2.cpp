#include "binarySearchTree.h"
#include "timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include<ctype.h>

using std::string;
using std::to_string;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;


template <class T>
void binarySearchTree<T>::insert(T item) {
    binaryNode<T> * parent = nullptr; // reset parent
    localDepth = 0;
    lR_1 = 0; lR_2 = 0; // initialized to 0 arbitrarially, on the first move, they will both be set
    insert(item, root, parent); // to either 0 or 1 (depending on direction). move >=2 they will be set individually
}


template <class T>
void binarySearchTree<T>::insert(T item, binaryNode<T> *&t, binaryNode<T> *p) {

    if (t == nullptr) {
        t = new binaryNode<T> (item);
        t -> nodeDepth = localDepth;
        t -> parent = p; // on node insertion, track parent. Default is nullptr unless depth >=1.
        size++;
        if (localDepth > ((get_shallow_node() -> nodeDepth )+ 1)) {
            if (lR_1 == lR_2) {
                if (lR_1 == 0) {
                    single_rotate_left(find_common_ancestor(t, get_shallow_node()));

                } else {
                    single_rotate_right(find_common_ancestor(t, get_shallow_node()));

                }
            } else {
                if (lR_1 == 0) {
                    double_rotate_left(find_common_ancestor(t, get_shallow_node()));
                } else {
                    double_rotate_right(find_common_ancestor(t, get_shallow_node()));
                }
            }
        }

    } else if (item.compare(t -> data) < 0) {
        localDepth += 1;
        if (localDepth == 1) {
            lR_1 = 0;
            lR_2 = 0;
        } else {
            lR_2 = lR_1;
            lR_1 = 0;
        }

        if (t -> left == nullptr) {
            p = t;
        }
        insert(item, t -> left, p);

    } else if(item.compare(t -> data) > 0) {
        localDepth += 1;
        if (localDepth == 1) {
            lR_1 = 1;
            lR_2 = 1;
        } else {
            lR_2 = lR_1;
            lR_1 = 1;
        }

        if (t -> right == nullptr) {
            p = t;
        }
        insert(item, t -> right, p);

    }

}

template <class T>
binaryNode<T> * binarySearchTree<T>::find(T item) {
    localCompares=0;
    return find(item, root);
}


template <class T>
binaryNode<T> * binarySearchTree<T>::find(T item, binaryNode<T> *t) {

    if (!isalpha(item[0])) {

        if(!(item[0] == '\0')) {
            notChecked++;
        }
        return t;
    }

    if (t == nullptr) {
        badCompares += localCompares;
        notInDict += 1; 
        insert_misspelled(item);
        return nullptr;
    }


    if (item.compare(t -> data) < 0) {
        localCompares += 1;
        find(item, t -> left);

    } else if (item.compare(t -> data) > 0) {
        localCompares += 1;
        find(item, t -> right);

    } else if (item.compare(t -> data) == 0) {
        localCompares += 1;
        goodCompares += localCompares;
        inDict += 1;
        return t;
    }
    

    return t;
}


template<class T>
binaryNode<T> * binarySearchTree<T>::find_common_ancestor(binaryNode<T> *&t1, binaryNode<T> *t2) {
    if (t1 -> data == t2 -> data) { // if they're the same, they are the parent
        return t1;
    } 
    
    if (t2 -> nodeDepth > t1 -> nodeDepth) { // if at different depths, back up to same depth
        t2 = t2 -> parent;
    } else if (t2 -> nodeDepth < t1 -> nodeDepth) {
        t1 = t1 -> parent;
    } else {                                 // back it up
        t1 = t1 -> parent;
        t2 = t2 -> parent;
    }

    find_common_ancestor(t1, t2);

    return nullptr;
}


template<class T>
binaryNode<T> * binarySearchTree<T>::get_shallow_node() {
    shallowNode -> nodeDepth = 100;
    return get_shallow_node(root);
}


template<class T>
binaryNode<T> * binarySearchTree<T>::get_shallow_node(binaryNode<T> *t) {
    
    if (t != nullptr) {
        get_shallow_node(t -> left);
        if (t -> nodeDepth < shallowNode -> nodeDepth) {
            shallowNode = t;
        }
        get_shallow_node(t -> right);
    }
    
    return shallowNode;
}


template <class T>
void binarySearchTree<T>::clear() {
    binaryNode<T> * tmp;
    while(!is_empty()) {
        for (tmp = root; tmp != nullptr; tmp = tmp -> left) {
            if (tmp -> left == nullptr) {
                tmp = tmp -> right;
            }
        }

        delete tmp;
        size--;

    }
}


template<class T>
void binarySearchTree<T>::print_misspelled(fstream &file) {
    binaryNode<T> * tmp;
    for (tmp = misspelled; tmp != nullptr; tmp = tmp -> left) {
        file << tmp -> data << endl;
    }
}


template<class T>
void binarySearchTree<T>::insert_misspelled(T item) {
    if (misspelled == nullptr) {
        misspelled = new binaryNode<T>(item);
    } else {
        binaryNode<T> * tmp = new binaryNode<T>(item);
        tmp -> left = misspelled;
        misspelled = tmp;
    }
}


template <class T>
void binarySearchTree<T>::single_rotate_left(binaryNode<T> *t) {
    binaryNode<T> * toRotate = t -> right;
    t -> right = toRotate -> left;
    t = toRotate;
    toRotate -> parent = t -> parent;
    t -> parent = toRotate;

    toRotate -> nodeDepth -= 1;
    t -> nodeDepth += 1;
    change_node_depth(toRotate -> left, -1);
    change_node_depth(t -> right, 1);

}


template <class T>
void binarySearchTree<T>::single_rotate_right(binaryNode<T> *t) {
    binaryNode<T> * toRotate = t -> left;
    t -> left = toRotate -> right;
    t = toRotate;
    
    toRotate -> nodeDepth -= 1;
    t -> nodeDepth += 1;
    change_node_depth(toRotate -> left, -1);
    change_node_depth(t -> right, 1);

}


template <class T>
void binarySearchTree<T>::double_rotate_left(binaryNode<T> *t) {
    single_rotate_left(t -> right);
    single_rotate_left(t);

}


template <class T>
void binarySearchTree<T>::double_rotate_right(binaryNode<T> *t) {
    single_rotate_right(t -> left);
    single_rotate_right(t);

}


template<class T>
void binarySearchTree<T>::change_node_depth(binaryNode<T> *t, int change) {
    if (t != nullptr) {
        t -> nodeDepth += change;
        change_node_depth(t -> left, change);
        change_node_depth(t -> right, change);
    }

    return;
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

    binarySearchTree<string> tree;

    string in;
    while (dict >> in) {
        tree.insert(in);
    }

    time.Start();

    string check;
    while (book >> check) {
        tree.find(clean_word(check));
    }

    time.Stop();

    tree.print_misspelled(misspelled);

    cout << "dictionary size " << tree.get_size() << "\nDone checking and these are the results\n";
    cout << "finished in time: " << time.Time() << "\n";
    cout << "There are " << tree.get_in_dict(1) << " words found in the dictionary\n";
    cout << "\t" << tree.get_compares(1) << " compares. Average: " << (tree.get_compares(1) / tree.get_in_dict(1));
    cout << "\nThere are " << tree.get_in_dict(0) << " words NOT found in the dictionary\n";
    cout << "\t" << tree.get_compares(0) << " compares. Average: " << (tree.get_compares(0) / tree.get_in_dict(0));
    cout << "\nThere are " << tree.get_not_checked() << " words not checked.\n";

    dict.close();
    book.close();
    misspelled.close();

    return 0;
}