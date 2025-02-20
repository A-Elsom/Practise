#include <iostream>
#include <vector>

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
        //a, b sorted by reference
        MergeSort(a,depth);
        MergeSort(b,depth);

        for (int i = 0; i < sortArray.size(); i++) 
        {
            //for (int n = 0; n < b.size(); n++)
            //{
                if (a_Index < l1) 
                {
                    cout << "depth " << depth << " : ";
                    for(int item : sortArray)
                    {
                        cout << item << " ";
                    }
                    cout << "\n";
                    if (a[a_Index] < b[b_Index])
                    {
                        sortArray[i] = a[a_Index];
                        a_Index++;
                    }
                    else if (a[a_Index] > b[b_Index])
                    {
                        sortArray[i] = b[b_Index];
                        sortArray[i+1] = a[a_Index];
                        b_Index++;
                        a_Index++;
                        i++;
                    }
                    else 
                    {
                        sortArray[i] = a[a_Index];
                        sortArray[i + 1] = b[b_Index];
                        b_Index++;
                        a_Index++;
                        i++;
                    }
                }
                else 
                {
                    sortArray[i] = b[b_Index];
                    b_Index++;
                }
    
            //}
        }
        cout<< "\n" << "finished depth : " << depth << "\n";
    }

};

int main()
{
    static vector<int> newList = {1,3,5,2,11,23,4};
    SortingMethods sortMethod;
    int newDepth = 0;
    sortMethod.MergeSort(newList, newDepth);
    for(int c : newList)
    {
        cout << c << "\n";
    }
    cout << "\n";
    return 0;
}


