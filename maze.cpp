#include <iostream>
#include <cstdlib>                                           ///Librarie care asigura generarea aleatorie a numerelor.
#include <ctime>
#include <stdio.h>
#include <time.h>

using namespace std;

void delay(int secunde)
{
    int milisecunde=1000*secunde;
    clock_t goal=milisecunde+clock();
    while(goal>clock());
}

struct Killer                                                ///Pe capul tau este o recompensa frumoasa,asigurate ca nu te intalnesti cu unul dintre acesti mercenari.
{
    int x,y;
    char kill;
};

struct anotherPrizonier                                      ///Unul dintre colegi tai,inchis impreuna cu tine in inchisoare,nu te lasa sa treci mai departe.Va trebui sa gasesti o alta cale.
{
    int x,y;
    char block;
};

struct Police                                                ///Daca te prinde politistul te va duce inapoi in celula de unde vei incerca o noua tentativa de fuga.
{
    int x,y;
    char restart;
};

const char height=25,width=30;
char prizonier='@',enemy1='K',enemy2='F',enemy3='P',goal='G';     ///Simbolurile care apar in labirint
int prizonierPOZx=1,prizonierPOZy=1,goalPOZx=18,goalPOZy=23;      ///Pozitia prizonierului si pozitia libertatii lui
char prizonierMOVEMENT;                                           ///WASD,miscarile prizonierului

unsigned char escapePLAN[height][width]={
//      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24
/*0*/  '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
/*1*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*2*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*3*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*4*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*5*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*6*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*7*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*8*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*9*/  '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*10*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*11*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*12*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*13*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*14*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*15*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*16*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*17*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*18*/ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
/*19*/ '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
};

int refresescapePLAN()                                       ///O functie ce va actualiza planul tau de fuga.
{
    int i,j;
    escapePLAN[prizonierPOZx][prizonierPOZy]=prizonier;      ///Genereaza pozitia prizonierului pe plan.
    escapePLAN[goalPOZx][goalPOZy]=goal;                     ///Genereaza pozitia de finish pe plan.
    for(i=0; i<height; i++)
    {
        cout<<'\n';
        for(j=0; j<width; j++)
        {
            cout<<escapePLAN[i][j];
        }
    }
    return 0;
}

int spawnENEMY1()                                            ///O functie ce va genera primul tau tip de inamici
{
    Killer myenemy1;                                         ///Creeaza o variabila myenemy1 de la struct Killer
    myenemy1.kill=enemy1;
    srand(time(0));                                          ///O functie ce va genera un numar aleatoriu

    int enemy1SPAWNpointX=myenemy1.x;
    enemy1SPAWNpointX=(rand()%18)+1;                         ///Genereaza un numar de la 0-18(unde se va plasa inamicul pe axa X) + 1.

    int enemy1SPAWNpointY=myenemy1.y;
    enemy1SPAWNpointY=(rand()%23)+1;                         ///Genereaza un numar de la 0-23(unde se va plasa inamicul pe axa Y) + 1.

    if(escapePLAN[enemy1SPAWNpointX][enemy1SPAWNpointY]!='#')            ///Conditie de a nu genera inamicul in peretii inchisorii('#') sau pe prizonier('@').
    {
        if(escapePLAN[enemy1SPAWNpointX][enemy1SPAWNpointY]!='@')
        {
            escapePLAN[enemy1SPAWNpointY][enemy1SPAWNpointX]=enemy1;
        }
    }
    return 0;
}

