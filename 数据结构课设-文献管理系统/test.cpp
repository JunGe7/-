#include"test.h"
void Menu()
{
	int Select;
	result r;
	BTree T=NULL;
	printf(" ���ڿ�ʼ��ʼ����\n");
	InitBTree(T);
	printf(" ��ʼ�����!\n");
	PrintBTree(T);
	printf("**************************************************************************************\n");
	while (1)
	{
		system("pause");
		system("cls");
		printf("**********���׹���ϵͳ*********\n");
		printf("*                             *\n");
		printf("*       1���������           *\n");
		printf("*       2��������׿��       *\n");
		printf("*       3�����׽���           *\n");
		printf("*       4�����׹黹           *\n");
		printf("*       5����ʾ������Ϣ       *\n");
		printf("*       6�����B ��           *\n");
		printf("*       0���˳�ϵͳ           *\n");
		printf("*                             *\n");
		printf("*******************************\n");
		printf("\n�������ֲ��س�ѡ���Ӧѡ�\n");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			printf("���������׵ı��\n");
			int key01;
			scanf_s("%d", &key01);
			SearchBTree(T, key01, r);
			if (r.tag == 1) 
			{
				printf("�������Ѵ���\n");
				ShowBook(T, key01);
				int n1;
				printf("��������Ҫ��Ӵ����׵�����\n");
				scanf_s("%d", &n1);
				addBook(T, key01, n1);
			}
			else 
			{
				printf("�����ײ����ڣ�\n");
				char bn[30], bw[20], bp[30];
				printf("�밴˳����������׵������������ߡ������磨�ÿո������\n");
				scanf_s("%s%s%s", bn, 30, bw, 20, bp, 30);
				printf("��������Ҫ��Ӵ����׵�����\n");
				int n2;
				scanf_s("%d", &n2);
				InsertBook(T, key01, r, bn, bw, bp, n2);
			}
			printf("������!\n");
			ShowBook(T, key01);
			PrintBTree(T);
			printf("**************************************************************************************\n"); break;
		case 2:
			printf("���������׵ı��\n");
			int key02;
			scanf_s("%d", &key02);
			SearchBTree(T, key02, r);
			if (r.tag == 0)
				printf("�����ײ����ڣ�\n");
			else 
			{
				ShowBook(T, key02);
				printf("��ʾ������󲻿ɻָ�����ȷ���Ƿ������\n");
				printf("  1��ȷ�����       0��ȡ��  \n");
				int a;
				scanf_s("%d", &a);
				if (a == 1) 
				{
					DeleteBook(T, key02);
					printf("����ɹ�!\n");
				}
				else
					printf("��ȡ��\n");
			}
			PrintBTree(T);
			printf("**************************************************************************************\n"); break;
		case 3:
			printf("���������׵ı��\n");
			int key03;
			scanf_s("%d", &key03);
			SearchBTree(T, key03, r);
			if (r.tag == 0)
				printf("�����ײ����ڣ�\n");
			else 
			{
				ShowBook(T, key03);
				if (emtyBook(r.pt, r.i))
					printf("�������ֿ�治�㣬��ʱ�޷����ģ�\n");
				else 
				{
					printf("��ȷ���Ƿ�������ף�\n");
					printf("1��ȷ��   0��ȡ��  \n");
					int a;
					scanf_s("%d", &a);
					if (a == 1) 
					{
						printf("���������֤�ţ�\n");
						int q;
						scanf_s("%d", &q);
						printf("������������\n");
						char name[20];
						scanf_s("%s", name, sizeof(name));
						BorrowBook(r, q, name);
						ShowBook(T, key03);
						printf("����ɹ�!\n");
					}
					else
						printf("��ȡ��\n");
				}
			}

			printf("**************************************************************************************\n"); break;
		case 4:
			printf("���������׵ı��\n");
			int key04;
			scanf_s("%d", &key04);
			SearchBTree(T, key04, r);
			if (r.tag == 0)
				printf("�����ײ����ڣ�\n");
			else 
			{
				ShowBook(T, key04);
				printf("��ȷ���Ƿ�黹���ף�\n");
				printf("1��ȷ��   0��ȡ��  \n");
				int b;
				scanf_s("%d", &b);
				if (b == 1)
				{
					printf("���������֤�ţ�\n");
					int q;
					scanf_s("%d", &q);
					printf("������������\n");
					char name[20];
					scanf_s("%s", name, sizeof(name));
					if (ReturnBook(r, q, name)) 
					{
						ShowBook(T, key04);
						printf("����ɹ�!\n");
					}
					else
						printf("����ʧ��!���޶�Ӧ�Ľ����ߣ�\n");
				}
				else
					printf("��ȡ��\n");
			}
			printf("**************************************************************************************\n"); break;
		case 5:
			printf("���������׵ı��\n");
			int key05;
			scanf_s("%d", &key05);
			SearchBTree(T, key05, r);
			if (r.tag == 0)
				printf("�����ײ����ڣ�\n");
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
			printf("�����������������!\n");
			printf("**************************************************************************************\n"); break;
		}

	}
	
}