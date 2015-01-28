#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_native_dialog.h>
#include <fstream>

using namespace std;

#define ALLEGRO_PI	3.14159265358979323846

#define LOG allegroLog							//Change name of log when applicable (third position)
#define LOGSTRING "allegroLog"					//Change name of string log when applicable (third position)

const char * title = "Visual Editor 0.1.0.3";		//Major.Minor.Bug.Commit#
const double FPS = 30;								//Frames per second

ofstream LOG;			//Keep track of which function and pointer succeeded or failed

int main(int argc, char ** argv)
{
	
	
	LOG.open(LOGSTRING".txt");		//Open init log file
	






	if (al_init())
	{
		LOG << "al_init() success\n";
	}
	else
	{
		LOG << "al_init() failed\n";

		return -1;
	}

	
	if (al_init_acodec_addon())
	{
		LOG << "al_init_acodec_addon() success\n";
	}
	else
	{
		LOG << "al_init_acodec_addon() failed\n";

		return -1;
	}


	al_init_font_addon();


	if (al_init_image_addon())
	{
		LOG << "al_init_image_addon() success\n";
	}
	else
	{
		LOG << "al_init_image_addon() failed\n";

		return -1;
	}


	if (al_init_native_dialog_addon())
	{
		LOG << "al_init_native_dialog_addon() success\n";
	}
	else
	{
		LOG << "al_init_native_dialog_addon() failed\n";

		return -1;
	}


	if (al_init_primitives_addon())
	{
		LOG << "al_init_primitives_addon() success\n";
	}
	else
	{
		LOG << "al_init_primitives_addon() failed\n";

		return -1;
	}


	if (al_init_ttf_addon())
	{
		LOG << "al_init_ttf_addon() success\n";
	}
	else
	{
		LOG << "al_init_ttf_addon() failed\n";

		return -1;
	}


	if (al_install_keyboard())
	{
		LOG << "al_install_keyboard() success\n";
	}
	else
	{
		LOG << "al_install_keyboard() failed\n";

		return -1;
	}


	if (al_install_mouse())
	{
		LOG << "al_install_mouse() success\n";
	}
	else
	{
		LOG << "al_install_mouse() failed\n";

		return -1;
	}











	//Window resolution
	int windowWidth = 640;
	int windowHeight = 480;

	bool redraw = true;



	//Create display
	ALLEGRO_DISPLAY * window = al_create_display(windowWidth, windowHeight);

	if (window)
	{
		LOG << "display success\n";
	}
	else
	{
		LOG << "display failed\n";

		return -1;
	}




	//Create event queue
	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();

	if (event_queue)
	{
		LOG << "event_queue success\n";
	}
	else
	{
		LOG << "event_queue failed\n";

		al_destroy_display(window);		//Destroy display

		return -1;
	}




	//Create timer
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);

	if (timer)
	{
		LOG << "timer success\n";
	}
	else
	{
		LOG << "timer failed\n";

		al_destroy_event_queue(event_queue);	//Destroy event_queue
		al_destroy_display(window);				//Destroy display

		return -1;
	}



	//Close log file
	LOG.close();





	//Register the display's events in our event queue so as to fetch the events later
	al_register_event_source(event_queue, al_get_display_event_source(window));

	//Register the timer's events in our event queue so as to fetch the events later
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	





	//Set title of application
	al_set_window_title(window,  title);

	//Clear bitmap and set to black
	al_clear_to_color(al_map_rgb(0,0,0));

	//Update screen
	al_flip_display();

	//Start the timer
	al_start_timer(timer);



	
	
	
	
	
	
	////////////////main loop/////////////////
	while (true)
	{
		ALLEGRO_EVENT ev;			//Short for event

		//Wait for event in the event queue to fire then assign to ev thus removing from the event queue
		al_wait_for_event(event_queue, &ev);

		//If the event is a timer event, trigger a redraw
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			//Game Logic goes here
		}

		//If the event is to close window, break out of loop (user clicked the x button)
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}

		//
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//Clear bitmap and set to black
			al_clear_to_color(al_map_rgb(0,0,0));

			//Update screen
			al_flip_display();
		}
	}

	

	
	
	
	
	
	
	
	

	//Stops current thread here for a number of second(s)
	//al_rest(4.0);

	al_destroy_timer(timer);
	al_destroy_display(window);
	al_destroy_event_queue(event_queue);


	return 0;
}