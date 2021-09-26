#ifndef BITACORA_H
#define BITACORA_H
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Entrada.h"
using namespace std;

class Bitacora{
  public:
    //Constructor
    Bitacora();

    //Funciones
    void cargaDatos(string);
    void sort();
    int binSearch(int, int, char);
    void searchRange(int, int, int, int);
    string total_segToTime(int);
    string numToMonth(int);
    void guardar(int, int, int, int);
  
  private:
    vector<Entrada*> bitacora; //Vector que guarda las entradas de la bitacora
};

Bitacora::Bitacora(){
}

//Lee el archivo .txt y guarda cada linea como elemento del vector bitacora
void Bitacora::cargaDatos(string file){
  //Declaración de variables
  string mes_s, IP, razon;
  int mes, dia, total_seg = 0;

  ifstream archivo;
  archivo.open(file);

  if(archivo.is_open()){ 
    string linea;
    while(getline(archivo, linea)){//Lee una linea y la guarda en un string
      total_seg = 0;
      stringstream sstr(linea);//sstream para guardar datos especificos
      string dato;//Aqui se guarda cada string separado por ' '
      string paste_str;//Aqui se unen las palabras de la razon de error
      vector<string> datos;//vector donde se guardan temporalmente los datos
      int i = 0; //Para llevar cuenta del dato que se esta leyendo
      while (getline(sstr, dato, ' ')){//Guarda cada dato separado por ' ' en "dato"
        if(i < 4){//Guarda el string obtenido tal cual hasta el cuarto
          datos.push_back(dato);
        //Como el dato de razon esta separado por espacios unimos cada
        //string obtenido a partir del cuarto en una sola variable
        } else if(i == 4){
          paste_str += ' ' + dato + ' ';
        } else {
          paste_str += dato + ' ';
        }
        i++;
      }

      mes_s = datos[0];
      //Guarda el mes como su int correspondiente para
      //facilitar sorting y busqueda
      if(mes_s == "Jan"){
          mes = 1;
      }
      else if(mes_s == "Feb"){
          mes = 2;
      }
      else if(mes_s == "Mar"){
          mes = 3;
      }
      else if(mes_s == "Apr"){
          mes = 4;
      }
      else if(mes_s == "May"){
          mes = 5;
      }
      else if(mes_s == "Jun"){
          mes = 6;
      }
      else if(mes_s == "Jul"){
          mes = 7;
      }
      else if(mes_s == "Aug"){
          mes = 8;
      }
      else if(mes_s == "Sep"){
          mes = 9;
      }
      else if(mes_s == "Oct"){
          mes = 10;
      }
      else if(mes_s == "Nov"){
          mes = 11;
      }
      else if(mes_s == "Dec"){
          mes = 12;
      }
      dia = stoi(datos[1]);
      //Para facilitar el sorting y la busqueda se guarda el
      //tiempo como un int con el total de segundos
      istringstream tiempo(datos[2]); //Para guardar el tiempo en las variables hh mm y ss
      int hh, mm, ss;
      char c; //Aqui se guarda el ':' 
      tiempo >> hh >> c >> mm >> c >> ss;
      total_seg += hh * 3600;
      total_seg += mm * 60;
      total_seg += ss;
      IP = datos[3];
      razon = paste_str;
      bitacora.push_back(new Entrada(mes, dia, total_seg, IP, razon)); //Creacion de una entrada
    }
    archivo.close();
  } else {
    cout << "Error al tratar de leer el archivo" << endl;
  }
}

//Algoritmo de ordenamiento por intercambio
void Bitacora::sort(){
  for(int i = 0; i < bitacora.size() - 1; i++){
    for (int j = i + 1; j < bitacora.size(); j++){
      if (bitacora[i]->getMes() > bitacora[j]->getMes()){
        swap(bitacora[i], bitacora[j]);
      }
      else if (bitacora[i]->getMes() == bitacora[j]->getMes() && bitacora[i]->getDia() > bitacora[j]->getDia()){
        swap(bitacora[i], bitacora[j]);
      }
      else if (bitacora[i]->getMes() == bitacora[j]->getMes() && bitacora[i]->getDia() == bitacora[j]->getDia()
      && bitacora[i]->getTotal_seg() > bitacora[j]->getTotal_seg()){
        swap(bitacora[i], bitacora[j]);
      }
    }
  }
}

