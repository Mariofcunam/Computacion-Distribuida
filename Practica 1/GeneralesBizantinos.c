#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "GeneralesBizantinos.h"

const int SIN_DECISION = -1;

const int NUMERO_DE_DECISIONES_POSIBLES = 2;
const int ATACAR = 0;
const int RETIRARSE = 1;

const int DECISION= 1;

int ponerse_acuerdo(const int proceso, const int num_proceso){
    const int num_fallos = get_numero_de_fallos(num_proceso);

    enum tipo_nodo tipo_nodo = get_tipo_nodo(proceso, num_proceso);
    int decision = get_decision_aleatoria();
    int *decisiones = malloc(num_proceso * sizeof(int));

    for(int general=0; general< no_fallos; ++general){
        emitir_mensaje_a_todos_excepto_a_si_mismo(proceso,num_proceso,tipo_nodo,decision);
        decisiones[proceso] = decision;

        recibir_de_todos_excepto_de_si_mismo(proceso,num_proceso,decisiones);

        struct resultado_del_voto_de_mayoria resultado_voto;
        resultado_voto = calcula_mayoria(num_proceso,decisiones);

        int decision_del_general;
        if(proceso==general){
            decision_del_general = resultado_voto.decision;
            emitir_mensaje_a_todos_excepto_a_si_mismo(proceso,num_proceso,tipo_nodo,decision_del_general);
        } else{
            decision_del_general = recibir_orden_del_general(general);
        }
        if(resultado_voto > num_proceso / 2 + num_fallos){
            decision = resultado_voto.decision;
        } else{
            decision = decision_del_general;
        }
    }
    free(decisiones);

    return decision;
}

enum tipo_nodo get_tipo_nodo(const int proceso, const int num_proceso){
    const int NUM_FALLOS=get_numero_de_fallos(num_proceso);

    enum tipo_nodo estado;
    if(proceso < NUM_FALLOS){
        estado = TRAIDOR;
    } else{
        estado = LEAL;
    }
    return estado;
}

void emitir_mensaje_a_todos_excepto_a_si_mismo(const int proceso, const int num_proceso, const enum tipo_nodo tipo_nodo, int decision){
    if(tipo_nodo==LEAL){
        emitir_mensaje_a_todos_excepto_a_si_mismo_leal(proceso,no_proceso,decision);
    }else if(tipo_nodo==TRAIDOR){
        emitir_mensaje_a_todos_excepto_a_si_mismo_traidor(proceso,no_proceso);
    }
}

void emitir_mensaje_a_todos_excepto_a_si_mismo_traidor(const int proceso, const int no_proceso){
    for(int proceso_a_llegar = 0; proceso_a_llegar < no_proceso; ++proceso_a_llegar){
        if(proceso_a_llegar != proceso){
            int accion_planeada= get_decision_aleatoria();
            MPI_Send(&accion_planeada, 1, MPI_INT, proceso_a_llegar,DECISION, MPI_COMM_WORLD);
        }
    }
}

void emitir_mensaje_a_todos_excepto_a_si_mismo_leal(const int proceso, const int no_proceso, const int decision){
    for(int proceso_a_llegar=0; proceso_a_llegar < no_proceso; ++proceso_a_llegar){
        if(proceso_a_llegar !=proceso){
            MPI_Send(&decision,1, MPI_INT, proceso_a_llegar, DECISION, MPI_COMM_WORLD);
        }
    }
}

void recibir_mensaje_de_todos_excepto_de_si_mismo(const int proceso, const int no_proceso, int *decisiones){
    MPI_Status estado;

    for(int remitente=0; remitente < no_proceso; ++remitente){
        if(remitente != proceso){
            int valor;
            MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, DECISION, MPI_COMM_WORLD, $estado);
                decisiones[estado.MPI_SOURCE] = valor;
            }
        }
    }

struct resultado_del_voto_de_mayoria calcula_mayoria(const int no_proceso, const int * const decisiones){
    int elemento = decisiones[0];
    int conteo = 1;

    for(int i=1; i<no_proceso; ++i){
        if(elemento != decisiones[i]){
            --conteo;
            if(conteo==0){
                elemento=decisiones[i];
                conteo=1;
            }
        } else {
            ++conteo;
        }
    }
    conteo = 0;
    for(int i = 0; i<no_proceso;++i){
        if(elemento==decisiones[i]){
            ++conteo;
        }
    }
    struct resultado_del_voto_de_mayoria resultado_voto;
    resultado_voto.desicion=elemento;
    resultado_voto.desicion.conteo=conteo;
    return resultado_voto;
}

int recibido_del_general(int general_proceso){
    int valor;
    MPI_Status estado;
    MPI_Recv($valor,MPI_INT, general_proceso, DECISION, MPI_COMM_WORLD, $estado);
    return valor;
}

int get_numero_de_fallos(const int no_procesos){
    return no_procesos / 4;
}

int get_decision_aleatoria(){
    return rand() % NUMERO_DE_DECISIONES_POSIBLES;
}

void mensaje(const int proceso, const int no_procesos, const int * const desiciones, const int ronda){
    printf("Ronda [%d] tiene las siguiente desiciones:", ronda,proceso);
    for(int i=0; i<no_procesos; ++i){
        printf("%d", desiciones[i]);
    }
    printf("\n");
}