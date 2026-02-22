#ifndef MOVIES_H
#define MOVIES_H

#include "movie.h"

class Movies {
private:
    Movie* movies;
    int size;
    int capacity;

    void resize();

public:
    Movies(int capacity = 10);
    ~Movies();

    // Rule of Five
    Movies(const Movies& other);
    Movies& operator=(const Movies& other);

    Movies(Movies&& other) noexcept;
    Movies& operator=(Movies&& other) noexcept;

    bool add_movie(std::string name, std::string rating, int watched);
};

#endif