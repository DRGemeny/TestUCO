#include "HardwareInterface.h"
#ifdef STUB_MODE
#include <iostream>
#endif
#if defined(Q_WS_WIN)

#include <windows.h>

typedef int (__stdcall *TOpenInterface)(char*,void**);
typedef int (__stdcall *TCloseInterface)(void*);

typedef int (__stdcall *TWaitEndStatus)(void*, unsigned int, double*, double);
typedef int (__stdcall *TGlobalReset)(void*, unsigned int);

typedef int (__stdcall *TReadCOReg) (void*, unsigned int, unsigned int, unsigned int*);
typedef int (__stdcall *TWriteCOReg)(void*, unsigned int, unsigned int, unsigned int);
#ifdef DEPRECATED_API
typedef int (__stdcall *TReadCOReg_nocap) (void*, unsigned int, unsigned int, unsigned int*);
typedef int (__stdcall *TWriteCOReg_nocap)(void*, unsigned int, unsigned int, unsigned int);
#endif
typedef int (__stdcall *TWriteBufferCOReg)(void*, unsigned int, unsigned int, unsigned int, unsigned int*);
typedef int (__stdcall *TReadBufferCOReg)(void*, unsigned int, unsigned int, unsigned int, unsigned int*);

#ifdef DEPRECATED_API
typedef int (__stdcall *TReadCOMem64) (void*, unsigned int, unsigned int, unsigned __int64*);
typedef int (__stdcall *TWriteCOMem64)(void*, unsigned int, unsigned int, unsigned __int64*);
#endif

typedef int (__stdcall *TReadCOMem32) (void*, unsigned int, unsigned int, unsigned int*);
typedef int (__stdcall *TWriteCOMem32)(void*, unsigned int, unsigned int, unsigned int*);

typedef int (__stdcall *TReadDMCReg64) (void*, unsigned int, unsigned int, unsigned int, unsigned __int64*);
typedef int (__stdcall *TWriteDMCReg64)(void*, unsigned int, unsigned int, unsigned int, unsigned __int64);
typedef int (__stdcall *TReadDMCReg) (void*, unsigned int, unsigned int, unsigned int, unsigned int*);
typedef int (__stdcall *TWriteDMCReg)(void*, unsigned int, unsigned int, unsigned int, unsigned int);

typedef int (__stdcall *TReadMem64Fast) (void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned __int64*);
typedef int (__stdcall *TReadMemFast) (void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int*);
typedef int (__stdcall *TWriteMem64Fast)(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned __int64*);
typedef int (__stdcall *TWriteMemFast)(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int*);

typedef int (__stdcall *TLoadFileFast) (void*, unsigned int, char*);
typedef int (__stdcall *TLoadFile64Fast) (void*, unsigned int, char*);
typedef int (__stdcall *TCheckLoadFile) (void*, unsigned int, char*);
#ifdef DEPRECATED_API
typedef int (__stdcall *TCaptureChannel)(void*);
typedef int (__stdcall *TFreeChannel)(void*);
#endif
typedef int (__stdcall *TSpecBuffAlloc)(void*, int, void**);
typedef int (__stdcall *TSpecBuffFree)(void*, int, void*);

typedef int (__stdcall *TReadBAR3)(void*, int, unsigned short *);
typedef int (__stdcall *TWriteBAR3)(void*, int, unsigned short);

typedef int (__stdcall *TGetVer)(void*, void**);

typedef int (__stdcall *TWriteCOCmd) (void *, unsigned int, unsigned int);
typedef int (__stdcall *TReadCOCmd) (void *, unsigned int, unsigned int*);

typedef int (__stdcall *TReadBufferCODataReg) (void*, unsigned int, unsigned int, unsigned int*);
typedef int (__stdcall *TWriteBufferCODataReg) (void*, unsigned int, unsigned int, unsigned int*);

typedef int (__stdcall *TRunDMC) (void*, unsigned int);
typedef int (__stdcall *TStopDMC) (void*, unsigned int);


#ifdef DEPRECATED_API
TCaptureChannel			CaptureChannelProcAddr = NULL;
TFreeChannel			FreeChannelProcAddr = NULL;
#endif
TOpenInterface			OpenInterfaceProcAddr = NULL;
TCloseInterface			CloseInterfaceProcAddr = NULL;

TWaitEndStatus			WaitEndStatusProcAddr = NULL;
TGlobalReset			GlobalResetProcAddr = NULL;

TReadCOReg				ReadCORegProcAddr = NULL;
TWriteCOReg				WriteCORegProcAddr = NULL;
#ifdef DEPRECATED_API
TReadCOReg_nocap		ReadCOReg_nocapProcAddr = NULL;
TWriteCOReg_nocap		WriteCOReg_nocapProcAddr = NULL;
TReadCOMem64			ReadCOMem64ProcAddr = NULL;
TWriteCOMem64			WriteCOMem64ProcAddr = NULL;
#endif
TReadCOMem32			ReadCOMem32ProcAddr = NULL;
TWriteCOMem32			WriteCOMem32ProcAddr = NULL;

TWriteBufferCOReg		WriteBufferCORegProcAddr = NULL;
TReadBufferCOReg		ReadBufferCORegProcAddr = NULL;

TReadDMCReg64			ReadDMCReg64ProcAddr = NULL;
TWriteDMCReg64			WriteDMCReg64ProcAddr = NULL;

TReadDMCReg             ReadDMCRegProcAddr = NULL;
TWriteDMCReg            WriteDMCRegProcAddr = NULL;

TReadMem64Fast			ReadMem64FastProcAddr = NULL;
TReadMemFast			ReadMemFastProcAddr = NULL;
TWriteMem64Fast			WriteMem64FastProcAddr = NULL;
TWriteMemFast			WriteMemFastProcAddr = NULL;

TLoadFileFast			LoadFileFastProcAddr = NULL;
TLoadFile64Fast			LoadFile64FastProcAddr = NULL;
#ifdef DEPRECATED_API
TCheckLoadFile			CheckLoadFileProcAddr = NULL;
#endif
TSpecBuffAlloc			SpecBuffAllocProcAddr = NULL;
TSpecBuffFree			SpecBuffFreeProcAddr = NULL;

