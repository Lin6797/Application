#include <stdio.h>
#include <iostream>
#include "SQLoperation.h"

using namespace std;

int main() {
	string name;
	string password;
	char Judge = 'N';

	string allOPERATION = "1���������ݱ�\n2���������ݣ�\n3��ɾ�����ݣ�\n4���޸����ݣ�\n"
		"5��ɾ�����ݱ�\n6�� join����;\n7������֧�֣�\n8���������\n9)ɾ������\n10���˳�\n";

	cout << "name:"; cin >> name;
	cout << "password:"; cin >> password;
	SQLopertaion* SQ = new SQLopertaion(name, password);
	while ( Judge!='y' && Judge!='Y')
	{
		cout << allOPERATION;
		int oper;
		cout << "������Ҫִ�еĲ�����";
		cin >> oper; cin.clear();
		SQ->Operation(oper);

		cout << "�Ƿ���������в�����Y/N����";
		cin >> Judge; cin.clear();

		if (Judge == 'y' || Judge == 'Y') { break; }
		system("cls");
	}
	
	return 0;
}