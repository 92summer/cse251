#include "display.h"

void print_opt()
{
    printf("Please select an option:");
}

void print_menu()
{
    printf("1 - Insert a new event\n");
    printf("2 - Display all events\n");
    printf("3 - Now?\n");
    printf("4 - Delete expired\n");
    printf("0 - Exit\n");
    
}

time_t InputDate(char *prompt)
{
    char buffer[100];
    char *result;
    struct tm date;

    do
    {
        printf("%s", prompt);

        /* Get a line of up to 100 characters */
        fgets(buffer, sizeof(buffer), stdin);

        /* Remove any \n we may have input */
        if(strlen(buffer) > 0)
            buffer[strlen(buffer)-1] = '\0';

        result = strptime(buffer, "%m/%d/%Y", &date);

    } while(result == NULL);

    /* Convert to time_t format */
    date.tm_min = 0;
    date.tm_hour = 0;
    date.tm_sec = 0;
    date.tm_isdst = 1;

    return mktime(&date);
}

time_t InputTime(char *prompt, time_t date)
{
    char buffer[100];
    char *result;
    struct tm time ;

    time = *localtime(&date);

    do
    {
        printf("%s", prompt);

        /* Get a line of up to 100 characters */
        fgets(buffer, sizeof(buffer), stdin);

        /* Remove any \n we may have input */
        if(strlen(buffer) > 0)
            buffer[strlen(buffer)-1] = '\0';

        result = strptime(buffer, "%I:%M%p", &time);

    } while(result == NULL);

    return mktime(&time);
}

void InputEventName(char *prompt, char *n)
{

    printf("%s", prompt);

    /* Get a line of up to 50 characters */
    fgets(n, EVENT_NAME_SIZE, stdin);

    /* Remove any \n we may have input */
    char *sn = n;
    for (int i = 0; i < 50; i++)
    {
        if (*sn == '\n')
        {
            *sn = '\0';
            break;
        }  
        sn++;
    } 
}

void new_event(Event* eve,int *event_volume)
{
    if(*event_volume >= EVENT_MAX)
    {
        printf("Event full!\n");
        return;
    }

    //
    InputEventName("What is the event:", eve[*event_volume].name);

    //  
    eve[*event_volume].date = InputDate("Event date:");

    // 
    eve[*event_volume].starttime = InputTime("Start time:",eve[*event_volume].date);

    //
    eve[*event_volume].endtime = InputTime("End time:",eve[*event_volume].date);
  
    /*判断事件是否冲突*/
    Event *pE = eve;
    while (pE->starttime)
    {
        
        if (pE->endtime < eve[*event_volume].endtime && pE->endtime > eve[*event_volume].starttime)
        {
            printf("\nWarning, this event overlaps: \n");
            print_event(pE);
        }
        else if (pE->starttime > eve[*event_volume].starttime && pE->starttime < eve[*event_volume].endtime) 
        {
            printf("\nWarning, this event overlaps: \n");
            print_event(pE);
        }
        else if (pE->endtime > eve[*event_volume].endtime && pE->starttime < eve[*event_volume].starttime)
        {
            printf("Warning, this event overlaps: \n");
            print_event(pE);
        }
        else ;
        pE++;
    }
    

    (*event_volume)++;
}

void print_event(Event* eve)
{
    /*测试输入*/
    /*
    printf("%s",ctime(&eve[event_].starttime));
    printf("%s\n",eve[event_].name);
    printf("%s",ctime(&eve[event_].endtime));
    */
    
    struct tm startTM;
    //starttime
    startTM = *localtime(&eve->starttime);
    //月/日/年
    printf("%d/%d/%d\t", startTM.tm_mon + 1, startTM.tm_mday, startTM.tm_year + 1900);
    //12小时格式
    if (startTM.tm_hour <= 12)
    {
        printf("%d:%d%dAM\t",startTM.tm_hour, startTM.tm_min/10, startTM.tm_min%10);
    }
    else
    {
        printf("%d:%d%dPM\t",startTM.tm_hour - 12, startTM.tm_min/10, startTM.tm_min%10);
    }
    //endtime
    startTM = *localtime(&eve->endtime);
    //12小时格式
    if (startTM.tm_hour <= 12)
    {
        printf("%d:%d%dAM\t",startTM.tm_hour, startTM.tm_min/10, startTM.tm_min%10);
    }
    else
    {
        printf("%d:%d%dPM\t",startTM.tm_hour - 12, startTM.tm_min/10, startTM.tm_min%10);
    }

    //事件名字
    printf("%s\n", eve->name);
    
}

void display_all_event(Event* eve, int event_)
{
    /*无序输出*/
    
    Event* pE = eve;
    printf("\nSchedule:\n");
    while (pE->starttime)
    {
        print_event(pE);
        pE++;
    }
    

    /*按时间顺序*/
    /*/*/
    
     
}
void print_now_event(Event *eve)
{
    Event *pE = eve;
    time_t now;
	now = time(&now);
    
    while (pE->starttime)
    {
            if (now > pE->starttime && now < pE->endtime)
        {
            printf("Currently active events:\n");
            print_event(pE);
        }
        pE++;
    }
   
}

/********//*待完成*/
void Delete_expired(Event *eve)
{
    time_t now;
	now = time(&now);//获取当前时间
    
    //数组删除
    printf("Deleting:\n");
    while (eve->starttime)
    {
        if (now > eve->endtime)
        {
            
            print_event(eve);

            int count = 0;
            Event *pE = eve+1;
            while (pE->starttime)
            {
                count ++;//计数剩余事件
                pE++;
            }
            pE = eve +1;
            for (int j = 0; j < count; j++)
            {
                eve[j] = *pE;
                pE++;
            }
            pE->date = pE->endtime = pE->name[0] =pE->starttime = 0;
        }
        
        eve++;
    }

}