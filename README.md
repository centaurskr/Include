# include

`~/Project` 하위 프로젝트(`libsrc`, `Zmq`, `tools` 등)가 공유하는 C 헤더 모음입니다.
이 저장소 자체는 빌드 대상이 아니며, `-I$(HOME)/Project/include`로 include되어 `libTbC.a`,
`libTbzmq.a` 등을 사용하는 코드에 함수 프로토타입과 공용 구조체/매크로를 제공합니다.

함수 구현은 이 저장소가 아니라 `~/Project/libsrc`에 있습니다. 시그니처를 바꿀 때는 양쪽을 함께
수정해야 합니다.

## 빠른 API 찾기

필요한 기능을 아래에서 찾아 해당 헤더 파일을 확인하세요.

| 기능 | 헤더 파일 | 주요 함수/타입 |
|---|---|---|
| **날짜/시간** | `TbCapi.h` | `GetTimestamp()`, `GetNumYyyymmdd()`, `GetStrYyyymmdd()` |
| **TCP/스트림 연결** | `TbCapi.h` | `OpenInetStreamClient()`, `OpenInetStreamServer()`, `ReadStream()`, `WriteStream()` |
| **파일 메모리 매핑** | `TbCapi.h` | `MakeMapFile()`, `AttachMapFile()`, `UnmapMapFile()` |
| **멀티캐스트** | `TbCapi.h` | `OpenMtPublish()`, `OpenMtSubscribe()` |
| **Control Message** | `TbCapi.h` | `InitControlMessage()`, `ControlMessage()`, `GetControlMessageFd()` |
| **연결 리스트** | `TbCapi.h` | `TbListInit()`, `TbListInsert()`, `TbListDelete()`, `TbListFetchByKey()` |
| **JSON 생성** | `TbCapi.h` | `JsonInit()`, `JsonAdd()`, `JsonGetStr()` |
| **JSON 파싱** | `TbCapi.h` | `JsonParser()`, `JsonParserGet()` |
| **이벤트 루프(select)** | `TbCapi.h` | `AppEventInitSelect()`, `AppEventLoopSelect()`, `AppAddEventAutoIdSelect()` |
| **이벤트 루프(epoll)** | `TbCapi.h` | `Event_CreateNew()`, `Event_AddEvent()`, `Event_StartLoop()` |
| **DOUBLE 정밀 연산** | `TbCapi.h` | `AddDoubleStr()`, `SubDoubleStr()`, `MulDoubleStr()` |
| **ZeroMQ 소켓** | `Tbzmqapi.h` | `OpenPubSocket0mq()`, `OpenSubSocket0mq()`, `OpenReqSocket0mq()`, `OpenRepSocket0mq()` |
| **ZeroMQ 메시지 송수신** | `Tbzmqapi.h` | `SendMessage0mq()`, `ReceiveMessage0mq()` |
| **ZeroMQ 이벤트 루프** | `Tbzmqapi.h` | `AppEventInit()`, `AppEventLoop()` |
| **로깅 (Standalone)** | `TbLogout.h` | `InitLogout()`, `Logout()`, `CloseLogout()` |
| **로깅 (ZMQ)** | `TbLogout.h` | `InitLogout()` + `-DLOGOUT_TYPE=1 또는 11` |
| **로깅 (멀티캐스트)** | `TbLogout.h` | `InitLogout()` + `-DLOGOUT_TYPE=2` |
| **고성능 네트워크 로깅** | `netlog.h` | `InitNetLogout()`, `NetLogout()` |
| **��트워크 헬스체크** | `healthcheck.h` | `CHECK_START`, `CHECKPK` (구조체) |
| **공용 데이터 타입** | `TbData.h` | `DOUBLESTR`, `DOUBLE`, `LOG_INIT`, `CTLPK` |
| **시세 데이터 (트레이딩)** | `centodata.h` | `OHLC`, `TDATA`, `WATCHLIST` |
| **프록시 정보** | `proxy.h` | `PROXYINFOR`, `PROXY_THREAD_ARG` |
| **JSON 라이브러리** | `yyjson.h` | `yyjson_read()`, `yyjson_write()` (외부 라이브러리) |

## 구성

