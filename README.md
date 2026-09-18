# include

`~/Project` 하위 프로젝트(`libsrc`, `Zmq`, `tools` 등)가 공유하는 C 헤더 모음입니다.
이 저장소 자체는 빌드 대상이 아니며, `-I$(HOME)/Project/include`로 include되어 `libTbC.a`,
`libTbzmq.a` 등을 사용하는 코드에 함수 프로토타입과 공용 구조체/매크로를 제공합니다.

함수 구현은 이 저장소가 아니라 `~/Project/libsrc`에 있습니다. 시그니처를 바꿀 때는 양쪽을 함께
수정해야 합니다.

## 구성

| 파일 | 설명 |
|---|---|
| `TbCapi.h` | 핵심 C API: 날짜/시간, 멀티캐스트 Control Message, mmap/env 파일, 소켓/스트림 I/O, `DOUBLE`/`DOUBLESTR` 연산, 연결 리스트, JSON 빌드/파싱, `select()`/`epoll()` 기반 두 종류의 이벤트 루프 |
| `TbData.h` | 공용 타입 정의: `DOUBLESTR`/`DOUBLE`, 로깅 구조체(`LOG_INIT`/`LOG_DATAHD`), Control Message 패킷(`CTLPK`), 색상 코드 매크로 |
| `TbLogout.h` | `Logout()`/`InitLogout()` 로깅 매크로. `-DLOGOUT_TYPE=N` 빌드 플래그로 백엔드(standalone/ZMQ/멀티캐스트, 쓰레드 유무)가 결정됨 |
| `Tbzmqapi.h` | `libzmq` 래퍼 API: 패턴별 소켓 open, 단일 프레임/토픽 송수신, Control Message, `IsRunning0mq()`, `GetProxyEnv()`, `zmq_poller` 기반 이벤트 루프 |
| `centodata.h` | 트레이딩/코인 감시용 시세 데이터 구조체(`OHLC`, `TDATA`, `WATCHLIST`, `MAPHD`, `ORDSIG`) 및 cJSON 매크로 |
| `healthcheck.h` | PUB/SUB 네트워크 헬스체크 패킷(`CHECK_START` + `CHECKPK`...) |
| `netlog.h` | UNIX domain datagram 기반 고성능 로거(`InitNetLogout()`/`NetLogout()`) API |
| `proxy.h` | ZeroMQ 프록시(`Zmq/ReqRepProxy`)의 런타임 상태(`PROXYINFOR`) 및 워커 쓰레드 인자 구조체 |
| `yyjson.h` | 서드파티 JSON 라이브러리(MIT, ibireme/yyjson) 원본 그대로 vendoring |
| `old/` | 이전 세대 헤더(`tugboat.h`, `tblibC.h`, `logout.h`, `logoutst.h`). 현재 어떤 헤더에서도 include되지 않는 참고/레거시 용도 |

## 사용법

빌드가 필요한 프로젝트에서 이 경로를 include 경로로 추가합니다.

```makefile
LD_HOME     = $(HOME)/Project
COMMON_INCL = -I$(LD_HOME)/include
```

## 참고

- 테스트/빌드 스위트가 없습니다. 이 헤더를 사용하는 `~/Project/libsrc`, `~/Project/Zmq`,
  `~/Project/tools` 등이 정상적으로 컴파일되는지로 검증합니다.
