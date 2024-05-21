#ifndef MEMORIA_MAIN_H_
#define MEMORIA_MAIN_H_

#include"memoria_globals.h"
#include "iniciar_memoria.h"
#include "memoria_kernel.h"
#include "memoria_io.h"
#include "memoria_cpu.h"

//Var globales
int fd_memoria; //Creo el filedescriptor para la memoria y para c/u de los modulos  que se conecten
int fd_io;
int fd_cpu;
int fd_kernel;

t_log* memoria_logger;
t_log* memoria_logger_debug;
t_config* memoria_config;

char* PUERTO_ESCUCHA;
int TAM_MEMORIA;
int TAM_PAGINA;
char* PATH_INSTRUCCIONES;
int RETARDO_RESPUESTA;
#endif