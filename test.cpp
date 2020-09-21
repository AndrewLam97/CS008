#include <iostream>
using namespace std;

//int counter = 0;

int coffee(int n ){
    int s = n*n;
    for(int q = 0; q < n; q++){
        s = s-q;
        cout << ".";
    }
    for(int q = n; q > 0; q--){
        s = s-q;
        cout << ".";
    }
    //++counter;
    //cout << ".";
    return s+2;
}

int mocha(int n){
    int r = 0;
    for(int i=0;i<=n;i=i+16){
        for(int j = 0; j<i;j++){
            r++;
            //++counter;
            cout << "-";
        }  
    }
    return r;
}

int espresso(int n){
    int j=0;
    for(int k=16;coffee(k) * mocha(k) - k <=n; k+=16){
        j++;
        //++counter;
        cout << "0";
    }
    return j;
}

int fun(int n){
    int j = 0;
    for(int k = 0; k < coffee(k) * n; k++){
        j = j +2;
        cout << ".";
    }
    return espresso(mocha(j));
}

int main(){
    fun(20);
    //cout << counter << endl;
    cout << "DONE" << endl;
    system("PAUSE");

    return 0;
}