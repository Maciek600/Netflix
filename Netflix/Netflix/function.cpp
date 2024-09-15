#include "NetflixDB.h"

void NetflixDb::displayCountryWithMostShows() {
	map<string, int> countryCount;
	for (const auto& show : database) {
		countryCount[show.getCountry()]++;
	}

	// Find the country with the most shows
	string mostShowsCountry;
	int maxShows = 0;
	for (const auto& entry : countryCount) {
		if (entry.second > maxShows) {
			maxShows = entry.second;
			mostShowsCountry = entry.first;
		}
	}

	// Display the result
	cout << "Country with the most shows: " << mostShowsCountry << " (" << maxShows << " shows)\n";
}

void NetflixDb::sortAndDisplayShowsByDateAdded() {
	// Sort shows based on the date_added in the existing database list
	list<Item>databasecopy = database; //kopia bazy
	databasecopy.sort([](const Item& a, const Item& b) {
		return a.getDate() < b.getDate();
		});

	// wyswietlamy posortowane
	for (const auto& show : databasecopy) {
		cout << "Title: " << show.getTitle() << "\n";
		cout << "Type: " << show.getType() << "\n";
		cout << "Director: " << show.getDirector() << "\n";
		cout << "Cast:" << show.getCast() << "\n";
		cout << "Country:" << show.getCountry() << "\n";
		cout << "Date added:" << show.getDate() << "\n";
		cout << "Released year: " << show.getYear() << "\n";
		cout << "Rating: " << show.getRating() << "\n";
		cout << "Duration: " << show.getDuration() << "\n";
		cout << "Listed in: " << show.getListed() << "\n";
		cout << "Description: " << show.getDescritpion() << "\n";
		cout << "\n";
	}
}

void NetflixDb::displayReleaseNetflixDifference() {
	
		for (const auto& show : database) {
		
			// odcinamy rok od daty
			int addedYear = stoi(show.getDate().substr(show.getDate().size() - 4));

			// roznica
			int difference = addedYear - show.getYear();

			// wyswietl info o filmie
			cout << "Title: " << show.getTitle() << "\n";
			cout << "Type: " << show.getType() << "\n";
			cout << "Director: " << show.getDirector() << "\n";
			cout << "Country:" << show.getCountry() << "\n";
			cout << "Date added:" << show.getDate() << "\n";
			cout << "Released year: " << show.getYear() << "\n";

			// wyswietl roznice
			cout << "\nRelease-Netflix Difference: " << difference << " years\n";
			cout << "\n";
		}
	
}

void NetflixDb::displayAverageDurationByCountry() {
	// Mapa do przechowywania krajow i czasu trwania
	unordered_map<string, pair<int, int>> countryDurationCount; //std::pair is a class template that provides a way 
	//to store two heterogeneous objects as a single unit. A pair is a specific case of a std::tuple with two elements.

	// Przechodzimy przez baze i dodajemy do krajow kolejne minuty
	for (const auto& show : database) {
		/*countryDurationCount[show.getCountry()].first += show.getDuration();
		countryDurationCount[show.getCountry()].second++;*/
		if (show.getType() == "Movie") {
			// Parsowanie czasu trwania (usuniêcie ostatnich 4 znaków, czyli " min")
			int duration = stoi(show.getDuration().substr(0, show.getDuration().size() - 4));
			countryDurationCount[show.getCountry()].first += duration;
			countryDurationCount[show.getCountry()].second++;
		}
	}

	// wyswietl sredni czas
	for (const auto& entry : countryDurationCount) {
		const string& country = entry.first;
		int totalDuration = entry.second.first;
		int showCount = entry.second.second;

		// nie dziel przez zero
		if (showCount > 0) {
			double averageDuration = static_cast<double>(totalDuration) / showCount;
			cout << "Country: " << country << "\n";
			cout << "Average Duration: " << averageDuration << " minutes\n";
			cout << "Number of Shows: " << showCount << "\n\n";
		}
	}
}

void NetflixDb::addShow(const Item& show) {
	database.push_back(show);
}

void NetflixDb::addNew() {
	string typeN,titleN,directorN,castN,countryN,date_addedN,ratingN,listed_inN,descriptionN;
	int release_yearN;
	string durationN;


	cout << "Aby dodac nowa pazycje do bazy podaj nastepujace informacje: " << endl;
	cout << "Type: " << endl;
	cin >> typeN;
	cout << "Title: " << endl;
	cin >> titleN;
	cout << "Director: " << endl;
	cin >> directorN;
	cout << "Cast: " << endl;
	cin >> castN;
	cout << "Country: " << endl;
	cin >> countryN;
	cout << "Data added: " << endl;
	cin >> date_addedN;
	cout << "Release year: " << endl;
	cin >> release_yearN;
	cout << "Rating: " << endl;
	cin >> ratingN;
	cout << "Duration [min]: " << endl;
	cin >> durationN;
	cout << "Listed in: " << endl;
	cin >> listed_inN;
	cout << "Description: " << endl;
	cin >> descriptionN;

	int newId = 1;
	string NewId;
	if (!database.empty()) {
		string newIdA = database.back().getShowId();
		newIdA = newIdA.substr(1);
		newId = stoi(newIdA) + 1;
		NewId = "s" + to_string(newId);
	}
	Item NewItem(NewId, typeN, titleN, directorN, castN, countryN, date_addedN, release_yearN, ratingN, durationN, listed_inN, descriptionN);
	addShow(NewItem);


}

void NetflixDb::removeShow() {
	string showId;
	cout << "Podaj numer id do usuniecia (poprawny zapis: s<numer>) : " << endl;
	cin >> showId;
	database.remove_if([showId](const Item& s) { return s.getShowId() == showId; });
	cout << "Movie/ TV series about ID: " << showId << " has been removed from database." << endl;
}

