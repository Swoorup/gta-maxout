#include "../StdInc.h"
#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Direct3D8/Renderer.h>
#pragma comment(lib,"CEGUIBase-0.lib")
#pragma comment(lib,"CEGUIDirect3D8Renderer-0.lib")

using namespace HookSystem;
using namespace boost;

bool bWindowedMode;

DWORD OldDirect3DCreate8 = 0x66355C;

std::vector<void (*)(void)> fnAfterRwInit;
std::vector<void (*)(void)> fn2DRenderCallbacks;



void _cdecl render_callbacks()
{
	IDirect3DDevice8* get_d3d_device(void);
	// save the D3D states first before applying CEGUI
	DWORD pStateBlock = NULL;
	get_d3d_device()->CreateStateBlock( D3DSBT_ALL, &pStateBlock );

	std::vector<void (*)(void)>::iterator itr;
	for(itr = fn2DRenderCallbacks.begin(); itr != fn2DRenderCallbacks.end(); itr++)
	{
		(*itr)();
	}

	//restore the states
	get_d3d_device()->ApplyStateBlock( pStateBlock );
	get_d3d_device()->DeleteStateBlock(pStateBlock);
}

void _cdecl init_once_after_rw_callbacks(void)
{
	std::vector<void (*)(void)>::iterator itr;
	for(itr = fnAfterRwInit.begin(); itr != fnAfterRwInit.end(); itr++)
	{
		(*itr)();
	}
}

void add_render2d_callback(void (*fn)(void))
{
	fn2DRenderCallbacks.push_back(fn);
}

void add_initfunc_after_rw(void (*fn)(void))
{
	fnAfterRwInit.push_back(fn);
}

IDirect3DDevice8* get_d3d_device(void)
{
	return *(IDirect3DDevice8**)0x7897A8;
}

void install_d3d_hooks()
{
	CMemory::UnProtect(0x4A6501, 0x06);
	InstallFnByCall(0x4A6501, render_callbacks);
	(*(uint8_t*)(0x4A6501 + 5)) = 0xC3;

	CMemory::UnProtect(0x4A50FF, 0x08);
	InstallFnByCall(0x4A50FF, init_once_after_rw_callbacks);
	(*(uint16_t*)(0x4A50FF + 5)) = 0x01B0;
	(*(uint8_t*)(0x4A50FF + 7)) = 0xC3;

	void RenderCEGUI(void);
	add_render2d_callback(RenderCEGUI);
	
	void InitCEGUI(void);
	add_initfunc_after_rw(InitCEGUI);
}

using namespace CEGUI;

CEGUI::MultiLineEditbox * txtbox;
void InitCEGUI(void)
{
	static bool bInitonce = false;
	
	if(bInitonce == false)
		bInitonce = true;
	else
		return;

	CEGUI::Direct3D8Renderer* myRenderer = &CEGUI::Direct3D8Renderer::create(get_d3d_device());
	//myRenderer->setDisplaySize(CEGUI::Sizef(1280.0f, 720.0f));
	CEGUI::System *m_pSystem = &CEGUI::System::create(*myRenderer, 0, 0, 0, 0, "", "CEGUI.log");
	//CEGUI::System::create(*myRenderer);

	// Initialize the required dirs for the DefaultResourceProvider
    CEGUI::DefaultResourceProvider * rp = (CEGUI::DefaultResourceProvider *)m_pSystem->getResourceProvider();


    // For each resource type, set a resource group directory
    rp->setResourceGroupDirectory("schemes", "hdata/schemes/");
    rp->setResourceGroupDirectory("imagesets", "hdata/imagesets/");
    rp->setResourceGroupDirectory("fonts", "hdata/fonts/");
    rp->setResourceGroupDirectory("layouts", "hdata/layouts/");
    rp->setResourceGroupDirectory("looknfeels", "hdata/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", "hdata/lua_scripts/");
	

	// Set the default resource groups to be used
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");

	WindowManager& wmgr = WindowManager::getSingleton();
    wmgr.setDefaultResourceGroup("layouts");

	CEGUI::XMLParser * parser = m_pSystem->getXMLParser();

    if(parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");

	
	SchemeManager::getSingleton().createFromFile("GameMenu.scheme");
	SchemeManager::getSingleton().createFromFile("Generic.scheme");
	SchemeManager::getSingleton().createFromFile("SampleBrowser.scheme");
	SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
	FontManager::getSingleton().createFromFile("DejaVuSans-10.font");
	System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");

	Window* mytest = WindowManager::getSingleton().loadLayoutFromFile( "VanillaConsole.layout" );
	System::getSingleton().getDefaultGUIContext().setRootWindow( mytest );

	txtbox = (MultiLineEditbox*)mytest->getChild("History");//("Vanilla/MultiLineEditbox", "Position");
	return;
	Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
	System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
	myRoot->setText("Hello World!");
	FrameWindow* fWnd = (FrameWindow*)wmgr.createWindow( "Vanilla/FrameWindow", "testWindow" );
	myRoot->addChild( fWnd );

	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition( UVector2( UDim( 0.0f, 5 ), UDim( 0.0f, 5 ) ) );
	
	// set size to be half the size of the parent
	fWnd->setSize( USize( UDim( 0.3f, 0 ), UDim( 0.3f, 0 ) ) );
	fWnd->setText( "Hello World!" );
	txtbox = (MultiLineEditbox*)wmgr.createWindow("Vanilla/MultiLineEditbox", "Position");
	fWnd->addChild(txtbox);
	txtbox->setPosition(UVector2( UDim( 0.0f, 0 ), UDim( 0.0f, 0 ) ) );
	txtbox->setSize( USize( UDim( 0.8f, 0 ), UDim( 0.7f, 0 ) ) );

}

void RenderCEGUI(void)
{
	CEGUI::System::getSingleton().renderAllGUIContexts();
	CVector ahi;
	FindPlayerCoors(&ahi);

	std::string szPosition = lexical_cast<std::string>(ahi.fX) + " " + lexical_cast<std::string>(ahi.fY) + " " + lexical_cast<std::string>(ahi.fZ);
	txtbox->setText(CEGUI::String(szPosition));
	
	
}

void D3D8HookInit(bool bWindowed)
{

    bWindowedMode = bWindowed;
	
	install_d3d_hooks();
	// if the launcher is not present, to get window mode override the reset method in the original game device
	/*IDirect3DDevice8* pGameD3DDevice = (IDirect3DDevice8*)0x7897A8;
	DWORD AddrDeviceVtbl = **(DWORD**)pGameD3DDevice;
	
	IDirect3DDevice8Hook deviceFake;
	
	DWORD fnNewReset = (DWORD)*(DWORD*)(*((DWORD*)(&deviceFake)) + 14*4);
	D3DPRESENT_PARAMETERS& pParams = *(D3DPRESENT_PARAMETERS*)0xA0FD04;
	DWORD Protect = CMemory::UnProtect(AddrDeviceVtbl + 14 * 4, 4);
	pfnOldReset = ((DWORD)*(DWORD**)(AddrDeviceVtbl + 14 * 4));
	*(DWORD**)(AddrDeviceVtbl + 14 * 4) = (DWORD*)fnNewReset;
	CMemory::RestoreProtection(AddrDeviceVtbl + 14 * 4, 4, Protect);
	pParams.Windowed = true;*/

	//pGameD3DDevice->Reset(&pParams);
}