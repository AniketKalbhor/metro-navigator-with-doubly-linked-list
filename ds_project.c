#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct station
{
    char name[25];
    int station_no;
    float distance;
    struct station *prev;
    struct station *next;
};
struct station *head;
struct station *tail;
struct station *temp;
struct station *start_st;
struct station *end_st;

char start[25], end[25];
char station_names[14][25]={"PCMC","SANT TUKARAM NAGAR","BHOSARI","KASARWADI","PHUGEWADI","DAPODI","BOPODI","KHADKI","RANGE HILL","SHIVAJINAGAR","CIVIL COURT","BUDHWAR PETH","MANDAI","SWARGATE"};
float station_distances[14]={2,0.65,1.5,1.1,0.8,1.6,1.4,1.4,5.5,1.4,1.7,0.6,1.5,0};

void to_UpperCase(char *str);
struct station *station_search(char *destination);
void assign_destinations(char *tart, char *end);
void print_route(char *start, char *end);
void dist_fare(char *start, char *end); 
int fare(float distance);

int i=0;
int creation(char station_name[][25])
{
    struct station *create;
    create = (struct station *)malloc(sizeof(struct station));

    if(i!=14)
    {
        strcpy(create->name, station_name[i]);
        create->station_no = i;
        create->distance = station_distances[i];
        create->prev = NULL;
        create->next = NULL;
        if(head == NULL)
        {
            head = create;
            tail = create;
        }
        else
        {
            tail->next = create;
            create->prev = tail;
            tail = create;
        }
		i++;
		creation(station_names);
    }
	else
		return 0;
}

int main()
{
    creation(station_names);

    int choice; 
    do
    {  
        printf("1. Print all routes\n2. Fare\n3. Print Route\n4. Exit\n\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("\nNorth South corridor of Pune metro: \n");
                print_route("PCMC", "SWARGATE");
                break;
            case 2:
                fflush(stdin); 
                printf("Enter the starting station: ");
                gets(start);
                fflush(stdin);
                printf("Enter the destination station: ");
                gets(end);
                dist_fare(start, end);
                break;
            case 3:
                fflush(stdin);
                printf("Enter the starting station:");
                gets(start);
                fflush(stdin);
                printf("Enter the destination station:");
                gets(end);
                print_route(start, end);
                break;
            case 4:
                exit(0);
        }
    }while(choice!=4);
    return 0;
}

void to_UpperCase(char *str)
{
    for(int i=0;str[i]!='\0';i++)
        if(str[i]>='a'&& str[i]<='z')
            str[i] = str[i]-32;
}

struct station *station_search(char *destination)
{
    to_UpperCase(destination);
    temp = head;
    while(temp!=NULL)
    {
        if(strcmp(temp->name, destination)==0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void assign_destinations(char *start, char *end)
{
    start_st = station_search(start);
    end_st = station_search(end);
}

void print_route(char *start, char *end)
{
    assign_destinations(start, end);

    if (start_st == NULL || end_st == NULL)
    {
        printf("\n************Invalid station names**************\n");
        return;
    }

    temp = start_st;

    if(start_st->station_no < end_st->station_no)
    {
        while(temp!=end_st)
        {
            printf("%s ==> ", temp->name);
            temp = temp->next;
        }
        printf("%s", temp->name);
        printf("\n\n");
    }
    else if(start_st->station_no > end_st->station_no)
    {
        while(temp!=end_st)
        {
            printf("%s ==> ", temp->name);
            temp = temp->prev;
        }
        printf("%s", temp->name);
        printf("\n\n");
    }
    else
        printf("You are already at %s\n", start);
}

int fare(float distance)
{
    if (distance<=2)
        return 10;
    else if(distance>2 && distance<=4)
        return 20;
    else if(distance>4 && distance<=12)
        return 30;
    else if(distance>12 && distance<=18)
        return 40;
    else
        return 50;
}

void dist_fare(char *start, char *end)
{
    int money = 0;
    float total_distance = 0;
    assign_destinations(start, end);

    if (start_st == NULL || end_st == NULL)
    {
        printf("\n************Invalid station names**************\n");
        return;
    }

    temp = start_st;

    if(start_st->station_no < end_st->station_no)
    {
        while(temp!=end_st)
        {
            total_distance += temp->distance;
            temp = temp->next;
        }
        printf("Distance = %.2f km\n", total_distance);
        money = fare(total_distance);
        printf("Fare = Rs %d\n", money);
    }
    else if(start_st->station_no > end_st->station_no)
    {
        while(temp!=end_st)
        {
            temp = temp->prev;
            total_distance += temp->distance;
        }
        printf("Distance of your journey is %.2f\n", total_distance);
        money = fare(total_distance);
        printf("Fare = Rs %d\n", money);
    }
    else
        printf("You are already at %s\n", start);
}