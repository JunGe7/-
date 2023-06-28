#include"BTree.h"
//初始化文献管理系统
void InitBTree(BTree& t)
{	//先初始化t

	result r;
	int j, n = 14;
	KeyType key[] = { 35,16,18,70,5,50,22,60,13,17,12,45,25,42 };
	int num[] = { 50,60,75,81,45,12,44,55,66,77,85,40,40,52 };
	char name[14][30] = { "君哥帅出天际","数据结构真是好","昨天一餐饱饭",
		"论楚汉之争","论材料制作","论交通","论前端","论饱饭",
		"论中古英雄","论计算机发展","论身体健康","论高数","论开心","论快乐" };
	char writer[14][20] = { "李敏君","张三","李四","刘邦","王五","王五",
		"李四","甲方","李敏君","老外","老外","老外","张三","刘邦" };
	char press[14][20] = { "广东工业大学出版社","广东工业大学出版社",
		"广东工业大学出版社","广东工业大学出版社","广东工业大学出版社",
		"广东工业大学出版社","广东工业大学出版社","广东工业大学出版社",
		"广东工业大学出版社","广东工业大学出版社","广东工业大学出版社",
		"广东工业大学出版社","广东工业大学出版社","广东工业大学出版社" };
	for (j = 0; j < n; j++) {     //逐一插入元素
		SearchBTree(t, key[j], r);
		if (r.tag == 0)
			InsertBook(t, key[j], r, name[j], writer[j], press[j], num[j]);
		printf("插入%d:\n", key[j]);
		PrintBTree(t);   //调试输出
		ShowBook(t, key[j]);
	}
}




//B树各个接口的实现(大方向上的接口)
//查找
void SearchBTree(BTree t, KeyType k, result& r) 
{
	int i = 0, found = 0;
	BTree p = t, q = NULL;
	while (p != NULL && found == 0) 
	{
		i = SearchBTNode(p, k);
		if (i <= p->keynum && p->key[i] == k)
			found = 1;
		else 
		{
			q = p;
			p = p->ptr[i - 1];
		}
	}

	if (found == 1) 
	{
		r.pt = p;
		r.i = i;
		r.tag = 1;
	}
	else 
	{
		r.pt = q;
		r.i = i;
		r.tag = 0;
	}
}

//插入
void InsertBTree(BTree& t, KeyType k, BTree q, int i, BookType* book) 
{
	int s, finished = 0, needNewRoot = 0;
	KeyType x;
	BookType* b;
	BTree ap;
	if (q == NULL)  newRoot(t, NULL, k, NULL, book);
	else 
	{
		x = k; ap = NULL; b = book;
		while (needNewRoot == 0 && finished == 0) 
		{
			Insert(q, i, x, ap, b);
			if (q->keynum < m) finished = 1;
			else 
			{
				s = (m + 1) / 2;
				split(q, s, ap);
				x = q->key[s];
				b = q->book[s];
				if (q->parent != NULL) 
				{
					q = q->parent;
					i = SearchBTNode(q, x);
				}
				else needNewRoot = 1;
			}
		}
		if (needNewRoot == 1)
			newRoot(t, q, x, ap, b);
	}
}

//删除
void DeleteBTree(BTree& t, KeyType key)
{
	BTNode* p;
	int a = BTNodeDelete(t, key);//删除关键字key 
	if (a == 0)                //查找失败 
		printf("关键字%d不在B树中\n", key);
	else if (t->keynum == 0) //调整
	{                           
		p = t;
		t = t->ptr[0];
		free(p);
	}
}

//遍历打印输出
void PrintBTree(BTree t)
{
	printf("此时B树的状态如下：\n");
	if (t == NULL)
		printf("此B树为空树\n");
	else
		Traverse(t, 0); //以凹入表的形式递归遍历输出
}




//各个小接口实现的地方，减小代码的重复利用率
//在结点p中查找关键字
int SearchBTNode(BTree p, KeyType k) 
{
	int i = 1;
	while (i <= p->keynum && k > p->key[i])
		i++;
	return i;
}

