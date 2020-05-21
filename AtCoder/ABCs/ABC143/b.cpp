#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> l_l;
typedef pair<int, int> i_i;

template<class T>
inline bool chmax(T &a, T b) {
    if(a < b) {
        a = b;
        return true;
    }
    return false;
}
 
template<class T>
inline bool chmin(T &a, T b) {
    if(a > b) {
        a = b;
        return true;
    }
    return false;
}

const ll INF = 1e18;
const ll MOD = 998244353;
const ll MX = 1000001;

int N;
ll ans;

void solve() {
    cin >> N;
    vector<int> a(N);
    for (auto& i : a) cin >> i;
    for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			ans += a[i] * a[j];	
		}
	}
	cout << ans;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
    ll testCases = 1; // cin >> testCases;
    while (testCases--) solve();
    return 0;
    // You should actually read the stuff at the bottom
}

/* Stuff to Look For
 * -----------------
 * Int overflow, array bounds
 * Initializing all variables, avoid weird behavior
 * Edge cases(n = 0, n = 1)
 * Just return 0 after result
 */
