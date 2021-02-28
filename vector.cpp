#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <random>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


struct Studentas
{
    string vardas, pavarde;
    vector<int> namudarbai;
    int ND, egz_pazymys;
    double galutinis_pazymys;
};


bool isdigits(string &str)
{    return std::all_of(str.begin(), str.end(), ::isdigit);     }


void NamuDarbai(bool PazymiuSkaicius, Studentas& Studentas){
    bool run = true;
    string pazymys;
    if (PazymiuSkaicius)
    {
        for (int i = 0; i < Studentas.ND; i++)
        {
            do {
                cout << Studentas.namudarbai.size() + 1 << " -ojo pazymio ivestis ";
                cin >> pazymys;
                if  (isdigits(pazymys) && std::stoi(pazymys) <= 10 && std::stoi(pazymys) > 0 )
                {
                    Studentas.namudarbai.push_back(std::stoi(pazymys));
                    run = false;
                }
                else
                {
                    cout << "Ivestas klaidingas pazymys" << endl;
                    run = true;
                }
            }
            while(run);
        }
    }
else
{
        cout << endl << "Iveskite pazymius:" << endl;
        cout << "Norint baigti pazymiu ivedima, iveskite '0' " << endl;
        do {
            cout << Studentas.namudarbai.size() + 1 << " -ojo pazymio ivestis ";
            cin >> pazymys;
            if  (isdigits(pazymys) && std::stoi(pazymys) <= 10 && std::stoi(pazymys) > 0 )
            {
                Studentas.namudarbai.push_back(std::stoi(pazymys));
            }
            else if (pazymys == "0")
            {
                Studentas.ND = Studentas.namudarbai.size();
                Studentas.namudarbai.shrink_to_fit();
                run = false;
            }
            else
            {
                    cout << "Įvestas neteisingas pazymys!" << endl;
            }

            if (Studentas.namudarbai.empty() && pazymys == "end")
            {
                cout << "Įveskite bent vieną pažymį!" << endl;
                run = true;
            }
        }
        while (run);
    }
}
   

bool validateName(string name){
    for (char i : name)
    {
        if (!isalpha(i))
        {
            cout << "Vardo įvedimui naudokite tik raides!" << endl;
            cout << "Įveskite vardą iš naujo ";

            return false;
        }
    }
    return true;
}


string getDigits(){
    bool valid;
    string number;
    do {
        cin >> number;
        cout << endl;
            if (!isdigits(number))
            {
                cout << "Pazymio ivedimui naudokite tik teigiamus skaicius!" << endl;
                cout << "Iveskite pazymi is naujo ";
                valid = false;
            }
            else
            {
                valid = true;
            }
        }
    while(!valid);

    return number;
}

int egzaminas(){
    int pazymys;
    bool valid = false;
    do
    {
        pazymys = std::stoi(getDigits());
        if (pazymys > 10 || pazymys <=0)
        {
            cout << "Egzamino pažymys įvestas neteisingai!" << endl;
            cout << "Įveskite egzamino pažymį iš naujo ";
        }
        else
        {
            valid = true;
        }
    }
    while(!valid);

    return pazymys;
}