| 파일 | 설명 | Include Guard |
|---|---|---|
| `TbCapi.h` | 핵심 C API: 날짜/시간, 멀티캐스트 Control Message, mmap/env 파일, 소켓/스트림 I/O, `DOUBLE`/`DOUBLESTR` 연산, 연결 리스트, JSON 빌드/파싱, 이벤트 루프 | `TBC_API_H` |
| `TbData.h` | 공용 타입 정의: `DOUBLESTR`/`DOUBLE`, 로깅 구조체(`LOG_INIT`/`LOG_DATAHD`), Control Message 패킷(`CTLPK`), 색상 코드 매크로 | `TBC_DATA_H` |
| `TbLogout.h` | `Logout()`/`InitLogout()` 로깅 매크로. `-DLOGOUT_TYPE=N` 빌드 플래그로 백엔드(standalone/ZMQ/멀티캐스트, 쓰레드 유무)가 결정됨 | `TB_LOGOUT_H` |
| `Tbzmqapi.h` | `libzmq` 래퍼 API: 패턴별 소켓 open, 단일 프레임/토픽 송수신, Control Message, `IsRunning0mq()`, `GetProxyEnv()`, `zmq_poller` 기반 이벤트 루프 | `TB_ZMQ_API_H` |
| `centodata.h` | 트레이딩/코인 감시용 시세 데이터 구조체(`OHLC`, `TDATA`, `WATCHLIST`, `MAPHD`, `ORDSIG`) 및 cJSON 매크로 | `CENTODATA_H` |
| `healthcheck.h` | PUB/SUB 네트워크 헬스체크 패킷(`CHECK_START` + `CHECKPK`...) | `HEALTHCHECK_H` |
| `netlog.h` | UNIX domain datagram 기반 고성능 로거(`InitNetLogout()`/`NetLogout()`) API | `NETLOG_H` |
| `proxy.h` | ZeroMQ 프록시(`Zmq/ReqRepProxy`)의 런타임 상태(`PROXYINFOR`) 및 워커 쓰레드 인자 구조체 | `PROXY_H` |
| `yyjson.h` | 서드파티 JSON 라이브러리(MIT, ibireme/yyjson) 원본 그대로 vendoring | 원본 유지 |
| `old/` | 이전 세대 헤더(`tugboat.h`, `tblibC.h`, `logout.h`, `logoutst.h`). 현재 어떤 헤더에서도 include되지 않는 참고/레거시 용도 | - |

## 사용법

빌드가 필요한 프로젝트에서 이 경로를 include 경로로 추가합니다.

```makefile
LD_HOME     = $(HOME)/Project
COMMON_INCL = -I$(LD_HOME)/include
```

### 로깅 설정 예제

**Standalone 로깅**
```bash
gcc -DLOGOUT_TYPE=0 myapp.c -o myapp
```

**ZeroMQ 로깅 (비스레드)**
```bash
gcc -DLOGOUT_TYPE=1 myapp.c -o myapp -lzmq
```

**ZeroMQ 로깅 (스레드)**
```bash
gcc -DLOGOUT_TYPE=11 myapp.c -o myapp -lzmq -lpthread
```

**멀티캐스트 로깅**
```bash
gcc -DLOGOUT_TYPE=2 myapp.c -o myapp
```

## 헤더별 기본 사용 패턴

### TbCapi.h - 시간 얻기
```c
#include "TbCapi.h"

unsigned long timestamp = GetTimestamp();     // UNIX 타임스탬프
int yymmdd = GetNumYyyymmdd();                // YYYYMMDD 정수형
```

### TbCapi.h - TCP 연결
```c
#include "TbCapi.h"

int fd = OpenInetStreamClient("127.0.0.1", 8080);
if (fd < 0) { /* error */ }
char buf[1024];
int n = ReadStream(fd, buf);
```

### Tbzmqapi.h - ZeroMQ PUB/SUB
```c
#include "Tbzmqapi.h"

void *pub = OpenPubSocket0mq(ctx, "tcp://127.0.0.1:5555");
SendMessage0mq(pub, "Hello", 5);
```

### TbLogout.h - 로깅
```c
#include "TbLogout.h"

InitLogout(argc, argv, "myapp.log", 30);  // 30일 보관
Logout('I', "Application started");
Logout('E', "Error occurred: %d", errno);
CloseLogout();
```

### netlog.h - 고성능 네트워크 로깅
```c
#include "netlog.h"

InitNetLogout("order-engine", 0);
NetLogout(LOG_INFO, "Trade executed: %.2f", price);
```

## 참고

- 테스트/빌드 스위트가 없습니다. 이 헤더를 사용하는 `~/Project/libsrc`, `~/Project/Zmq`,
  `~/Project/tools` 등이 정상적으로 컴파일되는지로 검증합니다.
- Include guard는 표준화되었습니다: `파일명_대문자_H` 형식 (예: `TBC_API_H`)
