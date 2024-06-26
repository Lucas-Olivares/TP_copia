#ifndef IO_GLOBALS_H_
#define IO_GLOBALS_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/shared.h>

#include <commons/log.h>
#include <commons/config.h>

//Var globales
extern t_log* io_logger;
extern t_log* io_logger_debug;
extern t_config* io_config;

extern int fd_kernel;
extern int fd_memoria;

extern char* TIPO_INTERFAZ;
extern int TIEMPO_UNIDAD_TRABAJO;
extern char* IP_KERNEL;
extern char* PUERTO_KERNEL;
extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* PATH_BASE_DIALFS;
extern int BLOCK_SIZE;
extern int BLOCK_COUNT;
#endif