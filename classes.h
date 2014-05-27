//Anirudh Agarwala
#ifndef classes
  #define classes

class Node
{
  public:
  int frequency;
  int x;
  Node* right;
  Node* left;
  int x_copy;

  Node(int freq, int character, Node* r, Node* l, int charcopy);
};

class MinHeap
{

  public:
  Node** nodeheap;
  int heapSize;

  MinHeap();
  void Push(Node* node);
  void Pop();
  void Print();

};
#endif
