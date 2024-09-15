#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <list>
#include <map>
#include <unordered_map>
#include "NetflixDB.h"
#include <stdlib.h>


using namespace std;
string extractTextInQuotes(istringstream& ss) {
	string token;
	getline(ss, token, '"'); // Przeczytaj tekst od pocz¹tku cudzys³owu
	getline(ss, token, '"'); // Przeczytaj tekst do koñca cudzys³owu
	return token;
}



int main() {

	//menu();
	NetflixDb database;

	fstream DBinput("C:\\Users\\macie\\source\\repos\\31942107-gr03-repo\\Projekt\\Netflix\\Netflix\\netflixmoj.csv");
	if (DBinput.is_open()) {

		string line;

		getline(DBinput, line);
		
		

		while (getline(DBinput, line)) {
			
			istringstream ss(line);
			string token;

			string showId;
			string type, title, director, cast, country, dateAdded, rating, listedIn, description;
			int releaseYear;
			string duration;

			getline(ss, showId, ',');
			getline(ss, type, ',');
			
			title= extractTextInQuotes(ss);
			getline(ss, token, ',');

			getline(ss, director, ',');
			
			cast = extractTextInQuotes(ss);
			getline(ss, token, ',');

			getline(ss, country, ',');
			
			dateAdded = extractTextInQuotes(ss);
			getline(ss, token, ',');

			ss >> releaseYear;
			getline(ss, token, ',');
			
			rating = extractTextInQuotes(ss);
			getline(ss, token, ',');

			getline(ss, duration, ',');
			//ss >> duration;
			
			listedIn = extractTextInQuotes(ss);
			getline(ss, token, ',');

			description = extractTextInQuotes(ss);

			if (!showId.empty() && !type.empty() && !title.empty() && !director.empty() && !cast.empty() && !country.empty() && !dateAdded.empty() && releaseYear != 0 && !rating.empty() && !listedIn.empty() && !description.empty()) {
				Item newItem(showId, type, title, director, cast, country, dateAdded, releaseYear, rating, duration, listedIn, description);
				database.addShow(newItem);
			}else {
				cout << "\nInvalid data, skipping line.";
			}
					 			
		}
		DBinput.close();
	}
	else {
		cout << "Unable to open the CSV file.\n";
		return 1;
	}

	database.displayAllShows();

	database.menu();


	return 0;
}


