#ifndef KERNEL_GLOBALS_H_
#define KERNEL_GLOBALS_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/shared.h>

#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/queue.h>
//Var globales
extern t_log* kernel_logger;
extern t_log* kernel_logger_debug;
extern t_config* kernel_config;

extern int fd_kernel;
extern int fd_memoria;
extern int fd_io;
extern int fd_cpu_dispatch;
extern int fd_cpu_interrupt;

extern char* PUERTO_ESCUCHA;
extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* IP_CPU;
extern char* PUERTO_CPU_DISPATCH;
extern char* PUERTO_CPU_INTERRUPT;
extern char* ALGORITMO_PLANIFICACION;
extern int QUANTUM;
extern char** RECURSOS;
extern char** INSTANCIAS_RECURSOS;
//estos dos ultimos son listas si quisieramos trabajar con los elementos
//podriamos aplicar la funcion split (ver /commons/string.h)
extern int GRADO_MULTIPROGRAMACION;
#endif