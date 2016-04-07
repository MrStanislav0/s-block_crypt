#include <string>
#include <fstream>
#include <vector>

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

int file_read (string name)
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
	out_file.close();
}