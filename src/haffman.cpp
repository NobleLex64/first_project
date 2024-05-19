#include "haffman.h"

/* STL libraries  */
#include <string>
#include <unordered_map>
#include <queue>

/* My libraries */
#include "myalgoritm.h"

/* 
  1) Node constructors. <(13, 15, 17)>

  2) Compare for priority_queue, less at the top. <(19)>
*/

haff::helper::Node::Node(wchar_t value, double freaq): Node(value, freaq, nullptr, nullptr) {}

haff::helper::Node::Node(double freaq, Node *left, Node *right): Node(L'\0', freaq, left, right) {}

haff::helper::Node::Node(wchar_t value, double freaq, Node *left, Node *right): value(value), freaq(freaq), left(left), right(right) {}

bool haff::helper::Compare::operator()(const Node *a, const Node *b){
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

haff::helper::Node* haff::helper::getHaffTreeHead(auto &nodes){

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

void haff::helper::getHaffTable(Node *head, auto &result, std::wstring val){
  if(!head)
    return;
  
  if(head->value != L'\0')
    result[head->value] = val;

  getHaffTable(head->left,  result, val + L'0');
  getHaffTable(head->right, result, val + L'1');
}

size_t haff::helper::sizeHaffTable(std::wstring_view data, auto &haff_table)
{
  size_t size = 0;
  for(auto it = data.cbegin(), end = data.cend(); it < end; ++it)
    size += haff_table[*it].size();

  return size;
}

/*
  1) compression(...) -> return compressed data
    Speed: O(N), Memmory: O(N), where N - data.size()
  
  2) decompression(...) -> return original data, before compresion
     Speed: O(N*M*k), Memmory: O(M * k) , where N - shifr.size(), M - alphabet, k - code size
*/

std::wstring haff::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  helper::Node *head = nullptr;
  { 
    std::priority_queue<helper::Node*, std::vector<helper::Node*>, helper::Compare> nodes;
    {
      std::unordered_map<wchar_t, size_t> frequency_table;

      for(auto it = data.cbegin(), end = data.cend(); it < end; ++it)
        ++frequency_table[*it];

      size_t size = data.size();
      for(auto it = frequency_table.cbegin(), end = frequency_table.cend(); it != end; ++it)
        nodes.emplace(new helper::Node(it->first, (it->second / static_cast<double>(size))));
    }
    head = helper::getHaffTreeHead(nodes);
  }

  std::unordered_map<wchar_t, std::wstring> haff_table;
  helper::getHaffTable(head, haff_table, L"");

  std::wstring shifr;
  std::wstring pre_shifr;

  size_t size = helper::sizeHaffTable(data, haff_table);
  pre_shifr.reserve(32);
  shifr.reserve(size / 8 + haff_table.size() * 2 + 1);

  shifr.push_back(static_cast<wchar_t>(haff_table.size()));

  for(auto it = haff_table.cbegin(), end = haff_table.cend(); it != end; ++it){
    shifr.push_back(static_cast<wchar_t>(alg::getOneBySize((*it).second) | (1 << (*it).second.size())));
    shifr.push_back((*it).first);
  }

  for(auto it = data.cbegin(), end = data.cend(); it < end; ++it)
  {
    pre_shifr.append(haff_table[*it]);

    while(pre_shifr.size() > 8)
    {
      shifr.push_back(alg::getOneBySize(pre_shifr.substr(0, 8)));
      pre_shifr.erase(0, 8);
    }

    if(it == end - 1 && !pre_shifr.empty())
    {
      shifr.push_back(static_cast<wchar_t>(pre_shifr.size()));
      shifr.push_back(alg::getOneBySize(pre_shifr));
      break;
    }
  }

  //alg::eightXcompression(pre_shifr, shifr);

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
  for(auto end = shifr.end(); it < end - 1; ++it)
  {
    if(it == end - 2)
      cur_str += alg::getByteByBit(*(it + 1), *it);
    else
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
 