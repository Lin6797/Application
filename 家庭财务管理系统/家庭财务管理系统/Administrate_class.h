//����Ա�� 

#include<iostream>
using namespace std;

class Adm{
	public:
		Adm(string ID, string object);//���캯��
		bool Delete_all();//ɾ����ͥ��Ա 
		bool View();//�鿴��Ա��֧��Ϣ
		bool Edit_finance();//�༭��Ա��֧��Ϣ
	private:
		string Pu_id;//��������ID
		string Object;//�жϲ�������Ϊ����Ա�Լ���������
		bool Choice_opera_self();//ѡ�����������Ϊ����Ա�Լ�ʱ��
		bool Choice_opera_other();//ѡ�����(����Ϊ������Ա��ļ�ͥ��Աʱ)
		bool Delete_login();//ɾ��Login_message�ļ��еĶ�Ӧ���� 
	    bool Delete_member();//ɾ��Member_message�ļ��еĶ�Ӧ����
	    bool Delete_finance();//ɾ��Finance_message�ļ��еĶ�Ӧ����
};
