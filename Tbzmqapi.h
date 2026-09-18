//
// Description : libzmq.a 를 사용하는 Application library header
// File Name   : Tbzmqapi.h
// Date        : 2021. 10. 04. (월) 14:49:59 KST
// By  : Cento
//
#include <zmq.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ARGEVENT_
extern void _AppEventLoop           (void *);
extern void _AppChangeDefaultHandler(void *, int (*)());
extern void _AppChangeEventTimeout  (void *, int);
extern void _AppEventLoopShutdown   (void *);
extern int  _AppDelEvent            (void *, int);
extern int  _AppAddEventAutoId0mq   (void *, void *, int , int , 
	                                  int (*)(void *, void *, int));
extern int _AppAddEventAutoIdFd     (void *, int, int , int , 
	                                  int (*)(void *, int, int));
extern void *_AppEventInit          (void *);
extern void *AppEventGetUserData    (void *);
extern void AppEventSetUserData     (void *, void *);
extern void AppEventFreeUserData    (void *);

#define AppEventInit(udata)               _AppEventInit(udata)
#define AppEventLoop(ent)                 _AppEventLoop(ent)
#define AppChangeDefaultHandler(ent, fun) _AppChangeDefaultHandler(ent, fun)
#define AppChangeEventTimeout(ent, sec)   _AppChangeEventTimeout(ent, sec)
#define AppEventLoopShutdown(ent)         _AppEventLoopShutdown(ent)
#define AppDelEvent(ent, type)            _AppDelEvent(ent, type)
#define AppAddEventAutoId0mq(ent, sc, n, r, fun) \
		_AppAddEventAutoId0mq(ent, sc, n, r, fun)
#define AppAddEventAutoIdFd(ent, s, n, r, fun)  \
		_AppAddEventAutoIdFd(ent, s, n, r, fun) 

#else // _ARGEVENT_

extern void AppEventLoop(void *);
extern void AppChangeDefaultHandler(void *, int (*)());
extern void AppChangeEventTimeout(void *, int);
extern void AppEventLoopShutdown(void *);
extern int  AppDelEvent(void *, int);
extern int AppAddEventAutoId0mq(void *, void *, int , int , 
	int (*)(void *, void *, int));
extern int AppAddEventAutoIdFd(void *, int, int , int , 
	int (*)(void *, int, int));
extern void *AppEventInit();

#endif //_ARGEVENT_


extern void *OpenPullSocket0mq(void *, char *);
extern void *OpenPubSocket0mq(void *, char *);
extern void *OpenRepSocket0mq(void *, char *);
extern void *OpenReqSocket0mq(void *, char *);
extern void *OpenSubSocket0mq(void *, char *);
extern int   SetSubTopic0mq(void *, char *);
extern int   SetUnsubTopic0mq(void *, char *);

extern int ReceiveTopic0mq(void *, char *, char *, int );
extern int SendTopic0mq(void *, char *, char *, int );

extern char *ReceiveMessage0mq(void *, int *); // free() 필수
extern int  SendMessage0mq(void *, char *, int );

extern char *ReceiveTopicMessage0mq(void *, char *, int *); // free() 필수
extern int  SendTopicMessage0mq(void *, char *, char *, int );

extern int IsRunning0mq(void *, int);

extern void ColseControlMsg0mq(void *);
extern void *MakeControlMsgSocket0mq(void *, int, char *, char *);
extern int SendControlMsg0mq(int, int, char *);
extern int ReceiveControlMsg0mq(void *, void *, char *, int );
extern int GetFdFrom0mqSocket(void *);

extern int GetProxyEnv(char *, int *, char *, char *, char *, char *);

extern void *MakeMonitorSocket0mq(void *, void *);
#ifdef __cplusplus
}
#endif

