///
/// @file    testmd.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-19 11:59:08
///

#include <iostream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <hiredis/hiredis.h>//redis C接口库
using namespace std;

int edit_length(string &x, string &y){ //秒查的最小编辑距离算法 
	int xlen = x.length();  
	int ylen = y.length();  
	int edit[xlen+1][ylen+1];  
	memset(edit, 0, sizeof(edit));  

	int i = 0;  
	int j = 0;  
	for(j = 0; j <= ylen; j++){  
		edit[0][j] = j;  
	}  
	for(i = 1; i <= xlen; i++){  
		edit[i][0] = edit[(i-1)][0] + 1;  
		for(j = 1; j <= ylen; j++){  
			if (x[i-1] == y[j-1]) {  
				edit[i][j] = min(min(edit[i][j-1] + 1, edit[(i-1)][j] + 1),  
						edit[(i-1)][j-1]);  
			} else {  
				if(i >= 2 && j >= 2 && x[i-2] == y[j-1] && x[i-1] == y[j-2]){  
					edit[i][j] = min(min(edit[i][j-1] + 1, edit[(i-1)][j] + 1),  
							min(edit[(i-1)][j-1] + 1, edit[(i-2)][j-2] + 1));  
				} else {  
					edit[i][j] = min(min(edit[i][j-1] + 1, edit[(i-1)][j] + 1),  
							edit[(i-1)][j-1] + 1);  
				}  
			}  
		}  
	}  
	return edit[(i-1)][j-1];  
}

int main(){
	string lhs = "pone";
	string rhs = "pnoe";
	int ret = edit_length(lhs,rhs);
	cout << lhs << "----" << rhs << "----" << ret << endl;
	return 0;
}
