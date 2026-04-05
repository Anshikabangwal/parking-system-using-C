# Parking System using C

## Overview

This project is a Parking Management System implemented in C using the Binary Search Tree (BST) data structure.

It efficiently manages parking slots by allowing users to add, search, and display vehicle records in a structured manner.

The system demonstrates the real-world application of data structures for optimizing parking operations.


## Features

- Park Vehicle (Insert into BST)
- Search Vehicle by Slot Number
- Display All Occupied Slots (Sorted Order)
- Delete Vehicle (In Progress)
- AVL Tree Balancing (Planned)
- Fixed Slot Management (Planned)


## Project Structure

ParkingSlot (Structure)

Stores:
- Slot Number (Key)
- Vehicle Number
- Owner Name
- Left pointer
- Right pointer


Core Functions

- createSlot() → Create new node
- insertSlot() → Add vehicle
- searchSlot() → Find vehicle
- deleteSlot() → Remove vehicle (in progress)
- displaySlots() → Inorder traversal


## Technologies Used

C Programming Language

Libraries:
- stdio.h
- stdlib.h
- string.h


## Limitations

- BST may become unbalanced (O(n) in worst case)
- No fixed slot capacity
- Data not stored permanently
- Console-based interface


## Note

This project is developed as part of academic learning to demonstrate the use of Data Structures (BST) in solving real-world problems.
