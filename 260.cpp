#include <vector>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
class Solution {
  public:
    vector<int> singleNumber(vector<int>& nums) {
      int xx = 0;
      int x1 = 0;
      int x2 = 0;
      int mask = 1;
      for(auto n : nums) xx ^= n;
      while((xx & mask) == 0) mask <<= 1;
      for(auto n : nums) 
        if(n & mask) x1 ^= n;
        else x2 ^= n;

      return vector<int>{x1, x2};
    }
};
////////////////////////////////////////////////////////////////////////////////

int main()
{
  Solution s;
  vector<int> nums = {9, 9, 3, 7};
  for(auto x : s.singleNumber(nums)) {
    cout << x << ' ';
  }
  cout << endl;

  return 0;
}