TReadBAR3               ReadBAR3ProcAddr = NULL;
TWriteBAR3              WriteBAR3ProcAddr = NULL;

TGetVer                 GetVerProcAddr = NULL;

TWriteCOCmd             WriteCOCmdAddr = NULL;
TReadCOCmd              ReadCOCmdAddr = NULL;

TReadBufferCODataReg    ReadBufferCODataRegAddr = NULL;
TWriteBufferCODataReg   WriteBufferCODataRegAddr = NULL;

TRunDMC    RunDMCAddr = NULL;
TStopDMC   StopDMCAddr = NULL;

HINSTANCE IOAModule = NULL;

int LoadHardwareInterfaceDll(){
	
	IOAModule=LoadLibrary(TEXT("HardwareInterface"));
    if (IOAModule==NULL) return brFailed;
#ifdef DEPRECATED_API
	CaptureChannelProcAddr = (TCaptureChannel)GetProcAddress(IOAModule,"CaptureChannel");

	FreeChannelProcAddr = (TFreeChannel)GetProcAddress(IOAModule,"FreeChannel");
#endif
	OpenInterfaceProcAddr=(TOpenInterface)GetProcAddress(IOAModule,"OpenInterface");

	CloseInterfaceProcAddr=(TCloseInterface)GetProcAddress(IOAModule,"CloseInterface");

	WaitEndStatusProcAddr=(TWaitEndStatus)GetProcAddress(IOAModule,"WaitEndStatus");

	GlobalResetProcAddr=(TGlobalReset)GetProcAddress(IOAModule,"GlobalReset");

	ReadCORegProcAddr=(TReadCOReg)GetProcAddress(IOAModule,"ReadCOReg");

	WriteCORegProcAddr=(TWriteCOReg)GetProcAddress(IOAModule,"WriteCOReg");
#ifdef DEPRECATED_API
	ReadCOReg_nocapProcAddr=(TReadCOReg_nocap)GetProcAddress(IOAModule,"ReadCOReg_nocap");

	WriteCOReg_nocapProcAddr=(TWriteCOReg_nocap)GetProcAddress(IOAModule,"WriteCOReg_nocap");

	ReadCOMem64ProcAddr=(TReadCOMem64)GetProcAddress(IOAModule,"ReadCOMem64");

	WriteCOMem64ProcAddr=(TWriteCOMem64)GetProcAddress(IOAModule,"WriteCOMem64");
#endif
	ReadCOMem32ProcAddr=(TReadCOMem32)GetProcAddress(IOAModule,"ReadCOMem32");

	WriteCOMem32ProcAddr=(TWriteCOMem32)GetProcAddress(IOAModule,"WriteCOMem32");

	WriteBufferCORegProcAddr=(TWriteBufferCOReg)GetProcAddress(IOAModule,"WriteBufferCOReg");

	ReadBufferCORegProcAddr=(TReadBufferCOReg)GetProcAddress(IOAModule,"ReadBufferCOReg");

	ReadDMCReg64ProcAddr=(TReadDMCReg64)GetProcAddress(IOAModule,"ReadDMCReg64");

    ReadDMCRegProcAddr=(TReadDMCReg)GetProcAddress(IOAModule,"ReadDMCReg");

	WriteDMCReg64ProcAddr=(TWriteDMCReg64)GetProcAddress(IOAModule,"WriteDMCReg64");

    WriteDMCRegProcAddr=(TWriteDMCReg)GetProcAddress(IOAModule,"WriteDMCReg");

	ReadMem64FastProcAddr=(TReadMem64Fast)GetProcAddress(IOAModule,"ReadMem64Fast");

    ReadMemFastProcAddr=(TReadMemFast)GetProcAddress(IOAModule,"ReadMemFast");

	WriteMem64FastProcAddr=(TWriteMem64Fast)GetProcAddress(IOAModule,"WriteMem64Fast");

    WriteMemFastProcAddr=(TWriteMemFast)GetProcAddress(IOAModule,"WriteMemFast");

	LoadFileFastProcAddr=(TLoadFileFast)GetProcAddress(IOAModule,"LoadFileFast");

    LoadFile64FastProcAddr=(TLoadFile64Fast)GetProcAddress(IOAModule,"LoadFile64Fast");

#ifdef DEPRECATED_API
	CheckLoadFileProcAddr=(TCheckLoadFile)GetProcAddress(IOAModule,"CheckLoadFile");
#endif
	SpecBuffAllocProcAddr=(TSpecBuffAlloc)GetProcAddress(IOAModule,"SpecBuffAlloc");

	SpecBuffFreeProcAddr=(TSpecBuffFree)GetProcAddress(IOAModule,"SpecBuffFree");

    ReadBAR3ProcAddr=(TReadBAR3)GetProcAddress(IOAModule,"ReadBAR3");

    WriteBAR3ProcAddr=(TWriteBAR3)GetProcAddress(IOAModule,"WriteBAR3");

    GetVerProcAddr=(TGetVer)GetProcAddress(IOAModule,"GetVer");

    WriteCOCmdAddr=(TWriteCOCmd)GetProcAddress(IOAModule,"WriteCOCmd");

    ReadCOCmdAddr=(TReadCOCmd)GetProcAddress(IOAModule,"ReadCOCmd");

    ReadBufferCODataRegAddr = (TReadBufferCODataReg)GetProcAddress(IOAModule,"ReadBufferCODataReg");

    WriteBufferCODataRegAddr=(TWriteBufferCODataReg)GetProcAddress(IOAModule,"WriteBufferCODataReg");

	return 0;
}

#ifdef DEPRECATED_API
int CaptureChannel(void * handle){
    if (CaptureChannelProcAddr == NULL)
        return brFailed;

	return CaptureChannelProcAddr(handle);
}

int FreeChannel(void * handle){
    if (FreeChannelProcAddr == NULL)
        return brFailed;

    return FreeChannelProcAddr(handle);
}
#endif

int FreeHardwareInterfaceDll(){
	BOOL rs;
	rs=FreeLibrary(IOAModule);
	if (!rs) return 2;
	else return 0;
}

