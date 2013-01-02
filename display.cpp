#include "display.h"

void db_display(QueryResult *res)
{
	int cnt_row = res->result_count();
    int cnt_column = res->column_count();
	
    for(int i = 0; i < cnt_column; i ++)
    {
        const char *cname = res->column_name(i);
        int len_name = strlen(cname);
        printf("%s", cname);
        for(int j = len_name; j < NBLANK; j ++)
            putchar(' ');
    }
    putchar('\n');
    int ntmp;
    char ctmp[100];
    for(int i = 0; i < cnt_row; i ++)
    {
        res->next_row();
        for(int j = 0; j < cnt_column; j ++)
        {
        	void *ptr_data = res->get_data(j);
            int bk;
         	switch(res->column_type(j))
         	{
         		case DT_CHAR:
         			printf("%c ", *((char *)ptr_data));
         			for(bk = 1; bk < NBLANK; bk ++)
         				putchar(' ');
         			break;
         		case DT_INT:
         		case DT_LONG:
         			printf("%d ", *((int *)ptr_data));
         			snprintf(ctmp, sizeof(ctmp), "%d", *((int *)ptr_data));
         			for(bk = strlen(ctmp); bk < NBLANK; bk ++)
                        putchar(' ');
         			break;
         		case DT_FLOAT:
         			printf("%f ", *(float *)ptr_data);
         			snprintf(ctmp, sizeof(ctmp), "%f", (*((float *)ptr_data)));
         			for(bk = strlen(ctmp); bk < NBLANK; bk ++)
         				putchar(' ');
         			break;
         		case DT_DOUBLE:
         			printf("%lf ", *(double *)ptr_data);
         			snprintf(ctmp, sizeof(ctmp), "%d", (int)(*((double *)ptr_data)));
         			for(bk = strlen(ctmp); bk < NBLANK; bk ++)
                        putchar(' ');
         			break;
         		case DT_TEXT:
         			printf("%s ", (char *)ptr_data);
         			for(bk = strlen((char *)ptr_data); bk < NBLANK; bk ++)
                        putchar(' ');
         			break;
         		case DT_BOOL:
         			if(*(bool *)ptr_data)
         			{
         				printf("%s ", "True");
         				ntmp = 4;
         			}
         			else
         			{
         				printf("%s ", "False");
         				ntmp = 5;
         			}
         			for(bk = ntmp; bk < NBLANK; bk ++)
         				putchar(' ');
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
