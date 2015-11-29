#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

void euler_forward(double Y1[], double Y2[], int N, double dt){
string word = "euler_forward";
string word2 = ".txt";
if(dt==M_PI/10)
	word2 = "_pi_10.txt";
if(dt==M_PI/100)
    word2 = "_pi_100.txt";
word += word2;
ofstream out(word.c_str());

for(int i=0 ; i<N-1 ; i++ ){
	Y1[i+1] =  Y2[i]*dt + Y1[i];
	Y2[i+1] = -Y1[i]*dt + Y2[i];
	out << Y1[i+1] << endl;
}
}

void euler_backward(double Y1[], double Y2[], int N, double dt){
string word = "euler_backward";
string word2 = ".txt";
if(dt==M_PI/10)
	word2 = "_pi_10.txt";
if(dt==M_PI/100)
    word2 = "_pi_100.txt";
word += word2;
ofstream out(word.c_str());

for(int i=0 ; i<N-1 ; i++ ){
	Y1[i+1] = (Y1[i]+Y2[i]*dt) / (1+dt*dt);
	Y2[i+1] = Y2[i] - Y1[i+1]*dt;
	// Es waere auch moeglich gewesen:
	// Y2[i+1] = (Y2[i]-Y1[i]*dt) / (1+dt*dt);
	// Jedoch haben wir bereits Y[i+1] ermittelt!
	out << Y1[i+1] << endl;
}
out.close();
}

void analytical(double Y1[], int N, double dt){
ofstream out("analytical.txt");
// Nach https://www.wolframalpha.com/input/?i=x%27%27%28t%29%2Bx%28t%29%3D0+and+x%280%29%3D1+and+x%27%280%29%3D0
// ist die Loesung der DGL
// x(t) = cos(t)
for(int i=0 ; i<N ; i++ ){
	Y1[i] =  cos(i*dt);
	out << Y1[i] << endl;
}
out.close();
}

int main(){
double dt_1 = M_PI/10;
double dt_2 = M_PI/100;
double T_end = 20*M_PI;
int N = int(T_end/dt_2)+1;

// Ich erstelle mit dem kleineren dt
// (und daraus resultierendem groesseren N)
// die Arrays, damit ich diese nur einmal kreieren brauch.
// Es stoert ja nicht, dass diese beim ersten Durchlauf
// nicht bis zum Ende benutzt werden.
double* Y1 = new double [N];
double* Y2 = new double [N];

Y1[0] = 1;
Y2[0] = 0;

N = int(T_end/dt_1)+1;
euler_forward(Y1, Y2, N, dt_1);
euler_backward(Y1, Y2, N, dt_1);

N = int(T_end/dt_2)+1;
euler_forward(Y1, Y2, N, dt_2);
euler_backward(Y1, Y2, N, dt_2);
// Fuer die analytische Loesung verwende
// ich den Speicherplatz von Array Y1
analytical(Y1, N, dt_2);

delete[] Y1;
delete[] Y2;

return 0;
}