int OpenInterface(char * ip, void ** handle){
#ifdef STUB_MODE
	std::cout << "OpenInterface stub called." << std::endl;
	return 0;
#else
	int res;
	if (IOAModule == NULL){
		res = LoadHardwareInterfaceDll();
		if (res != 0) return res;
	};

	if (OpenInterfaceProcAddr == NULL)
		return brFailed;

	return OpenInterfaceProcAddr(ip, handle);
#endif	
}

int CloseInterface(void * handle){
#ifdef STUB_MODE
	std::cout << "CloseInterface stub called." << std::endl;
	return 0;
#else
	int res1,res2;

    if (CloseInterfaceProcAddr == NULL)
        return brFailed;

    res1=CloseInterfaceProcAddr(handle);
        //res2=FreeHardwareInterfaceDll();
	if (res1!=0) return res1;
        //if (res2!=0) return res2;
	return 0;
#endif
}

int WaitEndStatus (void * handle, unsigned int BmId, double* time, double timeout){
#ifdef STUB_MODE
	std::cout << "WaitEndStatus stub called." <<  
		" BmId = " << BmId	<<
		". timeout = " << timeout <<
		std::endl;
	return 0;
#else
    if (WaitEndStatusProcAddr == NULL)
        return brFailed;

	return WaitEndStatusProcAddr(handle, BmId, time, timeout);
#endif
}

int GlobalReset (void * handle, unsigned int BmId){
#ifdef STUB_MODE
	std::cout << "GlobalReset stub called." <<
		" BmId = " << BmId <<		
		std::endl;
	return 0;
#else
    if (GlobalResetProcAddr == NULL)
        return brFailed;

    return GlobalResetProcAddr(handle, BmId);
#endif
}

int ReadCOReg (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int* value){
#ifdef STUB_MODE
	std::cout << 
		"ReadCOReg stub called. " <<
		"BmId = "<< 
		BmId << 
		". RegCode = " <<
		RegCode << 
		std::endl;
	if (value)
	{
		if (0x18 == RegCode)
		{
			*value = 0xE0;
		}
		else 
		{
			*value = 12345;
		}
		
	}
	return 0;
#else
	if (ReadCORegProcAddr == NULL)
		return brFailed;

	return ReadCORegProcAddr(handle, BmId, RegCode, value);
#endif
}

int WriteCOReg (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int value){
#ifdef STUB_MODE
	std::cout <<
		"WriteCOReg stub called. " <<
		"BmId = " <<
		BmId <<
		". RegCode = " <<
		RegCode <<
		". value = " << 
		value << 
		std::endl;
	return 0;
#else
	if (WriteCORegProcAddr == NULL)
        return brFailed;

    return WriteCORegProcAddr(handle, BmId, RegCode, value);
#endif
}
#ifdef DEPRECATED_API
int ReadCOReg_nocap (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int* value){
    if (ReadCOReg_nocapProcAddr == NULL)
        return brFailed;

    return ReadCOReg_nocapProcAddr(handle, BmId, RegCode, value);
}

int WriteCOReg_nocap (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int value){
    if (WriteCOReg_nocapProcAddr == NULL)
        return brFailed;

    return WriteCOReg_nocapProcAddr(handle, BmId, RegCode, value);
}

int ReadCOMem64 (void* handle, unsigned int BmId, unsigned int count, unsigned __int64* value){
    if (ReadCOMem64ProcAddr == NULL)
        return brFailed;

    return ReadCOMem64ProcAddr(handle, BmId, count, value);
}

int WriteCOMem64 (void* handle, unsigned int BmId, unsigned int count, unsigned __int64* value){
    if (WriteCOMem64ProcAddr == NULL)
        return brFailed;

    return WriteCOMem64ProcAddr(handle, BmId, count, value);
}
#endif
int ReadCOMem32 (void* handle, unsigned int BmId, unsigned int count, unsigned int* value){
#ifdef STUB_MODE
	std::cout <<
		"ReadCOMem32 stub called. " <<
		"BmId = " << BmId <<
		". count = " << count <<
		std::endl;	
	return 0;
#else
    if (ReadCOMem32ProcAddr == NULL)
        return brFailed;

    return ReadCOMem32ProcAddr(handle, BmId, count, value);
#endif
}

int WriteCOMem32 (void* handle, unsigned int BmId, unsigned int count, unsigned int* value){
#ifdef STUB_MODE
	std::cout <<
		"WriteCOMem32 stub called. " <<
		"BmId = " << BmId <<
		". count = " << count <<
		std::endl;
	return 0;
#else
    if (WriteCOMem32ProcAddr == NULL)
        return brFailed;

    return WriteCOMem32ProcAddr(handle, BmId, count, value);
#endif
}

int WriteBufferCOReg(void * handle, unsigned int BmId, unsigned int RegCode, unsigned int count, unsigned int* buffer){
#ifdef STUB_MODE
	std::cout <<
		"WriteBufferCOReg stub called. " <<
		"BmId = " << BmId <<
		". RegCode = " << RegCode <<
		". count = " << count <<
		std::endl;
	return 0;
#else
    if (WriteBufferCORegProcAddr == NULL)
        return brFailed;

    return WriteBufferCORegProcAddr(handle, BmId, RegCode, count, buffer);
#endif
}

int ReadBufferCOReg(void * handle, unsigned int BmId, unsigned int RegCode, unsigned int count, unsigned int* buffer){
#ifdef STUB_MODE
	std::cout <<
		"ReadBufferCOReg stub called. " <<
		"BmId = " << BmId <<
		". RegCode = " << RegCode <<
		". count = " << count <<
		std::endl;
	return 0;
#else
    if (ReadBufferCORegProcAddr == NULL)
        return brFailed;

    return ReadBufferCORegProcAddr(handle, BmId, RegCode, count, buffer);
#endif
}

int ReadDMCReg64(void* handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned __int64* value)
{
#ifdef STUB_MODE
	std::cout <<
		"ReadDMCReg64 stub called. " <<
		"BmId = " << BmId <<
		". RegCode = " << RegCode <<
		". DMCNumber = " << DMCNumber <<
		std::endl;
	return 0;
#else
    if (ReadDMCReg64ProcAddr == NULL)
        return brFailed;

    return ReadDMCReg64ProcAddr(handle, BmId, RegCode, DMCNumber, value);
#endif
}

