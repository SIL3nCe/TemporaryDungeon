#include "Extension.h"

#include "ShSDK/ShSDK.h"

//
// Include plugins
#include "../Plugins/PluginST/PluginST.h"

typedef void(*register_fn)(void);
typedef void(*unregister_fn)(void);
typedef PluginST * (*get_instance_fn)(void);

static register_fn pRegisterST = shNULL;
static unregister_fn pUnRegisterST = shNULL;
static get_instance_fn pGetInstanceST = shNULL;

static FuncOnTouchDownPtr pOnTouchDownST = shNULL;
static FuncOnTouchUpPtr pOnTouchUpST = shNULL;
static FuncOnTouchMovePtr pOnTouchMoveST = shNULL;

#ifdef PLUGIN_ST_PATH
static const CShString strPluginSTFilePath(PLUGIN_ST_PATH);
#else
#	error "Plugin path not defined"
#endif

static CShDynamicLibrary pluginST_library(strPluginSTFilePath);

extern "C"
{

EXTENSION_EXPORT void ExtensionInitialize(void)
{
	// ...
}

EXTENSION_EXPORT void ExtensionRelease(void)
{
	// ...
}

EXTENSION_EXPORT void ExtensionOnPluginStarted(const CShIdentifier & levelIdentifier)
{
	//
	// Load Library
	bool bInit = pluginST_library.Initialize();

	//
	// Get Functions
	if (bInit)
	{
		pRegisterST = (register_fn)pluginST_library.GetFunctionAddress(CShString("RegisterPlugin"));
		SH_ASSERT(shNULL != pRegisterST);

		pUnRegisterST = (register_fn)pluginST_library.GetFunctionAddress(CShString("UnRegisterPlugin"));
		SH_ASSERT(shNULL != pUnRegisterST);

		pGetInstanceST = (get_instance_fn)pluginST_library.GetFunctionAddress(CShString("GetPlugin"));
		SH_ASSERT(shNULL != pGetInstanceST);

		pOnTouchDownST = (FuncOnTouchDownPtr)pluginST_library.GetFunctionAddress(CShString("TouchDownPluginST"));
		SH_ASSERT(shNULL != pOnTouchDownST);

		pOnTouchUpST = (FuncOnTouchUpPtr)pluginST_library.GetFunctionAddress(CShString("TouchUpPluginST"));
		SH_ASSERT(shNULL != pOnTouchUpST);

		pOnTouchMoveST = (FuncOnTouchMovePtr)pluginST_library.GetFunctionAddress(CShString("TouchMovePluginST"));
		SH_ASSERT(shNULL != pOnTouchMoveST);
	}

	//
	// Call factory (auto-register)
	if (shNULL != pRegisterST)
	{
		pRegisterST();

		ShInput::AddOnTouchDown(pOnTouchDownST);
		ShInput::AddOnTouchUp(pOnTouchUpST);
		ShInput::AddOnTouchMove(pOnTouchMoveST);
	}
}

EXTENSION_EXPORT void ExtensionOnPluginStopped(const CShIdentifier & levelIdentifier)
{
	//
	// Call factory (auto-unregister)
	if (shNULL != pUnRegisterST)
	{
		ShInput::RemoveOnTouchDown(pOnTouchDownST);
		ShInput::RemoveOnTouchUp(pOnTouchUpST);
		ShInput::RemoveOnTouchMove(pOnTouchMoveST);

		pUnRegisterST();
	}

	//
	// Reset function pointers
	{
		pGetInstanceST = shNULL;
		pUnRegisterST = shNULL;
		pRegisterST = shNULL;
	}

	//
	// Unload Library
	pluginST_library.Release();
}

}
