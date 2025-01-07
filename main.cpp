#include <iostream>
#include "playlists.h"
#include "playlist.h"
#include "DLL.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <fstream>
#include <sstream>
using namespace std;

void addNewPlaylist(playlists& allPlaylists)
{
    string name;
    cout << "Enter playlist name: ";
    cin.ignore();
    getline(cin, name);

    allPlaylists.addplaylist(playlist(name));

}

void addShurahToPlaylist(playlists& allPlaylists)
{
    allPlaylists.displayPlaylists();
    if(allPlaylists.isEmpty())
    {
        return;
    }
    string playlistName;
    cout << "Enter playlist name: ";
    cin.ignore();
    getline(cin, playlistName);

    playlist* selectedPlaylist = allPlaylists.findPlaylist(playlistName);
    if (selectedPlaylist == nullptr)
    {
        cout << "Playlist not found.\n";
        return;
    }

    char addMore;
    do
    {
        string surahName, surahType, surahPath;
        cout << "Enter surah name: ";
        getline(cin, surahName);
        cout << "Enter surah type: ";
        getline(cin, surahType);
        cout << "Enter surah path: ";
        getline(cin, surahPath);

        selectedPlaylist->addsurah(surah(surahName, surahType, surahPath));

        cout << "Add another surah to the current list? Press (y/n): ";
        cin >> addMore;
        cin.ignore();
    }
    while (tolower(addMore) == 'y');

    cout << "Surahs added successfully to playlist \"" << playlistName << "\".\n";
}

void displayAllPlaylists(playlists& allPlaylists)
{
    cout << "+===================================+" << endl;
    cout << "|       Current Playlists           |" << endl;
    cout << "+===================================+" << endl;

    allPlaylists.displayPlaylists();

    cout << "+===================================+" << endl;
}

void displayAllPlaylistsSurahs(playlists& allPlaylists)
{
    if (allPlaylists.getSize() == 0)
    {
        cout << "No playlists available.\n";
        return;
    }

    Node<playlist>* currentPlaylist = allPlaylists.gethead();
    while (currentPlaylist != nullptr)
    {
        cout << "-------------------------------------------------------------" << endl;
        cout << "                        Playlist: " << currentPlaylist->data.getName() << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "ID        Surah               Type                       Path" << endl;
        cout << "-------------------------------------------------------------" << endl;

        Node<surah>* currentSurah = currentPlaylist->data.getSurahList().gethead(); // Assuming `getSurahList()` returns the DLL of surahs.
        int id = 1;

        while (currentSurah != nullptr)
        {
            cout << id << "          ";
            currentSurah->data.display();
            currentSurah = currentSurah->next;
            id++;
        }

        cout << "--------------------------------------------------------" << endl;

        currentPlaylist = currentPlaylist->next;
    }
}

void displaySpecificPlaylist(playlists& allPlaylists)
{
    allPlaylists.displayPlaylists();
    if(allPlaylists.isEmpty())
    {
        return;
    }

    string playlistName;
    cout << "\nEnter playlist name: ";
    cin.ignore();
    getline(cin, playlistName);

    playlist* selectedPlaylist = allPlaylists.findPlaylist(playlistName);
    if (selectedPlaylist == nullptr)
    {
        cout << "Playlist not found.\n";
        return;
    }


    cout << "\nPlaylist: " << selectedPlaylist->getName() << endl;
    cout << "--------------------------------------------------------\n";
    cout << "ID       Surah              Type                      Path\n";
    cout << "--------------------------------------------------------\n";

    DLL<surah>& surahList = selectedPlaylist->getSurahList();
    Node<surah>* currentSurah = surahList.getHead();
    int surahId = 1;

    while (currentSurah != nullptr)
    {
        cout << surahId << "        ";
        currentSurah->data.display();
        surahId++;
        currentSurah = currentSurah->next;
    }

    cout << "--------------------------------------------------------\n";
}


