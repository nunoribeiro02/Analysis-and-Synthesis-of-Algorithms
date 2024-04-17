#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <set>

using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2
#define GREEN 3
#define RED 4
#define BLUE 5

typedef struct vertex{
    vector<int> parents;
    int colour;
    int num_parents;
    bool solution;

}Vertex;

bool DFS(vector<Vertex> *graph);
bool DFS_Visit(vector<Vertex> *graph, int v);
void getCommonAncestors(vector<Vertex> *graph, int v1, int v2);
void BFS(vector<Vertex> *graph, int v);
set<int> SecBFS(vector<Vertex> *graph, int v);
void cutParents(vector<Vertex> *graph, int v);


int main() {
    int v1, v2;    
    int num_vert, num_conect;

    // Get identifiers for v1 and v2
    if((scanf("%d %d", &v1, &v2)) < 0 ){return -1;}
    
    // Get number of vertices and connections
    if( (scanf("%d %d", &num_vert, &num_conect)) < 0 ) {return -1;}
    vector<Vertex> graph(num_vert);

    int v_parent, v_child;
    bool invaltree = false;
    for (int i = 0; i < num_conect; i++){
        // Get identifiers for vertice parent and child
        
        if ((scanf("%d %d", &v_parent, &v_child)) != 2) {
            invaltree = true;
            break;
        }

        Vertex* vertex_c = &graph[v_child-1];
        Vertex &vertex_child = *vertex_c;
        vertex_child.parents.push_back(v_parent-1);
        vertex_child.num_parents++;
        if (vertex_child.num_parents > 2){
            invaltree = true;
        }
        
    }  

    // If the DFS returns false or the tree is invalid, the graps is cyclical and thus invalid
    
    if (!DFS(&graph) || invaltree){
        printf("0\n");
        return 0;
    }


    getCommonAncestors(&graph, v1, v2);

    return 0;
}


bool DFS(vector<Vertex> *graph){
    vector<Vertex> &g = *graph;
    int size = g.size();
    for (int i = 0; i < size; i++){
        g[i].colour = WHITE;
    }
    for (int i = 0; i < size; i++){
        if (g[i].colour == WHITE){
            if (DFS_Visit(graph, i) == false){
                return false;
            }
        }
    }

    return true;
}

bool DFS_Visit(vector<Vertex> *graph, int v){
    vector<Vertex> &g = *graph;
    g[v].colour = GREY;
    for (int w : g[v].parents){
        if (g[w].colour == WHITE) {
            if (!DFS_Visit(graph, w)){
                return false;
            }
        }
        else if (g[w].colour == GREY) {
            return false;
        }
    }     
    g[v].colour = BLACK;

    return true;
} 

void BFS(vector<Vertex> *graph, int v){
    vector<Vertex> &g = *graph;
    int u;
    vector<int> queue;
    queue.push_back(v-1);
    while(!queue.empty()){
        u = queue.back();
        queue.pop_back();
        for(int p : g[u].parents){
            if(g[p].colour == BLACK){
                g[p].colour = RED;
                queue.push_back(p);
            }
        
        }  
        g[u].colour = RED;
    }

}

void cutParents(vector<Vertex> *graph, int v){
    vector<Vertex> &g = *graph;
    for (int p: g[v].parents){
        g[p].colour = BLUE;
        g[p].solution = false;
        cutParents(graph, p);
    }
}
set<int> SecBFS(vector<Vertex> *graph, int v){
    vector<Vertex> &g = *graph;
    int u;
    vector<int> queue;
    set<int> ancestors;
    queue.push_back(v-1);
    while(!queue.empty()){
        u = queue.back();
        queue.pop_back();
        if (g[u].colour == RED){
            g[u].colour = GREEN;
            g[u].solution = true;
            ancestors.insert(u);
            cutParents(graph, u);
        }

        for(int p : g[u].parents){

            if(g[p].colour == RED){
                g[p].colour = GREEN;
                g[p].solution = true;
                ancestors.insert(p);
                cutParents(graph, p);
            }
            queue.push_back(p);
        } 
    }   
        
    
    return ancestors;
}

void getCommonAncestors(vector<Vertex> *graph, int v1, int v2){
    vector<Vertex> &g = *graph;
    BFS(graph, v1);
    set<int> ancestors = SecBFS(graph, v2);
    
    if (ancestors.size() == 0){
        printf("-");
    }
    else{
        for (int a: ancestors){
            if (g[a].solution){
                printf("%d ", a+1);
            }
        }
    }
    
    printf("\n");
    
    return;
}