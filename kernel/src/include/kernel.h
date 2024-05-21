#ifndef KERNEL_MAIN_H_
#define KERNEL_MAIN_H_

#include "kernel_globals.h"
#include "iniciar_kernel.h"
typedef enum {
    NEW,
    READY,
    BLOCKED,
    EXEC,
    EXIT
} estado_proceso;
typedef struct {
    uint8_t AX, BX, CX, DX;
    uint32_t EAX, EBX, ECX, EDX;
    uint32_t SI, DI, PC;
} Registros_CPU;
typedef struct
{
    int PID;
    uint32_t program_counter;
    int quantum;
    Registros_CPU registros_cpu;;
    estado_proceso estado;
} PCB;

//Var globales
t_log* kernel_logger;
t_log* kernel_logger_debug;
t_config* kernel_config;
t_queue* cola_new;
t_queue* cola_ready;
int fd_kernel;
int fd_memoria;
int fd_io;
int fd_cpu_dispatch;
int fd_cpu_interrupt;
int ultimo_pid;

char* PUERTO_ESCUCHA;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* IP_CPU;
char* PUERTO_CPU_DISPATCH;
char* PUERTO_CPU_INTERRUPT;
char* ALGORITMO_PLANIFICACION;
int QUANTUM;
char** RECURSOS;
char** INSTANCIAS_RECURSOS;
//estos dos ultimos son listas si quisieramos trabajar con los elementos
//podriamos aplicar la funcion split (ver /commons/string.h)
int GRADO_MULTIPROGRAMACION;
#endif