#ifndef IO_MAIN_H_
#define IO_MAIN_H_

#include "io_globals.h"
#include "iniciar_io.h"

#include "io_memoria.h"
#include "io_kernel.h"

//Var globales
t_log* io_logger;
t_log* io_logger_debug;
t_config* io_config;

int fd_kernel;
int fd_memoria;

char* TIPO_INTERFAZ;
int TIEMPO_UNIDAD_TRABAJO;
char* IP_KERNEL;
char* PUERTO_KERNEL;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PATH_BASE_DIALFS;
int BLOCK_SIZE;
int BLOCK_COUNT;
#endif