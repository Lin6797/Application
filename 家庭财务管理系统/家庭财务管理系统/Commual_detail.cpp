//ʵ��Commul��

#include"Commual_class.h"
#include<fstream>
#include<vector> 
using namespace std;

//���캯�� 
Commual::Commual(){ 
	Num=0; //��ʼ���������Ԫ�ظ���

	ifstream in("Login_message.txt",ios::in);//��Login_message�ļ� 
	if(!in){//��ʧ��ʱ�� 
		cerr<<"��ʱϵͳΪ���û�,�����Ƚ���ע��"<<endl;
		Resgin();
		return ;
	}
	
	string login;//�����ȡ����Ϊstring 
	while(getline(in,login)){
		Num++;
		logins.push_back(login);//�������� 
	}
	in.close();//�ر�Login_message�ļ� 
	
	ID = new string[Num];
	Passcode = new string[Num];
	IsAdm = new string[Num];
	int num=0;//����Ԫ�ر��  
	string Judge="name";//�жϻ�õ��ַ������� 
	
	vector<string>::iterator it = logins.begin();//����itΪ����logins�ĵ�����
	for(;it!=logins.end();it++){//��ʼ���зָ� 
		int start=0;//�����ַ�������ʼλ��
		for(int i=0; i<(*it).length(); i++){
			if((*it)[i]==' ' && Judge=="name"){
				ID[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "passcode";
			}
			else if((*it)[i]==' ' && Judge=="passcode"){
				Passcode[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "IsAdm";
			}
			else if((*it)[i]==' ' && Judge=="IsAdm"){
				IsAdm[num] = (*it).substr(start,i-start);
				start = i; Judge = "name";
			}
		}
		num++;
	}
}

//���º���
bool Commual::New(){ 
	Num=0; //��ʼ���������Ԫ�ظ���
	logins.clear();
	ifstream in("Login_message.txt",ios::in);//��Login_message�ļ� 
	if(!in){//��ʧ��ʱ�� 
		cerr<<"��ʱ�ļ�Ϊ��"<<endl;
		Resgin();
		return false;
	}
	
	string login;//�����ȡ����Ϊstring 
	while(getline(in,login)){
		Num++;
		cout<<"Num:"<<Num<<endl;
		logins.push_back(login);//�������� 
	}
	in.close();//�ر�Login_message�ļ� 
	
	ID = new string[Num];
	Passcode = new string[Num];
	IsAdm = new string[Num];
	int num=0;//����Ԫ�ر��  
	string Judge="name";//�жϻ�õ��ַ������� 
	
	vector<string>::iterator it = logins.begin();//����itΪ����logins�ĵ�����
	for(;it!=logins.end();it++){//��ʼ���зָ� 
		int start=0;//�����ַ�������ʼλ��
		for(int i=0; i<(*it).length(); i++){
			if((*it)[i]==' ' && Judge=="name"){
				ID[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "passcode";
			}
			else if((*it)[i]==' ' && Judge=="passcode"){
				Passcode[num] = (*it).substr(start,i-start);
				start = i+1; Judge = "IsAdm";
			}
			else if((*it)[i]==' ' && Judge=="IsAdm"){
				IsAdm[num] = (*it).substr(start,i-start);
				start = i; Judge = "name";
			}
		}
		num++;
	}
	return true;
}

//ע��
bool Commual::Resgin(){
	string in_ID, in_Pass1, in_Pass2; //������û��������� 
	char in_IsAdm; //������ж��Ƿ�Ϊ����Ա 
	
	string Judge;//��Ϊĳ�����ıȽ���ɵı�־
	ofstream out_login("Login_message.txt",ios::app);//���ļ������ں������� 
	while(1){ //�ж��û����Ƿ��������
		cout<<"�������û�����";cin>>in_ID; 
		Judge = "equal";
		for(int i=0; i<Num; i++){
			if(ID[i] == in_ID){ //������Ҫ��
				cout<<"���û����ѱ�ʹ�ã�����������"<<endl;
				Judge = "inequal"; break;
			}
		}
		if(Judge == "equal"){ //����Ҫ�� 
			out_login<<in_ID<<" "; break;
		}
	}
	
	while(1){ //�ж������Ƿ�������� 
		cout<<"���������룺"; cin>>in_Pass1;
		cout<<"���ٴ��������룺"; cin>>in_Pass2;
		Judge = "equal";
		if(in_Pass1 != in_Pass2){
			cout<<"��������벻ͬ������������"<<endl;
			Judge = "inequal";
		}
		if(Judge == "equal"){
			out_login<<in_Pass1<<" "; break; 
		}
	}
	
	//�ж�������Ĺ���Ա�жϱ�־ 
	cout<<"�ó�Ա�Ƿ�Ϊ����Ա����y/n��:"; cin>>in_IsAdm;
	if(in_IsAdm=='y' || in_IsAdm=='Y'){
		Judge="equal";
		for(int i=0; i<Num; i++){
			if(IsAdm[i] == "Y"){//�Ѿ����ڹ���Ա 
				cout<<"�Ѿ����ڹ���Ա���ʲ��ɳ�Ϊ����Ա"<<endl;
				out_login<<"N"<<" "<<"\n"; Judge="inequal"; break;
			}
		}
		if(Judge == "equal")//�����ڹ���Ա 
		out_login<<"Y"<<" "<<"\n";
	}
	else if(in_IsAdm=='n' || in_IsAdm=='N'){
		out_login<<"N"<<" "<<"\n";
	}
	
	out_login.close();
	//��Login_message�ļ��������Ϣ���
	 
	//��ʼ��Member_messahe����ӳ�Ա��Ϣ
	string name,sex,age,weight,height;//���ָ�����Ϣ
	int birth_year,birth_mouth,birth_day;//���������� 
	 
	ofstream out("Member_message.txt",ios::app);//���ļ�
	out<<in_ID<<" "; 
	cout<<"��������ʵ������"; cin>>name; out<<name<<" ";
	cout<<"�������Ա�(��/Ů)��"; cin>>sex; out<<sex<<" ";
	cout<<"��������������գ��� �� �գ���"; cin>>birth_year; cin>>birth_mouth; cin>>birth_day;  out<<birth_year<<" "<<birth_mouth<<" "<<birth_day<<" ";
	cout<<"���������䣺"; cin>>age; out<<age<<" ";
	cout<<"���������أ�kg��:"; cin>>weight; out<<weight<<" ";
	cout<<"��������ߣ�m����"; cin>>height; out<<height<<" "<<"\n";
	out.close();
	
	New();
	return true; 
}

//��½
string Commual::Login(){
	string id,passcode;//������ȡ���û��������� 
	
	while(1){
		string Judge="inexist";//�ж�������û����Ƿ���ڵı�־ 
	    cout<<"�������û�����";cin>>id;
	    cout<<"���������룺";cin>>passcode;
		
		for(int i=0; i<Num; i++){
			if(ID[i]==id){
				Judge="exist";//�����и��û���
				if(Passcode[i]==passcode){//��¼�ɹ� 
					if(IsAdm[i]=="Y"){
						system("cls");
						cout<<"��½����Ա�˺ųɹ�"<<endl;//������õģ�����ǵ�ɾ��
						return id+IsAdm[i]; 
					}
					else{
						system("cls");
						cout<<"��½��ͨ��Ա�˺ųɹ�"<<endl;
						return id+IsAdm[i];
					}
				}
				else{//����������� 
					system("cls"); 
					cout<<"**********[��½]**********"<<endl;
					cout<<"���������������������"<<endl;
					break;
				}
			}
		}//forѭ������ 
		if(Judge=="inexist"){
			system("cls");
			cout<<"**********[��½]**********"<<endl;
			cout<<"���û��������ڣ�����������"<<endl;
		}
	}
}

//�޸�����
bool Commual::c_passcpde(){
	string pu_ID,new_Pass1,new_Pass2;//Ҫ�޸�����Ķ���������� 
	string Judge; string origin_passcode;
	while(1){
		cout<<"�������û�����"; cin>>pu_ID;
		Judge = "inexist";
		for(int i=0; i<Num; i++){
			if(ID[i] == pu_ID){//������Ҫ�޸ĵ� 
			    Judge = "exist";
			    while(1){//�ж������ԭ������ȷ��� 
			    	cout<<"������ԭ����:";cin>>origin_passcode;cin.sync();
			    	if(origin_passcode == Passcode[i]){//��ȷ�����Կ�ʼ׼���޸����� 
					    while(1){//�ж�������������ͬ��� 
					        cout<<"�����������룺"; cin>>new_Pass1; cin.sync();
			    		    cout<<"����һ�����������룺"; cin>>new_Pass2; cin.sync();
			    		    if(new_Pass1 == new_Pass2){ //��ͬ��ɹ��޸� 
			    		    	Passcode[i]=new_Pass1;
			    		    	cout<<"******�޸ĳɹ�********"<<endl;
								return true;//����������� 
			    		    }
			    		    else{//��ͬ�򷵻��������� 
			    		    	system("cls");
			    		    	cout<<"�޸Ķ���Ϊ��"<<pu_ID<<endl;
			    		    	cout<<"��������������벻һ�£�����������"<<endl;
			    		    }
						}
						break;//�����޸ĳ�����ֱ�������ж�����ԭ�����Ƿ�ͬ��ѭ�� 
			    	}
			    	else{//����ȷ������������������ 
			    	   system("cls");
			    	   cout<<"��ԭ���벻һ�£�����������"<<endl;
					}
			    }
			}
			//else (�����еģ�����û��Ҫ) 
		} 
		if(Judge == "inexist"){
			cout<<"���û��������ڣ�����������"<<endl;
			continue;
		}
	}
}
bool Commual::c_write(){
	ofstream out("Login_message.txt",ios::out);
	for(int i=0; i<Num; i++){
		out<<ID[i]<<" "<<Passcode[i]<<" "<<IsAdm[i]<<" "<<endl;
	}
	out.close();
}
