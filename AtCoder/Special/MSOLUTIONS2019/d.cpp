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
const ll MX = 10005;

int N, U, V;
vector<int> graph[MX], a;
int num[MX];
int cnt, ans;

void dfs(int v, int p) {
	num[v] = a[cnt];
	cnt++;
	if (p != -1) ans += num[v];
	for (auto& u : graph[v]) {
		if (u != p) dfs(u, v);
	}
}

void solve() {
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
		cin >> U >> V;
		graph[U].push_back(V);
		graph[V].push_back(U);
	}
	a.resize(N);
	for(auto& i : a) cin >> i;
	sort(a.begin(), a.end(), greater<int>());
	
	dfs(1, -1);
	cout << ans << "\n";
	for (int i = 1; i <= N; i++) cout << num[i] << " ";
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
    ll T = 1; // cin >> T;
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
