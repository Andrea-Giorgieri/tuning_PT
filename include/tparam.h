#ifndef TPARAM_H
#define TPARAM_H

#include"macro.h"

#include<stdio.h>
#include<stdlib.h>

typedef struct TParam {

	// parallel tempering parameters
	int d_N_replica_pt;		    // numbers of replica used in parallel tempering
	double* d_pt_replica_coeff; // replica coefficients
	
	// tuning parameters
	double d_target_acc;
	double d_target_tolerance;
	double d_target_std;
	double d_tuning_k;
	
	// file names
	char d_simulation_file[STD_STRING_LENGTH]; //input file of the simulation
	char d_swap_acc_file[STD_STRING_LENGTH];   //data file with acceptances
	char d_output_file[STD_STRING_LENGTH];     //to print tuned coefficients
	char d_analysis_file[STD_STRING_LENGTH];   //to save acceptances

	
} TParam;

void remove_white_line_and_comments_tuning(FILE *input);
void copy_white_line_and_comments_tuning(FILE *input, FILE *output);
void readinput_tuning(char *in_file, TParam *param);
void init_arrays_tuning(double **acc, double **err_acc, TParam const * const param);
void read_acceptances_tuning(double *acc, double *err_acc, TParam const * const param);
void print_acceptances_tuning(double *acc, double *err_acc, TParam const * const param);
void tune_pt_parameters(int *N_replica, double **tuned_coeff, double *acc, double *err_acc, TParam const * const param);
void print_tuned_parameters(int N_replica, double *tuned_coeff, TParam const * const param);

#endif
