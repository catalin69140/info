#include <fstream>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;
ifstream fin("pluton.in");
ofstream fout("pluton.out");

int ap[10];

pair<int,int>v[4005];

bool corect(pair<int,int>a,pair<int,int>b)
{
    return(a.second<b.second || a.second==b.second && a.first<b.first);
}

int sortare(int x)
{
    int p=1,y,i,lcrt,lmax;
    while(x)
    {
        ap[x%10]++;
        x=x/10;
    }
    p=1;
    for(i=9; i>=0; i--)
    {
        y=i*p+y;
        p=p*10;
    }
    return y;
}

int main()
{
    int n,i,lcrt=1,lmax=INT_MIN,start,nrp=1;
    fin>>n;
    for(i=1; i<=n; i++)
    {
        fin>>v[i].first;
        v[i].second=sortare(v[i].first);
    }
    sort(v+1,v+n+1,corect);
    
    for(i=2; i<=n; i++)
    {
        if(corect(v[i-1],v[i]))
        {
            lcrt++;
        }
        else
        {
            if(lcrt>lmax)
            {
                lmax=lcrt;
                start=i-lcrt;
            }
            nrp++;
            lcrt=1;
        }
    }
    
    if(lcrt>lmax)
    {
        lmax=lcrt;
        start=i-lcrt;
    }
    lcrt=1;
    
    fin.close();
    fout.close();
    return 0;
}
