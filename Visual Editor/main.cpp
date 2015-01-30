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

#define LOG allegroLog					//The name of log in program
#define LOGSTRING "allegroLog"			//The name of log in .txt file

//Color code
#define RED   255,0,0
#define GREEN 0,255,0
#define BLUE  0,0,255
#define BLACK 0,0,0
#define WHITE 255,255,255

const bool DISPLAYMODEFULL = false;		//Determine here whether display mode will be full or not		

const char * title = "Visual Editor 0.0.0.8";		//Major.Minor.Bug.Commit#
const double FPS = 24;								//Frames per second

//Window resolution (16:9)
const int windowWidth = 640;
const int windowHeight = 360;

ofstream LOG;			//Keep track of which function and pointer succeeded or failed

//Everything above main must be constant (except ofstream)

//NOTE: if pixel dimension is less than one it will not show

int main(int argc, char ** argv)
{
	
	//Macro LOGSTRING expands and automatically concatenate with .txt string
	LOG.open(LOGSTRING".txt");		//Open init log file
	



#pragma region al_init al_install output to .txt file

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

#pragma endregion



	bool keyPressed[ALLEGRO_KEY_MAX];

	//Assign to each pressed key the initial value of false
	for (int keyPosition = 0; keyPosition < ALLEGRO_KEY_MAX; keyPosition++)
	{
		keyPressed[keyPosition] = false;
	}

	bool redraw = true;




	ALLEGRO_DISPLAY * window;
	
	ALLEGRO_BITMAP * icon = NULL; //al_load_bitmap("image/1.png");		//Choose what image to use for icon


#pragma region Display_Mode_And_Window_Config
	
	//If display mode full is true
	if (DISPLAYMODEFULL)
	{
		//The monitor information will be stored in the displayData structure
		ALLEGRO_DISPLAY_MODE displayData;

		//displayData populated by al_get_display_mode() with monitor display information
		//
		//al_get_num_display_modes() return the total number of display modes (or resolutions)
		// that the monitor is able to handle, then subtract 1 to get the last index
		//
		al_get_display_mode(al_get_num_display_modes()-1, &displayData);

		//Set to display in full screen
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);

		//Create display
		//Everything on screen will depend on displayData.width and displayData.height when
		// in full screen mode
		window = al_create_display(displayData.width, displayData.height);
	}

	//Else display in lowest resolution
	else
	{
		//Create display
		window = al_create_display(windowWidth, windowHeight);
	}
	
#pragma endregion


#pragma region window output to .txt file

	if (window)
	{
		LOG << "display success\n";
	}
	else
	{
		LOG << "display failed\n";

		return -1;
	}

#pragma endregion




	//Create event queue
	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();

#pragma region event_queue output to .txt file

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

#pragma endregion


	//Create timer
	ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);

#pragma region timer output to .txt file

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

#pragma endregion


	//Close log file
	LOG.close();






	//Register the display's events in our event queue so as to fetch the events later
	al_register_event_source(event_queue, al_get_display_event_source(window));

	//Register the timer's events in our event queue so as to fetch the events later
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//Register the keyboard's events in our event queue so as to fetch the events later
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	





	//Set title of application
	al_set_window_title(window,  title);

	//Set window icon after changing icon from NULL to valid image
	//al_set_display_icon(window,icon)

	//Clear bitmap and set to black
	al_clear_to_color(al_map_rgb(0,0,0));

	//Update screen
	al_flip_display();

	//Start the timer
	al_start_timer(timer);


	
	
	
	bool continueLoop = true;
	
