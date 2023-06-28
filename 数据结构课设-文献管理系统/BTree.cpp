#include"BTree.h"
//��ʼ�����׹���ϵͳ
void InitBTree(BTree& t)
{	//�ȳ�ʼ��t

	result r;
	int j, n = 14;
	KeyType key[] = { 35,16,18,70,5,50,22,60,13,17,12,45,25,42 };
	int num[] = { 50,60,75,81,45,12,44,55,66,77,85,40,40,52 };
	char name[14][30] = { "����˧�����","���ݽṹ���Ǻ�","����һ�ͱ���",
		"�۳���֮��","�۲�������","�۽�ͨ","��ǰ��","�۱���",
		"���й�Ӣ��","�ۼ������չ","�����彡��","�۸���","�ۿ���","�ۿ���" };
	char writer[14][20] = { "������","����","����","����","����","����",
		"����","�׷�","������","����","����","����","����","����" };
	char press[14][20] = { "�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������",
		"�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������",
		"�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������",
		"�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������",
		"�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������","�㶫��ҵ��ѧ������" };
	for (j = 0; j < n; j++) {     //��һ����Ԫ��
		SearchBTree(t, key[j], r);
		if (r.tag == 0)
			InsertBook(t, key[j], r, name[j], writer[j], press[j], num[j]);
		printf("����%d:\n", key[j]);
		PrintBTree(t);   //�������
		ShowBook(t, key[j]);
	}
}




//B�������ӿڵ�ʵ��(�����ϵĽӿ�)
//����
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

//����
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

//ɾ��
void DeleteBTree(BTree& t, KeyType key)
{
	BTNode* p;
	int a = BTNodeDelete(t, key);//ɾ���ؼ���key 
	if (a == 0)                //����ʧ�� 
		printf("�ؼ���%d����B����\n", key);
	else if (t->keynum == 0) //����
	{                           
		p = t;
		t = t->ptr[0];
		free(p);
	}
}

//������ӡ���
void PrintBTree(BTree t)
{
	printf("��ʱB����״̬���£�\n");
	if (t == NULL)
		printf("��B��Ϊ����\n");
	else
		Traverse(t, 0); //�԰�������ʽ�ݹ�������
}




//����С�ӿ�ʵ�ֵĵط�����С������ظ�������
//�ڽ��p�в��ҹؼ���
int SearchBTNode(BTree p, KeyType k) 
{
	int i = 1;
	while (i <= p->keynum && k > p->key[i])
		i++;
	return i;
}

//�ڽ��p��ɾ���ؼ���
int BTNodeDelete(BTNode* p, KeyType key) 
{
	int i;
	int tag; //���ұ�־
	if (p == NULL)
		return 0;
	else 
	{
		tag = FindBTNode(p, key, i);  //���ز��ҽ�� 
		if (tag == 1)  //���ҳɹ�
		{
			if (p->ptr[i - 1] != NULL) //ɾ�����Ƿ�Ҷ�ӽ��
			{             
				Substitution(p, i); //Ѱ�����ڹؼ���(����������С�Ĺؼ���)
				BTNodeDelete(p->ptr[i], p->key[i]);  //ִ��ɾ������
			}
			else Remove(p, i);   //�ӽ��p��λ��i��ɾ���ؼ���
		}
		else
			tag = BTNodeDelete(p->ptr[i], key); //�غ��ӽ��ݹ���Ҳ�ɾ���ؼ���k
		if (p->ptr[i] != NULL)
			if (p->ptr[i]->keynum < (m - 1) / 2)     //ɾ����ؼ��ָ���С��MIN=(m-1)/2
				AdjustBTree(p, i);                   //����B�� 
		return tag;
	}
}

