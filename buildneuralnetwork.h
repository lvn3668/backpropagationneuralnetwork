#include<stdio.h>
#define HIDDEN_NODES 30
#define INPUT_NODES 6 
# define HIDDEN_LAYERS 1
//header file for building ann
float weights_input[INPUT_NODES][HIDDEN_LAYERS][HIDDEN_NODES];
// Author: Lalitha Viswanathan
// Affiliation: Tata Consultancy Services 
//6 input params 1 hidden layer with 30 nodes
float weights_hidden[HIDDEN_LAYERS][HIDDEN_NODES],
weights_input[INPUT_NODES][HIDDEN_LAYERS][HIDDEN_NODES],
weights_input_new[INPUT_NODES][HIDDEN_LAYERS][HIDDEN_NODES],
weights_hidden_new[HIDDEN_LAYERS][HIDDEN_NODES];
//weights for output layer
float outputs_hidden[HIDDEN_LAYERS][HIDDEN_NODES];
float output_gradient,input_gradient[HIDDEN_LAYERS][HIDDEN_NODES];
float learning_rate,momentum;
float final_output,expected_output,output_gradient;
float inputs[INPUT_NODES];
void set_random_weights();
void copy_weights();
void compute_outputs();
void compute_gradient();
void recompute_weights();
void train_ann();
