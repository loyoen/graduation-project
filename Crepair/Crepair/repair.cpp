#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <stdio.h>

using namespace std;

struct point
{
	int num;
	int sectionnum;
	point *next;
};

struct section
{
	int num;
	point *first;
};

struct ArcNodeH
{
	int hedge;  //指向超边号
	ArcNodeH *nextarc; //包含该顶点下一条超边
};

struct Vnode
{
	int  node; //顶点号
	ArcNodeH *firstarc; //包含该顶点的第一条超边  
};
struct ArcNodeV
{
	int node; //指向的顶点号
	ArcNodeV *nextarc; //该超边包含的下个顶点
};

struct HEnode
{
	int Enode; //超边号
	ArcNodeV *firstarc; //该超边包含的第一个顶点
	int weight;
};


bool judge(int m,int n,HEnode HE[],Vnode V[],int num)
{
	ArcNodeH *p=V[m].firstarc;
	if(num<=0)
		return false;
	while(p!=NULL)
	{
		ArcNodeV *q=HE[p->hedge].firstarc;
		while(q!=NULL)
		{
			if(q->node==n)
				return true;
			else
			{
				if(judge(q->node,n,HE,V,num-1))
					return true;
			}
			q=q->nextarc;
		}
		p=p->nextarc;	
	}
	return false;
}

bool belong(int node,point p)
{
	point *q =p.next;
	while(q!=NULL)
	{
		if(node==q->num)
			return true;
		q=q->next;
	}
	return false;
}

