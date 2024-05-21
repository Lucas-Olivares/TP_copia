#include "include/memoria.h"

int main(void) {
    //decir_hola("Memoria");

    //Se inicializaron las estructuras de memoria
    iniciar_memoria();

    //Iniciar server de memoria(de la shared.c)
    fd_memoria = iniciar_servidor(PUERTO_ESCUCHA, memoria_logger, "Servidor de memoria iniciada");
    
    log_info(memoria_logger, "Esperando clientes...");
    //Esperar cliente(CPU)
    fd_cpu = esperar_cliente(fd_memoria, memoria_logger, "CPU");

    //Esperar cliente(KERNEL)
    fd_kernel = esperar_cliente(fd_memoria, memoria_logger, "KERNEL"); 

    //Esperar cliente(IO)
    fd_io = esperar_cliente(fd_memoria, memoria_logger, "IO");
    
    //Atender a IO (prueba)
	pthread_t hilo_cpu;
	pthread_create(&hilo_cpu, NULL, (void*) memoria_atender_cpu, NULL);
	pthread_detach(hilo_cpu);

	pthread_t hilo_kernel;
	pthread_create(&hilo_kernel, NULL, (void*) memoria_atender_kernel, NULL);
	pthread_detach(hilo_kernel);

	pthread_t hilo_io;
	pthread_create(&hilo_io, NULL, (void*) memoria_atender_io, NULL);
	pthread_join(hilo_io, NULL);

    //Finalizar memoria
    
    
    return EXIT_SUCCESS;
}


//Nota: en este tp memoria actua unicamente como servidor para los otros 3 modulos