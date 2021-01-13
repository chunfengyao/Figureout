#include <stdio.h>
#include <stdlib.h>
#define maxsize 100
//运算符栈数据类型定义
typedef char Item;
typedef struct charstack {
	Item data[maxsize];
	int top;
}
op;
typedef op * Op;
//运算子栈数据类型定义
typedef long double stItem;
typedef struct intstack {
	stItem num[maxsize];
	int top;
}
st;
typedef st * St;
Op Initop();
int Pushop(Op p,Item i);
int sop(Item a);
int sch(Item a);
int Popop(Op p,Item * i);
Item gettopop(Op p);
void printop(Op p);
void Destoryop(Op p);
stItem workout(Item a[]);
St Initst();
int Pushst(St p,stItem i);
int Popst(St p,stItem * i);
stItem gettopst(St p);
void Destoryst(St p);
int wheatherleft(Op p);
int main() {
	char a[maxsize+1]= {
		0
	};
	int b;
	b=0;
	char postb[maxsize+1]= {
		0
	};
	int i;
	printf("请在英文状态下输入表达式，表达式长度为%d个字符以内。\n",maxsize);
	printf("注：目前不支持输入中有小数，如果输入了小数，会被忽略掉小数点！！！或者，可以修改源码自己处理一下小数点。\n");
	printf("注：表达式中请勿出现空格结尾记得加上等于号\n");
	scanf("%s",a);
	system("cls");
	printf("以下是您所输入的表达式\n");
	puts(a);
	Op q;
	q=Initop();
	Pushop(q,'=');
	for (i=0;a[i]!=0;i++) {
		if (a[i]=='=' || a[i]=='+' || a[i]=='-' || a[i]=='*' || a[i]=='/' || a[i]=='(' || a[i]==')') {
			if(sch(a[i])>sop(gettopop(q))) {
				Pushop(q,a[i]);
			} else if(sch(a[i])<=sop(gettopop(q))) {
				Item j;
				while(sch(a[i])<=sop(gettopop(q))) {
					if(sch(a[i])==sop(gettopop(q))) {
						Popop(q,&j);
						continue;
					};
					Popop(q,&j);
					postb[b]=j;
					b++;
				}
				if(a[i]==')')
					continue;
				Pushop(q,a[i]);
			};
		} else {
		// TODO 这里并没有对小数进行入栈，需要的话，自行添加并处理一下！！！
		//while ((a[i]>='0' && a[i]<='9') || (a[i] == '.')) {
			while (a[i]>='0' && a[i]<='9') {
				postb[b]=a[i];
				b++;
				i++;
			};
			postb[b]='#';
			b++;
			i--;
		}
	};
	while(gettopop(q)!='=') {
		Item j;
		Popop(q,&j);
		postb[b]=j;
		b++;
	};
	printf("\n以下为该中缀表达式的后缀表达式：\n");
	int j;
	puts(postb);
	Destoryop(q);
	printf("\n以下是表达式运算结果：\n%.10f\n",workout(postb));
	return 0;
};
stItem workout(Item a[]) {
	St q;
	q=Initst();
	int i;
	for (i=0;a[i]!='';i++) {
		switch (a[i]) {
			case '+': {
				stItem j,k;
				Popst(q,&j);
				Popst(q,&k);
				Pushst(q,j+k);
				break;
			}
			case '-': {
				stItem j,k;
				Popst(q,&j);
				Popst(q,&k);
				Pushst(q,k-j);
				break;
			}
			case '*': {
				stItem j,k;
				Popst(q,&j);
				Popst(q,&k);
				Pushst(q,j*k);
				break;
			}
			case '/': {
				stItem j,k;
				Popst(q,&j);
				Popst(q,&k);
				Pushst(q,k/j);
				break;
			}
			default: {
				stItem s,s1;
				s1=0;
				for (s=1;a[i]>='0' && a[i]<='9';s=s*10) {
					s1=s1*s+(a[i]-'0');
					i++;
				};
				Pushst(q,s1);
				break;
			}
		}
	}
	return q->num[q->top];
};
//op运算符栈
int wheatherleft(Op p) {
	int i;
	i=p->top;
	for (i;i>=0;i--) {
		if(p->data[i]=='(')
			return 0;
	};
	return 1;
};
int sop(Item a) {
	switch (a) {
		case '=' : return 0;
		case '(' : return 1;
		case '+' : return 3;
		case '-' : return 3;
		case '*' : return 5;
		case '/' : return 5;
		case ')' : return 6;
	}
};
int sch(Item a) {
	switch (a) {
		case '=' : return 0;
		case '(' : return 6;
		case '+' : return 2;
		case '-' : return 2;
		case '*' : return 4;
		case '/' : return 4;
		case ')' : return 1;
	}
};
Op Initop() {
	Op p;
	p=(Op)malloc(sizeof(op));
	p->top=-1;
	return p;
};
int Pushop(Op p,Item i) {
	if (p->top==maxsize-1)
		return 1; else {
		(p->top)++;
		p->data[p->top]=i;
		return 0;
	};
};
int Popop(Op p,Item * i) {
	if(p->top==-1)
		return 1; else {
		*i=p->data[p->top];
		p->top--;
		return 0;
	};
};
void printop(Op p) {
	int i;
	i=p->top;
	printf("此刻栈内元素有：");
	for (i;i>=0;i--)
		printf("%c ",p->data[i]);
	printf("\n");
};
Item gettopop(Op p) {
	//有一定的隐患（需要加入栈空的判断）！！！！！！
	return p->data[p->top];
};
void Destoryop(Op p) {
	free(p);
};
//st运算子栈
St Initst() {
	St p;
	p=(St)malloc(sizeof(st));
	p->top=-1;
	return p;
};
int Pushst(St p,stItem i) {
	if (p->top==maxsize-1)
		return 1; else {
		(p->top)++;
		p->num[p->top]=i;
		return 0;
	};
};
int Popst(St p,stItem * i) {
	if(p->top==-1)
		return 1; else {
		*i=p->num[p->top];
		p->top--;
		return 0;
	};
};
void Destoryst(St p) {
	free(p);
};
