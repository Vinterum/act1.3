#ifndef ENTRADA_H
#define ENTRADA_H
#include <iostream>
using namespace std;

class Entrada {    
    public:
        //Constructores
        Entrada();
        Entrada(int, int, int, string, string); 

        //Metodos de acceso
        int getMes()const;
        int getDia()const;
        int getTotal_seg()const;
        string getIP()const;
        string getRazon()const;

        //Metodos de modificacion
        void setMes(int);
        void setDia(int);
        void setTotal_seg(int);
        void setIP(string);
        void setRazon(string);

        // Otros metodos
        string toString();

        // sobrecargas
        friend ostream& operator<< (ostream&, Entrada*);
    
    private:
        // atributos
        int mes, dia, total_seg;
        string IP, razon;

};

Entrada::Entrada(){
  mes = 0;
  dia = 0;
  total_seg = 0;
  IP = "s/n";
  razon = "s/n";
}

Entrada::Entrada(int mes, int dia, int total_seg, string IP, string razon){
  this -> mes = mes;
  this -> dia = dia;
  this -> total_seg = total_seg;
  this -> IP = IP;
  this -> razon = razon;
}

int Entrada::getMes()const{
  return mes;
}

int Entrada::getDia()const{
  return dia;
}

int Entrada::getTotal_seg()const{
  return total_seg;
}

string Entrada::getIP()const{
  return IP;
}

string Entrada::getRazon()const{
  return razon;
}

void Entrada::setMes(int mes){
  this -> mes = mes;
}

void Entrada::setDia(int dia){
  this -> dia = dia;
}

void Entrada::setTotal_seg(int total_seg){
  this -> total_seg = total_seg;
}

void Entrada::setIP(string IP){
  this -> IP = IP;
}

void Entrada::setRazon(string razon){
  this -> razon = razon;
}

string Entrada::toString(){
    //Se guarda un string con los datos que se deben imprimir
    string info = to_string(mes) + ' ' + to_string(dia) + ' ' + to_string(total_seg) + ' ' + IP + razon;
    return info;
}

ostream& operator<< (ostream& salida, Entrada* ent){
    //Cuando se ponga un objeto entrada frente a un cout se imprimirá el toString directamente
    salida << ent -> toString();
    return salida;
}

#endif