void updateSurahOrder(playlists& allPlaylists)
{

    allPlaylists.displayPlaylists();
    if(allPlaylists.isEmpty())
    {
        return;
    }
    string playlistName;
    cout << "Enter playlist name: ";
    cin.ignore();
    getline(cin, playlistName);

    playlist* selectedPlaylist = allPlaylists.findPlaylist(playlistName);
    if (selectedPlaylist == nullptr)
    {
        cout << "Playlist not found.\n";
        return;
    }


    cout << "Playlist: " << selectedPlaylist->getName() << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "ID       Surah              Type                      Path" << endl;
    cout << "--------------------------------------------------------" << endl;

    DLL<surah>& surahList = selectedPlaylist->getSurahList();
    Node<surah>* currentSurah = surahList.getHead();
    int id = 1;

    while (currentSurah != nullptr)
    {
        cout << id << "        ";
        currentSurah->data.display();
        currentSurah = currentSurah->next;
        id++;
    }

    cout << "--------------------------------------------------------" << endl;


    int surahId, newPosition;
    cout << "Enter the ID of the surah to move: ";
    cin >> surahId;

    if (surahId < 1 || surahId > surahList.getSize())
    {
        cout << "Invalid Surah ID.\n";
        return;
    }


    cout << "Enter new position: ";
    cin >> newPosition;


    if (newPosition < 1 || newPosition > surahList.getSize())
    {
        cout << "Invalid position.\n";
        return;
    }


    Node<surah>* selectedSurahNode = surahList.getNodeAt(surahId);
    if (selectedSurahNode == nullptr)
    {
        cout << "Surah not found.\n";
        return;
    }


    surah surahToMove = selectedSurahNode->data;
    surahList.deleteAtSpecificPos(surahId);


    surahList.insertAtGivenPos(surahToMove, newPosition);


    cout << "Surah \"" << surahToMove.getname() << "\" moved to position " << newPosition << ".\n";
}

void displayMenu()
{
    cout << "+=======================================================================+" << endl;
    cout << "|                       Quran Playlist Manager Menu                     |" << endl;
    cout << "========================================================================" << endl;
    cout << "| 1.  Add a new playlist                                                |" << endl;
    cout << "| 2   Add Surah to an existing playlist                                 |" << endl;
    cout << "| 3.  Remove Shurah from an existing playlist                           |" << endl;
    cout << "| 4.  Update the order of existing playlist                             |" << endl;
    cout << "| 5.  Display All Current Playlists                                     |" << endl;
    cout << "| 6.  Display all Playlists Surah                                       |" << endl;
    cout << "| 7.  Display All Surahs in a specific playlist                         |" << endl;
    cout << "| 8.  Play Surah from specific playlist                                 |" << endl;
    cout << "|     Use left arrow (<-) to play the previous surah                    |" << endl;
    cout << "|     Use right arrow (->) to play the next surah                       |" << endl;
    cout << "|     Use up arrow (^) to pause the current surah                       |" << endl;
    cout << "|     Use down arrow (v) to resume the current surah                    |" << endl;
    cout << "|     Press q to exit current playlist & return back to menu            |" << endl;
    cout << "| 9.  Save a  playlist to a file                                        |" << endl;
    cout << "| 10. Load an existing The playlists from a file                        |" << endl;
    cout << "| 11. Remove an existing playlist                                       |" << endl;
    cout << "| 12. Exit                                                              |" << endl;
    cout << "+=======================================================================+" << endl;
}

void removeSurahFromPlaylist(playlists& allPlaylists)
{


    cout<<"-------------------\n";
    allPlaylists.displayPlaylists();
    cout<<"-------------------\n";
    if (allPlaylists.isEmpty())
    {
        return;
    }

    string playlistName;
    cout << "Enter playlist name: ";
    cin.ignore();
    getline(cin, playlistName);

    playlist* selectedPlaylist = allPlaylists.findPlaylist(playlistName);  // البحث عن البلاي ليست
    if (selectedPlaylist == nullptr)
    {
        cout << "Playlist not found.\n";
        return;
    }


    cout << "Surahs in \"" << playlistName << "\":\n";
    DLL<surah>& surahList = selectedPlaylist->getSurahList();
    Node<surah>* currentSurah = surahList.getHead();
    int surahId = 1;

    cout << "ID   Surah\n";
    cout << "-------------\n";
    while (currentSurah != nullptr)
    {
        cout << surahId << "    " << currentSurah->data.getname() << endl;
        currentSurah = currentSurah->next;
        surahId++;
    }


    int surahToDelete;
    cout << "Enter the ID of the surah to remove: ";
    cin >> surahToDelete;

    if (surahToDelete < 1 || surahToDelete > surahList.getSize())
    {
        cout << "Invalid surah ID.\n";
        return;
    }


    string removedSurahName = surahList.getNodeAt(surahToDelete)->data.getname();
    surahList.deleteAtSpecificPos(surahToDelete);

    cout << "Surah \"" << removedSurahName << "\" removed from playlist \"" << playlistName << "\".\n";
}


void saveToFile(playlists& allPlaylists)
{

    allPlaylists.displayPlaylists();
    if(allPlaylists.isEmpty())
    {
        return;
    }
    string playlistName;
    cout << "Enter playlist name to save: ";
    cin.ignore();
    getline(cin, playlistName);


    playlist* selectedPlaylist = allPlaylists.findPlaylist(playlistName);
    if (selectedPlaylist == nullptr)
    {
        cout << "Playlist not found.\n";
        return;
    }

    // فتح ملف لحفظ البلاي ليست
    ofstream file("playlists.txt", ios::app);  // فتح الملف في وضع الإضافة (append)
    if (!file)
    {
        cout << "Error opening file.\n";
        return;
    }


    file << "Playlist: " << selectedPlaylist->getName() << endl;
    file << "--------------------------------------------------------" << endl;

    DLL<surah>& surahList = selectedPlaylist->getSurahList();
    Node<surah>* currentSurah = surahList.getHead();
    int idSurah = 1;

    while (currentSurah != nullptr)
    {
        file << idSurah << " "
             << currentSurah->data.getname() << " "
             << currentSurah->data.gettype() << " "
             << currentSurah->data.getaudiopath() << endl;
        currentSurah = currentSurah->next;
        idSurah++;
    }

    file << "--------------------------------------------------------" << endl;
    file.close();
    cout << "Playlist \"" << selectedPlaylist->getName() << "\" saved to playlists.txt\n";
}

