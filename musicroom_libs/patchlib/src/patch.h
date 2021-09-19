// Touhou Vorbis Compressor
// Shared patch library
// ------------------------
// patch.h - Import Address Table Patching functions and DLL function declaration/definition macros
// ------------------------
// "©" Nmlgc, 2011

#ifndef PATCHLIB_PATCH_H
#define PATCHLIB_PATCH_H

// Writes [Val] to [ptr] in the address space of the current process,
// if the current value in [ptr] equals [Prev]
int PatchDWORD(DWORD ptr, DWORD Prev, DWORD Val);

// Low-level patching
// ------------------
// Replaces the function pointer of [pThunk] with [pNewFunc]
int PatchFunc(PIMAGE_THUNK_DATA pThunk, void* pNewFunc);

// Searches for [cOrigFuncName] starting from [pOrigFirstThunk].
// Only used on Win9x, where patching by pointer doesn't seem to work
int PatchFuncByName(HMODULE hMod, PIMAGE_THUNK_DATA pOrigFirstThunk, PIMAGE_THUNK_DATA pImpFirstThunk, char* cOrigFuncName, void* pNewFunc);

// Searches for [pOrigFunc] starting from [pImpFirstThunk], and replaces it with [pNewFunc] if found
int PatchFuncByPtr(PIMAGE_THUNK_DATA pImpFirstThunk, void* pOrigFunc, void* pNewFunc);
// ------------------

// PE structures
// -------------
// Returns the IMAGE_NT_HEADERS structure of [hMod]
PIMAGE_NT_HEADERS WINAPI GetNtHeader(HMODULE hMod);

// Returns the import descriptor of [DLLName]
PIMAGE_IMPORT_DESCRIPTOR WINAPI GetDllImportDesc(HMODULE hMod, const char* DllName);

// Returns the section header named [SectionName]
PIMAGE_SECTION_HEADER WINAPI GetSectionHeader(HMODULE hMod, const char* SectionName);
// -------------

// DLL function macros
// -------------------

// For external DLL functions, the form [(dll)_(func)] is used for the individual function pointers.

#define DLL_FUNC(dll, func)			dll##_##func
#define DLL_FUNC_TYPE(dll, func)	DLL_FUNC(dll, func)##_type

#define DLL_FUNC_DEC(dll, func)	extern DLL_FUNC_TYPE(dll, func) DLL_FUNC(dll, func)
#define DLL_FUNC_DEF(dll, func)	 DLL_FUNC_TYPE(dll, func) DLL_FUNC(dll, func) = NULL

#define DLL_GET_PROC_ADDRESS(handle, dll, func)	DLL_FUNC(dll, func) = (DLL_FUNC_TYPE(dll, func))GetProcAddress(handle, #func)
#define DLL_GET_PROC_ADDRESS_STDCALL(handle, dll, func, name)	DLL_FUNC(dll, func) = (DLL_FUNC_TYPE(dll, func))GetProcAddress(handle, name); if(!DLL_FUNC(dll, func))	MessageBox(NULL, "Function <" name "> not found!", "patchlib", MB_ICONEXCLAMATION | MB_OK);
// -------------------

// High-level patching
// -------------------
// Information about a single function to patch
typedef struct
{
	char* old_func;
	void* old_ptr;
	void* new_ptr;
}
func_patch_t;
// Convenience function to set a single func_patch_t entry
void SetFuncPatch(func_patch_t* patch, char* old_func, void* old_ptr, void* new_ptr);

// Patches [FuncPatchCount] functions in the [FuncPatch] array
int PatchDllFuncs(HMODULE hMod, char* DllName, func_patch_t* FuncPatch, UINT FuncPatchCount);
// -------------------

#endif /* PATCHLIB_PATCH_H */
