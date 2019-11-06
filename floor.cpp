#include<iostream>
#include<fstream>
using namespace std;

int battery_row,battery_col;
int step=0;

typedef struct _Node
{
    int row;
    int col;
    bool visited=false;
    int dis=-1;
    int parent[2];//parent[0]=row,parent[1]=col
} Node;

typedef struct _place
{
    int row;
    int col;
} Place;

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
        if(point_pop==point+1)
            return true;
        else
            return false;
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

void BFStobattery(char** floor,int map_row,int map_col,Node** node)
{
    my_queue q;
    q.push(battery_row,battery_col);
    //q.setvisit();
    //q.setparent(-1,-1);
    node[battery_row][battery_col].parent[0]=-1;
    node[battery_row][battery_col].parent[1]=-1;
    node[battery_row][battery_col].visited=true;
    node[battery_row][battery_col].dis=0;
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
            node[q.front_row()-1][q.front_col()].dis=node[q.front_row()][q.front_col()].dis+1;
        }
        if(q.front_row()+1<map_row&&floor[q.front_row()+1][q.front_col()]!='1'&&node[q.front_row()+1][q.front_col()].visited==false)
        {
            q.push(q.front_row()+1,q.front_col());
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            node[q.front_row()+1][q.front_col()].visited=true;
            node[q.front_row()+1][q.front_col()].parent[0]=q.front_row();
            node[q.front_row()+1][q.front_col()].parent[1]=q.front_col();
            node[q.front_row()+1][q.front_col()].dis=node[q.front_row()][q.front_col()].dis+1;
        }
        if(q.front_col()-1>=0&&floor[q.front_row()][q.front_col()-1]!='1'&&node[q.front_row()][q.front_col()-1].visited==false)
        {
            q.push(q.front_row(),q.front_col()-1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            node[q.front_row()][q.front_col()-1].visited=true;
            node[q.front_row()][q.front_col()-1].parent[0]=q.front_row();
            node[q.front_row()][q.front_col()-1].parent[1]=q.front_col();
            node[q.front_row()][q.front_col()-1].dis=node[q.front_row()][q.front_col()].dis+1;
        }
        if(q.front_col()+1<map_col&&floor[q.front_row()][q.front_col()+1]!='1'&&node[q.front_row()][q.front_col()+1].visited==false)
        {
            q.push(q.front_row(),q.front_col()+1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            node[q.front_row()][q.front_col()+1].visited=true;
            node[q.front_row()][q.front_col()+1].parent[0]=q.front_row();
            node[q.front_row()][q.front_col()+1].parent[1]=q.front_col();
            node[q.front_row()][q.front_col()+1].dis=node[q.front_row()][q.front_col()].dis+1;
        }
        q.pop();
    }
}

void printBFSpath(int finish_row,int finish_col,Node** node)
{
    if(node[finish_row][finish_col].parent[0]!=-1)
    {
        printBFSpath(node[finish_row][finish_col].parent[0],node[finish_row][finish_col].parent[1],node);
    }
    cout<<finish_row<<" "<<finish_col<<endl;
    step++;
}

void printBFSbackpath(int finish_row,int finish_col,Node** node,char**check)
{
    while(node[finish_row][finish_col].parent[0]!=-1)
    {
        check[finish_row][finish_col]='1';
        int last_row,last_col;
        last_row=node[finish_row][finish_col].parent[0];
        last_col=node[finish_row][finish_col].parent[1];
        cout<<last_row<<" "<<last_col<<endl;
        finish_row=last_row;
        finish_col=last_col;
        step++;
    }
}

bool checkisover(char**check,int map_row,int map_col)
{
    for(int i=0; i<map_row; i++)
    {
        for(int j=0; j<map_col; j++)
        {
            if(check[i][j]=='0')
                return false;
        }
    }
    return true;
}

void findthefarest(char**check,int*farest_row,int*farest_col,int map_row,int map_col,Node**node)
{
    int cur_dis=0;
    for(int i=0; i<map_row; i++)
    {
        for(int j=0; j<map_col; j++)
        {
            if(check[i][j]=='0')
            {
                if(node[i][j].dis>cur_dis)
                {
                    cur_dis=node[i][j].dis;
                    *farest_row=i;
                    *farest_col=j;
                }
            }
        }
    }
}


int main()
{
    int map_row;
    int map_col;
    int battery;

    //ifstream fin("floor.data");
    //ofstream fout("final.path");
    cin>>map_row>>map_col>>battery;
    char floor[map_row][map_col+1];
    char* arr[map_row];
    for(int i=0; i<map_row; i++)
    {
        arr[i]=floor[i];
        arr[i][map_col]='\0';
        for(int j=0; j<map_col; j++)
        {
            char c=getchar();
            if(c=='\n')
                c=getchar();
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
    for(int i=0; i<map_row; i++)
    {
        BFS_arr_node[i]=BFS_node[i];
    }
    Node DFS_node[map_row][map_col];
    Node* DFS_arr_node[map_row];
    for(int i=0; i<map_row; i++)
    {
        DFS_arr_node[i]=DFS_node[i];
    }

    char check[map_row][map_col+1];
    for(int i=0; i<map_row; i++)
    {
        check[i][map_col]='\0';
        for(int j=0; j<map_col; j++)
        {
            check[i][j]=floor[i][j];
        }
    }
    char* checkarr[map_row];
    for(int i=0; i<map_row; i++)
    {
        checkarr[i]=check[i];
    }
    BFStobattery(arr,map_row,map_col,BFS_arr_node);

    int farest_row,farest_col;
    while(!checkisover(checkarr,map_row,map_col))
    {
        findthefarest(checkarr,&farest_row,&farest_col,map_row,map_col,BFS_arr_node);
        printBFSpath(farest_row,farest_col,BFS_arr_node);
        printBFSbackpath(farest_row,farest_col,BFS_arr_node,checkarr);
    }

    cout<<step-1<<endl;
    //printBFSpath(1,3,BFS_arr_node);
    //printBFSbackpath(1,3,BFS_arr_node);

}
