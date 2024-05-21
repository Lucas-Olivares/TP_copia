#include "../include/memoria_io.h"

void memoria_atender_io(){
	bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_io);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_io, memoria_logger);
		    break;
/*	    case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		    break;*/
	    case -1:
	    	log_error(memoria_logger, "IO se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(memoria_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}