#include "table.h"
Table::Table(const char *name, Database *db, 
    std::vector<std::pair<int, std::string> >& cols, std::map<int, void*>& defs)
{
    tbl_name = name;
    assoc_db = db;
    dbms = db->db_one();
    
    std::map<int, void*>::iterator it;
    for (int c = 0; c < cols.size(); c++){
        printf("Column #%d (%s): data type %s", c, cols[c].second.c_str(), GET_TYPE_NAME(cols[c].first & ~NEED_FREE_MASK));
        it = defs.find(c);
        if (it != defs.end()){
            printf(" with default value ");
            switch (cols[c].first & ~NEED_FREE_MASK){
                case DT_CHAR:   printf("\'%c\'", *(char*)((*it).second)); break;
                case DT_INT:    printf("%d", *(int*)((*it).second)); break;
                case DT_LONG:   printf("%ld", *(long*)((*it).second)); break;
                case DT_FLOAT:  printf("%f", *(float*)((*it).second)); break;
                case DT_DOUBLE: printf("%lf", *(double*)((*it).second)); break;
                case DT_TEXT:   printf("\"%s\"", (char*)((*it).second)); break;
                case DT_BOOL:   printf("%s", (*(bool*)((*it).second))?"true(bool)":"false()bool"); break;
                default:
                    printf("bad value.");
                    break;
            }
        }
        putchar('\n');
    }
}
Table::~Table(){

}
void Table::drop(){

}