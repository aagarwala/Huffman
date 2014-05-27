//Anirudh Agarwala
#include <iostream>
#include <string.h>
#include "classes.h"
using namespace std;

Node::Node(int freq, int character, Node* r, Node* l, int charcopy)
{
  frequency = freq; //frequency
  x = character; //character
  right = r; //right node
  left = l; //left node
  x_copy = charcopy; //copy of character
}

MinHeap::MinHeap()
{
  heapSize=0;
  nodeheap = new Node*[257];
}

void MinHeap::Push(Node* leaf)
{
  int currentNode = ++heapSize;

  while(currentNode !=1 && (nodeheap[currentNode/2]->frequency >= leaf->frequency))
  {
    if(nodeheap[currentNode/2]->frequency == leaf->frequency)
    {
      if(nodeheap[currentNode/2]->x_copy < leaf->x_copy)
      {
        Node *temp = leaf;
        leaf = nodeheap[currentNode/2];
        nodeheap[currentNode/2] = temp;
        continue;
      }//if 
    }//if the frequency of the root node is greater
    nodeheap[currentNode] = nodeheap[currentNode/2];
    currentNode /= 2;
  }//bubble up

  nodeheap[currentNode] = leaf;
}//pushes character onto MinHeap

void MinHeap::Print()
{
  for(int i=1; i<heapSize+1; i++)
    cout << char(nodeheap[i]->x) << " " << nodeheap[i]->frequency << endl;
}

void MinHeap::Pop()
{
  Node* one;
  one = nodeheap[1];

  Node* lastNode = nodeheap[heapSize--]; 
  int currentNode=1;
  int child=2;
  while(child <= heapSize)
  {
    if(child < heapSize && (nodeheap[child]->frequency >= nodeheap[child+1]->frequency))
    {
      if(nodeheap[child]->frequency == nodeheap[child+1]->frequency)
      {
        if(nodeheap[child]->x_copy < nodeheap[child+1]->x_copy)
        {
          child--;
        }
      }//if same frequency check which has lower character

      child++;
    }//set child to smaller child of currentNode

    if(lastNode->frequency <= nodeheap[child]->frequency)
    {
      if(lastNode->frequency == nodeheap[child]->frequency)
      {
          if(nodeheap[child]->x_copy < lastNode->x_copy)
          {
            nodeheap[currentNode] = nodeheap[child];
            currentNode = child;
            child*=2;
            continue;
          }
      }//if same frequency check which has lower character
      break;
    } 
    nodeheap[currentNode] = nodeheap[child];
    currentNode = child;
    child *= 2;
  }//while
  nodeheap[currentNode] = lastNode;

  Node* two;
  two = nodeheap[1];
  
  lastNode = nodeheap[heapSize--];
  currentNode=1;
  child=2;
  while(child <= heapSize)
  {
    if(child < heapSize && (nodeheap[child]->frequency >= nodeheap[child+1]->frequency))
    {
      if(nodeheap[child]->frequency == nodeheap[child+1]->frequency)
      {
        if(nodeheap[child]->x_copy < nodeheap[child+1]->x_copy)
        {
          child--;
        }
      }//if same frequency check which has lower character
      child++;
    }//set child to smaller child of currentNode

    if(lastNode->frequency <= nodeheap[child]->frequency)
    {
      if(lastNode->frequency == nodeheap[child]->frequency)
      {
          if(nodeheap[child]->x_copy < lastNode->x_copy)
          {
            nodeheap[currentNode] = nodeheap[child];
            currentNode = child;
            child*=2;
            continue;
          }
      }//if same frequency check which has lower character
      break;
    }
    nodeheap[currentNode] = nodeheap[child];
    currentNode = child;
    child *= 2;
  }//while
  nodeheap[currentNode] = lastNode;

  Node* merge;
  if(one->x_copy < two-> x_copy)
  {
    merge = new Node(one->frequency + two->frequency, -1, one, two, one->x_copy);
  } 
  else
  {
    merge = new Node(one->frequency + two->frequency, -1, one, two, two->x_copy);
  }
  Push(merge);
}//pops leaf/Node from heap
