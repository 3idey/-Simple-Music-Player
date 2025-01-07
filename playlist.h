#ifndef PLAYLIST_H
#define PLAYLIST_H
#define byte rpcndr_byte
#include<iostream>
#include <conio.h>
#include "DLL.h"
#include "surah.h"
#include <windows.h>
#include <mmsystem.h>
class playlist
{
private:
    DLL<surah> surahs ;
    string nameplaylist;


public:
    playlist(const string& nameplaylist="")
        :nameplaylist(nameplaylist) {}
     ~playlist()
     {
         surahs.clear();
     }
    string getName() const
    {
        return nameplaylist;
    }
    DLL<surah>& getSurahList()
    {
        return surahs;
    }

    string getplaylistname () const
    {
        return nameplaylist;
    }
    void setplaylistname(const string& nameplaylist)
    {
        this->nameplaylist=nameplaylist;
    }
    void addsurah(const surah& Surah)
    {
        surahs.insertAtEnd(Surah);
    }

    void playsurah(const string& surahname)
    {
        Node<surah>* current = surahs.gethead();
        bool isplaying = false;
        bool ispaused = false;
        string path;

        // Open the audio file using MCI
        while (current != nullptr)
        {
            if (current->data.getname() == surahname)
            {
                path = current->data.getaudiopath();


                // Open the audio file
                string openCommand = "open \"" + path + "\" type waveaudio alias myAudio";
                mciSendString(openCommand.c_str(), NULL, 0, NULL);

                // Play the audio
                mciSendString("play myAudio from 0", NULL, 0, NULL);
                isplaying = true;
                cout << "Playing: " << surahname << endl;

                while (isplaying)
                {
                    if (_kbhit())   // Check if a key is pressed
                    {
                        int key = getch();

                        // Check for special keys (arrows)
                        if (key == 0 || key == 224)
                        {
                            key = getch(); // Get the actual key value (for arrows)

                            if (key == 72)   // Up Arrow key (Pause)
                            {
                                if (!ispaused)
                                {
                                    mciSendString("pause myAudio", NULL, 0, NULL);
                                    ispaused = true;
                                    cout << "Playback paused.\n";
                                }
                                else
                                {
                                    cout << "Audio is already paused.\n";
                                }
                            }
                            else if (key == 80)   // Down Arrow key (Resume)
                            {
                                if (ispaused)
                                {
                                    mciSendString("resume myAudio", NULL, 0, NULL);
                                    ispaused = false;
                                    cout << "Playback resumed.\n";
                                }
                                else
                                {
                                    cout << "Audio is not paused.\n";
                                }
                            }
                            else if (key == 75)   // Left Arrow key (Prev)
                            {
                                if (current->prev != nullptr)
                                {
                                    mciSendString("stop myAudio", NULL, 0, NULL);
                                    mciSendString("close myAudio", NULL, 0, NULL);
                                    current = current->prev;
                                    string surahname2 = current->data.getname();
                                    playsurah(surahname2); // Play previous Surah
                                    return;
                                }
                                else
                                {
                                    cout << "This is the first Surah.\n";
                                }
                            }
                            else if (key == 77)   // Right Arrow key (Next)
                            {
                                if (current->next != nullptr)
                                {
                                    mciSendString("stop myAudio", NULL, 0, NULL);
                                    mciSendString("close myAudio", NULL, 0, NULL);
                                    current = current->next;
                                    string surahname3 = current->data.getname();
                                    playsurah(surahname3); // Play next Surah
                                    return;
                                }
                                else
                                {
                                    cout << "This is the last Surah.\n";
                                }
                            }
                        }

                        // Check for exit key 'q' or 'Q'
                        else if (key == 'q' || key == 'Q')
                        {
                            mciSendString("stop myAudio", NULL, 0, NULL);
                            mciSendString("close myAudio", NULL, 0, NULL);
                            isplaying = false;
                            cout << "Exiting...\n";
                        }
                    }
                }

                // Close the file after playback
                mciSendString("close myAudio", NULL, 0, NULL);
                return;
            }
            current = current->next;
        }

        cout << "Surah not found in playlist!" << endl;
    }





    void displaySurahs() const
    {
        //surahs.traverse();
        Node<surah>* current = surahs.gethead();
        if (!current)
        {
            cout << "Playlist is empty!" << endl;
            return;
        }
        while (current != nullptr)
        {
            current->data.display();
            current = current->next;
        }

    }




};
#endif

