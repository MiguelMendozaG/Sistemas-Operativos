#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include <cstdlib>


using namespace std;

void pausa();

int selec_mem =0;
int cola = 0;
int proceso_memoria = 0;
int proceso[8];
static int memo_total = 100;
int memo_libre = 100;
int mat_proc[100][8];
int mat_mem[100][8];
int proceso_a_memoria = 0;  //ing_mem
int antiguedad_proceso = 0;
int i_memoria = 0;
int id_pet=0, id_proceso=0, nom_pet=0, id_part=0;
//int i_compacta=0, i2_compacta=0;

void cola_peticiones(int *proces);

void imprimir_peticiones(){
  cout << "\n Cola de peticiones" << endl;
  cout << "\nID Pet\tNom Pet\tTam\n" << endl;
  for (int i=0; i<cola; i++){
    cout << mat_proc[i][1] << "\t"<< mat_proc[i][2] << "\t"<< mat_proc[i][3] << "\t"<<endl;
  }
}

void imprimir_memoria(){
  int suma=0;
  cout << "\n Procesos en memoria" << endl;
  cout << "\nID\tID\tNomb\t\tFrag\tFrag" << endl;
  cout << "\nPart\tProc\tProc\tTam\tExt.\tLib\tTam lb\tAntiguedad\n" << endl;
  for (int i=0; i<proceso_memoria; i++){
    suma+=mat_mem[i][3];
  }
  for (int i=0; i<proceso_memoria; i++){
    if(mat_mem[i][5]==1){
	
      cout << mat_mem[i][0] << "\t"<< mat_mem[i][1] << "\t"<< mat_mem[i][2] << "\t"<< mat_mem[i][3] << "\t"<< mat_mem[i][6]-mat_mem[i][3] << "\t" << mat_mem[i][5] << "\t"<< mat_mem[i][6] << "\t"<< mat_mem[i][7] << "\t"<<endl;
      suma+=mat_mem[i][6];
	}
    else
      cout << mat_mem[i][0] << "\t"<< mat_mem[i][1] << "\t"<< mat_mem[i][2] << "\t"<< mat_mem[i][3] << "\t"<< mat_mem[i][4] << "\t" << mat_mem[i][5] << "\t"<< mat_mem[i][6] << "\t"<< mat_mem[i][7] << "\t"<<endl;
  }
 // if (suma <= memo_libre){
    cout << "Espacio" << "\t"<< "libre" << "\t\t"<< memo_libre <<endl;
  //}
}

void genera_peticion(int peticion){
	int proceso[8]={0};
	
	proceso[1] = id_pet++;
	proceso[2] = nom_pet++;
	proceso[3] = peticion;
	cola_peticiones(proceso);
	
}



void ordenamiento(){
	int vector_aux;
	for (int j = 0; j < proceso_memoria-1 ; j++){
		for (int k = j+1; k < proceso_memoria; k++){
			if (mat_mem[j][7] > mat_mem[k][7]){
				for(int i_orden = 0; i_orden < 8; i_orden++){
					vector_aux = mat_mem[j][i_orden];
					mat_mem[j][i_orden] = mat_mem[k][i_orden];
					mat_mem[k][i_orden] = vector_aux;
				}
			}
		}
	}
	
}
void compactar(){
  int i_compacta=0, i2_compacta=0;
  while (mat_mem[++i_compacta][5]==0);
  
  	for (int i_frag_ext = 0; i_frag_ext < proceso_memoria; i_frag_ext++){ //se agrega a memo_libre la memoria que está en frag_ext y en tam_libre
  		if(mat_mem[i_frag_ext][5]==1) //tam_libre
  			memo_libre+=mat_mem[i_frag_ext][6];
  		if(mat_mem[i_frag_ext][4]>0){ //frag_ext
  			memo_libre+=mat_mem[i_frag_ext][4];
  			mat_mem[i_frag_ext][4]=0;
  		}
  		
	  }
	if (i_compacta < 100){
	  while (mat_mem[++i2_compacta + i_compacta][5]==1);
	  i2_compacta+=i_compacta;
	  for (int i = i_compacta; i < i2_compacta; i++){
	    for (int j =0; j<8; j++){
	      mat_mem[i][j]=0;
	    }
	   
	    proceso_memoria--;
	    i_memoria--;
	  }  
	}
	else
		cout << "\n Nada que compactar " << endl;
}

