/*

AUDIO MANAGER

The Audio Manager, much like the Sprite Manager, is used to store and re-use loaded files. In this case audio files.
It uses the SDL Chunks to store sound snippets and SDL Music to store music.

It was created to make sure all audio files just had to be loaded once, and then could be re-used whenever.

*/

#pragma once

#include <map>
#include <vector>
#include <SDL_mixer.h>

class Sound {

	Mix_Chunk* m_chunk;
	int m_channel;

public:
	Sound(Mix_Chunk* p_chunk);
	void play_sound(int p_loops);
	void stop_sound();
};

class Music {

	Mix_Music* m_music;

public:
	Music(Mix_Music* p_music);
	void play_music(int p_loops);
};

class AudioManager {
	std::map<const char*, Mix_Chunk*> m_chunks;
	std::map<const char*, Mix_Music*> m_tracks;
	std::vector<Sound*> m_sounds;
	std::vector<Music*> m_music;
public:
	AudioManager();
	~AudioManager();
	Sound* create_sound(const char* p_path);
	Music* create_music(const char* p_path);
	void stop_music();
};