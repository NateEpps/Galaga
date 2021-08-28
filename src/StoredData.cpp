//
// StoredData.cpp
// Nathanael Epps
//

#include "StoredData.hpp"

#include <fstream>
#include <memory>

#include <Config.hpp>
#include "Util.hpp"

static int instances = 0;
static std::string filename = CMAKE_BINARY_DIR + "/galaga.data";

static unsigned highScore;

StoredData::StoredData()
{
    Print("Opening ", filename);
    Print("sizeof(unsigned) = ", sizeof(unsigned), " bytes");
    
    instances++;
    if (instances > 1)
        throw MakeException("StoredData: multiple objects");
    
    std::ifstream test(filename);
    // stackoverflow says this is the best way to check existence?
    if (test.good()) {
        Print("Using file");
        std::fstream file;
        file.open(filename, std::ios::in | std::ios::binary);
        
        file.read(reinterpret_cast<char*>(&highScore), sizeof(unsigned));
        file.close();
    }
    else {
        Print("NOT using file");
        highScore = 0;
    }
}

StoredData::~StoredData()
{
    Print("Writing to ", filename);
    
    instances--;
    // can't throw exceptions, sooooo
    if (instances < 0)
        Error("Error: instances < 0 (still attempting to serialize)");
    
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);
        
    file.write(reinterpret_cast<const char*>(&highScore), sizeof(unsigned));
    file.close();
}

void StoredData::setHighScore(unsigned int hs)
{
    highScore = hs;
}

unsigned StoredData::getHighScore()
{
    return highScore;
}
