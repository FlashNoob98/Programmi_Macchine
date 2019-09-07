/* Programma per il calcolo dei valori caratteristici di un impianto semplice con turbina a gas
 * Fornito senza alcuna garanzia e per uso non professionale, libera la copia, la modifica e la ridistribuzione
 * Scritto da Olivieri Daniele
 */
#include <iostream>
#include <cmath>
using namespace std;
float T2,T3=0,P2,P3,P4;  //Valori dell'acqua
float Beta,Eta_globale,mdot,power,T4; //Parametri impianto
float T1=15,P1=1,k=1.4,mass=28.96,Cp=1.005; //atmosfera ISO
float lambda=(k-1)/k,Eta_pe,Eta_pc,Tmax=(1600+273);
float Hi,mdotc; //potere calorifico e portata massica carburante
float DeltaT;


void schema(){
	cout << "Questo è un calcolatore dei valori caratteristici"<<endl;
	cout << "di un impianto con turbina a Gas semplice"<<endl;
	cout<<endl;
	cout<<"        --→→--(CC)--→→--     " << endl;
	cout<<"       |(2)          (3)|    " << endl;
	cout<<"       |                |    " << endl;
	cout<<"    |\\ |                | /|      ___" << endl;
	cout<<"    | \\|                |/ |     /" << endl;
	cout<<"    |C |================|TG|==(∼)---- " << endl;
	cout<<"    | /                  \\ |     \\___" << endl;
	cout<<"    |/                    \\| " << endl;
	cout<<"    |                      | " << endl;
	cout<<"    ↑                      ↓ " << endl;
	cout<<"    ↑(1)                (4)↓ " << endl;
	cout<<"    |                      | " << endl<<endl;
}

void input(){
	char ans='N';
	cout << "Questo programma utilizza i valori dell'atmosfera ICAO"<<endl;
	cout << "Desideri modificarli? (s/N) ";
	ans = getchar();
	if ((ans == 's') || (ans =='S')){ //parametri atmosfera ISO (facoltativo)
		cout<<"Inserisci il valore di T1 ("<<T1<<" °C): ";
		cin>>T1;
		cout<<"Inserisci il valore di P1 ("<<P1<<" atm): ";
		cin>>P1;
		cout<<"Fattore di espansione isoentropico k ("<<k<<" gas biatomici): ";
		cin>>k;
		cout<<"Inserisci la massa molare ("<<mass<<" kg/kmol): ";
		cin>>mass;
		cout<<"Inserisci il Cp: ("<<Cp<<" kJ/(kg*K)): ";
		cin>>Cp;
	}
	cout<<"Utilizzerò i seguenti valori: \nT1 = "<<T1<<"°C \nP1 = "<<P1<<" atm \nk = "<<k<<"  \nmassa molare = "<<mass<<" kg/kmol \nCp = "<<Cp<<" kJ/(kg*K)"<<endl;
	cout<<endl<<"Ora devi inserire tutti i parametri della macchina"<<endl; //Parametri impianto
	cout<<"Potenza (kW): "; cin >> power;
	cout<<"Efficienza (%): "; cin >> Eta_globale; Eta_globale=Eta_globale/100;
	cout<<"Rapporto di compressione beta: "; cin >> Beta;
	cout<<"Portata massica (kg/s): "; cin>>mdot;
	cout<<"Temperatura in uscita dalla turbina T4 (°C): "; cin>>T4;
}	

void calcolo_P2(){
	P2=Beta*P1;
}

void calcolo_mcomb(){ //calcolo portata combustibile
	cout<<"Inserisci il potere calorifico inferiore (MJ/kg): ";
	cin>>Hi; Hi=Hi*1000; //trasformo in kJ
	mdotc=power/(Eta_globale*Hi); //portata combustibile in kg/s
}

void deltaT(){
	DeltaT = Hi*mdotc/(mdot*Cp)*0.99; //0.99 supposto il rendimento di combustione
	cout << "La variazione di temperatura subita in camera di combustione è di: " << DeltaT <<" K \n";
}

void calc(){

	// double A,B;
	Eta_pe=1;
	Eta_pc =1;
	// //cout<<T4<<" "<<T1<<endl;
	 do{
	 	T3=(T4+273.15)*(pow(Beta,(lambda/Eta_pe)));
	 	//Eta_pc=Eta_pe-0.01; //rendimento politropico di espansione e compressione	
	 	T2=(T1+273.15)*(pow(Beta,(lambda/Eta_pc)));
	// 	A=mdot*Cp*T2+mdotc*Hi;
	// 	B=(mdot+mdotc)*Cp*T3;
	// 	cout<<"T3= "<<T3-273.15<<" test T2 = "<<T2-273.15<<"  "<<Eta_pc<<" "<<Eta_pe<<endl;
		Eta_pc=Eta_pc - 0.001;
		Eta_pe = Eta_pc -0.002;
	//	getchar();
	}while((T3-T2) > DeltaT);
	 cout<<"Eta_pe = "<<Eta_pe+0.001<<" \nEta_pc = "<<Eta_pc+0.001<<" \nT2 = "<<T2-273.15<<" °C\nT3 = "<<T3-273.15<<" °C\n";
}

void calcolo_T3(){

	do {
		Eta_pe=Eta_pe+0.001;
		T3=(T4+273)*pow(Beta,(lambda/Eta_pe));
		
		cout<<(T3-273)<<" °C"<<endl;
	} while ((T3>=Tmax) && (Eta_pe<1));
	cout<<Eta_pe<<endl;
}

int main(){
	schema();
	input();
	calcolo_P2();
	//cout <<P2;
	lambda=(k-1)/k;
	calcolo_mcomb();
	cout<<mdotc<<" kg/s di combustibile"<<endl;
	deltaT();
	calc();
	//calcolo_T3();
	//cout<<T3<<endl;
	return 0;
}
