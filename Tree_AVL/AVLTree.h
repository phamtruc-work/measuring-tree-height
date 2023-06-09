#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;

template <typename T>
class Node{
    public:
        T key;
        int height;
        Node<T> * left;
        Node<T> * right;
        explicit Node(T);
};

template <typename T>
class AVLTree{
    public:
        Node<T> * root = NULL;
        int numNodes;
        void insert(T);
        int maxDepth();
    private:
        int height(Node<T> *&);
        Node<T> * rightRotation(Node<T> *&);
        Node<T> * leftRotation(Node<T> *&);
        Node<T> * insertUtil(Node<T> *&, T );
        int maxDepthUtil(Node<T> *&);
};

template <typename T>
Node<T>::Node(T data){
    height = 1;
    key = data;
    left = NULL;
    right = NULL;
}

template <typename T>
void AVLTree<T>::insert(T x){
    root=insertUtil(root, x);
}

template <typename T>
int AVLTree<T>::maxDepth(){
    return maxDepthUtil(root);
}

template <typename T>
int AVLTree<T>::height(Node<T> *& head){
    if(head==NULL) return 0;
    return head->height;
}

template <typename T>
Node<T> * AVLTree<T>::rightRotation(Node<T> *& head){
    Node<T> * newhead = head->left;
    head->left = newhead->right;
    newhead->right = head;
    head->height = 1+max(height(head->left), height(head->right));
    newhead->height = 1+max(height(newhead->left), height(newhead->right));
    return newhead;
}

template <typename T>
Node<T> * AVLTree<T>::leftRotation(Node<T> *& head){
    Node<T> * newhead = head->right;
    head->right = newhead->left;
    newhead->left = head;
    head->height = 1+max(height(head->left), height(head->right));
    newhead->height = 1+max(height(newhead->left), height(newhead->right));
    return newhead;
}

template <typename T>
Node<T> * AVLTree<T>::insertUtil(Node<T> *& head, T x){
    if(head==NULL){
        numNodes+=1;
        Node<T> * temp = new Node<T>(x);
        return temp;
    }

    if (x < head->key) 
        head->left = insertUtil(head->left, x);
    else if(x > head->key) 
        head->right = insertUtil(head->right, x);

    head->height = 1 + max(height(head->left), height(head->right));

    int balanceFactor = height(head->left) - height(head->right);
    if (balanceFactor > 1){
        if(x < head->left->key){
            return rightRotation(head);
        }else{
            head->left = leftRotation(head->left);
            return rightRotation(head);
        }
    } else if(balanceFactor < -1){
        if(x > head->right->key){
            return leftRotation(head);
        }else{
            head->right = rightRotation(head->right);
            return leftRotation(head);
        }
    }
    return head;
}

template <typename T>
int AVLTree<T>::maxDepthUtil(Node<T> *& node){
    if (node == NULL)
        return 0;
    else {
        /* compute the depth of each subtree */
        int lDepth = maxDepthUtil(node->left);
        int rDepth = maxDepthUtil(node->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

#endif //AVLTREE_H