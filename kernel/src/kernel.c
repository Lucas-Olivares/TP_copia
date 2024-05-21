#include "include/kernel.h"
void kernel_atender_io();
void kernel_atender_memoria();
void kernel_atender_cpu_dispatch();
void kernel_atender_cpu_interrupt();
void crear_pcb(int);
void mover_procesos_ready();

int main(void) {
    //decir_hola("Kernel");
    //Inicio de las estructuras del kernel
    iniciar_kernel();

    //iniciar kernel como servidor
    fd_kernel = iniciar_servidor(PUERTO_ESCUCHA, kernel_logger, "Servidor de kernel iniciado");
    //conectar kernel como cliente a memoria
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA);
    //conectar kernel como cliente con cpu
    fd_cpu_dispatch=crear_conexion(IP_CPU, PUERTO_CPU_DISPATCH);
    fd_cpu_interrupt=crear_conexion(IP_CPU, PUERTO_CPU_INTERRUPT);
    //Esperar conexion de IO(lo dejo para el final, por que la f esperar posee elementos bloqueantes)
    fd_io = esperar_cliente(fd_kernel, kernel_logger, "IO");
	
    cola_new = queue_create();
    cola_ready = queue_create();

	mover_procesos_ready();
    //Atender a IO (prueba)
	//enviar_mensaje("adkadskASFASDFASDAS",fd_io);
	//dormir("12",fd_io);
    pthread_t hilo_cpu_dispatch;
    pthread_create(&hilo_cpu_dispatch, NULL, (void*) kernel_atender_cpu_dispatch, NULL);
	pthread_detach(hilo_cpu_dispatch);
    pthread_t hilo_cpu_interrupt;
    pthread_create(&hilo_cpu_interrupt, NULL, (void*) kernel_atender_cpu_interrupt, NULL);
	pthread_detach(hilo_cpu_interrupt);
	pthread_t hilo_memoria;
    pthread_create(&hilo_memoria, NULL, (void*) kernel_atender_memoria, NULL);
	pthread_detach(hilo_memoria);
	pthread_t hilo_io;
    pthread_create(&hilo_io, NULL, (void*) kernel_atender_io, NULL);
	pthread_join(hilo_io, NULL);

    return EXIT_SUCCESS;
}
void crear_pcb(int quantum) {
    PCB *pcb = malloc(sizeof(PCB));
    if (pcb == NULL)
        printf("Error al crear el PCB\n");
    // Incrementar el PID y asignarlo al nuevo PCB
    ultimo_pid++;
    pcb->PID = ultimo_pid;
    pcb->program_counter = 0;
    pcb->quantum = quantum;
    pcb->estado = NEW;
    // El PCB se agrega a la cola de los procesos NEW
    queue_push(cola_new, pcb);
    // Crear un buffer para almacenar el mensaje con el último PID
    char mensaje[100];
    // Usar sprintf para formatear el mensaje con el último PID
    sprintf(mensaje, "Se crea el proceso %d en NEW\n", ultimo_pid);
    log_info(kernel_logger, mensaje);
}

void mover_procesos_ready() {
    // Obtener el grado de multiprogramación del archivo de configuración
    int grado_multiprogramacion = GRADO_MULTIPROGRAMACION;
    // Calcular la cantidad de procesos en la cola de NEW y en la cola de READY
    int cantidad_procesos_new = queue_size(cola_new);
    int cantidad_procesos_ready = queue_size(cola_ready);
    // Verificar si el grado de multiprogramación lo permite
    if (cantidad_procesos_ready < grado_multiprogramacion){
        // Mover procesos de la cola de NEW a la cola de READY
        while (cantidad_procesos_new > 0 && cantidad_procesos_ready < grado_multiprogramacion){
            // Seleccionar el primer proceso de la cola de NEW
            PCB *proceso_nuevo = queue_peek(cola_new);
            // Borro el proceso que acabo de seleccionar DE LA COLA
            queue_pop(cola_new);
            // Cambiar el estado del proceso a READY
            proceso_nuevo->estado = READY;
            // Agregar el proceso a la cola de READY
            queue_push(cola_ready, proceso_nuevo);
            cantidad_procesos_ready++;
            // Reducir la cantidad de procesos en la cola de NEW
            cantidad_procesos_new--;
        }
    }
    if (cantidad_procesos_new == 0)
        printf("Ya no hay más procesos en la cola de NEW.\n");
    else
        printf("El grado de multiprogramación máximo ha sido alcanzado. %d procesos permanecerán en la cola de NEW.\n",cantidad_procesos_new);
}

void kernel_atender_cpu_dispatch(){
    bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_cpu_dispatch);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_cpu_dispatch, kernel_logger);
		    break;
/*	    case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		    break;*/
	    case -1:
	    	log_error(kernel_logger, "CPU Dispatch se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}

void kernel_atender_cpu_interrupt(){
    bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_cpu_interrupt);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_cpu_interrupt, kernel_logger);
		    break;
/*	    case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		    break;*/
	    case -1:
	    	log_error(kernel_logger, "CPU Interrupt se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}

void kernel_atender_io(){
    bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_io);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_io, kernel_logger);
		    break;
/*	    case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		    break;*/
	    case -1:
	    	log_error(kernel_logger, "IO se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}

void kernel_atender_memoria(){
    bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_memoria);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_memoria, kernel_logger);
		    break;
/*	    case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		    break;*/
	    case -1:
	    	log_error(kernel_logger, "Memoria se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}
