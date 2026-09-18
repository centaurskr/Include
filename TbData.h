///
/// ## Tugboat Data Define header file
/// @file TbData.h
/// @date 2023. 12. 28. (목) 10:27:19 KST
/// @author Cento 
///
#include <time.h>

///////////////////// NETWOKR ENV  /////////////////////////////////////////////
// LOG_HOME    -- Logout lib
// LOG_GROUP   -- Multicasting Logout
// tbnova/tcp  -- tb_nova
// tblog/udp   -- Multicasting Logout
// tbctl/udp   -- Control Message
// tbagent/tcp -- tb_agent

#define   PROC_CTL_GROUP  "224.3.3.5"

///////////////////// DOUBLE STRING  ///////////////////////////////////////////
#ifndef _DOUBLE_STR
#define _DOUBLE_STR
#define  DSTR_LEN    30 

///< double 계산하기 위한 String 구조체
typedef struct _DOUBLESTR{
	unsigned char  istr  [DSTR_LEN]; ///< 정수부분
	unsigned char  fstr  [DSTR_LEN]; ///< 소수부분
	int            ilen, flen      ; ///< 정수부 길이, 소수부 길이
	int            sign            ; ///< 부호
}DOUBLESTR;
#endif
typedef long double DOUBLE;
////////////////////////////////////////////////////////////////////////////////

///////////////////// LOGOUT  /////////////////////////////////////////////////
///< Logout 관련 Define
#ifndef _LOGOUTD
#define _LOGOUTD
typedef struct _LOGINIT{
    char mode    [4];      ///< C:생성, I:Information, D:Debug, E:ERROR, J:Journal
    struct timespec nanotm; ///< Log 시각
    char lname   [80];      ///< Logfile name
    char dir     [80];      ///< Logfile DIR
    int  validdt     ;      ///< Log 보관일자
    int  pid         ;      ///< Process id
}LOG_INIT;
typedef struct _LOGDATHD{
    char mode    [4] ; ///< Logmode (C, I, D, E, J)
    struct timespec nanotm; ///< Log 시각
    char lname   [80]; ///< Logname
    char fname   [30]; ///< file name
    char funname [30]; ///< function name
    int  line        ; ///< line number
    int          pid ; ///< Process id
    int          tid ; ///< thread id
	int         dtlen; ///< Data len
}LOG_DATAHD;
#define SZ_MAXLOG   40960 + sizeof(LOG_DATAHD)
#endif // _LOGOUTD - tb_Logman이 사용
////////////////////////////////////////////////////////////////////////////////

///////////////////////// CONTROL MESSAGE /////////////////////////////////////
#ifndef _CTL_PK_
#define _CTL_PK_
#define  CTL_MSG_LEN   80    ///< control Message 길이
///< Control Message Packet 정의
typedef struct _CTL_PK {
	struct  timespec tv;     ///< Control message 시각
	unsigned int  From;      ///< From Process ID
	unsigned int  To;        ///< To Process ID
	unsigned int  Cmd;       ///< Control Message Command ID
	char Msg[CTL_MSG_LEN ];  ///< Control Message
}CTLPK;

#define  CMD_START       1   ///< START Command ID
#define  PROCID_ALL      0   ///< 모든 PROCESS
#define  PROCID_LOGMAN   2   ///< Logman Process ID
#endif
////////////////////////////////////////////////////////////////////////////////

///< Color
#define RED   "\x1B[31m"   ///< 붉은
#define GRN   "\x1B[32m"   ///< 그린
#define YEL   "\x1B[33m"   ///< 노랑
#define BLU   "\x1B[34m"   ///< 파랑
#define MAG   "\x1B[35m"   ///< 마젠타
#define CYN   "\x1B[36m"   ///< 시얀
#define WHT   "\x1B[37m"   ///< 흰색
#define RESET "\x1B[0m"    ///< 초기화

