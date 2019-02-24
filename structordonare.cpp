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
    float aux1;
    char aux2[50];
    fin>>n;
    for(i=1; i<=n; i++)
    {
        fin.get(e[i].nume,50);
        fin>>e[i].nota1;
        fin>>e[i].nota2;
        fin>>e[i].nota3;
        fin>>e[i].teza;
        e[i].media=((e[i].nota1+e[i].nota2+e[i].nota3)+e[i].teza)/4;
    }
    for(i=1; i<=n; i++)
    {
        for(j=i+1; j<=n;)
        {
            if(e[i].media<e[j].media)
            {
                aux1=e[i].media;
                e[i].media=e[j].media;
                e[j].media=aux1;

                strcpy(aux2,e[i].nume);
                strcpy(e[i].nume,e[j].nume);
                strcpy(e[j].nume,aux2);
            }
        }
    }
    fout<<"Elevii ordonati descrescatori in functie de medie sunt:";
    fout<<'\n';
    for(i=1; i<=n; i++)
    {
        fout<<e[i].nume;
        fout<<'\n';
    }
    fin.close();
    fout.close();
    return 0;
}
/*#include <iostream>
#include <cstring>
using namespace std;
struct elev
{
    char numeprenume[60];
    int nota1,nota2,nota3,teza;
    float media;
};
int main()
{
    int n,i,j;
    float med[50],x;
    elev e[50];
    char aux[60];
    cout<<"Introduceti numarul de elevi : ";
    cin>>n;
    cin.get();
    for (i=1; i<=n; i++)
    {
        cout<<"Introduceti numele elevului "<<i<<" ";
        cin.get(e[i].numeprenume,50);
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
                x=e[i].media;
                e[i].media=e[j].media;
                e[j].media=x;

                strcpy(aux,e[i].numeprenume);
                strcpy(e[i].numeprenume,e[j].numeprenume);
                strcpy(e[j].numeprenume,aux);
            }
        }
    }
    cout<<"Elevii ordonati descrescatori in functie de medie sunt:";
    cout<<endl;
    for (i=1; i<=n; i++)
    {
        cout<<e[i].numeprenume<<endl;
    }
}*/
