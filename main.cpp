#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
#include<string.h>
#include <assert.h>
#include <stdlib.h>
using namespace std;
typedef struct persoana
{
    char *nume,*prenume,*nrtel;
    struct persoana *urm;
} nod;

const char fisier[] = "agenda.txt";

nod *adauga(nod*&prim,char *nume,char *prenume,char *nrtel)
{
    nod *q,*p;
    p=(nod*)malloc(sizeof(nod));
    p->nume=(char*)malloc(strlen(nume)+1);
    p->prenume=(char*)malloc(strlen(prenume)+1);
    p->nrtel=(char*)malloc(strlen(nrtel)+1);
    strcpy(p->nume,nume);
    strcpy(p->prenume,prenume);
    strcpy(p->nrtel,nrtel);
    p->urm=NULL;
    if(p==NULL || p->nume==NULL)
    {
        cout<<"Eroare la alocare!";
        exit(0);
    }
    if(p==NULL || p->prenume==NULL)
    {
        cout<<"Eroare la alocare!";
        exit(0);
    }
    if(p==NULL || p->nrtel==NULL)
    {
        cout<<"Eroare la alocare!";
        exit(0);
    }
    if(prim==NULL)
        return p;
    else if(strcmp(prim->nume,p->nume)>0)
    {
        p->urm=prim;
        return p;
    }
    else
    {
        q=prim;
        while(q->urm!=NULL && strcmp(q->urm->nume,p->nume)<0)
            q=q->urm;
        p->urm=q->urm;
        q->urm=p;
        return prim;
    }
}
void afisare(nod *prim)
{
    nod *q;
    q=prim;
    while(q!=NULL)
    {
        cout<<q->nume<<" "<<q->prenume<<" "<<q->nrtel<<"\n";
        q=q->urm;
    }
}
void cautare(nod *prim,char *nume)
{
    nod *q;
    q=prim;
    while(q!=NULL && strcmp(q->nume,nume)!=0)
        q=q->urm;
    while(q!=NULL && strcmp(q->nume,nume)==0)
    {
        cout<<q->nume<<" "<<q->prenume<<" "<<q->nrtel<<"\n";
        q=q->urm;
    }
}
nod* stergere(nod *prim,char *nume,char *prenume)
{
    nod *q,*p;
    if(prim!=NULL)
    {
        if(strcmp(prim->nume,nume)==0&&strcmp(prim->prenume,prenume)==0)
        {
            q=prim;
            prim=prim->urm;
            free(q->nume);
            free(q->prenume);
            free(q->nrtel);
            free(q);
            return prim;
        }
        q=prim;
        while(q->urm!=NULL && strcmp(q->urm->nume,nume)!=0 && strcmp(q->urm->prenume,prenume)!=0)
            q=q->urm;
        if(q->urm!=NULL && strcmp(q->urm->nume,nume)==0 && strcmp(q->urm->prenume,prenume)==0)
        {
            p=q->urm;
            q->urm=q->urm->urm;
            free(p->nume);
            free(p->prenume);
            free(p->nrtel);
            free(p);
        }
        return prim;
    }
    else
        return prim;
}

int nr_persoane(nod *prim)
{
    if(prim!=NULL)
    {
        return nr_persoane(prim->urm)+1;
    }
    //return 0;
}

