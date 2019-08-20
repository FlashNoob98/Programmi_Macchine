/*Calcolatore compressione aria secca
 * PV=RT
*/

#include <iostream>
#include <cmath>

using namespace std;
//definizione variabili
float Cp = 1.005, Cv = 0.7179, K=Cp/Cv, R=Cp-Cv;
float T1,T2,P1,P2,V1,V2;
float mass, beta;
float lavoro, calore;
float eta_pc, eta_ad;

//chiamata funzioni
void startup();
void input();
void calcola_stato();
float isoentropica();
float adiabatica_reale();

//funzione main
int main(){
    //cout << R <<endl;
    startup();
    input();
    calcola_stato();
    //isoentropica();
    adiabatica_reale();
    //cout << "Hello world \n";
    cout << endl;
    return 0;
}

//output all'avvio del programma
void startup(){

    //cout << "Hello world \n";
}

//richiesta dati
void input(){
    cout << "Inserisci la massa (Kg)\n";
    cin >> mass;
    cout << "Inserisci la temperatura iniziale (in Kelvin)\n";
    cin >> T1;
    cout << "Inserisci la pressione iniziale (in bar)\n";
    cin >> P1;
    cout << "Inserisci la pressione finale (in bar)\n";
    cin >> P2;
}

//calcoli
void calcola_stato(){
    beta = P2/P1;
    //cout << beta << endl;
    V1 = R*T1/P1/100;
    V2 = V1/(pow(beta,(1/K)));
    cout <<"V1 e V2 = "<< V1 << "  " << V2 <<" m^3/kg"<<endl;
    T2 = P2*V2/R*100;
    cout <<"T2 = "<< T2-273.15 <<" °C\n" ;
}

float isoentropica(){
    /*isoentropica L=m\DeltaH=m*Cp*\Delta T*/
    float L = mass*Cp*(T2-T1);
    cout <<"Lavoro necessario per compressione adiabatica isoentropica: "<< L << " kJ\n";
    return L;
}

float adiabatica_reale(){
    float Lis = isoentropica();
    cout << "Inserisci il valore del rendimento politropico per il calcolo dell'adiaabtica reale\n";
    cin >> eta_pc;
    eta_ad = (1-pow(beta,((K-1)/K)))/(1-pow(beta,((K-1)/(K*eta_pc))));
    cout << "Rendimento adiabatico: " << eta_ad << endl;
    float Lad = Lis/eta_ad;
    cout << "Lavoro necessario alla trasformazione adiabatica reale: " << Lad <<" kJ\n";
    return Lad;
}