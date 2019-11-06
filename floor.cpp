#include<iostream>
#include<fstream>
using namespace std;
typedef struct _Node
{
    int row;
    int col;
    bool visited=false;
    int parent[2];//parent[0]=row,parent[1]=col
}Node;

typedef struct _place
{
    int row;
    int col;
}Place;

class my_queue
{
    public:
       my_queue()
       {
           point=NULL;
           point_pop=&(data[0]);
       }
       void push(int row,int col)
       {
            if(point==NULL)
            {
                point=&(data[0]);
                point->row=row;
                point->col=col;
            }
            else
            {
                point++;
                point->row=row;
                point->col=col;
            }
       }
       void pop()
       {
            point_pop++;
       }
       void clear()
       {
           point=NULL;
           point_pop=&(data[0]);
       }
       int empty()
       {
           if(point_pop==point+1)return true;
           else return false;
       }
       int front_row()
       {
           return point_pop->row;
       }
       int front_col()
       {
           return point_pop->col;
       }
       /*void setvisit()
       {
           point->visited=true;
       }*/
       /*void setparent(int lastrow,int lastcol)
       {
           point->parent[0]=lastrow;
           point->parent[1]=lastcol;
       }*/
    private:
        Place data[100000];
        Place* point;
        Place* point_pop;
};

void BFStobattery(int battery_row,int battery_col,char** floor,int map_row,int map_col,Node** node)
{
    my_queue q;
    q.push(battery_row,battery_col);
    //q.setvisit();
    //q.setparent(-1,-1);
    node[battery_row][battery_col].parent[0]=-1;
    node[battery_row][battery_col].parent[1]=-1;
    node[battery_row][battery_col].visited=true;
    while(!q.empty())
    {
        if(q.front_row()-1>=0&&floor[q.front_row()-1][q.front_col()]!='1'&&node[q.front_row()-1][q.front_col()].visited==false)
        {
            q.push(q.front_row()-1,q.front_col());
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            node[q.front_row()-1][q.front_col()].visited=true;
            node[q.front_row()-1][q.front_col()].parent[0]=q.front_row();
            node[q.front_row()-1][q.front_col()].parent[1]=q.front_col();
        }
        if(q.front_row()+1<map_row&&floor[q.front_row()+1][q.front_col()]!='1'&&node[q.front_row()+1][q.front_col()].visited==false)
        {
            q.push(q.front_row()+1,q.front_col());
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            node[q.front_row()+1][q.front_col()].visited=true;
            node[q.front_row()+1][q.front_col()].parent[0]=q.front_row();
            node[q.front_row()+1][q.front_col()].parent[1]=q.front_col();
        }
        if(q.front_col()-1>=0&&floor[q.front_row()][q.front_col()-1]!='1'&&node[q.front_row()][q.front_col()-1].visited==false)
        {
            q.push(q.front_row(),q.front_col()-1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            node[q.front_row()][q.front_col()-1].visited=true;
            node[q.front_row()][q.front_col()-1].parent[0]=q.front_row();
            node[q.front_row()][q.front_col()-1].parent[1]=q.front_col();
        }
        if(q.front_col()+1<map_col&&floor[q.front_row()][q.front_col()+1]!='1'&&node[q.front_row()][q.front_col()+1].visited==false)
        {
            q.push(q.front_row(),q.front_col()+1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            node[q.front_row()][q.front_col()+1].visited=true;
            node[q.front_row()][q.front_col()+1].parent[0]=q.front_row();
            node[q.front_row()][q.front_col()+1].parent[1]=q.front_col();
        }
        q.pop();
    }
}

void printBFSpath(int finish_row,int finish_col,Node** node)
{
    while(node[finish_row][finish_col].parent[0]!=-1)
    {
        int last_row,last_col;
        last_row=node[finish_row][finish_col].parent[0];
        last_col=node[finish_row][finish_col].parent[1];
        cout<<last_row<<" "<<last_col<<endl;
        finish_row=last_row;
        finish_col=last_col;
    }
}

void DFSfrombattery(int map_row,int map_col,int start_row,int start_col,char**floor,Node**DFS_node,Node**BFS_node)
{
    static int counting=1;
    cout<<start_row<<" "<<start_col<<endl;
    DFS_node[start_row][start_col].visited=true;
    if(start_row-1>=0&&floor[start_row-1][start_col]!='1'&&DFS_node[start_row-1][start_col].visited==false)
    {
        DFSfrombattery(map_row,map_col,start_row-1,start_col,floor,DFS_node,BFS_node);
    }
    if(start_row+1<map_row&&floor[start_row+1][start_col]!='1'&&DFS_node[start_row+1][start_col].visited==false)
    {
        DFSfrombattery(map_row,map_col,start_row+1,start_col,floor,DFS_node,BFS_node);
    }
    if(start_col-1>=0&&floor[start_row][start_col-1]!='1'&&DFS_node[start_row][start_col-1].visited==false)
    {
        DFSfrombattery(map_row,map_col,start_row,start_col-1,floor,DFS_node,BFS_node);
    }
    if(start_col+1<map_col&&floor[start_row][start_col+1]!='1'&&DFS_node[start_row][start_col+1].visited==false)
    {
        DFSfrombattery(map_row,map_col,start_row,start_col+1,floor,DFS_node,BFS_node);
    }
    if(counting)
    {
        printBFSpath(start_row,start_col,BFS_node);
        counting--;
    }
}

int main()
{
    int map_row;
    int map_col;
    int battery;

    int battery_row,battery_col;
    //ifstream fin("floor.data");
    //ofstream fout("final.path");
    cin>>map_row>>map_col>>battery;
    char floor[map_row][map_col+1];
    char* arr[map_row];
    for(int i=0;i<map_row;i++)
    {
        arr[i]=floor[i];
        arr[i][map_col]='\0';
        for(int j=0;j<map_col;j++)
        {
            char c=getchar();
            if(c=='\n')c=getchar();
            arr[i][j]=c;
            if(arr[i][j]=='R')
            {
                battery_row=i;
                battery_col=j;
            }
        }
    }
    Node BFS_node[map_row][map_col];
    Node* BFS_arr_node[map_row];
    for(int i=0;i<map_row;i++)
    {
        BFS_arr_node[i]=BFS_node[i];
    }
    Node DFS_node[map_row][map_col];
    Node* DFS_arr_node[map_row];
    for(int i=0;i<map_row;i++)
    {
        DFS_arr_node[i]=DFS_node[i];
    }
    BFStobattery(battery_row,battery_col,arr,map_row,map_col,BFS_arr_node);
    DFSfrombattery(map_row,map_col,battery_row,battery_col,arr,DFS_arr_node,BFS_arr_node);
}