void NetflixDb::generateReport(const string& filename) {
	string filenameTXT = filename + ".txt";
	string filenameCSV = filename + ".csv";
	ofstream outfile(filenameTXT);
	if (outfile.is_open()) {
		
		

		for (const auto& show : database) {
			outfile << "Title: " << show.getTitle() << "\n";
			outfile << "Type: " << show.getType() << "\n";
			outfile << "Director: " << show.getDirector() << "\n";
			outfile << "Cast:" << show.getCast() << "\n";
			outfile << "Country:" << show.getCountry() << "\n";
			outfile << "Date added:" << show.getDate() << "\n";
			outfile << "Released year: " << show.getYear() << "\n";
			outfile << "Rating: " << show.getRating() << "\n";
			outfile << "Duration: " << show.getDuration() << "\n";
			outfile << "Listed in: " << show.getListed() << "\n";
			outfile << "Description: " << show.getDescritpion() << "\n";
			outfile << "\n";
		}
		outfile.close();
		cout << setw(35);
		cout << "Report generated successfully.\n";
	}
	else {
		cout << setw(35);
		cout << "Unable to open the file.\n";
	}


	ofstream outfile1(filenameCSV);

	if (outfile1.is_open()) {
		// Nag³ówki w pliku CSV
		outfile1 << "Type,Title,Director,Cast,Country,Date added,Released year,Rating,Duration,Listed in,Description\n";
		char ch{'"'};
		for (const auto& show : database) {
			// Zapisujemy ka¿de pole oddzielone przecinkiem
			outfile1 << show.getShowId() << "," << show.getType() << ","
				<< ch << show.getTitle() << ch << ","
				<< show.getDirector() << ","
				<< ch << show.getCast() << ch << ","
				<< show.getCountry() << ","
				<< ch << show.getDate() << ch << ","
				<< show.getYear() << ","
				<< ch << show.getRating() << ch << ","
				<< show.getDuration() << ","
				<< ch << show.getListed() << ch << ","
				<< ch << show.getDescritpion() << ch << "\n";
		}

		outfile1.close();
		cout << setw(35);
		cout << "CSV Report generated successfully.\n";
	}
	else {
		cout << setw(35);
		cout << "Unable to open the file.\n";
	}
}

void NetflixDb::menu() {
	int menu;
	do {
		cout << "_____________________________________________________________" << endl;
		cout << setw(35);
		cout << "Netflix" << endl;
		cout << "_____________________________________________________________" << endl;

		cout << "\nWitamy w bazie filmow Netflix! Wybierz interesujaca cie opcje: " << endl;
		cout <<"1. Wyswietl kraj, z ktorego pochodzilo najwiecej filmow / show" << endl;
		cout << "2. Posortuj i wyswietl filmy/ programy wg dat ich dodania do Netflixa" << endl;
		cout << "3. Oblicz roznice pomiedzy data premiery filmu a udostepnieniem na Netlix" << endl;
		cout << "4. Oblicz sredni czas trwania filmu / show dla poszczegolnych krajow" << endl;
		cout << "5. Dodaj utwor do bazy" << endl; 
		cout << "6. Usun utwor z bazy" << endl;
		cout << "7. Generuj raport" << endl;
		cout << "8. Wyswietl wszystkie pozycje bazy" << endl;
		cout << "0. Zakoncz program." << endl;
		cout << "_____________________________________________________________" << endl;


		cin >> menu;

		switch (menu)
		{
		case 1:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "1. Wyswietl kraj, z ktorego pochodzilo najwiecej filmow / show" << endl;
			displayCountryWithMostShows();
			break;
		case 2:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "2. Posortuj i wyswietl filmy/ programy wg dat ich dodania do Netflixa" << endl;
			sortAndDisplayShowsByDateAdded();
			break;
		case 3:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "3. Oblicz roznice pomiedzy data premiery filmu a udostepnieniem na Netlix" << endl;
			displayReleaseNetflixDifference();
			break;
		case 4:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "4. Oblicz sredni czas trwania filmu / show dla poszczegolnych krajow" << endl;
			displayAverageDurationByCountry();
			break;
		case 5:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "5. Dodaj utwor do bazy" << endl;
			addNew();
			break;
		case 6:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "6. Usun utwor z bazy" << endl;
			removeShow();
			break;
		case 7:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "7. Generuj raport" << endl;
			generateReport("raport");
			break;
		case 8:
			system("CLS");
			cout << "_____________________________________________________________" << endl;
			cout << "8. Wyswietl wszystkie pozycje" << endl;
			displayAllShows();
		default:
			cout << "\nPodales liczbe ktora nie wystepuje w tym menu. Prosze, sprobuj jeszcze raz" << endl;
		}
	} while (menu != 0);
}

void NetflixDb::displayAllShows() {
	for (const auto& show : database) {
		cout << "\nId:  " << show.getShowId() << "\n";
		cout << "Title: " << show.getTitle() << "\n";
		cout << "Type: " << show.getType() << "\n";
		cout << "Director: " << show.getDirector() << "\n";
		cout << "Cast:" << show.getCast() << "\n";
		cout << "Country:" << show.getCountry() << "\n";
		cout << "Date added:" << show.getDate() << "\n";
		cout << "Released year: " << show.getYear() << "\n";
		cout << "Rating: " << show.getRating() << "\n";
		cout << "Duration: " << show.getDuration() << "\n";
		cout << "Listed in: " << show.getListed() << "\n";
		cout << "Description: " << show.getDescritpion() << "\n";
		cout << "\n";
	}
}