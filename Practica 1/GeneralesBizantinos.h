#ifndef GENERALESBIZANTINOS_GENERALESBIZANTINOS_H
#define GENERALES_BIZANTINOS_GENERALESBIZANTOS_H

enum tipo_nodo{
    TRAIDOR,
    LEAL
};

struct resultado_del_voto_de_mayoria{
    int decision;
    int conteo;
};

int ponerse_acuerdo(int proceso, int num_proceso);

enum tipo_nodo get_tipo_nodo(int proceso, int num_proceso);

void emitir_a_todos_excepto_a_si_mismo(int proceso, int num_proceso, enum tipo_nodo tipo_nodo, int decision);

void emitir_a_todos_excepto_a_si_mismo_traidor(int proceso, int num_proceso);

void emitir_a_todos_excepto_a_si_mismo_leal(int proceso, int num_proceso,int decision);

void recibir_mensaje_de_todos_excepto_de_si_mismo(const int proceso, const int num_proceso, int *decisiones);

int recibido_del_general(int general_proceso);

int get_numero_de_fallos(const int num_procesos);

int get_decision_aleatoria();

void mensaje(const int proceso, const int num_procesos, const int * const desiciones, const int ronda);

#endif