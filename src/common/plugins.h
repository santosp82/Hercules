// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef	_PLUGINS_H_
#define _PLUGINS_H_

#include "../common/plugin.h"

////// Dynamic Link Library functions ///////////////

#ifdef WIN32

	#include <windows.h>
	#define DLL_OPEN(x)		LoadLibrary(x)
	#define DLL_SYM(x,y,z)	(FARPROC)(x) = GetProcAddress(y,z)
	#define DLL_CLOSE(x)	FreeLibrary(x)
	char *DLL_ERROR(void);

	#define DLL_EXT			".dll"
	#define DLL				HINSTANCE

#else

	#include <dlfcn.h>
	#define DLL_OPEN(x)		dlopen(x,RTLD_NOW)
	#define DLL_SYM(x,y,z)	(x) = (void *)dlsym(y,z)
	#define DLL_CLOSE(x)	dlclose(x)
	#define DLL_ERROR		dlerror

	#ifdef CYGWIN
		#define DLL_EXT		".dll"
	#else
		#define DLL_EXT		".so"
	#endif
	#define DLL				void *

	#include <string.h> // size_t

#endif

////// Plugin Definitions ///////////////////

typedef struct _Plugin {
	DLL dll;
	char state;
	char* filename;
	struct _Plugin_Info* info;
	struct _Plugin* next;	
} Plugin;

/////////////////////////////////////////////

int register_plugin_func(char* name);
int register_plugin_event(Plugin_Event_Func* func, char* name);
int plugin_event_trigger(char* name);

int export_symbol(void* var, size_t offset);
#define EXPORT_SYMBOL(s)	export_symbol((s), -1);

Plugin* plugin_open(const char* filename);
void plugin_load(const char* filename);
void plugin_unload(Plugin* plugin);
void plugins_init(void);
void plugins_final(void);

#endif /* _PLUGINS_H_ */
