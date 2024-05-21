#include "include/io.h"

int main(int argc, char** argv) {
    //decir_hola("una Interfaz de Entrada/Salida");
    if (argc < 2) {
        fprintf(stderr, "Usar: %s </home/utnso/tp-2024-1c-Grupo-SO-/entradasalida/io.config>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    iniciar_io(argc, argv); //abrir modulo con: ./bin/entradasalida /home/utnso/tp-2024-1c-Grupo-SO-/entradasalida/io.config

    //conectar como cliente con memoria
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);

    //conectar como cliente con kernel
    fd_kernel = crear_conexion(IP_KERNEL, PUERTO_KERNEL);

    //enviar mensaje a memoria
    //enviar_mensaje("Hola soy I/O", fd_memoria);
    //enviar mensaje a cpu
    //enviar_mensaje("Hola soy I/O", fd_kernel);
	pthread_t hilo_kernel;
	pthread_create(&hilo_kernel, NULL, (void*) io_atender_kernel, NULL);
	pthread_detach(hilo_kernel);
	pthread_t hilo_memoria;
	pthread_create(&hilo_memoria, NULL, (void*) io_atender_memoria, NULL);
    pthread_join(hilo_memoria,NULL);

	log_destroy(io_logger);
	config_destroy(io_config);
	liberar_conexion(fd_memoria);
    liberar_conexion(fd_kernel);
    
    return EXIT_SUCCESS;
}