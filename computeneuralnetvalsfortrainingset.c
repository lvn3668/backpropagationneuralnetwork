// Author: Lalitha Viswanathan
// Affiliation: Tata Consultancy Services 
//this computes the values for the training set and stores the values in a file
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
void process_valuesfromfile(char*);
#define LENGTH 80
#define GAUSSIANMEANCONSTANT 0.368
main(int argc, char*argv[])
{
	char fname[100];
	if(argc!=2)
	{
		printf("Run as <compute_ann> <filename>. The filename should be a set of integers, representing the aminoacid\n");
		exit(1);
	}
	strcpy(fname, argv[1]);
	printf("Filename containing input string is %s\n",fname);	
	process_valuesfromfile(fname);
}
void process_valuesfromfile(char* fname)
{
	FILE* filereadpointer, *filewritepointer;

	char str[500],*entirestringfromfile;

	float totalscore=0,frac_of_zeroes=0,variance=0,
		moment_of_skewness=0,max_length_continuous_stretch=0,
		gaussian_mean=0,no_zeroes=0,mean=0,var_sum=0,totalgscore=0,
		non_numbers=0;

	int length,continuous_stretch,flag=1,totalength=0;

	float* integer_array,*gaussian_array;

	filereadpointer=fopen(fname,"r");

	filewritepointer=fopen("input.txt","w");

	entirestringfromfile=NULL, integer_array=NULL, gaussian_array=NULL;
	while(filereadpointer)
        {
	
		fgets(str,80,filereadpointer);
		if(feof(filereadpointer))
			break;
		if(str[0]=='>')
		{
		if(!entirestringfromfile)
		{
			continue;
		}
		totalength=strlen(entirestringfromfile);
		integer_array=(float *)malloc(totalength*sizeof(float));
		for(length=0;length<totalength;length++)	
		{
		if((entirestringfromfile[length]!='S')&&(entirestringfromfile[length]!='*')&&(!isspace(entirestringfromfile[length])))
		{
			switch(entirestringfromfile[length])
			{
				case '0':
				integer_array[length]=0;	
				break;
				case '1':
				totalscore+=1;
				integer_array[length]=1;	
				break;
				case '2':
				totalscore+=2;
				integer_array[length]=2;	
				break;
				case '3':
				totalscore+=3;
				integer_array[length]=3;	
				break;
				case '4':
				totalscore+=4;
				integer_array[length]=4;	
				break;
				case '5':
				totalscore+=5;
				integer_array[length]=5;	
				break;
				case '6':
				totalscore+=6;
				integer_array[length]=6;	
				break;
				case '7':
				totalscore+=7;
				integer_array[length]=7;	
				break;
				case '8':
				totalscore+=8;
				integer_array[length]=8;	
				break;
				case '9':
				totalscore+=9;
				integer_array[length]=9;	
				break;
				}
					}
				
					if(integer_array[length]==0)
				
						no_zeroes++;
				
					if(entirestringfromfile[length]=='S')
				
						integer_array[length]=99.00;
				
					if(entirestringfromfile[length]=='*')
				
						integer_array[length]=199.00;
				}
				//compute mean
				
				if(totalength>1)
				mean=totalscore/(totalength-1);
				//compute frac_of_zeroes
				
				if(totalength>1)
				frac_of_zeroes=no_zeroes/(totalength-1);
				
				
	for(length=0;length<totalength;length++)
	{
		if((integer_array[length]!=99.00)&&(integer_array[length]!=199.00))
				
			var_sum+=(integer_array[length]-mean);
	}
	if(totalength>1)
	variance=(var_sum*var_sum)/(totalength-1);

	if(variance>0.0)
		moment_of_skewness=(((var_sum)*(var_sum)*(var_sum))/(totalength-1))/sqrt(pow(variance,3));
	//compute length of max continuous stretch
	for(length=0;length<strlen(entirestringfromfile)-1;length++)
	{			
	
		continuous_stretch=length;
	
	while((entirestringfromfile[continuous_stretch]!='S')&&(entirestringfromfile[continuous_stretch]!='*')&&(entirestringfromfile[continuous_stretch]!='0')&&(!isspace(entirestringfromfile[continuous_stretch])))

		continuous_stretch++;
	
	if(continuous_stretch>max_length_continuous_stretch) 
	
		max_length_continuous_stretch=continuous_stretch;
	
	}
	//compute gaussian mean
	/*****************************************************************/
	gaussian_array=(float*)calloc((totalength+1),sizeof(float));
	
	for(length=1;length<totalength;length++)
	{
	
		if((integer_array[length-1]!=99)&&(integer_array[length-1]!=199)&&(integer_array[length+1]!=99)&&(integer_array[length+1]!=199)&&(integer_array[length]!=99)&&(integer_array[length]!=199))
		{
	
		gaussian_array[length-1]=( integer_array[length-1]*GAUSSIANMEANCONSTANT+integer_array[length]+integer_array[length+1]*GAUSSIANMEANCONSTANT);
			if(gaussian_array[length-1]>0)
				gaussian_array[length-1]/=(GAUSSIANMEANCONSTANT+1+GAUSSIANMEANCONSTANT);	
			totalgscore+=gaussian_array[length-1];
		}
		else
			non_numbers++;
	}
	if((non_numbers+totalength>0)&&(totalgscore>0))
	gaussian_mean=totalgscore/(non_numbers+totalength);
	
	free(gaussian_array);
	/********************************************************************/
	fprintf(filewritepointer,"%f %f %f %f %f %2.4f\n",totalscore,frac_of_zeroes,variance,moment_of_skewness,max_length_continuous_stretch,gaussian_mean);
	
	totalscore=frac_of_zeroes=variance=moment_of_skewness=
	
	no_zeroes=totalength=mean=var_sum=continuous_stretch=
	
	max_length_continuous_stretch=gaussian_mean=totalgscore=non_numbers=0;

	free(integer_array);
	free(entirestringfromfile);
	entirestringfromfile=NULL;
	flag=1;
	}
	else
	{
		strncpy(str,str,LENGTH);
		if(flag)
		{
		if(isspace(str[strlen(str)-1]))
			str[strlen(str)-1]='\0';
		entirestringfromfile=(char*)malloc(sizeof(char)*LENGTH);
		strncpy(entirestringfromfile,str,strlen(str));
		entirestringfromfile[strlen(str)]='\0';
		flag=0;
		}
		else
		{
		entirestringfromfile=(char*)realloc(entirestringfromfile,sizeof(char)*(strlen(entirestringfromfile)+80));
		strncat(entirestringfromfile,str,strlen(str));
		if(isspace(entirestringfromfile[strlen(entirestringfromfile)-1]))
			entirestringfromfile[strlen(entirestringfromfile)-1]='\0';
		}
	}
	}

	fclose(filereadpointer);

	fclose(filewritepointer);
}

