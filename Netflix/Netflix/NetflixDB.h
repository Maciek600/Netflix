#pragma once
#define Netflix_DB_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <list>
#include <map>
#include <unordered_map>
#include <iomanip> 
#include <stdlib.h>
using namespace std;

class Item { //item jako pozycja w bazie
private:
	string show_id;
	string type;  // np. film, program, serial
	string title;
	string director;
	string cast;
	string country;
	string date_added; // Zak³adaj¹c format YYYY-MM-DD
	int release_year;
	string rating; // np. PG-13
	string duration; // np. 90 min
	string listed_in;
	string description;
public:
	Item(string id, const string& t, const string& tt, const string& d, const string& c, const string& co,
		const string& da, int ry, const string& r, string dur, const string& li, const string& desc)
		: show_id(id), type(t), title(tt), director(d), cast(c), country(co), date_added(da),
		release_year(ry), rating(r), duration(dur), listed_in(li), description(desc) {}


	string getShowId() const { return show_id; }
	string getType() const { return type; }
	string getTitle() const { return title; }
	string getDirector() const { return director; }
	string getCast() const { return cast; }
	string getCountry() const { return country; }
	string getDate() const { return date_added; } //tu musi byæ chyba date
	int getYear() const { return release_year; }
	string getRating() const { return rating; }
	string getDuration() const { return duration; }
	string getListed() const { return listed_in; }
	string getDescritpion() const { return description; }
};

class NetflixDb {
private:
	list<Item> database;

public:
	void displayCountryWithMostShows();
	void sortAndDisplayShowsByDateAdded();
	void displayReleaseNetflixDifference();
	void displayAverageDurationByCountry();
	void addShow(const Item& show);
	void addNew();
	void removeShow();
	void generateReport(const string& filename);
	void menu();
	void displayAllShows();
};