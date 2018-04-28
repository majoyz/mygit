///
/// @file    removeDuplicates.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-28 22:34:44
///

#include <iostream>
#include <vector>
using namespace std;

class Solution {
	public:
		int removeDuplicates(vector<int>& nums) {
			if(nums.empty())
				return 0;
			auto pruc = nums.begin();
			pruc++;
			auto pre = nums.begin();
			auto newone = nums.begin();
			int len = 0;
			while(pre != nums.end()){
				if(pruc == nums.end()){
					*newone = *pre;
					return len+1;
				}else if(*pre!=*pruc){
					*newone = *pre;
					++pre;
					++newone;
					++pruc;
					++len;
				}else{
					++pruc;
					++pre;
				}
			}
			return -1;
		}
};
#if 0
class Solution {
	public:
		int removeDuplicates(vector<int>& nums) {
			int i = 0;
			for (int n : nums)
				if (!i || n > nums[i-1])
					nums[i++] = n;
			return i;

		}
};
#endif
int main(){
	vector<int> nums{-1,0,0,0,0,3,3};
	Solution num;
	int n = num.removeDuplicates(nums);
	cout << n << endl;
	for(int i=0;i<n;++i){
		cout << nums[i] << " ";
	}
	cout << endl;

	return 0;
}
