#include "../include/io_memoria.h"

void io_atender_memoria(){
    bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_memoria);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_memoria, io_logger);
		    break;
/*	    case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		    break;*/
	    case -1:
	    	log_error(io_logger, "Memoria se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(io_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}