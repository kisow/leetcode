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
      int h_;
      int idx_;
      int current_k_;
      Meta() {}
      bool operator<(auto& o) const {
        if(current_k_ == o.current_k_) return h_ > o.h_;
        else return current_k_ > o.current_k_; 
      }
    };

    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
      vector<Meta> metas(people.size());

      int i = 0;
      int min = 0;
      for(auto& p : people) {
        metas[i].idx_ = i;
        metas[i].h_ = p.first;
        metas[i].current_k_ = p.second;
        if(metas[min] < metas[i]) min = i;
        ++i;
      }

      vector<pair<int, int>> out(people.size());

      for(i = 0; not metas.empty(); i++) {
        auto p = people[metas[min].idx_];
        swap(metas[min], metas.back());
        out[i] = p;
        metas.pop_back();

        min = 0;
        int j = 0;
        for(auto& meta : metas) {
          auto& o = people[meta.idx_];
          if(p.first >= o.first) {
            meta.current_k_--;
          }
          if(metas[min] < meta) min = j;
          j++;
        }
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
