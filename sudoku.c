#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int fila[9][10] = {0};
  int colum[9][10] = {0};
  int box[9][10] = {0};

  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      int num = n->sudo[i][j];
      if(num != 0){
        int submatriz = (i / 3) * 3 + (j / 3);
        if(fila[i][num] || colum[j][num] || box[submatriz][num]){
          return 0;
        }
        fila[i][num] = 1;
        colum[j][num] = 1;
        box[submatriz][num] = 1;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0) {
          for(int dato = 1; dato <= 9; dato++){
            Node *newNode = copy(n);
            newNode->sudo[i][j] = dato;
            if (is_valid(newNode)){
              pushBack(list,newNode);
            } else {
              free(newNode);
            }
          }
          
        }
      }
    }
    return list;
}



int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
    return 1;
}

/*Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack,initial);
  *cont = 0;

  while(!is_empty(stack)){
    Node* temp = pop(stack);
    (*cont)++;

    if(is_final(temp)){
      return temp;
    }
    List* nodosADJ = get_adj_nodes(temp);
    for(node* current = nodosADJ->first; current != NULL; current = current->next){
      Node* adjNode = (Node*) current->data;
      push(stack,adjNote);
    }
    free(temp);
  }
  return NULL;
}*/
Node* DFS(Node* initial, int* cont) {
    Stack* stack = createStack();  // Crear la pila
    push(stack, initial);  // Empujar el nodo inicial a la pila
    *cont = 0;  // Inicializar el contador de iteraciones
    
    while (!is_empty(stack)) {
        // Sacar el primer nodo de la pila (debe ser de tipo Node*)
        Node* temp = pop(stack);  
        (*cont)++;  // Incrementar el contador de iteraciones
        
        // Verificar si es un nodo final
        if (is_final(temp)) {
            return temp;
        }
        
        // Obtener los nodos adyacentes
        List* nodosADJ = get_adj_nodes(temp);
        
        // Recorrer la lista de nodos adyacentes y empujarlos a la pila
        for (node* current = nodosADJ->first; current != NULL; current = current->next) {
            Node* adjNode = (Node*) current->data;  // Obtener el Node* de current->data
            push(stack, adjNode);  // Empujar el nodo adyacente a la pila
        }
        
        free(temp);  // Liberar la memoria del nodo procesado
    }
    
    return NULL;
}




/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/