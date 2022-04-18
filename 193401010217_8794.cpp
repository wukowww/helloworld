#include<iostream>
#include <vector>
using namespace std;
class father{   //����ͼ�ļ�·��
private:
    vector<int> path;
    int count;
    int start;
    int **map;    // ���ڽӾ���
    int end;     // �յ�
    
    int temp;   //path·������  ��Ч����
public:
    father(int count , int start ,int end );//���ڳ�ʼ������ı���
    ~father();//��������  ������������ڴ���ͷ�
    void creat(); // �����ڽӾ���
    void commondfs(int v); //�ҳ����д�start �� end  �ļ�·��
   
    void print();//��ӡ·���ĺ���
    int findnext(int v,int con);//�ҵ���һ���ڽӵ�   con������V�ĵ�CON���ڽӵ�
    bool iscircle(int next);//�ж��Ƿ�·���Ƿ��γɻ�·
};
father::father(int total, int s, int e) {
    count=total;
    start=s;
    end=e;
   
    path.push_back(s);  //�����
    temp=0;//��ʱ·��������1
    map=new int*[total];  //�����ά����Ŀռ�   �·���
    for (int i = 0; i < total; ++i) {
        map[i]=new int[total];  //�����ά�����еײ�Ŀռ�
    }
}
father::~father() {  //��������  �ͷ��ڴ�
    delete [] map;
}

void father::creat() { //�����ڽӾ���   ����ͼ
    int a;
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            cin>>a;
            map[i][j]=a;
        }
    }
}

void father::commondfs(int v) { //��������·��
    if (v==end){  //�ݹ����  ����ҵ��յ������
        print();  //��ӡ·��
        return ;
    }
    int con = 0;  //��ǰΪ0����V�ĵ�һ���ڽӵ�
    int next =findnext(v,con);  //ͨ��findnext�ҵ���һ���ڽӵ�
    while(next != -1){  //�ж��Ƿ��ҵ�
        while (iscircle(next)){  //�ж� �ҵ����ڽӵ�᲻���֮ǰ��·�����ɻ�·
            con++; //������ɻ�·  ����һ��next����ѡ  �ҵڶ����ڽӵ�  Ȼ���ж�
            next=findnext(v,con); //��������

        }
        path.push_back(next);//�������ҵ�һ�������ɻ�·���ڽӵ�ʱ��  ����·��
        commondfs(next); //�ݹ���next ���ڽ�
        path.pop_back();  //�ߵ������ʱ�� ����������һ��·��   �������߲����յ� ��Ҫ����ѡȡnext
        //v=path.back(); //��֮ǰ���next����  �����õ�next֮ǰ���Ǹ�ֵ  ��д�ɲ�д
        con++; //��con���м�һ  ��ʾV����һ���ڽӵ�
        next=findnext(v,con);//���ڽӵ�
    }
}

void father::print() {  //��ӡ
    vector<int>::iterator it=path.begin();
    for(;it<path.end()-1;it++)
        cout<<*it<<"->";
    cout<<*it<<endl;
}
int father::findnext(int v, int con) {  //���ڽӵ�
    int a=-1,k=0;  //a=-1 ��ʾû�ҵ��ڽӵ� ����-1
    for (int j = 0; j < count; ++j) {  
        if (map[v][j]!=0){  //�ҵ��ڽӵ�
            if(k==con){  //�ж��ǲ��ǵ�con���ڽӵ�
                a=j ;  //���ص�
                break;
            }
            k++; //  ������ǵ�con���ڽӵ� �����   ע��con ��ʵ�ʵڼ����ڽӵ������
            /*f(k>con){  //��Ҫ�ɲ�Ҫ  д�Ϸ����˽�
                break;
            }*/
        }
    }
    return a;
}
bool father::iscircle(int next) {  //�ж��Ƿ��ǻ�
    //����ǰ���ڽӵ��루����path�е����һ���㣩path�еĵ��Ƿ���ͬ ��ͬ���л�·  ��֮û��  ����⻭��ͼ �����
    for (vector<int>::iterator it=path.begin();it<path.end()-1;it++) {
        if (*it==next){
            return true;
        }
    }
    return false;
}
int main(){
    cout<<"������ڵ���  ���  �յ�  "<<endl;
    int n,x,y;
    cin>>n>>x>>y;
    father a(n,x,y);
    cout<<"����������ڽӾ���"<<endl;
    a.creat();
    cout<<"���м�·��Ϊ--->"<<endl;
    a.commondfs(x);
    system("pause");
}
