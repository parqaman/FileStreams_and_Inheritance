#include "Database.h"
#include <fstream>
#include <conio.h>
#include <string>

std::vector<Mediafiles*> Database::mediaList;
int Database::numOfMovies;
int Database::numOfSeries;

//----------------------------------------------------------------------------- helpful functions---------------------------------------------------------
int Database::convertStr2Int(const char*& ptr)
{
    int val = 0;
    int place = 1;
    std::string duration;

    for (; *ptr != '\n' && *ptr >= '0' && *ptr <= '9'; ptr++) {
        duration += (*ptr - '0');
    }
    // skip \r\n (binary mode) \n std::ios::in
    ptr++;
    int c;
    // z.b 198
    for (int i = duration.size() - 1; i >= 0; i--) {

        // val = val + 8  * 1 , val + val + 9 * 10, val = val + 1 * 100
        val += duration.at(i) * place;
        place *= 10;
    }
    return val;
}

std::string Database::substr(const char*& ptr)
{
    std::string string;
    for (; *ptr != '\n'; ptr++) {
        string += *ptr;
    }
    // skip \r\n (binary mode) \n std::ios::in
    ptr++;
    return string;
}

void Database::pauseProgramm(const char* string)
{
    std::cout << string;
    while (!_kbhit());
    system("cls");
}

std::string Database::readString()
{
    std::string string;
    for (char c = _getch(); c != 13; c = _getch())
    {
        string.push_back(c);
        _putch(c);
    }
    return string;
}

// ---------------------------------------------------------------------- MAIN MENU ------------------------------------------------------------------------------------------

void Database::mainMenu()
{
    int eingabe;
    do {
        std::cout << "********** Main Menu **********\n";
        std::cout << "1. Add\n2. Remove\n3. Review\n4. Show list\n5. Watch\n6. Sorted List\n7. Save Data\n8. Exit\n";
        std::cout << "Geben Sie bitte die Nummer ein: ";
        std::cin.clear();
        std::cin >> eingabe;
        switch (eingabe) {
        case (int)Options::ADD:
            addFile();
            break;
        case (int)Options::REMOVE:
            removeFilm();
            break;
        case (int)Options::EVALUATION:
            evaluateFilm();
            break;
        case (int)Options::SHOW:
            showFilmlist();
            break;
        case (int)Options::SPECIFIC_MOVIE:
            watch();
            break;
        case (int)Options::SORTED_LIST:
            sortedList();
            break;
        case (int)Options::SAVE:
            saveData();
            break;
        case (int)Options::EXIT:
            break;
        default:
            std::cout << "Falsche Eingabe\n";
        }
    } while (eingabe != (int)Options::EXIT);
    std::cout << "\n";
}

//----------------------------------------------------------------- Database section ----------------------------------------------------------------------------------

void Database::init(const char* bytestream)
{
    // figures out the List Size
    const std::string _movie = substr(bytestream);
    numOfMovies = convertStr2Int(bytestream);
        
    // insert Data into mediaList
    int startValue = 0;
    while (startValue < numOfMovies) {

        const std::string _titel = substr(bytestream);
        const int _duration = convertStr2Int(bytestream);
        const std::string _evaluation = substr(bytestream);
        const std::string _genre = substr(bytestream);
        const int _releaseYear = convertStr2Int(bytestream);

        Movie* ptr1 = new Movie(_titel, _evaluation, _genre, _duration, _releaseYear);

        mediaList.push_back(ptr1);
        startValue++;
    }

    startValue = 0;
    const std::string _series = substr(bytestream);
    numOfSeries = convertStr2Int(bytestream);
    while (startValue < numOfSeries) {
        const std::string _titel = substr(bytestream);
        const int _duration = convertStr2Int(bytestream);
        const std::string _evaluation = substr(bytestream);
        const std::string _genre = substr(bytestream);
        const int _numbersOfEpisode = convertStr2Int(bytestream);
        const int lastWatched = convertStr2Int(bytestream);

        Serie* ptr2 = new Serie(_titel, _evaluation, _genre, _duration, _numbersOfEpisode);
        ptr2->setWatchEpisode(lastWatched);

        mediaList.push_back(ptr2);
        startValue++;
    }
}

//Not yet finished
void Database::saveData() {
    std::ofstream out("Database.txt", std::ios::in);

    out << "Movies\n" << numOfMovies << "\n";

    for (int i = 0; i < numOfMovies; i++) {
        out << dynamic_cast<Movie*>(mediaList.at(i))->getTitel() << "\n"
            << dynamic_cast<Movie*>(mediaList.at(i))->getFilmduration() << "\n"
            << dynamic_cast<Movie*>(mediaList.at(i))->getReview() << "\n"
            << dynamic_cast<Movie*>(mediaList.at(i))->getGenre() << "\n"
            << dynamic_cast<Movie*>(mediaList.at(i))->getReleaseYear() << "\n";
    }

    out << "Series\n" << numOfSeries << "\n";

    for (int i = numOfMovies; i < mediaList.size(); i++) { //i begin from num of movies, because series are saved after movies
        out << dynamic_cast<Serie*>(mediaList.at(i))->getTitel() << "\n"
            << dynamic_cast<Serie*>(mediaList.at(i))->getFilmduration() << "\n"
            << dynamic_cast<Serie*>(mediaList.at(i))->getReview() << "\n"
            << dynamic_cast<Serie*>(mediaList.at(i))->getGenre() << "\n"
            << dynamic_cast<Serie*>(mediaList.at(i))->getNumOfEpisodes()<< "\n"
            << dynamic_cast<Serie*>(mediaList.at(i))->getWatchEpisode() << "\n";
    }

    out.close();
    pauseProgramm("Data saved. Please press any key to continue\n");
}

