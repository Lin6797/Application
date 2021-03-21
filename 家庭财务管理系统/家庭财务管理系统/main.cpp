#include "Commual_class.h"
#include "Normal_class.h"
#include "Administrate_class.h"
#include<vector>
#include<fstream>
#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int Length; 
//����Ա��ȡȫԱ�û��� 
string* Get_ID(){
	string* ID;//�洢�û���������
	int Num=0;//�û����� 
	ifstream in("Login_message.txt",ios::in);//��Login_message�ļ�����ȡȫ���û����� 
	if(!in){//��ʧ��ʱ�� 
		cerr<<"���ļ�ʧ��"<<endl;
		return NULL;
	}
	
	string Login;//�����ȡ����Ϊstring 
	vector<string> Logins;//����Login�������ͺ��������� 
	while(getline(in,Login)){
		Num++;//Ŀǰ�û���Ŀ 
		Logins.push_back(Login);//ȫ����½��Ϣ��������
	}
	in.close();//�ر�Login_message�ļ�
	
	ID = new string[Num]; 
	int num=0;//ID���
	vector<string>::iterator it = Logins.begin();//����itΪ����logins�ĵ�����
	for(;it!=Logins.end();it++){//��ʼ���б��� 
		for(int i=0; i<(*it).length(); i++){
			if((*it)[i]==' '){
				ID[num] = (*it).substr(0,i);//��ȡ��һ���ո�ǰ���ַ���,���ID 
				break;
			}
		}
		num++; 
	}//�õ������û����û���
	extern int Length;
	Length=Num;
	return ID;//����ID���� 
}

//����Աѡ��������� 
string Choice(){
	string *ID;//�û������� 
	ID = Get_ID();//���ID����
	int no=0;//����û����ı�� 
	int purpose;//Ŀ���û����ı�� 
	while(1){
		cout<<"    -------------------------------------------------------------"<<endl;
	    for(; no<Length; no++){//���������û��� 
		     cout<<"    |                  "<<no+1<<"."<<ID[no]<<endl; 
	    }
	    cout<<"    |                  "<<no+1<<"."<<"�˳�����"<<endl;
	    cout<<"    -------------------------------------------------------------"<<endl;
	    no=0;//��ʼ��no 
	    cout<<"��ѡ������Ҫ���в������û���"; cin>>purpose;cin.sync();
	    if(purpose>0 && purpose<=Length)
	    	return ID[purpose-1];//�õ���Ӧ���û���
	    else if(purpose==Length+1) exit(1);
	    else {system("cls"); cout<<"�������ݴ�������������"<<endl;continue;}
	}
}


int main(int argc, char** argv) { 
	string id;//��½���˺��û���
	string type;//��½���˺����� 
	
	Commual c; //��½/ע��/�޸�������� 
	char operation;//ѡ��Ĳ���

	while(1){
	   string c_judge = "down";//ֱ������
	   system("cls");
	   cout<< "\t\t|-------------------------------------------------------|\n";
       cout<< "\t\t|                       1.��½                          |\n";
       cout<< "\t\t|                       2.ע��                          |\n";
       cout<< "\t\t|                       3.�˳�ϵͳ                      |\n";
       cout<< "\t\t|-------------------------------------------------------|\n";
	   cout<<"��ѡ����Ҫ���еĲ�����"; cin>>operation; cin.sync();
	   switch (operation){
	   	   case '1':{//��½ 
	   	    	system("cls");
				cout<<"**********[��½]**********"<<endl;
	   		    id = c.Login();
	   		    break;
	   	      }
	   	    case'2':{//ע�� 
	   	      	system("cls");
				cout<<"**********[ע��]**********"<<endl;
	   	      	c.Resgin(); c_judge = "up";//������ 
				break;
	   	      }
	   	    case'3':{
	   	    	system("cls");
				cout<<"*********[�˳�ϵͳ]*********"; 
	   	    	return 0;
	   	       }
	   	    default:{
	   	    	cout<<"�������"; 
                continue;	
	   	       } 
	   }
	   if(c_judge == "up") continue;
	   else break;
    }
    
	type = id.substr(id.length()-1,1);//�˺����� 
    id = id.substr(0,id.length()-1);//��½�˺��û���
	
	if(type=="N"){//��ͨ�˻� 
		Nor n(id); char nor_oper; char con_oper;//�Ƿ����������־ 
        while(1){
        	cout<< "\t\t|----------------------------------------------------------|\n";
            cout<< "\t\t|                       1.�鿴��֧��Ϣ                     |\n";
            cout<< "\t\t|                       2.д����֧��Ϣ                     |\n";
            cout<< "\t\t|                       3.ɾ����֧��Ϣ                     |\n";
            cout<< "\t\t|                       4.�޸���֧��Ϣ                     |\n";
            cout<< "\t\t|                       5.�˳�ϵͳ                         |\n";
            cout<< "\t\t|----------------------------------------------------------|\n";
        	cout<<"��ѡ����Ҫ���еĲ�����"; cin>>nor_oper; cin.sync();
		    switch(nor_oper){
			    case'1':{n.View();break;}
			    case'2':{n.Write();break;}
			    case'3':{n.Delete();break;}
			    case'4':{n.Alter();break;}
			    case'5':{return 0;}
			    default:{system("cls");cout<<"�����������������"<<endl; continue;}
		    }
		    cout<<endl;
		    while(1){
			    cout<<"�Ƿ�������в�������Y/N����"; cin>>con_oper;cin.sync();system("cls");
		        if(con_oper == 'N' || con_oper == 'n') return 0;
		        else if(con_oper == 'Y' || con_oper == 'y') break;
		        else {cout<<"�����������������"<<endl;continue;}
		    }
        }
	}
	
	else{//����Ա�˻� 
		system("cls"); 
		char con_oper;//�Ƿ����������־ 
        while(1){
        	string Pu_id = Choice();//��ò�������ID 
        	if(Pu_id==id){//�������Ϊ����Ա�Լ� 
				Adm A(Pu_id, "Self");//��Ŀ���û����û����ͱ�־"Self"�������Ա���� 
        	}
        	else{//�������Ϊ���˹���Ա֮����� 
        		Adm A(Pu_id, "Other");//��Ŀ���û����û����ͱ�־"Other"�������Ա���� 
        	}
        	cout<<"�Ƿ�ѡ��������ͥ��Ա�������в�������Y/N����";
        	while(1){//�ж��Ƿ�ѡ��������Ա���в���
        		cin>>con_oper; cin.sync();
        		if(con_oper=='y' || con_oper=='Y'){
        			break;
        		}
        		else if(con_oper=='n' || con_oper=='N'){
        			return 0;
        		}
        		else{
        			cout<<"�����������������";
        			continue;
        		}
        	}//�ж��Ƿ�ѡ��������Ա���в������� 
        }
	}
	 
	return 0;
}

