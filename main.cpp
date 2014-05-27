//Anirudh Agarwala
#include <iostream>
#include <string>
#include <stdio.h>
#include "classes.h"
using namespace std;

string codes[256]; //string to hold codes of characters
string compressed_bits; //string of compressed data
bool bits[8]; //boolean that stores 8 bits
void traverse(string output, Node* node); //function that traverses the huffman tree
void traverse2(string input, Node* node); //function that converts compressed data to decompressed
void bits2bytes(bool bits[8]);
void bytes2bits(unsigned char value, bool bits[8]);

int main(int argc, char* argv[])
{
  unsigned int freq[256];
  for(int i=0; i < 256; i++)
    freq[i]=0;
  // char c;
  char c;
  string output;

  if(argc==2)
  {
    char decomp[4];
    cin.read(decomp, sizeof(unsigned int));
    cin.read(decomp, sizeof(unsigned int));

    for(int i=0; i<256; i++)
    {
      cin.read(decomp, sizeof(unsigned int));
      unsigned int x = *(int*)decomp;                 
      freq[i] = x;
    }//reads in input

    /*for(int i=0; i<256; i++)
      if(freq[i]!=0)
        cout << (char)i << " " << freq[i] << endl;
    */
    
    Node* node; //initial node
    MinHeap minheap; //minheap

    for(int i=0; i<256; i++)
    {
      if(freq[i]!=0)
      {
        node = new Node(freq[i], i, NULL, NULL, i);
        //cout << freq[i] << " " << i << endl; 
        minheap.Push(node); 
      }//if frequency is not 0
    }//pushes all the characters onto the minheap intially

    while(minheap.heapSize!=1)
    {
       minheap.Pop();
    }//Pops two smallest nodes/leafs and merges them, then pushes merged node onto heap again
    //Basically builds huffman tree  
    
    while(cin.get(c))
    {
      bytes2bits((unsigned char)c, bits);
    }
   
    traverse2(compressed_bits, minheap.nodeheap[1]);
    return 0;
  }

  while(cin.get(c))
  {
    freq[(unsigned char)c]++;
  }//gets input

  Node* node; //initial node
  MinHeap minheap; //minheap

  for(int i=0; i<256; i++)
  {
    if(freq[i]!=0)
    {
      node = new Node(freq[i], i, NULL, NULL, i);
      //cout << freq[i] << " " << i << endl; 
      minheap.Push(node); 
    }//if frequency is not 0
  }//pushes all the characters onto the minheap intially

  //minheap.Print(); //prints minheap

  while(minheap.heapSize!=1)
  {
    minheap.Pop();
  }//Pops two smallest nodes/leafs and merges them, then pushes merged node onto heap again
   //Basically builds huffman tree
   
  //cout << endl;
  traverse(output, minheap.nodeheap[1]);   

  /*
  for(int i=0; i < 256; i++)
    if(freq[i]!=0)
      cout << codes[i] << endl;
  */
  string input; //input to be compressed
  cin.clear();
  string input_bits;
  cin.seekg(0, ios::beg);
 
  while(cin.get(c)) {
    input_bits += codes[(unsigned char)c];
  }
   
  cout << "HUFFMA3" << '\0';
  for(unsigned int i=0; i < 256; i++)
  {
    unsigned char byte0, byte1, byte2, byte3;
    if(freq[i]==0)
      cout.write((const char*)&freq[i], sizeof(freq[i]));
    else
    {
      byte0 = (unsigned char)(freq[i]);
      byte1 = (unsigned char)(freq[i] >> 8);
      byte2 = (unsigned char)(freq[i] >> 16);
      byte3 = (unsigned char)(freq[i] >> 24);
      cout.write((const char*)&byte0, sizeof(byte0));
      cout.write((const char*)&byte1, sizeof(byte1));
      cout.write((const char*)&byte2, sizeof(byte2));
      cout.write((const char*)&byte3, sizeof(byte3)); 
    }
    //cout << i << endl;
  }//prints frequencies as little endian

  while((input_bits.length())%8 != 0)
  {
    input_bits += '0';
  }//pads on 0's so compressed data is a multiple of 8
 
  for(unsigned int i=0; i < input_bits.length(); i++)
  {
    if((i != 0) && (i%8 == 0))
      bits2bytes(bits);
    if(input_bits[i] == '0')
      bits[i%8] = false;
    else
      bits[i%8] = true;
    if(i == (input_bits.length()-1))
      bits2bytes(bits);
  }//converts bits to bytes

  return 0;

}//main

void traverse(string output, Node* node)
{
  if(node->x != -1)
  {
    codes[node->x] = output;
    //cout << char(node->x) << " " << codes[node->x] << endl;
  }
  else
  {
    string left, right;
    left = output + '0';
    traverse(left, node->left);
    right = output + '1';
    traverse(right, node->right);
  }//traverses to the bottom of the tree
}//traverses huffman tree


void traverse2(string input, Node* node)
{
  int counter=0; //compare to the total frequency, stop when you hit it
  int frequency = node->frequency; //node will keep changing so this is the only time it is the root
  Node* resetnode = node;
  for(unsigned int i=0; i < input.length(); i++)
  {
    if(input[i]=='0')
    {
      node = node->left;
      if(node->x != -1)
      {
        cout << (char)node->x;
        node = resetnode;
        counter++;
      }
    }//if character is 0

    else
    {
      node = node->right;
      if(node->x != -1)
      {
        cout << (char)node->x;
        node = resetnode;
        counter++;
      }
    }//if character is 1
    if(counter==frequency)
      break;
  }//iterates through string
}//traverses compressed_input and outputs as uncompressed data

void bits2bytes(bool bits[8])
{
  unsigned char base = 1, sum = 0;
  for(int i = 0; i < 8; i++)
  {
    sum += bits[i]*base;
    base *= 2;
  }
  //cout << "boo!" << endl;
  cout << sum; //prints out byte character
}//converts bits to bytes

void bytes2bits(unsigned char value, bool bits[8])
{
  for(int i = 0; i < 8; i++)
  {
    bits[i] = value%2;
    value /=2;
  }//for
  for(int i =0; i < 8; i++)
  {
    if(bits[i]==false)
      compressed_bits += '0';
    else
      compressed_bits += '1';
  }//converts boolean to string
}//converts bytes to bits
