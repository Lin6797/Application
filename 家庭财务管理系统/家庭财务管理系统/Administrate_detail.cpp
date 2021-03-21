//����Ա���ʵ��
#include"Administrate_class.h"
#include"Normal_class.h"
#include<vector>
#include<fstream>
using namespace std;

//���캯��
Adm::Adm(string ID, string object){
	Pu_id=ID; Object=object;
	cout<<"Object:"<<Object<<endl;
	if(Object=="Self"){
		Choice_opera_self();//ѡ����� 
	}
	else{
		Choice_opera_other();//ѡ����� 
	}
}

//ѡ�����������Ϊ����Ա����ʱ��
bool Adm::Choice_opera_self(){
	char nor_oper;//������־ 
	char con_oper;//�Ƿ����������־
	Nor s(Pu_id); 
	while(1){
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<< "\t\t|                       1.�鿴��֧��Ϣ                     |\n";
        cout<< "\t\t|                       2.д����֧��Ϣ                     |\n";
        cout<< "\t\t|                       3.ɾ����֧��Ϣ                     |\n";
        cout<< "\t\t|                       4.�޸���֧��Ϣ                     |\n";
        cout<< "\t\t|                       5.�˳�����                         |\n";
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<<"��ѡ����Ҫ���еĲ�����"; cin>>nor_oper; cin.sync();
		switch(nor_oper){
			case'1':{s.View();break;}
			case'2':{s.Write();break;}
			case'3':{s.Delete();break;}
			case'4':{s.Alter();break;}
			case'5':{return 0;}
			default:{system("cls");cout<<"�����������������"<<endl; continue;}
		}
		cout<<endl;
		while(1){
			cout<<"�Ƿ�����Ըó�Ա���в�������Y/N����"; cin>>con_oper;cin.sync();system("cls");
		    if(con_oper == 'N' || con_oper == 'n') return 0;
		    else if(con_oper == 'Y' || con_oper == 'y') break;
		    else {cout<<"�����������������"<<endl;continue;}
		}
    }
}

//ѡ�����������Ϊ������Ա���������ͥ��Աʱ��
bool Adm::Choice_opera_other(){
	char nor_oper;//������־ 
	char con_oper;//�Ƿ����������־
	Nor t(Pu_id); 
	while(1){
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<< "\t\t|                       1.�鿴��֧��Ϣ                     |\n";
        cout<< "\t\t|                       2.д����֧��Ϣ                     |\n";
        cout<< "\t\t|                       3.ɾ����֧��Ϣ                     |\n";
        cout<< "\t\t|                       4.�޸���֧��Ϣ                     |\n";
        cout<< "\t\t|                       5.ɾ���ó�Ա��Ϣ                   |\n";
        cout<< "\t\t|                       6.�˳�����                         |\n";
        cout<< "\t\t|----------------------------------------------------------|\n";
        cout<<"��ѡ����Ҫ���еĲ�����"; cin>>nor_oper; cin.sync();
		switch(nor_oper){
			case'1':{t.View();break;}
			case'2':{t.Write();break;}
			case'3':{t.Delete();break;}
			case'4':{t.Alter();break;}
			case'5':{Delete_all();return true;}
			case'6':{return 0;}
			default:{system("cls");cout<<"�����������������"<<endl; continue;}
		}
		cout<<endl;
		while(1){
			cout<<"�Ƿ�����Ըó�Ա���в�������Y/N����"; cin>>con_oper;cin.sync();system("cls");
		    if(con_oper == 'N' || con_oper == 'n') return 0;
		    else if(con_oper == 'Y' || con_oper == 'y') break;
		    else {cout<<"�����������������"<<endl;continue;}
		}
    }
}

//ɾ����ͥ��Ա��ȫ������ 
bool Adm::Delete_all(){
	Delete_login();//ɾ��Login_message�ļ��еĶ�Ӧ���� 
	Delete_member();//ɾ��Member_message�ļ��еĶ�Ӧ���� 
	Delete_finance();//ɾ��Finance_message�ļ��еĶ�Ӧ���� 
}

//ɾ����½��Ϣ 
bool Adm::Delete_login(){
	ifstream in("Login_message.txt",ios::in);
	string login;
	vector<string> logins;//�����������ͺ��������� 
	while(getline(in,login)){
		for(int i=0; i<login.length(); i++){
			if(login[i]==' '){//��ȡ��һ���ո�ǰ����ַ��� 
				if(login.substr(0,i) != Pu_id)
				 logins.push_back(login);//��������logins.push_back(login);//��������
				break;
			}
		} 
	}
	in.close();
	//��ȡ����ѡ����Pu_id��Ĵ����������
	 
	ofstream out("Login_message.txt",ios::out);
	vector<string>::iterator it = logins.begin();//������������ͺ͵�������ͬʱ����������ֵ 
	while(it!=logins.end()){
		out<<*it<<endl;
		it++;
	}
	out.close();
	//д�룬���ԭ�ļ��������������д���ļ��� 
}

//ɾ����Ա��Ϣ 
bool Adm::Delete_member(){
	ifstream in("Member_message.txt",ios::in);
	string member;
	vector<string> members;//�����������ͺ��������� 
	while(getline(in,member)){
		for(int i=0; i<member.length(); i++){
			if(member[i]==' '){//��ȡ��һ���ո�ǰ����ַ��� 
				if(member.substr(0,i) != Pu_id)
				 members.push_back(member);//��������logins.push_back(login);//��������
				break;
			}
		} 
	}
	in.close();
	//��ȡ����ѡ����Pu_id��Ĵ����������
	 
	ofstream out("Member_message.txt",ios::out);
	vector<string>::iterator it = members.begin();//������������ͺ͵�������ͬʱ����������ֵ 
	while(it!=members.end()){
		out<<*it<<endl;
		it++;
	}
	out.close(); 
	//д�룬���ԭ�ļ��������������д���ļ��� 
}

//ɾ��������Ϣ 
bool Adm::Delete_finance(){
	ifstream in("Finance_message.txt",ios::in);
	string finance;
	vector<string> finances;//�����������ͺ��������� 
	while(getline(in,finance)){
		for(int i=0; i<finance.length(); i++){
			if(finance[i]==' '){//��ȡ��һ���ո�ǰ����ַ��� 
				if(finance.substr(0,i) != Pu_id)
				 finances.push_back(finance);//��������logins.push_back(login);//��������
				break;
			}
		} 
	}
	in.close();
	//��ȡ����ѡ����Pu_id��Ĵ����������
	 
	ofstream out("Finance_message.txt",ios::out);
	vector<string>::iterator it = finances.begin();//������������ͺ͵�������ͬʱ����������ֵ 
	while(it!=finances.end()){
		out<<*it<<endl;
		it++;
	}
	out.close();
	//д�룬���ԭ�ļ��������������д���ļ��� 
} 
