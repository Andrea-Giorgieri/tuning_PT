#ifndef TPARAM_C
#define TPARAM_C

#include"../include/macro.h"
#include"../include/tparam.h"

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// remove from input file white/empty lines and comments
// comments start with the charachter #
void remove_white_line_and_comments(FILE *input)
	{
	int temp_i;

	temp_i=getc(input);
	if(temp_i=='\n' || temp_i==' ' || temp_i=='\043') // scan for white lines and comments
	{
	ungetc(temp_i, input);

	temp_i=getc(input);
	if(temp_i=='\n' || temp_i==' ') // white line
		{
		do
		{
		temp_i=getc(input);
		}
		while(temp_i=='\n' || temp_i==' ');
		}
	ungetc(temp_i, input);

	temp_i=getc(input);
	if(temp_i=='\043')	// comment, \043 = ascii oct for #
		{
		do
		{
		temp_i=getc(input);
		}
		while(temp_i!='\n');
		}
	else
		{
		ungetc(temp_i, input);
		}

	remove_white_line_and_comments(input);
	}
	else
	{
	ungetc(temp_i, input);
	}
	}

// copy white/empty lines and comments from input file to output file
// comments start with the charachter #
void copy_white_line_and_comments(FILE *input, FILE *output)
	{
	int temp_i;

	temp_i=getc(input);
	if(temp_i=='\n' || temp_i==' ' || temp_i=='\043') // scan for white lines and comments
		{
		if(temp_i=='\n' || temp_i==' ') // white line
			{
			do
				{
				putc(temp_i, output);
				temp_i=getc(input);
				}
			while(temp_i=='\n' || temp_i==' ');
			}
		
		if(temp_i=='\043')	// comment, \043 = ascii oct for #
			{
			do
				{
				putc(temp_i, output);
				temp_i=getc(input);
				}
			while(temp_i!='\n');
			putc(temp_i, output);
			}
		else
			{
			ungetc(temp_i, input);
			}

		copy_white_line_and_comments(input, output);
		}
	else
		{
		ungetc(temp_i, input);
		}
	}

