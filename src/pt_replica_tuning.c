#ifndef PT_REPLICA_TUNING_C
#define PT_REPLICA_TUNING_C

#include"../include/macro.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../include/tparam.h"

void real_main(char *in_file)
	{
	TParam param;

    int N_replica;
	double *acc, *err_acc, *tuned_coeff;

    // read tuning input file
    readinput_tuning(in_file, &param);
	
	if (param.d_N_replica_pt>1)
		{
		// init acceptances array
		init_arrays_tuning(&acc, &err_acc, &param);
		
		// read swap acceptances
		read_acceptances_tuning(acc, err_acc, &param);
		
		// print acceptances before tuning
		print_acceptances_tuning(acc, err_acc, &param);
		
		// calculate new PT parameters
		tune_pt_parameters(&N_replica, &tuned_coeff, acc, err_acc, &param);
		
		// write new PT parameters
		print_tuned_parameters(N_replica, tuned_coeff, &param);
		
		// free arrays
		free(acc);
		free(err_acc);
		free(tuned_coeff);
		}
	else
		{
		N_replica = 1;
		*tuned_coeff = param.d_pt_replica_coeff[0];
		
		// write PT parameters
		print_tuned_parameters(N_replica, tuned_coeff, &param);
		}
	}


void print_template_input(void)
	{
	FILE *fp;

	fp=fopen("template_input.example", "w");

	if(fp==NULL)
    {
		fprintf(stderr, "Error in opening the file template_input.example (%s, %d)\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
    }
	else
	{
		fprintf(fp,"#file names\n");
		fprintf(fp,"simulation_input_file input\n");
		fprintf(fp,"tuning_output_file    tuned_parameters.dat\n");
		fprintf(fp,"tuning_analysis_file  tuning_acc.dat\n");
		fprintf(fp,"\n#tuning parameters\n");
		fprintf(fp,"target_acceptance 30.0\n");
		fprintf(fp,"target_tolerance   1.0\n");
		fprintf(fp,"target_std         1.0\n");
		fprintf(fp,"tuning_step_coeff  0.1\n");
		fclose(fp);
    }
	}

int main (int argc, char **argv)
    {
    char in_file[STD_STRING_LENGTH];

    if(argc != 2)
		{
		printf("\nTuning of Parallel Tempering parameters implemented by Andrea Giorgieri (andrea.giorgieri.pi@gmail.com) for the yang-mills package\n");
		printf("Usage: %s input_file \n\n", argv[0]);

		#ifdef __INTEL_COMPILER
			printf("\tcompiled with icc\n");
		#elif defined(__clang__)
			printf("\tcompiled with clang\n");
		#elif defined( __GNUC__ )
			printf("\tcompiled with gcc version: %d.%d.%d\n",
				__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
		#endif

		print_template_input();

		return EXIT_SUCCESS;
		}
    else
		{
		if(strlen(argv[1]) >= STD_STRING_LENGTH)
			{
			fprintf(stderr, "File name too long. Increse STD_STRING_LENGTH in /include/macro.h\n");
			return EXIT_SUCCESS;
			}
		else
			{
			strcpy(in_file, argv[1]);
			real_main(in_file);
			return EXIT_SUCCESS;
			}
		}
	}

#endif
