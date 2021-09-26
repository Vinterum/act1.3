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

    void cargaDatos(string);
    void imprime();
    vector<Entrada*> getBitacora()const;
    void sort();
    int binSearch(int, int, char);
    void searchRange(int, int, int, int);
    void total_segToTime(int);
    string numToMonth(int);
  
  private:
    vector<Entrada*> bitacora;
};

Bitacora::Bitacora(){
}

void Bitacora::cargaDatos(string file){
  //Declaración de variables
  string mes_s, IP, razon;
  int mes, dia, total_seg = 0;
  ifstream archivo;
  archivo.open(file);
  if(archivo.is_open()){
    string linea;
    while(getline(archivo, linea)){
      total_seg = 0;
      stringstream sstr(linea);
      string dato, paste_str;
      vector<string> datos;
      int i = 0;
      while (getline(sstr, dato, ' ')){ 
        if(i < 4){
          datos.push_back(dato);
        } else if(i == 4){
          paste_str += ' ' + dato + ' ';
        } else {
          paste_str += dato + ' ';
        }
        i++;
      }
      istringstream tiempo(datos[2]);
      int hh, mm, ss;
      char c;
      tiempo >> hh >> c >> mm >> c >> ss;
      total_seg += hh * 3600;
      total_seg += mm * 60;
      total_seg += ss;
      mes_s = datos[0];
      if(mes_s == "Jun"){
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
      dia = stoi(datos[1]);
      IP = datos[3];
      razon = paste_str;
      bitacora.push_back(new Entrada(mes, dia, total_seg, IP, razon));
    }
    archivo.close();
  } else {
    cout << "Error al tratar de leer el archivo" << endl;
  }
}

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

void Bitacora::imprime(){
  cout << "Hay " << bitacora.size() << "entradas" << endl << endl;
  for (int i = 0; i < bitacora.size(); i++){
    cout << bitacora[i] << endl;
  }
}

int Bitacora::binSearch(int keyM, int keyD, char flag){
  int izq = 0;
  int der = bitacora.size();
  if((bitacora[der-1] -> getMes() <= keyM && bitacora[der-1] -> getDia() <= keyD)
    || bitacora[der-1] -> getMes() < keyM){
      return der-1;
    }

  while(izq <= der){
    int acc = 0;
    int mid = izq + (der - izq) / 2;
    if(keyM == bitacora[mid]->getMes() && keyD == bitacora[mid]->getDia()){
      if(flag == 's'){
        while(keyD == bitacora[mid + acc]->getDia()){
          acc--;
        }
        return mid + acc + 1;
      }
      else{
        while(keyD == bitacora[mid + acc]->getDia()){
          acc++;
        }
      }
      return mid + acc - 1;
    }
    else if((bitacora[mid]->getMes() == keyM  && bitacora[mid] -> getDia() > keyD)
    || bitacora[mid] -> getMes() > keyM){
      der = mid - 1;
    }
    else{
      izq = mid + 1;
    }
  }
  if(flag == 's'){
    return izq;
  }
  else if(flag == 'a'){
    return der;
  }
  else{
    return -1;
  }
}

void Bitacora::searchRange(int keyM_s, int keyD_s, int keyM_a, int keyD_a){
  int inicio = binSearch(keyM_s, keyD_s, 's');
  int fin = binSearch(keyM_a, keyD_a, 'a');
  cout << inicio << endl;
  cout << fin << endl;
  for(; inicio <= fin; inicio++){
    cout << numToMonth(bitacora[inicio] -> getMes()) << ' ' << bitacora[inicio] -> getDia() << ' ';
    total_segToTime(inicio);
    cout << bitacora[inicio] -> getIP() << bitacora[inicio] -> getRazon() << endl;
  }
}

void Bitacora::total_segToTime(int i){
  int hh, mm, ss;
  string time;
  int total_seg = bitacora[i] -> getTotal_seg();
  hh = total_seg/3600;
  total_seg = total_seg - (hh * 3600);
  mm = total_seg / 60;
  ss = total_seg - (mm * 60);
  cout << setw(2) << setfill('0') << hh << ":"
       << setw(2) << setfill('0') << mm << ":"
       << setw(2) << setfill('0') << ss << ' ';
}

string Bitacora::numToMonth(int m){
  vector<string> months {"Jan", "Feb", "Mar", "Apr", "May",
  "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  return months[m - 1];
}


#endif