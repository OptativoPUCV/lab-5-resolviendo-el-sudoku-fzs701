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

//verificar si un tablero es valido
int is_valid(Node* n){
  int fila[9][10] = {0};    //verificar filas
  int colum[9][10] = {0};   //verificar columnas
  int box[9][10] = {0};     //verificar submatriz

  //recorrer tablero sudoku
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      int num = n->sudo[i][j];

      if(num != 0){      //si no esta vacia
        if (num < 1 || num > 9) {  //verificar si esta dentro rango
          return 0;
        }

        int submatriz = (i / 3) * 3 + (j / 3);  //indice submatriz
        //verificar si numero ya esta
        if(fila[i][num] || colum[j][num] || box[submatriz][num]){
          return 0;
        }
        //marcar numero como usado.
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
  //se busca casilla vacia en tablero
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){

      if(n->sudo[i][j] == 0) {
        //probar numeros 1 al 9 en casilla vacia
        for(int dato = 1; dato <= 9; dato++){
          Node *newNode = copy(n);
          newNode->sudo[i][j] = dato; //colocar numero en casilla

          if (is_valid(newNode)){
            pushBack(list,newNode); //agregamos nodos validos
          } else {
            free(newNode);
          }
        }
        return list; //se retorna nodos adyacentes
      }
    }
  }
  return list; //retorna lista vacia si no se encontro casillas
}

//verificar si tablero esta resuelto
int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){

      if(n->sudo[i][j] == 0){ //si hay casilla vacia no esta resuelto
        return 0;
      }

    }
  }
    return 1; //resuelto :)
}

//encontrar solucion
Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack,initial);  //inserta nodo inicial
  *cont = 0; //contador iteraciones

  while(!is_empty(stack)){
    Node* current = (Node*)top(stack); //obtener nodo en la c
    pop(stack); //eliminamos e incrementamos contador
    (*cont)++;

    if(is_final(current)){ //se retorna si es al final
      return current;
    }
    //obtener adyacentes
    List* nodosADJ = get_adj_nodes(current);
    void* nodeData;
    //recoremos nodos
    for(nodeData = first(nodosADJ); nodeData != NULL; nodeData = next(nodosADJ)){
      Node* nodosADJ = (Node*)nodeData;

      if(is_valid(nodosADJ)){ //se agrega pila si es valido
        push(stack,nodosADJ);
      }
    }

    free(current); //se libera nodo procesado
    clean(nodosADJ); //limpia lista nodos adyacnetos
  }
  return NULL; //NULL si no encuentra solucion
}




/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/