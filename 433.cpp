#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

ostream& print(auto& p) {
  return cout << '[' << p.first << ',' << p.second << "], ";
}

////////////////////////////////////////////////////////////////////////////////
class Solution {
  public:
    using data_t = pair<int, int>;
    int minMutation(string start, string end, vector<string>& bank) {
      bank.push_back(start);
      vector<int> dist(bank.size());
      vector<int> prev(bank.size());
      vector<vector<int>> adj(bank.size());

      auto length = [&](int u, int v) {
        int l = 0;
        for(int i = 0; i < 8 and l < 2; i++) 
          if(bank[u] != bank[v]) l++;
        return l;
      };

      for(int v = 0; v < bank.size(); v++) {
        for(int u = v + 1; u < bank.size(); u++) 
          if(length(u, v) == 1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
          }
      }

      vector<data_t> q;
      int inf = bank.size() << 1;

      for(int v = 0; v < bank.size(); v++) {
        dist[v] = inf;
        prev[v] = -1;
        q.push_back({dist[v], v});
      }

      while(not q.empty()) {
        auto m = q.back();
        auto v = m.second;
        print(m);
        for(auto u : adj[v]) {
          int alt = dist[u] + length(u, v);
          if(alt < dist[v]) {
            dist[v] = alt;
            prev[v] = u;
          }
        }
        q.pop_back();
      }
    }
};
////////////////////////////////////////////////////////////////////////////////

int main()
{
  Solution s;
  vector<string> bank = {"", "", ""};
  s.minMutation("", "", bank);

  return 0;
}
