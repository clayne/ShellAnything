//#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#include <initguid.h>
#include <shlguid.h>
#include <shlobj.h>
#include <cmnquery.h>
#include <dsquery.h>
#include <dsclient.h>

#include <glog/logging.h>

#include "shellext.h"
#include "win32Registry.h"

#include "rapidassist/strings.h"
#include "rapidassist/environment.h"
#include "rapidassist/filesystem.h"
#include "rapidassist/process.h"

//Declarations
UINT      g_cRefDll = 0;   // Reference counter of this DLL
HINSTANCE g_hmodDll = 0;   // HINSTANCE of the DLL

//http://www.codeguru.com/cpp/w-p/dll/tips/article.php/c3635
#if _MSC_VER >= 1300    // for VC 7.0
  // from ATL 7.0 sources
  #ifndef _delayimp_h
  extern "C" IMAGE_DOS_HEADER __ImageBase;
  #endif
#endif

HMODULE GetCurrentModule2000()
{
#if _MSC_VER < 1300 // earlier than .NET compiler (VC 6.0)
  // Here's a trick that will get you the handle of the module
  // you're running in without any a-priori knowledge:
  // http://www.dotnet247.com/247reference/msgs/13/65259.aspx

  MEMORY_BASIC_INFORMATION mbi;
  static int dummy;
  VirtualQuery( &dummy, &mbi, sizeof(mbi) );
  return reinterpret_cast<HMODULE>(mbi.AllocationBase);
#else // VC 7.0
  // from ATL 7.0 sources
  return reinterpret_cast<HMODULE>(&__ImageBase);
#endif
}

HMODULE GetCurrentModule()
{
  return GetCurrentModule2000();
}

const char * GetCurrentModulePath()
{
  static char buffer[MAX_PATH];
  GetModuleFileName(GetCurrentModule(), buffer, MAX_PATH);
  return buffer;
}

std::string GuidToString(GUID guid) {
  std::string output;
  output.assign(40, 0);
  sprintf_s((char*)output.c_str(), output.size(), "{%08X-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
  return output;
}

CContextMenu::CContextMenu()
{
  LOG(INFO) << __FUNCTION__ << "(), new";
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  m_cRef = 0L;
  m_pDataObj = NULL;

  // Increment the dll's reference counter.
  InterlockedIncrement(&g_cRefDll);
}

CContextMenu::~CContextMenu()
{
  LOG(INFO) << __FUNCTION__ << "(), delete";
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  if (m_pDataObj) m_pDataObj->Release();

  // Decrement the dll's reference counter.
  InterlockedDecrement(&g_cRefDll);
}

std::string getMenuDescriptor(HMENU hMenu)
{
  std::string output;

  int numItems = GetMenuItemCount(hMenu);
  for(int i=0; i<numItems; i++)
  {
    UINT id = GetMenuItemID(hMenu, i);

    static const int BUFFER_SIZE = 1024;
    char name[BUFFER_SIZE];
    int result = GetMenuStringA(hMenu, i, name, BUFFER_SIZE, 0);

    char item_desc[BUFFER_SIZE];
    sprintf(item_desc, "%d:%s", id, name);
    if (!output.empty())
      output.append(",");
    output.append(item_desc);
  }

  output.insert(0, "MENU{");
  output.append("}");
  return output;
}

HRESULT STDMETHODCALLTYPE CContextMenu::QueryContextMenu(HMENU hMenu,  UINT indexMenu,  UINT idCmdFirst,  UINT idCmdLast, UINT uFlags)
{
  //build function descriptor
  LOG(INFO) << __FUNCTION__ << "(), hMenu=" << getMenuDescriptor(hMenu) << ", indexMenu=" << indexMenu << ", idCmdFirst=" << idCmdFirst << ", idCmdLast=" << idCmdLast << ", uFlags=" << uFlags;
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  //g_Logger->print("begin of QueryContextMenu");

  ////Debugging:
  //{
  //  extProcess * currentProcess = extProcessHandler::getCurrentProcess();
  //  std::string message = ra::strings::format("Attach to process %d and press OK to continue...", currentProcess->getPid());
  //  MessageBox(NULL, message.c_str(), "DEBUG!", MB_OK);
  //}

  //UINT nextCommandId = idCmdFirst;
  //long nextSequentialId = 0;
  //extMenuTools::insertMenu(hMenu, indexMenu, mMenus, nextCommandId, nextSequentialId);

  //indexMenu++;

  //g_Logger->print("end of QueryContextMenu");
    
  //return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, nextCommandId - idCmdFirst );

  return E_INVALIDARG;
}

HRESULT STDMETHODCALLTYPE CContextMenu::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
  LOG(INFO) << __FUNCTION__ << "()";
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  //g_Logger->print("begin of InvokeCommand");

  //if (!HIWORD(lpcmi->lpVerb))
  //{
  //  long sequentialId = LOWORD(lpcmi->lpVerb);

  //  //check for a clicked menu command
  //  ShellMenu * selectedMenu = findMenuBySequentialId(mMenus, sequentialId);
  //  if (selectedMenu)
  //  {
  //    runMenu( (*selectedMenu), mSelectedItems );
  //  }
  //  else
  //  {
  //    //Build error message
  //    std::string message = ra::strings::format("Menu item with system id %d not found!\n\n", sequentialId);
  //    MessageBox(NULL, message.c_str(), "Unable to invoke command", MB_OK | MB_ICONERROR);
  //  }
  //}
  //g_Logger->print("end of InvokeCommand");

  return E_INVALIDARG;
}