int ReadDMCReg(void* handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned int* value)
{
#ifdef STUB_MODE
	std::cout <<
		"ReadDMCReg stub called. " <<
		"BmId = " << BmId <<
		". RegCode = " << RegCode <<
		". DMCNumber = " << DMCNumber <<
		std::endl;
	return 0;
#else
    if (ReadDMCRegProcAddr == NULL)
        return brFailed;

    return ReadDMCRegProcAddr(handle, BmId, RegCode, DMCNumber, value);
#endif
}

int WriteDMCReg64(void* handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned __int64 value)
{
#ifdef STUB_MODE
	std::cout <<
		"WriteDMCReg64 stub called. " <<
		"BmId = " << BmId <<
		". RegCode = " << RegCode <<
		". DMCNumber = " << DMCNumber <<
		std::endl;
	return 0;
#else
    if (WriteDMCReg64ProcAddr == NULL)
        return brFailed;

    return WriteDMCReg64ProcAddr(handle, BmId, RegCode, DMCNumber, value);
#endif
}

int WriteDMCReg(void* handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned int value)
{
#ifdef STUB_MODE
	std::cout <<
		"WriteDMCReg stub called. " <<
		"BmId = " << BmId <<
		". RegCode = " << RegCode <<
		". DMCNumber = " << DMCNumber <<
		". value = " << value <<
		std::endl;
	return 0;
#else
    if (WriteDMCRegProcAddr == NULL)
        return brFailed;

    return WriteDMCRegProcAddr(handle, BmId, RegCode, DMCNumber, value);
#endif
}

int ReadMem64Fast(void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned __int64* value)
{
#ifdef STUB_MODE
	std::cout <<
		"ReadMem64Fast stub called. " <<
		"BmId = " << BmId <<
		". code = " << code <<
		". DMC_Num = " << DMC_Num <<
		". addr = " << addr <<
		". step = " << step <<
		". count = " << count <<
		std::endl;
	return 0;
#else
	if (ReadMem64FastProcAddr == NULL)
        return brFailed;

    return ReadMem64FastProcAddr(handle, BmId, code, DMC_Num, addr, step, count, value);
#endif
}

int ReadMemFast(void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned int* value)
{
#ifdef STUB_MODE
	std::cout <<
		"ReadMemFast stub called. " <<
		"BmId = " << BmId <<
		". code = " << code <<
		". DMC_Num = " << DMC_Num <<
		". addr = " << addr <<
		". step = " << step <<
		". count = " << count <<
		std::endl;
	return 0;
#else
	if (ReadMemFastProcAddr == NULL)
        return brFailed;

    return ReadMemFastProcAddr(handle, BmId, code, DMC_Num, addr, step, count, value);
#endif
}

int WriteMem64Fast(void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned __int64* value)
{
#ifdef STUB_MODE
	std::cout <<
		"WriteMem64Fast stub called. " <<
		"BmId = " << BmId <<
		". code = " << code <<
		". DMC_Num = " << DMC_Num <<
		". addr = " << addr <<
		". step = " << step <<
		". count = " << count <<
		std::endl;
	return 0;
#else
	if (WriteMem64FastProcAddr == NULL)
        return brFailed;

    return WriteMem64FastProcAddr(handle, BmId, code, DMC_Num, addr, step, count, value);
#endif
}

int WriteMemFast(void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned int* value)
{
#ifdef STUB_MODE
	std::cout <<
		"WriteMem64Fast stub called. " <<
		"BmId = " << BmId <<
		". code = " << code <<
		". DMC_Num = " << DMC_Num <<
		". addr = " << addr <<
		". step = " << step <<
		". count = " << count <<
		std::endl;
	return 0;
#else
    if (WriteMemFastProcAddr == NULL)
        return brFailed;

    return WriteMemFastProcAddr(handle, BmId, code, DMC_Num, addr, step, count, value);
#endif
}

int LoadFileFast(void * handle, unsigned int BmId, char* FileName)
{
#ifdef STUB_MODE
	std::cout <<
		"LoadFileFast stub called. " <<
		"BmId = " << BmId <<
		". FileName = " << FileName <<		
		std::endl;
	return 0;
#else
    if (LoadFileFastProcAddr == NULL)
        return brFailed;

    return LoadFileFastProcAddr(handle, BmId, FileName);
#endif
}

int LoadFile64Fast(void * handle, unsigned int BmId, char* FileName)
{
#ifdef STUB_MODE
	std::cout <<
		"LoadFileFast stub called. " <<
		"BmId = " << BmId <<
		". FileName = " << FileName <<
		std::endl;
	return 0;
#else
    if (LoadFile64FastProcAddr == NULL)
        return brFailed;

    return LoadFile64FastProcAddr(handle, BmId, FileName);
#endif
}

#ifdef DEPRECATED_API
int CheckLoadFile(void * handle, unsigned int BmId, char* FileName){
    if (CheckLoadFileProcAddr == NULL)
        return brFailed;

    return CheckLoadFileProcAddr(handle, BmId, FileName);
}
#endif
int SpecBuffAlloc(void * handle, int count, void ** buff){
#ifdef STUB_MODE
	std::cout <<
		"SpecBuffAlloc stub called. " <<
		"count = " << count <<		
		std::endl;
	return 0;
#else
    if (SpecBuffAllocProcAddr == NULL)
        return brFailed;

    return SpecBuffAllocProcAddr(handle, count, buff);
#endif
}

int SpecBuffFree(void * handle, int count, void * buff){
#ifdef STUB_MODE
	std::cout <<
		"SpecBuffFree stub called. " <<
		"count = " << count <<
		std::endl;
	return 0;
#else
    if (SpecBuffFreeProcAddr == NULL)
        return brFailed;

    return SpecBuffFreeProcAddr(handle, count, buff);
#endif
}

int ReadBAR3(void * handle, unsigned int index, unsigned short * value){

#ifdef STUB_MODE
	std::cout <<
		"ReadBAR3 stub called. " <<
		"index = " <<
		index << 
		std::endl;
	if (value)
	{
		*value = 12345;
	}
	return 0;
#else
	if (ReadBAR3ProcAddr == NULL)
        return brFailed;

    return ReadBAR3ProcAddr(handle, index, value);
#endif
} 

