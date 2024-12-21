//Program to implement flight information system
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
//creating a structure to store flight details
struct Flight 
{
    char flightID[10];
    char source[20];
    char arrivalTime[10];
    char destination[20];
    char departureTime[10];
    float flightTime;
    float fare;
}flights[20];
//creating a structure to store cities
struct city
{
    char cities[20]; 
}city_list[7];
//Creating prototypes for function
void displayallflights();
void displaysource();    
void displaysourcetodesination();   
//Main function
int main()
{
    FILE *fp, *fp2;
    int flightn=20,i=0,choice;
    //opening FLIGHT DETAILS csv file
    fp = fopen("FLIGHTDETAILS.csv", "r");
    if (fp == NULL) 
    {
        printf("Error opening file FLIGHT DETAILS");
        return 1;
    }
    //opening LOCATION csv file
    fp2 = fopen("PLACES.csv", "r");
    if (fp2 == NULL) 
    {
        printf("Error opening file PLACES");
        return 2;
    }
    //reading flight details from csv file
    char line[60];
    while (fgets(line, sizeof(line), fp)){
        if(sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%f,%f", &flights[i].flightID, &flights[i].source, &flights[i].arrivalTime, &flights[i].destination, &flights[i].departureTime, &flights[i].flightTime, &flights[i].fare) == 7) {
            i++;
            if (i==20) {
            break;
            }
        }
    }
    i=0;
    //reading city details from csv file
    while (fscanf(fp2, "%s", city_list[i].cities) == 1) 
    {
        i++;
        if (i == 7) 
        {
            break;
        }
    }
    //closing files
    fclose(fp);
    fclose(fp2);
    //Asking user to select option
    do
    {
        printf("Select a option\n");
        printf("1.To check all the flights available.\n");
        printf("2.To check all the flights from once place.\n");
        printf("3.To check all the flights from one place to another place.\n");
        printf("4.To exit\n");
    //To verify user is giving option in intergers
        while((scanf("%d",&choice)!=1))
        {
            while(getchar()!='\n');
            printf("Error in option ,Please type respective option.\n");
        }
        switch(choice)
        {
            case 1:displayallflights();
                   break; 
            case 2:displaysource();       
                   break; 
            case 3:displaysourcetodesination(); 
                   break;      
            case 4:return 0;       
            default:printf("Invalid choice\n");
                    break;    
        }
    } while (choice!=4);
    return 0;   
}
//function to display all flights
void displayallflights()
{
    //Displaying all flights
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int i=0;i<75;i++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < 20; i++) 
    {
        printf("%-10s %-10s %-10s %-10s %-10s %-10.2f  %-10.2f\n",
               flights[i].flightID, flights[i].source, flights[i].arrivalTime,
               flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
    }
      for(int i=0;i<75;i++)
    {
        printf("-");
    }
    printf("\n");
}
//function to display a flight from user given source
void displaysource()
{
    int option;
    //Asking user to select a source
    jump_here1:
    printf("Select the source\n");
    for(int i=0;i<7;i++)
    {
        printf("%d.%s\n",i+1,city_list[i].cities);
    }   
    //To verify user is giving option in intergers
    while((scanf("%d",&option)!=1))
    {
        while(getchar()!='\n');
        printf("Error in option ,Please type respective option.\n");
    }
    if(option>=8)
    {
        printf("Please Enter different source\n");
        goto jump_here1;
    }
    printf("%s\n",city_list[option-1].cities);
    //Displaying all flights from selected source
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n");
    //Display flights
    for(int i=0;i<20;i++)
    {
        if(strcmp(city_list[option-1].cities,flights[i].source)==0)
        {
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                    flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
        }
    }           
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
        printf("\n");
}    
//function to display flights from user given source and destination
void displaysourcetodesination()
{
    int option,option1,verify=0;
    float totaltime,totalfare;
    //Asking user to select the source
    jump_here2:
    printf("Select the source\n");
    for(int i=0;i<7;i++)
    {
        printf("%d.%s\n",i+1,city_list[i].cities);
    }   
    //To verify user is giving option in intergers
    while((scanf("%d",&option)!=1))
    {
        while(getchar()!='\n');
        printf("Error in option ,Please type respective option.\n");
    }
    printf("%s\n",city_list[option-1].cities);
    //Asking user to select destination
    printf("Select the destination\n");
    for(int i=0;i<7;i++)
    {
        if(strcmp(city_list[option-1].cities,city_list[i].cities)==0)
        {
            continue;
        }
        printf("%d.%s\n",i+1,city_list[i].cities);   
    }   
    //To verify user is giving option in intergers
    while((scanf("%d",&option1)!=1))
    {
        while(getchar()!='\n');
        printf("Error in option ,Please type respective option.\n");
    }
    printf("%s\n",city_list[option1-1].cities);
    //Asking user to select different destination 
    if(city_list[option-1].cities==city_list[option1-1].cities||option1>=8||option>=8)
    {
        printf("Please Enter different destination\n");
        goto jump_here2;
    }
    //printing direct flights from source to destintation
    printf("%40s\n","DIRECT FLIGHTS");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n");
    //Display flights
    for(int i=0;i<20;i++)
    {
        if(strcmp(city_list[option-1].cities,flights[i].source)==0 && strcmp(city_list[option1-1].cities,flights[i].destination)==0)
        {
            verify=1;
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                    flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
        }
    }   
    //Displaying no direct files if not available
    if(verify==0)
    {
        printf("\t\t\tNO DIRECT FLIGHTS ):\n");
    }        
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n\n");
    verify=0;
    //Displaying Indirect flights
    printf("%40s\n","INDIRECT FLIGHTS");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Flight ID", "Source", "Arrival", "Destination", "Departure", "Time", "Fare");
    for(int j=0;j<75;j++)
    {
        printf("-");
    }
    printf("\n");
    //Display flights
    for(int i=0;i<20;i++)
    for(int j=0;j<20;j++)
    {
        if(strcmp(city_list[option-1].cities,flights[i].source)==0 && strcmp(flights[j].source,flights[i].destination)==0 && strcmp(city_list[option1-1].cities,flights[j].destination)==0)
        {
            verify=1;
            printf("%s","**FLIGHT 1**\n\n");
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[i].flightID, flights[i].source, flights[i].arrivalTime,
                    flights[i].destination, flights[i].departureTime, flights[i].flightTime, flights[i].fare);
            printf("%s","\n**FLIGHT 2**\n\n");
            printf("%-10s %-10s %-10s %-10s %-10s %-10.2f %-10.2f \n",
                    flights[j].flightID, flights[j].source, flights[j].arrivalTime,
                    flights[j].destination, flights[j].departureTime, flights[j].flightTime, flights[j].fare);        
            totalfare=flights[i].fare+flights[j].fare;      
            totaltime=flights[i].flightTime+flights[j].flightTime;  
            printf("\n");
            printf("TOTAL TIME = %0.2f hours\n",totaltime);
            printf("TOTAL FARE = Rs. %0.2f\n",totalfare);
            for(int j=0;j<75;j++)
            {
                printf("-");
            }
        printf("\n");
        }
    }     
    //Displaying no Indirect files if not available
    if(verify==0)
    {
        printf("\t\t\tNO INDIRECT FLIGHTS ):\n");
        for(int j=0;j<75;j++)
        {
            printf("-");
        }
    }      
    printf("\n");
}

    
