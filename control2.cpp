#include <omp.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string.h>
#include <vector>
#include <queue>
#include <string>
using namespace std;
#define MAX 10005 //maximo numero de v�rtices
#define Node pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas
unsigned t0, t1;

int matrizAdy[119][119];
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
void print( int destino, estacion est[] , int cant){
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        print( previo[ destino],est,cant );  //recursivamente sigo explorando
        for(int i=0;i<cant;i++){
          if(est[i].numero == destino){
            cout<<est[i].nombreEstacion<<"- ";        //terminada la recursion imprimo los vertices recorridos
            i=cant;
          }

        }
    //cout<<est[destino].nombreEstacion<<endl;

}

void dijkstra( int inicial ,int destino, estacion est[],int cant){
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


    /*printf( "Distancias mas cortas iniciando en vertice %d\n" , inicial );
    for( int i = 1 ; i <= V ; ++i ){
        printf("Vertice %d , distancia mas corta = %d\n" , i , distancia[ i ] );
    }*/

    print( destino, est, cant);
    printf("\n");
}


int main(int argc, char* argv[]){
    int origen, destino , peso , inicial,contador=0,cant=0;
    int tid,nthreads;
        //Ingreso de numero de vertices y de conecciones
    string input = argv[1];
    int posicion = input.find(' ');
    string token = input.substr(0,posicion);
    input.erase(0,posicion+1);
    if (token=="-f") {
      int E=118;
      V=119;
      estacion est[MAX];
      ifstream infile1("codigos.txt");
  	  string linea;
      while(getline(infile1, linea)){
       est[contador].codigo=linea;
       contador++;
      }
      cant=contador;
      contador=0;
      ifstream infile2("numeros.txt");
      while(getline(infile2, linea)){
       est[contador].numero=stoi(linea);
       contador++;
      }
      contador=0;
      ifstream infile3("estaciones.txt");
      while(getline(infile3, linea)){
       est[contador].nombreEstacion=linea;
       contador++;
      }
      contador=0;
      for(contador;contador<E;contador++ ){
          //instanciación del vector de adyacencia
          // se omite peso =1    --ya que todos pesaran 1;
          for(int contador2=0;contador2<118;contador2++){
            if(est[contador].nombreEstacion.find(',') == -1){
            origen=est[contador].numero;
            destino=est[contador+1].numero;
              //if(origen==contador){
                matrizAdy[ contador ][ origen ]= 1;
                /*ady[ origen ].push_back( Node( destino , peso ) ); //consideremos grafo dirigido
                ady[ destino ].push_back( Node( origen , peso ) ); //grafo no dirigido */
              //}
            }
          }
      }
      for(int y=0;y<118;y++){
        for(int z=0;z<118;z++){
          cout << " "<< matrizAdy[ y ][ z ];
        }
        cout << " || termina fila "<<endl;
      }
      posicion = input.find(' ');
      token = input.substr(0,posicion);
      input.erase(0,posicion+1);
      for(int i=0;i<cant;i++){
        if(est[i].codigo == token){ //revisar qué pasa con las estaciones con doble código
          inicial = est[i].numero;
          i=cant;
        }
      }

       posicion = input.find(' ');
      token = input.substr(0,posicion);
      for(int i=0;i<cant;i++){
        if(est[i].codigo == token){ //revisar qué pasa con las estaciones con doble código
          destino = est[i].numero;
          i=cant;
        }

      }
      cout << "matriz de adyacencia con las estaciones del metro completadas :) " << endl;
      #pragma omp parallel private(tid)
      {
          tid = omp_get_thread_num();
          nthreads = omp_get_num_threads();
          std::cout<<"Soy el hilo= "<<tid<<" de "<< nthreads <<" que somos."<<std::endl;
          cout<<"inicio: "<<inicial<<" | destino: "<<destino<<endl;
          cout<<"aqui va dijkstra o vecino mas proximo para hacerlo en paralelo" <<endl;
          //dijkstra( inicial ,destino, est,cant);
      }
    }else if(token=="-v"){
      printf("Integrantes: \n");
      printf("Nataniel Donoso Acevedo \n");
      printf("Esteban Hernandez Bratesco \n ");
    }
    return 0;
}
