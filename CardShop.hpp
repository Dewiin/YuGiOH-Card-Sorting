#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

class CardShop : public DoublyLinkedList<YGOCard*>
{
public:
  CardShop() = default; //default constructor
  ~CardShop();          //destructor calls clear

  /**
    @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
    @param: the name of the input file
    @post:  Reads the input file and adds pointers to YGOCard objects 
            instantiated with the information read from the file. 
  */
  CardShop(string input_file_name); //parameterized constructor

  /** 
    @post: displays information of all cards in the shop, one per line
  */
  void display();

  /** 
    @param: the index of the first card to be displayed
    @param: the index of the last card to be displayed
    @post: displays the names of all cards in the shop with startRange and endRange, inclusive, one per line
  */
  void displayName(int startRange, int endRange);

  /**
    @post: removes all cards from the shop
  */
  void clear();                               

  /** 
    @return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
  */
  bool operator==(const CardShop &rhs) const; 

  /** 
    @param: template comparator parameter
    @param: key to compare
    @pre: determine descending or ascending order
    @post: swaps cards based on key and order
    @return: the number of swaps performed by sorting algorithm
  */
  template <typename Comparator>
  int bubbleSort(Comparator comp, string key);

  /** 
    @param: template comparator parameter
    @param: key to compare
    @pre: determine descending or ascending order
    @post: swaps cards based on key and order
    @return: the number of swaps performed by sorting algorithm
  */
  template <typename Comparator>
  int insertionSort(Comparator comp, string key);  

  /** 
    @param: template comparator parameter
    @param: key to compare
    @pre: determine descending or ascending order
    @post: swaps cards based on key and order
    @return: the number of swaps performed by sorting algorithm
  */
  template <typename Comparator>
  int quickSort(Comparator comp, string key);

  /** 
    @param first index of partition
    @param last index of partition
    @post: compares and swaps elements
    @return int index of pivot
  */
  template<typename Comparator>
  int partition(Comparator comp, string key, int first, int last, int& count);

  /**
    Helper function to sort sub linked lists
  */
  template <typename Comparator>
  void quickSortHelper(Comparator comp, string key, int first, int last, int& count);

  /** 
    @param: template comparator parameter
    @param: key to compare
    @pre: determine descending or ascending order
    @post: swaps cards based on key and order
    @return: the number of swaps performed by sorting algorithm
  */
  template <typename Comparator>
  int mergeSort(Comparator comp, string key);

};


#endif