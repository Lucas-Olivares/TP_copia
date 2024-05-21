#include <utils/shared.h>
//t_log* memoria_logger;
void decir_hola(char* quien) {
    printf("Hola desde %s!!\n", quien);
}

int crear_conexion(char *ip, char* puerto){
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	// Ahora vamos a crear el socket.
	//int socket_cliente = fd_conexion;
	int socket_cliente = socket(server_info->ai_family,
                         	server_info->ai_socktype,
                         	server_info->ai_protocol);


	// Ahora que tenemos el socket, vamos a conectarlo

	connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);

	freeaddrinfo(server_info);

	return socket_cliente;
}


//Modifico la siguiente funcion ya que los valores van a depender 
//de cada modulo al iniciar las configs.
//De igual manera ocurre con msj; para memoria dira memoria inicializada,
//para cpu cpu inicializada, etc
int iniciar_servidor(char* puerto, t_log* un_logger, char* msj_server){
	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, puerto, &hints, &servinfo);

	// Creamos el socket de escucha del servidor
	socket_servidor = socket(servinfo->ai_family,
                         		 servinfo->ai_socktype,
                         		 servinfo->ai_protocol);
	// Estas 2 lineas permiter liberar los puertos y no tener que esperar para volver a conectar los modulos
	setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));
	// Asociamos el socket a un puerto

	bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);

	// Escuchamos las conexiones entrantes

	listen(socket_servidor, SOMAXCONN);


	freeaddrinfo(servinfo);
	log_info(un_logger, "SERVER: %s", msj_server);

	return socket_servidor;
}

//Nuevamente el logger dependera de cada cconexion
int esperar_cliente(int socket_servidor, t_log* un_logger, char* mensaje){
	/* Quitar esta línea cuando hayamos terminado de implementar la funcion
	assert(!"no implementado!");*/

	// Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor, NULL, NULL);
	log_info(un_logger, "Se conecto un cliente %s", mensaje);

	return socket_cliente;
}

//REVISAR 
int recibir_operacion(int socket_cliente){
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else{
		close(socket_cliente);
		return -1;
	}
}


void* serializar_paquete(t_paquete* paquete, int bytes){
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}

void eliminar_paquete(t_paquete* paquete){
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}
void enviar_mensaje(char* mensaje, int socket_cliente){
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	eliminar_paquete(paquete);
}

void* recibir_buffer(int* size, int socket_cliente){
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente,t_log* logger){
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}


void dormir(char* mensaje, int socket_cliente){
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = IO_GEN_SLEEP;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	eliminar_paquete(paquete);

}

t_buffer* recibir_todo_el_buffer(int conexion){
	t_buffer* un_buffer = malloc(sizeof(t_buffer));
	if(recv(conexion, &(un_buffer->size), sizeof(int), MSG_WAITALL) > 0){
		un_buffer->stream=malloc(un_buffer->size);
		if(recv(conexion, un_buffer->stream, un_buffer->size, MSG_WAITALL))
			return un_buffer;
		else
			{perror("error al recibir void* del buffer");
			exit(EXIT_FAILURE);
		}
	}
	else{
		perror("error al recibir el tamaño del buffer");
		exit(EXIT_FAILURE);
	}
	return un_buffer;
}


