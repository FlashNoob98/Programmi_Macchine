/* calcolatore renimenti
*
*/

#include <iostream> //input-output
#include <cmath>    //comandi matematici avanzati
#include <iomanip>  //precisione decimali

using namespace std;
float portata,potere_cal;
float P_el;

int main(){
    cout << "Inserisci portata massica combustibile (t/h): ";
    cin >> portata;
    portata = portata/3.6;
    cout << "Inserisci potere calorifico inferiore (MJ/kg): ";
    cin >> potere_cal;
    cout << "Inserisci potenza elettrica netta generata (MW): ";
    cin >> P_el;
    cout << "Il rendimento globale elettrico è: "<< setprecision(3)<<P_el/(portata*potere_cal)*1000 <<endl;
    return 0;
}
