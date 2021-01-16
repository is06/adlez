#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include "game.h"

using namespace std;

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Unable to init SDL" << endl;
    }
    window = SDL_CreateWindow("My Zelda NES",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              960,
                              540,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Unable to create window" << endl;
    }

    graphics = new Graphics(window);
    spriteBatch = new SpriteBatch(window);
    currentMap = new Map(this);

    running = true;
}

void Game::run()
{
    SDL_Event events;

    auto game = Game();
    while (game.running) {
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT) {
                game.running = false;
            }
        }

        game.update();
        game.draw();

        this_thread::yield();
    }
}

void Game::update()
{
    if (currentMap != nullptr) {
        currentMap->update();
    }
}

void Game::draw()
{
    auto color = SDL_Color();
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    graphics->clearFrameBuffer(color);

    if (currentMap != nullptr) {
        currentMap->draw();
    }

    graphics->endRender();
}

void Game::quit()
{
    running = false;
}

Game::~Game()
{
    delete graphics;
    delete spriteBatch;

    SDL_DestroyWindow(window);
    SDL_Quit();
}
