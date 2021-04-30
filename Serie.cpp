#include "Serie.h"

Serie::Serie(std::string _title, std::string _evaluation, std::string _genre, int _duration, int _numbersOfEpisodes)
	:
	numbersOfEpisodes(_numbersOfEpisodes),
	listOfEpisodes(new int[numbersOfEpisodes]), //array of watchEpisode
	Mediafiles(_title, _evaluation, _genre, _duration) //_duration is average playbacktime of the series
{
	for (int i = 0; i < numbersOfEpisodes; i++) {
		*listOfEpisodes = i + 1;
		listOfEpisodes++;
	}
	watchEpisode = listOfEpisodes - numbersOfEpisodes;
}

void Serie::playFile()
{
	watchEpisode++;
	std::cout << "Currently playing: " << *watchEpisode << ". Episode.\n";
	if (*watchEpisode == numbersOfEpisodes) { //if all episodes are watched, back to first episode 
		watchEpisode -= numbersOfEpisodes;
	}
}

void Serie::showMediafiles() const
{
	std::string review;
	for (int i = 0; i < getEvaluation().size(); i++)
	{
		review.push_back(getEvaluation()[i]);
		review += ' ';
	}
	std::cout << "Title: " << getTitel() << ", Duration: " << getFilmduration() << ", Evaluation: " << review
		<< ", Average: " << getAverageReview() << ", Genre: " << getGenre() << ", Number of Episodes: " << numbersOfEpisodes << "\n";
}

int Serie::getNumOfEpisodes() const
{
	return numbersOfEpisodes;
}

int Serie::getWatchEpisode() const
{
	return *watchEpisode;
}

void Serie::setWatchEpisode(int lastWatched)
{
	watchEpisode = listOfEpisodes - numbersOfEpisodes + lastWatched - 1; //-1 because the last watched episode, not next episode
}

