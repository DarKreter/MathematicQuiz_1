#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    string linia;
    fstream plik;
    int licznik = 0;float suma_pkt = 0;
    vector <string> pytania, odpA, odpB, odpC, odpD, popodp;
    plik.open("bin/debug/quiz",ios::in);
    while(getline(plik,linia))
    {
        if(licznik % 6 == 0)
        {
            pytania.push_back(linia);
        }
        else if(licznik % 6 == 1)
        {
            odpA.push_back(linia);
        }
        else if(licznik % 6 == 2)
        {
            odpB.push_back(linia);
        }
        else if(licznik % 6 == 3)
        {
            odpC.push_back(linia);
        }
        else if(licznik % 6 == 4)
        {
            odpD.push_back(linia);
        }
        else if(licznik % 6 == 5)
        {
            popodp.push_back(linia);
        }
        licznik ++ ;
    }
    plik.close();
    bool powtorka = false;
    powtarzamy:
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);  ///Zmiana koloru pisania na jasna zielen
    cout << (powtorka == true ? "A czy teraz jestes w stanie rozpoczac quiz ?":"Czy jestes gotow rozpoczac guiz? (by rozpoczac wpisz \"tak\")") << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xB);  ///Zmiana koloru pisania na blekitny
    getline(cin,linia);
    transform(linia.begin(), linia.end(), linia. begin(), ::tolower);
    if(linia != "tak")
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);  ///Zmiana koloru pisania na jasna zielen
        cout << "Rozumiem, ze jeszcze nie jestes w gotow/a\n";
        powtorka = true;
        goto powtarzamy;
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);  ///Zmiana koloru pisania na jasna zielen
        cout << "Startujemy";
        for(int i = 0;i<3;i++)
        {
            cout << ".";
            Sleep(700);
        }
        int nr; int tab[pytania.size()], tablica[pytania.size() * 3];

        for(int i = 0; i < pytania.size();i++)
        {

            tab[i] = 1;
        }
        for(int i = 0; i < pytania.size() * 3;i = i +3)
        {
            tablica[i] = -5;
        }
        int x = pytania.size(), numer = 0;

        for(int i = 0;i<pytania.size();i++)
        {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);  ///Zmiana koloru pisania na jasna zielen
            tutaj:
            nr = rand() % x;
            if(tab[nr] == 0)
            {
                //cout << nr<<"\n";
                goto tutaj;
            }
            //cout << nr << endl;
            tab[nr] = 0;
            cout << "Pytanie "<<i + 1<< ". "<< pytania[nr]<< endl;
            cout << "A) " << odpA[nr] <<endl;
            cout << "B) " << odpB[nr] <<endl;
            cout << "C) " << odpC[nr] <<endl;
            cout << "D) " << odpD[nr] <<endl;
            wrocmy_sie:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xB);  ///Zmiana koloru pisania na blekitny
            getline(cin , linia);
            transform(linia.begin(),linia.end(),linia.begin(),::tolower);  ///Zmieniamy
            if(linia != "a" && linia != "b" && linia != "c" && linia != "d")
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);  ///Zmiana koloru pisania na jasna zielen
                cout << "Nie ma takiej odpowiedzi w opcjach! Podaj poprawna odpowiedz: ";
                goto wrocmy_sie;
            }
            if(linia == popodp[nr])  suma_pkt ++;
            else
            {
                tablica[numer] = nr;
                if(popodp[nr] == "a")tablica[numer + 1] = 1;
                else if(popodp[nr] == "b")tablica[numer + 1] = 2;
                else if(popodp[nr] == "c")tablica[numer + 1] = 3;
                else if(popodp[nr] == "d")tablica[numer + 1] = 4;
                if(linia == "a") tablica[numer + 2] = 1;
                else if(linia == "b") tablica[numer + 2] = 2;
                else if(linia == "c") tablica[numer + 2] = 3;
                else if(linia == "d") tablica[numer + 2] = 4;
                numer = numer + 3;
            }
        }
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);  ///Zmiana koloru pisania na jasna zielen
        cout << "Gratuluje, uzyskales: " <<(suma_pkt / pytania.size()) * 100<<"% czyli "<< suma_pkt << " pkt na max. " << pytania.size() << "\n";
        bool pierwszy_raz = 0;
        for(int i = 0;i < pytania.size() * 3; i = i + 3)
        {
            if(tablica[i] == -5)continue;
            else
            {
                cout << "\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
                cout << (pierwszy_raz == 0 ? "Popelniles blad w zadaniach: \n" : "")
                     << pytania[tablica[i]]
                     << endl;
                if(tablica[i + 1] == 1)   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
                else if(tablica[i + 2] == 1)    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
                cout << "A) " << odpA[tablica[i]] << endl;
                if(tablica[i + 1] == 2)   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
                else if(tablica[i + 2] == 2)    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
                else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
                cout << "B) " << odpB[tablica[i]] << endl;
                if(tablica[i + 1] == 3)   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
                else if(tablica[i + 2] == 3)    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
                else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
                cout << "C) " << odpC[tablica[i]] << endl;
                if(tablica[i + 1] == 4)   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
                else if(tablica[i + 2] == 4)    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
                else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
                cout << "D) " <<odpD[tablica[i]] << endl;
                pierwszy_raz = 1;
            }
        }
        for(;;)
        {
            Sleep(10000);
        }
    }
    return 0;
}
