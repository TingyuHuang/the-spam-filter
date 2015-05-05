#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

int main(int argc, char *argv[])
{
	std::list<std::string> tokenList;

	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
	}

	if (2 == argc) {
		std::fstream file(argv[1], std::fstream::in);

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

			// find space
			if(result.find_first_not_of(' ') != std::string::npos) {
				std::cout << result << ' ';
				tokenList.push_back(result);
			}
		}


		file.close();
	}

	
}
