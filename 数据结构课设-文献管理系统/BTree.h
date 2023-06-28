#define _CRT_SECURE_NO_WARNINGS
#pragma once
//����ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Ԥ���峣��������
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
typedef int KeyType;
#define m 3//��������B��

//��������
typedef struct ReaderType {
	int readerId;    //���߽���֤��
	char name[20];   //��������
	int time;        //�黹ʱ��
	struct ReaderType* next;
}ReaderType;  

//��������
typedef struct {
	char bookName[30];   //������
	char writerName[20]; //����
	char bookPress[30];  //������
	int booknumNow;    //�ִ���
	int booknumAll;    //�ܿ����
	ReaderType* reader;
}BookType;  

//B���Ľ���ָ������
typedef struct BTNode {
	int keynum;                  //��㵱ǰ�Ĺؼ��ָ���
	KeyType key[m + 1];          //�ؼ������飬key[0]δ��
	struct BTNode* parent;      //˫�׽��ָ��
	struct BTNode* ptr[m + 1];  //���ӽ��ָ������
	BookType* book[m + 1];      //����ָ�����飬bkptr[0]δ��
}BTNode, * BTree;  

typedef struct {
	BTree pt;  //ָ���ҵ��Ľ��
	int i;     //����еĹؼ���λ��
	int tag;   //1Ϊ�ɹ���0Ϊʧ��
}result; //Search�������



//B���Ĳ����ӿ�
//����(��������ϵͳ��ĳ�ʼͼ��)
void InitBTree(BTree& t);
//����
void SearchBTree(BTree t, KeyType k, result& r);   
//����
void InsertBTree(BTree& t, KeyType k, BTree q, int i, BookType* book);  
//ɾ��
void DeleteBTree(BTree& t, KeyType key);  
//������ӡ���
void PrintBTree(BTree t);    




//����С���������ٴ����ظ���
//�ݹ����
void Traverse(BTree t, int k);
//�ڽ��p�в��ҹؼ���k
int SearchBTNode(BTree p, KeyType k);
//��q�����ѳ�������㣬ǰһ������ԭ�ڵ㣬��һ������apָ����½��
void split(BTree& q, int s, BTree& ap);
//�����µĸ����
void newRoot(BTree& t, BTree p, KeyType x, BTree ap, BookType* book);
//�ؼ���x���½��ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
void Insert(BTree& q, int i, KeyType x, BTree ap, BookType* book);
//�ڽ��p��ɾ���ؼ���key
int BTNodeDelete(BTNode* p, KeyType key);
//�ڽ��p�в��ҹؼ���k������λ��i
int FindBTNode(BTNode* p, KeyType k, int& i);
//�ڽ��p��ɾ���ؼ���key[i]���亢�ӽ��ptr[i]
void Remove(BTNode* p, int i);
//�ڽ��p�в��ұ�ɾ���Ĺؼ���key[i]�����Ҷ�ӽ��
void Substitution(BTNode* p, int i);
//�ڽ��p��ɾ���ؼ���key[i]�����B��
void AdjustBTree(BTNode* p, int i);
//��˫�׽��p�е����һ���ؼ��������ҽ��q��,������aq�е����һ���ؼ�������˫�׽��p��
void MoveRight(BTNode* p, int i);
//��˫�׽��p�еĵ�һ���ؼ���������aq��,�����q�еĵ�һ���ؼ�������˫�׽��p��
void MoveLeft(BTNode* p, int i);
//��˫�׽��p���ҽ��q�ϲ�������aq,������˫�׽��p�е�ʣ��ؼ��ֵ�λ��
void Combine(BTNode* p, int i);



//������ֱ�Ӳ����Ľӿ�
//�ɱ����
void InsertBook(BTree& t, KeyType key, result r, char* bookname, char* writername, char* bookpress, int num);  
//������
void DeleteBook(BTree& t, KeyType key);  
//����ͼ��
void BorrowBook(result r, int number, char* name);   
//�黹ͼ��
Status ReturnBook(result r, int number, char* name);   
//�鿴ĳ��ͼ�����Ϣ�����������ߣ�
void ShowBookAll(BTree t, KeyType key);  
//���ĳ�������Ϣ
void ShowBook(BTree t, KeyType key); 
//���ĳ���������
void addBook(BTree t, KeyType key, int num); 
//���ĳ������ִ����Ƿ����0
Status emtyBook(BTree q, int i); 
