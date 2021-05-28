#pragma once
#include "pch.h"

typedef struct Stats
{
	string username;
	int gamesPlayed;
	int totalAnswers;
	int rightAnswers;
	float totalAnswerTime;
	int bestScore;
} Stats;

typedef struct Question
{
	int id;
	string question;
	string rightAnswer;
	string wrongAnswers[3];
} Question;