void terminar_proceso_memoria(int num_proceso){
  int vector_aux[8];
  int i;
  mat_mem[num_proceso][5] = 1;
  mat_mem[num_proceso][6] = mat_mem[num_proceso][3];
  mat_mem[num_proceso][7] = 1000;//rescata variables que sirven despues de borrar
  for ( i = 1; i<5 ; i++){
    mat_mem[num_proceso][i] = 0; //borra variables que no seran utiles
  }
  for ( i = 0; i < 9; i++){ //se respalda particion en vector_aux
    vector_aux[i] = mat_mem[num_proceso][i];
  }
  for( i = num_proceso; i < proceso_memoria ; i++){ //se recorren todas las particiones con procesos
    for (int j = 0; j < 8; j++){
      mat_mem[i][j] = mat_mem[i+1][j];
    }
  }
  for (int j = 0; j < 8; j++){ //se copia vector_aux en la ultima posicion de la matriz mat_mem
    mat_mem[i-1][j] = vector_aux[j];
  }
}

int consulta_memoria(int tamanio_proceso){ //regresa proceso_a_memoria = 1 cuando se encuentra espacio
  int i=0, m=0, salir=0, diferencia=0, diferencia_aux=100;// y 0 cuando no hay espacio, tambien envía la posición en bloque de memoria para guardar el proceso
  int i_select=0, si_part=0,  i_frag=0;
  if (mat_mem[0][0] == 0 && mat_mem[0][1] == 0 && mat_mem[0][2] == 0 && mat_mem[0][3] == 0 && mat_mem[0][4] == 0 &&
    mat_mem[0][5] == 0 && mat_mem[0][6] == 0 && mat_mem[0][7] == 0){
    memo_libre -= tamanio_proceso;
    proceso_a_memoria = 1;
    return 0;
  }
	while (mat_mem[++m][5] == 0);
	  if( m <= proceso_memoria){
	  	si_part=1;
		  for(int j = m; j <=proceso_memoria; j++){
		  	if(mat_mem[j][6] >= tamanio_proceso){
		  		diferencia=mat_mem[j][6] - tamanio_proceso;
		  		if(diferencia <= diferencia_aux){
		  			i_select = j;
		  			diferencia_aux = diferencia;
		  			i_frag=1;
		  		}
			  }
		  }
	}
  
  /*while (mat_mem[i][5] == 0 && salir ==0){ //posicion 6 indica si el bloque de memoria está libre (0 no libre)(1 libre)
    if (mat_mem[i+1][6]>=tamanio_proceso && mat_mem[i+1][5]==1){// el bloque 7 indica el tamaño libre del presente bloque
      proceso_memoria--;
      proceso_a_memoria = 1; //pone a uno para indicar que si se puede proceder con el almacenamiento
      return ++i; //regresa la posicion del bloque de memoria libre
    }
    if (i==100){
      salir = 1;
    }
    i++;
  } */ 
  //llega a esta condicion cuando no se encontro ningun bloque de memoria libre
	  if (tamanio_proceso <= memo_libre){ //por lo que ahora busca en memoria que no esta fragmentada  ***
	    proceso_a_memoria = 1; //***
	    if (si_part == 1){
	    	diferencia = memo_libre - tamanio_proceso;
	    	if(diferencia <= diferencia_aux){
	    		memo_libre -= tamanio_proceso; //hace el calculo de la nueva memoria libre    ****
		    	return i_memoria+=1;  //*****
			}
			else{
				//proceso_memoria--;
				return i_select;
			}
	    		
		}
		else{
		    memo_libre -= tamanio_proceso; //hace el calculo de la nueva memoria libre    ****
		    return i_memoria+=1;  //*****
		}
	  }
  else if (memo_libre>=0){//llega aqui, por que el proceso no cabe ni en memoria particionada como tampoco en memoria libre, pero queda espacio libre donde guardar otro proceso de cola de peticion
  	if(i_frag==1){
  		proceso_memoria--;
  		proceso_a_memoria=1;
		return i_select;
	  }
	  else{
	  	proceso_a_memoria = 2;
  		cout << "\n No cabe proceso en memoria" << endl;
  		return 0;
  	}
  }
  else { //cuando llega a esta condicion indica que no se encontró espacio libre ni en memoria fragmentada como en la no fragmentada y no cabe ningun otro proceso de toda la cola de peticiones
  	proceso_a_memoria = 0; // proceso_a_memoria no deja que la funcion ingresa_memoria proceda con el alojamiento
  	cout << "\n Memoria llena" << endl;
  	return 0;
	//memo_libre -= tamanio_proceso; //hace el calculo de la nueva memoria libre    ****
    //return i_memoria+=1;  //*****
  }
    
}

