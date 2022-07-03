#ifndef OUCH_MESSAGE_H
#define OUCH_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/*
 * Package header:
 */
struct package_header {
        uint16_t StreamId;
        uint32_t PackageSize;
}__attribute__((packed));;

/*
 * Message types:
 */
enum ouch_msg_type {
	OUCH_MSG_SYSTEM_EVENT   = 'S',
	OUCH_MSG_ACCEPTED	= 'A',
	OUCH_MSG_REPLACED	= 'U',
	OUCH_MSG_CANCELED	= 'C',
	OUCH_MSG_EXECUTED	= 'E',
};

/*
 * OUCH message length:
 */
struct ouch_message_len {
        uint16_t MsgLen;   
} __attribute__((packed));

/*
 * OUCH message length:
 */
struct ouch_message {
        char                    MessageType;
} __attribute__((packed));

/*
 * OUCH message event:
 */
struct ouch_msg_system_event {
        char   			PackageType;  
	uint8_t			MessageType;
	uint64_t		Timestamp;
	char			EventEnumeration;
} __attribute__((packed));

/*
 * OUCH message accepted:
 */
struct ouch_msg_accepted {
        char   			PackageType;  
	uint8_t			MessageType;
	uint64_t		Timestamp;
	char			OrderToken[14];
	char			Side;
	uint32_t		Shares;
	char			Symbol[8];
	uint32_t		Price;
	uint32_t		TimeInForce;
	char			Firm[4];
	char			Display;
	uint64_t		OrderReferenceNumber;
	char			Capacity;
	char			IntermarketSweep;
	uint32_t		MinimumQuantity;
	char			CrossType;
	char			OrderState;
} __attribute__((packed));

/*
 * OUCH message replaced:
 */
struct ouch_msg_replaced {
        char   			PackageType;  
	uint8_t			MessageType;
	uint64_t		Timestamp;
	char			OrderToken[14];
	char			Side;
	uint32_t		Shares;
	char			Symbol[8];
	uint32_t		Price;
	uint32_t		TimeInForce;
	char			Firm[4];
	char			Display;
	uint64_t		OrderReferenceNumber;
	char			Capacity;
	char			IntermarketSweep;
	uint32_t		MinimumQuantity;
	char			CrossType;
	char			OrderState;
	char			PreviousOrderToken[14];
} __attribute__((packed));

/*
 * OUCH message cancelled:
 */
struct ouch_msg_canceled {
        char   			PackageType;  
	uint8_t			MessageType;
	uint64_t		Timestamp;
	char			OrderToken[14];
	uint32_t		DecrementShares;
	char			Reason;
} __attribute__((packed));

/*
 * OUCH message executed:
 */
struct ouch_msg_executed {
        char   			PackageType;  
	uint8_t			MessageType;
	uint64_t		Timestamp;
	char			OrderToken[14];
	uint32_t		ExecutedShares;
	uint32_t		ExecutionPrice;
	char			LiquidityFlag;
	uint64_t		MatchNumber;
} __attribute__((packed));

#ifdef __cplusplus
}
#endif

#endif
