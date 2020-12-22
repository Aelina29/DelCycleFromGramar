#ifndef H
#define H

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<string.h>
#include<queue>
#include <iostream>
#include <fstream>
using namespace std;

//split string by ch
size_t split(const string &txt, vector<string> &strs, char ch = ' ')
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();
	while (pos != std::string::npos) 
	{
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;
		pos = txt.find(ch, initialPos);
	}
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
	return strs.size();
}

//array<string> -> map<char, array<string>>
//"S->A|d|/e|As" -> [S] {A, d, /e, As}
void create_gramar_map(vector<string> &ar, map<char, vector<string>> &m)
{
	for (string s : ar)
	{
		char key = s[0];
		s.erase(0, 3);
		vector<string> vstr;
		vstr.clear();
		split(s, vstr, '|');
		m[key] = vstr;
	}
}

//creat N^A for all A from Nonterminals
void create_N(map<char, vector<string>> &Gramar, map<char, vector<char>> &N)
{
	map<char, vector<char>> N1;
	vector<char> help;
	for (map<char, vector<string>>::iterator it = Gramar.begin(); it != Gramar.end(); it++)
	{
		help.clear();
		for (int i = 0; i < it->second.size(); i++)
		{
			if (it->second[i].size() == 1)
				if ('A' <= it->second[i][0] && it->second[i][0] <= 'Z')
					help.push_back(it->second[i][0]);
		}
		N1[it->first] = help;
	}
	/*
	cout << "N1" << endl;
	for (map<char, vector<char>>::iterator it = N1.begin(); it != N1.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << endl;
	*/
	vector<char> empt;
	empt.clear();
	for (map<char, vector<char>>::iterator it = N1.begin(); it != N1.end(); it++)
	{
		queue<char> q;
		if (it->second.size() == 0)
		{
			N[it->first] = empt;
			//cout << "empt\n";
		}
		else
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				q.push(it->second[i]);
				//cout << "1pushed to queue " << it->second[i] << endl;
			}
			while (!q.empty())
			{
				char c = q.front();
				q.pop();
				//cout << "poped from queue " << c << endl;
				if (c != it->first /*!N[it->first].contains(c)*/ && (find(N[it->first].begin(), N[it->first].end(),c) == N[it->first].end()))
				{
					//cout << "if\n";
					N[it->first].push_back(c);
					//cout << "pushed to N[" << it->first << "] " << c << endl;
					for (int i = 0; i < N1[c].size(); i++)
					{
						q.push(N1[c][i]);
						//cout << "2pushed to queue " << N1[c][i] << endl;
					}
				}
			}
		}
	}
}

//delete A->B where A,B from Nonterminals
void clean_gramar(map<char, vector<string>> &Gramar)
{
	for (map<char, vector<string>>::iterator it = Gramar.begin(); it != Gramar.end(); it++)
	{
		for (int i = 0; i < it->second.size();)
		{
			if (it->second[i].size() == 1 && 'A' <= it->second[i][0] && it->second[i][0] <= 'Z')
			{
				Gramar[it->first].erase(find(it->second.begin(), it->second.end(), it->second[i]));
			}
			else i++;
		}
	}
}

//add to gramar
map<char, vector<string>> add_to_gramar(map<char, vector<string>> &Gramar, map<char, vector<char>> &N)
{
	map<char, vector<string>> NewGramar;
	for (map<char, vector<string>>::iterator it = Gramar.begin(); it != Gramar.end(); it++)
	{
		char key = it->first;
		for (int i = 0; i < Gramar[key].size(); i++)
		{
			NewGramar[key].push_back(Gramar[key][i]);
		}
		for (int i = 0; i < N[key].size(); i++)
		{
			char help = N[key][i];
			for (int i = 0; i < Gramar[help].size(); i++)
			{
				string s = Gramar[help][i];
				/*!NewGramar[key].contains(s)*/
				if (find(NewGramar[key].begin(), NewGramar[key].end(), s) == NewGramar[key].end())
					NewGramar[key].push_back(s);
			}
		}
	}
	return NewGramar;
}

//string <- map<char, array<string>>
//"S->A|d|/e|As" <- [S] {A, d, /e, As}
string create_gramar_from_map(map<char, vector<string>> &m)
{
	string res = "";
	for (map<char, vector<string>>::iterator it = m.begin(); it != m.end(); it++)
	{
		res.insert(res.end(), it->first);
		res.insert(res.size(), "->");
		for (int i = 0; i < m[it->first].size(); i++)
		{
			res.insert(res.size(), m[it->first][i]);
			if (i != m[it->first].size() - 1)
				res.insert(res.size(), "|");
		}
		res.insert(res.size(), " ");
	}
	return res;
}

//тестирование вспомогательных функций
void testing(string str)
{
	cout << "\ntesting split" << endl;
	vector<string> P;
	split(str, P);
	for (int i = 0; i < P.size(); i++)
		cout << P[i] << endl;
	cout << endl;

	cout << "testing S->A | d|/e | As -> [S] {A, d, /e, As}" << endl;
	map<char, vector<string>> Gramar;
	create_gramar_map(P, Gramar);
	for (map<char, vector<string>>::iterator it = Gramar.begin(); it != Gramar.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "testing create N" << endl;
	map<char, vector<char>> N;
	create_N(Gramar, N);
	for (map<char, vector<char>>::iterator it = N.begin(); it != N.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "testing clean_gramar" << endl;
	for (map<char, vector<string>>::iterator it = Gramar.begin(); it != Gramar.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << "=======================\n";
	clean_gramar(Gramar);
	for (map<char, vector<string>>::iterator it = Gramar.begin(); it != Gramar.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "testing add_to_gramar\n";
	map<char, vector<string>> NewGramar = add_to_gramar(Gramar, N);
	cout << "N\n";
	for (map<char, vector<char>>::iterator it = N.begin(); it != N.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << "gramar" << endl;
	for (map<char, vector<string>>::iterator it = Gramar.begin(); it != Gramar.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << "New gramar\n";
	for (map<char, vector<string>>::iterator it = NewGramar.begin(); it != NewGramar.end(); it++)
	{
		cout << "[" << it->first << "] ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << endl;
	}
	cout << endl;

	cout << "testing create_gramar_from_map" << endl;
	string res = create_gramar_from_map(NewGramar);
	cout << res << endl;
}

//удаляет из грамматики из файла цепные продукции и выводит текст с описанием новой грамматики
string del_cycle(string filename)
{
	ifstream file(filename);
	string GramarStr;
	getline(file, GramarStr);
	cout << GramarStr << endl;
	vector<string> P;
	split(GramarStr, P);
	map<char, vector<string>> Gramar;
	create_gramar_map(P, Gramar);
	map<char, vector<char>> N;
	create_N(Gramar, N);
	clean_gramar(Gramar);
	map<char, vector<string>> NewGramar = add_to_gramar(Gramar, N);
	string res = create_gramar_from_map(NewGramar);
	cout << res << endl;
	return res;
}

#endif