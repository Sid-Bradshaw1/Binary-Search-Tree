#ifndef BINARYSEARCHTREE_BSTDERIVED_H
#define BINARYSEARCHTREE_BSTDERIVED_H
#include "bstInterface.h"
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include "Queue.h"
#include "Deque.h"

using namespace std;
template<typename T>

class BST : public BSTInterface<T>
{
private:
    typedef struct Node
            {
                T data;
                Node* left;
                Node* right;
                Node(T d) : data(d), left(NULL), right(NULL) {};
                ~Node() = default;

                friend ostream& operator<<(ostream& os, const struct Node& node)
                    {
                        os << node.data;
                        return os;
                    }
            };
    int sizeVar = 0;
    Node* root;




public:
    BST() { this->root = NULL; }
    ~BST() { clearTree(); }

    bool RecFind(Node*& node, const T& value)
    {
        if (node == NULL)
        {
            return false;
        }

        else if (value == node->data)
        {
            return true;
        }


        else if (value < node->data)
        {
            return RecFind(node->left, value);
        }

        else if (value > node->data)
        {
            return RecFind(node->right, value);
        }
    }

    bool RecInsert(Node*& node, const T& value)
    {
        if (node == NULL)
        {
            node = new Node(value);
            sizeVar++;
            return true;
        }

        else if (value == node->data)
        {
            return false;
        }

        else if (value < node->data)
        {
            return RecInsert(node->left, value);
        }

        else if (value > node->data)
        {
            return RecInsert(node->right, value);
        }



    }

    /** Return true if node added to BST, else false */
    bool addNode(const T& value)
    {
        if (!RecFind(root, value))
        {
            return RecInsert(root, value);

        }

        else
        {
            return false;
        }


    }

    bool RecRemove(Node*& node, const T& value)
    {
        if (node == NULL) return false;
        if (value < node->data) return RecRemove(node->left, value);
        if (value > node->data) return RecRemove(node->right, value);

        // We found it!!!!!
        Node* oldNode = node;
        if (node->left == NULL) node = node->right;		// 1) only right (1 child or no child)
        else if (node->right == NULL) node = node->left;	// 2) only left

            // The node we want to delete has 2 children
        else
        {
            Node* predecessor = node->left;				// 3) 2 children
            while (predecessor->right != NULL) predecessor = predecessor->right;
            swap(node->data, predecessor->data);
            RecRemove(node->left, value);
            return true;
        }
        delete oldNode;
        sizeVar--;
        return true;
    }

    /** Return true if node removed from BST, else false */
    bool removeNode(const T& value)
    {
        RecRemove(root, value);

    }

    bool clear(Node*& node)
    {
        if (node != NULL)
        {
            clear(node->left);
            clear(node->right);
            delete node;
            sizeVar = 0;
        }

    }

    /** Return true if BST cleared of all nodes, else false */
    bool clearTree()
    {
        clear(root);
        root = NULL;

    }

    /** Return a level order traversal of a BST as a string */


    int GetTreeSize()
    {
        return sizeVar;
    }

    bool FinderFunc(const T& value)
    {
        if (RecFind(root, value))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void levelOrder()
    {
        if (root == NULL)  return;		// base Case
        Queue<Node*> q;					// create queue for level order traversal
        q.push(root);					// enque root (start)

        while (q.empty() == false)
        {

            Node* node = q.front();		// visit node
            q.pop();
            cout << " " << node->data;
            if (node->left != NULL)	q.push(node->left);
            if (node->right != NULL) q.push(node->right);
        }
        return;
    }

    bool outLevel(Node* node, int level, stringstream& out) const
    {
        if (node == NULL) return false;
        if (level == 1)
        {
            out << " " << node->data;
            if ((node->left != NULL) || (node->right != NULL)) return true;
            return false;
        }
        if ((level == 2) && !node->left && node->right) out << " _";
        bool left = outLevel(node->left, level - 1, out);
        bool right = outLevel(node->right, level - 1, out);
        if ((level == 2) && node->left && !node->right) out << " _";
        return left || right;
    } // end outLevel()

    string toString() const
    {
        stringstream out;
        if (root == NULL)
        {
            out << " empty";
        }
        else
        {
            int level = 0;
            do
            {
                out << endl << "  " << ++level << ":";
            } while (outLevel(root, level, out));
        }
        return out.str();
    }

    friend ostream& operator<< (ostream& os, BST<T>& bst)
    {
        os << bst.toString();
        return os;
    }




};

#endif //BINARYSEARCHTREE_BSTDERIVED_H