HRESULT STDMETHODCALLTYPE CContextMenu::GetCommandString(UINT_PTR idCmd, UINT uFlags, UINT FAR *reserved, LPSTR pszName, UINT cchMax)
{
  //build function descriptor
  LOG(INFO) << __FUNCTION__ << "(), idCmd=" << idCmd << ", uFlags=" << uFlags << ", reserved=" << reserved << ", pszName=" << pszName << ", cchMax=" << cchMax;
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  //g_Logger->print("begin of GetCommandString");
        
  //long menuSequenceId = idCmd;
  ////check for a menu that matches menuSequenceId
  //ShellMenu * selectedMenu = findMenuBySequentialId(mMenus, menuSequenceId);

  //if (selectedMenu == NULL)
  //{
  //  //Build error message
  //  std::string message = ra::strings::format("Menu item with sequential id %d not found!\n\n", menuSequenceId);
  //  MessageBox(NULL, message.c_str(), "Unable to process GetCommandString()", MB_OK | MB_ICONERROR);

  //  //g_Logger->print("end #1 of GetCommandString");
  //  return S_FALSE;
  //}

  ////Build up tooltip string
  //const char * tooltip = " ";
  //if (selectedMenu->getDescription().size() > 0)
  //  tooltip = selectedMenu->getDescription().c_str();

  ////Textes � afficher dans la barre d'�tat d'une fen�tre de l'explorateur quand
  ////l'un de nos �l�ments du menu contextuel est point� par la souris:
  //switch(uFlags)
  //{
  //case GCS_HELPTEXTA:
  //  {
  //    //ANIS tooltip handling
  //    lstrcpynA(pszName, tooltip, cchMax);
  //    //g_Logger->print("end #2 of GetCommandString");
  //    return S_OK;
  //  }
  //  break;
  //case GCS_HELPTEXTW:
  //  {
  //    //UNICODE tooltip handling
  //    extMemoryBuffer unicodeDescription = extStringConverter::toUnicode(tooltip);
  //    bool success = false;
  //    if (unicodeDescription.getSize() <= cchMax)
  //    {
  //      memcpy(pszName, unicodeDescription.getBuffer(), unicodeDescription.getSize());
  //      success = true;
  //    }
  //    //g_Logger->print("end #3 of GetCommandString");
  //    return success ? S_OK : E_FAIL;
  //  }
  //  break;
  //case GCS_VERBA:
  //  break;
  //case GCS_VERBW:
  //  break;
  //case GCS_VALIDATEA:
  //case GCS_VALIDATEW:
  //  {
  //    //VALIDATE ? already validated, selectedMenu is non-NULL
  //    //g_Logger->print("end #4 of GetCommandString");
  //    return S_OK;
  //  }
  //  break;
  //}
  ////g_Logger->print("end #5 of GetCommandString");
  //return S_OK;

  return S_FALSE;
}

