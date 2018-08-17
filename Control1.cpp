#include <iostream>
#include <fstream>

using namespace std;

struct Estacion{
	string nombre;
	string cod;
	string linea;
	string combinacion; 
	int val;
};
struct Linea{
	string nombre;
	Estacion estaciones[50];
	int largo;
};

struct Camino{
	Estacion estaciones[100];
	int costo;
};


void CrearMatrizAdyacencia(Estacion estaciones[],Estacion matriz[][116]){
	
}

void LeerFichero(Linea linea[]){
	ifstream infile("Estaciones");
	string fila,token,nombre_linea="";
	int n=0,pos,cont_linea=0;
	char delim = ' ',delim2='+';
	while(getline(infile,fila)){
		if(fila.substr(0,fila.find(delim)) == "Línea"){
			nombre_linea = fila;
			linea[cont_linea].nombre = fila;			
			cont_linea++;
			n=0;
		}else{
			pos = fila.find(delim);
			token = fila.substr(0,pos);
			linea[cont_linea-1].estaciones[n].cod = token;
			fila.erase(0,pos+1);
			if(fila.find(',') != -1){
				pos = fila.find(',');
				token = fila.substr(0,pos);
				linea[cont_linea-1].estaciones[n].nombre = token;
				fila.erase(0,pos+1);
				linea[cont_linea-1].estaciones[n].combinacion = fila;
			}else{
				linea[cont_linea-1].estaciones[n].nombre = fila;
				linea[cont_linea-1].estaciones[n].combinacion = "nulo";
			}			
			linea[cont_linea-1].estaciones[n].linea = nombre_linea;
			linea[cont_linea-1].largo = linea[cont_linea-1].largo + 1;
			n++;
		}

	}
}

void ObtenerLineas(Linea linea[],string &inicial,string &final,string &linea_inicial,string &linea_final,int &pos_linea_inicial,int &pos_linea_final){
	for(int i=0;i<6;i++){
		for(int j=0;j<linea[i].largo;j++){
			if(linea[i].estaciones[j].cod == inicial){
				linea_inicial = linea[i].estaciones[j].linea;
				pos_linea_inicial = i;
			}
			if(linea[i].estaciones[j].cod == final){
				linea_final = linea[i].estaciones[j].linea;
				pos_linea_final = i;

			}
		}
	}
	
}


void VerificarCamino(Camino caminofinal,Linea lineas[]){
	Estacion estacion_actual;
	while(estacion_actual.nombre != final){
		if(linea_inicial != linea_final){

		}else{
			for(int i=0;i<lineas[pos_linea_inicial].largo;i++){
				if(lineas[pos_linea_inicial].estaciones[i].nombre == final){
					posicion_final = i;
				}
				if(lineas[pos_linea_inicial].estaciones[i].nombre == inicial){
					posicion_inicial = i;
				}
			}
			costo = posicion_inicial - posicion_inicial;			
		}
	}
}
int main(int argc, char* argv[]){
	Linea lineas[6];
	Camino caminofinal;
	string inicial="TOB",linea_inicial,linea_final;
	string final="LL";
	int largo, pos_linea_inicial,pos_linea_final;
	Estacion estaciones[115],matriz[116][116];
	LeerFichero(lineas);
	ObtenerLineas(lineas,inicial,final,linea_inicial,linea_final,pos_linea_inicial,pos_linea_final);

	//VerificarCamino(caminofinal,lineas); Aun no terminado

	//CrearMatrizAdyacencia(estaciones,matriz);
}