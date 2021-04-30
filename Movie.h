#pragma once
#include <iostream>
#include "Mediafiles.h"
class Movie : public Mediafiles
{
public:
	Movie(std::string _titel, std::string _evaluation, std::string _genre, int _duration, int _releaseYear);
	void showMediafiles()const;
	int getReleaseYear() const;

private:
	int releaseYear;
};

