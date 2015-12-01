#include"Neuron.h"
#include<Math.h>

void Neuron::setup(){
    return;
}

void Neuron::calc(){
    u=0;
    for(int i=0; i < w.size(); i++){
        u+=w[i]*x[i];
    }
    y = sigmoid(u);
    return;
}

float Neuron::sigmoid(float x){
    return 1.0f / ( 1.0f + (float)exp(- beta * x));
}
float Neuron::sigmoid_dash(float x){
    return 2.0*(1.0f-sigmoid(x))*sigmoid(x);
}

void Neuron::disp(){
    calc();
    printf("---Neuron  -----\n");
    for(int i =0; i < w.size(); i++){
        printf("w[%d]: %f\n",i,w[i]);
    }
    for(int i =0; i < x.size(); i++){
        printf("x[%d]: %f\n",i,x[i]);
    }
    
    printf("u: %f\n",u);
    printf("y: %f\n",y);
    return;
}
