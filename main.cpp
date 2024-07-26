/*
Name: Devin Xie
Main testing file for Project 5
*/

#include "CardShop.cpp"

int main(){
    /*
    YGOCard card1("1", "Normal Monster", 10, "Beast", "Dark", 1000, 1000);
    YGOCard card2("2", "Normal Monster", 10, "Beast", "Dark", 2000, 1000);
    YGOCard card3("3", "Normal Monster", 10, "Beast", "Dark", 2200, 1000);
    YGOCard card4("4", "Normal Monster", 10, "Beast", "Dark", 500, 1000);
    YGOCard card5("5", "Normal Monster", 10, "Beast", "Dark", 100, 1000);
    YGOCard card6("6", "Normal Monster", 10, "Beast", "Dark", 3500, 1000);
    */

    /*
    DoublyLinkedList<int> *linked1 = new DoublyLinkedList<int>();
    linked1->insert(0, 1);
    linked1->insert(1, 2);
    linked1->insert(2, 3);
    linked1->insert(3, 4);
    linked1->insert(4, 5);
    linked1->insert(5, 6);
    
    linked1->display(); //display
    linked1->swap(0, 1); //swap
    linked1->display(); //display
    linked1->swap(1, 2); //swap
    linked1->display(); //display
    linked1->swap(2, 3); //swap
    linked1->display(); //display
    */

    //CardShop *shop1 = new CardShop("cards.csv");
    CardShop *shop1 = new CardShop("cards.csv");
    //YGOCard *card1 = new YGOCard("Dragon", "Beast", 10, "Human", "Light", 10000, 10000);
    //YGOCard *card2 = new YGOCard("Goku", "God", 10, "Human", "Fire", 20000, 20000);


    //shop1 -> insert(shop1->getLength(), card1);
    //shop1 -> insert(shop1->getLength(), card2);

    //shop1 -> mergeSort(less<int>{}, "atk");
    //shop1 -> bubbleSort(less<int>{}, "atk");
    //shop1 -> insertionSort(less<int>{}, "atk");
    cout << shop1 -> mergeSort(less<int>{}, "atk");
    shop1->display();

    //shop1 -> display();
}