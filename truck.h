#ifndef TRUCK_H
#define TRUCK_H
#define truck_num 4

typedef struct location{
    int vertice;
    char name[50];
}location;

typedef struct Bin{
    int hasBin;
    int FullLevel;
}bin;

typedef struct Truck{
    int capacity;
    int currentLoad;
    int position;
}truck;


void initTruck(truck arr[], int n);
void displayTrucks(int n, truck arr[]);
int selectTruck(int num, int n, truck arr[], bin binArr[]);

#endif
