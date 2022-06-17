// main.cpp
// Project UID db1f506d06d84ab787baf250c265e24e

#include <cassert>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <cmath>
#include "csvstream.h"
using namespace std;

class PiazzaBot {
private:
	double numPosts;
	double vocabSize;
	map<string, double> words;
	map<string, double> labels;
	map<pair<string, string>, double> finalMap; // For each label C and word W, 
											    // num posts with label C that contain W
public:
	PiazzaBot() {
		numPosts = 0;
		vocabSize = 0;
	}
	// R: file is valid
	// M: all private member variables of PiazzaBot
	// E: trains PiazzaBot using all smaller training functions
	bool Train(const string& str, bool wantDebug, bool isOpen) {
		if (!isOpen) {
			return true;
		}
		ifstream a;
		ifstream b;
		ifstream c;
		ifstream d;
		ifstream e;
		a.open(str);
		b.open(str);
		c.open(str);
		d.open(str);
		e.open(str);
		if (!(a.is_open() && b.is_open() && c.is_open()
			&& d.is_open() && e.is_open())) {
			return false;
		}
		csvstream trainPost(e);
		csvstream trainVocab(d);
		csvstream trainWords(c);
		csvstream trainLabels(b);
		csvstream trainfinalMap(a);
		post_train(trainPost, wantDebug);
		vocab_train(trainVocab, wantDebug);
		words_train(trainWords);
		labels_train(trainLabels, wantDebug);
		finalMap_train(trainfinalMap, wantDebug);		
		return true;
	}

	void Predict(csvstream& file) {
		map<string, string> row;
		int guesses = 0;
		int correctGuesses = 0;
		double max = 0;
		while (file >> row) {
			set<string> bagOfVocab = unique_words(row["content"]);
			map<double, string> Logs;
			vector<double> logVector;
			for (auto i = labels.begin(); i != labels.end(); ++i) {
				double logPerLabel = 0;
				for (auto j = bagOfVocab.begin(); j != bagOfVocab.end(); ++j) {
					logPerLabel = logPerLabel + calc_log_likelihood(i->first, *j);
				}
				logPerLabel = logPerLabel + calc_log_prior(i->first);
				if (Logs.find(logPerLabel) == Logs.end()) {
					pair<double, string> p1(logPerLabel, i->first);
					Logs.insert(p1);
				}
				logVector.push_back(logPerLabel);
			}			
			max = *max_element(logVector.begin(), logVector.end());
			string prediction = Logs[max];
			if (prediction == row["tag"]) {
				correctGuesses++;
			}
			guesses++;
			cout << "test data:\n";
			cout << "  correct = " << row["tag"] << ", predicted = "
				<< prediction << ", log-probability score = " << max << "\n";
			cout << "  content = " << row["content"] << "\n\n";
		}
		cout << "performance: " << correctGuesses << " / " << guesses
			<< " posts predicted correctly\n";
	}
	// R: str is valid
	// M: N/A
	// E: returns log prior
	double calc_log_prior(const string& str) {
		double numPostsC = labels[str];
		return log(numPostsC / numPosts);
	}
	// R: str and finder are valid
	// M: N/A
	// E: returns log likelihood in three scenarios
	double calc_log_likelihood(const string& str, const string& finder) {
		pair<string, string> p1(str, finder);
		double numPostsW = words[finder];
		double numPostsC = labels[str];
		double numPostsCW = finalMap[p1];
		if (words.find(finder) == words.end()) {
			return log(1 / numPosts);
		}
		if (finalMap.find(p1) == finalMap.end()) {
			return log(numPostsW / numPosts);
		}
		return log(numPostsCW / numPostsC);
	}

