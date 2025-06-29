#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

bool DoesPavelWin(int n, int m, const vector<int>& a) {
    vector<int> dp(n + 1, 0);   // вектор, содержащий максимальную разницу очков между игроками

    for (int i = n - 1; i >= 0; i--) {   // просматриваем позиции с конца
        int best = 0; // наибольшая разница за итерацию
        int sum = 0;
        for (int k = 1; k <= m && i + k <= n; k++) {   // все варианты с позиции i
            sum += a[i + k - 1];
            best = max(best, sum - dp[i + k]);   // максимальная разница из текущего best и разницы нынешней суммы и лучшего результата противника
        }
        dp[i] = best;
    }

    return dp[0] > 0;  // если с позиции 0 Павел сможет организовать разницу больше 0, то он гарантированно выигрывает
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    cout << (DoesPavelWin(n, m, a) ? 1 : 0) << endl;

    return 0;
}
