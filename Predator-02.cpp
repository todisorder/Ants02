# include <fstream>
# include "stdlib.h"
# include <iostream>
# include <cmath>
# include <string>
#include <sstream>
#include <iomanip> 

using namespace std;

#include "matriz.h"
//#include "vector.h"


static double const Pi = 3.14159;
static double const Ln2 = 0.6931471806;

//////////////////////////////////////////////////////
// Population parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//  Prey diffusion (nondimensional!)
static double const DDPrey = 1.;         //

//  Predator diffusion (nondimensional!)
static double const DDPredator = 1.;         // Tem de ser 1.!!!!!!

//  Prey Pheromone diffusion (nondimensional!)
static double const DDPreyPhero = 30.;         //

//  Predator Pheromone diffusion (nondimensional!)
static double const DDPredatorPhero = 10.;         //

//  Prey chemotactical sensitivity (nondimensional!)
static double const ChiPrey = 10.;          //

//  Prey Pheromone evaporation (nondimensional!)
static double const DeltaPreyPhero = .5;           //

//  Prey Equation alpha coefficient (nondimensional!)
static double const alpha = 25.;           //

//  Predator chemotactical sensitivity (nondimensional!)
static double const ChiPredator = 20.;          //

//  Predator Pheromone evaporation (nondimensional!)
static double const DeltaPredatorPhero = .5;           //

//  Predator Equation beta coefficient (nondimensional!)
static double const beta = 25.;           //
//////////////////////////////////////////////////////
// End Population parameters
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// tempo final
//static double const TFINAL = 0.1;
static double const delta_t = 0.00002;   //     0.001


////////////////////////////
//  Definição do  Domínio
////////////////////////////
// extremo inferior do intervalo em x
static double const x_1 = -10.;      //a_x

// extremo superior do intervalo em x
static double const x_2 = 10.;       //b_x

// extremo inferior do intervalo em y
static double const y_1 =  -10.;     //a_y

// extremo superior do intervalo em y
static double const y_2 = 10.;       //b_y
////////////////////////////
// End Definição do  Domínio
////////////////////////////



