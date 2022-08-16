#include "sorter.h"

Sorter::Sorter()
{
    isSorted = false;
    setSwaps(0);
    setCompares(0);
}

void Sorter::bubbleSort(int arr[],int arrSize,int &swaps, int &compares)
{
    int temp = 0;
    bool stop = false;
    
    while(!stop)
    {
        for(int i = 0; i < (arrSize - 1); i++)
        {
            compares++;
            if(arr[i] > arr[i + 1])
            {
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                swaps++;
            }
        }
        
        stop = sortCheck(arr,arrSize,compares);
        //loopCount++;
    }
}

void Sorter::selectionSort(int arr[], int arrSize, int &swaps, int &compares)
{
    bool stop = false, firstRun = true;
    int front = 0, size = arrSize;
    int temp = 0, min = 0, minLocation = 0;
    
    while(stop == false)
    {
        for(int i = 0; i < size; i++)
        {
            int position = i + front;
            if(position != size)
            {
                if(i == 0)
                {
                    if(arr[position] == 10)
                    {
                        min = 10;
                    }
                    else
                    {
                        min = arr[position];
                    }
                    minLocation = position;
                }
                else
                {
                    if(min > arr[position])
                    {
                        compares++;
                        
                        if(arr[position] == 10)
                        {
                            min = 10;
                        }
                        else
                        {
                            min = arr[position];
                        }
                        minLocation = position;
                    }
                }
                    
            }
        }

            temp = arr[front];
            arr[front] = min;
            arr[minLocation] = temp;
            swaps++;
            
            stop = sortCheck(arr,size,compares);
            front++;
    }
}

void Sorter::quickSort(int arr[], int lowBound, int highBound)
{
    int pivotLocation = 0;
    int pivLocPlusOne;
    int comparisons = 0;
    
    comparisons = getCompares();
    
    comparisons += 1;
    if(lowBound < highBound)
    {
        pivotLocation = Pivot(arr,lowBound,highBound);
       
        int pivMinusOne = (pivotLocation - 1);
        pivLocPlusOne = pivotLocation + 1;
        
        quickSort(arr,lowBound,pivMinusOne);
        quickSort(arr,pivLocPlusOne,highBound);
    }
    
    setCompares(comparisons);
}

void Sorter::swap(int arr[],int pos1, int pos2)
{
    int temp = 0;
    
    temp = arr[pos2];
    arr[pos2] = arr[pos1];
    arr[pos1] = temp;
    
    temp = getSwaps();
    temp+=1;
    setSwaps(temp);
}

int Sorter::Pivot(int arr[], int lowBound, int highBound)
{
    int pivot = arr[highBound];
    int i = (lowBound - 1);
    int compares = 0;
    int temp = 0;
    
    for (int j = lowBound; j <= highBound - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++; 
            swap(arr,i,j);
        }
    }
    
    temp = getCompares();
    temp +=compares;
    setCompares(temp);

    int iPlusOne = (i + 1);
    swap(arr,iPlusOne,highBound);
    return iPlusOne;
   
}


/*
{
    int pivot = arr[highBound];
    int i = lowBound;
    for(int j = lowBound; j < highBound;j++)
    {
        if(arr[j] < pivot)
        {
            swap(arr,i,j);
            i++;
        }
        swap(arr,i,highBound);
         return i;
    }
    
    return -1;
}
*/

bool Sorter::sortCheck(int arr[], int arrSize, int &compCounter)
{
    for(int x = 0; x < (arrSize - 1); x++)
    {
        compCounter++;
        if(arr[x] > arr[x + 1])
            {
                isSorted = false;
                break;
            }
        else
            {
                isSorted = true;
            }
    }
    
    return isSorted;
}

void Sorter::setSwaps(int newSwaps)
{
    swaps = newSwaps;
}
void Sorter::setCompares(int newCompares)
{
    compares = newCompares;
}
int Sorter::getSwaps()
{
    return swaps;
}
int Sorter::getCompares()
{
    return compares;
}