int WriteBAR3(void * handle, unsigned int index, unsigned short value){
#ifdef STUB_MODE
	std::cout <<
		"WriteBAR3 stub called. " <<
		"index = " <<
		index << 
		". value = " <<
		value <<
		std::endl;
	return 0;
#else
	if (WriteBAR3ProcAddr == NULL)
        return brFailed;

    return WriteBAR3ProcAddr(handle, index, value);
#endif
} 

int GetVersions(void * handle, void ** buffer){
    if (GetVerProcAddr == NULL)
        return brFailed;

    return GetVerProcAddr(handle, buffer);
}

int WriteCOCmd (void * handle, unsigned int BmId, unsigned int value){
#ifdef STUB_MODE
	std::cout <<
		"WriteCOCmd stub called. " <<
		"BmId = " << BmId <<
		". value = " << value <<
		std::endl;
	return 0;
#else
    if (WriteCOCmdAddr == NULL)
        return brFailed;

    return WriteCOCmdAddr(handle, BmId, value);
#endif
}

int ReadCOCmd (void * handle, unsigned int BmId, unsigned int * value){
#ifdef STUB_MODE
	std::cout <<
		"ReadCOCmd stub called. " <<
		"BmId = " << BmId <<
		std::endl;
	if (value)
	{
		*value = 12345;
    }
	return 0;
#else
    if (ReadCOCmdAddr == NULL)
        return brFailed;

    return ReadCOCmdAddr(handle, BmId, value);
#endif
}

int ReadBufferCODataReg (void * handle, unsigned int BmId, unsigned int size, unsigned int* buffer){
#ifdef STUB_MODE
	std::cout <<
		"ReadBufferCODataReg stub called. " <<
		"BmId = " << BmId <<
		". size = " << size <<		
		std::endl;
	
	return 0;
#else
    if (ReadBufferCODataRegAddr == NULL)
        return brFailed;

    return ReadBufferCODataRegAddr(handle, BmId, size, buffer);
#endif
}

int WriteBufferCODataReg (void * handle, unsigned int BmId, unsigned int size, unsigned int* buffer){
#ifdef STUB_MODE
	std::cout <<
		"WriteBufferCODataReg stub called. " <<
		"BmId = " << BmId <<
		". size = " << size <<
		std::endl;

	return 0;
#else
    if (WriteBufferCODataRegAddr == NULL)
        return brFailed;

    return WriteBufferCODataRegAddr(handle, BmId, size, buffer);
#endif
}

int RunDMC (void * handle, unsigned int BmId){
#ifdef STUB_MODE
	std::cout <<
		"RunDMC stub called. " <<
		"BmId = " << BmId <<		
		std::endl;

	return 0;
#else
    if (RunDMCAddr == NULL)
        return brFailed;

    return RunDMCAddr(handle, BmId);
#endif
}

int StopDMC (void * handle, unsigned int BmId){
#ifdef STUB_MODE
	std::cout <<
		"StopDMC stub called. " <<
		"BmId = " << BmId <<
		std::endl;

	return 0;
#else
    if (StopDMCAddr == NULL)
        return brFailed;

    return StopDMCAddr(handle, BmId);
#endif
}
#else

#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <features.h>
#include <string.h>
#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

static void            *dll_handle = NULL;
static char            *error;

#if defined(NEED_FAST)
static const char      libname[] = "HardwareInterface_fast.so";
#else
static const char      libname[] = "HardwareInterface.so";
#endif

static int             res;

int (*ptr_OpenInterface)(char *, void **) = NULL;
int (*ptr_CloseInterface)(void *) = NULL;

int (*ptr_ReadBAR3)(void *, unsigned int, unsigned short *) = NULL;
int (*ptr_WriteBAR3)(void *, unsigned int, unsigned short) = NULL;
#ifdef DEPRECATED_API
int (*ptr_CaptureChannel)(void *) = NULL;
int (*ptr_FreeChannel)(void *) = NULL;
int (*ptr_WriteCOReg_nocap)(void *, unsigned int, unsigned int, unsigned int) = NULL;
int (*ptr_ReadCOReg_nocap)(void *, unsigned int, unsigned int, unsigned int *) = NULL;
#endif
int (*ptr_WriteCOReg)(void *, unsigned int, unsigned int, unsigned int) = NULL;
int (*ptr_WriteBufferCOReg)(void *, unsigned int, unsigned int, unsigned int, unsigned int *) = NULL;
int (*ptr_ReadCOReg)(void *, unsigned int, unsigned int, unsigned int *) = NULL;
int (*ptr_ReadBufferCOReg)(void *, unsigned int, unsigned int, unsigned int, unsigned int *) = NULL;

int (*ptr_ReadDMCReg64)(void*, unsigned int, unsigned int, unsigned int, unsigned __int64 *) = NULL;
int (*ptr_WriteDMCReg64)(void*, unsigned int, unsigned int, unsigned int, unsigned __int64) = NULL;

int (*ptr_ReadDMCReg)(void*, unsigned int, unsigned int, unsigned int, unsigned int*) = NULL;
int (*ptr_WriteDMCReg)(void*, unsigned int, unsigned int, unsigned int, unsigned int) = NULL;

int (*ptr_ReadMem64Fast)(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned __int64 *) = NULL;
int (*ptr_ReadMemFast)(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int *) = NULL;
int (*ptr_WriteMem64Fast)(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned __int64 *) = NULL;
int (*ptr_WriteMemFast)(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int*) = NULL;

int (*ptr_SpecBuffAlloc)(void *, int, void **) = NULL;
int (*ptr_SpecBuffFree)(void *, int, void*) = NULL;

int (*ptr_GlobalReset)(void *, unsigned int) = NULL;
int (*ptr_WaitEndStatus)(void *, unsigned int, double* , double) = NULL;

