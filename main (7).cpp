#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#include "sorter.h"

void copyArray(int originalArr[],int copyArray[], int arrSize);
void fileWriter(string sortType,int swaps, int compares, chrono::duration<double> timePassed,int iterations);
void fileWriterVect(string fileToBeOpened, vector<int> swaps, vector<int> compares, vector<chrono::duration<double>> times);

int main()
{
    int sizes[5], random = 0;
    Sorter sortManager;
    bool actuallySorted =  false;
    sizes[0] = 1000; sizes[1] = 10000; sizes[2] = 100000;
    sizes[3] = 1000; sizes[4] = 10000; sizes[5] = 100000;    
    vector<int> quickVect, bubbleVect, selectionVect;
    vector<int> bubbleSwaps,bubbleComps,quickSwaps,quickComps,selectSwaps, selectComps;
    vector<chrono::duration<double>> bubbleTime,quickTime,selectTime;
    chrono::time_point<std::chrono::system_clock> start, end;
    chrono::duration<double> qTime, bTime, sTime;
    int avgSwaps = 0, avgComps = 0;
    chrono::duration<double> avgTime;
    
    
    srand(time(NULL));
    // 0 - swaps
    // 1 - compares
    
    for(int i = 0; i < 3; i++)
    {
        for(int n = 0; n < 10; n++)
        {
            int size = sizes[i];
            if(size == 100000)
            {
                break
            }
            int numbers[size], quick[size], bubble[size], selection[size];
   
            for(int i = 0; i < size; i++)
            {
                random = rand() % size + 1;
                numbers[i] = random;
            }
            
            copyArray(numbers,bubble,size); copyArray(numbers,quick,size); copyArray(numbers,selection,size);
            
            int numSwaps = 0, numCompares = 0;
            int swapTemp = 0, comparesTemp = 0;    
                
                start = chrono::system_clock::now();
                sortManager.bubbleSort(bubble,sizes[i],numSwaps,numCompares);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;           
                bTime = elapsed_seconds;
                 
                
                bubbleVect.push_back(0); //swaps
                bubbleVect.push_back(0); //compares

                swapTemp = bubbleVect.at(0);
                comparesTemp = bubbleVect.at(1);
                
                bubbleSwaps.push_back(numSwaps);
                bubbleComps.push_back(numCompares);
                bubbleTime.push_back(bTime);
                
                swapTemp += numSwaps;
                comparesTemp += numCompares;
                
                bubbleVect.at(0) = swapTemp;
                bubbleVect.at(1) = comparesTemp;

            numSwaps = 0; numCompares = 0; swapTemp = 0; comparesTemp = 0; 

                start = chrono::system_clock::now();
                sortManager.selectionSort(selection,sizes[i],numSwaps,numCompares);
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds2 = end - start;           
                sTime = elapsed_seconds2;
                
                selectionVect.push_back(0); //swaps
                selectionVect.push_back(0); //compares

                swapTemp = selectionVect.at(0);
                comparesTemp = selectionVect.at(1);
                
                selectSwaps.push_back(numSwaps);
                selectComps.push_back(numCompares);
                selectTime.push_back(sTime);
                
                swapTemp += numSwaps;
                comparesTemp += numCompares;
                
                selectionVect.at(0) = swapTemp;
                selectionVect.at(1) = comparesTemp;            
                
            numSwaps = 0; numCompares = 0; swapTemp = 0; comparesTemp = 0; 
            
                start = chrono::system_clock::now();
                int highB = (sizes[i] - 1);
                sortManager.quickSort(quick,0,highB);
                actuallySorted = sortManager.sortCheck(quick,sizes[i],numCompares);
                numCompares = 0;
                
                
                end = chrono::system_clock::now();
                chrono::duration<double> elapsed_seconds3 = end - start;           
                qTime = elapsed_seconds3;

                
                quickVect.push_back(0); //swaps
                quickVect.push_back(0); //compares

                swapTemp = quickVect.at(0);
                comparesTemp = quickVect.at(1);
                
                quickSwaps.push_back(sortManager.getSwaps());
                quickComps.push_back(sortManager.getCompares());
                quickTime.push_back(sTime);
                
                swapTemp += sortManager.getSwaps();
                comparesTemp += sortManager.getCompares();
                
                quickVect.at(0) = swapTemp;
                quickVect.at(1) = comparesTemp;            
               
                
        }
        
        string fileName = "";
        switch(i)
        {
            case 0:
                fileName = "1000unsorted.csv";
                break;
            case 1:
                fileName = "10000unsorted.csv";
                break;
            case 2:
                fileName = "100000unsorted.csv";
                break;
        }
        fileWriterVect(fileName, bubbleSwaps, bubbleComps, bubbleTime);
        avgTime = bTime/10; avgSwaps = bubbleVect.at(0)/10; avgComps = bubbleVect.at(1)/10;
        fileWriter("Bubble Sort Avg: ", avgSwaps, avgComps, avgTime, i);
        
        fileWriterVect(fileName, selectSwaps, selectComps, selectTime);
        avgTime = sTime/10; avgSwaps = selectionVect.at(0)/10; avgComps = selectionVect.at(1)/10;
        fileWriter("Selection Sort Avg: ", avgSwaps, avgComps, avgTime, i);
        
        fileWriterVect(fileName, quickSwaps, quickComps, quickTime);
        avgTime = qTime/10; avgSwaps = quickVect.at(0)/10; avgComps = quickVect.at(1)/10;
        fileWriter("Quick Sort Avg : ", avgSwaps, avgComps, avgTime, i);
        
        int size = sizes[i];
        int sorted[size]; 
        int numbers[size], quick[size], bubble[size], selection[size];        
        for(int x = 0;x < size;x++)
        {
            sorted[x] = bubble[x];
        }
        
        for(int n = 0; n < 10; n++)
        {
                    copyArray(sorted,bubble,size); copyArray(sorted,quick,size); copyArray(sorted,selection,size);
                    
                    int numSwaps = 0, numCompares = 0;
                    int swapTemp = 0, comparesTemp = 0;    
                        
                        start = chrono::system_clock::now();
                        sortManager.bubbleSort(bubble,sizes[i],numSwaps,numCompares);
                        end = chrono::system_clock::now();
                        chrono::duration<double> elapsed_seconds = end - start;           
                        bTime = elapsed_seconds;
                         
                        
                        bubbleVect.push_back(0); //swaps
                        bubbleVect.push_back(0); //compares
        
                        swapTemp = bubbleVect.at(0);
                        comparesTemp = bubbleVect.at(1);
                        
                        bubbleSwaps.push_back(numSwaps);
                        bubbleComps.push_back(numCompares);                        
                        
                        swapTemp += numSwaps;
                        comparesTemp += numCompares;
                        
                        bubbleVect.at(0) = swapTemp;
                        bubbleVect.at(1) = comparesTemp;
                     
                    numSwaps = 0; numCompares = 0; swapTemp = 0; comparesTemp = 0; 
        
                        start = chrono::system_clock::now();
                        sortManager.selectionSort(selection,sizes[i],numSwaps,numCompares);
                        end = chrono::system_clock::now();
                        chrono::duration<double> elapsed_seconds2 = end - start;           
                        sTime = elapsed_seconds2;
                        
                        selectionVect.push_back(0); //swaps
                        selectionVect.push_back(0); //compares
        
                        swapTemp = selectionVect.at(0);
                        comparesTemp = selectionVect.at(1);

                        selectSwaps.push_back(numSwaps);
                        selectComps.push_back(numCompares);
                        
                        swapTemp += numSwaps;
                        comparesTemp += numCompares;
                        
                        selectionVect.at(0) = swapTemp;
                        selectionVect.at(1) = comparesTemp;            
                        
                    numSwaps = 0; numCompares = 0; swapTemp = 0; comparesTemp = 0; 
                    
                        start = chrono::system_clock::now();
                        int highB = (sizes[i] - 1);
                        sortManager.quickSort(quick,0,highB);
                        end = chrono::system_clock::now();
                        chrono::duration<double> elapsed_seconds3 = end - start;           
                        qTime = elapsed_seconds3;
        
                        
                        quickVect.push_back(0); //swaps
                        quickVect.push_back(0); //compares
        
                        swapTemp = quickVect.at(0);
                        comparesTemp = quickVect.at(1);
                        
                        quickSwaps.push_back(sortManager.getSwaps());
                        quickComps.push_back(sortManager.getCompares());                 
                        
                        swapTemp += sortManager.getSwaps();
                        comparesTemp += sortManager.getCompares();
                        
                        quickVect.at(0) = swapTemp;
                        quickVect.at(1) = comparesTemp;            
                       
                        
                }
        int switchControl = (i + 3);
        switch(switchControl)
        {
            case 3:
                fileName = "1000sorted.csv";
                break;
            case 4:
                fileName = "10000sorted.csv";
                break;
            case 5:
                fileName = "100000sorted.csv";
                break;
        }
        
        fileWriterVect(fileName, bubbleSwaps, bubbleComps, bubbleTime);
        avgTime = bTime/10; avgSwaps = bubbleVect.at(0)/10; avgComps = bubbleVect.at(1)/10;
        fileWriter("Bubble Sort Avg: ", avgSwaps, avgComps, avgTime, switchControl);
        
        fileWriterVect(fileName, selectSwaps, selectComps, selectTime);
        avgTime = sTime/10; avgSwaps = selectionVect.at(0)/10; avgComps = selectionVect.at(1)/10;
        fileWriter("Selection Sort Avg: ", avgSwaps, avgComps, avgTime, switchControl);
        
        fileWriterVect(fileName, quickSwaps, quickComps, quickTime);
        avgTime = qTime/10; avgSwaps = quickVect.at(0)/10; avgComps = quickVect.at(1)/10;
        fileWriter("Quick Sort Avg : ", avgSwaps, avgComps, avgTime, switchControl);              
                
    }
    
    return 0;
}