HRESULT STDMETHODCALLTYPE CContextMenu::Initialize(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObj, HKEY hRegKey)
{
  LOG(INFO) << __FUNCTION__ << "()";
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  //https://docs.microsoft.com/en-us/windows/desktop/ad/example-code-for-implementation-of-the-context-menu-com-object
  STGMEDIUM   stm;
  FORMATETC   fe;
  HRESULT     hr;

  if(NULL == pDataObj)
  {
    return E_INVALIDARG;
  }

  fe.cfFormat = RegisterClipboardFormat(CFSTR_DSOBJECTNAMES);
  fe.ptd = NULL;
  fe.dwAspect = DVASPECT_CONTENT;
  fe.lindex = -1;
  fe.tymed = TYMED_HGLOBAL;
  hr = pDataObj->GetData(&fe, &stm);
  if(SUCCEEDED(hr))
  {
    LPDSOBJECTNAMES pdson = (LPDSOBJECTNAMES)GlobalLock(stm.hGlobal);

    if(pdson)
    {
      DWORD   dwBytes = GlobalSize(stm.hGlobal);

      DSOBJECTNAMES * m_pObjectNames = (DSOBJECTNAMES*)GlobalAlloc(GPTR, dwBytes);
      if(m_pObjectNames)
      {
        CopyMemory(m_pObjectNames, pdson, dwBytes);
      }

      GlobalUnlock(stm.hGlobal);
    }

    ReleaseStgMedium(&stm);
  }

  fe.cfFormat = RegisterClipboardFormat(CFSTR_DS_DISPLAY_SPEC_OPTIONS);
  fe.ptd = NULL;
  fe.dwAspect = DVASPECT_CONTENT;
  fe.lindex = -1;
  fe.tymed = TYMED_HGLOBAL;
  hr = pDataObj->GetData(&fe, &stm);
  if(SUCCEEDED(hr))
  {
    PDSDISPLAYSPECOPTIONS   pdso;

    pdso = (PDSDISPLAYSPECOPTIONS)GlobalLock(stm.hGlobal);
    if(pdso)
    {
      DWORD   dwBytes = GlobalSize(stm.hGlobal);

      PDSDISPLAYSPECOPTIONS m_pDispSpecOpts = (PDSDISPLAYSPECOPTIONS)GlobalAlloc(GPTR, dwBytes);
      if(m_pDispSpecOpts)
      {
        CopyMemory(m_pDispSpecOpts, pdso, dwBytes);
      }

      GlobalUnlock(stm.hGlobal);
    }

    ReleaseStgMedium(&stm);
  }

  return hr;
}

HRESULT STDMETHODCALLTYPE CContextMenu::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
  //build function descriptor
  LOG(INFO) << __FUNCTION__ << "(), riid=" << GuidToString(riid).c_str() << ", ppvObj=" << ppvObj;
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  //https://docs.microsoft.com/en-us/office/client-developer/outlook/mapi/implementing-iunknown-in-c-plus-plus

  // Always set out parameter to NULL, validating it first.
  if (!ppvObj)
    return E_INVALIDARG;
  *ppvObj = NULL;
  if (IsEqualGUID(riid, IID_IUnknown) || IsEqualGUID(riid, IID_IShellExtInit) || IsEqualGUID(riid, IID_IContextMenu))
  {
    // Increment the reference count and return the pointer.
    LOG(INFO) << __FUNCTION__ << "(), found interface " << GuidToString(riid).c_str();
    *ppvObj = (LPVOID)this;
    AddRef();
    return NOERROR;
  }
  LOG(ERROR) << __FUNCTION__ << "(), Interface " << GuidToString(riid).c_str() << " not found!";
  return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CContextMenu::AddRef()
{
  //https://docs.microsoft.com/en-us/office/client-developer/outlook/mapi/implementing-iunknown-in-c-plus-plus

  // Increment the object's internal counter.
  InterlockedIncrement(&m_cRef);
  return m_cRef;
}

