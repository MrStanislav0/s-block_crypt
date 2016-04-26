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

vector <string> divide_str (string str, int n)
{
	vector <string> block;

	int m = (int) str.size() / n;

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

vector <string> use_s_box (vector <string> hs, map <string,string> sbox)
{
	for(int i = 0; i < (int)hs.size(); i++)
	{
		hs[i]=sbox[hs[i]];
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
		swap(tabl[i], tabl[rand() % (n*m)]); // генерируем таблицу замены
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
	double r = dRand(0.4, 0.6);
	int ed = (double) round(r * n * j);
	
	vector <int> temp_table;

	for (int i = 0; i < n*j; i++)
	{
		if (ed > 0)
		{
			temp_table.push_back(1);
			ed--;
		}
		else
		{
			temp_table.push_back(0);
		}

	}

	random_shuffle(begin(temp_table), end(temp_table));

	string str;
	for (int i = 0; i < n*j; i++)
	{
		char s = temp_table[i] + '0';
		str = str + s;
	}

	vector <string> key = divide_str(str, j);
	
	return key;
}

vector <string> Random_sbox(int m)
{
	vector <string> temp_table;

	for (int i = 0; i < (int) pow(2.0, (double)m); i++)
	{
		string str = Int_to_BitStr(i, m);
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
		string str = Int_to_BitStr(i, m);
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

string Int_to_BitStr(int n, int bit)
{
	string str;
	for (int j = 0; j < bit; j++)
	{
		char temp = n % 2 + '0';
		str = temp + str;
		n = n / 2;
	}

	return str;
}

string crypto (int n, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box,string text)//создано, чтобы шифровать текст. J раз:(Делает XOR с ключом, делает sbox, делает pbox)
{
	for (int i = 0; i < j; i++) // по раундам
	{
		vector <string> hs = divide_str(text, n); // Разбиение текста на блоки
		hs = use_s_box(hs, s_box); // Применение s-блока
		text = use_p_box(hs, p_box); // Применение p-блока
		text = help_xor(text, key[i]); // XOR
	}
	return text; // возвращает строку текста y или y` будет
}

vector <pair_text> create_pair ( int count, int n, int m, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box, string delta_A)//создает count штук пар открытых - закрытых текстов. Count задает пользователь
{
	vector <pair_text> elis;

	map <string, int> temp;

	for (int i=0; i < count; i++)
	{
		pair_text fox;

		fox.x = Random_Bits_no_multi(n*m, temp);
		temp[fox.x] = 1;
		
		fox.x_ = help_xor(fox.x,delta_A);// х_ = x XOR A
		fox.y = crypto (n, j, key, s_box, p_box, fox.x);//шифрование x
		fox.y_ = crypto (n, j, key, s_box, p_box, fox.x_);//шифрование x_
		elis.push_back(fox);
	}

	return elis;
}

string Random_Bits_no_multi(int n, map <string, int> temp)
{
	string str;
	int done = 0;

	while (done != 1)
	{

		for (int i = 0; i < n; i++)
		{
			int r = rand() % 2;
			char temp = r + '0';
			str = str + temp;
		}

		if (temp[str] == 0)
		{
			done = 1;
		}
		else
		{
			str = "";
		}
		
	}
	return str;
}

double dRand(double dMin, double dMax)
{
	double f = (double)rand() / RAND_MAX;
	return dMin + f * (dMax - dMin);
}

string Use1_sbox(map <string, string> sbox, string s1)
{
	return sbox[s1];
}

map <string, map<string, int>> Analyse_Tabl_generate(map <string, string> sbox, int m)
{
	map <string, map<string, int>> Tabl;

	int cikl = (int)pow(2.0, (double)m);

	for (int i = 0; i < cikl; i++)
	{
		string temp1 = Int_to_BitStr(i, m); // a1

		for (int j = 0; j < cikl; j++)
		{

			string temp2 = Int_to_BitStr(j, m); // a2

			string final1 = help_xor(temp1, temp2); // a1 xor a2
			string final2 = help_xor(Use1_sbox(sbox, temp1), Use1_sbox(sbox, temp2)); // S(a1) xor S(a2)
			Tabl[final1][final2]++;

			if (Tabl[temp1][temp2] == 0)
				Tabl[temp1][temp2] = 0;
		}

	}

	return Tabl;
}