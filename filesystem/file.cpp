#include "filesystem.h"

int style = 1;			//�ļ�������
int file_array_head;	//�ļ�����ͷ
int physic[100];		//�ļ���ַ������
string cur_user;		//��ǰ�û�
int file_array[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };  //���ļ�����
node temp_file;
string temp_write;

/*�����ļ�*/
void create_file(char filename[], int length, int userid, string limit){
	int i, j;
	for (i = 0; i<640; i++)
	{
		//�ж�����
		if (strcmp(filename, root[i].file_name) == 0)
		{
			printf("�Ѿ�����ͬ���ļ������������������ļ�\n");
			return;
		}
	}
	for (i = 0; i<640; i++)
	{
		//�ҵ����п�
		if (root[i].i_num == -1)
		{
			root[i].i_num = i;
			strcpy(root[i].file_name, filename);
			strcpy(root[i].dir_name, cur_dir);  //�ѵ�ǰĿ¼�� ���½������ļ�
			i_node[i].file_style = style;//style==0 ˵���ļ���Ŀ¼�ļ�
			i_node[i].file_length = length;
			i_node[i].limit = limit;
			i_node[i].file_UserId = userid; 
			allot(length);
			for (j = 0; j<length; j++)
			{
				i_node[i].file_address[j] = physic[j];
			}

			//��ʼ���ļ�
			for (int add = 0; add < 100; add++)
				for (int c = 0; c < length; c++) {
					memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
				}
			int u;
			for (u = 0; u<100; u++)//��������ջ�����
			{
				physic[u] = -1;
			}
			break;
		}
	}
}

/*ɾ���ļ�*/
void del_file(char filename[])     {
	int i, j, k;
	for (i = 0; i<640; i++)
	{

		if ((strcmp(filename, root[i].file_name) == 0) && (strcmp(cur_dir, root[i].dir_name) == 0) && (i_node[root[i].i_num].file_UserId == login_userid))
		{
			int add, c;
			for (add = 0; add<i_node[root[i].i_num].file_length; add++)//�ļ��������
			{
				for (c = 0; memory[i_node[root[i].i_num].file_address[add]].content[c] != '\0'; c++)
				{
					memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
				}
			}
			k = root[i].i_num; 
			i_node[k].file_UserId = -1;
			i_node[k].limit = "";
			for (j = 0; j<i_node[k].file_length; j++)
			{
				physic[j] = i_node[k].file_address[j];
			}
			callback(i_node[k].file_length); //���� ���պ���
			int u;//��������ջ�����
			for (u = 0; u<100; u++)
			{
				physic[u] = -1;
			}
			for (j = 0; j<100; j++)     //ɾ���ļ���Ҫ���ļ����Ժ�Ŀ¼��ĸ���ֵ�ָ���ֵ
			{
				i_node[k].file_address[j] = -1; //�ļ�ռ�õĿ�ŵ�ַ�ָ���ֵ
			}
			strcpy(root[i].file_name, "");  //�ļ����ָ���ֵ
			root[i].i_num = -1;				//Ŀ¼���I�����Ϣ�ָ���ֵ
			strcpy(root[i].dir_name, "");	//Ŀ¼����ļ�Ŀ¼��Ϣ�ָ���ֵ
			i_node[k].file_length = -1;		//�ļ����Ȼָ�
			i_node[k].file_style = -1;		//�ļ����ͻָ���ֵ
			break;
		}
	}
	if (i == 640)
	{
		printf("��¼�û��ĸ�Ŀ¼�²���������ļ�\n");
	}
}

/*���ļ�*/
int open(char filename[10]){
	int i;
	for (i = 0; i<640; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_num].file_style == 1 && i_node[root[i].i_num].file_UserId == login_userid)
		{
			if (file_array_head<8)
			{
				file_array[file_array_head] = root[i].i_num;
				file_array_head++;
			}
			else
			{
				printf("�򿪵��ļ��Ѵ����ޣ��޷��򿪱��ļ�\n");
			}
			return root[i].i_num;
		}
	}
	if (i = 640)
	{
		printf("��Ҫ�򿪵��ļ������ڻ����ڸ��û�\n");
	}
	return 0;
}

/*�ر��ļ�*/
void close(char filename[10]){
	int i;
	for (i = 0; i<640; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_num].file_style == 1 && i_node[root[i].i_num].file_UserId == login_userid)
		{
			int j;
			for (j = 0; j<file_array_head; j++)
			{
				if (root[i].i_num == file_array[j])
				{
					int m;
					for (m = j; m<file_array_head; m++)
					{
						file_array[m] = file_array[m + 1];
					}
					file_array_head--;
					return;
				}
			}
			if (j == file_array_head)
			{
				printf("��Ҫ�رյ��ļ�δ�򿪹���\n");
			}
			return;
		}
	}
	if (i = 640)
	{
		printf("��Ҫ�رյ��ļ������ڻ����ڸ��û�\n");
	}
	return;
}

