#include <iostream>
#include <math.h>
#include <vector>
#include <random>

using namespace std;

random_device r;

vector<int> Sieve(int n) {                 // нахождение простых чисел через решето Эратосфена
    vector<bool> is_prime(n + 1, true);
    
    for (int i = 2; i <= n; i++)
        if (is_prime[i])
            for (int j = 2*i; j <= n; j += i)
                is_prime[j] = false;
    
    vector<int> pr_num;
    
    for (int i = 2; i <= n; i++){
        if (is_prime[i]){
            pr_num.push_back(i);
        }
    }
    return pr_num;
}

int aXmodP (int a, int x, int p){ // быстрое возведение в степень по модулю
    int degree = x % (p - 1); // применение теоремы Ферма
    int result = 1;
    for(int i = 1; i <= degree; i++){
        result = result * a;
        result %= p;
    }
    
    return result;
}


vector<pair<int, int>> Decomposition(int n) {   // каноническое рахложение числа
    vector<pair<int, int>> dcompsitn;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                count++;
                n /= i;
            }
            dcompsitn.push_back({i, count});
        }
    }
    if (n > 1) {
        dcompsitn.push_back({n, 1});
    }
    return dcompsitn;
}






bool MilerTest(int n, int t){      // тест Милера на простоту
    vector<int> rand_numbers;
    
    for (int i = 0; i < t; i++){
        int a = r() % n;
        if (aXmodP(a, n - 1, n) != 1){
            return false;
        }
        rand_numbers.push_back(a);
    }
    
    vector<pair<int, int>> decomp = Decomposition(n - 1);
    
    
    
    for (pair<int, int> factor : decomp){
        bool all_one = true;
        for (int aj : rand_numbers){
            if (aXmodP(aj, (n - 1) / factor.first, n) != 1){
                all_one = false;
                break;
            }
        }
        
        if (all_one){
            return true;
        }
    }
    
    return true;
}


int MilerPrimary(int k, const int& t, const vector<int>& pr_nums){
    int n = 0;
    while (!MilerTest(n, t)){
        int m = 1;
        while (m <= pow(2, k - 1)){
            m *= pow(pr_nums[r() % pr_nums.size()], r() % 10);
        }
        
        n = 2 * m - 1;
    }
    
    return n;
}









bool TestPolk (int n, int t, const vector<pair<int, int>>& decomp){
    vector<int> rand_numbers;
    
    for (int i = 0; i < t; i++){
        int a = r() % n;
        if (aXmodP(a, n - 1, n) != 1){
            return false;
        }
        rand_numbers.push_back(a);
    }
    
    
    for (int ai : rand_numbers){
        bool no_one = true;
        for (pair<int, int> factor : decomp){
            if (aXmodP(ai, (n - 1) / factor.first, n) == 1){
                no_one = false;
                break;
            }
        }
        if (no_one) {
            return true;
        }
    }
    return false;
}



int PolkPrimary (int k, int t, const vector<int>& pr_nums){
    int n = 0;
    while (!TestPolk(n, t, Decomposition(n - 1))){
        int f = 1;
        while (f <= pow(2, k - 1)){
            f *= pow(pr_nums[r() % pr_nums.size()], r() % 10);
        }
        int R = r() % static_cast<int>(pow(2, k - 2));
        if (R % 2 != 0){R += 1;}
        n = R * f + 1;
    }
    
    return n;
}






int GOST (int t, int q, int eps){
    int N, u = 0, p = 0;
    do {
        N = ceil((pow(2, t - 1)/ q) + (pow(2, t - 1) * eps / q));
        if (N % 2 != 0){N += 1;}
        
        
        p = (N + u) * q + 1;
        if (p > pow(2, t)){
            continue;
        }
        if (aXmodP(2, p - 1, p) == 1 && aXmodP(2, N + u, p) != 1){
            u += 2;
        }
    } while (!(aXmodP(2, p - 1, p) == 1 && aXmodP(2, N + u, p) != 1));
    return p;
}


int main(){
    
    cout << GOST(7, 13, 0) << endl;
    /*double cnt = 0;
    for (int i = 0; i < 100; i++){
        if (TestPolk(437, 1, {{109, 1}, {2, 2}})){cnt++;}
    }
    cout << cnt / 100 << endl;*/
    return 0;
}
