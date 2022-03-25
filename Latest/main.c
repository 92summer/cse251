#include "display.h"
#include "file.h"

int main()
{
    Event event_list[EVENT_MAX]={0};
    Event *ptrEvent = &event_list[EVENT_MAX];
    ptrEvent->name[0] = ptrEvent->date = ptrEvent->starttime = ptrEvent->endtime = 0;//防止越界
    
    int event_volume = 0;//事件数组下标
    int opt;

    print_menu();
    
    do
    {
        print_opt();

        scanf("%d",&opt);
        getchar();//消除'\n'

            switch (opt)
        {
        case 0:
            exit(0);
            break;

        case 1://1 - Insert a new event
            new_event(event_list, &event_volume);
            break;

        case 2://2 - Display all events
            display_all_event(event_list, event_volume);
            break;

        case 3://3 - Now?
            print_now_event(event_list);            
            break;

        case 4://4 - Delete expired
            Delete_expired(event_list, &event_volume);
            break;
        
        default:
            break;
        }
    print_menu();
    } while (1);
    
    return 0;
}

