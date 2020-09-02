#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//---ESTRUCTURAS
typedef struct nodo_s
{
    int dato;
    struct nodo_s *sig;
}nodo_s;

typedef struct nodoP
{
    int dato;
    struct nodo_s *ady; //Inicio de la adyacencia de cada nodo
    struct nodoP *next;
}nodoP;
//--------------

//---Prototipos
nodo_s *crearNodoAdy(int dato);
nodoP *crearNodoLista(int dato);
nodoP *crearNodosGrafo(nodoP *inicio,int dato);
nodoP *crearAdyacencia(nodoP *inicio,int datoLista,int dato_Ady);
nodoP *obtenerNodo_ady(nodoP *inicio,int);
nodoP *recorrido(nodoP *inicio,nodoP *nodo,int);
bool valADY(nodoP *nodo,int dato);
void mostrarListaAdyacencia(nodoP *inicio);
//-------------

//---VARIABLES GLOBALES
nodoP *finalLista = NULL;

//---------------------

int main()
{
    system("cls");
    nodoP *grafo = NULL;
    bool ext = false;

    //---Crear los nodos que se utilizaran en el grafo
    grafo = crearNodosGrafo(grafo,1);
    grafo = crearNodosGrafo(grafo,2);
    grafo = crearNodosGrafo(grafo,3);
    grafo = crearNodosGrafo(grafo,4);
    grafo = crearNodosGrafo(grafo,5);
    grafo = crearNodosGrafo(grafo,6);
    //---------------------------------

    //---Crear Las Adyacencias
    grafo = crearAdyacencia(grafo,1,2);
    grafo = crearAdyacencia(grafo,1,3);
    grafo = crearAdyacencia(grafo,1,4);

    grafo = crearAdyacencia(grafo,2,1);
    grafo = crearAdyacencia(grafo,2,2);
    grafo = crearAdyacencia(grafo,2,5);

    grafo = crearAdyacencia(grafo,3,1);
    grafo = crearAdyacencia(grafo,3,4);
    grafo = crearAdyacencia(grafo,3,6);

    grafo = crearAdyacencia(grafo,4,1);
    grafo = crearAdyacencia(grafo,4,3);

    grafo = crearAdyacencia(grafo,5,2);
    grafo = crearAdyacencia(grafo,5,6);

    grafo = crearAdyacencia(grafo,6,3);
    grafo = crearAdyacencia(grafo,6,5);
    //-----------------------------------

    mostrarListaAdyacencia(grafo);
    //Recorrido
    nodoP *ruta = grafo, *aux;
    int u;
    printf("\nINGRESE -1 PARATERMINAR");

    do
    {
        printf("\n\nUBUCACION ACTUAL: nodo %d\n",ruta->dato);
        printf("Ingrese Siguiente Ubicacion: ");
        scanf("%d",&u);
        //aux = ruta;
        if(u != -1)
            ruta = recorrido(grafo,ruta,u);
    } while (u != -1);
    
    

    printf("\n");
    system("pause");
    return 0;
}
void mostrarListaAdyacencia(nodoP *inicio)
{
    nodo_s *ady = NULL;
    if (inicio != NULL)
    {
        while (inicio != NULL)
        {
            printf("%d -> ",inicio->dato);
            ady = inicio->ady;
            while(ady !=NULL)
            {
                printf(" %d - ",ady->dato);
                ady = ady->sig;
            }
            printf("\n");
            inicio = inicio->next;
        }
    }
}
nodo_s *crearNodoAdy(int dato)
{
    nodo_s *nuevoNodo = (nodo_s*)malloc(sizeof(nodo_s));

    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;
}

nodoP *crearNodoLista(int dato)
{
    nodoP *nuevoNodo = (nodoP*)malloc(sizeof(nodoP));

    nuevoNodo->dato = dato;
    nuevoNodo->ady = NULL;
    nuevoNodo->next = NULL;
}

nodoP *crearNodosGrafo(nodoP *inicio,int dato)
{
    if(inicio == NULL)
    {
        inicio = crearNodoLista(dato);
        finalLista = inicio;
        return inicio;
    }
    finalLista->next = crearNodoLista(dato);
    finalLista = finalLista->next;
    return inicio;
}
nodoP *obtenerNodo_ady(nodoP *inicio,int dato)
{//Asumiendo que el dato existe en la lista pricipal
    nodoP *aux = inicio;
    //nodo_s *nodo;
    bool ext = false;
    while(ext != true)
    {
        if(aux->dato == dato)
        {
            ext = true;
            return aux;
        }
        aux = aux->next;
    }
    return aux;
    
}
nodoP *crearAdyacencia(nodoP *inicio,int datoLista,int dato_Ady)
{
    if(inicio != NULL)
    {
        nodoP *lista_ady = NULL;
        //Validar que el datoLista exista en el grafo
        lista_ady = obtenerNodo_ady(inicio,datoLista);
        if(lista_ady->ady == NULL)
        {
            lista_ady->ady = crearNodoAdy(dato_Ady);
            return inicio;
        }
        else
        {
            nodo_s *aux = lista_ady->ady; 
            while (aux->sig != NULL)
            {
                aux = aux->sig;
            }
            aux->sig = crearNodoAdy(dato_Ady);
            return inicio;
        }
    }
    else
    {
        printf("\nGRAFO SIN NODOS GENERADOS\n");
    }
    
}

bool valADY(nodoP *nodo,int dato)
{
    nodo_s *aux = nodo->ady;
    while (aux != NULL)
    {
        if(aux->dato == dato)
        {
            return true;
        }
        aux = aux->sig;
    }
    return false;
    
}

nodoP *recorrido(nodoP *inicio,nodoP *nodo,int dato)
{
    //Validar que exista en la adyacencia
    //recorrer en la lista principal
    //obtener nodo y devolver
    if(valADY(nodo,dato) != false)
    {
        return obtenerNodo_ady(inicio,dato);
    }
    else
    {
        printf("NO EXITSTE ADYACENCIA");
        return nodo;
    }
    
}