void cola_peticiones(int *proces){
  for (int i=0; i<8; i++) //copia el vector proceso a la cola de peticiones en la posicion 
    mat_proc[cola][i] = proces[i];// cola (cola inicia en 0)
    cola++;
}

void ingresa_memoria(int selec_proc){
  int j, selec_proc_aux = selec_proc;
  // si mete == 0 entonces saca un vector de la matriz mat_proc y la copia a 
  //una posicion de mat_mem
  if (cola == 0) { //si no hay procesos en cola envia mensaje y no hace nada
    cout << "\n No hay peticiones" << endl;
  }/*
  else if ( memo_libre<=0 ){
  	cout << "\n Memoria llena" << endl;
  }*/
  else{
    selec_mem = consulta_memoria(mat_proc[selec_proc][3]);
    if (proceso_a_memoria==1){
      proceso_memoria++;
      mat_proc[selec_proc][0] = id_part++;      	
      
      if (mat_mem[selec_mem][5] == 1){ // en caso de que el lugar de memoria donde se va a pasar el proceso de peticiones, sea una particion 
    	mat_proc[selec_proc][4] = mat_mem[selec_mem][6] - mat_proc[selec_proc][3]; // pasa la diferencia a la parte de fragmento externo
    	mat_proc[selec_proc][0] = mat_mem[selec_mem][0];
		}
      if (antiguedad_proceso > 1001)
		antiguedad_proceso = 0;
      if(cola == 1){//si hay un proceso en cola de peticiones, entonces es el único que puede copiar
	for(int i=0; i<8; i++){// a memoria
	    mat_mem[selec_mem][i] = mat_proc[0][i];
	    mat_proc[1][i] = 0; // y borra el vector actual de mat_proc
	} 
      }
      else{ //cuando hay mas de dos procesos en cola, entonces copia cual es el seleccionado (selec) a mat_mem
	for (int i = 0; i<8; i++){
	    mat_mem[selec_mem][i]= mat_proc[selec_proc][i];
	    
	}
	for (j = selec_proc; j<cola ; j++){ //recorre los vectores de cola de peticiones hacia arriba
	  for (int i=0; i<8;i++){
	    mat_proc[j][i] = mat_proc[j+1][i];
	  }
	}
	for (int i =0; i<8; i++){ //se borra el último vector
	  mat_proc[j][i] = 0;
	}
      }
      mat_mem[selec_mem][7] = antiguedad_proceso++;
      cola--;
    }
    else if (proceso_a_memoria == 2){
    	//selec_mem = consulta_memoria(mat_proc[++selec_proc][3]);
    	if (mat_proc[++selec_proc_aux ][3]!= 0){
    		cout << "\n Siguiente proceso" << endl;
			ingresa_memoria(selec_proc_aux);
		}
	}
  }
  ordenamiento();
}