//�ݹ�������
void Traverse(BTree t, int k) 
{
	if (t != NULL) 
	{
		int i;
		for (i = 1; i <= t->keynum; i++) 
		{
			if (t->ptr[i - 1] != NULL) //������ն˽��
			{  
				if (i == 1) 
				{
					for (int j = 1; j <= (k * 2); j++) printf("  "); //����ո�
					for (int j = 1; j <= t->keynum; j++) 
					{
						if (j == t->keynum)  printf("%d\n", t->key[j]);
						else printf("%d,", t->key[j]);
					}
					k++;
				}
			}
			else 
			{                        //����ն˽��
				if (i == 1 && i == t->keynum) 
				{
					for (int j = 1; j <= (k * 2); j++) printf("  ");//����ո�
					printf("%d\n", t->key[i]);
				}
				if (i == 1 && i < t->keynum) 
				{
					for (int j = 1; j <= (k * 2); j++) printf("  ");//����ո�
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
			Traverse(t->ptr[i], k);  //�ݹ����
		}
	}
}

//��q�����ѳ�������㣬ǰһ������ԭ�ڵ㣬��һ������apָ����½��
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

//�����µĸ����
void newRoot(BTree& t, BTree p, KeyType x, BTree ap, BookType* book) 
{
	t = (BTNode*)malloc(sizeof(BTNode));
	t->keynum = 1; t->ptr[0] = p; t->ptr[1] = ap; t->key[1] = x; t->book[1] = book;
	if (p != NULL) p->parent = t;
	if (ap != NULL) ap->parent = t;
	t->parent = NULL;
}

//�ؼ���x���½��ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
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

//�ڽ��p�в��ҹؼ���k������λ��i
int FindBTNode(BTNode* p, KeyType k, int& i) //��ӳ�Ƿ��ڽ��p���Ƿ���ҵ��ؼ���k 
{ 
	if (k < p->key[1])  //���p�в��ҹؼ���kʧ��
	{                                
		i = 0;
		return 0;
	}
	else  //��p����в���
	{                                          
		i = p->keynum;
		while (k < p->key[i] && i>1)
			i--;
		if (k == p->key[i])   //���p�в��ҹؼ���k�ɹ� 
			return 1;
	}
}

//�ڽ��p��ɾ���ؼ���key[i]���亢�ӽ��ptr[i]
void Remove(BTNode* p, int i) 
{
	int j;
	for (j = i + 1; j <= p->keynum; j++)  //ǰ��ɾ��key[i]��ptr[i]
	{    
		p->key[j - 1] = p->key[j];
		p->ptr[j - 1] = p->ptr[j];
		p->book[j - 1] = p->book[j];
	}
	p->keynum--;
}

//���ұ�ɾ�ؼ���p->key[i](�ڷ�Ҷ�ӽ����)�����Ҷ�ӽ��(��������ֵ��С�Ĺؼ���)
void Substitution(BTNode* p, int i) 
{
	BTNode* q;
	for (q = p->ptr[i]; q->ptr[0] != NULL; q = q->ptr[0]);
	p->key[i] = q->key[1];  //���ƹؼ���ֵ
	p->book[i] = q->book[1];
} 

//�ڽ��p��ɾ���ؼ���key[i]�����B��
void AdjustBTree(BTNode* p, int i) 
{
	int Min = (m - 1) / 2;
	if (i == 0)      //ɾ����������߹ؼ���
		if (p->ptr[1]->keynum > Min)     //�ҽ����Խ�
			MoveLeft(p, 1);
		else      //���ֵܲ����� 
			Combine(p, 1);
	else if (i == p->keynum)     //ɾ���������ұ߹ؼ���
		if (p->ptr[i - 1]->keynum > Min)  //������Խ� 
			MoveRight(p, i);
		else        //���㲻���� 
			Combine(p, i);
	else if (p->ptr[i - 1]->keynum > Min)   //ɾ���ؼ������в������㹻�� 
		MoveRight(p, i);
	else if (p->ptr[i + 1]->keynum > Min)    //ɾ���ؼ������в����ҽ�㹻�� 
		MoveLeft(p, i + 1);
	else    //ɾ���ؼ������в������ҽ�㶼������
		Combine(p, i);
}

//��˫�׽��p�е����һ���ؼ��������ҽ��q��,������aq�е����һ���ؼ�������˫�׽��p��
void MoveRight(BTNode* p, int i) 
{
	int j;
	BTNode* q = p->ptr[i];
	BTNode* aq = p->ptr[i - 1];

	for (j = q->keynum; j > 0; j--) //�����ֵ�q�����йؼ�������ƶ�һλ
	{                       
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
		q->book[j + 1] = q->book[j];
	}

	q->ptr[1] = q->ptr[0];  //��˫�׽��p�ƶ��ؼ��ֵ����ֵ�q��
	q->key[1] = p->key[i];
	q->book[1] = q->book[i];
	q->keynum++;

	p->key[i] = aq->key[aq->keynum]; //�����ֵ�aq�����һ���ؼ����ƶ���˫�׽��p��
	p->book[i] = aq->book[aq->keynum];
	p->ptr[i]->ptr[0] = aq->ptr[aq->keynum];
	aq->keynum--;
}

//��˫�׽��p�еĵ�һ���ؼ���������aq��,�����q�еĵ�һ���ؼ�������˫�׽��p��
void MoveLeft(BTNode* p, int i) 
{
	//��˫�׽��p�еĵ�һ���ؼ�����������aq�У�
	//���ҽ��q�еĵ�һ���ؼ�������˫�׽��p��
	int j;
	BTNode* aq = p->ptr[i - 1];
	BTNode* q = p->ptr[i];

	aq->keynum++;   //��˫�׽��p�еĹؼ����ƶ������ֵ�aq��
	aq->key[aq->keynum] = p->key[i];
	aq->book[aq->keynum] = p->book[i];
	aq->ptr[aq->keynum] = p->ptr[i]->ptr[0];

	p->key[i] = q->key[1];  //�����ֵ�q�еĹؼ����ƶ���˫�׽ڵ�p��  
	p->book[i] = q->book[1];
	q->ptr[0] = q->ptr[1];
	q->keynum--;

	for (j = 1; j <= aq->keynum; j++) //�����ֵ�q�����йؼ�����ǰ�ƶ�һλ
	{                     
		aq->key[j] = aq->key[j + 1];
		aq->book[j] = aq->book[j + 1];
		aq->ptr[j] = aq->ptr[j + 1];
	}
}

//��˫�׽��p���ҽ��q�ϲ�������aq,������˫�׽��p�е�ʣ��ؼ��ֵ�λ��
void Combine(BTNode* p, int i) 
{
	int j;
	BTNode* q = p->ptr[i];
	BTNode* aq = p->ptr[i - 1];

	aq->keynum++;    //��˫�׽��Ĺؼ���p->key[i]���뵽����aq     
	aq->key[aq->keynum] = p->key[i];
	aq->book[aq->keynum] = p->book[i];
	aq->ptr[aq->keynum] = q->ptr[0];

	for (j = 1; j <= q->keynum; j++)  //���ҽ��q�е����йؼ��ֲ��뵽����aq 
	{                     
		aq->keynum++;
		aq->key[aq->keynum] = q->key[j];
		aq->book[aq->keynum] = q->book[i];
		aq->ptr[aq->keynum] = q->ptr[j];
	}

	for (j = i; j < p->keynum; j++) //��˫�׽��p�е�p->key[i]������йؼ�����ǰ�ƶ�һλ 
	{                       
		p->key[j] = p->key[j + 1];
		p->book[j] = p->book[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
	p->keynum--;    //�޸�˫�׽��p��keynumֵ 
	free(q);  //�ͷſ��ҽ��q�Ŀռ�
}






//������ֱ�Ӳ����Ľӿ�
//�ɱ����
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

//������
void DeleteBook(BTree& t, KeyType key) 
{
	DeleteBTree(t, key);
}

//����ͼ��
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

//�黹ͼ��
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

//���ĳ�����ȫ����Ϣ�����������ߣ�
void ShowBookAll(BTree t, KeyType key) 
{
	ShowBook(t, key);
	result r;
	SearchBTree(t, key, r);
	ReaderType* q;
	q = r.pt->book[r.i]->reader;
	while (q != NULL) 
	{
		printf("|����֤�ţ�%d, ������%s, ��ٻ�����ʱ��Ϊ��%d��\n", q->readerId, q->name, q->time);
		printf("|-------------------------------------------------------------------------|\n");
		q = q->next;
	}
}

//���ĳ�������Ϣ�������������ߣ�
void ShowBook(BTree t, KeyType key) 
{
	result r;
	SearchBTree(t, key, r);
	if (r.tag == 1) 
	{
		printf("|-----------------------------------------------------------------------------|\n");
		printf("|���׺�     ������           ����          ������            �ִ���  �ܿ���� |\n");
		printf("|-----------------------------------------------------------------------------|\n");
		printf("|%d     %s      %s     %s        %d     %d      |\n", r.pt->key[r.i], r.pt->book[r.i]->bookName,
			r.pt->book[r.i]->writerName, r.pt->book[r.i]->bookPress, r.pt->book[r.i]->booknumNow, r.pt->book[r.i]->booknumAll);
		printf("|-----------------------------------------------------------------------------|\n");
	}
}

//���ĳ���������
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

//���ĳ������ִ����Ƿ����0
Status emtyBook(BTree q, int i) 
{
	if (q->book[i]->booknumNow >= 1)
		return FALSE;
	return TRUE;
}
