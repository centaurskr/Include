# 사용 예제

이 디렉터리에는 각 헤더 파일별 실제 사용 예제가 포함되어 있습니다.

## 예제 목록

### 기본 데이터 타입
- [`DOUBLESTR_example.c`](#doublestr_examplec) - 고정밀 소수점 연산
- [`TimeDate_example.c`](#timedate_examplec) - 날짜/시간 함수

### 네트워크 통신
- [`TCP_Client_example.c`](#tcp_client_examplec) - TCP 클라이언트
- [`TCP_Server_example.c`](#tcp_server_examplec) - TCP 서버
- [`Multicast_example.c`](#multicast_examplec) - 멀티캐스트 송수신

### ZeroMQ
- [`ZMQ_PubSub_example.c`](#zmq_pubsub_examplec) - PUB/SUB 패턴
- [`ZMQ_ReqRep_example.c`](#zmq_reqrep_examplec) - REQ/REP 패턴
- [`ZMQ_EventLoop_example.c`](#zmq_eventloop_examplec) - 이벤트 루프

### 로깅
- [`Logging_Standalone_example.c`](#logging_standalone_examplec) - Standalone 로깅
- [`Logging_ZMQ_example.c`](#logging_zmq_examplec) - ZMQ 로깅
- [`Logging_Netlog_example.c`](#logging_netlog_examplec) - 고성능 네트워크 로깅

### 데이터 구조
- [`LinkedList_example.c`](#linkedlist_examplec) - 연결 리스트
- [`JSON_example.c`](#json_examplec) - JSON 생성/파싱

---

## DOUBLESTR_example.c

고정밀 소수점 연산 예제

```c
#include <stdio.h>
#include "TbCapi.h"
#include "TbData.h"

int main(void)
{
    DOUBLESTR a, b, result;

    // a = "123.456"
    SetDoubleStr_Str(&a, "123.456");
    
    // b = "789.321"
    SetDoubleStr_Str(&b, "789.321");

    // result = a + b
    AddDoubleStr(&result, &a, &b);
    
    char buf[100];
    GetDoubleStr_Str(buf, &result);
    printf("Sum: %s\n", buf);  // 912.777

    // result = a * b
    MulDoubleStr(&result, &a, &b);
    GetDoubleStr_Str(buf, &result);
    printf("Product: %s\n", buf);

    return 0;
}
```

---

## TimeDate_example.c

날짜/시간 함수 사용 예제

```c
#include <stdio.h>
#include <time.h>
#include "TbCapi.h"

int main(void)
{
    unsigned long timestamp = GetTimestamp();
    printf("Current UNIX timestamp: %lu\n", timestamp);

    int yymmdd = GetNumYyyymmdd();
    printf("Current date (YYYYMMDD): %d\n", yymmdd);

    char buf[20];
    GetStrYyyymmdd(buf);
    printf("Date string (YYYY-MM-DD): %s\n", buf);

    GetStrYymmddhhmmsscc(buf);
    printf("DateTime string: %s\n", buf);

    // 다음날 계산
    int next_day = IncDecNumYyyymmdd(yymmdd, 1);
    printf("Next day: %d\n", next_day);

    return 0;
}
```

---

## TCP_Client_example.c

TCP 클라이언트 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "TbCapi.h"

int main(int argc, char *argv[])
{
    const char *host = "127.0.0.1";
    int port = 8080;

    // 서버에 연결
    int fd = OpenInetStreamClient((char *)host, port);
    if (fd < 0) {
        fprintf(stderr, "Failed to connect to %s:%d\n", host, port);
        return 1;
    }

    printf("Connected to %s:%d\n", host, port);

    // 메시지 송신
    const char *msg = "Hello Server!";
    int n = WriteStream(fd, (char *)msg, strlen(msg));
    printf("Sent %d bytes\n", n);

    // 메시지 수신
    char buf[1024];
    int nbytes = ReadStream(fd, buf);
    if (nbytes > 0) {
        printf("Received: %.*s\n", nbytes, buf);
    }

    close(fd);
    return 0;
}
```

---

## TCP_Server_example.c

TCP 서버 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "TbCapi.h"

int main(void)
{
    int port = 8080;

    // 서버 소켓 생성
    int server_fd = OpenInetStreamServer(port);
    if (server_fd < 0) {
        fprintf(stderr, "Failed to create server on port %d\n", port);
        return 1;
    }

    printf("Server listening on port %d\n", port);

    // 클라이언트 대기
    int client_fd = WaitConnect(server_fd, NULL);
    if (client_fd >= 0) {
        printf("Client connected\n");

        // 클라이언트로부터 데이터 수신
        char buf[1024];
        int n = ReadStream(client_fd, buf);
        if (n > 0) {
            printf("Received from client: %.*s\n", n, buf);
        }

        // 클라이언트로 응답 송신
        const char *response = "Hello Client!";
        WriteStream(client_fd, (char *)response, 13);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
```

---

## Multicast_example.c

멀티캐스트 송수신 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "TbCapi.h"

int main(void)
{
    const char *group = "224.0.0.1";
    int port = 12345;
    const char *dev = "eth0";  // 네트워크 디바이스
    int ttl = 64;

    // 발행자
    struct sockaddr_in addr;
    int pub_fd = OpenMtPublish(&addr, dev, (char *)group, port, ttl);
    if (pub_fd >= 0) {
        const char *msg = "Multicast message";
        WriteStream(pub_fd, (char *)msg, sizeof(msg));
        printf("Published message\n");
        close(pub_fd);
    }

    // 구독자
    int sub_fd = OpenMtSubscribe(dev, (char *)group, port);
    if (sub_fd >= 0) {
        char buf[1024];
        int n = ReadStream(sub_fd, buf);
        printf("Received: %.*s\n", n, buf);
        close(sub_fd);
    }

    return 0;
}
```

---

## ZMQ_PubSub_example.c

ZeroMQ PUB/SUB 패턴 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>
#include "Tbzmqapi.h"

int main(void)
{
    // ZMQ 컨텍스트 생성
    void *ctx = zmq_ctx_new();

    // 발행자 소켓 생성
    void *pub = OpenPubSocket0mq(ctx, "tcp://127.0.0.1:5555");
    if (!pub) {
        fprintf(stderr, "Failed to create PUB socket\n");
        return 1;
    }

    // 토픽별로 메시지 송신
    SendTopicMessage0mq(pub, "weather", "sunny", 5);
    printf("Published: weather=sunny\n");

    sleep(1);

    // 구독자 소켓 생성
    void *sub = OpenSubSocket0mq(ctx, "tcp://127.0.0.1:5555");
    SetSubTopic0mq(sub, "weather");

    sleep(1);  // 구독 시간 확보

    // 메시지 수신
    char topic[64], msg[256];
    int msg_len;
    ReceiveTopic0mq(sub, topic, msg, sizeof(msg));
    printf("Subscribed: %s=%s\n", topic, msg);

    zmq_close(pub);
    zmq_close(sub);
    zmq_ctx_destroy(ctx);

    return 0;
}
```

---

## ZMQ_ReqRep_example.c

ZeroMQ REQ/REP 패턴 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>
#include "Tbzmqapi.h"

// 서버 (REP)
void *server_thread(void *arg)
{
    void *ctx = (void *)arg;
    void *rep = OpenRepSocket0mq(ctx, "tcp://127.0.0.1:5556");

    char buf[256];
    int size;

    size = ReceiveMessage0mq(rep, &size);  // 요청 수신
    printf("Server received: %s\n", buf);

    const char *response = "Reply from server";
    SendMessage0mq(rep, (char *)response, strlen(response));

    zmq_close(rep);
    return NULL;
}

int main(void)
{
    void *ctx = zmq_ctx_new();

    // 클라이언트 (REQ)
    void *req = OpenReqSocket0mq(ctx, "tcp://127.0.0.1:5556");

    const char *request = "Hello Server";
    SendMessage0mq(req, (char *)request, strlen(request));
    printf("Client sent: %s\n", request);

    char buf[256];
    int size;
    ReceiveMessage0mq(req, &size);
    printf("Client received: %s\n", buf);

    zmq_close(req);
    zmq_ctx_destroy(ctx);

    return 0;
}
```

---

## ZMQ_EventLoop_example.c

ZeroMQ 이벤트 루프 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <zmq.h>
#include "Tbzmqapi.h"

int socket_handler(void *ent, void *socket, int events)
{
    char buf[256];
    int size;
    char *msg = ReceiveMessage0mq(socket, &size);
    
    printf("Event handler received: %s\n", msg);
    free(msg);
    
    return 0;
}

int main(void)
{
    void *ctx = zmq_ctx_new();

    // 이벤트 루프 초기화
    void *event = AppEventInit();
    if (!event) {
        fprintf(stderr, "Failed to initialize event loop\n");
        return 1;
    }

    // SUB 소켓 생성 및 이벤트에 등록
    void *sub = OpenSubSocket0mq(ctx, "tcp://127.0.0.1:5557");
    SetSubTopic0mq(sub, "events");
    
    AppAddEventAutoId0mq(event, sub, 1000, 0, socket_handler);

    // 이벤트 루프 실행
    AppEventLoop(event);

    zmq_close(sub);
    zmq_ctx_destroy(ctx);

    return 0;
}
```

---

## Logging_Standalone_example.c

Standalone 로깅 예제 (컴파일: `gcc -DLOGOUT_TYPE=0`)

```c
#include <stdio.h>
#include "TbLogout.h"

int main(int argc, char *argv[])
{
    // 로깅 초기화
    InitLogout(argc, argv, "myapp.log", 30);  // 30일 보관

    // 정보 로그
    Logout('I', "Application started");
    Logout('I', "Version: %s", "1.0.0");

    // 에러 로그
    Logout('E', "Failed to connect to database");
    Logout('E', "Error code: %d", 404);

    // 디버그 로그
    Logout('D', "Debug information: x=%d, y=%d", 10, 20);

    // 로깅 종료
    CloseLogout();

    return 0;
}
```

---

## Logging_ZMQ_example.c

ZMQ 로깅 예제 (컴파일: `gcc -DLOGOUT_TYPE=1 -lzmq`)

```c
#include <stdio.h>
#include "TbLogout.h"

int main(int argc, char *argv[])
{
    // ZMQ를 통한 로깅 초기화
    InitLogout(NULL, 0, "zmq_app.log", 7);

    Logout('I', "ZMQ logging initialized");
    Logout('I', "Processing order: %s", "BUY 100 AAPL");
    Logout('E', "Order failed: insufficient balance");

    CloseLogout();

    return 0;
}
```

---

## Logging_Netlog_example.c

고성능 네트워크 로깅 예제

```c
#include <stdio.h>
#include <unistd.h>
#include "netlog.h"

int main(void)
{
    // 프로세스명과 인덱스로 초기화
    InitNetLogout("order-engine", 0);

    // 정보 로그
    NetLogout(LOG_INFO, "Engine started");
    
    // 트레이드 로그
    NetLogout(LOG_INFO, "Trade executed: AAPL@150.25 qty=100");
    
    // 에러 로그
    NetLogout(LOG_ERROR, "Connection lost to price feed");
    
    // 디버그 로그
    NetLogout(LOG_DEBUG, "Processing tick data: %s", "SPY,AAPL,MSFT");

    return 0;
}
```

---

## LinkedList_example.c

연결 리스트 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TbCapi.h"

typedef struct {
    int id;
    char name[32];
} Record;

int main(void)
{
    // 리스트 초기화
    void *list = TbListInit();

    // 항목 추가
    Record r1 = {1, "Alice"};
    Record r2 = {2, "Bob"};
    Record r3 = {3, "Charlie"};

    TbListInsert(list, 1, &r1, sizeof(Record));
    TbListInsert(list, 2, &r2, sizeof(Record));
    TbListInsert(list, 3, &r3, sizeof(Record));

    // 인덱스로 조회
    Record *p = (Record *)TbListFetchByIndex(list, 2);
    if (p) {
        printf("Found: id=%d, name=%s\n", p->id, p->name);
    }

    // 키로 조회
    p = (Record *)TbListFetchByKey(list, 1);
    if (p) {
        printf("Found: id=%d, name=%s\n", p->id, p->name);
    }

    // 항목 삭제
    TbListDelete(list, 2);
    printf("Deleted record with id=2\n");

    // 리스트 해제
    TbListDestory(list);

    return 0;
}
```

---

## JSON_example.c

JSON 생성/파싱 예제

```c
#include <stdio.h>
#include <stdlib.h>
#include "TbCapi.h"

int main(void)
{
    // JSON 생성
    void *json = JsonInit();

    JsonStart(json);
    JsonAdd(json, "name", "John");
    JsonAdd(json, "city", "Seoul");
    JsonAddInt(json, "age", 30);
    JsonEnd(json, 0);

    char *json_str = JsonGetStr(json);
    printf("Generated JSON: %s\n", json_str);

    JsonFree(json);

    // JSON 파싱
    const char *json_data = "{\"name\":\"Alice\",\"age\":25,\"city\":\"Busan\"}";
    void *parser = JsonParser((char *)json_data);

    char *name = JsonParserGet(parser, "name");
    char *city = JsonParserGet(parser, "city");

    printf("Parsed: name=%s, city=%s\n", name, city);

    JsonParserFree(parser);

    return 0;
}
```

---

## 컴파일 및 실행

### 기본 컴파일
```bash
gcc -I$(HOME)/Project/include -o example example.c -L$(HOME)/Project/lib -lTbC
```

### ZMQ 예제
```bash
gcc -I$(HOME)/Project/include -o zmq_example zmq_example.c -L$(HOME)/Project/lib -lTbzmq -lzmq
```

### 로깅 예제 (Standalone)
```bash
gcc -DLOGOUT_TYPE=0 -I$(HOME)/Project/include -o logging_example logging_example.c -L$(HOME)/Project/lib -lTbC
```

### 로깅 예제 (ZMQ)
```bash
gcc -DLOGOUT_TYPE=1 -I$(HOME)/Project/include -o logging_zmq_example logging_zmq_example.c -L$(HOME)/Project/lib -lTbzmq -lzmq
```

---

## 주의사항

- 모든 예제는 참고용이며, 실제 프로젝트에 맞게 수정하여 사용하세요.
- 포트 번호, 호스트명, 로그 경로 등은 환경에 맞게 변경하세요.
- ZMQ 예제는 `libzmq`가 설치되어 있어야 합니다.
- 로깅은 `-DLOGOUT_TYPE` 플래그로 백엔드를 지정해야 합니다.
