/*#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("student.in");
ofstream fout("student.out");

struct elev
{
    char nume[50];
    int nota1,nota2,nota3,teza;
    float media;
} e[50];

int main()
{
    int n,i,j;
    elev aux;
    fin>>n;
    for(i=1; i<=n; i++)
    {
        fin.get();
        fin.getline(e[i].nume,50);
        fin>>e[i].nota1;
        fin>>e[i].nota2;
        fin>>e[i].nota3;
        fin>>e[i].teza;
        e[i].media=((e[i].nota1+e[i].nota2+e[i].nota3)+e[i].teza)/4;
    }
    for(i=1; i<=n; i++)
    {
        for(j=i+1; j<=n; j++)
        {
            if(e[i].media<e[j].media)
            {
               aux=e[i];
               e[i]=e[j];
               e[j]=aux;
            }
        }
    }
    fout<<"Elevii ordonati descrescatori in functie de medie sunt:";
    fout<<'\n';
    for(i=1; i<=n; i++)
    {
        fout<<e[i].nume<<" "<<e[i].media;
        fout<<'\n';
    }
    fin.close();
    fout.close();
    return 0;
}*/
#include <iostream>
#include <cstring>
using namespace std;
struct elev
{
    char nume[60];
    double nota1,nota2,nota3,teza,media;
};
int main()
{
    int n,i,j;
    elev aux;
    elev e[50];
    cout<<"Introduceti numarul de elevi : ";
    cin>>n;
    for (i=1; i<=n; i++)
    {
        cin.get();
        cout<<"Introduceti numele elevului "<<i<<": ";
        cin.getline(e[i].nume,50);
        cout<<"Introduceti nota 1 : ";
        cin>>e[i].nota1;
        cout<<"Introduceti nota 2 : ";
        cin>>e[i].nota2;
        cout<<"Introduceti nota 3 : ";
        cin>>e[i].nota3;
        cout<<"Introduceti teza : ";
        cin>>e[i].teza;
        e[i].media=((e[i].nota1+e[i].nota2+e[i].nota3)+e[i].teza)/4;
    }
    for (i=1; i<=n-1; i++)
    {
        for (j=i+1; j<=n; j++)
        {
            if (e[i].media<e[j].media)
            {
                aux=e[i];
                e[i]=e[j];
                e[j]=aux;
            }
        }
    }
    cout<<"Elevii ordonati descrescatori in functie de medie sunt:";
    cout<<'\n';
    for (i=1; i<=n; i++)
    {
        cout<<e[i].nume<<" "<<e[i].nota1<<" "<<e[i].nota2<<" "<<e[i].nota3<<" "<<e[i].teza<<" "<<e[i].media;
        cout<<'\n';
    }
}
