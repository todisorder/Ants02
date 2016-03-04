# include <fstream>
# include "stdlib.h"
# include <iostream>
# include <cmath>
# include <string>
#include <sstream>
#include <iomanip> 
#include <random>

using namespace std;

#include "matriz.h"
#include "vector.h"


//static double const Pi = 3.14159;
static double const Pi =  3.1415926535;
static double const Ln2 = 0.6931471806;

default_random_engine generator;
normal_distribution<double> Normal(0.,.5);      //Normal(0.,1.)
//http://www.cplusplus.com/reference/random/normal_distribution/
// Normal(mean,stddev)
// Usage:
// double number = Normal(generator);
static double const Turn_off_random = .01;
//  ^^^ 0. = No Random!

//	Parameter for Regularizing Function
static double const RegularizingEpsilon = 0.01;


//////////////////////////////////////////////////////
// Ant parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//  Time scale t_hat em segundos
static double const t_hat_in_seconds = 1.;

//  Space scale X_hat em centimetros
static double const X_hat_in_cm = 1.73;

//  Relaxation time tau em segundos:
static double const tau = .5;         //    0.5

//  Nondimensional relaxation TAU = (t_hat / tau)^(-1).
//  Deve ser o relaxation time nas unidades t_hat.
//  Na equa��o deve aparecer 1/TAU.
static double const TAU = tau / t_hat_in_seconds;         //

//  Sensing area radius em centimetros
static double const SensingAreaRadius = .4;         //  .5

//  Sensing area radius em X_hat
static double const SENSING_AREA_RADIUS = SensingAreaRadius / X_hat_in_cm;         //

//  Sensing Area Half Angle
static double const SensingAreaHalfAngle = Pi/3.;         //

//  Converter quantidade de feromona numa taxa (velocidade sem espa�o). Lambda � 1/(feromona * tempo).
//  A quantidade padr�o de feromona d� uma taxa de Lambda / t_hat.
//  Por exemplo, se quando deteta uma quantidade de feromona = 1 ela anda a 2 * X_hat por t_hat, ent�o
//  Lambda seria 2 * (3/2) * (sen theta * ell(em X_hat)^3)^(-1),
//  para que a Velocidade Desejada seja 2. X_hat/t_hat.
//static double const Lambda = .5* (3./2.) *(1./(sin(SensingAreaHalfAngle) * pow(SENSING_AREA_RADIUS,3.)));        //

//  Lambda versao sem sin():
//static double const Lambda = .5* (3./2.) *(1./(1. * pow(SENSING_AREA_RADIUS,3.)));        //

//  Lambda versao s� com a media do integral
//static double const Lambda = .5* (3./2.) *(1./(SensingAreaHalfAngle * pow(SENSING_AREA_RADIUS,3.)));        //

//	With Weber's Law, Lambda may be ~ 1 ??
static double const Lambda = 1.;         //10./SENSING_AREA_RADIUS;????

//////////////////////////////////////////////////////
// End Ant parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// tempo final
//static double const TFINAL = 0.1;
static double const delta_t = 0.1;   //     0.005


////////////////////////////
//  Defini��o do  Dom�nio
////////////////////////////
// extremo inferior do intervalo em x (cm)
static double const x_1_cm = -50.;

// extremo superior do intervalo em x (cm)
static double const x_2_cm = 50.;

// extremo inferior do intervalo em y (cm)
static double const y_1_cm =  -50.;

// extremo superior do intervalo em y (cm)
static double const y_2_cm = 50.;

// extremo inferior do intervalo em x
static double const x_1 = x_1_cm / X_hat_in_cm;

// extremo superior do intervalo em x
static double const x_2 = x_2_cm / X_hat_in_cm;

// extremo inferior do intervalo em y
static double const y_1 = y_1_cm / X_hat_in_cm;

// extremo superior do intervalo em y
static double const y_2 = y_2_cm / X_hat_in_cm;

