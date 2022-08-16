#ifndef SORTER_H
#define SORTER_H

#include <iostream>

using namespace std;

class Sorter
{
    private:
    
    int swaps;
    int compares;
    
    public:
        Sorter();
        
        bool isSorted;
        
        void bubbleSort(int arr[],int arrSize,int &swaps, int &compares);
        void selectionSort(int arr[], int arrSize, int &swaps, int &compares);        
        void quickSort(int arr[], int lowBound, int highBound);       
        
        //ref https://www.youtube.com/watch?v=Hoixgm4-P4M&ab_channel=MichaelSambol
        
        bool sortCheck(int arr[], int arrSize,int &compCounter);
        void swap(int arr[],int pos1, int pos2);
        int Pivot(int arr[], int lowBound, int highBound);
        
        void setSwaps(int newSwaps);
        void setCompares(int newCompares);
        int getSwaps();
        int getCompares();
};
#endif