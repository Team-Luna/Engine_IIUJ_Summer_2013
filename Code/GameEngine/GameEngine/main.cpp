///Includes
#include <irrlicht.h>
#include <Level.h>
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

///Class Declarations
class KeyReciever : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event) {
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	virtual bool IsKeyDown(EKEY_CODE keyCode) const {
		return KeyIsDown[keyCode];
	}
	
	KeyReciever() {
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

///Program Startup
int main()
{
	KeyReciever receiver;

	///Creating Game Window
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(800, 600), 16,
			false, false, false, &receiver);

	if (!device)
		return 1;

	device->setWindowCaption(L"Game Engine Demo");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	
	//ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0,30,0), vector3df(0,0,0));
	ICameraSceneNode *cam = smgr->addCameraSceneNode(0, vector3df(0,15,-40), vector3df(0,0,0));

	///Creating level (From file, yay!)
	Level L = Level(device, "../Init/level1.ini");

	f32 FrameInterval = 1.0/60.0;
	u32 t2 = device->getTimer()->getTime();

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
					L.process_key(irr::KEY_ESCAPE);
				}

				//Updating Level
				L.advance_frame(cam);

				smgr->drawAll();
				guienv->drawAll();

				driver->endScene();
			}
		}
	}
	device->drop();
	return 0;
}
