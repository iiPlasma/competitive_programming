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

template <typename num_t> 
struct segtree {
  int n, depth;
  num_t tree[4*MX], lazy[4*MX];

  void init(int s, long long* arr) {
    n = s;
    init(0, 0, n - 1, arr);
  }

  num_t init(int i, int l, int r, long long* arr) {
    if (l == r) return tree[i] = arr[l];

    int mid = (l + r) / 2;
    num_t a = init(2 * i + 1, l, mid, arr),
          b = init(2 * i + 2, mid + 1, r, arr);
    return tree[i] = a.op(b);
  }

  void update(int l, int r, num_t v) {
	if (l > r) return;
    update(0, 0, n - 1, l, r, v);
  }

  num_t update(int i, int tl, int tr, int ql, int qr, num_t v) {
    eval_lazy(i, tl, tr);
	
	if (tl > tr || tr < ql || qr < tl) return tree[i];
    if (ql <= tl && tr <= qr) {
      lazy[i] = lazy[i].val + v.val;
      eval_lazy(i, tl, tr);
      return tree[i];
    }
    
    if (tl == tr) return tree[i];

    int mid = (tl + tr) / 2;
    num_t a = update(2 * i + 1, tl, mid, ql, qr, v),
          b = update(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  num_t query(int l, int r) {
	if (l > r) return num_t::null_v;
    return query(0, 0, n-1, l, r);
  }

  num_t query(int i, int tl, int tr, int ql, int qr) {
    eval_lazy(i, tl, tr);
    
    if (ql <= tl && tr <= qr) return tree[i];
    if (tl > tr || tr < ql || qr < tl) return num_t::null_v;

    int mid = (tl + tr) / 2;
    num_t a = query(2 * i + 1, tl, mid, ql, qr),
          b = query(2 * i + 2, mid + 1, tr, ql, qr);
    return a.op(b);
  }

  void eval_lazy(int i, int l, int r) {
    tree[i] = tree[i].lazy_op(lazy[i], (r - l + 1));
    if (l != r) {
      lazy[i * 2 + 1] = lazy[i].val + lazy[i * 2 + 1].val;
      lazy[i * 2 + 2] = lazy[i].val + lazy[i * 2 + 2].val;
    }

    lazy[i] = num_t();
  }
};

struct sum_t {
  long long val;
  static const long long null_v = 0;

  sum_t(): val(0) {}
  sum_t(long long v): val(v) {}

  sum_t op(sum_t& other) {
    return sum_t(val + other.val);
  }
  
  sum_t lazy_op(sum_t v, int size) {
    return sum_t(val + v.val * size);
  }
};

/* DSU */
ll parent[MX], sz[MX];
l_l bounds[MX];

void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
    bounds[v] = {v, v};
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        chmin(bounds[a].first, bounds[b].first);
        chmax(bounds[a].second, bounds[b].second);
    }
}

int N, Q;
ll ar[MX], diff[MX];
ll cur = 0;

void solve() {
    cin >> N; 
    for (int i = 0; i < N; i++) {
		cin >> ar[i];
		make_set(i);
	}
    for (int i = 0; i < N - 1; i++) cin >> diff[i];
    for (int i = 1; i < N; i++) {
		if (ar[i - 1] + diff[i - 1] == ar[i]) union_sets(i - 1, i);
	}
	
	segtree<sum_t> st;
	
    st.init(N,  ar);
    cin >> Q;
    while (Q--) {
		char a; int b, c;
		cin >> a >> b >> c;
		if (a == '+') {
			b--;
			
			int num = b;
			b = find_set(b);
			int bf = bounds[b].first, bs = bounds[b].second;
			if (num != bf) {
				for (int i = bf; i < num; i++) make_set(i);
				for (int i = bf + 1; i < num; i++) union_sets(i, i - 1);
				for (int i = num; i <= bs; i++) make_set(i);
				for (int i = num + 1; i <= bs; i++) union_sets(i, i - 1);
			}
			b = find_set(num);
			bf = bounds[b].first, bs = bounds[b].second;
			st.update(num, bs, c);
			// cout << "Bounds: " << bf << " " << bs << "\n";
			while (bs < N - 1 && st.query(bs, bs).val + diff[bs] > st.query(bs + 1, bs + 1).val) {
				int d = find_set(bs + 1);
				int df = bounds[d].first, ds = bounds[d].second;
				// cout << "adding to " << st.query(bs + 1, bs + 1).val << "\n";
				st.update(df, ds, st.query(bs, bs).val + diff[bs] - st.query(bs + 1, bs + 1).val);
				union_sets(b, d);
				b = find_set(b);
				bf = bounds[b].first, bs = bounds[b].second;
			}
		} else { 
			b--; c--;
			cout << st.query(b, c).val << "\n";
		}
	}
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
 * Edge cases(N = 0, N = 1)
 * Just return 0 after result
 */
