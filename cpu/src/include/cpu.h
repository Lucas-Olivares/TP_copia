#ifndef CPU_MAIN_H_
#define CPU_MAIN_H_

#include "cpu_globals.h"
#include "iniciar_cpu.h"
#include "cpu_memoria.h"
#include "cpu_kernel_dispatch.h"
#include "cpu_kernel_interrupt.h"
//Var globales
t_log* cpu_logger;
t_log* cpu_logger_debug;
t_config* cpu_config;

int fd_cpu_dispatch;
int fd_cpu_interrupt;
int fd_memoria;
int fd_kernel;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PUERTO_ESCUCHA_DISPATCH;
char* PUERTO_ESCUCHA_INTERRUPT;
char* CANTIDAD_ENTRADAS_TLB;
char* ALGORITMO_TLB;
//utilizo char y no int por que las funciones definidas en shared reciben char
#endif