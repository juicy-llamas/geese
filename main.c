// Include gtk
#define MINIAUDIO_IMPLEMENTATION
#define GNU_SOURCE

#include <gtk/gtk.h>
#include "gio/gio.h"
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
  GtkWindow* realwind = GTK_WINDOW( window );
  GtkWidget* image = gtk_picture_new_for_filename( conf->image_name );
  gtk_window_set_child( realwind, image );
  gtk_window_set_focus( realwind, image );
  gtk_widget_activate( image );
  gtk_window_present( realwind );
}

int main ( int argc, char** argv ) {
  // We don't have to free this--I just don't want it to
  // disappear in case main returns.
  struct config* conf = malloc( sizeof( struct config ) );
  conf->image_name = "geese.jpg";

  // Create a new GTK application
	GtkApplication* app = gtk_application_new(
            "com.example.GtkApplication", G_APPLICATION_DEFAULT_FLAGS );
	g_signal_connect( app, "activate", G_CALLBACK( on_activate ), conf );

  ma_result result;
  ma_engine engine;

  result = ma_engine_init(NULL, &engine);
  if ( result != MA_SUCCESS ) {
    printf( "Failed to initialize audio engine." );
    return -1;
  }

  ma_engine_play_sound( &engine, "geese.wav", NULL );

	int ret = g_application_run( G_APPLICATION( app ), argc, argv );

  return ret;
}