void Database::showFilmlist() {

    std::cout << "***** Film List *****\n";
    int gesamtDauer = 0;
    for (auto& mv : mediaList) {
        mv->showMediafiles();
        gesamtDauer += mv->getFilmduration();
    }
    std::cout << "\nGesamte Dauer aller Filme und Serien: " << gesamtDauer << "\n";
    pauseProgramm("Please press any key to continue\n");
}

void Database::watch() {
    std::cout << "Which movie/series (1 - " << mediaList.size() << ") do you want to watch?\n";
    int i;
    std::cin >> i;
    i--;
    if (i < (int)mediaList.size() && i >= 0) {
        mediaList.at(i)->playFile();
    }
    pauseProgramm("\nPlease press any key to continue\n");
}

void Database::addFile() {
    int input;
    std::cout << "Add (1) Movie or (2) Series?\nInput number: ";
    std::cin >> input;

    std::cout << "Titel: ";
    const std::string _titel = readString();
    const std::string _review = "";
    std::cout << "\nGenre: ";
    const std::string _genre = readString();

    int _duration, releaseYear;
    std::cout << "\nDuration: ";
    std::cin.clear();
    std::cin >> _duration;

    switch (input)
    {
    case 1:
    {
        std::cout << "Release Year: ";
        std::cin >> releaseYear;
        Movie* newMovie = new Movie(_titel, _review, _genre, _duration, releaseYear);
        mediaList.insert(mediaList.begin() + numOfMovies, newMovie); //inserted in the last movie list, not last vector index
        //mediaList.push_back(newMovie);
        numOfMovies++;
        break;
    }
    case 2:
    {
        int numOfEpisodes;
        std::cout << "Number of Episodes: ";
        std::cin >> numOfEpisodes;
        Serie* newSerie = new Serie(_titel, _review, _genre, _duration, numOfEpisodes);
        mediaList.push_back(newSerie);
        numOfSeries++;
        break;
    }
    default:
        std::cout << "Wrong input\n";
        break;
    }
    pauseProgramm("New file has been added. Please press any key to continue\n");
}

void Database::removeFilm() {
    std::cout << "Which index you want to delete?\n";
    int i;
    std::cin >> i;
    i--;
    if (i < mediaList.size() && i >= 0) {
        if (i < numOfMovies) 
            numOfMovies--;
        else
            numOfSeries--;
        
        delete mediaList.at(i);
        
        mediaList.erase(mediaList.begin() + i);
        pauseProgramm("File has been removed. Please press any key to continue");
    }
    else
    {
        pauseProgramm("Invalid number. Please press any key to continue");
    }

}

void Database::evaluateFilm() {
    std::cout << "Which Movie/Series do you want to evaluate?\nTitle: ";
    const std::string title = readString();

    for (auto& mv : mediaList) {
        if (mv->getTitel()._Equal(title)) {
            std::cout << "\nEvaluate " << mv->getTitel() << ": ";
            char c = _getch();
            _putch(c);
            mv->setEvaluation(c);
            pauseProgramm("Please press any key to continue");
            break;
        }
    }
}

void Database::compareFilms(Movie& comparedMovie)
{
    std::string movieInput;
    std::cout << "Input the to be compared movie title: ";
    movieInput = readString();
    bool isFound = false;
    
    Movie* movie = nullptr;
    for (int i = 0; i < numOfMovies; i++) {
        if (mediaList.at(i)->getTitel() == movieInput) {
            isFound = true;
            movie = (Movie*)mediaList.at(i);
        }
    }

    if (isFound) {
        std::cout << "\nComparing " << comparedMovie.getTitel() << " and " << movieInput << "\n";
        if (comparedMovie.getReleaseYear() < movie->getReleaseYear()) {
            std::cout << comparedMovie.getTitel() << " is older\n";
        }
        else {
            std::cout << movie->getTitel() << " is older\n";
        }
    }
    else{
        std::cout << "\n" << movieInput << " is not found in the Database\n";
    }

}

void Database::sortedList() {
    std::cout << "** Sorted Film List **\n";
    for (int i = 1; i < mediaList.size(); i++) {
        Mediafiles* movie = mediaList.at(i);
        int j = i - 1;

        while (j >= 0 && movie->getAverageReview() > mediaList.at(j)->getAverageReview())
        {
            mediaList.at(j + 1) = mediaList.at(j);
            j--;
        }
        mediaList.at(j + 1) = movie;
    }
    showFilmlist();
}
