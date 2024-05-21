#ifndef UTILS_SHARED_H_
#define UTILS_SHARED_H_

#include <stdlib.h>
#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
#include<pthread.h>

//copio struct por si se necesitacen a futuro, no lo se :/
typedef enum
{
	MENSAJE,
	PAQUETE,

	//IO
	IO_GEN_SLEEP

}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

/**
* @fn    decir_hola
* @brief Imprime un saludo al nombre que se pase por parámetro por consola.
*/
void decir_hola(char* quien);

int crear_conexion(char *ip, char* puerto);

void dormir(char* , int);

int iniciar_servidor(char* puerto, t_log* un_logger, char* msj_server);
int esperar_cliente(int socket_servidor, t_log* un_logger, char* mensaje);
int recibir_operacion(int socket_cliente); //puede ser util a futuro

void eliminar_paquete(t_paquete* );
void* serializar_paquete(t_paquete* , int );
void enviar_paquete(t_paquete* , int );

void enviar_mensaje(char* , int);
void recibir_mensaje(int, t_log*);

void liberar_conexion(int socket_cliente);

t_buffer* recibir_todo_el_buffer(int);

#endif