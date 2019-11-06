#include<iostream>
#include<fstream>
using namespace std;
typedef struct _Node
{
    int row;
    int col;
    int parent[2];//parent[0]=row,parent[1]=col
}Node;
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
    private:
        Node data[1000000];
        Node* point;
        Node* point_pop;
};
int main()
{
    int map_row,map_col,battery;
    char floor[1000][1000];
    ifstream fin("floor.data");
    ofstream fout("final.path");
    fin>>map_row>>map_col>>battery;
    for(int i=0;i<map_row;i++)
    {
        for(int j=0;j<map_col;j++)
        {
            char c=getchar();
            if(c=='\n')c=getchar();
            floor[i][j]=c;
        }
    }

}
