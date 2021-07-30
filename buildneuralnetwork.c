// Author: Lalitha Viswanathan
// Affiliation: Tata Consultancy Services 
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include "buildneuralnetwork.h"
#define HIDDEN_NODES 30
#define INPUT_NODES 6 
#define HIDDEN_LAYERS 1 
//header file for building ann
float weights_input[INPUT_NODES][HIDDEN_LAYERS][HIDDEN_NODES];
//6 input params 1 hidden layer with 30 nodes
float weights_hidden[HIDDEN_LAYERS][HIDDEN_NODES],weights_input[INPUT_NODES][HIDDEN_LAYERS][HIDDEN_NODES],
weights_input_new[INPUT_NODES][HIDDEN_LAYERS][HIDDEN_NODES],weights_hidden_new[HIDDEN_LAYERS][HIDDEN_NODES],
weights_hidden_old[HIDDEN_LAYERS][HIDDEN_NODES],weights_input_old[INPUT_NODES][HIDDEN_LAYERS][HIDDEN_NODES],
outputs_hidden[HIDDEN_LAYERS][HIDDEN_NODES]; // weights for output layer 
float output_gradient,input_gradient[HIDDEN_LAYERS][HIDDEN_NODES];
float learning_rate=0.1,momentum=1;
float final_output,expected_output=1,output_gradient;
float inputs[INPUT_NODES];
void set_random_weights();
void copy_weights();
void compute_outputs();
void compute_gradient();
void recompute_weights();
void train_ann();
void read_input();
int counter=0;
float* final_output_array=NULL;
//builds nn
// set random weights for input nodes, hidden layers and nodes therein
void set_random_weights()
{
       int inputnodes,hiddennodes;
        for(inputnodes=0;inputnodes<INPUT_NODES;inputnodes++)
		{ 
			for (int hiddenlayers = 0; hiddenlayers < HIDDEN_LAYERS; hiddenlayers++) {
				for (hiddennodes = 0; hiddennodes < HIDDEN_NODES; hiddennodes++)
				{
					weights_input_old[inputnodes][hiddenlayers][hiddennodes] = 0.3333;
					weights_input[inputnodes][hiddenlayers][hiddennodes] = 0.3333;
					weights_input_new[inputnodes][hiddenlayers][hiddennodes] = weights_input[inputnodes][hiddenlayers][hiddennodes];
				}
			}
		}
		for (int hiddenlayers = 0; hiddenlayers < HIDDEN_LAYERS; hiddenlayers++) {
			for (inputnodes = 0; inputnodes < HIDDEN_NODES; inputnodes++)
			{
				weights_hidden_old[hiddenlayers][inputnodes] = 0.3333;
				weights_hidden[hiddenlayers][inputnodes] = 0.3333;
				weights_hidden_new[hiddenlayers][inputnodes] = weights_hidden[hiddenlayers][inputnodes];
				outputs_hidden[hiddenlayers][inputnodes] = 0;
			}
		}
}

void compute_outputs()
{
		for (int hiddenlayer = 0, counter=0; hiddenlayer < HIDDEN_NODES; hiddenlayer++)
		{
			for (int hiddennode = 0; hiddennode < HIDDEN_NODES; hiddennode++)
			{
				outputs_hidden[hiddenlayer][hiddennode] = 0;
				for (int inputnode = 0; inputnode < INPUT_NODES; inputnode++) 
				{
					outputs_hidden[hiddenlayer][hiddennode] += inputs[inputnode] * 
						weights_input[inputnode][hiddenlayer][hiddennode];
				}
				outputs_hidden[hiddenlayer][hiddennode] = 1 / (1 + exp(-outputs_hidden[hiddenlayer][hiddennode]));
				final_output += outputs_hidden[hiddenlayer][hiddennode] * weights_hidden[hiddenlayer][hiddennode];
			}
			final_output = 1 / (1 + exp(-final_output));
			final_output_array = (float*)realloc(final_output_array, sizeof(float) * (counter + 2));
			final_output_array[counter++] = final_output;

		}
	}

// Compute gradient
void compute_gradient()
{
		output_gradient=(expected_output-final_output)*(1-final_output)*final_output;
}

