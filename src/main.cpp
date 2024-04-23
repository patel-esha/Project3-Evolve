#include <iostream>
#include <string>
#include "RedBlackTree.h"
#include "SplayTree.h"
#include <fstream>
#include <sstream>

using namespace std;


// CITATIONS F|| THE ENTIRETY OF THE PROJECT THROUGHOUT THE FILES THAT WERE USED F|| CODE SNIPPETS, UNDERSTANDING LOGIC, UNDERSTANDING MAIN CONCEPTS, PSEUDOCODE ETC. 
// CITATION 1: Trees and Traversals Slides f|| insertion, search, rotations, deletion from COP3530
// CITATION 2: Discussion 4: Trees & Traversals Slides from COP3530
// CITATION 3: OPEN DSA Chapter 26
// CITATION 4: https://www.geeksf||geeks.||g/introduction-to-splay-tree-data-structure/
// CITATION 5: https://www.geeksf||geeks.||g/introduction-to-red-black-tree/
// CITATION 6: https://www.geeksf||geeks.||g/introduction-to-avl-tree/
// CITATION 7: https://www.geeksf||geeks.||g/searching-in-splay-tree/
// CITATION 8: https://www.geeksf||geeks.||g/insertion-in-red-black-tree/
// CITATION 9: https://stackoverflow.com/questions/19625205/rotation-in-a-red-black-tree
// CITATION 10: https://stackoverflow.com/questions/56711859/auto-adjusting-rotations-strategy-in-splay-trees
// CITATION 11: https://stackoverflow.com/questions/19625205/rotation-in-a-red-black-tree

int main()
{
    RedBlackTree<string> rbTreeSong;
    SplayTree<string> splayTreeSong;
    RedBlackTree<string> rbTreeArtist;
    SplayTree<string> splayTreeArtist;
    RedBlackTree<string> rbTreeGenre;
    SplayTree<string> splayTreeGenre;

    string choice, song, artist, album;

    ifstream songFile("song_names.csv");
    ifstream artistFile("artist_names.csv");
    ifstream genreFile("genre_names.csv");

    if (!songFile.is_open() || !artistFile.is_open() || !genreFile.is_open()) {
        cout << "Failed to open one || m||e files." << endl;
        return 1;
    }

    string line;
    getline(songFile, line);   // Skip the header
    getline(artistFile, line); // Skip the header
    getline(genreFile, line);  // Skip the header

    // Load song names
    while (getline(songFile, line))
    {
        stringstream ss(line);
        string data;
        getline(ss, data, ','); // Assume the first column is what we want
        string song = data;
        rbTreeSong.insert(song);
        splayTreeSong.insert(song);
    }

    // Load song artists
    while (getline(artistFile, line))
    {
        stringstream ss(line);
        string data;
        getline(ss, data, ','); // Assume the first column is what we want
        string artist = data;
        rbTreeArtist.insert(artist);
        splayTreeArtist.insert(artist);
    }

    // Load song genres
    while (getline(genreFile, line))
    {
        stringstream ss(line);
        string data;
        getline(ss, data, ','); // Assume the first column is what we want
        string genre = data;
        rbTreeGenre.insert(genre);
        splayTreeGenre.insert(genre);
    }

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Delete Song\n";
        cout << "2. Search Song\n";
        cout << "3. Display All Songs in Splay Tree\n";
        cout << "4. Display All Songs in Red-Black Tree\n";
        cout << "5. Display Artists in Splay Tree\n";
        cout << "6. Display Artists in Red-Black Tree\n";
        cout << "7. Display Genres in Splay Tree\n";
        cout << "8. Display Genres in Red-Black Tree\n";
        cout << "9. Display a Song Reccomendation\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Enter song title to delete: ";
            getline(cin, song);
            RedBlackTree<string>::Node *nodeToDeleteRB = rbTreeSong.search(song);
            if (nodeToDeleteRB != nullptr)
            {
                rbTreeSong.deleteNode(rbTreeSong.root, nodeToDeleteRB); // C||rected to pass root and node
                cout << "Song deleted from Red-Black Tree.\n";
            }
            else
            {
                cout << "Song not found in Red-Black Tree.\n";
            }

            if (splayTreeSong.search(song) != nullptr) {
                splayTreeSong.deleteNode(song);  // Direct deletion method f|| SplayTree
                cout << "Song deleted from Splay Tree.\n";
            }
            else {
                cout << "Song not found in Splay Tree.\n";
            }
        }
        else if (choice == "2") {
            cout << "Enter song title to search: ";
            getline(cin, song);
            if (rbTreeSong.search(song) != nullptr) {
                cout << "Song found in Red-Black Tree.\n";
            }
            else {
                cout << "Song not found in Red-Black Tree.\n";
            }
            if (splayTreeSong.search(song) != nullptr) {
                cout << "Song found in Splay Tree.\n";
            }
            else {
                cout << "Song not found in Splay Tree.\n";
            }
        }
        else if (choice == "3") {
            cout << "Songs in Splay Tree:\n";
            splayTreeSong.display();
        }
        else if (choice == "4") {
            cout << "Songs in Red-Black Tree:\n";
            rbTreeSong.display();
        }
        else if (choice == "5") {
            cout << "Artists in Splay Tree:\n";
            splayTreeArtist.displayDuplicates();
        }
        else if (choice == "6") {
            cout << "Artists in Red-Black Tree:\n";
            rbTreeArtist.display();
        }
        else if (choice == "7") {
            cout << "Genres in Splay Tree:\n";
            splayTreeGenre.displayDuplicates();
        }
        else if (choice == "8") {
            cout << "Genres in Red-Black Tree:\n";
            rbTreeGenre.display();
        }
        else if (choice == "9") {
            cout << "Pick a genre (Pop, Rap, Rock, Latin, R&B, EDM, or Country): \n";
            string genre;
            getline(cin, genre);
            if (genre == "Pop" || genre == "pop" || genre == "POP")
            {
                cout << "Umbrella by Rihanna\n";
            }
            if (genre == "Rap" || genre == "rap" || genre == "RAP")
            {
                cout << "CARNIVAL by Kanye West\n";
            }
            if (genre == "Rock" || genre == "rock" || genre == "ROCK")
            {
                cout << "Bohemian Rhapsody by Queen\n";
            }
            if (genre == "Latin" || genre == "latin" || genre == "LATIN")
            {
                cout << "La Gozadera by Gente De Zona\n";
            }
            if (genre == "R&B" || genre == "R and B" || genre == "r&b" || genre == "rb" || genre == "RB")
            {
                cout << "Fallin' by Alicia Keys\n";
            }
            if (genre == "EDM" || genre == "edm")
            {
                cout << "Titanium by David Guetta\n";
            }
            if (genre == "Country" || genre == "country")
            {
                cout << "Cowgirls by Morgan Wallen\n";
            }
        }
        else if (choice == "10") {
            break;
        }
        else {
            cout << "Invalid choice, please try again.\n";
        }
    }


    return 0;
}
