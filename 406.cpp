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
    vector<int> cks_;
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
      cks_.resize(people.size());

      auto cmp = [&](auto& x, auto& y) {
        if(cks_[x] == cks_[y]) return people[x].first > people[y].first;
        else return cks_[x] > cks_[y]; 
      };

      int i = 0;
      int min = 0;
      for(auto& p : people) {
        cks_[i] = p.second;
        if(cmp(min, i)) min = i;
        ++i;
      }

      for(i = 0; i < people.size(); i++) {
        auto p = people[min];
        swap(cks_[i], cks_[min]);
        swap(people[i], people[min]);

        min = i + 1;
        for(int j = i + 1; j < cks_.size(); j++) {
          auto& o = people[j];
          if(p.first >= o.first) cks_[j]--;
          if(cmp(min, j)) min = j;
        }
      }

      return move(people);
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
