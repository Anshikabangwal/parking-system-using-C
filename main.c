#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for parking slot
typedef struct ParkingSlot {
    int slotNumber;
    char vehicleNumber[20];
    char ownerName[50];
    struct ParkingSlot *left;
    struct ParkingSlot *right;
} ParkingSlot;

// Create new slot
ParkingSlot* createSlot(int slotNumber, char vehicleNumber[], char ownerName[]) {
    ParkingSlot* newSlot = (ParkingSlot*)malloc(sizeof(ParkingSlot));

    newSlot->slotNumber = slotNumber;
    strcpy(newSlot->vehicleNumber, vehicleNumber);
    strcpy(newSlot->ownerName, ownerName);

    newSlot->left = NULL;
    newSlot->right = NULL;

    return newSlot;
}

// Insert slot in BST
ParkingSlot* insertSlot(ParkingSlot* root, int slotNumber, char vehicleNumber[], char ownerName[]) {
    if (root == NULL)
        return createSlot(slotNumber, vehicleNumber, ownerName);

    if (slotNumber < root->slotNumber)
        root->left = insertSlot(root->left, slotNumber, vehicleNumber, ownerName);
    else if (slotNumber > root->slotNumber)
        root->right = insertSlot(root->right, slotNumber, vehicleNumber, ownerName);
    else
        printf("Slot already occupied!\n");

    return root;
}

// Search slot
ParkingSlot* searchSlot(ParkingSlot* root, int slotNumber) {
    if (root == NULL || root->slotNumber == slotNumber)
        return root;

    if (slotNumber < root->slotNumber)
        return searchSlot(root->left, slotNumber);

    return searchSlot(root->right, slotNumber);
}

// Find minimum value node
ParkingSlot* findMin(ParkingSlot* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Delete slot
ParkingSlot* deleteSlot(ParkingSlot* root, int slotNumber) {
    if (root == NULL)
        return root;

    if (slotNumber < root->slotNumber)
        root->left = deleteSlot(root->left, slotNumber);
    else if (slotNumber > root->slotNumber)
        root->right = deleteSlot(root->right, slotNumber);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            ParkingSlot* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            ParkingSlot* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        ParkingSlot* temp = findMin(root->right);

        root->slotNumber = temp->slotNumber;
        strcpy(root->vehicleNumber, temp->vehicleNumber);
        strcpy(root->ownerName, temp->ownerName);

        root->right = deleteSlot(root->right, temp->slotNumber);
    }

    return root;
}

// Inorder traversal to display slots
void displaySlots(ParkingSlot* root) {
    if (root != NULL) {
        displaySlots(root->left);

        printf("Slot %d - Vehicle: %s - Owner: %s\n",
               root->slotNumber,
               root->vehicleNumber,
               root->ownerName);

        displaySlots(root->right);
    }
}

// Main function
int main() {
    ParkingSlot* root = NULL;
    int choice, slotNumber;
    char vehicleNumber[20], ownerName[50];

    while (1) {
        printf("\n--- Parking Management System ---\n");
        printf("1. Park Vehicle\n");
        printf("2. Remove Vehicle\n");
        printf("3. Search Vehicle\n");
        printf("4. Display Parking Slots\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Slot Number: ");
                scanf("%d", &slotNumber);

                printf("Enter Vehicle Number: ");
                scanf("%s", vehicleNumber);

                printf("Enter Owner Name: ");
                scanf(" %[^\n]", ownerName);

                root = insertSlot(root, slotNumber, vehicleNumber, ownerName);
                break;

            case 2:
                printf("Enter Slot Number to Remove: ");
                scanf("%d", &slotNumber);

                root = deleteSlot(root, slotNumber);
                printf("Vehicle removed successfully.\n");
                break;

            case 3: {
                printf("Enter Slot Number to Search: ");
                scanf("%d", &slotNumber);

                ParkingSlot* found = searchSlot(root, slotNumber);

                if (found)
                    printf("Slot %d - Vehicle: %s - Owner: %s\n",
                           found->slotNumber,
                           found->vehicleNumber,
                           found->ownerName);
                else
                    printf("Slot %d is empty.\n", slotNumber);

                break;
            }

            case 4:
                printf("\n----- Parking Slots -----\n");
                displaySlots(root);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
