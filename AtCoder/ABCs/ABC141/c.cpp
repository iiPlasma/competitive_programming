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
const ll MX = 100005;

ll N, K, Q;
int cnt[MX];

void solve() {
    cin >> N >> K >> Q;
    vector<int> a(Q);
    for (auto& i : a) {
		cin >> i;
		cnt[i]++;
	}
	for (int i = 1; i <= N; i++) {
		K - Q + cnt[i] > 0 ? cout << "Yes\n" : cout << "No\n";
	}
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
    ll T = 1; //cin >> T;
    while (T--) solve();
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
