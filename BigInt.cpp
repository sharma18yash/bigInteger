#include<stdio.h>
#include<iostream>
#include<string.h>
#include<csignal>
using namespace std;
#define MAX 1000
class stack{
    int top;
public:
    string arr[MAX];
    stack(){
        top=-1;
    }
    int push(string x){
        if(top >= (MAX-1)){
            return false;
        }
        else{
            arr[++top]=x;
            return true;
        }
    }
    string pop()
    {
        if(top<0) return "0";
        else{
            string x = arr[top--];
            return x;
        }
    }
    string peek()
    {
        string x = arr[top];
        return x;
    }
    bool isEmpty(){
        return (top<0);
    }
};
int precedense(string op){
    if(op=="43" || op == "45") return 1;
    if(op=="120") return 2;
    return 0;
}
void signal_handler( int signal_num ) {
    return;
}
string remZero(string x)
{
    while(x[0]=='0' && x.size()>1)
        x.erase(0,1);
    return x;
}

int isEven(string x)
{
    int n = x[x.size()-1] - '0';
    if((n%2)==0) return true;
    else return false;
}

string rev(string x)
{
    string ans;
    for(int i=x.length()-1; i>=0; i--)
    {
        ans.push_back(x[i]);
    }
    return ans;
}
string addZeros(string x,int num)
{
    for(int i=0; i<num; i++)
    {
        x='0'+x;
    }
    return x;
}
string add(string x, string y)
{
    int carry=0;
    int l1 = x.size();
    int l2 = y.size();

    int m = max(l1,l2);
    if(l1!=l2)
    {
        if(m==l1)
            y = addZeros(y, l1-l2);
        else if(m==l2)
            x = addZeros(x,l2-l1);
    }
    // cout<<x<<" "<<y<<endl;
    string ans;
    for(int i=m-1; i>=0; i--)
    {
        // cout<<x[i]<<" "<<y[i]<<endl;
        int sum = x[i]-'0' + y[i]-'0' + carry;
        // cout<<sum<<" ";
        if(sum>9)
        {
            carry=1;
            int num = sum-10;
            string c = to_string(num);
            ans+=c;
        }
        else
        {
            carry=0;
            string c = to_string(sum);
            ans+=c;
        }
    }
    if(carry==1)
        ans+='1';
    string z = rev(ans);
    return remZero(z);
}

