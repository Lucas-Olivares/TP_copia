#include "../include/iniciar_kernel.h"

void iniciar_kernel(){
    iniciar_logs();
    iniciar_configs();
    mostrar_configs();
}

void iniciar_logs(){
    kernel_logger = log_create("cliente.log", "LOGGER_KERNEL", true, LOG_LEVEL_INFO);
	if( kernel_logger == NULL){
		perror ("Algo raro paso con el log, nose pudo crear o encontrar el archivo");
		exit(EXIT_FAILURE);
	}
}

/*t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("cliente.log", "LOGGER_KERNEL", true, LOG_LEVEL_INFO);
	if( nuevo_logger == NULL){
		perror ("Algo raro paso con el log, nose pudo crear o encontrar el archivo");
		exit(EXIT_FAILURE);
	}
	return nuevo_logger;
}*/

void iniciar_configs(){
    kernel_config = config_create("kernel.config");
    
    if (kernel_config == NULL) {
        // No se pudo crear el config, terminemos el programa
		perror("Error al intentar cargar el config.");
        exit(EXIT_FAILURE);
        }	
    
    PUERTO_ESCUCHA = config_get_string_value(kernel_config, "PUERTO_ESCUCHA");
    IP_MEMORIA = config_get_string_value(kernel_config, "IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(kernel_config, "PUERTO_MEMORIA");
    IP_CPU = config_get_string_value(kernel_config, "IP_CPU");
    PUERTO_CPU_DISPATCH = config_get_string_value(kernel_config, "PUERTO_CPU_DISPATCH");
    PUERTO_CPU_INTERRUPT = config_get_string_value(kernel_config, "PUERTO_CPU_INTERRUPT");
    ALGORITMO_PLANIFICACION = config_get_string_value(kernel_config, "ALGORITMO_PLANIFICACION");
    QUANTUM = config_get_int_value(kernel_config, "QUANTUM");
    RECURSOS = config_get_array_value(kernel_config, "RECURSOS");
    INSTANCIAS_RECURSOS = config_get_array_value(kernel_config, "INSTANCIAS_RECURSOS");
    GRADO_MULTIPROGRAMACION = config_get_int_value(kernel_config, "GRADO_MULTIPROGRAMACION");
}

void mostrar_configs(){
    log_info(kernel_logger, "PUERTO_ESCUCHA: %s", PUERTO_ESCUCHA);
    log_info(kernel_logger, "IP_MEMORIA: %s", IP_MEMORIA);
    log_info(kernel_logger, "PUERTO_MEMORIA: %s", PUERTO_MEMORIA);
    log_info(kernel_logger, "IP_CPU: %s", IP_CPU);
    log_info(kernel_logger, "PUERTO_CPU_DISPATCH: %s", PUERTO_CPU_DISPATCH);
    log_info(kernel_logger, "PUERTO_CPU_INTERRUPT: %s", PUERTO_CPU_INTERRUPT);
    log_info(kernel_logger, "ALGORITMO_PLANIFICACION: %s", ALGORITMO_PLANIFICACION);
    log_info(kernel_logger, "QUANTUM: %d", QUANTUM);
    log_info(kernel_logger, "[Recursos]:%s-%s-%s",RECURSOS[0],RECURSOS[1],RECURSOS[2]);
    log_info(kernel_logger, "[INSTANCIAS_RECURSOS]:%s-%s-%s",INSTANCIAS_RECURSOS[0],INSTANCIAS_RECURSOS[1],INSTANCIAS_RECURSOS[2]);
    log_info(kernel_logger, "GRADO_MULTIPROGRAMACION: %d", GRADO_MULTIPROGRAMACION);
}