int spawnENEMY2()                                             ///O functie ce va genera primul tau tip de inamici
{
    anotherPrizonier myenemy2;
    myenemy2.block=enemy2;
    srand(time(0));                                          ///O functie ce va genera un numar aleatoriu

    int enemy2SPAWNpointX=myenemy2.x;
    enemy2SPAWNpointX=(rand()%18)+2;                         ///Genereaza un numar de la 0-18(unde se va plasa inamicul pe axa X) + 2.

    int enemy2SPAWNpointY=myenemy2.y;
    enemy2SPAWNpointY=(rand()%23)+2;                         ///Genereaza un numar de la 0-23(unde se va plasa inamicul pe axa Y) + 2.

    if(escapePLAN[enemy2SPAWNpointX][enemy2SPAWNpointY]!='#')            ///Conditie de a nu genera inamicul in peretii inchisorii('#') sau pe prizonier('@').
    {
        if(escapePLAN[enemy2SPAWNpointX][enemy2SPAWNpointY]!='@')
        {
            escapePLAN[enemy2SPAWNpointY][enemy2SPAWNpointX]=enemy2;
        }
    }
    return 0;
}

int spawnENEMY3()                                             ///O functie ce va genera primul tau tip de inamici
{
    Police myenemy3;
    myenemy3.restart=enemy3;
    srand(time(0));                                          ///O functie ce va genera un numar aleatoriu

    int enemy3SPAWNpointX=myenemy3.x;
    enemy3SPAWNpointX=(rand()%18)+3;                         ///Genereaza un numar de la 0-18(unde se va plasa inamicul pe axa X) + 3.

    int enemy3SPAWNpointY=myenemy3.y;
    enemy3SPAWNpointY=(rand()%23)+3;                         ///Genereaza un numar de la 0-23(unde se va plasa inamicul pe axa Y) + 3.

    if(escapePLAN[enemy3SPAWNpointX][enemy3SPAWNpointY]!='#')            ///Conditie de a nu genera inamicul in peretii inchisorii('#') sau pe prizonier('@').
    {
        if(escapePLAN[enemy3SPAWNpointX][enemy3SPAWNpointY]!='@')
        {
            escapePLAN[enemy3SPAWNpointY][enemy3SPAWNpointX]=enemy3;
        }
    }
    return 0;
}

int prizonierDIRECTION()
{
    int i;
    for(;;)
    {
        cin>>prizonierMOVEMENT;
        switch(prizonierMOVEMENT)
        {
            case 'w':                                                            ///Cazul in care este apasata tasta 'w'.
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy1)             ///Cazul in care intalneste vanatorul de recompense.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        for(i=0; i<6; i++)
                        {
                            cout<<"Ai fost asasinat!"<<'\n';
                            //delay(1);
                        }
                }
                if(escapePLAN[prizonierPOZx-1][prizonierPOZy]!='#')
                {
                    if(escapePLAN[prizonierPOZx-1][prizonierPOZy]!=enemy2)       ///Cazul in care intalneste un 'vechi prieten'.
                    {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZx--;
                    }
                }
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy3)             ///Cazul in care intalneste politistul.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZx=1;                                         ///Prizonierul va fi dus in celula si va incerca din nou sa evadeze.
                        prizonierPOZy=1;
                }
                break;

            case 's':                                                            ///Cazul in care este apasata tasta 'w'.
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy1)             ///Cazul in care intalneste vanatorul de recompense.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        for(;;)
                        {
                            cout<<"Ai fost asasinat!"<<'\n';
                            //delay(1);
                        }
                }
                if(escapePLAN[prizonierPOZx+1][prizonierPOZy]!='#')
                {
                    if(escapePLAN[prizonierPOZx+1][prizonierPOZy]!=enemy2)       ///Cazul in care intalneste un 'vechi prieten'.
                    {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZx++;
                    }
                }
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy3)             ///Cazul in care intalneste politistul.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZx=1;                                         ///Prizonierul va fi dus in celula si va incerca din nou sa evadeze.
                        prizonierPOZy=1;
                }
                break;

            case 'a':                                                            ///Cazul in care este apasata tasta 'w'.
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy1)             ///Cazul in care intalneste vanatorul de recompense.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        for(;;)
                        {
                            //cout<<"Ai fost asasinat!"<<'\n';
                            delay(1);
                        }
                }
                if(escapePLAN[prizonierPOZx][prizonierPOZy-1]!='#')
                {
                    if(escapePLAN[prizonierPOZx][prizonierPOZy-1]!=enemy2)       ///Cazul in care intalneste un 'vechi prieten'.
                    {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZy--;
                    }
                }
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy3)             ///Cazul in care intalneste politistul.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZx=1;                                         ///Prizonierul va fi dus in celula si va incerca din nou sa evadeze.
                        prizonierPOZy=1;
                }
                break;

            case 'd':                                                            ///Cazul in care este apasata tasta 'w'.
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy1)             ///Cazul in care intalneste vanatorul de recompense.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        for(;;)
                        {
                            cout<<"Ai fost asasinat!"<<'\n';
                            //delay(1);
                        }
                }
                if(escapePLAN[prizonierPOZx][prizonierPOZy+1]!='#')
                {
                    if(escapePLAN[prizonierPOZx][prizonierPOZy+1]!=enemy2)       ///Cazul in care intalneste un 'vechi prieten'.
                    {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZy++;
                    }
                }
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==enemy3)             ///Cazul in care intalneste politistul.
                {
                        escapePLAN[prizonierPOZx][prizonierPOZy]=' ';            ///Creeaza un spatiu unde sta prizonierul.
                        prizonierPOZx=1;                                         ///Prizonierul va fi dus in celula si va incerca din nou sa evadeze.
                        prizonierPOZy=1;
                }
                if(escapePLAN[prizonierPOZx][prizonierPOZy]==goal)
                {
                    for(;;)
                    {
                        cout<<"Ai evadat!!! =))"<<'\n';
                        //delay(1);
                    }
                }
                break;

            default:
            cout<<"Ai apasat butonul gresit!!!"<<'\n';
            break;
        }
    cout<<spawnENEMY1();
    cout<<spawnENEMY2();
    cout<<spawnENEMY3();
    refresescapePLAN();
    }
    return 0;
}

