#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

#include "fun.h"
#include "Sfiles.h"

bool Is_file (string name)
{
	ifstream file_text;
    file_text.open(name.c_str());
	if (file_text)
	{
		file_text.close();
		return true;
	}
	else
	{
		file_text.close();
		return false;
	}
	return false;
}

void outpute_sbox(string name, map <string, string> s_box, int mode)
{
	ofstream out_file;
    if (mode == 2) out_file.open(name.c_str(), ios_base::app);
    else out_file.open(name.c_str());

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
    if (mode == 2) out_file.open(name.c_str(), ios_base::app);
    else out_file.open(name.c_str());

	map <int, int> ::iterator it;
	for (it = p_box.begin(); it != p_box.end(); it++)
	{
		out_file << (*it).first << " " << (*it).second << endl;
	}
	
	out_file.close();
}

void outpute_info(string name, string login, int m, int n, int j, int mode)
{
	ofstream out_file;
    if (mode == 2) out_file.open(name.c_str(), ios_base::app);
    else out_file.open(name.c_str());

    out_file << login << endl;
	out_file << m << endl;
	out_file << n << endl;
	out_file << j << endl;

	out_file.close();
}

void outpute_file_full(string name, string login, int m, int n, int j, map <string, string> s_box, map <int, int> p_box)
{
    outpute_info(name, login, m, n, j, 1);

	outpute_sbox(name, s_box, 2);

	outpute_pbox(name, p_box, 2);
}


data_file inpute_file_full(string name)
{
	data_file temp;
	ifstream file_text;

    file_text.open(name.c_str());
	if (file_text)
	{
        file_text >> temp.login;
		file_text >> temp.m;
		file_text >> temp.n;
		file_text >> temp.j;

		file_text.close();
		return temp;
	}
	return temp;
}

void outpute_deltaA(string name, vector <pair_text> pair2, string delta, int mode)
{
    ofstream out_file;
    if (mode == 2) out_file.open(name.c_str(), ios_base::app);
    else out_file.open(name.c_str());

    out_file << "ΔA: " << delta << endl;
    out_file << "X Y X' Y' ΔC" << endl;

    for (int i = 0; i < (int) pair2.size(); i++)
    {
        out_file << pair2[i].x <<" "<< pair2[i].y <<" "<< pair2[i].x_ <<" " << pair2[i].y_ <<" "<< pair2[i].C << endl;
    }

    out_file.close();
}
