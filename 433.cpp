#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
class Solution {
  public:
    using data_t = pair<int, int>;
    const int INF = numeric_limits<int>::max();

    int length(const string& u, const string& v) {
      int l = 0;
      for(int i = 0; i < 8 and l < 2; i++) 
        if(u[i] != v[i]) l++;
      return l <= 1 ? l : INF;
    };

    int minMutation(string start, string end, vector<string>& bank) {
      if(bank.empty()) return -1;
      else {
        auto it = find(bank.begin(), bank.end(), end);
        if(it == bank.end()) return -1;
      }
      bank.push_back(start);

      vector<int> dist(bank.size());
      vector<vector<int>> adj(bank.size());
      for(int v = 0; v < bank.size(); v++) {
        for(int u = v + 1; u < bank.size(); u++) 
          if(length(bank[u], bank[v]) == 1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
          }
      }

      vector<data_t> q;
      for(int v = 0; v < bank.size() - 1; v++) {
        dist[v] = length(start, bank[v]);
        q.push_back({dist[v], v});
      }
      dist.back() = 0;
      make_heap(q.begin(), q.end(), greater<data_t>());

      while(not q.empty()) {
        pop_heap(q.begin(), q.end(), greater<data_t>());
        auto m = q.back();
        auto v = m.second;
        for(auto u : adj[v]) {
          long alt = dist[u];
          alt += length(bank[u], bank[v]);
          if(alt < dist[v]) {
            dist[v] = alt;
          }
        }
        q.pop_back();
        make_heap(q.begin(), q.end(), greater<data_t>());
      }

      bank.pop_back();
      int mm = INF;
      for(int v = 0; v < bank.size(); v++) {
        long d = dist[v];
        d += length(bank[v], end);
        if(mm > d) mm = d;
      }
      if(mm == INF) return -1;
      else return mm;
    }
};
////////////////////////////////////////////////////////////////////////////////

int main()
{
  Solution s;
  auto start = "AAAACCCC";
  auto end = "CCCCCCCC";
  vector<string> bank = {"AAAACCCA","AAACCCCA","AACCCCCA","AACCCCCC","ACCCCCCC","CCCCCCCC","AAACCCCC","AACCCCCC"};
  cout << s.minMutation(start, end, bank) << endl;

  return 0;
}
