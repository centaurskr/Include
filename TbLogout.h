///
///  Logout Header file
/// @file TbLogout.h
/// @date 2024. 01. 03. (수) 11:46:22 KST
/// @author Cento 
//  -DLOGOUT_TYPE=1  : 0MQ Non_Thread Version
//  -DLOGOUT_TYPE=11 : 0MQ Thread Version
//  -DLOGOUT_TYPE=0  : Stand alone Version
//  -DLOGOUT_TYPE=2  : Multicasting Version
//

typedef enum {DEBUG = 'D', INFOR = 'I', ERROR = 'E', CMD = 'C', JURNAL = 'J'}LOG_TYPE;

#ifdef __cplusplus
extern "C" {
#endif

//------------------- LOGOUT_TYPE==1 Zmq Non Thread ---------------------
#if LOGOUT_TYPE==1    /// 0MQ Non_Thread Version

extern int _XInitLogout0mq       (void* , int ,char **, char *, int);
extern void _XLogout0mq          (char,const char *, const char *, 
									int, const char *, ...);
extern void _XCloseLogout0mq     ();
extern void _XChangeDateLogout0mq();

#define InitLogout(ctx, arc, arv, lname, valid) \
    _XInitLogout0mq(ctx, arc, arv, lname, valid)
#define Logout(mode, fmt,...) \
    _XLogout0mq(mode, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define CloseLogout() _XCloseLogout0mq()
#define ChangeDateLogout() _XChangeDateLogout0mq()

//------------------- LOGOUT_TYPE==11 Zmq Thread ---------------------
#elif LOGOUT_TYPE==11 //// 0MQ Thread 용 

extern void * _TInitLogout0mq       (void* , int ,char **, char *, int);
extern void   _TLogout0mq           (void *, char,const char *, const char *, 
										int, const char *, ...);
extern void   _TCloseLogout0mq      (void *);
extern void   _TChangeDateLogout0mq (void *);
extern void  *InitLogoutThread0mq   (void *);

#define InitLogout(ctx, arc, arv, lname, valid) \
    _TInitLogout0mq(ctx, arc, arv, lname, valid)
#define Logout(ep, mode, fmt,...) \
    _TLogout0mq(ep, mode, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define CloseLogout(ep)      _TCloseLogout0mq(ep)
#define ChangeDateLogout(ep) _TChangeDateLogout0mq(ep)

//------------------- LOGOUT_TYPE==0  stand alone ---------------------
#elif  LOGOUT_TYPE==0 /// Stand alone Logout

extern int _SInitLogout          (int ,char **, char *, int);
extern void _SLogout             (int, const char *, const char *, 
								  int, const char *, ...);
extern void _SCloseLogout        ();
extern void _SChangeDateLogout   ();

#define InitLogout(arc, arv, lname, valid) \
    _SInitLogout(arc, arv, lname, valid)
#define Logout(mode, fmt,...) \
    _SLogout(mode, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define CloseLogout() _SCloseLogout()
#define ChangeDateLogout() _SChangeDateLogout()

//------------------- LOGOUT_TYPE==2  Multicasting ---------------------
#elif  LOGOUT_TYPE==2 /// Multicasting Version

extern int  _MtInitLogout         (int, char **, char *, int);
extern void _MtLogout             (char,const char *, const char *, 
									int, const char *, ...);
extern void _MtCloseLogout0mq     ();
extern void _MtChangeDateLogout0mq();

#define InitLogout(arc, arv, lname, valid) \
    _MtInitLogout(arc, arv, lname, valid)
#define Logout(mode, fmt,...) \
    _MtLogout(mode, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define CloseLogout() _MtCloseLogout()
#define ChangeDateLogout() _MtChangeDateLogout()

#endif //------------- LOGOUT ENDIF


#ifdef __cplusplus
}
#endif

