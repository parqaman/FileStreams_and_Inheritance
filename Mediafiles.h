#pragma once
#include <iostream>
#include <string>
#include <conio.h>

class Mediafiles {
public:
    Mediafiles(std::string _titel, std::string _evaluation, std::string _genre, int _duration);
    virtual void showMediafiles()const; //virtual because derived classes has the same function but a few specific features
    float calculateAverageReview(std::string review);
    void setEvaluation(char c);
    std::string getEvaluation() const;
    int getFilmduration()const;
    std::string getTitel()const;
    std::string getReview()const;
    std::string getGenre()const;
    float getAverageReview()const;
    virtual void playFile();
    

private:
    void pauseProgramm(const char*)const;

private:
    std::string titel;
    std::string evaluation;
    std::string genre;
    int duration;
    float averageReview;


};

