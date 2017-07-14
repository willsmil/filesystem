#include "filesystem.h"

int style = 1;
int file_array_head;
int physic[100];
string cur_user;
int file_array[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };

/*创建文件*/
void create_file(char filename[], int length, int userid, int limit){
	int i, j;
	for (i = 0; i<640; i++)
	{
		if (strcmp(filename, root[i].file_name) == 0)
		{
			printf("已经存在同名文件，不允许建立重名的文件\n");
			return;
		}
	}
	for (i = 0; i<640; i++)
	{
		if (root[i].i_num == -1)
		{
			root[i].i_num = i;
			strcpy(root[i].file_name, filename);
			strcpy(root[i].dir_name, cur_dir);  //把当前目录名 给新建立的文件
			i_node[i].file_style = style;//style==0 说明文件是目录文件
			i_node[i].file_length = length;
			i_node[i].limit = limit;
			i_node[i].file_UserId = userid; //printf("%s.%d\n",root[i].file_name,i_node[i].file_UserId);
			allot(length);
			for (j = 0; j<length; j++)
			{
				i_node[i].file_address[j] = physic[j];
			}

			//初始化文件

			for (int add = 0; add < 100; add++)
				for (int c = 0; c < length; c++) {
					memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
				}
			int u;
			for (u = 0; u<100; u++)//分配完清空缓冲区
			{
				physic[u] = -1;
			}
			break;
		}
	}
}

/*删除文件*/
void del_file(char filename[])     {
	int i, j, k;
	for (i = 0; i<640; i++)
	{

		if ((strcmp(filename, root[i].file_name) == 0) && (strcmp(cur_dir, root[i].dir_name) == 0) && (i_node[root[i].i_num].file_UserId == login_userid))
		{//printf("1get here\n");
			int add, c;
			for (add = 0; add<i_node[root[i].i_num].file_length; add++)//文件内容清空
			{
				for (c = 0; memory[i_node[root[i].i_num].file_address[add]].content[c] != '\0'; c++)
				{
					memory[i_node[root[i].i_num].file_address[add]].content[c] = '\0';
				}
			}
			k = root[i].i_num; //printf("2get here\n");
			i_node[k].file_UserId = -1;
			i_node[k].limit = -1;
			for (j = 0; j<i_node[k].file_length; j++)
			{
				physic[j] = i_node[k].file_address[j];
			}// printf("get here\n");
			callback(i_node[k].file_length); //调用 回收函数
			int u;//回收完情空缓存区
			for (u = 0; u<100; u++)
			{
				physic[u] = -1;
			}
			for (j = 0; j<100; j++)     //删除文件后要将文件属性和目录项的各个值恢复初值
			{
				i_node[k].file_address[j] = -1; //文件占用的块号地址恢复初值
			}
			strcpy(root[i].file_name, "");  //文件名恢复初值
			root[i].i_num = -1;     //目录项的I结点信息恢复初值
			strcpy(root[i].dir_name, "");  //目录项的文件目录信息恢复初值
			i_node[k].file_length = -1;   //文件长度恢复
			i_node[k].file_style = -1;   //文件类型恢复初值
			break;
		}
	}
	if (i == 640)
	{
		printf("登录用户的该目录下不存在这个文件\n");
	}
}

/*打开文件*/
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
				printf("打开的文件已达上限，无法打开本文件\n");
			}
			return root[i].i_num;
		}
	}
	if (i = 640)
	{
		printf("您要打开的文件不存在或不属于该用户\n");
	}
	return 0;
}

/*关闭文件*/
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
				printf("您要关闭的文件未打开过！\n");
			}
			return;
		}
	}
	if (i = 640)
	{
		printf("您要关闭的文件不存在或不属于该用户\n");
	}
	return;
}

/*读文件*/
int read(char filename[10]){
	int i;
	for (i = 0; i<640; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_num].file_style == 1)
		{
			int j;
			for (j = 0; j<8; j++)
			{          //int n; for (n=0;n<8;n++) printf("%d\n",file_array[n]);
				if (root[i].i_num == file_array[j])
				{
					if (i_node[root[i].i_num].limit == 0 || i_node[root[i].i_num].limit == 1)
					{
						int c, add;
						printf("\n  文件内容：");
						for (add = 0; add < 100; add++) {
							cout << memory[i_node[root[i].i_num].file_address[add]].content;
						}
						//for (c = 0; memory[i_node[root[i].i_num].file_address[add]].content[c] != '\0'; c++)
						//	printf("%c", memory[i_node[root[i].i_num].file_address[add]].content[c]);
						printf("\n ");
					}
					else
					{
						printf("你没有权限读取文件内容！！\n");
					}
					return 0;
				}
			}
			if (j == 8)
			{
				printf("\n  该文件未打开，请先打开文件再进行读写操作!!\n");
			}
			return 0;
		}
	}
	if (i == 640)
	{
		printf("您要读取的文件不存在\n");
	}
	return 0;
}

/*写入文件*/
void write(char filename[10], string writec){
	int i;
	for (i = 0; i<640; i++)
	{
		if (strcmp(root[i].file_name, filename) == 0 && i_node[root[i].i_num].file_style == 1)
		{
			int j;  //for(j=0;j<8;j++) printf("%d",file_array[j]);
			for (j = 0; j<8; j++)
			{
				if (root[i].i_num == file_array[j])
				{
					if (i_node[root[i].i_num].limit == 0 || i_node[root[i].i_num].limit == 2)
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
									cout << writec << "已写入文件" << endl;
									return;
								}
							}
						}
						if (add == 100)
						{
							printf("\n文件空间已满，写入失败！！\n");
						}
						return;
					}

					else
					{
						printf("你没有权限将内容写入文件！！\n");
						return;
					}
					return;
				}
			}
			if (j == 8)
			{
				printf("\n  该文件未打开，请先打开文件再进行读写操作!!\n");
			}
			return;
		}
	}
	if (i == 640)
	{
		printf("您要写入的文件不存在\n");
	}
	return;
}

/*显示文件信息*/
void show_file(char filename[]){
	int i, j, k;
	printf("\t\t文件名字  文件类型  文件长度  读取权限  所属目录\t所属用户\n");
	for (i = 0; i<640; i++)
	{
		k = root[i].i_num;
		if (strcmp(filename, root[i].file_name) == 0 && (i_node[k].file_style == 1))
		{
			printf("\t\t  %s\t", root[i].file_name);   //文件名
			printf("\t%d\t", i_node[k].file_style);   //文件的类型
			printf("%d\t", i_node[k].file_length);   //文件的长度
			printf("%d\t", i_node[k].limit);
			printf("%s\t", root[i].dir_name);    //文件所在的目录
			cout << cur_user << endl;
			printf("\t\t文件占用的物理地址\n");
			for (j = 0; j<i_node[k].file_length; j++)   //显示物理地址
			{
				printf("%d  ", i_node[k].file_address[j]); //文件具体占用的盘块号
			}
			printf("\n");
			break;
		}
	}
	if (i == 640)
	{
		printf("没有这个文件 或者这个文件不是正规文件\n");
	}
}


