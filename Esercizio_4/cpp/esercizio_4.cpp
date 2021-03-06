// commento
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define PI 3.14159265
float P1,P2,T1,T2,v1,v2;
float k = 1.4,R=0.287,Cp=1.005;
float dHstar,c_1,c_2,alpha;
float r, Tmedia,beta_parziale;
float T0,TB,T1star; //condizioni di ristagno

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
    return Cp*(t1-t2)*1000;
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
    cout << "L'entalpia disponibile è: "<< dHstar/1000 << " kJ/kg\n";
    c_1 = c1(dHstar,0);
    cout << "Velocità c_1 per stadio ad azione: " << c_1 << " m/s\n";
    cout << "Velocità tangenziale u del rotore: " << u(alpha,c_1) << " m/s\n";
    c_2 = vel_uscita(alpha,c_1);
    cout << "Velocità assiale in uscita c_2: " << c_2 << " m/s\n";
    cout << "Lavoro ottenuto: " << work(c_2,dHstar)/1000 << " kJ/kg\n";
    cout << "Rendimento massimo a " << alpha << "° : " << eta_max(alpha) << endl;
    //cout << "Rendimento effettivo: " << work(c_2,dHstar)/dHstar << endl;
    T0 = ((1000*Cp*T1)-((c_2*c_2)/2))/(1000*Cp);
    cout << "Temperatura T0 all'ingresso dello statore: " << T0-273.15 << " °C\n"; 
    cout << "Pressione p0 all'ingresso dello statore: " << P1*pow((T0/T1),k/(k-1)) << " bar\n";
    TB = ((1000*Cp*T2)+((c_2*c_2)/2))/(1000*Cp);
    cout << "Temperatura TB di ristagno: " << TB-273.15 << " °C\n"; 

    cout << "\nCalcolo stadio a reazione!\n\n";
    cout << "Inserisci il grado di reazione (0~1): ";
    cin >> r;
    c_1 = c1(dHstar,r);
    cout << "Velocità c_1 per stadio a reazione: " << c_1 << " m/s\n";
    cout << "Velocità tangenziale u del rotore: " << u(alpha,c_1)*2 << " m/s\n";
    cout << "Rendimento massimo a " << alpha << "° : " << eta_reazione(alpha) << endl<<endl;
    Tmedia = T1-(pow(c_1,2)/(2*Cp*1000));
    cout << "Temperatura intermedia: " << Tmedia-273.15 <<" °C\n";
    float P_parz = P1*pow((Tmedia/T1),k/(k-1));
    cout << "Pressione parziale: " << P_parz << " bar\n";
    c_2 = vel_uscita(alpha,c_1);
    cout << "Velocità assiale in uscita c_2: " << c_2 << " m/s\n";
    T0 = ((1000*Cp*T1)-((c_2*c_2)/2))/(1000*Cp);
    cout << "Temperatura T0 all'ingresso dello statore: " << T0-273.15 << " °C\n"; 
    cout << "Pressione p0 all'ingresso dello statore: " << P1*pow((T0/T1),k/(k-1)) << " bar\n";
    TB = ((1000*Cp*T2)+((c_2*c_2)/2))/(1000*Cp);
    cout << "Temperatura TB di ristagno: " << TB-273.15 << " °C\n";
    // le seguenti righe non producono alcuna informazione utile :)
    // T1star = Tmedia + (pow(c_1,2)/(2*Cp*1000));
    // cout <<"Temperatura di ristagno intermedia: " << T1star-273.15 << " °C\n";
    // cout << "Pressione di ristagno intermedia: " << P_parz*pow(T1star/Tmedia,k/(k-1)) << " bar\n";
    return 0;
}
