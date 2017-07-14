#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

//����
struct command{
	char com[10];
};

//�̿���Ϣ��1KB/�飩
struct block
{
	int n;				//��ſ����̿�ĸ���
	int free[50];		//��ſ����̿�ĵ�ַ
	int a;				//�̿��Ƿ�ռ�ñ�־
	char content[1000];	//����ÿ���ֽڴ�ŵķ���
};

//������
struct block_super{
	int n;      //���е��̿�ĸ���
	int free[50];    //��Ž���ջ�еĿ��п�					
};

//i�����Ϣ��32B/i�ڵ㣩
struct node{
	int file_style;    //i��� �ļ�����
	int file_length;   //i��� �ļ�����
	int file_address[100];  //�ļ�ռ�õ������š�
	string limit;//�򿪶�дȨ�ޣ�0��ʾ�ܴ򿪶�д��1��ʾ�ܴ򿪶���2��ʾ�ܴ�д��3��ʾֻ�ܴ�
	int file_UserId;
};

//�û���Ϣ
struct user {
	string username;
	string password;
} ;

//Ŀ¼����Ϣ
struct dir      {
	char file_name[10];   //�ļ���
	int  i_num;     //�ļ��Ľ���
	char dir_name[10];   //Ŀ¼������˵�ļ�����Ŀ¼
};

extern int user_num;				//��ע���û�����
extern int login_userid;			//��ǰ��¼���û�ID
extern string cur_user;				//��ǰ�û�
extern int file_array[8];			// ���ļ�����
extern int file_array_head;			//�ļ�����ͷ
extern int physic[100];				//�ļ���ַ������
extern int style;					//�ļ�������
extern char cur_dir[10];			//��ǰĿ¼
extern string temp_write;			//��ʱ�ļ�����
extern node temp_file;			//��ʱ�ļ�


extern command cmd[17];
extern block memory[20449];
extern block_super super_block;
extern node i_node[640];
extern user user_array[8];
extern dir root[640];

/*��������*/
extern void del_dir(char filename[]);			//ɾ��Ŀ¼
extern void back_dir();							//������һ��
extern void create_dir(char filename[]);		//����Ŀ¼
extern void display_curdir();					//��ʾ��ǰĿ¼�µ��ļ��б�
extern void display_dir(char filename[]);		//����ָ����Ŀ¼
extern void close(char filename[10]);			//�ر��ļ�
extern void del_file(char filename[]);			//ɾ���ļ�
extern int open(char filename[10]);				//���ļ�
extern void copy(char filename[10]);			//�����ļ�
extern void paste(char filename[10]);			//ճ���ļ�
extern int read(char filename[10]);				//��ȡ�ļ�����
extern void show_file_content();				//��ʾ�ļ�����
extern void show_file(char filename[]);			//��ʾ�ļ���Ϣ
extern void help();								//�������
extern void display_sys();						//��ʾϵͳ��Ϣ������ʹ�������
extern void read_file(FILE *fp);				//����ϵͳ�ļ�����Ϣ
extern void write_file(FILE *fp);				//����Ϣд��ϵͳ�ļ�
extern int login();								//��½
extern void logout();							//�ǳ�
extern void reg();								//ע��
extern void format();							//��ʼ��
extern void allot(int length);					//����ռ�
extern void callback(int length);				//���տռ�
extern void write(char filename[10], string writec);//д���ļ�
extern void create_file(char filename[], int length, int userid, string limit); //�����ļ