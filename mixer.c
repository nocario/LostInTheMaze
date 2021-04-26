#include <stdio.h>
#include <SDL_mixer.h>
#include "mixer.h"

Mix_Music *musique;
Mix_Music *musique2;
Mix_Music *musique3;
Mix_Music *musique4;
Mix_Music *musique5;
Mix_Music *musique6;

void initMixer() {
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	//musique = Mix_LoadMUS("Day of Fate Spirit VS Spirit Lyric Video (Unmei No Hi English Cover) Team Four Star.mp3");
	//playlist[0] = musique;
	//Mix_PlayMusic(musique, 1);
	musique2 = Mix_LoadMUS("1.mp3");
	playlist[0] = musique2;
	musique3 = Mix_LoadMUS("2.mp3");
	playlist[1] = musique3;
	musique4 = Mix_LoadMUS("3.mp3");
	playlist[2] = musique4;
	musique5 = Mix_LoadMUS("4.mp3");
	playlist[3] = musique5;
	musique6 = Mix_LoadMUS("5.mp3");
	playlist[3] = musique6;
	//musique4 = Mix_LoadMUS("National Anthem of USSR.mp3");
	//playlist[2] = musique4;
	//Mix_PlayMusic(musique2, 1);
}

void freeMusic() {
	//Mix_FreeMusic(musique);
	Mix_FreeMusic(musique2);
	Mix_FreeMusic(musique3);
	Mix_FreeMusic(musique4);
	Mix_FreeMusic(musique5);
	Mix_FreeMusic(musique6);
}