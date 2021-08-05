#include <iostream>
#include <stack>
#include<vector>
using namespace std;
int func(const string &s)
{
    int answer=0;
    stack<int> m;
    for(int i=0;i<s.length();i++){
        switch(s[i]){
            case '-':
            { int a=m.top();
                m.pop();
                int b=m.top();
                m.pop();
                m.push(b-a);
                break;
            }
            case '+':
            {  int a=m.top();
                m.pop();
                int b=m.top();
                m.pop();
                m.push(b+a);
                break;
            }
            case '/':
            {  int a=m.top();
                m.pop();
                int b=m.top();
                m.pop();
                m.push(a/b);
                break;
            }
            case '*':
            {  int a=m.top();
                m.pop();
                int b=m.top();
                m.pop();
                m.push(a*b);
                break;
            }
            case '=':
            {
                answer=m.top();
                break;
            }
            default:
            {
                m.push(s[i]-48);
                break;
            }
        }
    }
    return answer;
}
int number(char a)
{
    switch(a){
        case '+':
            return 1;
        case '-':
            return 1;
        case'*':
            return 2;
        case'/':
            return 2;
    }
    return 0;
}
string getpost(const string &in)
{
    vector<char> out;
    stack<char> oper;
    for(int i=0;i<in.length();i++){
        switch(in[i]){
            case '+':
            {
                if(!oper.empty()){
                    while(number(oper.top())>=number('+')){
                        char temp=oper.top();
                        oper.pop();
                        out.push_back(temp);
                        if(oper.empty())break;
                    }
                }
                    oper.push('+');
                break;
            }
            case '-':
            {
                if(!oper.empty()){
                    while(number(oper.top())>=number('+')){
                        char temp=oper.top();
                        oper.pop();
                        out.push_back(temp);
                        if(oper.empty())break;
                    }
                }
                    oper.push('-');
                break;
            }
            case '/':
            {
                if(!oper.empty()){
                    while(number(oper.top())==number('/')){
                        char temp=oper.top();
                        oper.pop();
                        out.push_back(temp);
                        if(oper.empty())break;
                    }
                }
                    oper.push('/');
                break;
            }
            case '*':
            {
                if(!oper.empty()){
                    while(number(oper.top())==number('/')){
                        char temp=oper.top();
                        oper.pop();
                        out.push_back(temp);
                        if(oper.empty())break;
                    }
                }
                    oper.push('*');
                break;
            }
            case '=':
            {
                oper.push('=');
                break;
            }
            default:
                out.push_back(in[i]);
                break;
        }
    }
    int a=oper.top();
    oper.pop();
    while(!oper.empty()){
        int b=oper.top();
        out.push_back(b);
        oper.pop();
    }
    out.push_back(a);
    char *output=new char[out.size()];
    for(int i=0;i<out.size();i++){
        output[i]=out[i];
    }
    return output;
}
int main(int argc, const char * argv[]) {
    string str;
    cin>>str;
    string my;
    my=getpost(str);
    cout<<func(my);
    return 0;
}
