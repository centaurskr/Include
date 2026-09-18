//
// Description : Define C API for Tugboat 
// File Name   : TbC.h
// Date        : 2021. 10. 13. (수) 19:09:38 KST
// By  : Cento
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <net/if.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

#include "TbData.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void          GetStrYyyymmdd      (char *buff);
extern void          GetStrYymmddhhmmsscc(char *buff);
extern void          GetStrYyyymmdd      (char *ymd);
extern void          GetStrYymmdd        (char *ymd);
extern unsigned long GetNumYymmddhhmm    ();
extern unsigned long GetTimestamp        ();
extern unsigned long GetTimestampMs      ();
extern int           GetNumYyyymmdd      ();
extern int           GetNumYymmdd        ();
extern unsigned long GetNumYyyymmddhhmmsscc();
extern unsigned long GetNumYyyymmddhhmmssmmm();
extern unsigned long GetNumYyyymmddhhmm();
extern unsigned long ConvertTimeStemp(unsigned long  );
extern int           IncDecNumYyyymmdd(int , int );
extern int           NextSundayNumYyyymmdd(int );
extern int           ThisSundayNumYyyymmdd(int );
extern int           NextMondayNumYyyymmdd(int );
extern int           ThisMondayNumYyyymmdd(int );

///---- CONTROL MESSAGE (MULTICASTING VERSION) ------
extern void  DestroyControlMessage(void *ctlifo);
extern void *InitControlMessage(int port, char *group, int mynum);
extern int   ControlMessage(void *info, unsigned int to, unsigned int cmd, char *msg, int len);
extern int   GetControlMessageFd(void *info);

extern int   GetEnvValue(char *fname, char *section, char *key, char *value);
extern char *MakeMapFile(char *fname, off_t size);
extern void *AttachMapFile(char *filename, off_t size);
extern void  UnmapMapFile(void *point, size_t size);
extern int   SyncMapFile(void *point, size_t size);
extern int   GetPortNumberR(char *name, char *proto);
extern int   GetPortNumber(char *name, char *proto);
extern int   OpenMtPublish(struct sockaddr_in *addr, const char *dev, const char *group, int port, int ttl);
extern int   OpenMtSubscribe(const char *dev, const char *group, int port);
extern int   OpenInetStreamClient(char *host, int port);
extern int   OpenInetStreamServer(int port);
extern int   ReadFd(int fd, char *buf, size_t buflen);
extern int   ReadStream(int fd,char *buff);
extern int   ReadStream2(int fd,char *buff);
extern int   WriteFd(int fd, int sendfd, void *ptr, size_t nbytes);
extern int   WaitConnect(int fd, char *buff);
extern int   WriteStream(int fd,char *buff,int sz);
extern int   WriteStream2(int fd,char *buff,int sz);
extern int   CreateTimerfd(int sec);
extern int   ResetTimer(int fd, int sec);
extern int   StrTrim(char *dst, char *src, int len);
extern int   Stringcmp(char *a, char *b);
extern int   GetFileSize(char *);
extern int   GetMyHostCharAddress(char *);
extern int   IsRunning(char *);

extern DOUBLE DoubleMode(DOUBLE, DOUBLE);
extern int    IsEqDouble8(DOUBLE , DOUBLE );
extern int    IsZeroDouble8(DOUBLE);
extern int    CompareDouble8(DOUBLE, DOUBLE);
extern void   CutDoubleStr8(char *);
extern int    IsRoundUpDouble16(DOUBLE );
extern int    SetDoubleStr_Str(DOUBLESTR *, char *);
extern void   GetDoubleStr_Str(char *, DOUBLESTR *);
extern int    CompDoubleStr(DOUBLESTR *, DOUBLESTR *); 
extern void   CopyDoubleStr(DOUBLESTR *, DOUBLESTR *);
extern void   AddDoubleStr(DOUBLESTR *, DOUBLESTR *, DOUBLESTR *);
extern void   SubDoubleStr(DOUBLESTR *, DOUBLESTR *, DOUBLESTR *);
extern void   MulDoubleStr(DOUBLESTR *, DOUBLESTR *, DOUBLESTR *);
extern void   InitDoubleStr(DOUBLESTR *);
extern int    IsZeroDoubleStr(DOUBLESTR *);
extern void   RoundDoubleStr(DOUBLESTR *, int);

extern void *BinSearch(const void *, int , void *, int, int, int (*)());

extern int   CleanLogfile          (char *pt, char *f, int gdate);
//-------------------- LINKED LIST------------------
extern void *TbListInit        (                        );
extern int   TbListInsert      (void *, int, void *, int);
extern int   TbListDelete      (void *, int             );
extern void  TbListDestory     (void *                  );
extern void *TbListFetchByIndex(void *, int             );
extern void *TbListFetchByKey  (void *, int             );

