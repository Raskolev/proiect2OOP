#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
fstream f("graf.txt");
int MA[10][10];
int m,n,i,j;
int sf;
int sol[10];
void shift_right(int poz)  //face un loc liber in  vectorul sol
// pe pozitia sol[poz], luand  la dreapta cu un loc
//restul sirului cuprins intre poz si sf
{
    sf++;
    for(int i=sf; i>poz; i--)
        sol[i]=sol[i-1];
}
void citeste()
{
//citesc numarul de noduri n
    f>>n;
//initializez matricea de adiacenta cu 0
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            MA[i][j]=0;

//citesc muchiile din fisierul de intrare graf.txt
    while(!f.eof())
    {
        int m=0;//numar cate muchii are graful
        f>>i>>j;//citesc muchia
        MA[i][j]=MA[j][i]=1;
        if(MA[i][j]==1)
            m++;
//completez matricea de adiacenta cu valori de 1 acolo unde exista muchii
    }
}

void matrice_adiacenta()
{
    int i,j;
    cout<<"Matricea de adiacenta este:"<<endl;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            cout<<MA[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

//Un graf este complet daca numarul de muchii este egal cu n*(n-1)/2
void graf_complet()
{
    if(m==n*(n-1)/2)
        cout<<"Graful este complet";
    else
        cout<<"Graful nu este complet";
    cout<<endl;
}

void muchii_lipsa()
{
//parcurg matricea de adiacenta de deasupra diagonalei principale
    cout<<"Muchiile care lipsesc pentru ca graful sa devina complet sunt: "<<endl;
    for(i=1; i<=n-1; i++)
        for(j=i+1; j<=n; j++)
            if(MA[i][j]==0)
                cout<<i<<" "<<j<<endl;


}
int main()
{
    f>>n;
    while(f>>i>>j)
        MA[i][j]=1;
    sol[1]=1;
    sf=1;
    for(int p=2; p<=n; p++)
    {
        //testez situatia 1: exista arc de la nodul p la sol[1],
        //nodul p  se insereaza la inceputul lui sol
        if(MA[p][sol[1]]==1)
        {
            shift_right(1);
            sol[1]=p;
        }
        //testez situatia 2: exista arc de la ultimul nod din sol catre nodul p
        //nodul p se insereaza in urma ultimului nod din sol
        else if(MA[sol[sf]][p]==1)
        {
            sf++;
            sol[sf]=p;
        }
        //daca nu suntem nici in situatia 1, nici in situatia 2,
        //rezulta ca suntem in situatia 3, in care se va cauta o succesiune de doua noduri
        //in vectorul sol, care au sagetile opuse, intre care
        //se va intercala nodul p.
        else
        {
            bool gasit=false;
            for(int i=2; i<=sf&&!gasit; i++)
            {
                //testam sensul sagetii dintre doua noduri sucesive si nodul de inserat p
                if(MA[sol[i-1]][p]==1&&MA[p][sol[i]]==1)
                {
                    //am gasit doua noduri cu arce de sens opus
                    //nodul p se va insera intre ele
                    shift_right(i);
                    sol[i]=p;
                    gasit=true;
                }
            }
        }
    }
    citeste();
    matrice_adiacenta();
    graf_complet();
    muchii_lipsa();
    cout<<"\n";

    //afisare lant
    cout<<"Fiind dat un graf turneu, se cere sa se afiseze un drum elementar care trece prin toate varfurile grafului: \n";
    for(int i=1; i<=n; i++)
        cout<<sol[i]<<" ";
    return 0;
    f.close();
}


