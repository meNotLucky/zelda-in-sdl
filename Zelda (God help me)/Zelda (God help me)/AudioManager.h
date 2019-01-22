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

// TODO: Implement Music (Mix_Music, Mix_LoadMUS)
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