#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#include "fun.h"

string XOR (vector <vector <string>> hs, map<int,int> p_box, vector< vector<int>> sub_key, int j)
{
	string answer;

	for (int i=0;i<hs.size();i++)//по всем возможным блокам из (n блоков по m элементов)
	{
		string str;//Сохраняем сюда целую строчку (склеиваем из s-blok)
		char alpha,betta;//созданы для удобства понимания кода. И чтобы не громоздить скобки

		for (int k=0;k<j;k++)//j раундов
		{
			for (int h=0;h<hs[i].size();h++)//Склеиваем строку (n блоков склеиваем вместе)
				str=str+hs[i][h];
			for (int h=0;h<str.size();h++)//делаем XOR char-ов
			{
				int r = sub_key[i][		p_box[h]	];//берем значение из sub_key из j-ого (какой раунд) и согласно таблице замены элемент под номером h
				betta=r+'0';
				alpha=((str[h]) ^ (betta));//сам xor
				answer=answer+alpha;//добавляем букву
			}
		}
	}
	return answer;
}

vector <vector <string>> sub_str_blok (string str, int n, int m)
{
	//!!
	//в функции не рассматриваю, когда не влезает целиком sblok. То есть n=3,m=3, длина текста 17
	vector <vector <string>> blok;
	char alpha;

	for (int i=0;i<str.size();)
	{
		vector <string> oops;
		for (int j=0;j<n;j++)//отмеряем n штук блоков
		{
			string sub;
			for (int k=0;k<m;k++)//отмеряем m штук символов
			{
				alpha=str[i];
				sub=sub+alpha;
				i++;
			}
			oops.push_back(sub);
		}
		blok.push_back(oops);
	}
	return blok;
}

vector <vector <string>> use_s_box (vector <vector <string>> hs, map <string,string> sbox)
{
	string str;
	for(int i=0;i<hs.size();i++)
		for (int j=0;j<hs[i].size();j++)
		{
			str=hs[i][j];
			hs[i][j]=sbox[str];
		}
	return hs;
}

string generate_text (int n, int m)
{
	string str;
	char alpha;
	int r;
	for (int i=0;i<n*m;i++)
	{
		r=rand()%2;
		alpha=r+'0';
		str=str+alpha;
	}
	return str;
}

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
