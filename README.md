# Multilingual Dictionary using Hash Table

A **C++ command-line multilingual dictionary** that uses an efficient **hash table with quadratic probing** to manage and retrieve words, their meanings, and translations in multiple languages.

---

## **Features**
- **Hash Table Based Lookup**  
  - Supports insertion, deletion, and search in average constant time using a polynomial rolling hash.

- **Multilingual Support**  
  - Words can have multiple translations in different languages.
  - Each translation can have multiple meanings (separated by semicolons).

- **Custom Data Structures**  
  - Custom `HashTable` implementation with `Entry` and `Translation` classes.
  - Efficient memory use and fast access using quadratic probing.

- **File I/O Support**  
  - Import dictionaries from text files (e.g., English-German, English-French).
  - Export translations for a specific language into a structured file format.

---

## **Project Structure**
```
.
├── hashtable.cpp / hashtable.h   # Core logic for dictionary entries and hash table
├── main.cpp                      # Command-line interface and main loop
├── makefile                      # Build instructions
```

---

## **Commands**

| Command                          | Description |
|----------------------------------|-------------|
| `find <word>`                    | Search for a word and display its translations |
| `import <filename>`              | Import a dictionary file |
| `add <word,meanings,language>`   | Add a word or meanings (use `;` to separate meanings) |
| `delTranslation <word,language>` | Delete a translation in a specific language |
| `delMeaning <word,meaning,language>` | Delete a specific meaning |
| `delWord <word>`                 | Remove a word and all its translations |
| `export <language,filename>`     | Export dictionary for a given language |
| `help`                           | Show list of available commands |
| `exit`                           | Exit the application |

---

## **Installation & Usage**

### **1. Clone the Repository**
```bash
git clone https://github.com/<your-username>/Multilingual-HashDictionary.git
cd Multilingual-HashDictionary
```

### **2. Compile**
```bash
make
```

### **3. Run**
```bash
./main
```

---

## **Dictionary File Format**

Each file starts with the **language** on the first line, followed by:
```
word1:meaning1;meaning2
word2:meaning1;meaning2;meaning3
```

Example (`en-de.txt`):
```
German
book:Buch
apple:Apfel;Apfelsine
```

---

## **Performance**
- Capacity: 1,171,891 entries
- Hash collisions tracked and minimized using a robust hashing method
- Quadratic probing for efficient collision resolution

---
