//��ͨ��Ա���Խ��еĲ���������(����д�Լ����˻����鿴�Լ����˻���ɾ���Լ����˻�)
#include<iostream>
#include<vector>
using namespace std;

class Nor{
	public:
		Nor(string id);//���캯��(���ļ��е��˻����ݶ�ȡ����)
		bool View();//�鿴��֧��¼ 
		bool Write();//д��֧��¼ 
		bool Delete();//ɾ����֧��¼ 
		bool Alter();//�޸���֧��¼ 
	private:
		int Num; //����Ԫ�ظ���
		string ID; //�洢�û���
		vector<string> finances;//�����������ͺ��������֣����ڴ洢���û��Ĳ�����Ϣ��
		vector<string> other_finances;//�����������ͺ��������֣����ڴ洢�����û��Ĳ�����Ϣ��
		bool New_vector(string id); //���ڸ������������� 
		bool New_file();//���ڸ����ļ���Ϣ
};

