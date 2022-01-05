#include "node.h"

void msqge_node_default_init(msqge_node* this)
{
    //silence unused variable warning
    (void)this;
}

void msqge_node_default_draw(msqge_node* this)
{
    //silence unused variable warning
    (void)this;
}

void msqge_node_default_end(msqge_node* this)
{
    //silence unused variable warning
    (void)this;
}

void msqge_node_default_constr(msqge_node* this)
{
    this->init = msqge_node_default_init;
    this->draw = msqge_node_default_draw;
    this->end = msqge_node_default_end;
}