ULONG STDMETHODCALLTYPE CContextMenu::Release()
{
  //https://docs.microsoft.com/en-us/office/client-developer/outlook/mapi/implementing-iunknown-in-c-plus-plus

  // Decrement the object's internal counter.
  ULONG ulRefCount = InterlockedDecrement(&m_cRef);
  if (0 == m_cRef)
  {
    delete this;
  }
  return ulRefCount;
}

// Constructeur de l'interface IClassFactory:
CClassFactory::CClassFactory()
{
  LOG(INFO) << __FUNCTION__ << "(), new";
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  m_cRef = 0L;

  // Increment the dll's reference counter.
  InterlockedIncrement(&g_cRefDll);
}

// Destructeur de l'interface IClassFactory:
CClassFactory::~CClassFactory()
{
  LOG(INFO) << __FUNCTION__ << "(), delete";

  // Decrement the dll's reference counter.
  InterlockedDecrement(&g_cRefDll);
}

HRESULT STDMETHODCALLTYPE CClassFactory::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
  //build function descriptor
  LOG(INFO) << __FUNCTION__ << "(), riid=" << GuidToString(riid).c_str() << ", ppvObj=" << ppvObj;
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  //https://docs.microsoft.com/en-us/office/client-developer/outlook/mapi/implementing-iunknown-in-c-plus-plus

  // Always set out parameter to NULL, validating it first.
  if (!ppvObj)
    return E_INVALIDARG;
  *ppvObj = NULL;
  if (IsEqualGUID(riid, IID_IUnknown) || IsEqualGUID(riid, IID_IClassFactory))
  {
    // Increment the reference count and return the pointer.
    LOG(INFO) << __FUNCTION__ << "(), found interface " << GuidToString(riid).c_str();
    *ppvObj = (LPVOID)this;
    AddRef();
    return NOERROR;
  }

  LOG(ERROR) << __FUNCTION__ << "(), Interface " << GuidToString(riid).c_str() << " not found!";
  return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CClassFactory::AddRef()
{
  //https://docs.microsoft.com/en-us/office/client-developer/outlook/mapi/implementing-iunknown-in-c-plus-plus

  // Increment the object's internal counter.
  InterlockedIncrement(&m_cRef);
  return m_cRef;
}

ULONG STDMETHODCALLTYPE CClassFactory::Release()
{
  //https://docs.microsoft.com/en-us/office/client-developer/outlook/mapi/implementing-iunknown-in-c-plus-plus

  // Decrement the object's internal counter.
  ULONG ulRefCount = InterlockedDecrement(&m_cRef);
  if (0 == m_cRef)
  {
    delete this;
  }
  return ulRefCount;
}

HRESULT STDMETHODCALLTYPE CClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObj)
{
  //build function descriptor
  LOG(INFO) << __FUNCTION__ << "(), pUnkOuter=" << pUnkOuter << ", riid=" << GuidToString(riid).c_str();
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  *ppvObj = NULL;
  if (pUnkOuter) return CLASS_E_NOAGGREGATION;
  CContextMenu* pContextMenu = new CContextMenu();
  if (!pContextMenu) return E_OUTOFMEMORY;
  HRESULT hr = pContextMenu->QueryInterface(riid, ppvObj);
  if (FAILED(hr))
  {
    delete pContextMenu;
    pContextMenu = NULL;
  }
  return hr;
}

