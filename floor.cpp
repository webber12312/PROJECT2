#include<iostream>
#include<fstream>
using namespace std;



int battery_row,battery_col;
int step=0;
int cur_used_battery=0;
bool pass_battery=false;
FILE*fp=tmpfile();

typedef struct _Node
{
    int row;
    int col;
    bool visited=false;
    int dis=-1;
    int parent[2];//parent[0]=row,parent[1]=col
} Node;


Node BFS_node[1000][1000];
Node DFS_node[1000][1000];

class Place
{
public:
    int row;
    int col;
    Place* next;
    Place(int x,int y):row(x),col(y),next(NULL) {}
};

class my_queue
{
public:
    my_queue()
    {
        my_front=NULL;
        my_back=NULL;
    }
    void push(int row,int col)
    {
        if(isempty())
        {
            my_front=new Place(row,col);
            my_back=my_front;
        }
        else
        {
            Place*node=new Place(row,col);
            my_back->next=node;
            my_back=node;

        }
    }
    void pop()
    {
        Place*node=my_front;
        my_front=my_front->next;
        delete node;
    }
    int isempty()
    {
        if(my_front==NULL||my_back==NULL)
            return true;
        else
            return false;
    }
    int front_row()
    {
        return my_front->row;
    }
    int front_col()
    {
        return my_front->col;
    }
private:
    Place* my_front;
    Place* my_back;
};