void copyArray(int originalArr[],int copyArray[], int arrSize)
{
    for(int i = 0; i < arrSize; i++)
    {
        copyArray[i] = originalArr[i];
    }
}

void fileWriterVect(string fileToBeOpened, vector<int> swaps, vector<int> compares, vector<chrono::duration<double>> times)
{
    ofstream fout2;
    fout2.open(fileToBeOpened, std::fstream::in | std::fstream::out | std::fstream::app);
    
    for(int y = 0; y < 6; y++)
    {
        fout2 << "Run " << y << ": ," << swaps.at(y) << " , " << compares.at(y) << " , " << times.at(y).count() << endl;  
    }
    
    fout2.close();
}

void fileWriter(string sortType,int swaps, int compares, chrono::duration<double> timePassed,int iterations)
{
    ofstream fout;
    cout << "Writing to file, write number " << iterations << endl;
    switch(iterations)
    {
        
        case 0:
            fout.open("1000unsorted.csv", std::fstream::in | std::fstream::out | std::fstream::app);
            
            fout << sortType  << " , " <<swaps << " , " << compares  << " , " << timePassed.count() << endl; 
            
            fout.close();
            
            cout << "1000 unsorted accessed" << endl;
            
            break;
        case 1:
            fout.open("10000unsorted.csv", std::fstream::in | std::fstream::out | std::fstream::app);
            
            fout << sortType  << " , " <<swaps << " , " << compares  << " , " << timePassed.count() << endl; 
            
            fout.close();
            
            cout << "10000 unsorted accessed" << endl;
            
            break;
        
        case 2:
            fout.open("100000unsorted.csv", std::fstream::in | std::fstream::out | std::fstream::app);
            fout << sortType  << " , " <<swaps << " , " << compares  << " , " << timePassed.count() << endl; 
            
            fout.close();
            
            cout << "100000 unsorted accessed" << endl;
            
            break;
        
        case 3:
            fout.open("1000sorted.csv", std::fstream::in | std::fstream::out | std::fstream::app);
            
            fout << sortType  << " , " <<swaps << " , " << compares  << " , " << timePassed.count() << endl; 
            
            fout.close();
            
            cout << "1000 sorted accessed" << endl;
            
            break;
        case 4:
            fout.open("10000sorted.csv", std::fstream::in | std::fstream::out | std::fstream::app);
            
            fout << sortType  << " , " <<swaps << " , " << compares  << " , " << timePassed.count() << endl; 
            
            fout.close();
            
            cout << "10000 sorted accessed" << endl;
            
            break;
        
        case 5:
            fout.open("100000sorted.csv", std::fstream::in | std::fstream::out | std::fstream::app);
            fout << sortType  << " , " <<swaps << " , " << compares  << " , " << timePassed.count() << endl; 
            
            fout.close();
            
            cout << "100000 stored accessed" << endl;
            
            break;
        default:
            cout << "You've messed up in a way that literally should not be possible" << endl;
            break;
    }

    
}