/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Prey
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void IniPrey (int xx,int yy, my_matrix ci)
{
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;
    double xxi, yyj;
    double aux_1 = 0.;
    double centx = 0.;
    double centy = 0.;
    
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            xxi = x_1 + delta_x*i;
            yyj = y_1 + delta_y*j;
            aux_1 = sqrt((xxi-centx)*(xxi-centx) + (yyj-centy)*(yyj-centy));
            if (aux_1 <= 1.) {
                ci(i,j) = 3.;
            } else {
                ci(i,j)= 0.;
            }
            
//            ci(i,j) = 0.;         //
//            ci(i,j) = 1.;         //
        }
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Prey
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Prey Pheromone
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void IniPreyPhero (int xx,int yy, my_matrix ci)
{
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;
    double xxi, yyj;
    double aux_1 = 0.;
    double centx = 0.;
    double centy = 0.;

    
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            xxi = x_1 + delta_x*i;
            yyj = y_1 + delta_y*j;
            aux_1 = sqrt((xxi-centx)*(xxi-centx) + (yyj-centy)*(yyj-centy));
            if (aux_1 <= 1.) {
                ci(i,j) = 3.;
            } else {
                ci(i,j)= 0.;
            }
            
            ci(i,j) = 0.;         //
            //            ci(i,j) = 1.;         //
        }
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Prey Pheromone
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Predator
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void IniPredator (int xx,int yy, my_matrix ci)
{
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;
    double xxi, yyj;
    double aux_1 = 0.;
    double val = 10.;
    double centx = 2.5;
    double centy = 0.;
    
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            xxi = x_1 + delta_x*i;
            yyj = y_1 + delta_y*j;
            aux_1 = sqrt((xxi-centx)*(xxi-centx) + (yyj-centy)*(yyj-centy));
            if (aux_1 <= .3) {
                ci(i,j) = val;
            } else {
                ci(i,j)= 0.;
            }
            
            //            ci(i,j) = 0.;         //
            //            ci(i,j) = 1.;         //
        }
    }
    centy = 2.;
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            xxi = x_1 + delta_x*i;
            yyj = y_1 + delta_y*j;
            aux_1 = sqrt((xxi-centx)*(xxi-centx) + (yyj-centy)*(yyj-centy));
            if (aux_1 <= .3) {
                ci(i,j) = ci(i,j) + val;
            } else {
                //                ci(i,j)= 0.;
            }
            
            //            ci(i,j) = 0.;         //
            //            ci(i,j) = 1.;         //
        }
    }
    centy = -2.;
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            xxi = x_1 + delta_x*i;
            yyj = y_1 + delta_y*j;
            aux_1 = sqrt((xxi-centx)*(xxi-centx) + (yyj-centy)*(yyj-centy));
            if (aux_1 <= .3) {
                ci(i,j) = ci(i,j) + val;
            } else {
                //                ci(i,j)= 0.;
            }
            
            //            ci(i,j) = 0.;         //
            //            ci(i,j) = 1.;         //
        }
    }
    centx = 0.5;
    centy = 4.;
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            xxi = x_1 + delta_x*i;
            yyj = y_1 + delta_y*j;
            aux_1 = sqrt((xxi-centx)*(xxi-centx) + (yyj-centy)*(yyj-centy));
            if (aux_1 <= .3) {
                ci(i,j) = ci(i,j) + val;
            } else {
                //                ci(i,j)= 0.;
            }
            
            //            ci(i,j) = 0.;         //
            //            ci(i,j) = 1.;         //
        }
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Predator
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//  Cond. Inicial Predator Phero
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void IniPredatorPhero (int xx,int yy, my_matrix ci)
{
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;
    double xxi, yyj;
    double aux_1 = 0.;
    
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            xxi = x_1 + delta_x*i;
            yyj = y_1 + delta_y*j;
            aux_1 = sqrt((xxi-0.5)*(xxi-0.5) + (yyj-0.5)*(yyj-0.5));
            if (aux_1 <= 0.2) {
                ci(i,j) = 3.;
            } else {
                ci(i,j)= 0.;
            }
            
            ci(i,j) = 0.;         //
            //            ci(i,j) = 1.;         //
        }
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//
//      End Cond. Inicial Predator Phero
//
/////////////////////////////////////////////////
/////////////////////////////////////////////////

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//  Definir a topografia do terreno
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void define_topography (int xx,int yy, my_matrix topography)
{
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;
    double aux = 0.;
    int aux_5 = 5;
    double value = 300.;
    my_matrix temptop(xx,yy); temptop.matrix("zero");
    
    
    //    Random topography         // http://www.cplusplus.com/reference/cstdlib/rand/?kw=rand
    ////////////////////////////////////////////////////////
    //    srand (time(NULL));
    srand (3);
    for(int i=0;i<xx;i++){
        for(int j=0;j<yy;j++){
            
            aux = rand() % 10 + 10; aux = 1./aux;
            topography(i,j)=10.*aux - .75;
            if (i<aux_5 || i>xx-aux_5 || j<aux_5 || j>yy-aux_5) {
                topography(i,j)=-0.75;
            }
        }
    }
    for (int l=1; l<=30; l++) {      //l<= 20.   Regularização
        for(int i=1;i<xx-1;i++){
            for(int j=1;j<yy-1;j++){
                topography(i,j)= 0.25*(topography(i-1,j) + topography(i+1,j) + topography(i,j-1) + topography(i,j+1));
            }
        }
        for(int j=1;j<xx-1;j++){    // Na fronteira
            topography(j,0) = (1./3.)*(topography(j+1,0) + topography(j-1,0) + topography(j,1));
        }
        for(int k=1;k<yy-1;k++){
            topography(0,k) = (1./3.)*(topography(0,k+1) + topography(0,k-1) + topography(1,k));
        }
        for(int j=1;j<xx-1;j++){
            topography(j,yy-1) = (1./3.)*(topography(j+1,yy-1) + topography(j-1,yy-1) + topography(j,yy-2));
        }
        for(int k=1;k<yy-1;k++){
            topography(xx-1,k) = (1./3.)*(topography(xx-1,k+1) + topography(xx-1,k-1) + topography(xx-2,k));
        }   // Cantos
        topography(0,0) = 0.5*(topography(1,0) + topography(0,1));
        topography(xx-1,0) = 0.5*(topography(xx-2,0) + topography(xx-1,1));
        topography(0,yy-1) = 0.5*(topography(0,yy-2) + topography(1,yy-1));
        topography(xx-1,yy-1) = 0.5*(topography(xx-2,yy-1) + topography(xx-1,yy-2));
    }
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            topography(j,k) = max(topography(j,k),-0.04);  //-0.02  //-0.035
            topography(j,k) *= 4.;
        }
    }
    //   END Random topography
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            topography(j,k) = 0.;        //Para testar com zero
        }
    }
}




////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// Fncs para calcular gradientes, divergencia, Laplaciano, método upwiwnd
//
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
double Dmais(double dx,double uj, double ujj){
    
    return (ujj - uj)/dx;
}


double PartePositiva(double aa){
    
    return max(aa,0.);
}

