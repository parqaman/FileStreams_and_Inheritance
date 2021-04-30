#pragma once
#include "Mediafiles.h"
#include <iostream>
#include <vector>
#include <string>
#include "Movie.h"
#include "Serie.h"
#include "Mediafiles.h"
class Database
{
private:
    enum class Options { ADD = 1, REMOVE, EVALUATION, SHOW, SPECIFIC_MOVIE, SORTED_LIST, SAVE, EXIT };

public:
    static void init(const char* bytestream);
    static void mainMenu();
    static void compareFilms(Movie& comparedMovie);
private:
    static void addFile();
    static void removeFilm();
    static void showFilmlist();
    static void watch();
    static void evaluateFilm();
    static void sortedList();
    static void saveData();
    Database();
    //_________________HELPFUL FUNCTIONS____________________________________
    static int convertStr2Int(const char*& ptr);
    static std::string substr(const char*& ptr);
    static void pauseProgramm(const char*);
    static std::string readString();
private:
    static std::vector <Mediafiles*> mediaList;
    static int numOfSeries;
    static int numOfMovies;

};

