#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

//константы индексов регистров КБМ (для функций работы с КБМ)
enum
{
    RDL = 0x0,
    RCL = 0x1,
    RCC = 0x2,
    RDC = 0x3,
    RMB = 0x4
};

//константы кодов сегментов памяти КРП (для функций работы с КРП)
enum
{
    scOperSeg = 0x20,
    scParamSeg = 0x21,
    scDataSeg = 0x22,
    scCycleSeg = 0x23
};

#if defined(Q_WS_WIN)
	
// возвращаемые функциями результаты 
const int  brSuccess            = 0;//успешное выполнение
const int  brBMIError           = 1;//ошибка библиотеки BMInterface.dll
const int  brFailed             = 2;//ошибка по какой-либо другой причине
const int  brQueued             = 3;//запрос на выполнение поставлен в очередь
const int  brBadUser            = 4;//ошибка идентификации пользователя
const int  brBadBM              = 5;//базовый модуль выключен или неисправен
const int  brTimeout            = 6;//ошибка, таймаут выполнения операции
const int  brDriverError        = 7;//ошибка в драйвере PCI (ver9a)
const int  brChManagerError     = 8;//ошибка или таймаут библиотеки ChManager.dll
const int  brSocketError        = 9;//ошибка сокета
const int  brMemLockError       = 10;//ошибка блокировки или разблокировки виртуального диапазона памяти в физический
const int  brPCIExpressError    = 11;//ошибка платы PCI-Express
const int  brPCIExpressTimeout  = 12;//ошибка, таймаут ожидания платы PCI-Express
const int  brNotImplemented     = 13;//функция не реализована
const int  brPSSDKerror         = 14;//ошибка драйвера PSSDK
const int  brMemAllocError      = 15;//ошибка выделения памяти
const int  brWaitError          = 16;//ошибка ожидания объекта синхронизации Windows
const int  brPhysBuffAllocError = 17;//ошибка расположения начала буфера не кратно странице
const int  brOtherException     = 18;//исключительная ситуация
const int  brFileLoadError      = 19;//ошибка загрузки out-файла
const int  brPCIExpressFIFOOverflow = 20;//ошибка, переполнена FIFO PCI-Express


#else

#define brSuccess               0
#define brBMIError              1
#define brFailed                2
#define brQueued                3
#define brBadUser               4
#define brBadBMId               5
#define brTimeout               6
#define brDriverError           7
#define brChManagerError        8
#define brSocketError           9
#define brMemLockError          10
#define brPCIExpressError       11
#define brPCIExpressTimeout     12
#define brNotImplemented        13
#define brPSSDKerror            14
#define brMemAllocError         15
#define brWaitError             16
#define brPhysBuffAllocError    17
#define brOtherException        18
#define brFileIOError           19

#define brSO_SIG                0x100
#define brSO_OK                 (brSO_SIG | 0x0)
#define brSO_Error              (brSO_SIG | 0x1)
#define brSO_CantLoadSO         (brSO_SIG | 0x2)
#define brSO_CantOpenFunc       (brSO_SIG | 0x3)

#endif

#define __int64 long long int

