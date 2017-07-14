#include "filesystem.h"

node i_node[640];
dir root[640];
char cur_dir[10] = "filsystem";

/*��ʾ��ǰĿ¼�µ��ļ��б�*/
void display_curdir(){
	int i, k;
	cout << "�û�����" << user_array[login_userid].username << endl;
	printf("\t\t�ļ�����  �ļ�����  �ļ�����  ����Ŀ¼\n");
	for (i = 0; i<640; i++)
	{
		if (strcmp(cur_dir, root[i].dir_name) == 0 && i_node[root[i].i_num].file_UserId == login_userid)   //��ѯ�ļ��� ����Ŀ¼��Ϣ�͵�ǰĿ¼��Ϣ��ͬ������
		{
			k = root[i].i_num;
			printf("\t\t  %s\t", root[i].file_name);  //�ļ���
			printf("\t%d\t", i_node[k].file_style);  //�ļ�������
			printf("%d\t", i_node[k].file_length);  //�ļ��ĳ���
			printf("%s\n", root[i].dir_name);   //�ļ����ڵ�Ŀ¼
		}
	}
}

/*����ָ����Ŀ¼*/
void display_dir(char filename[]){
	int i, k;
	for (i = 0; i<640; i++)
	{
		k = root[i].i_num;    //printf("i_node[%d].file_UserId %d,login_userid %d",k,i_node[k].file_UserId,login_userid)  ; //�ж��ļ������ǲ���Ŀ¼����
		if ((strcmp(filename, root[i].file_name) == 0) && (i_node[k].file_style == 0) && (i_node[k].file_UserId == login_userid))
		{//printf("yes\n");
			strcpy(cur_dir, filename); //printf("cur_dir= %s\n",cur_dir);   //��Ҫ�����ָ��Ŀ¼����Ϊ��ǰĿ¼  ��ֵ��Ҫ����strcpy(Ŀ�ģ�Դ)
			return;
		}
	}
	if (i == 640)
	{
		printf("��¼�û�û�����Ŀ¼\n");
	}
}

/*������һ��Ŀ¼*/
void back_dir(){
	int  i, k;
	for (i = 0; i<640; i++)       //��ѯ�͵�ǰĿ¼����ͬ��Ŀ¼�ļ���
	{
		k = root[i].i_num;
		if (strcmp(cur_dir, root[i].file_name) == 0 && (i_node[k].file_style == 0))
		{
			strcpy(cur_dir, root[i].dir_name); //����ѯ����Ŀ¼�ļ���  ���ڵ�Ŀ¼��ֵ����ǰĿ¼
		}
	}
}

/*����Ŀ¼*/
void create_dir(char filename[]){
	style = 0;         //0�����ļ�������Ŀ¼�ļ�
	create_file(filename, 4, login_userid, -1);
	style = 1;         //����ָ���ֵ����Ϊȫ�ֱ���������
}

/*ɾ��Ŀ¼*/
void del_dir(char filename[]){
	int i, j, k;
	for (i = 0; i<640; i++)       //��Ҫ�������ж�Ҫɾ����Ŀ¼�ǲ��ǵ�ǰĿ¼
	{
		k = root[i].i_num;      //�ҵ�Ŀ¼����
		if (strcmp(root[i].file_name, filename) == 0 && strcmp(cur_dir, filename) != 0 && (i_node[k].file_style) == 0)
		{

			for (j = 0; j<640; j++)
			{
				if (strcmp(filename, root[j].dir_name) == 0)
				{
					printf("Ŀ¼��Ϊ�ղ���ֱ��ɾ��\n");
					break;
				}
			}
			if (j == 640 || i_node[root[i].i_num].file_UserId == login_userid)
			{
				del_file(filename);
				break;
			}

			break;
		}
	}
	if (i == 640)
	{
		printf("�������Ŀ¼�ļ� �����ѵ�¼�û����������Ŀ¼,������Ҫɾ�����ǵ�ǰĿ¼\n");
	}
}
