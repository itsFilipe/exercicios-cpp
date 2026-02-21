#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>

class movie {
    std::string movieName;
    std::string rating;
    size_t timesWatched;

public:
    movie(std::string mn, std::string r, size_t tw);

    movie(const movie &source); //porque?

    ~movie();

    void set_name(std::string name) {movieName = name;}
    std::string get_name() const { return movieName;}

    void set_rating(std::string rate) {rating = rate;}
    std::string get_rating() const { return rating;}

    void set_watched(size_t watched) {timesWatched = watched;}
    size_t get_watched() const { return timesWatched;}
    
    void increment_watched() { ++timesWatched; }

    void display() const;
};

#endif