int main(){ 
  /*
  int proces2[8]={2,2,3,10,0,0,0,0};
  cola_peticiones(proces2);
  
  int proces3[8]={3,2,3,11,0,0,0};
  cola_peticiones(proces3);
  
  int proces4[8]={4,2,3,12,0,0,0};
  cola_peticiones(proces4);
  
  int proces5[8]={5,2,3,13,0,0,0};
  cola_peticiones(proces5);
  
  int proces6[8]={6,2,3,14,0,0,0};
  cola_peticiones(proces6);
  
  int proces7[8]={7,2,3,15,0,0,0};
  cola_peticiones(proces7);
  
   int proces8[8]={7,2,3,16,0,0,0};
  cola_peticiones(proces8);
  
   int proces9[8]={7,2,3,17,0,0,0};
  cola_peticiones(proces9);
  
   int proces10[8]={7,2,3,18,0,0,0};
  cola_peticiones(proces10);
  
   int proces11[8]={7,2,3,19,0,0,0};
  cola_peticiones(proces11);

  ingresa_memoria(0);
  ingresa_memoria(0);
  ingresa_memoria(0);
  ingresa_memoria(0);
  ingresa_memoria(0);
  ingresa_memoria(0);
  ingresa_memoria(0);
  
  imprimir_memoria();
  imprimir_peticiones();
  
  terminar_proceso_memoria(0);
  
 
  ingresa_memoria(0);
  imprimir_memoria();
  
     int proces12[8]={7,2,3,10,0,0,0};
  cola_peticiones(proces12);
  
  ingresa_memoria(0);
  imprimir_memoria();
  imprimir_peticiones();
  */

int peticion=0, term_proceso=0;
 bool bandera=false;
    char tecla;
 
    do
    {
        system("cls");
        cin.clear();
        cout << "Menu Principal" << endl;
        cout << "-----------" << endl << endl;
        cout << "\t1 .- Ingresar peticion" << endl;
        cout << "\t2 .- Cargar a memoria" << endl;
        cout << "\t3 .- Mostrar tabla de peticiones" << endl;
        cout << "\t4 .- Mostrar memoria" << endl;
        cout << "\t5 .- Terminar proceso" << endl;
        cout << "\t6 .- Compactar" << endl;
        cout << "\t7 .- Salir" << endl << endl;
        cout << "Elije una opcion: ";
 
        cin >> tecla;
 
		switch(tecla)
		{
			case '1':
				system("cls");
				cout << "Ingresar peticion.\n";
				cout << "\nIngresa una peticion menor a 100:  ";
				cin >> peticion ;
				if (peticion <1 || peticion > 100)
					cout << "\n Opcion no valida, el tamanio debe ser mayor a 0 y menor a 101" << endl;
				else
					genera_peticion(peticion);
				pausa();
				break;
 
			case '2':
				system("cls");
				cout << "Cargar a memoria.\n";
				if (cola>0)
					ingresa_memoria(0);
				else
					cout << "\n No hay procesos en cola" << endl;
				pausa();
				break;
 
			case '3':
				system("cls");
				cout << "Mostrar tabla de peticiones.\n";
				imprimir_peticiones();
				pausa();
				break;
 
			case '4':
				system("cls");
				cout << "Mostrar memoria.\n";
				imprimir_memoria();
				pausa();
				break;
				
			case '5':
				system("cls");
				cout << "Terminar proceso.\n";
				cout << "\n Indique el proceso a terminar : " << endl;
				cin >> term_proceso;
				if (term_proceso < proceso_memoria && term_proceso>=0)
				terminar_proceso_memoria(term_proceso);
				else
				cout << "\n Proceso no encontrado" <<endl;
				pausa();
				break;
				
			case '6':
				system("cls");
				cout << "Compactar.\n";
				compactar();
				pausa();
				break;
 
			case '7':
				bandera=true;
				//exit(1);
				break;
 
			default:
				system("cls");
				cout << "Opcion no valida.\a\n";
				pausa();
				break;
		}
    }while(bandera!=true);
 
    return 0;
}
 
void pausa()
{
    cout << "Pulsa una tecla para continuar...";
    getwchar();
    getwchar();
}


