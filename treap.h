#ifndef NOBLELEX64_CARTESIAN_TREE
#define NOBLELEX64_CARTESIAN_TREE

#include <random>

namespace trh{

  namespace hlp{

  }

  /// @brief Cartesian tree
  class Treap{
  private:
    
    /// @brief is a treap node
    struct Node{

      // key, part of binary tree
      int _x;

      // priority, part of heap
      int _y;
      
      // pointer on the left child
      Node *_left;

      // pointer on the right child
      Node *_right;

      /// @brief default constructor, key = 0
      Node();

      /// @brief constructor
      /// @param x key 
      Node(int key);

      /// @brief constructor
      /// @param x key
      /// @param left left child
      /// @param right right child
      Node(int key, Node *left, Node *right);
    } *_root;

    static Node* merge(Node *a, Node *b);
    static void split(Node *n, int key, Node *&a, Node *&b);
    static void deleteBranch(Node *n);

  public:

    /// @brief default constructor
    Treap();

    /// @brief insert node in tree whith x = key
    /// @param key value x
    void insert(int key);

    /// @brief search node with x = key
    /// @param key value x
    /// @return true if there is key in tree
    bool contains(int key);

    /// @brief delete nodes with x = key
    /// @param key value x
    void erase(int key);
    
    /// @brief default destructor
    ~Treap();
  };
  
}
#endif // NOBLELEX64_CARTESIAN_TREE