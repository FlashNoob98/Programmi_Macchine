// commento
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

float P1,P2,T1,T2,v1,v2;
float k = 1.4,R=0.287;

void input_dati(){
    cout << "Inserisci la pressione di ristagno (bar): ";
    cin >> P1;
    cout << "Inserisci la temperatura di ristagno (K): ";
    cin >> T1;
    cout << "Inserisci la pressione ambiente (bar): ";
    cin >> P2;
}

float calcolo_T2(float beta, float T, float k){
    float T2 = T*pow(beta,(1-k)/k);
    return T2;
}

float calcolo_v(float p, float T){
    return R*T/p/100;
}

int main(){
    input_dati();
    T2 = calcolo_T2(P1/P2,T1,k);
    //cout << "La temperatura in uscita dalla turbina è :" << T2 << " K\n";
    v1 = calcolo_v(P1,T1);
    v2 = calcolo_v(P2,T2);
    float pr = 4; //precisione decimale
    cout <<"Stato\t"<< "P(bar)\t" << "v(m^3/kg) " <<"T(°C)"<<endl;
    cout <<"1\t"<<P1<<'\t'<<setprecision(pr)<<v1<<"\t  "<<T1-273.15 <<endl;
    cout <<"2\t"<<P2<<'\t'<<setprecision(pr)<<v2<<"\t  "<<T2-273.15 <<endl<<endl;

    return 0;
}
