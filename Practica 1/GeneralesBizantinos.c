#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "GeneralesBizantinos.h"

const int SIN_DECISION = -1;

const int NUMERO_DE_DECISIONES_POSIBLES = 2;
const int ATACAR = 0;
const int RETIRARSE = 1;

const int DECISION= 1;

int ponerse_acuerdo(const int proceso, const int no_proceso){
    const int num_fallos = get_numero_de_fallos(no_proceso);

    enum tipo_nodo tipo_nodo = get_tipo_nodo(proceso, no_proceso);
    int decision = get_decision_aleatoria();
    int *decisiones = malloc(no_proceso * sizeof(int));

    for(int general=0; general< no_fallos; ++general){
        dar_mensaje_a_todos_excepto_a_si_mismo(proceso,no_proceso,tipo_nodo,decision);
        decisiones[proceso] = decision;

        recibir_de_todos_excepto_de_si_mismo(proceso,no_proceso,decisiones);

        struct resultado_del_voto_de_mayoria resultado_voto;
        resultado_voto = calcula_mayoria(no_proceso,decisiones);

        int decision_del_general;
        if(proceso==general){
            decision_del_general = resultado_voto.decision;
            dar_mensaje_a_todos_excepto_a_si_mismo(proceso,no_proceso,tipo_nodo,decision_del_general);
        } else{
            decision_del_general = recibir_orden_del_general(general);
        }
        if(resultado_voto > no_proceso / 2 + no_fallos){
            decision = resultado_voto.decision;
        } else{
            decision = decision_del_general;
        }
    }
    free(decisiones);

    return decision;
}

enum tipo_nodo get_tipo_nodo(const int proceso, const int no_proceso){
    const int NO_FALLOS=get_numero_de_fallos(no_proceso);

    enum tipo_nodo estado;
    if(proceso )
}