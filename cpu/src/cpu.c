#include "include/cpu.h"


int main(void) {
    //decir_hola("CPU");
    
    iniciar_cpu();

    //Iniciar CPU como servidor de kernel para mensajes de dispatch
    fd_cpu_dispatch = iniciar_servidor(PUERTO_ESCUCHA_DISPATCH, cpu_logger, "Servidor CPU iniciado para mensajes dispatch");

    //Iniciar CPU como servidor de kernel para mensajes de interrupt
    fd_cpu_interrupt = iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT, cpu_logger, "Servidor CPU iniciado para mensajes interrupt");

    //Conectar CPU como cliente de memoria
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);

    log_info(cpu_logger, "Esperando clientes...");

    //Esperar cliente para mensajes dispatch (KERNEL)
    fd_kernel = esperar_cliente(fd_cpu_dispatch, cpu_logger, "KERNEL-Dispatch");

    //Esperar cliente para mensajes interrupt (KERNEL)
    fd_kernel = esperar_cliente(fd_cpu_interrupt, cpu_logger, "KERNEL-Interrupt");

    pthread_t hilo_kernel_dispatch;
    pthread_create(&hilo_kernel_dispatch, NULL, (void*) cpu_atender_kernel_dispatch, NULL);
	pthread_detach(hilo_kernel_dispatch);

    pthread_t hilo_kernel_interrupt;
	pthread_create(&hilo_kernel_interrupt, NULL, (void*) cpu_atender_kernel_interrupt, NULL);
	pthread_detach(hilo_kernel_interrupt);

    pthread_t hilo_kernel_memoria;
    pthread_create(&hilo_kernel_memoria, NULL, (void*) cpu_atender_memoria, NULL);
	pthread_join(hilo_kernel_memoria, NULL);
    
    return EXIT_SUCCESS;
}
