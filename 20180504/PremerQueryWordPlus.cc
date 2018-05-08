 ///
 /// @file    PrimerQueryWordPlus.cc
 /// @author  majoyz(zmj-miss@live.com)
 /// @date    2018-04-25 15:27:43
 ///
 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
using namespace std;

string make_plural(int ctr,const string & word,const string &ending){
	return ctr==1? word:word+ending;//复数判断是否加s
}

class QueryResult;//query的返回类型

class TextQuery{//读入文件并构建一个查找图
	public:
		using line_no = vector<string>::size_type;
		TextQuery(ifstream&);
		QueryResult query(const string&) const;//接受要查询的单词，返回一个结果
	private:
		shared_ptr<vector<string>> _file; //输入文件
		//每个单词到它所在行号的集合的映射
		map<string,shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is)
: _file(new vector<string>)
{
	string text;
	while(getline(is,text)){//对文件中的每一行
		_file->push_back(text);//保存此行文本
		int n = _file->size()-1;//当前行号
		istringstream line(text);//将行文本分解为单词
		string word;
		while(line >> word){//对行重的每个单词
			auto &_lines = wm[word];//_lines是一个shared_ptr
			if(!_lines)//第一次遇到这个单词，指针为空
				_lines.reset(new set<line_no>);//分配一个新set
			_lines->insert(n);//将此行号插入set中
		}
	}
}

class QueryResult{//保存一个query操作的结果，将private里的三者保存起来
	friend ostream& print(ostream&,const QueryResult&);
	public:
		QueryResult(string s,
					shared_ptr<set<TextQuery::line_no>> p,
					shared_ptr<vector<string>> f)
		:_sought(s)
		,_lines(p)
		,_file(f){}

		set<TextQuery::line_no>::iterator begin(){return _lines->begin();}
		set<TextQuery::line_no>::iterator end(){return _lines->end();}
		shared_ptr<vector<string>> get_file(){return _file;}
	private:
		string _sought;//查询单词
		shared_ptr<set<TextQuery::line_no>> _lines;//出现的行号
		shared_ptr<vector<string>> _file;//输入文件
};

QueryResult TextQuery::query(const string &_sought) const//查询单词_sought
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(_sought);
	if(loc == wm.end())
		return QueryResult(_sought,nodata,_file);//如果没有的话出现的行号返回一个nodata的set
	else
		return QueryResult(_sought,loc->second,_file);//如果有的话返回对应的行号set
}

ostream &print(ostream & os,const QueryResult &qr){//打印QueryResult查询结果
	os << qr._sought << " occurs" << qr._lines->size() << " "
		<< make_plural(qr._lines->size(),"time","s") << endl;
	for(auto num:*qr._lines)
		os << "(line " << num + 1 << ") "
			<< *(qr._file->begin() + num) << endl;
	return os;
}

class Query_base{//抽象基类，每个表示具体查询的类都必须定义继承而来的纯虚函数eval和rep
	friend class Query;
	protected:
		using line_no = TextQuery::line_no;
		virtual ~Query_base() = default;//虚析构函数
	private:
		virtual QueryResult eval(const TextQuery&) const = 0;//虚eval，接受一个TextQuery对象并返回一个QueryResult
		virtual string rep() const = 0;//虚rep，返回基础查询的string表示形式
};

class Query{
	friend Query operator~(const Query &);//重载Query对象的三个运算符
	friend Query operator|(const Query&,const Query&);
	friend Query operator&(const Query&,const Query&);
public:
	Query(const string&);
	QueryResult eval(const TextQuery &t) const
	{return q->eval(t);}
	string rep() const
	{return q->rep();}
private:
	Query(shared_ptr<Query_base> query)
	:q(query)
	{}
	shared_ptr<Query_base> q;
};

ostream &operator<<(ostream &os,const Query &query){
	return os << query.rep() << endl;
}

class WordQuery
:public Query_base
{
	friend class Query;//Query使用WordQuery构造函数
	WordQuery(const string &s)
	:query_word(s){}
	QueryResult eval(const TextQuery &t) const//调用TextQuery的query进行实际查找
	{return t.query(query_word);}
	string rep() const {return query_word;}//普通查找的rep这样就可以
	string query_word;
};
inline
Query::Query(const string &s)
:q(new WordQuery(s)){}

class NotQuery
:public Query_base
{
	friend Query operator~(const Query &);
	NotQuery(const Query &q)
	:query(q){}
	string rep() const {return "~(" + query.rep() + ")";}//这里的rep开始有变化
	QueryResult eval(const TextQuery&) const;//具体定义在下面
	Query query;
};
inline Query operator~(const Query &operand)
{
	return shared_ptr<Query_base>(new NotQuery(operand));
}

class BianryQuery//没有定义eval，而是继承了该纯虚函数，也是一个抽象基类
:public Query_base{
protected:
	BianryQuery(const Query &l,const Query &r,string s)
	:lhs(l),rhs(r),opSym(s){}
	string rep() const {return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";}//不过定义了rep
	Query lhs,rhs;
	string opSym;
};

class AndQuery//继承了rep并定义了其他虚函数，是具体的类
:public BianryQuery{
	friend Query operator&(const Query&,const Query&);
	AndQuery(const Query &left,const Query &right)
	:BianryQuery(left,right,"&"){}
	QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs,const Query &rhs)
{
	return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

class OrQuery
:public BianryQuery{
	friend Query operator|(const Query&,const Query&);
	OrQuery(const Query &left,const Query &right)
	:BianryQuery(left,right,"|"){}
	QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs,const Query &rhs)
{
	return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const
{
	auto right = rhs.eval(text),left = lhs.eval(text);//调用正常查询的eval
	auto ret_lines = make_shared<set<line_no>>(left.begin(),left.end());//在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr
	ret_lines->insert(right.begin(),right.end());//或的话，直接把右单词的查询结果的set插入到左单词查询结果的set里
	return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const
{
	auto right = rhs.eval(text),left = lhs.eval(text);//调用正常查询的eval
	auto ret_lines = make_shared<set<line_no>>();//一个空的set？
	set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*ret_lines,ret_lines->begin()));//set容器的交集，stl自带
	return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult NotQuery::eval(const TextQuery & text) const
{
	auto result = query.eval(text);//调用正常查询的eval，结果为result
	auto ret_lines = make_shared<set<line_no>>();//搞一个空set？存放需要的not结果
	auto beg = result.begin(),end = result.end();
	auto sz = result.get_file()->size();//get_file返回的是文件的vector，size是行数来着吧
	for(size_t n=0;n != sz;++n){//对总行数进行遍历
		if(beg == end||*beg!=n)//如果正常查询结果遍历完了（那就剩下的每行都insert）或者该行不在正常查询结果中（插入该行）
			ret_lines->insert(n);
		else if(beg != end)//遍历到正常查询结果的这个了，但是属于正常查询结果的还没遍历完，插入下一个正常查询结果之前的到反向结果里
			++beg;
	}
	return QueryResult(rep(),ret_lines,result.get_file());
}

int main(){

	ifstream mytext("china_daily.txt");
	TextQuery myfile(mytext);
	Query q = Query("the") & Query("as") | Query("Beijing");
	const auto result = q.eval(myfile);
	cout << "Executing Query for:" << q << endl;
	print(cout,result) << endl;

	return 0;
}
