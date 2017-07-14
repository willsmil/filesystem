#include "filesystem.h"
#include <iostream>
using namespace std;

command cmd[17];

/*����*/
void help()          //��ʾ������Ϣ
{
	printf("ע�⣺�������ļ����� < 100\n"); //˵���ļ�
	printf("0.��ʼ��-------------------------format\n");
	printf("1.�鿴��ǰĿ¼�ļ��б�-----------dir\n");
	printf("2.�鿴�ļ���Ϣ-------------------cat-----(cat + �ո� + �ļ���)  \n");
	printf("3.�鿴ϵͳ��Ϣ-------------------ls    \n");
	printf("4.����Ŀ¼-----------------------md------(md  + �ո� + Ŀ¼��)  \n");
	printf("5.�����ļ�-----------------------vi------(vi  + �ļ��� + �ļ����� + Ȩ��)\n");
	printf("6.ɾ���ļ�-----------------------del-----(del + �ո� + �ļ���) \n");
	printf("7.���ļ�-----------------------open----(open + �ո� + �ļ���) \n");
	printf("8.�ر��ļ�-----------------------close---(close + �ո� + �ļ���) \n");
	printf("9.��ȡ�ļ�-----------------------read----(read + �ո� + �ļ���) \n");
	printf("10.д���ļ�----------------------write---(write + �ո� + �ļ���+ �ո� + д���ַ�)\n");
	printf("11.ɾ��Ŀ¼----------------------deldir--(deldir + �ո� + Ŀ¼��)\n");
	printf("12.���뵱ǰĿ¼�µ�ָ��Ŀ¼------cd------(cd + �ո� + Ŀ¼��)\n");
	printf("13.������һ��Ŀ¼----------------cd..  \n");
	printf("14.��ʾ��������------------------help  \n");
	printf("15.�˳��ļ�ϵͳ------------------quit  \n");
	printf("16.�˳���¼----------------------logout  \n");
}

/*������*/
void main()          //������
{
	char tmp[10], com[10], tmp1[10];
	struct command tmp2[10];
	int i, j = 0, p, len = 0;
	FILE *fp;
	//if ((fp = fopen("filesave", "rb")) != NULL)
	//	read_user(fp);
	//login or register

	//printf("loginid %d\n",login_userid);

	strcpy(cmd[0].com, "format");    //�����������������
	strcpy(cmd[1].com, "dir");
	strcpy(cmd[2].com, "cat");
	strcpy(cmd[3].com, "ls");
	strcpy(cmd[4].com, "md");
	strcpy(cmd[5].com, "vi");
	strcpy(cmd[6].com, "del");
	strcpy(cmd[7].com, "deldir");
	strcpy(cmd[8].com, "cd");
	strcpy(cmd[9].com, "cd..");
	strcpy(cmd[10].com, "help");
	strcpy(cmd[11].com, "quit");
	strcpy(cmd[12].com, "open");
	strcpy(cmd[13].com, "read");
	strcpy(cmd[14].com, "write");
	strcpy(cmd[15].com, "logout");
	strcpy(cmd[16].com, "close");
	if ((fp = fopen("filesave", "rb")) == NULL)   //�ж�ϵͳ�ļ��Ƿ����
	{
		printf("can not open file\n");
		printf("format the disk   \n");
		Sleep(500);
		format();
	}
	else
	{
		read_file(fp);       //��ȡϵͳ�ļ�������
	}
	//ע���½
	while (1) {
		int log_com;
		cout << "1------login" << endl;
		cout << "2------register" << endl;
		cin >> log_com;
		switch (log_com) {
		case 1:login(); break;
		case 2:reg(); break;
		default:cout << "unknown command" << endl;
		}
		if (login_userid != -1)
			break;
	}
	help();
	while (1)
	{
		j = 0;         //�������¸��ָ�0�������
		strcpy(tmp, cur_dir);
		while (strcmp(tmp, "filsystem") != 0)
		{
			for (i = 0; i<640; i++)
			{
				p = root[i].i_num;
				if (strcmp(tmp, root[i].file_name) == 0 && (i_node[p].file_style == 0))
				{
					strcpy(tmp2[j].com, tmp);
					j++;
					strcpy(tmp, root[i].dir_name);
				}
			}
		}

		strcpy(tmp2[j].com, tmp);
		for (i = j; i >= 0; i--)
		{
			printf("%s/", tmp2[i].com);
		}

		scanf("%s", com);       //��������Ҳ����������ز���
		for (i = 0; i<17; i++)
		{
			if (strcmp(com, cmd[i].com) == 0)
			{
				p = i;
				break;
			}
		}
		if (i == 17)         //���û���������Ժ����������͵�һ�������Ч��һ��
		{
			p = -1; //����һ��ֵ
		}
		switch (p)
		{
		case 0: format();       //��ʼ��
			break;
		case 1: display_curdir();     //�鿴��ǰĿ¼�µ��ļ��б�
			break;
		case 2: scanf("%s", tmp);     //�鿴�ļ�
			show_file(tmp);
			break;
		case 3: display_sys();      //�鿴ϵͳ��Ϣ
			break;
		case 4:scanf("%s", tmp);      //����Ŀ¼
			create_dir(tmp);
			break;
		case 5: scanf("%s", tmp);     //�����ļ�
			scanf("%d", &len);
			int limit;
			scanf("%d", &limit);
			create_file(tmp, len, login_userid, limit);
			break;
		case 6: scanf("%s", tmp);     //ɾ���ļ�
			for (i = 0; i<640; i++)     //�ж��ļ��ǲ��������ļ�
			{
				j = root[i].i_num;
				if (strcmp(tmp, root[i].file_name) == 0 && (i_node[j].file_style) == 1)
				{
					del_file(tmp);
					break;
				}
			}
			if (i == 640)
			{
				printf("������������ļ��ļ�\n");
			}
			break;
		case 7:
			scanf("%s", tmp);     //ɾ��Ŀ¼
			del_dir(tmp);
			break;
		case 8: scanf("%s", tmp1);     //���뵱ǰĿ¼�µ�ָ��Ŀ¼   �൱�ڽ���Ŀ¼  cd  +  Ŀ¼��
			display_dir(tmp1);
			break;
		case 9: back_dir();       //������һ��Ŀ¼
			break;
		case 10:help();
			break;
		case 11:write_file(fp);      //������������Ϣд��ϵͳ�ļ����˳�
			system("pause");
		case 12:scanf("%s", tmp);
			open(tmp);
			break;
		case 13:scanf("%s", tmp);
			read(tmp);
			break;
		case 14: {
			scanf("%s", tmp);
			getchar();
			string writec;
			cin >> writec;
			write(tmp, writec);
			break; }
		case 15:write_file(fp);
			logout();
			int l;
			for (l = 0; l<8; l++)
			{
				file_array[l] = -1;
			}
			file_array_head = 0;
			login();
			help();
			break;
		case 16:scanf("%s", tmp);
			close(tmp);
			break;

		default:printf("SORRY,û���������\n");
			break;
		}
	}
	system("pause");
}