int (*ptr_ReadCOMem32)(void *, unsigned int, unsigned int, unsigned int *) = NULL;
int (*ptr_WriteCOMem32)(void *, unsigned int, unsigned int, unsigned int *) = NULL;
#ifdef DEPRECATED_API
int (*ptr_ReadCOMem64)(void *, unsigned int, unsigned int, unsigned __int64 *) = NULL;
int (*ptr_WriteCOMem64)(void *, unsigned int, unsigned int, unsigned __int64 *) = NULL;
#endif
int (*ptr_LoadFileFast) (void*, unsigned int, char*) = NULL;
int (*ptr_LoadFile64Fast) (void*, unsigned int, char*) = NULL;

#ifdef DEPRECATED_API
int (*ptr_CheckLoadFile) (void*, unsigned int, char*) = NULL;
#endif

int (*ptr_GetVer) (void*, void**) = NULL;

int (*ptr_WriteCOCmd) (void*, unsigned int, unsigned int) = NULL;

int (*ptr_ReadCOCmd) (void*, unsigned int, unsigned int*) = NULL;

int (*ptr_ReadBufferCODataReg) (void*, unsigned int, unsigned int, unsigned int*) = NULL;

int (*ptr_WriteBufferCODataReg) (void*, unsigned int, unsigned int, unsigned int*) = NULL;

int (*ptr_RunDMC) (void*, unsigned int) = NULL;

int (*ptr_StopDMC) (void*, unsigned int) = NULL;

int check_dll_is_open(){

    char        fullpath[128], path1[]={"./"}, path2[]={"../"}, path3[]={"/usr/lib/"};

    if(NULL == dll_handle){

        while(1){
        strcpy(stpcpy(fullpath, path1), libname);
        dll_handle = dlopen(fullpath, RTLD_LAZY);
        if(NULL == dll_handle){
            fprintf(stderr, "INFO: Can't open `%s` from `%s`\n", libname, fullpath);
            if((error = dlerror()) != NULL){
                fprintf (stderr, "%s\n", error);
                }
            //return brSO_CantLoadSO;
            } else break;

        strcpy(stpcpy(fullpath, path2), libname);
        dll_handle = dlopen(fullpath, RTLD_LAZY);
        if(NULL == dll_handle){
            fprintf(stderr, "INFO: Can't open `%s` from `%s`\n", libname, fullpath);
            if((error = dlerror()) != NULL){
                fprintf (stderr, "%s\n", error);
                }
            //return brSO_CantLoadSO;
            } else break;

        strcpy(stpcpy(fullpath, path3), libname);
        dll_handle = dlopen(fullpath, RTLD_LAZY);
        if(NULL == dll_handle){
            fprintf(stderr, "ERROR: Can't open `%s` from `%s`\n", libname, fullpath);
            if((error = dlerror()) != NULL){
                fprintf (stderr, "%s\n", error);
                }
            return brSO_CantLoadSO;
            }
        break;
        }

        }

    return 0;
}


int check_func_loaded(void *func_ptr){

    if(NULL == func_ptr){
        if((error = dlerror()) != NULL){
            fprintf(stderr, "ERROR: Can't load func from `%s`\n", libname);
            fprintf(stderr, "%s\n", error);
            }
        return brSO_CantOpenFunc;
        }

    return 0;
}


int OpenInterface(char *ip, void **handle){

    res = check_dll_is_open();
    if(res) return res;
    ptr_OpenInterface = (int (*)(char*, void**))dlsym(dll_handle, "OpenInterface");
    res = check_func_loaded((void*)ptr_OpenInterface);
    if(res) return res;

    //printf("HardwareInterface.c: *handle = 0x%08x\n", *handle);

    return (*ptr_OpenInterface)(ip, handle);
}


int CloseInterface(void *handle){

    res = check_dll_is_open();
    if(res) return res;
    ptr_CloseInterface = (int (*)(void*))dlsym(dll_handle, "CloseInterface");
    res = check_func_loaded((void*)ptr_CloseInterface);
    if(res) return res;

    return (*ptr_CloseInterface)(handle);
}


int ReadBAR3(void *handle, unsigned int index, unsigned short *Value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadBAR3 = (int (*)(void*, unsigned int, short unsigned int*))dlsym(dll_handle, "ReadBAR3");
    res = check_func_loaded((void*)ptr_ReadBAR3);
    if(res) return res;

    return (*ptr_ReadBAR3)(handle, index, Value);
}


int WriteBAR3(void *handle, unsigned int index, unsigned short Value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteBAR3 = (int (*)(void*, unsigned int, short unsigned int))dlsym(dll_handle, "WriteBAR3");
    res = check_func_loaded((void*)ptr_WriteBAR3);
    if(res) return res;

    return (*ptr_WriteBAR3)(handle, index, Value);
}

#ifdef DEPRECATED_API
int CaptureChannel(void *handle){

    res = check_dll_is_open();
    if(res) return res;
    ptr_CaptureChannel = (int (*)(void*))dlsym(dll_handle, "CaptureChannel");
    res = check_func_loaded((void*)ptr_CaptureChannel);
    if(res) return res;

    return (*ptr_CaptureChannel)(handle);
}


int FreeChannel(void *handle){

    res = check_dll_is_open();
    if(res) return res;
    ptr_FreeChannel = (int (*)(void*))dlsym(dll_handle, "FreeChannel");
    res = check_func_loaded((void*)ptr_FreeChannel);
    if(res) return res;

    return (*ptr_FreeChannel)(handle);
}


int WriteCOReg_nocap(void *handle, unsigned int BmId, unsigned int Reg_Code, unsigned int value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteCOReg_nocap = (int (*)(void*, unsigned int, unsigned int, unsigned int))dlsym(dll_handle, "WriteCOReg_nocap");
    res = check_func_loaded((void*)ptr_WriteCOReg_nocap);
    if(res) return res;

    return (*ptr_WriteCOReg_nocap)(handle, BmId, Reg_Code, value);
}


