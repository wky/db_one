#include "display.h"
#include <stdlib.h>
#include <cstdlib>
void db_display(QueryResult *res)
{
	int cnt_row = res->result_count();
    int cnt_column = res->column_count();
	
    for(int i = 0; i < cnt_column; i ++)
    {
        const char *cname = res->column_name(i);
        int len_name = strlen(cname);
        printf("%s", cname);
        for(int j = 0; j < NBLANK-len_name; j ++)
        printf(" ");
    }
    printf("\n");

    int ntmp;
    char ctmp[100];
    for(int i = 0; i < cnt_row; i ++)
    {
        res->next_row();
        for(int j = 0; j < cnt_column; j ++)
        {
        	void *ptr_data = res->get_data(j);
         	switch(res->column_type(j))
         	{
         		case DT_CHAR:
         			printf("%c", *((char *)ptr_data));
         			for(int bk = 0; bk < NBLANK-1; bk ++)
         				printf(" ");
         			break;
         		case DT_INT:
         		case DT_LONG:
         			printf("%d\n", *((int *)ptr_data));
         			snprintf(ctmp, sizeof(ctmp), "%d", *((int *)ptr_data));
         			for(int bk = 0; bk < NBLANK-strlen(ctmp); bk ++)
         				printf(" ");
         			break;
         		case DT_FLOAT:
         			printf("%.2f\n", *(float *)ptr_data);
         			snprintf(ctmp, sizeof(ctmp), "%d", (int)(*((float *)ptr_data)));
         			for(int bk = 0; bk < NBLANK-2-strlen(ctmp); bk ++)
         				printf(" ");
         			break;
         		case DT_DOUBLE:
         			printf("%.2lf\n", *(double *)ptr_data);
         			snprintf(ctmp, sizeof(ctmp), "%d", (int)(*((double *)ptr_data)));
         			for(int bk = 0; bk < NBLANK-2-strlen(ctmp); bk ++)
         				printf(" ");
         			break;
         		case DT_TEXT:
         			printf("%s", (char *)ptr_data);
         			for(int bk = 0; bk < NBLANK-strlen((char *)ptr_data); bk ++)
         				printf(" ");
         			break;
         		case DT_BOOL:
         			if(*(bool *)ptr_data)
         			{
         				printf("%s", "True");
         				ntmp = 4;
         			}
         			else
         			{
         				printf("%s\n", "False");
         				ntmp = 5;
         			}
         			for(int bk = 0; bk < NBLANK-ntmp; bk ++)
         				printf(" ");
         			break;
         		default:
         			break;

         	}       
        }
        printf("\n");
    }
    //printf("Display End!\n");
    return ;
}
