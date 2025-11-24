// Include gtk
#include <gtk/gtk.h>
#include "miniaudio.h"
#include <stdlib.h>
#include <printf.h>

struct config {
    char* image_name;
};

static void on_activate ( GtkApplication *app, void* user_data ) {
    struct config* conf = (struct config*)user_data;
    GError* err;
	// Create a new window
	GtkWidget* window = gtk_application_window_new( app );
    GdkPixbuf* imgbuf = gdk_pixbuf_new_from_file( conf->image_name, err );
    if ( err ) {
        imgbuf = gdk_pixbuf_new_from_file( "geese.jpg", err );
        if ( err ) {
            printf( "oh no" );
            return;
        }
    }
    GtkWidget* image = gtk_image_new_from_pixbuf( imgbuf );
    gtk_container_add( GTK_WINDOW( window ), image );
	gtk_window_present( GTK_WINDOW( window ) );
}

int main ( int argc, char** argv ) {
    // We don't have to free this--I just don't want it to
    // disappear in case main returns.
    struct config* conf = malloc( sizeof( struct config ) );
    conf->image_name = "geese.jpg";

    ma_result result;
    ma_engine engine;

    if (argc < 2) {
        printf("No input file.");
        return -1;
    }

    result = ma_engine_init(NULL, &engine);
    if ( result != MA_SUCCESS ) {
        printf( "Failed to initialize audio engine." );
        return -1;
    }

    ma_engine_play_sound( &engine, "geese.wav", NULL );

	// Create a new GTK application
	GtkApplication* app = gtk_application_new(
            "com.example.GtkApplication", G_APPLICATION_FLAGS_NONE );
	g_signal_connect( app, "activate", G_CALLBACK( on_activate ), conf );
	return g_application_run( G_APPLICATION( app ), argc, argv );
}

