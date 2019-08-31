/*
	CREATED BY: Jakub Kozupa
	DATE: 31.08.2019
	FEEL FREE TO USE
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>

bool fileExists(const std::string& filePath)
{
	std::ifstream f(filePath.c_str());
	return f.good();
}

int main()
{
	std::vector<std::string> file = { "AreAambienceData.txt", "AreaData.txt", "AreaProperty.txt" };
	std::vector<std::string> directories = { "00000", "00100", "00200", "00300", "00400", "00500", "00600", "00700", "00800", "00900" };

	bool endForDir      = false;
	int amountOfChanges = 0;
	int breakAmount     = 0;
	double difference;

	clock_t start, end;
	start = clock();

	for (int i = 0; i < directories.size(); i++)
	{
		//std::cout << "Petla glowna nr " + std::to_string(i) << std::endl;

		// FOR EVERY DIR (EX.: 000001, 000002, 000003 ... 002000, 002001, 002002 etc..)
		for (int j = 0; j < directories.size(); j++)
		{ 
			if (!endForDir) {
				//std::cout << "Petla wewnetrzna" << std::endl;
				std::string dir = directories[i] + std::to_string(j);
				for (int k = 0; k < file.size(); k++)
				{
					//std::cout << "Petla zmieniajaca nazwe" << std::endl;
					std::string path = dir + "\\" + file[k];
					std::string oryginalPath = path;

					std::transform(path.begin(), path.end(), path.begin(), ::tolower);

					if (fileExists(oryginalPath))
					{
						if (rename(oryginalPath.c_str(), path.c_str()) == 0)
							std::cout << "Zmieniono: " + path << std::endl;
						amountOfChanges += 1;
						breakAmount = 0;
					}
					else
					{
						//std::wcout << "BREAK!!" << std::endl;
						endForDir = true;
						breakAmount += 1;
						break;
					}
				}
			}
			else endForDir = false;
			if (breakAmount >= 3) break;
		}
		if (breakAmount >= 3) break;
	}

	end = clock();
	difference = (end-start)/(double)CLOCKS_PER_SEC;

	std::cout << std::endl << "---------------------------------" << std::endl;
	std::cout << "Lacznie zmieniono nazwe: " + std::to_string(amountOfChanges) + " plikow!" << std::endl;
	std::cout << "Czas wykonywania programu: " + std::to_string(difference) + " sekund." << std::endl;
	std::cout << "Program zakonczyl prace, wcisnij [ENTER] aby wyjsc." << std::endl;
	std::cin.get();

	return 0;
}

