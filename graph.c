#include <stdio.h>
#include "truck.h"
#include "dijkstra.h"

typedef struct location {
    int vertice;
    char name[50];
} location;

typedef struct Bin {
    int hasBin;
    int FullLevel;
} bin;

void main() {

    int num = 0, dist = 0, ch;
    printf("\n\n\t\t=========================================\n");
    printf("\t\t        ROADMAP OF DEHRADUN\n");
    printf("\t\t=========================================\n\n");

    printf("Enter the number of locations -> ");
    scanf("%d", &num);

    location location[num];
    int adj[num][num];
    bin bin[num];

    for (int i = 0; i < num; i++) {
        location[i].vertice = i;
        printf("\nEnter the name of location %d -> ", i);
        scanf("%s", location[i].name);

        printf("Does this location have a Bin? (1 = Yes / 0 = No): ");
        scanf("%d", &bin[i].hasBin);

        if (bin[i].hasBin) {
            printf("Enter the fill level (%%) of bin at %s -> ", location[i].name);
            scanf("%d", &bin[i].FullLevel);
        } else {
            bin[i].FullLevel = 0; 
        }
    }

    printf("\n\n============================================\n");
    printf("  Enter the distance between locations (0 if none)\n");
    printf("============================================\n\n");

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            printf("Distance between %-12s and %-12s -> ", location[i].name, location[j].name);
            scanf("%d", &adj[i][j]);
        }
        printf("\n");
    }

    printf("\n\n============================================================\n");
    printf("                   CITY AND BIN INFORMATION\n");
    printf("============================================================\n\n");

    printf("%-5s %-15s %-10s %-10s\n", "No.", "Location", "Bin", "Fill Level");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < num; i++) {
        printf("%-5d %-15s %-10s %d%%\n",location[i].vertice,location[i].name,(bin[i].hasBin ? "YES" : "NO"),bin[i].FullLevel);
    }

    printf("\n\n\t\t=========================================\n");
    printf("\t\t            DISTANCE MATRIX(---MAP---)\n");
    printf("\t\t=========================================\n\n");

    printf("%-15s", " ");
    for (int i = 0; i < num; i++) {
        printf("%-15s", location[i].name);
    }
    printf("\n");

    for (int i = 0; i < num; i++) {
        printf("%-15s", location[i].name);
        for (int j = 0; j < num; j++) {
            printf("%-15d", adj[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    
    truck arrTruck[truck_num];

    initTruck(arrTruck, truck_num);
    
    displayTrucks(truck_num, arrTruck);

    printf("\n Enter the starting position from where u want to start sending Garbage Trucks : ");
    int startPosition;
    scanf("%d", &startPosition);
    
    int truckNum = selectTruck(num, truck_num, arrTruck, bin);
    
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("         TRUCK ASSIGNMENT\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    if(truckNum != -1){
        printf("✓ Truck-%d assigned for collection\n", truckNum + 1);
        printf("  Capacity: %d units\n", arrTruck[truckNum].capacity);
        printf("  Current Load: %d units\n", arrTruck[truckNum].currentLoad);
    } else {
        printf("✗ ERROR: No truck available with sufficient capacity!\n");
        printf("  Total load exceeds maximum truck capacity.\n");
        printf("  Please use multi-truck dispatch (Task 2).\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
        return;
    }
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

    //Greedy

    int route[num];
    int routeLen = 0;
    int totalDist = 0;
    
    greedyCollectionRoute(num, adj, startPosition, bin, location, 
                         route, &routeLen, &totalDist, 
                         arrTruck[truckNum].capacity);

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("     SHORTEST DISTANCES FROM DEPOT (Reference)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    int distance[num], parent[num];
    dijkstra(num, adj, startPosition, distance, parent);
    for(int i = 0 ; i < num; i++){
        if(i != startPosition) {
            printf("%s ➜ %-15s : %d km\n", 
                   location[startPosition].name, location[i].name, distance[i]);
        }
    }
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}
