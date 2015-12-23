#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<random>
#include<vector>
int NUM_INPUT= 100;
int NUM_INTERM =50;
int NUM_OUTPUT =5;
using namespace::std;

class Dataset{
public:
  //here comes data
    Dataset(){};
    Dataset(int _target){
        float org_data[] = {0};
        data = vector<float>(*org_data);
        target = _target;
    }
    
    int target = 1;
    void makeData();
    void disp();
    void makeNoise();
    vector<float>data;
    
private:
    
};

void Dataset::makeData(){
    data.clear();
    for(int i=0; i<NUM_INPUT;i++){
        float r = (float)rand()/(float)RAND_MAX;
        data.push_back (r);
    }
}
void Dataset::disp(){
    printf("Data::%d [",target);
    for(int i=0; i<NUM_INPUT;i++){
        printf("%f ",data[i]);
        
    }printf("]\n");
}
void Dataset::makeNoise(){
    printf("Making noise...\n");
    for(int i=0; i < data.size();i++){
        
        data[i]+=(float)(rand()%10/2.0f-0.25);
    }
    return;
}
////////////////////////////////////////////////////////////////////////////////////
class Neuron{
public:
    Neuron(){setup();}
    Neuron(int w_num){
      //        srand((unsigned)time(NULL));
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


////////////////////////////////////////////////////////////////////////////////////
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
        //printf("NeuralNetwork is now build:\n");
        //printf("Size of input_layer: %lu\n",input_layer.size());
        //printf("Size of interm_layer:%lu\n",interm_layer.size());
        //printf("Size of output_layer:%lu\n",output_layer.size());
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
  float noise_prob = 0.0;
    vector<float>_noise;
    vector<float> makeNoise(){
        vector<float>noise;
        for(int i=0; i<NUM_INPUT;i++){
            noise.push_back(static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(noise_hi-noise_lo))));
        }
        return noise;
    }
};
void NeuralNetwork::setup(){

    _noise=makeNoise();
    for(int i=0; i < NUM_INPUT;i++){input_layer[i].y = dataset.data[i];}
    for(int i=0; i < NUM_INTERM;i++){
        for(int j=0; j < NUM_INPUT;j++){
            
            interm_layer[i].x[j] =( static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.0)))<noise_prob)?
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
    //    printf("mse=%f\n",mse);
    if(mse<0.00001f)return true;
    else return false;
}

float NeuralNetwork::sigmoid(float x){
    return 1 / ( 1 + exp(- beta * (x)));
}
float NeuralNetwork::sigmoid_dash(float x){
    //alpha = 2.0
    return 2.0*(1.0-sigmoid(x))*sigmoid(x);
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
int main (int argc,char **argv){
  FILE *fp;

  if((fp=fopen("out_eta.csv","w"))==NULL){
    printf("file open err!!\n");
    return 1;
  }

  int count =0;
	vector<Dataset>datas;	
	printf("Data Making\n");
	Dataset data = Dataset(1);
	for(int i=0;i<NUM_OUTPUT;i++){
		data.target = i;
		data.makeData();
		datas.push_back(data);
		datas[i].disp();
	}


	for(float k=0.05;k<2;k+=0.05){
	  fprintf(fp,"%f,",k);
	} fprintf(fp,"\b\n");

	for(int n=0;n<100;n+=10){
	  for(float k=0.05 ;k<2;k+=0.05){
	      //NUM_INTERM=k;
	      
	  NeuralNetwork net = NeuralNetwork(NUM_INPUT,NUM_INTERM,NUM_OUTPUT,datas[0]);
	  net.setup();
	  net.ita=k;
	  net.noise_prob=n/100.0;
	  printf("Fitting for eta =%f, noise = %f\n",net.ita,net.noise_prob);	
	  bool flag = true;
	  do{
	    count++;
	    flag = true;
	    for(int i=0; i < NUM_OUTPUT; i++){
	      net.dataset = datas[i];
	      net.update_bp(i);
	      if(net.output_layer[i].y<0.9)flag = false;
	    }
	    if(net.isFinished() && flag)break;	    	    
	    if(count>2999)break;
	  }while(!net.isFinished()||count>3000);
	  if(flag)printf("Finish Fitting on count $$ %d $$\n",count*NUM_OUTPUT);
	  else{ printf("                                    Neural Network Broken!!\n"); count = 3000;}
	  fprintf(fp,"%d,",count*NUM_OUTPUT);
	  count=0;
	  net.disp();
	  }
	  fprintf(fp,"\b\n");
	}
	
	fclose(fp);

/*	for(int i=0; i < NUM_OUTPUT; i++){
		printf("TEST CASE NUM_%d ",i);
		net.dataset = datas[i];
		net.setup();
		net.disp();
		}*/	
    return 0;
}
