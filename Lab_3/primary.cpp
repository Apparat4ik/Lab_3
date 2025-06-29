#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

random_device r;


vector<int> Sieve(int n, vector<int>& not_prime) {                 // нахождение простых чисел через решето Эратосфена
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
    if (n == 1){return false;}
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
            return false;
        }
    }
    
    return true;
}


int MilerPrimary(int k, const int& t, const vector<int>& pr_nums){
    int n_min = 1 << (k - 2) , n_max = ( 1 << (k - 1) ) - 1;
    
    int n = 0;
    do {
        int m = 1;
        while (m <= pow(2, k - 1)){
            m *= pow(pr_nums[r() % pr_nums.size()], r() % 5);
            if (n_min < m && m < n_max){
                break;
            }
            m = 1;
        }
        
        n = 2 * m - 1;
    } while (!MilerTest(n, t));
    
    return n;
}









bool TestPolk (int n, int t, const vector<pair<int, int>>& decomp){
    if (n == 1){return false;}
    
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



int PolkPrimary (int k, int t, const vector<int>& pr_nums, vector<pair<int, int>>& decomp){
    int f_min = 1 << (k + 1) , f_max = ( 1 << (k + 2) ) - 1;
    int R_min = 1 << (k - 2) , R_max = ( 1 << (k - 1) ) - 1;
    
    int n = 1;
    do {
        int f = 1;
        while (f <= pow(2, k - 1)){
            f *= pow(pr_nums[r() % pr_nums.size()], r() % 10);
            if (f_min < f && f < f_max){
                break;
            }
            f = 1;
            
        }
        
        
        
        int R = r() % static_cast<int>(pow(2, k - 2));
        if (R % 2 != 0){R += 1;}
        if (R_min > R || R > R_max){
            n = 1;
        } else {
            n = R * f + 1;
        }
        decomp = Decomposition((n - 1) / R);
    } while (!TestPolk(n, t, decomp));
    
    return n;
}






int GOST (int t, int q){
    int N, u = 0, p = 0;
    double eps;
    do {
        eps = (r() % 100) / 100.0;
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



double phi(int n) {
    int result = n;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}


int main(){
    cout << "Выберите метод генерации числа:" << endl;
    cout << "1 - Метод Миллера" << endl;
    cout << "2 - Метод Поклингтона" << endl;
    cout << "1 - ГОСТ Р 34.10-94" << endl;
    int choice;
    
    int k, t, q, p, cnt = 0;
    vector<int> pr_nums, not_prime;
    vector<pair<int, int>> decomp;
            
            
            
    vector<int> k_nums, results;
    vector<char> is_pr;
    
    
    
    for (int i = 0; i < 10; i++){
        
        cin >> choice;
        
        switch (choice) {
            case 1:
                pr_nums = Sieve(500, not_prime);
                cout << "Введите через пробел битовую длину числа и параметр надежности: " << '\t';
                cin >> k >> t;
                p = MilerPrimary(k, t, pr_nums);
                cout << "Ваше простое число: " << p << " Вероятность ошибки: " << pow((phi(p - 1)/ (p - 1)), t) << endl;
                results.push_back(p);
                
                cout << "Повторная проверка" << endl;
                
                if (MilerTest(p, 1)){
                    cout << "Число простое" << endl;
                    is_pr.push_back('+');
                } else {
                    cout << "Число составное" << endl;
                    is_pr.push_back('-');
                }
                
                
                for (int num : not_prime){
                    if (MilerTest(num, 1)){
                        cnt++;
                    }
                }
                k_nums.push_back(cnt);
                cnt = 0;
                break;
                
            case 2:
                pr_nums = Sieve(500, not_prime);
                cout << "Введите через пробел битовую длину числа и параметр надежности: " << '\t';
                cin >> k >> t;
                p = PolkPrimary(k, t, pr_nums, decomp);
                cout << "Ваше простое число: " << p << endl;
                
                results.push_back(p);
                
                cout << "Повторная проверка" << endl;
                
                if (TestPolk(p, 1, decomp)){
                    cout << "Число простое" << endl;
                    is_pr.push_back('+');
                } else {
                    cout << "Число составное" << endl;
                    is_pr.push_back('-');
                }
                
                for (int num : not_prime){
                    if (TestPolk(num, 1, decomp)){
                        cnt++;
                    }
                }
                k_nums.push_back(cnt);
                cnt = 0;
                
                break;
                
            case 3:
                cout << "Введите через пробел битовую длину числа, простое число, битовая длина которого в 2 раза меньше и параметр t для теста: " << '\t';
                cin >> k >> q >> t;
                p = GOST(k, q);
                cout << "Ваше простое число: " << p << " Вероятность ошибки: " << 1.0 - 1.0 / q << endl;
                
                results.push_back(p);
                
                cout << "Повторная проверка" << endl;
                
                if (MilerTest(p, 1)){
                    cout << "Число простое" << endl;
                    is_pr.push_back('+');
                } else {
                    cout << "Число составное" << endl;
                    is_pr.push_back('-');
                    
                }
                
                for (int num : not_prime){
                    if (MilerTest(num, 1)){
                        cnt++;
                    }
                }
                k_nums.push_back(cnt);
                cnt = 0;
                
                break;
                
            default:
                cerr << "Нет такого выбора" << endl;
                i--;
                break;
        }
    }
    
    cout << "| №     P         Результат    K |" << endl;
    for (int i = 0; i < 10; i++){
        cout << "| " << i + 1 << setw(2) << "    "<< results[i] << setw(10) << "         " << is_pr[i] << "       "<< k_nums[i] <<" |" << endl;
    }
    
    return 0;
    
}
