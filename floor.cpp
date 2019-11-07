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

void printBFSpath(int finish_row,int finish_col,Node** node,char**check)
{
    if(node[finish_row][finish_col].parent[0]!=-1)
    {
        printBFSpath(node[finish_row][finish_col].parent[0],node[finish_row][finish_col].parent[1],node,check);
    }
    cout<<finish_row<<" "<<finish_col<<endl;
    check[finish_row][finish_col]='1';
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

void findthenearest(char**check,int*nearest_row,int*nearest_col,int map_row,int map_col,Node**node)
{
    int cur_dis=10000;
    for(int i=0; i<map_row; i++)
    {
        for(int j=0; j<map_col; j++)
        {
            if(check[i][j]=='0')
            {
                if(node[i][j].dis<cur_dis)
                {
                    cur_dis=node[i][j].dis;
                    *nearest_row=i;
                    *nearest_col=j;
                }
            }
        }
    }
}

void DFS(char**check,char**floor,int row,int col,int map_row,int map_col,int* end_row,int* end_col,int battery,Node**node)
{
    int current_move=0;
    while(1)
    {
        if(floor[row-1][col]=='0'&&check[row-1][col]=='0'&&row-1>=0)
        {
            cout<<row-1<<" "<<col<<endl;
            check[row-1][col]='1';
            row=row-1;
            step++;
            current_move++;
            if(current_move+node[row][col].dis==battery)break;
            continue;
        }
        else if(floor[row+1][col]=='0'&&check[row+1][col]=='0'&&row+1<map_row)
        {
            cout<<row+1<<" "<<col<<endl;
            check[row+1][col]='1';
            row=row+1;
            step++;
            current_move++;
            if(current_move+node[row][col].dis==battery)break;
            continue;
        }
        else if(floor[row][col-1]=='0'&&check[row][col-1]=='0'&&col-1>=0)
        {
            cout<<row<<" "<<col-1<<endl;
            check[row][col-1]='1';
            col=col-1;
            step++;
            current_move++;
            if(current_move+node[row][col].dis==battery)break;
            continue;
        }
        else if(floor[row][col+1]=='0'&&check[row][col+1]=='0'&&col+1<map_col)
        {
            cout<<row<<" "<<col+1<<endl;
            check[row][col+1]='1';
            col=col+1;
            step++;
            current_move++;
            if(current_move+node[row][col].dis==battery)break;
            continue;
        }
        else
        {
            step++;
            current_move++;
            check[row][col]='1';
            *end_row=row;
            *end_col=col;
            break;
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
    char floor[map_row][map_col];
    char* arr[map_row];
    for(int i=0;i<map_row;i++)
    {
        for(int j=0;j<map_col;j++)
        {
            char c=getchar();
            if(c=='\n')
                c=getchar();
            floor[i][j]=c;
            if(floor[i][j]=='R')
            {
                battery_row=i;
                battery_col=j;
            }
        }
    }
    for(int i=0;i<map_row;i++)
    {
        arr[i]=floor[i];
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

    int nearest_row,nearest_col;
    int end_row,end_col;
    while(!checkisover(checkarr,map_row,map_col))
    {
        findthenearest(checkarr,&nearest_row,&nearest_col,map_row,map_col,BFS_arr_node);
        cout<<"the nearrow is"<<nearest_row<<"the nearest col is"<<nearest_col<<endl;
        printBFSpath(nearest_row,nearest_col,BFS_arr_node,checkarr);
        DFS(checkarr,arr,nearest_row,nearest_col,map_row,map_col,&end_row,&end_col,battery,BFS_arr_node);
        printBFSbackpath(end_row,end_col,BFS_arr_node,checkarr);
    }

    cout<<step-3<<endl;
    //printBFSpath(1,3,BFS_arr_node);
    //printBFSbackpath(1,3,BFS_arr_node);

}
