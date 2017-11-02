#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

ostream& print(auto& p) {
  return cout << '[' << p.first << ',' << p.second << "], ";
}

////////////////////////////////////////////////////////////////////////////////
class Solution {
  public:
    struct Meta {
      int sum_;
      int idx_;
      int current_k_;
      Meta() {}
      Meta(int sum, int idx, int k)
        : sum_(sum)
          , idx_(idx)
          , current_k_(k)
      {}

      bool operator<(auto& o) const {
        if(current_k_ == o.current_k_) return sum_ > o.sum_;
        else return current_k_ > o.current_k_; 
      }
    };

    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
      vector<Meta> metas(people.size());

      int i = 0;
      for(auto& p : people) {
        int sum = p.first + p.second;
        metas[i].sum_ = sum;
        metas[i].idx_ = i;
        metas[i].current_k_ = p.second;
        ++i;
      }

      vector<pair<int, int>> out(people.size());

      for(i = 0; not metas.empty(); i++) {
        make_heap(metas.begin(), metas.end());
        pop_heap(metas.begin(), metas.end());
        auto p = people[metas.back().idx_];

        for(auto& meta : metas) {
          auto& o = people[meta.idx_];
          if(p.first >= o.first) {
            meta.sum_--;
            meta.current_k_--;
          }
        }
        out[i] = p;
        metas.pop_back();
      }

      return move(out);
    }
};
////////////////////////////////////////////////////////////////////////////////

int main()
{
  Solution s;
  vector<pair<int, int>> queue = {{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}};
  for(auto p : queue) {
    print(p);
  }
  cout << endl;
  for(auto p : s.reconstructQueue(queue)) {
    print(p);
  }
  cout << endl;
  return 0;
}