#pragma region Main_Loop
	
	////////////////////main loop/////////////////////////
	while (continueLoop)
	{
		////////////////////Define section///////////////////
		
		static class Cursor
		{
			float width;
			float height;
			float x1;
			float y1;
			float x2;
			float y2;
			
		public:
			Cursor (float x1value, float y1value, float widthValue, float heightValue)
			{
				width = windowWidth/640*widthValue;
				height = windowHeight/360*heightValue;
				x1 = windowWidth/640*x1value;
				y1 = windowHeight/360*y1value;
				x2 = x1+width;
				y2 = y1;
			}

			//Default position
			Cursor ()
			{
				width = windowWidth/640*8;
				height = windowHeight/360*3;
				x1 = 0;
				y1 = 0;
				x2 = x1+width;
				y2 = y1;
			}

			void setx1y1(float x1value, float y1value)
			{
				x1 = windowWidth/640*x1value;
				y1 = windowHeight/360*y1value;
				x2 = x1+width;
				y2 = y1;
			}

			void setWidth(float widthValue)
			{
				width = widthValue;
			}

			void setHeight(float heightValue)
			{
				height = heightValue;
			}

			float getWidth()
			{
				return width;
			}

			float getHeight()
			{
				return height;
			}

			float getx1()
			{
				return x1;
			}

			float gety1()
			{
				return y1;
			}

			float getx2()
			{
				return x2;
			}

			float gety2()
			{
				return y2;
			}
		};

		static ALLEGRO_COLOR  cursorPixelColor;								//To be passed to al_map_rgb
		static Cursor cursor (16,16,16,6);										//(x1,y1,width,height)


		static ALLEGRO_EVENT  ev;						//Short for event
		
		//////////////////End Define section/////////////////

		//Wait for event in the event queue to fire then assign to ev thus removing from the event queue
		al_wait_for_event(event_queue, &ev);

		//If the event is a timer event, trigger a redraw and process game logic
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			//The number of times the clock ticked
			static int tickNumber = 0;

			//Everytime the clock ticks increase the tick number by one
			tickNumber++;

			///////////////////////////////////Game Logic////////////////////////////////////////////
			
			//After 12 out of 24 ticks the underscore will be black
			if (tickNumber == 12)
			{
				cursorPixelColor = al_map_rgb(BLACK);
			}

			//After 24 out of 24 ticks the underscore will be green
			//If the tick number is 30 assign it the value 0 and the underscore will be green
			if (tickNumber == 24)
			{
				cursorPixelColor = al_map_rgb(GREEN);
				
				tickNumber = 0;
			}

			//If key pressed is 'a'
			if (keyPressed[ALLEGRO_KEY_A])
			{
				cursor.setx1y1(cursor.getx1()-cursor.getWidth(), cursor.gety1());
			}

			//If key pressed is 's'
			if (keyPressed[ALLEGRO_KEY_S])
			{
				cursor.setx1y1(cursor.getx1(), cursor.gety1()+cursor.getHeight());
			}

			//If key pressed is 's'
			if (keyPressed[ALLEGRO_KEY_D])
			{
				cursor.setx1y1(cursor.getx1()+cursor.getWidth(), cursor.gety1());
			}

			//If key pressed is 's'
			if (keyPressed[ALLEGRO_KEY_W])
			{
				cursor.setx1y1(cursor.getx1(), cursor.gety1()-cursor.getHeight());
			}

			/////////////////////////////////End Game Logic//////////////////////////////////////////
		
		}

		//Else if the event is to close window, break out of loop (user clicked the x button)
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			continueLoop = false;
		}

		//Else if the event is any key down
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			
			//If event is key 'a' down
			case ALLEGRO_KEY_A:

				keyPressed[ev.keyboard.keycode] = true;

				break;
			
			//If event is key 's' down
			case ALLEGRO_KEY_S:

				keyPressed[ev.keyboard.keycode] = true;

				break;
			
			//If event is key 'd' down
			case ALLEGRO_KEY_D:
				
				keyPressed[ev.keyboard.keycode] = true;

				break;

			//If event is key 'w' down
			case ALLEGRO_KEY_W:

				keyPressed[ev.keyboard.keycode] = true;

				break;
			}

			
			
		}

		//Else if the event is any key up
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
				//If event is key 'esc' up
				case ALLEGRO_KEY_ESCAPE:

					//Application closes
					continueLoop = false;

					break;
				//If event is key 'a' up
				case ALLEGRO_KEY_A:

					keyPressed[ev.keyboard.keycode] = false;

					break;

				//If event is key 's' up
				case ALLEGRO_KEY_S:

					keyPressed[ev.keyboard.keycode] = false;

					break;
			
				//If event is key 'd' up
				case ALLEGRO_KEY_D:
				
					keyPressed[ev.keyboard.keycode] = false;

					break;

				//If event is key 'w' up
				case ALLEGRO_KEY_W:

					keyPressed[ev.keyboard.keycode] = false;

					break;
			}

		}
		
		//After checking all events in the queue and redraw is true
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//Clear bitmap and set to black
			al_clear_to_color(al_map_rgb(BLACK));

			///////////////Game Visuals (Everything is redrawn below this line)///////////////

			//Draw cursor to screen
			al_draw_line(cursor.getx1(), cursor.gety1(), cursor.getx2(), cursor.gety2(), cursorPixelColor, cursor.getHeight());

			

			/////////////////////////////////End Game Visuals/////////////////////////////////

			//Update screen
			al_flip_display();
		}
	}

#pragma endregion

	
	
	
	
	
	
	
	

	//Stops current thread here for a number of second(s)
	//al_rest(4.0);

	al_destroy_timer(timer);
	al_destroy_display(window);
	al_destroy_event_queue(event_queue);


	return 0;
}