HRESULT STDMETHODCALLTYPE CClassFactory::LockServer(BOOL fLock)
{
  //https://docs.microsoft.com/en-us/windows/desktop/api/unknwnbase/nf-unknwnbase-iclassfactory-lockserver
  //https://docs.microsoft.com/en-us/windows/desktop/api/combaseapi/nf-combaseapi-colockobjectexternal
  return S_OK;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut)
{
  //build function descriptor
  LOG(INFO) << __FUNCTION__ << "(), rclsid=" << GuidToString(rclsid).c_str() << ", riid=" << GuidToString(riid).c_str() << "";
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  *ppvOut = NULL;
  if (IsEqualGUID(rclsid, CLSID_ShellExtension))
  {
    CClassFactory *pcf = new CClassFactory;
    if (!pcf) return E_OUTOFMEMORY;
    HRESULT hr = pcf->QueryInterface(riid, ppvOut);
    if (FAILED(hr))
    {
      LOG(ERROR) << __FUNCTION__ << "(), Interface " << GuidToString(riid).c_str() << " not found!";
      delete pcf;
      pcf = NULL;
    }
    LOG(INFO) << __FUNCTION__ << "(), found interface " << GuidToString(riid).c_str();
    return hr;
  }
  LOG(ERROR) << __FUNCTION__ << "(), ClassFactory " << GuidToString(rclsid).c_str() << " not found!";
  return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow(void)
{
  MessageBox(NULL, __FUNCTION__, __FUNCTION__, MB_OK);

  ULONG ulRefCount = 0;
  ulRefCount = InterlockedIncrement(&g_cRefDll);
  ulRefCount = InterlockedDecrement(&g_cRefDll);

  if (0 == ulRefCount)
  {
    LOG(INFO) << __FUNCTION__ << "() -> Yes";
    return S_OK;
  }
  LOG(INFO) << __FUNCTION__ << "() -> No, " << ulRefCount << " instance are still in use.";
  return S_FALSE;
}

STDAPI DllRegisterServer(void)
{
  // Add the CLSID of this DLL to the registry
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\CLSID\\%s", CLSID_ShellExtensionStr);
    if (!win32Registry::createKey(key.c_str()))
      return E_ACCESSDENIED;
    if (!win32Registry::setValue(key.c_str(), "", ShellExtensionDescription))
      return E_ACCESSDENIED;
  }

  // Define the path and parameters of our DLL:
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\CLSID\\%s\\InProcServer32", CLSID_ShellExtensionStr);
    if (!win32Registry::createKey(key.c_str()))
      return E_ACCESSDENIED;
    if (!win32Registry::setValue(key.c_str(), "", GetCurrentModulePath() ))
      return E_ACCESSDENIED;
    if (!win32Registry::setValue(key.c_str(), "ThreadingModel", "Apartment"))
      return E_ACCESSDENIED;
  }

  // Register the shell extension for all the file types
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\*\\shellex\\ContextMenuHandlers\\%s", ShellExtensionName);
    if (!win32Registry::createKey(key.c_str()))
      return E_ACCESSDENIED;
    if (!win32Registry::setValue(key.c_str(), "", CLSID_ShellExtensionStr))
      return E_ACCESSDENIED;
  }

  // Register the shell extension for directories
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\Directory\\shellex\\ContextMenuHandlers\\%s", ShellExtensionName);
    if (!win32Registry::createKey(key.c_str()))
      return E_ACCESSDENIED;
    if (!win32Registry::setValue(key.c_str(), "", CLSID_ShellExtensionStr))
      return E_ACCESSDENIED;
  }

  // Notify the Shell to pick the default icon definition change
  SHChangeNotify(SHCNE_ASSOCCHANGED,0,0,0);

  // Register the shell extension for the desktop or the file explorer's background
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\Directory\\Background\\ShellEx\\ContextMenuHandlers\\%s", ShellExtensionName);
    if (!win32Registry::createKey(key.c_str()))
      return E_ACCESSDENIED;
    if (!win32Registry::setValue(key.c_str(), "", CLSID_ShellExtensionStr))
      return E_ACCESSDENIED;
  }

  // Register the shell extension to the system's approved Shell Extensions
  {
    std::string key = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved";
    if (!win32Registry::createKey(key.c_str()))
      return E_ACCESSDENIED;
    if (!win32Registry::setValue(key.c_str(), CLSID_ShellExtensionStr, ShellExtensionDescription))
      return E_ACCESSDENIED;
  }

  return S_OK;
}

