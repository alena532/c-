#include <iostream>
#include<forward_list>
using namespace std;
template<class Key,class Value>
class Table
{
private:
    int size;
    int count;
    forward_list<pair<Key,Value>>*arr;
    size_t hashIndex (Key key);
public:
    Table(int count);
    void Insert(pair<Key,Value> number);
    void Erase(Key key);
    void Rehash(int count);
    void Clear();
    bool Contains(Key key);
    Value& operator[](Key key);
    Value& operator[](Key key) const;
    ~Table();
};
template<class Key,class Value>
Table<Key,Value>::Table(int count)
{
    size=count;
    arr=new forward_list<pair<Key,Value>>[size];
    count=0;
}
template<class Key,class Value>
size_t Table<Key,Value>:: hashIndex (Key key)
{
    size_t index=static_cast<size_t>(hash<Key>()(key));
    index=index%size;
    return index;
}
template<class Key,class Value>
void Table<Key,Value>:: Insert(pair<Key,Value> number)
{
    if (size==count){
        Rehash(size*2);
    }
    size_t index=hashIndex(number.first);
    arr[index].push_front(number);
    count++;
}
template<class Key,class Value>
void Table<Key,Value>:: Erase(Key key)
{
    size_t index=hashIndex(key);
    auto it=arr[index].begin();
    int i=0;
    for(;it!=arr[index].end();it++){
        i++;
        if( it->first==key){
            it->first=0;
            it->second=0;
            return;
        }
    }
}
template<class Key,class Value>
void Table<Key,Value>::Rehash(int count)
{
    forward_list<pair<Key,Value>>*temp=arr;
    forward_list<pair<Key,Value>>*arr2=new
    forward_list<pair<Key,Value>>[count];
    arr=arr2;
    arr2=temp;
    for(int i=0;i<size;i++){
        for(auto it=arr2[i].begin();it!=arr2[i].end();it++){
            pair<int,int>ab(it->first,it->second);
            Insert(ab);
        }
    }
    delete[] arr2;
}
template<class Key,class Value>
bool Table<Key,Value>:: Contains(Key key)
{
    size_t index=hashIndex(key);
    auto it=arr[index].begin();
    for(;it!=arr[index].end();it++){
        if( it->first==key){
            return true;
        }
    }
    return false;
}
template<class Key,class Value>
Value& Table<Key,Value>::operator[](Key key)
{
    size_t index=hashIndex(key);
    if (!Contains(key)){
        pair<int,int>ab(key,0);
        Insert(ab);
        return arr[index].front().second;
    }
    auto it=arr[index].begin();
    for(;it!=arr[index].end();it++){
        if(it->first==key){
            break;
        }
    }
    return it->second;
}
template<class Key,class Value>
Value& Table<Key,Value>::operator[](Key key) const
{
    auto it=arr[index].begin();
    for(;it!=arr[index].end();it++){
        if(it->first==key){
            return it->second;
        }
    }
}
template<class Key,class Value>
Table<Key,Value>::~Table()
{
    delete[]arr;
    arr=nullptr;
}
template<class Key,class Value>
void Table<Key,Value>::Clear()
{
    delete[]arr;
    arr=nullptr;
}
int main(int argc, const char * argv[]) {
    Table<int,int> a(10);
    pair<int,int>ab(100,230);
    pair<int,int>bc(130,200);
    a.Insert(ab);
    a.Insert(bc);
    cout<<a[100];
    a.Rehash(2);
    cout<<a[130];
    return 0;
}
