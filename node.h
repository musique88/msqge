typedef struct node{
    void* data;
    void (*init)(struct node*);
    void (*draw)(struct node*);
    void (*end)(struct node*);
} msqge_node;

void msqge_node_default_init(msqge_node*);
void msqge_node_default_draw(msqge_node*);
void msqge_node_default_end(msqge_node*);
void msqge_node_default_constr(msqge_node*);
