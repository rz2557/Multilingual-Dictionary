# Multilingual Dictionary using a Hash Table

A C++ command-line dictionary that stores words, meanings and translations in multiple languages in a custom hash table with quadratic probing.

## Features

- **Hash-table lookup:** insertion, deletion and search in average constant time, using a polynomial rolling hash.
- **Multilingual entries:** a word can have translations in several languages, and each translation can have several meanings (separated by semicolons).
- **Custom implementation:** `HashTable`, `Entry` and `Translation` classes written from scratch, with quadratic probing for collision resolution.
- **File I/O:** import dictionaries from text files (for example English-German or English-French) and export one language's translations to a file.

## Project structure

```
.
├── hashtable.cpp / hashtable.h   # Hash table and dictionary entry logic
├── main.cpp                      # Command-line interface
└── makefile                      # Build instructions
```

## Build and run

```bash
git clone https://github.com/rz2557/Multilingual-Dictionary.git
cd Multilingual-Dictionary
make
./main
```

## Commands

| Command | Description |
|---|---|
| `find <word>` | Look up a word and show its translations |
| `import <filename>` | Import a dictionary file |
| `add <word,meanings,language>` | Add a word or meanings (separate meanings with `;`) |
| `delTranslation <word,language>` | Delete a translation in one language |
| `delMeaning <word,meaning,language>` | Delete one meaning |
| `delWord <word>` | Remove a word and all its translations |
| `export <language,filename>` | Export the dictionary for one language |
| `help` | List commands |
| `exit` | Quit |

## Dictionary file format

The first line is the target language, followed by one `word:meaning1;meaning2` entry per line. Example `en-de.txt`:

```
German
book:Buch
apple:Apfel;Apfelsine
```

Save it next to the executable and run `import en-de.txt`, then `find book`.

## Design notes

- Table capacity: 1,171,891 slots.
- Collisions are resolved with quadratic probing, and collision counts are tracked while building the table.
