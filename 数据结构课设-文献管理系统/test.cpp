#include"test.h"
void Menu()
{
	int Select;
	result r;
	BTree T=NULL;
	printf(" 现在开始初始化！\n");
	InitBTree(T);
	printf(" 初始化完成!\n");
	PrintBTree(T);
	printf("**************************************************************************************\n");
	while (1)
	{
		system("pause");
		system("cls");
		printf("**********文献管理系统*********\n");
		printf("*                             *\n");
		printf("*       1、文献入库           *\n");
		printf("*       2、清除文献库存       *\n");
		printf("*       3、文献借阅           *\n");
		printf("*       4、文献归还           *\n");
		printf("*       5、显示文献信息       *\n");
		printf("*       6、输出B 树           *\n");
		printf("*       0、退出系统           *\n");
		printf("*                             *\n");
		printf("*******************************\n");
		printf("\n输入数字并回车选择对应选项：\n");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			printf("请输入文献的编号\n");
			int key01;
			scanf_s("%d", &key01);
			SearchBTree(T, key01, r);
			if (r.tag == 1) 
			{
				printf("此文献已存在\n");
				ShowBook(T, key01);
				int n1;
				printf("请输入需要添加此文献的数量\n");
				scanf_s("%d", &n1);
				addBook(T, key01, n1);
			}
			else 
			{
				printf("此文献不存在，\n");
				char bn[30], bw[20], bp[30];
				printf("请按顺序输入此文献的文献名、作者、出版社（用空格隔开）\n");
				scanf_s("%s%s%s", bn, 30, bw, 20, bp, 30);
				printf("请输入需要添加此文献的数量\n");
				int n2;
				scanf_s("%d", &n2);
				InsertBook(T, key01, r, bn, bw, bp, n2);
			}
			printf("添加完成!\n");
			ShowBook(T, key01);
			PrintBTree(T);
			printf("**************************************************************************************\n"); break;
		case 2:
			printf("请输入文献的编号\n");
			int key02;
			scanf_s("%d", &key02);
			SearchBTree(T, key02, r);
			if (r.tag == 0)
				printf("此文献不存在！\n");
			else 
			{
				ShowBook(T, key02);
				printf("提示：清除后不可恢复！请确认是否清除：\n");
				printf("  1：确认清除       0：取消  \n");
				int a;
				scanf_s("%d", &a);
				if (a == 1) 
				{
					DeleteBook(T, key02);
					printf("清除成功!\n");
				}
				else
					printf("已取消\n");
			}
			PrintBTree(T);
			printf("**************************************************************************************\n"); break;
		case 3:
			printf("请输入文献的编号\n");
			int key03;
			scanf_s("%d", &key03);
			SearchBTree(T, key03, r);
			if (r.tag == 0)
				printf("此文献不存在！\n");
			else 
			{
				ShowBook(T, key03);
				if (emtyBook(r.pt, r.i))
					printf("此文献现库存不足，暂时无法借阅！\n");
				else 
				{
					printf("请确认是否借阅文献：\n");
					printf("1：确认   0：取消  \n");
					int a;
					scanf_s("%d", &a);
					if (a == 1) 
					{
						printf("请输入借阅证号：\n");
						int q;
						scanf_s("%d", &q);
						printf("请输入姓名：\n");
						char name[20];
						scanf_s("%s", name, sizeof(name));
						BorrowBook(r, q, name);
						ShowBook(T, key03);
						printf("借读成功!\n");
					}
					else
						printf("已取消\n");
				}
			}

			printf("**************************************************************************************\n"); break;
		case 4:
			printf("请输入文献的编号\n");
			int key04;
			scanf_s("%d", &key04);
			SearchBTree(T, key04, r);
			if (r.tag == 0)
				printf("此文献不存在！\n");
			else 
			{
				ShowBook(T, key04);
				printf("请确认是否归还文献：\n");
				printf("1：确认   0：取消  \n");
				int b;
				scanf_s("%d", &b);
				if (b == 1)
				{
					printf("请输入借阅证号：\n");
					int q;
					scanf_s("%d", &q);
					printf("请输入姓名：\n");
					char name[20];
					scanf_s("%s", name, sizeof(name));
					if (ReturnBook(r, q, name)) 
					{
						ShowBook(T, key04);
						printf("还书成功!\n");
					}
					else
						printf("还书失败!查无对应的借阅者！\n");
				}
				else
					printf("已取消\n");
			}
			printf("**************************************************************************************\n"); break;
		case 5:
			printf("请输入文献的编号\n");
			int key05;
			scanf_s("%d", &key05);
			SearchBTree(T, key05, r);
			if (r.tag == 0)
				printf("此文献不存在！\n");
			else 
			{
				ShowBookAll(T, key05);

			}
			printf("**************************************************************************************\n"); break;
		case 6:
			PrintBTree(T);
			printf("**************************************************************************************\n"); break;
		case 0: return;
		default:
			printf("输入错误，请重新输入!\n");
			printf("**************************************************************************************\n"); break;
		}

	}
	
}