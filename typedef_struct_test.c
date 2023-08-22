#include <stdio.h>

typedef struct People
{
    char name[12];
    unsigned short int age;
    float height;
    float weight;
    char job[10];
    char address[20];

} Person;

void main()
{
  
    Person data, data2;
    Person *pData;

    //-------
    pData = &data;
    //-------
  

    printf("Please insert the information.\n");
    printf("Name: ");
    scanf("%s", data.name);
    printf("Age: ");
    scanf("%hu", &data.age);
    printf("Height: ");
    scanf("%f", &data.height);
    printf("weight: ");
    scanf("%f", &data.weight);
    printf("Job: ");
    scanf("%s", data.job);
    printf("Address: ");
    scanf("%s", data.address);

    data2 = data;

    printf("\nYour inserted result is \n");
    printf("%s: %d years old, %.1fcm, %.1fkg, %s, %s\n", data2.name, data2.age, data2.height,  pData->weight, data2.job, pData->address);
}
