GAT150: 2D Platformer Game

GAT150 is a 2D side-scrolling platformer game developed using C++ and the Gaia game engine. The game features dynamic scenes, physics-based interactions, and a variety of actors such as players, enemies, and collectibles.

🎮 Game Overview

Genre: 2D Platformer

Engine: Gaia (C++ Framework)

Current Features:

Player movement and interactions

Enemy AI and spawning

Collectibles and scoring system

Scene management and transitions

Audio integration (music and sound effects)

🛠️ Setup Instructions
Prerequisites

C++17 or later

Gaia game engine (included in the project)

Visual Studio 2019 or later (Windows)

SFML
 for windowing and graphics

OpenAL
 for audio playback

Building the Project

Clone this repository:

git clone https://github.com/Rin-coder69/GAT150.git


Open the solution file GAT150.sln in Visual Studio.

Build the solution (press Ctrl+Shift+B).

Run the project (press F5).

🎵 Adding Audio

To integrate background music or sound effects:

Place your .wav files in the Assets/Audio directory.

In your game code, load and play the audio using Gaia's audio system:

gaia::Audio::Play("Assets/Audio/background_music.wav");


Ensure that audio playback is initialized in your game's setup routine.

🧩 Game Structure

Scenes: Located in the Assets/Scenes directory.

Actors: Defined in JSON files within the Assets/Actors directory.

Textures: Stored in the Assets/Textures directory.

Audio: Managed through the Assets/Audio directory.


🧪 Contributors
https://github.com/Rin-coder69
