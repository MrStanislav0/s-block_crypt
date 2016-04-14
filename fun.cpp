#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#include "fun.h"



string help_xor (string a ,string b)
{
	int r,alpha;
	char betta;
	string str;
	for (int h = 0; h < (int) a.size(); h++)
	{
		r = a[h]-'0'; // берем значение согласно таблице замены элемент под номером h
		alpha = b[h] - '0';
		betta = alpha ^ r + '0';
		str = str + betta; //добавляем букву
	}
	return str;
}

vector <string> sub_block (string str,int n,int m)
{
	vector  <string> blok;
	char alpha;
	for (int i = 0; i < (int) str.size();)
		for (int j = 0; j < n; j++)//отмеряем n штук блоков
		{
			string sub;
			for (int k = 0; k < m; k++)//отмеряем m штук символов
			{
				alpha=str[i];
				sub=sub+alpha;
				i++;
			}
			blok.push_back(sub);
		}
	return blok;
}

string use_p_box (vector <string> hs,map<int,int>p_box)
{
	string str;
	string answer;
	for (int h=0; h < (int) hs.size(); h++)//Склеиваем строку (n блоков склеиваем вместе)
		str=str+hs[h];
	for (int h = 0; h < (int) str.size(); h++)
		answer=answer+str[ p_box[h] ];
	return answer;
}

string int_to_str (vector <int> sub_key)
{
	string str;
	char alpha;
	for (int i=0;i<sub_key.size();i++)
	{
		alpha=sub_key[i]+'0';
		str=str+alpha;
	}
	return str;
}

vector <vector <string>> sub_str_blok (string str, int n, int m)
{
	//в функции не рассматриваю, когда не влезает целиком sblok. То есть n=3,m=3, длина текста 17
	vector <vector <string>> blok;
	char alpha;

	for (int i = 0; i < (int) str.size();)
	{
		vector <string> oops;
		for (int j = 0; j < n; j++)//отмеряем n штук блоков
		{
			string sub;
			for (int k = 0; k < m; k++)//отмеряем m штук символов
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

string sbox_str (string str,  map <string,string> sbox)
{
	string answer=sbox[str];
	return answer;
}

vector <string> use_s_box (vector <string> hs, map <string,string> sbox)
{
	string str;
	for(int i = 0 ;i < (int)hs.size(); i++)
	{
		str=hs[i];
		hs[i]=sbox[str];
	}
	return hs;
}

string generate_text (int n, int m)
{
	string str;
	char alpha;
	int r;
	for (int i = 0; i < n*m; i++)
	{
		r=rand()%2;
		alpha=r+'0';
		str=str+alpha;
	}
	return str;
}

map <int, int> swap(map <int, int> tabl, int n,int m)
{
	for (int i = 0; i < n*m; i++)
		swap(tabl[i], tabl[rand() % (n*m)]);// генерируем таблицу замены
	return tabl;
}

map <int, int> generate_tabl(int n, int m)
{
	map <int, int> a;
	for (int i = 0; i < n*m; i++)
		a[i] = i;
	return a;
}

vector <int> generate_key(int n, int m, int j)
{
	vector <int> key;
	for (int i = 0; i < n*m*j; i++)
	{
		int r = rand() % 2;
		key.push_back(r);
	}
	return key;
}

vector <vector<int>> sub(vector<int> key,int n,int m, int j)
{
	vector <vector <int>> sub_key;
	int counter=0;
	sub_key.resize(j);
	for (int i = 0; i < j; i++)
		for (int k = 0; k < n*m; k++)
		{
			sub_key[i].push_back(key[counter]);
			counter++;
		}
	return sub_key;
}

int Counter_Bits(vector <string> &text)
{
	int count = 0;
	for (int i = 0; i < (int) text.size(); i++)
	{
		for (int j = 0; j < (int) text[i].size(); j++)
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

	for (int i = 0; i < (int) pow(2.0, (double)m); i++)
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

	for (int i = 0; i < (int) pow(2.0, (double) m); i++)
	{
		int k = i;
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
	int i = 0;
	map <string,string> :: iterator it;

	for (it = sblock.begin(); it!=sblock.end(); it++)
	{
		(*it).second = temp[i];
		i++;
	}
	return sblock;
}

map <string, vector<difference>> create_dif_tabl (int m)
{
	map <string, vector<difference>> table;//будем возвращать это
	vector <string> save;//Храним тут все возможные строки
	for (int i = 0; i < (int) pow(2.0, (double) m); i++)//генерируем все возможные строки
	{
		int k = i;
		string str;
		for (int j = 0; j < m; j++)
		{
			char temp = k % 2 + '0';
			str = str + temp;
			k = k / 2;
		}
		save.push_back(str);
	}

	vector<difference> help;//вспомогательная, дабы не париться с кучей скобок и был понятнее код
	help.resize((int) pow(2.0, (double) m));
	string str;

	for (int i = 0; i < (int) pow(2.0, (double) m); i++)
	{
		for (int k = 0; k < (int) pow(2.0, (double) m); k++)
		{
			help[k].y=save[k];
			str = help_xor(save[i],save[k]);
			help[k].x=str;
		}
		table[save[i]]=help;
	}
	return table;
}

map <string, map<string,int>> create_tabl_count_diff (map <string, vector<difference>> dif,map <string,string> sbox)
{
	map <string, map<string,int>> Ulia;

	map <string, vector<difference>>::iterator it;
	string str,c;
	string a1,a2;

	for (it=dif.begin();it!=dif.end();it++)
	{
		str=(*it).first;
		for (int i=0;i<(*it).second.size();i++)
		{
			a1=sbox_str ( (*it).second[i].x,sbox);
			a2=sbox_str ( (*it).second[i].y,sbox);
			c=help_xor (a1,a2);
			Ulia [c][str]++;
		}
	}
	return Ulia;
}

