//
//  main.cpp
//  BFS
//
//  Created by 杜明泽 on 20/3/28.
//  Copyright © 2020年 dumingze. All rights reserved.
//

#include <iostream>


#define MAX 10
#define INFINITY 88888
#define TRUE 1
#define FALSE 0

typedef int VertexType;
typedef int EdgeType;
typedef int ElemType;    //链队列的数据类型
bool visited[MAX];


/*邻接矩阵结构*/
typedef struct
{
    VertexType vexs[MAX];   //顶点表
    EdgeType arc[MAX][MAX];//邻接矩阵可看作边表
    int numVertexes,numEdges;   //顶点数和边数
}MGraph;

/*队列结构*/
typedef struct Linknode{
    ElemType data;
    struct Linknode *next;
}Linknode;

typedef struct
{
    Linknode *front,*rear;  //队头队尾指针
}LinkQueue;


//构造邻接矩阵
void create(MGraph *G)
{
    int i,j,k,w;
    printf("请输入顶点数和边数:\n");
    scanf("%d%d",&(G->numVertexes),&(G->numEdges));
    for(i=0;i<G->numVertexes;i++)     //建立顶点表
    {
        printf("\n第%d个顶点",i);
        scanf("%d",&(G->vexs[i]));
        getchar();
    }
    
    for(i=0;i<G->numVertexes;i++)   //矩阵初始化
        for(j=0;j<G->numVertexes;j++)
            G->arc[i][j]=INFINITY;
    
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边（Vi,Vj）的上下标i,j和权w(空格隔开)：");
        scanf("%d%d%d",&i,&j,&w);
        G->arc[i][j]=w;
        G->arc[j][i]=G->arc[i][j];
    }
}

//输出邻接矩阵
void Output(MGraph *G)
{
    int i,j,count=0;
    
    for(i=0;i<G->numVertexes;i++){
        
        printf("%d \n",G->vexs[i]);}
   
     printf("邻接矩阵如下：\n");
    
    for(i=0;i<G->numVertexes;i++)
    {
        printf("%4c",G->vexs[i]);
        for(j=0;j<G->numVertexes;j++)
        {
            
            printf("\t%d",G->arc[i][j]);
            count++;
            if(count%G->numVertexes==0)
                printf("\n");
        }
    }
}


//创建空队列
void InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=(Linknode*)malloc(sizeof(Linknode));
    Q.front->next=NULL;
}

//入队列
//将s作为新元素加入队尾
void EnQueue(LinkQueue &Q,ElemType x)
{
   Linknode *s=(Linknode*)malloc(sizeof(Linknode));
    s->data=x;
    s->next=NULL;
    Q.rear->next=s;
    
    Q.rear=s;
}

//检验是否为空
bool IsEmpty(LinkQueue Q)
{
    if(Q.front==Q.rear) return true;
    else return false;
}

//出队列
bool DeQueue(LinkQueue &Q,ElemType &x)
{
   if(Q.front==Q.rear) return false;//空队列
    Linknode *p=Q.front->next;
    x=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    free(p);
    return true;
}



/*广度遍历*/
LinkQueue Q;

void BFS(MGraph G,int i){
    int j;
    visited[i]=TRUE;
    printf("%d->",G.vexs[i]);
    EnQueue(Q,i);      //将其入队列
    while(!IsEmpty(Q))
    {
        DeQueue(Q,i);    //将队中元素出队列，赋值给i
        for(j=0;j<G.numVertexes;j++)
        {
            if(G.arc[i][j]==1&&!visited[j])    //其他顶点与该顶点存在边且未访问过
            {
                visited[j]=TRUE;
                printf("%d－>",G.vexs[j]);
                EnQueue(Q,j);                 //入队列
            }
            
        }
    }
}

void BFSTraverse(MGraph G)
{
    int i;
    
    for(i=0;i<G.numVertexes;i++)
        visited[i]=FALSE;
    InitQueue(Q);          //初始化队列
    for(i=0;i<G.numVertexes;i++)
    {
        if(!visited[i])    //未访问过该顶点
        {
            BFS(G,i);
        }
    }
}



int main()
{
    MGraph G;
    create(&G);
    printf("邻接矩阵顶点数组如下：\n");
    Output(&G);
    BFSTraverse(G);
    printf("\n图遍历完毕");
    return 0;	 
    
}