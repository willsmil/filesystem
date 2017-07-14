#include "filesystem.h"

block_super super_block;
block memory[20449];

/*将信息写入系统文件*/
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

/*读出系统文件的信息*/
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

/*显示系统信息（磁盘使用情况）*/
void display_sys()        {
	int i, m, k = 0;
	for (i = 0; i<20449; i++)
	{
		if (memory[i].a == 0)
			k++;
	}
	m = 20449 - k;
	printf("空闲的盘块数是：\t");
	printf("%d\n", k);
	printf("使用的盘块数是：\t");
	printf("%d\n", m);
}

/*格式化*/
void format()     {
	int i, j, k;
	super_block.n = 50;
	for (i = 0; i<50; i++)     //超级块初始化
	{
		super_block.free[i] = i;   //存放进入栈中的空闲块
								   //super_block.stack[i]=50+i;  //存放下一组的盘块
	}

	for (i = 0; i<640; i++)     //i结点信息初始化
	{
		for (j = 0; j<100; j++)
		{
			i_node[i].file_address[j] = -1;//文件地址
		}
		i_node[i].limit = -1;
		i_node[i].file_length = -1;  //文件长度
		i_node[i].file_style = -1; //文件类型
		i_node[i].file_UserId = -1;//用户ID
	}

	for (i = 0; i<640; i++)     //目录项信息初始化
	{
		strcpy(root[i].file_name, "");
		root[i].i_num = -1;
		strcpy(root[i].dir_name, "");
	}
	for (i = 0; i<20449; i++)     //存储空间初始化
	{
		memory[i].n = 0;      //必须有这个
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
	for (i = 0; i<20449; i++)    //将空闲块的信息用成组链接的方法写进每组的最后一个块中
	{         //存储空间初始化

		if ((i + 1) % 50 == 0)
		{
			k = i + 1;
			for (j = 0; j<50; j++)
			{
				if (k<20450)
				{
					memory[i].free[j] = k;//下一组空闲地址
					memory[i].n++;  //下一组空闲个数   注意在memory[i].n++之前要给其赋初值
					k++;
				}
				else
				{
					memory[i].free[j] = -1;
				}
			}
			memory[i].a = 0;    //标记为没有使用
			continue;     //处理完用于存储下一组盘块信息的特殊盘块后，跳过本次循环
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
	printf("已经初始化完毕\n");
}

/*分配空间*/
void allot(int length)     {
	int i, j, k, m, p;
	for (i = 0; i<length; i++)
	{
		k = 50 - super_block.n;    //超级块中表示空闲块的指针
		m = super_block.free[k];   //栈中的相应盘块的地址
		p = super_block.free[49];   //栈中的最后一个盘块指向的地址
		if (p == -1/*||memory[p].a==1*/)  //没有剩余盘块
		{
			printf("内存不足,不能够分配空间\n");
			callback(i);//之前已分配的i个盘块回收；
			break;
		}
		if (super_block.n == 1)
		{
			memory[m].a = 1;    //将最后一个盘块分配掉
			physic[i] = m;
			super_block.free[49] = -1;
			super_block.n = 0;
			for (j = 50 - memory[m].n; j<50; j++) //从最后一个盘块中取出下一组盘块号写入栈中
			{
				super_block.free[j] = memory[m].free[j];
				super_block.n++;
			}
			continue;     //要跳过这次循环，下面的语句在IF中已经执行过
		}
		physic[i] = m;     //如果栈中超过一个盘，栈中的相应盘块的地址写进 文件地址缓冲区
		memory[m].a = 1;
		m = -1;
		super_block.n--;
	}

}

/*回收磁盘空间*/
void callback(int length)    {
	int i, j, k, m, q = 0;
	for (i = length - 1; i >= 0; i--)
	{
		k = physic[i];     //需要提供要回收的文件的地址
		m = 49 - super_block.n;    //回收到栈中的哪个位置
		if (super_block.n == 50)   //注意 当super_block.n==50时 m=-1;的值
		{        //super_block.n==50的时候栈满了，要将这个栈中的所有地址信息写进下一个地址中
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
			m = 49;      //将下一个文件地址中的盘块号回收到栈底中，这个地址中存放着刚才满栈的地址的信息
		}
		super_block.free[m] = physic[i]; //将下一个文件地址中的盘块号回收到栈中
		super_block.n++;
	}
}