int main()
{
	
	ifstream file,file3;
	ofstream file2,file4;
	char temp[1024];


	section sec[8000];
	point poi[60000];
	HEnode HE[30000];
	Vnode V[60000];
	for(int i=0;i<30000;i++)
	{
		HE[i].firstarc=NULL;
		HE[i].weight=-1;
	}
	for(int i=0;i<60000;i++)
		V[i].firstarc=NULL;
	for(int i=0;i<8000;i++)
		sec[i].first=NULL;
	for(int i=0;i<60000;i++)
	{
		poi[i].next=NULL;
		poi[i].sectionnum=-1;
	}

	file.open(".//testfile.hgr.part.8000");
	file2.open(".//norepair.txt");
	int count=1;
	if(file != NULL)
	{
		while(!file.eof())
		{
		
			file.getline(temp,1024);
			int num = atoi(temp);
			point *p=(point *)malloc(sizeof(point));
			p->num=count;
			p->next=NULL;
			if(sec[num].first==NULL)
				sec[num].first=p;
			else
			{
				point *q=sec[num].first;
				while(q->next!=NULL)
					q=q->next;
				q->next=p;
			}
			poi[count].sectionnum=num;
			count++;
		}
	}
	
	for(int i=1;poi[i].sectionnum!=-1;i++)
	{
		char temp[10];
		sprintf_s(temp,10,"%d",i);
		file2.write(temp,strlen(temp));
		file2.write(" : ",3);
		point *p=sec[poi[i].sectionnum].first;
		while(p!=NULL)
		{
			if(p->num!=i)
			{
				sprintf_s(temp,10,"%d",p->num);
				file2.write(temp,strlen(temp));
				file2.write(" ",1);
			}
			p=p->next;
		}
		file2.write("\n",1);
		
	}
	file.close();
	file2.close();
	file3.open(".//testfile.hgr");
	file4.open(".//repair.txt");    //第一次优化的文件
	int readline=-1;
	if(file3 != NULL)
	{
		while(!file3.eof())
		{

			readline++;
			file3.getline(temp,1024);
			if(strlen(temp)<=1)
				break;
			if(readline==0)
				continue;
			char *weight,*p;
			p=strtok(temp," ");
			weight=(char *)malloc(strlen(p)+1);
			char *strtemp;
			strcpy(weight,p);
			while(p!=NULL)
			{
				p=strtok(NULL," ");
				if(p==NULL)
					break;
				strtemp=(char *)malloc(strlen(p)+1);
				strcpy(strtemp,p);
				int num=atoi(strtemp);
				ArcNodeV *q=(ArcNodeV *)malloc(sizeof(ArcNodeV));
				q->node=num;
				q->nextarc=NULL;
				ArcNodeV *t;
				t=HE[readline].firstarc;
				HE[readline].firstarc=q;
				q->nextarc=t;
				HE[readline].Enode=readline;
				HE[readline].weight=atoi(weight);

				ArcNodeH *m = (ArcNodeH *)malloc(sizeof(ArcNodeH));
				m->hedge=readline;
				m->nextarc=NULL;

				ArcNodeH *n,*back;             //每个顶点的超边用非递减排序存储在V中
				n=V[num].firstarc;
				int swit=-1;
				while(n!=NULL)
				{
					if(HE[m->hedge].weight<HE[n->hedge].weight)
					{
						back=n;
						swit=1;
						n=n->nextarc;
					}
					else
						break;
				}

				if(-1==swit)
				{
					V[num].firstarc=m;
					V[num].node=num;
					m->nextarc=n;
				}
				else
				{
					back->nextarc=m;
					m->nextarc=n;
				}
				

				
			}

			
			
		}
	}

	for(int i=1;poi[i].sectionnum!=-1;i++)
	{
		char temp[10];
		sprintf_s(temp,10,"%d",i);
		file4.write(temp,strlen(temp));
		file4.write(" : ",3);
		point *p=sec[poi[i].sectionnum].first;
		point *last;
		int note=0;
		if(i==2023)
			int k=1;
		while(p!=NULL)
		{
			if(p->num!=i)
			{
				if(judge(p->num,i,HE,V,2))   //是否两条超边可达
				{
					sprintf_s(temp,10,"%d",p->num);
					file4.write(temp,strlen(temp));
					file4.write(" ",1);
					
					point *qq=(point *)malloc(sizeof(point));   //poi[i]存储点i第一次修正后的推荐集合
					qq->num=p->num;
					qq->sectionnum=poi[i].sectionnum;
					qq->next=NULL;
					point *qq2=poi[i].next;
					if(qq2==NULL)
						poi[i].next=qq;
					else
					{
						while(qq2->next!=NULL)
							qq2=qq2->next;
						qq2->next=qq;
					}
				}
			/*	else
				{
					if(note!=0)
					{
						last->next=p->next;
					}
					else
					{
						sec[poi[i].sectionnum].first=p->next;
					}
				}
			*/
			}
			last=p;
			p=p->next;
			note++;
		}
		file4.write("\n",1);
		
	}
	file3.close();
	file4.close();


	int icount=0;
	for(int i=1;poi[i].sectionnum!=-1;i++)
	{
		icount=0;
		if(i==12127)
			int k=0;
		ArcNodeH *p=V[i].firstarc;
		while(p!=NULL&&icount<4)
		{
			ArcNodeV *m=HE[p->hedge].firstarc;
			while(m!=NULL&&icount<4)
			{
				if(m->node!=i)
				{
					if(!belong(m->node,poi[i]))
					{
						icount++;
						point *qq=(point *)malloc(sizeof(point));    //第二次修正poi[i]，顶点复用，尾插法
						qq->num=m->node;
						qq->sectionnum=poi[m->node].sectionnum;
						qq->next=NULL;
						point *qq2=poi[i].next;
						if(qq2==NULL)
							poi[i].next=qq;
						else
						{
							while(qq2->next!=NULL)
								qq2=qq2->next;
							qq2->next=qq;
						}
						
							
					}
				}
				m=m->nextarc;
			}
			p=p->nextarc;
		}
	}
	
	ofstream file6;
	file6.open(".//repair2.txt");
	for(int i=1;poi[i].sectionnum!=-1;i++)
	{
		char temp[10];
		sprintf_s(temp,10,"%d",i);
		file6.write(temp,strlen(temp));
		file6.write(" : ",3);
		point *p=poi[i].next;
		while(p!=NULL)
		{
			sprintf_s(temp,10,"%d",p->num);
			file6.write(temp,strlen(temp));
			file6.write(" ",1);
			p=p->next;
		}
		file6.write("\n",1);

	}
	file6.close();
	return 1;
}
