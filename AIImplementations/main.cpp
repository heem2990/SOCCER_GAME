#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include <vector> 
#include "Constants.h"
#include "SoccerGame.h"

using namespace std;

int main( void )
{
   // initializing ALLEGRO's diplay,  event_queue ,and timer. 
   ALLEGRO_DISPLAY * display = NULL;
   ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
   ALLEGRO_TIMER *timer = NULL;

   double timeKeeper = 0.0;
   bool done = false;
   
   if( !al_init() )
   {
      al_show_native_message_box(NULL, NULL, NULL,"FAILED TO INITIALIZE",NULL,NULL);
      return -1;
   }

   al_init_image_addon();
   display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );

   if( !display )
   {
      al_show_native_message_box(NULL, NULL, NULL,"FAILED TO INITIALIZE",NULL,NULL);
       return -1;
   }

   // Initializing , keyboard, primitives and fonts. 
   al_init_primitives_addon();
   al_install_keyboard();
   al_init_font_addon();
	al_init_ttf_addon();

   // Creating the timer for 1/60 seconds so that we can get an update 60 times a second = 60F PS
   timer = al_create_timer( 1.0 / 60.0  );
   eventQueue = al_create_event_queue();

   // Registering timer events, so that the update  loop can be called 60 times a seconds, and registering events for keyboard inputs. 
   al_register_event_source( eventQueue, al_get_timer_event_source( timer ) );
   al_register_event_source( eventQueue, al_get_keyboard_event_source() );
   al_start_timer( timer );

   //***********************
   SoccerGame::initRegions();
   SoccerGame* mainSoccerGame = new SoccerGame();
   
   ALLEGRO_BITMAP* pitch = al_load_bitmap( "soccerPitch.png" );
   //***********************
   int i = 0;
   //timeKeeper = GetCurrentTime();
   // WIP. 
   while( !done )
   {
     al_clear_to_color(al_map_rgb(0,0,0));
     mainSoccerGame->update();

	  ALLEGRO_EVENT ev;
	  al_wait_for_event( eventQueue, &ev );
      
     al_flip_display();
   }

   al_destroy_event_queue( eventQueue );
   al_destroy_display(display);
   
   return 0;
}