//在结点p中删除关键字
int BTNodeDelete(BTNode* p, KeyType key) 
{
	int i;
	int tag; //查找标志
	if (p == NULL)
		return 0;
	else 
	{
		tag = FindBTNode(p, key, i);  //返回查找结果 
		if (tag == 1)  //查找成功
		{
			if (p->ptr[i - 1] != NULL) //删除的是非叶子结点
			{             
				Substitution(p, i); //寻找相邻关键字(右子树中最小的关键字)
				BTNodeDelete(p->ptr[i], p->key[i]);  //执行删除操作
			}
			else Remove(p, i);   //从结点p中位置i处删除关键字
		}
		else
			tag = BTNodeDelete(p->ptr[i], key); //沿孩子结点递归查找并删除关键字k
		if (p->ptr[i] != NULL)
			if (p->ptr[i]->keynum < (m - 1) / 2)     //删除后关键字个数小于MIN=(m-1)/2
				AdjustBTree(p, i);                   //调整B树 
		return tag;
	}
}

//递归遍历输出
void Traverse(BTree t, int k) 
{
	if (t != NULL) 
	{
		int i;
		for (i = 1; i <= t->keynum; i++) 
		{
			if (t->ptr[i - 1] != NULL) //输出非终端结点
			{  
				if (i == 1) 
				{
					for (int j = 1; j <= (k * 2); j++) printf("  "); //输出空格
					for (int j = 1; j <= t->keynum; j++) 
					{
						if (j == t->keynum)  printf("%d\n", t->key[j]);
						else printf("%d,", t->key[j]);
					}
					k++;
				}
			}
			else 
			{                        //输出终端结点
				if (i == 1 && i == t->keynum) 
				{
					for (int j = 1; j <= (k * 2); j++) printf("  ");//输出空格
					printf("%d\n", t->key[i]);
				}
				if (i == 1 && i < t->keynum) 
				{
					for (int j = 1; j <= (k * 2); j++) printf("  ");//输出空格
					printf("%d,", t->key[i]);
				}
				if (i != 1 && i < t->keynum) 
				{
					printf("%d,", t->key[i]);
				}
				if (i != 1 && i == t->keynum) 
				{
					printf("%d\n", t->key[i]);
				}
			}
			if (i == 1)
				Traverse(t->ptr[i - 1], k);
			Traverse(t->ptr[i], k);  //递归遍历
		}
	}
}

//将q结点分裂成两个结点，前一半留在原节点，后一半留在ap指向的新结点
void split(BTree& q, int s, BTree& ap) 
{
	int i, j, n = q->keynum;
	ap = (BTNode*)malloc(sizeof(BTNode));
	ap->ptr[0] = q->ptr[s];
	for (i = s + 1, j = 1; i <= n; i++, j++) 
	{
		ap->key[j] = q->key[i];
		ap->ptr[j] = q->ptr[i];
		ap->book[j] = q->book[i];
	}
	ap->keynum = n - s;
	ap->parent = q->parent;
	for (i = 0; i <= n - s; i++)
		if (ap->ptr[i] != NULL) ap->ptr[i]->parent = ap;
	q->keynum = s - 1;
}

//生成新的根结点
void newRoot(BTree& t, BTree p, KeyType x, BTree ap, BookType* book) 
{
	t = (BTNode*)malloc(sizeof(BTNode));
	t->keynum = 1; t->ptr[0] = p; t->ptr[1] = ap; t->key[1] = x; t->book[1] = book;
	if (p != NULL) p->parent = t;
	if (ap != NULL) ap->parent = t;
	t->parent = NULL;
}

//关键字x和新结点指针ap分别插入到q->key[i]和q->ptr[i]
void Insert(BTree& q, int i, KeyType x, BTree ap, BookType* book) 
{
	int j, n = q->keynum;
	for (j = n; j >= i; j--) 
	{
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
		q->book[j + 1] = q->book[j];
	}
	q->key[i] = x;
	q->ptr[i] = ap;
	q->book[i] = book;
	if (ap != NULL)
		ap->parent = q;
	q->keynum++;
}

//在结点p中查找关键字k，返回位置i
int FindBTNode(BTNode* p, KeyType k, int& i) //反映是否在结点p中是否查找到关键字k 
{ 
	if (k < p->key[1])  //结点p中查找关键字k失败
	{                                
		i = 0;
		return 0;
	}
	else  //在p结点中查找
	{                                          
		i = p->keynum;
		while (k < p->key[i] && i>1)
			i--;
		if (k == p->key[i])   //结点p中查找关键字k成功 
			return 1;
	}
}

