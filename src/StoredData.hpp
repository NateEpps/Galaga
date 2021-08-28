//
// StoredData.hpp
// Nathanael Epps
//

#ifndef STORED_DATA_HPP
#define STORED_DATA_HPP

class StoredData
{
public:
    StoredData();
    ~StoredData();
    
    static void setHighScore(unsigned);
    static unsigned getHighScore();
};

#endif
