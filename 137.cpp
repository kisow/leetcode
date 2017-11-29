#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
class Solution {
  public:
    int singleNumber(vector<int>& nums) {
      /* x\hl 00 01 10
       * 0    00 01 10
       * 1    01 10 00
       *
       * h = l & x | h & ~x
       * l = ~h & (l ^ x)
       */

      int h = 0;
      int l = 0;
      for(auto x : nums) {
        int hh = l & x | h & ~x;
        int ll = ~h & (l ^ x);
        h = hh;
        l = ll;
      }
      return l;
    }
};
////////////////////////////////////////////////////////////////////////////////

int main()
{
  Solution s;
  vector<int> nums = {9, 9, 9, 7};
  cout << s.singleNumber(nums) << endl;

  return 0;
}
