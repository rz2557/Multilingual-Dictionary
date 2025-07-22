# include <iostream>
# include "hashtable.h"
# include <fstream>
# include <sstream>
# include <cctype>
using namespace std;


// Constructor for the Translation class with initialization of meanings and language
Translation :: Translation(string meanings,string language)
{
    // Initialize language of translation
    this->language = language;

    // Initialize variables to parse meanings string
    size_t pos = 0, nextPos = 0;

    // Loop through the string to extract each meaning separated by a semicolon
    while ((nextPos = meanings.find(';', pos)) != string::npos) 
    {
        string part = meanings.substr(pos, nextPos - pos);

        // Add the extracted meaning if it is not already present
        if (!part.empty() && find(this->meanings.begin(), this->meanings.end(), part) == this->meanings.end()) 
        {
            this->meanings.push_back(part);
        }
        pos = nextPos + 1;
    }

    // Handle the last part of meanings after the final semicolon
    if (pos < meanings.size()) 
    {
        string lastPart = meanings.substr(pos);
        if (!lastPart.empty() && find(this->meanings.begin(), this->meanings.end(), lastPart) == this->meanings.end()) 
        {
            this->meanings.push_back(lastPart);
        }
    }
}


// Method to add new meanings to an existing Translation object
void Translation :: addMeaning(const string newMeanings) 
{
    // Check if the new meanings string matches any existing meanings
    for (size_t i = 0; i < meanings.size(); ++i)
    {
        if (newMeanings == meanings[i])
        {
            return; // Return without adding if already present
        }
    }

    // Parse and add each new unique meaning from newMeanings
    size_t pos = 0, nextPos = 0;
    while ((nextPos = newMeanings.find(';', pos)) != string::npos) 
    {
        string part = newMeanings.substr(pos, nextPos - pos);
        if (!part.empty() && find(meanings.begin(), meanings.end(), part) == meanings.end())
        {
            meanings.push_back(part);
        }
        pos = nextPos + 1;
    }

    // Handle the last part of newMeanings after the final semicolon
    if (pos < newMeanings.size()) 
    {
        string lastPart = newMeanings.substr(pos);
        if (!lastPart.empty() && find(meanings.begin(), meanings.end(), lastPart) == meanings.end())
        {
            meanings.push_back(lastPart);
        }
    }
}

// Display method for the Translation class
void Translation :: display()
{
    // Check if there are any meanings to display
    if(!(this->meanings.empty()))
    {
        cout<<this->language<<" "<<":"<<" ";

        // Print each meaning followed by a semicolon, except the last one
        for(int i = 0 ; i < meanings.size() -1; i++)
        {
            cout<<this->meanings[i]<<"; ";
        }
        // Print the last meaning without a trailing semicolon
        cout<<this->meanings[meanings.size()-1]<<endl;
    }
}


// Constructor for the Entry class to initialize word, meanings, and language
Entry :: Entry(string word, string meanings,string language)
{
    // Initialize word
    this->word = word;

    // Create a Translation object and add it to translations vector
    Translation T1(meanings,language);
    translations.push_back(T1);

    // Initialize deleted flag as false
    this->deleted = false;
}



// Add a new translation to the existing Entry object
void Entry :: addTranslation(string newMeanings, string language)
{
    bool found = false;
    for(int i = 0; i < this->translations.size(); i++)
    {
        // Check if the translation already exists for the given language
        if(this->translations[i].language == language)
        {
            // Add new meanings to the existing translation
            this->translations[i].addMeaning(newMeanings);
            found = true;
            break;
        }
    }

    // If no existing translation found, create a new one and add it
    if(!found)
    {
        Translation T1(newMeanings,language);
        this->translations.push_back(T1);  
    }
}

// Print method for the Entry class
void Entry :: print()
{
    // Check if there are any translations to display
    if(!(this->translations.empty()))
    {
        for(int i = 0; i<this->translations.size(); i++)
        {
            this->translations[i].display();
        }
    }
}


