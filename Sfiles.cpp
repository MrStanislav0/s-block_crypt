#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

#include "Sfiles.h"

vector <string> inpute_file(string name)
{
	vector <string> text;
	ifstream file_text;
	string text_temp;
	file_text.open(name);
	if (file_text)
	{
		while (!file_text.eof())
		{
			getline(file_text, text_temp);
			text.push_back(text_temp);
		}
		file_text.close();
		return text;
	}
	return text;
}

int Is_file (string name)
{
	ifstream file_text;
	file_text.open(name);
	if (file_text)
	{
		file_text.close();
		return 1;
	}
	else
	{
		file_text.close();
		return 0;
	}
	return 0;
}

void outpute_file(string name, vector <string> &text, int mode)
{
	ofstream out_file;
	string text_temp;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);
	for (int i = 0; i < text.size(); i++)
	{
		out_file << text[i] << endl;
	}
	out_file << endl;
	out_file.close();
}

void outpute_file(string name, string text, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);
	
	out_file << text << endl;
	out_file << endl;
	out_file.close();
}

void outpute_file(string name, map <string, string> s_box, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	map <string, string> ::iterator it;
	for (it = s_box.begin(); it != s_box.end(); it++)
	{
		out_file << (*it).first <<" - "<< (*it).second << endl;
	}
	out_file << endl;
	out_file.close();
}

void outpute_file(string name, map <int, int> p_box, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	map <int, int> ::iterator it;
	for (it = p_box.begin(); it != p_box.end(); it++)
	{
		out_file << (*it).first << " - " << (*it).second << endl;
	}
	out_file << endl;
	out_file.close();
}

void outpute_file(string name, vector <vector <int>> key, int mode)
{
	ofstream out_file;
	string text_temp;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	for (int i = 0; i < key.size(); i++)
	{
		for (int j = 0; j < key[i].size(); j++)
		{
			out_file << key[i][j];
		}
	}
	out_file << endl;
	out_file << endl;
	out_file.close();
}

void outpute_file(string name, map <string, map<string, int>> tabl, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	int one = 1;

	map <string, map<string, int>> ::iterator it;

	for (it = tabl.begin(); it != tabl.end(); it++)
	{
		map <string, int> ::iterator it_2;

		if (one == 0)
		{
			out_file << (*it).first << " ";

			for (it_2 = (*it).second.begin(); it_2 != (*it).second.end(); it_2++)
			{
				
				out_file << (*it_2).second << " ";
			}

		}
		else
		{
			string str;
			for (int k = 0; k < (int)(*it).first.size(); k++)
			{
				str = str + " ";
			}

			out_file << str << " ";

			for (it_2 = (*it).second.begin(); it_2 != (*it).second.end(); it_2++)
			{
				
				out_file << (*it_2).first << " ";

			}

			out_file << endl;

			out_file << (*it).first << " ";

			for (it_2 = (*it).second.begin(); it_2 != (*it).second.end(); it_2++)
			{

				out_file << (*it_2).second << " ";

			}
		}


		if (one == 1)
		{
			one = 0;
		}

		out_file << endl;
	}
	out_file << endl;
	out_file.close();
}

void outpute_info(string name, int m, int n, int j, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	
	out_file << "Размер блока " << m << endl;
	out_file << "Количество блоков " << n << endl;
	out_file << "Количество раундов " << j << endl;

	out_file << endl;

	out_file.close();
}