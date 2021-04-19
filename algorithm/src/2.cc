#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <stdlib.h>
#include <rlib/stdio.hpp>
using namespace std;
string num_to_string(int intV) //int转string型
{
	string result;
	stringstream stream;
	stream << intV;
	stream >> result;
	return result;
}
int string_to_num(string stringV) //string转int型
{
	int result;
	stringstream instr(stringV);
	instr>>result;
	return result;
}
string BeforeZero(string num, int j) //在数字前补j个0
{
	int i;
	for(i = 0;i < j; i++)
	{
		num.insert(0,"0");
	}
	return num;
}
string FollowZero(string num, int j) //在数字后面补j个0
{
	int i;
	for(i = 0; i < j ;i++)
	{
		num.insert(num.size(),"0");
	}
	return num;
}
string SubNum(string num1, string num2) //大数减法
{
	while(num1[0] == '0'&&num1.size()>1) num1 = num1.substr(1,num1.size()-1);
	while(num2[0] == '0'&&num2.size()>1) num2 = num2.substr(1,num2.size()-1);
	int sign = 1;
	if(num1.size()>num2.size())
	{
		num2 = BeforeZero(num2,num1.size()-num2.size());
	}
	else if(num1.size()<num2.size())
	{
		sign = 0;
		num1 = BeforeZero(num1,num2.size()-num1.size());
	}
	else
	{
		for(int x = 0;x<num1.size()&&sign==1;x++)
		{
			if(num1[x]>num2[x]) break;
			else if(num1[x]<num2[x]) sign = 0;
		}
	}
	string sub;
	int i, lend = 0, r;
	if(sign == 1)
	{
		for(i = num1.size()-1;i>=0;i--)
		{
			r = num1[i]-lend-num2[i];
			if(r < 0)
			{
				r+=10;
				lend = 1;
			}
			else lend = 0;
			sub.insert(0,num_to_string(r));
		}
		while(sub[0]=='0'&&sub.size()>1)
			sub = sub.substr(1,sub.size()-1);
	}
	else if(sign == 0)
	{
		for(i = num1.size()-1;i>=0;i--)
		{
			r = num2[i]-lend-num1[i];
			if(r < 0)
			{
				r+=10;
				lend = 1;
			}
			sub.insert(0,num_to_string(r));
		}
		while(sub[0]=='0'&&sub.size()>1)
			sub = sub.substr(1,sub.size()-1);
		sub.insert(0,"-");
	}
	return sub;
}
string AddNum(string num1, string num2) //大数加法
{
	while(num1[0] == '0'&&num1.size()>1) num1 = num1.substr(1,num1.size()-1);
	while(num2[0] == '0'&&num2.size()>1) num2 = num2.substr(1,num2.size()-1);
	if(num1[0]=='-')
	{
		num1 = num1.substr(1,num1.size()-1);
		return SubNum(num2,num1);
	}
	else if(num2[0]=='-')
	{
		num2 = num2.substr(1,num2.size()-1);
		return SubNum(num1,num2);
	}
	if(num1.size()>num2.size()) num2 = BeforeZero(num2,num1.size()-num2.size());
	else if(num1.size()<num2.size()) num1 = BeforeZero(num1,num2.size()-num1.size());
	
	string add;
	int i, in = 0, r;
	for(i = num1.size()-1;i>=0;i--)
	{
		r = num1[i]-'0'+num2[i]-'0'+in;
		in = r/10;
		r = r%10;
		add.insert(0,num_to_string(r));
	}
	if(in != 0) add.insert(0,num_to_string(in));
	return add;
}
string MultNum(string num1, string num2) //大数乘法
{
	while(num1[0] == '0'&&num1.size()>1) num1 = num1.substr(1,num1.size()-1);
	while(num2[0] == '0'&&num2.size()>1) num2 = num2.substr(1,num2.size()-1);
	int sign=1;
	if(num1[0]=='-')
	{
		sign-=1;
		num1 = num1.substr(1,num1.size()-1);
	}
	if(num2[0]=='-')
	{
		sign-=1;
		num2 = num2.substr(1,num2.size()-1);
	}
	int f = 2;
	if(num1.size()>=num2.size())
	{
		while(num1.size()>f) f*=2;
		if(num1.size() !=f)
		{
			num1 = BeforeZero(num1,f-num1.size());
		}
		num2 = BeforeZero(num2,f-num2.size());
	}
	else
	{
		while(num2.size()>f) f*=2;
		if(num2.size() !=f)
		{
			num2 = BeforeZero(num2,f-num2.size());
		}
		num1 = BeforeZero(num1,f-num1.size());
	}
	int length = num1.size();
	string h1, l1, h2, l2, result;
	if(length > 1)
	{
		h1 = num1.substr(0,length/2);
		l1 = num1.substr(length/2,length/2);
		h2 = num2.substr(0,length/2);
		l2 = num2.substr(length/2,length/2);
		//cout<<h1<<' '<<l1<<' '<<h2<<' '<<l2<<endl;
	}
	if(length == 2){
		int na = string_to_num(h1);
		int nb = string_to_num(l1);
		int nc = string_to_num(h2);
		int nd = string_to_num(l2);
		result = num_to_string((na*10+nb)*(nc*10+nd));
	}
	else
	{
		string ac = MultNum(h1,h2);    //a*c
		string a_b = AddNum(h1,l1);    //a+b
		string d_c = AddNum(l2,h2);    //c+d
		string a_bd_c = MultNum(a_b,d_c);  //(a+b)*(c+d)
		string bd = MultNum(l1,l2);    //b*d
		string ac_bd = AddNum(ac,bd);  //a*c+b*d
		string r1 = FollowZero(ac,length);  //a*c*10^length
		string r0 = SubNum(a_bd_c,ac_bd);
		string r2 = FollowZero(r0,length/2);
		result = AddNum(r1,AddNum(r2,bd));
	}
	if(sign==0) result.insert(0,"-");
	return result;
}
int main()
{
    auto line = rlib::scanln();
    auto op = 'E';
    auto op_func = &::AddNum;
    if(line.find('+') != std::string::npos) {
        op = '+';
        op_func = &::AddNum;
    }
    if(line.find('-') != std::string::npos) {
        op = '-';
        op_func = &::SubNum;
    }
    if(line.find('*') != std::string::npos) {
        op = '*';
        op_func = &::MultNum;
    }
    auto operands = line.split(op);
    if(operands.size() != 2)
        throw std::invalid_argument("Format: num1 op num2");
    auto result = op_func(operands[0].strip(), operands[1].strip());
    rlib::println(result);
    return 0;
}
