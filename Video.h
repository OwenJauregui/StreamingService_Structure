//Owen Jáuregui Borbón
//A01638122

#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

class Video
{
    protected:

        int duracion, num_calif;
        double calificacion;
        std::string id,nombre,genero;

    public:

        Video(std::vector<std::string>);

        void calificar(int);
        double getCalificacion();
        std::string getGenero();
        std::string getId();

        virtual std::ostream& print(std::ostream&) = 0;

        friend std::ostream& operator << (std::ostream& os, Video& vd)
        {
            return vd.print(os);
        }
               
};

#endif