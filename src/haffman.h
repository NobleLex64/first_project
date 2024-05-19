#ifndef PROJECT02_SRC_HAFFMAN_H_
#define PROJECT02_SRC_HAFFMAN_H_ 1

/// produced.. Noble_lex 64, 05.2024
/// algoritm Haffmana (compression and decompression)
/// used my libs "myAlg.h"

/* STL libraries  */
#include <string>
#include <unordered_map>
#include <queue>

/* My libraries */
#include "myalgoritm.h"

namespace haff{

namespace helper{

/// @brief needs for the haffman tree
struct Node{

wchar_t value;
double  freaq;
Node *left;
Node *right;

/// @brief constructor
/// @param value charters
/// @param freaq frequency of charcters in data
Node(wchar_t value, double freaq);

/// @brief constructor
/// @param freaq frequency of charcters in data
/// @param left  left child
/// @param right right child
Node(double freaq, Node *left, Node *right);

/// @brief constructor
/// @param value charters
/// @param freaq frequency of charcters in data
/// @param left  left child
/// @param right right child
Node(wchar_t value, double freaq, Node *left, Node *right);
};

/// @brief needs for the queue nodes
struct Compare{

/// @brief need for priority_queue
/// @param a first param
/// @param b second param
/// @return a.frequency > b.frequency
bool operator()(const Node *a, const Node *b);
};

/// @brief       return the head of tree, what comes from the queue of nodes
/// @param nodes queue of nodes
/// @return      root of the tree
Node* getHaffTreeHead(auto &nodes);

/// @brief create haffman table, used haffman tree
/// @param head the haffman tree top
/// @param result haffman table
/// @param val variables where storage left -> +'0' or right-> +'1'
void getHaffTable(Node* head, auto &result, std::wstring val);

/// @brief count Sum of len(.second) by characters in data
/// @param data data
/// @param haff_table haffman table
/// @return Sum haffman_table[data[i]].second.size()
size_t sizeHaffTable(std::wstring_view data, const auto &haff_table);

}// helper

/// @brief haffman algoritm for compression 
/// @param data data before compression
/// @return data after compression
std::wstring compression(std::wstring_view data);

/// @brief haffman algoritm for decompression 
/// @param shifr data after compression
/// @return data before compression
std::wstring decompression(std::wstring_view shifr);

}//haff

#endif //PROJECT02_SRC_HAFFMAN_H_