//
// Description :
// File Name   : centodata.h
// Date        : 2023. 05. 25. (목) 14:54:16 KST
// By  : Cento
//

#ifndef CENTODATA_H
#define CENTODATA_H

#define GETJSON(json, key)      cJSON_GetObjectItem(json, key)
#define GETJSONARRAY(json, idx) cJSON_GetArrayItem(json, idx)

// MA short term and long term
#define MA_STERM  7
#define MA_LTERM  24

// 기본 DATA 갯수
#define DATA_COUNT  1440
typedef struct _OHLC{
	unsigned long   tmsp;
	unsigned long   tm;
	double  o,h,l,c;
	double  v;
}OHLC;

typedef struct _TDATA{
	unsigned long   tmsp;
	unsigned long   tm;
	int     isopen;
	double  o,h,l,c;
	double  v;
	int     cnt;
	double  price;
	int     ema,macd;
	int     ema_cnt;
	int     macd_cnt;
}TDATA;
typedef struct _WATCHLIST{
	char    coin[30];
	TDATA   data[DATA_COUNT];
	unsigned long lastseq;
	int     isord;
}WATCHLIST;
typedef struct _MAPHD{
	int     count;
	int     dcount;
	int     pos;
	int     bpos;
	int     startpos;
}MAPHD;

typedef struct _ORDSIG{ char coin[30]; double price; }ORDSIG;

#endif /* CENTODATA_H */
