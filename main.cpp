#include "Mediafiles.h"
#include "Movie.h"
#include "Serie.h"
#include "Database.h"
#include<vector>
#include<fstream>

int main()
{
	
    int size = 600;
    char* bytestream = new char[size];

    std::string filePath = "Database.txt";
    std::ifstream in;
    in.open(filePath, std::ios::in);

    if (in.good()) {
        // read file into array
        int dynamic_size = 0;
        for (char c = in.get(); in.good(); c = in.get()) {
            bytestream[dynamic_size] = c;
            dynamic_size++;
        }
        in.close();

        Database::init(bytestream);
        Database::mainMenu();

        //comparing two films
        Movie newMovie("Imitation Game", "555", "Action", 120, 2020);
        Database::compareFilms(newMovie);
    }
    delete[] bytestream;

	return 0;
}