# YuGiOH-Card-Sorting

# Build and Run
1) Clone the repository
2) ```.csv``` file given, but it can be replaced with any ```.csv`` YuGiOH dataset
3) Construct a ```CardShop``` in ```main.cpp``` e.g: ```CardShop *shop1 = new CardShop("cards.csv");```
4) Sort it with any algorithm: ```bubbleSort, insertionSort, quickSort, mergeSort``` e.g: ```shop1->mergesort(less<int>{}, "atk")```
5) If you want to display the cards: ```shop1->display()```
