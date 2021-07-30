// Author: Lalitha Viswanathan
// Compute neural network values for training set 

//this computes the values for the training set and stores the values in a file
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
void process_valuesfromfile(char*);
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
	FILE* filepointerread, *filepointerwrite;

	char str[500],*entirestringinfile;

	float totalscore=0,frac_of_zeroes=0,variance=0,moment_of_skewness=0,
		max_length_continuous_stretch=0,gaussian_mean=0,no_zeroes=0,
		mean=0,var_sum=0,totalgscore=0,non_numbers=0;

	int length,continuous_stretch,flag=1,totalength=0;

	float* integer_array,*gaussian_array;

	filepointerread=fopen(fname,"r");

	filepointerwrite=fopen("input_test.txt","w");

	entirestringinfile=NULL, integer_array=NULL, gaussian_array=NULL;
	while(filepointerread)
        {
	
		fgets(str,80,filepointerread);
		if(feof(filepointerread))
			break;
		if(str[0]=='>')
		{
		if(!entirestringinfile)
		{
			continue;
		}
		totalength=strlen(entirestringinfile);
		integer_array=(float *)malloc(totalength*sizeof(float));
		for(length=0;length<totalength;length++)	
		{
		if((entirestringinfile[length]!='S')&&(entirestringinfile[length]!='*')&&(!isspace(entirestringinfile[length])))
		{
			switch(entirestringinfile[length])
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
				
					if(entirestringinfile[length]=='S')
				
						integer_array[length]=99.00;
				
					if(entirestringinfile[length]=='*')
				
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
	/****************************************************/
	if(totalength>1)
	variance=(var_sum*var_sum)/(totalength-1);

	if(variance>0.0)

		moment_of_skewness=(((var_sum)*(var_sum)*(var_sum))/(totalength-1))/sqrt(pow(variance,3));
	/****************************************************/
	//compute length of max continuous stretch
	for(length=0;length<strlen(entirestringinfile)-1;length++)
	{			
	
		continuous_stretch=length;
	
	while((entirestringinfile[continuous_stretch]!='S')&&(entirestringinfile[continuous_stretch]!='*')&&(entirestringinfile[continuous_stretch]!='0')&&(!isspace(entirestringinfile[continuous_stretch])))

		continuous_stretch++;
	
	if(continuous_stretch>max_length_continuous_stretch) 
	
		max_length_continuous_stretch=continuous_stretch;
	
	}
	/****************************************************/
	//compute gaussian mean
	
//	printf("before computing gaussian mean %d \n",totalength);
	
	gaussian_array=(float*)calloc((totalength+1),sizeof(float));
	
	for(length=1;length<totalength;length++)
	{
	
		if((integer_array[length-1]!=99)&&(integer_array[length-1]!=199)&&(integer_array[length+1]!=99)&&(integer_array[length+1]!=199)&&(integer_array[length]!=99)&&(integer_array[length]!=199))
		{
	
		gaussian_array[length-1]=( integer_array[length-1]*.368+integer_array[length]+integer_array[length+1]*.368);
			if(gaussian_array[length-1]>0)
				gaussian_array[length-1]/=(0.368+1+0.368);	
			totalgscore+=gaussian_array[length-1];
		}
		else
			non_numbers++;
	}
	if((non_numbers+totalength>0)&&(totalgscore>0))
	gaussian_mean=totalgscore/(non_numbers+totalength);
	
	free(gaussian_array);
	/****************************************************/
	
	fprintf(filepointerwrite,"%f %f %f %f %f %2.4f\n",totalscore,frac_of_zeroes,variance,moment_of_skewness,max_length_continuous_stretch,gaussian_mean);
	
	totalscore=frac_of_zeroes=variance=moment_of_skewness=
	
	no_zeroes=totalength=mean=var_sum=continuous_stretch=
	
	max_length_continuous_stretch=gaussian_mean=totalgscore=non_numbers=0;

	free(integer_array);
	free(entirestringinfile);
	entirestringinfile=NULL;
	flag=1;
	}
	else
	{
		strncpy(str,str,80);
		if(flag)
		{
		if(isspace(str[strlen(str)-1]))
			str[strlen(str)-1]='\0';
		entirestringinfile=(char*)malloc(sizeof(char)*80);
		entirestringinfile[0] = '\0';
		strncpy(entirestringinfile,str,strlen(str));
		entirestringinfile[strlen(str)]='\0';
		flag=0;
		}
		else
		{
		entirestringinfile=(char*)realloc(entirestringinfile,sizeof(char)*(strlen(entirestringinfile)+80));
		strncat(entirestringinfile,str,strlen(str));
		if(isspace(entirestringinfile[strlen(entirestringinfile)-1]))
			entirestringinfile[strlen(entirestringinfile)-1]='\0';
		}	
	}
	}

	fclose(filepointerread);

	fclose(filepointerwrite);
}

