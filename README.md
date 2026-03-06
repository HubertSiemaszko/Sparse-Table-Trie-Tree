# Sparse Table Storage using Custom Trie

This Uni project from DSA class implements a specialized **Trie (Prefix Tree)** designed to store values indexed by sparse keys from a large universe $N$. It serves as an alternative to hash tables, providing a more predictable and better-performing pessimistic (worst-case) time complexity.



## Overview

In this implementation, the Trie is defined by two structural parameters:
* **n**: The number of child nodes linked to the **root**.
* **k**: The number of child nodes for every **subsequent internal node**.

Every node in the tree stores at most one key. This structure is specifically optimized for cases where keys are spread out (sparse) across a large range.

## How It Works

### Insertion & Search
The path for a key $x$ is determined using modulo operations:
1.  **At the Root**: The index is calculated as $idx = x \pmod n$.
2.  **At Internal Nodes**: The index for the next level is calculated as $idx = x \pmod k$ (repeatedly moving deeper).
3.  **Placement**: If the target node is empty, the key is stored. If occupied, the algorithm moves to the next child level based on the calculated index.

### Deletion Strategy
Deleting a key from an internal node requires restructuring to keep the tree valid:
* The algorithm identifies the node $p$ containing the key.
* It searches for a **leaf node candidate** $q$ (a node with no children) using a **"search always to the left"** strategy.
* The value from candidate $q$ is moved to node $p$, and node $q$ is then safely removed.

## Command Interface

The program reads commands from standard input (`stdin`). The first few lines of input define the number of commands and the tree parameters ($n, k$).

| Command | Action | Description |
| :--- | :--- | :--- |
| `I <key>` | **Insert** | Adds the key to the tree if it doesn't already exist. |
| `D <key>` | **Delete** | Removes the key and reorganizes the tree using the leaf-replacement strategy. |
| `L <key>` | **Lookup** | Checks if the key exists and prints the status. |
| `P` | **Print** | Performs an **Inorder Traversal** and prints all keys currently in the tree. |

### Example input

```
5 0 100 3 2
I 10
I 20
L 10
P
D 10
```