// Constructor for the HashTable class with specified capacity
HashTable :: HashTable(int capacity)
{
    // Allocate memory for the buckets array with the specified capacity
    buckets = new Entry*[capacity];
    for(int i=0; i<capacity; i++)
        buckets[i] = nullptr;

    // Initialize hash table properties
    this->capacity = capacity;
    this->size = 0;
    this->collisions = 0;
}



 unsigned long HashTable :: hashCode(string word)
{
    const unsigned long base = 37; // Use 37 as the base for the polynomial hash function
    const unsigned long mod = 1e9 + 9; // Use a large prime number as modulus to minimize hash collisions
    unsigned long hashValue = 0; // Initialize hash value to 0


    for (int i = 0; i < word.length(); i++) // Iterate through each character in the key
     {
        hashValue = (hashValue * base + word[i]) % mod; // Polynomial accumulation of the hash value
    }
    return hashValue % this->capacity; // Return the computed hash code
}




// // Compute the hash code of a word and return the index
// unsigned long HashTable::hashCode(string word)
// {
//     unsigned long h = 5381; // Initialize the hash value

//     for (int i = 0; i < word.length(); i++) // Loop through the characters of the word
//     {
//         h = ((h << 5) + h) + word[i]; // Update the hash value
//     }

//     return h % this->capacity; // Return the computed index
// }






// unsigned long HashTable :: hashCode(string word)
// {
//     unsigned int hashvalue = 0; // assumed to be 4 bytes = 32 bits


//      for (int i = 0; i < word.length(); ++i)
//     {
//         hashvalue = (hashvalue << 5) | (hashvalue >> 27); // 5-bit cyclic shift
//         hashvalue += (unsigned int) word[i]; // add in next character
//     }
//     return ((int) hashvalue ) % this->capacity;
// }





// Get method to return the current size of the hash table
unsigned int HashTable :: getSize()
{
    return this->size; // Return the number of elements currently stored in the hash table
}



// Get method to return the number of collisions that occurred during insertions
unsigned int HashTable :: getCollisions()
{
    return this->collisions;
}



// Method to import data from a file into the hash table
void HashTable :: import(string path)
{
    ifstream my_file(path);
    if (my_file.is_open())
    {
        string language;
        string word_line;
        string word;
        string meanings;
        int counter = 0;

        getline(my_file,language);
        while(getline(my_file,word_line))
        {
            stringstream buffer_name(word_line);
            getline(buffer_name,word,':');
            getline(buffer_name,meanings);
            counter++;
            insert(word,meanings,language);
        }
        cout<<counter<<" "<< language<<" words have been imported successfully "<<endl;
        my_file.close();
    }
    else
    {
        cout<<"file could not open";
    }
}




// Method to insert a new word along with its meanings and language into the hash table
void HashTable :: insert(string word, string meanings,string language) 
{
    string words = "";
    for (int i = 0; i < word.length(); i++)
    { // Convert the word to lowercase
            char c = word[i];  
            words += tolower(c);
        }
        word = words;

    if (this->size == this->capacity) // Check if the hash table is full
    {
        cout << "The hash table is full, no additional records can be added!" << endl;
        return; // Exit if the table is full to prevent overfilling
    }

    unsigned int index  = hashCode(word); 
    
    for (int i = 0; i < this->capacity; i++) // Probe up to the size of the hash table
    {
       
        if (i > 0) // Increment collision count only if we are not at the first probe position
        {
            this->collisions++;
        } 

        int probe_index = (index + (i * i)) % this->capacity; // Calculate the probe index
        if (buckets[probe_index] == nullptr || buckets[probe_index]->deleted) // Check if the bucket is empty or previously deleted
        {
            if (buckets[probe_index] == nullptr) // If the bucket is empty
            { 
                buckets[probe_index] = new Entry(word, meanings,language); // Create a new entry at the probe index
            } 
            else
            { // If the bucket was deleted
                delete  this->buckets[probe_index];
                buckets[probe_index] = new Entry(word, meanings,language); // Create a new entry at the probe index
            }
            this->size++; // Increment the size of the hash table
            return; // Exit after inserting
        } 
        
        else if (buckets[probe_index]->word == word) // If the key already exists in the hash table
        {
            buckets[probe_index]->addTranslation(meanings,language); // Update the value
            return; // Exit after updating
        }
    }
}



