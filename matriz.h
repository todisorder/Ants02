
class my_matrix {
public:
    int dim1,dim2;
    double * elementos;
    
    
    my_matrix (int m,int n)
    {
        dim1=m;
        dim2=n;
        elementos=new double[m*n];
    }
    //    ~my_matrix()
    //    {
    //        delete[] elementos;
    //    }
    
    
    double &operator() (int i,int j){
        if(i>=dim1){
            cout << "erro x" << endl;
            exit(1);}
        if(j>=dim2){
            cout << "erro y" << endl;
            exit(1);}
        
        return elementos[i*dim2+j];
    }
    

    
    
    void print (){
        int i,j;
        for(i=0;i<dim1;i++)
            for(j=0;j<dim2;j++){
                cout << operator()(i,j) << " ";
                if(j==dim2-1)
                    cout << endl;
            }
    }
    
    
    
    void matrix (string s)
    {
        int i,j;
        if(s=="id")
        {
            for(i=0;i<dim1;i++)
                for(j=0;j<dim2;j++)
                    operator()(i,j)=1.0;
        }
        
        if(s=="zero")
        {
            for(i=0;i<dim1;i++)
                for(j=0;j<dim2;j++)
                    operator()(i,j)=0.0;
        }
        
        if(s=="pi")
        {
            for(i=0;i<dim1;i++)
                for(j=0;j<dim2;j++)
                    operator()(i,j)=3.14;
        }
        
        if(s=="euler")
        {
            for(i=0;i<dim1;i++)
                for(j=0;j<dim2;j++)
                    operator()(i,j)=2.718;
        }
        
    }
    
    
};

// Ver http://condor.depaul.edu/ntomuro/courses/262/notes/lecture3.html
my_matrix operator+(const my_matrix &M1, const my_matrix &M2)
{
    my_matrix soma (M1.dim1, M1.dim2);
    for (int i=0; i< soma.dim1 ; i++) {
        for (int j=0; j<soma.dim2; j++) {
            soma.elementos[i*M1.dim2+j] = M1.elementos[i*M1.dim2+j] + M2.elementos[i*M1.dim2+j];
        }
    }
    return soma;
}
my_matrix operator-(const my_matrix &M1, const my_matrix &M2)
{
    my_matrix soma (M1.dim1, M1.dim2);
    for (int i=0; i< soma.dim1 ; i++) {
        for (int j=0; j<soma.dim2; j++) {
            soma.elementos[i*M1.dim2+j] = M1.elementos[i*M1.dim2+j] - M2.elementos[i*M1.dim2+j];
        }
    }
    return soma;
}
