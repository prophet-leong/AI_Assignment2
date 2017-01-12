#include "FileInit.h"

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}
void FileReader::ReadFile(vector<Enemy*>enemy, vector<Character*>ally, string fileNmae)
{
	std::ifstream file;
	file.open(fileNmae);
	string line;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{

		}
	}
}