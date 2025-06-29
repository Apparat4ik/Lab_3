#include <iostream>
#include <cmath>
#include <cstdint>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    while(b != 0) {
        int64_t r = b;
        b = a % b;
        a = r;
    }
    return a;
}

pair<int64_t, int64_t> simplify(int64_t num, int64_t den) {
    int64_t g = gcd(abs(num), abs(den));
    
    num /= g;
    den /= g;

    if (den < 0) {
        num *= -1;
        den *= -1;
    }

    return {num, den};
}

int64_t compute_numerator(int a, int b) {
    switch(a) {
        case 1: return b;
            
        case 2: return b * (b + 1);
            
        case 3: return b * (b*b + 4*b + 1);
            
        case 4: return b * (b*b*b + 11*b*b + 11*b + 1);
            
        case 5: return b * (b*b*b*b + 26*b*b*b + 66*b*b + 26*b + 1);
            
        case 6: return b * (static_cast<int64_t>(pow(b,5)) + 57*static_cast<int64_t>(pow(b,4)) + 302*static_cast<int64_t>(pow(b,3)) + 302*b*b + 57*b + 1);
            
        case 7: return b * (static_cast<int64_t>(pow(b,6)) + 120*static_cast<int64_t>(pow(b,5)) + 1191*static_cast<int64_t>(pow(b,4)) + 2416*static_cast<int64_t>(pow(b,3)) + 1191*b*b + 120*b + 1);
            
        case 8: return b * (static_cast<int64_t>(pow(b,7)) + 247*static_cast<int64_t>(pow(b,6)) + 4293*static_cast<int64_t>(pow(b,5)) + 15619*static_cast<int64_t>(pow(b,4)) + 15619*static_cast<int64_t>(pow(b,3)) + 4293*b*b + 247*b + 1);
            
        case 9: return b * (static_cast<int64_t>(pow(b,8)) + 502*static_cast<int64_t>(pow(b,7)) + 14608*static_cast<int64_t>(pow(b,6)) + 88234*static_cast<int64_t>(pow(b,5)) + 156190*static_cast<int64_t>(pow(b,4)) + 88234*static_cast<int64_t>(pow(b,3)) + 14608*b*b + 502*b + 1);
            
        case 10: return b * (static_cast<int64_t>(pow(b,9)) + 1013*static_cast<int64_t>(pow(b,8)) + 47840*static_cast<int64_t>(pow(b,7)) + 455192*static_cast<int64_t>(pow(b,6)) + 1310354*static_cast<int64_t>(pow(b,5)) + 1310354*static_cast<int64_t>(pow(b,4)) + 455192*static_cast<int64_t>(pow(b,3)) + 47840*b*b + 1013*b + 1);
            
        default: return 0;
    }
}

int main() {
    int a, b;
    cin >> a >> b;

    if (b < 1 || (b == 1 &&  a >= -1)) {
        cout << "infinity" << endl;
        return 0;
    }

    int64_t numerator = compute_numerator(a, b);
    int64_t denominator = static_cast<int64_t>(pow(b - 1, a + 1));

    auto [sim_num, sim_den] = simplify(numerator, denominator);
    
    if (sim_den == 1) {
        cout << sim_num << endl;
    } else {
        cout << sim_num << "/" << sim_den << endl;
    }

    return 0;
}
