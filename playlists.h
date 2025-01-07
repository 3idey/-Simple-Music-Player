#define MAX_PLAYLISTS 100  // تعريف الحد الأقصى للقوائم
#include <iostream>
#include "playlist.h"
#include "DLL.h"
using namespace std;

class playlists
{
private:
    int playlistCount;

    DLL<playlist> allPlaylists;

public:
    playlists()
    {
        playlistCount = 0;
    }
    ~playlists()
    {
        allPlaylists.clear();
    }

    Node<playlist>* gethead()
    {
        return allPlaylists.gethead(); // Assuming head is a pointer to the first node in DLL.
    }
    void addplaylist(const playlist& Playlist)
    {
        if (playlistCount < MAX_PLAYLISTS)
        {
            allPlaylists.insertAtEnd(Playlist);
            playlistCount++;
            cout << "Playlist \"" << Playlist.getName() << "\" added successfully.\n";

        }
        else
        {
            cout << "Cannot add more playlists. Maximum limit reached!" << endl;
        }
    }

    void updatePlaylist(const string& name, const playlist& newPlaylist)
    {
        Node<playlist>* current = allPlaylists.gethead();
        while (current != nullptr)
        {
            if (current->data.getplaylistname() == name)
            {
                current->data = newPlaylist;
                cout << "Playlist updated successfully..\n";
                return;
            }
            current = current->next;
        }
        cout << "Playlist not found.\n";
    }

    bool removePlaylist(const string& name)
    {
        if (allPlaylists.gethead() == nullptr)
        {
            cout << "No playlists available!" << endl;
            return false;
        }

        // Search for the playlist by name to find its position
        Node<playlist>* temp = allPlaylists.gethead();
        int position = 1; // Start counting positions from 1
        while (temp != nullptr)
        {
            if (temp->data.getName() == name)
            {
                break;
            }
            temp = temp->next;
            position++;
        }

        if (temp == nullptr)
        {
            cout << "Playlist not found!" << endl;
            return false;
        }

        // Delete the playlist at the identified position
        allPlaylists.deleteAtSpecificPos(position);

        return true;
    }

    int getSize()
    {
        return playlistCount; // استرجاع عدد القوائم
    }



    bool isEmpty()
    {
        return getSize() == 0;
    }

    playlist* findPlaylist(const string& playlistName)
    {
        Node<playlist>* current = allPlaylists.gethead();
        while (current != nullptr)
        {
            if (current->data.getplaylistname() == playlistName)
            {
                return &current->data;  // إرجاع العنصر الذي تم العثور عليه
            }
            current = current->next;
        }
        return nullptr;  // إذا لم يتم العثور على القائمة
    }
    void displayPlaylists()
    {
        if (isEmpty())
        {
            cout << "No playlists available.\n";
            return;
        }
        Node<playlist>* current = allPlaylists.gethead();
        int id =1;
        cout << "The current playlists are:\n";
        while (current != nullptr)
        {
            cout << id << "    " << current->data.getName() << endl;
            current = current->next;
            id++;
        }
    }


};
