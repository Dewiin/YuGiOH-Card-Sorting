#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
*/
CardShop::CardShop(string input_file_name) 
{
  ifstream fin(input_file_name);
  if (fin.fail())
  {
    cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  string name, type, race, attribute;
  int level_rank, atk, def;

  string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items

void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor

CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line

void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

//@param: the index of the first card to be displayed
//@param: the index of the last card to be displayed
//@post: displays the names of all cards in the shop with startRange and endRange, 
//       inclusive, one per line

void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      cout << ", ";
    }
    else
    {
      cout << endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise

bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

/** 
  @param: template comparator parameter
  @param: key to compare
  @pre: determine descending or ascending order
  @return: the number of swaps performed by sorting algorithm
*/
template<typename Comparator>
int CardShop::bubbleSort(Comparator comp, string key)
{
  bool swapped = true;
  int pass = 1; //tracks each pass of sorting
  int count = 0; //tracks number of swaps
  Node<YGOCard*> *temp = nullptr; 
  Node<YGOCard*> *temp2 = nullptr;  
  while(swapped && (pass < getLength())){
    swapped = false;
    for(int i = 0; i < getLength() - pass; i++){
      temp = getPointerTo(i);
      temp2 = getPointerTo(i+1);

      if(key == "atk"){
        if(comp(temp2->getItem()->getAtk(), temp->getItem()->getAtk())){
          swap(i, i+1);
          swapped = true;
          count++;
        }
      }
      else if(key == "def"){
        if(comp(temp2->getItem()->getDef(), temp->getItem()->getDef())){
          swap(i, i+1);
          swapped = true; 
          count++;
        }
      }

    }
    pass++;
  }
  return count;
}

/** 
  @param: template comparator parameter
  @param: key to compare
  @pre: determine descending or ascending order
  @post: swaps cards based on key and order
  @return: the number of swaps performed by sorting algorithm
*/
template <typename Comparator>
int CardShop::insertionSort(Comparator comp, string key)
{
  int count = 0; //tracks number of swaps
  
  for(int unsorted = 1; unsorted < getLength(); unsorted++){
    int current = unsorted;
    if(key == "atk"){
      while((current > 0) && (comp(getPointerTo(current)->getItem()->getAtk(), getPointerTo(current-1)->getItem()->getAtk()))){ 
        swap(current, current-1);
        current--;
        count++;
      }
    }
    else if(key == "def"){
      while((current > 0) && (comp(getPointerTo(current)->getItem()->getDef(), getPointerTo(current-1)->getItem()->getDef()))){
        swap(current, current-1);
        current--;
        count++;
      }
    }
  }
  return count;
}

/** 
  @param: template comparator parameter
  @param: key to compare
  @pre: determine descending or ascending order
  @return: the number of swaps performed by sorting algorithm
*/
template<typename Comparator>
int CardShop::quickSort(Comparator comp, string key)
{
  int swap_count = 0;
  int first = 0;
  int last = getLength()-1;
  quickSortHelper(comp, key, first, last, swap_count);

  return swap_count;
}

/**
  Helper function to call recursion of partition
  @param: Comparator for comparison
  @param first index 
  @param last index
  @return int number of swaps
*/
template <typename Comparator>
void CardShop::quickSortHelper(Comparator comp, string key, int first, int last, int& count)
{
  if(first < last){
    int pivot_index = partition(comp, key, first, last, count);
    quickSortHelper(comp, key, first, pivot_index - 1, count);
    quickSortHelper(comp, key, pivot_index + 1, last, count);
  }
}

/** 
  Helper function to create pivot and compare subarrays
  @param first index of partition
  @param last index of partition
  @return int index of pivot
*/
template<typename Comparator>
int CardShop::partition(Comparator comp, string key, int first, int last, int& count)
{
  YGOCard* pivot = getItem(last); //pivot value for comparison
  int index_count = first - 1;

  for(int i = first; i < last; i++){
    if(key == "atk"){
      if(comp(getItem(i)->getAtk(), pivot->getAtk())){
        index_count++; //increment an index
        swap(index_count, i); 
        count++;
      }
    }
    else if(key == "def"){
      if(comp(getItem(i)->getDef(), pivot->getDef())){
        index_count++; //increment an index
        swap(index_count, i);
        count++;
      }
    } 
  }
  swap(index_count+1, last); //swapping for pivot index
  count++; //INCREMENT!!

  return index_count+1;
}

/** 
  @param: template comparator parameter
  @param: key to compare
  @pre: determine descending or ascending order
  @return: the number of swaps performed by sorting algorithm
*/
template<typename Comparator>
int CardShop::mergeSort(Comparator comp, string key)
{
  int count = 0; //number of merges

  //base case
  if(getLength() <= 1){
    return count;
  }

  CardShop *shopLeft = new CardShop(); //CardShop to hold left side values
  CardShop *shopRight = new CardShop(); //CardShop to hold right side values

  /*
    splits the list into half, and adds left half of YGOCards 
    into left shop and right half of YGOCards into right shop
  */
  for(int i = 0; i < getLength(); i++){
    YGOCard *temp = new YGOCard(getItem(i)->getName(),getItem(i)->getType(),getItem(i)->getLevel(),getItem(i)->getRace(),getItem(i)->getAttribute(),getItem(i)->getAtk(),getItem(i)->getDef());
    if(i < getLength()/2){
      shopLeft->insert(i, temp);
    }
    else{
      shopRight->insert(shopRight->getLength(), temp);
    }
  }

  //recursion
  shopLeft->mergeSort(comp, key);
  shopRight->mergeSort(comp, key);


  /*******************************
    MERGING the two sorted lists
  ********************************/

  //indices for both halves, and def is the index for the default sorted list
  int left_side_index = 0, index = 0, right_side_index = 0;

  while((left_side_index < (shopLeft->getLength())) && right_side_index < (shopRight->getLength())){
    if(key == "atk"){
      if(comp(shopLeft->getItem(left_side_index)->getAtk(), shopRight->getItem(right_side_index)->getAtk())){
        getPointerTo(index++)->setItem(shopLeft->getItem(left_side_index++)); //merge
      }
      else{
        getPointerTo(index++)->setItem(shopRight->getItem(right_side_index++)); //merge
      }
      count++;
    }
    else if(key == "def"){
      if(comp(shopLeft->getItem(left_side_index)->getDef(), shopRight->getItem(right_side_index)->getDef())){
        getPointerTo(index++)->setItem(shopLeft->getItem(left_side_index++)); //merge
      }
      else{
        getPointerTo(index++)->setItem(shopRight->getItem(right_side_index++)); //merge
      }
      count++;
    }
  }
  
  /********* MERGING REMAINING ELEMENTS FROM UNEVEN HALVES *********/
  
  //from left shop
  while(left_side_index < (shopLeft->getLength())){
    getPointerTo(index++)->setItem(shopLeft->getItem(left_side_index++)); //merge
  }
  //from right shop
  while(right_side_index < (shopRight->getLength())){
    getPointerTo(index++)->setItem(shopRight->getItem(right_side_index++)); //merge
  }

  return count; //return
}