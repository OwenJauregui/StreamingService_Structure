//Owen Jáuregui Borbón
//A01638122

#include "Episodio.h"

Episodio::Episodio(std::vector<std::string> datos):Video(datos)
{
    this->serie = datos[5];
    this->episodio = std::stoi(datos[6]);
}

std::ostream& Episodio::print(std::ostream& os)
{
    os << "Serie: \"" << this->serie << '"' << std::endl;
    os << "Episodio " << this->episodio;
    os << ": " << this->nombre << std::endl;
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

std::string Episodio::getSerie(){return this->serie;}