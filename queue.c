#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf(stderr, __VA_ARGS__);

/* Internal implementation definitions */
struct queue_node
{
    queue_item_t item;
    struct queue_node *link;
};

typedef struct queue_node queue_node;

struct queue
{
    queue_node *front;
    queue_node *rear;
};

/* Functions */

queue *queue_new(void)
{
    struct queue *q = malloc(sizeof(struct queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void queue_free(queue *this)
{
    assert(queue_isempty(this));
    free(this);
}

void queue_insert(queue *this, queue_item_t item)
{
    struct queue_node *newN = malloc(sizeof(struct queue_node));
    newN->item = item;
    if (this->front==NULL)
    {
        this->front = newN;
        this->rear = newN;
    }
    else
    {
        this->rear->link = newN;
        this->rear = newN;
    }
}

queue_item_t queue_remove(queue *this)
{
    assert(!queue_isempty(this));
    queue_node *temp=this->front;
    queue_item_t item = temp->item;
    this->front=this->front->link;
    free(temp->item);
    free(temp);
    return item;
}

bool queue_isempty(queue *this)
{
    return this->front == NULL;
}
