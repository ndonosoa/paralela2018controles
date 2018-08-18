#include <stdio.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
#define MAX 10005 //maximo numero de v�rtices
#define Node pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};
struct estacion{
    int numero;
    string codigo;
    string nombreEstacion;
};

vector< Node > ady[ MAX ]; //lista de adyacencia
int distancia[ MAX ];      //distancia[ u ] distancia de v�rtice inicial a v�rtice con ID = u
bool visitado[ MAX ];      //para v�rtices visitados
priority_queue< Node , vector<Node> , cmp > Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
int V;                     //numero de vertices
int previo[ MAX ];         //para la impresion de caminos

//funci�n de inicializaci�n
void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[ i ] = false; //inicializamos todos los v�rtices como no visitados
        previo[ i ] = -1;      //inicializamos el previo del vertice i con -1
    }
}

//Paso de relajacion
void relajacion( int actual , int adyacente , int peso ){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        Q.push( Node( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}

//Impresion del camino mas corto desde el vertice inicial y final ingresados
void print( int destino ){
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        print( previo[ destino ] );  //recursivamente sigo explorando
    printf("%d " , est[destino].nombreEstacion);
    //printf("%d " , destino );        //terminada la recursion imprimo los vertices recorridos
}

void dijkstra( int inicial ,int destino){
    init(); //inicializamos nuestros arreglos
    Q.push( Node( inicial , 0 ) ); //Insertamos el v�rtice inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q.empty() ){                   //Mientras cola no este vacia
        actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo ser� el inicial
        Q.pop();                           //Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; //Si el v�rtice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         //Marco como visitado el v�rtice actual

        for( int i = 0 ; i < ady[ actual ].size() ; ++i ){ //reviso sus adyacentes del vertice actual
            adyacente = ady[ actual ][ i ].first;   //id del vertice adyacente
            peso = ady[ actual ][ i ].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !visitado[ adyacente ] ){        //si el vertice adyacente no fue visitado
                relajacion( actual , adyacente , peso ); //realizamos el paso de relajacion
            }
        }
    }


    printf( "Distancias mas cortas iniciando en vertice %d\n" , inicial );
    for( int i = 1 ; i <= V ; ++i ){
        printf("Vertice %d , distancia mas corta = %d\n" , i , distancia[ i ] );
    }

    puts("\n**************Impresion de camino mas corto**************");
    printf("Ingresando vertice destino: ");
    print( destino );
    printf("\n");
}


int main(int argc, char* argv[]){
    int origen, destino , peso , inicial, contador=0;
    //Ingreso de numero de vertices y de conecciones
    string input = argv[1];
    int posicion = input.find(' ');
    string token = input.substr(0,posicion);
    input.erase(0,posicion+1);
    if (input=='f') {
      int V=11, E=108;
      estacion est[MAX];
      ifstream infile1("codigos.txt");
  	  string linea;
      while(getline(infile1, linea)){
       est[contador].codigo=linea;
       contador++;
      }
      contador=0;
      ifstream infile2("numeros.txt");
      while(getline(infile2, linea)){
       est[contador].numero=stoi(linea);
       contador++;
      }
      ifstream infile3("estaciones.txt");
      while(getline(infile3, linea)){
       est[contador].nombreEstacion=linea;
       contador++;
      }
      contador=0;
      while( E-- ){
          //instanciación de la matriz de adyacencia
          peso =1;
          origen=est[contador].numero;
          destino=est[contador+1].numero;
          if(contador<108){
          ady[ origen ].push_back( Node( destino , peso ) ); //consideremos grafo dirigido
          ady[ destino ].push_back( Node( origen , peso ) ); //grafo no dirigido
          contador=contador++;
          }
          else{
            origen=est[contador-1].numero;
            destino=est[contador-1].numero;
            ady[ origen ].push_back( Node( destino , peso ) ); //consideremos grafo dirigido
            ady[ destino ].push_back( Node( origen , peso ) ); //grafo no dirigido
            break;
          }
      }
      printf("Ingresando el vertice inicial y final: ");
      int posicion = input.find(' ');
      string token = input.substr(0,posicion);
      input.erase(0,posicion+1);
      inicial =atoi(input);

      int posicion = input.find(' ');
      string token = input.substr(0,posicion);
      input.erase(0,posicion+1);
      destino =atoi(input);
      dijkstra( inicial ,destino);
    }else if(argv[1]=="v"){
      printf("Integrantes: \n");
      printf("Integrantes: Nataniel Donoso Acevedo \n");
      printf("Integrantes: Esteban Hernandez Bratesco \n ");
    }
    return 0;
}
