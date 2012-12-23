#ifndef __TABLE__
#define __TABLE__

#include <string>

class Table
{
private:
    std::string tbl_name;
public:
    Table(const char *);
    void drop();
    ~Table();
};
#endif