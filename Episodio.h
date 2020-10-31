//Owen Jáuregui Borbón
//A01638122

#ifndef EPISODIO_H
#define EPISODIO_H

#include "Video.h"

class Episodio:public Video
{
    private:
        int episodio;
        std::string serie; 

    public:

        Episodio(std::vector<std::string>);

        std::ostream& print(std::ostream&);
        std::string getSerie();

};

#endif