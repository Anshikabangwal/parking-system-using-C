#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AREAS 3
#define MAX_SLOTS 25
#define TABLE_SIZE 100

// ---------------- HASH STRUCTURE ----------------
struct hash_node {
    char vehicle_number[20];
    int area_index;
    int slot_index;
    struct hash_node *next;
};

struct hash_node* hash_table[TABLE_SIZE];

// hash function
int hash_function(char *vehicle) {
    int sum = 0;
    for (int i = 0; vehicle[i] != '\0'; i++)
        sum += vehicle[i];
    return sum % TABLE_SIZE;
}

// insert into hash
void insert_hash(char *vehicle, int area, int slot) {
    int index = hash_function(vehicle);

    struct hash_node *new_node = (struct hash_node*)malloc(sizeof(struct hash_node));
    strcpy(new_node->vehicle_number, vehicle);
    new_node->area_index = area;
    new_node->slot_index = slot;
    new_node->next = hash_table[index];

    hash_table[index] = new_node;
}

// search in hash
struct hash_node* search_hash(char *vehicle) {
    int index = hash_function(vehicle);

    struct hash_node *temp = hash_table[index];
    while (temp != NULL) {
        if (strcmp(temp->vehicle_number, vehicle) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// delete from hash
void delete_hash(char *vehicle) {
    int index = hash_function(vehicle);

    struct hash_node *temp = hash_table[index];
    struct hash_node *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->vehicle_number, vehicle) == 0) {
            if (prev == NULL)
                hash_table[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// ---------------- ORIGINAL STRUCTURES ----------------
struct slot {
    int occupied;
    char vehicle_number[20];
    char owner_name[50];
};

struct area {
    char name;
    int free_slots;
    struct slot slots[MAX_SLOTS];
};

int graph[MAX_AREAS][MAX_AREAS] = {
    {0,1,1},
    {1,0,1},
    {1,1,0}
};

struct area areas[MAX_AREAS];

// initialize
void initialize() {
    for (int i = 0; i < TABLE_SIZE; i++)
        hash_table[i] = NULL;

    for (int i = 0; i < MAX_AREAS; i++) {
        areas[i].name = 'A' + i;
        areas[i].free_slots = MAX_SLOTS;

        for (int j = 0; j < MAX_SLOTS; j++)
            areas[i].slots[j].occupied = 0;
    }
}

// find area
int find_area() {
    for (int i = 0; i < MAX_AREAS; i++) {
        if (areas[i].free_slots > 0)
            return i;
    }
    return -1;
}

// park vehicle
void park_vehicle() {
    char vehicle[20], owner[50];

    printf("Enter vehicle number: ");
    scanf(" %[^\n]", vehicle);

    // prevent duplicate entry
    if (search_hash(vehicle) != NULL) {
        printf("Vehicle already parked!\n");
        return;
    }

    printf("Enter owner name: ");
    scanf(" %[^\n]", owner);

    int area_index = find_area();

    if (area_index == -1) {
        printf("All parking areas are FULL!\n");
        return;
    }

    struct area *a = &areas[area_index];

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (!a->slots[i].occupied) {
            a->slots[i].occupied = 1;
            strcpy(a->slots[i].vehicle_number, vehicle);
            strcpy(a->slots[i].owner_name, owner);

            a->free_slots--;

            // insert into hash
            insert_hash(vehicle, area_index, i);

            printf("\nVehicle parked successfully!\n");
            printf("Area: %c\nSlot: %d\n", a->name, i+1);
            return;
        }
    }
}

// remove vehicle
void remove_vehicle() {
    char vehicle[20];

    printf("Enter vehicle number: ");
    scanf(" %[^\n]", vehicle);

    struct hash_node *found = search_hash(vehicle);

    if (found == NULL) {
        printf("Vehicle not found!\n");
        return;
    }

    int i = found->area_index;
    int j = found->slot_index;

    areas[i].slots[j].occupied = 0;
    areas[i].free_slots++;

    delete_hash(vehicle);

    printf("Vehicle removed from Area %c, Slot %d\n",
           areas[i].name, j+1);
}

// search vehicle
void search_vehicle() {
    char vehicle[20];

    printf("Enter vehicle number: ");
    scanf(" %[^\n]", vehicle);

    struct hash_node *found = search_hash(vehicle);

    if (found == NULL) {
        printf("Vehicle not found!\n");
        return;
    }

    int i = found->area_index;
    int j = found->slot_index;

    printf("Found!\nArea: %c\nSlot: %d\nOwner: %s\n",
           areas[i].name,
           j+1,
           areas[i].slots[j].owner_name);
}

// display status
void display_status() {
    printf("\n--- Parking Status ---\n");

    for (int i = 0; i < MAX_AREAS; i++) {
        printf("Area %c → %d/%d occupied (%d free)\n",
               areas[i].name,
               MAX_SLOTS - areas[i].free_slots,
               MAX_SLOTS,
               areas[i].free_slots);
    }
}

// area details
void area_details() {
    int choice;
    printf("Select Area (1-A, 2-B, 3-C): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice\n");
        return;
    }

    struct area *a = &areas[choice - 1];

    printf("\n--- Area %c Details ---\n", a->name);

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (a->slots[i].occupied) {
            printf("Slot %d → Occupied (%s - %s)\n",
                   i+1,
                   a->slots[i].vehicle_number,
                   a->slots[i].owner_name);
        } else {
            printf("Slot %d → Free\n", i+1);
        }
    }
}

// main
int main() {
    int choice;
    initialize();

    while (1) {
        printf("\nSMART PARKING SYSTEM\n");
        printf("1. Park Vehicle\n");
        printf("2. Remove Vehicle\n");
        printf("3. Search Vehicle\n");
        printf("4. Display Status\n");
        printf("5. Area Details\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: park_vehicle(); break;
            case 2: remove_vehicle(); break;
            case 3: search_vehicle(); break;
            case 4: display_status(); break;
            case 5: area_details(); break;
            case 6: exit(0);
            default: printf("Invalid choice\n");
        }
    }

    return 0;
}
