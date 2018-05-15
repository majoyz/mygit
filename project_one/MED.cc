///
/// @file    MED.cc
/// @author  majoyz(zmj-miss@live.com)
/// @date    2018-05-14 10:05:12
///

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int mymin(int a,int b,int c){
	if(a<=b&&a<=c)
		return a;
	else if(b<=a&&b<=c)
		return b;
	else
		return c;
}

int getmed(int tsize,int ssize,string &target,string &source){
	if(tsize == 0)
		return ssize;
	else if(ssize == 0)
		return tsize;
	return mymin(getmed(tsize-1,ssize,target,source)+1
			,getmed(tsize-1,ssize-1,target,source)+(target[tsize-1]==source[ssize-1]?0:2)
			,getmed(tsize,ssize-1,target,source)+1);
}

int Min_Edit_Distance(string target,string source){
	int tsize = target.size();
	int ssize = source.size();
	int ret = getmed(tsize,ssize,target,source);
	return ret;
}

int main(){
	//测试最小编辑距离函数
	string source = "iphoe";
	string target1= "xiphoe";
	string target2= "myphoe";
	string target3= "xphoe";
	string target4= "iphones";
	vector<string> strings;
	strings.push_back(target1);
	strings.push_back(target2);
	strings.push_back(target3);
	strings.push_back(target4);
	for(auto it : strings){
		int ret = Min_Edit_Distance(it,source);
		cout << it << " : " << ret << endl;
	}
	return 0;
}
