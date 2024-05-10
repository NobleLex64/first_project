
/* STL libraries  */

#include "haffman.h"
#include "myalgoritm.h"

/* 
  1) Node constructors. <(13, 15, 17)>

  2) Compare for priority_queue, less at the top. <(19)>
*/

haff::hlp::Node::Node(wchar_t value, double freaq): Node(value, freaq, nullptr, nullptr) {}

haff::hlp::Node::Node(double freaq, Node *left, Node *right): Node(L'\0', freaq, left, right) {}

haff::hlp::Node::Node(wchar_t value, double freaq, Node *left, Node *right): value(value), freaq(freaq), left(left), right(right) {}

bool haff::hlp::Compare::operator()(const Node *a, const Node *b){
    return a->freaq > b->freaq;
}

/*
  1) getHaffTreeHead(priority_queue<Node*> &nodes) -> function merge nodes in 'nodes' 
     and returns the root of the resulting tree. Speed: O(N), Memmory: O(1), where N - size 'nodes'

  2) getHaffTable(..., unordered_map<wchar_t, wstring> &result, ...) -> recursively traverses the tree,
     if to the left then 0 if to the right then 1.  Speed: O(N), Memmory: O(log(N)), where N - number of nodes in the tree
    
  3) sizeHaffTable(..., const unordered_map<wchar_t, wstring> &haff_table) ->
     return size of every .second element. Speed: O(N), Memmory: O(1), where N - size of the unordered_map
*/

haff::hlp::Node* haff::hlp::getHaffTreeHead(auto &nodes){

  Node *node1 = nullptr;
  Node *node2 = nullptr;

  while(nodes.size() > 1){
    node1 = nodes.top();
    nodes.pop();
    node2 = nodes.top();
    nodes.pop();
    nodes.emplace(new Node((node2->freaq + node1->freaq), node1, node2));
  }

  return nodes.top();
}

void haff::hlp::getHaffTable(Node *head, auto &result, std::wstring val){
  if(!head)
    return;
  
  if(head->value != L'\0')
    result[head->value] = val;

  getHaffTable(head->left,  result, val + L'0');
  getHaffTable(head->right, result, val + L'1');
}

size_t haff::hlp::sizeHaffTable(std::wstring_view data, auto &haff_table)
{
  size_t size = 0;
  for(auto it = data.cbegin(), end = data.cend(); it < end; ++it)
    size += haff_table[*it].size();

  return size;
}

/*
  1) compression(...) -> return compressed data
    Speed: O(8 * N), Memmory: O(8 * N), where N - data.size()
  
  2) decompression(...) -> return original data, before compresion
     Speed: O(N*M*k), Memmory: O(M * k) , where N - shifr.size(), M - alphabet, k - code size
*/

std::wstring haff::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  /* 
    The part where we work with the Haffman tree.

    1) 'Node' -> point top of the Haffman tree
    2) 'nodes' -> Haffman tree nodes 
    3) created nodes and add it in 'nodes' ()
    4) getHaffTreeHead -> merge nodes in 'nodes' and return top (
    5) 'haff_table' -> tree in hash
    6) getHaffmanTable -> filling 'haff_table' first-> characters value{a},{b} etc., second-> byte code {10101}, {001}, etc.
    )
  */

  hlp::Node *head = nullptr;
  { 
    std::priority_queue<hlp::Node*, std::vector<hlp::Node*>, hlp::Compare> nodes;
    {
      std::unordered_map<wchar_t, size_t> frequency_table;

      for(auto it = data.cbegin(), end = data.cend(); it < end; ++it)
        ++frequency_table[*it];

      size_t size = data.size();
      for(auto it = frequency_table.cbegin(), end = frequency_table.cend(); it != end; ++it)
        nodes.emplace(new hlp::Node(it->first, (it->second / static_cast<double>(size))));
    }
    head = hlp::getHaffTreeHead(nodes);
  }

  std::unordered_map<wchar_t, std::wstring> haff_table;
  hlp::getHaffTable(head, haff_table, L"");

  /* 
    The part where we work with the shifr.
    
    1) reserve memmory for shifr and pre_shifr ()
      {
        sizeHaffTable -> return SUM(second.size())
      }
    2) filling pre_shifr ()
    3) Add size of haff_table, to separate the cipher itself from the metadata ()
    4) Add the Huffman table itself ()
      { 
        add -> (byte code -> int16_t num) OR (1 to the most significant bit of this number to identify it during decoding) 
        add -> the meaning of the symbol
      }
    5) compress the prepared string 'pre_shifr' 8 times ()
    6) return result ()
  */

  std::wstring shifr;
  std::wstring pre_shifr;

  pre_shifr.reserve(hlp::sizeHaffTable(data, haff_table));

  for(auto it = data.cbegin(), end = data.cend(); it < end; ++it)
    pre_shifr.append(haff_table[*it]);
  
  shifr.reserve(pre_shifr.size() / 8 + haff_table.size() * 2);

  shifr.push_back(static_cast<wchar_t>(haff_table.size()));

  for(auto it = haff_table.cbegin(), end = haff_table.cend(); it != end; ++it){
    shifr.push_back(static_cast<wchar_t>(alg::getOneBySize((*it).second) | (1 << (*it).second.size())));
    shifr.push_back((*it).first);
  }

  alg::eightXcompression(pre_shifr, shifr);

  return shifr;
}

std::wstring haff::decompression(std::wstring_view shifr){

  if(shifr.empty())
    return std::wstring();

  std::wstring data;
  std::unordered_map<std::wstring, wchar_t> haff_table;

  auto it = shifr.begin() + 1;

  for(auto end = it + *(it - 1) * 2; it < end; it += 2)
  {
    std::pair<uint8_t, wchar_t> size_value = alg::getSizeAndValue(*it);
    haff_table[alg::getByteByBit(size_value.second, size_value.first)] = *(it + 1);
  }

  std::wstring cur_str;
  for(auto end = shifr.end(); it < end; ++it)
  {
    cur_str += alg::getByteByBit(*it, 8);

    for(auto start = haff_table.cbegin(); start != haff_table.cend();)
    {
      if(*cur_str.begin() == *(*start).first.cbegin() && cur_str.substr(0,(*start).first.size()) == (*start).first)
      {
        data.push_back((*start).second);

        cur_str.erase(0, (*start).first.size());
       
        if(!cur_str.empty())
          start = haff_table.begin();
        else 
          break;
      }
      else
        ++start;
    }
  }

  return data;
}
 