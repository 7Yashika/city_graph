#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* city_name;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    int num_vertices;
    Node** adj_lists;
} Graph_List;

Graph_List* create_graph_list(int vertices) 
{
    Graph_List* graph = malloc(sizeof(Graph_List));
    graph->num_vertices= vertices;
    graph->adj_lists = malloc(sizeof(Node*) * vertices);
    for (int i = 0; i < vertices; i++) 
    {
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

int add_edge(Graph_List* graph, int src, int dest, int weight, const char* src_city, const char* dest_city) 
{
    if (src < 0 || src >= graph->num_vertices || dest < 0 || dest >= graph->num_vertices) 
    {
        printf("Invalid vertices\n");
        return -1;
    }

    Node* new_node_src = malloc(sizeof(Node));
    if(new_node_src == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node_src->city_name = strdup(src_city);
    new_node_src->weight = weight;
    new_node_src->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node_src;

    Node* new_node_dest = malloc(sizeof(Node));
    if(new_node_dest == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node_dest->city_name = strdup(dest_city);
    new_node_dest->weight = weight;
    new_node_dest->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node_dest;

    return 0;
}

void print_graph_list(Graph_List* graph) 
{
    for (int i = 0; i < graph->num_vertices; i++) 
    {
        Node* temp = graph->adj_lists[i];
        printf("\nVertex %d:", i);
        while (temp != NULL) 
        {
            printf(" -> %s (Charge: %d)", temp->city_name, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() 
{
    Graph_List* graph;
    int num_vertex = 4; 
    graph= create_graph_list(num_vertex);
    add_edge(graph,1, 3, 1436, "Delhi", "Mumbai");
    add_edge(graph, 2, 0, 900, "Mumbai", "Hyederbad");
    add_edge(graph, 0, 2, 1300, "Hyederbad", "Gujrat");
    add_edge(graph, 3, 4, 2907, "Gujrat", "assam");

    print_graph_list(graph);

    for (int i = 0; i < graph->num_vertices; i++) 
    {
        Node* current = graph->adj_lists[i];
        while (current != NULL) 
        {
            Node* next = current->next;
            free(current->city_name);
            free(current);
            current = next;
        }
        graph->adj_lists[i] = NULL;
    }
    free(graph->adj_lists);
    free(graph);

    return 0;
}
