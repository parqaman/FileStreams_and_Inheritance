#include "Movie.h"

Movie::Movie(std::string _titel, std::string _evaluation, std::string _genre, int _duration, int _releaseYear)
	:
	Mediafiles(_titel, _evaluation, _genre, _duration),
	releaseYear(_releaseYear)
{
}

int Movie::getReleaseYear() const
{
	return releaseYear;
}

void Movie::showMediafiles()const {
    std::string review;
    for (int i = 0; i < getEvaluation().size(); i++)
    {
        review.push_back(getEvaluation()[i]);
        review += ' ';
    }
    std::cout << "Title: " << getTitel() << ", Duration: " << getFilmduration() << ", Evaluation: " << review
        << ", Average: " << getAverageReview() << ", Genre: " << getGenre() << ", Release Year: " << releaseYear << "\n";
}