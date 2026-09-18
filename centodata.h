//
// Description :
// File Name   : centodata.h
// Date        : 2023. 05. 25. (목) 14:54:16 KST
// By  : Cento
//

#ifndef _CENTODATA_H_
#define _CENTODATA_H_

#define GETJSON(json, key)      cJSON_GetObjectItem(json, key)
#define GETJSONARRAY(json, idx) cJSON_GetArrayItem(json, idx)

// MA short term and long term
#define MA_STERM  7
#define MA_LTERM  24

// 기본 DATA 갯수
#define DATA_COUNT  1440
typedef struct _OHLC{
	unsigned long   tmsp; // timestamp
	unsigned long   tm  ; // yymmddhhmm
	double  o,h,l,c     ; // OHLC
	double  v           ; // 거래량
}OHLC;

typedef struct _TDATA{
	unsigned long   tmsp; // timestamp
	unsigned long   tm  ; // yymmddhhmm
	int     isopen      ; // 시가?
	double  o,h,l,c     ; // OHLC
	double  v         ; // 거래량
	int     cnt         ; // 체결건수
	double  price       ; // 대표 값 = (h + l)/2.0
	int     ema,macd    ; // Golden cross flag
	int     ema_cnt     ; // 이동평균 Golden cross count
	int     macd_cnt    ; // MACD     Golden cross count
}TDATA;
typedef struct _WATCHLIST{
	char    coin[30]        ;  // 종목명
	TDATA   data[DATA_COUNT];
	unsigned long lastseq   ; // 마지막 sequential_id : 1683514583071000
	int     isord           ;
}WATCHLIST;
typedef struct _MAPHD{
	int     count   ; // Coin count
	int     dcount  ; // 일자 COUNT(DATA_COUNT)
	int     pos     ; // Current Index (will be write)
	int     bpos    ; // 직전 Index
	int     startpos; // Data 시작 Index
}MAPHD;

// 주문 SIGNAL PACKET
typedef struct _ORDSIG{ char coin[30]; double price; }ORDSIG;

#endif // _CENTODATA_H_
