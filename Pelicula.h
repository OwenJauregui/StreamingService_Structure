//Owen Jáuregui Borbón
//A01638122

#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"

class Pelicula:public Video
{
    public:

        Pelicula(std::vector<std::string>);

        std::string quitarEspacio(std::string);
        std::ostream& print(std::ostream&);

};

#endif