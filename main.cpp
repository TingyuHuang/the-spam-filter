#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>

namespace quiz {
typedef std::vector<std::string> list;
typedef std::map<std::string, int> hash;
}

int biGram(const quiz::list &list, const size_t n = 2)
{
	quiz::hash map;
	double score = 1.0;
	double k = 0;

	for (size_t i = 0; i < list.size() - n + 1; i++) {
		std::string gram;

		for (size_t j = 0; j < n; j++) {
			gram += list[i+j] + ',';
		}

		if (map.end() == map.find(gram)) {
			map[gram] = 1;
		} else {
			map[gram] += 1;
		}

		k += 1;
	}

	for (quiz::hash::iterator it=map.begin(); it!=map.end(); ++it) {
		for (int i = 0; i < it->second; i++) {
			score *= it->second;
		}
	}

	std::cout << std::fixed << std::setprecision(5)
			  << "P = " << pow(score, 1 / k) << std::endl
			  << "k = " << k << std::endl;

	return 0;
}

int parseFile(const char *filename, quiz::list &list)
{
	std::fstream file(filename, std::fstream::in);

	if (NULL == filename) {
		std::cerr << "Filename should not be NULL." << std::endl;
		return -1;
	}

	if (not file.is_open()) {
		std::cerr << "Bad file: " << filename << std::endl;
		return -1;
	}

	while (!file.eof()) {
		std::string token, result;

		file >> token;

		// Remove punctuations
		std::remove_copy_if(token.begin(), token.end(),
							std::back_inserter(result),
							std::ptr_fun<int, int>(&std::ispunct)
							);

		// to lower-case
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);

		// filter space
		if(result.find_first_not_of(' ') != std::string::npos) {
			list.push_back(result);
		}
	}

	file.close();

	return 0;
}


int main(int argc, char *argv[])
{
	quiz::list list;

	if (2 != argc) {
		std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
		return -1;
	}

	if (0 < parseFile(argv[1], list)) {
		return -1;
	}

	biGram(list);

	return 0;
}
