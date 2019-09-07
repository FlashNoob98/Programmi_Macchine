/* Codice copiato dal file esercizio_01.cpp e adattato all'ultima richiesta dell'esercizio
 * per il calcolo del rendimento di un compressore commerciale
*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
//definizione variabili
float Cp = 1.005, Cv = 0.7179, K=Cp/Cv, R=Cp-Cv;
float T1,T2,P1,P2,V1,V2;
float L_is; //lavoro isoentropica
float L_ad; //lavoro reale
float n; //esponente politropica
float mass, volum, beta;
float eta_pc, eta_ad;

//chiamata funzioni
void startup();
void input();
void calcola_stato(float n);
void isoentropica();
void potenza_reale();
void rendimento();
void adiabatica_reale();
// float politropica();
// float isoterma();
void adiabatico_to_politropico();

//funzione main
int main(){
    startup();
    input();
    calcola_stato(K);
    //trasformo portata volumetrica in portata massica
    mass = volum/(60000*V1);
    cout << "Portata massica: " << mass*1000 <<" dm^3/s\n";
    isoentropica();
    potenza_reale();
    rendimento();
    adiabatico_to_politropico();
    cout << "Condizioni di uscita reali\n";
    calcola_stato(n);
    cout << endl;
    return 0;
}

//output all'avvio del programma
void startup(){
    //cout << "Hello world \n";
}

//richiesta dati
void input(){
    cout << "Inserisci la portata volumetrica (l/min)\n";
    cin >> volum;
    cout << "Inserisci la temperatura iniziale (in Celsius)\n";
    cin >> T1;
    T1 = T1 + 273.15; //è più comoda da inserire in °C
    cout << "Inserisci la pressione iniziale (in bar)\n";
    cin >> P1;
    cout << "Inserisci la pressione finale (in bar)\n";
    cin >> P2;
}

//calcoli
void calcola_stato(float n){
    //con n = 0 non funziona, va implementato if case(?)
    beta = P2/P1;
    //cout << beta << endl;
    V1 = R*T1/P1/100;
    V2 = V1/(pow(beta,(1/n)));
    T2 = P2*V2/R*100;
    int p=3; //imposta precisione tabella
    cout << endl;
    cout <<"Stato\t"<< "P(bar)\t" << "v(m^3/kg) " <<"T(°C)"<<endl;
    cout <<"1\t"<<P1<<'\t'<<setprecision(p)<<V1<<"\t  "<<T1-273.15 <<endl;
    cout <<"2\t"<<P2<<'\t'<<setprecision(p)<<V2<<"\t  "<<T2-273.15 <<endl<<endl;
}

void isoentropica(){
    /*isoentropica L=m\DeltaH=m*Cp*\Delta T*/
    L_is = mass*Cp*(T2-T1);
    //float L = -P1*V1*100/(K-1)*(pow(V1,1-K)- pow(V2,1-K));
    //float L = mass*Cp*(T2-T1);
    cout <<"Potenza necessaria per compressione adiabatica isoentropica: "<< L_is << " kW\n";
}

void potenza_reale(){
    L_ad = L_is -1;
    while (L_ad <= L_is){
        cout << "Inserisci il valore della potenza necessaria (in kW): ";
        cin >> L_ad;
        if (L_ad < L_is){
            cout << "Impossibile!\n";
        }
    }
}

void rendimento(){
    eta_ad = L_is/L_ad;
    cout << "Il rendimento adiabatico di compressione è: "<< eta_ad << endl;
}

void adiabatico_to_politropico(){
    cout << "\nCalcolo del rendimento politropico a partire da quello adiabatico\n";
    float eta = eta_ad; //il rendimento è già stato precedentemente calcolato
    // float n = -1/(log((eta - 1 + pow(beta,(K-1)/K))/(eta))/log(beta)-1);
    n = log(beta)/(log(beta)-log((eta-1+pow(beta,(K-1)/K))/(eta)));
    cout << "Il coefficiente n della politropica che passa per lo stato di uscita reale vale: " << n <<endl;
    float res = n*(K-1)/(K*(n-1));
    cout << "Il rendimento politropico vale: " << res << endl;
}
