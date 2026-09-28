#ifndef PROXY_H
#define PROXY_H

///
/// @brief    Proxy rhksfus Header file
/// @file     proxy.h
/// @date     2024. 12. 18. (수) 09:50:02 KST
/// @author   Cento
///

///
/// Proxy Information
/// Capture endpoint에 대한 생각
///  PUS/SUB Proxy의 Capture는 Backend point에서 수신하는것으로 .....
///
typedef struct _PROXYINFOR{
    int  ID;
    char RunHost          [ 20];
    char Comment          [255];
    char ProxyType        [ 12];
    char FrontEndPoint    [ 32];
    char BackEndPoint     [ 32];
    char ControlEndPoint  [ 32];
    char CaptureEndPoint  [ 32];
    char StartTime        [ 20];
    int  ReadCount;
    int  WriteCount;
    int  FrontCount;
    int  BackCount;
    int  CaptureCount;
    int  Pause;
}PROXYINFOR;

typedef struct _THREAD_ARG{
    void *ctx;
    void *log;
    char front[255];
    char back [255];
}PROXY_THREAD_ARG;

typedef struct _CAPTURE_THREAD_ARG{
    void *ctx;
    void *log;
    char front[255];
    void *pubsocket;
}CAPTURE_THREAD_ARG;

typedef struct _CONTROL_THREAD_ARG{
    void *ctx;
    void *log;
    char reppoint[32];
}CONTROL_THREAD_ARG;

#endif /* PROXY_H */
