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
	double d_target_acc;		// target acceptance mean
	double d_target_tolerance;	// tolerance on target_acc
	double d_target_std;		// target acceptance std
	double d_tuning_k;			// coefficient for the tuning step
	
	// file names
	char d_simulation_file[STD_STRING_LENGTH]; //input file of the simulation
	char d_swap_acc_file[STD_STRING_LENGTH];   //data file with acceptances
	char d_analysis_file[STD_STRING_LENGTH];   //to save acceptances

} TParam;

void remove_white_line_and_comments(FILE *input);
void copy_white_line_and_comments(FILE *input, FILE *output);
void readinput(char *in_file, TParam *param);
void init_arrays(double **acc, double **err_acc, TParam const * const param);
void read_acceptances(double *acc, double *err_acc, TParam const * const param);
void print_acceptances(double *acc, double *err_acc, TParam const * const param);
void tune_pt_parameters(int *N_replica, double **tuned_coeff, double *acc, TParam const * const param);
void print_tuned_parameters(int N_replica, double *tuned_coeff, TParam const * const param);

#endif
