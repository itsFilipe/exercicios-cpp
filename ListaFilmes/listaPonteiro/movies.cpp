#include "movies.h"
#include <iostream>

// Construtor
Movies::Movies(int capacity)
    : size(0), capacity(capacity) {
    movies = new Movie[capacity];
    std::cout << "Construtor\n";
}

// Destrutor
Movies::~Movies() {
    delete[] movies;
    std::cout << "Destrutor\n";
}

// Resize
void Movies::resize() {
    capacity *= 2;

    Movie* newArray = new Movie[capacity];

    for (int i = 0; i < size; i++)
        newArray[i] = movies[i];

    delete[] movies;
    movies = newArray;
}

// Copy Constructor
Movies::Movies(const Movies& other)
    : size(other.size), capacity(other.capacity) {

    movies = new Movie[capacity];

    for (int i = 0; i < size; i++)
        movies[i] = other.movies[i];

    std::cout << "Copy constructor\n";
}

// Copy Assignment
Movies& Movies::operator=(const Movies& other) {

    std::cout << "Copy assignment\n";

    if (this == &other)
        return *this;

    delete[] movies;

    size = other.size;
    capacity = other.capacity;

    movies = new Movie[capacity];

    for (int i = 0; i < size; i++)
        movies[i] = other.movies[i];

    return *this;
}

// Move Constructor
Movies::Movies(Movies&& other) noexcept
    : movies(other.movies),
      size(other.size),
      capacity(other.capacity) {

    other.movies = nullptr;
    other.size = 0;
    other.capacity = 0;

    std::cout << "Move constructor\n";
}

// Move Assignment
Movies& Movies::operator=(Movies&& other) noexcept {

    std::cout << "Move assignment\n";

    if (this == &other)
        return *this;

    delete[] movies;

    movies = other.movies;
    size = other.size;
    capacity = other.capacity;

    other.movies = nullptr;
    other.size = 0;
    other.capacity = 0;

    return *this;
}

// Add Movie
bool Movies::add_movie(std::string name, std::string rating, int watched) {

    for (int i = 0; i < size; i++) {
        if (movies[i].get_name() == name)
            return false;
    }

    if (size == capacity)
        resize();

    movies[size] = Movie(name, rating, watched);
    size++;

    return true;
}