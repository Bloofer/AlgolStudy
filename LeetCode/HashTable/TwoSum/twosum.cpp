#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> twoSum_bruteforce(vector<int>& nums, int target) {
        vector<int> sums;
        for (int i = 0; i < nums.size()-1; i++) {
          for (int j = i+1; j < nums.size(); j++) {
            if(nums[i] + nums[j] == target) {
              sums.push_back(i);
              sums.push_back(j);
            }
          }
        }
        return sums;
    }

    vector<int> twoSum_hash(vector<int>& nums, int target) {
        map<int, int> maps;
        for (int i = 0; i < nums.size(); i++) {
          maps.insert(pair<int,int>(nums[i], i));
        }
        for (int i = 0; i < nums.size(); i++) {
          int complement = target - nums[i];
          if(maps.count(complement) && maps[complement] != i) return vector<int> {i, maps[complement]};
        }
        return vector<int> {};
    }

    vector<int> twoSum_onepass_hash(vector<int>& nums, int target) {
        map<int, int> maps;
        for (int i = 0; i < nums.size(); i++) {
          int complement = target - nums[i];
          if(maps.count(complement)) return vector<int> {i, maps[complement]};
          maps.insert(pair<int,int>(nums[i], i));
        }
        return vector<int> {};
    }
};
