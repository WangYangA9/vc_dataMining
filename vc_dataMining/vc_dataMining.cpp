// vc_dataMining.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

double stringToDouble(const string str)
{
	istringstream ss(str);
	double d;
	ss>>d;
	//	cout<<str<<" "<<d<<endl;
	return d;
}

//强窄 、强宽 、强特宽 、较强窄 、较强宽 、较强特宽 、较弱窄 、较弱宽 、较弱特宽 、弱窄 、弱宽 、弱特宽 
// 1      2       3       4         5         6         7        8         9        10     11      12
//峰强*3+峰宽  的整数值，即为一维值
int FengQiangZhuanHuan(const double fengQiang)
{
	int result;
	if(fengQiang >= 5)//强
		result = 0;
	else if(fengQiang >= 1)//较强
		result = 1;
	else if(fengQiang >= 0.5)//较弱
		result = 2;
	else //弱
		result = 3;
	return result;
}

int FengKuanZhuanHuan(const int fengKuan)
{
	int result;
	if(fengKuan < 5)//窄
		result = 1;
	else if(fengKuan < 10)//宽
		result = 2;
	else  //特宽
		result = 3;
	return result;
}

//下面是化学性质的转换
int WenduZhuanhuan(double wendu)
{
	return (wendu-1500)/500;
}
int GuangduZhuanhuan(double guangdu)
{
	int result = 0;
	if(guangdu >= 3.6 && guangdu <=4.1)
		result = 5;
	else if(guangdu >= 2.6)
		result = 4;
	else if(guangdu >= 1.1)
		result = 3;
	else if(guangdu >= 0)
		result = 2;
	else if(guangdu >= -1)
		result = 1;
	return result;
}
int HuaxuefengduZhuanhuan(double huanxuefengdu)
{
	int result = 0;
	if(huanxuefengdu >= 0.3 && huanxuefengdu <=0.7)
		result = 5;
	else if(huanxuefengdu >= -0.1)
		result = 4;
	else if(huanxuefengdu >= -0.5)
		result = 3;
	else if(huanxuefengdu >= -3)
		result = 2;
	else if(huanxuefengdu >= -5)
		result = 1;
	return result;
}
int WeituanliuZhuanhuan(double weituanliu)
{
	int result;
	if (weituanliu >= 1)
	{
		result = 2;
	} 
	else
	{
		result = 1;
	}
	return result;
}

int mhZhuanhuan(double mh, double maxMH,double minMH)
{
	int result;
	if(mh >= (maxMH+minMH)/2)
		result = 1;
	else result = 2;

	return result;
}