void cautare_persoana(nod *prim,char *nume,char *prenume,char *nrtel,bool &ok)
{
    nod *q;
    char n[30], p[30], t[30];
    if(prim!=NULL){
        if(strcmp(prim->nume,nume)==0&& strcmp(prim->prenume,prenume)==0&& strcmp(prim->nrtel,nrtel)==0){
            //cout<<prim->nume<<" "<<prim->prenume<<"\n";
            printf("Schimbari\n");
            printf("Numele:");
            cin >> ws;
            cin.getline(n,30);
            printf("Preumele:");
            cin>>p;
            printf("numar telefon:");
            cin>>t;
            strcpy(prim->nume,n);
            strcpy(prim->prenume,p);
            strcpy(prim->nrtel,t);
            ok=1;
            return ;
        }
        cautare_persoana(prim->urm,nume,prenume,nrtel,ok);
    }
}
void afisare_persoane_nr_tel(nod *prim,char *pref)
{
    if(prim!=NULL){
        if(strncmp(prim->nrtel,pref,strlen(pref))==0)
            cout<<prim->nume<<" "<<prim->prenume<<" "<<prim->nrtel<<"\n";
        afisare_persoane_nr_tel(prim->urm,pref);
    }

}
nod* cautare_numar_tel(nod *prim,char *nrtel)
{
    nod *q;
    q=prim;
    while(q!=NULL && strcmp(q->nrtel,nrtel)!=0)
        q=q->urm;
    return q;
}
void ordonare_nume(nod* prim)
{
    nod* c;

    int ord;
    do
    {
        c=prim;
        ord=1;
        while(c->urm)
        {
            if(strcmp(c->nume,c->urm->nume)>0)
            {
                char numm[30],prenumm[30],nrtt[30];
                strcpy(numm,c->nume);
                strcpy(c->nume,c->urm->nume);
                strcpy(c->urm->nume,numm);
                strcpy(prenumm,c->prenume);
                strcpy(c->prenume,c->urm->prenume);
                strcpy(c->urm->prenume,prenumm);
                strcpy(nrtt,c->nrtel);
                strcpy(c->nrtel,c->urm->nrtel);
                strcpy(c->urm->nrtel,nrtt);
                ord=0;
            }
            c=c->urm;
        }
    }
    while(ord==0);
}
void ordonare_prenume(nod* prim)
{
    nod* c;
    int ord;
    do
    {
        c=prim;
        ord=1;
        while(c->urm!=NULL)
        {
            if(strcmp(c->nume,c->urm->nume)==0&&strcmp(c->prenume,c->urm->prenume)>0)
            {
                char numm[30],prenumm[30],nrtt[30];
                strcpy(numm,c->nume);
                strcpy(c->nume,c->urm->nume);
                strcpy(c->urm->nume,numm);
                strcpy(prenumm,c->prenume);
                strcpy(c->prenume,c->urm->prenume);
                strcpy(c->urm->prenume,prenumm);
                strcpy(nrtt,c->nrtel);
                strcpy(c->nrtel,c->urm->nrtel);
                strcpy(c->urm->nrtel,nrtt);
                ord=0;
            }
            c=c->urm;
        }
    }
    while(ord==0);
}
void initializare_lista(nod* &prim)
{
    ifstream in(fisier);
    //s = new nod;
    prim=NULL;
    //nod *u = prim;
    char nume[30],prenume[30],numar_telefon[30];
    while (in >> nume)
    {
        in.get();
        in.get(prenume, 30);
        in.get();
        in.get(numar_telefon, 30);
        //cout<<nume<<" "<<prenume<<" "<<numar_telefon<<"\n";
        prim=adauga(prim, nume,prenume,numar_telefon);
    }
    in.close();
}
void salvare_lista(nod *prim)
{
    ofstream out(fisier);
    for (nod *q = prim; q != NULL; q = q->urm)
    {
        out << q->nume << "\n";
        out << q->prenume << "\n";
        out << q->nrtel << "\n";
    }
    out.close();
}
int main()
{
    int opt;
    nod *prim,*p;
    char nume[30],prenume[30],numar_telefon[30],pref[30],num[30],prenum[30],numar_telefo[30];
    //prim=NULL;
    initializare_lista(prim);
    while(opt!=0)
    {
        //system("cls");///curata consola windows  system("clear"); //For Linux
        printf("\n0. Iesire");
        printf("\n1. Introducerea unei persoane");
        printf("\n2. Afisarea alfabetica a persoanelor introduse");
        printf("\n3. Cautarea unei persoane dupa nume si afiseaza persoanele in ordine alfabetica");
        printf("\n4. Stergerea unei persoane");
        printf("\n5. Cautarea unei persoane dupa numar de telefon");
        printf("\n6. Introducerea unei persoane cu pastrarea alfabetica");
        printf("\n7. afisarea persoanelor cu prefix identic citit de la tastatura");
        printf("\n8. modificarea unei persoane");
        printf("\n9. numar de contacte\n");
        cin>>opt;
        //fflush(stdin);
        if(opt==1)
        {
            printf("Numele:");
            cin >> ws;
            cin.getline(nume,30);
            printf("Preumele:");
            cin>>prenume;
            printf("numar telefon:");
            cin>>numar_telefon;
            prim=adauga(prim,nume,prenume,numar_telefon);
        }
        if(opt==2)
        {
            ordonare_nume(prim);
            ordonare_prenume(prim);
            afisare(prim);
        }
        if(opt==3)
        {
            ordonare_nume(prim);
            ordonare_prenume(prim);
            printf("Introduceti numele persoanei cautat:");
            cin >> ws;
            cin.getline(nume,30);
            cautare(prim,nume);
        }
        if(opt==4)
        {
            printf("Introduceti numele persoanei:");
            cin >> ws;
            cin.getline(nume,30);
            printf("Introduceti prenumele persoanei:");
            cin>>prenume;
            prim=stergere(prim,nume,prenume);
            ///afisare(prim);
        }
        if(opt==5)
        {
            printf("Introduceti numarul de telefon persoanei:");
            cin >> ws;
            cin.getline(numar_telefon,30);
            p=cautare_numar_tel(prim,numar_telefon);
            if(p==NULL)
                cout<<"NU exista\n";
            else
                cout<<p->nume<<" "<<p->prenume<<"\n";
        }
        if(opt==6)
        {
            printf("Numele:");
            cin >> ws;
            cin.getline(nume,30);
            printf("Preumele:");
            cin>>prenume;
            printf("numar telefon:");
            cin>>numar_telefon;
            prim=adauga(prim,nume,prenume,numar_telefon);
            ordonare_nume(prim);
            ordonare_prenume(prim);
            afisare(prim);
        }
        if(opt==7)
        {
            printf("Introduceti prefix numar de telefon:");
            cin >> ws;
            cin.getline(pref,30);
            afisare_persoane_nr_tel(prim,pref);
        }
        if(opt==8)
        {
            printf("Introduceti numele persoanei:");
            cin >> ws;
            cin.getline(nume,30);
            printf("Introduceti prenumele persoanei:");
            cin>>prenume;
            printf("Introduceti prenumele numar telefon:");
            cin>>numar_telefon;
            //cout<<prim->nume<<" "<<prim->prenume<<" "<<prim->nrtel;
            bool ok=0;
            cautare_persoana(prim,nume,prenume,numar_telefon,ok);
            //afisare(prim);
            if(ok==0)
                cout<<"Studentul nu se gaseste in lista!\n";
        }
        if(opt==9)
        {
            printf("\n numar de contacte:");
            cout<<nr_persoane(prim)<<"\n";
        }
        if(opt>9||opt<0)
        {
            cout<<"1..9!\n";
        }
        //getch();
    }
    salvare_lista(prim);
    return 0;
}