void randomgrades(bool PazymiuSkaicius, Studentas& Studentas){
    using chronoClock = std::chrono::high_resolution_clock;
    unsigned seed = static_cast<long unsigned int> (chronoClock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(1, 10);

    if (!PazymiuSkaicius)
    {
        std::uniform_int_distribution<int> distributionSize(1, 15);
        Studentas.ND = distributionSize(generator);
    }

    cout << "Atsitiktinai sugeneruoti " << Studentas.ND << " namu darbu pazymiai:  ";
    for (int i = 0 ; i < Studentas.ND ; i++ )
    {
        Studentas.namudarbai.push_back(distribution(generator));
        cout << Studentas.namudarbai[i] << " ";
    }
    Studentas.egz_pazymys = distribution(generator);
    cout << endl << "Sugeneruotas egzamino pazymys:  " << Studentas.egz_pazymys << endl << endl;

}



void galutinis(vector<Studentas>& group, int n){
    double vidurkis;
    for (int i=0; i<n; i++)
    {
        vidurkis = 0;
        for (int j=0; j<group[i].ND; j++)
        {
            vidurkis = vidurkis + group[i].namudarbai[j];
        }
        vidurkis = vidurkis / group[i].ND;
        group[i].galutinis_pazymys = (vidurkis*0.4) + (group[i].egz_pazymys*0.6);
    }
}

void mediana(vector<Studentas>& group, int n){
    double mediana;
    for (int i=0; i<n; i++)
    {
        std::sort(group[i].namudarbai.begin(), group[i].namudarbai.end());
        mediana = group[i].namudarbai[(group[i].ND/2)];
        if (group[i].ND%2 == 0)
        {
            mediana = (mediana + group[i].namudarbai[(group[i].ND/2)-1]) / 2;
        }
        group[i].galutinis_pazymys = (mediana*0.4) + (group[i].egz_pazymys*0.6);
    }
}

void print(vector<Studentas>& group, int n, bool ismediana){
    cout << endl;
    if (ismediana)
    {
        cout << "Vardas              Pavarde              Mediana" << endl;
        cout << "----------------------------------------------------------" << endl;
        for (int i=0; i<n; i++)
        {
            cout << std::setprecision(2)<< std::fixed << group[i].vardas << string (20-group[i].vardas.length(), ' ')
                 << group[i].pavarde << string (21-group[i].pavarde.length(), ' ')  << group[i].galutinis_pazymys << endl;
        }
    }
    else
    {
        cout << "Vardas              Pavarde              Vidurkis" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (int i=0; i<n; i++)
        {
            cout << std::setprecision(2) << std::fixed <<group[i].vardas << string (20-group[i].vardas.length(), ' ')
                 << group[i].pavarde << string (21-group[i].pavarde.length(), ' ')  << group[i].galutinis_pazymys << endl;
        }
    }
}

int main()  {
    vector<Studentas> group;
    int n;                  
    bool run = true;        
    bool PazymiuSkaicius;       

    cout << "Iveskite studentu skaiciu:   ";
    n = std::stoi(getDigits());

    for (int i=0; i<n; i++)
    {
        group.push_back(Studentas());

        cout << "Iveskite studento varda:   ";
        do {
           cin >> group[i].vardas;
           cout << endl;
        }
        while(!validateName(group[i].vardas));

        cout << "Iveskite studento pavarde:   ";
        do{
            cin >> group[i].pavarde;
            cout << endl;
        }
        while(!validateName(group[i].pavarde));

        string atsakymas_pazymiai;
        cout << "Ar zinomas studento pazymiu kiekis? Jei taip, spauskite 't', jei ne, spauskite 'n' ";
        do{
            cin >> atsakymas_pazymiai;
            if (atsakymas_pazymiai == "t" || atsakymas_pazymiai == "T")
            {
                int temp;
                cout << "Iveskite pazymiu kieki:   ";
                do {
                    temp = std::stoi(getDigits());
                    if (temp > 0)
                    {
                        group[i].ND = temp;
                        run = false;
                    }
                    else
                    {
                        cout << "Ivestas negalimas pazymiu kiekis" << endl << "Iveskite is naujo: ";
                        run = true;
                    }
                }
                while(run);
                PazymiuSkaicius = true;
            }
            else if (atsakymas_pazymiai == "n" || atsakymas_pazymiai == "N")
            {
                cout << endl;
                PazymiuSkaicius = false;
                run = false;
            }
            else
            {
                cout << endl;
                cout << "Klaidingas ivedimas" << endl;
                cout << "Iveskite is naujo:   ";
                run = true;
            }
        }
        while(run);

        string atsakymas_rng;
        cout <<"Ar pazymius generuoti atsitiktiniu budu? Jei taip, spauskite 't', jei ne, spauskite 'n' ";
        do {
            cin >> atsakymas_rng;
            if (atsakymas_rng == "t" || atsakymas_rng == "T")
            {
                cout << endl;
                randomgrades(PazymiuSkaicius,group[i]);
                run = false;
            }
            else if (atsakymas_rng == "n" || atsakymas_rng == "N")
            {
                NamuDarbai(PazymiuSkaicius, group[i]);
                cout << endl <<"Iveskite egzamino pazymi:   ";
                group[i].egz_pazymys = egzaminas();
                run = false;
            }
            else
            {
            cout << endl;
            cout << "Pazymys ivestas neteisingai" << endl;
            cout << "Iveskite is naujo:   ";
            run = true;
            }
        }
        while(run);
    }
    group.shrink_to_fit();

    string atsakymas_mediana;
    cout << "Ar norite rezultata matyti mediana? Jei taip, spauskite 't', jei ne, spauskite 'n' ";
    do{
        cin >> atsakymas_mediana;
        if (atsakymas_mediana == "t" || atsakymas_mediana == "T")
        {
            mediana(group, n);
            print(group, n, true);
            run = false;
        }
        else if (atsakymas_mediana == "n" || atsakymas_mediana == "N")
        {
            galutinis(group, n);
            print(group, n, false);
            run = false;
        }
        else
        {
            cout << endl;
            cout << "Ivesta neteisingai!" << endl;
            cout << "Iveskite is naujo:   ";
            run = true;
        }
    }
    while(run);
}
