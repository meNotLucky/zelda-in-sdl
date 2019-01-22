#include "AudioManager.h"
#include "ErrorLogger.h"
#include "Service.h"

// SOUND

Sound::Sound(Mix_Chunk * p_chunk)
{
	m_chunk = p_chunk;
}

void Sound::play_sound(int p_loops)
{
	m_channel = Mix_PlayChannel(-1, m_chunk, p_loops);
	if (m_channel == -1) {
		Service<ErrorLogger>::Get()->log_error("_Mix", Mix_GetError());
	}
}

void Sound::stop_sound()
{
	Mix_HaltChannel(m_channel);
}

Music::Music(Mix_Music * p_music)
{
	m_music = p_music;
}

// MUSIC

void Music::play_music(int p_loops)
{
	if (Mix_PlayMusic(m_music, p_loops) == -1) {
		Service<ErrorLogger>::Get()->log_error("Mix", Mix_GetError());
	}
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	for (Sound* sound : m_sounds) {
		delete sound;
		sound = nullptr;
	}
	m_sounds.clear();

	for (auto pair : m_chunks) {
		Mix_FreeChunk(pair.second);
		pair.second = nullptr;
	}
	m_chunks.clear();
}

// SOUND MANAGER

Sound * AudioManager::create_sound(const char * p_path)
{
	auto it = m_chunks.find(p_path);
	if (it == m_chunks.end()) {

		Mix_Chunk* chunk = Mix_LoadWAV(p_path);
		if (chunk == nullptr) {
			Service<ErrorLogger>::Get()->log_error("_Mix", Mix_GetError());
			return nullptr;
		}
		m_chunks[p_path] = chunk;
		Sound* sound = new Sound(chunk);
		m_sounds.push_back(sound);
		return sound;
	}
	else {
		Sound* sound = new Sound(m_chunks[p_path]);
		m_sounds.push_back(sound);
		return sound;
	}
}

Music * AudioManager::create_music(const char * p_path)
{
	auto it = m_tracks.find(p_path);
	if (it == m_tracks.end()) {

		Mix_Music* track = Mix_LoadMUS(p_path);
		if (track == nullptr) {
			Service<ErrorLogger>::Get()->log_error("_Mix", Mix_GetError());
			return nullptr;
		}
		m_tracks[p_path] = track;
		Music* music = new Music(track);
		m_music.push_back(music);
		return music;
	}
	else {
		Music* music = new Music(m_tracks[p_path]);
		m_music.push_back(music);
		return music;
	}
}

void AudioManager::stop_music()
{
	Mix_HaltMusic();
}
