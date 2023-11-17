#ifndef MACRO_H
#define MACRO_H

#include"../config.h"

#define MIN_VALUE 1.0e-13

#define INT_ALIGN 16
#define DOUBLE_ALIGN 32

#define STD_STRING_LENGTH 150 // standarg lenght of unknown strings

// way to print a macro: if
// #define val1 val2
// then QUOTEME(val1) give the string "val2"
#define _QUOTEME(x) #x
#define QUOTEME(x) _QUOTEME(x)

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

// to activate posix_memalign in stdlib.h
#define _POSIX_C_SOURCE 200809L

#endif
