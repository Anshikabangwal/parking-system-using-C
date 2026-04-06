#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for parking slot
struct parking_slot
{
    int slot_number;
    char vehicle_number[20];
    char owner_name[50];
    struct parking_slot *left;
    struct parking_slot *right;
};

// create new slot
struct parking_slot* create_slot(int slot_number, char vehicle_number[], char owner_name[])
{
    

    struct parking_slot *new_slot = (struct parking_slot*)malloc(sizeof(struct parking_slot));

    new_slot->slot_number = slot_number;
    strcpy(new_slot->vehicle_number, vehicle_number);
    strcpy(new_slot->owner_name, owner_name);

    new_slot->left = NULL;
    new_slot->right = NULL;

    return new_slot;
}

// insert in tree 
struct parking_slot* insert_slot(struct parking_slot *root, int slot_number, char vehicle_number[], char owner_name[])
{
    if (root == NULL)
        return create_slot(slot_number, vehicle_number, owner_name);

    if (slot_number < root->slot_number)
        root->left = insert_slot(root->left, slot_number, vehicle_number, owner_name);
    else if (slot_number > root->slot_number)
        root->right = insert_slot(root->right, slot_number, vehicle_number, owner_name);
    else
        printf("slot already occupied!\n");

    return root;
}

// search slot
struct parking_slot* search_slot(struct parking_slot *root, int slot_number)
{
    if (root == NULL || root->slot_number == slot_number)
        return root;
    // go search in left 
    if (slot_number < root->slot_number)
        return search_slot(root->left, slot_number);
    // go search in right 
    return search_slot(root->right, slot_number);
}

// display 
void display_slots(struct parking_slot *root)
{   
    // inorder traversal implemented 
    
    if (root != NULL)
    {
        display_slots(root->left);

        printf("slot %d - vehicle: %s - owner: %s\n",
               root->slot_number,
               root->vehicle_number,
               root->owner_name);

        display_slots(root->right);
    }
}

int main()
{
    struct parking_slot *root = NULL;
    int choice, slot_number;
    char vehicle_number[20], owner_name[50]; 

    while (1)
    {
        printf("\n \t\t\t parking management system \n\n");
        printf("1. park vehicle\n");
        printf("2. remove vehicle (not implemented) \n");
        printf("3. search vehicle\n");
        printf("4. display parking slots\n");
        printf("5. exit\n");
        printf("enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("enter slot number: ");
                scanf("%d", &slot_number);

                printf("enter vehicle number: ");
                scanf(" %[^\n]", vehicle_number);

                printf("enter owner name: ");
                scanf(" %[^\n]", owner_name); 

                root = insert_slot(root, slot_number, vehicle_number, owner_name);
                break;

            case 2:
                printf("in progress \n");
                break;

            case 3:
            {
                printf("enter slot number to search: ");
                scanf("%d", &slot_number);
                // calling
                struct parking_slot *found = search_slot(root, slot_number);
                
                if (found != NULL)
                    printf("slot %d - vehicle: %s - owner: %s\n",
                           found->slot_number,
                           found->vehicle_number,
                           found->owner_name);
                else
                    printf("No vehicle parked \n");

                break;
            }

            case 4:
                printf("\n \t \t parking slots\t \t \n");
                display_slots(root);
                break;

            case 5:
                printf("exiting...\n");
                exit(0);

            default:
                printf("please select valid choice\n");
        }
    }

    return 0;
}
