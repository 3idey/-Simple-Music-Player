# Quran Playlist Manager

The Quran Playlist Manager is a C++ application designed to manage and organize playlists of Quranic surahs. It allows users to create playlists, add or remove surahs, update the order of surahs, and play surahs with basic playback controls.

# Code Structure

DLL.h: Contains the implementation of a doubly linked list used to manage playlists and surahs.

playlist.h: Defines the playlist class, which manages a collection of surahs.

playlists.h: Defines the playlists class, which manages multiple playlists.

main.cpp: The main application logic, including the user interface and menu system.
## Features

- **Create Playlists**: Add new playlists with custom names.
- **Add Surahs**: Add surahs to existing playlists with details like name, type, and audio path.
- **Remove Surahs**: Remove surahs from playlists.
- **Update Order**: Change the order of surahs within a playlist.
- **Play Surahs**: Play surahs with controls for play, pause, next, and previous.
- **Save and Load Playlists**: Save playlists to a file and load them back.
- **Display Playlists**: View all playlists and their surahs.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., GCC, Clang, or MSVC).
- Windows OS (for audio playback using `winmm.lib`).
- Audio must be in WAV format

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/3idey/Simple-Quran-Player.git
