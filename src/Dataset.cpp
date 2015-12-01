//
//  Dataset.cpp
//  myNeuralNetoworkVisualizer
//
//  Created by 茂山 丈太郎 on 2015/11/07.
//
//

#include "Dataset.h"
#include <stdlib.h>
using namespace std;


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