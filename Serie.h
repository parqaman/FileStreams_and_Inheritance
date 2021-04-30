#pragma once
#include<iostream>
#include <string>
#include "Mediafiles.h"
class Serie : public Mediafiles
{
public:
	Serie(std::string _title, std::string _evaluation, std::string _genre, int _duration, int _numbersOfEpisode);
	void playFile();
	void showMediafiles()const;
	int getNumOfEpisodes() const;
	int getWatchEpisode() const;
	void setWatchEpisode(int lastWatched);

private:
	int numbersOfEpisodes;
	int* watchEpisode = nullptr;
	int* listOfEpisodes = nullptr;
};