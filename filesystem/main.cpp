#include "filesystem.h"
#include <iostream>
using namespace std;

command cmd[17];  //命令

/*帮助*/
void help(){
	printf("0.初始化-------------------------format\n");
	printf("1.查看当前目录文件列表-----------dir\n");
	printf("2.查看文件信息-------------------cat-----(cat + 文件名)  \n");
	printf("3.查看系统信息-------------------ls    \n");
	printf("4.创建目录-----------------------md------(md  + 目录名)  \n");
	printf("5.创建文件-----------------------mkdir---(mkdir  + 文件名 + 文件长度 + 权限)\n");
	printf("6.删除文件-----------------------del-----(del + 文件名) \n");
	printf("7.打开文件-----------------------open----(open + 文件名) \n");
	printf("8.关闭文件-----------------------close---(close + 文件名) \n");
	printf("9.读取文件-----------------------read----(read + 文件名) \n");
	printf("10.写入文件----------------------write---(write + 文件名 + 写入字符)\n");
	printf("11.删除目录----------------------deldir--(deldir + 目录名)\n");
	printf("12.进入当前目录下的指定目录------cd------(cd + 目录名)\n");
	printf("13.返回上一级目录----------------cd..  \n");
	printf("14.显示帮助命令------------------help  \n");
	printf("15.退出文件系统------------------quit  \n");
	printf("16.退出登录----------------------logout  \n");
}

/*主函数*/
void main(){
	char tmp[10], com[10], tmp1[10];
	struct command tmp2[10];
	int i, j = 0, p, len = 0;
	FILE *fp;

	//将各个命令存进命令表
	strcpy(cmd[0].com, "format");    
	strcpy(cmd[1].com, "dir");
	strcpy(cmd[2].com, "cat");
	strcpy(cmd[3].com, "ls");
	strcpy(cmd[4].com, "md");
	strcpy(cmd[5].com, "mkdir");
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
	
	//初始化
	if ((fp = fopen("filesave", "rb")) == NULL)   //判断系统文件是否存在
	{
		cout << "正在初始化系统" << endl;
		format();
	}
	else
	{
		cout << "加载文件系统" << endl;
		read_file(fp);       //读取系统文件的内容
	}

	//注册登陆
	while (1) {
		int log_com;
		cout << "1------登陆------1" << endl;
		cout << "2------注册------2" << endl;
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
		j = 0;         //必须重新给恢复0否则出错
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
		cout << endl;

		strcpy(tmp2[j].com, tmp);
		for (i = j; i >= 0; i--)
		{
			printf("%s>", tmp2[i].com);
		}

		scanf("%s", com);       //输入命令并且查找命令的相关操作
		for (i = 0; i<17; i++){
			if (strcmp(com, cmd[i].com) == 0){
				p = i;
				break;
			}
		}
		if (i == 17){       //如果没有这个语句以后输入的命令都和第一次输入的效果一样
			p = -1;			//随便的一个值
		}
		switch (p){
		case 0: {
			format();       //初始化
			break;
		}
		case 1: {
			display_curdir();     //查看当前目录下的文件列表
			break;
		}
		case 2: {
			scanf("%s", tmp);     //查看文件
			show_file(tmp);
			break;
		}
		case 3: {
			display_sys();      //查看系统信息
			break; 
		}
		case 4: {
			scanf("%s", tmp);      //创建目录
			create_dir(tmp);
			break;
		}
		case 5: {
			scanf("%s", tmp);     //创建文件
			scanf("%d", &len);
			string limit;
			cin >> limit;
			create_file(tmp, len, login_userid, limit);
			break; 
		}
		case 6: {
			scanf("%s", tmp);     //删除文件
			for (i = 0; i < 640; i++)     //判断文件是不是正规文件
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
				printf("这个不是正规文件文件\n");
			}
			break;
		}
		case 7: {
			scanf("%s", tmp);     //删除目录
			del_dir(tmp);
			break;
		}
		case 8: {
			scanf("%s", tmp1);     //进入当前目录下的指定目录   相当于进入目录  cd  +  目录名
			display_dir(tmp1);
			break;
		}
		case 9: {
			back_dir();       //返回上一级目录
			break;
		}
		case 10: {
			help();
			break;
		}
		case 11: {
			write_file(fp);      //将磁盘利用信息写进系统文件，退出
			system("pause");
		}
		case 12: {
			scanf("%s", tmp);
			open(tmp);
			break;
		}
		case 13: {
			scanf("%s", tmp);
			read(tmp);
			break;
		}
		case 14: {
			scanf("%s", tmp);
			getchar();
			string writec;
			cin >> writec;
			write(tmp, writec);
			break; 
		}
		case 15: {
			write_file(fp);
			logout();
			int l;
			for (l = 0; l < 8; l++)
			{
				file_array[l] = -1;
			}
			file_array_head = 0;
			while (1) {
				int log_com;
				cout << "1------登陆------1" << endl;
				cout << "2------注册------2" << endl;
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
			break;
		}
		case 16: {
			scanf("%s", tmp);
			close(tmp);
			break; 
		}
		default: {
			cout << "无效指令" << endl;
			break;
		}
		}
	}
	system("pause");
}