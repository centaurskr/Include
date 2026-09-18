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
    int  ID                    ; // Proxy ID
    char RunHost          [ 20]; // Running host
    char Comment          [255]; // Comment
    char ProxyType        [ 12]; // REP/REQ or  PUB/SUB ...
    char FrontEndPoint    [ 32]; // Front Endpoint
    char BackEndPoint     [ 32]; // Back Endpoint
    char ControlEndPoint  [ 32]; // Control Endpoint
    char CaptureEndPoint  [ 32]; // Capture Endpoint - REP/REQ인 경우만
    char StartTime        [ 20]; // Start Time
    int  ReadCount             ; // Read Packet count of frontendpoint
    int  WriteCount            ; // Write Packet count of backendpoint
    int  FrontCount            ; // Frontend Connection count
    int  BackCount             ; // Backend  Connection count
    int  CaptureCount          ; // Capture Connection count - REP REQ만
    int  Pause                 ; // PAUSE 상태
}PROXYINFOR;

typedef struct _THREAD_ARG{
	void *ctx      ;   // Zmq Context
	void *log      ;   // Logout Context
	char front[255];   // FrontEnd Point
	char back [255];   // BackEnd Point 
}PROXY_THREAD_ARG;

typedef struct _CAPTURE_THREAD_ARG{
	void *ctx            ;   // Zmq Context
	void *log            ;   // Logout Context
	char front[255]      ;   // Inner Proxy Back end point(SUB)
	void *pubsocket      ;   // Back End socket (PUB)
}CAPTURE_THREAD_ARG;

typedef struct _CONTROL_THREAD_ARG{
	void *ctx            ;   // Zmq Context
	void *log            ;   // Logout Context
	char reppoint[32]    ;   // REP point
}CONTROL_THREAD_ARG;
