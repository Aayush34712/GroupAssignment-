#include <iostream>
using namespace std;

int rFib(int n) {
    if(n == 0){
    return 0;
    }
    if(n == 1){
    return 1;
    }
    int a = 1;
    int b =1;
for (int i = 3; i<= n; i++){
    int c = a + b;
    a = b;
    b =c;
    }
    return b;
}



int main() {
    int fibNum, factNum;

    cout << "Enter position for Fibonacci number: ";
    cin >> fibNum;
    cout << "Fibonacci number at position " << fibNum << " is: " << rFib(fibNum) << endl;

    

    return 0;
}