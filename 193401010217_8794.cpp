#include<iostream>
#include <vector>
using namespace std;
class father{   //有向图的简单路径
private:
    vector<int> path;
    int count;
    int start;
    int **map;    // 存邻接矩阵
    int end;     // 终点
    
    int temp;   //path路径长度  有效长度
public:
    father(int count , int start ,int end );//用于初始化上面的变量
    ~father();//析构函数  类加载完后进行内存的释放
    void creat(); // 创建邻接矩阵
    void commondfs(int v); //找出所有从start 到 end  的简单路径
   
    void print();//打印路径的函数
    int findnext(int v,int con);//找到下一个邻接点   con代表着V的第CON个邻接点
    bool iscircle(int next);//判断是否路径是否形成环路
};
father::father(int total, int s, int e) {
    count=total;
    start=s;
    end=e;
   
    path.push_back(s);  //入起点
    temp=0;//此时路径长度是1
    map=new int*[total];  //申请二维数组的空间   新方法
    for (int i = 0; i < total; ++i) {
        map[i]=new int[total];  //申请二维数组中底层的空间
    }
}
father::~father() {  //析构函数  释放内存
    delete [] map;
}

void father::creat() { //构建邻接矩阵   有向图
    int a;
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            cin>>a;
            map[i][j]=a;
        }
    }
}

void father::commondfs(int v) { //搜索所有路径
    if (v==end){  //递归出口  如果找到终点则结束
        print();  //打印路径
        return ;
    }
    int con = 0;  //当前为0代表V的第一个邻接点
    int next =findnext(v,con);  //通过findnext找到第一个邻接点
    while(next != -1){  //判断是否找到
        while (iscircle(next)){  //判断 找到的邻接点会不会和之前的路径构成回路
            con++; //如果构成回路  则上一个next不能选  找第二个邻接点  然后判断
            next=findnext(v,con); //依次类推

        }
        path.push_back(next);//当我们找到一个不构成环路的邻接点时候  加入路径
        commondfs(next); //递归找next 的邻接
        path.pop_back();  //走到这里的时候 可能是走完一条路径   或者是走不到终点 需要重新选取next
        //v=path.back(); //把之前存的next出队  并且拿到next之前的那个值  可写可不写
        con++; //对con进行加一  表示V的下一个邻接点
        next=findnext(v,con);//找邻接点
    }
}

void father::print() {  //打印
    vector<int>::iterator it=path.begin();
    for(;it<path.end()-1;it++)
        cout<<*it<<"->";
    cout<<*it<<endl;
}
int father::findnext(int v, int con) {  //找邻接点
    int a=-1,k=0;  //a=-1 表示没找到邻接点 返回-1
    for (int j = 0; j < count; ++j) {  
        if (map[v][j]!=0){  //找到邻接点
            if(k==con){  //判断是不是第con个邻接点
                a=j ;  //返回点
                break;
            }
            k++; //  如果不是第con个邻接点 则继续   注意con 和实际第几个邻接点的区别
            /*f(k>con){  //可要可不要  写上方便了解
                break;
            }*/
        }
    }
    return a;
}
bool father::iscircle(int next) {  //判断是否是环
    //看当前的邻接点与（除了path中的最后一个点）path中的点是否相同 相同则有回路  反之没有  不理解画个图 可理解
    for (vector<int>::iterator it=path.begin();it<path.end()-1;it++) {
        if (*it==next){
            return true;
        }
    }
    return false;
}
int main(){
    cout<<"请输入节点数  起点  终点  "<<endl;
    int n,x,y;
    cin>>n>>x>>y;
    father a(n,x,y);
    cout<<"请输入你的邻接矩阵"<<endl;
    a.creat();
    cout<<"所有简单路径为--->"<<endl;
    a.commondfs(x);
    system("pause");
}
