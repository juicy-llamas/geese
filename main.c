//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

#define sdlerr( stuff ) do {                                \
    printf( stuff " SDL Error: %s\n", SDL_GetError() );     \
    return 1;                                               \
} while( 0 );

int main ( int argc, char** argv ) {
    printf( "yep it is doing something\n" );

    SDL_Window* window = 0;
    SDL_Surface* screenSurface, image;
    SDL_Event e;
    
    // sound
    SDL_AudioSpec s_want, s_have;
    SDL_AudioDeviceID s_dev;
    Uint32 s_len;
    Uint8* s_buf;

    // sdl init
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        sdlerr( "SDL could not initialize!" );
    
    // window init
    window = SDL_CreateWindow( "geese", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_SHOWN );

    if ( window == 0 )
        sdlerr( "Window couldn't start." );

    // image load
    image = IMG_Load( "~/.local/share/geese/geese.jpg" );

    if ( image == 0 )
        sdlerr( "Image didn't load." );

    // put the img on the window
    screenSurface = SDL_GetWindowSurface( window );
    
    SDL_FillRect( screenSurface, 0, SDL_MapRGB( screenSurface->format,
            0xFF, 0x00, 0xFF ) );
    
    SDL_UpdateWindowSurface( window );

    // load audio
    
    SDL_memset( &s_want
    if ( SDL_LoadWAV( "~/.local/share/geese/geese.wav", &s_want, &s_buf, 
                &s_len ) )
        sdlerr( "Wav didn't load." );

    s_dev = SDL_OpenAudioDevice( 0, 0, &s_want, &s_have, 
            SDL_ALLOW_AUDIO_FORMAT_CHANGE );
    
    if ( s_dev == 0 )
        sdlerr( "Failed to get audio device." );

    if ( SDL_QueueAudio( s_dev, s_buf, s_len ) < 0 )
        sdlerr( "Failed to queue audio." );

    // SDL_Delay( 42000 );
    while ( 1 ) {
        if ( SDL_PollEvent( &e ) && e.type == SDL_QUIT )
            break;
    }

    SDL_FreeWAV( s_buf );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
