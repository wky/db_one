#include "types.h"

static char types[][10] = {"Unknown", "Char", "Int", "Long", "Float", "Double", "Text", "Bool"};

const char *GET_TYPE_NAME(int t){
    switch (t & ~NEED_FREE_MASK){
        case DT_CHAR:       return types[1];
        case DT_INT:        return types[2];
        case DT_LONG:       return types[3];
        case DT_FLOAT:      return types[4];
        case DT_DOUBLE:     return types[5];
        case DT_TEXT:       return types[6];
        case DT_BOOL:       return types[7];
        default:            return types[0];
    }
}