//
//  NeuralNetwork.h
//  
//
//  Created by 茂山 丈太郎 on 2015/11/07.
//
//
#include<vector>
#include<random>
#include "Neuron.h"
#include "Dataset.h"


using namespace std;

class NeuralNetwork{
public:
    
    NeuralNetwork(){};
    NeuralNetwork(int in_num, int interm_num , int out_num,Dataset data){
        for(int i = 0;i < out_num; i++){
            Neuron n = Neuron(NUM_INTERM);
            output_layer.push_back(Neuron(NUM_INTERM));
        }
        for(int i = 0;i < interm_num; i++){
            Neuron n = Neuron(NUM_INPUT);
            interm_layer.push_back(n);
        }
        for(int i = 0;i < in_num; i++){
            input_layer.push_back(Neuron(1));
        }
        dataset = data;
        printf("NeuralNetwork is now build:\n");
        printf("Size of input_layer: %lu\n",input_layer.size());
        printf("Size of interm_layer:%lu\n",interm_layer.size());
        printf("Size of output_layer:%lu\n",output_layer.size());
    }
    vector<Neuron> input_layer;
    vector<Neuron> interm_layer;
    vector<Neuron> output_layer;
    vector<Neuron> output_layer_before;
    Dataset dataset;
    
    
    void update_bp(int );
    void setup();
    void disp();

    bool isFinished();
    bool makeNoiseFlag=false;
    float sigmoid(float);
    float sigmoid_dash(float);
    float ita = 0.2f;
    float beta = 1.0f;
    float noise_hi=0.5;
    float noise_lo = -0.5;
    vector<float>_noise;
    vector<float> makeNoise(){
        vector<float>noise;
        for(int i=0; i<NUM_INPUT;i++){
            noise.push_back(static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(noise_hi-noise_lo))));
        }
        return noise;
    }
};