//Algoritmo de busqueda binaria. KeyM es el mes que se busca y KeyD el dia
//flag indica si se busca la fecha inicio o final, es decir 'i' o 'f'
int Bitacora::binSearch(int keyM, int keyD, char flag){
  int izq = 0; //Inicio del vector
  int der = bitacora.size(); //Final del vector
  //Caso particular para extremo final
  if((bitacora[der-1] -> getMes() <= keyM && bitacora[der-1] -> getDia() <= keyD)
    || bitacora[der-1] -> getMes() < keyM){
      return der-1;
    }

  while(izq <= der){//Inicio de busqueda binaria
    int acc = 0; //Acumulador de instancias repetidas
    int mid = izq + (der - izq) / 2; //Se obtiene la mitad
    if(keyM == bitacora[mid]->getMes() && keyD == bitacora[mid]->getDia()){//Encuentra la fecha
      if(flag == 'i'){//Si es el inicio itera en reversa para buscar la primera instancia
        while(keyD == bitacora[mid + acc]->getDia()){
          acc--;
        }
        return mid + acc + 1; //Regresa la primera instancia
      }
      else{//flag == 'f' itera para encontrar la ultima instancia de la fecha
        while(keyD == bitacora[mid + acc]->getDia()){
          acc++;
        }
      }
      return mid + acc - 1;//Regresa la ultima instancia
    }
    else if((bitacora[mid]->getMes() == keyM  && bitacora[mid] -> getDia() > keyD)
    || bitacora[mid] -> getMes() > keyM){//Si la fecha se encuentra en la mitad izquierda
      der = mid - 1;
    }
    else{//Si la fecha se encuentra en la mitad derecha
      izq = mid + 1;
    }
  }
  if(flag == 'i'){//Si no encontro la fecha inicial regresa el siguiente elemento
    return izq;
  }
  else if(flag == 'f'){//Si no encontro la fecha final regresa el elemento anterior
    return der;
  }
  else{
    return -1; 
  }
}

void Bitacora::searchRange(int keyM_s, int keyD_s, int keyM_a, int keyD_a){
  int inicio = binSearch(keyM_s, keyD_s, 'i'); //Diferencia como fecha de inicio
  int fin = binSearch(keyM_a, keyD_a, 'f'); //Diferencia como fecha final
  for(; inicio <= fin; inicio++){//Itera el rango obtenido para imprimir datos
    cout << numToMonth(bitacora[inicio] -> getMes()) << ' ' << bitacora[inicio] -> getDia() << ' ';
    cout << total_segToTime(inicio);
    cout << bitacora[inicio] -> getIP() << bitacora[inicio] -> getRazon() << endl;
  }
}

string Bitacora::total_segToTime(int i){//Convierte total de seg a formato hh:mm:ss
  int hh, mm, ss;
  stringstream buffer; //sstream para guardar el formato del cout a string 
  string time;
  int total_seg = bitacora[i] -> getTotal_seg();
  hh = total_seg/3600;
  total_seg = total_seg - (hh * 3600);
  mm = total_seg / 60;
  ss = total_seg - (mm * 60);
  buffer << setw(2) << setfill('0') << hh << ":"
       << setw(2) << setfill('0') << mm << ":"
       << setw(2) << setfill('0') << ss << ' ';
  return buffer.str();
}

string Bitacora::numToMonth(int m){//Convierte int al string del mes correspondiente
  vector<string> months {"Jan", "Feb", "Mar", "Apr", "May",
  "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  return months[m - 1];
}

 //En esta parte se realizará un nuevo txt donde se guardaran los datos pedidos. 
 //Se usa una estructura similar a searchRange, ya que esos mismos datos que se 
 //imprimen en la consola, son los mismos que se deben de guardar en el txt
void Bitacora::guardar(int keyM_s, int keyD_s, int keyM_a, int keyD_a){
	ofstream registro;
	registro.open("sorted.txt",ios::out); //aquí se generará un txt que se llama sorted.txt donde se guardará todo
  //se hará la búsqueda binaria declarando el inicio y el final
	int inicio = binSearch(keyM_s, keyD_s, 'i');
  int fin = binSearch(keyM_a, keyD_a, 'f');
  for(; inicio <= fin; inicio++){
    //todos los datos, en vez de ser impresos en la consola, serán guardados en el txt 
    registro << numToMonth(bitacora[inicio] -> getMes()) << ' ' << bitacora[inicio] -> getDia() << ' ';
    registro << total_segToTime(inicio);
    registro << bitacora[inicio] -> getIP() << bitacora[inicio] -> getRazon() << endl;
  }
  registro.close();	//aquí se cierra el registro 

}

#endif