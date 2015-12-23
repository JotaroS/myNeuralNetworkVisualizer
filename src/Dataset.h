//
//  Dataset.h
//  myNeuralNetoworkVisualizer
//
//  Created by 茂山 丈太郎 on 2015/11/07.
//
//

#include <stdio.h>
#include <vector>
#define NUM_INPUT 100
#define NUM_INTERM 49
#define NUM_OUTPUT 5
using namespace std;

class Dataset{
public:
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