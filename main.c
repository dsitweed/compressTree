#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "jrb.h"
#include "dllist.h"
#include "un_directed_graph.h"
#define max 100000//Max of vertex

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2);
void add_2_Edge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);

int degree(Graph graph, int v, int* output);
void dropGraph(Graph graph);
void deleteNei(Graph graph,int v1,int v2);
void nenCay(Graph graph,int *output,int *length);

int main(int argc,char *argv[])
{
  Graph graph = createGraph();
  int n,v1,v2;
  int output[max],menu;
  FILE * file;
  printf("Phuong thuc nhap lieu?\n");
  printf("1. Doc tu file (Mac dinh data.txt)\n");
  printf("2. Doc tu ban phim\n");
  printf("YOUR CHOICE:");
  scanf("%d%*c",&menu);
  switch (menu)
    {
    case 1:
      file = fopen("data.txt","r");
      if (file == NULL)
	{
	  printf("ERROR INPUT\n");return 0;
	}
      fscanf(file,"%d%*c",&n);
      for (int i = 0;i < n;i++)
	{
	  fscanf(file,"%d %d%*c",&v1,&v2);
	  addVertex(graph,v1,"OK");
	  addVertex(graph,v2,"OK");
	  add_2_Edge(graph,v1,v2);
	}
      break;
    case 2:
      printf("Nhap tong so canh cua cay:");
      scanf("%d%*c",&n);
      for (int i = 0;i < n;i++)
	{
	  scanf("%d %d%*c",&v1,&v2);
	  addVertex(graph,v1,"OK");
	  addVertex(graph,v2,"OK");
	  add_2_Edge(graph,v1,v2);
	}
      break;
    }
  nenCay(graph,output,&n);
  for (int i = 0;i < n;i++)
    {
      printf("%-6d",output[i]);
    }
  printf("\n");
}//end main

void nenCay(Graph graph,int *output,int *length)
{
  int n,bac[max],tmp[max],v,u;
  JRB node;
  JRB priorityQueue = make_jrb();
  n = 0;
  jrb_traverse(node,graph.vertices)
    {
      v = jval_i(node->key);
      bac[v] = degree(graph,v,tmp);
      if (bac[v] == 1)
	jrb_insert_int(priorityQueue,v,new_jval_i(1));
      n++;
    }
  jrb_traverse(node,priorityQueue);
  for (int i = 0;i < n - 2;i++)
    {
      node = jrb_first(priorityQueue);
      v = jval_i(node->key);
      jrb_delete_node(node);
      degree(graph,v,tmp);
      u = tmp[0];
      output[i] = u;
      deleteNei(graph,u,v);
      // printf("%d\n",u);
      bac[u]--;
      if (bac[u] == 1)
	jrb_insert_int(priorityQueue,u,new_jval_i(1));
    }
  *length = n - 2;
}

void deleteNei(Graph graph,int v1,int v2)
{
  JRB node,tree;
  node = jrb_find_int(graph.edges,v1);
  tree = (JRB) jval_v(node->val);
  node = jrb_find_int(tree,v2);
  jrb_delete_node(node);
}
