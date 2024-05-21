#ifndef MEMORIA_GLOBALS_H_
#define MEMORIA_GLOBALS_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/shared.h>

#include <commons/log.h>
#include <commons/config.h>

//Var globalesatender_memoria_kernel();
extern t_log* memoria_logger;
extern t_log* memoria_logger_debug;
extern t_config* memoria_config;

extern int fd_memoria; //Creo el filedescriptor para la memoria y para c/u de los modulos  que se conecten
extern int fd_io;
extern int fd_cpu;
extern int fd_kernel;

extern char* PUERTO_ESCUCHA;
extern int TAM_MEMORIA;
extern int TAM_PAGINA;
extern char* PATH_INSTRUCCIONES;
extern int RETARDO_RESPUESTA;

#endif