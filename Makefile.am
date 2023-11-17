bin_PROGRAMS = pt_replica_tuning

tparam = ./include/tparam.h \
         ./lib/tparam.c

pt_replica_tuning_SOURCES=./src/pt_replica_tuning.c \
							$(tparam) \
							./macro.h

AM_CFLAGS = -std=c99 -O3 -Wall -Wextra -Werror -pedantic -Wconversion

CLEANFILES = acceptances.dat input_tuning.dat 
