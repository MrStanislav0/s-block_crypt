#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#include "fun.h"

extern polynom pol1, pol2;

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
		answer=answer+str[p_box[h]];
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

map <int, int> generate_pbox(int n, int m)
{
	map <int, int> p_box;
	for (int i = 0; i < n*m; i++)
		p_box[i] = i;

	for (int i = 0; i < n*m; i++)
		swap(p_box[i], p_box[iRand() % (n*m)]);

	return p_box;
}

vector <string> generate_key(int n, int j)
{
	Result_random gen_key = Random_Bits(pol1, pol2, n*j); // Генерирование ключа длины m*n*j
	pol1 = gen_key.liniya_svyazi; // изменяем полиномы
	pol2 = gen_key.liniya_svyazi2;

	string str = IntVec_to_Str(gen_key.bits); // преобразем в строку
	vector <string> key = divide_str(str, j); // разделяем на раунды
	
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

vector <pair_text> create_pair (int count, int n, int m, int j,vector <string> key, map <string, string> s_box, map <int, int> p_box, string delta_A) //создает count штук пар открытых - закрытых текстов. Count задает пользователь
{
	vector <pair_text> elis;

	map <string, int> temp;

	for (int i=0; i < count; i++)
	{
		pair_text fox;

		fox.x = Random_Bits_no_multi(n*m, temp);
		temp[fox.x] = 1;
		
		fox.x_ = help_xor(fox.x,delta_A); // х_ = x XOR A
		fox.y = crypto (n, j, key, s_box, p_box, fox.x); //шифрование x
		fox.y_ = crypto (n, j, key, s_box, p_box, fox.x_); //шифрование x_

		fox.C = help_xor(fox.y, fox.y_); // C = y xor y_

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

// Функция сдвига вправо на 1 позицию

vector <int> sdvig(vector <int> &text_sdvg)
{
	rotate(text_sdvg.rbegin(), text_sdvg.rbegin() + 1, text_sdvg.rend());
	return text_sdvg;
}


polynom generate_polynom(int x1, int x2, int x3, int x4, int x5)
{
	polynom liniya_svyazi;

	liniya_svyazi.N = x1;

	// Вычитание из всех степений степень при x1. В вектор numbers заносятся позиции битов, которые надо XOR'ить

	if (x3 == 0)
	{
		x2 = x2 - x1;
		x3 = x3 - x1;
		x1 = 0;

		if (x2 < 0)
			x2 = -x2;
		if (x3 < 0)
			x3 = -x3;

		x2 = x2 - 1;
		x3 = x3 - 1;

		liniya_svyazi.numbers.push_back(x2);
		liniya_svyazi.numbers.push_back(x3);
	}
	else if (x4 == 0)
	{
		x2 = x2 - x1;
		x3 = x3 - x1;
		x4 = x4 - x1;
		x1 = 0;

		if (x2 < 0)
			x2 = -x2;
		if (x3 < 0)
			x3 = -x3;
		if (x4 < 0)
			x4 = -x4;

		x2 = x2 - 1;
		x3 = x3 - 1;
		x4 = x4 - 1;

		liniya_svyazi.numbers.push_back(x2);
		liniya_svyazi.numbers.push_back(x3);
		liniya_svyazi.numbers.push_back(x4);
	}
	else if (x5 == 0)
	{
		x2 = x2 - x1;
		x3 = x3 - x1;
		x4 = x4 - x1;
		x5 = x5 - x1;
		x1 = 0;

		if (x2 < 0)
			x2 = -x2;
		if (x3 < 0)
			x3 = -x3;
		if (x4 < 0)
			x4 = -x4;
		if (x5 < 0)
			x5 = -x5;

		x2 = x2 - 1;
		x3 = x3 - 1;
		x4 = x4 - 1;
		x5 = x5 - 1;

		liniya_svyazi.numbers.push_back(x2);
		liniya_svyazi.numbers.push_back(x3);
		liniya_svyazi.numbers.push_back(x4);
		liniya_svyazi.numbers.push_back(x5);
	}

	// Заполнение случайной последовательности

	for (int i = 0; i < liniya_svyazi.N; i++)
	{
		int r = rand() % 2;
		liniya_svyazi.lenta.push_back(r);
	}

	return liniya_svyazi;
}

polynom result_polynom(polynom liniya_svyazi)
{

	int result = liniya_svyazi.lenta[liniya_svyazi.numbers[0]];

	// Делаем XOR битов согласно полиному
	for (int i = 0; i < liniya_svyazi.numbers.size() - 1; i++)
	{
		result = result ^ liniya_svyazi.lenta[liniya_svyazi.numbers[i + 1]];
	}

	liniya_svyazi.lenta = sdvig(liniya_svyazi.lenta); // Сдвигаем последовательность вправо
	liniya_svyazi.lenta[0] = result; // Записываем на 1 место результат

	return liniya_svyazi;
}

Result_random random_bit(polynom liniya_svyazi, polynom liniya_svyazi2)
{
	liniya_svyazi = result_polynom(liniya_svyazi); // Результат от первого полинома
	liniya_svyazi2 = result_polynom(liniya_svyazi2); // Результат от второго полинома
	int bit = liniya_svyazi.lenta[0] ^ liniya_svyazi2.lenta[0]; // XOR битов - получается случайный бит

	// Возвращаем измененнные полиномы и случайный бит

	Result_random temp;
	temp.liniya_svyazi = liniya_svyazi;
	temp.liniya_svyazi2 = liniya_svyazi2;
	temp.bit = bit;

	return temp;
}

Result_random Random_Bits(polynom liniya_svyazi, polynom liniya_svyazi2, int n)
{
	Result_random final_result;

	for (int i = 0; i < n; i++)
	{
		Result_random temp;
		temp = random_bit(liniya_svyazi, liniya_svyazi2); // Получение случайного бита 
		liniya_svyazi = temp.liniya_svyazi;
		liniya_svyazi2 = temp.liniya_svyazi2;

		final_result.bits.push_back(temp.bit); // Записываем случайный бит в вектор
	}

	// Возвращаем измененнные полиномы и случайные биты

	final_result.liniya_svyazi = liniya_svyazi;
	final_result.liniya_svyazi2 = liniya_svyazi2;

	return final_result;
}

string IntVec_to_Str(vector <int> vec)
{
	string str;
	for (int i = 0; i < vec.size(); i++)
	{
		char temp = vec[i] + '0';
		str = str + temp;
	}
	return str;
}

int iRand()
{
	Result_random temp = Random_Bits(pol1, pol2, 15); 
	pol1 = temp.liniya_svyazi; // изменяем полиномы
	pol2 = temp.liniya_svyazi2;

	int final_rand = 0;
	int c = temp.bits.size() - 1;
	for (int i = 0; i < temp.bits.size(); i++)
	{
		final_rand = final_rand + temp.bits[i] * pow(2.0, c);
		c--;
	}
	return final_rand;
}