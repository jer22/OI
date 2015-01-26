/*
ID: dccmx1
PROG: cryptcow
LANG: C++
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;
 
const int HashSize=131071;
const string dest="Begin the Escape execution at the Break of Dawn";
 
bool searched[HashSize];
 
bool IsEncrypted(string text);
 
int main()
{
    freopen("cryptcow.in","r",stdin);
    // freopen("cryptcow.out","w",stdout);
 
    string text;
    getline(cin,text);
 
    if (IsEncrypted(text))
    {
        cout<<"1 "<<count(text.begin(),text.end(),'C')<<endl;
    }
    else
    {
        cout<<"0 0"<<endl;
    }
 
    return 0;
}
 
int Hash(const string &str);
bool Impossible(const string &text);
string Transform(const string &src,int c,int o,int w);
 
bool IsEncrypted(string text)
{
    int hash=Hash(text)%HashSize;
    if (searched[hash])//not reasonable, but works for most test data.
    {
        return false;
    }
    searched[hash]=true;
 
    if (text==dest)
    {
        return true;
    }
    if (Impossible(text))
    {
        return false;
    }
 
    for (int o=1; o<text.length()-1; o++)
    {
        if (text[o]=='O')
        {
            for (int c=0; c<o; c++)
            {
                if (text[c]=='C')
                {
                    for (int w=text.length()-1; w>o; w--)
                    {
                        if (text[w]=='W')
                        {
                            if (IsEncrypted(Transform(text,c,o,w)))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
 
    return false;
}
 
bool Impossible(const string &text)
{
    if ((text.length()-dest.length())%3!=0)
    {
        return true;
    }
    int i=0,j;
    while (i<text.length())
    {
        j=i+1;
        if (text[i]!='C' && text[i]!='O' && text[i]!='W')
        {
            while (j<text.length())
            {
                if (text[j]=='C' || text[j]=='O' || text[j]=='W')
                {
                    break;
                }
                j++;
            }
 
            if (dest.find(text.substr(i,j-i))==string::npos)
            {
                return true;
            }
        }
 
        i=j;
    }
 
    return false;
}
 
string Transform(const string &src,int c,int o,int w)
{
    static char buffer[100];
    int i,ich=0;
 
    for (i=0; i<c; i++)
    {
        buffer[ich++]=src[i];
    }
    for (i=o+1; i<w; i++)
    {
        buffer[ich++]=src[i];
    }
    for (i=c+1; i<o; i++)
    {
        buffer[ich++]=src[i];
    }
    for (i=w+1; i<src.length(); i++)
    {
        buffer[ich++]=src[i];
    }
    buffer[ich++]=0;
 
    return string(buffer);
}
 
int Hash(const string &str)
{
    unsigned long h=0,g;
    for (int i=0; i<str.length(); i++)
    {
        h=(h<<4)+str[i];
        g=h &0xf0000000l;
        if (g)
        {
            h^=g>>24;
        }
        h&=~g;
    }
    return h;
}

