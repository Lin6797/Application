//ͨ�����������ڲ�����ע�ᡢ��¼���޸����룩 

#include<iostream>
#include<vector>
using namespace std;

class Commual{
	public:
		Commual();//���캯������Num��ֵ�����Login_message��Ԫ�أ�
		bool Resgin();//ע�� 
		string Login();//��¼
		bool c_passcpde();//�޸�����
		bool c_write();//�޸������д���ļ� 
	private:
		string* ID;//Login_message�е��û��� 
		string* Passcode;//Login_message�е����� 
		string* IsAdm;//Login_message�е��Ƿ�Ϊ����Ա�ı�־
		int Num;//����Ԫ�ظ���
		vector<string> logins;//����login�������ͺ��������� 
		bool New();
};
