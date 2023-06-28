#define _CRT_SECURE_NO_WARNINGS
#pragma once
//常用头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//预定义常量和类型
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
typedef int KeyType;
#define m 3//定义三阶B树

//读者类型
typedef struct ReaderType {
	int readerId;    //读者借阅证号
	char name[20];   //读者姓名
	int time;        //归还时间
	struct ReaderType* next;
}ReaderType;  

//文献类型
typedef struct {
	char bookName[30];   //文献名
	char writerName[20]; //作者
	char bookPress[30];  //出版社
	int booknumNow;    //现存量
	int booknumAll;    //总库存量
	ReaderType* reader;
}BookType;  

//B树的结点和指针类型
typedef struct BTNode {
	int keynum;                  //结点当前的关键字个数
	KeyType key[m + 1];          //关键字数组，key[0]未用
	struct BTNode* parent;      //双亲结点指针
	struct BTNode* ptr[m + 1];  //孩子结点指针数组
	BookType* book[m + 1];      //文献指针数组，bkptr[0]未用
}BTNode, * BTree;  

typedef struct {
	BTree pt;  //指向找到的结点
	int i;     //结点中的关键字位序
	int tag;   //1为成功，0为失败
}result; //Search结果类型



//B树的操作接口
//创建(赋予文献系统里的初始图书)
void InitBTree(BTree& t);
//查找
void SearchBTree(BTree t, KeyType k, result& r);   
//插入
void InsertBTree(BTree& t, KeyType k, BTree q, int i, BookType* book);  
//删除
void DeleteBTree(BTree& t, KeyType key);  
//遍历打印输出
void PrintBTree(BTree t);    




//各种小操作，减少代码重复率
//递归遍历
void Traverse(BTree t, int k);
//在结点p中查找关键字k
int SearchBTNode(BTree p, KeyType k);
//将q结点分裂成两个结点，前一半留在原节点，后一半留在ap指向的新结点
void split(BTree& q, int s, BTree& ap);
//生成新的根结点
void newRoot(BTree& t, BTree p, KeyType x, BTree ap, BookType* book);
//关键字x和新结点指针ap分别插入到q->key[i]和q->ptr[i]
void Insert(BTree& q, int i, KeyType x, BTree ap, BookType* book);
//在结点p中删除关键字key
int BTNodeDelete(BTNode* p, KeyType key);
//在结点p中查找关键字k，返回位置i
int FindBTNode(BTNode* p, KeyType k, int& i);
//在结点p中删除关键字key[i]和其孩子结点ptr[i]
void Remove(BTNode* p, int i);
//在结点p中查找被删除的关键字key[i]的替代叶子结点
void Substitution(BTNode* p, int i);
//在结点p中删除关键字key[i]后调整B树
void AdjustBTree(BTNode* p, int i);
//将双亲结点p中的最后一个关键字移入右结点q中,将左结点aq中的最后一个关键字移入双亲结点p中
void MoveRight(BTNode* p, int i);
//将双亲结点p中的第一个关键字移入结点aq中,将结点q中的第一个关键字移入双亲结点p中
void MoveLeft(BTNode* p, int i);
//将双亲结点p、右结点q合并入左结点aq,并调整双亲结点p中的剩余关键字的位置
void Combine(BTNode* p, int i);



//对文献直接操作的接口
//采编入库
void InsertBook(BTree& t, KeyType key, result r, char* bookname, char* writername, char* bookpress, int num);  
//清除库存
void DeleteBook(BTree& t, KeyType key);  
//借阅图书
void BorrowBook(result r, int number, char* name);   
//归还图书
Status ReturnBook(result r, int number, char* name);   
//查看某种图书的信息（包括借阅者）
void ShowBookAll(BTree t, KeyType key);  
//输出某本书的信息
void ShowBook(BTree t, KeyType key); 
//添加某本书的数量
void addBook(BTree t, KeyType key, int num); 
//检查某本书的现存量是否大于0
Status emtyBook(BTree q, int i); 
