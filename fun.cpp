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
	int done = 0;
	while (done != 1)
	{
		int ed = 0;
		int kol = 0;
		vector <string> temp;
		for (int i = 0; i < j; i++)
		{
			string str = Random_Bits(n);
			for (int k = 0; k < str.size(); k++)
			{
				if (str[i] == '1')
				{
					ed++;
				}
				kol++;
			}

			temp.push_back(str);
		}

		double kol2 = kol;
		double proc = ed / kol2;

		if ((proc >= 0.4) && (proc <= 0.6))
		{
			done = 1;
			key = temp;
		}
	}
	
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

map <string, vector<difference>> create_dif_tabl (int m)
{
	map <string, vector<difference>> table;//будем возвращать это
	vector <string> save;//Храним тут все возможные строки
	for (int i = 0; i < (int) pow(2.0, (double) m); i++)//генерируем все возможные строки
	{
		
		string str = Int_to_BitStr(i, m);
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

	//заполнение таблицы нулями

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
		str = temp + str;
		n = n / 2;
	}

	return str;
}

string crypto (int n, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box,string text)//создано, чтобы шифровать текст. J раз:(Делает XOR с ключом, делает sbox, делает pbox)
{
	vector <string> hs ;
	string new_text;

	for (int i = 0; i < j; i++) // по раундам
	{
		new_text = help_xor(text, key[i]); // XOR
		hs = divide_str(text, n); // Разбиение текста на блоки
		hs = use_s_box(hs, s_box); // Применение s-блока
		string p_str = use_p_box(hs, p_box); // Применение p-блока
		text=p_str;
	}
	return text;// возвращает строку текста y или y` будет
}

map <string, map<string,int>> create_tabl_count_diff_version2 (map <string, vector<difference>> dif,map <string,string> sbox, int m)
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

map <int,vector<string>> ulia (int n, int j, string delta_A,  map <string, map<string, int>> Table_analysis, map <int, int> p_box)
{
	map <string,vector<string>> helga;// Сюда перетащу значения из Table_analysis, дабы было проще работать
	map <string, map<string, int>> :: iterator it;
	map<string, int>:: iterator it2;

	for (it =  Table_analysis.begin(); it!=Table_analysis.end(); it++)//обход всех элемнтов
		for (it2 = (*it).second.begin(); it2!=(*it).second.end(); it2++)//обход всех элемнтов, опять же
			helga[(*it).first].push_back((*it2).first);// сохраняем в нужные в helga



	vector<string> delta_a_i; //блоки строки, чтобы было сподручнее заменять блоки
	map <int,vector<string>> alpha;// тут сохраняем строки, которые были получены на k-ом раунде
	alpha[0].push_back(delta_A);// 0-ой раунд, исходная разность

	for (int i=1;i<j;i++)// по всем циклам, кроме последнего, как в методичке
	{
		for (int k=0;k<alpha[i-1].size();k++)// по всем элементам (строкам из предыдущего раунда) будем создавать новые возможные строчки
		{
			delta_a_i= divide_str(alpha[i-1][k], n);//Вытащили строчку, k-ую из предыдущего раунда
			vector<string> help;//тут будут хранится строки, которые можно получить из текущей разности
			help.resize(1);//одна пустая строка
		
			for (int h1=0;h1<n;h1++)// по всем блокам, которые можем заменить во входной разности
			{
				vector<string> help_to_help;
				for (int h2=0; h2<help.size();h2++)// по всем возможным строкам, которые пока там лежат
					for (int h3=0;h3<helga[delta_a_i[h1]].size();h3++)// по всем блокам, которые можем заменить (от блока, который заменяем
					{
						string str;
						str=help[h2]+helga[delta_a_i[h1]][h3];//взяли текущую строку, прибавили к ней возможный элемент
						help_to_help.push_back(str);//засунули ее в новый элемент
					}
				help=help_to_help;
			}

			for (int h=0;h<help.size();h++)
				alpha[i].push_back(help[h]);
		}
	}
	return alpha;
}

vector <pair_text> create_pair ( int count, int n, int m, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box, string delta_A)//создает count штук пар открытых - закрытых текстов. Count задает пользователь
{
	vector <pair_text> elis;

	map <string, int> temp;

	for (int i=0;i<count;i++)
	{
		pair_text fox;

		fox.x = Random_Bits_no_multi(n*m, temp);
		temp[fox.x] = 1;
		
		fox.x_=help_xor(fox.x,delta_A);// х_ = x XOR A
		fox.y=crypto (n, j, key, s_box, p_box, fox.x);//шифрование x
		fox.y_=crypto (n, j, key, s_box, p_box, fox.x_);//шифрование x_
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