#include <iostream>
#include "movies.h"

movies::movies() {
}

movies::~movies() {
}

bool movies::add_movie(std::string movieName, 
                       std::string rating, 
                       int timesWatched) {

    for(size_t i = 0; i < myMovies.size(); i++) {
        if(myMovies.at(i).get_name() == movieName) {
            return false;  
        }
    }

    movie m(movieName, rating, timesWatched);
    myMovies.push_back(m);
    return true;
}

bool movies::increment_watched(std::string movieName) {

    for(size_t i = 0; i < myMovies.size(); i++) {

        if(myMovies.at(i).get_name() == movieName) {
            myMovies.at(i).increment_watched();
            return true;
        }

    }

    return false;
}

void movies::display() const {
    if(myMovies.size() == 0) {
        std::cout << "Nenhum filme a ser listado...\n" << std::endl;
    } else {
        std::cout << "=================================\n";
        for (size_t i = 0; i < myMovies.size(); i++)
        {
            myMovies.at(i).display();
        }
        std::cout << "=================================\n";
        std::cout << std::endl;
    }
}