void recompute_weights()
{
	int hiddennode,inputnode;
	for (int hiddenlayer = 0; hiddenlayer < HIDDEN_LAYERS; hiddenlayer++) {
		for (hiddennode = 0; hiddennode < HIDDEN_NODES; hiddennode++)
		{
			weights_hidden_new[hiddenlayer][hiddennode] = (output_gradient * learning_rate * 
				outputs_hidden[hiddenlayer][hiddennode]) + 
				weights_hidden[hiddenlayer][hiddennode]/*+(momentum*(weights_hidden[x]-weights_hidden_old[x]))*/;
			input_gradient[hiddenlayer][hiddennode] = outputs_hidden[hiddenlayer][hiddennode] * 
				(1 - outputs_hidden[hiddenlayer][hiddennode]) * output_gradient * weights_hidden[hiddenlayer][hiddennode];
			for (inputnode = 0; inputnode < INPUT_NODES; inputnode++) {
				for (int hiddenlayer = 0; hiddenlayer < HIDDEN_LAYERS; hiddenlayer++) {
					weights_input_new[inputnode][hiddenlayer][hiddennode] = (input_gradient[hiddenlayer][hiddennode] * 
						learning_rate * 
						inputs[inputnode]) + weights_input[inputnode][hiddenlayer][hiddennode]/*+(momentum*(weights_input[y][x]-weights_input_old[y][x]))*/;
				}
			}
		}
	}
}

void copy_weights()
{
	for (int hiddenlayer = 0; hiddenlayer < HIDDEN_LAYERS; hiddenlayer++) {
		for (int hiddennode = 0; hiddennode < HIDDEN_NODES; hiddennode++)
		{
			weights_hidden_old[hiddenlayer][hiddennode] = weights_hidden[hiddenlayer][hiddennode];
			weights_hidden[hiddenlayer][hiddennode] = weights_hidden_new[hiddenlayer][hiddennode];
			weights_hidden_new[hiddenlayer][hiddennode] = 0;
			for (int inputnode = 0; inputnode < INPUT_NODES; inputnode++)
			{
				weights_input_old[inputnode][hiddenlayer][hiddennode] = weights_input[inputnode][hiddenlayer][hiddennode];
				weights_input[inputnode][hiddenlayer][hiddennode] = weights_input_new[inputnode][hiddenlayer][hiddennode];
				weights_input_new[inputnode][hiddenlayer][hiddennode] = 0;
			}
		}
	}
}

void write_weights()
{
	FILE *fp;
	int hiddennode,inputnode;
	fp=fopen("final_weights.txt","w+");
	for (int hiddenlayer = 0; hiddenlayer < HIDDEN_LAYERS; hiddenlayer++) {
		for (hiddennode = 0; hiddennode < HIDDEN_NODES; hiddennode++)
		{
			for (inputnode = 0; inputnode < INPUT_NODES; inputnode++)
				fprintf(fp, " %f ", weights_input[hiddennode][hiddenlayer][inputnode]);
			fprintf(fp, "%f \n", weights_hidden[hiddenlayer][hiddennode]);
		}
	}
	fclose(fp);
}
float max_input_value()
{
	FILE* fp;
	long size;
	int counter=0,i,j;
	float* arr1,*arr2,*arr3,*arr4,*arr5,*arr6,temp,max_val=0,val;
	fp=fopen("input.txt","r");
	while(!feof(fp))
	{
		int retval = fscanf(fp,"%f",&val);
		if(val>max_val)
			max_val=val;
	}
	fclose(fp);
return max_val;
}
main()
{
	FILE* fp;
	int i,no_of_epochs=0;
	float sum_of_squares=1;
	float max_value=max_input_value();
	printf("max input value is %f\n",max_value);
	set_random_weights();
	while(sum_of_squares>0.9)
	{
	sum_of_squares=0;
	counter=0;
	final_output_array=NULL;
	fp=fopen("input.txt","r");
	while(fp)
	{
		if(feof(fp))
			break;
		int retval = fscanf(fp,"%f %f %f %f %f %f\n",&inputs[0],&inputs[1],&inputs[2],&inputs[3],&inputs[4],&inputs[5]);
		for(i=0;i<INPUT_NODES;i++)
			inputs[i]/=max_value;
		compute_outputs();
		compute_gradient();
		recompute_weights();
		copy_weights();
	final_output=0;	
	}
	int retval = fclose(fp);
	for(i=0;i<counter;i++)
		sum_of_squares+=(final_output_array[i]-1)*(final_output_array[i]-1);
	sum_of_squares/=counter;	
	printf(" counter=%d epoch number = %d sum_of_squares= %f %f %f\n",counter,no_of_epochs,sum_of_squares,weights_hidden[15],weights_hidden[16]);
	no_of_epochs++;
	}
	write_weights();
}