//在结点p中删除关键字key[i]和其孩子结点ptr[i]
void Remove(BTNode* p, int i) 
{
	int j;
	for (j = i + 1; j <= p->keynum; j++)  //前移删除key[i]和ptr[i]
	{    
		p->key[j - 1] = p->key[j];
		p->ptr[j - 1] = p->ptr[j];
		p->book[j - 1] = p->book[j];
	}
	p->keynum--;
}

//查找被删关键字p->key[i](在非叶子结点中)的替代叶子结点(右子树中值最小的关键字)
void Substitution(BTNode* p, int i) 
{
	BTNode* q;
	for (q = p->ptr[i]; q->ptr[0] != NULL; q = q->ptr[0]);
	p->key[i] = q->key[1];  //复制关键字值
	p->book[i] = q->book[1];
} 

//在结点p中删除关键字key[i]后调整B树
void AdjustBTree(BTNode* p, int i) 
{
	int Min = (m - 1) / 2;
	if (i == 0)      //删除的是最左边关键字
		if (p->ptr[1]->keynum > Min)     //右结点可以借
			MoveLeft(p, 1);
		else      //右兄弟不够借 
			Combine(p, 1);
	else if (i == p->keynum)     //删除的是最右边关键字
		if (p->ptr[i - 1]->keynum > Min)  //左结点可以借 
			MoveRight(p, i);
		else        //左结点不够借 
			Combine(p, i);
	else if (p->ptr[i - 1]->keynum > Min)   //删除关键字在中部且左结点够借 
		MoveRight(p, i);
	else if (p->ptr[i + 1]->keynum > Min)    //删除关键字在中部且右结点够借 
		MoveLeft(p, i + 1);
	else    //删除关键字在中部且左右结点都不够借
		Combine(p, i);
}

//将双亲结点p中的最后一个关键字移入右结点q中,将左结点aq中的最后一个关键字移入双亲结点p中
void MoveRight(BTNode* p, int i) 
{
	int j;
	BTNode* q = p->ptr[i];
	BTNode* aq = p->ptr[i - 1];

	for (j = q->keynum; j > 0; j--) //将右兄弟q中所有关键字向后移动一位
	{                       
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
		q->book[j + 1] = q->book[j];
	}

	q->ptr[1] = q->ptr[0];  //从双亲结点p移动关键字到右兄弟q中
	q->key[1] = p->key[i];
	q->book[1] = q->book[i];
	q->keynum++;

	p->key[i] = aq->key[aq->keynum]; //将左兄弟aq中最后一个关键字移动到双亲结点p中
	p->book[i] = aq->book[aq->keynum];
	p->ptr[i]->ptr[0] = aq->ptr[aq->keynum];
	aq->keynum--;
}

//将双亲结点p中的第一个关键字移入结点aq中,将结点q中的第一个关键字移入双亲结点p中
void MoveLeft(BTNode* p, int i) 
{
	//将双亲结点p中的第一个关键字移入左结点aq中，
	//将右结点q中的第一个关键字移入双亲结点p中
	int j;
	BTNode* aq = p->ptr[i - 1];
	BTNode* q = p->ptr[i];

	aq->keynum++;   //把双亲结点p中的关键字移动到左兄弟aq中
	aq->key[aq->keynum] = p->key[i];
	aq->book[aq->keynum] = p->book[i];
	aq->ptr[aq->keynum] = p->ptr[i]->ptr[0];

	p->key[i] = q->key[1];  //把右兄弟q中的关键字移动到双亲节点p中  
	p->book[i] = q->book[1];
	q->ptr[0] = q->ptr[1];
	q->keynum--;

	for (j = 1; j <= aq->keynum; j++) //将右兄弟q中所有关键字向前移动一位
	{                     
		aq->key[j] = aq->key[j + 1];
		aq->book[j] = aq->book[j + 1];
		aq->ptr[j] = aq->ptr[j + 1];
	}
}

