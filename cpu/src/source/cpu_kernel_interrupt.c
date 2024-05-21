#include "../include/cpu_kernel_interrupt.h"

void cpu_atender_kernel_interrupt(){
    bool control=1;
    while (control) {
	    int cod_op = recibir_operacion(fd_kernel);
	    switch (cod_op) {
	    case MENSAJE:
		    recibir_mensaje(fd_kernel, cpu_logger);
		    break;
/*	    case PAQUETE:
	    	lista = recibir_paquete(fd_io);
    		//log_info(memoria_logger, "Me llegaron los siguientes valores:\n");
		    //list_iterate(lista, (void*) iterator);
		    break;*/
	    case -1:
	    	log_error(cpu_logger, "Kernel Interrupt se desconectó. Terminando servidor");
	    	control = 0;
			break;
	    default:
		    log_warning(cpu_logger,"Operacion desconocida. No quieras meter la pata");
		    break;
	    }
    }
}