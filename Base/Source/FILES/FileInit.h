#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "Berserker.h"
#include "Knight.h"
#include "Archer.h"
#include "Mage.h"
#include "Ally.h"
using std::string;
using std::vector;
class FileReader
{
public:
	FileReader();
	~FileReader();
	void ReadFile(vector<Enemy*>enemy,vector<Character*>ally,string fileNmae);
private:

};