	set<string> unique_words(const string& str) {
		istringstream source(str);
		set<string> words;
		string word;
		// Read word by word from the stringstream and insert into the set
		while (source >> word) {
			words.insert(word);
		}
		return words;
	}
	// R: file is valid
	// M: numPosts
	// E: trains PiazzaBot on X amount of posts
	void post_train(csvstream& file, bool wantDebug) {
		if (wantDebug) {
			cout << "training data:" << endl;
		}
		map<string, string> debugRow;
		while (file >> debugRow) {
			if (wantDebug) {
				cout << "  label = " << debugRow["tag"] << ", content = "
					<< debugRow["content"] << "\n";
			}
			numPosts++;
		}
		cout << "trained on " << numPosts << " examples\n";
	}
	// R: file is valid
	// M: vocabSize
	// E: trains PiazzaBot on all unique vocab
	void vocab_train(csvstream& file, bool wantDebug) {
		map<string, string> debugRow;
		set<string> allVocabSet;
		string allVocab = "";
		while (file >> debugRow) {
			allVocab += " " + debugRow["content"];
		}
		allVocabSet = unique_words(allVocab);
		vocabSize = allVocabSet.size();
		if (wantDebug) {
			cout << "vocabulary size = " << vocabSize << "\n\n";
		}
	}
	// R: file is valid
	// M: words map
	// E: trains PiazzaBot on words, stores in a map
	void words_train(csvstream& file) {
		map<string, string> row;
		string allVocab = "";
		set<string> allVocabSet;
		while (file >> row) {
			allVocabSet = unique_words(row["content"]);
			for (auto i = allVocabSet.begin(); i != allVocabSet.end(); ++i) {
				if (words.find(*i) != words.end()) {
					words[*i] += 1;
				}
				else {
					pair<string, int> p1(*i, 1);
					words.insert(p1);
				}
			}
		}
	}
	// R: file is valid
	// M: labels map
	// E: trains PiazzaBot on labels, stores in a map
	void labels_train(csvstream& file, bool wantDebug) {
		map<string, string> debugRow;
		while (file >> debugRow) {
			if (labels.find(debugRow["tag"]) != labels.end()) {
				auto i = labels.find(debugRow["tag"]);
				i->second += 1;
			}
			else {
				pair<string, double> p1(debugRow["tag"], 1);
				labels.insert(p1);
			}
		}
		if (wantDebug) {
			cout << "classes:\n";
			for (auto i = labels.begin(); i != labels.end(); ++i) {
				cout << "  " << i->first << ", "
					 << i->second << " examples, log-prior = "
					 << calc_log_prior(i->first) << "\n";
			}
		}
	}
	// R: file is valid
	// M: labels map
	// E: trains PiazzaBot on labels, stores in a map
	void finalMap_train(csvstream& file, bool wantDebug) {
		map<string, string> debugRow;
		set<string> allVocabSet;
		while (file >> debugRow) {
			allVocabSet = unique_words(debugRow["content"]);
			for (auto i = allVocabSet.begin(); i != allVocabSet.end(); ++i) {
				pair<string, string> p1(debugRow["tag"], *i);
				if (finalMap.find(p1) != finalMap.end()) {
					finalMap.find(p1)->second += 1;
				}
				else if (finalMap.find(p1) == finalMap.end()) {
					pair<pair<string, string>, int> p2(p1, 1);
					finalMap.insert(p2);
				}
			}
		}
		if (wantDebug) {
			cout << "classifier parameters:\n";
			for (auto i = finalMap.begin(); i != finalMap.end(); ++i) {
				if (i->second != 0) {
					cout << "  " << i->first.first << ":"
						 << i->first.second << ", count = "
						 << i->second << ", log-likelihood = "
						 << calc_log_likelihood(i->first.first, i->first.second)
						 << "\n";
				}
			}
		}
	}
}; // End class PiazzaBot

void print_error() {
	cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
}

void file_error(string file) {
	cout << "Error opening file: " << file << endl;
}

int main(int argc, char** argv) {
	bool wantDebug, successTrain;
	ifstream file;
	cout.precision(3);
	string openString = argv[2];
	string trainingFile = argv[1];
	bool fileOpen = false;
	if (argc != 3 && argc != 4) {
		print_error();
		return 1;
	}
	if (argc == 4) {
		string DB = argv[3];
		if (DB != "--debug") {
			print_error();
			return 1;
		}
		else if (DB == "--debug") {
			wantDebug = true;
		}		
	}
	PiazzaBot PiazzaBot;
	file.open(openString);
	if (file.is_open()) {
		fileOpen = true;
	}
	if (!file.is_open()) {
		file_error(openString);
		return 1;
	}
	successTrain = PiazzaBot.Train(trainingFile, wantDebug, fileOpen);
	if (!successTrain) {
		file_error(trainingFile);
		return 1;
	}
	csvstream tester(file);
	PiazzaBot.Predict(tester);
	return 0;
} 