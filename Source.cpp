#include"Header.h"

/*
�������� ���������, ������� ��������� �� ����� �������� ����������, ������� �� ��� ������ ���������
� ������� ����� � ��������� ����� ����������. ���������� ��������� ����� ���: �D-> ...� ���
������� ����������� ������ ������ ��������� � \e ���������� �������.
*/

int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	del_cycle("gramar1.txt");
	cout << endl;

	//string ex = "S->S+T|S-T|T T->T*E|T/E|E E->(S)|a|b";
	//testing(ex);
	//string my = "A->C|as|B B->As|E C->Ds D->B|C|a E->a";
	//testing(my);
	

	system("pause");
}