/*��ȡ�ļ�*/
int read(char filename[10]){
	int i;
	for (i = 0; i<640; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_num].file_style == 1)
		{
			int j;
			for (j = 0; j<8; j++)
			{          
				if (root[i].i_num == file_array[j])
				{
					if (i_node[root[i].i_num].limit == "o+r+w" || i_node[root[i].i_num].limit == "o+r")
					{
						int c, add;
						for (add = 0; add < 100; add++) {
							temp_write= memory[i_node[root[i].i_num].file_address[add]].content;
							if (temp_write.length() != 0)
								break;
						}
						printf("\n ");
					}
					else
					{
						printf("��û��Ȩ�޶�ȡ�ļ����ݣ���\n");
					}
					return 0;
				}
			}
			if (j == 8)
			{
				printf("\n  ���ļ�δ�򿪣����ȴ��ļ��ٽ��ж�д����!!\n");
			}
			return 0;
		}
	}
	if (i == 640)
	{
		printf("��Ҫ��ȡ���ļ�������\n");
	}
	return 0;
}
void show_file_content() {
	cout << "�ļ�����Ϊ��";
	cout << temp_write << endl;
}
/*д���ļ�*/
void write(char filename[10], string writec){
	int i;
	for (i = 0; i<640; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_num].file_style == 1)
		{
			int j; 
			for (j = 0; j<8; j++)
			{
				if (root[i].i_num == file_array[j])
				{
					if (i_node[root[i].i_num].limit == "o+r+w" || i_node[root[i].i_num].limit == "o+w")
					{
						int c, add, write_length;
						for (add = 0; add<100; add++)
						{
							for (c = 0; c<1000; c++)
							{
								if (memory[i_node[root[i].i_num].file_address[add]].content[c] == '\0')
								{
									for (write_length = 0; write_length < writec.length() && c<1000; c++, write_length++) {
										memory[i_node[root[i].i_num].file_address[add]].content[c] = writec[write_length];
									}
									return;
								}
							}
						}
						if (add == 100)
						{
							printf("\n�ļ��ռ�������д��ʧ�ܣ���\n");
						}
						return;
					}
					else
					{
						printf("��û��Ȩ�޽�����д���ļ�����\n");
						return;
					}
					return;
				}
			}
			if (j == 8)
			{
				printf("\n  ���ļ�δ�򿪣����ȴ��ļ��ٽ��ж�д����!!\n");
			}
			return;
		}
	}
	if (i == 640)
	{
		printf("��Ҫд����ļ�������\n");
	}
	return;
}

/*��ʾ�ļ���Ϣ*/
void show_file(char filename[]){
	int i, j, k;
	printf("\t\t�ļ�����  �ļ�����  �ļ�����  ��ȡȨ��  ����Ŀ¼\t�����û�\n");
	for (i = 0; i<640; i++)
	{
		k = root[i].i_num;
		if (strcmp(filename, root[i].file_name) == 0 && (i_node[k].file_style == 1))
		{
			printf("\t\t  %s\t", root[i].file_name);	//�ļ���
			printf("\t%d\t", i_node[k].file_style);		//�ļ�������
			printf("%d\t", i_node[k].file_length);		//�ļ��ĳ���
			cout << i_node[k].limit << "\t";
			printf("%s\t", root[i].dir_name);			//�ļ����ڵ�Ŀ¼
			cout << cur_user << endl;
			printf("\t\t�ļ�ռ�õ������ַ\n");
			for (j = 0; j<i_node[k].file_length; j++)   //��ʾ�����ַ
			{
				printf("%d  ", i_node[k].file_address[j]); //�ļ�����ռ�õ��̿��
			}
			printf("\n");
			break;
		}
	}
	if (i == 640)
	{
		printf("û������ļ� ��������ļ����������ļ�\n");
	}
}

/*�����ļ�*/
void copy(char filename[10]) {
	int i;
	open(filename);
	read(filename);
	close(filename);
	for ( i= 0; i < 640; i++) {
		if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_num].file_style == 1)
			temp_file = i_node[root[i].i_num];
	}
}

/*ճ��*/
void paste(char filename[10]) {
	create_file(filename, temp_file.file_length, login_userid, temp_file.limit);
	open(filename);
	write(filename, temp_write);
	close(filename);
}