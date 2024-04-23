#include <iostream>
#include <string>
#include "RedBlackTree.h"
#include "SplayTree.h"
#include <fstream>
#include <sstream>

using namespace std;

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
        cout << "Failed to open one or more files." << endl;
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
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Enter song title to delete: ";
            getline(cin, song);
              RedBlackTree<string>::Node *nodeToDeleteRB = rbTreeSong.search(song);
            if (nodeToDeleteRB != nullptr)
            {
                rbTreeSong.deleteNode(rbTreeSong.root, nodeToDeleteRB); // Corrected to pass root and node
                cout << "Song deleted from Red-Black Tree.\n";
            }
            else
            {
                cout << "Song not found in Red-Black Tree.\n";
            }

            if (splayTreeSong.search(song) != nullptr) {
                splayTreeSong.deleteNode(song);  // Direct deletion method for SplayTree
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
            break;
        } 
        else {
            cout << "Invalid choice, please try again.\n";
        }
    }


    return 0;
}
