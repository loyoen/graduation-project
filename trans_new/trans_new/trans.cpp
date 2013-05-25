#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <time.h>

using namespace std;


struct vertex
{
	int value;   //顶点编号
	vertex *next;  //解决哈希冲突链表
	char title[1024];
	char url[1024];
	char content[1024];
};

int main()
{
	vertex *point[100000],*out[100000];
	for(int i=0;i<100000;i++)
	{
		point[i]=(vertex *)malloc(sizeof(vertex));
		point[i]->value=-1;
		point[i]->next=NULL;
	}
	int count = 0;  //统计顶点数
	int edgecount = 0; //统计边数
	ifstream file;
	ofstream file2,file3;
	char temp[1024];
	char strtemp[3][1024];
	file.open("C://Users//Zenas//Desktop//loyoen//file//test.txt");
	file2.open("C://Users//Zenas//Desktop//loyoen//file//testfile2.txt");
	file3.open("C://Users//Zenas//Desktop//loyoen//file//testfile3.txt");
	if(file != NULL)
	{
		while(!file.eof())
		{
		
			file.getline(temp,1024);
			int num = atoi(temp);
			if(num==0)
				int a =1;
			if(count==77365)
				int c=1;
			if(num!=0)
				edgecount++;
			if(count==76176)
				int b=1;
			char weight[10],key[50];
			file.getline(weight,10);
			int weig=atoi(weight);
			file.getline(key,50);
			weig += 2*strlen(key);
			sprintf_s(weight,10,"%d",weig);
			if(num!=0)
			{
				file2.write(weight,strlen(weight));
				file2.write(" ",1);
				//file2.write("88 ",3);
			}
			else
				continue;
			for(int i=0;i<num;i++)
			{
				
				int n=0;
				char te[1024];
				for(int j=0;j<3;j++)
				{
					file.getline(te,1024);
					while(strlen(te)<=1)
						file.getline(te,1024);
					strcpy(strtemp[j],te);
				}
				for(int k=0;k<strlen(strtemp[2]);k++)
					n = n + strtemp[2][k];
				n = abs(n)%10000;
			
				
				if(point[n]->value==-1)
				{
		
					count++;
					point[n]->value=count;
			
					strcpy(point[n]->title,strtemp[0]);
			
					strcpy(point[n]->content,strtemp[1]);
				
					strcpy(point[n]->url,strtemp[2]);

	


					char tempvalue[10];
					sprintf_s(tempvalue, 10, "%d", point[n]->value);
					file2.write(tempvalue,strlen(tempvalue));
					if(i!=num-1)
						file2.write(" ",1);

					
				}
				else  //头插法插入p   不知空间会不会被释放
				{
					vertex *q=point[n];
					bool belong =false;
				
					while(q!=NULL)
					{
						if(strcmp(q->url,strtemp[2])==0)
						{
							belong =true;
							char tempvalue[10];
							sprintf_s(tempvalue, 10, "%d", q->value);
							file2.write(tempvalue,strlen(tempvalue));
							if(i!=num-1)
								file2.write(" ",1);
							break;
						}
						else
							q=q->next;
					}
					if(belong==false)
					{
						count++;
						vertex *p = (vertex *)malloc(sizeof(vertex));
						p->next=point[n]->next;
						p->value=count;
						strcpy(p->title,strtemp[0]);
						strcpy(p->content,strtemp[1]);
						strcpy(p->url,strtemp[2]);
						point[n]->next=p;
						char tempvalue[10];
						sprintf_s(tempvalue, 10, "%d", p->value);
						file2.write(tempvalue,strlen(tempvalue));
						if(i!=num-1)
							file2.write(" ",1);
					}
				}   //end else
				
			}  //end for
			file2.write("\n",1);
		}
	}
	char ecount[10];
	char vcount[10];
	sprintf_s(ecount, 10, "%d", edgecount);
	sprintf_s(vcount, 10, "%d", count);
	file2.write("\n",1);
	file2.write(ecount,strlen(ecount));
	file2.write(" ",1);
	file2.write(vcount,strlen(vcount));
	file2.write(" ",1);
	file2.write("1",1);
	
	for(int i=0;i<10000;i++)
	{
		if(point[i]->value==-1)
			continue;
		else
		{
			vertex *m = point[i];
			while(m!=NULL)
			{
				if(edgecount==11974)
					printf("%d",m->value);
				out[m->value]=m;

				m=m->next;
			}
		}
	}
	char val[10];
	for(int i=1;i<=count;i++)
	{
		sprintf_s(val, 10, "%d", i);
		file3.write(val,strlen(val));
		file3.write("\n",1);
		char tem[1024];
		strcpy(tem,out[i]->title);
		file3.write(out[i]->title,strlen(out[i]->title));
		file3.write("\n",1);
		file3.write(out[i]->content,strlen(out[i]->content));
		file3.write("\n",1);
		file3.write(out[i]->url,strlen(out[i]->url));
		file3.write("\n",1);

	}
	file.close();
	file2.close();
	file3.close();
	return 1;
}