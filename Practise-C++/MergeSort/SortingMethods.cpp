#include <iostream>
#include <vector>
#include <random>

using namespace std;

class SortingMethods
{
public:
    void MergeSort(vector<int>& sortArray, int depth)
    {
        depth++;
        if (sortArray.size() <= 1) return;
    
        int a_Index = 0;
        int b_Index = 0;
        int l1 = sortArray.size() / 2;
        int l2 = sortArray.size() - l1;
    
        vector<int> a {sortArray.begin(), sortArray.begin() + l1};
        vector<int> b {sortArray.begin() + l1, sortArray.end()};
        /*
        cout << depth << " a list : ";
        for(int item : a)
        {
            cout << item << " ";
        }
        cout << "\n" << depth << " b list : ";
        for(int item : b)
        {
            cout << item << " ";
        }
        cout << "\n";
        */
        //a, b sorted by reference
        MergeSort(a,depth);
        MergeSort(b,depth);

        for (int i = 0; i < sortArray.size(); i++) 
        {
            //for (int n = 0; n < b.size(); n++)
            //{
                if (a_Index < l1 && b_Index < l2) 
                {
                    /*
                    cout << "depth " << depth << " : ";
                    for(int item : sortArray)
                    {
                        cout << item << " ";
                    }
                    */
                    //cout << "\n";
                    if (a[a_Index] < b[b_Index])
                    {
                        //cout << "depth " << depth << " : b larger"; 
                        sortArray[i] = a[a_Index];
                        a_Index++;
                    }
                    else if (a[a_Index] > b[b_Index])
                    {
                        //cout << "depth " << depth << " : a larger";
                        sortArray[i] = b[b_Index];
                        //sortArray[i+1] = a[a_Index];
                        b_Index++;
                        //a_Index++;
                        //i++;
                    }
                    else 
                    {
                        //cout << "depth " << depth << " : both equal";
                        sortArray[i] = a[a_Index];
                        sortArray[i + 1] = b[b_Index];
                        b_Index++;
                        a_Index++;
                        i++;
                    }
                }
                else if(b_Index == l2)
                {
                    sortArray[i] = a[a_Index];
                    a_Index++;
                }
                else 
                {
                    sortArray[i] = b[b_Index];
                    b_Index++;
                }
    
            //}
        }
        //cout<< "\n" << "finished depth : " << depth << "\n";
    }

    vector<int> myMergeSort(vector<int>& mainArr)
    {
        int l1 = mainArr.size() / 2;
        int l2 = mainArr.size() - l1;
        //check if mainArr is at its max depth
        if(mainArr.size() == 1)
        {
            return mainArr;
        }
        
        //create new vectors
        vector<int> a {mainArr.begin(), mainArr.begin() + l1};
        vector<int> b {mainArr.begin() + l1, mainArr.end()};
        myMergeSort(a);
        myMergeSort(b);
        int aPointer = 0;
        int bPointer = 0;
        
        for(int i = 0; i < mainArr.size(); i++)
        {
            if(aPointer < l1 && bPointer < l2)
            {
                if(a[aPointer] < b[bPointer])
                {
                    mainArr[i] = a[aPointer];
                    aPointer++;
                }
                else if(a[aPointer] > b[bPointer])
                {
                    mainArr[i] = b[bPointer];
                    bPointer++;
                }
                else
                {
                    mainArr[i] = a[aPointer];
                    mainArr[i+1] = b[bPointer];
                    i++;
                    bPointer++;
                    aPointer++;
                }
            }
            else if(aPointer < l1)
            {
                mainArr[i] = a[aPointer];
                aPointer++;
            }
            else
            {
                mainArr[i] = b[bPointer];
                bPointer++;
            }
            
        }
        return mainArr;
    }

    void QuickSort(vector<int> &sortArray){

    }
};



int main()
{
    
    static vector<int> newList;
    for(int i = 0; i < 1000001 ; i++){newList.push_back(rand() % 1000000001);};
    //newList = {7,2,1,5,4,12,1};
    SortingMethods sortMethod;
    int newDepth = 0;
    long startTime;
    //sortMethod.MergeSort(newList, newDepth);
    sortMethod.myMergeSort(newList);
    for(int c : newList)
    {
        cout << c << " , ";
    }
    cout << "\n";
    return 0;
}


