#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
private:
    std::string name;
    std::string rating;
    int watched;

public:
    Movie();
    Movie(std::string name, std::string rating, int watched);

    std::string get_name() const;
    void increment_watched();
};

#endif