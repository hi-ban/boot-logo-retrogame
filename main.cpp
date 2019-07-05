#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include "assets.h"

//---------------------------------------------------//

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}
	
	SDL_Surface *screen;
	SDL_Surface *logo_brand;
	SDL_Surface *logo;
	SDL_Surface *logo_step1;
	SDL_Surface *logo_step2;
	SDL_Surface *logo_step3;
	SDL_RWops *RWops;
	SDL_RWops *RWops1;
	SDL_RWops *RWops2;
	SDL_RWops *RWops3;
	uint32_t color;

	// init surfaces 
	screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
	SDL_ShowCursor(SDL_DISABLE);
	
	// load logo images
	RWops = SDL_RWFromMem(logo0, sizeof(logo0));
    logo = IMG_LoadPNG_RW(RWops);

	RWops1 = SDL_RWFromMem(step1, sizeof(step1));
    logo_step1 = IMG_LoadPNG_RW(RWops1);

    RWops2 = SDL_RWFromMem(step2, sizeof(step2));
    logo_step2 = IMG_LoadPNG_RW(RWops2);

    RWops3 = SDL_RWFromMem(step3, sizeof(step3));
    logo_step3 = IMG_LoadPNG_RW(RWops3);

	logo_brand = IMG_Load("./brand.png");

    if ((!logo_step1) || (!logo_step2) || (!logo_step3) || (!logo)) {
    	printf("Error loading logo: %s\n", IMG_GetError());
    	return -1;
    }

    // init frame time
	uint32_t curr_time = SDL_GetTicks();
	uint32_t old_time = curr_time;

	if (logo_brand) {
		// brand fade in
		color = SDL_MapRGB(screen->format, 0, 0, 0);
		for (int i = 0; i <= 255; i = i + 8) {
			SDL_FillRect(screen, NULL, color);
			SDL_SetAlpha(logo_brand, SDL_SRCALPHA, i);
			SDL_BlitSurface(logo_brand, NULL, screen, NULL);
			while (curr_time < old_time + 16) {
				curr_time = SDL_GetTicks();
			}
			old_time = curr_time;
			SDL_Flip(screen);
		}

		// display brand
		SDL_SetAlpha(logo_brand, SDL_SRCALPHA, 255);
		SDL_BlitSurface(logo_brand, NULL, screen, NULL);
		while (curr_time < old_time + 16) {
			curr_time = SDL_GetTicks();
		}
		old_time = curr_time;
		SDL_Flip(screen);
		SDL_Delay(1000);

		// brand fade out
		for (int i = 255; i >= 0; i = i - 8) {
			SDL_FillRect(screen, NULL, color);
			SDL_SetAlpha(logo_brand, SDL_SRCALPHA, i);
			SDL_BlitSurface(logo_brand, NULL, screen, NULL);
			while (curr_time < old_time + 16) {
				curr_time = SDL_GetTicks();
			}
			old_time = curr_time;
			SDL_Flip(screen);
		}

		// display nothing
		color = SDL_MapRGB(screen->format, 0, 0, 0);
		SDL_FillRect(screen, NULL, color);
		while (curr_time < old_time + 16) {
			curr_time = SDL_GetTicks();
		}
		old_time = curr_time;
		SDL_Flip(screen);
		SDL_Delay(250);
    } else {
    	printf("Error loading logo: %s\n", IMG_GetError());
    }	

	// step3 fade in
	color = SDL_MapRGB(screen->format, 0, 0, 0);
	for (int i = 0; i <= 255; i = i + 8) {
		SDL_FillRect(screen, NULL, color);
		SDL_SetAlpha(logo_step3, SDL_SRCALPHA, i);
		SDL_BlitSurface(logo_step3, NULL, screen, NULL);
		while (curr_time < old_time + 16) {
			curr_time = SDL_GetTicks();
		}
		old_time = curr_time;
		SDL_Flip(screen);
	}

	// step1 fade in
	SDL_SetAlpha(logo_step3, SDL_SRCALPHA, 255);
	for (int i = 0; i <= 255; i = i + 64) {
		SDL_BlitSurface(logo_step3, NULL, screen, NULL);
		SDL_SetAlpha(logo_step1, SDL_SRCALPHA, i);
		SDL_BlitSurface(logo_step1, NULL, screen, NULL);
		while (curr_time < old_time + 16) {
			curr_time = SDL_GetTicks();
		}
		old_time = curr_time;
		SDL_Flip(screen);
	}

	// step2 fade in
	SDL_SetAlpha(logo_step1, SDL_SRCALPHA, 255);
	for (int i = 0; i <= 255; i = i + 16) {
		SDL_BlitSurface(logo_step1, NULL, screen, NULL);
		SDL_SetAlpha(logo_step2, SDL_SRCALPHA, i);
		SDL_BlitSurface(logo_step2, NULL, screen, NULL);
		while (curr_time < old_time + 16) {
			curr_time = SDL_GetTicks();
		}
		old_time = curr_time;
		SDL_Flip(screen);
	}

	// logo fade in
	SDL_SetAlpha(logo_step2, SDL_SRCALPHA, 255);
	for (int i = 0; i <= 255; i = i + 16) {
		SDL_BlitSurface(logo_step2, NULL, screen, NULL);
		SDL_SetAlpha(logo, SDL_SRCALPHA, i);
		SDL_BlitSurface(logo, NULL, screen, NULL);
		while (curr_time < old_time + 16) {
			curr_time = SDL_GetTicks();
		}
		old_time = curr_time;
		SDL_Flip(screen);
	}

	// display logo
	SDL_SetAlpha(logo, SDL_SRCALPHA, 255);
	SDL_BlitSurface(logo, NULL, screen, NULL);
	while (curr_time < old_time + 16) {
		curr_time = SDL_GetTicks();
	}
	old_time = curr_time;
	SDL_Flip(screen);
	SDL_Delay(1500);

	// logo fade out
	color = SDL_MapRGB(screen->format, 0, 0, 0);
	for (int i = 255; i >= 0; i = i - 8) {
		SDL_FillRect(screen, NULL, color);
		SDL_SetAlpha(logo, SDL_SRCALPHA, i);
		SDL_BlitSurface(logo, NULL, screen, NULL);
		while (curr_time < old_time + 16) {
			curr_time = SDL_GetTicks();
		}
		old_time = curr_time;
		SDL_Flip(screen);
	}

	// display nothing
	SDL_FillRect(screen, NULL, color);
	while (curr_time < old_time + 16) {
		curr_time = SDL_GetTicks();
	}
	old_time = curr_time;
	SDL_Flip(screen);
	SDL_Delay(250);

	// close and exit
	SDL_FreeRW(RWops);
	SDL_FreeRW(RWops1);
	SDL_FreeRW(RWops2);
	SDL_FreeRW(RWops3);
	SDL_FreeSurface(logo_brand);
	SDL_FreeSurface(logo);
	SDL_FreeSurface(logo_step1);
	SDL_FreeSurface(logo_step2);
	SDL_FreeSurface(logo_step3);
	
	SDL_Quit();

	return 0;
}
