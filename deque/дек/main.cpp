#include <iostream>
#include<array>
#include<vector>
#include<deque>
#include<iterator>
using namespace std;
template<class T>
struct Block
{
    array<T,4> data={} ;//k=4
};
template<class T>
class Pointer
{
    public:
        T *p;
        int index;
    public:
        bool check_next();
        bool check_previous();
        Pointer();
        void next_blockend(T *p);
        void next_block(T *p,int index);
        Pointer& operator++();
        void add(T number);
        Pointer& operator--();
};
template<class T>
Pointer<T>::Pointer()
{
    this->p=NULL;
}
template<class T>
bool Pointer <T>::check_next()
{
    if(index!=3){
        index++;
        return true;
    }else return false;
}
template<class T>
bool Pointer <T>::check_previous()
{
    if(index!=0){
        index--;
        return true;
    }else return false;
}
template<class T>
void Pointer <T>::next_block(T *p,int index)
{
    this->p=p;
   this-> index =index;
}
template<class T>
Pointer<T>& Pointer <T>:: operator++()
{
    p++;
    return *this;
}
template<class T>
Pointer<T>& Pointer<T>:: operator--()
{
    p--;
    return *this;
}
template<class T>
class Deque:public Pointer<T>
{
private:
    vector<Block<T>*> pdata;
    vector<Block<T>> block;
    Pointer<T> Begin;
    Pointer<T> End;
    int index_end;
    int n_blocks;
    int count_block;
    int size;
public:
    Deque();
    void Resize();
   void clear();
    void Print();
    void push_frontpdata();
    void Push_front(T number);
    void Pop_back();
    void Push_back(T number);
    bool empty();
    T& operator [](const int index);
    int Size();
    class Iterator;
    Iterator begin() const
    {
        return Iterator(Begin.index, 0, pdata);
    }
    Iterator end() const
    {
        return Iterator((End.index)+1,count_block,pdata);
    }
};
template<class T>
class Deque<T>::Iterator
{
private:
    vector<Block<T>*> pointerBlock;
    int index_element;
    int index_block;
public:
    Iterator(int index,int idex_block,vector<Block<T>*> pdata)
    {
        this->index_element=index;
        pointerBlock=pdata;
        this->index_block=idex_block;
    }
    T& operator*()
    {
        return pointerBlock[index_block]->data[index_element];
    }
    Iterator operator++()
    {
        if(index_element!=3){
            index_element++;
           return *this;
        }else{
            index_block++;
            index_element=0;
            return *this;
        }
    }
    Iterator operator--()
    {
        if(index_element!=0){
            index_element--;
           return *this;
        }else{
            index_block--;
            index_element=3;
            return *this;
        }
    }
    bool operator !=(const Iterator& obj)
    {
        if(index_element==obj.index_element && index_block==obj.index_block){
            return true;
        }else{
            return false;
        }
    }
    bool operator ==(const Iterator& obj)
    {
        if(index_element==obj.index_element && index_block==obj.index_block){
            return true;
        }else{
            return false;
        }
    }
};
template <class T>
Deque<T>::Deque()
{
    size=0;
    count_block=0;
    n_blocks=3;
    pdata.resize(n_blocks);
    block.resize(n_blocks);
    for(int i=0;i<n_blocks;i++){
        pdata[i]=&block[i];
    }
}
template <class T>
void Deque<T>::push_frontpdata()
{
    pdata.insert(pdata.begin(),pdata[n_blocks-1]);
}
template <class T>
void Deque<T>::Push_front(T number)
{
    size++;
    if(Begin.p==NULL){
        pdata[count_block]->data[0]=number;
        Begin.next_block(&(pdata[count_block]->data[0]),0);
        End.next_block(&(pdata[count_block]->data[0]),0);
        return;
    }
    if(!Begin.check_previous()){
        if(End.p==&(pdata[n_blocks-1]->data[0])||End.p==&(pdata[n_blocks-1]->data[1])||End.p==&(pdata[n_blocks-1]->data[2])||End.p==&(pdata[n_blocks-1]->data[3])){
            Resize();
            push_frontpdata();
            pdata.pop_back();
            Begin.next_block(&(pdata[0]->data[3]), 3);
            *(Begin.p)=number;
            return;
        }else{
            push_frontpdata();
            pdata.pop_back();
            Begin.next_block(&(pdata[0]->data[3]), 3);
            *(Begin.p)=number;
        }
    }else{
    --Begin;
    *(Begin.p)=number;
    }
}
template <class T>
void Deque<T>::clear()
{
    pdata.clear();
    block.clear();
    size=0;
    count_block=0;
    n_blocks=3;
    pdata.resize(n_blocks);
    block.resize(n_blocks);
    for(int i=0;i<n_blocks;i++){
        pdata[i]=&block[i];
    }
}
template <class T>
void Deque<T>::Push_back(T number)
{
    size++;
    if(Begin.p==NULL){
        pdata[count_block]->data[0]=number;
        Begin.next_block(&(pdata[count_block]->data[0]),0);
        End.next_block(&(pdata[count_block]->data[0]),0);
        return;
    }
    if(!End.check_next()){
        if((++count_block)>pdata.size()){
            Resize();
            End.next_block(&(pdata[count_block]->data[0]), 0);
            *(End.p)=number;
            return;
        }else{
            End.next_block(&(pdata[count_block]->data[0]), 0);
            *(End.p)=number;
        }
    }else{
    ++End;
    *(End.p)=number;
    }
}
template<class T>
void Deque<T>::Pop_back()
{
    size--;
    if(Begin.p==NULL){
        cout<<"Mistake!!!";
        return;
    }
    if(!End.check_previous()){
        End.next_block(&(pdata[++count_block]->data[3]), 3);
    }
    else{
    --End;
    }
}
template<class T>
bool Deque<T>::empty()
{
    if(Begin.p==NULL){
       return true;
    }else{
        return false;
    }
}
template<class T>
T& Deque<T>::operator[](const int index)
{
    int buff=(Begin.index+index)%(n_blocks*4);
    int chunk_index=buff/4;
    int i=buff%4;
    return pdata[chunk_index]->data[i];
}
template <class T>
void Deque<T>:: Resize()
{
    n_blocks+=3;
    pdata.resize(n_blocks);
    block.resize(n_blocks);
    for(int i=n_blocks-3;i<n_blocks;i++){
        pdata[i]=&block[i];
    }
}
template <class T>
int Deque<T>:: Size()
{
    return size;
}
int main(int argc, const char * argv[]) {
    Deque<int> a;
    a.Push_front(8);
    a.Push_front(6);
    a.Push_front(5);
    a.Push_front(8);
    a.Push_front(6);
    a.Push_front(5);
    cout<<a[0];
    for(int i=0;i<a.Size();i++){
        cout<<a[i];
    }
    auto it=a.begin();
    ++it;
    ++it;
    cout<<*it;
    a.clear();
    return 0;
}
