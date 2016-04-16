#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#include "fun.h"



string help_xor (string a, string b)
{
	string str;
	for (int i = 0; i < (int) a.size(); i++)
	{
		char temp = (b[i] - '0') ^ (a[i] - '0') + '0';
		str = str + temp; //добавляем букву
	}
	return str;
}

string use_p_box (vector <string> hs, map<int,int>p_box)
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
	for (int i=0;i<sub_key.size();i++)
	{
		char temp = sub_key[i]+'0';
		str=str + temp;
	}
	return str;
}

vector <string> divide_str (string str, int n)
{
	vector <string> block;

	int m = str.size() / n;

	int k = 0;

	for (int i = 0; i < n; i++)//отмеряем n штук блоков
	{
		string sub;
		for (int j = 0; j < m; j++)//отмеряем m штук символов
		{
			char temp = str[k];
			sub = sub + temp;
			k++;
		}

		block.push_back(sub);
	}
	
	return block;
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

string Random_Bits (int n)
{
	string str;
	for (int i = 0; i < n; i++)
	{
		int r = rand() % 2;
		char temp = r + '0';
		str=str + temp;
	}
	return str;
}

map <int, int> Mix_pbox(map <int, int> tabl, int n,int m)
{
	for (int i = 0; i < n*m; i++)
		swap(tabl[i], tabl[rand() % (n*m)]);// генерируем таблицу замены
	return tabl;
}

map <int, int> generate_pbox(int n, int m)
{
	map <int, int> p_box;
	for (int i = 0; i < n*m; i++)
		p_box[i] = i;

	p_box = Mix_pbox(p_box, m, n);

	return p_box;
}

vector <string> generate_key(int n, int j)
{
	vector <string> key;
	for (int i = 0; i < j; i++)
	{
		string str = Random_Bits(n);
		key.push_back(str);
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

	table = generate_tabl_mix(table, m);

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

map <string, map<string,int>> create_tabl_count_diff (map <string, vector<difference>> dif,map <string,string> sbox, int m)
{
	map <string, map<string,int>> Ulia;

	// Заполнение таблицы нулями

	int cikl = (int)pow(2.0, (double)m);

	for (int i = 0; i < cikl; i++)
	{
		string temp1 = Int_to_BitStr(i, m);

		for (int j = 0; j < cikl; j++)
		{
			
			string temp2 = Int_to_BitStr(j, m);

			Ulia[temp1][temp2] = 0;
		}

	}

	// Заполнение таблицы значениями

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

string Int_to_BitStr(int n, int bit)
{
	string str;
	for (int j = 0; j < bit; j++)
	{
		char temp = n % 2 + '0';
		str = str + temp;
		n = n / 2;
	}

	return str;
}