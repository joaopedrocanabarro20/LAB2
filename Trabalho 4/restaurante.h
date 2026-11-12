typedef struct mesa Mesa;

//mesas
void libera_mesa(Mesa** mesas, int l);
Mesa** inicializa_mesa(int l, int c);

//pratos
Pilha* inicializa_pilha_pratos(void);
void push_pratos(Pilha* pratos);