#ifdef __cplusplus
extern "C"{
#endif

//==========функции открытия/закрытия интерфейса==========

//OpenInterface - открытие интерфейса
//ip - ip-адрес ВБ (если открытие интерфейса выполняется локально на ВБ, то этот параметр может быть NULL)
//handle - указатель на дескриптор интерфейса, дескриптор интерфейса имеет тип void*
int OpenInterface(char*ip, void ** handle);

//CloseInterface - закрытие интерфейса
//handle - дескриптор интерфейса
int CloseInterface(void * handle);


//==========функции работы с КБМ==========

//ReadCOReg - чтение регистра КБМ
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс регистра КБМ, может принимать значения riCOCmdReg или riCODataReg
//value - указатель на читаемое значение из регистра КБМ
int ReadCOReg (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int* value);

//WriteCOReg - запись в регистр КБМ
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс регистра КБМ, может принимать значения riCOCmdReg или riCODataReg
//value - записываемое значение в регистр КБМ
int WriteCOReg (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int value);

#ifdef DEPRECATED_API
//ReadCOReg_nocap - чтение регистра КБМ минуя синхронизацию доступа к каналу PCI-Express (не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс регистра КБМ, может принимать значения riCOCmdReg или riCODataReg
//value - указатель на читаемое значение из регистра КБМ
int ReadCOReg_nocap (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int* value);

//WriteCOReg_nocap - запись в регистр КБМ минуя синхронизацию доступа к каналу PCI-Express (не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс регистра КБМ, может принимать значения riCOCmdReg или riCODataReg
//value - записываемое значение в регистр КБМ
int WriteCOReg_nocap (void * handle, unsigned int BmId, unsigned int RegCode, unsigned int value);
#endif

//ReadBufferCOReg - чтение массива слов из регистра КБМ (функция используется для тестирования БМ, не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс регистра КБМ, может принимать значения riCOCmdReg или riCODataReg
//size - количество читаемых слов (размер слова - 4 байта)
//buffer - указатель на читаемый из регистра КРП массив
int ReadBufferCOReg(void * handle, unsigned int BmId, unsigned int RegCode, unsigned int size, unsigned int* buffer);

//WriteBufferCOReg - запись массива слов в регистр КБМ (функция используется для конфигурирования ПЛИС и тестирования БМ, не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс регистра КБМ, может принимать значения riCOCmdReg или riCODataReg
//size - количество записываемых слов (размер слова - 4 байта)
//buffer - указатель на записываемый в регистр КБМ массив 
int WriteBufferCOReg(void * handle, unsigned int BmId, unsigned int RegCode, unsigned int size, unsigned int* buffer);

#ifdef DEPRECATED_API
//ReadCOMem64 - чтение памяти устройства сопряжения PCI-Express (не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//count - количество читаемых слов (размер слова - 8 байт)
//value - указатель на читаемый массив (массив должен быть выделен с помощью функции SpecBuffAlloc) 
int ReadCOMem64 (void* handle, unsigned int BmId, unsigned int count, unsigned __int64* value);

//WriteCOMem64 - запись в память устройства сопряжения PCI-Express (не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//count - количество записываемых слов (размер слова - 8 байт)
//value - указатель на записываемый массив (массив должен быть выделен с помощью функции SpecBuffAlloc)
int WriteCOMem64 (void* handle, unsigned int BmId, unsigned int count, unsigned __int64* value);
#endif

//==========функции работы с КРП==========

//RunDMC - пуск КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
int RunDMC (void * handle, unsigned int BmId);

//StopDMC - останов КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
int StopDMC (void * handle, unsigned int BmId);

//WaitEndStatus - ожидание завершения работы КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//time - указатель на переменную, в которую будет записано значение времени, в течении которого работала функция
//timeout - максимальное время ожидания работы КРП
int WaitEndStatus (void * handle, unsigned int BmId, double* time, double timeout);

//GlobalReset - сброс КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
int GlobalReset (void * handle, unsigned int BmId);

//ReadDMCReg64 - чтение регистра КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс читаемого регистра
//DMCNumber - индекс КРП
//value - указатель на читаемое значение из регистра КРП
int ReadDMCReg64(void * handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned __int64* value);

//ReadDMCReg - чтение регистра КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс читаемого регистра
//DMCNumber - индекс КРП
//value - указатель на читаемое значение из регистра КРП
int ReadDMCReg(void* handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned int* value);

//WriteDMCReg64 - чтение регистра КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс записываемого регистра
//DMCNumber - индекс КРП
//value - указатель на записываемое значение в регистр КРП
int WriteDMCReg64(void * handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned __int64 value);

//WriteDMCReg - чтение регистра КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//RegCode - индекс записываемого регистра
//DMCNumber - индекс КРП
//value - указатель на записываемое значение в регистр КРП
int WriteDMCReg(void* handle, unsigned int BmId, unsigned int RegCode, unsigned int DMCNumber, unsigned int value);

//ReadMem64Fast - чтение памяти КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//code - код сегмента памяти, может принимать значения scOperSeg, scParamSeg, scDataSeg или scCycleSeg
//DMC_Num - индекс КРП
//addr - начальный адрес чтения из КРП
//step - шаг чтения
//count - количество читаемых слов (размер слова - 8 байт)
//value - указатель на читаемый массив (массив должен быть выделен с помощью функции SpecBuffAlloc)
int ReadMem64Fast (void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned __int64* value);

//ReadMemFast - чтение памяти КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//code - код сегмента памяти, может принимать значения scOperSeg, scParamSeg, scDataSeg или scCycleSeg
//DMC_Num - индекс КРП
//addr - начальный адрес чтения из КРП
//step - шаг чтения
//count - количество читаемых слов (размер слова - 8 байт)
//value - указатель на читаемый массив (массив должен быть выделен с помощью функции SpecBuffAlloc)
int ReadMemFast (void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned int* value);

//WriteMem64Fast - чтение памяти КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//code - код сегмента памяти, может принимать значения scOperSeg, scParamSeg, scDataSeg или scCycleSeg
//DMC_Num - индекс КРП
//addr - начальный адрес записи в КРП
//step - шаг записи
//count - количество записываемых слов (размер слова - 8 байт)
//value - указатель на записываемый массив (массив должен быть выделен с помощью функции SpecBuffAlloc)
int WriteMem64Fast(void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned __int64* value);

//WriteMemFast - чтение памяти КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//code - код сегмента памяти, может принимать значения scOperSeg, scParamSeg, scDataSeg или scCycleSeg
//DMC_Num - индекс КРП
//addr - начальный адрес записи в КРП
//step - шаг записи
//count - количество записываемых слов (размер слова - 8 байт)
//value - указатель на записываемый массив (массив должен быть выделен с помощью функции SpecBuffAlloc)
int WriteMemFast(void * handle, unsigned int BmId, unsigned int code, unsigned int DMC_Num, unsigned int addr, unsigned int step, unsigned int count, unsigned int* value);

//LoadFileFast - загрузка *.out-файла в память КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//FileName - имя загружаемого файла
int LoadFileFast(void * handle, unsigned int BmId, char* FileName);

//LoadFile64Fast - загрузка *.out-файла в память КРП
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//FileName - имя загружаемого файла
int LoadFile64Fast(void * handle, unsigned int BmId, char* FileName);

#ifdef DEPRECATED_API
int CheckLoadFile(void * handle, unsigned int BmId, char* FileName);
#endif

//==========функции работы с памятью управляющей машины==========

//SpecBuffAlloc - выделение памяти
//handle - дескриптор интерфейса
//count - количество выделяемых слов (размер слова - 8 байт)
//buff - указатель на указатель на выделенный массив
int SpecBuffAlloc(void * handle, int count, void ** buff);

//SpecBuffFree - освобождение памяти, выделенной функцией SpecBuffAlloc
//handle - дескриптор интерфейса
//count - количество освобождаемых слов (размер слова - 8 байт)
//buff - указатель на освобождаемый массив
int SpecBuffFree(void * handle, int count, void * buff);


#ifdef DEPRECATED_API
//==========функции доступа к каналу PCI-Express==========

//CaptureChannel - захват канала (не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
int CaptureChannel(void * handle);

//CaptureChannel - освобождение канала (не рекоммендуется использовать данную функцию)
//handle - дескриптор интерфейса
int FreeChannel(void * handle);
#endif

//==========прочие функции==========

int ReadBAR3(void * handle, unsigned int index, unsigned short * value);
int WriteBAR3(void * handle, unsigned int index, unsigned short value);

int ReadCOMem32(void *handle, unsigned int BmId, unsigned int count, unsigned int *value);
int WriteCOMem32(void *handle, unsigned int BmId, unsigned int count, unsigned int *value);

//GetVersions – возвращение версий интерфейса и нижележащего программно-аппаратного обеспечения (компонентов)
//buffer – указатель на указатель на буфер с данными о версиях (указатель на структуру versions)
//handle - дескриптор интерфейса
int GetVersions(void * handle, void ** buffer);

//==========функции работы в SLOW-режиме==========

//WriteCOCmd - запись команды
//handle - дескриптор интерфейса
//BmId - индекс ПВМ в пределах ВМ
//value - записываемое значение команды
int WriteCOCmd (void * handle, unsigned int BmId, unsigned int value);

//ReadCOCmd - чтение регистра команд
//handle - дескриптор интерфейса
//BmId - индекс ПВМ в пределах ВМ
//value – указатель на читаемое значение
int ReadCOCmd (void * handle, unsigned int BmId, unsigned int * value);

//ReadBufferCODataReg - чтение данных в SLOW-режиме
//handle - дескриптор интерфейса
//BmId - индекс БМ в пределах ВБ
//size - количество читаемых слов (размер слова - 4 байта)
//buffer - указатель на читаемый массив
int ReadBufferCODataReg (void * handle, unsigned int BmId, unsigned int size, unsigned int* buffer);

//WriteBufferCODataReg - запись данных в SLOW-режиме
//handle - дескриптор интерфейса
//BmId - индекс ПВМ в пределах ВМ
//size - количество записываемых слов (размер слова - 4 байта)
//buffer - указатель на записываемый массив
int WriteBufferCODataReg (void * handle, unsigned int BmId, unsigned int size, unsigned int* buffer);

#ifdef __cplusplus
}
#endif

#endif