int isGreater(string x, string y)
{
    x = remZero(x);
    y = remZero(y);
    int flag=0;
    if(x.size() > y.size()) return 1;
    if(x.size() < y.size()) return -1;
    else
    {
        for(int i=0; i<x.size(); i++)
        {
            if(x[i]==y[i]) continue;
            int ele1 = x[i] - '0';
            int ele2 = y[i] - '0';
            if(x[i] - '0' > y[i] - '0')
            {
                return true;    
            }
            else if(ele1 < ele2)
                return -1;
        }
        return 0;
    }
}
string sub(string str1, string str2)
{
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    int diff = n1 - n2;
    int carry = 0;
 
    for (int i = n2 - 1; i >= 0; i--) {

        int sub = ((str1[i + diff] - '0') - (str2[i] - '0')
                   - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        str.push_back(sub + '0');
    }
 
    for (int i = n1 - n2 - 1; i >= 0; i--) {
        if (str1[i] == '0' && carry) {
            str.push_back('9');
            continue;
        }
        int sub = ((str1[i] - '0') - carry);
        if (i > 0 || sub > 0) 
            str.push_back(sub + '0');
        carry = 0;
    }
    str = rev(str);
    return remZero(str);
}
string mul(string x, string y)
{
    string ans="0";
    int carry=0;
    for(int j=y.size()-1; j>=0; j--)
    {
        string sum;
        carry=0;
        for(int i=x.size()-1; i>=0; i--)
        {
            int num = (x[i]-'0') * (y[j]-'0') + carry;
            if(num > 9)
            {
                carry = num/10;
                num = num%10;
            }
            else
                carry=0;
            string c = to_string(num);
            sum+=c;
        }
        if(carry>0)
            // cout<<"carry = "<<carry<<endl;
            sum = sum + to_string(carry);
        sum = rev(sum);
        for(int x=y.size()-1; x>j; x--)
            sum+='0';
        // cout<<"sum = "<<sum<<endl;
        ans = add(ans,sum); 
    }
    return remZero(ans);
}
string exponent(string base, long long int power)
{
    string ans = "1";
    long long int i;
    for(int i=0; i<power; i++)
    {
        ans = mul(ans, base);
    }
    return ans;
}
string factorial(string x)
{
    string n="2";
    string ans="1";
    while(n!=x)
    {
        ans = mul(ans,n);
        n = add(n,"1");
    }
    ans = mul(ans, x);
    return ans;
}
string divide(string number, int divisor)
{
    string ans;
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');

    while (number.size() > idx) {
        ans += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
    if (ans.length() == 0)
        return "0";
    return remZero(ans);
}

string apply(string a, string b, string op){
    if(op=="43")
        return add(a,b);
    else if(op=="45")
        return sub(a,b);
    else if(op=="120")
        return mul(a,b);
    return "0";
}
string findCorrectSub(string s, string sbStr)
{
    string res="";
    int i=1;
    while(true){
        string tStr = mul(s,to_string(i));
        if(isGreater(tStr, sbStr)<0)
            res=tStr;
        else if(isGreater(tStr, sbStr)==0){
            res = tStr;
            break;
        }
        else break;

        i++;
    }
    return res;
}
string mod(string dividend, string divisor)
{
    int len1 = dividend.size();
    int len2 = divisor.size();
    string res="0";
    if(len1<len2) return dividend;
    else if(len1==len2){
        string temp = findCorrectSub(divisor, dividend);
        return remZero(sub(dividend, temp));
    }
    else{
        string currDividend = dividend.substr(0, len2+1);
        string currDivisor = findCorrectSub(divisor, currDividend);
        currDividend = sub(currDividend, currDivisor);
        int st=len2+1;
        res = currDividend;
        while(st<len1){
            while(isGreater(currDividend, divisor)<0 && st<len1){
                currDividend+=dividend[st++];
            }
            if(isGreater(currDividend, divisor)<0)
                return remZero(currDividend);
        string temp = findCorrectSub(divisor, currDividend);
        res = sub(currDividend, temp);
        }
    }
    return remZero(res);

}

string gcd(string a, string b)
{
    if(a=="0")
        return b;
    return gcd(mod(b,a),a);
}
int main()
{
    signal(SIGTERM, signal_handler);
    int ch;
    cin>>ch;
    if(ch==4){
        string expr;
        cin>>expr;
        stack value;
        stack op;
        for(int i=0; i<expr.size(); i++){
            if(isdigit(expr[i])){
                string val="";
                while(i<expr.length() && isdigit(expr[i])){
                    val = val+to_string((expr[i]-'0'));
                    i++;
                }
                value.push(val);
                i--;
            }
            else{
                while(!op.isEmpty() && precedense(op.peek()) >= precedense(to_string(expr[i]))){
                    string val2 = value.peek();
                    value.pop();
                    string val1 = value.peek();
                    value.pop();
                    string oper = op.peek();
                    op.pop();
                    // cout<<oper<<endl;
                    value.push(apply(val1, val2, oper));
                }
                op.push(to_string(expr[i]));
            }
        }
        while(!op.isEmpty()){
            string val2 = value.peek();
            value.pop();
            string val1 = value.peek();
            value.pop();
            string oper = op.peek();
            op.pop();
            // cout<<oper<<endl;
            value.push(apply(val1, val2, oper));
        }
        cout<<value.peek();
    }
    if(ch==1)
    {
        string base, ans;
        long long int pow;
        cin>>base>>pow;
        ans = exponent(base, pow);
        cout<<ans;
    }
    if(ch==2){
        string num1,num2, ans;
        cin>>num1>>num2;
        ans = gcd(num1, num2);
        cout<<ans;
    }
    if(ch==3){
        string num1, ans;
        cin>>num1;
        ans = factorial(num1);
        cout<<ans;
    }
    return 0;
}