// Method to remove a translation of a specific word and language from the hash table
void HashTable :: delTranslation(string word, string language)
{
     if(word.empty() || language.empty())
    {
        cout<<"invalid input"<<endl;
        return;
    }

     string words = "";
    for (int i = 0; i < word.length(); i++)
    { // Convert the word to lowercase
            char c = word[i];  
            words += tolower(c);
        }
        word = words;

    unsigned int index  = hashCode(word); 
  

    for (int i = 0; i < this->capacity; i++) // Probe up to the size of the hash table
    {
        int probe_index = (index + (i * i)) % this->capacity; // Calculate the probe index
        if (buckets[probe_index] == nullptr) // If the bucket is empty
        {
            cout << word << " is not found" << endl; // Key not found
            return; // Exit as key cannot be found in an empty slot
        }

        if (!buckets[probe_index]->deleted && buckets[probe_index]->word == word) // If the key is found and not marked as deleted
        {
            for(int j = 0; j< buckets[probe_index]->translations.size(); j++)
            {
                if(buckets[probe_index]->translations[j].language == language)
                {
                   buckets[probe_index]->translations.erase(buckets[probe_index]->translations.begin() + j);

                   if(buckets[probe_index]->translations.empty())
                   {
                     buckets[probe_index]->deleted = true;
                   }
                   break;
                }
            }
            cout << "translations has been successfully removed from the dictionary!" << endl; // Confirm removal
            return; // Exit after removing
        }
    }
    cout << language << " is not found" << endl; // language not found after full probing
}




// Method to delete a specific word from the hash table
void HashTable :: delWord(string word)
{
    if(word.empty())
    {
        cout<<"Word not found!"<<endl;
        return;
    }

     string words = "";
    for (int i = 0; i < word.length(); i++){ // Convert the word to lowercase
            char c = word[i];  
            words += tolower(c);
        }
        word = words;

    unsigned int index = hashCode(word); 
 

    for (int i = 0; i < this->capacity; i++) // Probe up to the size of the hash table
    {
        int probe_index = (index + (i*i)) % this->capacity; // Calculate the probe index
        if (buckets[probe_index] == nullptr) // If the bucket is empty
        {
            cout << word << " not found in the Dictionary." << endl; // Key not found
            return; // Exit as key cannot be found in an empty slot
        }
        if (!buckets[probe_index]->deleted && buckets[probe_index]->word == word) // If the key is found and not marked as deleted
        {
            buckets[probe_index]->deleted = true; // Mark the entry as deleted
            this->size--; // Decrement the size of the hash table
            cout << word << " has been successfully deleted from the Dictionary." << endl; // Confirm removal
            return; // Exit after removing
        }
    }
    cout << word << " not found in the Dictionary." << endl; // Key not found after full probing
}





// Method to delete a specific meaning of a specific word and language from the hash table
void HashTable :: delMeaning(string word, string meaning, string language)
{
    if(meaning.empty() || word.empty() || language.empty()) // check if the input is empty
    {
        cout<<"invalid input"<<endl; // display the error message
        return;
    }
    
     string words = "";
    for (int i = 0; i < word.length(); i++)
    { // Convert the word to lowercase
            char c = word[i];  
            words += tolower(c);
        }
        word = words;

    unsigned int index = hashCode(word); // Compute the hash code for the key

    for (int i = 0; i < this->capacity; i++) // Probe up to the size of the hash table
    {
        int probe_index = (index + (i*i)) % this->capacity; // Calculate the probe index
        if (buckets[probe_index] == nullptr) // If the bucket is empty
        {
            cout << word << " not found" << endl; // Key not found
            return; // Exit as key cannot be found in an empty slot
        }

        if (!buckets[probe_index]->deleted && buckets[probe_index]->word == word) // If the key is found and not marked as deleted
        {
            for(int j = 0; j < buckets[probe_index]->translations.size(); j++)
            {
                if(buckets[probe_index]->translations[j].language == language)
                {
                    for(int k = 0; k < buckets[probe_index]->translations[j].meanings.size(); k++)
                    {
                        if(buckets[probe_index]->translations[j].meanings[k] == meaning)
                        {
                            buckets[probe_index]->translations[j].meanings.erase(buckets[probe_index]->translations[j].meanings.begin() + k);

                            if (buckets[index]->translations[j].meanings.empty()) 
                            {
                                buckets[index]->translations.erase(buckets[index]->translations.begin()+j);// Remove the translation if the meanings vector is empty
                            }
                            cout<< "meaning has been successfully deleted from the Translation!" << endl; // Confirm removal
                            return;
                        }
                    } 
                    cout << "word/Meaning not found.!" << endl; 
                    return; 
                }
            }
            cout << "language not found.!"<<endl;
            return;
        }
    }  
}



