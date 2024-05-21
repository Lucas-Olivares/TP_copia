#include "../include/iniciar_cpu.h"

void iniciar_cpu(){
    iniciar_logs();
    iniciar_configs();
    mostrar_configs();
}

void iniciar_logs(){
    cpu_logger = log_create("cliente.log", "LOGGER_CPU", true, LOG_LEVEL_INFO);
	if( cpu_logger == NULL){
		perror ("Algo raro paso con el log, nose pudo crear o encontrar el archivo");
		exit(EXIT_FAILURE);
	}
}

void iniciar_configs(){
    cpu_config = config_create("cpu.config");
    
    if (cpu_config == NULL) {
        // No se pudo crear el config, terminemos el programa
		perror("Error al intentar cargar el config.");
        exit(EXIT_FAILURE);
    }	

    IP_MEMORIA = config_get_string_value(cpu_config, "IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(cpu_config, "PUERTO_MEMORIA");
    PUERTO_ESCUCHA_DISPATCH = config_get_string_value(cpu_config, "PUERTO_ESCUCHA_DISPATCH");
    PUERTO_ESCUCHA_INTERRUPT = config_get_string_value(cpu_config, "PUERTO_ESCUCHA_INTERRUPT");
    CANTIDAD_ENTRADAS_TLB = config_get_string_value(cpu_config, "CANTIDAD_ENTRADAS_TLB");
    ALGORITMO_TLB = config_get_string_value(cpu_config, "ALGORITMO_TLB");
}

void mostrar_configs(){
    log_info(cpu_logger, "IP_MEMORIA: %s", IP_MEMORIA);
    log_info(cpu_logger, "PUERTO_MEMORIA: %s", PUERTO_MEMORIA);
    log_info(cpu_logger, "PUERTO_ESCUCHA_DISPATCH: %s", PUERTO_ESCUCHA_DISPATCH);
    log_info(cpu_logger, "PUERTO_ESCUCHA_INTERRUPT: %s", PUERTO_ESCUCHA_INTERRUPT);
    log_info(cpu_logger, "CANTIDAD_ENTRADAS_TLB: %s", CANTIDAD_ENTRADAS_TLB);
    log_info(cpu_logger, "ALGORITMO_TLB: %s", ALGORITMO_TLB);
}