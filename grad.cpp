#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("grad.in");
ofstream fout("grad.out");
pair<int,pair<int,int> >v[260];
bool corect(pair<int,pair<int,int> >a,pair<int,pair<int,int> >b)
{
    return(a.second.first<b.second.first || a.second.first==b.second.first && a.second.first<b.second.first);
}
int suma(int x)
{
    int s=0;
    while(x>0)
    {
        s=s+x%10;
        x=x/10;
    }
    return s;
}
int main()
{
    int n,i;
    fin>>n;
    for(i=1; i<=n; i++)
    {
        fin>>v[i].first;
        v[i].second.first=suma(v[i].first);
        v[i].second.second=i;
    }
    sort(v+1,v+n+1,corect);
    for(i=1; i<=n; i++)
    {
        fout<<v[i].first<<" ";
        if(v[i].second.first!=v[i+1].second.first)
        {
            fout<<'\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}