int ReadCOReg_nocap(void *handle, unsigned int BmId, unsigned int Reg_Code, unsigned int *value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadCOReg_nocap = (int (*)(void*, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "ReadCOReg_nocap");
    res = check_func_loaded((void*)ptr_ReadCOReg_nocap);
    if(res) return res;

    return (*ptr_ReadCOReg_nocap)(handle, BmId, Reg_Code, value);
}
#endif

int WriteCOReg(void *handle, unsigned int BmId, unsigned int Reg_Code, unsigned int value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteCOReg = (int (*)(void*, unsigned int, unsigned int, unsigned int))dlsym(dll_handle, "WriteCOReg");
    res = check_func_loaded((void*)ptr_WriteCOReg);
    if(res) return res;

    return (*ptr_WriteCOReg)(handle, BmId, Reg_Code, value);
}


int ReadCOReg(void *handle, unsigned int BmId, unsigned int Reg_Code, unsigned int * value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadCOReg = (int (*)(void*, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "ReadCOReg");
    res = check_func_loaded((void*)ptr_ReadCOReg);
    if(res) return res;

    return (*ptr_ReadCOReg)(handle, BmId, Reg_Code, value);
}


int WriteBufferCOReg(void *handle, unsigned int BmId, unsigned int Reg_Code, unsigned int size, unsigned int *buffer){

    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteBufferCOReg = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "WriteBufferCOReg");
    res = check_func_loaded((void*)ptr_WriteBufferCOReg);
    if(res) return res;

    return (*ptr_WriteBufferCOReg)(handle, BmId, Reg_Code, size, buffer);
}


int ReadBufferCOReg(void *handle, unsigned int BmId, unsigned int Reg_Code, unsigned int size, unsigned int *buffer){

    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadBufferCOReg = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "ReadBufferCOReg");
    res = check_func_loaded((void*)ptr_ReadBufferCOReg);
    if(res) return res;

    return (*ptr_ReadBufferCOReg)(handle, BmId, Reg_Code, size, buffer);
}


int ReadDMCReg64(void* handle, unsigned int BmId, unsigned int Reg_Code, unsigned int DMC_Num, unsigned __int64* value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_ReadDMCReg64 = (int (*)(void*, unsigned int, unsigned int, unsigned int, long long unsigned int*))dlsym(dll_handle, "ReadDMCReg64");
    res = check_func_loaded((void*)ptr_ReadDMCReg64);
    if (res) return res;

    return (*ptr_ReadDMCReg64)(handle, BmId, Reg_Code, DMC_Num, value);
}

int ReadDMCReg(void* handle, unsigned int BmId, unsigned int Reg_Code, unsigned int DMC_Num, unsigned int *value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_ReadDMCReg = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "ReadDMCReg");
    res = check_func_loaded((void*)ptr_ReadDMCReg);
    if (res) return res;

    return (*ptr_ReadDMCReg)(handle, BmId, Reg_Code, DMC_Num, value);
}

int WriteDMCReg64(void* handle, unsigned int BmId, unsigned int Reg_Code, unsigned int DMC_Num,  unsigned __int64 value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_WriteDMCReg64 = (int (*)(void*, unsigned int, unsigned int, unsigned int, long long unsigned int))dlsym(dll_handle, "WriteDMCReg64");
    res = check_func_loaded((void*)ptr_WriteDMCReg64);
    if (res) return res;

    return (*ptr_WriteDMCReg64)(handle, BmId, Reg_Code, DMC_Num, value);
}

int WriteDMCReg(void* handle, unsigned int BmId, unsigned int Reg_Code, unsigned int DMC_Num, unsigned int value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_WriteDMCReg = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int))dlsym(dll_handle, "WriteDMCReg");
    res = check_func_loaded((void*)ptr_WriteDMCReg);
    if (res) return res;

    return (*ptr_WriteDMCReg)(handle, BmId, Reg_Code, DMC_Num, value);
}

int ReadMem64Fast(void *handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned __int64 *value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_ReadMem64Fast = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, long long unsigned int*))dlsym(dll_handle, "ReadMem64Fast");
    check_func_loaded((void*)ptr_ReadMem64Fast);
    if (res) return res;

    return (*ptr_ReadMem64Fast)(handle, BmId, code, DMC_Num, addr, step, count, value);
}

int ReadMemFast(void *handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned int* value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_ReadMemFast = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "ReadMemFast");
    check_func_loaded((void*)ptr_ReadMemFast);
    if (res) return res;

    return (*ptr_ReadMemFast)(handle, BmId, code, DMC_Num, addr, step, count, value);
}


int WriteMem64Fast(void *handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned __int64 *value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_WriteMem64Fast = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, long long unsigned int*))dlsym(dll_handle, "WriteMem64Fast");
    res = check_func_loaded((void*)ptr_WriteMem64Fast);
    if (res) return res;

    return (*ptr_WriteMem64Fast)(handle, BmId, code, DMC_Num, addr, step, count, value);
}

int WriteMemFast(void* handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned int* value)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_WriteMemFast = (int (*)(void*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "WriteMemFast");
    res = check_func_loaded((void*)ptr_WriteMemFast);
    if (res) return res;

    return (*ptr_WriteMemFast)(handle, BmId, code, DMC_Num, addr, step, count, value);
}


int SpecBuffAlloc(void *handle, int count, void **buff){

    res = check_dll_is_open();
    if(res) return res;
    ptr_SpecBuffAlloc = (int (*)(void*, int, void**))dlsym(dll_handle, "SpecBuffAlloc");
    res = check_func_loaded((void*)ptr_SpecBuffAlloc);
    if(res) return res;

    return (*ptr_SpecBuffAlloc)(handle, count, buff);
}


int SpecBuffFree(void *handle, int count, void *buff){

    res = check_dll_is_open();
    if(res) return res;
    ptr_SpecBuffFree = (int (*)(void*, int, void*))dlsym(dll_handle, "SpecBuffFree");
    check_func_loaded((void*)ptr_SpecBuffFree);
    if(res) return res;

    return (*ptr_SpecBuffFree)(handle, count, buff);
}


int WaitEndStatus (void * handle, unsigned int BmId, double* time, double timeout){
	
    res = check_dll_is_open();
    if(res) return res;
    ptr_WaitEndStatus = (int (*)(void*, unsigned int,double*, double))dlsym(dll_handle, "WaitEndStatus");
    res = check_func_loaded((void*)ptr_WaitEndStatus);
    if(res) return res;

    return (*ptr_WaitEndStatus)(handle, BmId, time, timeout);
}


