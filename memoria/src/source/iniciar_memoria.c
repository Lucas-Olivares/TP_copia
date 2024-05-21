#include "../include/iniciar_memoria.h"

void iniciar_memoria(){
    iniciar_logs();
    iniciar_configs();
    mostrar_configs();
}

void iniciar_logs(){
    memoria_logger = log_create("cliente.log", "LOGGER_MEMORIA", true, LOG_LEVEL_INFO);
	if( memoria_logger == NULL){
		perror ("Algo raro paso con el log, no se pudo crear o encontrar el archivo");
		exit(EXIT_FAILURE);
	}
}

void iniciar_configs(){
    memoria_config = config_create("memoria.config");
    
    if (memoria_config == NULL) {
        // No se pudo crear el config, terminemos el programa
		perror("Error al intentar cargar el config.");
        exit(EXIT_FAILURE);
    }
    PUERTO_ESCUCHA = config_get_string_value(memoria_config, "PUERTO_ESCUCHA");
    TAM_MEMORIA = config_get_int_value(memoria_config, "TAM_MEMORIA");
    TAM_PAGINA = config_get_int_value(memoria_config, "TAM_PAGINA");
    PATH_INSTRUCCIONES = config_get_string_value(memoria_config, "PATH_INSTRUCCIONES");
    RETARDO_RESPUESTA = config_get_int_value(memoria_config, "RETARDO_RESPUESTA");
}

void mostrar_configs(){
    log_info(memoria_logger, "PUERTO_ESCUCHA: %s", PUERTO_ESCUCHA);
    log_info(memoria_logger, "TAM_MEMORIA: %d", TAM_MEMORIA);
    log_info(memoria_logger, "TAM_PAGINA: %d", TAM_PAGINA);
    log_info(memoria_logger, "PATH_INSTRUCCIONES: %s", PATH_INSTRUCCIONES);
    log_info(memoria_logger, "RETARDO_RESPUESTA: %d", RETARDO_RESPUESTA);
}