#ifndef CPU_GLOBALS_H_
#define CPU_GLOBALS_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/shared.h>

#include <commons/log.h>
#include <commons/config.h>

//Var globales
extern t_log* cpu_logger;
extern t_log* cpu_logger_debug;
extern t_config* cpu_config;

extern int fd_cpu_dispatch;
extern int fd_cpu_interrupt;
extern int fd_memoria;
extern int fd_kernel;

extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* PUERTO_ESCUCHA_DISPATCH;
extern char* PUERTO_ESCUCHA_INTERRUPT;
extern char* CANTIDAD_ENTRADAS_TLB;
extern char* ALGORITMO_TLB;
//utilizo char y no int por que las funciones definidas en shared reciben char
#endif