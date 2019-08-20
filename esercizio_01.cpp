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
void calcola_stato(float n);
float isoentropica();
float adiabatica_reale();
float politropica();

//funzione main
int main(){
    //cout << R <<endl;
    startup();
    input();
    calcola_stato(K);
    //isoentropica();
    float gamma = adiabatica_reale();
    cout << "\nCalcolo ora lo stato utilizzando l'esponente della politropica:\n";
    calcola_stato(gamma);

    politropica();
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
void calcola_stato(float n){
    beta = P2/P1;
    //cout << beta << endl;
    V1 = R*T1/P1/100;
    V2 = V1/(pow(beta,(1/n)));
    cout <<"V1 e V2 = "<< V1 << "  " << V2 <<" m^3/kg"<<endl;
    T2 = P2*V2/R*100;
    cout <<"T2 = "<< T2-273.15 <<" °C\n" ;
}

float isoentropica(){
    /*isoentropica L=m\DeltaH=m*Cp*\Delta T*/
    float L = mass*Cp*(T2-T1);
    return L;
}

float adiabatica_reale(){
    float L_is = isoentropica();
    cout <<"Lavoro necessario per compressione adiabatica isoentropica: "<< L_is << " kJ\n";
    cout << "Inserisci il valore del rendimento politropico per il calcolo dell'adiabtica reale\n";
    cin >> eta_pc;
    eta_ad = (1-pow(beta,((K-1)/K)))/(1-pow(beta,((K-1)/(K*eta_pc))));
    cout << "Rendimento adiabatico: " << eta_ad << endl;
    float L_ad = L_is/eta_ad;
    cout << "Lavoro necessario alla trasformazione adiabatica reale: " << L_ad <<" kJ\n";
    //calcolo esponente politropica
    float n = eta_pc/(eta_pc -((K-1)/K));
    cout <<"Calcolo dell'esponente della politropica: " << n << endl;
    //facoltativa la seguente
    //cout << "Altra formula per il calcolo del lavoro: "<< mass*Cp*T1*(pow(beta,((n-1)/n))-1) << " kJ\n";
    return n;
}

float politropica(){
    //il nuovo calcolo della funzione isoentropica() viene eseguito sulla seconda condizione termodinamica
    //rappresenta quindi il lavoro della adiabatica reale e non della isoentropica
    float L_ad = isoentropica();
    float L_pc = L_ad*eta_pc;
    cout << "Lavoro necessario alla trasformazione politropica: " << L_pc << " kJ\n";
    cout << "Calore necessario alla trasformazione politropica (positivo entrante): " << L_ad-L_pc << " kJ\n";
return 0;
}