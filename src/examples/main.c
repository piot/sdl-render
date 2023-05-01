/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include "sdl-render/font.h"
#include "sdl-render/gamepad.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <clog/console.h>
#include <sdl-render/sprite.h>
#include <sdl-render/window.h>

clog_config g_clog;

typedef struct ExampleRenderer {
    SrTextTexture helloWorldText;
    SrSprites spriteRenderer;
    SrSprite avatarSprite;
    SrFont font;
    int i;
} ExampleRenderer;

static void render(void *_self, SrWindow *window) {
    ExampleRenderer *renderer = (ExampleRenderer *) _self;

    float scale = (1.0 + sinf(renderer->i / 40.0f)) * 2 + 0.5f;
    srSpritesCopyEx(&renderer->spriteRenderer, &renderer->avatarSprite, renderer->i, 100, renderer->i * 5, scale, 0xff);

    srTextTextureRender(&renderer->helloWorldText, 10, 10);

    SDL_Colour color;
    color.a = SDL_ALPHA_OPAQUE;
    color.r = renderer->i % 0xff;
    color.g = 0xff;
    color.b = 0xff;

    char buf[32];
    snprintf(buf, 32, "dynamic: %d", renderer->i);

    srFontRenderAndCopy(&renderer->font, buf, 10, 40, color);
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

    srFontInit(&exampleRenderer.font, window.renderer, "data/mouldy.ttf", 8);

    SDL_Colour color;
    color.a = SDL_ALPHA_OPAQUE;
    color.r = 0xff;
    color.g = 0xff;
    color.b = 0xff;

    SrTextTexture textTexture = srFontRender(&exampleRenderer.font, "Hello World", color);

    exampleRenderer.helloWorldText = textTexture;
    srSpritesInit(&exampleRenderer.spriteRenderer, window.renderer);
    exampleRenderer.avatarSprite.rect.x = 0;
    exampleRenderer.avatarSprite.rect.y = 0;
    exampleRenderer.avatarSprite.rect.w = 22;
    exampleRenderer.avatarSprite.rect.h = 32;
    exampleRenderer.avatarSprite.texture = charactersTexture;

    SrGamepad gamepads[1];

    srGamepadInit(&gamepads[0]);

    for (size_t i = 0; i < 300; ++i) {
        exampleRenderer.i = (int) i;

        srWindowRender(&window, 0xfe00fe, &exampleRenderer, render);

        int wantsToQuit = srGamepadPoll(gamepads, 1);
        if (wantsToQuit) {
            break;
        }
    }

    srFontDestroy(&exampleRenderer.font);
    srWindowClose(&window);
}