int GlobalReset(void *handle, unsigned int BmId){

    res = check_dll_is_open();
    if(res) return res;
    ptr_GlobalReset = (int (*)(void*, unsigned int))dlsym(dll_handle, "GlobalReset");
    res = check_func_loaded((void*)ptr_GlobalReset);
    if(res) return res;

    return (*ptr_GlobalReset)(handle, BmId);
}


int ReadCOMem32(void *handle, unsigned int BmId, unsigned int count, unsigned int *value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadCOMem32 = (int (*)(void *, unsigned int, unsigned int, unsigned int *))dlsym(dll_handle, "ReadCOMem32");
    res = check_func_loaded((void*)ptr_ReadCOMem32);
    if(res) return res;

    return (*ptr_ReadCOMem32)(handle, BmId, count, value);
}


int WriteCOMem32(void *handle, unsigned int BmId, unsigned int count, unsigned int *value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteCOMem32 = (int (*)(void *, unsigned int, unsigned int, unsigned int *))dlsym(dll_handle, "WriteCOMem32");
    res = check_func_loaded((void*)ptr_WriteCOMem32);
    if(res) return res;

    return (*ptr_WriteCOMem32)(handle, BmId, count, value);
}
#ifdef DEPRECATED_API
int ReadCOMem64(void *handle, unsigned int BmId, unsigned int count, unsigned __int64 *value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadCOMem64 = (int (*)(void *, unsigned int, unsigned int, unsigned __int64 *))dlsym(dll_handle, "ReadCOMem64");
    res = check_func_loaded((void*)ptr_ReadCOMem64);
    if(res) return res;

    return (*ptr_ReadCOMem64)(handle, BmId, count, value);
}


int WriteCOMem64(void *handle, unsigned int BmId, unsigned int count, unsigned __int64 *value){

    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteCOMem64 = (int (*)(void *, unsigned int, unsigned int, unsigned __int64 *))dlsym(dll_handle, "WriteCOMem64");
    res = check_func_loaded((void*)ptr_WriteCOMem64);
    if(res) return res;

    return (*ptr_WriteCOMem64)(handle, BmId, count, value);
}
#endif

int LoadFileFast(void * handle, unsigned int BmId, char* FileName)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_LoadFileFast = (int (*)(void *, unsigned int, char *))dlsym(dll_handle, "LoadFileFast");
    res = check_func_loaded((void*)ptr_LoadFileFast);
    if (res) return res;

	return (*ptr_LoadFileFast)(handle, BmId, FileName);
}

int LoadFile64Fast(void * handle, unsigned int BmId, char* FileName)
{
    res = check_dll_is_open();
    if (res) return res;
    ptr_LoadFileFast = (int (*)(void *, unsigned int, char *))dlsym(dll_handle, "LoadFile64Fast");
    res = check_func_loaded((void*)ptr_LoadFileFast);
    if (res) return res;

    return (*ptr_LoadFile64Fast)(handle, BmId, FileName);
}

#ifdef DEPRECATED_API
int CheckLoadFile(void * handle, unsigned int BmId, char* FileName){
    res = check_dll_is_open();
    if(res) return res;
    ptr_CheckLoadFile = (int (*)(void *, unsigned int, char *))dlsym(dll_handle, "CheckLoadFile");
    res = check_func_loaded((void*)ptr_CheckLoadFile);
    if(res) return res;
	
	return (*ptr_CheckLoadFile)(handle, BmId, FileName);
}
#endif

int GetVersions(void * handle, void ** buffer){
    res = check_dll_is_open();
    if(res) return res;
    ptr_GetVer = (int (*)(void *, void **))dlsym(dll_handle, "GetVer");
    res = check_func_loaded((void*)ptr_GetVer);
    if(res) return res;

    return (*ptr_GetVer)(handle, buffer);
}

int WriteCOCmd (void * handle, unsigned int BmId, unsigned int value){
    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteCOCmd = (int (*)(void*, unsigned int, unsigned int))dlsym(dll_handle, "WriteCOCmd");
    res = check_func_loaded((void*)ptr_WriteCOCmd);
    if(res) return res;

    return (*ptr_WriteCOCmd)(handle, BmId, value);
}

int ReadCOCmd (void * handle, unsigned int BmId, unsigned int * value){
    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadCOCmd = (int (*)(void*, unsigned int, unsigned int*))dlsym(dll_handle, "ReadCOCmd");
    res = check_func_loaded((void*)ptr_ReadCOCmd);
    if(res) return res;

    return (*ptr_ReadCOCmd)(handle, BmId, value);
}

int ReadBufferCODataReg (void * handle, unsigned int BmId, unsigned int size, unsigned int* buffer){
    res = check_dll_is_open();
    if(res) return res;
    ptr_ReadBufferCODataReg = (int (*)(void*, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "ReadBufferCODataReg");
    res = check_func_loaded((void*)ptr_ReadBufferCODataReg);
    if(res) return res;

    return (*ptr_ReadBufferCODataReg)(handle, BmId, size, buffer);
}

int WriteBufferCODataReg (void * handle, unsigned int BmId, unsigned int size, unsigned int* buffer){
    res = check_dll_is_open();
    if(res) return res;
    ptr_WriteBufferCODataReg = (int (*)(void*, unsigned int, unsigned int, unsigned int*))dlsym(dll_handle, "WriteBufferCODataReg");
    res = check_func_loaded((void*)ptr_WriteBufferCODataReg);
    if(res) return res;

    return (*ptr_WriteBufferCODataReg)(handle, BmId, size, buffer);
}

int RunDMC(void * handle, unsigned int BmId){
    res = check_dll_is_open();
    if(res) return res;
    ptr_RunDMC = (int (*)(void*, unsigned int))dlsym(dll_handle, "RunDMC");
    res = check_func_loaded((void*)ptr_RunDMC);
    if(res) return res;

    return (*ptr_RunDMC)(handle, BmId);
}

int StopDMC(void * handle, unsigned int BmId){
    res = check_dll_is_open();
    if(res) return res;
    ptr_StopDMC = (int (*)(void*, unsigned int))dlsym(dll_handle, "StopDMC");
    res = check_func_loaded((void*)ptr_StopDMC);
    if(res) return res;

    return (*ptr_StopDMC)(handle, BmId);
}
#endif