/*void delay(int secunde)
{
    int milisecunde=1000*secunde;
    clock_t goal=milisecunde+clock();
    while(goal>clock());
}*/

int main()
{
    cout<<'\n';
    cout<<'\n';
    cout<<'\n';
    cout<<'\n';
    cout<<'\n';

    cout<<"                                        Bun venit la evadarea din inchisoare!!!";
    cout<<'\n';
    cout<<'\n';
    cout<<"W:Deplasare in sus.";
    cout<<'\n';
    cout<<"A:Deplasare spre stanga.";
    cout<<'\n';
    cout<<"S:Deplasare in jos.";
    cout<<'\n';
    cout<<"D:Deplasare spre dreapta.";
    cout<<'\n';
    cout<<'\n';
    cout<<"Vei intalni pe parcursul evadarii tale urmatorii inamici:";
    cout<<'\n';
    //delay(5);
    cout<<"   -K(vanatorul de recompense):Fereste-te de acest inamic care a reusit sa se infiltreze in inchisoare pentru a te vana pentru recompensa frumoasa pusa pentru capul tau.Acesta iti va pune capat evadarii tale.";
    cout<<'\n';
    //delay(5);
    cout<<"   -F(vechi prieten):Fii cu ochii in patru pentru ca prietenii vor incerca sa-ti puna piedici blocandut-ti caile spre libertate.";
    cout<<'\n';
    //delay(5);
    cout<<"   -P(politistul):Ai grija sa nu te intalnesti cu politistul pentru ca altfel planul tau de evadare va fi un esec si vei fi dus din nou in celula de unde vei incerca o noua tentativa de evadare.";
    cout<<'\n';
    //delay(3);
    cout<<spawnENEMY1();
    cout<<spawnENEMY2();
    cout<<spawnENEMY3();
    refresescapePLAN();
    cout<<'\n';
    prizonierDIRECTION();
    return 0;
}
