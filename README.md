# 🚗✨ Smart Parking System using C

---

## 🌟 Overview

The **Smart Parking System** is a console-based application developed in C that efficiently manages parking across multiple areas using advanced data structures like **Hash Tables** and **Graph Representation**.

It enables fast vehicle lookup, prevents duplicate entries, and ensures optimal utilization of parking slots — making it a practical simulation of a real-world smart parking solution.

---

## 🎯 Key Features

- ✨ Park Vehicle with automatic slot allocation  
- 🔍 Instant Vehicle Search using Hashing (**O(1)** time complexity)  
- ❌ Remove Vehicle with quick deallocation  
- 📊 Real-time Parking Status (Area-wise)  
- 📍 Detailed View of Individual Parking Areas  
- 🚫 Duplicate Vehicle Entry Prevention  
- 🏢 Multiple Parking Areas (A, B, C)  
- 🔗 Graph-based Area Connectivity  

---

## 🧠 System Architecture

### 🚘 Parking Slot Structure
Each slot stores:
- Occupancy Status  
- Vehicle Number  
- Owner Name  

---

### 🏢 Parking Area Structure
Each area contains:
- Area Name (A, B, C)  
- Number of Free Slots  
- Array of 25 Parking Slots  

---

### ⚡ Hash Table (Core Optimization)

Used for **fast vehicle tracking**.

Stores:
- Vehicle Number (Key 🔑)  
- Area Index  
- Slot Index  

➡️ Uses **Linked List Chaining** for collision handling  

---

### 🔗 Graph Representation

Parking areas are connected using an adjacency matrix:

```
A ↔ B ↔ C
```

---

## ⚙️ Core Functionalities

- `initialize()` → Setup parking areas & hash table  
- `hash_function()` → Generate index from vehicle number  
- `insert_hash()` → Store vehicle location  
- `search_hash()` → Fast vehicle lookup  
- `delete_hash()` → Remove vehicle record  
- `find_area()` → Find available parking area  
- `park_vehicle()` → Allocate slot  
- `remove_vehicle()` → Free slot  
- `search_vehicle()` → Display vehicle info  
- `display_status()` → Show occupancy status  
- `area_details()` → Slot-wise detailed view  

---

## 🛠️ Technologies Used

### 💻 Programming Language
- C  

### 📚 Libraries
- `stdio.h`  
- `stdlib.h`  
- `string.h`  

---

## 🚀 Working Flow

1. System initializes all parking areas and hash table  
2. User selects an operation from the menu  
3. System processes request:  
   - Park → Assign slot  
   - Search → Instant lookup  
   - Remove → Free slot  
4. Data structures update dynamically  

---

## 📊 Sample Menu

```
SMART PARKING SYSTEM
1. Park Vehicle
2. Remove Vehicle
3. Search Vehicle
4. Display Status
5. Area Details
6. Exit
```

---

## ⚡ Advantages

- ✅ Fast Search (**O(1)** using Hashing)  
- ✅ Efficient Space Utilization  
- ✅ Structured Multi-Area Management  
- ✅ Scalable Design for Future Expansion  
- ✅ Simple & User-Friendly Interface  

---

## ⚠️ Limitations

- Fixed Areas (3) and Slots (25 per area)  
- Console-based (No GUI)  
- No persistent storage (data resets on restart)  
- Graph not fully utilized yet  

---

## 🔮 Future Enhancements

- 🚀 Dynamic parking allocation  
- 📍 Smart slot selection using Graph algorithms  
- 🧠 Machine Learning for demand prediction  
- 🌐 Web/App-based interface  
- 💾 Database integration for permanent storage  
- 📱 Online booking system  

---

## 📌 Conclusion

This project showcases how **Data Structures like Hashing and Graphs** can be effectively used to solve real-world problems such as parking management.

It serves as a strong foundation for building advanced **Smart City Parking Solutions**.
