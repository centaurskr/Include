//
/// @short  Zmq PUB/SUB broker 를 이용하는 Process들 사이의 \n
///         Network 상황을 검사하는 packet 정의
/// @file healthcheck.h
/// @date 2023. 12. 06. (수) 14:10:41 KST
/// @author Cento 
//
#include <time.h>

//
/// @struct _CHECK_START
/// @brief  Network Check 맨 처음 packet
//
typedef struct _CHECK_START{
	unsigned long   id          ; ///< Health check id (timestamp)
	char            hostname[16]; ///< hostname
	char            pname   [32]; ///< 프로세스이름
	int             index       ; ///< Process Index (필요시, 0:관계없음)
	char            endpoint[80]; ///< Return endpoint(tcp://xxxx:port)
	int             hops        ; ///< 현재 몇번 째 Process인가? (처음은 0)
	struct timespec tmspec      ; ///< 시작 시각
}CHECK_START;
//
/// @struct _CHECKPK
/// @brief  Network Check process structure\n
/// 하나의 Process를 통과할 때 마다 _NETCHECK가 추가된다\n
/// ex) CHECK_START + CHECKPK ....... + CHECKPK
//
typedef struct _CHECKPK{
	char            hostname[16]; ///< hostname
	char            pname   [32]; ///< 프로세스이름
	int             index       ; ///< Process Index (필요시, 0:관계없음)
	struct timespec tmspec      ; ///< 수신 시각
}CHECKPK;
