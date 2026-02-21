#include <iostream>
#include "movies.h"

void addMovie(movies &m, std::string nome, std::string rate, size_t watched);
void incrementWatched(movies &m, std::string nome);

int main() {

    movies minhaLista;

    minhaLista.display(); //nenhum filme

    addMovie(minhaLista, "Big", "PG-13",2);                 // OK
    addMovie(minhaLista,"Star Wars", "PG",5);             // OK
    addMovie(minhaLista,"Cinderella", "PG",7);           // OK
     
    minhaLista.display();   // Big, Star Wars, Cinderella
    
    addMovie(minhaLista,"Cinderella", "PG",7);            // Already exists
    addMovie(minhaLista,"Ice Age", "PG",12);              // OK
 
    minhaLista.display();    // Big, Star Wars, Cinderella, Ice Age
    
    incrementWatched(minhaLista,"Big");                    // OK
    incrementWatched(minhaLista,"Ice Age");              // OK
    
    minhaLista.display();    // Big and Ice Age watched count incremented by 1
    
    incrementWatched(minhaLista,"XXX");         // XXX not found

	return 0;
}

void addMovie(movies &m, std::string nome, std::string rate, size_t watched){
    if(m.add_movie(nome, rate, watched)){
        std::cout << nome << " adicionado." << std::endl;
    } else {
        std::cout << nome << " ja existe." << std::endl;
    }
}

void incrementWatched(movies &m, std::string nome){
    if(m.increment_watched(nome)){
        std::cout << "Quantidade assistida de " << nome << " foi incrementada." << std::endl;
    } else {
        std::cout << nome << " não existe." << std::endl;
    }
}