#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include "game.h"
#include "texture.h"

using namespace std;

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Unable to init SDL" << endl;
    }
    m_window = SDL_CreateWindow("My Zelda NES",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              960,
                              540,
                              SDL_WINDOW_SHOWN);
    if (!m_window) {
        cerr << "Unable to create window" << endl;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    m_content = new ContentLoader(m_renderer);
    m_graphics = new Graphics(m_renderer);
    m_sprite_batch = new SpriteBatch(m_renderer);
    m_current_map = new Map(this);
    m_in_game_frame_buffer = new Texture(SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 320, 180));

    running = true;
}

void Game::update()
{
    if (m_current_map != nullptr) {
        m_current_map->update();
    }
}

void Game::draw()
{
    auto color = SDL_Color();
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    m_graphics->set_render_target(m_in_game_frame_buffer);
    m_graphics->clear_frame_buffer(color);
    if (m_current_map != nullptr) {
        m_current_map->draw();
    }

    m_graphics->set_render_target(nullptr);

    m_sprite_batch->begin();
    m_sprite_batch->draw(m_in_game_frame_buffer, Rectangle(0, 0, 320, 180), Rectangle(0, 0, 960, 540));
    m_sprite_batch->end();

    m_graphics->end_render();
}

void Game::quit()
{
    running = false;
}

ContentLoader* Game::content()
{
    return m_content;
}

SpriteBatch* Game::sprite_batch()
{
    return m_sprite_batch;
}

void Game::run()
{
    SDL_Event events;

    Game game = Game();

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

Game::~Game()
{
    delete m_content;
    delete m_graphics;
    delete m_sprite_batch;

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
