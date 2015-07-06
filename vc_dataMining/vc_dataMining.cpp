// vc_dataMining.cpp : �������̨Ӧ�ó������ڵ㡣
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

//ǿխ ��ǿ�� ��ǿ�ؿ� ����ǿխ ����ǿ�� ����ǿ�ؿ� ������խ �������� �������ؿ� ����խ ������ �����ؿ� 
// 1      2       3       4         5         6         7        8         9        10     11      12
//��ǿ*3+���  ������ֵ����Ϊһάֵ
int FengQiangZhuanHuan(const double fengQiang)
{
	int result;
	if(fengQiang >= 5)//ǿ
		result = 0;
	else if(fengQiang >= 1)//��ǿ
		result = 1;
	else if(fengQiang >= 0.5)//����
		result = 2;
	else //��
		result = 3;
	return result;
}

int FengKuanZhuanHuan(const int fengKuan)
{
	int result;
	if(fengKuan < 5)//խ
		result = 1;
	else if(fengKuan < 10)//��
		result = 2;
	else  //�ؿ�
		result = 3;
	return result;
}

//�����ǻ�ѧ���ʵ�ת��
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

//���������¶����� O 25000  B  11000  A  7500  F  6000  G  5000  K  3500  M  
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
	vector<vector<double> >  data;//����������ݵĽṹ
	vector<map<int, int> > dataResult;
	const int startWavelength = 3810;
	ifstream in("�����������ԵĹ�������8000.txt", ios::in);//���ļ�

	//============================================
	//��ȡ�ļ�
	string str;//������Ŷ�����ÿһ������


	while(!in.eof())//����ļ�û�ж�ȡ���
	{
		getline(in, str, '\n');//��ȡһ������
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
		data.push_back(dataLine);//���������ݼ��뵽data
	}
	//==================================================================
	//ʹ����ֵ�˲�������ɢ������  7������һ��
	double maxMH = data[0][205],minMH = data[0][205];//����MHֵ�������Сֵ

	for(unsigned int i = 0;i<data.size();i++)
	{
		//������ȡ�Ѿ����ļ��������ĺ���
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
			double midValue = sortVector.at(3);//7�����ֵ���ֵ
			if(j == 194)//��󼸸�����һ�´�����
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
	//��ʼ���㲨�岨��
	for(unsigned int i = 0;i<data.size();i++)
	{
		vector<double> lineNum = data[i];//������ȡ�Ѿ����ļ��������ĺ���
		map<int,int> singleNum;
		for(unsigned int j = 2;j<200;j++)//��2��199�����ݣ���0λ��ÿ�е��к�
		{//��һ�����㲻�㲨�岨��
			//cout<<"["<<lineNum[j-1]<<"|"<<lineNum[j]<<"|"<<lineNum[j+1]<<"����򲨹�]:";
			int waveLength = startWavelength +20*(j-1);
			if(lineNum[j] > lineNum[j-1])
			{
				if(lineNum[j] > lineNum[j+1])
				{
					//cout<<"����"<<lineNum[j];
					singleNum.insert(pair<int,int>(waveLength,FengQiangZhuanHuan(lineNum[j])));//3810��ʾ����
				}
			}
			else //lineNum[j] < lineNum[j-1]
			{
				if(lineNum[j] < lineNum[j+1])
				{
					//cout<<"����"<<lineNum[j];
					singleNum.insert(pair<int,int>(waveLength+1,FengQiangZhuanHuan(lineNum[j])));//3811��ʾ����
				}
			}

		}
		//for(unsigned int l = 1;l<singleNum.size();l++)
		//{
		//	cout<<singleNum.at(l)<<",";
		//}
		//cout<<endl;
		dataResult.push_back(singleNum);
		//cout<<"��ջ�ɹ�\n";
	}
	//�Բ���Ϊ��׼�㣬��÷����һ�����ȵ�λ��-��ǰ�����λ�ã����õ���ά���ݣ���ת����1ά����
	for(unsigned int i = 0;i<dataResult.size();i++)
	{
		//cout<<"��"<<i+1<<"������-----------------------------------------------------\n";
		//������ȡ�Ѿ����ļ��������ĺ���
		map<int, int>::iterator lineNumIt;
		for(lineNumIt = dataResult[i].begin();lineNumIt != dataResult[i].end(); )
		{
			//cout<<lineNumIt->first<<"+"<<lineNumIt->second<<endl;//������������
			if(lineNumIt->first % 10 == 0)//�����������ǲ���
			{
				map<int, int>::iterator lineNumIt_next = lineNumIt;//��һ�����ݵĵ�ָ��
				lineNumIt_next++;
				if(lineNumIt_next == dataResult[i].end()) 
					break;//�����һ�����ݲ����ڣ��������������ݺ���û�������ˣ���û�а취�����ˣ�
				lineNumIt->second = lineNumIt->second*3+FengKuanZhuanHuan((lineNumIt_next->first-1-lineNumIt->first)/20);//ֱ�ӽ���άֵת����һάֵ
				//cout<<lineNumIt_next->first<<"-"<<lineNumIt->first<<" = "<<lineNumIt_next->first-lineNumIt->first<<endl;;
				//cout<<"�����"<<lineNumIt->first<<"+"<<lineNumIt->second<<endl;
				lineNumIt++;//ָ��++
			}
			else
			{
				lineNumIt = dataResult[i].erase(lineNumIt);//ɾ���������ݣ�������ָ��
			}
		}
	}

	//����д���ļ�
	ofstream file;

	file.open("file.txt");		

	for(unsigned int i = 0;i<dataResult.size();i++)
	{
		//cout<<"��"<<i+1<<"������-----------------------------------------------------\n";
		vector<double> outToFile;
		for(int temp = 0;temp<208;temp++)
		{
			outToFile.push_back((startWavelength+temp*20)*100);//����Ԫ����0
		}
		outToFile[0] = i+1;//�к�
		outToFile[201] = 201*100+WenduZhuanhuan(data[i][201]);
		outToFile[202] = 202*100+GuangduZhuanhuan(data[i][202]);
		outToFile[203] = 203*100+HuaxuefengduZhuanhuan(data[i][203]);
		outToFile[204] = 204*100+WeituanliuZhuanhuan(data[i][204]);
		outToFile[205] = 205*100+mhZhuanhuan(data[i][205],maxMH,minMH);
		outToFile[206] = 206*100+DaidingZhuanhuan(data[i][201]);
		outToFile[207] = 207*100+data[i][207];
		//������ȡ�Ѿ����ļ��������ĺ���
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