//Owen Jáuregui Borbón
//A01638122

#include "Video.h"

Video::Video(std::vector<std::string> datos)
{
    this->calificacion = 0;
    this->num_calif    = 0;
    this->id           = datos[1];
    this->nombre       = datos[2];
    this->duracion     = std::stoi(datos[3]);
    std::string temp = "";
    for (int i = 0; i < datos[4].size(); ++i) {
        if (datos[4][i] >= 'a' && datos[4][i] <= 'z') {
            temp = temp + datos[4][i];
        }
    }
    this->genero = temp;
}

void Video::calificar(int calificacion_)
{
    int puntaje = this->calificacion * this->num_calif;
    this->num_calif++;
    this->calificacion = (puntaje + calificacion_)/double (this->num_calif);
}

double Video::getCalificacion(){return this->calificacion;}

std::string Video::getGenero(){return this->genero;}

std::string Video::getId(){return this->id;}