double ParteNegativa(double aa){
    
    return - min(aa,0.);
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// End Fncs para calcular gradientes, divergencia, Laplaciano, método upwiwnd
//
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// Fcs RK 4
//
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

double FuncRKPrey(double dt, double dx, double dy, double Preyjmenosum, double Preyjk, double Preyjmaisum, double Preykmenosum, double Preykmaisum, double Veljmenosummeio, double Veljmaisummeio,double Velkmenosummeio, double Velkmaisummeio,double DDPrey, double beta, double Predatorjk) {
    double result=0.;
    
    result = DDPrey*(dt/(dx*dx))*(Preyjmenosum - 2.* Preyjk + Preyjmaisum)
    + DDPrey*(dt/(dy*dy))*(Preykmenosum - 2.* Preyjk + Preykmaisum)
    - (dt/dx)*(PartePositiva(Veljmaisummeio)*Preyjk
               - ParteNegativa(Veljmaisummeio)*Preyjmaisum
               - PartePositiva(Veljmenosummeio)*Preyjmenosum
               + ParteNegativa(Veljmenosummeio)*Preyjk)
    - (dt/dy)*(PartePositiva(Velkmaisummeio)*Preyjk
               - ParteNegativa(Velkmaisummeio)*Preykmaisum
               - PartePositiva(Velkmenosummeio)*Preykmenosum
               + ParteNegativa(Velkmenosummeio)*Preyjk)
    +  dt * beta * Preyjk * ( 1. - Preyjk - Predatorjk );
    
    return result;
}

double FuncRKPreyPhero(double dt, double dx, double dy, double PreyPherojmenosum, double PreyPherojk, double PreyPherojmaisum, double PreyPherokmenosum, double PreyPherokmaisum, double DDPreyPhero, double DeltaPreyPhero, double Preyjk) {
    double result=0.;
    
    result = DDPreyPhero*(dt/(dx*dx))*(PreyPherojmenosum - 2.* PreyPherojk + PreyPherojmaisum)
    + DDPreyPhero*(dt/(dy*dy))*(PreyPherokmenosum - 2.* PreyPherojk + PreyPherokmaisum)
    + dt * Preyjk - dt * DeltaPreyPhero * PreyPherojk ;
    
    return result;
}


double FuncRKPredator(double dt, double dx, double dy, double Predatorjmenosum, double Predatorjk, double Predatorjmaisum, double Predatorkmenosum, double Predatorkmaisum, double Veljmenosummeio, double Veljmaisummeio,double Velkmenosummeio, double Velkmaisummeio,double DDPredator, double alpha, double Preyjk) {
    double result=0.;
    
    result = DDPredator*(dt/(dx*dx))*(Predatorjmenosum - 2.* Predatorjk + Predatorjmaisum)
    + DDPredator*(dt/(dy*dy))*(Predatorkmenosum - 2.* Predatorjk + Predatorkmaisum)
    - (dt/dx)*(PartePositiva(Veljmaisummeio)*Predatorjk
               - ParteNegativa(Veljmaisummeio)*Predatorjmaisum
               - PartePositiva(Veljmenosummeio)*Predatorjmenosum
               + ParteNegativa(Veljmenosummeio)*Predatorjk)
    - (dt/dy)*(PartePositiva(Velkmaisummeio)*Predatorjk
               - ParteNegativa(Velkmaisummeio)*Predatorkmaisum
               - PartePositiva(Velkmenosummeio)*Predatorkmenosum
               + ParteNegativa(Velkmenosummeio)*Predatorjk)
    +  dt * ( alpha * Predatorjk * Preyjk - Predatorjk );
    
    return result;
}

double FuncRKPredatorPhero(double dt, double dx, double dy, double PredatorPherojmenosum, double PredatorPherojk, double PredatorPherojmaisum, double PredatorPherokmenosum, double PredatorPherokmaisum, double DDPredatorPhero, double DeltaPredatorPhero, double Predatorjk) {
    double result=0.;
    
    result = DDPredatorPhero*(dt/(dx*dx))*(PredatorPherojmenosum - 2.* PredatorPherojk + PredatorPherojmaisum)
    + DDPredatorPhero*(dt/(dy*dy))*(PredatorPherokmenosum - 2.* PredatorPherojk + PredatorPherokmaisum)
    + dt * Predatorjk - dt * DeltaPredatorPhero * PredatorPherojk ;
    
    return result;
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//
// End Fcs RK 4
//
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
// Método propriamente dito
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void IteraPredator (int tt,int xx,int yy, int icurrent, string IsRK, my_matrix Prey_old, my_matrix Predator_old, my_matrix PreyPhero_old, my_matrix PredatorPhero_old, my_matrix topography)
{

    double aux_1, aux_2, aux_3, aux_4;
    double xxi, yyj, xxj, yyk;
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;
    // amplitude dos subintervalos em tempo
    double tfinal;
    //    double delta_t;
    tfinal = delta_t * tt;
    //    delta_t = tfinal/tt;
    double Tcurrent = icurrent * delta_t;
    double lambda_y = delta_t/delta_y;
    double lambda_x = delta_t/delta_x;


    my_matrix Vel_Prey_x(xx,yy); Vel_Prey_x.matrix("zero");
    my_matrix Vel_Prey_y(xx,yy); Vel_Prey_y.matrix("zero");
    my_matrix Vel_Predator_x(xx,yy); Vel_Predator_x.matrix("zero");
    my_matrix Vel_Predator_y(xx,yy); Vel_Predator_y.matrix("zero");

    my_matrix Prey_aux(xx,yy); Prey_aux.matrix("zero");
    my_matrix PreyPhero_aux(xx,yy); PreyPhero_aux.matrix("zero");
    my_matrix Predator_aux(xx,yy); Predator_aux.matrix("zero");
    my_matrix PredatorPhero_aux(xx,yy); PredatorPhero_aux.matrix("zero");

    my_matrix kapaum(xx,yy); kapaum.matrix("zero");
    my_matrix kapadois(xx,yy); kapadois.matrix("zero");
    my_matrix kapatres(xx,yy); kapatres.matrix("zero");
    my_matrix kapaquatro(xx,yy); kapaquatro.matrix("zero");
    

    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    //
    //  Cálculo das velocidades. Os sinais são do LHS!!!.
    //
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    for(int j=1;j<xx-1;j++){
        for(int k=1;k<yy-1;k++){
            
            Vel_Prey_x(j,k) = - ChiPrey * Dmais(delta_x,PredatorPhero_old(j,k),PredatorPhero_old(j+1,k)) -  Dmais(delta_x,topography(j,k),topography(j+1,k));
            
            Vel_Prey_y(j,k) = - ChiPrey * Dmais(delta_y,PredatorPhero_old(j,k),PredatorPhero_old(j,k+1)) -   Dmais(delta_y,topography(j,k),topography(j,k+1));
        }
    }

    for(int j=1;j<xx-1;j++){
        for(int k=1;k<yy-1;k++){
            
            Vel_Predator_x(j,k) =  ChiPredator * Dmais(delta_x,PreyPhero_old(j,k),PreyPhero_old(j+1,k)) -  Dmais(delta_x,topography(j,k),topography(j+1,k));
            
            Vel_Predator_y(j,k) = - ChiPredator * Dmais(delta_y,PreyPhero_old(j,k),PreyPhero_old(j,k+1)) -   Dmais(delta_y,topography(j,k),topography(j,k+1));
        }
    }

    
    
    
    // Evolução
    
    ////////////////////////////////////////////////////////
    // Evolução
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    // Prey
    ////////////////////////////////////////////////////////
    // Ref:: double FuncRKPrey(double dt, double dx, double dy, double Preyjmenosum, double Preyjk, double Preyjmaisum, double Preykmenosum, double Preykmaisum, double Veljmenosummeio, double Veljmaisummeio,double Velkmenosummeio, double Velkmaisummeio,double DDPrey, double beta, double Predatorjk) {
    
    if (IsRK=="y") {
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaum(j,k) = FuncRKPrey(delta_t, delta_x, delta_y, Prey_old(j-1,k), Prey_old(j,k), Prey_old(j+1,k), Prey_old(j,k-1), Prey_old(j,k+1), Vel_Prey_x(j-1,k), Vel_Prey_x(j,k),Vel_Prey_y(j,k-1), Vel_Prey_y(j,k),  DDPrey, beta, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapadois(j,k) = FuncRKPrey(delta_t, delta_x, delta_y, Prey_old(j-1,k)+0.5*kapaum(j-1,k), Prey_old(j,k)+0.5*kapaum(j,k), Prey_old(j+1,k)+0.5*kapaum(j+1,k), Prey_old(j,k-1)+0.5*kapaum(j,k-1), Prey_old(j,k+1)+0.5*kapaum(j,k+1), Vel_Prey_x(j-1,k), Vel_Prey_x(j,k),Vel_Prey_y(j,k-1), Vel_Prey_y(j,k), DDPrey, beta, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapatres(j,k) = FuncRKPrey(delta_t, delta_x, delta_y, Prey_old(j-1,k)+0.5*kapadois(j-1,k), Prey_old(j,k)+0.5*kapadois(j,k), Prey_old(j+1,k)+0.5*kapadois(j+1,k), Prey_old(j,k-1)+0.5*kapadois(j,k-1), Prey_old(j,k+1)+0.5*kapadois(j,k+1), Vel_Prey_x(j-1,k), Vel_Prey_x(j,k),Vel_Prey_y(j,k-1), Vel_Prey_y(j,k), DDPrey, beta, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaquatro(j,k) = FuncRKPrey(delta_t, delta_x, delta_y, Prey_old(j-1,k)+kapatres(j-1,k), Prey_old(j,k)+kapatres(j,k), Prey_old(j+1,k)+kapatres(j+1,k), Prey_old(j,k-1)+kapatres(j,k-1), Prey_old(j,k+1)+kapatres(j,k+1), Vel_Prey_x(j-1,k), Vel_Prey_x(j,k),Vel_Prey_y(j,k-1), Vel_Prey_y(j,k), DDPrey, beta, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                Prey_aux(j,k) = Prey_old(j,k) + ( kapaum(j,k) + 2.*kapadois(j,k) + 2.*kapatres(j,k) + kapaquatro(j,k) )/6.;
            }
        }
        
        ////////////////////////////////////////////////////////
        // END   Prey
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        // PreyPhero
        ////////////////////////////////////////////////////////
        // Ref:: double FuncRKPreyPhero(double dt, double dx, double dy, double PreyPherojmenosum, double PreyPherojk, double PreyPherojmaisum, double PreyPherokmenosum, double PreyPherokmaisum, double DDPreyPhero, double DeltaPreyPhero, double Preyjk) {
        
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaum(j,k) = FuncRKPreyPhero(delta_t, delta_x, delta_y, PreyPhero_old(j-1,k), PreyPhero_old(j,k), PreyPhero_old(j+1,k), PreyPhero_old(j,k-1), PreyPhero_old(j,k+1), DDPreyPhero, DeltaPreyPhero, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapadois(j,k) = FuncRKPreyPhero(delta_t, delta_x, delta_y, PreyPhero_old(j-1,k)+0.5*kapaum(j-1,k), PreyPhero_old(j,k)+0.5*kapaum(j,k), PreyPhero_old(j+1,k)+0.5*kapaum(j+1,k), PreyPhero_old(j,k-1)+0.5*kapaum(j,k-1), PreyPhero_old(j,k+1)+0.5*kapaum(j,k+1), DDPrey, DeltaPreyPhero, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapatres(j,k) = FuncRKPreyPhero(delta_t, delta_x, delta_y, PreyPhero_old(j-1,k)+0.5*kapadois(j-1,k), PreyPhero_old(j,k)+0.5*kapadois(j,k), PreyPhero_old(j+1,k)+0.5*kapadois(j+1,k), PreyPhero_old(j,k-1)+0.5*kapadois(j,k-1), PreyPhero_old(j,k+1)+0.5*kapadois(j,k+1), DDPrey, DeltaPreyPhero, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaquatro(j,k) = FuncRKPreyPhero(delta_t, delta_x, delta_y, PreyPhero_old(j-1,k)+kapatres(j-1,k), PreyPhero_old(j,k)+kapatres(j,k), PreyPhero_old(j+1,k)+kapatres(j+1,k), PreyPhero_old(j,k-1)+kapatres(j,k-1), PreyPhero_old(j,k+1)+kapatres(j,k+1), DDPrey, DeltaPreyPhero, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                PreyPhero_aux(j,k) = PreyPhero_old(j,k) + ( kapaum(j,k) + 2.*kapadois(j,k) + 2.*kapatres(j,k) + kapaquatro(j,k) )/6.;
            }
        }
        ////////////////////////////////////////////////////////
        // END   PreyPhero
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        // Predator
        ////////////////////////////////////////////////////////
        // Ref:: double FuncRKPredator(double dt, double dx, double dy, double Predatorjmenosum, double Predatorjk, double Predatorjmaisum, double Predatorkmenosum, double Predatorkmaisum, double Veljmenosummeio, double Veljmaisummeio,double Velkmenosummeio, double Velkmaisummeio,double DDPredator, double alpha, double Preyjk) {
        
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaum(j,k) = FuncRKPredator(delta_t, delta_x, delta_y, Predator_old(j-1,k), Predator_old(j,k), Predator_old(j+1,k), Predator_old(j,k-1), Predator_old(j,k+1), Vel_Predator_x(j-1,k), Vel_Predator_x(j,k),Vel_Predator_y(j,k-1), Vel_Predator_y(j,k),  DDPredator, alpha, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapadois(j,k) = FuncRKPredator(delta_t, delta_x, delta_y, Predator_old(j-1,k)+0.5*kapaum(j-1,k), Predator_old(j,k)+0.5*kapaum(j,k), Predator_old(j+1,k)+0.5*kapaum(j+1,k), Predator_old(j,k-1)+0.5*kapaum(j,k-1), Predator_old(j,k+1)+0.5*kapaum(j,k+1), Vel_Predator_x(j-1,k), Vel_Predator_x(j,k),Vel_Predator_y(j,k-1), Vel_Predator_y(j,k), DDPredator, alpha, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapatres(j,k) = FuncRKPredator(delta_t, delta_x, delta_y, Predator_old(j-1,k)+0.5*kapadois(j-1,k), Predator_old(j,k)+0.5*kapadois(j,k), Predator_old(j+1,k)+0.5*kapadois(j+1,k), Predator_old(j,k-1)+0.5*kapadois(j,k-1), Predator_old(j,k+1)+0.5*kapadois(j,k+1), Vel_Predator_x(j-1,k), Vel_Predator_x(j,k),Vel_Predator_y(j,k-1), Vel_Predator_y(j,k), DDPredator, alpha, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaquatro(j,k) = FuncRKPredator(delta_t, delta_x, delta_y, Predator_old(j-1,k)+kapatres(j-1,k), Predator_old(j,k)+kapatres(j,k), Predator_old(j+1,k)+kapatres(j+1,k), Predator_old(j,k-1)+kapatres(j,k-1), Predator_old(j,k+1)+kapatres(j,k+1), Vel_Predator_x(j-1,k), Vel_Predator_x(j,k),Vel_Predator_y(j,k-1), Vel_Predator_y(j,k), DDPredator, alpha, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                Predator_aux(j,k) = Predator_old(j,k) + ( kapaum(j,k) + 2.*kapadois(j,k) + 2.*kapatres(j,k) + kapaquatro(j,k) )/6.;
            }
        }
        ////////////////////////////////////////////////////////
        // END   Predator
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        // PredatorPhero
        ////////////////////////////////////////////////////////
        // Ref:: double FuncRKPredatorPhero(double dt, double dx, double dy, double PredatorPherojmenosum, double PredatorPherojk, double PredatorPherojmaisum, double PredatorPherokmenosum, double PredatorPherokmaisum, double DDPredatorPhero, double DeltaPredatorPhero, double Predatorjk) {
        
        
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaum(j,k) = FuncRKPredatorPhero(delta_t, delta_x, delta_y, PredatorPhero_old(j-1,k), PredatorPhero_old(j,k), PredatorPhero_old(j+1,k), PredatorPhero_old(j,k-1), PredatorPhero_old(j,k+1), DDPredatorPhero, DeltaPredatorPhero, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapadois(j,k) = FuncRKPredatorPhero(delta_t, delta_x, delta_y, PredatorPhero_old(j-1,k)+0.5*kapaum(j-1,k), PredatorPhero_old(j,k)+0.5*kapaum(j,k), PredatorPhero_old(j+1,k)+0.5*kapaum(j+1,k), PredatorPhero_old(j,k-1)+0.5*kapaum(j,k-1), PredatorPhero_old(j,k+1)+0.5*kapaum(j,k+1), DDPredator, DeltaPredatorPhero, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapatres(j,k) = FuncRKPredatorPhero(delta_t, delta_x, delta_y, PredatorPhero_old(j-1,k)+0.5*kapadois(j-1,k), PredatorPhero_old(j,k)+0.5*kapadois(j,k), PredatorPhero_old(j+1,k)+0.5*kapadois(j+1,k), PredatorPhero_old(j,k-1)+0.5*kapadois(j,k-1), PredatorPhero_old(j,k+1)+0.5*kapadois(j,k+1), DDPredator, DeltaPredatorPhero, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                kapaquatro(j,k) = FuncRKPredatorPhero(delta_t, delta_x, delta_y, PredatorPhero_old(j-1,k)+kapatres(j-1,k), PredatorPhero_old(j,k)+kapatres(j,k), PredatorPhero_old(j+1,k)+kapatres(j+1,k), PredatorPhero_old(j,k-1)+kapatres(j,k-1), PredatorPhero_old(j,k+1)+kapatres(j,k+1), DDPredator, DeltaPredatorPhero, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                PredatorPhero_aux(j,k) = PredatorPhero_old(j,k) + ( kapaum(j,k) + 2.*kapadois(j,k) + 2.*kapatres(j,k) + kapaquatro(j,k) )/6.;
            }
        }
        ////////////////////////////////////////////////////////
        // END   PredatorPhero
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
    } else {        // Isto é do If IsRK=="y"
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                Prey_aux(j,k) = Prey_old(j,k) + FuncRKPrey(delta_t, delta_x, delta_y, Prey_old(j-1,k), Prey_old(j,k), Prey_old(j+1,k), Prey_old(j,k-1), Prey_old(j,k+1), Vel_Prey_x(j-1,k), Vel_Prey_x(j,k),Vel_Prey_y(j,k-1), Vel_Prey_y(j,k),  DDPrey, beta, Predator_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                PreyPhero_aux(j,k) = PreyPhero_old(j,k) + FuncRKPreyPhero(delta_t, delta_x, delta_y, PreyPhero_old(j-1,k), PreyPhero_old(j,k), PreyPhero_old(j+1,k), PreyPhero_old(j,k-1), PreyPhero_old(j,k+1), DDPreyPhero, DeltaPreyPhero, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                Predator_aux(j,k) = Predator_old(j,k) + FuncRKPredator(delta_t, delta_x, delta_y, Predator_old(j-1,k), Predator_old(j,k), Predator_old(j+1,k), Predator_old(j,k-1), Predator_old(j,k+1), Vel_Predator_x(j-1,k), Vel_Predator_x(j,k),Vel_Predator_y(j,k-1), Vel_Predator_y(j,k),  DDPredator, alpha, Prey_old(j,k));
            }
        }
        for(int j=1;j<xx-1;j++){
            for(int k=1;k<yy-1;k++){
                PredatorPhero_aux(j,k) = PredatorPhero_old(j,k) + FuncRKPredatorPhero(delta_t, delta_x, delta_y, PredatorPhero_old(j-1,k), PredatorPhero_old(j,k), PredatorPhero_old(j+1,k), PredatorPhero_old(j,k-1), PredatorPhero_old(j,k+1), DDPredatorPhero, DeltaPredatorPhero, Predator_old(j,k));
            }
        }
    }

    
    ////////////////////////////////////////////////////////
    // Atualização
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    

    for(int j=1;j<xx-1;j++){
        for(int k=1;k<yy-1;k++){
            Prey_old(j,k) = Prey_aux(j,k);
            Predator_old(j,k) = Predator_aux(j,k);
            PreyPhero_old(j,k) = PreyPhero_aux(j,k);
            PredatorPhero_old(j,k) = PredatorPhero_aux(j,k);
        }
    }
    


    ////////////////////////////////////////////////////////
    // Valores na fronteira NEUMANN
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    
    
    for(int j=0;j<xx;j++){
        Prey_old(j,0)=Prey_old(j,1);
        Predator_old(j,0)=Predator_old(j,1);
        PreyPhero_old(j,0)=PreyPhero_old(j,1);
        PredatorPhero_old(j,0)=PredatorPhero_old(j,1);
        //
        Prey_old(j,yy-1)=Prey_old(j,yy-2);
        Predator_old(j,yy-1)=Predator_old(j,yy-2);
        PreyPhero_old(j,yy-1)=PreyPhero_old(j,yy-2);
        PredatorPhero_old(j,yy-1)=PredatorPhero_old(j,yy-2);
    }
    //
    for(int k=0;k<yy;k++){
        Prey_old(0,k)=Prey_old(1,k);
        Predator_old(0,k)=Predator_old(1,k);
        PreyPhero_old(0,k)=PreyPhero_old(1,k);
        PredatorPhero_old(0,k)=PredatorPhero_old(1,k);
        //
        Prey_old(xx-1,k)=Prey_old(xx-2,k);
        Predator_old(xx-1,k)=Predator_old(xx-2,k);
        PreyPhero_old(xx-1,k)=PreyPhero_old(xx-2,k);
        PredatorPhero_old(xx-1,k)=PredatorPhero_old(xx-2,k);
    }
    ////////////////////////////////////////////////////////
    // End Valores na fronteira NEUMANN
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
  

    ////////////////////////////////////////////////////////
    // Delete
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////


    delete Vel_Prey_x.elementos;
    delete Vel_Prey_y.elementos;
    delete Vel_Predator_x.elementos;
    delete Vel_Predator_y.elementos;
    
    delete Prey_aux.elementos;
    delete PreyPhero_aux.elementos;
    delete Predator_aux.elementos;
    delete PredatorPhero_aux.elementos;
    
    delete kapaum.elementos;
    delete kapadois.elementos;
    delete kapatres.elementos;
    delete kapaquatro.elementos;
    
}
////////////////////////////////////////////////////////
// END IteraPredator
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
// Fcns para escrever resultados e nomes de ficheiros
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void save_time_step(int xx, int yy, my_matrix u1, int icurrent, string ref, string dir)
{
    double Tcurrent = icurrent * delta_t;
    
    stringstream sstream_buffer;
    string string_buffer;
    
    // create the filename (using string/stringstream for manipulation of the data that will form the name);
    sstream_buffer.clear();
    //	sstream_buffer << "./" << method_name << "/U_" << fixed << setprecision(6) << t_n  << "___" << n;
    //  	sstream_buffer << ref << "T-" << fixed << setprecision(2) << icurrent  << ".txt";
    sstream_buffer << "./" << dir << "/" << ref << "T-" << setfill('0')  << setw(6) << icurrent  << ".txt";
    string_buffer.clear();
    sstream_buffer >> string_buffer;
    
    // create the output stream
    ofstream of_U_n(string_buffer.c_str());
    
    // write all the key->values present the U_n
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            of_U_n << u1(j,k) << "\t";
            if(k==yy-1)
            of_U_n << endl;
        }
    }
    
}

void save_time_step_vector(int xx, int yy, my_matrix u1, my_matrix u2, int icurrent, string ref, string dir)
{
    double Tcurrent = icurrent * delta_t;
    
    stringstream sstream_buffer;
    string string_buffer;
    
    // create the filename (using string/stringstream for manipulation of the data that will form the name);
    sstream_buffer.clear();
    //	sstream_buffer << "./" << method_name << "/U_" << fixed << setprecision(6) << t_n  << "___" << n;
    //  	sstream_buffer << ref << "T-" << fixed << setprecision(2) << icurrent  << ".txt";
    sstream_buffer << "./" << dir << "/" << ref << "T-" << setfill('0')  << setw(6) << icurrent  << ".txt";
    string_buffer.clear();
    sstream_buffer >> string_buffer;
    
    // create the output stream
    ofstream of_U_n(string_buffer.c_str());
    
    // write all the key->values present the U_n
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            of_U_n << j << "\t"<< k<< "\t" << u1(j,k)<< "\t" << u2(j,k) << endl;
        }
    }
}

////////////////////////////////////////////////////////
// Fc para calcular massa
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

double Compute_mass(double delta_x, double delta_y, int xx, int yy, my_matrix U )
{
    double aux = 0.;
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            aux += delta_x*delta_y * U(j,k);
        }
    }
    return aux;
}


////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

int main (void){
    
    int xx;
    int yy;
    int tt;
    
    string COMM;
    string DIR;
    string IsRK;
    
    int isAbort = 0;
    
    cout << "// Comments:" << endl;
    getline(cin, COMM, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
    //    cout << "// Name of Results Folder:" << endl;
    //    getline(cin, DIR, '\n');               // Nice... de http://www.cprogramming.com/tutorial/string.html
    cout << "// Number of x intervals:" << endl;
    cin >> xx;
    cout << "// Number of y intervals:" << endl;
    cin >> yy;
    cout << "//  Number of time iterations:" << endl;
    cin >> tt;
    cout << "//  RK4? (y/n):" << endl;
    cin >> IsRK;
    
    string DIR2 = "./"+DIR+"/";

    
//    PrintInfo(xx,yy,tt,COMM);
    
    
    double delta_x;
    delta_x = (x_2-x_1)/xx;
    double delta_y;
    delta_y = (y_2-y_1)/yy;

    ////////////////////////////
    //  Conds Iniciais
    ////////////////////////////
    
    my_matrix Prey_old(xx,yy); IniPrey(xx,yy,Prey_old);
    my_matrix PreyPhero_old(xx,yy); IniPreyPhero(xx,yy,PreyPhero_old);
    my_matrix Predator_old(xx,yy); IniPredator(xx,yy,Predator_old);
    my_matrix PredatorPhero_old(xx,yy); IniPredatorPhero(xx,yy,PredatorPhero_old);
    my_matrix topography(xx,yy); define_topography(xx,yy,topography);
    
    double Mass_Prey = Compute_mass(delta_x, delta_y, xx,yy, Prey_old);
    double Mass_Predator = Compute_mass(delta_x, delta_y, xx,yy, Predator_old);

    ofstream Mass(DIR2+"Mass.txt");
    Mass << "# tcurrent - [($2) Mass_u1] - [($3) Mass_u2] - [($4) Mass_food] - [($5) Iter] -[($6) Mass_u1 + Mass_u2] - [($7) Tempo em Horas]" << endl;

    /////////////////////////////
    // Ciclo em tempo
    /////////////////////////////
    //Ref:: IteraPredator (int tt,int xx,int yy, int icurrent, my_matrix Prey_old, my_matrix Predator_old, my_matrix PreyPhero_old, my_matrix PredatorPhero_old, my_matrix topography)
    
    for (int i=1; i<=tt; i++) {
        IteraPredator(tt, xx, yy, i, IsRK, Prey_old, Predator_old, PreyPhero_old, PredatorPhero_old, topography);
        
        if (i%2000 == 0) {   //1000
            cout << "Iter restantes: " << tt - i << endl;
            Mass_Prey = Compute_mass(delta_x, delta_y, xx,yy, Prey_old);
            Mass_Predator = Compute_mass(delta_x, delta_y, xx,yy, Predator_old);
            
            Mass << i*(delta_t) << "\t" << Mass_Prey << "\t" << Mass_Predator  << "\t" << i <<"\t" << i*delta_t << endl;
            
            if (isnan(Prey_old(xx/2,yy/2))) {
                cout <<  "NAN numa iter menor que "<< i << endl;
                //                system("open sticky-notifications://note?message=NAN-ABORT");
                system("osascript -e 'tell app \"System Events\" to display dialog \"Abort!!!\" with icon 0 with title \"Abort!\" '");
                system("sh plot-png.sh");
                isAbort = 1;
                //abort();
                break;
            }
            
        }
        
        if (i%500 == 0) {            //  2000 !!!
            save_time_step(xx, yy, Prey_old, i, "Prey-", DIR);
            save_time_step(xx, yy, Predator_old, i, "Predator-", DIR);
            save_time_step(xx, yy, PreyPhero_old, i, "PreyPhero-", DIR);
            save_time_step(xx, yy, PredatorPhero_old, i, "PredatorPhero-", DIR);
            save_time_step(xx, yy, Prey_old - Predator_old, i, "PreyPredator-", DIR);
        }
    }
    /////////////////////////////
    // End Ciclo em tempo
    /////////////////////////////

    

    cout << "Tfinal  = " << tt*delta_t<< endl;
    cout << "delta_t = " << delta_t<< endl;
    cout << "Num Iter = " << tt << endl;
    cout << "Num Ptos xx = " << xx << endl;
    cout << "Num Ptos yy = " << yy << endl;
    cout << "delta_x = " << delta_x<< endl;
    cout << "delta_y = " << delta_y<< endl;

    
    /////////////////////////////
    // Escrever resultados
    /////////////////////////////

    ofstream outfile_solucao1;
    outfile_solucao1.open(DIR2+"LastPrey.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            outfile_solucao1 << Prey_old(j,k) << "\t";
            if(k==yy-1)
            outfile_solucao1 << endl;
        }
    }
    outfile_solucao1.close();
    
    ofstream outfile_solucao2;
    outfile_solucao2.open(DIR2+"LastPredator.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            outfile_solucao2 << Predator_old(j,k) << "\t";
            if(k==yy-1)
            outfile_solucao2 << endl;
        }
    }
    outfile_solucao2.close();
    
    ofstream outfile_solucao3;
    outfile_solucao3.open(DIR2+"LastPreyPhero.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            outfile_solucao3 << PreyPhero_old(j,k) << "\t";
            if(k==yy-1)
            outfile_solucao3 << endl;
        }
    }
    outfile_solucao3.close();
    
    ofstream outfile_solucao4;
    outfile_solucao4.open(DIR2+"LastPredatorPhero.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            outfile_solucao4 << PredatorPhero_old(j,k) << "\t";
            if(k==yy-1)
                outfile_solucao4 << endl;
        }
    }
    outfile_solucao4.close();
    
    ofstream outfile_solucao5;
    outfile_solucao5.open(DIR2+"Topography.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            outfile_solucao5 << topography(j,k) << "\t";
            if(k==yy-1)
            outfile_solucao5 << endl;
        }
    }
    outfile_solucao5.close();

    ofstream outfile_solucao6;
    outfile_solucao6.open(DIR2+"LastOsDois.txt");
    for(int j=0;j<xx;j++){
        for(int k=0;k<yy;k++){
            outfile_solucao6 << Predator_old(j,k) + Prey_old(j,k) << "\t";
            if(k==yy-1)
                outfile_solucao6 << endl;
        }
    }
    outfile_solucao6.close();
    

    
    
    
    
    if (isAbort==1) {
        abort();
    }

    
    cout << COMM << endl;
    
    return 0;
}





    
    
    
    
    
    
    
    
    




