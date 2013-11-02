#ifndef _QICHE_COMMON_HPP_
#define _QICHE_COMMON_HPP_

#include <map>

enum EType
{
	eTypeData = 0,
	eTypeNumber
};

static const std::string kTypeRaw    = "raw";
static const std::string kTypeAscii  = "ascii";
static const std::string kTypeHexa   = "hexa";
static const std::string kTypeUInt8  = "uint8";
static const std::string kTypeInt8   = "int8";
static const std::string kTypeUInt16 = "uint16";
static const std::string kTypeInt16  = "int16";
static const std::string kTypeUInt32 = "uint32";
static const std::string kTypeInt32  = "int32";
static const std::string kTypeHalf   = "half";
static const std::string kTypeFloat  = "float";
static const std::string kTypeDouble = "double";

enum ESubType
{
	eTypeRaw = 0,
	eTypeAscii,
	eTypeHexa,
	eTypeUInt8,
	eTypeInt8,
	eTypeUInt16,
	eTypeInt16,
	eTypeUInt32,
	eTypeInt32,
	eTypeHalf,
	eTypeFloat,
	eTypeDouble
};

static std::map< std::string, ESubType > mSubType {
	{ kTypeRaw,    eTypeRaw    },
	{ kTypeAscii,  eTypeAscii  },
	{ kTypeHexa,   eTypeHexa   },
	{ kTypeUInt8,  eTypeUInt8  },
	{ kTypeInt8,   eTypeInt8   },
	{ kTypeUInt16, eTypeUInt16 },
	{ kTypeInt16,  eTypeInt16  },
	{ kTypeUInt32, eTypeUInt32 },
	{ kTypeInt32,  eTypeInt32  },
	{ kTypeHalf,   eTypeHalf   },
	{ kTypeFloat,  eTypeFloat  },
	{ kTypeDouble, eTypeDouble }
};

enum EStatus
{
	eStatusNotCheck = 0,
	eStatusValid,
	eStatusInvalid,
	eStatusInvalidButOptional,
	eStatusInvalidForUnordered,
	eStatusInvalidButSkip,
	eStatusPassOverData,
	eStatusSkip
};

#endif
