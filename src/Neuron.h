#include<vector>
#include <stdlib.h>

using namespace std;

class Neuron{
public:
    Neuron(){setup();}
    Neuron(int w_num){
        srand((unsigned)time(NULL));
        for(int i=0; i <w_num;i++){
            w.push_back((float)(rand()%1000)*0.001-0.5);
            x.push_back((float)(rand()%1000)*0.001-0.5);
        }
    }
    
    Neuron(vector<float> w_){
        w = w_;
    }
    
    void setup();
    void calc(); 			//caluculate output based on some function;
    void init_w();
    void disp();
    float sigmoid(float );
    float sigmoid_dash(float );
    vector<float> w;	
    vector<float> x;
    float y,u;
    
    float beta = 1.0f;
};