STDAPI DllUnregisterServer(void)
{
  // Unregister the shell extension from the system's approved Shell Extensions
  {
    std::string key = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved";
    if (!win32Registry::deleteValue(key.c_str(), CLSID_ShellExtensionStr))
      return E_ACCESSDENIED;
  }

  // Unregister the shell extension for the desktop or the file explorer's background
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\Directory\\Background\\ShellEx\\ContextMenuHandlers\\%s", ShellExtensionName);
    if (!win32Registry::deleteKey(key.c_str()))
      return E_ACCESSDENIED;
  }

  // Notify the Shell to pick the default icon definition change
  SHChangeNotify(SHCNE_ASSOCCHANGED,0,0,0);

  // Unregister the shell extension for directories
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\Directory\\shellex\\ContextMenuHandlers\\%s", ShellExtensionName);
    if (!win32Registry::deleteKey(key.c_str()))
      return E_ACCESSDENIED;
  }

  // Unregister the shell extension for all the file types
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\*\\shellex\\ContextMenuHandlers\\%s", ShellExtensionName);
    if (!win32Registry::deleteKey(key.c_str()))
      return E_ACCESSDENIED;
  }

  // Remove the CLSID of this DLL from the registry
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\CLSID\\%s\\InProcServer32", CLSID_ShellExtensionStr);
    if (!win32Registry::deleteKey(key.c_str()))
      return E_ACCESSDENIED;
  }
  {
    std::string key = ra::strings::format("HKEY_CLASSES_ROOT\\CLSID\\%s", CLSID_ShellExtensionStr);
    if (!win32Registry::deleteKey(key.c_str()))
      return E_ACCESSDENIED;
  }

  return S_OK;
}

void DeletePreviousLogs()
{
  std::string module_path = GetCurrentModulePath();
  std::string module_filename = ra::filesystem::getFilename(module_path.c_str());
  std::string temp_var = ra::environment::getEnvironmentVariable("TEMP");

  ra::strings::StringVector files;
  bool success = ra::filesystem::findFiles(files, temp_var.c_str());
  if (!success) return;

  std::string pattern_prefix = temp_var + ra::filesystem::getPathSeparatorStr() + module_filename;

  //for each files
  for(size_t i=0; i<files.size(); i++)
  {
    const std::string & path = files[i];
    if (path.find(pattern_prefix) != std::string::npos)
    {
      //that's a log file
      ra::filesystem::deleteFile(path.c_str());
    }
  }
}

void InitLogger()
{
  //delete previous logs for easier debugging
  DeletePreviousLogs();

  // Initialize Google's logging library.
  const char * argv[] = {
    GetCurrentModulePath(),
    ""
  };
  google::InitGoogleLogging(argv[0]);

  fLI::FLAGS_logbufsecs = 0; //flush logs after each LOG() calls

  LOG(INFO) << "Enabling logging";
  LOG(INFO) << "DLL path: " << GetCurrentModulePath();
  LOG(INFO) << "EXE path: " << ra::process::getCurrentProcessPath().c_str();

  LOG(INFO) << "IID_IUnknown      : " << GuidToString(IID_IUnknown).c_str();
  LOG(INFO) << "IID_IClassFactory : " << GuidToString(IID_IClassFactory).c_str();
  LOG(INFO) << "IID_IShellExtInit : " << GuidToString(IID_IShellExtInit).c_str();
  LOG(INFO) << "IID_IContextMenu  : " << GuidToString(IID_IContextMenu).c_str();
}

extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
  if (dwReason == DLL_PROCESS_ATTACH)
  {
    g_hmodDll = hInstance;

    // Initialize Google's logging library.
    InitLogger();
  }
  return 1; 
}

//int main(int argc, char* argv[])
//{
//  {
//    HRESULT result = DllRegisterServer();
//    if (result == S_OK)
//      MessageBox(NULL, "Manual dll registration successfull", ShellExtensionName, MB_OK | MB_ICONINFORMATION);
//    else                                              
//      MessageBox(NULL, "Manual dll registration FAILED !", ShellExtensionName, MB_OK | MB_ICONERROR);
//  }
//
//  {
//    HRESULT result = DllUnregisterServer();
//    if (result == S_OK)
//      MessageBox(NULL, "Manual dll unregistration successfull", ShellExtensionName, MB_OK | MB_ICONINFORMATION);
//    else
//      MessageBox(NULL, "Manual dll unregistration FAILED !", ShellExtensionName, MB_OK | MB_ICONERROR);
//  }
//}
