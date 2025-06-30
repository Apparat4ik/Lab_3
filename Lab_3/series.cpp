#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <cstdint>

using namespace std;

int64_t calculate_gcd(int64_t a, int64_t b) {
    return gcd(abs(a), abs(b));
}

pair<int64_t, int64_t> simplify_fraction(int64_t numerator, int64_t denominator) {   // упрощение дроби
    int64_t common_divisor = calculate_gcd(numerator, denominator);
    numerator /= common_divisor;
    denominator /= common_divisor;
    
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    
    return {numerator, denominator};
}

int64_t compute_eulerian_numerator(int n, int b) {   // функция для вычисления знаменателя через числа эйлера
    if (n == 0) {
        return 1;
    }
    
    vector<vector<int64_t>> eulerian_numbers(n + 1, vector<int64_t>(n + 1, 0));
    eulerian_numbers[0][0] = 1;
    
    for (int i = 1; i <= n; ++i) {
        for (int k = 0; k < i; ++k) {
            eulerian_numbers[i][k] = (k + 1) * eulerian_numbers[i - 1][k];
            if (k > 0) {
                eulerian_numbers[i][k] += (i - k) * eulerian_numbers[i - 1][k - 1];
            }
        }
    }
    
    int64_t polynomial_value = 0;
    int64_t b_power = 1;
    
    for (int k = 0; k < n; ++k) {
        polynomial_value += eulerian_numbers[n][k] * b_power;
        b_power *= b;
    }
    
    return polynomial_value * b;
}

int main() {
    
    int a, b;
    cin >> a >> b;
    
    if (b == 1) {
        cout << "infinity\n";
        return 0;
    }
    
    int64_t numerator = compute_eulerian_numerator(a, b);
    int64_t denominator = static_cast<int64_t>(pow(b - 1, a + 1));
    auto [simplified_num, simplified_den] = simplify_fraction(numerator, denominator);
    
    cout << "Сумма ряда равна " << simplified_num << "/" << simplified_den << endl;
    
    return 0;
}