//将双亲结点p、右结点q合并入左结点aq,并调整双亲结点p中的剩余关键字的位置
void Combine(BTNode* p, int i) 
{
	int j;
	BTNode* q = p->ptr[i];
	BTNode* aq = p->ptr[i - 1];

	aq->keynum++;    //将双亲结点的关键字p->key[i]插入到左结点aq     
	aq->key[aq->keynum] = p->key[i];
	aq->book[aq->keynum] = p->book[i];
	aq->ptr[aq->keynum] = q->ptr[0];

	for (j = 1; j <= q->keynum; j++)  //将右结点q中的所有关键字插入到左结点aq 
	{                     
		aq->keynum++;
		aq->key[aq->keynum] = q->key[j];
		aq->book[aq->keynum] = q->book[i];
		aq->ptr[aq->keynum] = q->ptr[j];
	}

	for (j = i; j < p->keynum; j++) //将双亲结点p中的p->key[i]后的所有关键字向前移动一位 
	{                       
		p->key[j] = p->key[j + 1];
		p->book[j] = p->book[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
	p->keynum--;    //修改双亲结点p的keynum值 
	free(q);  //释放空右结点q的空间
}






//对文献直接操作的接口
//采编入库
void InsertBook(BTree& t, KeyType key, result r, char* bookname, char* writername, char* bookpress, int num) 
{
	BookType* book;
	book = (BookType*)malloc(sizeof(BookType));
	strcpy_s(book->bookName, bookname);
	strcpy_s(book->writerName, writername);
	strcpy_s(book->bookPress, bookpress);
	book->booknumAll = num;
	book->booknumNow = num;
	book->reader = NULL;
	if (r.tag == 0)
		InsertBTree(t, key, r.pt, r.i, book);
}

//清除库存
void DeleteBook(BTree& t, KeyType key) 
{
	DeleteBTree(t, key);
}

//借阅图书
void BorrowBook(result r, int number, char* name) 
{
	ReaderType* reader;
	reader = (ReaderType*)malloc(sizeof(ReaderType));
	strcpy_s(reader->name, name);
	reader->readerId = number;
	reader->time = 50;
	ReaderType* q;
	q = r.pt->book[r.i]->reader;
	if (q == NULL) 
	{
		r.pt->book[r.i]->reader = reader;
		reader->next = NULL;
	}
	else 
	{
		reader->next = r.pt->book[r.i]->reader;
		r.pt->book[r.i]->reader = reader;
	}
	r.pt->book[r.i]->booknumNow--;
}

//归还图书
Status ReturnBook(result r, int number, char* name) {
	ReaderType* q, * p;
	q = r.pt->book[r.i]->reader;
	p = q;
	while (q != NULL && (q->readerId != number || strcmp(q->name, name))) {
		p = q;
		q = q->next;
	}
	if (q == NULL) {
		return FALSE;
	}
	else {
		if (q == r.pt->book[r.i]->reader)
			r.pt->book[r.i]->reader = q->next;
		else
			p->next = q->next;
		free(q);
		r.pt->book[r.i]->booknumNow++;
	}
	return TRUE;
}

//输出某本书的全部信息（包括借阅者）
void ShowBookAll(BTree t, KeyType key) 
{
	ShowBook(t, key);
	result r;
	SearchBTree(t, key, r);
	ReaderType* q;
	q = r.pt->book[r.i]->reader;
	while (q != NULL) 
	{
		printf("|借阅证号：%d, 姓名：%s, 最迟还文献时间为：%d。\n", q->readerId, q->name, q->time);
		printf("|-------------------------------------------------------------------------|\n");
		q = q->next;
	}
}

//输出某本书的信息（不包括借阅者）
void ShowBook(BTree t, KeyType key) 
{
	result r;
	SearchBTree(t, key, r);
	if (r.tag == 1) 
	{
		printf("|-----------------------------------------------------------------------------|\n");
		printf("|文献号     文献名           作者          出版社            现存量  总库存量 |\n");
		printf("|-----------------------------------------------------------------------------|\n");
		printf("|%d     %s      %s     %s        %d     %d      |\n", r.pt->key[r.i], r.pt->book[r.i]->bookName,
			r.pt->book[r.i]->writerName, r.pt->book[r.i]->bookPress, r.pt->book[r.i]->booknumNow, r.pt->book[r.i]->booknumAll);
		printf("|-----------------------------------------------------------------------------|\n");
	}
}

//添加某本书的数量
void addBook(BTree t, KeyType key, int num) 
{
	result r;
	SearchBTree(t, key, r);
	if (r.tag == 1) 
	{
		r.pt->book[r.i]->booknumNow = r.pt->book[r.i]->booknumNow + num;
		r.pt->book[r.i]->booknumAll = r.pt->book[r.i]->booknumAll + num;
	}
}

//检查某本书的现存量是否大于0
Status emtyBook(BTree q, int i) 
{
	if (q->book[i]->booknumNow >= 1)
		return FALSE;
	return TRUE;
}
