//��ͨ��Ա���Խ��еĲ���ʵ��(����д�Լ����˻����鿴�Լ����˻���ɾ���Լ����˻�)

#include"Normal_class.h"
#include<fstream>
#include<vector>
using namespace std;

Nor::Nor(string id){
	ID = id;
	Num = 0;//����������ʼ����Ԥ������£�Num=num�� 
	ifstream in("Finance_message.txt",ios::in);
	if(!in){
		cerr<<"Ŀǰδ����֧��Ϣ"<<endl;
		return ;
	}
	
	string finance;//��ȡ���Ĳ�����Ϣ 
	while(getline(in,finance)){
		for(int i=0; i<finance.length(); i++){
			if(finance[i]==' '){
				if(finance.substr(0,i) == id){
					finances.push_back(finance);//���û�������Ϣ��������
					break;
				}
				else{
					other_finances.push_back(finance);//�����û�������Ϣ�������� 
					break;
				}
			}
		}
	}
	in.close();//�ر� Finance_message�ļ�
}
//�������������� 
bool Nor::New_vector(string id){
	ID = id;
	Num = 0;//����������ʼ����Ԥ������£�Num=num�� 
	ifstream in("Finance_message.txt",ios::in);
	finances.clear();
	string finance;
	while(getline(in,finance)){
		for(int i=0; i<finance.length(); i++){
			if(finance[i]==' '){
				if(finance.substr(0,i) == id){
					finances.push_back(finance);//��������
					break;
				}
				else break;
			}
		}
	}
	in.close();//�ر� Finance_message�ļ�
}

//�����ļ������� 
bool Nor::New_file(){
	ofstream out("Finance_message.txt",ios::out);//���ļ� 
	vector<string>::iterator other = other_finances.begin();//��������������Լ�������ָ��
	while(other!=other_finances.end()){
		out<<*other<<endl;//��������Ա����Ϣд���ļ�
		other++; 
	}
	vector<string>::iterator it = finances.begin();//��������������Լ�������ָ��
	while(it!=finances.end()){
		out<<*it<<endl;//���ó�Ա�޸ĺ����Ϣд���ļ�
		it++;
	}
	out.close();//�ر��ļ� 
}
//�鿴��֧��Ϣ 
bool Nor::View(){ 
	int i=1;//��� 
	vector<string>::iterator it = finances.begin();//������������ͺ͵�������ͬʱ����������ֵ 
	while(it!=finances.end()){
		cout<<i<<"  "<<*it<<endl;
		it++; i++;
	}
}

//��д��֧��Ϣ 
bool Nor::Write(){
	int year,mouth,day;
	char Kind;string Type_symbol; char Type;
	float account;
	
	char Judge;//�жϱ�־ 
	ofstream out("Finance_message.txt",ios::app);//׷�� 

		out<<ID<<" ";
		cout<<"�����뽻�׽���ʱ��(�� �� ��)��"; cin>>year;cin>>mouth;cin>>day; out<<"����ʱ��:"<<year<<" "<<mouth<<" "<<day<<" ";
		
		cout<< "\t\t|----------------------------------------------------------------|\n";
        cout<< "\t\t|                          1.����                                |\n";
        cout<< "\t\t|                          2.֧��                                |\n";
        cout<< "\t\t|----------------------------------------------------------------|\n";
		while(1){//ѡ���������֧�� 
            cout<<"��ѡ����Ҫ��¼�����ࣺ"; cin>>Kind;cin.sync();
			switch(Kind){
				case'1':{Type_symbol="income";break;}
				case'2':{Type_symbol="expen";break;}
				default:{cout<<"�����������������"<<endl;continue;}
			}
			break;
		}
		
		if(Type_symbol == "expen"){//֧�� 
			cout<< "\t\t|-----------------------------------------------------------------|\n";
            cout<< "\t\t|                            1.ʳ��                               |\n";
        	cout<< "\t\t|                            2.��ͨ                               |\n";
        	cout<< "\t\t|                            3.����                               |\n";
        	cout<< "\t\t|                            4.����                               |\n";
        	cout<< "\t\t|                            5.ѧϰ                               |\n";
        	cout<< "\t\t|                            6.ҽ��                               |\n";
        	cout<< "\t\t|                            7.����                               |\n";
        	cout<< "\t\t|-----------------------------------------------------------------|\n";
        	cout<<"��ѡ�����ͣ�"; cin>>Type; cin.sync();
			while(1){
		 	 switch(Type){
        		case'1':{out<<"����ԭ��"<<"ʳ��"<<" "; break;}
        		case'2':{out<<"����ԭ��"<<"��ͨ"<<" "; break;}
        		case'3':{out<<"����ԭ��"<<"����"<<" "; break;} 
        		case'4':{out<<"����ԭ��"<<"����"<<" "; break;}
        		case'5':{out<<"����ԭ��"<<"ѧϰ"<<" "; break;} 
        		case'6':{out<<"����ԭ��"<<"ҽ��"<<" "; break;} 
        		case'7':{out<<"����ԭ��"<<"����"<<" "; break;}
        		default:{cout<<"�����������������"<<endl; continue;} 
          	  }
          	  cout<<"�����뽻�׽��(Ԫ)��";
			  cin>>account; cin.sync();
			  out<<"���׽�"<<"-"<<account<<"Ԫ "<<"\n";
          	  break;
        	}
		}
		
		else {//���� 
			cout<< "\t\t|------------------------------------------------------------------|\n";
            cout<< "\t\t|                           1.����                                 |\n";
        	cout<< "\t\t|                           2.����                                 |\n";
        	cout<< "\t\t|------------------------------------------------------------------|\n";
        	cout<<"��ѡ�����ͣ�"; cin>>Type; cin.sync();
        	while(1){
		 	 switch(Type){
        		case'1':{out<<"����ԭ��"<<"����"<<" "; break;}
        		case'2':{out<<"����ԭ��"<<"����"<<" "; break;}
        		default:{cout<<"�����������������"<<endl; continue;} 
          	  }
          	  cout<<"�����뽻�׽��(Ԫ)��";
			  cin>>account; cin.sync();
			  out<<"���׽�"<<"+"<<account<<"Ԫ "<<"\n";
          	  break;
        	}
		}
		out.close();
		
	New_vector(ID);//�������������ݣ����ļ��ڶ���) 
}

bool Nor::Delete(){//ɾ������ 
	int purpose;
	View();
	cout<<"����������Ҫɾ������֧��Ϣ��ţ�";
	while(1){
		cin>>purpose; cin.sync();
		if(purpose>finances.size()||purpose<=0){
			cout<<"����������������룺";
			continue;
		}
		break;
	}
	finances.erase(finances.begin()+purpose-1);
	New_file();//�����ļ���Ϣ 
}

//�޸���֧��¼ 
bool Nor::Alter(){
	int purpose;
	View();
	cout<<"����������Ҫ�޸ĵ���֧��Ϣ��ţ�";
	while(1){
		cin>>purpose; cin.sync();
		if(purpose>finances.size()||purpose<=0){
			cout<<"����������������룺";
			continue;
		}
		break;
	}
	finances.erase(finances.begin()+purpose-1);
	New_file();
	cout<<"�������޸ĺ����֧��Ϣ��"<<endl;
	Write();
}
