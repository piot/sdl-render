/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <sdl-render/window.h>
#include <clog/console.h>
#include <sdl-render/sprite.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

clog_config g_clog;




typedef struct ExampleRenderer {
    SrSprites spriteRenderer;
    SrSprite avatarSprite;
    int i;
} ExampleRenderer;

static void render(void *_self, SrWindow *window) {
    ExampleRenderer *renderer = (ExampleRenderer *) _self;

    float scale = (1.0 + sinf(renderer->i / 40.0f)) * 2 + 0.5f;
    srSpritesCopyEx(&renderer->spriteRenderer, &renderer->avatarSprite, renderer->i, 50, renderer->i * 5, scale);
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    g_clog.log = clog_console;
    CLOG_VERBOSE("example start")

    SrWindow window;
    srWindowInit(&window, 320, 200, "SdlRender Example");

    SDL_Texture *charactersTexture = IMG_LoadTexture(window.renderer, "data/sheet_characters.png");

    ExampleRenderer exampleRenderer;
    exampleRenderer.spriteRenderer.renderer = window.renderer;
    exampleRenderer.avatarSprite.rect.x = 0;
    exampleRenderer.avatarSprite.rect.y = 0;
    exampleRenderer.avatarSprite.rect.w = 22;
    exampleRenderer.avatarSprite.rect.h = 32;
    exampleRenderer.avatarSprite.texture = charactersTexture;

    for (size_t i = 0; i < 300; ++i) {
        exampleRenderer.i = (int) i;

        srWindowRender(&window, 0xfe00fe, &exampleRenderer, render);
        int wantsToQuit = checkSdlEvent();
        if (wantsToQuit) {
            break;
        }
    }

    srWindowClose(&window);
}
