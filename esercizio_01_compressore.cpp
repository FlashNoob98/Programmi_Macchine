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
float mass, beta;
float lavoro, calore;
float eta_pc, eta_ad;

//chiamata funzioni
void startup();
void input();
void calcola_stato(float n);
void isoentropica();
float adiabatica_reale();
float politropica();
float isoterma();
void adiabatico_politropico();

//funzione main
int main(){
    //cout << R <<endl;
    startup();
    input();
    calcola_stato(K);
    isoentropica();
   // float gamma = adiabatica_reale();
   // cout << "\nCalcolo ora lo stato utilizzando l'esponente della politropica:\n";
   // calcola_stato(gamma);

    //politropica();
//
    //isoterma();
    //adiabatico_politropico();
    cout << endl;
    return 0;
}

//output all'avvio del programma
void startup(){

    //cout << "Hello world \n";
}

//richiesta dati
void input(){
    cout << "Inserisci la portata massica (Kg/s)\n";
    cin >> mass;
    cout << "Inserisci la temperatura iniziale (in Kelvin)\n";
    cin >> T1;
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