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

ofstream initAllegroFuncLog;			//Keeping track of which init function succeeded or failed
ofstream installAllegroFuncLog;			//Keeping track of which install function succeeded or failed

int main(int argc, char ** argv)
{
	//---------Func logs--------------------------------------------------------------------

	initAllegroFuncLog.open("initAllegroFuncLog.txt");		//Open init log file
	
	if (al_init())
	{
		initAllegroFuncLog << "al_init() success\n";
	}
	else
	{
		initAllegroFuncLog << "al_init() failed\n";
	}

	
	if (al_init_acodec_addon())
	{
		initAllegroFuncLog << "al_init_acodec_addon() success\n";
	}
	else
	{
		initAllegroFuncLog << "al_init_acodec_addon() failed\n";
	}


	al_init_font_addon();


	if (al_init_image_addon())
	{
		initAllegroFuncLog << "al_init_image_addon() success\n";
	}
	else
	{
		initAllegroFuncLog << "al_init_image_addon() failed\n";
	}


	if (al_init_native_dialog_addon())
	{
		initAllegroFuncLog << "al_init_native_dialog_addon() success\n";
	}
	else
	{
		initAllegroFuncLog << "al_init_native_dialog_addon() failed\n";
	}


	if (al_init_primitives_addon())
	{
		initAllegroFuncLog << "al_init_primitives_addon() success\n";
	}
	else
	{
		initAllegroFuncLog << "al_init_primitives_addon() failed\n";
	}


	if (al_init_ttf_addon())
	{
		initAllegroFuncLog << "al_init_ttf_addon() success\n";
	}
	else
	{
		initAllegroFuncLog << "al_init_ttf_addon() failed\n";
	}

	
	installAllegroFuncLog.open("installAllegroFuncLog.txt");		//Open insall log file


	if (al_install_keyboard())
	{
		installAllegroFuncLog << "al_install_keyboard() success\n";
	}
	else
	{
		installAllegroFuncLog << "al_install_keyboard() failed\n";
	}


	if (al_install_mouse())
	{
		installAllegroFuncLog << "al_install_mouse() success\n";
	}
	else
	{
		installAllegroFuncLog << "al_install_mouse() failed\n";
	}
	
	//Close logs after writing to them
	initAllegroFuncLog.close();
	installAllegroFuncLog.close();

	//---------Func logs end--------------------------------------------------------------------


	//---------------------------------------------------------------------

	//Window resolution
	int windowWidth = 640;
	int windowHeight = 480;

	//Create display
	ALLEGRO_DISPLAY * window = al_create_display(windowWidth, windowHeight);

	//Set background to color
	al_clear_to_color(al_map_rgb(0,0,0));







	//Update screen
	al_flip_display();

	//Stops current thread here for a number of second(s)
	al_rest(5.0);

	return 0;
}