#include "movie.h"

Movie::Movie()
    : name(""), rating(""), watched(0) {}

Movie::Movie(std::string name, std::string rating, int watched)
    : name(name), rating(rating), watched(watched) {}

std::string Movie::get_name() const {
    return name;
}

void Movie::increment_watched() {
    watched++;
}