void BFStobattery(char** floor,int map_row,int map_col)
{
    my_queue q;
    q.push(battery_row,battery_col);
    BFS_node[battery_row][battery_col].parent[0]=-1;
    BFS_node[battery_row][battery_col].parent[1]=-1;
    BFS_node[battery_row][battery_col].visited=true;
    BFS_node[battery_row][battery_col].dis=0;
    while(!q.isempty())
    {
        if(q.front_row()-1>=0&&floor[q.front_row()-1][q.front_col()]!='1'&&BFS_node[q.front_row()-1][q.front_col()].visited==false)
        {
            q.push(q.front_row()-1,q.front_col());
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            BFS_node[q.front_row()-1][q.front_col()].visited=true;
            BFS_node[q.front_row()-1][q.front_col()].parent[0]=q.front_row();
            BFS_node[q.front_row()-1][q.front_col()].parent[1]=q.front_col();
            BFS_node[q.front_row()-1][q.front_col()].dis=BFS_node[q.front_row()][q.front_col()].dis+1;
        }
        if(q.front_row()+1<map_row&&floor[q.front_row()+1][q.front_col()]!='1'&&BFS_node[q.front_row()+1][q.front_col()].visited==false)
        {
            q.push(q.front_row()+1,q.front_col());
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            BFS_node[q.front_row()+1][q.front_col()].visited=true;
            BFS_node[q.front_row()+1][q.front_col()].parent[0]=q.front_row();
            BFS_node[q.front_row()+1][q.front_col()].parent[1]=q.front_col();
            BFS_node[q.front_row()+1][q.front_col()].dis=BFS_node[q.front_row()][q.front_col()].dis+1;
        }
        if(q.front_col()-1>=0&&floor[q.front_row()][q.front_col()-1]!='1'&&BFS_node[q.front_row()][q.front_col()-1].visited==false)
        {
            q.push(q.front_row(),q.front_col()-1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            BFS_node[q.front_row()][q.front_col()-1].visited=true;
            BFS_node[q.front_row()][q.front_col()-1].parent[0]=q.front_row();
            BFS_node[q.front_row()][q.front_col()-1].parent[1]=q.front_col();
            BFS_node[q.front_row()][q.front_col()-1].dis=BFS_node[q.front_row()][q.front_col()].dis+1;
        }
        if(q.front_col()+1<map_col&&floor[q.front_row()][q.front_col()+1]!='1'&&BFS_node[q.front_row()][q.front_col()+1].visited==false)
        {
            q.push(q.front_row(),q.front_col()+1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            BFS_node[q.front_row()][q.front_col()+1].visited=true;
            BFS_node[q.front_row()][q.front_col()+1].parent[0]=q.front_row();
            BFS_node[q.front_row()][q.front_col()+1].parent[1]=q.front_col();
            BFS_node[q.front_row()][q.front_col()+1].dis=BFS_node[q.front_row()][q.front_col()].dis+1;
        }
        q.pop();
    }
}

void printBFSpath(int finish_row,int finish_col,char**check)
{
    if(BFS_node[finish_row][finish_col].parent[0]!=-1)
    {
        printBFSpath(BFS_node[finish_row][finish_col].parent[0],BFS_node[finish_row][finish_col].parent[1],check);
    }
    //cout<<finish_row<<" "<<finish_col<<endl;
    fprintf(fp,"%d %d\n",finish_row,finish_col);
    check[finish_row][finish_col]='1';
    step++;
    cur_used_battery++;
}

void printBFSpath2(int finish_row,int finish_col,char**check)
{
    if(DFS_node[finish_row][finish_col].parent[0]!=-1)
    {
        printBFSpath2(DFS_node[finish_row][finish_col].parent[0],DFS_node[finish_row][finish_col].parent[1],check);
    }
    if(DFS_node[finish_row][finish_col].parent[0]!=-1)
    {
        //cout<<finish_row<<" "<<finish_col<<endl;
        fprintf(fp,"%d %d\n",finish_row,finish_col);
        check[finish_row][finish_col]='1';
        step++;
        cur_used_battery++;
    }
}

void printBFSbackpath(int finish_row,int finish_col,char**check)
{
    while(BFS_node[finish_row][finish_col].parent[0]!=-1)
    {
        check[finish_row][finish_col]='1';
        int last_row,last_col;
        last_row=BFS_node[finish_row][finish_col].parent[0];
        last_col=BFS_node[finish_row][finish_col].parent[1];
        if(BFS_node[last_row][last_col].parent[0]!=-1)
            //cout<<last_row<<" "<<last_col<<endl;
            fprintf(fp,"%d %d\n",last_row,last_col);
        finish_row=last_row;
        finish_col=last_col;
        step++;
        cur_used_battery++;
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

int findthenearest_BFS(char**check,int*nearest_row,int*nearest_col,int map_row,int map_col)
{
    int cur_dis=1000000;
    for(int i=0; i<map_row; i++)
    {
        for(int j=0; j<map_col; j++)
        {
            if(check[i][j]=='0')
            {
                if(BFS_node[i][j].dis<cur_dis)
                {
                    cur_dis=BFS_node[i][j].dis;
                    *nearest_row=i;
                    *nearest_col=j;
                }
            }
        }
    }
    return cur_dis;
}


int BFStonearest(char** floor,char**check,int map_row,int map_col,int cur_row,int cur_col,int* nearest_row,int* nearest_col)
{
    my_queue q;
    q.push(cur_row,cur_col);
    DFS_node[cur_row][cur_col].parent[0]=-1;
    DFS_node[cur_row][cur_col].parent[1]=-1;
    DFS_node[cur_row][cur_col].visited=true;
    DFS_node[cur_row][cur_col].dis=0;
    int dis;
    while(!q.isempty())
    {
        if(q.front_row()-1>=0&&floor[q.front_row()-1][q.front_col()]!='1'&&DFS_node[q.front_row()-1][q.front_col()].visited==false)
        {
            q.push(q.front_row()-1,q.front_col());
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            DFS_node[q.front_row()-1][q.front_col()].visited=true;
            DFS_node[q.front_row()-1][q.front_col()].parent[0]=q.front_row();
            DFS_node[q.front_row()-1][q.front_col()].parent[1]=q.front_col();
            DFS_node[q.front_row()-1][q.front_col()].dis=DFS_node[q.front_row()][q.front_col()].dis+1;
            if(check[q.front_row()-1][q.front_col()]!='1')
            {
                *nearest_row=q.front_row()-1;
                *nearest_col=q.front_col();
                dis=DFS_node[q.front_row()-1][q.front_col()].dis;
                break;
            }
        }
        if(q.front_row()+1<map_row&&floor[q.front_row()+1][q.front_col()]!='1'&&DFS_node[q.front_row()+1][q.front_col()].visited==false)
        {
            q.push(q.front_row()+1,q.front_col());
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            DFS_node[q.front_row()+1][q.front_col()].visited=true;
            DFS_node[q.front_row()+1][q.front_col()].parent[0]=q.front_row();
            DFS_node[q.front_row()+1][q.front_col()].parent[1]=q.front_col();
            DFS_node[q.front_row()+1][q.front_col()].dis=DFS_node[q.front_row()][q.front_col()].dis+1;
            if(check[q.front_row()+1][q.front_col()]!='1')
            {
                *nearest_row=q.front_row()+1;
                *nearest_col=q.front_col();
                dis=DFS_node[q.front_row()+1][q.front_col()].dis;
                break;
            }
        }
        if(q.front_col()-1>=0&&floor[q.front_row()][q.front_col()-1]!='1'&&DFS_node[q.front_row()][q.front_col()-1].visited==false)
        {
            q.push(q.front_row(),q.front_col()-1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            DFS_node[q.front_row()][q.front_col()-1].visited=true;
            DFS_node[q.front_row()][q.front_col()-1].parent[0]=q.front_row();
            DFS_node[q.front_row()][q.front_col()-1].parent[1]=q.front_col();
            DFS_node[q.front_row()][q.front_col()-1].dis=DFS_node[q.front_row()][q.front_col()].dis+1;
            if(check[q.front_row()][q.front_col()-1]!='1')
            {
                *nearest_row=q.front_row();
                *nearest_col=q.front_col()-1;
                dis=DFS_node[q.front_row()][q.front_col()-1].dis;
                break;
            }
        }
        if(q.front_col()+1<map_col&&floor[q.front_row()][q.front_col()+1]!='1'&&DFS_node[q.front_row()][q.front_col()+1].visited==false)
        {
            q.push(q.front_row(),q.front_col()+1);
            //q.setvisit();
            //q.setparent(q.front_row(),q.front_col());
            DFS_node[q.front_row()][q.front_col()+1].visited=true;
            DFS_node[q.front_row()][q.front_col()+1].parent[0]=q.front_row();
            DFS_node[q.front_row()][q.front_col()+1].parent[1]=q.front_col();
            DFS_node[q.front_row()][q.front_col()+1].dis=DFS_node[q.front_row()][q.front_col()].dis+1;
            if(check[q.front_row()][q.front_col()+1]!='1')
            {
                *nearest_row=q.front_row();
                *nearest_col=q.front_col()+1;
                dis=DFS_node[q.front_row()][q.front_col()+1].dis;
                break;
            }
        }
        q.pop();
    }
    for(int i=0; i<map_row; i++)
    {
        for(int j=0; j<map_col; j++)
        {
            DFS_node[i][j].visited=false;
        }
    }
    return dis;
}


void ispassbattery(int finish_row,int finish_col,char**check)
{
    if(DFS_node[finish_row][finish_col].parent[0]!=-1)
    {
        ispassbattery(DFS_node[finish_row][finish_col].parent[0],DFS_node[finish_row][finish_col].parent[1],check);
    }
    if(finish_row+1==battery_row&&finish_col==battery_col)pass_battery=true;
    else if(finish_row-1==battery_row&&finish_col==battery_col)pass_battery=true;
    else if(finish_row==battery_row&&finish_col+1==battery_col)pass_battery=true;
    else if(finish_row==battery_row&&finish_col-1==battery_col)pass_battery=true;
}


void DFS(char**check,char**floor,int row,int col,int map_row,int map_col,int* end_row,int* end_col,int battery)
{
    //Node* DFS_arr_node[map_row];
    /*for(int i=0; i<map_row; i++)
    {
        DFS_arr_node[i]=DFS_node[i];
    }*/
    while(1)
    {
        if(floor[row-1][col]=='0'&&check[row-1][col]=='0'&&row-1>=0)
        {
            if(cur_used_battery+BFS_node[row-1][col].dis+1>battery)
            {
                *end_row=row;
                *end_col=col;
                break;
            }
            //cout<<row-1<<" "<<col<<endl;
            fprintf(fp,"%d %d\n",row-1,col);
            check[row-1][col]='1';
            row=row-1;
            step++;
            cur_used_battery++;
            continue;
        }
        else if(floor[row+1][col]=='0'&&check[row+1][col]=='0'&&row+1<map_row)
        {
            if(cur_used_battery+BFS_node[row+1][col].dis+1>battery)
            {
                *end_row=row;
                *end_col=col;
                break;
            }
            //cout<<row+1<<" "<<col<<endl;
            fprintf(fp,"%d %d\n",row+1,col);
            check[row+1][col]='1';
            row=row+1;
            step++;
            cur_used_battery++;
            continue;
        }
        else if(floor[row][col-1]=='0'&&check[row][col-1]=='0'&&col-1>=0)
        {
            if(cur_used_battery+BFS_node[row][col-1].dis+1>battery)
            {
                *end_row=row;
                *end_col=col;
                break;
            }
            //cout<<row<<" "<<col-1<<endl;
            fprintf(fp,"%d %d\n",row,col-1);
            check[row][col-1]='1';
            col=col-1;
            step++;
            cur_used_battery++;
            continue;
        }
        else if(floor[row][col+1]=='0'&&check[row][col+1]=='0'&&col+1<map_col)
        {
            if(cur_used_battery+BFS_node[row][col+1].dis+1>battery)
            {
                *end_row=row;
                *end_col=col;
                break;
            }
            //cout<<row<<" "<<col+1<<endl;
            fprintf(fp,"%d %d\n",row,col+1);
            check[row][col+1]='1';
            col=col+1;
            step++;
            cur_used_battery++;
            continue;
        }
        else
        {
            /*check[row][col]='1';
            *end_row=row;
            *end_col=col;
            break;*/
            int nearest_row,nearest_col;
            int dis=BFStonearest(floor,check,map_row,map_col,row,col,&nearest_row,&nearest_col);
            //int dis=findthenearest_DFS(check,&nearest_row,&nearest_col,map_row,map_col);
            if(checkisover(check,map_row,map_col))
            {
                check[row][col]='1';
                *end_row=row;
                *end_col=col;
                break;
            }
            if(dis+cur_used_battery+BFS_node[nearest_row][nearest_col].dis>battery)
            {
                check[row][col]='1';
                *end_row=row;
                *end_col=col;
                break;
            }
            else
            {
                ispassbattery(nearest_row,nearest_col,check);
                if(pass_battery==true)
                {
                    check[row][col]='1';
                    *end_row=row;
                    *end_col=col;
                    pass_battery=false;
                    break;
                }
                printBFSpath2(nearest_row,nearest_col,check);
                row=nearest_row;
                col=nearest_col;
            }
        }
    }
}

/*void DFSsearch(char**check,char**floor,int map_row,int map_col,int row,int col)
{
    //cout<<row<<" "<<col<<endl;
    if(floor[row-1][col]=='0'&&check[row-1][col]=='0'&&row-1>=0)
    {
        step++;
        check[row-1][col]='1';
        cout<<row<<" "<<col<<endl;
        DFSsearch(check,floor,map_row,map_col,row-1,col);
    }
    if(floor[row+1][col]=='0'&&check[row+1][col]=='0'&&row+1<map_row)
    {
        step++;
        check[row+1][col]='1';
        cout<<row<<" "<<col<<endl;
        DFSsearch(check,floor,map_row,map_col,row+1,col);
    }
    if(floor[row][col-1]=='0'&&check[row][col-1]=='0'&&col-1>=0)
    {
        step++;
        check[row][col-1]='1';
        cout<<row<<" "<<col<<endl;
        DFSsearch(check,floor,map_row,map_col,row,col-1);
    }
    if(floor[row][col+1]=='0'&&check[row][col+1]=='0'&&col+1<map_col)
    {
        step++;
        check[row][col+1]='1';
        cout<<row<<" "<<col<<endl;
        DFSsearch(check,floor,map_row,map_col,row,col+1);
    }
    cout<<row<<" "<<col<<endl;
}*/


int main()
{



    int map_row;
    int map_col;
    int battery;

    ifstream fin("floor.data");
    ofstream fout("final.path");
    fin>>map_row>>map_col>>battery;
    char floor[map_row][map_col+1];
    char* arr[map_row];

    for(int i=0;i<map_row;i++)
    {
        fin>>floor[i];
    }

    for(int i=0; i<map_row; i++)
    {
        for(int j=0; j<map_col; j++)
        {
            /*char c=getchar();
            if(c=='\n')
                c=getchar();
            floor[i][j]=c;*/
            if(floor[i][j]=='R')
            {
                battery_row=i;
                battery_col=j;
            }
        }
    }
    for(int i=0; i<map_row; i++)
    {
        arr[i]=floor[i];
    }


    /*Node* BFS_arr_node[map_row];
    for(int i=0; i<map_row; i++)
    {
        BFS_arr_node[i]=BFS_node[i];
    }*/

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
    BFStobattery(arr,map_row,map_col);

    int nearest_row,nearest_col;
    int end_row,end_col;
    while(!checkisover(checkarr,map_row,map_col))
    {
        findthenearest_BFS(checkarr,&nearest_row,&nearest_col,map_row,map_col);
        //cout<<"the nearrow is"<<nearest_row<<"the nearest col is"<<nearest_col<<endl
        printBFSpath(nearest_row,nearest_col,checkarr);
        cur_used_battery--;
        step--;
        //DFSsearch(checkarr,arr,map_row,map_col,nearest_row,nearest_col);
        DFS(checkarr,arr,nearest_row,nearest_col,map_row,map_col,&end_row,&end_col,battery);
        printBFSbackpath(end_row,end_col,checkarr);
        cur_used_battery=0;
    }
    //cout<<battery_row<<" "<<battery_col<<endl;
    fprintf(fp,"%d %d\n",battery_row,battery_col);
    fout<<step<<endl;
    rewind(fp);
    char path[5];
    while(fgets(path,5,fp))
    {
        fout<<path;
    }
    //printBFSpath(1,3,BFS_arr_node);
    //printBFSbackpath(1,3,BFS_arr_node);

}