// Method to add a new word with translations to the dictionary if it does not already exist
void HashTable :: addWord(string word, string meanings, string language)
{
    if(meanings.empty() || word.empty() || language.empty()) // check if the input is empty
    {
        cout<<"invalid input"<<endl;
        return;
    }

     string words = "";
    for (int i = 0; i < word.length(); i++)
    { // Convert the word to lowercase
            char c = word[i];  
            words += tolower(c);
        }
        word = words;

    bool wordExists = false;

    unsigned int index = hashCode(word); 

    for (int i = 0; i < this->capacity; i++) // Probe up to the size of the hash table
    {
        int probe_index = (index + (i*i)) % this->capacity; // Calculate the probe index
        if (buckets[probe_index] == nullptr) // If the bucket is empty
        {
           break;
        }

        if (!buckets[probe_index]->deleted && buckets[probe_index]->word == word) // If the key is found and not marked as deleted
        {
          wordExists = true;
        }
    }

    if (!wordExists) 
    {
        cout << "New word has been added to the dictionary." << endl;
    }
    // add the word
    insert(word, meanings, language);
}



// Method to find a word in the dictionary and print its details
void HashTable :: find(string word)
{
    if(word.empty()) // check if the input is empty
    {
        cout<<"invalid input"<<endl; // display the error message
        return;
    }

     string words = "";
    for (int i = 0; i < word.length(); i++)
    { // Convert the word to lowercase
            char c = word[i];  
            words += tolower(c);
        }
        word = words;

    unsigned int index = hashCode(word); 


    for (int i = 0; i < this->capacity; i++) // Probe up to the size of the hash table
    {
        int probe_index = (index + (i*i)) % this->capacity; // Calculate the probe index
        if (buckets[probe_index] == nullptr) // If the bucket is empty
        {
            cout<< word << " not found in the Dictionary."<<endl;
            return;
        }
        if (!buckets[probe_index]->deleted && buckets[probe_index]->word == word) // If the key is found and not marked as deleted
        {
        cout<< word<<" found in the Dictionary after " << to_string(i + 1)<<" Comparisons."<<endl ;
        buckets[probe_index]->print();
        return;
        }
    }
    cout<< word << " not found in the Dictionary."<<endl; 
}



// Method to export dictionary data to a file based on the specified language
void HashTable::exportData(string language, string filePath) 
{
    if( language.empty() || filePath.empty()) // check if the input is empty
    {
        cout<<"invalid input"<<endl; // display the error message
        return;
    }

    ofstream my_file(filePath);
    if (my_file.is_open())
     {
        int counter = 0;
        my_file << language << endl;
        for (int i = 0; i < this->capacity; i++) 
        {
            if (buckets[i] != nullptr && !buckets[i]->deleted) 
            {  // Check for non-null and not deleted
                counter++;
                my_file << buckets[i]->word << ":";
                for (int j = 0; j < buckets[i]->translations.size(); j++) 
                {
                    if (buckets[i]->translations[j].language == language)
                     {
                        for (int k = 0; k < buckets[i]->translations[j].meanings.size(); k++) 
                        {
                            my_file << buckets[i]->translations[j].meanings[k];
                            if (k < buckets[i]->translations[j].meanings.size() - 1) 
                            {
                                my_file << ";";
                            }
                        }
                        my_file << endl;
                    }
                }
            }
        }
        cout << counter << " records have been successfully exported to " << filePath << endl;
        my_file.close();
    } 
    else
     {
        cout << "file could not export" << endl;
    }
}



// Destructor for the HashTable class to deallocate memory
HashTable :: ~HashTable()
{
for(int i = 0; i < this->capacity; i++)
{
    if(buckets[i] != NULL)
    
    {
    delete this->buckets[i];
    }
}
delete [] this->buckets;
}




















	

	
	
	
	
		
	
		
		
		















 















