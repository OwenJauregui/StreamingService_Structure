//Owen Jáuregui Borbón
//A01638122

#ifndef SERIE_H
#define SERIE_H

#include "Episodio.h"

struct Serie
{
    std::string titulo;
    std::vector<Episodio*> episodios;
};

#endif