//待定根据温度生成 O 25000  B  11000  A  7500  F  6000  G  5000  K  3500  M  
int DaidingZhuanhuan(double wendu)
{
	int result;
	if(wendu >= 25000)
		result = 1;
	else if(wendu >= 11000)
		result = 2;
	else if(wendu >= 7500)
		result = 3;
	else if(wendu >= 6000)
		result = 4;
	else if(wendu >= 5000)
		result = 5;
	else if(wendu >= 3500)
		result = 6;
	else
		result = 7;
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<vector<double> >  data;//用来存放数据的结构
	vector<map<int, int> > dataResult;
	const int startWavelength = 3810;
	ifstream in("带有物理属性的光谱数据8000.txt", ios::in);//打开文件

	//============================================
	//读取文件
	string str;//用来存放读出的每一行数据


	while(!in.eof())//如果文件没有读取完毕
	{
		getline(in, str, '\n');//读取一行数据
		vector<double> dataLine;
		int endPos = 0;
		int breakPos = str.find_last_of(',',0);
		for(unsigned int i = 0;i<str.size();i++)
		{
			endPos = str.find(',', i);
			//cout<<str.substr(i, endPos-i-1)<<endl;
			dataLine.push_back(stringToDouble(str.substr(i, endPos-i-1)));
			//            cout<<str.substr(i, endPos-i-1)<<"  "<<stringToDouble(str.substr(i, endPos-i-1))<<endl;
			i = endPos+1;
			if(endPos == breakPos) break;
		}
		//        for(unsigned int i = 0;i<dataLine.size();i++)
		//            cout<<dataLine.at(i);
		//        cout<<endl;
		data.push_back(dataLine);//将改行数据加入到data
	}
	//==================================================================
	//使用中值滤波进行离散化处理  7个数字一组
	double maxMH = data[0][205],minMH = data[0][205];//所有MH值的最大最小值

	for(unsigned int i = 0;i<data.size();i++)
	{
		//用来读取已经从文件读出来的函数
		vector<double>::iterator lineNumIt = data[i].begin();
		if(lineNumIt[205] > maxMH)
			maxMH = lineNumIt[205];
		if(lineNumIt[205] < minMH)
			minMH = lineNumIt[205];

		for(unsigned int j = 1;j < 201;j++)
		{
			vector<double> sortVector;
			for(unsigned int k = 0;k<7;k++)
			{
				sortVector.push_back(lineNumIt[j+k]);
			}
			sort(sortVector.begin(), sortVector.end());
			double midValue = sortVector.at(3);//7个数字的中值
			if(j == 194)//最后几个数据一下处理了
			{
				for(unsigned int k = 0;k<7;k++)
				{
					lineNumIt[j+k] = lineNumIt[j+k]/midValue;
				}
				break;
			}
			else
			{
				lineNumIt[j] = lineNumIt[j]/midValue;
			}
		}
		for(unsigned int l = 1;l<data[i].size();l++)
		{
			cout<<lineNumIt[l]<<",";
		}
		cout<<endl;
	}
	//while(1);
	//==================================================================
	//开始计算波峰波谷
	for(unsigned int i = 0;i<data.size();i++)
	{
		vector<double> lineNum = data[i];//用来读取已经从文件读出来的函数
		map<int,int> singleNum;
		for(unsigned int j = 2;j<200;j++)//第2到199个数据，第0位是每行的行号
		{//第一个点算不算波峰波谷
			//cout<<"["<<lineNum[j-1]<<"|"<<lineNum[j]<<"|"<<lineNum[j+1]<<"波峰或波谷]:";
			int waveLength = startWavelength +20*(j-1);
			if(lineNum[j] > lineNum[j-1])
			{
				if(lineNum[j] > lineNum[j+1])
				{
					//cout<<"波峰"<<lineNum[j];
					singleNum.insert(pair<int,int>(waveLength,FengQiangZhuanHuan(lineNum[j])));//3810表示波峰
				}
			}
			else //lineNum[j] < lineNum[j-1]
			{
				if(lineNum[j] < lineNum[j+1])
				{
					//cout<<"波谷"<<lineNum[j];
					singleNum.insert(pair<int,int>(waveLength+1,FengQiangZhuanHuan(lineNum[j])));//3811表示波谷
				}
			}

		}
		//for(unsigned int l = 1;l<singleNum.size();l++)
		//{
		//	cout<<singleNum.at(l)<<",";
		//}
		//cout<<endl;
		dataResult.push_back(singleNum);
		//cout<<"入栈成功\n";
	}
	//以波峰为基准点，获得峰宽（后一个波谷的位置-当前波峰的位置），得到二维数据，并转换成1维数据
	for(unsigned int i = 0;i<dataResult.size();i++)
	{
		//cout<<"第"<<i+1<<"行数据-----------------------------------------------------\n";
		//用来读取已经从文件读出来的函数
		map<int, int>::iterator lineNumIt;
		for(lineNumIt = dataResult[i].begin();lineNumIt != dataResult[i].end(); )
		{
			//cout<<lineNumIt->first<<"+"<<lineNumIt->second<<endl;//输出处理的数据
			if(lineNumIt->first % 10 == 0)//如果这个数据是波峰
			{
				map<int, int>::iterator lineNumIt_next = lineNumIt;//下一个数据的的指针
				lineNumIt_next++;
				if(lineNumIt_next == dataResult[i].end()) 
					break;//如果下一个数据不存在（即本个波峰数据后面没有数据了，就没有办法算峰宽了）
				lineNumIt->second = lineNumIt->second*3+FengKuanZhuanHuan((lineNumIt_next->first-1-lineNumIt->first)/20);//直接将二维值转换成一维值
				//cout<<lineNumIt_next->first<<"-"<<lineNumIt->first<<" = "<<lineNumIt_next->first-lineNumIt->first<<endl;;
				//cout<<"处理后："<<lineNumIt->first<<"+"<<lineNumIt->second<<endl;
				lineNumIt++;//指针++
			}
			else
			{
				lineNumIt = dataResult[i].erase(lineNumIt);//删除波谷数据，并更新指针
			}
		}
	}

	//按行写入文件
	ofstream file;

	file.open("file.txt");		

	for(unsigned int i = 0;i<dataResult.size();i++)
	{
		//cout<<"第"<<i+1<<"行数据-----------------------------------------------------\n";
		vector<double> outToFile;
		for(int temp = 0;temp<208;temp++)
		{
			outToFile.push_back((startWavelength+temp*20)*100);//所有元素置0
		}
		outToFile[0] = i+1;//行号
		outToFile[201] = 201*100+WenduZhuanhuan(data[i][201]);
		outToFile[202] = 202*100+GuangduZhuanhuan(data[i][202]);
		outToFile[203] = 203*100+HuaxuefengduZhuanhuan(data[i][203]);
		outToFile[204] = 204*100+WeituanliuZhuanhuan(data[i][204]);
		outToFile[205] = 205*100+mhZhuanhuan(data[i][205],maxMH,minMH);
		outToFile[206] = 206*100+DaidingZhuanhuan(data[i][201]);
		outToFile[207] = 207*100+data[i][207];
		//用来读取已经从文件读出来的函数
		map<int, int>::iterator lineNumIt;
		for(lineNumIt = dataResult[i].begin();lineNumIt != dataResult[i].end(); lineNumIt++)
		{
			int first = (lineNumIt->first-startWavelength)/20+1;
			outToFile[first] += lineNumIt->second;
		}
		for(unsigned int l = 1;l<outToFile.size();l++)
		{
			//cout<<outToFile.at(l)<<",";
			file<<outToFile.at(l)<<" ";
		}
		file<<"\n";
	}
	file.close();

	return 0;
}