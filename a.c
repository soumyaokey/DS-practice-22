#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next
};

struct graph
{
    int V; // number of vertices
    struct Node **arr;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct graph *creategraph()
{
    int V;
    struct graph *gp = malloc(sizeof(struct graph));

    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    gp->arr = calloc(V, sizeof(struct Node *));
    gp->V = V;

    return gp;
}

void add_an_edge(struct graph *gp)
{
    int v1, v2;

    printf("Enter 1st and 2nd vertices: ");
    scanf("%d %d", &v1, &v2);

    struct Node *node1 = createNode(v2);
    node1->next = gp->arr[v1];
    gp->arr[v1] = node1;

    struct Node *node2 = createNode(v1);
    node2->next = gp->arr[v2];
    gp->arr[v2] = node2;
}

void show_the_graph(struct graph *gp)
{
    for (int i = 0; i < gp->V; i++)
    {
        struct Node *cr = gp->arr[i];
        while (cr)
        {
            printf(" -> | %d |", cr->data);
            cr = cr->next;
        }
    }
    printf("\n");
}

struct queue{
    int *arr;
    int size,h,t;
};
struct queue *create_queue(int size)
{
    struct queue *q = malloc(sizeof(struct queue));
    q->arr = malloc(size * sizeof(int));
    q->size = size;
    q->h = q->t = 0;
    return q;
}

void enqueue(struct queue *q, int data)
{
    if (q->h == -1){
        q->h=q->t=0;
        q->arr[0] = data;
    }else{
        q->arr[++q->t] = data;
    }
}

int dequeue (struct queue *q){
    int data =q->arr[q->h++];

    ++q->h;

    return data;
}

void bfs(struct graph *gp){
    int v,i;

    struct queue *q = create_queue(gp->V);
    show_the_graph(gp);

    printf("From which vertex we can start:");
    scanf("%d",&v);

    enqueue(q,v);

    while(q->h !=q->size){
        v = dequeue(q);
        printf("%d- ",v);

        struct Node *cr = gp->arr[v];

        while(cr){

            for(i=0;i<=q->t;i++){
                if(cr->data == q->arr[i]){
                    break;
                }
            }
            if(i == q->t){
                enqueue(q, cr->data);
            }
            cr = cr->next;
        }
    }
}
int main(){
    int inp;
    struct graph *gp = creategraph();

    while(1){
        printf("\n\nPress 1 to create a new graph \n2 to add an edge\n3 to show the graph\n4 BFS\n5 to exit:");
         scanf("%d", &inp);

        switch (inp) {
        case 1:
            gp = create_graph();
            break;
        case 2:
            if (gp) {
                add_an_edge(gp);
            } else {
                printf("\nNo Graph Found");
            }
            break;
        case 3:
            if (gp) {
                show_the_graph(gp);
            } else {
                printf("\nNo Graph Found");
            }
            break;
        case 4:
                bfs(gp);
        break;
       default:
            exit(0);
        }
    }
