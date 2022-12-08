/*
* File: main.c
* Author: Eugenio Moya
* Course: 20211
* Descripción: PEC6 2021 1
*/

/* System header files */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>


/* Global constants */
#define CATEGORY1 1   				//Category 1 id
#define CATEGORY2 2   				//Category 2 id
#define CATEGORY3 3   				//Category 3 id
#define MAX_CHAR_LEN 15+1			//Max. char len
#define CENTER1_WIN 1
#define CENTER2_WIN -1
#define CENTER_TIED 0

/* User defined types */
typedef enum {STARTUPS, FREELANCERS, RURAL, SPECIALIZED, GENERALIST} tCoworkingType;

/* User defined Struct */
typedef struct {
    char name[MAX_CHAR_LEN];
    char city[MAX_CHAR_LEN];
    int category;
    tCoworkingType centerType;
	int numSpaces;
    float price;
    float distanceFromCityCenter;
	bool hasMeetingRooms;
	bool hasAuditorium;
} tCoworkingCenter;

/* Predeclaration of actions and functions */
void readCenter (tCoworkingCenter *center);
void writeCenter (tCoworkingCenter center);
bool isAcceptableCenter (tCoworkingCenter center, float price, float distance);
int bestCenter (tCoworkingCenter center1, tCoworkingCenter center2);

/* Main function */
int main(int argc, char **argv) {
	
	/* Variables */
	tCoworkingCenter center1;
	tCoworkingCenter center2;
	float price;
	float distance; 
	bool isAcceptableCenterReturn1;  
	bool isAcceptableCenterReturn2;
	int isBestCenter;
	
	
	/* Exercise 2.5 */
	/* Data input Center 1 */
	printf("ENTER DATA FOR CENTER 1\n");
	readCenter(&center1);
	
	/* Data input Center 2*/
	printf("ENTER DATA FOR CENTER 2\n");
	readCenter(&center2);
	
	/* Data input aceptable price */
	printf("ACCEPTABLE PRICE [EUR]? >>\n");
	scanf("%f",&price);

	/* Data input aceptable distance */
	printf("ACCEPTABLE DISTANCE FROM CITY CENTER [KM]? >>\n");
	scanf("%f",&distance);

	/*Check that the centers are acceptable*/
	isAcceptableCenterReturn1 = isAcceptableCenter (center1, price, distance);
	isAcceptableCenterReturn2 = isAcceptableCenter (center2, price, distance);
	 
	printf("RESULTS\n");

	if ((isAcceptableCenterReturn1 == true) && (isAcceptableCenterReturn2 == true) && (strcmp(center1.city, center2.city)==0)) {
		isBestCenter = bestCenter(center1, center2);
		if ((isBestCenter == CENTER_TIED) || (isBestCenter == CENTER1_WIN)) {
                printf("CENTER 1 SUITS YOU BETTER, AND THE DATA ARE:\n");
                writeCenter(center1);
                printf("THE SECOND BEST CENTER IS CENTER 2 AND THE DATA ARE:\n");
                writeCenter(center2);
		}else{ 
                printf("CENTER 2 SUITS YOU BETTER, AND THE DATA ARE:\n");
                writeCenter(center2);
                printf("THE SECOND BEST CENTER IS CENTER 1 AND THE DATA ARE:\n");
                writeCenter(center1);	
		}
	}else{ 
            printf("CENTERS CAN'T BE COMPARED\n");
		
	}
	
	return 0;
}

/* Implementation of actions and functions */

 /* Exercise 2.1 */
void readCenter (tCoworkingCenter *center) {
	int intToBool;
	printf("NAME? (A STRING)>>\n");
	scanf("%s",center->name);
	printf("CITY? (A STRING)>>\n");
	scanf("%s",center->city);
	printf("CATEGORY? (1-CATEGORY1, 2-CATEGORY2, 3-CATEGORY3)>>\n");
	scanf("%d",&center->category);
	printf("CENTER TYPE? (1-STARTUPS, 2-FREELANCERS, 3-RURAL, 4-SPECIALIZED, 5-GENERALIST)>>\n");
	scanf("%u",&center->centerType);
	printf("NUM. SPACES? (AN INTEGER)>>\n");
	scanf("%d",&center->numSpaces);
	printf("PRICE EUR? (A REAL)>>\n");
	scanf("%f",&center->price);
	printf("DISTANCE TO CITY CENTER [KM]? (A REAL)>>\n");
	scanf("%f",&center->distanceFromCityCenter);
	printf("HAS MEETING ROOMS? (0-FALSE, 1-TRUE)>>\n");
	scanf("%d",&intToBool);
	center->hasMeetingRooms = (bool)intToBool;
	printf("HAS AUDITORIUM? (0-FALSE, 1-TRUE)>>\n");
	scanf("%d",&intToBool);
	center->hasAuditorium = (bool)intToBool;
}

/* Exercise 2.2 */
void writeCenter (tCoworkingCenter center){
	printf("CENTER'S DATA:\n");
	printf("NAME: %s\n",center.name);
	printf("CITY: %s\n",center.city);	
	printf("CATEGORY (1-CATEGORY1, 2-CATEGORY2, 3-CATEGORY3): %d\n",center.category);
	printf("CENTER TYPE (1-STARTUPS, 2-FREELANCERS, 3-RURAL, 4-SPECIALIZED, 5-GENERALIST): %u\n",center.centerType);	
	printf("NUM. SPACES: %d\n",center.numSpaces);
	printf("PRICE: %.2f\n",center.price);
	printf("DISTANCE TO CITY CENTER [KM]: %.2f\n",center.distanceFromCityCenter);
	printf("HAS MEETING ROOMS (0-FALSE, 1-TRUE): %d\n",center.hasMeetingRooms);	  
	printf("HAS AUDITORIUM (0-FALSE, 1-TRUE): %d\n",center.hasAuditorium);
}

/*Exercise 2.3 */
bool isAcceptableCenter (tCoworkingCenter center, float price, float distance) {
		
	bool isAcceptableCenterReturn;  

    if(((center.hasMeetingRooms == true) || (center.hasAuditorium == true)) && ((center.price <= price) && (center.distanceFromCityCenter <= distance))) {
        isAcceptableCenterReturn = true;
    }else{
        isAcceptableCenterReturn = false;
    }

	return isAcceptableCenterReturn;

}

/* Exercise 2.4 */
int bestCenter (tCoworkingCenter center1, tCoworkingCenter center2) {

	int isBestCenter=0;
    
    if (center1.category > center2.category) {
        isBestCenter = CENTER1_WIN;
    }else{
        if (center2.category > center1.category) {
            isBestCenter = CENTER2_WIN;
        }else{
            if (center1.distanceFromCityCenter < center2.distanceFromCityCenter) {
                isBestCenter = CENTER1_WIN;
            }else{
                if(center2.distanceFromCityCenter < center1.distanceFromCityCenter) {
                    isBestCenter = CENTER2_WIN;
                }else{
                    if ((center1.hasMeetingRooms == true) && (center2.hasMeetingRooms == false)) {
                        isBestCenter =  CENTER1_WIN;
                    }else{
                        if((center2.hasMeetingRooms == true) && (center1.hasMeetingRooms == false)) {
                            isBestCenter = CENTER2_WIN;
                        }else{
                            isBestCenter = CENTER_TIED;
                        }
                    }
                }
            }
        }
    }
           
    return isBestCenter;

}


