/// \file wmi_controller.cpp
/// \brief реализация методов контроллера, позволяющего работать с wmi

#include "wmi_controller.h"
#include "device_controller_strings.h"

#include <common/encoding_helper.h>

#include <fmt/core.h>

#include <comdef.h>
#include <stdexcept>

#pragma comment(lib, "wbemuuid.lib")


using namespace std;


namespace deviceController
{

WmiController::WmiController()
    : service_{NULL}
    , locator_{NULL}
    , wmiConnected_{false}
{

}

WmiController::~WmiController()
{
    if (service_)
    {
        service_->Release();
    }
    if (locator_)
    {
        locator_->Release();
    }
    CoUninitialize();
    wmiConnected_ = false;

}

void WmiController::disonnectWmi()
{
    if (service_)
    {
        service_->Release();
    }
    if (locator_)
    {
        locator_->Release();
    }
    CoUninitialize();
    wmiConnected_ = false;

}

std::shared_ptr<std::vector<std::string>> WmiController::Request(const std::string& wmiNamespace,
        const std::string& wmiClass, const std::string& objectField)
{
    if(!wmiConnected_)
    {
        connectToWmi(wmiNamespace);
    }

    if(currentWmiNamespace_ != wmiNamespace)
    {
        disonnectWmi();
        connectToWmi(wmiNamespace);
    }

    auto Request = common::encoding_helper::s2ws(fmt::format(RequestTemplate, wmiClass));

    IEnumWbemClassObject* pEnumerator = NULL;
    HRESULT hres = service_->ExecQuery(
          bstr_t("WQL"),
          bstr_t(Request.c_str()),
          WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
          NULL,
          &pEnumerator);

     if (FAILED(hres))
     {
        throw std::runtime_error(errorText);
     }

     // Step 7: -------------------------------------------------
     // Get the data from the query in step 6 -------------------

     IWbemClassObject* pclsObj = NULL;
     ULONG uReturn = 0;

    auto results = std::make_shared<std::vector<std::string>>();

     while (pEnumerator)
     {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp = {};

        // Get the value of the Name property
        hr = pclsObj->Get(common::encoding_helper::s2ws(objectField).c_str(), 0, &vtProp, 0, 0);

        if (vtProp.vt == VT_BSTR )
        {
            results->push_back( common::encoding_helper::ws2s(vtProp.bstrVal));
        }
        else if (vtProp.vt == VT_I8 || vtProp.vt == VT_I4 || vtProp.vt == VT_I2)
        {
            results->push_back( to_string(vtProp.intVal));
        }
         else if (vtProp.vt == VT_UI2 || vtProp.vt == VT_UI4 || vtProp.vt == VT_UI8)
        {
            results->push_back( to_string(vtProp.uintVal));
        }
         else if (vtProp.vt == VT_UI2 || vtProp.vt == VT_UI4 || vtProp.vt == VT_UI8)
        {
            results->push_back( to_string(vtProp.uintVal));
        }
         else if (vtProp.vt == VT_DECIMAL)
        {
            results->push_back( to_string(vtProp.fltVal));
        }
        else
        {
        }


        pclsObj->Release();
        VariantClear(&vtProp);
     }

     return results;

}

void WmiController::connectToWmi(const string& wmiNamespace)
{
    currentWmiNamespace_ = wmiNamespace;

    auto wideNamespace = common::encoding_helper::s2ws(wmiNamespace);

    HRESULT hres;

    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------

    hres =  CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        throw runtime_error(errorText); // Program has failed.
    }

    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------

    hres =  CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities
        NULL                         // Reserved
        );


    if (FAILED(hres))
    {
        throw runtime_error(errorText); // Program has failed.
    }

    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID *) &(locator_));

    if (FAILED(hres))
    {
        CoUninitialize();
        throw runtime_error(errorText);                 // Program has failed.
    }

    // Step 4: -----------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    // Connect to the root\cimv2 namespace with
    // the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = locator_->ConnectServer(
         _bstr_t(wideNamespace.c_str()), // Object path of WMI namespace
         NULL,                    // User name. NULL = current user
         NULL,                    // User password. NULL = current
         0,                       // Locale. NULL indicates current
         NULL,                    // Security flags.
         0,                       // Authority (for example, Kerberos)
         0,                       // Context object
         &service_                // pointer to IWbemServices proxy
         );

    if (FAILED(hres))
    {

        locator_->Release();
        CoUninitialize();
        throw runtime_error(errorText);                // Program has failed.
    }


    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------

    hres = CoSetProxyBlanket(
       service_,                        // Indicates the proxy to set
       RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
       RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
       NULL,                        // Server principal name
       RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
       RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
       NULL,                        // client identity
       EOAC_NONE                    // proxy capabilities
    );

    if (FAILED(hres))
    {

        service_->Release();
        locator_->Release();
        CoUninitialize();
        throw runtime_error(errorText);              // Program has failed.
    }
    wmiConnected_ = true;

}



}