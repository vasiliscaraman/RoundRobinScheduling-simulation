#include<iostream>
#include<cstring>
#include<string.h>
using namespace std;

int timpfinal=0,cuantum;

struct Nod{
	char nume[100];
	int timpPornire;
    int durataExecutie;
    int finalizat;
    int asteptare=0;
	Nod * urm=NULL;
};

Nod *prim = NULL;

void Afisare(Nod *prim){
    cout<<"~~~~~Procesele: "<<endl;
    Nod *el=prim;
    cout<<"Nume: "<<el->nume<<"   "<<"Timp de sosire: "<<el->timpPornire<<"   "<<"Durata de executie: "<<el->durataExecutie<<endl;
    el=el->urm;
	while(el!=prim){
	 cout<<"Nume: "<<el->nume<<"   "<<"Timp de sosire: "<<el->timpPornire<<"   "<<"Durata de executie: "<<el->durataExecutie<<endl;
	 el=el->urm;
    }
}

void adaugareFinal(Nod *&prim,char *nume,int timpPornire,int durataExecutie){
	Nod *el=new Nod;
	strcpy(el->nume,nume);
	el->timpPornire=timpPornire;
	el->durataExecutie=durataExecutie;
	el->finalizat=0;
	if(prim!=NULL){
        el->urm=prim;
	}else el->urm=NULL;

	if(prim==NULL)
	  prim=el;
	else
	{
		Nod *list=prim;
		if(list->urm==NULL)
            list->urm=el;
        else{
            list=list->urm;
            while(list->urm!=prim){
                list=list->urm;
            }
        }
        list->urm=el;
	}
}

void stergereElement(Nod * el)
{
	Nod * elSterg=el->urm;
	el->urm=el->urm->urm;
	delete elSterg;
}

void stergElemNume (Nod *&el,char *nume)
{
    Nod *element=el;
    element=element->urm;
    while(element->urm!=prim)
        element=element->urm;
    if (strcmp(el->nume,nume)==0)
    {
        Nod *elSterg=el;
        el=el->urm;
        element->urm=el;
        delete elSterg;
    }
    Nod *elem=el;
    if (strcmp(elem->nume,nume)==0)
    {
        Nod *elSterg=elem;
        elem=elem->urm;
        delete elSterg;
    }
    while (elem->urm!=prim&&strcmp(elem->urm->nume,nume)!=0)
    {
        elem=elem->urm;
    }
    if(elem->urm!=prim)
        stergereElement(elem);
}

int verificFinalizat(Nod *prim)
{
    Nod *el=prim;
    if (el->finalizat==0)
        return 0;
    el=el->urm;
    while(el!=prim){
        if(el->finalizat==0)
            return 0;
        el=el->urm;
    }
    return 1;
}

void StatiLaRand(Nod *&prim, int timp)
{
    Nod *el=prim;
    if(timp>=el->timpPornire&&el->asteptare!=0){
        el->asteptare-=1;
    }
    if(timp<el->timpPornire&&el->asteptare==0){
        el->asteptare==3*cuantum;
    }
    el=el->urm;
    while(el!=prim)
    {
        if(timp>=el->timpPornire&&el->asteptare!=0){
            el->asteptare-=1;
        }
        if(timp<el->timpPornire&&el->asteptare==0){
            el->asteptare==3*cuantum;
        }
        el=el->urm;
    }
}

void RoundRobin(Nod *&prim)
{
    int timp=0;
    int etapa=1;
    cout<<endl<<"Procesele initial: "<<endl;
    Afisare(prim);
    cout<<endl<<"Se vor afisa procesele dupa fiecare etapa a executiei:"<<endl;
    while(verificFinalizat(prim)==0)
    {
        Nod * el=prim;
        if(el->timpPornire<=timp&&el->finalizat==0&&el->asteptare==0){
            cout<<"~~~~~Etapa "<<etapa<<endl;
            etapa++;
            if(el->durataExecutie-cuantum<=0){
                el->finalizat=1;
            }
            if(el->durataExecutie-cuantum>=0){
                timpfinal+=cuantum;
                timp+=cuantum;
            }
            if(el->durataExecutie<cuantum){
                timpfinal+=el->durataExecutie;
                timp+=el->durataExecutie;
            }
            el->durataExecutie-=cuantum;
            StatiLaRand(prim,timp);
            Afisare(prim);
            cout<<"     -Timp final de executie curent: "<<timpfinal<<"-"<<endl<<endl;
        }
        el=el->urm;
        while(el!=prim){
            if(el->timpPornire<=timp&&el->finalizat==0&&el->asteptare==0){
                cout<<"~~~~~Etapa "<<etapa<<endl;
                etapa++;
                if(el->durataExecutie-cuantum<=0){
                    el->finalizat=1;
                }
                if(el->durataExecutie-cuantum>=0){
                    timpfinal+=cuantum;
                    timp+=cuantum;
                }
                if(el->durataExecutie<cuantum){
                    timpfinal+=el->durataExecutie;
                    timp+=el->durataExecutie;
                }
                el->durataExecutie-=cuantum;
                Afisare(prim);
                cout<<"     -Timp final de executie curent: "<<timpfinal<<"-"<<endl<<endl;
            }
            el=el->urm;
        }
        timp++;
    }

}

int main()
{
    char optiune[25],nume[100];
    int timpPornire, durataExecutie;
    cout<<"Introduceti cuantum: ";
    cin>>cuantum;
    cout<<endl<<"Pentru a introduce primul element al listei, introduceti:"<<endl;
    cout<<"Numele primului element: ";
    cin>>nume;
    cout<<"Momentul in timp in care porneste procesarea primului element: ";
    cin>>timpPornire;
    cout<<"Cat timp ii este necesar primului element pentru a fi procesat complet: ";
    cin>>durataExecutie; cout<<endl;
    adaugareFinal(prim,nume,timpPornire,durataExecutie);

    cout<<"Introduceti una dintre urmatoarele comenzi: adaugare, stergere, afisare, start, exit."<<endl;
    while(strcmp(optiune,"stop")!=0){
        cin>>optiune;cout<<endl;
        if(strcmp(optiune,"adaugare")==0)
        {
            cout<<"Introduceti numele elementului nou: "; cin>>nume;
            cout<<"Introduceti momentul in care ii va porni procesarea: "; cin>>timpPornire;
            cout<<"Introduceti timpul necesar pentru o procesare completa: "; cin>>durataExecutie;
            adaugareFinal(prim,nume,timpPornire,durataExecutie);
        }
        if(strcmp(optiune,"stergere")==0)
        {
            cout<<"Introduceti numele elementului pe care doriti sa il stergeti: "; cin>>nume;
            stergElemNume(prim,nume);
        }
        if(strcmp(optiune,"afisare")==0)
        {
            Afisare(prim);
        }
        if(strcmp(optiune,"start")==0)
        {
            cout<<endl<<endl<<endl<<endl<<"           ROUND ROBIN:            "<<endl<<endl;
            RoundRobin(prim);
        }
        if(strcmp(optiune,"exit")==0)
        {
            cout<<"Iesire din program"<<endl<<"."<<endl<<"."<<endl<<".";
            break;
        }
        cout<<endl<<"Introduceti o noua comanda: "<<endl;
    }

    return 0;
}
