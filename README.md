# 🚀 Algorithmic Strategies

## Introduction
In this practice, I will implement two key algorithmic strategies in C for solving the task assignment problem to individuals. This problem will be approached in two versions: with and without the `usadas[]` vector.

## Problem Statement
You are required to test with `n = 3`, as per the exercise solved in class (using the given benefit table), and with a larger `n = 6` using the following benefit tables:

### For `n=3`:
| TASKS | B | 1 | 2 | 3 |
|-------|---|---|---|---|
| **PEOPLE** |   |   |   |
| 1     |    | 11| 17| 8 |
| 2     |    | 9 | 7 | 6 |
| 3     |    |13| 15| 16|

### For `n=6`:
| TASKS | B | 1 | 2 | 3 | 4 | 5 | 6 |
|-------|---|---|---|---|---|---|---|
| **PEOPLE** |   |   |   |   |   |   |
| 1     |    |11| 17| 8 | 16| 20| 14|   
| 2     |    |9 | 7 | 6 | 12| 15| 18|   
| 3     |    |13| 15| 16| 12| 16| 18|   
| 4     |    |21| 24| 28| 17| 26| 20|   
| 5     |    |10| 14| 12| 11| 15| 13|   
| 6     |    |12| 20| 19| 13| 22| 17|


## Part 1: Backtracking Strategy Implementation 🔄
Implement the backtracking algorithm seen in theory, both with and without the `usadas` vector. Use the pseudocode from the class exercise as a reference.

Your program should print the number of nodes generated by the algorithm in each case (those meeting the criteria).

### Deliverables
- The program that solves the problem.
- A report explaining:
  1. The meaning of the components of the `s` vector.
  2. The function that assigns a task to a person.
  3. The purpose of the `MasHermanos()` function.
  4. The objective of the `Retroceder()` function.
  5. Theoretical and practical conclusions about the complexity of the task and the number of steps when using the `usadas` vector.

### Data to be Calculated and Printed
- `n`
- Vector `usadas`
- Number of nodes visited
- Number of steps for criteria, generation, solution, `MasHermanos`, and `Retroceder`.

## Part 2: Branch and Bound Strategy Implementation 🌿✂️
The goal here is to examine the effect of pruning on the number of nodes visited in the implicit solution exploration tree.

### Specifications
- The branching strategy will be MB-LIFO.
- Test both trivial and precise estimates for bounding and compare the differences in pruning effectiveness.

### Deliverables
- The program that solves the problem.
- A report explaining:
  1. Conclusions on the effects of pruning.
  2. Necessary changes for the case of minimization (if matrix B represents costs instead of benefits).

### Data to be Calculated and Printed
Always using the `usadas` vector:
- `N` Number of nodes explored

## How to Run 🏃‍♂️
### Backtracking
First, we have to compile the program:

```
gcc -o backtring mainBacktracking.c Backtring.c
```

After this, we execute it:

```
./backtring
```

### Branch and Bound

First, we have to compile the program:

```
gcc -o brachAndBound mainRamificacion.c RamificacionYPoda.c
```

After this, we execute it:

```
./brachAndBound
```

## 📝 Important Configuration Steps

> **⚠️ IMPORTANT NOTICE:**  
> When switching between different matrix configurations, please follow these steps carefully:
> 1. **Matrix Selection**: If you wish to change the matrix being used, first uncomment the desired matrix code block. Then, make sure to comment out the currently active matrix code block to avoid conflicts.
> 2. **Update Matrix Size**: After selecting the desired matrix, remember to update the matrix size in the `backtracking.h` file accordingly. This step ensures that the program operates with the correct dimensions for your chosen matrix configuration.

Failure to follow these steps may result in incorrect program behavior or compilation errors. Please adjust the settings carefully to match your intended use case.


## Contributors 👥
- Pablo Seijo

## Contact 📩

Pablo Seijo - [@__pabloseijo__](https://twitter.com/_pabloseijo_)

Project Link: [https://github.com/pabloseijo/Algorithmic-Strategies](https://github.com/pabloseijo/Algorithmic-Strategies)

---

Feel free to contribute to this project and suggest improvements! Happy coding! 💻😊
