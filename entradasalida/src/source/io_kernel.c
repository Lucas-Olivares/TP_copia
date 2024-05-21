#include "../include/io_kernel.h"


void io_atender_kernel(){
    bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_kernel);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_kernel, io_logger);
		    break;
	    /*//case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		 //   break;*/
		case IO_GEN_SLEEP:
			recibir_todo_el_buffer(fd_kernel);
			sleep(5 * TIEMPO_UNIDAD_TRABAJO/1000);
			enviar_mensaje("Terminó I/O", fd_kernel);
			break;
	    case -1:
	    	log_error(io_logger, "Kernel se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(io_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}