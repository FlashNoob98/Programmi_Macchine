// commento
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define PI 3.14159265
#define e 2.71828
float P1,P2,T1,T2,v1,v2;
float k = 1.4,R=0.287,Cp=1.005;
float dHstar,c_1,c_2,alpha;
float r, Tmedia,beta_parziale;

void input_dati(){
    cout << "Inserisci la pressione di ristagno (bar): ";
    cin >> P1;
    cout << "Inserisci la temperatura di ristagno (K): ";
    cin >> T1;
    cout << "Inserisci la pressione ambiente (bar): ";
    cin >> P2;
    cout << "Inserisci l'angolo alpha1 (gradi): ";
    cin >> alpha;
}

float calcolo_T2(float beta, float T, float k){
    float T2 = T*pow(beta,(1-k)/k);
    return T2;
}

float calcolo_v(float p, float T){
    return R*T/p/100;
}

float entalpia_disp(float t1,float t2){
    return Cp*(t1-t2);
}

float c1(float H,float r){
    return pow(2*H*(1-r),0.5);
}

float u(float angolo,float c){
    return c*cos(angolo*PI/180)/2;
}

float eta_max(float angolo){
    return pow(cos(angolo*PI/180),2);
}

float vel_uscita(float angolo, float c){
    return c*sin(angolo*PI/180);
}

float work(float vel,float H){
    return H-(pow(vel,2)/2);
}

float eta_reazione(float angolo){
    return 2*pow(cos(angolo*PI/180),2)/(1+pow(cos(angolo*PI/180),2));
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
    dHstar = entalpia_disp(T1,T2);
    cout << "L'entalpia disponibile è: "<< dHstar << " kJ/kg\n";
    c_1 = c1(dHstar,0);
    cout << "Velocità c_1 per stadio ad azione: " << c_1 << " m/s\n";
    cout << "Velocità tangenziale u del rotore: " << u(alpha,c_1) << " m/s\n";
    c_2 = vel_uscita(alpha,c_1);
    cout << "Velocità assiale in uscita c_2: " << c_2 << " m/s\n";
    cout << "Lavoro ottenuto: " << work(c_2,dHstar) << " kJ/kg\n";
    cout << "Rendimento massimo a " << alpha << "° : " << eta_max(alpha) << endl<<endl;
    //cout << "Rendimento effettivo: " << work(c_2,dHstar)/dHstar << endl;
    cout << "Calcolo stadio a reazione!\n\n";
    cout << "Inserisci il grado di reazione (0~1): ";
    cin >> r;
    c_1 = c1(dHstar,r);
    cout << "Velocità c_1 per stadio a reazione: " << c_1 << " m/s\n";
    cout << "Velocità tangenziale u del rotore: " << u(alpha,c_1)*2 << " m/s\n";
    cout << "Rendimento massimo a " << alpha << "° : " << eta_reazione(alpha) << endl<<endl;
    Tmedia = T1-(pow(c_1,2)/(2*Cp));
    cout << "Temperatura intermedia: " << Tmedia-273.15 <<" °C\n";
    beta_parziale = pow(e,Cp/R*log(T1/Tmedia));
    cout << "Pressione parziale: " << P1/beta_parziale << " bar\n";
    return 0;
}
