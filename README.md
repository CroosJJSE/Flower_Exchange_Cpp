# Flower_Exchange_Cpp
a project done for the C++ workshop series by LSEG.

![Screenshot 2023-09-03 232051](https://github.com/CroosJJSE/Flower_Exchange_Cpp/assets/141708783/f3007cdd-f090-4c9f-a120-3afe7606852c)


---

## Trading Application using C++: Buyers and Sellers

Welcome to the Trading Application, a C++ program designed for managing trading operations between buyers and sellers. This application takes input data comprising Client Order ID, Instrument, Side (Buy or Sell), Price, and Quantity and generates an output CSV file with detailed trading information, including Client Order ID, Order ID, Instrument, Side, Price, Quantity, Status, and Reasons for rejection.

### Key Features:

- **Dynamic Sizing**: Our application efficiently manages data of varying sizes. Trading operations often involve an unpredictable number of transactions, and the program dynamically adjusts to accommodate this, ensuring optimal resource usage.

- **Efficient Insertions and Deletions**: In trading, insertions and deletions are frequent operations, especially when handling a large number of transactions. Our program excels in managing these operations, offering constant-time insertion and deletion in the middle of the data structure, thanks to its initial use of **linked lists**.

    > **Note:** I initially implemented a linked list data structure, which proved crucial for efficient insertions and deletions in reak time applications.
    >  But Why Linked Lists May Not Be Suitable for Big Data:
    > > -   Memory Overhead: Linked lists consume additional memory for pointers, becoming a significant overhead with large data.
    > > -   Fragmentation: Dynamic memory allocation can lead to memory fragmentation, causing inefficient memory usage.
    > > -   Poor Cache Performance: Linked lists offer poor cache locality, resulting in less efficient cache performance.
    > > -   Slower Access Time: Accessing specific elements can be slower due to linear search, while other data structures provide faster access times.
    > > -   Complexity: The management of pointers, memory, and code complexity can become more challenging with large data.
    > > -   Suboptimal Iteration: Traversing large linked lists can be less efficient for operations requiring sequential access.
    > > -   Limited Parallelism: Linked lists may not support parallel processing, which is crucial for handling big data efficiently.
    > > -   Stack Overflow: Recursion in linked list operations may lead to stack overflow with a large number of elements.
  
![image](https://github.com/CroosJJSE/Flower_Exchange_Cpp/assets/141708783/299d4eee-4e26-4e13-9888-28fe4fba4832)


### output i received when the number of input is high
![image](https://github.com/CroosJJSE/Flower_Exchange_Cpp/assets/141708783/5c8222a0-04e4-4cd1-a6ea-d273c85e637e)

- **Robust Performance**: We have extensively tested the program with a wide range of data sizes and scenarios. While initially implemented using linked lists, which excel at certain operations, we have since transitioned to using vectors for better scalability. Vectors have proven to handle very large datasets, successfully managing over 80 transactions without issues.

  
![image](https://github.com/CroosJJSE/Flower_Exchange_Cpp/assets/141708783/7598326c-8a0b-4f06-996f-b9f31e3fb735)

## How Vectors Overcome Challenges with Big Data:

    - Efficient Memory Usage: Vectors allocate memory in larger blocks, reducing memory overhead compared to linked lists.
    - Optimal Cache Performance: Contiguous memory storage enhances cache locality, leading to efficient cache performance.
    - Fast Access Time: Vectors offer fast access times for specific elements, crucial for large data sets.
    - Simplicity: Vectors simplify memory management by using a single memory block, reducing code complexity.
    - Efficient Iteration: Iterating through vectors is efficient for operations involving sequential access in large data sets.
    - Parallelism Support: Vectors can be effectively processed in parallel, enhancing performance with big data.
    - Reduced Risk of Stack Overflow: Vectors avoid stack overflow issues as they do not rely on recursion


## after implemented Vector list

![image](https://github.com/CroosJJSE/Flower_Exchange_Cpp/assets/141708783/fc7cafa8-d3c5-4bda-b787-8d47ced084e7)

### inside output.CSV
![image](https://github.com/CroosJJSE/Flower_Exchange_Cpp/assets/141708783/3d0d6978-c9b1-4233-8029-d256488f3027)

logic of algorithm is ok, but it can be modified to be run faster


