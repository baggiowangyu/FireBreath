/**********************************************************\ 
Original Author: Richard Bateman (taxilian)

Created:    Oct 16, 2009
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 Richard Bateman, Firebreath development team
\**********************************************************/

#pragma once
#ifndef H_NPJAVASCRIPTOBJECT
#define H_NPJAVASCRIPTOBJECT

#include "APITypes.h"
#include "JSAPI.h"
#include "NpapiTypes.h"
#include "NpapiBrowserHost.h"
#include "JSFunction.h"

namespace FB { namespace Npapi {
    class NPJavascriptObject :
        public NPObject
    {
    public:
        static bool isNPJavaScriptObject(const NPObject* const npo);
    
    protected:
        static NPClass NPJavascriptObjectClass;
        FB::JSAPIWeakPtr m_api;
        NpapiBrowserHostPtr m_browser;
        bool m_valid;

    public:
        static NPJavascriptObject *NewObject(NpapiBrowserHostPtr host, FB::JSAPIWeakPtr api);
        void setAPI(FB::JSAPIWeakPtr api, NpapiBrowserHostPtr host);
        FB::JSAPIPtr getAPI() const;
        virtual ~NPJavascriptObject(void);

    private:
        NPJavascriptObject(NPP npp);

    protected:
        void Invalidate();
        bool HasMethod(NPIdentifier name);
        bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
        bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);
        bool HasProperty(NPIdentifier name);
        bool GetProperty(NPIdentifier name, NPVariant *result);
        bool SetProperty(NPIdentifier name, const NPVariant *value);
        bool RemoveProperty(NPIdentifier name);
        bool Enumeration(NPIdentifier **value, uint32_t *count);
        bool Construct(const NPVariant *args, uint32_t argCount, NPVariant *result);

    public:
        // Static methods referenced in the NPClass
        static NPObject *Allocate(NPP npp, NPClass *aClass);
        static void _Deallocate(NPObject *npobj);
        static void _Invalidate(NPObject *npobj);
        static bool _HasMethod(NPObject *npobj, NPIdentifier name);
        static bool _Invoke(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
        static bool _InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);
        static bool _HasProperty(NPObject *npobj, NPIdentifier name);
        static bool _GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result);
        static bool _SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value);
        static bool _RemoveProperty(NPObject *npobj, NPIdentifier name);
        static bool _Enumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count);
        static bool _Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);

    public:
        FB_FORWARD_PTR(NPO_addEventListener);
        FB_FORWARD_PTR(NPO_removeEventListener);
        friend class NPO_addEventListener;
        friend class NPO_removeEventListener;
        NPO_addEventListenerPtr m_addEventFunc;
        NPO_removeEventListenerPtr m_removeEventFunc;

        class NPO_addEventListener : public FB::JSFunction
        {
        public:
            NPO_addEventListener(NPJavascriptObject* ptr)
                : FB::JSFunction(FB::JSAPIPtr(), "attachEvent"), obj(ptr) { }
            FB::variant exec(const std::vector<variant>& args);
        private:
            NPJavascriptObject* obj;
        };
        class NPO_removeEventListener : public FB::JSFunction
        {
        public:
            NPO_removeEventListener(NPJavascriptObject* ptr)
                : FB::JSFunction(FB::JSAPIPtr(), "detachEvent"), obj(ptr) { }
            FB::variant exec(const std::vector<variant>& args);
        private:
            NPJavascriptObject* obj;
        };
    };

}; };

#endif
