#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

#include "Sfiles.h"

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

void outpute_sbox(string name, map <string, string> s_box, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	map <string, string> ::iterator it;
	for (it = s_box.begin(); it != s_box.end(); it++)
	{
		out_file << (*it).first <<" "<< (*it).second << endl;
	}
	
	out_file.close();
}

void outpute_pbox(string name, map <int, int> p_box, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	map <int, int> ::iterator it;
	for (it = p_box.begin(); it != p_box.end(); it++)
	{
		out_file << (*it).first << " " << (*it).second << endl;
	}
	
	out_file.close();
}

void outpute_info(string name, int m, int n, int j, int mode)
{
	ofstream out_file;
	if (mode == 2) out_file.open(name, ios_base::app);
	else out_file.open(name);

	out_file << m << endl;
	out_file << n << endl;
	out_file << j << endl;

	out_file.close();
}

void outpute_file_full(string name, int m, int n, int j, map <string, string> s_box, map <int, int> p_box)
{
	outpute_info(name, m, n, j, 1);

	outpute_sbox(name, s_box, 2);

	outpute_pbox(name, p_box, 2);
}


data_file inpute_file_full(string name)
{
	data_file temp;
	ifstream file_text;
	string text_temp;
	file_text.open(name);
	if (file_text)
	{
		
		file_text >> temp.m;
		file_text >> temp.n;
		file_text >> temp.j;

		string str1, str2;
		int n1, n2;

		for (int i = 0; i < (int)pow(2.0, (double)temp.m); i++)
		{
			file_text >> str1;
			file_text >> str2;

			temp.s_box[str1] = str2;
		}

		for (int i = 0; i < temp.m * temp.n; i++)
		{
			file_text >> n1;
			file_text >> n2;

			temp.p_box[n1] = n2;
		}

		file_text.close();
		return temp;
	}
	return temp;
}