void loadFromFile(playlists& allPlaylists)
{
    ifstream file("playlists.txt");
    if (!file)
    {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    playlist* currentplaylist = nullptr; // Pointer to the current playlist

    while (getline(file, line))
    {
        if (line.find("Playlist: ") == 0)
        {
            string playlistName = line.substr(10); // Extract playlist name
            allPlaylists.addplaylist(playlistName);
            currentplaylist = allPlaylists.findPlaylist(playlistName);
            if (!currentplaylist)
            {
                cout << "Error: Playlist not found after creation.\n";
                continue;
            }
        }
        else if (line.find("--------------------------------------------------------") != string::npos)
        {
            continue; // Skip separator lines
        }
        else
        {
            if (!currentplaylist)
            {
                cout << "Error: No playlist found to add Surah.\n";
                continue;
            }

            stringstream ss(line);
            string id, surahName, surahType, surahPath;

            getline(ss, id, ' ');          // Read ID (ignored here)
            getline(ss, surahName, ' ');  // Read Surah name
            getline(ss, surahType, ' ');  // Read Surah type
            getline(ss, surahPath);       // Read Surah path

            currentplaylist->addsurah(surah(surahName, surahType, surahPath));
        }
    }

    file.close();  // إغلاق الملف
    cout << "Playlists loaded from playlists.txt\n";
}



void removePlaylist(playlists& allPlaylists)
{


    cout << "----------------\n";
    allPlaylists.displayPlaylists();
    cout << "----------------\n";
    if (allPlaylists.getSize() == 0)
    {
        return;
    }

    string playlistName;
    cout << "Enter playlist name to remove: ";
    cin.ignore();
    getline(cin, playlistName);


    bool removed =allPlaylists.removePlaylist(playlistName);



    if (removed)
    {
        cout << "Removed playlist \"" << playlistName << "\" successfully.\n";
    }
    else
    {
        cout << "Error removing playlist.\n";
    }
}
void playsurah(playlists& allPlaylists)
{

    cout << "----------------\n";
    allPlaylists.displayPlaylists();
    cout << "----------------\n";
    if (allPlaylists.isEmpty())
    {
        return;
    }
    string playlistName;
    cout << "Enter playlist : ";
    cin.ignore();
    getline(cin, playlistName);
    playlist* selectedPlaylist = allPlaylists.findPlaylist(playlistName);
    if (selectedPlaylist == nullptr)
    {
        cout << "Playlist not found.\n";
        return;
    }

    cout << "Playlist: " << selectedPlaylist->getName() << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "ID       Surah              Type                      Path" << endl;
    cout << "--------------------------------------------------------" << endl;

    DLL<surah>& surahList = selectedPlaylist->getSurahList();
    Node<surah>* currentSurah = surahList.getHead();
    int id = 1;

    while (currentSurah != nullptr)
    {
        cout << id << "        ";
        currentSurah->data.display();
        currentSurah = currentSurah->next;
        id++;
    }
    cout << "--------------------------------------------------------" << endl;
    string surahname;
    cout<<"Enter surah  ";

    getline(cin, surahname);

    selectedPlaylist->playsurah(surahname);
}

int main()
{
    playlists allPlaylists;  // إنشاء الكائن
    int choice;

    while (true)
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addNewPlaylist(allPlaylists);
            break;
        case 2:
            addShurahToPlaylist(allPlaylists);
            break;
        case 3:
            removeSurahFromPlaylist(allPlaylists);
            break;
        case 4:
            updateSurahOrder(allPlaylists);
            break;
        case 5:
            displayAllPlaylists(allPlaylists);
            break;
        case 6:
            displayAllPlaylistsSurahs(allPlaylists);
            break;
        case 7:
            displaySpecificPlaylist(allPlaylists);
            break;
        case 8:
            playsurah(allPlaylists);
            break;
        case 9:
            saveToFile(allPlaylists);
            break;
        case 10:
            loadFromFile(allPlaylists);
            break;
        case 11:
            removePlaylist(allPlaylists);
            break;
        case 12:
            cout << "Exiting...\n";
            return 0;

        }
    }

    return 0;
}
