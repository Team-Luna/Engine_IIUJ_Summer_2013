///Includes
#include <irrlicht.h>
#include <Level.h>
#include <Background.h>
#include <HUD.h>

#include "IniWriter.h" //Temp
#include "IniReader.h" //Temp
///Namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
///Defs
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

// Gamestate Manager
enum GAME_STATE
{
	MAINMENU = 0,
	GAMEPLAY = 1,
	QUIT = 2
};

///Class Declarations
class KeyReciever : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event) {
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		// dla myszki (w menu)
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                MouseState.LeftButtonDown = true;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                MouseState.LeftButtonDown = false;
                break;

            case EMIE_MOUSE_MOVED:
                MouseState.Position.X = event.MouseInput.X;
                MouseState.Position.Y = event.MouseInput.Y;
                break;

            default:
                // We won't use the wheel
                break;
            }
        }

		return false;
	}

	virtual bool IsKeyDown(EKEY_CODE keyCode) const {
		return KeyIsDown[keyCode];
	}
	
	KeyReciever() {
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	// dla myszki (w menu)
    struct SMouseState
    {
        core::position2di Position;
        bool LeftButtonDown;
        SMouseState() : LeftButtonDown(false) { }
    } MouseState;

    const SMouseState & GetMouseState(void) const
    {
        return MouseState;
    }

	/* // nie wiadomo czy potrzebne
    MyEventReceiver()
    {
    }
	*/

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

bool fexists(const char *filename)
{
  ifstream ifile(filename);
  return ifile;
}

void iniGenerate(){
CIniWriter iniWriter("../Init/Settings.ini");
 iniWriter.WriteInteger("Setting", "Resolution_X_Size", 800);   
 iniWriter.WriteInteger("Setting", "Resolution_Y_Size", 600); 

}

///Program Startup
int main()
{
	int Resolution_X_Size;
	int Resolution_Y_Size;
	//Get .ini file
	if(!fexists("../Init/Settings.ini")){
		iniGenerate();
	}
	CIniReader iniReader("../Init/Settings.ini");
	Resolution_X_Size = iniReader.ReadInteger("Setting", "Resolution_X_Size", 800); 
	Resolution_Y_Size = iniReader.ReadInteger("Setting", "Resolution_Y_Size", 600); 
	
	// najpierw menu glowne
	GAME_STATE state = MAINMENU;

	KeyReciever receiver;

	///Creating Game Window
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(Resolution_X_Size, Resolution_Y_Size), 16,
			false, false, false, &receiver);

	if (!device)
		return 1;

	device->setWindowCaption(L"Game Engine Demo");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();


	while(true)
	{
		while(state==MAINMENU)
		{
			video::ITexture* buttonTexture = driver->getTexture("../media/menu/dark.png");
			video::ITexture* backgroundTexture = driver->getTexture("../media/menu/menu_beach_background.jpg");

			gui::IGUIFont* font = device->getGUIEnvironment()->getFont("../media/menu/BuxtonSketch24.png");

			while(device->run() && driver)
			{
				if (device->isWindowActive())
				{
					u32 time = device->getTimer()->getTime();

					driver->beginScene(true, true, SColor(255,100,101,140));
				}

				// tlo
				driver->draw2DImage(backgroundTexture, core::position2d<s32>(0,0),
				core::rect<s32>(0,0,Resolution_X_Size,Resolution_Y_Size), 0,
				video::SColor(255,255,255,255), false);

				// przycisk NEW GAME
				driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.16666)),
                core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
                video::SColor(255,255,255,255), false);

				if((receiver.GetMouseState().Position.X>(Resolution_X_Size*0.3125)) && (receiver.GetMouseState().Position.X<(Resolution_X_Size*0.6875)) && (receiver.GetMouseState().Position.Y>(Resolution_Y_Size*0.16666)) && (receiver.GetMouseState().Position.Y<(Resolution_Y_Size*0.25)))
				{
					driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.16666)),
					core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
					video::SColor(200,35,120,170), false);
				}

				if((receiver.GetMouseState().Position.X>(Resolution_X_Size*0.3125)) && (receiver.GetMouseState().Position.X<(Resolution_X_Size*0.6875)) && (receiver.GetMouseState().Position.Y>(Resolution_Y_Size*0.16666)) && (receiver.GetMouseState().Position.Y<(Resolution_Y_Size*0.25)) && receiver.GetMouseState().LeftButtonDown)
				{
					state = GAMEPLAY;
					break;
				}

				// przycisk ENTER PASSWORD
				driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.33333)),
                core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
                video::SColor(255,255,255,255), false);

				if((receiver.GetMouseState().Position.X>(Resolution_X_Size*0.3125)) && (receiver.GetMouseState().Position.X<(Resolution_X_Size*0.6875)) && (receiver.GetMouseState().Position.Y>(Resolution_Y_Size*0.33333)) && (receiver.GetMouseState().Position.Y<(Resolution_Y_Size*0.41666)))
				{
					driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.33333)),
					core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
					video::SColor(200,35,120,170), false);
				}

				// przycisk SETTINGS
				driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.5)),
                core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
                video::SColor(255,255,255,255), false);

				if((receiver.GetMouseState().Position.X>(Resolution_X_Size*0.3125)) && (receiver.GetMouseState().Position.X<(Resolution_X_Size*0.6875)) && (receiver.GetMouseState().Position.Y>(Resolution_Y_Size*0.5)) && (receiver.GetMouseState().Position.Y<(Resolution_Y_Size*0.5833)))
				{
					driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.5)),
					core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
					video::SColor(200,35,120,170), false);
				}

				if((receiver.GetMouseState().Position.X>(Resolution_X_Size*0.3125)) && (receiver.GetMouseState().Position.X<(Resolution_X_Size*0.6875)) && (receiver.GetMouseState().Position.Y>(Resolution_Y_Size*0.5)) && (receiver.GetMouseState().Position.Y<(Resolution_Y_Size*0.5833)) && receiver.GetMouseState().LeftButtonDown)
				{

				}

				// przycisk EXIT
				driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.66666)),
                core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
                video::SColor(255,255,255,255), false);

				if((receiver.GetMouseState().Position.X>(Resolution_X_Size*0.3125)) && (receiver.GetMouseState().Position.X<(Resolution_X_Size*0.6875)) && (receiver.GetMouseState().Position.Y>(Resolution_Y_Size*0.66666)) && (receiver.GetMouseState().Position.Y<(Resolution_Y_Size*0.75)))
				{
					driver->draw2DImage(buttonTexture, core::position2d<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.66666)),
					core::rect<s32>(0,0,(Resolution_X_Size*0.375),(Resolution_Y_Size*0.08333)), 0,
					video::SColor(200,35,120,170), false);
				}
				
				if((receiver.GetMouseState().Position.X>(Resolution_X_Size*0.3125)) && (receiver.GetMouseState().Position.X<(Resolution_X_Size*0.6875)) && (receiver.GetMouseState().Position.Y>(Resolution_Y_Size*0.66666)) && (receiver.GetMouseState().Position.Y<(Resolution_Y_Size*0.75)) && receiver.GetMouseState().LeftButtonDown)
				{
					return 0;
				}

				// draw some text
				if (font)
				{
					font->draw(L"NEW GAME",
						core::rect<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.16666),(Resolution_X_Size*0.6875),(Resolution_Y_Size*0.25)),
						video::SColor(255,255,255,255),true,true);

					font->draw(L"ENTER PASSWORD",
						core::rect<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.33333),(Resolution_X_Size*0.6875),(Resolution_Y_Size*0.41666)),
						video::SColor(255,255,255,255),true,true);

					font->draw(L"SETTINGS",
						core::rect<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.5),(Resolution_X_Size*0.6875),(Resolution_Y_Size*0.5833)),
						video::SColor(255,255,255,255),true,true);

					font->draw(L"EXIT",
						core::rect<s32>((Resolution_X_Size*0.3125),(Resolution_Y_Size*0.66666),(Resolution_X_Size*0.6875),(Resolution_Y_Size*0.75)),
						video::SColor(255,255,255,255),true,true);
				}

				/*core::position2d<s32> m = device->getCursorControl()->getPosition();
				driver->draw2DRectangle(video::SColor(100,255,255,255),
                core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));*/

				driver->endScene();
			}
		}
		while(state==GAMEPLAY)
		{
			//ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0,30,0), vector3df(0,0,0));
			ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0,15,-40), vector3df(0,0,0));

			///Creating level (From file, yay!)
			Level L = Level(device, "../Init/level1.ini");

			f32 FrameInterval = 1.0/60.0;
			u32 t2 = device->getTimer()->getTime();

			HUD headsUpDisplay = HUD(&L, device);

			///Running the Game
			while(device->run())
			{
				if (device->isWindowActive())
				{
					u32 t1 = device->getTimer()->getTime();
					f32 frameDeltaTime = (f32)(t1 - t2) / 1000.f; // Time in seconds
					if (FrameInterval <= frameDeltaTime)
					{
						//Updating Time
						t2 = t1;
						driver->beginScene(true, true, SColor(255,100,101,140));
						L.delta_time = (frameDeltaTime < 3*FrameInterval) ? frameDeltaTime : 3*FrameInterval; //min, deltaTime or 3 frames
				
						//Handling Keys
						if(receiver.IsKeyDown(irr::KEY_KEY_W))
							L.process_key(irr::KEY_KEY_W);
						else if(receiver.IsKeyDown(irr::KEY_KEY_S))
							L.process_key(irr::KEY_KEY_S);
						if(receiver.IsKeyDown(irr::KEY_KEY_D)) {
							L.process_key(irr::KEY_KEY_D);
						}
						else if(receiver.IsKeyDown(irr::KEY_KEY_A)) {
							L.process_key(irr::KEY_KEY_A);
						}
						else if(receiver.IsKeyDown(irr::KEY_KEY_Q)) {
							L.process_key(irr::KEY_KEY_Q);
						}
						else if(receiver.IsKeyDown(irr::KEY_KEY_Z)) {
							L.process_key(irr::KEY_KEY_Z);
						}
						else if(receiver.IsKeyDown(irr::KEY_ESCAPE)) {
							return 0;
						}

						//Updating Level
						L.advance_frame(cam);

						smgr->drawAll();
						guienv->drawAll();
						
						headsUpDisplay.drawHUD();

						driver->endScene();
					}
				}
			}
			device->drop();
		}
		if(state==QUIT) {
			return 0;
		}
	}
	return 0;
}
