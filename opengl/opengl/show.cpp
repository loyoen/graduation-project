#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
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
void drawedge(int a,int b,int i)
{
	int h1 = a/200 +1;
	int z1 = a%200;
	int h2 = b/200 +1;
	int z2 = b%200;
	GLfloat  fh1 = (GLfloat )h1 * 0.0066-1.0;
	GLfloat  fz1 = (GLfloat )z1 * 0.010-1.0;
	GLfloat  fh2 = (GLfloat )h2 * 0.0066-1.0;
	GLfloat  fz2 = (GLfloat )z2 * 0.010-1.0;
	
	//glColor3f(0,0,10);
    glVertex2f(fh1, fz1);
	 //glVertex2f(0.5f, 0.5f);
	glVertex2f(fh2, fz2);
	 //glVertex2f(0.0f, 0.0f);


}

HEnode HE[30000];
Vnode V[60000];
section sec[8000];
point poi[60000];
int edgecount =1;
int numv=12127;
int stage=1;
void myDisplay(void)

{

	
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(0.1f);
	//glScalef(10, 10, 1.0);
	
/*
	for(int i=1;HE[i].weight!=-1;i++)
	{
		ArcNodeV *p = HE[i].firstarc;
		ArcNodeV * q = p->nextarc;
		while(q!=NULL)
		{
			drawedge(p->node,q->node,i%8);
			p=q;
			q=q->nextarc;
		}

	}
*/


	glColor3f(255,255,255);
	//glPointSize(10.0f);
	glBegin(GL_POINTS);
	
	for(int i=1;i<=51376;i++)
	{	
		int h1 = i/200 +1;
		int z1 = i%200;
		GLfloat  fh1 = (GLfloat )h1 * 0.0066-1.0;
		GLfloat  fz1 = (GLfloat )z1 * 0.010-1.0;
		glVertex2f(fh1, fz1);

	}

	glEnd();
	
	glFlush();
	glColor3f(255,0,0);

	if(stage==1)
	{
			int i=1;
			ArcNodeH *m = V[numv].firstarc;
			while(m!=NULL)
			{
				if(i>edgecount)
					break;
				if(i==edgecount)
					glColor3f(0,255,0);
				ArcNodeV *p = HE[m->hedge].firstarc;
				ArcNodeV * q = p->nextarc;
				
				while(q!=NULL)
				{
					glBegin(GL_LINES);
					drawedge(p->node,q->node,i);
					glEnd();
					glFlush();
					p=q;
					q=q->nextarc;
				}
				m=m->nextarc;
				i++;
				
			}
	}
	else if(stage==2)
	{
			point *p = poi[numv].next;
			glPointSize(1.5f);
			glColor3f(255,255,0);
			int h = numv/200 +1;
			int z = numv%200;
			GLfloat  fh = (GLfloat )h * 0.0066-1.0;
			GLfloat  fz = (GLfloat )z * 0.010-1.0;
			glBegin(GL_POINTS);
			glVertex2f(fh, fz);
			glEnd();
			glFlush();
			while(p!=NULL)
			{
				int h1 = p->num/200 +1;
				int z1 = p->num%200;
				GLfloat  fh1 = (GLfloat )h1 * 0.0066-1.0;
				GLfloat  fz1 = (GLfloat )z1 * 0.010-1.0;
				glBegin(GL_POINTS);
				glVertex2f(fh1, fz1);
				glEnd();
				glFlush();
				p=p->next;
			}
			glPointSize(0.1f);
	}

	else if(stage==3)
	{
			point *p = poi[numv].next;
			glPointSize(1.5f);
			glColor3f(255,255,0);
			int h = numv/200 +1;
			int z = numv%200;
			GLfloat  fh = (GLfloat )h * 0.0066-1.0;
			GLfloat  fz = (GLfloat )z * 0.010-1.0;
			glBegin(GL_POINTS);
			glVertex2f(fh, fz);
			glEnd();
			glFlush();
			while(p!=NULL)
			{
				int h1 = p->num/200 +1;
				int z1 = p->num%200;
				GLfloat  fh1 = (GLfloat )h1 * 0.0066-1.0;
				GLfloat  fz1 = (GLfloat )z1 * 0.010-1.0;
				glBegin(GL_POINTS);
				glVertex2f(fh1, fz1);
				glEnd();
				glFlush();
				p=p->next;
			}
			glPointSize(0.1f);
	}

}
void dealFile()
{
	
	 ifstream file,file3;
	ofstream file2,file4;
	char temp[1024];
	
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
}

void MousePlot ( int button, int action, int xMouse, int yMouse)
{
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{

	}
	if(button == GLUT_LEFT_BUTTON && action == GLUT_UP)
	{
		edgecount++;
		glutSwapBuffers();
		glutPostRedisplay();
	}
	if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
	{
		stage = 1;
		edgecount=1;
		scanf("%d",&numv);
	}
}

void ProcessSpecialKeyboead(int key, int x, int y) 
{
	if (key == GLUT_KEY_DOWN )
	{
		
		if(stage<4)
		{
			stage++;
			glutSwapBuffers();
			glutPostRedisplay();
		}
	}
	if (key == GLUT_KEY_UP )
	{
	    
		if(stage>1)
		{
			stage--;
			glutSwapBuffers();
			glutPostRedisplay();
		}
	}
}

int main(int argc, char *argv[])

{
	 dealFile();
     glutInit(&argc, argv);

     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

     glutInitWindowPosition(100, 100);

     glutInitWindowSize(400, 400);

     glutCreateWindow("超图");
	 glutInitDisplayMode(GLUT_DOUBLE);
     glutDisplayFunc(&myDisplay);

	 glutMouseFunc(MousePlot);
	 glutSpecialFunc(ProcessSpecialKeyboead);

     glutMainLoop();

     return 0;

}