#include "Mediafiles.h"

Mediafiles::Mediafiles(std::string _titel, std::string _evaluation, std::string _genre, int _duration)
    :
    titel(_titel),
    evaluation(_evaluation),
    genre(_genre),
    duration(_duration)
{
    averageReview = calculateAverageReview(evaluation);
}
float Mediafiles::calculateAverageReview(std::string string)
{
    if (evaluation.empty()) {
        return 0;
    }
    float average = 0;
    for (int i = 0; i < string.size(); i++)
    {
        average += (float)string.at(i) - '0';
    }
    return average /= string.size();
}
void Mediafiles::setEvaluation(char c)
{
    if (c - '0' >= 1 && c - '0' <= 9) {
        evaluation += c;
        pauseProgramm("\nFile has been evaluated.\n");
        averageReview = calculateAverageReview(evaluation);
    }
    else {
        pauseProgramm("\nWrong input\n");
    }
}
std::string Mediafiles::getEvaluation() const
{
    return evaluation;
}
int Mediafiles::getFilmduration()const {
    return duration;
}
std::string Mediafiles::getGenre() const {
    return genre;
}

std::string Mediafiles::getReview() const {
    return evaluation;
}
std::string Mediafiles::getTitel() const {
    return titel;
}

void Mediafiles::showMediafiles()const {
    std::string review;
    for (int i = 0; i < evaluation.size(); i++)
    {
        review.push_back(evaluation[i]);
        review += ' ';
    }
    std::cout << "Title: " << titel << " ,Duration: " << duration << " ,Evaluation: " << review << ", Average: " << averageReview << " ,Genre: " << genre << "\n";
}

float Mediafiles::getAverageReview() const
{
    return averageReview;
}

void Mediafiles::playFile()
{
    std::cout << "Now playing: " << titel;
}

void Mediafiles::pauseProgramm(const char* string)const
{
    std::cout << string;
    while (!_kbhit());
    system("cls");
}

