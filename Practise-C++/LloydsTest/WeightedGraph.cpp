#include <map>
#include <vector>
#include <iostream>
using namespace std;



int solution(int N, vector<int>& A, vector<int>& B){
    map<int, int> weights = map<int,int>();
    map<int, int> Occurs = map<int,int>();
    //Assign map values
    for(int i = 1; i <= N; i++){
        weights[i] = 0;
        Occurs[i] = 0;
    }
    // find num of occurs
    for(int i = 0 ; i < N; i++){
        if(i < A.size()){
            Occurs[A[i]] += 1;
        }
        else{
            Occurs[B[(i - A.size())]] += 1;
        }
    }
/*
    for(int i = 1 ; i <= N; i++){
        cout<< i << " : "<<Occurs[i]<<"\n";
    }
*/
    //assign weights
    int currMax = 1;
    int maxWeightAssign = N;
    for(int i = 0; i < N; i++){
        currMax = 1;
        for(int n = 1; n <= N; n++){
            if(weights[currMax] == 0){
                if(weights[n] == 0){
                    if(Occurs[n] > Occurs[currMax]){
                        currMax = n;
                        //cout<<"changed max \n";
                    }
                }
            }
            else{
                currMax += 1;
            }
        }
        //currMax = i;
        cout<<currMax<<"\n";
        weights[currMax] = maxWeightAssign;
        //currMax = 1;
        maxWeightAssign--;
    }

    for(int i = 1 ; i <= N; i++){
        cout<< i << " : "<<weights[i]<<"\n";
    }

    //traverse through links and add to total
    int total = 0;
    for(int i = 0; i < A.size(); i++){
        total += weights[A[i]] + weights[B[i]];
    }

    return total;
}

int main(){
    vector<int> a = vector<int>{2,2,1,1};
    vector<int> b = vector<int>{4,3,3,2};
    cout<<solution(5,a,b);
}