////////////////////////////
// End Defini��o do  Dom�nio
////////////////////////////

////////////////////////////
// Parametro tempor�rio para a pheromone
////////////////////////////
static double const PheroNarrow = 1.;
static double const PheroHigh = 1.;
////////////////////////////
// End Parametro tempor�rio para a pheromone
////////////////////////////

////////////////////////////
// Parametro S� para os plots n�o ficarem
//  com um risco do lado ao outro
//  quando muda de lado por periodicidade
////////////////////////////
int ChangedSide = 0;




/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Position
//  http://stackoverflow.com/questions/10959694/why-does-call-by-value-example-not-modify-input-parameter
//  Preciso do & sen�o n�o muda o valor!
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void InitialPosition (double& Xini, double& Yini)
{
    Xini = -1.;     //-1.
    Yini = 0.;      //0.
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Position
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Velocity
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void InitialVelocity (double& Vx, double& Vy)
{
    Vx = .1;
    Vy = .2;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Velocity
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Fcs �teis
/////////////////////////////////////////////////
/////////////////////////////////////////////////


double PartePositiva(double aa){
    
    return max(aa,0.);
}

double ParteNegativa(double aa){
    
    return - min(aa,0.);
}

//  cf. http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
double Sinal(double aa){
    if (aa > 0.) return 1.;
    if (aa < 0.) return -1.;
    return 0.;
}


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Define Pheromone
//      Definida como fun��o de (x,y), tenho de dar uma
//      f�rmula expl�cita!
//      Mais tarde, ser� num�rico e vou precisar de interpola��es, etc.
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double PheromoneConcentration (double Xpos, double Ypos)
{
    double aux = 0.;
    
    aux = 1.*exp(-PheroNarrow*abs(Xpos));
    
    return aux;

}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Define Pheromone
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Define Pheromone Gradient X
//      Definida como fun��o de (x,y), tenho de dar uma
//      f�rmula expl�cita!
//      Mais tarde, ser� num�rico e vou precisar de interpola��es, etc.
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double PheromoneGradientX (double Xpos, double Ypos)
{
    double aux = 0.;
    
    aux = - 1.*PheroNarrow*Sinal(Xpos)*exp(-PheroNarrow*abs(Xpos));
    
    return aux;
    
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Define Pheromone Gradient X
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Define Pheromone Gradient Y
//      Definida como fun��o de (x,y), tenho de dar uma
//      f�rmula expl�cita!
//      Mais tarde, ser� num�rico e vou precisar de interpola��es, etc.
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double PheromoneGradientY (double Xpos, double Ypos)
{
    double aux = 0.;
    
    return aux;
    
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Define Pheromone Gradient Y
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Norma de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double Norm(double X, double Y)
{
    double aux =  sqrt(X*X + Y*Y);
    if (aux <= .000001) {
        return .000001;
    } else {
        return aux;
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Norma de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Theta de vetor  http://en.cppreference.com/w/cpp/numeric/math/atan2
//      Cuidado que atan2 est� entre -Pi/2 e Pi/2,
//      mas acho que isso n�o tem influencia porque
//      eu s� calculo senos e cosenos do angulo,
//      que dariam a mesma coisa se fosse em (0, 2Pi).
//      CUIDADO Usage: atan2(Y,X) = arctan(Y/X) !!!!
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double Angle(double X, double Y)
{
    double aux =  atan2(Y,X);
    return aux;
    
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Theta de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Radius de vetor  http://en.cppreference.com/w/cpp/numeric/math/hypot
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double Radius(double X, double Y)
{
    double aux =  hypot(X,Y);
    return aux;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Radius de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      Regularizing Function
/////////////////////////////////////////////////
/////////////////////////////////////////////////
double RegularizingFunction(double X)
{
    double aux =  pow(RegularizingEpsilon*RegularizingEpsilon
				+X*X,0.5);
    return aux;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//      End Radius de vetor
/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//       Define Force X,Y coordinates
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

double ForceX(double AntXpos,double  AntYpos,double  AntVelX, double  AntVelY)
{
    double aux;
	double auxX;
    double N = Norm(AntVelX,AntVelY);
    
    double A11 = sin(2.*SensingAreaHalfAngle)/2.
    * cos(2.*Angle(AntVelX,AntVelY));
    
    double A12 = sin(2.*SensingAreaHalfAngle)/2.
    * sin(2.*Angle(AntVelX,AntVelY));
    
    
    aux = (2./3.) * pow(SENSING_AREA_RADIUS,3.) * Lambda * cos(Angle(AntVelX,AntVelY))
    * PheromoneConcentration(AntXpos,AntYpos) * sin(SensingAreaHalfAngle)
    + (1./4.)*pow(SENSING_AREA_RADIUS,4.) * Lambda
    * (SensingAreaHalfAngle * PheromoneGradientX(AntXpos,AntYpos)
       + A11 * PheromoneGradientX(AntXpos,AntYpos) + A12 * PheromoneGradientY(AntXpos,AntYpos))
    ;
    
	auxX = PheromoneConcentration(AntXpos,AntYpos)*SENSING_AREA_RADIUS*SENSING_AREA_RADIUS
		* SensingAreaHalfAngle 
        + PheromoneGradientX(AntXpos,AntYpos) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
        * cos(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle)
        + PheromoneGradientY(AntXpos,AntYpos) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
        * sin(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle);
	
	auxX = RegularizingFunction(auxX);
	
	aux = aux/auxX;


//    cout << "PheromoneConcentration="<<PheromoneConcentration(AntXpos,AntYpos) << endl;
//    cout << "A11="<<A11 << endl;
//    cout << "A12="<<A12 << endl;
//    cout << "ForceX="<<aux << endl;
    
    return 1.*aux;
}

double ForceY(double AntXpos,double  AntYpos,double  AntVelX, double  AntVelY)
{
    double aux;
    double auxY;
    double N = Norm(AntVelX,AntVelY);
    
    double A22 = - sin(2.*SensingAreaHalfAngle)/2.
    * cos(2.*Angle(AntVelX,AntVelY));
    
    double A21 = sin(2.*SensingAreaHalfAngle)/2.
    * sin(2.*Angle(AntVelX,AntVelY));

    
    aux = (2./3.) *  pow(SENSING_AREA_RADIUS,3.) * Lambda * sin(Angle(AntVelX,AntVelY))
    * PheromoneConcentration(AntXpos,AntYpos) * sin(SensingAreaHalfAngle)
    + (1./4.)*pow(SENSING_AREA_RADIUS,4.) * Lambda
    * (SensingAreaHalfAngle * PheromoneGradientY(AntXpos,AntYpos)
       + A21 * PheromoneGradientX(AntXpos,AntYpos) + A22 * PheromoneGradientY(AntXpos,AntYpos))
    ;
    
    auxY = PheromoneConcentration(AntXpos,AntYpos)*SENSING_AREA_RADIUS*SENSING_AREA_RADIUS
    * SensingAreaHalfAngle
    + PheromoneGradientX(AntXpos,AntYpos) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
    * cos(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle)
    + PheromoneGradientY(AntXpos,AntYpos) * (2./3.) * pow(SENSING_AREA_RADIUS,3.)
    * sin(Angle(AntVelX,AntVelY)) * sin(SensingAreaHalfAngle);
	
	auxY = RegularizingFunction(auxY);
	
	aux = aux/auxY;


//    cout << "ForceY="<<aux << endl;
//    cout << "A22="<<A22 << endl;
//    cout << "A21="<<A21 << endl;
//    cout << "Grad X = "<<PheromoneGradientX(AntXpos,AntYpos) << endl;
//    cout << "Grad Y = "<<PheromoneGradientY(AntXpos,AntYpos) << endl;
    
    return 1.*aux;
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//       End Define Force X,Y coordinates
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// Fncs para calcular gradientes, divergencia, Laplaciano, m�todo upwiwnd
//
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
double Dmais(double dx,double uj, double ujj){
    
    return (ujj - uj)/dx;
}


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// End Fncs para calcular gradientes, divergencia, Laplaciano, m�todo upwiwnd
//
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// Print Info
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void PrintInfo(double delta_t, string COMM, int tt){
    
    ofstream tempfile;
    tempfile.open("DataUsed.txt");
    string tempinfo;
    
    tempfile << "#############################################################"<<endl;
    tempfile << "#############################################################"<<endl;
    tempfile << "#############################################################"<<endl;
    tempfile <<"# dt = "<< delta_t<< endl;
    tempfile <<"#" << "\t" << COMM <<endl;
    tempfile <<"#" << "Iter: " << tt <<endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "Space scale X_hat_in_cm (cm)       " << X_hat_in_cm << endl;
    tempfile << "Time scale t_hat_in_seconds (sec)       " << t_hat_in_seconds << endl;
    tempfile << "Sensing Area Radius (cm)       " << SensingAreaRadius << endl;
    tempfile << "Sensing Area Radius (X_hat)    " << SENSING_AREA_RADIUS << endl;
    tempfile << "Sensing Half Angle             Pi/" << Pi/SensingAreaHalfAngle << endl;
    tempfile << "Lambda                         " << Lambda << endl;
    tempfile << "------------------------------------------------------" << endl;
    tempfile << "delta t (seconds) = " << delta_t * t_hat_in_seconds << endl;
    tempfile << "Tfinal (seconds) = " << tt*delta_t * t_hat_in_seconds << endl;
    tempfile << "Tfinal (minutes) = " << tt*delta_t * t_hat_in_seconds / 60.<< endl;
    tempfile << "Tfinal (hours) = " << tt*delta_t * t_hat_in_seconds / 3600.<< endl;
    tempfile << "------------------------------------------------------" << endl;
    
    tempfile << " " << endl;
    
    tempfile.close();
    
    system("cp DataUsed.txt temp1.txt");
//    system("cat LogsLast.txt >> LogsData.txt");
    
    ifstream tempfile1;
    tempfile1.open("temp1.txt");
    
    while (getline(tempfile1, tempinfo,'\n'))
    {
        cout << tempinfo << endl;
    }
    
    tempfile1.close();
    
    system("rm temp1.txt");
    
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// End Print Info
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////





////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//                              ////////////////////////
// M�todo propriamente dito     ////////////////////////
//                              ////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//  http://stackoverflow.com/questions/10959694/why-does-call-by-value-example-not-modify-input-parameter
//  Preciso do & sen�o n�o muda o valor!
////////////////////////////////////////////////////////
void AntWalk (int tt, int icurrent, double& AntXposOld, double& AntYposOld, double& AntVelXOld, double& AntVelYOld)
{

    // amplitude dos subintervalos em tempo
    double tfinal;
    //    double delta_t;
    tfinal = delta_t * tt;
    //    delta_t = tfinal/tt;
    double Tcurrent = icurrent * delta_t;


    double AntXposNew;
    double AntYposNew;
    double AntVelXNew;
    double AntVelYNew;
    double ForceXvalue;
    double ForceYvalue;
    double RandomWalkVelX = 0.;
    double RandomWalkVelY = 0.;
    double RandomWalkVelXnew = RandomWalkVelX;
    double RandomWalkVelYnew = RandomWalkVelY;
    
    ////////////////////////////////////////////////////////
    // C�lculo das For�as
    ////////////////////////////////////////////////////////
    
    ForceXvalue = ForceX(AntXposOld, AntYposOld, AntVelXOld, AntVelYOld);
    ForceYvalue = ForceY(AntXposOld, AntYposOld, AntVelXOld, AntVelYOld);
    
    ////////////////////////////////////////////////////////
    // End C�lculo das For�as
    ////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    // C�lculo do Random Walk
    //  estou a tentar ver de http://www.caam.rice.edu/~cox/stoch/dhigham.pdf
    ////////////////////////////////////////////////////////
    int substeps = 20;
    for (int i=0; i<=substeps; i++) {
        RandomWalkVelXnew = RandomWalkVelXnew + sqrt(delta_t/substeps)* Normal(generator);
    }
    for (int i=0; i<=substeps; i++) {
        RandomWalkVelYnew = RandomWalkVelYnew + sqrt(delta_t/substeps)* Normal(generator);
    }
//    RandomWalkVelXnew = RandomWalkVelX + sqrt(delta_t)* Normal(generator);
//            cout << RandomWalkVelXnew << endl;
//
//    RandomWalkVelYnew = RandomWalkVelY + sqrt(delta_t)*Normal(generator);
//            cout << RandomWalkVelYnew << endl;
    ////////////////////////////////////////////////////////
    // End C�lculo do Random Walk
    ////////////////////////////////////////////////////////
    
    

    ////////////////////////////////////////////////////////
    // Evolu��o
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
//  Com relaxa��o:::
    
    AntVelXNew = AntVelXOld + delta_t * ( -(1./TAU)*( AntVelXOld - ForceXvalue) )
    + RandomWalkVelXnew * Turn_off_random;
    
    AntVelYNew = AntVelYOld + delta_t * ( -(1./TAU)*( AntVelYOld - ForceYvalue) )
    + RandomWalkVelYnew * Turn_off_random;

//  Sem relaxa��o:::
    
//    AntVelXNew = AntVelXOld + delta_t * ( ForceXvalue )
//    + RandomWalkVelXnew;
//    
//    AntVelYNew = AntVelYOld + delta_t * ( ForceYvalue )
//    + RandomWalkVelYnew;

    AntXposNew = AntXposOld + delta_t * (AntVelXNew);

    AntYposNew = AntYposOld + delta_t * (AntVelYNew);
    
//        cout << "AntVelXNew="<< AntVelXNew << endl;
//        cout << "AntVelYNew="<< AntVelYNew << endl;
    
    
    ////////////////////////////////////////////////////////
    // End Evolu��o
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    
    ////////////////////////////////////////////////////////
    // Fronteira PERIODIC!
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    if (AntXposNew <= x_1) {
        AntXposNew = AntXposNew + (x_2 - x_1);
        ChangedSide = 1;
    }
    if (AntXposNew >= x_2) {
        AntXposNew = AntXposNew - (x_2 - x_1);
        ChangedSide = 1;
    }
    if (AntYposNew <= y_1) {
        AntYposNew = AntYposNew + (y_2 - y_1);
        ChangedSide = 1;
    }
    if (AntYposNew >= y_2) {
        AntYposNew = AntYposNew - (y_2 - y_1);
        ChangedSide = 1;
    }

    ////////////////////////////////////////////////////////
    // End Fronteira PERIODIC!
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    

    
    ////////////////////////////////////////////////////////
    // Atualiza��o
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    AntXposOld = AntXposNew;

    AntYposOld = AntYposNew;
    
    AntVelXOld = AntVelXNew;
    
    AntVelYOld = AntVelYNew;
    
//    RandomWalkVelX = RandomWalkVelXnew;
//
//    RandomWalkVelY = RandomWalkVelYnew;
//        cout << "dentro  " << AntXposOld << endl;

    ////////////////////////////////////////////////////////
    // Delete Acho que n�o preciso pq n�o tenho vetores
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
}




////////////////////////////////////////////////////////
// END AntWalk
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

int main (void){
    
    int tt;
    
    string COMM;
    string DIR;
    
    int isAbort = 0;
    
    cout << "// Comments:" << endl;
    getline(cin, COMM, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
    //    cout << "// Name of Results Folder:" << endl;
    //    getline(cin, DIR, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
    // Pus a escolha da pasta no ficheiro Shell para executar.
    cout << "//  Number of time iterations:" << endl;
    cin >> tt;
    
    string DIR2 = "./"+DIR+"/";

    
    double TotalDistanceInCm = 0.;
    
    

    ////////////////////////////
    //  Conds Iniciais
    ////////////////////////////
    
    double AntXposOld;
    double AntYposOld;
    InitialPosition(AntXposOld, AntYposOld);

    double AntVelXOld;
    double AntVelYOld;
    InitialVelocity(AntVelXOld, AntVelYOld);
    
//    double RandomWalkVelX = 0.;
//    double RandomWalkVelY = 0.;
    
    ofstream AntPos(DIR2+"AntPos.txt");
    
    AntPos << AntXposOld << "\t" << AntYposOld << endl;
    
    ofstream AntVel(DIR2+"AntVel.txt");
    
    AntVel << AntVelXOld << "\t" << AntVelYOld << endl;
    
    ofstream AntVelAngle(DIR2+"AntVelAngle.txt");
    
    AntVelAngle << Angle(AntVelXOld,AntVelYOld) << endl;
    
    ofstream AntVelRadius(DIR2+"AntVelRadius.txt");
    
    AntVelRadius << Radius(AntVelXOld,AntVelYOld) << endl;

    ofstream AntDistance(DIR2+"AntDistance.txt");
    
    AntDistance << 0. <<"\t" << 0. << endl;

    /////////////////////////////
    // Ciclo em tempo
    /////////////////////////////
    //Ref:: AntWalk (int tt, double icurrent, double AntXposOld, double AntYposOld, double AntVelXOld, double AntVelYOld)
    
    for (int i=1; i<=tt; i++) {
        
        AntWalk (tt, i, AntXposOld, AntYposOld, AntVelXOld, AntVelYOld);
        
        TotalDistanceInCm = TotalDistanceInCm + delta_t * Radius(AntVelXOld,AntVelYOld)*X_hat_in_cm;
        
        if (i%100 == 0) {   //1000
            cout << "Iter restantes: " << tt - i << endl;
            
            //            if (isnan(AntXposOld)) {
            //                cout <<  "NAN numa iter menor que "<< i << endl;
            //                system("osascript -e 'tell app \"System Events\" to display dialog \"Abort!!!\" with icon 0 with title \"Abort!\" '");
            //                system("sh plot-png.sh");
            //                isAbort = 1;
            //                //abort();
            //                break;
            //            }
            
        }
        if (ChangedSide == 1) {
            AntPos << endl;
            ChangedSide = 0;
        }
        AntPos << AntXposOld << "\t" << AntYposOld << endl;
        AntVel << AntVelXOld << "\t" << AntVelYOld << endl;
        AntVelAngle << Angle(AntVelXOld,AntVelYOld) << endl;
        AntVelRadius << Radius(AntVelXOld,AntVelYOld) << endl;
        AntDistance << i*delta_t << "\t" << TotalDistanceInCm << endl;
    }
    /////////////////////////////
    // End Ciclo em tempo
    /////////////////////////////
    
    

//    cout << "Tfinal  = " << tt*delta_t<< endl;
//    cout << "delta_t = " << delta_t<< endl;
//    cout << "Num Iter = " << tt << endl;

    PrintInfo(delta_t,COMM,tt);
    
    /////////////////////////////
    // Escrever resultados
    /////////////////////////////

//    ofstream outfile_solucao1;
//    outfile_solucao1.open(DIR2+"LastPrey.txt");
//    for(int j=0;j<xx;j++){
//        for(int k=0;k<yy;k++){
//            outfile_solucao1 << Prey_old(j,k) << "\t";
//            if(k==yy-1)
//            outfile_solucao1 << endl;
//        }
//    }
//    outfile_solucao1.close();
    
    
    
    
    if (isAbort==1) {
        abort();
    }

    
    cout << COMM << endl;
    
    return 0;
}





    
    
    
    
    
    
    
    
    




