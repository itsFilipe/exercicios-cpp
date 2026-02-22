#include "movies.h"

Movies createCollection() {
    Movies temp;
    temp.add_movie("Matrix", "R", 5);
    return temp;
}

int main() {

    Movies a;
    a.add_movie("Batman", "PG", 3);

    Movies b = a;          // Copy constructor

    Movies c;
    c = a;                 // Copy assignment

    Movies d = createCollection();  // Move constructor

    Movies e;
    e = createCollection();         // Move assignment

    return 0;
}