//  
//
//  Created by 茂山 丈太郎 on 2015/11/07.
//
//

#include<vector>
#include "NeuralNetwork.h"
#include <math.h>

void NeuralNetwork::setup(){
    _noise=makeNoise();
    for(int i=0; i < NUM_INPUT;i++){input_layer[i].y = dataset.data[i];}
    for(int i=0; i < NUM_INTERM;i++){
        for(int j=0; j < NUM_INPUT;j++){
            
            interm_layer[i].x[j] =( static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.0)))<0.0)?
            _noise[j]:
            dataset.data[j];
        }
        interm_layer[i].calc();
    }
    for(int i=0; i < NUM_OUTPUT;i++){
        for(int j=0; j < NUM_INTERM;j++){
            output_layer[i].x[j] = interm_layer[j].y;
        }
        output_layer[i].calc();
    }
    return;
}
void NeuralNetwork::update_bp(int target){
    //output layer weight coeff update
    vector<float>delta_k;
    output_layer_before=output_layer;
    setup();
    
    for(int k=0; k < output_layer.size(); k++){
        float delta = 0;
        delta = (output_layer[k].y-(k==dataset.target?1:0));
        delta*= sigmoid_dash(output_layer[k].u);
        for(int i=0; i < output_layer[k].w.size();i++){
            output_layer[k].w[i] = output_layer[k].w[i] - ita * delta * interm_layer[i].y;
        }
        delta_k.push_back(delta);
    }
    //interm layer weight coeff update
    for(int i=0; i < interm_layer.size(); i++){
        float delta = 0;
        for(int k=0; k<output_layer.size();k++){
            delta+=output_layer[k].w[i]*delta_k[k];
        }
        delta*=sigmoid_dash(interm_layer[i].u);
        for(int j=0; j < interm_layer[i].w.size();j++){
            interm_layer[i].w[j] = interm_layer[i].w[j] - ita * delta * input_layer[j].y;
        }
    }
    return;
}

void NeuralNetwork::disp(){
    printf("output layer neuron output value: \n [ ");
    for(int i = 0; i <output_layer.size();i++){
        printf("%.3f ",output_layer[i].y);
    }
    printf("]\n");
    return;
}

bool NeuralNetwork::isFinished(){
    float mse;
    for(int i=0;i<NUM_OUTPUT;i++){
        for(int k=0; k < NUM_INTERM;k++)
            mse += pow((output_layer_before[i].w[k]-output_layer[i].w[k]), 2);
    }
    if(mse<0.00001)return true;
    else return false;
}

float NeuralNetwork::sigmoid(float x){
    return 1 / ( 1 + exp(- beta * (x)));
}
float NeuralNetwork::sigmoid_dash(float x){
    //alpha = 2.0
    return 2.0*(1.0-sigmoid(x))*sigmoid(x);
}
