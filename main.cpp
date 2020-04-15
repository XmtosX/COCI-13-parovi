#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
string s1,s2;
int a[50004],b[50004];
int memo1[50004][2][2][2][2],memo2[50004][2][2][2][2];
int cnt(int pos,bool yes1,bool yes2,bool yes3,bool yes4)
{
    if (pos==s1.size())
    {
        return 1;
    }
    int &ret=memo1[pos][yes1][yes2][yes3][yes4];
    if (ret!=-1)
        return ret;
    ret=0;
    for (int i=0;i<10;i++)
    {
        for (int j=0;j<10;j++)
        {
            if ((yes1||i>=a[pos])&&(yes2||i<=b[pos])&&(yes3||j>=a[pos])&&(yes4||j<=b[pos]))
            {
                ret+= cnt(pos+1,yes1|(i>a[pos]),yes2|(i<b[pos]),yes3|(j>a[pos]),yes4|(j<b[pos]));
                ret%=mod;
            }
        }
    }
    return ret;
}
int dp(int pos,bool yes1,bool yes2,bool yes3,bool yes4)
{
    if (pos==s1.size())
    {
        return 0;
    }
    int &ret=memo2[pos][yes1][yes2][yes3][yes4];
    if (ret!=-1)
        return ret;
    ret=0;
    for (int i=0;i<10;i++)
    {
        for (int j=0;j<10;j++)
        {
           if ((yes1||i>=a[pos])&&(yes2||i<=b[pos])&&(yes3||j>=a[pos])&&(yes4||j<=b[pos]))
            {
                ret+= ((long long)cnt(pos+1,yes1|(i>a[pos]),yes2|(i<b[pos]),yes3|(j>a[pos]),yes4|(j<b[pos])) *((long long)abs(i-j)))%mod;
                ret%=mod;
                ret+= dp(pos+1,yes1|(i>a[pos]),yes2|(i<b[pos]),yes3|(j>a[pos]),yes4|(j<b[pos]));
                ret%=mod;
            }
        }
    }
    return ret;
}
int main()
{
    memset(memo1,-1,sizeof memo1);
    memset(memo2,-1,sizeof memo2);
    cin >>s1>>s2;
    reverse(s1.begin(),s1.end());
    reverse(s2.begin(),s2.end());
    while (s1.size()<s2.size())
        s1+='0';
    reverse(s1.begin(),s1.end());
    reverse(s2.begin(),s2.end());
    for (int i=0;i<s1.size();i++)
        a[i]=s1[i]-'0',b[i]=s2[i]-'0';
    cout <<dp(0,0,0,0,0);
    return 0;
}
