#include <iostream>



class my_vector{
      public:
             int dim;
             double * elementos;
    
      my_vector (int n)
      {
                dim=n;
                elementos=new double[n];}
    ~my_vector()
        {
            delete[] elementos;
        }

    

      double &operator() (int i){
             return elementos[i];
      }                
      
      void preencher(double v){
           
                    for(int i=0;i<dim;i++)
                    operator()(i)=v;
      }
      
      void print (){
           int i;
           for(i=0;i<dim;i++)
           cout << operator()(i) << endl;
           }
    
};
