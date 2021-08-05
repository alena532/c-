#include <iostream>
#include <initializer_list>
using namespace std;
struct Node
{
    Node*previous;
    Node*next;
    int data;
    Node(int data,Node *previous,Node*next){
        this->data=data;
        this->previous=previous;
        this->next=next;
    }
};
class List
{
private:
    Node *head;
    Node *tail;
    int size;
public:
    class Iterator
    {
    public:
        Node *temp;
    public:
        Iterator(Node *count):temp(count){};
        Iterator& operator++()
        {
            temp=temp->next;
            return *this;
        }
        Iterator& operator--()
        {
            temp=temp->previous;
            return *this;
        }
        Iterator& operator++(int)
        {
            Iterator other(temp);
            temp=temp->next;
            return other;
        }
        Iterator& operator--(int)
        {
            Iterator other(temp);
            temp=temp->previous;
            return other;
        }
        Iterator operator+(int n)
        {
            while(n!=0){
                temp=temp->next;
                n--;
            }
            return *this;
        }
        int operator*()
        {
            return temp->data;
        }
        bool operator!=(Iterator &it){
            return temp!=it.temp;
        }
        bool operator==(Iterator &it){
            return temp==it.temp;
        }
        bool operator>=(Iterator &it){
            return temp>=it.temp;
        }
        bool operator<=(Iterator &it){
            return temp<=it.temp;
        }
    };
    Iterator begin()
    {
        return Iterator(head);
    }
    Iterator end()
    {
        tail->next=new Node(0,tail,NULL);
        return Iterator(tail->next);
    }
    List();
    List(const List&temp);
    //List (const initializer_list<int> &list);
    void Push_front(int data);
    void Show();
    void Push_back(int data);
    void Insert(int index,int data);
    void Pop_back();
    void Pop_front();
    int Size();
    bool Empty();
    ~List();
};
/*List::List(const initializer_list<int> &list )
{
    tail=head=NULL;
    size=0;
    for(auto element:list){
        Push_back(element);
    }
}
*/
List::List()
{
    tail=head=NULL;
    size=0;
}
List::List(const List&temp)
{
    tail=head=NULL;
    size=0;
    Node *count2=temp.head;
    while(count2!=NULL){
        Push_back(count2->data);
        count2=count2->next;
    }
}
void List::Push_front(int data)
{
    if(head==NULL&& tail==NULL){
      head=tail= new Node(data,NULL,NULL);
    }else{
        head->previous =new Node(data,NULL,head);
        head=head->previous;
    }
    size++;
}
void List::Show()
{
    Node *temp=head;
    
    while(temp!=NULL){
        cout<<temp->data;
        temp=temp->next;
    }
}
void List::Push_back(int data)
{
    if(head==NULL&& tail==NULL){
      head=tail= new Node(data,NULL,NULL);
    }else{
        tail->next=new Node(data,tail,NULL);
        tail=tail->next;
    }
    size++;
}
void List::Pop_back()
{
    if(head==NULL &&tail==NULL){
        cout<<"Mistake";
        return;
    }
    Node *temp=tail;
    tail=tail->previous;
    tail->next=NULL;
    delete temp;
    size--;
}
void List::Pop_front()
{
    if(head==NULL &&tail==NULL){
        cout<<"Mistake";
        return;
    }
    Node *temp=head;
    head=head->next;
    head->previous=NULL;
    delete temp;
    size--;
}
int List::Size()
{
    return size;
}
bool List::Empty()
{
    if(size==0){
        return true;
    }else return false;
}
List::~List()
{
    Node *temp=head;
    Node *del;
    while(temp!=NULL){
        del=temp;
        temp=temp->next;
        delete del;
    }
    delete temp;
}
int main(int argc, const char * argv[]) {
    List a;
    a.Push_front(7);
    a.Push_front(8);
    a.Push_front(9);
    a.Push_front(2);
    a.Push_back(6);
    a.Push_back(9);
    a.Pop_back();
    
   
    cout<<endl;
    List::Iterator It(a.begin());
    It++;
    cout<<*It;
    
    return 0;
}
