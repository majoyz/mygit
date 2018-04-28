///
/// @file    rotate.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-28 23:22:15
///

#include <iostream>
#include <vector>
using namespace std;

class Solution {//超时啦！！！
	public:
		void rotate(vector<int>& nums, int k) {
			if(nums.empty()){
				return;
			}
			auto pruc = nums.begin();
			pruc++;
			if(pruc == nums.end()){
				return;
			}
			k %= nums.size();
			int tt=*nums.begin();
			int ttt;
			for(int t=k;t>0;t--){
				pruc = nums.begin()+1;
				while(pruc!=nums.end()){
					ttt=*pruc;
					*pruc=tt;
					tt=ttt;
					pruc++;
				}
				*nums.begin()=tt;
			}
			return;
		}
};

int main(){
	vector<int> nums{0,1,2,3,4,5,6,7};
	Solution s;
	s.rotate(nums,3);
	for(auto number : nums){
		cout << number << " ";
	}
	cout << endl;

	return 0;
}
