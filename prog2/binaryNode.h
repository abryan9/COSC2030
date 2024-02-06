#ifndef BINARYNODE_
#define BINARYNODE_

template <class T>
    class binaryNode {
        public:
            T data;
            int nodeDepth; // tracks depth of each individual node
            binaryNode<T> * left;
            binaryNode<T> * right;
            binaryNode<T> * parent; // Allows backwards traversal from leaf to root

            binaryNode(T d) : data (d), left (nullptr), right (nullptr), parent (nullptr) {}
    };
#endif