// read input file and write parameters to param
void readinput(char *in_file, TParam *param)
	{
	FILE *input;
	char str[STD_STRING_LENGTH], temp_str[STD_STRING_LENGTH];
	double temp_d;
	int temp_i, i;
	int err, end=1;

	// initialize to avoid mistakes
	param->d_N_replica_pt=1;

	input=fopen(in_file, "r"); // open the input file
	if(input==NULL)
		{
		fprintf(stderr, "Error in opening the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
		exit(EXIT_FAILURE);
		}
	else
		{
		while(end==1) // slide the file
			{
			remove_white_line_and_comments(input);
			
			err=fscanf(input, "%s", str);
			if(err!=1)
			{
				fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
				exit(EXIT_FAILURE);
			}

			if(strncmp(str, "target_acceptance", 17)==0)
					{
					err=fscanf(input, "%lf", &temp_d);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					
					if(temp_d >= 0 && temp_d <= 100) param->d_target_acc=temp_d;
					else
						{	
						fprintf(stderr, "Error: target_acceptance must be between 0 and 100 in %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					}
			
			else if(strncmp(str, "target_tolerance", 16)==0)
					{
					err=fscanf(input, "%lf", &temp_d);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					
					if(temp_d > 0) param->d_target_tolerance=temp_d;
					else
						{	
						fprintf(stderr, "Error: target_tolerance must be positive in %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					}
			
			else if(strncmp(str, "target_std", 10)==0)
					{
					err=fscanf(input, "%lf", &temp_d);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					
					if(temp_d > 0) param->d_target_std=temp_d;
					else
						{	
						fprintf(stderr, "Error: target_std must be positive in %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					}
					
			else if(strncmp(str, "tuning_step_coeff", 17)==0)
					{
					err=fscanf(input, "%lf", &temp_d);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					
					if(temp_d > 0) param->d_tuning_k=temp_d;
					else
						{	
						fprintf(stderr, "Error: tuning_step_coeff must be positive in %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					}
			
			else if(strncmp(str, "simulation_input_file", 21)==0)
					{
					err=fscanf(input, "%s", temp_str);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					strcpy(param->d_simulation_file, temp_str);
					}

			else if(strncmp(str, "tuning_analysis_file", 20)==0)
					{
					err=fscanf(input, "%s", temp_str);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					strcpy(param->d_analysis_file, temp_str);
					}
			
			else
				{
				fprintf(stderr, "Error: unrecognized option %s in the file %s (%s, %d)\n", str, in_file, __FILE__, __LINE__);
				exit(EXIT_FAILURE);
				}
			
			remove_white_line_and_comments(input);

			// check if the read line is the last one
			temp_i=getc(input);
			if(temp_i==EOF) end=0;
			else ungetc(temp_i, input);
			
			}

		fclose(input);
		
		end =1;
		input=fopen(param->d_simulation_file, "r"); // open the simulation input file
		if(input==NULL)
			{
			fprintf(stderr, "Error in opening the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
			exit(EXIT_FAILURE);
			}
		else
			{
			while(end==1) // slide the file
				{
				remove_white_line_and_comments(input);
			
				err=fscanf(input, "%s", str);
				if(err!=1)
					{
					fprintf(stderr, "Error in reading the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
					exit(EXIT_FAILURE);
					}
				
				if(strncmp(str, "N_replica_pt", 12)==0)
					{
					err=fscanf(input, "%d", &temp_i);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					param->d_N_replica_pt=temp_i;
					if(param->d_N_replica_pt<1)
						{
						fprintf(stderr, "Error: number of replica of parallel tempering must be greater than 0 (%s, %d)\n", __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					err=posix_memalign( (void **) &(param->d_pt_replica_coeff), (size_t) DOUBLE_ALIGN, (size_t) param->d_N_replica_pt * sizeof(double));
					if(err!=0)
						{
						fprintf(stderr, "Problems in allocating parallel tempering parameters! (%s, %d)\n", __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					for(i=0;i<param->d_N_replica_pt;i++)
						{
						err=fscanf(input, "%lf", &temp_d);
						if(err!=1)
							{
							fprintf(stderr, "Error in reading the file %s (%s, %d)\n", in_file, __FILE__, __LINE__);
							exit(EXIT_FAILURE);
							}
						param->d_pt_replica_coeff[i]=temp_d;
						}
					}
				
				else if(strncmp(str, "swap_acc_file", 13)==0)
					{ 
					err=fscanf(input, "%s", temp_str);
					if(err!=1)
						{
						fprintf(stderr, "Error in reading the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
						exit(EXIT_FAILURE);
						}
					strcpy(param->d_swap_acc_file, temp_str);
					}
				
				remove_white_line_and_comments(input);

				// check if the read line is the last one
				temp_i=getc(input);
				if(temp_i==EOF) end=0;
				else ungetc(temp_i, input);
				}
				
			fclose(input);
			
			}
		}
	}

// allocate arrays for saving acceptances
void init_arrays(double **acc, double **err_acc, TParam const * const param)
	{
	int i, err;
	
	if(param->d_N_replica_pt==1)
		{
		*acc=NULL;
		*err_acc=NULL;
		}
	else
		{	
		err=posix_memalign( (void **) acc, (size_t) DOUBLE_ALIGN, (size_t) ((param->d_N_replica_pt)-1) * sizeof(double));
		if(err!=0)
			{
			fprintf(stderr, "Problems in allocating the acceptances array (%s, %d)\n", __FILE__, __LINE__);
			exit(EXIT_FAILURE);
			}

		err=posix_memalign( (void **) err_acc, (size_t) DOUBLE_ALIGN, (size_t) ((param->d_N_replica_pt)-1) * sizeof(double));
		if(err!=0)
			{
			fprintf(stderr, "Problems in allocating the acceptances array (%s, %d)\n", __FILE__, __LINE__);
			exit(EXIT_FAILURE);
			}
		
		for(i=0; i<(param->d_N_replica_pt-1); i++) 
			{
			(*acc)[i] = 0.0;
			(*err_acc)[i] = 0.0;
			}
		}
	}

// read acceptances from swap_acc file and save them
void read_acceptances(double *acc, double *err_acc, TParam const * const param)
	{	
	int r, err;
	FILE *fp;
	
	fp=fopen(param->d_swap_acc_file, "r");
	if(fp!=NULL) // file exists -> read acceptances
		{
		remove_white_line_and_comments(fp);
		for(r=0;r<((param->d_N_replica_pt)-1);r++)
			{			
			err=fscanf(fp, "%*d %*d %*f %*f %lf %lf %*d %*d\n", &(acc[r]), &(err_acc[r]));
			if(err!=2)
				{
				fprintf(stderr, "Error in reading the file %s (%s, %d)\n", param->d_swap_acc_file, __FILE__, __LINE__);
				exit(EXIT_FAILURE);
				}
			}
		fclose(fp);
		}
	}

// print old acceptances for later analysis
void print_acceptances(double *acc, double *err_acc, TParam const * const param)
	{
	int i;
	FILE *fp;
	
	//open analysis file
	fp=fopen(param->d_analysis_file, "r");
	if(fp!=NULL) // file exists
		{
		fclose(fp);
		fp=fopen(param->d_analysis_file, "a");
		}
	else
		{
 		fp=fopen(param->d_analysis_file, "w");
		fprintf(fp, "#N_replica acc err_acc\n");
		}
	
	//print acceptance
	fprintf(fp, "%d ", param->d_N_replica_pt);
	for(i=0; i<(param->d_N_replica_pt-1); i++) fprintf(fp, "%lf %lf ", acc[i], err_acc[i]);
	fprintf(fp, "\n");
	fclose(fp);
	}

// calculate the new PT parameters
void tune_pt_parameters(int *N_replica, double **tuned_coeff, double *acc, TParam const * const param)
	{
	int i, sgn, err;
	double acc_mean, acc_std, acc_target_delta, coeff_diff, aux_a, aux_b;
	
	acc_mean = 0.0;
	acc_std = 0.0;
	for(i=0; i<(param->d_N_replica_pt-1); i++) // calculate meand and std of acceptances
		{
		acc_mean += acc[i];
		acc_std += acc[i]*acc[i];
		}
	acc_mean = acc_mean/(param->d_N_replica_pt-1);
	acc_std = sqrt(acc_std/(param->d_N_replica_pt-1) - acc_mean*acc_mean);
	
	acc_target_delta = acc_mean-param->d_target_acc;
	
	// if acc_mean is outide the tolerance range, adjust N_replica accordingly
	if(fabs(acc_target_delta) > param->d_target_tolerance && acc_std < param->d_target_std)
		{
		sgn = 1;
		if(acc_target_delta < 0.0) sgn = -1;
		*N_replica = param->d_N_replica_pt - sgn; //N_replica increased/decreased by 1 if acc_mean </> target_acc
		
		err=posix_memalign( (void **) tuned_coeff, (size_t) DOUBLE_ALIGN, (size_t) (*N_replica) * sizeof(double));
		if(err!=0)
			{
			fprintf(stderr, "Problems in allocating the coefficients array (%s, %d)\n", __FILE__, __LINE__);
			exit(EXIT_FAILURE);
			}
		
		// new replica coefficients are linear interpolation of old ones,
		// keeping first and last fixed
		(*tuned_coeff)[0] = param->d_pt_replica_coeff[0];
		for(i=1; i<(*N_replica-1); i++)
			{
			aux_a = param->d_pt_replica_coeff[i+sgn];
			aux_b = param->d_pt_replica_coeff[i];
			(*tuned_coeff)[i] = (i*aux_a + (*N_replica-i)*aux_b)/(*N_replica);
			}
		(*tuned_coeff)[*N_replica-1] = param->d_pt_replica_coeff[param->d_N_replica_pt-1];
		}
	
	// if acc_mean is inside the tolerance range, adjust the replica coefficients
	else
		{
		*N_replica = param->d_N_replica_pt;
		
		err=posix_memalign( (void **) tuned_coeff, (size_t) DOUBLE_ALIGN, (size_t) (*N_replica) * sizeof(double));
		if(err!=0)
			{
			fprintf(stderr, "Problems in allocating the coefficients array (%s, %d)\n", __FILE__, __LINE__);
			exit(EXIT_FAILURE);
			}
		
		// coeff_diff(r,r+1) -> coeff_diff(r,r+1) + aux_a*(a(r,r+1)-<a>) : 
		// distance between coefficients of two replicas decreased/increased if their acc is lower/higher than acc_mean,
		// first and last coefficients fixed
		(*tuned_coeff)[0] = param->d_pt_replica_coeff[0];
		coeff_diff = 0.0;
		aux_a = param->d_tuning_k*(param->d_pt_replica_coeff[*N_replica-1]-param->d_pt_replica_coeff[0])/(*N_replica);
		for(i=1; i<(*N_replica-1); i++)
			{
			coeff_diff += aux_a*(acc[i-1]-acc_mean)/100.0;
			(*tuned_coeff)[i] = param->d_pt_replica_coeff[i] + coeff_diff;
			}
		(*tuned_coeff)[*N_replica-1] = param->d_pt_replica_coeff[*N_replica-1];
		}
	}

// to print tuned parameters to output_file insted of simulation_file
/*void print_tuned_parameters(int N_replica, double *tuned_coeff, TParam const * const param)
	{
	int i;
	FILE *fp;
	
	//open output file
	fp=fopen(param->d_output_file, "w");
	
	//print tuned pt parameters
	fprintf(fp, "%d ", N_replica);
	for(i=0; i<N_replica; i++) fprintf(fp, "%lf ", tuned_coeff[i]);
	fprintf(fp, "\n");
	fclose(fp);
	}
*/

// edit simulation_file with the new PT parameters
void print_tuned_parameters(int N_replica, double *tuned_coeff, TParam const * const param)
	{
	int i, temp_i, err, end=1;
	double temp_d;
	char name[STD_STRING_LENGTH], str[STD_STRING_LENGTH];
	FILE *fp, *fp_tmp;
	
	//open simulation file and a tmp copy
	fp=fopen(param->d_simulation_file, "r");
	if(fp==NULL)
		{
		fprintf(stderr, "Error in opening the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
		exit(EXIT_FAILURE);
		}
	strcpy(name, param->d_simulation_file);
	strcat(name, "_tmp");
	fp_tmp=fopen(name, "r");
	i=0;
	while(fp_tmp!=NULL) //change tmp name if file exists
		{
		fclose(fp_tmp);
		strcpy(name, param->d_simulation_file);
		sprintf(str, "_tmp_%d", i);
		strcat(name,  str);
		fp_tmp=fopen(name, "r");
		i++;
		}
	fp_tmp=fopen(name, "w");
	
	while(end==1) //slide the files
		{
		copy_white_line_and_comments(fp, fp_tmp);
		err=fscanf(fp, "%s", str);
		if(err!=1)
			{
			fprintf(stderr, "Error in reading the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
			exit(EXIT_FAILURE);
			}
		
		//copy the file replacing PT parameters following "N_replica_pt"
		fprintf(fp_tmp, str);
		if(strncmp(str, "N_replica_pt", 12)==0)
			{
			err=fscanf(fp, "%d", &temp_i); //advance on old file
			if(err!=1)
				{
				fprintf(stderr, "Error in reading the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
				exit(EXIT_FAILURE);
				}
			fprintf(fp_tmp, " %d", N_replica); //write on new file
			
			for(i=0;i<param->d_N_replica_pt;i++) //advance on old file
				{
				err=fscanf(fp, "%lf", &temp_d);
				if(err!=1)
					{
					fprintf(stderr, "Error in reading the file %s (%s, %d)\n", param->d_simulation_file, __FILE__, __LINE__);
					exit(EXIT_FAILURE);
					}
				}
			
			for(i=0;i<N_replica;i++) //write on new file
				{
				fprintf(fp_tmp, " %lf", tuned_coeff[i]);
				}
			}
		copy_white_line_and_comments(fp, fp_tmp);
		
		// check if the read line is the last one
		temp_i=getc(fp);
		if(temp_i==EOF) end=0;
		else ungetc(temp_i, fp);
		}
	
	fclose(fp);
	fclose(fp_tmp);
	
	// remove the old file
	err = remove(param->d_simulation_file);
	if(err!=0)
		{
		fprintf(stderr, "Error in removing the file %s\n", param->d_simulation_file);
		exit(EXIT_FAILURE);
		}
		
	// rename the tmp file as the old file
	err = rename(name, param->d_simulation_file);
	if(err!=0)
		{
		fprintf(stderr, "Error in renaming the file %s\n", name);
		exit(EXIT_FAILURE);
		}
	}

#endif

