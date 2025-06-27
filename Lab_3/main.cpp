#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double f(const double& x){
    
    if (x < 0){
        return -x/2;
    }
    
    else if (x >= 0 && x < 2){
        return -sqrt(4- x * x) + 2;
    }
    
    else if (x >= 2 && x < 4){
        return sqrt(4 - (x - 2) * (x - 2));
    }
    
    else {
        return 2 - x/2;
    }
}



int main(){
    cout << "| x  |     y    |" << endl;
    cout << "-----------------" << endl;
    double x_beg = -4, x_end = 6, dx = 1;
    while (x_beg <= x_end){
        cout <<"| " << setw(2) << x_beg << " |" << " " << setw(8) << f(x_beg) << " |" << endl;
        x_beg += dx;
    }

    return 0;
}
