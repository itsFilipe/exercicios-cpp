#include <iostream>
#include "movie.h"

movie::movie(std::string mn, std::string r, size_t tw)
    : movieName(mn), rating(r), timesWatched(tw) {}

movie::movie(const movie &source)
    : movie{source.movieName, source.rating, source.timesWatched} {}

movie::~movie() {}

void movie::display() const {
    std::cout << movieName << ", " << rating <<  ", " << timesWatched << std::endl;
}