//-------------------- FOR JSON --------------------
extern void *JsonInit();
extern void  JsonFree(void *);
extern void  JsonStart(void *);
extern void  JsonArrayStart(void *, char *);
extern void  JsonAdd(void *, char *, char *);
extern void  JsonAddInt(void *, char *, int);
extern void  JsonAddLong(void *, char *, long);
extern void  JsonAddDouble(void *, char *, double);
extern void  JsonAddLDouble(void *, char *, long double);
extern void  JsonEnd(void *, int);
extern void  JsonArrayEnd(void *, int);
extern char *JsonGetStr(void *);
extern int   JsonGetLen(void *);
//---- JSON Parser
extern void *JsonParser(char *);
extern void  JsonParserFree(void *);
extern int   JsonParserAdd(void *, char *);
extern char *JsonParserGet(void *, char *);
//------------------------------------------------

//------------------- Event Version1 (select())--------
extern void *AppEventInitSelect          ();
extern void AppEventLoopSelect           (void *ent);
extern void AppChangeDefaultHandlerSelect(void *ent, int (*handler)());
extern void AppEventLoopShutdownSelect   (void *ent);
extern int  AppDelEventSelect            (void *ent, int id);
extern int  AppAddEventAutoIdSelect      (void *ent, int fd, int tout, 
										int answer, int (*handler)());

//------------------- Event Version2 (epoll())---------
///< ⛳ Default Handler를 등록한다
extern void Event_SetDefaultHandler(
            void *,                   ///< ⛷  Event context
            int  (*)(void *, void *), ///< ⛷  Default Handler function
            void *,                   ///< ⛷  수행시 사용하는 DATA
            int,                      ///< ⛷  수행 간격 (초단위)
            int);                   ///< ⛷  초기수행 상태 (0:PAUSE, 1:ACTIVATE)
///< ⛳ Default Handler 수행 간간격을 설정한다
extern void Event_SetDefaultHandlerTimer(
            void *,                   ///< ⛷  Event context
            int);                     ///< ⛷  수행 간격 (초단위)
///< ⛳ Default Handler 수행 상태를 설정한다
extern void Event_SetDefaultHandlerState(
            void *,                   ///< ⛷  Event context
            int);                     ///< ⛷  수행 상태 (0:PAUSE, 1:ACTIVATE)
///< ⛳ Handler 수행 상태를 설정한다
extern void Event_SetHandlerState(
            void *,                   ///< ⛷  Event context
			int   ,                   ///< ⛷  Event Fd
            int);                     ///< ⛷  수행 상태 (0:PAUSE, 1:ACTIVATE)
///< ⛳ Event loop의 기본 timeout 값을 재설정한다\n
///<      설정이 없는 초기 값은 1000(1초).\n
///<     ⛔timeout 값이 너무 작은 경우 CPU 사용량이 증가한다.
extern void Event_SetEventTimeout(
            void *,                   ///< ⛷  Event context
            double );                 ///< ⛷  초단위 (0.5초 = 0.5)

///< ⛳ Event Loop를 시작한다.
extern void Event_StartLoop(
            void *);                  ///< ⛷  Event context

///< ⛳ Event Loop를 종료한다.
extern void Event_Shutdown(
            void *);                  ///< ⛷  Event context

///< ⛳ 신규 Event를 생성한다.
extern void *Event_CreateNew();

///< ⛳ Event를 삭제한다
extern int Event_DeleteEvent(
            void *,                   ///< ⛷  Event context
			int );                    ///< ⛷  Event Fd
///< ⛳ Event를 등록한다
extern int Event_AddEvent(
            void *,                   ///< ⛷  Event context
			int   ,                   ///< ⛷  Event Fd
            int (*)(void *, int, int, void *), ///< ⛷  Data Handler function
            void * ,                 ///< ⛷  수행시 사용하는 DATA
            int,                      ///< ⛷  Timeout (초단위)
            int);                     ///< ⛷  수행 상태 (0:PAUSE, 1:ACTIVATE)

// ┌─────────────────────────────────────────────────────────────┐
// │   Event Handler                                             │
// │   handler (void *context, int fd, int ewhat, void *data)    │
// │   -. context : Event Context                                │
// │   -. fd      : Event fd                                     │
// │   -. ewhat   : 0:Data Event, 1:timeout event                │
// │   -. data    : user data                                    │
// │   Default handler                                           │
// │   defhandler(void *context, void *data)                     │
// │   -. Context : Event Context                                │
// │   -. data    : user data                                    │
// └─────────────────────────────────────────────────────────────┘

//-------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#define PRINTF(mode, fmt,...) \
    { \
	printf("%12.12s-%20.20s-%5d ", __FILE__, __FUNCTION__, __LINE__); \
	printf(fmt, ##__VA_ARGS__); \
	}

