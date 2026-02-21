#ifndef _MOVIES_H_
#define _MOVIES_H_

#include <vector>
#include <string>
#include "movie.h"

class movies {
    std::vector<movie> myMovies;

public:
    movies(); 
    ~movies();  

    bool add_movie(std::string movieName, std::string rating, int timesWatched);
    bool increment_watched(std::string movieName);
    void display() const;
};

#endif
