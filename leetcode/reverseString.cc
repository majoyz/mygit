///
/// @file    reverseString.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-04-28 21:03:43
///

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

class Solution {
	public:
		string reverseString(string s) {
			string result = "";
			for (int i = s.length() - 1; i >= 0; --i) {
				result += s[i];
			}
			return result;
		}
};

int main(){
	string s="Trap a rat! Stare piper at Star apart.";
	string ss;
	Solution cs;
	ss = cs.reverseString(s);
	cout << s << endl;
	cout << ss << endl;

	return 0;
}
