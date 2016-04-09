#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#include "fun.h"

map <int, int> swap(map <int, int> tabl, int n,int m)
{
	for (int i = 0; i<n*m; i++)
		swap(tabl[i], tabl[rand() % (n*m)]);// генерируем таблицу замены
	return tabl;
}

map <int, int> generate_tabl(int n, int m)
{
	map <int, int> a;
	for (int i = 0; i<n*m; i++)
		a[i] = i;
	return a;
}

vector <int> generate_key(int n, int m, int j)
{
	vector <int> key;
	int r;
	for (int i = 0; i<n*m*j; i++) //Генерируем ключ
	{
		r = rand() % 2; //собственно сгенерировали число, взяли остаток от деления на 2 (хз верно или нет)
		key.push_back(r);// запихиваем в массив
	}
	return key;
}

vector <vector<int>> sub(vector<int> key, int n, int m, int j)
{
	vector <vector <int>> sub_key;
	int counter = 0;

	sub_key.resize(j); // без этого не работает (??!??!!!)
	for (int i = 0; i<n; i++)// В цикле от 1 до n (n штук)
	{
		sub_key[i].resize(n*m);
		for (int k = 0; k<n*m; k++) // В цикле от 1 до m (размер m)
		{
			sub_key[i].push_back(key[counter]);
			counter++;
		}
	}
	return sub_key;
}

int Counter_Bits(vector <string> &text)
{
	int count = 0;
	for (int i = 0; i < (int)text.size(); i++)
	{
		for (int j = 0; j < (int)text[i].size(); j++)
		{
			unsigned int temp = text[i][j];
			while (temp != 0)
			{
				temp = temp >> 1;
				count++;
			}
		}
	}
	return count;
}

string Random_Bits(int m)
{
	string str;
	for (int i = 0; i < m; i++)
	{
		char temp = rand() % 2 + '0';
		str = str + temp;
	}
	return str;
}

vector <string> Random_sbox(int m)
{
	vector <string> temp_table;

	for (int i = 0; i < (int)pow(2.0, (double)m); i++)
	{
		int k = i;
		string str;
		for (int j = 0; j < m; j++)
		{
			char temp = k % 2 + '0';
			str = str + temp;
			k = k / 2;
		}

		temp_table.push_back(str);
	}
	random_shuffle(begin(temp_table), end(temp_table));
	return temp_table;
}

map <string, string> generate_sbox(int m)
{
	map <string, string> table;
	int k;

	for (int i = 0; i < (int) pow(2.0, (double) m); i++)
	{
		k = i;
		string str;
		for (int j = 0; j < m; j++)
		{
			char temp = k % 2 + '0';
			str = str + temp;
			k = k / 2;
		}
		table[str] = str;
	}
	return table;
}

map <string, string> generate_tabl_mix (map <string, string> sblock, int m)
{
	vector <string> temp = Random_sbox(m);
	int i = 0;//Счетчик, чтобы обойти вектор
	map <string,string> :: iterator it;//Счетчик, чтобы обойти map
	for (it=sblock.begin();it!=sblock.end();it++)
	{
		(*it).second = temp[i];
		i++;
	}
	return sblock;
}

vector <string> sub_str_blok (string str, int m)
{
	vector <string> blok;
	char alpha;

	for (int i=0;i<str.size();)
	{
		string sub;
		for (int j=0;j<m;j++)
		{
			alpha=str[i];
			sub=sub+alpha;
			i++;
		}
		blok.push_back(sub);
	}
	return blok;
}
