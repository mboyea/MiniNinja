#include <SDL.h>
#include "Audio.h"
#include "Files.h"
#include "Log.h"
#include <unordered_map>

static std::unordered_map<std::string, Mix_Chunk*> audios;

void InitAudio(std::string filePathDefault, int rate, uint16_t format, int channels, int buffers) {
	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(rate, format, channels, buffers) < 0) {
		Log("Unable to open audio: " + Mix_GetError()), WARNING);
	}
}

bool LoadAudio(std::string filePath) {
	if (!DoesPathExist(filePath)) {
		Log("File \"" + filePath + "\" does not exist.", WARNING);
		Log("Audio load failed.", FAULT);
		return false;
	}
	Mix_Chunk* audio = Mix_LoadWAV(filePath);
	if (audio == nullptr) {
		Log("Audio unable to load: " + (std::string)Mix_GetError(), WARNING);
		return false;
	}
	audios[GetFileName(filePath)] = audio;
	return true;
}

void LoadAudioFromDirectory(std::string folderPath) {
	std::set<std::string> files = GetFilesWithExtension(GetFilesInDirectory(folderPath), "mp3");
	for (std::string file : files) {
		LoadAudio(file);
	}
}

bool UnloadAudio(std::string key) {
	if (IsAudio(key)) {
		delete audios[key];
		audios.erase(key);
		return true;
	}
	return false;
}

void UnloadAllAudio() {
	for (std::pair<std::string, SDL_Texture*> audio : audios) {
		SDL_DestroyTexture(audio.second);
	}
	audios.clear();
}

bool IsAudio(std::string key) {
	return audios.find(key) != audios.end();
}

Mix_Chunk* GetAudio(std::string key) {
	if (IsAudio(key)) {
		return audios[key];
	}
	return nullptr;
}

std::string GetKey(Mix_Chunk* audio) {
	for (auto it = audios.begin(); it != audios.end(); it++) {
		if (it->second == audio) {
			return it->first;
		}
	}
	return "";
}

void PlayAudio(Mix_Chunk* audio) {
	Mix_PlayChannel(-1, audio, 0);
}

void PlayAudio(std::string key) {
	if (IsAudio(key)) {
		PlayAudio(audios[key]);
	}
}