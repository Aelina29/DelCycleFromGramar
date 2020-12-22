#include"Header.h"

/*
Ќапишите программу, котора€ считывает из файла описание грамматики, удал€ет из нее цепные продукции
и выводит текст с описанием новой грамматики. √рамматику описывать можно так: УD-> ...Ф где
правила раздел€ютс€ внутри строки пробелами и \e обозначает эпсилон.
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