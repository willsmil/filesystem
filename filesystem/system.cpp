#include "filesystem.h"

block_super super_block;
block memory[20449];

/*����Ϣд��ϵͳ�ļ�*/
void write_file(FILE *fp)    {
	int i;
	fp = fopen("filesave", "wb");
	for (i = 0; i<20449; i++)
	{
		fwrite(&memory[i], sizeof(struct block), 1, fp);
	}
	fwrite(&super_block, sizeof(struct block_super), 1, fp);

	for (i = 0; i<640; i++)
	{
		fwrite(&i_node[i], sizeof(struct node), 1, fp);
	}
	for (i = 0; i<640; i++)
	{
		fwrite(&root[i], sizeof(struct dir), 1, fp);
	}
	for (int i = 0; i < 8; i++) {
		fwrite(&user_array[i], sizeof(struct user), 1, fp);
	}
	fwrite(&user_num, sizeof(int), 1, fp);
	fclose(fp);
}

/*����ϵͳ�ļ�����Ϣ*/
void read_file(FILE *fp)   {
	int i;
	fp = fopen("filesave", "rb");
	for (i = 0; i<20449; i++)
	{
		fread(&memory[i], sizeof(struct block), 1, fp);
	}

	fread(&super_block, sizeof(struct block_super), 1, fp);

	for (i = 0; i<640; i++)
	{
		fread(&i_node[i], sizeof(struct node), 1, fp);
	}

	for (i = 0; i<640; i++)
	{
		fread(&root[i], sizeof(struct dir), 1, fp);
	}
	for (i = 0; i < 8; i++)
	{
		fread(&user_array[i], sizeof(struct user), 1, fp);
	}
	fread(&user_num, sizeof(int), 1, fp);
	fclose(fp);
}

/*��ʾϵͳ��Ϣ������ʹ�������*/
void display_sys()        {
	int i, m, k = 0;
	for (i = 0; i<20449; i++)
	{
		if (memory[i].a == 0)
			k++;
	}
	m = 20449 - k;
	printf("���е��̿����ǣ�\t");
	printf("%d\n", k);
	printf("ʹ�õ��̿����ǣ�\t");
	printf("%d\n", m);
}

/*��ʽ��*/
void format()     {
	int i, j, k;
	super_block.n = 50;
	for (i = 0; i<50; i++)     //�������ʼ��
	{
		super_block.free[i] = i;   //��Ž���ջ�еĿ��п�
								   //super_block.stack[i]=50+i;  //�����һ����̿�
	}

	for (i = 0; i<640; i++)     //i�����Ϣ��ʼ��
	{
		for (j = 0; j<100; j++)
		{
			i_node[i].file_address[j] = -1;//�ļ���ַ
		}
		i_node[i].limit = -1;
		i_node[i].file_length = -1;  //�ļ�����
		i_node[i].file_style = -1; //�ļ�����
		i_node[i].file_UserId = -1;//�û�ID
	}

	for (i = 0; i<640; i++)     //Ŀ¼����Ϣ��ʼ��
	{
		strcpy(root[i].file_name, "");
		root[i].i_num = -1;
		strcpy(root[i].dir_name, "");
	}
	for (i = 0; i<20449; i++)     //�洢�ռ��ʼ��
	{
		memory[i].n = 0;      //���������
		memory[i].a = 0;
		for (j = 0; j<50; j++)
		{
			memory[i].free[j] = -1;
		}

		int c;
		for (c = 0; c<1000; c++)
		{
			memory[i].content[c] = '\0';
		}

	}
	for (i = 0; i<20449; i++)    //�����п����Ϣ�ó������ӵķ���д��ÿ������һ������
	{         //�洢�ռ��ʼ��

		if ((i + 1) % 50 == 0)
		{
			k = i + 1;
			for (j = 0; j<50; j++)
			{
				if (k<20450)
				{
					memory[i].free[j] = k;//��һ����е�ַ
					memory[i].n++;  //��һ����и���   ע����memory[i].n++֮ǰҪ���丳��ֵ
					k++;
				}
				else
				{
					memory[i].free[j] = -1;
				}
			}
			memory[i].a = 0;    //���Ϊû��ʹ��
			continue;     //���������ڴ洢��һ���̿���Ϣ�������̿����������ѭ��
		}
		for (j = 0; j<50; j++)
		{
			memory[i].free[j] = -1;
		}
		memory[i].n = 0;
	}
	int l;
	for (l = 0; l<8; l++)
	{
		file_array[l] = -1;
	}
	file_array_head = 0;
	int u;
	for (u = 0; u<100; u++)
	{
		physic[u] = -1;
	}
	for (int k = 0; k < 8; k++) {
		user_array[k].username = "";
		user_array[k].password = "";
	}
	printf("�Ѿ���ʼ�����\n");
}

/*����ռ�*/
void allot(int length)     {
	int i, j, k, m, p;
	for (i = 0; i<length; i++)
	{
		k = 50 - super_block.n;    //�������б�ʾ���п��ָ��
		m = super_block.free[k];   //ջ�е���Ӧ�̿�ĵ�ַ
		p = super_block.free[49];   //ջ�е����һ���̿�ָ��ĵ�ַ
		if (p == -1/*||memory[p].a==1*/)  //û��ʣ���̿�
		{
			printf("�ڴ治��,���ܹ�����ռ�\n");
			callback(i);//֮ǰ�ѷ����i���̿���գ�
			break;
		}
		if (super_block.n == 1)
		{
			memory[m].a = 1;    //�����һ���̿�����
			physic[i] = m;
			super_block.free[49] = -1;
			super_block.n = 0;
			for (j = 50 - memory[m].n; j<50; j++) //�����һ���̿���ȡ����һ���̿��д��ջ��
			{
				super_block.free[j] = memory[m].free[j];
				super_block.n++;
			}
			continue;     //Ҫ�������ѭ��������������IF���Ѿ�ִ�й�
		}
		physic[i] = m;     //���ջ�г���һ���̣�ջ�е���Ӧ�̿�ĵ�ַд�� �ļ���ַ������
		memory[m].a = 1;
		m = -1;
		super_block.n--;
	}

}

/*���մ��̿ռ�*/
void callback(int length)    {
	int i, j, k, m, q = 0;
	for (i = length - 1; i >= 0; i--)
	{
		k = physic[i];     //��Ҫ�ṩҪ���յ��ļ��ĵ�ַ
		m = 49 - super_block.n;    //���յ�ջ�е��ĸ�λ��
		if (super_block.n == 50)   //ע�� ��super_block.n==50ʱ m=-1;��ֵ
		{        //super_block.n==50��ʱ��ջ���ˣ�Ҫ�����ջ�е����е�ַ��Ϣд����һ����ַ��
			for (j = 0; j<50; j++)
			{
				memory[k].free[j] = super_block.free[j];
			}
			int u;
			for (u = 0; u<50; u++)
			{
				super_block.free[u] = -1;
				//super_block.stack[u]=memory[k].free[u];
			}
			super_block.n = 0;
			memory[k].n = 50;
		}
		memory[k].a = 0;
		if (m == -1)
		{
			m = 49;      //����һ���ļ���ַ�е��̿�Ż��յ�ջ���У������ַ�д���Ÿղ���ջ�ĵ�ַ����Ϣ
		}
		super_block.free[m] = physic[i]; //����һ���ļ���ַ�е��̿�Ż��յ�ջ��
		super_block.n++;
	}
}


