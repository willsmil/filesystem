#include <string>
#include "filesystem.h"
using namespace std;

user user_array[8];
int login_userid = -1;
int user_num = 0;

/*ע��*/
void reg(){
	string tempusername;
	string temppassword;
	if (user_num<9)
	{
		cout << "-----ע��-----" << endl;
		while (1) {
			cout << "�û�����";
			cin >> tempusername;
			int i;
			for (i = 0; i<user_num; i++)//�ж��Ƿ�����
			{
				if (user_array[i].username == tempusername) {
					cout << "�û����Ѵ���" << endl;
					break;
				}
			}
			if (i == user_num)
				break;
		}
		user_array[user_num].username = tempusername;
		cout << "���룺";
		cin >> temppassword;
		user_array[user_num].password = temppassword;
		user_num++;
	}
	else {
		cout << "ע��������" << endl;
	}
}

/*��½*/
int login() {
	cout << "-----��½-----" << endl;
	string  getusername;
	string  getpassword;
	cout << "�û�����";
	cin >> getusername;
	cout << "���룺";
	cin >> getpassword;
	int i;
	if (user_num == 0) {
		cout << "�û��������벻��ȷ" << endl;
		return 0;
	}
	else {
		for (i = 0; i < user_num; i++) {
			if (getusername == user_array[i].username && getpassword == user_array[i].password) {
				login_userid = i;
				cur_user = getusername;
				cout << "��½�ɹ�" << endl;
				return 1;
			}
			else {
				continue;
			}
			cout << "�û��������벻��ȷ" << endl;
			return 0;
		}
	}
}

/*�˳�*/
void logout(){
	printf(" \n                        Logouting");
	for (int a = 0; a<4; a++)
	{
		Sleep(500);
		printf(".");
	}
	system("cls");
}
