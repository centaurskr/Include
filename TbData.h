#ifndef TBC_DATA_H
#define TBC_DATA_H

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

typedef struct _DOUBLESTR{
	unsigned char  istr  [DSTR_LEN];
	unsigned char  fstr  [DSTR_LEN];
	int            ilen, flen;
	int            sign;
}DOUBLESTR;
#endif
typedef long double DOUBLE;
////////////////////////////////////////////////////////////////////////////////

///////////////////// LOGOUT  /////////////////////////////////////////////////
#ifndef _LOGOUTD
#define _LOGOUTD
typedef struct _LOGINIT{
    char mode    [4];
    struct timespec nanotm;
    char lname   [80];
    char dir     [80];
    int  validdt;
    int  pid;
}LOG_INIT;
typedef struct _LOGDATHD{
    char mode    [4];
    struct timespec nanotm;
    char lname   [80];
    char fname   [30];
    char funname [30];
    int  line;
    int  pid;
    int  tid;
    int  dtlen;
}LOG_DATAHD;
#define SZ_MAXLOG   40960 + sizeof(LOG_DATAHD)
#endif
//////////////////////////////////////////////////////////////////////////////

///////////////////////// CONTROL MESSAGE /////////////////////////////////////
#ifndef _CTL_PK_
#define _CTL_PK_
#define  CTL_MSG_LEN   80
typedef struct _CTL_PK {
	struct  timespec tv;
	unsigned int  From;
	unsigned int  To;
	unsigned int  Cmd;
	char Msg[CTL_MSG_LEN ];
}CTLPK;

#define  CMD_START       1
#define  PROCID_ALL      0
#define  PROCID_LOGMAN   2
#endif
//////////////////////////////////////////////////////////////////////////////

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#endif /* TBC_DATA_H */
