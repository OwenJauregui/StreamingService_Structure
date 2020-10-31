//Owen Jáuregui Borbón
//A01638122
//Creado: 08/06/2020

#include <fstream>
#include <exception>
#include <limits>
#include <algorithm>
#include "Pelicula.h"
#include "Serie.h"

class file_error:public std::exception 
{
    virtual const char* what() const throw()
    {
        return "Archivo no encontrado";
    }
};

class App
{
    private:

        enum Criterios {
                       clasificacion = 1, 
                       genero = 2,
                       id = 3
                       };

        std::vector<Serie> series;
        std::vector<Video*> videos;
        std::vector<Pelicula*> peliculas;

    public:

        void menu()
        {
            std::cout << "A lo largo de la ejecucion del programa, solo debera usar el numero de la opcion para realizar una accion" << std::endl
            << "(cualquier numero decimal sera truncado durante la ejecucion del programa)" << std::endl;
            int seleccion;
            do 
            {
                std::cout << std::endl;
                std::cout << "Seleccione una accion" << std::endl
                << "1. Cargar archivo de datos" << std::endl
                << "2. Mostrar los videos en general con una cierta calificacion o de un cierto genero" << std::endl
                << "3. Mostrar los episodios de una determinada serie con una calificacion determinada" << std::endl
                << "4. Mostrar las peliculas con cierta calificacion" << std::endl
                << "5. Calificar un video" << std::endl
                << "0. Salir" << std::endl;
                try
                {
                    seleccion = this->entradaInt();

                    switch (seleccion)
                    {
                    case 0:
                        break;

                    case 1:
                    {
                        std::string nombre;
                        std::cout << "Ingrese el nombre del archivo con extension: ";
                        std::cin  >> nombre;
                        this->cargarDatos(nombre);
                        break;
                    }

                    case 2:
                    {
                        bool correcto;
                        do{
                            try
                            {
                                std::cout << "Elija el criterio de busqueda: " << std::endl
                                << "1. Buscar por calificacion" << std::endl
                                << "2. Buscar por genero" << std::endl;
                                correcto = true;
                                int opcion = this->entradaInt();
                                if(opcion == 1 || opcion == 2)
                                {
                                    this->printVideos(this->buscarVideos(opcion));
                                } 
                                else
                                {
                                    correcto = false;
                                    std::cout << "Opcion invalida, elija una de las opciones";
                                }
                            }
                            catch(std::ios_base::failure& ex)
                            {
                                correcto = false;
                                std::cout << "Opcion invalida, debe escribir el numero de la opcion" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                        }
                        while(!correcto);
                        break;
                    }

                    case 3:
                    {
                        bool correcto;
                        do{
                            try
                            {
                                correcto = true;
                                std::cout << "Elija la serie de la que se buscaran los episodios: " << std::endl;
                                this->printSeries();
                                this->printVideos(this->buscarEpisodios(this->entradaInt()));
                            }
                            catch(std::out_of_range& ex)
                            {
                                correcto = false;
                                ex.what();
                            }
                        }
                        while(!correcto);
                        break;
                    }

                    case 4:
                        this->printVideos(this->buscarPeliculas());
                        break;

                    case 5:
                    {
                        this->calificarVideo();
                        break;
                    }
                    

                    default:
                        std::cout << "Opcion invalida, intente nuevamente" << std::endl;
                        break;
                    }
                }
                catch(std::ios_base::failure& ex)
                {
                    seleccion = -1;
                    std::cout << "Opcion invalida, debe escribir el numero de la opcion" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                catch(file_error& ex)
                {
                    std::cout << "El archivo no pudo abrirse" << std::endl;
                }
                
            }
            while(seleccion != 0);
        }

        void cargarDatos(std::string nombre)
        {
            videos.clear();
            std::ifstream archivo(nombre);
            if(archivo.is_open())
            {
                std::string linea;
                while(getline(archivo, linea))
                {
                    std::vector<std::string> datos = this->separarDatos(linea);
                    if (datos[0] == "p")
                    {
                        Pelicula* pelicula = new Pelicula(datos);
                        this->videos.push_back(pelicula);
                        this->peliculas.push_back(pelicula);
                    }
                    else if (datos[0] == "c")
                    {
                        Episodio* episodio = new Episodio(datos);
                        this->videos.push_back(episodio);
                        anexarSerie(episodio);
                    }
                }
                archivo.close();
            }
            else
            {
                throw file_error();
            }
        }

        void anexarSerie(Episodio* ep)
        {
            bool existente = false;
            std::string titulo = ep->getSerie();
            
            for(int i = 0; i < series.size(); i++)
            {
                if (this->series[i].titulo == titulo)
                {
                    this->series[i].episodios.push_back(ep);
                    existente = true;
                    break;
                }
            }

            if(!existente)
            {
                this->series.push_back(Serie());
                this->series.back().titulo = titulo;
                this->series.back().episodios.push_back(ep);
            }
        }

        void calificarVideo()
        {   
            bool correcto;
            std::vector<Video*> video_;
            video_ = buscarVideos(3);
            while(video_.size() == 0)
            {
                std::cout << "El Id del video no existe, intentelo de nuevo" << std::endl;
                video_ = buscarVideos(3);
            }

            do{
                try{
                    correcto = true;
                    video_.back()->calificar(this->verificarCal());
                }
                catch (std::invalid_argument& ex)
                {
                    correcto = false;
                    std::cout << ex.what() << std::endl;
                }
                catch(std::ios_base::failure& ex)
                {
                    correcto = false;
                    std::cout << "Se debe ingresar un numero entero" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } 
            while(!correcto);
        }

        std::vector<Video*> buscarVideos(int busqueda)
        {
            bool correcto;
            std::vector<Video*> resBusqueda;

            do{
                try
                {
                    correcto = true;
                    switch (busqueda)
                    {
                        case Criterios::clasificacion:
                        {
                            int cal = this->verificarCal();
                            for(int i = 0; i < this->videos.size(); i++)
                            {
                                int calVideo = this->videos[i]->getCalificacion()/1;
                                if(calVideo == cal)
                                {
                                    resBusqueda.push_back(this->videos[i]);
                                }
                            }
                            break;
                        }

                        case Criterios::genero:
                        {
                            std::cout << "Elija el genero que desea buscar: " << std::endl
                            << "1. Drama" << std::endl
                            << "2. Accion" << std::endl
                            << "3. Misterio" << std::endl;
                            int gen = this->entradaInt();
                            if(gen < 1 || gen > 3)
                            {
                                throw std::out_of_range("Opcion inválida, elija una de las opciones");
                            }

                            std::string generos[3] = {"drama", "accion", "misterio"};

                            for(int i = 0; i < this->videos.size(); i++)
                            {
                                std::string genVideo = this->videos[i]->getGenero();
                                if(genVideo == generos[gen - 1])
                                {
                                    resBusqueda.push_back(this->videos[i]);
                                }
                            }
                            break;
                        }

                        case Criterios::id:
                        {
                            std::cout << "Ingrese el Id del video: ";
                            std::string id_;
                            std::cin >> id_;
                            for(int i = 0; i < this->videos.size(); i++)
                            {
                                std::string idVideo = this->videos[i]->getId();
                                if(idVideo == id_)
                                {
                                    resBusqueda.push_back(this->videos[i]);
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    return resBusqueda;
                }
                catch (std::invalid_argument& ex)
                {
                    correcto = false;
                    std::cout << ex.what() << std::endl;
                }
                catch (std::out_of_range& ex)
                {
                    correcto = false;
                    std::cout << ex.what() << std::endl;
                }
                catch(std::ios_base::failure& ex)
                {
                    correcto = false;
                    std::cout << "Se debe ingresar un numero entero" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            while (!correcto);
        }

        std::vector<Episodio*> buscarEpisodios(int serie_)
        {
            if(serie_ < 1 || serie_ > this->series.size())
            {
                throw std::out_of_range("Opcion invalida: no existe esta serie");
            }

            bool correcto;
            std::vector<Episodio*> episodios;
            Serie* serie = &(this->series[serie_ - 1]);

            do{
                try{
                    correcto = true;
                    int cal = this->verificarCal();

                    for(int i = 0; i < serie->episodios.size(); i++)
                    {
                        int calEpisodio = serie->episodios[i]->getCalificacion()/1;
                        if(calEpisodio == cal)
                        {
                            episodios.push_back(serie->episodios[i]);
                        }
                    }

                    return episodios;
                }
                catch (std::invalid_argument& ex)
                {
                    correcto = false;
                    std::cout << ex.what() << std::endl;
                }
                catch(std::ios_base::failure& ex)
                {
                    correcto = false;
                    std::cout << "Se debe ingresar un numero entero" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            while(!correcto);
        }

        std::vector<Pelicula*> buscarPeliculas()
        {
            bool correcto;
            std::vector<Pelicula*> resPel;

            do{
                try{
                    correcto = true;
                    int cal = this->verificarCal();

                    for(int i = 0; i < this->peliculas.size(); i++)
                    {
                        int calPel = this->peliculas[i]->getCalificacion()/1;
                        if(calPel == cal)
                        {
                            resPel.push_back(this->peliculas[i]);
                        }
                    }

                    return resPel;
                }
                catch (std::invalid_argument& ex)
                {
                    correcto = false;
                    std::cout << ex.what() << std::endl;
                }
                catch(std::ios_base::failure& ex)
                {
                    correcto = false;
                    std::cout << "Se debe ingresar un numero entero" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            while(!correcto);
        }

        int verificarCal()
        {
            std::cout << "Ingrese la calificacion: ";
            int cal = entradaInt();

            if(cal >= 1 && cal <= 5)
            {
                return cal;
            }
            else
            {
                throw std::invalid_argument("La calificación debe ser un numero entero entre 1 y 5");
            }
            
        }

        int entradaInt()
        {
            int entrada;
            std::cin.exceptions(std::ios::failbit|std::ios::badbit);
            std::cin >> entrada;
            return entrada;
        }

        void printVideos(std::vector<Video*> videos_)
        {
            std::cout << std::endl;
            if(videos_.size() > 0)
            {
                for(int i = 0; i < videos_.size(); i++)
                {
                    std::cout << *videos_[i] << std::endl;
                }
            }
            else
            {
                std::cout << "No hay resultados" << std::endl;
            }
        }

        void printVideos(std::vector<Episodio*> episodios_)
        {
            std::cout << std::endl;
            if(episodios_.size() > 0)
            {
                for(int i = 0; i < episodios_.size(); i++)
                {
                    std::cout << *episodios_[i] << std::endl;
                }
            }
            else
            {
                std::cout << "No hay resultados" << std::endl;
            }
        }

        void printVideos(std::vector<Pelicula*> peliculas_)
        {
            std::cout << std::endl;
            if(peliculas_.size() > 0)
            {
                for(int i = 0; i < peliculas_.size(); i++)
                {
                    std::cout << *peliculas_[i] << std::endl;
                }
            }
            else
            {
                std::cout << "No hay resultados" << std::endl;
            }
            
        }

        void printSeries()
        {
            for(int i = 0; i < this->series.size(); i++)
            {
                std::cout << i + 1 << ". " << this->series[i].titulo << std::endl;
            }
        }

        std::vector<std::string> separarDatos(const std::string& info)
        {
            std::vector<std::string> datos;
            std::istringstream ss(info);
            std::string item;

            while (std::getline(ss, item, ','))
            {
                datos.push_back(item);
            }

            return datos;
        }
};

int main()
{
    App aplicacion;
    aplicacion.menu();

    return 0;
}