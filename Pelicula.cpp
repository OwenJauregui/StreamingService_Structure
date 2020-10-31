//Owen Jáuregui Borbón
//A01638122

#include "Pelicula.h"

Pelicula::Pelicula(std::vector<std::string> datos):Video(datos){}


std::ostream& Pelicula::print(std::ostream& os)
{
    os << "Pelicula: \"" << this->nombre << '"' << std::endl;
    os << "Genero: " << this->genero << std::endl;
    os << "Duracion: " << this->duracion << " minutos" << std::endl;
    if (this->calificacion > 0)
    {
        os << "Calificacion: " << this->calificacion << std::endl;
    }
    else 
    {
        os << "Aun no tiene calificacion" << std::endl;
    }
    os << "Id: " << this->id << std::endl;

    return os;
}