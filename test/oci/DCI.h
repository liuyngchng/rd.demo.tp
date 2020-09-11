#ifndef _OCI_H
#define _OCI_H

#ifndef DCI_EXPORT
#define OCI_EXPORT
#endif
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OCI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OCI_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

//#ifdef OCI_EXPORTS
//#define OCI_API __declspec(dllexport)
//#else
//#define OCI_API __declspec(dllimport)
// #endif
#ifdef WIN32
#define OCI_API   __declspec( dllexport )
#else
#define OCI_API 
#endif

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * $Header: oci.h 26-nov-2003.16:37:14 chliang Exp $
 */
//int OCIInvalidHandle();
#define OCI_TYPECODE_REF         SQLT_REF        /* SQL/OTS OBJECT REFERENCE */
#define     DCI_TYPECODE_REF                OCI_TYPECODE_REF
#define OCI_TYPECODE_DATE        SQLT_DAT        /* SQL DATE  OTS DATE */
#define     DCI_TYPECODE_DATE               OCI_TYPECODE_DATE
#define OCI_TYPECODE_SIGNED8     27             /* SQL SIGNED INTEGER(8)  OTS SINT8 */
#define     DCI_TYPECODE_SIGNED8            OCI_TYPECODE_SIGNED8
#define OCI_TYPECODE_SIGNED16    28             /* SQL SIGNED INTEGER(16)  OTS SINT16 */
#define     DCI_TYPECODE_SIGNED16           OCI_TYPECODE_SIGNED16
#define OCI_TYPECODE_SIGNED32    29             /* SQL SIGNED INTEGER(32)  OTS SINT32 */
#define     DCI_TYPECODE_SIGNED32           OCI_TYPECODE_SIGNED32
#define OCI_TYPECODE_REAL        21             /* SQL REAL  OTS SQL_REAL */
#define     DCI_TYPECODE_REAL               OCI_TYPECODE_REAL
#define OCI_TYPECODE_DOUBLE      22             /* SQL DOUBLE PRECISION  OTS SQL_DOUBLE */
#define     DCI_TYPECODE_DOUBLE             OCI_TYPECODE_DOUBLE
#define OCI_TYPECODE_FLOAT       SQLT_FLT       /* SQL FLOAT(P)  OTS FLOAT(P) */
#define     DCI_TYPECODE_FLOAT              OCI_TYPECODE_FLOAT
#define OCI_TYPECODE_NUMBER      SQLT_NUM       /* SQL NUMBER(P S)  OTS NUMBER(P S) */
#define     DCI_TYPECODE_NUMBER             OCI_TYPECODE_NUMBER
#define OCI_TYPECODE_DECIMAL     SQLT_PDN       /* SQL DECIMAL(P S)  OTS DECIMAL(P S) */
#define     DCI_TYPECODE_DECIMAL            OCI_TYPECODE_DECIMAL
#define OCI_TYPECODE_UNSIGNED8   SQLT_BIN       /* SQL UNSIGNED INTEGER(8)  OTS UINT8 */
#define     DCI_TYPECODE_UNSIGNED8          OCI_TYPECODE_UNSIGNED8
#define OCI_TYPECODE_UNSIGNED16  25             /* SQL UNSIGNED INTEGER(16)  OTS UINT16 */
#define     DCI_TYPECODE_UNSIGNED16         OCI_TYPECODE_UNSIGNED16
#define OCI_TYPECODE_UNSIGNED32  26             /* SQL UNSIGNED INTEGER(32)  OTS UINT32 */
#define     DCI_TYPECODE_UNSIGNED32         OCI_TYPECODE_UNSIGNED32
#define OCI_TYPECODE_BFLOAT      SQLT_IBFLOAT   /* Binary float */
#define     DCI_TYPECODE_BFLOAT             OCI_TYPECODE_BFLOAT
#define OCI_TYPECODE_BDOUBLE     SQLT_IBDOUBLE  /* Binary double */
#define     DCI_TYPECODE_BDOUBLE            OCI_TYPECODE_BDOUBLE
#define OCI_TYPECODE_OCTET       245            /* SQL ???  OTS OCTET */
#define     DCI_TYPECODE_OCTET              OCI_TYPECODE_OCTET
#define OCI_TYPECODE_SMALLINT    246            /* SQL SMALLINT  OTS SMALLINT */
#define     DCI_TYPECODE_SMALLINT           OCI_TYPECODE_SMALLINT
#define OCI_TYPECODE_INTEGER     SQLT_INT       /* SQL INTEGER  OTS INTEGER */
#define     DCI_TYPECODE_INTEGER            OCI_TYPECODE_INTEGER
#define OCI_TYPECODE_RAW         SQLT_LVB       /* SQL RAW(N)  OTS RAW(N) */
#define     DCI_TYPECODE_RAW                OCI_TYPECODE_RAW
#define OCI_TYPECODE_PTR         32             /* SQL POINTER  OTS POINTER */
#define     DCI_TYPECODE_PTR                OCI_TYPECODE_PTR
#define OCI_TYPECODE_VARCHAR2    SQLT_VCS       /* SQL VARCHAR2(N)  OTS SQL_VARCHAR2(N) */
#define     DCI_TYPECODE_VARCHAR2           OCI_TYPECODE_VARCHAR2
#define OCI_TYPECODE_CHAR        SQLT_AFC       /* SQL CHAR(N)  OTS SQL_CHAR(N) */
#define     DCI_TYPECODE_CHAR               OCI_TYPECODE_CHAR
#define OCI_TYPECODE_VARCHAR     SQLT_CHR       /* SQL VARCHAR(N)  OTS SQL_VARCHAR(N) */
#define     DCI_TYPECODE_VARCHAR            OCI_TYPECODE_VARCHAR
#define OCI_TYPECODE_MLSLABEL    SQLT_LAB       /* OTS MLSLABEL */
#define     DCI_TYPECODE_MLSLABEL           OCI_TYPECODE_MLSLABEL
#define OCI_TYPECODE_VARRAY      247            /* SQL VARRAY  OTS PAGED VARRAY */
#define     DCI_TYPECODE_VARRAY             OCI_TYPECODE_VARRAY
#define OCI_TYPECODE_TABLE       248            /* SQL TABLE  OTS MULTISET */
#define     DCI_TYPECODE_TABLE              OCI_TYPECODE_TABLE
#define OCI_TYPECODE_OBJECT      SQLT_NTY       /* SQL/OTS NAMED OBJECT TYPE */
#define     DCI_TYPECODE_OBJECT             OCI_TYPECODE_OBJECT
#define OCI_TYPECODE_OPAQUE       58            /*  SQL/OTS Opaque Types */
#define     DCI_TYPECODE_OPAQUE             OCI_TYPECODE_OPAQUE
#define OCI_TYPECODE_NAMEDCOLLECTION  SQLT_NCO  /* SQL/OTS NAMED COLLECTION TYPE */
#define     DCI_TYPECODE_NAMEDCOLLECTION    OCI_TYPECODE_NAMEDCOLLECTION
#define OCI_TYPECODE_BLOB        SQLT_BLOB      /* SQL/OTS BINARY LARGE OBJECT */
#define     DCI_TYPECODE_BLOB               OCI_TYPECODE_BLOB
#define OCI_TYPECODE_BFILE       SQLT_BFILE     /* SQL/OTS BINARY FILE OBJECT */
#define     DCI_TYPECODE_BFILE              OCI_TYPECODE_BFILE
#define OCI_TYPECODE_CLOB        SQLT_CLOB      /* SQL/OTS CHARACTER LARGE OBJECT */
#define     DCI_TYPECODE_CLOB               OCI_TYPECODE_CLOB
#define OCI_TYPECODE_CFILE       SQLT_CFILE     /* SQL/OTS CHARACTER FILE OBJECT */
#define     DCI_TYPECODE_CFILE              OCI_TYPECODE_CFILE

/* the following are ANSI datetime datatypes added in 8.1 */
#define OCI_TYPECODE_TIME        SQLT_TIME              /* SQL/OTS TIME */
#define     DCI_TYPECODE_TIME               OCI_TYPECODE_TIME
#define OCI_TYPECODE_TIME_TZ     SQLT_TIME_TZ           /* SQL/OTS TIME_TZ */
#define     DCI_TYPECODE_TIME_TZ            OCI_TYPECODE_TIME_TZ
#define OCI_TYPECODE_TIMESTAMP   SQLT_TIMESTAMP         /* SQL/OTS TIMESTAMP */
#define     DCI_TYPECODE_TIMESTAMP          OCI_TYPECODE_TIMESTAMP
#define OCI_TYPECODE_TIMESTAMP_TZ  SQLT_TIMESTAMP_TZ    /* SQL/OTS TIMESTAMP_TZ */
#define     DCI_TYPECODE_TIMESTAMP_TZ       OCI_TYPECODE_TIMESTAMP_TZ

#define OCI_TYPECODE_TIMESTAMP_LTZ  SQLT_TIMESTAMP_LTZ  /* TIMESTAMP_LTZ */
#define     DCI_TYPECODE_TIMESTAMP_LTZ      OCI_TYPECODE_TIMESTAMP_LTZ

#define OCI_TYPECODE_INTERVAL_YM SQLT_INTERVAL_YM       /* SQL/OTS INTRVL YR-MON */
#define     DCI_TYPECODE_INTERVAL_YM        OCI_TYPECODE_INTERVAL_YM
#define OCI_TYPECODE_INTERVAL_DS SQLT_INTERVAL_DS       /* SQL/OTS INTRVL DAY-SEC */
#define     DCI_TYPECODE_INTERVAL_DS        OCI_TYPECODE_INTERVAL_DS

#define OCI_TYPECODE_OTMFIRST    228            /* first Open Type Manager typecode */
#define     DCI_TYPECODE_OTMFIRST           OCI_TYPECODE_OTMFIRST
#define OCI_TYPECODE_OTMLAST     320            /* last OTM typecode */
#define     DCI_TYPECODE_OTMLAST            OCI_TYPECODE_OTMLAST
#define OCI_TYPECODE_SYSFIRST    228            /* first OTM system type (internal) */
#define     DCI_TYPECODE_SYSFIRST           OCI_TYPECODE_SYSFIRST
#define OCI_TYPECODE_SYSLAST     235            /* last OTM system type (internal) */
#define     DCI_TYPECODE_SYSLAST            OCI_TYPECODE_SYSLAST
#define OCI_TYPECODE_PLS_INTEGER   266          /* type code for PLS_INTEGER */
#define     DCI_TYPECODE_PLS_INTEGER        OCI_TYPECODE_PLS_INTEGER

/* the following are PL/SQL-only internal. They should not be used */
#define OCI_TYPECODE_ITABLE      SQLT_TAB               /* PLSQL indexed table */
#define     DCI_TYPECODE_ITABLE             OCI_TYPECODE_ITABLE
#define OCI_TYPECODE_RECORD      SQLT_REC               /* PLSQL record */
#define     DCI_TYPECODE_RECORD             OCI_TYPECODE_RECORD
#define OCI_TYPECODE_BOOLEAN     SQLT_BOL               /* PLSQL boolean */
#define     DCI_TYPECODE_BOOLEAN            OCI_TYPECODE_BOOLEAN

/* NOTE : The following NCHAR related codes are just short forms for saying
   OCI_TYPECODE_VARCHAR2 with a charset form of SQLCS_NCHAR. These codes are
   intended for use in the OCIAnyData API only and nowhere else. */
#define OCI_TYPECODE_NCHAR       286
#define     DCI_TYPECODE_NCHAR              OCI_TYPECODE_NCHAR
#define OCI_TYPECODE_NVARCHAR2   287
#define     DCI_TYPECODE_NVARCHAR2          OCI_TYPECODE_NVARCHAR2
#define OCI_TYPECODE_NCLOB       288
#define     DCI_TYPECODE_NCLOB              OCI_TYPECODE_NCLOB

#ifndef TRUE
# define TRUE  1
# define FALSE 0
#endif

#ifndef lint
typedef unsigned char  ub1;
typedef   signed char  sb1;
#else
#define ub1 unsigned char
#define sb1 signed char
#endif

#define UB1MAXVAL ((ub1)UCHAR_MAX)
#define UB1MINVAL ((ub1)        0)
#define SB1MAXVAL ((sb1)SCHAR_MAX)
#define SB1MINVAL ((sb1)SCHAR_MIN)
#define MINUB1MAXVAL ((ub1)  255)
#define MAXUB1MINVAL ((ub1)    0)
#define MINSB1MAXVAL ((sb1)  127)
#define MAXSB1MINVAL ((sb1) -127)

#ifndef lint
typedef unsigned short    ub2;
typedef   signed short    sb2;
#else
#define ub2  unsigned short
#define sb2  signed short
#endif

#define UB2MAXVAL ((ub2)USHRT_MAX)
#define UB2MINVAL ((ub2)        0)
#define SB2MAXVAL ((sb2) SHRT_MAX)
#define SB2MINVAL ((sb2) SHRT_MIN)
#define MINUB2MAXVAL ((ub2) 65535)
#define MAXUB2MINVAL ((ub2)     0)
#define MINSB2MAXVAL ((sb2) 32767)
#define MAXSB2MINVAL ((sb2)-32767)

#ifndef lint
typedef unsigned int  ub4;
typedef   signed int  sb4;
#else
#define eb4 int
#define ub4 unsigned int
#define sb4 signed int
#endif 


#ifndef INT_MAX
#define INT_MIN     (-2147483647 - 1)   /* minimum (signed) int value */
#define INT_MAX       2147483647        /* maximum (signed) int value */
#endif

#define UB4MAXVAL ((ub4)UINT_MAX)
#define UB4MINVAL ((ub4)        0)
#define SB4MAXVAL ((sb4) INT_MAX)
#define SB4MINVAL ((sb4) INT_MIN)
#define MINUB4MAXVAL ((ub4) 4294967295)
#define MAXUB4MINVAL ((ub4)          0)
#define MINSB4MAXVAL ((sb4) 2147483647)
#define MAXSB4MINVAL ((sb4)-2147483647)


#define ORAUB8MINVAL    ((oraub8)0)
#define ORAUB8MAXVAL    ((oraub8)18446744073709551615)
#define ORASB8MINVAL    ((orasb8)-9223372036854775808)
#define ORASB8MAXVAL    ((orasb8) 9223372036854775807)

#define MAXORAUB8MINVAL ((oraub8)0)
#define MINORAUB8MAXVAL ((oraub8)18446744073709551615)
#define MAXORASB8MINVAL ((orasb8)-9223372036854775807)
#define MINORASB8MAXVAL ((orasb8) 9223372036854775807)

#define UB1BITS          CHAR_BIT
#define UB1MASK          ((1 << ((uword)CHAR_BIT)) - 1)


#ifdef lint
# define oratext unsigned char
#else
  typedef  unsigned char oratext;
#endif


#ifndef lint 
typedef          char     eb1;
typedef          short    eb2;
typedef          int      eb4;
#else
# define         eb1      char
# define         eb2      short
# define         eb4      int
#endif

#define EB1MAXVAL      ((eb1)SCHAR_MAX)
#define EB1MINVAL      ((eb1)        0)
#define MINEB1MAXVAL   ((eb1)  127)
#define MAXEB1MINVAL   ((eb1)    0)
#define EB2MAXVAL      ((eb2) SHRT_MAX)
#define EB2MINVAL      ((eb2)        0)
#define MINEB2MAXVAL   ((eb2) 32767)
#define MAXEB2MINVAL   ((eb2)     0)
#define EB4MAXVAL      ((eb4) INT_MAX)
#define EB4MINVAL      ((eb4)        0)
#define MINEB4MAXVAL   ((eb4) 2147483647)
#define MAXEB4MINVAL   ((eb4)          0)

#ifndef lint
typedef         sb1  b1;
#else
#define         b1 sb1
#endif
#define  B1MAXVAL  SB1MAXVAL
#define  B1MINVAL  SB1MINVAL

#ifndef lint
typedef         sb2      b2;
#else
#define         b2 sb2
#endif
#define  B2MAXVAL  SB2MAXVAL
#define  B2MINVAL  SB2MINVAL

#ifndef lint
typedef         sb4    b4;
#else 
#define         b4 sb4
#endif
# define  B4MAXVAL  SB4MAXVAL
# define  B4MINVAL  SB4MINVAL


#if !defined(LUSEMFC)
# ifdef lint
#  define text unsigned char
# else
   typedef oratext text;
# endif
#endif

#ifdef lint
# define OraText unsigned char
#else
  typedef oratext OraText;
#endif

#ifndef lint
typedef          int eword;
typedef unsigned int uword;
typedef   signed int sword;
#else
#define eword int
#define uword unsigned int
#define sword signed int
#endif

#define  EWORDMAXVAL  ((eword) INT_MAX)
#define  EWORDMINVAL  ((eword)       0)
#define  UWORDMAXVAL  ((uword)UINT_MAX)
#define  UWORDMINVAL  ((uword)       0)
#define  SWORDMAXVAL  ((sword) INT_MAX)
#define  SWORDMINVAL  ((sword) INT_MIN)
#define  MINEWORDMAXVAL  ((eword)  2147483647)
#define  MAXEWORDMINVAL  ((eword)      0)
#define  MINUWORDMAXVAL  ((uword)  4294967295)
#define  MAXUWORDMINVAL  ((uword)           0)
#define  MINSWORDMAXVAL  ((sword)  2147483647)
#define  MAXSWORDMINVAL  ((sword) -2147483647)

#ifdef _WIN64

#ifndef lint
typedef unsigned _int64 ubig_ora;
typedef   signed _int64 sbig_ora;
#else
#define ubig_ora unsigned _int64
#define sbig_ora signed _int64
#endif

#define UBIG_ORAMAXVAL ((ubig_ora)_UI64_MAX)
#define UBIG_ORAMINVAL ((ubig_ora)        0)
#define SBIG_ORAMAXVAL ((sbig_ora) _I64_MAX)
#define SBIG_ORAMINVAL ((sbig_ora) _I64_MIN)
#define MINUBIG_ORAMAXVAL ((ubig_ora) 4294967295)
#define MAXUBIG_ORAMINVAL ((ubig_ora)          0)
#define MINSBIG_ORAMAXVAL ((sbig_ora) 2147483647)
#define MAXSBIG_ORAMINVAL ((sbig_ora)-2147483647)

#else

#ifndef lint
typedef unsigned long  ubig_ora;
typedef   signed long  sbig_ora;
#else
#define ubig_ora unsigned long
#define sbig_ora signed long
#endif

#define UBIG_ORAMAXVAL ((ubig_ora)ULONG_MAX)
#define UBIG_ORAMINVAL ((ubig_ora)        0)
#define SBIG_ORAMAXVAL ((sbig_ora) LONG_MAX)
#define SBIG_ORAMINVAL ((sbig_ora) LONG_MIN)
#define MINUBIG_ORAMAXVAL ((ubig_ora) 4294967295)
#define MAXUBIG_ORAMINVAL ((ubig_ora)          0)
#define MINSBIG_ORAMAXVAL ((sbig_ora) 2147483647)
#define MAXSBIG_ORAMINVAL ((sbig_ora)-2147483647)

#endif                                                             /* _WIN64 */

/* --- Signed/Unsigned eight-byte scalar (orasb8/oraub8) --- */

#define ORAXB8_DEFINED
#ifndef lint
#ifndef __GNUC__
#ifdef __BORLANDC__
  typedef unsigned __int64 oraub8;
  typedef signed __int64 orasb8;
#else
  typedef unsigned _int64 oraub8;
  typedef signed _int64 orasb8;
#endif /* __BORLANDC__ */
#else
  typedef unsigned long long oraub8;
  typedef signed long long orasb8;
#endif /*__GNUC__*/
  typedef oraub8 ub8;
  typedef orasb8 sb8;
#else
#ifndef __GNUC__
#ifdef __BORLANDC__
#define oraub8 unsigned __int64 
#define orasb8 signed __int64 
#else
#define oraub8 unsigned _int64 
#define orasb8 signed _int64 
#endif 
#else
#define oraub8 unsigned long long
#define orasb8 signed long long
#endif
# define ub8 oraub8
# define sb8 orasb8

#endif /* !lint */

#define UBIGORABITS      (UB1BITS * sizeof(ubig_ora))

#undef CONST
#define CONST const

#define dvoid void

typedef void (*lgenfp_t)( void );

#ifndef ORASYS_TYPES
# include <sys/types.h>
# define ORASYS_TYPES
#endif

#ifndef boolean
# define boolean int
#endif

#ifdef sparc
# define SIZE_TMAXVAL SB4MAXVAL
#else
# define SIZE_TMAXVAL UB4MAXVAL
#endif

#define MINSIZE_TMAXVAL (size_t)4294967295

/*---------------------------------------------------------------------------*/
#define OCI_NUMBER_UNSIGNED 0                        /* Unsigned type -- ubX */
#define OCI_NUMBER_SIGNED   2                          /* Signed type -- sbX */
/*--------------------------- User Callback Constants -----------------------*/

#if !defined(MOTIF) && !defined(LISPL)  && !defined(__cplusplus) && !defined(LUSEMFC)
typedef  oratext *string;
#endif

#ifndef lint
typedef unsigned short  utext;
#else
#define utext  unsigned short
#endif
#define SQLT_CHR                        1               /* (ORANET TYPE) character string */
#define SQLT_NUM                        2               /* (ORANET TYPE) oracle numeric */
#define SQLT_INT                        3               /* (ORANET TYPE) integer */
#define SQLT_FLT                        4               /* (ORANET TYPE) Floating point number */
#define SQLT_STR                        5               /* zero terminated string */
#define SQLT_VNU                        6               /* NUM with preceding length byte */
#define SQLT_PDN                        7               /* (ORANET TYPE) Packed Decimal Numeric */
#define SQLT_LNG                        8               /* long */
#define SQLT_VCS                        9               /* Variable character string */
#define SQLT_NON                        10              /* Null/empty PCC Descriptor entry */
#define SQLT_RID                        11              /* rowid */
#define SQLT_DAT                        12              /* date in oracle format */
#define SQLT_VBI                        15              /* binary in VCS format */
#define SQLT_BFLOAT                     21              /* Native Binary float*/
#define SQLT_BDOUBLE                    22              /* NAtive binary double */
#define SQLT_BIN                        23              /* binary data(DTYBIN) */
#define SQLT_LBI                        24              /* long binary */
#define SQLT_UIN                        68              /* unsigned integer */
#define SQLT_SLS                        91              /* Display sign leading separate */
#define SQLT_LVC                        94              /* Longer longs (char) */
#define SQLT_LVB                        95              /* Longer long binary */ 
#define SQLT_AFC                        96              /* Ansi fixed char */
#define SQLT_AVC                        97              /* Ansi Var char */
#define SQLT_IBFLOAT                    100             /* binary float canonical */
#define SQLT_IBDOUBLE                   101             /* binary double canonical */
#define SQLT_CUR                        102             /* cursor  type */
#define SQLT_RDD                        104             /* rowid descriptor */
#define SQLT_LAB                        105             /* label type */
#define SQLT_OSL                        106             /* oslabel type */

#define SQLT_NTY                        108             /* named object type */
#define SQLT_REF                        110             /* ref type */
#define SQLT_CLOB                       112             /* character lob */
#define SQLT_BLOB                       113             /* binary lob */
#define SQLT_BFILEE                     114             /* binary file lob */
#define SQLT_CFILEE                     115             /* character file lob */
#define SQLT_RSET                       116             /* result set type */
#define SQLT_NCO                        122             /* named collection type (varray or nested table) */
#define SQLT_VST                        155             /* OCIString type */
#define SQLT_ODT                        156             /* OCIDate type */

/* datetimes and intervals */
#define SQLT_DATE                       184             /* ANSI Date */
#define SQLT_TIME                       185             /* TIME */
#define SQLT_TIME_TZ                    186             /* TIME WITH TIME ZONE */
#define SQLT_TIMESTAMP                  187             /* TIMESTAMP */
#define SQLT_TIMESTAMP_TZ               188             /* TIMESTAMP WITH TIME ZONE */
#define SQLT_INTERVAL_YM                189             /* INTERVAL YEAR TO MONTH */
#define SQLT_INTERVAL_DS                190             /* INTERVAL DAY TO SECOND */
#define SQLT_TIMESTAMP_LTZ              232             /* TIMESTAMP WITH LOCAL TZ */

#define SQLT_PNTY                       241             /* pl/sql representation of named types */

/* cxcheng: this has been added for backward compatibility -
   it needs to be here because ocidfn.h can get included ahead of sqldef.h */
#define SQLT_FILE                       SQLT_BFILEE     /* binary file lob */
#define SQLT_CFILE                      SQLT_CFILEE
#define SQLT_BFILE                      SQLT_BFILEE
 
/* CHAR/NCHAR/VARCHAR2/NVARCHAR2/CLOB/NCLOB char set "form" information */
#define SQLCS_IMPLICIT                  1               /* for CHAR, VARCHAR2, CLOB w/o a specified set */
#define SQLCS_NCHAR                     2               /* for NCHAR, NCHAR VARYING, NCLOB */
#define SQLCS_EXPLICIT                  3               /* for CHAR, etc, with "CHARACTER SET ..." syntax */
#define SQLCS_FLEXIBLE                  4               /* for PL/SQL "flexible" parameters */
#define SQLCS_LIT_NULL                  5               /* for typecheck of NULL and empty_clob() lits */

/*--------------------------------------------------------------------------- 
 Short names provided for platforms which do not allow extended symbolic names 
  ---------------------------------------------------------------------------*/

#ifdef SLSHORTNAME
/* Translation of the long function/type names to short names for IBM only */
/* maybe lint will use this too */
#define OCISessionEnd              ocitac
#define OCIResultSetToStmt         ocirs2sh
#define OCISessionBegin            ociauth
#define OCIServerAttach            ociatch
#define OCIDescriptorAlloc         ocigdesc
#define OCIServerDetach            ocidtch
#define OCIDescriptorFree          ocifdesc
#define OCIServerVersion           ocivers
#define OCIDescribeAny             ocidsca
#define OCIBindDynamic             ocibda
#define OCIBindByName              ocibdn
#define OCIBindByPos               ocibdp
#define OCIErrorGet                ocigdr
#define OCIBindArrayOfStruct       ocibsa
#define OCIEnvInit                 ociinit
#define OCIBindObject              ocibndt
#define OCIHandleAlloc             ocighndl
#define OCIHandleFree              ocifhndl
#define OCIRowidToChar             ociri2c
#ifdef NEVER
#define OCIStmtBindByPos           ocibndp
#define OCIStmtBindByName          ocibndn
#endif
#define OCIAttrGet                 ocigattr
#define OCIDefineByPos             ocidfne
#define OCIAttrSet                 ocisattr
#define OCIDefineDynamic           ociddf
#define OCILdaToSvcCtx             ocild2sv
#define OCIDefineArrayOfStruct     ocidarr
#define OCIInitialize              ocipi
#define OCIDefineObject            ocidndt
#define OCIStmtExecute             ociexec
#define OCILobAppend               ocilfap
#define OCILobOpenFile             ocifopn
#define OCILobCloseFile            ocifcls
#define OCILobLocator              ocilobd
#define OCILobCopy                 ocilfcp
#define OCILobFileCreate           ocifcrt
#define OCILobFileDelete           ocifdel
#define OCILobGetLength            ocilfln
#define OCILobWrite                ocilfwr
#define OCILobRead                 ocilfrd
#define OCILobErase                ocilfer
#define OCILobTrim                 ocilftr

#define OCIStmtFetch               ocifch
#define OCIStmtGetBindInfo         ocigbp
#define OCIStmtGetPieceInfo        ocigpi
#define OCIStmtPrepare             ocireq
#define OCIStmtSetPieceInfo        ocispi
#define OCISvcCtxToLda             ocisv2ld
#define OCITransCommit             ocitxcm
#define OCITransDetach             ocitxdt
#define OCITransForget             ocitxfgt
#define OCITransPrepare            ocitxpre
#define OCITransRollback           ocitxrl
#define OCIPasswordChange          ocicpw
#define OCITransStart              ocitxst
#define OCITransMultiPrepare       ocitxmp

#define OCIBreak                   ocibreak
#define OCIParamGet                ocigparm
#define OCIParamSet                ocisparm

#define OCISecurityOpenWallet           ocizwOpenWallet
#define OCISecurityCloseWallet          ocizwCloseWallet
#define OCISecurityCreateWallet         ocizwCreateWallet
#define OCISecurityDestroyWallet        ocizwDestroyWallet
#define OCISecurityStorePersona         ocizeStorePersona
#define OCISecurityOpenPersona          ocizeOpenPersona
#define OCISecurityClosePersona         ocizeClosePersona
#define OCISecurityRemovePersona        ocizeRemovePersona
#define OCISecurityCreatePersona        ocizeCreatePersona
#define OCISecuritySetProtection        ocizeSetProtection
#define OCISecurityGetProtection        ocizeGetProtection
#define OCISecurityRemoveIdentity       ociziRemoveIdentity
#define OCISecurityCreateIdentity       ociziCreateIdentity
#define OCISecurityAbortIdentity        ociziAbortIdentity
#define OCISecurityFreeIdentity         ociziFreeIdentity
#define OCISecurityStoreTrustedIdentity ociziStoreTrustedIdentity
#define OCISecuritySign                 ocizSign
#define OCISecuritySignExpansion        ocizxSignExpansion
#define OCISecurityVerify               ocizVerify
#define OCISecurityValidate             ocizValidate
#define OCISecuritySignDetached         ocizsd_SignDetached
#define OCISecuritySignDetExpansion     ocizxsd_SignDetachedExpansion
#define OCISecurityVerifyDetached       ocizved_VerifyDetached
#define OCISecurity_PKEncrypt           ocizkec_PKEncrypt
#define OCISecurityPKEncryptExpansion   ocizxkec_PKEncryptExpansion
#define OCISecurityPKDecrypt            ocizkdc_PKDecrypt
#define OCISecurityEncrypt              ocizEncrypt
#define OCISecurityEncryptExpansion     ocizxEncryptExpansion
#define OCISecurityDecrypt              ocizDecrypt
#define OCISecurityEnvelope             ocizEnvelope
#define OCISecurityDeEnvelope           ocizDeEnvelope
#define OCISecurityKeyedHash            ocizKeyedHash
#define OCISecurityKeyedHashExpansion   ocizxKeyedHashExpansion
#define OCISecurityHash                 ocizHash
#define OCISecurityHashExpansion        ocizxHashExpansion
#define OCISecuritySeedRandom           ocizSeedRandom
#define OCISecurityRandomBytes          ocizrb_RandomBytes
#define OCISecurityRandomNumber         ocizrn_RandomNumber
#define OCISecurityInitBlock            ocizibInitBlock
#define OCISecurityReuseBlock           ocizrbReuseBlock
#define OCISecurityPurgeBlock           ocizpbPurgeBlock
#define OCISecuritySetBlock             ocizsbSetBlock
#define OCISecurityGetIdentity          ocizgi_GetIdentity

#define OCIExtractInit             ocixeini
#define OCIExtractTerm             ocixetrm
#define OCIExtractReset            ocixerst
#define OCIExtractSetNumKeys       ocixesnk
#define OCIExtractSetKey           ocixesk
#define OCIExtractFromFile         ocixeff
#define OCIExtractFromStr          ocixefs
#define OCIExtractToInt            ocixeti
#define OCIExtractToBool           ocixetb
#define OCIExtractToStr            ocixets
#define OCIExtractToOCINum         ocixeton
#define OCIExtractToList           ocixetl
#define OCIExtractFromList         ocixefl

#define OCIDateTimeGetTime         ocidt01_GetTime
#define OCIDateTimeGetDate         ocidt02_GetDate
#define OCIDateTimeGetTimeZoneOffset     ocidt03_GetTZ
#define OCIDateTimeSetTime         ocidt04_SetTime
#define OCIDateTimeSetDate         ocidt05_SetDate
#define OCIDateTimeSysTimeStamp    ocidt07_SysTS
#define OCIDateTimeAssign          ocidt08_Assign
#define OCIDateTimeToText          ocidt09_ToText
#define OCIDateTimeFromText        ocidt10_FromText
#define OCIDateTimeCompare         ocidt11_Compare
#define OCIDateTimeCheck           ocidt12_Check
#define OCIDateTimeConvert         ocidt13_Convert
#define OCIDateTimeSubtract        ocidt14_Subtract
#define OCIDateTimeIntervalAdd     ocidt15_IntervalAdd
#define OCIDateTimeIntervalSub     ocidt16_IntervalSub
#define OCIDateTimeGetTimeZoneName ocidt17_Gettzname
#define OCIDateTimeToArray         ocidt18_ToArray
#define OCIDateTimeFromArray       ocidt19_FromArray
#define OCIDateTimeSetTimeZoneOffset     ocidt20_SetTZ
#define OCIDateTimeConstruct       ocidt21_Cstrct

#define OCIIntervalSubtract        ociint01_Subtract
#define OCIIntervalAdd             ociint02_Add
#define OCIIntervalMultiply        ociint03_Multiply
#define OCIIntervalDivide          ociint04_Divide
#define OCIIntervalCompare         ociint05_Compare
#define OCIIntervalFromText        ociint06_FromText
#define OCIIntervalToText          ociint07_ToText
#define OCIIntervalToNumber        ociint08_ToNumber
#define OCIIntervalCheck           ociint09_Check
#define OCIIntervalAssign          ociint10_Assign
#define OCIIntervalGetYearMonth    ociint11_GetYearMonth
#define OCIIntervalSetYearMonth    ociint12_SetYearMonth
#define OCIIntervalGetDaySecond    ociint13_GetDaySecond
#define OCIIntervalSetDaySecond    ociint14_SetDaySecond
#define OCIIntervalFromNumber      ociint15_FromNumber
#define OCIIntervalFromTZ          ociint16_FromTZ

#define OCIFormatInit              ocixs01_Init
#define OCIFormatString            ocixs02_Format
#define OCIFormatTerm              ocixs03_Term
#define OCIFormatTUb1              ocixs04_TUb1
#define OCIFormatTUb2              ocixs05_TUb2
#define OCIFormatTUb4              ocixs06_TUb4
#define OCIFormatTUword            ocixs07_TUword
#define OCIFormatTUbig_ora         ocixs08_TUbig_ora
#define OCIFormatTSb1              ocixs09_TSb1
#define OCIFormatTSb2              ocixs10_TSb2
#define OCIFormatTSb4              ocixs11_TSb4
#define OCIFormatTSword            ocixs12_TSword
#define OCIFormatTSbig_ora         ocixs13_TSbig_ora
#define OCIFormatTEb1              ocixs14_TEb1
#define OCIFormatTEb2              ocixs15_TEb2
#define OCIFormatTEb4              ocixs16_TEb4
#define OCIFormatTEword            ocixs17_TEword
#define OCIFormatTChar             ocixs18_TChar
#define OCIFormatTText             ocixs19_TText
#define OCIFormatTDouble           ocixs20_TDouble
#define OCIFormatTDvoid            ocixs21_TDvoid
#define OCIFormatTEnd              ocixs22_TEnd

#define OCIFileInit                ocifinit
#define OCIFileTerm                ocifterm
#define OCIFileOpen                ocifopen
#define OCIFileClose               ocifclose
#define OCIFileRead                ocifread
#define OCIFileWrite               ocifwrite
#define OCIFileSeek                ocifseek
#define OCIFileExists              ocifexists
#define OCIFileGetLength           ocifglen
#define OCIFileFlush               ocifflush


/* OCIThread short name */
#define OCIThreadProcessInit       ocitt01_ProcessInit
#define OCIThreadInit              ocitt02_Init
#define OCIThreadTerm              ocitt03_Term
#define OCIThreadIsMulti           ocitt04_IsMulti
#define OCIThreadMutexInit         ocitt05_MutexInit
#define OCIThreadMutexDestroy      ocitt06_MutexDestroy
#define OCIThreadMutexAcquire      ocitt07_MutexAcquire
#define OCIThreadMutexRelease      ocitt08_MutexRelease
#define OCIThreadKeyInit           ocitt09_KeyInit
#define OCIThreadKeyDestroy        ocitt10_KeyDestroy
#define OCIThreadKeyGet            ocitt11_KeyGet
#define OCIThreadKeySet            ocitt12_KeySet
#define OCIThreadIdInit            ocitt13_IdInit
#define OCIThreadIdDestroy         ocitt14_IdDestroy
#define OCIThreadIdSet             ocitt15_IdSet
#define OCIThreadIdSetNull         ocitt16_IdSetNull
#define OCIThreadIdGet             ocitt17_IdGet
#define OCIThreadIdSame            ocitt18_IdSame
#define OCIThreadIdNull            ocitt19_IdNull
#define OCIThreadHndInit           ocitt20_HndInit
#define OCIThreadHndDestroy        ocitt21_HndDestroy
#define OCIThreadCreate            ocitt22_Create
#define OCIThreadJoin              ocitt23_Join
#define OCIThreadClose             ocitt24_Close
#define OCIThreadHandleGet         ocitt25_HandleGet

/* Translation between the old and new datatypes */

#define OCISession                 ociusrh
#define OCIBind                    ocibndh
#define OCIDescribe                ocidsch
#define OCIDefine                  ocidfnh
#define OCIEnv                     ocienvh
#define OCIError                   ocierrh

#define OCICPool                   ocicpool

#define OCISPool                   ocispool
#define OCIAuthInfo                ociauthinfo


#define OCILob                     ocilobd
#define OCILobLength               ocillen
#define OCILobMode                 ocilmo
#define OCILobOffset               ociloff

#define OCILobLocator              ocilobd
#define OCIBlobLocator             ociblobl
#define OCIClobLocator             ociclobl
#define OCIBFileLocator            ocibfilel

#define OCIParam                   ocipard
#define OCIResult                  ocirstd
#define OCISnapshot                ocisnad
#define OCIServer                  ocisrvh
#define OCIStmt                    ocistmh
#define OCISvcCtx                  ocisvch
#define OCITrans                   ocitxnh
#define OCICallbackInBind          ocibicfp
#define OCICallbackOutBind         ocibocfp
#define OCICallbackDefine          ocidcfp
#define OCICallbackLobRead         ocilrfp
#define OCICallbackLobWrite        ocilwfp
#define OCISecurity                ociossh
#define OCIComplexObject           ocicorh
#define OCIComplexObjectComp       ocicord
#define OCIRowid                   ociridd

#define OCIAQDeq                   ociaqdeq
#define OCIAQEnq                   ociaqenq
#define OCIConnectionPoolCreate    ociconpc
#define OCIConnectionPoolDestroy   ociconpd
#define OCIEnvCreate               ocienvct
#define OCILobAssign               ociloass
#define OCIlobLocatorAssign        ocillass
#define OCILobCharSetForm          ocilocfm
#define OCILobCharSetId            ocilocid
#define OCILobDisableBuffering     ocilodbf
#define OCILobEnableBuffering      ociloebf
#define OCILobFileClose            ocilofcl
#define OCILobFileCloseAll         ocilofca
#define OCILobFileExists           ocilofex
#define OCILobFileGetName          ocilofgn
#define OCILobFileIsOpen           ocifiopn
#define OCILobFileOpen             ocilofop
#define OCILobFileSetName          ocilofsn
#define OCILobFlushBuffer          ocilofbf
#define OCILobIsEqual              ociloieq
#define OCILobLoadFromFile         ocilolff
#define OCILobLocatorIsInit        ocilolii
#define OCILobLocatorAssign        ocilolas
#define OCILogon                   ocilogon
#define OCILogon2                  ocilgon2
#define OCILogoff                  ocilgoff
#endif /* ifdef SLSHORTNAME */

/*--------------------------------------------------------------------------- 
                     PUBLIC TYPES AND CONSTANTS 
  ---------------------------------------------------------------------------*/

/*-----------------------------Handle Types----------------------------------*/
/* handle types range from 1 - 49 */
#define OCI_HTYPE_FIRST             1                      /* start value of handle type */
#define     DCI_HTYPE_FIRST             OCI_HTYPE_FIRST
#define OCI_HTYPE_ENV               1                      /* environment handle */
#define     DCI_HTYPE_ENV               OCI_HTYPE_ENV
#define OCI_HTYPE_ERROR             2                      /* error handle */
#define     DCI_HTYPE_ERROR             OCI_HTYPE_ERROR
#define OCI_HTYPE_SVCCTX            3                      /* service handle */
#define     DCI_HTYPE_SVCCTX            OCI_HTYPE_SVCCTX
#define OCI_HTYPE_STMT              4                      /* statement handle */
#define     DCI_HTYPE_STMT              OCI_HTYPE_STMT
#define OCI_HTYPE_BIND              5                      /* bind handle */
#define     DCI_HTYPE_BIND              OCI_HTYPE_BIND
#define OCI_HTYPE_DEFINE            6                      /* define handle */
#define     DCI_HTYPE_DEFINE            OCI_HTYPE_DEFINE
#define OCI_HTYPE_DESCRIBE          7                      /* describe handle */
#define     DCI_HTYPE_DESCRIBE          OCI_HTYPE_DESCRIBE
#define OCI_HTYPE_SERVER            8                      /* server handle */
#define     DCI_HTYPE_SERVER            OCI_HTYPE_SERVER
#define OCI_HTYPE_SESSION           9                      /* authentication handle */
#define     DCI_HTYPE_SESSION           OCI_HTYPE_SESSION
#define OCI_HTYPE_AUTHINFO          OCI_HTYPE_SESSION       /* SessionGet auth handle */
#define     DCI_HTYPE_AUTHINFO          OCI_HTYPE_AUTHINFO
#define OCI_HTYPE_TRANS             10                      /* transaction handle */
#define     DCI_HTYPE_TRANS             OCI_HTYPE_TRANS
#define OCI_HTYPE_COMPLEXOBJECT     11                      /* complex object retrieval handle */
#define     DCI_HTYPE_COMPLEXOBJECT     OCI_HTYPE_COMPLEXOBJECT
#define OCI_HTYPE_SECURITY          12                      /* security handle */
#define     DCI_HTYPE_SECURITY          OCI_HTYPE_SECURITY
#define OCI_HTYPE_SUBSCRIPTION      13                      /* subscription handle */
#define     DCI_HTYPE_SUBSCRIPTION      OCI_HTYPE_SUBSCRIPTION
#define OCI_HTYPE_DIRPATH_CTX       14                      /* direct path context */
#define     DCI_HTYPE_DIRPATH_CTX       OCI_HTYPE_DIRPATH_CTX
#define OCI_HTYPE_DIRPATH_COLUMN_ARRAY  15                  /* direct path column array */
#define     DCI_HTYPE_DIRPATH_COLUMN_ARRAY  OCI_HTYPE_DIRPATH_COLUMN_ARRAY
#define OCI_HTYPE_DIRPATH_STREAM    16                      /* direct path stream */
#define     DCI_HTYPE_DIRPATH_STREAM    OCI_HTYPE_DIRPATH_STREAM
#define OCI_HTYPE_PROC              17                      /* process handle */
#define     DCI_HTYPE_PROC              OCI_HTYPE_PROC
#define OCI_HTYPE_DIRPATH_FN_CTX    18                      /* direct path function context */
#define     DCI_HTYPE_DIRPATH_FN_CTX    OCI_HTYPE_DIRPATH_FN_CTX
#define OCI_HTYPE_DIRPATH_FN_COL_ARRAY  19                  /* dp object column array */
#define     DCI_HTYPE_DIRPATH_FN_COL_ARRAY  OCI_HTYPE_DIRPATH_FN_COL_ARRAY
#define OCI_HTYPE_XADSESSION        20                      /* access driver session */
#define     DCI_HTYPE_XADSESSION        OCI_HTYPE_XADSESSION
#define OCI_HTYPE_XADTABLE          21                      /* access driver table */
#define     DCI_HTYPE_XADTABLE          OCI_HTYPE_XADTABLE
#define OCI_HTYPE_XADFIELD          22                      /* access driver field */
#define     DCI_HTYPE_XADFIELD          OCI_HTYPE_XADFIELD
#define OCI_HTYPE_XADGRANULE        23                      /* access driver granule */
#define     DCI_HTYPE_XADGRANULE        OCI_HTYPE_XADGRANULE
#define OCI_HTYPE_XADRECORD         24                      /* access driver record */
#define     DCI_HTYPE_XADRECORD         OCI_HTYPE_XADRECORD
#define OCI_HTYPE_XADIO             25                      /* access driver I/O */
#define     DCI_HTYPE_XADIO             OCI_HTYPE_XADIO
#define OCI_HTYPE_CPOOL             26                      /* connection pool handle */
#define     DCI_HTYPE_CPOOL             OCI_HTYPE_CPOOL
#define OCI_HTYPE_SPOOL             27                      /* session pool handle */
#define     DCI_HTYPE_SPOOL             OCI_HTYPE_SPOOL
#define OCI_HTYPE_ADMIN             28                      /*administration handle*/
#define     DCI_HTYPE_ADMIN             OCI_HTYPE_ADMIN

#define OCI_HTYPE_LAST              28                      /* last value of a handle type */
#define     DCI_HTYPE_LAST              OCI_HTYPE_LAST

/*---------------------------------------------------------------------------*/


/*-------------------------Descriptor Types----------------------------------*/
/* descriptor values range from 50 - 255 */
#define OCI_DTYPE_FIRST             50                      /* start value of descriptor type */
#define     DCI_DTYPE_FIRST             OCI_DTYPE_FIRST
#define OCI_DTYPE_LOB               50                      /* lob  locator */
#define     DCI_DTYPE_LOB               OCI_DTYPE_LOB
#define OCI_DTYPE_SNAP              51                      /* snapshot descriptor */
#define     DCI_DTYPE_SNAP              OCI_DTYPE_SNAP
#define OCI_DTYPE_RSET              52                      /* result set descriptor */
#define     DCI_DTYPE_RSET              OCI_DTYPE_RSET
#define OCI_DTYPE_PARAM             53                      /* a parameter descriptor obtained from ocigparm */
#define     DCI_DTYPE_PARAM             OCI_DTYPE_PARAM
#define OCI_DTYPE_ROWID             54                      /* rowid descriptor */
#define     DCI_DTYPE_ROWID             OCI_DTYPE_ROWID
#define OCI_DTYPE_COMPLEXOBJECTCOMP 55                      /* complex object retrieval descriptor */
#define     DCI_DTYPE_COMPLEXOBJECTCOMP OCI_DTYPE_COMPLEXOBJECTCOMP
#define OCI_DTYPE_FILE              56                      /* File Lob locator */
#define     DCI_DTYPE_FILE              OCI_DTYPE_FILE
#define OCI_DTYPE_AQENQ_OPTIONS     57                      /* enqueue options */
#define     DCI_DTYPE_AQENQ_OPTIONS     OCI_DTYPE_AQENQ_OPTIONS
#define OCI_DTYPE_AQDEQ_OPTIONS     58                      /* dequeue options */
#define     DCI_DTYPE_AQDEQ_OPTIONS     OCI_DTYPE_AQDEQ_OPTIONS
#define OCI_DTYPE_AQMSG_PROPERTIES  59                      /* message properties */
#define     DCI_DTYPE_AQMSG_PROPERTIES  OCI_DTYPE_AQMSG_PROPERTIES
#define OCI_DTYPE_AQAGENT           60                      /* aq agent */
#define     DCI_DTYPE_AQAGENT           OCI_DTYPE_AQAGENT
#define OCI_DTYPE_LOCATOR           61                      /* LOB locator */
#define     DCI_DTYPE_LOCATOR           OCI_DTYPE_LOCATOR
#define OCI_DTYPE_INTERVAL_YM       62                      /* Interval year month */
#define     DCI_DTYPE_INTERVAL_YM       OCI_DTYPE_INTERVAL_YM
#define OCI_DTYPE_INTERVAL_DS       63                      /* Interval day second */
#define     DCI_DTYPE_INTERVAL_DS       OCI_DTYPE_INTERVAL_DS
#define OCI_DTYPE_AQNFY_DESCRIPTOR  64                      /* AQ notify descriptor */
#define     DCI_DTYPE_AQNFY_DESCRIPTOR  OCI_DTYPE_AQNFY_DESCRIPTOR
#define OCI_DTYPE_DATE              65                      /* Date */
#define     DCI_DTYPE_DATE              OCI_DTYPE_DATE
#define OCI_DTYPE_TIME              66                      /* Time */
#define     DCI_DTYPE_TIME              OCI_DTYPE_TIME
#define OCI_DTYPE_TIME_TZ           67                      /* Time with timezone */
#define     DCI_DTYPE_TIME_TZ           OCI_DTYPE_TIME_TZ
#define OCI_DTYPE_TIMESTAMP         68                      /* Timestamp */
#define     DCI_DTYPE_TIMESTAMP         OCI_DTYPE_TIMESTAMP
#define OCI_DTYPE_TIMESTAMP_TZ      69                      /* Timestamp with timezone */
#define     DCI_DTYPE_TIMESTAMP_TZ      OCI_DTYPE_TIMESTAMP_TZ
#define OCI_DTYPE_TIMESTAMP_LTZ     70                      /* Timestamp with local tz */
#define     DCI_DTYPE_TIMESTAMP_LTZ     OCI_DTYPE_TIMESTAMP_LTZ
#define OCI_DTYPE_UCB               71                      /* user callback descriptor */
#define     DCI_DTYPE_UCB               OCI_DTYPE_UCB
#define OCI_DTYPE_SRVDN             72                      /* server DN list descriptor */
#define     DCI_DTYPE_SRVDN             OCI_DTYPE_SRVDN
#define OCI_DTYPE_SIGNATURE         73                      /* signature */
#define     DCI_DTYPE_SIGNATURE         OCI_DTYPE_SIGNATURE
#define OCI_DTYPE_RESERVED_1        74                      /* reserved for internal use */
#define     DCI_DTYPE_RESERVED_1        OCI_DTYPE_RESERVED_1
#define OCI_DTYPE_LAST              74                      /* last value of a descriptor type */
#define     DCI_DTYPE_LAST              OCI_DTYPE_LAST

/*---------------------------------------------------------------------------*/

/*--------------------------------LOB types ---------------------------------*/
#define OCI_TEMP_BLOB               1                       /* LOB type - BLOB ------------------ */
#define     DCI_TEMP_BLOB               OCI_TEMP_BLOB
#define OCI_TEMP_CLOB               2                       /* LOB type - CLOB ------------------ */
#define     DCI_TEMP_CLOB               OCI_TEMP_CLOB
/*---------------------------------------------------------------------------*/

/*-------------------------Object Ptr Types----------------------------------*/
#define OCI_OTYPE_NAME              1                       /* object name */
#define     DCI_OTYPE_NAME              OCI_OTYPE_NAME
#define OCI_OTYPE_REF               2                       /* REF to TDO */
#define     DCI_OTYPE_REF               OCI_OTYPE_REF
#define OCI_OTYPE_PTR               3                       /* PTR to TDO */
#define     DCI_OTYPE_PTR               OCI_OTYPE_PTR
/*---------------------------------------------------------------------------*/

/*=============================Attribute Types===============================*/
/* 
   Note: All attributes are global.  New attibutes should be added to the end
   of the list. Before you add an attribute see if an existing one can be 
   used for your handle. 

   If you see any holes please use the holes first. 
 
*/
/*===========================================================================*/


#define OCI_ATTR_FNCODE                 1                           /* the OCI function code */
#define     DCI_ATTR_FNCODE                 OCI_ATTR_FNCODE
#define OCI_ATTR_OBJECT                 2                           /* is the environment initialized in object mode */
#define     DCI_ATTR_OBJECT                 OCI_ATTR_OBJECT
#define OCI_ATTR_NONBLOCKING_MODE       3                           /* non blocking mode */
#define     DCI_ATTR_NONBLOCKING_MODE       OCI_ATTR_NONBLOCKING_MODE
#define OCI_ATTR_SQLCODE                4                           /* the SQL verb */
#define     DCI_ATTR_SQLCODE                OCI_ATTR_SQLCODE
#define OCI_ATTR_ENV                    5                           /* the environment handle */
#define     DCI_ATTR_ENV                    OCI_ATTR_ENV
#define OCI_ATTR_SERVER                 6                           /* the server handle */
#define     DCI_ATTR_SERVER                 OCI_ATTR_SERVER
#define OCI_ATTR_SESSION                7                           /* the user session handle */
#define     DCI_ATTR_SESSION                OCI_ATTR_SESSION
#define OCI_ATTR_TRANS                  8                           /* the transaction handle */
#define     DCI_ATTR_TRANS                  OCI_ATTR_TRANS
#define OCI_ATTR_ROW_COUNT              9                           /* the rows processed so far */
#define     DCI_ATTR_ROW_COUNT              OCI_ATTR_ROW_COUNT
#define OCI_ATTR_SQLFNCODE              10                          /* the SQL verb of the statement */
#define     DCI_ATTR_SQLFNCODE              OCI_ATTR_SQLFNCODE
#define OCI_ATTR_PREFETCH_ROWS          11                          /* sets the number of rows to prefetch */
#define     DCI_ATTR_PREFETCH_ROWS          OCI_ATTR_PREFETCH_ROWS
#define OCI_ATTR_NESTED_PREFETCH_ROWS   12                          /* the prefetch rows of nested table*/
#define     DCI_ATTR_NESTED_PREFETCH_ROWS   OCI_ATTR_NESTED_PREFETCH_ROWS
#define OCI_ATTR_PREFETCH_MEMORY        13                          /* memory limit for rows fetched */
#define     DCI_ATTR_PREFETCH_MEMORY        OCI_ATTR_PREFETCH_MEMORY
#define OCI_ATTR_NESTED_PREFETCH_MEMORY 14                          /* memory limit for nested rows */
#define     DCI_ATTR_NESTED_PREFETCH_MEMORY OCI_ATTR_NESTED_PREFETCH_MEMORY
#define OCI_ATTR_CHAR_COUNT             15                          /* this specifies the bind and define size in characters */
#define     DCI_ATTR_CHAR_COUNT             OCI_ATTR_CHAR_COUNT
#define OCI_ATTR_PDSCL                  16                          /* packed decimal scale */
#define     DCI_ATTR_PDSCL                  OCI_ATTR_PDSCL
#define OCI_ATTR_FSPRECISION            OCI_ATTR_PDSCL              /* fs prec for datetime data types */
#define     DCI_ATTR_FSPRECISION            OCI_ATTR_FSPRECISION
#define OCI_ATTR_PDPRC                  17                          /* packed decimal format */
#define     DCI_ATTR_PDPRC                  OCI_ATTR_PDPRC
#define OCI_ATTR_LFPRECISION            OCI_ATTR_PDPRC              /* fs prec for datetime data types */
#define     DCI_ATTR_LFPRECISION            OCI_ATTR_LFPRECISION
#define OCI_ATTR_PARAM_COUNT            18                          /* number of column in the select list */
#define     DCI_ATTR_PARAM_COUNT            OCI_ATTR_PARAM_COUNT
#define OCI_ATTR_ROWID                  19                          /* the rowid */
#define     DCI_ATTR_ROWID                  OCI_ATTR_ROWID
#define OCI_ATTR_CHARSET                20                          /* the character set value */
#define     DCI_ATTR_CHARSET                OCI_ATTR_CHARSET
#define OCI_ATTR_NCHAR                  21                          /* NCHAR type */
#define     DCI_ATTR_NCHAR                  OCI_ATTR_NCHAR
#define OCI_ATTR_USERNAME               22                          /* username attribute */
#define     DCI_ATTR_USERNAME               OCI_ATTR_USERNAME
#define OCI_ATTR_PASSWORD               23                          /* password attribute */
#define     DCI_ATTR_PASSWORD               OCI_ATTR_PASSWORD
#define OCI_ATTR_STMT_TYPE              24                          /* statement type */
#define     DCI_ATTR_STMT_TYPE              OCI_ATTR_STMT_TYPE
#define OCI_ATTR_INTERNAL_NAME          25                          /* user friendly global name */
#define     DCI_ATTR_INTERNAL_NAME          OCI_ATTR_INTERNAL_NAME
#define OCI_ATTR_EXTERNAL_NAME          26                          /* the internal name for global txn */
#define     DCI_ATTR_EXTERNAL_NAME          OCI_ATTR_EXTERNAL_NAME
#define OCI_ATTR_XID                    27                          /* XOPEN defined global transaction id */
#define     DCI_ATTR_XID                    OCI_ATTR_XID
#define OCI_ATTR_TRANS_LOCK             28                          /* */
#define     DCI_ATTR_TRANS_LOCK             OCI_ATTR_TRANS_LOCK
#define OCI_ATTR_TRANS_NAME             29                          /* string to identify a global transaction */
#define     DCI_ATTR_TRANS_NAME             OCI_ATTR_TRANS_NAME
#define OCI_ATTR_HEAPALLOC              30                          /* memory allocated on the heap */
#define     DCI_ATTR_HEAPALLOC              OCI_ATTR_HEAPALLOC
#define OCI_ATTR_CHARSET_ID             31                          /* Character Set ID */
#define     DCI_ATTR_CHARSET_ID             OCI_ATTR_CHARSET_ID
#define OCI_ATTR_CHARSET_FORM           32                          /* Character Set Form */
#define     DCI_ATTR_CHARSET_FORM           OCI_ATTR_CHARSET_FORM
#define OCI_ATTR_MAXDATA_SIZE           33                          /* Maximumsize of data on the server  */
#define     DCI_ATTR_MAXDATA_SIZE           OCI_ATTR_MAXDATA_SIZE
#define OCI_ATTR_CACHE_OPT_SIZE         34                          /* object cache optimal size */
#define     DCI_ATTR_CACHE_OPT_SIZE         OCI_ATTR_CACHE_OPT_SIZE
#define OCI_ATTR_CACHE_MAX_SIZE         35                          /* object cache maximum size percentage */
#define     DCI_ATTR_CACHE_MAX_SIZE         OCI_ATTR_CACHE_MAX_SIZE
#define OCI_ATTR_PINOPTION              36                          /* object cache default pin option */
#define     DCI_ATTR_PINOPTION              OCI_ATTR_PINOPTION
#define OCI_ATTR_ALLOC_DURATION         37                          /* object cache default allocation duration */
#define     DCI_ATTR_ALLOC_DURATION         OCI_ATTR_ALLOC_DURATION
#define OCI_ATTR_PIN_DURATION           38                          /* object cache default pin duration */
#define     DCI_ATTR_PIN_DURATION           OCI_ATTR_PIN_DURATION
#define OCI_ATTR_FDO                    39                          /* Format Descriptor object attribute */
#define     DCI_ATTR_FDO                    OCI_ATTR_FDO
#define OCI_ATTR_POSTPROCESSING_CALLBACK    40                      /* Callback to process outbind data */
#define     DCI_ATTR_POSTPROCESSING_CALLBACK    OCI_ATTR_POSTPROCESSING_CALLBACK
#define OCI_ATTR_POSTPROCESSING_CONTEXT 41                          /* Callback context to process outbind data */
#define     DCI_ATTR_POSTPROCESSING_CONTEXT OCI_ATTR_POSTPROCESSING_CONTEXT
#define OCI_ATTR_ROWS_RETURNED          42                          /* Number of rows returned in current iter - for Bind handles */
#define     DCI_ATTR_ROWS_RETURNED          OCI_ATTR_ROWS_RETURNED
#define OCI_ATTR_FOCBK                  43                          /* Failover Callback attribute */
#define     DCI_ATTR_FOCBK                  OCI_ATTR_FOCBK
#define OCI_ATTR_IN_V8_MODE             44                          /* is the server/service context in V8 mode */
#define     DCI_ATTR_IN_V8_MODE             OCI_ATTR_IN_V8_MODE
#define OCI_ATTR_LOBEMPTY               45                          /* empty lob ? */
#define     DCI_ATTR_LOBEMPTY               OCI_ATTR_LOBEMPTY
#define OCI_ATTR_SESSLANG               46                          /* session language handle */
#define     DCI_ATTR_SESSLANG               OCI_ATTR_SESSLANG
#define OCI_ATTR_VISIBILITY             47                          /* visibility */
#define     DCI_ATTR_VISIBILITY             OCI_ATTR_VISIBILITY
#define OCI_ATTR_RELATIVE_MSGID         48                          /* relative message id */
#define     DCI_ATTR_RELATIVE_MSGID         OCI_ATTR_RELATIVE_MSGID
#define OCI_ATTR_SEQUENCE_DEVIATION     49                          /* sequence deviation */
#define     DCI_ATTR_SEQUENCE_DEVIATION     OCI_ATTR_SEQUENCE_DEVIATION
#define OCI_ATTR_CONSUMER_NAME          50                          /* consumer name */
#define     DCI_ATTR_CONSUMER_NAME          OCI_ATTR_CONSUMER_NAME
#define OCI_ATTR_DEQ_MODE               51                          /* dequeue mode */
#define     DCI_ATTR_DEQ_MODE               OCI_ATTR_DEQ_MODE
#define OCI_ATTR_NAVIGATION             52                          /* navigation */
#define     DCI_ATTR_NAVIGATION             OCI_ATTR_NAVIGATION
#define OCI_ATTR_WAIT                   53                          /* wait */
#define     DCI_ATTR_WAIT                   OCI_ATTR_WAIT
#define OCI_ATTR_DEQ_MSGID              54                          /* dequeue message id */
#define     DCI_ATTR_DEQ_MSGID              OCI_ATTR_DEQ_MSGID
#define OCI_ATTR_PRIORITY               55                          /* priority */
#define     DCI_ATTR_PRIORITY               OCI_ATTR_PRIORITY
#define OCI_ATTR_DELAY                  56                          /* delay */
#define     DCI_ATTR_DELAY                  OCI_ATTR_DELAY
#define OCI_ATTR_EXPIRATION             57                          /* expiration */
#define     DCI_ATTR_EXPIRATION             OCI_ATTR_EXPIRATION
#define OCI_ATTR_CORRELATION            58                          /* correlation id */
#define     DCI_ATTR_CORRELATION            OCI_ATTR_CORRELATION
#define OCI_ATTR_ATTEMPTS               59                          /* # of attempts */
#define     DCI_ATTR_ATTEMPTS               OCI_ATTR_ATTEMPTS
#define OCI_ATTR_RECIPIENT_LIST         60                          /* recipient list */
#define     DCI_ATTR_RECIPIENT_LIST         OCI_ATTR_RECIPIENT_LIST
#define OCI_ATTR_EXCEPTION_QUEUE        61                          /* exception queue name */
#define     DCI_ATTR_EXCEPTION_QUEUE        OCI_ATTR_EXCEPTION_QUEUE
#define OCI_ATTR_ENQ_TIME               62                          /* enqueue time (only OCIAttrGet) */
#define     DCI_ATTR_ENQ_TIME               OCI_ATTR_ENQ_TIME
#define OCI_ATTR_MSG_STATE              63                          /* message state (only OCIAttrGet) */
#define     DCI_ATTR_MSG_STATE              OCI_ATTR_MSG_STATE

/* NOTE: 64-66 used below */
#define OCI_ATTR_AGENT_NAME             64                          /* agent name */
#define     DCI_ATTR_AGENT_NAME             OCI_ATTR_AGENT_NAME
#define OCI_ATTR_AGENT_ADDRESS          65                          /* agent address */
#define     DCI_ATTR_AGENT_ADDRESS          OCI_ATTR_AGENT_ADDRESS
#define OCI_ATTR_AGENT_PROTOCOL         66                          /* agent protocol */
#define     DCI_ATTR_AGENT_PROTOCOL         OCI_ATTR_AGENT_PROTOCOL
#define OCI_ATTR_USER_PROPERTY          67                          /* user property */
#define     DCI_ATTR_USER_PROPERTY          OCI_ATTR_USER_PROPERTY
#define OCI_ATTR_SENDER_ID              68                          /* sender id */
#define     DCI_ATTR_SENDER_ID              OCI_ATTR_SENDER_ID
#define OCI_ATTR_ORIGINAL_MSGID         69                          /* original message id */
#define     DCI_ATTR_ORIGINAL_MSGID         OCI_ATTR_ORIGINAL_MSGID

#define OCI_ATTR_QUEUE_NAME             70                          /* queue name */
#define     DCI_ATTR_QUEUE_NAME             OCI_ATTR_QUEUE_NAME
#define OCI_ATTR_NFY_MSGID              71                          /* message id */
#define     DCI_ATTR_NFY_MSGID              OCI_ATTR_NFY_MSGID
#define OCI_ATTR_MSG_PROP               72                          /* message properties */
#define     DCI_ATTR_MSG_PROP               OCI_ATTR_MSG_PROP

#define OCI_ATTR_NUM_DML_ERRORS         73                          /* num of errs in array DML */
#define     DCI_ATTR_NUM_DML_ERRORS         OCI_ATTR_NUM_DML_ERRORS
#define OCI_ATTR_DML_ROW_OFFSET         74                          /* row offset in the array */
#define     DCI_ATTR_DML_ROW_OFFSET         OCI_ATTR_DML_ROW_OFFSET

/* AQ array error handling uses DML method of accessing errors */
#define OCI_ATTR_AQ_NUM_ERRORS          OCI_ATTR_NUM_DML_ERRORS
#define     DCI_ATTR_AQ_NUM_ERRORS          OCI_ATTR_AQ_NUM_ERRORS
#define OCI_ATTR_AQ_ERROR_INDEX         OCI_ATTR_DML_ROW_OFFSET
#define     DCI_ATTR_AQ_ERROR_INDEX         OCI_ATTR_AQ_ERROR_INDEX

#define OCI_ATTR_DATEFORMAT             75                          /* default date format string */
#define     DCI_ATTR_DATEFORMAT             OCI_ATTR_DATEFORMAT
#define OCI_ATTR_BUF_ADDR               76                          /* buffer address */
#define     DCI_ATTR_BUF_ADDR               OCI_ATTR_BUF_ADDR
#define OCI_ATTR_BUF_SIZE               77                          /* buffer size */
#define     DCI_ATTR_BUF_SIZE               OCI_ATTR_BUF_SIZE
#define OCI_ATTR_DIRPATH_MODE           78                          /* mode of direct path operation */
#define     DCI_ATTR_DIRPATH_MODE           OCI_ATTR_DIRPATH_MODE
#define OCI_ATTR_DIRPATH_NOLOG          79                          /* nologging option */
#define     DCI_ATTR_DIRPATH_NOLOG          OCI_ATTR_DIRPATH_NOLOG
#define OCI_ATTR_DIRPATH_PARALLEL       80                          /* parallel (temp seg) option */
#define     DCI_ATTR_DIRPATH_PARALLEL       OCI_ATTR_DIRPATH_PARALLEL
#define OCI_ATTR_NUM_ROWS               81                          /* number of rows in column array */
                                                                    /* NOTE that OCI_ATTR_NUM_COLS is a column array attribute too.*/
#define     DCI_ATTR_NUM_ROWS               OCI_ATTR_NUM_ROWS
#define OCI_ATTR_COL_COUNT              82                          /* columns of column array processed so far.       */
#define     DCI_ATTR_COL_COUNT              OCI_ATTR_COL_COUNT
#define OCI_ATTR_STREAM_OFFSET          83                          /* str off of last row processed */
#define     DCI_ATTR_STREAM_OFFSET          OCI_ATTR_STREAM_OFFSET
#define OCI_ATTR_SHARED_HEAPALLOC       84                          /* Shared Heap Allocation Size */
#define     DCI_ATTR_SHARED_HEAPALLOC       OCI_ATTR_SHARED_HEAPALLOC

#define OCI_ATTR_SERVER_GROUP           85                          /* server group name */
#define     DCI_ATTR_SERVER_GROUP           OCI_ATTR_SERVER_GROUP

#define OCI_ATTR_MIGSESSION             86                          /* migratable session attribute */
#define     DCI_ATTR_MIGSESSION             OCI_ATTR_MIGSESSION

#define OCI_ATTR_NOCACHE                87                          /* Temporary LOBs */
#define     DCI_ATTR_NOCACHE                OCI_ATTR_NOCACHE

#define OCI_ATTR_MEMPOOL_SIZE           88                          /* Pool Size */
#define     DCI_ATTR_MEMPOOL_SIZE           OCI_ATTR_MEMPOOL_SIZE
#define OCI_ATTR_MEMPOOL_INSTNAME       89                          /* Instance name */
#define     DCI_ATTR_MEMPOOL_INSTNAME       OCI_ATTR_MEMPOOL_INSTNAME
#define OCI_ATTR_MEMPOOL_APPNAME        90                          /* Application name */
#define     DCI_ATTR_MEMPOOL_APPNAME        OCI_ATTR_MEMPOOL_APPNAME
#define OCI_ATTR_MEMPOOL_HOMENAME       91                          /* Home Directory name */
#define     DCI_ATTR_MEMPOOL_HOMENAME       OCI_ATTR_MEMPOOL_HOMENAME
#define OCI_ATTR_MEMPOOL_MODEL          92                          /* Pool Model (proc,thrd,both)*/
#define     DCI_ATTR_MEMPOOL_MODEL          OCI_ATTR_MEMPOOL_MODEL
#define OCI_ATTR_MODES                  93                          /* Modes */
#define     DCI_ATTR_MODES                  OCI_ATTR_MODES

#define OCI_ATTR_SUBSCR_NAME            94                          /* name of subscription */
#define     DCI_ATTR_SUBSCR_NAME            OCI_ATTR_SUBSCR_NAME
#define OCI_ATTR_SUBSCR_CALLBACK        95                          /* associated callback */
#define     DCI_ATTR_SUBSCR_CALLBACK        OCI_ATTR_SUBSCR_CALLBACK
#define OCI_ATTR_SUBSCR_CTX             96                          /* associated callback context */
#define     DCI_ATTR_SUBSCR_CTX             OCI_ATTR_SUBSCR_CTX
#define OCI_ATTR_SUBSCR_PAYLOAD         97                          /* associated payload */
#define     DCI_ATTR_SUBSCR_PAYLOAD         OCI_ATTR_SUBSCR_PAYLOAD
#define OCI_ATTR_SUBSCR_NAMESPACE       98                          /* associated namespace */
#define     DCI_ATTR_SUBSCR_NAMESPACE       OCI_ATTR_SUBSCR_NAMESPACE

#define OCI_ATTR_PROXY_CREDENTIALS      99                          /* Proxy user credentials */
#define     DCI_ATTR_PROXY_CREDENTIALS      OCI_ATTR_PROXY_CREDENTIALS
#define OCI_ATTR_INITIAL_CLIENT_ROLES   100                         /* Initial client role list */
#define     DCI_ATTR_INITIAL_CLIENT_ROLES   OCI_ATTR_INITIAL_CLIENT_ROLES

#define OCI_ATTR_UNK                    101                         /* unknown attribute */
#define     DCI_ATTR_UNK                    OCI_ATTR_UNK
#define OCI_ATTR_NUM_COLS               102                         /* number of columns */
#define     DCI_ATTR_NUM_COLS               OCI_ATTR_NUM_COLS
#define OCI_ATTR_LIST_COLUMNS           103                         /* parameter of the column list */
#define     DCI_ATTR_LIST_COLUMNS           OCI_ATTR_LIST_COLUMNS
#define OCI_ATTR_RDBA                   104                         /* DBA of the segment header */
#define     DCI_ATTR_RDBA                   OCI_ATTR_RDBA
#define OCI_ATTR_CLUSTERED              105                         /* whether the table is clustered */
#define     DCI_ATTR_CLUSTERED              OCI_ATTR_CLUSTERED
#define OCI_ATTR_PARTITIONED            106                         /* whether the table is partitioned */
#define     DCI_ATTR_PARTITIONED            OCI_ATTR_PARTITIONED
#define OCI_ATTR_INDEX_ONLY             107                         /* whether the table is index only */
#define     DCI_ATTR_INDEX_ONLY             OCI_ATTR_INDEX_ONLY
#define OCI_ATTR_LIST_ARGUMENTS         108                         /* parameter of the argument list */
#define     DCI_ATTR_LIST_ARGUMENTS         OCI_ATTR_LIST_ARGUMENTS
#define OCI_ATTR_LIST_SUBPROGRAMS       109                         /* parameter of the subprogram list */
#define     DCI_ATTR_LIST_SUBPROGRAMS       OCI_ATTR_LIST_SUBPROGRAMS
#define OCI_ATTR_REF_TDO                110                         /* REF to the type descriptor */
#define     DCI_ATTR_REF_TDO                OCI_ATTR_REF_TDO
#define OCI_ATTR_LINK                   111                         /* the database link name */
#define     DCI_ATTR_LINK                   OCI_ATTR_LINK
#define OCI_ATTR_MIN                    112                         /* minimum value */
#define     DCI_ATTR_MIN                    OCI_ATTR_MIN
#define OCI_ATTR_MAX                    113                         /* maximum value */
#define     DCI_ATTR_MAX                    OCI_ATTR_MAX
#define OCI_ATTR_INCR                   114                         /* increment value */
#define     DCI_ATTR_INCR                   OCI_ATTR_INCR
#define OCI_ATTR_CACHE                  115                         /* number of sequence numbers cached */
#define     DCI_ATTR_CACHE                  OCI_ATTR_CACHE
#define OCI_ATTR_ORDER                  116                         /* whether the sequence is ordered */
#define     DCI_ATTR_ORDER                  OCI_ATTR_ORDER
#define OCI_ATTR_HW_MARK                117                         /* high-water mark */
#define     DCI_ATTR_HW_MARK                OCI_ATTR_HW_MARK
#define OCI_ATTR_TYPE_SCHEMA            118                         /* type's schema name */
#define     DCI_ATTR_TYPE_SCHEMA            OCI_ATTR_TYPE_SCHEMA
#define OCI_ATTR_TIMESTAMP              119                         /* timestamp of the object */
#define     DCI_ATTR_TIMESTAMP              OCI_ATTR_TIMESTAMP
#define OCI_ATTR_NUM_ATTRS              120                         /* number of sttributes */
#define     DCI_ATTR_NUM_ATTRS              OCI_ATTR_NUM_ATTRS
#define OCI_ATTR_NUM_PARAMS             121                         /* number of parameters */
#define     DCI_ATTR_NUM_PARAMS             OCI_ATTR_NUM_PARAMS
#define OCI_ATTR_OBJID                  122                         /* object id for a table or view */
#define     DCI_ATTR_OBJID                  OCI_ATTR_OBJID
#define OCI_ATTR_PTYPE                  123                         /* type of info described by */
#define     DCI_ATTR_PTYPE                  OCI_ATTR_PTYPE
#define OCI_ATTR_PARAM                  124                         /* parameter descriptor */
#define     DCI_ATTR_PARAM                  OCI_ATTR_PARAM
#define OCI_ATTR_OVERLOAD_ID            125                         /* overload ID for funcs and procs */
#define     DCI_ATTR_OVERLOAD_ID            OCI_ATTR_OVERLOAD_ID
#define OCI_ATTR_TABLESPACE             126                         /* table name space */
#define     DCI_ATTR_TABLESPACE             OCI_ATTR_TABLESPACE
#define OCI_ATTR_TDO                    127                         /* TDO of a type */
#define     DCI_ATTR_TDO                    OCI_ATTR_TDO
#define OCI_ATTR_LTYPE                  128                         /* list type */
#define     DCI_ATTR_LTYPE                  OCI_ATTR_LTYPE
#define OCI_ATTR_PARSE_ERROR_OFFSET     129                         /* Parse Error offset */
#define     DCI_ATTR_PARSE_ERROR_OFFSET     OCI_ATTR_PARSE_ERROR_OFFSET
#define OCI_ATTR_IS_TEMPORARY           130                         /* whether table is temporary */
#define     DCI_ATTR_IS_TEMPORARY           OCI_ATTR_IS_TEMPORARY
#define OCI_ATTR_IS_TYPED               131                         /* whether table is typed */
#define     DCI_ATTR_IS_TYPED               OCI_ATTR_IS_TYPED
#define OCI_ATTR_DURATION               132                         /* duration of temporary table */
#define     DCI_ATTR_DURATION               OCI_ATTR_DURATION
#define OCI_ATTR_IS_INVOKER_RIGHTS      133                         /* is invoker rights */
#define     DCI_ATTR_IS_INVOKER_RIGHTS      OCI_ATTR_IS_INVOKER_RIGHTS
#define OCI_ATTR_OBJ_NAME               134                         /* top level schema obj name */
#define     DCI_ATTR_OBJ_NAME               OCI_ATTR_OBJ_NAME
#define OCI_ATTR_OBJ_SCHEMA             135                         /* schema name */
#define     DCI_ATTR_OBJ_SCHEMA             OCI_ATTR_OBJ_SCHEMA
#define OCI_ATTR_OBJ_ID                 136                         /* top level schema object id */
#define     DCI_ATTR_OBJ_ID                 OCI_ATTR_OBJ_ID

#define OCI_ATTR_DIRPATH_SORTED_INDEX   137                         /* index that data is sorted on */
#define     DCI_ATTR_DIRPATH_SORTED_INDEX   OCI_ATTR_DIRPATH_SORTED_INDEX

            /* direct path index maint method (see oci8dp.h) */
#define OCI_ATTR_DIRPATH_INDEX_MAINT_METHOD     138
#define     DCI_ATTR_DIRPATH_INDEX_MAINT_METHOD     OCI_ATTR_DIRPATH_INDEX_MAINT_METHOD

    /* parallel load: db file, initial and next extent sizes */
#define OCI_ATTR_DIRPATH_FILE               139                     /* DB file to load into */
#define     DCI_ATTR_DIRPATH_FILE           OCI_ATTR_DIRPATH_FILE
#define OCI_ATTR_DIRPATH_STORAGE_INITIAL    140                     /* initial extent size */
#define     DCI_ATTR_DIRPATH_STORAGE_INITIAL    OCI_ATTR_DIRPATH_STORAGE_INITIAL
#define OCI_ATTR_DIRPATH_STORAGE_NEXT       141                     /* next extent size */
#define     DCI_ATTR_DIRPATH_STORAGE_NEXT       OCI_ATTR_DIRPATH_STORAGE_NEXT

#define OCI_ATTR_TRANS_TIMEOUT              142                     /* transaction timeout */
#define     DCI_ATTR_TRANS_TIMEOUT              OCI_ATTR_TRANS_TIMEOUT
#define OCI_ATTR_SERVER_STATUS              143                     /* state of the server handle */
#define     DCI_ATTR_SERVER_STATUS              OCI_ATTR_SERVER_STATUS
#define OCI_ATTR_STATEMENT                  144                     /* statement txt in stmt hdl */
#define     DCI_ATTR_STATEMENT                  OCI_ATTR_STATEMENT

/* direct path index maint method (see oci8dp.h) */
#define OCI_ATTR_DIRPATH_SKIPINDEX_METHOD   145
#define     DCI_ATTR_DIRPATH_SKIPINDEX_METHOD   OCI_ATTR_DIRPATH_SKIPINDEX_METHOD

#define OCI_ATTR_DEQCOND                    146                     /* dequeue condition */
#define     DCI_ATTR_DEQCOND                    OCI_ATTR_DEQCOND
#define OCI_ATTR_RESERVED_2                 147                     /* reserved */
#define     DCI_ATTR_RESERVED_2                 OCI_ATTR_RESERVED_2

#define OCI_ATTR_SUBSCR_RECPT               148                     /* recepient of subscription */
#define     DCI_ATTR_SUBSCR_RECPT               OCI_ATTR_SUBSCR_RECPT
#define OCI_ATTR_SUBSCR_RECPTPROTO          149                     /* protocol for recepient */
#define     DCI_ATTR_SUBSCR_RECPTPROTO          OCI_ATTR_SUBSCR_RECPTPROTO

/* 8.2 dpapi support of ADTs */
#define OCI_ATTR_DIRPATH_EXPR_TYPE          150                     /* expr type of OCI_ATTR_NAME */
#define     DCI_ATTR_DIRPATH_EXPR_TYPE          OCI_ATTR_DIRPATH_EXPR_TYPE

#define OCI_ATTR_DIRPATH_INPUT              151                     /* input in text or stream format */
#define     DCI_ATTR_DIRPATH_INPUT              OCI_ATTR_DIRPATH_INPUT
#define OCI_DIRPATH_INPUT_TEXT              0x01
#define     DCI_DIRPATH_INPUT_TEXT              OCI_DIRPATH_INPUT_TEXT
#define OCI_DIRPATH_INPUT_STREAM            0x02
#define     DCI_DIRPATH_INPUT_STREAM            OCI_DIRPATH_INPUT_STREAM
#define OCI_DIRPATH_INPUT_UNKNOWN           0x04
#define     DCI_DIRPATH_INPUT_UNKNOWN           OCI_DIRPATH_INPUT_UNKNOWN

#define OCI_ATTR_LDAP_HOST                  153                     /* LDAP host to connect to */
#define     DCI_ATTR_LDAP_HOST                  OCI_ATTR_LDAP_HOST
#define OCI_ATTR_LDAP_PORT                  154                     /* LDAP port to connect to */
#define     DCI_ATTR_LDAP_PORT                  OCI_ATTR_LDAP_PORT
#define OCI_ATTR_BIND_DN                    155                     /* bind DN */
#define     DCI_ATTR_BIND_DN                    OCI_ATTR_BIND_DN
#define OCI_ATTR_LDAP_CRED                  156                     /* credentials to connect to LDAP */
#define     DCI_ATTR_LDAP_CRED                  OCI_ATTR_LDAP_CRED
#define OCI_ATTR_WALL_LOC                   157                     /* client wallet location */
#define     DCI_ATTR_WALL_LOC                   OCI_ATTR_WALL_LOC
#define OCI_ATTR_LDAP_AUTH                  158                     /* LDAP authentication method */
#define     DCI_ATTR_LDAP_AUTH                  OCI_ATTR_LDAP_AUTH
#define OCI_ATTR_LDAP_CTX                   159                     /* LDAP adminstration context DN */
#define     DCI_ATTR_LDAP_CTX                   OCI_ATTR_LDAP_CTX
#define OCI_ATTR_SERVER_DNS                 160                     /* list of registration server DNs */
#define     DCI_ATTR_SERVER_DNS                 OCI_ATTR_SERVER_DNS

#define OCI_ATTR_DN_COUNT                   161                     /* the number of server DNs */
#define     DCI_ATTR_DN_COUNT                   OCI_ATTR_DN_COUNT
#define OCI_ATTR_SERVER_DN                  162                     /* server DN attribute */
#define     DCI_ATTR_SERVER_DN                  OCI_ATTR_SERVER_DN

#define OCI_ATTR_MAXCHAR_SIZE               163                     /* max char size of data */
#define     DCI_ATTR_MAXCHAR_SIZE               OCI_ATTR_MAXCHAR_SIZE

#define OCI_ATTR_CURRENT_POSITION           164                     /* for scrollable result sets*/
#define     DCI_ATTR_CURRENT_POSITION           OCI_ATTR_CURRENT_POSITION

/* Added to get attributes for ref cursor to statement handle */
#define OCI_ATTR_RESERVED_3                 165                     /* reserved */
#define     DCI_ATTR_RESERVED_3                 OCI_ATTR_RESERVED_3
#define OCI_ATTR_RESERVED_4                 166                     /* reserved */
#define     DCI_ATTR_RESERVED_4                 OCI_ATTR_RESERVED_4
#define OCI_ATTR_DIRPATH_FN_CTX             167                     /* fn ctx ADT attrs or args */
#define     DCI_ATTR_DIRPATH_FN_CTX             OCI_ATTR_DIRPATH_FN_CTX
#define OCI_ATTR_DIGEST_ALGO                168                     /* digest algorithm */
#define     DCI_ATTR_DIGEST_ALGO                OCI_ATTR_DIGEST_ALGO
#define OCI_ATTR_CERTIFICATE                169                     /* certificate */
#define     DCI_ATTR_CERTIFICATE                OCI_ATTR_CERTIFICATE
#define OCI_ATTR_SIGNATURE_ALGO             170                     /* signature algorithm */
#define     DCI_ATTR_SIGNATURE_ALGO             OCI_ATTR_SIGNATURE_ALGO
#define OCI_ATTR_CANONICAL_ALGO             171                     /* canonicalization algo. */
#define     DCI_ATTR_CANONICAL_ALGO             OCI_ATTR_CANONICAL_ALGO
#define OCI_ATTR_PRIVATE_KEY                172                     /* private key */
#define     DCI_ATTR_PRIVATE_KEY                OCI_ATTR_PRIVATE_KEY
#define OCI_ATTR_DIGEST_VALUE               173                     /* digest value */
#define     DCI_ATTR_DIGEST_VALUE               OCI_ATTR_DIGEST_VALUE
#define OCI_ATTR_SIGNATURE_VAL              174                     /* signature value */
#define     DCI_ATTR_SIGNATURE_VAL              OCI_ATTR_SIGNATURE_VAL
#define OCI_ATTR_SIGNATURE                  175                     /* signature */
#define     DCI_ATTR_SIGNATURE                  OCI_ATTR_SIGNATURE

/* attributes for setting OCI stmt caching specifics in svchp */
#define OCI_ATTR_STMTCACHESIZE              176                     /* size of the stm cache */
#define     DCI_ATTR_STMTCACHESIZE              OCI_ATTR_STMTCACHESIZE

/* --------------------------- Connection Pool Attributes ------------------ */
#define OCI_ATTR_CONN_NOWAIT                178
#define     DCI_ATTR_CONN_NOWAIT                OCI_ATTR_CONN_NOWAIT
#define OCI_ATTR_CONN_BUSY_COUNT            179
#define     DCI_ATTR_CONN_BUSY_COUNT            OCI_ATTR_CONN_BUSY_COUNT
#define OCI_ATTR_CONN_OPEN_COUNT            180
#define     DCI_ATTR_CONN_OPEN_COUNT            OCI_ATTR_CONN_OPEN_COUNT
#define OCI_ATTR_CONN_TIMEOUT               181
#define     DCI_ATTR_CONN_TIMEOUT               OCI_ATTR_CONN_TIMEOUT
#define OCI_ATTR_STMT_STATE                 182
#define     DCI_ATTR_STMT_STATE                 OCI_ATTR_STMT_STATE
#define OCI_ATTR_CONN_MIN                   183
#define     DCI_ATTR_CONN_MIN                   OCI_ATTR_CONN_MIN
#define OCI_ATTR_CONN_MAX                   184
#define     DCI_ATTR_CONN_MAX                   OCI_ATTR_CONN_MAX
#define OCI_ATTR_CONN_INCR                  185
#define     DCI_ATTR_CONN_INCR                  OCI_ATTR_CONN_INCR

#define OCI_ATTR_DIRPATH_OID                187                     /* loading into an OID col */
#define     DCI_ATTR_DIRPATH_OID                OCI_ATTR_DIRPATH_OID

#define OCI_ATTR_NUM_OPEN_STMTS             188                     /* open stmts in session */
#define     DCI_ATTR_NUM_OPEN_STMTS             OCI_ATTR_NUM_OPEN_STMTS
#define OCI_ATTR_DESCRIBE_NATIVE            189                     /* get native info via desc */
#define     DCI_ATTR_DESCRIBE_NATIVE            OCI_ATTR_DESCRIBE_NATIVE

#define OCI_ATTR_BIND_COUNT                 190                     /* number of bind postions */
#define     DCI_ATTR_BIND_COUNT                 OCI_ATTR_BIND_COUNT
#define OCI_ATTR_HANDLE_POSITION            191                     /* pos of bind/define handle */
#define     DCI_ATTR_HANDLE_POSITION            OCI_ATTR_HANDLE_POSITION
#define OCI_ATTR_RESERVED_5                 192                     /* reserverd */
#define     DCI_ATTR_RESERVED_5                 OCI_ATTR_RESERVED_5
#define OCI_ATTR_SERVER_BUSY                193                     /* call in progress on server*/
#define     DCI_ATTR_SERVER_BUSY                OCI_ATTR_SERVER_BUSY

#define OCI_ATTR_DIRPATH_SID                194                     /* loading into an SID col */
#define     DCI_ATTR_DIRPATH_SID                OCI_ATTR_DIRPATH_SID
/* notification presentation for recipient */
#define OCI_ATTR_SUBSCR_RECPTPRES           195
#define     DCI_ATTR_SUBSCR_RECPTPRES           OCI_ATTR_SUBSCR_RECPTPRES
#define OCI_ATTR_TRANSFORMATION             196                     /* AQ message transformation */
#define     DCI_ATTR_TRANSFORMATION             OCI_ATTR_TRANSFORMATION

#define OCI_ATTR_ROWS_FETCHED               197                     /* rows fetched in last call */
#define     DCI_ATTR_ROWS_FETCHED               OCI_ATTR_ROWS_FETCHED

/* --------------------------- Snapshot attributes ------------------------- */
#define OCI_ATTR_SCN_BASE                   198                     /* snapshot base */
#define     DCI_ATTR_SCN_BASE                   OCI_ATTR_SCN_BASE
#define OCI_ATTR_SCN_WRAP                   199                     /* snapshot wrap */
#define     DCI_ATTR_SCN_WRAP                   OCI_ATTR_SCN_WRAP

/* --------------------------- Miscellanous attributes --------------------- */
#define OCI_ATTR_RESERVED_6                 200                     /* reserved */
#define     DCI_ATTR_RESERVED_6                 OCI_ATTR_RESERVED_6
#define OCI_ATTR_READONLY_TXN               201                     /* txn is readonly */
#define     DCI_ATTR_READONLY_TXN               OCI_ATTR_READONLY_TXN
#define OCI_ATTR_RESERVED_7                 202                     /* reserved */
#define     DCI_ATTR_RESERVED_7                 OCI_ATTR_RESERVED_7
#define OCI_ATTR_ERRONEOUS_COLUMN           203                     /* position of erroneous col */
#define     DCI_ATTR_ERRONEOUS_COLUMN           OCI_ATTR_ERRONEOUS_COLUMN
#define OCI_ATTR_RESERVED_8                 204                     /* reserved */
#define     DCI_ATTR_RESERVED_8                 OCI_ATTR_RESERVED_8

/* -------------------- 8.2 dpapi support of ADTs continued ---------------- */
#define OCI_ATTR_DIRPATH_OBJ_CONSTR         206                     /* obj type of subst obj tbl */
#define     DCI_ATTR_DIRPATH_OBJ_CONSTR         OCI_ATTR_DIRPATH_OBJ_CONSTR
#define OCI_ATTR_INST_TYPE                  207                     /* oracle instance type */
#define     DCI_ATTR_INST_TYPE                  OCI_ATTR_INST_TYPE
/******USED attribute 208 for  OCI_ATTR_SPOOL_STMTCACHESIZE*******************/

#define OCI_ATTR_ENV_UTF16                  209                     /* is env in utf16 mode? */
#define     DCI_ATTR_ENV_UTF16                  OCI_ATTR_ENV_UTF16
#define OCI_ATTR_RESERVED_9                 210                     /* reserved for TMZ */
#define     DCI_ATTR_RESERVED_9                 OCI_ATTR_RESERVED_9
#define OCI_ATTR_RESERVED_10                211                     /* reserved */
#define     DCI_ATTR_RESERVED_10                OCI_ATTR_RESERVED_10

/* Attr to allow setting of the stream version PRIOR to calling Prepare */
#define OCI_ATTR_DIRPATH_STREAM_VERSION     212                     /* version of the stream*/
#define     DCI_ATTR_DIRPATH_STREAM_VERSION     OCI_ATTR_DIRPATH_STREAM_VERSION

#define OCI_ATTR_DIRPATH_VARRAY_INDEX       213                     /* varray index column */
#define     DCIP_ATTR_DIRPATH_VARRAY_INDEX      OCI_ATTR_DIRPATH_VARRAY_INDEX

#define OCI_ATTR_RESERVED_12                214                     /* reserved */
#define     DCI_ATTR_RESERVED_12                OCI_ATTR_RESERVED_12
#define OCI_ATTR_RESERVED_13                215                     /* reserved */
#define     DCI_ATTR_RESERVED_13                OCI_ATTR_RESERVED_13
#define OCI_ATTR_IS_EXTERNAL                216                     /* whether table is external */
#define     DCI_ATTR_IS_EXTERNAL                OCI_ATTR_IS_EXTERNAL

/* -------------------------- Statement Handle Attributes ------------------ */

#define OCI_ATTR_RESERVED_15                217                     /* reserved */
#define     DCI_ATTR_RESERVED_15                OCI_ATTR_RESERVED_15
#define OCI_ATTR_STMT_IS_RETURNING          218                     /* stmt has returning clause */
#define     DCI_ATTR_STMT_IS_RETURNING          OCI_ATTR_STMT_IS_RETURNING
#define OCI_ATTR_RESERVED_16                219                     /* reserved */
#define     DCI_ATTR_RESERVED_16                OCI_ATTR_RESERVED_16
#define OCI_ATTR_RESERVED_17                220                     /* reserved */
#define     DCI_ATTR_RESERVED_17                OCI_ATTR_RESERVED_17
#define OCI_ATTR_RESERVED_18                221                     /* reserved */
#define     DCI_ATTR_RESERVED_18                OCI_ATTR_RESERVED_18

/* --------------------------- session attributes ---------------------------*/
#define OCI_ATTR_RESERVED_19                222                     /* reserved */
#define     DCI_ATTR_RESERVED_19                OCI_ATTR_RESERVED_19
#define OCI_ATTR_LIST_TYPE                  223                     /*attributes of list,designates list type*/
#define     DCI_ATTR_LIST_TYPE                  OCI_ATTR_LIST_TYPE
#define OCI_ATTR_SSL_PATH                   10000                   /*attributes of SSL_PATH*/
#define     DCI_ATTR_SSL_PATH                   OCI_ATTR_SSL_PATH
#define OCI_ATTR_SSL_PWD                    10001
#define     DCI_ATTR_SSL_PWD                    OCI_ATTR_SSL_PWD
#define OCI_ATTR_MPP_LOGIN                  10002
#define     DCI_ATTR_MPP_LOGIN                  OCI_ATTR_MPP_LOGIN
#define OCI_ATTR_RW_SEPARATE                10003
#define     DCI_ATTR_RW_SEPARATE                OCI_ATTR_RW_SEPARATE
#define OCI_ATTR_RW_SEPARATE_PERCENT        10004
#define     DCI_ATTR_RW_SEPARATE_PERCENT        OCI_ATTR_RW_SEPARATE_PERCENT
#define OCI_ATTR_CONN_TYPE                  10005
#define     DCI_ATTR_CONN_TYPE                  OCI_ATTR_CONN_TYPE
#define OCI_ATTR_LOGIN_CERTIFICATE          10006
#define     DCI_ATTR_LOGIN_CERTIFICATE          OCI_ATTR_LOGIN_CERTIFICATE
#define OCI_ATTR_DRIVER_NAME                424                     /* Specifies the name of the driver layer using OCI. (Such as JDBC, ODBC, PHP, SQL*Plus, and so on. */			
#define     DCI_ATTR_DRIVER_NAME                OCI_ATTR_DRIVER_NAME
/*------------- Supported Values for Direct Path Stream Version -------------*/
#define OCI_DIRPATH_STREAM_VERSION_1        100
#define     DCI_DIRPATH_STREAM_VERSION_1        OCI_DIRPATH_STREAM_VERSION_1
#define OCI_DIRPATH_STREAM_VERSION_2        200
#define     DCI_DIRPATH_STREAM_VERSION_2        OCI_DIRPATH_STREAM_VERSION_2
#define OCI_DIRPATH_STREAM_VERSION_3        300                     /* default */
#define     DCI_DIRPATH_STREAM_VERSION_3        OCI_DIRPATH_STREAM_VERSION_3

/* ----------------------- row callback attributes ------------------------- */
#define OCI_ATTR_BIND_ROWCBK                301                     /* bind row callback */
#define     DCI_ATTR_BIND_ROWCBK                OCI_ATTR_BIND_ROWCBK
#define OCI_ATTR_BIND_ROWCTX                302                     /* ctx for bind row callback */
#define     DCI_ATTR_BIND_ROWCTX                OCI_ATTR_BIND_ROWCTX
#define OCI_ATTR_SKIP_BUFFER                303                     /* skip buffer in array ops */
#define     DCI_ATTR_SKIP_BUFFER                OCI_ATTR_SKIP_BUFFER

/* ----------------------- DM attributes ----------------------------------- */
#define OCI_ATTR_PORT                       1000                    /* DM login port	 */
#define     DCI_ATTR_PORT                       OCI_ATTR_PORT

#define OCI_ATTR_DIRPATH_SET_IDENTITY       2000                    /* DRIPATH INPUT ENABLE SET IDENTITY COLUMN*/
#define     DCI_ATTR_DIRPATH_SET_IDENTITY       OCI_ATTR_DIRPATH_SET_IDENTITY

/* -------- client side character and national character set ids ----------- */
#define OCI_ATTR_ENV_CHARSET_ID             OCI_ATTR_CHARSET_ID     /* charset id in env */
#define     DCI_ATTR_ENV_CHARSET_ID             OCI_ATTR_ENV_CHARSET_ID
#define OCI_ATTR_ENV_NCHARSET_ID            OCI_ATTR_NCHARSET_ID    /* ncharset id in env */
#define     DCI_ATTR_ENV_NCHARSET_ID            OCI_ATTR_ENV_NCHARSET_ID

/*------------- Supported Values for protocol for recepient -----------------*/
#define OCI_SUBSCR_PROTO_OCI                0                       /* oci */
#define     DCI_SUBSCR_PROTO_OCI                OCI_SUBSCR_PROTO_OCI
#define OCI_SUBSCR_PROTO_MAIL               1                       /* mail */
#define     DCI_SUBSCR_PROTO_MAIL               OCI_SUBSCR_PROTO_MAIL
#define OCI_SUBSCR_PROTO_SERVER             2                       /* server */
#define     DCI_SUBSCR_PROTO_SERVER             OCI_SUBSCR_PROTO_SERVER
#define OCI_SUBSCR_PROTO_HTTP               3                       /* http */
#define     DCI_SUBSCR_PROTO_HTTP               OCI_SUBSCR_PROTO_HTTP
#define OCI_SUBSCR_PROTO_MAX                4                       /* max current protocols */
#define     DCI_SUBSCR_PROTO_MAX                OCI_SUBSCR_PROTO_MAX

/*------------- Supported Values for presentation for recepient -------------*/
#define OCI_SUBSCR_PRES_DEFAULT             0                       /* default */
#define     DCI_SUBSCR_PRES_DEFAULT             OCI_SUBSCR_PRES_DEFAULT
#define OCI_SUBSCR_PRES_XML                 1                       /* xml */
#define     DCI_SUBSCR_PRES_XML                 OCI_SUBSCR_PRES_XML
#define OCI_SUBSCR_PRES_MAX                 2                       /* max current presentations */
#define     DCI_SUBSCR_PRES_MAX                 OCI_SUBSCR_PRES_MAX
                                                   

/* ----- Temporary attribute value for UCS2/UTF16 character set ID -------- */ 
#define OCI_UCS2ID                          1000                    /* UCS2 charset ID */
#define     DCI_UCS2ID                          OCI_UCS2ID
#define OCI_UTF16ID                         1000                    /* UTF16 charset ID */
#define     DCI_UTF16ID                         OCI_UTF16ID

/*============================== End OCI Attribute Types ====================*/

/*---------------- Session Handle Attribute Values ---------------------------*/
/* OCI_ATTR_MPP_LOGIN*/
#define OCI_MPP_LOGIN_GLOBAL                0
#define     DCI_MPP_LOGIN_GLOBAL                OCI_MPP_LOGIN_GLOBAL
#define OCI_MPP_LOGIN_LOCAL                 1
#define     DCI_MPP_LOGIN_LOCAL                 OCI_MPP_LOGIN_LOCAL

#define OCI_RW_SEPARATE_OFF                 0
#define     DCI_RW_SEPARATE_OFF                 OCI_RW_SEPARATE_OFF
#define OCI_RW_SEPARATE_ON                  1
#define     DCI_RW_SEPARATE_ON                  OCI_RW_SEPARATE_ON

#define OCI_CONN_TCP                        0
#define     DCI_CONN_TCP                        OCI_CONN_TCP
#define OCI_CONN_UDP                        1
#define     DCI_CONN_UDP                        OCI_CONN_UDP
#define OCI_CONN_IPC                    2
#define     DCI_CONN_IPC                OCI_CONN_IPC
#define OCI_CONN_RDMA                   3
#define     DCI_CONN_RDMA               OCI_CONN_RDMA
/*---------------- Server Handle Attribute Values ---------------------------*/

/* OCI_ATTR_SERVER_STATUS */
#define OCI_SERVER_NOT_CONNECTED            0x0
#define     DCI_SERVER_NOT_CONNECTED            OCI_SERVER_NOT_CONNECTED
#define OCI_SERVER_NORMAL                   0x1
#define     DCI_SERVER_NORMAL                   OCI_SERVER_NORMAL

/*---------------------------------------------------------------------------*/

/*------------------------- Supported Namespaces  ---------------------------*/
#define OCI_SUBSCR_NAMESPACE_ANONYMOUS      0                       /* Anonymous Namespace */
#define     DCI_SUBSCR_NAMESPACE_ANONYMOUS      OCI_SUBSCR_NAMESPACE_ANONYMOUS
#define OCI_SUBSCR_NAMESPACE_AQ             1                       /* Advanced Queues */
#define     DCI_SUBSCR_NAMESPACE_AQ             OCI_SUBSCR_NAMESPACE_AQ
#define OCI_SUBSCR_NAMESPACE_MAX            2                       /* Max Name Space Number */
#define     DCI_SUBSCR_NAMESPACE_MAX            OCI_SUBSCR_NAMESPACE_MAX

/*-------------------------Credential Types----------------------------------*/
#define OCI_CRED_RDBMS                      1                       /* database username/password */
#define     DCI_CRED_RDBMS                      OCI_CRED_RDBMS
#define OCI_CRED_EXT                        2                       /* externally provided credentials */
#define     DCI_CRED_EXT                        OCI_CRED_EXT
#define OCI_CRED_PROXY                      3                       /* proxy authentication */
#define     DCI_CRED_PROXY                      OCI_CRED_PROXY
#define OCI_CRED_RESERVED_1                 4                       /* reserved */
#define     DCI_CRED_RESERVED_1                 OCI_CRED_RESERVED_1
#define OCI_CRED_RESERVED_2                 5                       /* reserved */
#define     DCI_CRED_RESERVED_2                 OCI_CRED_RESERVED_2
/*---------------------------------------------------------------------------*/

/*------------------------Error Return Values--------------------------------*/
#define OCI_SUCCESS                         0                       /* maps to SQL_SUCCESS of SAG CLI */
#define     DCI_SUCCESS                         OCI_SUCCESS
#define OCI_SUCCESS_WITH_INFO               1                       /* maps to SQL_SUCCESS_WITH_INFO */
#define     DCI_SUCCESS_WITH_INFO               OCI_SUCCESS_WITH_INFO
#define OCI_RESERVED_FOR_INT_USE            200                     /* reserved */ 
#define     DCI_RESERVED_FOR_INT_USE            OCI_RESERVED_FOR_INT_USE
#define OCI_NO_DATA                         100                     /* maps to SQL_NO_DATA */
#define     DCI_NO_DATA                         OCI_NO_DATA
#define OCI_ERROR                           -1                      /* maps to SQL_ERROR */
#define     DCI_ERROR                           OCI_ERROR

#define OCI_INVALID_HANDLE                  -2                      /* maps to SQL_INVALID_HANDLE */
#define     DCI_INVALID_HANDLE                  OCI_INVALID_HANDLE
#define OCI_NEED_DATA                       99                      /* maps to SQL_NEED_DATA */
#define     DCI_NEED_DATA                       OCI_NEED_DATA
#define OCI_STILL_EXECUTING                 -3123                   /* OCI would block error */
#define     DCI_STILL_EXECUTING                 OCI_STILL_EXECUTING
/*---------------------------------------------------------------------------*/

/*--------------------- User Callback Return Values -------------------------*/
#define OCI_CONTINUE                        -24200                  /* Continue with the body of the OCI function */
#define     DCI_CONTINUE                        OCI_CONTINUE
#define OCI_ROWCBK_DONE                     -24201                  /* done with user row callback */
#define     DCI_ROWCBK_DONE                     OCI_ROWCBK_DONE
/*---------------------------------------------------------------------------*/

/*------------------DateTime and Interval check Error codes------------------*/

/* DateTime Error Codes used by OCIDateTimeCheck() */
#define OCI_DT_INVALID_DAY                  0x1                     /* Bad day */
#define     DCI_DT_INVALID_DAY                  OCI_DT_INVALID_DAY
#define OCI_DT_DAY_BELOW_VALID              0x2                     /* Bad DAy Low/high bit (1=low)*/
#define     DCI_DT_DAY_BELOW_VALID              OCI_DT_DAY_BELOW_VALID
#define OCI_DT_INVALID_MONTH                0x4                     /*  Bad MOnth */
#define     DCI_DT_INVALID_MONTH                OCI_DT_INVALID_MONTH
#define OCI_DT_MONTH_BELOW_VALID            0x8                     /* Bad MOnth Low/high bit (1=low) */
#define     DCI_DT_MONTH_BELOW_VALID            OCI_DT_MONTH_BELOW_VALID
#define OCI_DT_INVALID_YEAR                 0x10                    /* Bad YeaR */
#define     DCI_DT_INVALID_YEAR                 OCI_DT_INVALID_YEAR
#define OCI_DT_YEAR_BELOW_VALID             0x20                    /*  Bad YeaR Low/high bit (1=low) */
#define     DCI_DT_YEAR_BELOW_VALID             OCI_DT_YEAR_BELOW_VALID
#define OCI_DT_INVALID_HOUR                 0x40                    /*  Bad HouR */
#define     DCI_DT_INVALID_HOUR                 OCI_DT_INVALID_HOUR
#define OCI_DT_HOUR_BELOW_VALID             0x80                    /* Bad HouR Low/high bit (1=low) */
#define     DCI_DT_HOUR_BELOW_VALID             OCI_DT_HOUR_BELOW_VALID
#define OCI_DT_INVALID_MINUTE               0x100                   /* Bad MiNute */
#define     DCI_DT_INVALID_MINUTE               OCI_DT_INVALID_MINUTE
#define OCI_DT_MINUTE_BELOW_VALID           0x200                   /*Bad MiNute Low/high bit (1=low) */
#define     DCI_DT_MINUTE_BELOW_VALID           OCI_DT_MINUTE_BELOW_VALID
#define OCI_DT_INVALID_SECOND               0x400                   /*  Bad SeCond */
#define     DCI_DT_INVALID_SECOND               OCI_DT_INVALID_SECOND
#define OCI_DT_SECOND_BELOW_VALID           0x800                   /*bad second Low/high bit (1=low)*/
#define     DCI_DT_SECOND_BELOW_VALID           OCI_DT_SECOND_BELOW_VALID
#define OCI_DT_DAY_MISSING_FROM_1582        0x1000                  /*  Day is one of those "missing" from 1582 */
#define     DCI_DT_DAY_MISSING_FROM_1582        OCI_DT_DAY_MISSING_FROM_1582
#define OCI_DT_YEAR_ZERO                    0x2000                  /* Year may not equal zero */
#define     DCI_DT_YEAR_ZERO                    OCI_DT_YEAR_ZERO
#define OCI_DT_INVALID_TIMEZONE             0x4000                  /*  Bad Timezone */
#define     DCI_DT_INVALID_TIMEZONE             OCI_DT_INVALID_TIMEZONE
#define OCI_DT_INVALID_FORMAT               0x8000                  /* Bad date format input */
#define     DCI_DT_INVALID_FORMAT               OCI_DT_INVALID_FORMAT

/* Interval Error Codes used by OCIInterCheck() */
#define OCI_INTER_INVALID_DAY               0x1                     /* Bad day */
#define     DCI_INTER_INVALID_DAY               OCI_INTER_INVALID_DAY
#define OCI_INTER_DAY_BELOW_VALID           0x2                     /* Bad DAy Low/high bit (1=low) */
#define     DCI_INTER_DAY_BELOW_VALID           OCI_INTER_DAY_BELOW_VALID
#define OCI_INTER_INVALID_MONTH             0x4                     /* Bad MOnth */
#define     DCI_INTER_INVALID_MONTH             OCI_INTER_INVALID_MONTH
#define OCI_INTER_MONTH_BELOW_VALID         0x8                     /*Bad MOnth Low/high bit (1=low) */
#define     DCI_INTER_MONTH_BELOW_VALID         OCI_INTER_MONTH_BELOW_VALID
#define OCI_INTER_INVALID_YEAR              0x10                    /* Bad YeaR */
#define     DCI_INTER_INVALID_YEAR              OCI_INTER_INVALID_YEAR
#define OCI_INTER_YEAR_BELOW_VALID          0x20                    /*Bad YeaR Low/high bit (1=low) */
#define     DCI_INTER_YEAR_BELOW_VALID          OCI_INTER_YEAR_BELOW_VALID
#define OCI_INTER_INVALID_HOUR              0x40                    /* Bad HouR */
#define     DCI_INTER_INVALID_HOUR              OCI_INTER_INVALID_HOUR
#define OCI_INTER_HOUR_BELOW_VALID          0x80                    /*Bad HouR Low/high bit (1=low) */
#define     DCI_INTER_HOUR_BELOW_VALID          OCI_INTER_HOUR_BELOW_VALID
#define OCI_INTER_INVALID_MINUTE            0x100                   /* Bad MiNute */
#define     DCI_INTER_INVALID_MINUTE            OCI_INTER_INVALID_MINUTE
#define OCI_INTER_MINUTE_BELOW_VALID        0x200                   /*Bad MiNute Low/high bit(1=low) */
#define     DCI_INTER_MINUTE_BELOW_VALID        OCI_INTER_MINUTE_BELOW_VALID
#define OCI_INTER_INVALID_SECOND            0x400                   /* Bad SeCond */
#define     DCI_INTER_INVALID_SECOND            OCI_INTER_INVALID_SECOND
#define OCI_INTER_SECOND_BELOW_VALID        0x800                   /*bad second Low/high bit(1=low) */
#define     DCI_INTER_SECOND_BELOW_VALID        OCI_INTER_SECOND_BELOW_VALID
#define OCI_INTER_INVALID_FRACSEC           0x1000                  /* Bad Fractional second */
#define     DCI_INTER_INVALID_FRACSEC           OCI_INTER_INVALID_FRACSEC
#define OCI_INTER_FRACSEC_BELOW_VALID       0x2000                  /* Bad fractional second Low/High */
#define     DCI_INTER_FRACSEC_BELOW_VALID       OCI_INTER_FRACSEC_BELOW_VALID

/* --------------------END DateTime and Interval Constants ------------------*/

/*------------------------Parsing Syntax Types-------------------------------*/
#define OCI_V7_SYNTAX                       2                       /* V815 language - for backwards compatibility */
#define     DCI_V7_SYNTAX                       OCI_V7_SYNTAX
#define OCI_V8_SYNTAX                       3                       /* V815 language - for backwards compatibility */
#define     DCI_V8_SYNTAX                       OCI_V8_SYNTAX
#define OCI_NTV_SYNTAX                      1                       /* Use what so ever is the native lang of server */
#define     DCI_NTV_SYNTAX                      OCI_NTV_SYNTAX
                     /* these values must match the values defined in kpul.h */
/*---------------------------------------------------------------------------*/

/*------------------------Scrollable Cursor Fetch Options------------------- 
 * For non-scrollable cursor, the only valid (and default) orientation is 
 * OCI_FETCH_NEXT
 */
#define OCI_FETCH_CURRENT                   0x01                    /* refetching current position  */
#define     DCI_FETCH_CURRENT                   OCI_FETCH_CURRENT
#define OCI_FETCH_NEXT                      0x02                    /* next row */
#define     DCI_FETCH_NEXT                      OCI_FETCH_NEXT
#define OCI_FETCH_FIRST                     0x04                    /* first row of the result set */
#define     DCI_FETCH_FIRST                     OCI_FETCH_FIRST
#define OCI_FETCH_LAST                      0x08                    /* the last row of the result set */
#define     DCI_FETCH_LAST                      OCI_FETCH_LAST
#define OCI_FETCH_PRIOR                     0x10                    /* the previous row relative to current */
#define     DCI_FETCH_PRIOR                     OCI_FETCH_PRIOR
#define OCI_FETCH_ABSOLUTE                  0x20                    /* absolute offset from first */
#define     DCI_FETCH_ABSOLUTE                  OCI_FETCH_ABSOLUTE
#define OCI_FETCH_RELATIVE                  0x40                    /* offset relative to current */
#define     DCI_FETCH_RELATIVE                  OCI_FETCH_RELATIVE
#define OCI_FETCH_RESERVED_1                0x80                    /* reserved */
#define     DCI_FETCH_RESERVED_1                OCI_FETCH_RESERVED_1

/*---------------------------------------------------------------------------*/

/*------------------------Bind and Define Options----------------------------*/
#define OCI_SB2_IND_PTR                     0x00000001              /* unused */
#define     DCI_SB2_IND_PTR                     OCI_SB2_IND_PTR
#define OCI_DATA_AT_EXEC                    0x00000002              /* data at execute time */
#define     DCI_DATA_AT_EXEC                    OCI_DATA_AT_EXEC
#define OCI_DYNAMIC_FETCH                   0x00000002              /* fetch dynamically */
#define     DCI_DYNAMIC_FETCH                   OCI_DYNAMIC_FETCH
#define OCI_PIECEWISE                       0x00000004              /* piecewise DMLs or fetch */
#define     DCI_PIECEWISE                       OCI_PIECEWISE
#define OCI_DEFINE_RESERVED_1               0x00000008              /* reserved */
#define     DCI_DEFINE_RESERVED_1               OCI_DEFINE_RESERVED_1
#define OCI_BIND_RESERVED_2                 0x00000010              /* reserved */
#define     DCI_BIND_RESERVED_2                 OCI_BIND_RESERVED_2
#define OCI_DEFINE_RESERVED_2               0x00000020              /* reserved */
#define     DCI_DEFINE_RESERVED_2               OCI_DEFINE_RESERVED_2
#define OCI_BIND_SOFT                       0x00000040              /* soft bind or define */
#define     DCI_BIND_SOFT                       OCI_BIND_SOFT
#define OCI_DEFINE_SOFT                     0x00000080              /* soft bind or define */
#define     DCI_DEFINE_SOFT                     OCI_DEFINE_SOFT
/*---------------------------------------------------------------------------*/

/*-----------------------------  Various Modes ------------------------------*/
#define OCI_DEFAULT                         0x00000000              /* the default value for parameters and attributes */
#define     DCI_DEFAULT                         OCI_DEFAULT

/*-------------OCIInitialize Modes / OCICreateEnvironment Modes -------------*/
#define OCI_THREADED                        0x00000001              /* appl. in threaded environment */
#define     DCI_THREADED                        OCI_THREADED
#define OCI_OBJECT                          0x00000002              /* application in object environment */
#define     DCI_OBJECT                          OCI_OBJECT
#define OCI_EVENTS                          0x00000004              /* application is enabled for events */
#define     DCI_EVENTS                          OCI_EVENTS
#define OCI_RESERVED1                       0x00000008              /* reserved */
#define     DCI_RESERVED1                       OCI_RESERVED1
#define OCI_SHARED                          0x00000010              /* the application is in shared mode */
#define     DCI_SHARED                          OCI_SHARED
#define OCI_RESERVED2                       0x00000020              /* reserved */
#define     DCI_RESERVED2                       OCI_RESERVED2
/* The following *TWO* are only valid for OCICreateEnvironment call */
#define OCI_NO_UCB                          0x00000040              /* No user callback called during ini */
#define     DCI_NO_UCB                          OCI_NO_UCB
#define OCI_NO_MUTEX                        0x00000080              /* the environment handle will not be 
                                                                       protected by a mutex internally*/
#define     DCI_NO_MUTEX                        OCI_NO_MUTEX
#define OCI_SHARED_EXT                      0x00000100              /* Used for shared forms */
#define     DCI_SHARED_EXT                      OCI_SHARED_EXT
/************************** 0x00000200 free **********************************/
#define OCI_ALWAYS_BLOCKING                 0x00000400              /* all connections always blocking */
#define     DCI_ALWAYS_BLOCKING                 OCI_ALWAYS_BLOCKING
/************************** 0x00000800 free **********************************/
#define OCI_USE_LDAP                        0x00001000              /* allow  LDAP connections */
#define     DCI_USE_LDAP                        OCI_USE_LDAP
#define OCI_REG_LDAPONLY                    0x00002000              /* only register to LDAP */
#define     DCI_REG_LDAPONLY                    OCI_REG_LDAPONLY
#define OCI_UTF16                           0x00004000              /* mode for all UTF16 metadata */
#define     DCI_UTF16                           OCI_UTF16
#define OCI_AFC_PAD_ON                      0x00008000              /* turn on AFC blank padding when rlenp present */
#define     DCI_AFC_PAD_ON                      OCI_AFC_PAD_ON
#define OCI_ENVCR_RESERVED3                 0x00010000              /* reserved */
#define     DCI_ENVCR_RESERVED3                 OCI_ENVCR_RESERVED3
#define OCI_NEW_LENGTH_SEMANTICS            0x00020000              /* adopt new length semantics 
                                                                       the new length semantics, always bytes, is used by OCIEnvNlsCreate */
#define     DCI_NEW_LENGTH_SEMANTICS            OCI_NEW_LENGTH_SEMANTICS
#define OCI_NO_MUTEX_STMT                   0x00040000              /* Do not mutex stmt handle */
#define     DCI_NO_MUTEX_STMT                   OCI_NO_MUTEX_STMT
#define OCI_MUTEX_ENV_ONLY                  0x00080000              /* Mutex only the environment handle */
#define     DCI_MUTEX_ENV_ONLY                  OCI_MUTEX_ENV_ONLY
#define OCI_NCHAR_LITERAL_REPLACE_ON        0x00400000              /* nchar literal replace on */
#define     DCI_NCHAR_LITERAL_REPLACE_ON        OCI_NCHAR_LITERAL_REPLACE_ON
#define OCI_NCHAR_LITERAL_REPLACE_OFF       0x00800000              /* nchar literal replace off*/
#define     DCI_NCHAR_LITERAL_REPLACE_OFF       OCI_NCHAR_LITERAL_REPLACE_OFF
#define OCI_STM_RESERVED4                   0x00100000              /* reserved */
#define     DCI_STM_RESERVED4                   OCI_STM_RESERVED4

/*---------------------------------------------------------------------------*/
/*------------------------OCIConnectionpoolCreate Modes----------------------*/

#define OCI_CPOOL_REINITIALIZE              0x111
#define     DCI_CPOOL_REINITIALIZE              OCI_CPOOL_REINITIALIZE

/*---------------------------------------------------------------------------*/
/*--------------------------------- OCILogon2 Modes -------------------------*/

#define OCI_LOGON2_SPOOL                    0x0001                  /* Use session pool */
#define     DCI_LOGON2_SPOOL                    OCI_LOGON2_SPOOL
#define OCI_LOGON2_CPOOL                    OCI_CPOOL               /* Use connection pool */
#define     DCI_LOGON2_CPOOL                    OCI_LOGON2_CPOOL
#define OCI_LOGON2_STMTCACHE                0x0004                  /* Use Stmt Caching */
#define     DCI_LOGON2_STMTCACHE                OCI_LOGON2_STMTCACHE
#define OCI_LOGON2_PROXY                    0x0008                  /* Proxy authentiaction */
#define     DCI_LOGON2_PROXY                    OCI_LOGON2_PROXY

/*---------------------------------------------------------------------------*/
/*------------------------- OCISessionPoolCreate Modes ----------------------*/

#define OCI_SPC_REINITIALIZE                0x0001                  /* Reinitialize the session pool */
#define     DCI_SPC_REINITIALIZE                OCI_SPC_REINITIALIZE
#define OCI_SPC_HOMOGENEOUS                 0x0002                  /* Session pool is homogeneneous */
#define     DCI_SPC_HOMOGENEOUS                 OCI_SPC_HOMOGENEOUS
#define OCI_SPC_STMTCACHE                   0x0004                  /* Session pool has stmt cache */
#define     DCI_SPC_STMTCACHE                   OCI_SPC_STMTCACHE
#define OCI_SPC_NO_RLB                      0x0008                  /* Do not enable Runtime load balancing. */ 
#define     DCI_SPC_NO_RLB                      OCI_SPC_NO_RLB

/*---------------------------------------------------------------------------*/
/*--------------------------- OCISessionGet Modes ---------------------------*/

#define OCI_SESSGET_SPOOL                   0x0001                  /* SessionGet called in SPOOL mode */
#define     DCI_SESSGET_SPOOL                   OCI_SESSGET_SPOOL
#define OCI_SESSGET_CPOOL                   OCI_CPOOL               /* SessionGet called in CPOOL mode */
#define     DCI_SESSGET_CPOOL                   OCI_SESSGET_CPOOL
#define OCI_SESSGET_STMTCACHE               0x0004                  /* Use statement cache */
#define     DCI_SESSGET_STMTCACHE               OCI_SESSGET_STMTCACHE
#define OCI_SESSGET_CREDPROXY               0x0008                  /* SessionGet called in proxy mode */
#define     DCI_SESSGET_CREDPROXY               OCI_SESSGET_CREDPROXY
#define OCI_SESSGET_CREDEXT                 0x0010
#define     DCI_SESSGET_CREDEXT                 OCI_SESSGET_CREDEXT
#define OCI_SESSGET_SPOOL_MATCHANY          0x0020
#define     DCI_SESSGET_SPOOL_MATCHANY          OCI_SESSGET_SPOOL_MATCHANY
/*---------------------------------------------------------------------------*/
/*------------------------ATTR Values for Session Pool-----------------------*/
/* Attribute values for OCI_ATTR_SPOOL_GETMODE */
#define OCI_SPOOL_ATTRVAL_WAIT              0                       /* block till you get a session */
#define     DCI_SPOOL_ATTRVAL_WAIT              OCI_SPOOL_ATTRVAL_WAIT
#define OCI_SPOOL_ATTRVAL_NOWAIT            1                       /* error out if no session avaliable */
#define     DCI_SPOOL_ATTRVAL_NOWAIT            OCI_SPOOL_ATTRVAL_NOWAIT
#define OCI_SPOOL_ATTRVAL_FORCEGET          2                       /* get session even if max is exceeded */
#define     DCI_SPOOL_ATTRVAL_FORCEGET          OCI_SPOOL_ATTRVAL_FORCEGET

/*---------------------------------------------------------------------------*/
/*--------------------------- OCISessionRelease Modes -----------------------*/

#define OCI_SESSRLS_DROPSESS                0x0001                  /* Drop the Session */
#define     DCI_SESSRLS_DROPSESS                OCI_SESSRLS_DROPSESS
#define OCI_SESSRLS_RETAG                   0x0002                  /* Retag the session */
#define     DCI_SESSRLS_RETAG                   OCI_SESSRLS_RETAG

/*---------------------------------------------------------------------------*/
/*----------------------- OCISessionPoolDestroy Modes -----------------------*/

#define OCI_SPD_FORCE                       0x0001                  /* Force the sessions to terminate. 
                                                                       Even if there are some busy sessions close them */
#define     DCI_SPD_FORCE                       OCI_SPD_FORCE
 
/*---------------------------------------------------------------------------*/
/*----------------------------- Statement States ----------------------------*/

#define OCI_STMT_STATE_INITIALIZED          0x0001
#define     DCI_STMT_STATE_INITIALIZED          OCI_STMT_STATE_INITIALIZED
#define OCI_STMT_STATE_EXECUTED             0x0002
#define     DCI_STMT_STATE_EXECUTED             OCI_STMT_STATE_EXECUTED
#define OCI_STMT_STATE_END_OF_FETCH         0x0003
#define     DCI_STMT_STATE_END_OF_FETCH         OCI_STMT_STATE_END_OF_FETCH

/*---------------------------------------------------------------------------*/

/*----------------------------- OCIMemStats Modes ---------------------------*/
#define OCI_MEM_INIT                        0x01
#define     DCI_MEM_INIT                        OCI_MEM_INIT
#define OCI_MEM_CLN                         0x02
#define     DCI_MEM_CLN                         OCI_MEM_CLN
#define OCI_MEM_FLUSH                       0x04
#define     DCI_MEM_FLUSH                       OCI_MEM_FLUSH
#define OCI_DUMP_HEAP                       0x80
#define     DCI_DUMP_HEAP                       OCI_DUMP_HEAP

#define OCI_CLIENT_STATS                    0x10
#define     DCI_CLIENT_STATS                    OCI_CLIENT_STATS
#define OCI_SERVER_STATS                    0x20
#define     DCI_SERVER_STATS                    OCI_SERVER_STATS

/*----------------------------- OCIEnvInit Modes ----------------------------*/
/* NOTE: NO NEW MODES SHOULD BE ADDED HERE BECAUSE THE RECOMMENDED METHOD 
 * IS TO USE THE NEW OCICreateEnvironment MODES.
 */
#define OCI_ENV_NO_UCB                      0x01                    /* A user callback will not be called in OCIEnvInit() */
#define     DCI_ENV_NO_UCB                      OCI_ENV_NO_UCB
#define OCI_ENV_NO_MUTEX                    0x08                    /* the environment handle will not be protected by a mutex internally */
#define     DCI_ENV_NO_MUTEX                    OCI_ENV_NO_MUTEX

/*---------------------------------------------------------------------------*/

/*------------------------ Prepare Modes ------------------------------------*/
#define OCI_NO_SHARING                      0x01                    /* turn off statement handle sharing */
#define     DCI_NO_SHARING                      OCI_NO_SHARING
#define OCI_PREP_RESERVED_1                 0x02                    /* reserved */
#define     DCI_PREP_RESERVED_1                 OCI_PREP_RESERVED_1
#define OCI_PREP_AFC_PAD_ON                 0x04                    /* turn on blank padding for AFC */
#define     DCI_PREP_AFC_PAD_ON                 OCI_PREP_AFC_PAD_ON
#define OCI_PREP_AFC_PAD_OFF                0x08                    /* turn off blank padding for AFC */
#define     DCI_PREP_AFC_PAD_OFF                OCI_PREP_AFC_PAD_OFF
/*---------------------------------------------------------------------------*/

/*----------------------- Execution Modes -----------------------------------*/
#define OCI_BATCH_MODE                      0x01                    /* batch the oci statement for execution */
#define     DCI_BATCH_MODE                      OCI_BATCH_MODE
#define OCI_EXACT_FETCH                     0x02                    /* fetch the exact rows specified */
#define     DCI_EXACT_FETCH                     OCI_EXACT_FETCH
#define OCI_KEEP_FETCH_STATE                0x04                    /* unused */
#define     DCI_KEEP_FETCH_STATE                OCI_KEEP_FETCH_STATE
#define OCI_STMT_SCROLLABLE_READONLY        0x08                    /* if result set is scrollable */
#define     DCI_STMT_SCROLLABLE_READONLY        OCI_STMT_SCROLLABLE_READONLY
#define OCI_DESCRIBE_ONLY                   0x10                    /* only describe the statement */
#define     DCI_DESCRIBE_ONLY                   OCI_DESCRIBE_ONLY
#define OCI_COMMIT_ON_SUCCESS               0x20                    /* commit, if successful execution */
#define     DCI_COMMIT_ON_SUCCESS               OCI_COMMIT_ON_SUCCESS
#define OCI_NON_BLOCKING                    0x40                    /* non-blocking */
#define     DCI_NON_BLOCKING                    OCI_NON_BLOCKING
#define OCI_BATCH_ERRORS                    0x80                    /* batch errors in array dmls */
#define     DCI_BATCH_ERRORS                    OCI_BATCH_ERRORS
#define OCI_PARSE_ONLY                      0x100                   /* only parse the statement */
#define     DCI_PARSE_ONLY                      OCI_PARSE_ONLY
#define OCI_EXACT_FETCH_RESERVED_1          0x200                   /* reserved */
#define     DCI_EXACT_FETCH_RESERVED_1          OCI_EXACT_FETCH_RESERVED_1
#define OCI_SHOW_DML_WARNINGS               0x400                   /* return OCI_SUCCESS_WITH_INFO for delete/update w/no where clause */
#define     DCI_SHOW_DML_WARNINGS               OCI_SHOW_DML_WARNINGS
#define OCI_EXEC_RESERVED_2                 0x800                   /* reserved */
#define     DCI_EXEC_RESERVED_2                 OCI_EXEC_RESERVED_2
#define OCI_DESC_RESERVED_1                 0x1000                  /* reserved */
#define     DCI_DESC_RESERVED_1                 OCI_DESC_RESERVED_1
#define OCI_EXEC_RESERVED_3                 0x2000                  /* reserved */
#define     DCI_EXEC_RESERVED_3                 OCI_EXEC_RESERVED_3
#define OCI_EXEC_RESERVED_4                 0x4000                  /* reserved */
#define     DCI_EXEC_RESERVED_4                 OCI_EXEC_RESERVED_4

/*---------------------------------------------------------------------------*/

/*------------------------Authentication Modes-------------------------------*/
#define OCI_MIGRATE                         0x0001                  /* migratable auth context */
#define     DCI_MIGRATE                         OCI_MIGRATE
#define OCI_SYSDBA                          0x0002                  /* for SYSDBA authorization */
#define     DCI_SYSDBA                          OCI_SYSDBA
#define OCI_SYSOPER                         0x0004                  /* for SYSOPER authorization */
#define     DCI_SYSOPER                         OCI_SYSOPER
#define OCI_PRELIM_AUTH                     0x0008                  /* for preliminary authorization */
#define     DCI_PRELIM_AUTH                     OCI_PRELIM_AUTH
#define OCIP_ICACHE                         0x0010                  /* Private OCI cache mode to notify cache */
#define     DCIP_ICACHE                         OCIP_ICACHE
#define OCI_AUTH_RESERVED_1                 0x0020                  /* reserved */
#define     DCI_AUTH_RESERVED_1                 OCI_AUTH_RESERVED_1
#define OCI_STMT_CACHE                      0x0040                  /* enable OCI Stmt Caching */
#define     DCI_STMT_CACHE                      OCI_STMT_CACHE

/*---------------------------------------------------------------------------*/

/*------------------------Session End Modes----------------------------------*/
#define OCI_SESSEND_RESERVED_1              0x0001                  /* reserved */
#define     DCI_SESSEND_RESERVED_1              OCI_SESSEND_RESERVED_1
/*---------------------------------------------------------------------------*/

/*------------------------Attach Modes---------------------------------------*/

/* The following attach modes are the same as the UPI modes defined in 
 * UPIDEF.H.  Do not use these values externally.
 */

#define OCI_FASTPATH                        0x0010                  /* Attach in fast path mode */
#define     DCI_FASTPATH                        OCI_FASTPATH
#define OCI_ATCH_RESERVED_1                 0x0020                  /* reserved */
#define     DCI_ATCH_RESERVED_1                 OCI_ATCH_RESERVED_1
#define OCI_ATCH_RESERVED_2                 0x0080                  /* reserved */
#define     DCI_ATCH_RESERVED_2                 OCI_ATCH_RESERVED_2
#define OCI_ATCH_RESERVED_3                 0x0100                  /* reserved */
#define     DCI_ATCH_RESERVED_3                 OCI_ATCH_RESERVED_3
#define OCI_CPOOL                           0x0200                  /* Attach using server handle from pool */
#define     DCI_CPOOL                           OCI_CPOOL
#define OCI_ATCH_RESERVED_4                 0x0400                  /* reserved */
#define     DCI_ATCH_RESERVED_4                 OCI_ATCH_RESERVED_4

/*---------------------OCIStmtPrepare2 Modes---------------------------------*/
#define OCI_PREP2_CACHE_SEARCHONLY          0x0010                  /* ONly Search */
#define     DCI_PREP2_CACHE_SEARCHONLY          OCI_PREP2_CACHE_SEARCHONLY
#define OCI_PREP2_GET_PLSQL_WARNINGS        0x0020                  /* Get PL/SQL warnings  */
#define     DCI_PREP2_GET_PLSQL_WARNINGS        OCI_PREP2_GET_PLSQL_WARNINGS

/*---------------------OCIStmtRelease Modes----------------------------------*/
#define OCI_STRLS_CACHE_DELETE              0x0010                  /* Delete from Cache */
#define     DCI_STRLS_CACHE_DELETE              OCI_STRLS_CACHE_DELETE

/*-----------------------------End Various Modes ----------------------------*/

/*------------------------Piece Information----------------------------------*/
#define OCI_PARAM_IN                        0x01                    /* in parameter */
#define     DCI_PARAM_IN                        OCI_PARAM_IN
#define OCI_PARAM_OUT                       0x02                    /* out parameter */
#define     DCI_PARAM_OUT                       OCI_PARAM_OUT
/*---------------------------------------------------------------------------*/

/*------------------------ Transaction Start Flags --------------------------*/
/* NOTE: OCI_TRANS_JOIN and OCI_TRANS_NOMIGRATE not supported in 8.0.X       */
#define OCI_TRANS_NEW                       0x00000001              /* starts a new transaction branch */
#define     DCI_TRANS_NEW                       OCI_TRANS_NEW
#define OCI_TRANS_JOIN                      0x00000002              /* join an existing transaction */
#define     DCI_TRANS_JOIN                      OCI_TRANS_JOIN
#define OCI_TRANS_RESUME                    0x00000004              /* resume this transaction */
#define     DCI_TRANS_RESUME                    OCI_TRANS_RESUME
#define OCI_TRANS_STARTMASK                 0x000000ff
#define     DCI_TRANS_STARTMASK                 OCI_TRANS_STARTMASK

#define OCI_TRANS_READONLY                  0x00000100              /* starts a readonly transaction */
#define     DCI_TRANS_READONLY                  OCI_TRANS_READONLY
#define OCI_TRANS_READWRITE                 0x00000200              /* starts a read-write transaction */
#define     DCI_TRANS_READWRITE                 OCI_TRANS_READWRITE
#define OCI_TRANS_SERIALIZABLE              0x00000400              /* starts a serializable transaction */
#define     DCI_TRANS_SERIALIZABLE              OCI_TRANS_SERIALIZABLE
#define OCI_TRANS_ISOLMASK                  0x0000ff00
#define     DCI_TRANS_ISOLMASK                  OCI_TRANS_ISOLMASK

#define OCI_TRANS_LOOSE                     0x00010000              /* a loosely coupled branch */
#define     DCI_TRANS_LOOSE                     OCI_TRANS_LOOSE
#define OCI_TRANS_TIGHT                     0x00020000              /* a tightly coupled branch */
#define     DCI_TRANS_TIGHT                     OCI_TRANS_TIGHT
#define OCI_TRANS_TYPEMASK                  0x000f0000
#define     DCI_TRANS_TYPEMASK                  OCI_TRANS_TYPEMASK

#define OCI_TRANS_NOMIGRATE                 0x00100000              /* non migratable transaction */
#define     DCI_TRANS_NOMIGRATE                 OCI_TRANS_NOMIGRATE
#define OCI_TRANS_SEPARABLE                 0x00200000              /* separable transaction (8.1.6+) */
#define     DCI_TRANS_SEPARABLE                 OCI_TRANS_SEPARABLE

/*---------------------------------------------------------------------------*/

/*------------------------ Transaction End Flags ----------------------------*/
#define OCI_TRANS_TWOPHASE                  0x01000000              /* use two phase commit */
#define     DCI_TRANS_TWOPHASE                  OCI_TRANS_TWOPHASE
/*---------------------------------------------------------------------------*/

/*------------------------- AQ Constants ------------------------------------
 * NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 * The following constants must match the PL/SQL dbms_aq constants
 * NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 */
/* ------------------------- Visibility flags -------------------------------*/
#define OCI_ENQ_IMMEDIATE                   1                       /* enqueue is an independent transaction */
#define     DCI_ENQ_IMMEDIATE                   OCI_ENQ_IMMEDIATE
#define OCI_ENQ_ON_COMMIT                   2                       /* enqueue is part of current transaction */
#define     DCI_ENQ_ON_COMMIT                   OCI_ENQ_ON_COMMIT

/* ----------------------- Dequeue mode flags -------------------------------*/
#define OCI_DEQ_BROWSE                      1                       /* read message without acquiring a lock */
#define     DCI_DEQ_BROWSE                      OCI_DEQ_BROWSE
#define OCI_DEQ_LOCKED                      2                       /* read and obtain write lock on message */
#define     DCI_DEQ_LOCKED                      OCI_DEQ_LOCKED
#define OCI_DEQ_REMOVE                      3                       /* read the message and delete it */
#define     DCI_DEQ_REMOVE                      OCI_DEQ_REMOVE
#define OCI_DEQ_REMOVE_NODATA               4                       /* delete message w'o returning payload */
#define     DCI_DEQ_REMOVE_NODATA               OCI_DEQ_REMOVE_NODATA
#define OCI_DEQ_GETSIG                      5                       /* get signature only */
#define     DCI_DEQ_GETSIG                      OCI_DEQ_GETSIG

/* ----------------- Dequeue navigation flags -------------------------------*/
#define OCI_DEQ_FIRST_MSG                   1                       /* get first message at head of queue */
#define     DCI_DEQ_FIRST_MSG                   OCI_DEQ_FIRST_MSG
#define OCI_DEQ_NEXT_MSG                    3                       /* next message that is available */
#define     DCI_DEQ_NEXT_MSG                    OCI_DEQ_NEXT_MSG
#define OCI_DEQ_NEXT_TRANSACTION            2                       /* get first message of next txn group */
#define     DCI_DEQ_NEXT_TRANSACTION            OCI_DEQ_NEXT_TRANSACTION
#define OCI_DEQ_MULT_TRANSACTION            5                       /* array dequeue across txn groups */
#define     DCI_DEQ_MULT_TRANSACTION            OCI_DEQ_MULT_TRANSACTION

/* ----------------- Dequeue Option Reserved flags ------------------------- */
#define OCI_DEQ_RESERVED_1                  0x000001
#define     DCI_DEQ_RESERVED_1                  OCI_DEQ_RESERVED_1

/* --------------------- Message states -------------------------------------*/
#define OCI_MSG_WAITING                     1                       /* the message delay has not yet completed */
#define     DCI_MSG_WAITING                     OCI_MSG_WAITING
#define OCI_MSG_READY                       0                       /* the message is ready to be processed */
#define     DCI_MSG_READY                       OCI_MSG_READY
#define OCI_MSG_PROCESSED                   2                       /* the message has been processed */
#define     DCI_MSG_PROCESSED                   OCI_MSG_PROCESSED
#define OCI_MSG_EXPIRED                     3                       /* message has moved to exception queue */
#define     DCI_MSG_EXPIRED                     OCI_MSG_EXPIRED

/* --------------------- Sequence deviation ---------------------------------*/
#define OCI_ENQ_BEFORE                      2                       /* enqueue message before another message */
#define     DCI_ENQ_BEFORE                      OCI_ENQ_BEFORE
#define OCI_ENQ_TOP                         3                       /* enqueue message before all messages */
#define     DCI_ENQ_TOP                         OCI_ENQ_TOP

/* ------------------------- Visibility flags -------------------------------*/
#define OCI_DEQ_IMMEDIATE                   1                       /* dequeue is an independent transaction */
#define     DCI_DEQ_IMMEDIATE                   OCI_DEQ_IMMEDIATE
#define OCI_DEQ_ON_COMMIT                   2                       /* dequeue is part of current transaction */
#define     DCI_DEQ_ON_COMMIT                   OCI_DEQ_ON_COMMIT

/* ------------------------ Wait --------------------------------------------*/
#define OCI_DEQ_WAIT_FOREVER                -1                      /* wait forever if no message available */
#define     DCI_DEQ_WAIT_FOREVER                OCI_DEQ_WAIT_FOREVER
#define OCI_DEQ_NO_WAIT                     0                       /* do not wait if no message is available */
#define     DCI_DEQ_NO_WAIT                     OCI_DEQ_NO_WAIT

/* ------------------------ Delay -------------------------------------------*/
#define OCI_MSG_NO_DELAY                    0                       /* message is available immediately */
#define     DCI_MSG_NO_DELAY                    OCI_MSG_NO_DELAY

/* ------------------------- Expiration -------------------------------------*/
#define OCI_MSG_NO_EXPIRATION               -1                      /* message will never expire */
#define     DCI_MSG_NO_EXPIRATION               OCI_MSG_NO_EXPIRATION

/* ------------------------- Reserved ---------------------------------------*/
#define OCI_AQ_RESERVED_1                   0x0002
#define     DCI_AQ_RESERVED_1                   OCI_AQ_RESERVED_1
#define OCI_AQ_RESERVED_2                   0x0004
#define     DCI_AQ_RESERVED_2                   OCI_AQ_RESERVED_2
#define OCI_AQ_RESERVED_3                   0x0008
#define     DCI_AQ_RESERVED_3                   OCI_AQ_RESERVED_3

/* -------------------------- END AQ Constants ----------------------------- */

/*-----------------------Object Types----------------------------------------*/
/*-----------Object Types **** Not to be Used **** --------------------------*/
/* Deprecated */
#define OCI_OTYPE_UNK                       0
#define     DCI_OTYPE_UNK                       OCI_OTYPE_UNK
#define OCI_OTYPE_TABLE                     1
#define     DCI_OTYPE_TABLE                     OCI_OTYPE_TABLE
#define OCI_OTYPE_VIEW                      2
#define     DCI_OTYPE_VIEW                      OCI_OTYPE_VIEW
#define OCI_OTYPE_SYN                       3
#define     DCI_OTYPE_SYN                       OCI_OTYPE_SYN
#define OCI_OTYPE_PROC                      4
#define     DCI_OTYPE_PROC                      OCI_OTYPE_PROC
#define OCI_OTYPE_FUNC                      5
#define     DCI_OTYPE_FUNC                      OCI_OTYPE_FUNC
#define OCI_OTYPE_PKG                       6
#define     DCI_OTYPE_PKG                       OCI_OTYPE_PKG
#define OCI_OTYPE_STMT                      7
#define     DCI_OTYPE_STMT                      OCI_OTYPE_STMT
/*---------------------------------------------------------------------------*/

/*=======================Describe Handle Parameter Attributes ===============*/
/* 
   These attributes are orthogonal to the other set of attributes defined 
   above.  These attrubutes are tobe used only for the desscribe handle 
*/
/*===========================================================================*/
/* Attributes common to Columns and Stored Procs */
#define OCI_ATTR_DATA_SIZE                  1                       /* maximum size of the data */
#define     DCI_ATTR_DATA_SIZE                  OCI_ATTR_DATA_SIZE
#define OCI_ATTR_DATA_TYPE                  2                       /* the SQL type of the column/argument */
#define     DCI_ATTR_DATA_TYPE                  OCI_ATTR_DATA_TYPE
#define OCI_ATTR_DISP_SIZE                  3                       /* the display size */
#define     DCI_ATTR_DISP_SIZE                  OCI_ATTR_DISP_SIZE
#define OCI_ATTR_NAME                       4                       /* the name of the column/argument */
#define     DCI_ATTR_NAME                       OCI_ATTR_NAME
#define OCI_ATTR_PRECISION                  5                       /* precision if number type */
#define     DCI_ATTR_PRECISION                  OCI_ATTR_PRECISION
#define OCI_ATTR_SCALE                      6                       /* scale if number type */
#define     DCI_ATTR_SCALE                      OCI_ATTR_SCALE
#define OCI_ATTR_IS_NULL                    7                       /* is it null ? */
#define     DCI_ATTR_IS_NULL                    OCI_ATTR_IS_NULL
#define OCI_ATTR_TYPE_NAME                  8                       /* name of the named data type or a package name for package private types */
#define     DCI_ATTR_TYPE_NAME                  OCI_ATTR_TYPE_NAME
#define OCI_ATTR_SCHEMA_NAME                9                       /* the schema name */
#define     DCI_ATTR_SCHEMA_NAME                OCI_ATTR_SCHEMA_NAME
#define OCI_ATTR_SUB_NAME                   10                      /* type name if package private type */
#define     DCI_ATTR_SUB_NAME                   OCI_ATTR_SUB_NAME
#define OCI_ATTR_POSITION                   11                      /* relative position of col/arg in the list of cols/args */
#define     DCI_ATTR_POSITION                   OCI_ATTR_POSITION
/* complex object retrieval parameter attributes */
#define OCI_ATTR_COMPLEXOBJECTCOMP_TYPE     50
#define     DCI_ATTR_COMPLEXOBJECTCOMP_TYPE     OCI_ATTR_COMPLEXOBJECTCOMP_TYPE
#define OCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL   51
#define     DCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL   OCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL
#define OCI_ATTR_COMPLEXOBJECT_LEVEL        52
#define     DCI_ATTR_COMPLEXOBJECT_LEVEL        OCI_ATTR_COMPLEXOBJECT_LEVEL
#define OCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE   53
#define     DCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE   OCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE

/* Only Columns */
#define OCI_ATTR_DISP_NAME                  100                     /* the display name */
#define     DCI_ATTR_DISP_NAME                  OCI_ATTR_DISP_NAME
#define OCI_ATTR_ENCC_SIZE                  101                     /* encrypted data size */
#define     DCI_ATTR_ENCC_SIZE                  OCI_ATTR_ENCC_SIZE
#define OCI_ATTR_COL_ENC                    102                     /* column is encrypted ? */
#define     DCI_ATTR_COL_ENC                    OCI_ATTR_COL_ENC
#define OCI_ATTR_COL_ENC_SALT               103                     /* is encrypted column salted ? */
#define     DCI_ATTR_COL_ENC_SALT               OCI_ATTR_COL_ENC_SALT

/*Only Stored Procs */
#define OCI_ATTR_OVERLOAD                   210                     /* is this position overloaded */
#define     DCI_ATTR_OVERLOAD                   OCI_ATTR_OVERLOAD
#define OCI_ATTR_LEVEL                      211                     /* level for structured types */
#define     DCI_ATTR_LEVEL                      OCI_ATTR_LEVEL
#define OCI_ATTR_HAS_DEFAULT                212                     /* has a default value */
#define     DCI_ATTR_HAS_DEFAULT                OCI_ATTR_HAS_DEFAULT
#define OCI_ATTR_IOMODE                     213                     /* in, out inout */
#define     DCI_ATTR_IOMODE                     OCI_ATTR_IOMODE
#define OCI_ATTR_RADIX                      214                     /* returns a radix */
#define     DCI_ATTR_RADIX                      OCI_ATTR_RADIX
#define OCI_ATTR_NUM_ARGS                   215                     /* total number of arguments */
#define     DCI_ATTR_NUM_ARGS                   OCI_ATTR_NUM_ARGS

/* only named type attributes */
#define OCI_ATTR_TYPECODE                   216                     /* object or collection */
#define     DCI_ATTR_TYPECODE                   OCI_ATTR_TYPECODE
#define OCI_ATTR_COLLECTION_TYPECODE        217                     /* varray or nested table */
#define     DCI_ATTR_COLLECTION_TYPECODE        OCI_ATTR_COLLECTION_TYPECODE
#define OCI_ATTR_VERSION                    218                     /* user assigned version */
#define     DCI_ATTR_VERSION                    OCI_ATTR_VERSION
#define OCI_ATTR_IS_INCOMPLETE_TYPE         219                     /* is this an incomplete type */
#define     DCI_ATTR_IS_INCOMPLETE_TYPE         OCI_ATTR_IS_INCOMPLETE_TYPE
#define OCI_ATTR_IS_SYSTEM_TYPE             220                     /* a system type */
#define     DCI_ATTR_IS_SYSTEM_TYPE             OCI_ATTR_IS_SYSTEM_TYPE
#define OCI_ATTR_IS_PREDEFINED_TYPE         221                     /* a predefined type */
#define     DCI_ATTR_IS_PREDEFINED_TYPE         OCI_ATTR_IS_PREDEFINED_TYPE
#define OCI_ATTR_IS_TRANSIENT_TYPE          222                     /* a transient type */
#define     DCI_ATTR_IS_TRANSIENT_TYPE          OCI_ATTR_IS_TRANSIENT_TYPE
#define OCI_ATTR_IS_SYSTEM_GENERATED_TYPE   223                     /* system generated type */
#define     DCI_ATTR_IS_SYSTEM_GENERATED_TYPE   OCI_ATTR_IS_SYSTEM_GENERATED_TYPE
#define OCI_ATTR_HAS_NESTED_TABLE           224                     /* contains nested table attr */
#define     DCI_ATTR_HAS_NESTED_TABLE           OCI_ATTR_HAS_NESTED_TABLE
#define OCI_ATTR_HAS_LOB                    225                     /* has a lob attribute */
#define     DCI_ATTR_HAS_LOB                    OCI_ATTR_HAS_LOB
#define OCI_ATTR_HAS_FILE                   226                     /* has a file attribute */
#define     DCI_ATTR_HAS_FILE                   OCI_ATTR_HAS_FILE
#define OCI_ATTR_COLLECTION_ELEMENT         227                     /* has a collection attribute */
#define     DCI_ATTR_COLLECTION_ELEMENT         OCI_ATTR_COLLECTION_ELEMENT
#define OCI_ATTR_NUM_TYPE_ATTRS             228                     /* number of attribute types */
#define     DCI_ATTR_NUM_TYPE_ATTRS             OCI_ATTR_NUM_TYPE_ATTRS
#define OCI_ATTR_LIST_TYPE_ATTRS            229                     /* list of type attributes */
#define     DCI_ATTR_LIST_TYPE_ATTRS            OCI_ATTR_LIST_TYPE_ATTRS
#define OCI_ATTR_NUM_TYPE_METHODS           230                     /* number of type methods */
#define     DCI_ATTR_NUM_TYPE_METHODS           OCI_ATTR_NUM_TYPE_METHODS
#define OCI_ATTR_LIST_TYPE_METHODS          231                     /* list of type methods */
#define     DCI_ATTR_LIST_TYPE_METHODS          OCI_ATTR_LIST_TYPE_METHODS
#define OCI_ATTR_MAP_METHOD                 232                     /* map method of type */
#define     DCI_ATTR_MAP_METHOD                 OCI_ATTR_MAP_METHOD
#define OCI_ATTR_ORDER_METHOD               233                     /* order method of type */
#define     DCI_ATTR_ORDER_METHOD               OCI_ATTR_ORDER_METHOD

/* only collection element */
#define OCI_ATTR_NUM_ELEMS                  234                     /* number of elements */
#define     DCI_ATTR_NUM_ELEMS                  OCI_ATTR_NUM_ELEMS

/* only type methods */
#define OCI_ATTR_ENCAPSULATION              235                     /* encapsulation level */
#define     DCI_ATTR_ENCAPSULATION              OCI_ATTR_ENCAPSULATION
#define OCI_ATTR_IS_SELFISH                 236                     /* method selfish */
#define     DCI_ATTR_IS_SELFISH                 OCI_ATTR_IS_SELFISH
#define OCI_ATTR_IS_VIRTUAL                 237                     /* virtual */
#define     DCI_ATTR_IS_VIRTUAL                 OCI_ATTR_IS_VIRTUAL
#define OCI_ATTR_IS_INLINE                  238                     /* inline */
#define     DCI_ATTR_IS_INLINE                  OCI_ATTR_IS_INLINE
#define OCI_ATTR_IS_CONSTANT                239                     /* constant */
#define     DCI_ATTR_IS_CONSTANT                OCI_ATTR_IS_CONSTANT
#define OCI_ATTR_HAS_RESULT                 240                     /* has result */
#define     DCI_ATTR_HAS_RESULT                 OCI_ATTR_HAS_RESULT
#define OCI_ATTR_IS_CONSTRUCTOR             241                     /* constructor */
#define     DCI_ATTR_IS_CONSTRUCTOR             OCI_ATTR_IS_CONSTRUCTOR
#define OCI_ATTR_IS_DESTRUCTOR              242                     /* destructor */
#define     DCI_ATTR_IS_DESTRUCTOR              OCI_ATTR_IS_DESTRUCTOR
#define OCI_ATTR_IS_OPERATOR                243                     /* operator */
#define     DCI_ATTR_IS_OPERATOR                OCI_ATTR_IS_OPERATOR
#define OCI_ATTR_IS_MAP                     244                     /* a map method */
#define     DCI_ATTR_IS_MAP                     OCI_ATTR_IS_MAP
#define OCI_ATTR_IS_ORDER                   245                     /* order method */
#define     DCI_ATTR_IS_ORDER                   OCI_ATTR_IS_ORDER
#define OCI_ATTR_IS_RNDS                    246                     /* read no data state method */
#define     DCI_ATTR_IS_RNDS                    OCI_ATTR_IS_RNDS
#define OCI_ATTR_IS_RNPS                    247                     /* read no process state */
#define     DCI_ATTR_IS_RNPS                    OCI_ATTR_IS_RNPS
#define OCI_ATTR_IS_WNDS                    248                     /* write no data state method */
#define     DCI_ATTR_IS_WNDS                    OCI_ATTR_IS_WNDS
#define OCI_ATTR_IS_WNPS                    249                     /* write no process state */
#define     DCI_ATTR_IS_WNPS                    OCI_ATTR_IS_WNPS

#define OCI_ATTR_DESC_PUBLIC                250                     /* public object */
#define     DCI_ATTR_DESC_PUBLIC                OCI_ATTR_DESC_PUBLIC

/* Object Cache Enhancements : attributes for User Constructed Instances     */
#define OCI_ATTR_CACHE_CLIENT_CONTEXT       251
#define     DCI_ATTR_CACHE_CLIENT_CONTEXT       OCI_ATTR_CACHE_CLIENT_CONTEXT
#define OCI_ATTR_UCI_CONSTRUCT              252
#define     DCI_ATTR_UCI_CONSTRUCT              OCI_ATTR_UCI_CONSTRUCT
#define OCI_ATTR_UCI_DESTRUCT               253
#define     DCI_ATTR_UCI_DESTRUCT               OCI_ATTR_UCI_DESTRUCT
#define OCI_ATTR_UCI_COPY                   254
#define     DCI_ATTR_UCI_COPY                   OCI_ATTR_UCI_COPY
#define OCI_ATTR_UCI_PICKLE                 255
#define     DCI_ATTR_UCI_PICKLE                 OCI_ATTR_UCI_PICKLE
#define OCI_ATTR_UCI_UNPICKLE               256
#define     DCI_ATTR_UCI_UNPICKLE               OCI_ATTR_UCI_UNPICKLE
#define OCI_ATTR_UCI_REFRESH                257
#define     DCI_ATTR_UCI_REFRESH                OCI_ATTR_UCI_REFRESH

/* for type inheritance */
#define OCI_ATTR_IS_SUBTYPE                 258
#define     DCI_ATTR_IS_SUBTYPE                 OCI_ATTR_IS_SUBTYPE
#define OCI_ATTR_SUPERTYPE_SCHEMA_NAME      259
#define     DCI_ATTR_SUPERTYPE_SCHEMA_NAME      OCI_ATTR_SUPERTYPE_SCHEMA_NAME
#define OCI_ATTR_SUPERTYPE_NAME             260
#define     DCI_ATTR_SUPERTYPE_NAME             OCI_ATTR_SUPERTYPE_NAME

/* for schemas */
#define OCI_ATTR_LIST_OBJECTS               261                     /* list of objects in schema */
#define     DCI_ATTR_LIST_OBJECTS               OCI_ATTR_LIST_OBJECTS

/* for database */
#define OCI_ATTR_NCHARSET_ID                262                     /* char set id */
#define     DCI_ATTR_NCHARSET_ID                OCI_ATTR_NCHARSET_ID
#define OCI_ATTR_LIST_SCHEMAS               263                     /* list of schemas */
#define     DCI_ATTR_LIST_SCHEMAS               OCI_ATTR_LIST_SCHEMAS
#define OCI_ATTR_MAX_PROC_LEN               264                     /* max procedure length */
#define     DCI_ATTR_MAX_PROC_LEN               OCI_ATTR_MAX_PROC_LEN
#define OCI_ATTR_MAX_COLUMN_LEN             265                     /* max column name length */
#define     DCI_ATTR_MAX_COLUMN_LEN             OCI_ATTR_MAX_COLUMN_LEN
#define OCI_ATTR_CURSOR_COMMIT_BEHAVIOR     266                     /* cursor commit behavior */
#define     DCI_ATTR_CURSOR_COMMIT_BEHAVIOR     OCI_ATTR_CURSOR_COMMIT_BEHAVIOR
#define OCI_ATTR_MAX_CATALOG_NAMELEN        267                     /* catalog namelength */
#define     DCI_ATTR_MAX_CATALOG_NAMELEN        OCI_ATTR_MAX_CATALOG_NAMELEN
#define OCI_ATTR_CATALOG_LOCATION           268                     /* catalog location */
#define     DCI_ATTR_CATALOG_LOCATION           OCI_ATTR_CATALOG_LOCATION
#define OCI_ATTR_SAVEPOINT_SUPPORT          269                     /* savepoint support */
#define     DCI_ATTR_SAVEPOINT_SUPPORT          OCI_ATTR_SAVEPOINT_SUPPORT
#define OCI_ATTR_NOWAIT_SUPPORT             270                     /* nowait support */
#define     DCI_ATTR_NOWAIT_SUPPORT             OCI_ATTR_NOWAIT_SUPPORT
#define OCI_ATTR_AUTOCOMMIT_DDL             271                     /* autocommit DDL */
#define     DCI_ATTR_AUTOCOMMIT_DDL             OCI_ATTR_AUTOCOMMIT_DDL
#define OCI_ATTR_LOCKING_MODE               272                     /* locking mode */
#define     DCI_ATTR_LOCKING_MODE               OCI_ATTR_LOCKING_MODE

/* for externally initialized context */
#define OCI_ATTR_APPCTX_SIZE                273                     /* count of context to be init*/
#define     DCI_ATTR_APPCTX_SIZE                OCI_ATTR_APPCTX_SIZE
#define OCI_ATTR_APPCTX_LIST                274                     /* count of context to be init*/
#define     DCI_ATTR_APPCTX_LIST                OCI_ATTR_APPCTX_LIST
#define OCI_ATTR_APPCTX_NAME                275                     /* name  of context to be init*/
#define     DCI_ATTR_APPCTX_NAME                OCI_ATTR_APPCTX_NAME
#define OCI_ATTR_APPCTX_ATTR                276                     /* attr  of context to be init*/
#define     DCI_ATTR_APPCTX_ATTR                OCI_ATTR_APPCTX_ATTR
#define OCI_ATTR_APPCTX_VALUE               277                     /* value of context to be init*/
#define     DCI_ATTR_APPCTX_VALUE               OCI_ATTR_APPCTX_VALUE

/* for client id propagation */
#define OCI_ATTR_CLIENT_IDENTIFIER          278                     /* value of client id to set*/
#define     DCI_ATTR_CLIENT_IDENTIFIER          OCI_ATTR_CLIENT_IDENTIFIER

/* for inheritance - part 2 */
#define OCI_ATTR_IS_FINAL_TYPE              279                     /* is final type ? */
#define     DCI_ATTR_IS_FINAL_TYPE              OCI_ATTR_IS_FINAL_TYPE
#define OCI_ATTR_IS_INSTANTIABLE_TYPE       280                     /* is instantiable type ? */
#define     DCI_ATTR_IS_INSTANTIABLE_TYPE       OCI_ATTR_IS_INSTANTIABLE_TYPE
#define OCI_ATTR_IS_FINAL_METHOD            281                     /* is final method ? */
#define     DCI_ATTR_IS_FINAL_METHOD            OCI_ATTR_IS_FINAL_METHOD
#define OCI_ATTR_IS_INSTANTIABLE_METHOD     282                     /* is instantiable method ? */
#define     DCI_ATTR_IS_INSTANTIABLE_METHOD     OCI_ATTR_IS_INSTANTIABLE_METHOD
#define OCI_ATTR_IS_OVERRIDING_METHOD       283                     /* is overriding method ? */
#define     DCI_ATTR_IS_OVERRIDING_METHOD       OCI_ATTR_IS_OVERRIDING_METHOD

/* slot 284 available */

#define OCI_ATTR_CHAR_USED                  285                     /* char length semantics */
#define     DCI_ATTR_CHAR_USED                  OCI_ATTR_CHAR_USED
#define OCI_ATTR_CHAR_SIZE                  286                     /* char length */
#define     DCI_ATTR_CHAR_SIZE                  OCI_ATTR_CHAR_SIZE

/* SQLJ support */
#define OCI_ATTR_IS_JAVA_TYPE               287                     /* is java implemented type ? */
#define     DCI_ATTR_IS_JAVA_TYPE               OCI_ATTR_IS_JAVA_TYPE

/* N-Tier support */
#define OCI_ATTR_DISTINGUISHED_NAME         300                     /* use DN as user name */
#define     DCI_ATTR_DISTINGUISHED_NAME         OCI_ATTR_DISTINGUISHED_NAME
#define OCI_ATTR_KERBEROS_TICKET            301                     /* Kerberos ticket as cred. */
#define     DCI_ATTR_KERBEROS_TICKET            OCI_ATTR_KERBEROS_TICKET
 
/* for multilanguage debugging */
#define OCI_ATTR_ORA_DEBUG_JDWP             302                     /* ORA_DEBUG_JDWP attribute */
#define     DCI_ATTR_ORA_DEBUG_JDWP             OCI_ATTR_ORA_DEBUG_JDWP

#define OCI_ATTR_RESERVED_14                303                     /* reserved */
#define     DCI_ATTR_RESERVED_14                OCI_ATTR_RESERVED_14

/* TDE attributes on the Table */
#define OCI_ATTR_TABLE_ENC                  417                     /* does table have any encrypt columns */
#define     DCI_ATTR_TABLE_ENC                  OCI_ATTR_TABLE_ENC
#define OCI_ATTR_TABLE_ENC_ALG              418                     /* Table encryption Algorithm */
#define     DCI_ATTR_TABLE_ENC_ALG              OCI_ATTR_TABLE_ENC_ALG
#define OCI_ATTR_TABLE_ENC_ALG_ID           419                     /* Internal Id of encryption Algorithm*/
#define     DCI_ATTR_TABLE_ENC_ALG_ID           OCI_ATTR_TABLE_ENC_ALG_ID

/*---------------------------End Describe Handle Attributes -----------------*/

/*------------- Supported Values for Direct Path Date cache -----------------*/
#define OCI_ATTR_DIRPATH_DCACHE_NUM         303                     /* date cache entries */
#define     DCI_ATTR_DIRPATH_DCACHE_NUM         OCI_ATTR_DIRPATH_DCACHE_NUM
#define OCI_ATTR_DIRPATH_DCACHE_SIZE        304                     /* date cache limit */
#define     DCI_ATTR_DIRPATH_DCACHE_SIZE        OCI_ATTR_DIRPATH_DCACHE_SIZE
#define OCI_ATTR_DIRPATH_DCACHE_MISSES      305                     /* date cache misses */
#define     DCI_ATTR_DIRPATH_DCACHE_MISSES      OCI_ATTR_DIRPATH_DCACHE_MISSES
#define OCI_ATTR_DIRPATH_DCACHE_HITS        306                     /* date cache hits */
#define     DCI_ATTR_DIRPATH_DCACHE_HITS        OCI_ATTR_DIRPATH_DCACHE_HITS
#define OCI_ATTR_DIRPATH_DCACHE_DISABLE     307                     /* on set: disable datecache 
                                                                     * on overflow.
                                                                     * on get: datecache disabled? 
                                                                     * could be due to overflow
                                                                     * or others                  */
#define     DCI_ATTR_DIRPATH_DCACHE_DISABLE     OCI_ATTR_DIRPATH_DCACHE_DISABLE

/* ----------------------- Session Pool Attributes ------------------------- */
#define OCI_ATTR_SPOOL_TIMEOUT              308                     /* session timeout */
#define     DCI_ATTR_SPOOL_TIMEOUT              OCI_ATTR_SPOOL_TIMEOUT
#define OCI_ATTR_SPOOL_GETMODE              309                     /* session get mode */
#define     DCI_ATTR_SPOOL_GETMODE              OCI_ATTR_SPOOL_GETMODE
#define OCI_ATTR_SPOOL_BUSY_COUNT           310                     /* busy session count */
#define     DCI_ATTR_SPOOL_BUSY_COUNT           OCI_ATTR_SPOOL_BUSY_COUNT
#define OCI_ATTR_SPOOL_OPEN_COUNT           311                     /* open session count */
#define     DCI_ATTR_SPOOL_OPEN_COUNT           OCI_ATTR_SPOOL_OPEN_COUNT
#define OCI_ATTR_SPOOL_MIN                  312                     /* min session count */
#define     DCI_ATTR_SPOOL_MIN                  OCI_ATTR_SPOOL_MIN
#define OCI_ATTR_SPOOL_MAX                  313                     /* max session count */
#define     DCI_ATTR_SPOOL_MAX                  OCI_ATTR_SPOOL_MAX
#define OCI_ATTR_SPOOL_INCR                 314                     /* session increment count */
#define     DCI_ATTR_SPOOL_INCR                 OCI_ATTR_SPOOL_INCR
#define OCI_ATTR_SPOOL_STMTCACHESIZE        208                     /*Stmt cache size of pool  */
#define     DCI_ATTR_SPOOL_STMTCACHESIZE        OCI_ATTR_SPOOL_STMTCACHESIZE
/*------------------------------End Session Pool Attributes -----------------*/
/*---------------------------- For XML Types ------------------------------- */
/* For table, view and column */
#define OCI_ATTR_IS_XMLTYPE                 315                     /* Is the type an XML type? */
#define     DCI_ATTR_IS_XMLTYPE                 OCI_ATTR_IS_XMLTYPE
#define OCI_ATTR_XMLSCHEMA_NAME             316                     /* Name of XML Schema */
#define     DCI_ATTR_XMLSCHEMA_NAME             OCI_ATTR_XMLSCHEMA_NAME
#define OCI_ATTR_XMLELEMENT_NAME            317                     /* Name of XML Element */
#define     DCI_ATTR_XMLELEMENT_NAME            OCI_ATTR_XMLELEMENT_NAME
#define OCI_ATTR_XMLSQLTYPSCH_NAME          318                     /* SQL type's schema for XML Ele */
#define     DCI_ATTR_XMLSQLTYPSCH_NAME          OCI_ATTR_XMLSQLTYPSCH_NAME
#define OCI_ATTR_XMLSQLTYPE_NAME            319                     /* Name of SQL type for XML Ele */
#define     DCI_ATTR_XMLSQLTYPE_NAME            OCI_ATTR_XMLSQLTYPE_NAME
#define OCI_ATTR_XMLTYPE_STORED_OBJ         320                     /* XML type stored as object? */
#define     DCI_ATTR_XMLTYPE_STORED_OBJ         OCI_ATTR_XMLTYPE_STORED_OBJ

/*---------------------------- For Subtypes ------------------------------- */
/* For type */
#define OCI_ATTR_HAS_SUBTYPES               321                     /* Has subtypes? */
#define     DCI_ATTR_HAS_SUBTYPES               OCI_ATTR_HAS_SUBTYPES
#define OCI_ATTR_NUM_SUBTYPES               322                     /* Number of subtypes */
#define     DCI_ATTR_NUM_SUBTYPES               OCI_ATTR_NUM_SUBTYPES
#define OCI_ATTR_LIST_SUBTYPES              323                     /* List of subtypes */
#define     DCI_ATTR_LIST_SUBTYPES              OCI_ATTR_LIST_SUBTYPES

/* XML flag */
#define OCI_ATTR_XML_HRCHY_ENABLED          324                     /* hierarchy enabled? */
#define     DCI_ATTR_XML_HRCHY_ENABLED          OCI_ATTR_XML_HRCHY_ENABLED

/* Method flag */
#define OCI_ATTR_IS_OVERRIDDEN_METHOD       325                     /* Method is overridden? */
#define     DCI_ATTR_IS_OVERRIDDEN_METHOD       OCI_ATTR_IS_OVERRIDDEN_METHOD

/*------------- Attributes for 10i Updates to the DirPath API ---------------*/
#define OCI_ATTR_DIRPATH_RESERVED_7         326                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_7         OCI_ATTR_DIRPATH_RESERVED_7
#define OCI_ATTR_DIRPATH_RESERVED_8         327                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_8         OCI_ATTR_DIRPATH_RESERVED_8
#define OCI_ATTR_DIRPATH_CONVERT            328                     /* stream conversion needed? */
#define     DCI_ATTR_DIRPATH_CONVERT            OCI_ATTR_DIRPATH_CONVERT
#define OCI_ATTR_DIRPATH_BADROW             329                     /* info about bad row */
#define     DCI_ATTR_DIRPATH_BADROW             OCI_ATTR_DIRPATH_BADROW
#define OCI_ATTR_DIRPATH_BADROW_LENGTH      330                     /* length of bad row info */
#define     DCI_ATTR_DIRPATH_BADROW_LENGTH      OCI_ATTR_DIRPATH_BADROW_LENGTH
#define OCI_ATTR_DIRPATH_WRITE_ORDER        331                     /* column fill order */
#define     DCI_ATTR_DIRPATH_WRITE_ORDER        OCI_ATTR_DIRPATH_WRITE_ORDER
#define OCI_ATTR_DIRPATH_GRANULE_SIZE       332                     /* granule size for unload */
#define     DCI_ATTR_DIRPATH_GRANULE_SIZE       OCI_ATTR_DIRPATH_GRANULE_SIZE
#define OCI_ATTR_DIRPATH_GRANULE_OFFSET     333                     /* offset to last granule */
#define     DCI_ATTR_DIRPATH_GRANULE_OFFSET     OCI_ATTR_DIRPATH_GRANULE_OFFSET
#define OCI_ATTR_DIRPATH_RESERVED_1         334                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_1         OCI_ATTR_DIRPATH_RESERVED_1
#define OCI_ATTR_DIRPATH_RESERVED_2         335                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_2         OCI_ATTR_DIRPATH_RESERVED_2

/*------------- Attributes for 10i Distributed Objects ----------------------*/
#define OCI_ATTR_OBJ_SUBS                   336                     /* obj col/tab substitutable */
#define     DCI_ATTR_OBJ_SUBS                   OCI_ATTR_OBJ_SUBS

/*------ Attributes for 10i DirPathAPI conversion (NLS lang, terr, cs) ------*/
#define OCI_ATTR_DIRPATH_RESERVED_3         337                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_3         OCI_ATTR_DIRPATH_RESERVED_3
#define OCI_ATTR_DIRPATH_RESERVED_4         338                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_4         OCI_ATTR_DIRPATH_RESERVED_4


/*---------- Attributes for 10i XADFIELD (NLS language, territory -----------*/
#define OCI_ATTR_XADFIELD_RESERVED_1        339                     /* reserved */
#define     DCI_ATTR_XADFIELD_RESERVED_1        OCI_ATTR_XADFIELD_RESERVED_1
#define OCI_ATTR_XADFIELD_RESERVED_2        340                     /* reserved */
#define     DCI_ATTR_XADFIELD_RESERVED_2        OCI_ATTR_XADFIELD_RESERVED_2
/*------------- Kerberos Secure Client Identifier ---------------------------*/
#define OCI_ATTR_KERBEROS_CID               341                     /* Kerberos db service ticket*/
#define     DCI_ATTR_KERBEROS_CID               OCI_ATTR_KERBEROS_CID


/*------------------------ Attributes for Rules objects ---------------------*/
#define OCI_ATTR_CONDITION                  342                     /* rule condition */
#define     DCI_ATTR_CONDITION                  OCI_ATTR_CONDITION
#define OCI_ATTR_COMMENT                    343                     /* comment */
#define     DCI_ATTR_COMMENT                    OCI_ATTR_COMMENT
#define OCI_ATTR_VALUE                      344                     /* Anydata value */
#define     DCI_ATTR_VALUE                      OCI_ATTR_VALUE
#define OCI_ATTR_EVAL_CONTEXT_OWNER         345                     /* eval context owner */
#define     DCI_ATTR_EVAL_CONTEXT_OWNER         OCI_ATTR_EVAL_CONTEXT_OWNER
#define OCI_ATTR_EVAL_CONTEXT_NAME          346                     /* eval context name */
#define     DCI_ATTR_EVAL_CONTEXT_NAME          OCI_ATTR_EVAL_CONTEXT_NAME
#define OCI_ATTR_EVALUATION_FUNCTION        347                     /* eval function name */
#define     DCI_ATTR_EVALUATION_FUNCTION        OCI_ATTR_EVALUATION_FUNCTION
#define OCI_ATTR_VAR_TYPE                   348                     /* variable type */
#define     DCI_ATTR_VAR_TYPE                   OCI_ATTR_VAR_TYPE
#define OCI_ATTR_VAR_VALUE_FUNCTION         349                     /* variable value function */
#define     DCI_ATTR_VAR_VALUE_FUNCTION         OCI_ATTR_VAR_VALUE_FUNCTION
#define OCI_ATTR_VAR_METHOD_FUNCTION        350                     /* variable method function */
#define     DCI_ATTR_VAR_METHOD_FUNCTION        OCI_ATTR_VAR_METHOD_FUNCTION
#define OCI_ATTR_ACTION_CONTEXT             351                     /* action context */
#define     DCI_ATTR_ACTION_CONTEXT             OCI_ATTR_ACTION_CONTEXT
#define OCI_ATTR_LIST_TABLE_ALIASES         352                     /* list of table aliases */
#define     DCI_ATTR_LIST_TABLE_ALIASES         OCI_ATTR_LIST_TABLE_ALIASES
#define OCI_ATTR_LIST_VARIABLE_TYPES        353                     /* list of variable types */
#define     DCI_ATTR_LIST_VARIABLE_TYPES        OCI_ATTR_LIST_VARIABLE_TYPES
#define OCI_ATTR_TABLE_NAME                 356                     /* table name */
#define     DCI_ATTR_TABLE_NAME                 OCI_ATTR_TABLE_NAME

#define OCI_ATTR_DIRPATH_RESERVED_5         357                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_5         OCI_ATTR_DIRPATH_RESERVED_5
#define OCI_ATTR_DIRPATH_RESERVED_6         358                     /* reserved */
#define     DCI_ATTR_DIRPATH_RESERVED_6         OCI_ATTR_DIRPATH_RESERVED_6

#define OCI_ATTR_DIRPATH_LOCK_WAIT          359                     /* wait for lock in dpapi */
#define     DCI_ATTR_DIRPATH_LOCK_WAIT          OCI_ATTR_DIRPATH_LOCK_WAIT

#define OCI_ATTR_MESSAGE_CSCN               360                     /* message cscn */
#define     DCI_ATTR_MESSAGE_CSCN               OCI_ATTR_MESSAGE_CSCN
#define OCI_ATTR_MESSAGE_DSCN               361                     /* message dscn */
#define     DCI_ATTR_MESSAGE_DSCN               OCI_ATTR_MESSAGE_DSCN

/*--------------------- Audit Session ID ------------------------------------*/
#define OCI_ATTR_AUDIT_SESSION_ID           362                     /* Audit session ID */
#define     DCI_ATTR_AUDIT_SESSION_ID           OCI_ATTR_AUDIT_SESSION_ID

/*--------------------- Kerberos TGT Keys -----------------------------------*/
#define OCI_ATTR_KERBEROS_KEY               363                     /* n-tier Kerberos cred key */
#define     DCI_ATTR_KERBEROS_KEY               OCI_ATTR_KERBEROS_KEY
#define OCI_ATTR_KERBEROS_CID_KEY           364                     /* SCID Kerberos cred key */
#define     DCI_ATTR_KERBEROS_CID_KEY           OCI_ATTR_KERBEROS_CID_KEY


#define OCI_ATTR_TRANSACTION_NO             365                     /* AQ enq txn number */
#define     DCI_ATTR_TRANSACTION_NO             OCI_ATTR_TRANSACTION_NO

/*----------------------- Attributes for End To End Tracing -----------------*/
#define OCI_ATTR_MODULE                     366                     /* module for tracing */
#define     DCI_ATTR_MODULE                     OCI_ATTR_MODULE
#define OCI_ATTR_ACTION                     367                     /* action for tracing */
#define     DCI_ATTR_ACTION                     OCI_ATTR_ACTION
#define OCI_ATTR_CLIENT_INFO                368                     /* client info */
#define     DCI_ATTR_CLIENT_INFO                OCI_ATTR_CLIENT_INFO
#define OCI_ATTR_COLLECT_CALL_TIME          369                     /* collect call time */
#define     DCI_ATTR_COLLECT_CALL_TIME          OCI_ATTR_COLLECT_CALL_TIME
#define OCI_ATTR_CALL_TIME                  370                     /* extract call time */
#define     DCI_ATTR_CALL_TIME                  OCI_ATTR_CALL_TIME
#define OCI_ATTR_ECONTEXT_ID                371                     /* execution-id context */
#define     DCI_ATTR_ECONTEXT_ID                OCI_ATTR_ECONTEXT_ID
#define OCI_ATTR_ECONTEXT_SEQ               372                     /*execution-id sequence num */
#define     DCI_ATTR_ECONTEXT_SEQ               OCI_ATTR_ECONTEXT_SEQ

/*---------------- Describe Handle Parameter Attribute Values ---------------*/

/* OCI_ATTR_CURSOR_COMMIT_BEHAVIOR */
#define OCI_CURSOR_OPEN                     0
#define     DCI_CURSOR_OPEN                     OCI_CURSOR_OPEN
#define OCI_CURSOR_CLOSED                   1
#define     DCI_CURSOR_CLOSED                   OCI_CURSOR_CLOSED

/* OCI_ATTR_CATALOG_LOCATION */
#define OCI_CL_START                        0
#define     DCI_CL_START                        OCI_CL_START
#define OCI_CL_END                          1
#define     DCI_CL_END                          OCI_CL_END

/* OCI_ATTR_SAVEPOINT_SUPPORT */
#define OCI_SP_SUPPORTED                    0
#define     DCI_SP_SUPPORTED                    OCI_SP_SUPPORTED
#define OCI_SP_UNSUPPORTED                  1
#define     DCI_SP_UNSUPPORTED                  OCI_SP_UNSUPPORTED

/* OCI_ATTR_NOWAIT_SUPPORT */
#define OCI_NW_SUPPORTED                    0
#define     DCI_NW_SUPPORTED                    OCI_NW_SUPPORTED
#define OCI_NW_UNSUPPORTED                  1
#define     DCI_NW_UNSUPPORTED                  OCI_NW_UNSUPPORTED

/* OCI_ATTR_AUTOCOMMIT_DDL */
#define OCI_AC_DDL                          0
#define     DCI_AC_DDL                          OCI_AC_DDL
#define OCI_NO_AC_DDL                       1
#define     DCI_NO_AC_DDL                       OCI_NO_AC_DDL

/* OCI_ATTR_LOCKING_MODE */
#define OCI_LOCK_IMMEDIATE                  0
#define     DCI_LOCK_IMMEDIATE                  OCI_LOCK_IMMEDIATE
#define OCI_LOCK_DELAYED                    1
#define     DCI_LOCK_DELAYED                    OCI_LOCK_DELAYED

/* ------------------- Instance type attribute values -----------------------*/
#define OCI_INSTANCE_TYPE_UNKNOWN           0
#define     DCI_INSTANCE_TYPE_UNKNOWN           OCI_INSTANCE_TYPE_UNKNOWN
#define OCI_INSTANCE_TYPE_RDBMS             1
#define     DCI_INSTANCE_TYPE_RDBMS             OCI_INSTANCE_TYPE_RDBMS
#define OCI_INSTANCE_TYPE_OSM               2
#define     DCI_INSTANCE_TYPE_OSM               OCI_INSTANCE_TYPE_OSM

/*---------------------------------------------------------------------------*/

/*---------------------------OCIPasswordChange-------------------------------*/
#define OCI_AUTH                            0x08                    /* Change the password but do not login */
#define     DCI_AUTH                            OCI_AUTH


/*------------------------Other Constants------------------------------------*/
#define OCI_MAX_FNS                         100                     /* max number of OCI Functions */
#define     DCI_MAX_FNS                         OCI_MAX_FNS
#define OCI_SQLSTATE_SIZE                   5
#define     DCI_SQLSTATE_SIZE                   OCI_SQLSTATE_SIZE
#define OCI_ERROR_MAXMSG_SIZE               1024                    /* max size of an error message */
#define     DCI_ERROR_MAXMSG_SIZE               OCI_ERROR_MAXMSG_SIZE
#define OCI_LOBMAXSIZE                      MINUB4MAXVAL            /* maximum lob data size */
#define     DCI_LOBMAXSIZE                      OCI_LOBMAXSIZE
#define OCI_ROWID_LEN                       23
#define     DCI_ROWID_LEN                       OCI_ROWID_LEN
/*---------------------------------------------------------------------------*/

/*------------------------ Fail Over Events ---------------------------------*/
#define OCI_FO_END                          0x00000001
#define     DCI_FO_END                          OCI_FO_END
#define OCI_FO_ABORT                        0x00000002
#define     DCI_FO_ABORT                        OCI_FO_ABORT
#define OCI_FO_REAUTH                       0x00000004
#define     DCI_FO_REAUTH                       OCI_FO_REAUTH
#define OCI_FO_BEGIN                        0x00000008
#define     DCI_FO_BEGIN                        OCI_FO_BEGIN
#define OCI_FO_ERROR                        0x00000010
#define     DCI_FO_ERROR                        OCI_FO_ERROR
/*---------------------------------------------------------------------------*/

/*------------------------ Fail Over Callback Return Codes ------------------*/
#define OCI_FO_RETRY                        25410
#define     DCI_FO_RETRY                        OCI_FO_RETRY
/*---------------------------------------------------------------------------*/

/*------------------------- Fail Over Types ---------------------------------*/
#define OCI_FO_NONE                         0x00000001
#define     DCI_FO_NONE                         OCI_FO_NONE
#define OCI_FO_SESSION                      0x00000002
#define     DCI_FO_SESSION                      OCI_FO_SESSION
#define OCI_FO_SELECT                       0x00000004
#define     DCI_FO_SELECT                       OCI_FO_SELECT
#define OCI_FO_TXNAL                        0x00000008
#define     DCI_FO_TXNAL                        OCI_FO_TXNAL
/*---------------------------------------------------------------------------*/

/*-----------------------Function Codes--------------------------------------*/
#define OCI_FNCODE_INITIALIZE               1                       /* OCIInitialize */
#define     DCI_FNCODE_INITIALIZE               OCI_FNCODE_INITIALIZE
#define OCI_FNCODE_HANDLEALLOC              2                       /* OCIHandleAlloc */
#define     DCI_FNCODE_HANDLEALLOC              OCI_FNCODE_HANDLEALLOC
#define OCI_FNCODE_HANDLEFREE               3                       /* OCIHandleFree */
#define     DCI_FNCODE_HANDLEFREE               OCI_FNCODE_HANDLEFREE
#define OCI_FNCODE_DESCRIPTORALLOC          4                       /* OCIDescriptorAlloc */
#define     DCI_FNCODE_DESCRIPTORALLOC          OCI_FNCODE_DESCRIPTORALLOC
#define OCI_FNCODE_DESCRIPTORFREE           5                       /* OCIDescriptorFree */
#define     DCI_FNCODE_DESCRIPTORFREE           OCI_FNCODE_DESCRIPTORFREE
#define OCI_FNCODE_ENVINIT                  6                       /* OCIEnvInit */
#define     DCI_FNCODE_ENVINIT                  OCI_FNCODE_ENVINIT
#define OCI_FNCODE_SERVERATTACH             7                       /* OCIServerAttach */
#define     DCI_FNCODE_SERVERATTACH             OCI_FNCODE_SERVERATTACH
#define OCI_FNCODE_SERVERDETACH             8                       /* OCIServerDetach */
#define     DCI_FNCODE_SERVERDETACH             OCI_FNCODE_SERVERDETACH
/* unused         9 */ 
#define OCI_FNCODE_SESSIONBEGIN             10                      /* OCISessionBegin */
#define     DCI_FNCODE_SESSIONBEGIN             OCI_FNCODE_SESSIONBEGIN
#define OCI_FNCODE_SESSIONEND               11                      /* OCISessionEnd */
#define     DCI_FNCODE_SESSIONEND               OCI_FNCODE_SESSIONEND
#define OCI_FNCODE_PASSWORDCHANGE           12                      /* OCIPasswordChange */
#define     DCI_FNCODE_PASSWORDCHANGE           OCI_FNCODE_PASSWORDCHANGE
#define OCI_FNCODE_STMTPREPARE              13                      /* OCIStmtPrepare */
#define     DCI_FNCODE_STMTPREPARE              OCI_FNCODE_STMTPREPARE
/* unused       14- 16 */
#define OCI_FNCODE_BINDDYNAMIC              17                      /* OCIBindDynamic */
#define     DCI_FNCODE_BINDDYNAMIC              OCI_FNCODE_BINDDYNAMIC
#define OCI_FNCODE_BINDOBJECT               18                      /* OCIBindObject */
#define     DCI_FNCODE_BINDOBJECT               OCI_FNCODE_BINDOBJECT
/* 19 unused */
#define OCI_FNCODE_BINDARRAYOFSTRUCT        20                      /* OCIBindArrayOfStruct */
#define     DCI_FNCODE_BINDARRAYOFSTRUCT        OCI_FNCODE_BINDARRAYOFSTRUCT
#define OCI_FNCODE_STMTEXECUTE              21                      /* OCIStmtExecute */
#define     DCI_FNCODE_STMTEXECUTE              OCI_FNCODE_STMTEXECUTE
/* unused 22-24 */
#define OCI_FNCODE_DEFINEOBJECT             25                      /* OCIDefineObject */
#define     DCI_FNCODE_DEFINEOBJECT             OCI_FNCODE_DEFINEOBJECT
#define OCI_FNCODE_DEFINEDYNAMIC            26                      /* OCIDefineDynamic */
#define     DCI_FNCODE_DEFINEDYNAMIC            OCI_FNCODE_DEFINEDYNAMIC
#define OCI_FNCODE_DEFINEARRAYOFSTRUCT      27                      /* OCIDefineArrayOfStruct */
#define     DCI_FNCODE_DEFINEARRAYOFSTRUCT      OCI_FNCODE_DEFINEARRAYOFSTRUCT
#define OCI_FNCODE_STMTFETCH                28                      /* OCIStmtFetch */
#define     DCI_FNCODE_STMTFETCH                OCI_FNCODE_STMTFETCH
#define OCI_FNCODE_STMTGETBIND              29                      /* OCIStmtGetBindInfo */
#define     DCI_FNCODE_STMTGETBIND              OCI_FNCODE_STMTGETBIND
/* 30, 31 unused */
#define OCI_FNCODE_DESCRIBEANY              32                      /* OCIDescribeAny */
#define     DCI_FNCODE_DESCRIBEANY              OCI_FNCODE_DESCRIBEANY
#define OCI_FNCODE_TRANSSTART               33                      /* OCITransStart */
#define     DCI_FNCODE_TRANSSTART               OCI_FNCODE_TRANSSTART
#define OCI_FNCODE_TRANSDETACH              34                      /* OCITransDetach */
#define     DCI_FNCODE_TRANSDETACH              OCI_FNCODE_TRANSDETACH
#define OCI_FNCODE_TRANSCOMMIT              35                      /* OCITransCommit */
#define     DCI_FNCODE_TRANSCOMMIT              OCI_FNCODE_TRANSCOMMIT
/* 36 unused */
#define OCI_FNCODE_ERRORGET                 37                      /* OCIErrorGet */
#define     DCI_FNCODE_ERRORGET                 OCI_FNCODE_ERRORGET
#define OCI_FNCODE_LOBOPENFILE              38                      /* OCILobFileOpen */
#define     DCI_FNCODE_LOBOPENFILE              OCI_FNCODE_LOBOPENFILE
#define OCI_FNCODE_LOBCLOSEFILE             39                      /* OCILobFileClose */
#define     DCI_FNCODE_LOBCLOSEFILE             OCI_FNCODE_LOBCLOSEFILE
/* 40 was LOBCREATEFILE, unused */
/* 41 was OCILobFileDelete, unused  */
#define OCI_FNCODE_LOBCOPY                  42                      /* OCILobCopy */
#define     DCI_FNCODE_LOBCOPY                  OCI_FNCODE_LOBCOPY
#define OCI_FNCODE_LOBAPPEND                43                      /* OCILobAppend */
#define     DCI_FNCODE_LOBAPPEND                OCI_FNCODE_LOBAPPEND
#define OCI_FNCODE_LOBERASE                 44                      /* OCILobErase */
#define     DCI_FNCODE_LOBERASE                 OCI_FNCODE_LOBERASE
#define OCI_FNCODE_LOBLENGTH                45                      /* OCILobGetLength */
#define     DCI_FNCODE_LOBLENGTH                OCI_FNCODE_LOBLENGTH
#define OCI_FNCODE_LOBTRIM                  46                      /* OCILobTrim */
#define     DCI_FNCODE_LOBTRIM                  OCI_FNCODE_LOBTRIM
#define OCI_FNCODE_LOBREAD                  47                      /* OCILobRead */
#define     DCI_FNCODE_LOBREAD                  OCI_FNCODE_LOBREAD
#define OCI_FNCODE_LOBWRITE                 48                      /* OCILobWrite */
#define     DCI_FNCODE_LOBWRITE                 OCI_FNCODE_LOBWRITE
/* 49 unused */
#define OCI_FNCODE_SVCCTXBREAK              50                      /* OCIBreak */
#define     DCI_FNCODE_SVCCTXBREAK              OCI_FNCODE_SVCCTXBREAK
#define OCI_FNCODE_SERVERVERSION            51                      /* OCIServerVersion */
#define     DCI_FNCODE_SERVERVERSION            OCI_FNCODE_SERVERVERSION
#define OCI_FNCODE_KERBATTRSET              52                      /* OCIKerbAttrSet */
#define     DCI_FNCODE_KERBATTRSET              OCI_FNCODE_KERBATTRSET
/* unused 53 */
#define OCI_FNCODE_ATTRGET                  54                      /* OCIAttrGet */
#define     DCI_FNCODE_ATTRGET                  OCI_FNCODE_ATTRGET
#define OCI_FNCODE_ATTRSET                  55                      /* OCIAttrSet */
#define     DCI_FNCODE_ATTRSET                  OCI_FNCODE_ATTRSET
#define OCI_FNCODE_PARAMSET                 56                      /* OCIParamSet */
#define     DCI_FNCODE_PARAMSET                 OCI_FNCODE_PARAMSET
#define OCI_FNCODE_PARAMGET                 57                      /* OCIParamGet */
#define     DCI_FNCODE_PARAMGET                 OCI_FNCODE_PARAMGET
#define OCI_FNCODE_STMTGETPIECEINFO         58                      /* OCIStmtGetPieceInfo */
#define     DCI_FNCODE_STMTGETPIECEINFO         OCI_FNCODE_STMTGETPIECEINFO
#define OCI_FNCODE_LDATOSVCCTX              59                      /* OCILdaToSvcCtx */
#define     DCI_FNCODE_LDATOSVCCTX              OCI_FNCODE_LDATOSVCCTX
/* 60 unused */
#define OCI_FNCODE_STMTSETPIECEINFO         61                      /* OCIStmtSetPieceInfo */
#define     DCI_FNCODE_STMTSETPIECEINFO         OCI_FNCODE_STMTSETPIECEINFO
#define OCI_FNCODE_TRANSFORGET              62                      /* OCITransForget */
#define     DCI_FNCODE_TRANSFORGET              OCI_FNCODE_TRANSFORGET
#define OCI_FNCODE_TRANSPREPARE             63                      /* OCITransPrepare */
#define     DCI_FNCODE_TRANSPREPARE             OCI_FNCODE_TRANSPREPARE
#define OCI_FNCODE_TRANSROLLBACK            64                      /* OCITransRollback */
#define     DCI_FNCODE_TRANSROLLBACK            OCI_FNCODE_TRANSROLLBACK
#define OCI_FNCODE_DEFINEBYPOS              65                      /* OCIDefineByPos */
#define     DCI_FNCODE_DEFINEBYPOS              OCI_FNCODE_DEFINEBYPOS
#define OCI_FNCODE_BINDBYPOS                66                      /* OCIBindByPos */
#define     DCI_FNCODE_BINDBYPOS                OCI_FNCODE_BINDBYPOS
#define OCI_FNCODE_BINDBYNAME               67                      /* OCIBindByName */
#define     DCI_FNCODE_BINDBYNAME               OCI_FNCODE_BINDBYNAME
#define OCI_FNCODE_LOBASSIGN                68                      /* OCILobAssign */
#define     DCI_FNCODE_LOBASSIGN                OCI_FNCODE_LOBASSIGN
#define OCI_FNCODE_LOBISEQUAL               69                      /* OCILobIsEqual */
#define     DCI_FNCODE_LOBISEQUAL               OCI_FNCODE_LOBISEQUAL
#define OCI_FNCODE_LOBISINIT                70                      /* OCILobLocatorIsInit */
#define     DCI_FNCODE_LOBISINIT                OCI_FNCODE_LOBISINIT
#define OCI_FNCODE_LOBENABLEBUFFERING       71                      /* OCILobEnableBuffering */
#define     DCI_FNCODE_LOBENABLEBUFFERING       OCI_FNCODE_LOBENABLEBUFFERING
#define OCI_FNCODE_LOBCHARSETID             72                      /* OCILobCharSetID */
#define     DCI_FNCODE_LOBCHARSETID             OCI_FNCODE_LOBCHARSETID
#define OCI_FNCODE_LOBCHARSETFORM           73                      /* OCILobCharSetForm */
#define     DCI_FNCODE_LOBCHARSETFORM           OCI_FNCODE_LOBCHARSETFORM
#define OCI_FNCODE_LOBFILESETNAME           74                      /* OCILobFileSetName */
#define     DCI_FNCODE_LOBFILESETNAME           OCI_FNCODE_LOBFILESETNAME
#define OCI_FNCODE_LOBFILEGETNAME           75                      /* OCILobFileGetName */
#define     DCI_FNCODE_LOBFILEGETNAME           OCI_FNCODE_LOBFILEGETNAME
#define OCI_FNCODE_LOGON                    76                      /* OCILogon */
#define     DCI_FNCODE_LOGON                    OCI_FNCODE_LOGON
#define OCI_FNCODE_LOGOFF                   77                      /* OCILogoff */
#define     DCI_FNCODE_LOGOFF                   OCI_FNCODE_LOGOFF
#define OCI_FNCODE_LOBDISABLEBUFFERING      78                      /* OCILobDisableBuffering */
#define     DCI_FNCODE_LOBDISABLEBUFFERING      OCI_FNCODE_LOBDISABLEBUFFERING
#define OCI_FNCODE_LOBFLUSHBUFFER           79                      /* OCILobFlushBuffer */
#define     DCI_FNCODE_LOBFLUSHBUFFER           OCI_FNCODE_LOBFLUSHBUFFER
#define OCI_FNCODE_LOBLOADFROMFILE          80                      /* OCILobLoadFromFile */
#define     DCI_FNCODE_LOBLOADFROMFILE          OCI_FNCODE_LOBLOADFROMFILE
#define OCI_FNCODE_LOBOPEN                  81                      /* OCILobOpen */
#define     DCI_FNCODE_LOBOPEN                  OCI_FNCODE_LOBOPEN
#define OCI_FNCODE_LOBCLOSE                 82                      /* OCILobClose */
#define     DCI_FNCODE_LOBCLOSE                 OCI_FNCODE_LOBCLOSE
#define OCI_FNCODE_LOBISOPEN                83                      /* OCILobIsOpen */
#define     DCI_FNCODE_LOBISOPEN                OCI_FNCODE_LOBISOPEN
#define OCI_FNCODE_LOBFILEISOPEN            84                      /* OCILobFileIsOpen */
#define     DCI_FNCODE_LOBFILEISOPEN            OCI_FNCODE_LOBFILEISOPEN
#define OCI_FNCODE_LOBFILEEXISTS            85                      /* OCILobFileExists */
#define     DCI_FNCODE_LOBFILEEXISTS            OCI_FNCODE_LOBFILEEXISTS
#define OCI_FNCODE_LOBFILECLOSEALL          86                      /* OCILobFileCloseAll */
#define     DCI_FNCODE_LOBFILECLOSEALL          OCI_FNCODE_LOBFILECLOSEALL
#define OCI_FNCODE_LOBCREATETEMP            87                      /* OCILobCreateTemporary */
#define     DCI_FNCODE_LOBCREATETEMP            OCI_FNCODE_LOBCREATETEMP
#define OCI_FNCODE_LOBFREETEMP              88                      /* OCILobFreeTemporary */
#define     DCI_FNCODE_LOBFREETEMP              OCI_FNCODE_LOBFREETEMP
#define OCI_FNCODE_LOBISTEMP                89                      /* OCILobIsTemporary */
#define     DCI_FNCODE_LOBISTEMP                OCI_FNCODE_LOBISTEMP
#define OCI_FNCODE_AQENQ                    90                      /* OCIAQEnq */
#define     DCI_FNCODE_AQENQ                    OCI_FNCODE_AQENQ
#define OCI_FNCODE_AQDEQ                    91                      /* OCIAQDeq */
#define     DCI_FNCODE_AQDEQ                    OCI_FNCODE_AQDEQ
#define OCI_FNCODE_RESET                    92                      /* OCIReset */
#define     DCI_FNCODE_RESET                    OCI_FNCODE_RESET
#define OCI_FNCODE_SVCCTXTOLDA              93                      /* OCISvcCtxToLda */
#define     DCI_FNCODE_SVCCTXTOLDA              OCI_FNCODE_SVCCTXTOLDA
#define OCI_FNCODE_LOBLOCATORASSIGN         94                      /* OCILobLocatorAssign */
#define     DCI_FNCODE_LOBLOCATORASSIGN         OCI_FNCODE_LOBLOCATORASSIGN
#define OCI_FNCODE_UBINDBYNAME              95
#define     DCI_FNCODE_UBINDBYNAME              OCI_FNCODE_UBINDBYNAME
#define OCI_FNCODE_AQLISTEN                 96                      /* OCIAQListen */
#define     DCI_FNCODE_AQLISTEN                 OCI_FNCODE_AQLISTEN
#define OCI_FNCODE_SVC2HST                  97                      /* reserved */
#define     DCI_FNCODE_SVC2HST                  OCI_FNCODE_SVC2HST
#define OCI_FNCODE_SVCRH                    98                      /* reserved */
#define     DCI_FNCODE_SVCRH                    OCI_FNCODE_SVCRH
/* 97 and 98 are reserved for Oracle internal use */
#define OCI_FNCODE_TRANSMULTIPREPARE        99                      /* OCITransMultiPrepare */
#define     DCI_FNCODE_TRANSMULTIPREPARE        OCI_FNCODE_TRANSMULTIPREPARE
#define OCI_FNCODE_CPOOLCREATE              100                     /* OCIConnectionPoolCreate */
#define     DCI_FNCODE_CPOOLCREATE              OCI_FNCODE_CPOOLCREATE
#define OCI_FNCODE_CPOOLDESTROY             101                     /* OCIConnectionPoolDestroy */
#define     DCI_FNCODE_CPOOLDESTROY             OCI_FNCODE_CPOOLDESTROY
#define OCI_FNCODE_LOGON2                   102                     /* OCILogon2 */
#define     DCI_FNCODE_LOGON2                   OCI_FNCODE_LOGON2
#define OCI_FNCODE_ROWIDTOCHAR              103                     /* OCIRowidToChar */
#define     DCI_FNCODE_ROWIDTOCHAR              OCI_FNCODE_ROWIDTOCHAR
#define OCI_FNCODE_SPOOLCREATE              104                     /* OCISessionPoolCreate */
#define     DCI_FNCODE_SPOOLCREATE              OCI_FNCODE_SPOOLCREATE
#define OCI_FNCODE_SPOOLDESTROY             105                     /* OCISessionPoolDestroy */
#define     DCI_FNCODE_SPOOLDESTROY             OCI_FNCODE_SPOOLDESTROY
#define OCI_FNCODE_SESSIONGET               106                     /* OCISessionGet */
#define     DCI_FNCODE_SESSIONGET               OCI_FNCODE_SESSIONGET
#define OCI_FNCODE_SESSIONRELEASE           107                     /* OCISessionRelease */
#define     DCI_FNCODE_SESSIONRELEASE           OCI_FNCODE_SESSIONRELEASE
#define OCI_FNCODE_STMTPREPARE2             108                     /* OCIStmtPrepare2 */
#define     DCI_FNCODE_STMTPREPARE2             OCI_FNCODE_STMTPREPARE2
#define OCI_FNCODE_STMTRELEASE              109                     /* OCIStmtRelease */
#define     DCI_FNCODE_STMTRELEASE              OCI_FNCODE_STMTRELEASE
#define OCI_FNCODE_AQENQARRAY               110                     /* OCIAQEnqArray */
#define     DCI_FNCODE_AQENQARRAY               OCI_FNCODE_AQENQARRAY
#define OCI_FNCODE_AQDEQARRAY               111                     /* OCIAQDeqArray */
#define     DCI_FNCODE_AQDEQARRAY               OCI_FNCODE_AQDEQARRAY
#define OCI_FNCODE_LOBCOPY2                 112                     /* OCILobCopy2 */
#define     DCI_FNCODE_LOBCOPY2                 OCI_FNCODE_LOBCOPY2
#define OCI_FNCODE_LOBERASE2                113                     /* OCILobErase2 */
#define     DCI_FNCODE_LOBERASE2                OCI_FNCODE_LOBERASE2
#define OCI_FNCODE_LOBLENGTH2               114                     /* OCILobGetLength2 */
#define     DCI_FNCODE_LOBLENGTH2               OCI_FNCODE_LOBLENGTH2
#define OCI_FNCODE_LOBLOADFROMFILE2         115                     /* OCILobLoadFromFile2 */
#define     DCI_FNCODE_LOBLOADFROMFILE2         OCI_FNCODE_LOBLOADFROMFILE2
#define OCI_FNCODE_LOBREAD2                 116                     /* OCILobRead2 */
#define     DCI_FNCODE_LOBREAD2                 OCI_FNCODE_LOBREAD2
#define OCI_FNCODE_LOBTRIM2                 117                     /* OCILobTrim2 */
#define     DCI_FNCODE_LOBTRIM2                 OCI_FNCODE_LOBTRIM2
#define OCI_FNCODE_LOBWRITE2                118                     /* OCILobWrite2 */
#define     DCI_FNCODE_LOBWRITE2                OCI_FNCODE_LOBWRITE2
#define OCI_FNCODE_LOBGETSTORAGELIMIT       119                     /* OCILobGetStorageLimit */
#define     DCI_FNCODE_LOBGETSTORAGELIMIT       OCI_FNCODE_LOBGETSTORAGELIMIT

#define OCI_FNCODE_MAXFCN                   119                     /* maximum OCI function code */
#define     DCI_FNCODE_MAXFCN                   OCI_FNCODE_MAXFCN

/*---------------------------------------------------------------------------*/

/*-----------------------Handle Definitions----------------------------------*/
typedef struct OCIEnv           OCIEnv;            /* OCI environment handle */
typedef struct OCIError         OCIError;                /* OCI error handle */
typedef struct OCISvcCtx        OCISvcCtx;             /* OCI service handle */
typedef struct OCIStmt          OCIStmt;             /* OCI statement handle */
typedef struct OCIBind          OCIBind;                  /* OCI bind handle */
typedef struct OCIDefine        OCIDefine;              /* OCI Define handle */
typedef struct OCIDescribe      OCIDescribe;          /* OCI Describe handle */
typedef struct OCIServer        OCIServer;              /* OCI Server handle */
typedef struct OCISession       OCISession;     /* OCI Authentication handle */
typedef struct OCIComplexObject OCIComplexObject;          /* OCI COR handle */
typedef struct OCITrans         OCITrans;          /* OCI Transaction handle */
typedef struct OCISecurity      OCISecurity;          /* OCI Security handle */
typedef struct OCISubscription  OCISubscription;      /* subscription handle */

typedef OCIEnv           DCIEnv;            /* OCI environment handle */
typedef OCIError         DCIError;                /* OCI error handle */
typedef OCISvcCtx        DCISvcCtx;             /* OCI service handle */
typedef OCIStmt          DCIStmt;             /* OCI statement handle */
typedef OCIBind          DCIBind;                  /* OCI bind handle */
typedef OCIDefine        DCIDefine;              /* OCI Define handle */
typedef OCIDescribe      DCIDescribe;          /* OCI Describe handle */
typedef OCIServer        DCIServer;              /* OCI Server handle */
typedef OCISession       DCISession;     /* OCI Authentication handle */
typedef OCIComplexObject DCIComplexObject;          /* OCI COR handle */
typedef OCITrans         DCITrans;          /* OCI Transaction handle */
typedef OCISecurity      DCISecurity;          /* OCI Security handle */
typedef OCISubscription  DCISubscription;      /* subscription handle */ 

typedef struct OCICPool         OCICPool;          /* connection pool handle */
typedef struct OCISPool         OCISPool;             /* session pool handle */
typedef struct OCIAuthInfo      OCIAuthInfo;                  /* auth handle */
typedef struct OCIThreadMutex   OCIThreadMutex;
typedef struct OCIAdmin         OCIAdmin;    
/* OCIThread Key for Thread-Specific Data */
typedef struct OCIThreadKey     OCIThreadKey;  
typedef struct OCIThreadHandle  OCIThreadHandle;  

/* OCIThread Thread ID */
typedef struct OCIThreadId      OCIThreadId;  
typedef void (*OCIThreadKeyDestFunc)( void  * );



typedef OCICPool         DCICPool;          /* connection pool handle */
typedef OCISPool         DCISPool;             /* session pool handle */
typedef OCIAuthInfo      DCIAuthInfo;                  /* auth handle */
typedef OCIThreadMutex   DCIThreadMutex;
typedef OCIAdmin         DCIAdmin;
typedef OCIThreadKey     DCIThreadKey;
typedef OCIThreadHandle  DCIThreadHandle;
typedef OCIThreadId      DCIThreadId;

/*-----------------------Descriptor Definitions------------------------------*/
typedef struct OCISnapshot      OCISnapshot;      /* OCI snapshot descriptor */
typedef struct OCIResult        OCIResult;      /* OCI Result Set Descriptor */
typedef struct OCILobLocator    OCILobLocator; /* OCI Lob Locator descriptor */
typedef struct OCIParam         OCIParam;        /* OCI PARameter descriptor */
typedef struct OCIComplexObjectComp OCIComplexObjectComp;
                                                       /* OCI COR descriptor */

typedef OCISnapshot      DCISnapshot;      /* OCI snapshot descriptor */
typedef OCIResult        DCIResult;      /* OCI Result Set Descriptor */
typedef OCILobLocator    DCILobLocator; /* OCI Lob Locator descriptor */
typedef OCIParam         DCIParam;        /* OCI PARameter descriptor */
typedef OCIComplexObjectComp DCIComplexObjectComp;
/* OCI COR descriptor */

typedef struct OCIRowid OCIRowid;                    /* OCI ROWID descriptor */
typedef OCIRowid DCIRowid;                    /* OCI ROWID descriptor */

typedef struct OCIDateTime OCIDateTime;           /* OCI DateTime descriptor */
typedef struct OCIInterval OCIInterval;           /* OCI Interval descriptor */

typedef OCIDateTime DCIDateTime;           /* OCI DateTime descriptor */
typedef OCIInterval DCIInterval;           /* OCI Interval descriptor */

typedef struct OCIUcb           OCIUcb;      /* OCI User Callback descriptor */
typedef struct OCIServerDNs     OCIServerDNs;    /* OCI server DN descriptor */

typedef OCIUcb           DCIUcb;      /* OCI User Callback descriptor */
typedef OCIServerDNs     DCIServerDNs;    /* OCI server DN descriptor */

typedef struct OCIRaw       OCIRaw;
typedef OCIRaw              DCIRaw;

typedef struct OCIString       OCIString; 
typedef OCIString            DCIString;


/*
 * OCIType - OCI Type Description Object 
 *
 * The contents of an 'OCIType' is private/opaque to clients.  Clients just 
 * need to declare and pass 'OCIType' pointers in to the type manage
 * functions.
 * The pointer points to the type in the object cache.  Thus, clients don't
 * need to allocate space for this type and must NEVER free the pointer to the
 * 'OCIType'.
 */

typedef struct OCIType OCIType;
typedef OCIType        DCIType;

/* OCIColl - generic collection type */
typedef struct OCIColl OCIColl;
typedef OCIColl        DCIColl;

typedef OCIColl        OCITable;
typedef DCIColl        DCITable;

/* OCIIter - collection iterator */
typedef struct OCIIter OCIIter;
typedef OCIIter        DCIIter;

enum OCIPinOpt
{
    /* 0 = uninitialized */
    OCI_PIN_DEFAULT = 1,                                 /* default pin option */
    OCI_PIN_ANY = 3,                          /* pin any copy of the object */
    OCI_PIN_RECENT = 4,                    /* pin recent copy of the object */
    OCI_PIN_LATEST = 5                     /* pin latest copy of the object */
};
typedef enum OCIPinOpt OCIPinOpt;

enum DCIPinOpt
{
    /* 0 = uninitialized */
    DCI_PIN_DEFAULT = 1,                                 /* default pin option */
    DCI_PIN_ANY = 3,                          /* pin any copy of the object */
    DCI_PIN_RECENT = 4,                    /* pin recent copy of the object */
    DCI_PIN_LATEST = 5                     /* pin latest copy of the object */
};
typedef enum DCIPinOpt DCIPinOpt;

/* The OCITypeCode type is interchangeable with the existing SQLT type
   which is a ub2 */
typedef ub2 OCITypeCode;
typedef ub2 DCITypeCode;

/*----------------------- GET OPTIONS FOR TDO  ------------------------------*/

enum OCITypeGetOpt
{
    OCI_TYPEGET_HEADER,
    /* load only the header portion of the TDO when getting type */
    OCI_TYPEGET_ALL       /* load all attribute and method descriptors as well */
};
typedef enum OCITypeGetOpt OCITypeGetOpt;

enum DCITypeGetOpt
{
    DCI_TYPEGET_HEADER,
    /* load only the header portion of the TDO when getting type */
    DCI_TYPEGET_ALL       /* load all attribute and method descriptors as well */
};
typedef enum DCITypeGetOpt DCITypeGetOpt;

typedef ub1 OCIObjectPropId;
typedef ub1 DCIObjectPropId;

/*------------------------- OBJECT REFERENCE (REF) --------------------------*/
typedef struct OCIRef OCIRef;
typedef OCIRef        DCIRef;

/*-------------------------- AQ Descriptors ---------------------------------*/
typedef struct OCIAQEnqOptions    OCIAQEnqOptions; /* AQ Enqueue Options hdl */
typedef struct OCIAQDeqOptions    OCIAQDeqOptions; /* AQ Dequeue Options hdl */
typedef struct OCIAQMsgProperties OCIAQMsgProperties;  /* AQ Mesg Properties */
typedef struct OCIAQAgent         OCIAQAgent;         /* AQ Agent descriptor */
typedef struct OCIAQNfyDescriptor OCIAQNfyDescriptor;   /* AQ Nfy descriptor */
typedef struct OCIAQSignature     OCIAQSignature;            /* AQ Siganture */

typedef OCIAQEnqOptions    DCIAQEnqOptions; /* AQ Enqueue Options hdl */
typedef OCIAQDeqOptions    DCIAQDeqOptions; /* AQ Dequeue Options hdl */
typedef OCIAQMsgProperties DCIAQMsgProperties;  /* AQ Mesg Properties */
typedef OCIAQAgent         DCIAQAgent;         /* AQ Agent descriptor */
typedef OCIAQNfyDescriptor DCIAQNfyDescriptor;   /* AQ Nfy descriptor */
typedef OCIAQSignature     DCIAQSignature;            /* AQ Siganture */
/*---------------------------------------------------------------------------*/
 
/* Lob typedefs for Pro*C */
typedef struct OCILobLocator OCIClobLocator;    /* OCI Character LOB Locator */
typedef struct OCILobLocator OCIBlobLocator;       /* OCI Binary LOB Locator */
typedef struct OCILobLocator OCIBFileLocator; /* OCI Binary LOB File Locator */

typedef OCILobLocator DCIClobLocator;    /* OCI Character LOB Locator */
typedef OCILobLocator DCIBlobLocator;       /* OCI Binary LOB Locator */
typedef OCILobLocator DCIBFileLocator; /* OCI Binary LOB File Locator */
/*---------------------------------------------------------------------------*/

/* Undefined value for tz in interval types*/
#define OCI_INTHR_UNK               24
#define     DCI_INTHR_UNK               OCI_INTHR_UNK

  /* These defined adjustment values */
#define OCI_ADJUST_UNK              10
#define     DCI_ADJUST_UNK              OCI_ADJUST_UNK
#define OCI_ORACLE_DATE             0
#define     DCI_ORACLE_DATE             OCI_ORACLE_DATE
#define OCI_ANSI_DATE               1
#define     DCI_ANSI_DATE               OCI_ANSI_DATE

/*------------------------ Lob-specific Definitions -------------------------*/

/*
 * ociloff - OCI Lob OFFset
 *
 * The offset in the lob data.  The offset is specified in terms of bytes for
 * BLOBs and BFILes.  Character offsets are used for CLOBs, NCLOBs.
 * The maximum size of internal lob data is 4 gigabytes.  FILE LOB 
 * size is limited by the operating system.
 */
typedef ub4 OCILobOffset;
typedef OCILobOffset DCILobOffset;

/*
 * ocillen - OCI Lob LENgth (of lob data)
 *
 * Specifies the length of lob data in bytes for BLOBs and BFILes and in 
 * characters for CLOBs, NCLOBs.  The maximum length of internal lob
 * data is 4 gigabytes.  The length of FILE LOBs is limited only by the
 * operating system.
 */
typedef ub4 OCILobLength;
typedef OCILobLength DCILobLength;
/*
 * ocilmo - OCI Lob open MOdes
 *
 * The mode specifies the planned operations that will be performed on the
 * FILE lob data.  The FILE lob can be opened in read-only mode only.
 * 
 * In the future, we may include read/write, append and truncate modes.  Append
 * is equivalent to read/write mode except that the FILE is positioned for
 * writing to the end.  Truncate is equivalent to read/write mode except that
 * the FILE LOB data is first truncated to a length of 0 before use.
 */
enum OCILobMode
{
  OCI_LOBMODE_READONLY = 1,                                     /* read-only */
  OCI_LOBMODE_READWRITE = 2             /* read_write for internal lobs only */
};
typedef enum OCILobMode OCILobMode;

enum DCILobMode
{
	DCI_LOBMODE_READONLY = 1,                                     /* read-only */
	DCI_LOBMODE_READWRITE = 2             /* read_write for internal lobs only */
};
typedef enum DCILobMode DCILobMode;

/*--------------------------- OBJECT LOCK OPTION ----------------------------*/

enum OCILockOpt
{
  /* 0 = uninitialized */
  OCI_LOCK_NONE = 1,                               /* null (same as no lock) */
  OCI_LOCK_X = 2,                                          /* exclusive lock */
  OCI_LOCK_X_NOWAIT = 3                      /* exclusive lock, do not wait  */
};
typedef enum OCILockOpt OCILockOpt;

enum DCILockOpt
{
    /* 0 = uninitialized */
    DCI_LOCK_NONE = 1,                               /* null (same as no lock) */
    DCI_LOCK_X = 2,                                          /* exclusive lock */
    DCI_LOCK_X_NOWAIT = 3                      /* exclusive lock, do not wait  */
};
typedef enum DCILockOpt DCILockOpt;

/*------------------------ TYPE ENCAPSULTATION LEVEL ------------------------*/

enum OCITypeEncap
{
    /* 0 = uninitialized */
    OCI_TYPEENCAP_PRIVATE,                /* private: only internally visible */
    OCI_TYPEENCAP_PUBLIC /* public: visible to both internally and externally */
};
typedef enum OCITypeEncap OCITypeEncap;

enum DCITypeEncap
{
    /* 0 = uninitialized */
    DCI_TYPEENCAP_PRIVATE,                /* private: only internally visible */
    DCI_TYPEENCAP_PUBLIC /* public: visible to both internally and externally */
};
typedef enum DCITypeEncap DCITypeEncap;

/*--------------------------- TYPE PARAMETER MODE ---------------------------*/

enum OCITypeParamMode
{
    /* PL/SQL starts this from 0 */
    OCI_TYPEPARAM_IN = 0,                                                /* in */
    OCI_TYPEPARAM_OUT,                                                  /* out */
    OCI_TYPEPARAM_INOUT,                                             /* in-out */
    OCI_TYPEPARAM_BYREF,              /* call by reference (implicitly in-out) */
    OCI_TYPEPARAM_OUTNCPY,                         /* OUT with NOCOPY modifier */
    OCI_TYPEPARAM_INOUTNCPY                     /* IN OUT with NOCOPY modifier */
};
typedef enum OCITypeParamMode OCITypeParamMode;

enum DCITypeParamMode
{
    /* PL/SQL starts this from 0 */
    DCI_TYPEPARAM_IN = 0,                                                /* in */
    DCI_TYPEPARAM_OUT,                                                  /* out */
    DCI_TYPEPARAM_INOUT,                                             /* in-out */
    DCI_TYPEPARAM_BYREF,              /* call by reference (implicitly in-out) */
    DCI_TYPEPARAM_OUTNCPY,                         /* OUT with NOCOPY modifier */
    DCI_TYPEPARAM_INOUTNCPY                     /* IN OUT with NOCOPY modifier */
};
typedef enum DCITypeParamMode DCITypeParamMode;

#define OCI_ATTR_PURITY_DEFAULT    0x00
#define     DCI_ATTR_PURITY_DEFAULT     OCI_ATTR_PURITY_DEFAULT
#define OCI_ATTR_PURITY_NEW        0x01
#define     DCI_ATTR_PURITY_NEW         OCI_ATTR_PURITY_NEW
#define OCI_ATTR_PURITY_SELF       0x02
#define     DCI_ATTR_PURITY_SELF        OCI_ATTR_PURITY_SELF

/*-------------------------- OBJECT Duration --------------------------------*/

typedef ub2 OCIDuration;
typedef OCIDuration DCIDuration;

#define OCI_DURATION_INVALID        0xFFFF                                  /* Invalid duration */
#define     DCI_DURATION_INVALID        OCI_DURATION_INVALID;

#define OCI_DURATION_BEGIN         (OCIDuration)10
#define     DCI_DURATION_BEGIN          OCI_DURATION_BEGIN;

/* beginning sequence of duration */
#define OCI_DURATION_NULL           (OCIDuration)(OCI_DURATION_BEGIN-1)
#define     DCI_DURATION_NULL           OCI_DURATION_NULL;
/* null duration */
#define OCI_DURATION_DEFAULT        (OCIDuration)(OCI_DURATION_BEGIN-2)     /* default */
#define     DCI_DURATION_DEFAULT        OCI_DURATION_DEFAULT;

#define OCI_DURATION_USER_CALLBACK  (OCIDuration)(OCI_DURATION_BEGIN-3)
#define     DCI_DURATION_USER_CALLBACK  OCI_DURATION_USER_CALLBACK;

#define OCI_DURATION_NEXT           (OCIDuration)(OCI_DURATION_BEGIN-4)
#define     DCI_DURATION_NEXT           OCI_DURATION_NEXT;
/* next special duration */
#define OCI_DURATION_SESSION        (OCIDuration)(OCI_DURATION_BEGIN)
#define     DCI_DURATION_SESSION        OCI_DURATION_SESSION;
/* the end of user session */
#define OCI_DURATION_TRANS          (OCIDuration)(OCI_DURATION_BEGIN+1)
#define     DCI_DURATION_TRANS          OCI_DURATION_TRANS;
/* the end of user transaction */
/*---------------------------------------------------------------------------*/

enum OCIRefreshOpt
{
  /* 0 = uninitialized */
  OCI_REFRESH_LOADED = 1        /* refresh objects loaded in the transaction */
};
typedef enum OCIRefreshOpt OCIRefreshOpt; 

enum DCIRefreshOpt
{
  /* 0 = uninitialized */
  DCI_REFRESH_LOADED = 1        /* refresh objects loaded in the transaction */
};
typedef enum DCIRefreshOpt DCIRefreshOpt; 

/* OCI representation of XMLType */
typedef struct OCIXMLType OCIXMLType;
typedef struct OCIXMLType DCIXMLType;

/* OCI representation of OCIDomDocument */
typedef struct OCIDOMDocument OCIDOMDocument;
typedef struct OCIDOMDocument DCIDOMDocument;

/* OCI representation of OCIExtProcContext */
typedef struct OCIExtProcContext OCIExtProcContext;
typedef struct OCIExtProcContext DCIExtProcContext;
/*----------------------------Piece Definitions------------------------------*/

/* if ocidef.h is being included in the app, ocidef.h should precede oci.h */

/* 
 * since clients may  use oci.h, ocidef.h and ocidfn.h the following defines
 * need to be guarded, usually internal clients
 */

#ifndef OCI_FLAGS
#define OCI_FLAGS
#define OCI_ONE_PIECE                   0                   /* one piece */
#define OCI_FIRST_PIECE                 1                   /* the first piece */
#define OCI_NEXT_PIECE                  2                   /* the next of many pieces */
#define OCI_LAST_PIECE                  3                   /* the last piece */
#endif

#ifndef DCI_FLAGS
#define DCI_FLAGS
#define DCI_ONE_PIECE                   0                   /* one piece */
#define DCI_FIRST_PIECE                 1                   /* the first piece */
#define DCI_NEXT_PIECE                  2                   /* the next of many pieces */
#define DCI_LAST_PIECE                  3                   /* the last piece */
#endif
/*---------------------------------------------------------------------------*/

/*--------------------------- OBJECT INDICATOR ------------------------------*/

typedef sb2 OCIInd;
typedef OCIInd      DCIInd;
/*
 * OCIInd -- a variable of this type contains (null) indicator information
 */

#define OCI_IND_NOTNULL                 (OCIInd)0                       /* not NULL */
#define     DCI_IND_NOTNULL                 OCI_IND_NOTNULL
#define OCI_IND_NULL                    (OCIInd)(-1)                    /* NULL */
#define     DCI_IND_NULL                    OCI_IND_NULL
#define OCI_IND_BADNULL                 (OCIInd)(-2)                    /* BAD NULL */
#define     DCI_IND_BADNULL                 OCI_IND_BADNULL
#define OCI_IND_NOTNULLABLE             (OCIInd)(-3)                    /* not NULLable */
#define     DCI_IND_NOTNULLABLE             OCI_IND_NOTNULLABLE

/*--------------------------- FILE open modes -------------------------------*/
#define OCI_FILE_READONLY               1                               /* readonly mode open for FILE types */
#define     DCI_FILE_READONLY               OCI_FILE_READONLY
/*---------------------------------------------------------------------------*/
/*--------------------------- LOB open modes --------------------------------*/
#define OCI_LOB_READONLY                1                               /* readonly mode open for ILOB types */
#define     DCI_LOB_READONLY                OCI_LOB_READONLY
#define OCI_LOB_READWRITE               2                               /* read write mode open for ILOBs */
#define     DCI_LOB_READWRITE               OCI_LOB_READWRITE
#define OCI_LOB_WRITEONLY               3                               /* Writeonly mode open for ILOB types*/
#define     DCI_LOB_WRITEONLY               OCI_LOB_WRITEONLY
#define OCI_LOB_APPENDONLY              4                               /* Appendonly mode open for ILOB types */
#define     DCI_LOB_APPENDONLY              OCI_LOB_APPENDONLY
#define OCI_LOB_FULLOVERWRITE           5                               /* Completely overwrite ILOB */
#define     DCI_LOB_FULLOVERWRITE           OCI_LOB_FULLOVERWRITE
#define OCI_LOB_FULLREAD                6                               /* Doing a Full Read of ILOB */
#define     DCI_LOB_FULLREAD                OCI_LOB_FULLREAD

/*----------------------- LOB Buffering Flush Flags -------------------------*/
#define OCI_LOB_BUFFER_FREE             1
#define     DCI_LOB_BUFFER_FREE             OCI_LOB_BUFFER_FREE
#define OCI_LOB_BUFFER_NOFREE           2
#define     DCI_LOB_BUFFER_NOFREE           OCI_LOB_BUFFER_NOFREE
/*---------------------------------------------------------------------------*/

/*---------------------------LOB Option Types -------------------------------*/
#define OCI_LOB_OPT_COMPRESS            1                               /* SECUREFILE Compress */
#define     DCI_LOB_OPT_COMPRESS            OCI_LOB_OPT_COMPRESS
#define OCI_LOB_OPT_ENCRYPT             2                               /* SECUREFILE Encrypt */
#define     DCI_LOB_OPT_ENCRYPT             OCI_LOB_OPT_ENCRYPT
#define OCI_LOB_OPT_DEDUPLICATE         4                               /* SECUREFILE Deduplicate */
#define     DCI_LOB_OPT_DEDUPLICATE         OCI_LOB_OPT_DEDUPLICATE
#define OCI_LOB_OPT_ALLOCSIZE           8                               /* SECUREFILE Allocation Size */
#define     DCI_LOB_OPT_ALLOCSIZE           OCI_LOB_OPT_ALLOCSIZE
#define OCI_LOB_OPT_CONTENTTYPE         16                              /* SECUREFILE Content Type */
#define     DCI_LOB_OPT_CONTENTTYPE         OCI_LOB_OPT_CONTENTTYPE
#define OCI_LOB_OPT_MODTIME             32                              /* SECUREFILE Modification Time */
#define     DCI_LOB_OPT_MODTIME             OCI_LOB_OPT_MODTIME

/*------------------------   LOB Option Values ------------------------------*/
/* Compression */
#define OCI_LOB_COMPRESS_OFF            0                               /* Compression off */
#define     DCI_LOB_COMPRESS_OFF            OCI_LOB_COMPRESS_OFF
#define OCI_LOB_COMPRESS_ON             1                               /* Compression on */
#define     DCI_LOB_COMPRESS_ON             OCI_LOB_COMPRESS_ON
/* Encryption */
#define OCI_LOB_ENCRYPT_OFF             0                               /* Encryption Off */
#define     DCI_LOB_ENCRYPT_OFF             OCI_LOB_ENCRYPT_OFF
#define OCI_LOB_ENCRYPT_ON              2                               /* Encryption On */
#define     DCI_LOB_ENCRYPT_ON              OCI_LOB_ENCRYPT_ON
/* Deduplciate */
#define OCI_LOB_DEDUPLICATE_OFF         0                               /* Deduplicate Off */
#define     DCI_LOB_DEDUPLICATE_OFF         OCI_LOB_DEDUPLICATE_OFF
#define OCI_LOB_DEDUPLICATE_ON          4                               /* Deduplicate Lobs */
#define     DCI_LOB_DEDUPLICATE_ON          OCI_LOB_DEDUPLICATE_ON

/*--------------------------- OCI Statement Types ---------------------------*/
#define OCI_STMT_UNKNOWN                0                               /* Unknown statement */
#define    DCI_STMT_UNKNOWN                OCI_STMT_UNKNOWN
#define OCI_STMT_SELECT                 1                               /* select statement */
#define    DCI_STMT_SELECT                 OCI_STMT_SELECT
#define OCI_STMT_UPDATE                 2                               /* update statement */
#define    DCI_STMT_UPDATE                 OCI_STMT_UPDATE
#define OCI_STMT_DELETE                 3                               /* delete statement */
#define    DCI_STMT_DELETE                 OCI_STMT_DELETE
#define OCI_STMT_INSERT                 4                               /* Insert Statement */
#define    DCI_STMT_INSERT                 OCI_STMT_INSERT
#define OCI_STMT_CREATE                 5                               /* create statement */
#define    DCI_STMT_CREATE                 OCI_STMT_CREATE
#define OCI_STMT_DROP                   6                               /* drop statement */
#define    DCI_STMT_DROP                   OCI_STMT_DROP
#define OCI_STMT_ALTER                  7                               /* alter statement */
#define    DCI_STMT_ALTER                  OCI_STMT_ALTER
#define OCI_STMT_BEGIN                  8                               /* begin ... (pl/sql statement)*/
#define    DCI_STMT_BEGIN                  OCI_STMT_BEGIN
#define OCI_STMT_DECLARE                9                               /* declare .. (pl/sql statement ) */
#define    DCI_STMT_DECLARE                OCI_STMT_DECLARE
#define OCI_STMT_CALL                   10                              /* corresponds to kpu call */
#define    DCI_STMT_CALL                   OCI_STMT_CALL
/*---------------------------------------------------------------------------*/

/*--------------------------- OCI Parameter Types ---------------------------*/
#define OCI_PTYPE_UNK                   0                               /* unknown   */
#define     DCI_PTYPE_UNK                   OCI_PTYPE_UNK
#define OCI_PTYPE_TABLE                 1                               /* table     */
#define     DCI_PTYPE_TABLE                 OCI_PTYPE_TABLE
#define OCI_PTYPE_VIEW                  2                               /* view      */
#define     DCI_PTYPE_VIEW                  OCI_PTYPE_VIEW
#define OCI_PTYPE_PROC                  3                               /* procedure */
#define     DCI_PTYPE_PROC                  OCI_PTYPE_PROC
#define OCI_PTYPE_FUNC                  4                               /* function  */
#define     DCI_PTYPE_FUNC                  OCI_PTYPE_FUNC
#define OCI_PTYPE_PKG                   5                               /* package   */
#define     DCI_PTYPE_PKG                   OCI_PTYPE_PKG
#define OCI_PTYPE_TYPE                  6                               /* user-defined type */
#define     DCI_PTYPE_TYPE                  OCI_PTYPE_TYPE
#define OCI_PTYPE_SYN                   7                               /* synonym   */
#define     DCI_PTYPE_SYN                   OCI_PTYPE_SYN
#define OCI_PTYPE_SEQ                   8                               /* sequence  */
#define     DCI_PTYPE_SEQ                   OCI_PTYPE_SEQ
#define OCI_PTYPE_COL                   9                               /* column    */
#define     DCI_PTYPE_COL                   OCI_PTYPE_COL
#define OCI_PTYPE_ARG                   10                              /* argument  */
#define     DCI_PTYPE_ARG                   OCI_PTYPE_ARG
#define OCI_PTYPE_LIST                  11                              /* list      */
#define     DCI_PTYPE_LIST                  OCI_PTYPE_LIST
#define OCI_PTYPE_TYPE_ATTR             12                              /* user-defined type's attribute */
#define     DCI_PTYPE_TYPE_ATTR             OCI_PTYPE_TYPE_ATTR
#define OCI_PTYPE_TYPE_COLL             13                              /* collection type's element */
#define     DCI_PTYPE_TYPE_COLL             OCI_PTYPE_TYPE_COLL
#define OCI_PTYPE_TYPE_METHOD           14                              /* user-defined type's method */
#define     DCI_PTYPE_TYPE_METHOD           OCI_PTYPE_TYPE_METHOD
#define OCI_PTYPE_TYPE_ARG              15                              /* user-defined type method's arg */
#define     DCI_PTYPE_TYPE_ARG              OCI_PTYPE_TYPE_ARG
#define OCI_PTYPE_TYPE_RESULT           16                              /* user-defined type method's result */
#define     DCI_PTYPE_TYPE_RESULT           OCI_PTYPE_TYPE_RESULT
#define OCI_PTYPE_SCHEMA                17                              /* schema */
#define     DCI_PTYPE_SCHEMA                OCI_PTYPE_SCHEMA
#define OCI_PTYPE_DATABASE              18                              /* database */
#define     DCI_PTYPE_DATABASE              OCI_PTYPE_DATABASE
#define OCI_PTYPE_RULE                  19                              /* rule */
#define     DCI_PTYPE_RULE                  OCI_PTYPE_RULE
#define OCI_PTYPE_RULE_SET              20                              /* rule set */
#define     DCI_PTYPE_RULE_SET              OCI_PTYPE_RULE_SET
#define OCI_PTYPE_EVALUATION_CONTEXT    21                              /* evaluation context */
#define     DCI_PTYPE_EVALUATION_CONTEXT    OCI_PTYPE_EVALUATION_CONTEXT
#define OCI_PTYPE_TABLE_ALIAS           22                              /* table alias */
#define     DCI_PTYPE_TABLE_ALIAS           OCI_PTYPE_TABLE_ALIAS
#define OCI_PTYPE_VARIABLE_TYPE         23                              /* variable type */
#define     DCI_PTYPE_VARIABLE_TYPE         OCI_PTYPE_VARIABLE_TYPE
#define OCI_PTYPE_NAME_VALUE            24                              /* name value pair */
#define     DCI_PTYPE_NAME_VALUE            OCI_PTYPE_NAME_VALUE

/*---------------------------------------------------------------------------*/

/*----------------------------- OCI List Types ------------------------------*/
#define OCI_LTYPE_UNK                   0                               /* unknown   */
#define     DCI_LTYPE_UNK                   OCI_LTYPE_UNK
#define OCI_LTYPE_COLUMN                1                               /* column list */
#define     DCI_LTYPE_COLUMN                OCI_LTYPE_COLUMN
#define OCI_LTYPE_ARG_PROC              2                               /* procedure argument list */
#define     DCI_LTYPE_ARG_PROC              OCI_LTYPE_ARG_PROC
#define OCI_LTYPE_ARG_FUNC              3                               /* function argument list */
#define     DCI_LTYPE_ARG_FUNC              OCI_LTYPE_ARG_FUNC
#define OCI_LTYPE_SUBPRG                4                               /* subprogram list */
#define     DCI_LTYPE_SUBPRG                OCI_LTYPE_SUBPRG
#define OCI_LTYPE_TYPE_ATTR             5                               /* type attribute */
#define     DCI_LTYPE_TYPE_ATTR             OCI_LTYPE_TYPE_ATTR
#define OCI_LTYPE_TYPE_METHOD           6                               /* type method */
#define     DCI_LTYPE_TYPE_METHOD           OCI_LTYPE_TYPE_METHOD
#define OCI_LTYPE_TYPE_ARG_PROC         7                               /* type method w/o result argument list */
#define     DCI_LTYPE_TYPE_ARG_PROC         OCI_LTYPE_TYPE_ARG_PROC
#define OCI_LTYPE_TYPE_ARG_FUNC         8                               /* type method w/result argument list */
#define     DCI_LTYPE_TYPE_ARG_FUNC         OCI_LTYPE_TYPE_ARG_FUNC
#define OCI_LTYPE_SCH_OBJ               9                               /* schema object list */
#define     DCI_LTYPE_SCH_OBJ               OCI_LTYPE_SCH_OBJ
#define OCI_LTYPE_DB_SCH                10                              /* database schema list */
#define     DCI_LTYPE_DB_SCH                OCI_LTYPE_DB_SCH
#define OCI_LTYPE_TYPE_SUBTYPE          11                              /* subtype list */
#define     DCI_LTYPE_TYPE_SUBTYPE          OCI_LTYPE_TYPE_SUBTYPE
#define OCI_LTYPE_TABLE_ALIAS           12                              /* table alias list */
#define     DCI_LTYPE_TABLE_ALIAS           OCI_LTYPE_TABLE_ALIAS
#define OCI_LTYPE_VARIABLE_TYPE         13                              /* variable type list */
#define     DCI_LTYPE_VARIABLE_TYPE         OCI_LTYPE_VARIABLE_TYPE
#define OCI_LTYPE_NAME_VALUE            14                              /* name value list */
#define     DCI_LTYPE_NAME_VALUE            OCI_LTYPE_NAME_VALUE

/*---------------------------------------------------------------------------*/

/*-------------------------- Memory Cartridge Services ---------------------*/
#define OCI_MEMORY_CLEARED              1
#define     DCI_MEMORY_CLEARED              OCI_MEMORY_CLEARED
/*-------------------------- Pickler Cartridge Services ---------------------*/
typedef struct OCIPicklerTdsCtx OCIPicklerTdsCtx;
typedef struct OCIPicklerTds OCIPicklerTds;
typedef struct OCIPicklerImage OCIPicklerImage;
typedef struct OCIPicklerFdo OCIPicklerFdo;
typedef ub4 OCIPicklerTdsElement;

typedef OCIPicklerTdsCtx DCIPicklerTdsCtx;
typedef OCIPicklerTds DCIPicklerTds;
typedef OCIPicklerImage DCIPicklerImage;
typedef OCIPicklerFdo DCIPicklerFdo;
typedef OCIPicklerTdsElement DCIPicklerTdsElement;

typedef struct OCIAnyData OCIAnyData;
typedef OCIAnyData DCIAnyData;

typedef struct OCIAnyDataSet OCIAnyDataSet;
typedef struct OCIAnyDataCtx OCIAnyDataCtx;
typedef OCIAnyDataSet DCIAnyDataSet;
typedef OCIAnyDataCtx DCIAnyDataCtx;

/*---------------------------------------------------------------------------*/

/*--------------------------- User Callback Constants -----------------------*/
#define OCI_UCBTYPE_ENTRY       1                          /* entry callback */
#define OCI_UCBTYPE_EXIT        2                           /* exit callback */
#define OCI_UCBTYPE_REPLACE     3                    /* replacement callback */

/*---------------------------------------------------------------------------*/

/*--------------------- NLS service type and constance ----------------------*/
#define OCI_NLS_DAYNAME1      1                    /* Native name for Monday */
#define OCI_NLS_DAYNAME2      2                   /* Native name for Tuesday */
#define OCI_NLS_DAYNAME3      3                 /* Native name for Wednesday */
#define OCI_NLS_DAYNAME4      4                  /* Native name for Thursday */
#define OCI_NLS_DAYNAME5      5                    /* Native name for Friday */
#define OCI_NLS_DAYNAME6      6              /* Native name for for Saturday */
#define OCI_NLS_DAYNAME7      7                /* Native name for for Sunday */
#define OCI_NLS_ABDAYNAME1    8        /* Native abbreviated name for Monday */
#define OCI_NLS_ABDAYNAME2    9       /* Native abbreviated name for Tuesday */
#define OCI_NLS_ABDAYNAME3    10    /* Native abbreviated name for Wednesday */
#define OCI_NLS_ABDAYNAME4    11     /* Native abbreviated name for Thursday */
#define OCI_NLS_ABDAYNAME5    12       /* Native abbreviated name for Friday */
#define OCI_NLS_ABDAYNAME6    13 /* Native abbreviated name for for Saturday */
#define OCI_NLS_ABDAYNAME7    14   /* Native abbreviated name for for Sunday */
#define OCI_NLS_MONTHNAME1    15                  /* Native name for January */
#define OCI_NLS_MONTHNAME2    16                 /* Native name for February */
#define OCI_NLS_MONTHNAME3    17                    /* Native name for March */
#define OCI_NLS_MONTHNAME4    18                    /* Native name for April */
#define OCI_NLS_MONTHNAME5    19                      /* Native name for May */
#define OCI_NLS_MONTHNAME6    20                     /* Native name for June */
#define OCI_NLS_MONTHNAME7    21                     /* Native name for July */
#define OCI_NLS_MONTHNAME8    22                   /* Native name for August */
#define OCI_NLS_MONTHNAME9    23                /* Native name for September */
#define OCI_NLS_MONTHNAME10   24                  /* Native name for October */
#define OCI_NLS_MONTHNAME11   25                 /* Native name for November */
#define OCI_NLS_MONTHNAME12   26                 /* Native name for December */
#define OCI_NLS_ABMONTHNAME1  27      /* Native abbreviated name for January */
#define OCI_NLS_ABMONTHNAME2  28     /* Native abbreviated name for February */
#define OCI_NLS_ABMONTHNAME3  29        /* Native abbreviated name for March */
#define OCI_NLS_ABMONTHNAME4  30        /* Native abbreviated name for April */
#define OCI_NLS_ABMONTHNAME5  31          /* Native abbreviated name for May */
#define OCI_NLS_ABMONTHNAME6  32         /* Native abbreviated name for June */
#define OCI_NLS_ABMONTHNAME7  33         /* Native abbreviated name for July */
#define OCI_NLS_ABMONTHNAME8  34       /* Native abbreviated name for August */
#define OCI_NLS_ABMONTHNAME9  35    /* Native abbreviated name for September */
#define OCI_NLS_ABMONTHNAME10 36      /* Native abbreviated name for October */
#define OCI_NLS_ABMONTHNAME11 37     /* Native abbreviated name for November */
#define OCI_NLS_ABMONTHNAME12 38     /* Native abbreviated name for December */
#define OCI_NLS_YES           39   /* Native string for affirmative response */
#define OCI_NLS_NO            40                 /* Native negative response */
#define OCI_NLS_AM            41           /* Native equivalent string of AM */
#define OCI_NLS_PM            42           /* Native equivalent string of PM */
#define OCI_NLS_AD            43           /* Native equivalent string of AD */
#define OCI_NLS_BC            44           /* Native equivalent string of BC */
#define OCI_NLS_DECIMAL       45                        /* decimal character */
#define OCI_NLS_GROUP         46                          /* group separator */
#define OCI_NLS_DEBIT         47                   /* Native symbol of debit */
#define OCI_NLS_CREDIT        48                  /* Native sumbol of credit */
#define OCI_NLS_DATEFORMAT    49                       /* Oracle date format */
#define OCI_NLS_INT_CURRENCY  50            /* International currency symbol */
#define OCI_NLS_LOC_CURRENCY  51                   /* Locale currency symbol */
#define OCI_NLS_LANGUAGE      52                            /* Language name */
#define OCI_NLS_ABLANGUAGE    53           /* Abbreviation for language name */
#define OCI_NLS_TERRITORY     54                           /* Territory name */
#define OCI_NLS_CHARACTER_SET 55                       /* Character set name */
#define OCI_NLS_LINGUISTIC_NAME    56                     /* Linguistic name */
#define OCI_NLS_CALENDAR      57                            /* Calendar name */
#define OCI_NLS_DUAL_CURRENCY 78                     /* Dual currency symbol */
#define OCI_NLS_WRITINGDIR    79               /* Language writing direction */
#define OCI_NLS_ABTERRITORY   80                   /* Territory Abbreviation */
#define OCI_NLS_DDATEFORMAT   81               /* Oracle default date format */
#define OCI_NLS_DTIMEFORMAT   82               /* Oracle default time format */
#define OCI_NLS_SFDATEFORMAT  83       /* Local string formatted date format */
#define OCI_NLS_SFTIMEFORMAT  84       /* Local string formatted time format */
#define OCI_NLS_NUMGROUPING   85                   /* Number grouping fields */
#define OCI_NLS_LISTSEP       86                           /* List separator */
#define OCI_NLS_MONDECIMAL    87               /* Monetary decimal character */
#define OCI_NLS_MONGROUP      88                 /* Monetary group separator */
#define OCI_NLS_MONGROUPING   89                 /* Monetary grouping fields */
#define OCI_NLS_INT_CURRENCYSEP 90       /* International currency separator */
#define OCI_NLS_CHARSET_MAXBYTESZ 91     /* Maximum character byte size      */
#define OCI_NLS_CHARSET_FIXEDWIDTH 92    /* Fixed-width charset byte size    */
#define OCI_NLS_CHARSET_ID    93                         /* Character set id */
#define OCI_NLS_NCHARSET_ID   94                        /* NCharacter set id */

#define OCI_NLS_MAXBUFSZ   100 /* Max buffer size may need for OCINlsGetInfo */

#define OCI_NLS_BINARY            0x1           /* for the binary comparison */
#define OCI_NLS_LINGUISTIC        0x2           /* for linguistic comparison */
#define OCI_NLS_CASE_INSENSITIVE  0x10    /* for case-insensitive comparison */

#define OCI_NLS_UPPERCASE           0x20               /* convert to uppercase */
#define     DCI_NLS_UPPERCASE       OCI_NLS_UPPERCASE
#define OCI_NLS_LOWERCASE           0x40               /* convert to lowercase */
#define     DCI_NLS_LOWERCASE       OCI_NLS_LOWERCASE

#define OCI_NLS_CS_IANA_TO_ORA   0   /* Map charset name from IANA to Oracle */
#define OCI_NLS_CS_ORA_TO_IANA   1   /* Map charset name from Oracle to IANA */
#define OCI_NLS_LANG_ISO_TO_ORA  2   /* Map language name from ISO to Oracle */
#define OCI_NLS_LANG_ORA_TO_ISO  3   /* Map language name from Oracle to ISO */
#define OCI_NLS_TERR_ISO_TO_ORA  4   /* Map territory name from ISO to Oracle*/
#define OCI_NLS_TERR_ORA_TO_ISO  5   /* Map territory name from Oracle to ISO*/
#define OCI_NLS_TERR_ISO3_TO_ORA 6   /* Map territory name from 3-letter ISO */
                                     /* abbreviation to Oracle               */
#define OCI_NLS_TERR_ORA_TO_ISO3 7   /* Map territory name from Oracle to    */
                                     /* 3-letter ISO abbreviation            */

typedef struct OCIMsg  OCIMsg;
typedef ub4            OCIWchar;

#define OCI_XMLTYPE_CREATE_OCISTRING 1
#define OCI_XMLTYPE_CREATE_CLOB      2
#define OCI_XMLTYPE_CREATE_BLOB      3

/*------------------------- Kerber Authentication Modes ---------------------*/
#define OCI_KERBCRED_PROXY               1 /* Apply Kerberos Creds for Proxy */
#define OCI_KERBCRED_CLIENT_IDENTIFIER   2/*Apply Creds for Secure Client ID */

/*--------------------------------------------------------------------------- 
                     PRIVATE TYPES AND CONSTANTS 
  ---------------------------------------------------------------------------*/
struct OCITime
{
  ub1 OCITimeHH;                          /* hours; range is 0 <= hours <=23 */
  ub1 OCITimeMI;                     /* minutes; range is 0 <= minutes <= 59 */
  ub1 OCITimeSS;                     /* seconds; range is 0 <= seconds <= 59 */
};
typedef struct OCITime OCITime;
typedef OCITime DCITime;
/* 
 * OCITime - OCI TiMe portion of date
 *
 * This structure should be treated as an opaque structure as the format
 * of this structure may change. Use OCIDateGetTime/OCIDateSetTime 
 * to manipulate time portion of OCIDate.
 */

struct OCIDate
{
  sb2 OCIDateYYYY;         /* gregorian year; range is -4712 <= year <= 9999 */
  ub1 OCIDateMM;                          /* month; range is 1 <= month < 12 */
  ub1 OCIDateDD;                             /* day; range is 1 <= day <= 31 */
  OCITime OCIDateTime;                                               /* time */
};
typedef struct OCIDate OCIDate; 
typedef OCIDate DCIDate;

// #define OCIDateGetTime(date, hour, min, sec) \
// { \
//     *hour = (date)->OCIDateTime.OCITimeHH; \
//     *min = (date)->OCIDateTime.OCITimeMI; \
//     *sec = (date)->OCIDateTime.OCITimeSS; \
// }
// #define DCIDateGetTime(date, hour, min, sec) \
// { \
//     *hour = (date)->OCIDateTime.OCITimeHH; \
//     *min = (date)->OCIDateTime.OCITimeMI; \
//     *sec = (date)->OCIDateTime.OCITimeSS; \
// }
/*
   NAME: OCIDateGetTime - OCIDate Get Time portion of date
   PARAMETERS:
  	date (IN) - Oracle date whose time data is retrieved
	hour (OUT) - hour value returned
	min (OUT) - minute value returned
	sec (OUT) - second value returned
   DESCRIPTION:
  	Return time inforamtion stored in the given date. The time
	information returned is: hour, minute and seconds.
   RETURNS:
        NONE
 */

/*--------------------------- OCIDateGetDate --------------------------------*/
/*void OCIDateGetDate(CONST OCIDate *date, sb2 *year, ub1 *month, 
ub1 *day); */ 
// #define OCIDateGetDate(date, year, month, day) \
// { \
//     *year = (date)->OCIDateYYYY; \
//     *month = (date)->OCIDateMM; \
//     *day = (date)->OCIDateDD; \
// }
// #define DCIDateGetDate(date, year, month, day) \
// { \
//     *year = (date)->OCIDateYYYY; \
//     *month = (date)->OCIDateMM; \
//     *day = (date)->OCIDateDD; \
// }
/*
   NAME: OCIDateGetDate - OCIDate Get Date (year, month, day) portion of date
   PARAMETERS:
  	date (IN) - Oracle date whose year, month, day data is retrieved
	year (OUT) - year value returned
	month (OUT) - month value returned
	day (OUT) - day value returned
   DESCRIPTION:
  	Return year, month, day inforamtion stored in the given date.
   RETURNS:
        NONE
 */

/*--------------------------- OCIDateSetTime --------------------------------*/
//void OCIDateSetTime(OCIDate *date, ub1 hour, ub1 min, 
//                           ub1 sec );  
// #define OCIDateSetTime(date, hour, min, sec) \
// { \
//     (date)->OCIDateTime.OCITimeHH = hour; \
//     (date)->OCIDateTime.OCITimeMI = min; \
//     (date)->OCIDateTime.OCITimeSS = sec; \
// }
// #define DCIDateSetTime(date, hour, min, sec) \
// { \
//     (date)->OCIDateTime.OCITimeHH = hour; \
//     (date)->OCIDateTime.OCITimeMI = min; \
//     (date)->OCIDateTime.OCITimeSS = sec; \
// }
/*
   NAME: OCIDateSetTime - OCIDate Set Time portion of date
   PARAMETERS:
  	date (OUT) - Oracle date whose time data is set
	hour (IN) - hour value to be set 
	min (IN) - minute value to be set
	sec (IN) - second value to be set
   DESCRIPTION:
  	Set the date with the given time inforamtion.
   RETURNS:
        NONE
 */

/*--------------------------- OCIDateSetDate --------------------------------*/
//void OCIDateSetDate(OCIDate *date, sb2 year, ub1 month, ub1 day );

// #define OCIDateSetDate(date, year, month, day) \
// { \
//     (date)->OCIDateYYYY = year; \
//     (date)->OCIDateMM = month; \
//     (date)->OCIDateDD = day; \
// }
// #define DCIDateSetDate(date, year, month, day) \
// { \
//     (date)->OCIDateYYYY = year; \
//     (date)->OCIDateMM = month; \
//     (date)->OCIDateDD = day; \
// }
/* see ociap.h or ocikp.h */
 
/*--------------------------------------------------------------------------- 
                          PRIVATE FUNCTIONS 
  ---------------------------------------------------------------------------*/
struct cda_head {
    sb2             v2_rc;
    ub2             ft;
    ub4             rpc;
    ub2             peo;
    ub1             fc;
    ub1             rcs1;
    ub2             rc;
    ub1             wrn;
    ub1             rcs2;
    sword           rcs3;
    struct {
        struct {
           ub4      rcs4;
           ub2      rcs5;
           ub1      rcs6;
        } rd;
        ub4         rcs7;
        ub2         rcs8;
    } rid;
    sword           ose;
    ub1             chk;
    dvoid*          rcsp;
};

/*
** Size of HDA area:
** 512 for 64 bit arquitectures
** 256 for 32 bit arquitectures
*/

#if defined(SS_64BIT_SERVER) || defined(__64BIT__)
# define HDA_SIZE 512
#else
# define HDA_SIZE 256
#endif

#if defined(SS_64BIT_SERVER) || defined(__64BIT__)
#define CDA_SIZE 88
#else
# define CDA_SIZE 64
#endif

/* the real CDA, padded to CDA_SIZE bytes in size */
struct cda_def {
    sb2             v2_rc;                                  /* V2 return code */
    ub2             ft;                                     /* SQL function type */
    ub4             rpc;                                    /* rows processed count */
    ub2             peo;                                    /* parse error offset */
    ub1             fc;                                     /* OCI function code */
    ub1             rcs1;                                   /* filler area */
    ub2             rc;                                     /* V7 return code */
    ub1             wrn;                                    /* warning flags */
    ub1             rcs2;                                   /* reserved */
    sword           rcs3;                                   /* reserved */
    struct {                                                /* rowid structure */
        struct {
           ub4      rcs4;
           ub2      rcs5;
           ub1      rcs6;
        } rd;
        ub4         rcs7;
        ub2         rcs8;
    } rid;
    sword           ose;                                                /* OSD dependent error */
    ub1             chk;
    dvoid*          rcsp;                                               /* pointer to reserved area */
    ub1             rcs9[CDA_SIZE - sizeof (struct cda_head)];          /* filler */
};

typedef struct cda_def Cda_Def;

/* the logon data area (LDA)
   is the same shape as the CDA */
typedef struct cda_def Lda_Def;

/* OCI Environment Modes for opinit call */
#define OCI_EV_DEF 0                  /* default single-threaded environment */
#define OCI_EV_TSF 1                              /* thread-safe environment */

/* OCI Logon Modes for olog call */
#define OCI_LM_DEF 0                                        /* default login */
#define OCI_LM_NBL 1                                   /* non-blocking logon */

/* valuses for crsfc */
#define csrfpa                      2               /* ...OSQL */
#define csrfex                      4               /* ...OEXEC */
#define csrfbi                      6               /* ...OBIND */
#define csrfdb                      8               /* ...ODFINN */
#define csrfdi                      10              /* ...ODSRBN */
#define csrffe                      12              /* ...OFETCH */
#define csrfop                      14              /* ...OOPEN */
#define csrfcl                      16              /* ...OCLOSE */
#define csrfds                      22              /* ...ODSC */
#define csrfnm                      24              /* ...ONAME */
#define csrfp3                      26              /* ...OSQL3 */
#define csrfbr                      28              /* ...OBNDRV */
#define csrfbx                      30              /* ...OBNDRN */
#define csrfso                      34              /* ...OOPT */
#define csrfre                      36              /* ...ORESUM */
#define csrfbn                      50              /* ...OBINDN */
#define csrfca                      52              /* ..OCANCEL */
#define csrfsd                      54              /* ..OSQLD */
#define csrfef                      56              /* ..OEXFEN */
#define csrfln                      58              /* ..OFLNG */
#define csrfdp                      60              /* ..ODSCSP */
#define csrfba                      62              /* ..OBNDRA */
#define csrfbps                     63              /*..OBINDPS */
#define csrfdps                     64              /*..ODEFINPS */
#define csrfgpi                     65              /* ...OGETPI */
#define csrfspi                     66              /* ...OSETPI */

/* values for csrwrn */
#define CSRWANY  0x01                         /* there is a warning flag set */
#define CSRWTRUN 0x02                           /* a data item was truncated */
#define CSRWNVIC 0x04      /* NULL values were used in an aggregate function */
#define CSRWITCE 0x08           /* column count not equal to into list count */
#define CSRWUDNW 0x10               /* update or delete without where clause */
#define CSRWRSV0 0x20
#define CSRWROLL 0x40                                   /* rollback required */
#define CSRWRCHG 0x80       /* change after query start on select for update */

/*----- values for OCI_ATTR_DIRPATH_SKIPINDEX_METHOD attribute -----*/
#define OCI_DIRPATH_INDEX_MAINT_SKIP_UNUSABLE       2
#define     DCI_DIRPATH_INDEX_MAINT_SKIP_UNUSABLE       OCI_DIRPATH_INDEX_MAINT_SKIP_UNUSABLE
#define OCI_DIRPATH_INDEX_MAINT_DONT_SKIP_UNUSABLE  3
#define     DCI_DIRPATH_INDEX_MAINT_DONT_SKIP_UNUSABLE  OCI_DIRPATH_INDEX_MAINT_DONT_SKIP_UNUSABLE
#define OCI_DIRPATH_INDEX_MAINT_SKIP_ALL            4
#define     DCI_DIRPATH_INDEX_MAINT_SKIP_ALL            OCI_DIRPATH_INDEX_MAINT_SKIP_ALL

           /* values for OCI_ATTR_STATE attribute of OCIDirPathCtx */
#define OCI_DIRPATH_NORMAL                          1               /* can accept rows, last row complete */
#define     DCI_DIRPATH_NORMAL                          OCI_DIRPATH_NORMAL
#define OCI_DIRPATH_PARTIAL                         2               /* last row was partial */
#define     DCI_DIRPATH_PARTIAL                         OCI_DIRPATH_PARTIAL
#define OCI_DIRPATH_NOT_PREPARED                    3               /* direct path context is not prepared */
#define     DCI_DIRPATH_NOT_PREPARED                    OCI_DIRPATH_NOT_PREPARED

     /*----- values for cflg argument to OCIDirpathColArrayEntrySet -----*/
#define OCI_DIRPATH_COL_COMPLETE                    0               /* column data is complete */
#define     DCI_DIRPATH_COL_COMPLETE                    OCI_DIRPATH_COL_COMPLETE
#define OCI_DIRPATH_COL_NULL                        1               /* column is null */
#define     DCI_DIRPATH_COL_NULL                        OCI_DIRPATH_COL_NULL
#define OCI_DIRPATH_COL_PARTIAL                     2               /* column data is partial */
#define     DCI_DIRPATH_COL_PARTIAL                     OCI_DIRPATH_COL_PARTIAL
#define OCI_DIRPATH_COL_ERROR                       3               /* column error, ignore row */
#define     DCI_DIRPATH_COL_ERROR                       OCI_DIRPATH_COL_ERROR
/*----- values for action parameter to OCIDirPathDataSave -----*/
#define OCI_DIRPATH_DATASAVE_SAVEONLY               0               /* data save point only */
#define     DCI_DIRPATH_DATASAVE_SAVEONLY               OCI_DIRPATH_DATASAVE_SAVEONLY
#define OCI_DIRPATH_DATASAVE_FINISH                 1               /* execute finishing logic */
#define     DCI_DIRPATH_DATASAVE_FINISH                 OCI_DIRPATH_DATASAVE_FINISH
/* save portion of input data (before space error occurred) and finish */
#define OCI_DIRPATH_DATASAVE_PARTIAL                2
#define     DCI_DIRPATH_DATASAVE_PARTIAL                OCI_DIRPATH_DATASAVE_PARTIAL

/*- OCI_ATTR_DIRPATH_EXPR_TYPE values (describes OCI_ATTR_NAME expr type) -*/
#define OCI_DIRPATH_EXPR_OBJ_CONSTR                 1               /* NAME is an object constructor */
#define     DCI_DIRPATH_EXPR_OBJ_CONSTR                 OCI_DIRPATH_EXPR_OBJ_CONSTR
#define OCI_DIRPATH_EXPR_SQL                        2               /* NAME is an opaque or sql function */
#define     DCI_DIRPATH_EXPR_SQL                        OCI_DIRPATH_EXPR_SQL
#define OCI_DIRPATH_EXPR_REF_TBLNAME                3               /* NAME is table name if ref is scoped*/
#define     DCI_DIRPATH_EXPR_REF_TBLNAME                OCI_DIRPATH_EXPR_REF_TBLNAME

/* Listing of error bits used by OCIDateCheck() */
#define OCI_DATE_INVALID_DAY                        0x1             /* Bad DAy */
#define     DCI_DATE_INVALID_DAY                        OCI_DATE_INVALID_DAY
#define OCI_DATE_DAY_BELOW_VALID                    0x2             /* Bad DAy Low/high bit (1=low)*/
#define     DCI_DATE_DAY_BELOW_VALID                    OCI_DATE_DAY_BELOW_VALID
#define OCI_DATE_INVALID_MONTH                      0x4             /* Bad MOnth */
#define     DCI_DATE_INVALID_MONTH                      OCI_DATE_INVALID_MONTH
#define OCI_DATE_MONTH_BELOW_VALID                  0x8             /* Bad MOnth Low/high bit (1=low)*/
#define     DCI_DATE_MONTH_BELOW_VALID                  OCI_DATE_MONTH_BELOW_VALID
#define OCI_DATE_INVALID_YEAR                       0x10            /* Bad YeaR */
#define     DCI_DATE_INVALID_YEAR                       OCI_DATE_INVALID_YEAR
#define OCI_DATE_YEAR_BELOW_VALID                   0x20            /* Bad YeaR Low/high bit (1=low)*/
#define     DCI_DATE_YEAR_BELOW_VALID                   OCI_DATE_YEAR_BELOW_VALID
#define OCI_DATE_INVALID_HOUR                       0x40            /* Bad HouR */
#define     DCI_DATE_INVALID_HOUR                       OCI_DATE_INVALID_HOUR
#define OCI_DATE_HOUR_BELOW_VALID                   0x80            /* Bad HouR Low/high bit (1=low)*/
#define     DCI_DATE_HOUR_BELOW_VALID                   OCI_DATE_HOUR_BELOW_VALID
#define OCI_DATE_INVALID_MINUTE                     0x100           /* Bad MiNute */
#define     DCI_DATE_INVALID_MINUTE                     OCI_DATE_INVALID_MINUTE
#define OCI_DATE_MINUTE_BELOW_VALID                 0x200           /* Bad MiNute Low/high bit (1=low)*/
#define     DCI_DATE_MINUTE_BELOW_VALID                 OCI_DATE_MINUTE_BELOW_VALID
#define OCI_DATE_INVALID_SECOND                     0x400           /* Bad SeCond */
#define     DCI_DATE_INVALID_SECOND                     OCI_DATE_INVALID_SECOND
#define OCI_DATE_SECOND_BELOW_VALID                 0x800           /* bad second Low/high bit (1=low)*/
#define     DCI_DATE_SECOND_BELOW_VALID                 OCI_DATE_SECOND_BELOW_VALID
#define OCI_DATE_DAY_MISSING_FROM_1582              0x1000          /* Day is one of those "missing" from 1582 */
#define     DCI_DATE_DAY_MISSING_FROM_1582              OCI_DATE_DAY_MISSING_FROM_1582
#define OCI_DATE_YEAR_ZERO                          0x2000          /* Year may not equal zero */
#define     DCI_DATE_YEAR_ZERO                          OCI_DATE_YEAR_ZERO
#define OCI_DATE_INVALID_FORMAT                     0x8000          /* Bad date format input */
#define     DCI_DATE_INVALID_FORMAT                     OCI_DATE_INVALID_FORMAT

/* Listing of error bits used by OCIDateTimeCheck() */
#define OCI_DT_INVALID_DAY              0x1     /*Bad day*/
#define     DCI_DT_INVALID_DAY              OCI_DT_INVALID_DAY
#define OCI_DT_DAY_BELOW_VALID          0x2     /*Bad day low/high bit (1=low)*/
#define     DCI_DT_DAY_BELOW_VALID          OCI_DT_DAY_BELOW_VALID
#define OCI_DT_INVALID_MONTH            0x4     /*Bad month*/
#define     DCI_DT_INVALID_MONTH            OCI_DT_INVALID_MONTH
#define OCI_DT_MONTH_BELOW_VALID        0x8     /*Bad month low/high bit (1=low)*/
#define     DCI_DT_MONTH_BELOW_VALID        OCI_DT_MONTH_BELOW_VALID
#define OCI_DT_INVALID_YEAR             0x10    /*Bad year*/
#define     DCI_DT_INVALID_YEAR             OCI_DT_INVALID_YEAR
#define OCI_DT_YEAR_BELOW_VALID         0x20    /*Bad year low/high bit (1=low)*/
#define     DCI_DT_YEAR_BELOW_VALID         OCI_DT_YEAR_BELOW_VALID
#define OCI_DT_INVALID_HOUR             0x40    /*Bad hour*/
#define     DCI_DT_INVALID_HOUR             OCI_DT_INVALID_HOUR
#define OCI_DT_HOUR_BELOW_VALID         0x80    /*Bad hour low/high bit (1=low)*/
#define     DCI_DT_HOUR_BELOW_VALID         OCI_DT_HOUR_BELOW_VALID
#define OCI_DT_INVALID_MINUTE           0x100   /*Bad minute*/
#define     DCI_DT_INVALID_MINUTE           OCI_DT_INVALID_MINUTE
#define OCI_DT_MINUTE_BELOW_VALID       0x200   /*Bad minute low/high bit (1=low)*/
#define     DCI_DT_MINUTE_BELOW_VALID       OCI_DT_MINUTE_BELOW_VALID
#define OCI_DT_INVALID_SECOND           0x400   /*Bad second*/
#define     DCI_DT_INVALID_SECOND           OCI_DT_INVALID_SECOND
#define OCI_DT_SECOND_BELOW_VALID       0x800   /*Bad second low/high bit (1=low)*/
#define     DCI_DT_SECOND_BELOW_VALID       OCI_DT_SECOND_BELOW_VALID
#define OCI_DT_DAY_MISSING_FROM_1582    0x1000  /*Day is one of those missing from 1582*/
#define     DCI_DT_DAY_MISSING_FROM_1582    OCI_DT_DAY_MISSING_FROM_1582
#define OCI_DT_YEAR_ZERO                0x2000  /*Year may not equal zero*/
#define     DCI_DT_YEAR_ZERO                OCI_DT_YEAR_ZERO
#define OCI_DT_INVALID_TIMEZONE         0x4000  /*Bad time zone*/
#define     DCI_DT_INVALID_TIMEZONE         OCI_DT_INVALID_TIMEZONE
#define OCI_DT_INVALID_FORMAT           0x8000  /*Bad date format input*/
#define     DCI_DT_INVALID_FORMAT           OCI_DT_INVALID_FORMAT

typedef struct OCIDirPathCtx      OCIDirPathCtx;                  /* context */
typedef struct OCIDirPathFuncCtx  OCIDirPathFuncCtx;     /* function context */
typedef struct OCIDirPathColArray OCIDirPathColArray;        /* column array */
typedef struct OCIDirPathStream   OCIDirPathStream;                /* stream */
typedef struct OCIDirPathDesc     OCIDirPathDesc;  /* direct path descriptor */
typedef OCIDirPathCtx      DCIDirPathCtx;                  /* context */
typedef OCIDirPathFuncCtx  DCIDirPathFuncCtx;     /* function context */
typedef OCIDirPathColArray DCIDirPathColArray;        /* column array */
typedef OCIDirPathStream   DCIDirPathStream;                /* stream */
typedef OCIDirPathDesc     DCIDirPathDesc;  /* direct path descriptor */

typedef sb4 (*OCICallbackInBind)(dvoid *ictxp, OCIBind *bindp, ub4 iter,
                                  ub4 index, dvoid **bufpp, ub4 *alenp,
                                  ub1 *piecep, dvoid **indp);
typedef OCICallbackInBind DCICallbackInBind;

typedef sb4 (*OCICallbackOutBind)(dvoid *octxp, OCIBind *bindp, ub4 iter,
                                 ub4 index, dvoid **bufpp, ub4 **alenp,
                                 ub1 *piecep, dvoid **indp,
                                 ub2 **rcodep);
typedef OCICallbackOutBind DCICallbackOutBind;

typedef sb4 (*OCICallbackDefine)(dvoid *octxp, OCIDefine *defnp, ub4 iter,
 dvoid **bufpp, ub4 **alenp, ub1 *piecep,
 dvoid **indp, ub2 **rcodep);
typedef OCICallbackDefine DCICallbackDefine;

/*number*/
#define OCI_NUMBER_SIZE 22
struct OCINumber
{
    ub1 OCINumberPart[OCI_NUMBER_SIZE];
};
typedef struct OCINumber OCINumber;
typedef OCINumber DCINumber;

OCI_API
OCIEnv *xaoEnv(OraText *dbname); 

OCI_API
OCISvcCtx *xaoSvcCtx(OraText *dbname);

OCI_API sword   
#ifdef OCI_EXPORT
OCIInitialize(
#else
DCIInitialize(
#endif // OCI_EXPORT
    ub4         mode, 
    dvoid*      ctxp, 
    dvoid*      (*malocfp)(dvoid *ctxp, size_t size),
    dvoid*      (*ralocfp)(dvoid *ctxp, dvoid *memptr, size_t newsize),
    void        (*mfreefp)(dvoid *ctxp, dvoid *memptr)
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIEnvInit(
#else
DCIEnvInit(
#endif // OCI_EXPORT
    OCIEnv**    envp, 
    ub4         mode, 
    size_t      xtramem_sz,
    dvoid**     usrmempp
);

OCI_API sword	
#ifdef OCI_EXPORT
OCIEnvCreate(
#else
DCIEnvCreate(
#endif // OCI_EXPORT
    OCIEnv**        envhpp, 
    ub4             mode, 
    const void*     ctxp, 
    const void*     (*malocfp) (dvoid *ctxp, size_t size), 
    const void*     (*ralocfp) (dvoid *ctxp, dvoid *memptr, size_t newsize), 
    const void      (*mfreefp) (dvoid *ctxp, dvoid *memptr), 
    size_t          xtramemsz,
    dvoid**         usrmempp
);

OCI_API 
sword  
#ifdef OCI_EXPORT
OCIEnvNlsCreate(
#else
DCIEnvNlsCreate(
#endif // OCI_EXPORT
    OCIEnv**        envhpp,
    ub4             mode,
    void*           ctxp,
    void*           (*malocfp)(void  *ctxp, size_t size),
    void*           (*ralocfp)(void  *ctxp, void  *memptr, size_t newsize),
    void            (*mfreefp)(void  *ctxp, void  *memptr),
    size_t          xtramemsz,
    void**          usrmempp,
    ub2             charset,
    ub2             ncharset
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIHandleAlloc(
#else
DCIHandleAlloc(
#endif // OCI_EXPORT
    dvoid*          parenth,
    dvoid**         hndlpp,
    CONST ub4       type, 
    CONST size_t    xtramem_sz,
    dvoid**         usrmempp
);

OCI_API sword
#ifdef OCI_EXPORT
OCIHandleFree(
#else
DCIHandleFree(
#endif // OCI_EXPORT
    dvoid*          hndlp,
    CONST ub4       type
);

OCI_API sword   
#ifdef OCI_EXPORT
OCISessionBegin(
#else
DCISessionBegin(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCISession*     usrhp,
    ub4             credt,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIServerAttach(
#else
DCIServerAttach(
#endif // OCI_EXPORT
    OCIServer*      srvhp,
    OCIError*       errhp,
    CONST OraText*  dblink,
    sb4             dblink_len,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIStmtPrepare(
#else
DCIStmtPrepare(
#endif // OCI_EXPORT
    OCIStmt*        stmtp,
    OCIError*       errhp,
    OraText*        stmt,
    ub4             stmt_len,
    ub4             language,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIStmtGetPieceInfo(
#else
DCIStmtGetPieceInfo(
#endif // OCI_EXPORT
    OCIStmt*        stmtp,
    OCIError*       errhp, 
    dvoid**         hndlpp,
    ub4*            typep,
    ub1*            in_outp,
    ub4*            iterp,
    ub4*            idxp, 
    ub1*            piecep
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIStmtSetPieceInfo(
#else
DCIStmtSetPieceInfo(
#endif // OCI_EXPORT
    dvoid*          hndlp,
    ub4             type,
    OCIError*       errhp, 
    CONST dvoid*    bufp,
    ub4*            alenp,
    ub1             piece, 
    CONST dvoid*    indp,
    ub2*            rcodep
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIStmtExecute(
#else
DCIStmtExecute(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIStmt*        stmtp,
    OCIError*       errhp, 
    ub4             iters,
    ub4             rowoff,
    CONST OCISnapshot*  snap_in, 
    OCISnapshot*    snap_out,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIStmtFetch(
#else
DCIStmtFetch(
#endif // OCI_EXPORT
    OCIStmt*        stmtp,
    OCIError*       errhp,
    ub4             nrows, 
    ub2             orientation,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIDefineByPos(
#else
DCIDefineByPos(
#endif // OCI_EXPORT
    OCIStmt*        stmtp,
    OCIDefine**     defnp,
    OCIError*       errhp,
    ub4             position,
    dvoid*          valuep,
    sb4             value_sz,
    ub2             dty,
    dvoid*          indp,
    ub2*            rlenp,
    ub2*            rcodep,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIErrorGet(
#else
DCIErrorGet(
#endif // OCI_EXPORT
    dvoid*          hndlp,
    ub4             recordno,
    OraText*        sqlstate,
    sb4*            errcodep,
    OraText*        bufp,
    ub4             bufsiz,
    ub4             type
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIBindByPos(
#else
DCIBindByPos(
#endif // OCI_EXPORT
    OCIStmt*        stmtp,
    OCIBind**       bindp,
    OCIError*       errhp,
    ub4             position,
    dvoid*          valuep,
    sb4             value_sz,
    ub2             dty,
    dvoid*          indp,
    ub2*            alenp,
    ub2*            rcodep,
    ub4             maxarr_len,
    ub4*            curelep,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIBindByName(
#else
DCIBindByName(
#endif // OCI_EXPORT
    OCIStmt*        stmtp,
    OCIBind**       bindp,
    OCIError*       errhp,
    CONST OraText*  placeholder,
    sb4             placeh_len, 
    dvoid*          valuep,
    sb4             value_sz,
    ub2             dty, 
    dvoid*          indp,
    ub2*            alenp,
    ub2*            rcodep, 
    ub4             maxarr_len,
    ub4*            curelep,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIBindDynamic(
#else
DCIBindDynamic(
#endif // OCI_EXPORT
    OCIBind*        bindp,
    OCIError*       errhp,
    void            *ictxp,  
    OCICallbackInBind   icbfp,
    dvoid*          octxp,
    OCICallbackOutBind  ocbfp 
);

OCI_API sword   
#ifdef OCI_EXPORT
OCILogon(
#else
DCILogon(
#endif // OCI_EXPORT
    OCIEnv*         envhp,
    OCIError*       errhp,
    OCISvcCtx**     svchp, 
    CONST OraText*  username,
    ub4             uname_len, 
    CONST OraText*  password,
    ub4             passwd_len, 
    CONST OraText*  dbname,
    ub4             dbname_len
);

OCI_API sword
#ifdef OCI_EXPORT
OCILogoff(
#else
DCILogoff(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIPasswordChange(
#else
DCIPasswordChange(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp, 
    CONST OraText*  user_name,
    ub4             usernm_len, 
    CONST OraText*  opasswd,
    ub4             opasswd_len, 
    CONST OraText*  npasswd,
    ub4             npasswd_len, 
    ub4             mode
);

OCI_API sword
#ifdef OCI_EXPORT
OCITransStart(
#else
DCITransStart(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    uword           timeout,
    ub4             flags
);

OCI_API sword
#ifdef OCI_EXPORT
OCITransCommit(
#else
DCITransCommit(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    ub4             flags
);

OCI_API sword 
#ifdef OCI_EXPORT
OCITransRollback(
#else
DCITransRollback(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    ub4             flags
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIServerDetach(
#else
DCIServerDetach(
#endif // OCI_EXPORT
    OCIServer*      srvhp,
    OCIError*       errhp,
    ub4             mode
);

OCI_API sword   
#ifdef OCI_EXPORT
OCISessionEnd(
#else
DCISessionEnd(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCISession*     usrhp, 
    ub4             mode
);

OCI_API sword
#ifdef OCI_EXPORT
OCIAttrGet(
#else
DCIAttrGet(
#endif // OCI_EXPORT
    CONST dvoid*    trgthndlp,
    ub4             trghndltyp, 
    dvoid*          attributep,
    ub4*            sizep,
    ub4             attrtype, 
    OCIError*       errhp
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIAttrSet(
#else
DCIAttrSet(
#endif // OCI_EXPORT
    dvoid*          trgthndlp,
    ub4             trghndltyp,
    dvoid*          attributep,
    ub4             size,
    ub4             attrtype,
    OCIError*       errhp
);

OCI_API sword  
#ifdef OCI_EXPORT
OCIParamGet(
#else
DCIParamGet(
#endif // OCI_EXPORT
    CONST dvoid*    hndlp,
    ub4             htype,
    OCIError*       errhp, 
    dvoid**         parmdpp,
    ub4             pos
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIParamSet(
#else
DCIParamSet(
#endif // OCI_EXPORT
    dvoid*          hdlp,
    ub4             htyp,
    OCIError*       errhp,
    CONST dvoid*    dscp,
    ub4             dtyp,
    ub4             pos
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIDescribeAny(
#else
DCIDescribeAny(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp, 
    dvoid*          objptr, 
    ub4             objnm_len,
    ub1             objptr_typ,
    ub1             info_level,
    ub1             objtyp,
    OCIDescribe*    dschp
);

OCI_API sword
#ifdef OCI_EXPORT
OCIBindArrayOfStruct(
#else
DCIBindArrayOfStruct(
#endif // OCI_EXPORT
    OCIBind*        bindp,
    OCIError*       errhp,
    ub4             pvskip,
    ub4             indskip,
    ub4             alskip,
    ub4             rcskip
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIDefineArrayOfStruct(
#else
DCIDefineArrayOfStruct(
#endif // OCI_EXPORT
    OCIDefine*      defnp,
    OCIError*       errhp,
    ub4             pvskip,
    ub4             indskip,
    ub4             rlskip,
    ub4             rcskip
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDescriptorAlloc(
#else
DCIDescriptorAlloc(
#endif // OCI_EXPORT
    CONST dvoid*    parenth,
    dvoid**         descpp, 
    CONST ub4       type,
    CONST size_t    xtramem_sz, 
    dvoid**         usrmempp
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDescriptorFree(
#else
DCIDescriptorFree(
#endif // OCI_EXPORT
    dvoid*          descp,
    CONST ub4       type
);

OCI_API sword 
#ifdef OCI_EXPORT
OCILobWrite(
#else
DCILobWrite(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCILobLocator*  locp,
    ub4*            amtp,
    ub4             offset,
    dvoid*          bufp,
    ub4             buflen, 
    ub1             piece,
    dvoid*          ctxp, 
    sb4             (*cbfp)(dvoid *ctxp, dvoid* bufp, ub4* len, ub1* piece),
    ub2             csid,
    ub1             csfrm
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIBreak(
#else
DCIBreak(
#endif // OCI_EXPORT
    dvoid*          hndlp,
    OCIError*       errhp
);

OCI_API sword   
#ifdef OCI_EXPORT
OCIReset(
#else
DCIReset(
#endif // OCI_EXPORT
    dvoid*          hndlp,
    OCIError*       errhp
);

OCI_API sword   
#ifdef OCI_EXPORT
OCILobGetLength(
#else
DCILobGetLength(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp, 
    OCILobLocator*  locp,
    ub4*            lenp
);

OCI_API sword   
#ifdef OCI_EXPORT
OCILobRead(
#else
DCILobRead(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCILobLocator*  locp,
    ub4*            amtp,
    ub4             offset,
    dvoid*          bufp,
    ub4             bufl, 
    dvoid*          ctxp,
    sb4             (*cbfp)(dvoid* ctxp, CONST dvoid* bufp, ub4 len, ub1 piece),
    ub2             csid,
    ub1             csfrm
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobRead2 (  
#else
DCILobRead2 (
#endif // OCI_EXPORT
    OCISvcCtx*          svchp,
    OCIError*           errhp,
    OCILobLocator*      locp,
    oraub8*             byte_amtp,
    oraub8*             char_amtp,
    oraub8              offset,
    void*               bufp,
    oraub8              bufl,
    ub1                 piece,
    void*               ctxp, 
    sb4 (*cbfp)(void* ctxp, const void* bufp, oraub8 lenp, ub1 piecep, void** changed_bufpp, oraub8* changed_lenp),
    ub2                 csid,
    ub1                 csfrm
);

OCI_API sword 
#ifdef OCI_EXPORT
OCIStmtFetch2(
#else
DCIStmtFetch2(
#endif // OCI_EXPORT
    OCIStmt*        stmtp,
    OCIError*       errhp,
    ub4             nrows, 
    ub2             orientation,
    sb4             scrollOffset,
    ub4             mode
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathPrepare(
#else
DCIDirPathPrepare(
#endif // OCI_EXPORT
	OCIDirPathCtx*  dpctx, 
	OCISvcCtx*      svchp,
    OCIError*       errhp
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathColArrayReset(
#else
DCIDirPathColArrayReset(
#endif // OCI_EXPORT
	OCIDirPathColArray* dpca, 
	OCIError*       errhp 
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathStreamReset(
#else
DCIDirPathStreamReset(
#endif // OCI_EXPORT
	OCIDirPathStream*   dpstr, 
	OCIError*       errhp 
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathColArrayEntrySet(
#else
DCIDirPathColArrayEntrySet(
#endif // OCI_EXPORT
	OCIDirPathColArray* dpca, 
	OCIError*       errhp,
    ub4             rownum, 
	ub2             colIdx, 
	ub1*            cvalp, 
	ub4             clen,
    ub1             cflg 
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathColArrayEntryGet(
#else
DCIDirPathColArrayEntryGet(
#endif // OCI_EXPORT
    OCIDirPathColArray*         dpca,
    OCIError*                   errhp,
    ub4                         rownum,
    ub2                         colIdx,
    ub1**                       cvalpp,
    ub4*                        clenp,
    ub1*                        cflgp
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathDataSave(
#else
DCIDirPathDataSave(
#endif // OCI_EXPORT 
	OCIDirPathCtx*  dpctx, 
	OCIError*       errhp, 
	ub4             action 
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathColArrayToStream(
#else
DCIDirPathColArrayToStream(
#endif // OCI_EXPORT
	OCIDirPathColArray* dpca,  
	OCIDirPathCtx*      dpctx,
    OCIDirPathStream*   dpstr, 
	OCIError*           errhp,
    ub4                 rowcnt,
    ub4                 rowoff
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathFinish(
#else
DCIDirPathFinish(
#endif // OCI_EXPORT
	OCIDirPathCtx*      dpctx,
	OCIError*           errhp
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathLoadStream(
#else
DCIDirPathLoadStream(
#endif // OCI_EXPORT
	OCIDirPathCtx*      dpctx, 
	OCIDirPathStream*   dpstr,
    OCIError*           errhp
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathFlushRow(
#else
DCIDirPathFlushRow(
#endif // OCI_EXPORT 
    OCIDirPathCtx*      dpctx, 
    OCIError*           errhp 
);

OCI_API sword
#ifdef OCI_EXPORT
OCIDirPathAbort(
#else
DCIDirPathAbort(
#endif // OCI_EXPORT
    OCIDirPathCtx*      dpctx, 
    OCIError*           errhp 
);

/* interval */
/*--------------------begin--------------------*/
OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalAdd(
#else
DCIIntervalAdd(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    OCIInterval*    addend1, 
    OCIInterval*    addend2,
    OCIInterval*    result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIIntervalAssign(
#else
DCIIntervalAssign(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    CONST OCIInterval*  ininter,
    OCIInterval*    outinter
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalCheck(
#else
DCIIntervalCheck(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    CONST OCIInterval*  interval,
    ub4*            valid
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalCompare(
#else
DCIIntervalCompare(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    OCIInterval*    inter1, 
    OCIInterval*    inter2,
    sword*          result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalDivide(
#else
DCIIntervalDivide(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    OCIInterval*    dividend, 
    OCINumber*      divisor,
    OCIInterval*    result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalFromNumber(
#else
DCIIntervalFromNumber(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    OCIInterval*    inter, 
    OCINumber*      number
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalFromText(
#else
DCIIntervalFromText(
#endif // OCI_EXPORT 
    dvoid*          hndl,
    OCIError*       err,
    CONST OraText*  inpstr, 
    size_t          str_len,
    OCIInterval*    result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalFromTZ(
#else
DCIIntervalFromTZ(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    CONST oratext*  inpstring,
    size_t          str_len,
    OCIInterval*    result);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalGetDaySecond(
#else
DCIIntervalGetDaySecond(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    sb4*            dy,
    sb4*            hr,
    sb4*            mm,
    sb4*            ss,
    sb4*            fsec,
    CONST OCIInterval*  result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalGetYearMonth(
#else
DCIIntervalGetYearMonth(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    sb4*            yr,
    sb4*            mnth,
    CONST OCIInterval*  result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalMultiply(
#else
DCIIntervalMultiply(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    CONST OCIInterval*  inter,
    OCINumber*      nfactor,
    OCIInterval*    result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalSetDaySecond(
#else
DCIIntervalSetDaySecond(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    sb4             dy,
    sb4             hr,
    sb4             mm,
    sb4             ss,
    sb4             fsec,
    OCIInterval*    result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalSetYearMonth(
#else
DCIIntervalSetYearMonth(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    sb4             yr,
    sb4             mnth,
    OCIInterval*    result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalSubtract(
#else
DCIIntervalSubtract(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    OCIInterval*    minuend, 
    OCIInterval*    subtrahend,
    OCIInterval*    result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalToNumber(
#else
DCIIntervalToNumber(
#endif // OCI_EXPORT
    dvoid*          hndl,
    OCIError*       err,
    CONST OCIInterval*  inter, 
    OCINumber*      number
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIIntervalToText(
#else
DCIIntervalToText(
#endif // OCI_EXPORT 
    dvoid*          hndl,
    OCIError*       err,
    CONST OCIInterval*  inter,
    ub1             lfprec,
    ub1             fsprec, 
    OraText*        buffer,
    size_t          buflen,
    size_t*         resultlen
);

OCI_API sword   
#ifdef OCI_EXPORT
OCILobFileCloseAll(
#else
DCILobFileCloseAll(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp
);

OCI_API sword 
#ifdef OCI_EXPORT
OCIServerVersion(
#else
DCIServerVersion(
#endif // OCI_EXPORT
    dvoid*          hndlp,
    OCIError*       errhp,
    OraText*        bufp, 
    ub4             bufsz,
    ub1             hndltype
);

OCI_API sword 
#ifdef OCI_EXPORT
OCILobLocatorIsInit(
#else
DCILobLocatorIsInit(
#endif // OCI_EXPORT
    OCIEnv*         envhp,
    OCIError*       errhp, 
    CONST OCILobLocator*    locp, 
    boolean*        is_initialized
);

OCI_API sword   
#ifdef OCI_EXPORT
OCILobTrim(
#else
DCILobTrim(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCILobLocator*  locp,
    ub4             newlen
);

OCI_API sword   
#ifdef OCI_EXPORT
OCILobAssign(
#else
DCILobAssign(
#endif // OCI_EXPORT
    OCIEnv*         envhp,
    OCIError*       errhp, 
    CONST OCILobLocator*    src_locp, 
    OCILobLocator** dst_locpp
);

OCI_API 
sword
#ifdef OCI_EXPORT
OCILobCharSetForm(
#else
DCILobCharSetForm(
#endif // OCI_EXPORT
    OCIEnv*                 envhp, 
    OCIError*               errhp, 
    const OCILobLocator*    locp, 
    ub1*                    csfrm
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobIsEqual(  
#else
DCILobIsEqual(
#endif // OCI_EXPORT
    OCIEnv*                 envhp,
    const OCILobLocator*    x,
    const OCILobLocator*    y,
    boolean*                is_equal
);

OCI_API sword
#ifdef OCI_EXPORT
OCILobFileGetName(
#else
DCILobFileGetName(
#endif // OCI_EXPORT
    OCIEnv*         envhp,
    OCIError*       errhp, 
    CONST OCILobLocator*    filep, 
    OraText*        dir_alias,
    ub2*            d_length, 
    OraText*        filename,
    ub2*            f_length
);

OCI_API sword   
#ifdef OCI_EXPORT
OCILobFileSetName(
#else
DCILobFileSetName(
#endif // OCI_EXPORT
    OCIEnv*         envhp,
    OCIError*       errhp, 
    OCILobLocator** filepp, 
    CONST OraText*  dir_alias,
    ub2             d_length, 
    CONST OraText*  filename,
    ub2             f_length
);

OCI_API sword  
#ifdef OCI_EXPORT
OCILobFileExists(
#else
DCILobFileExists(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp, 
    OCILobLocator*  filep,
    boolean*        flag
);

OCI_API sword 
#ifdef OCI_EXPORT
OCINumberAssign(
#else
DCINumberAssign(
#endif // OCI_EXPORT    
    OCIError*       err,
    CONST OCINumber*    from,
    OCINumber*      to
);

OCI_API sword 
#ifdef OCI_EXPORT
OCINumberFromReal( 
#else
DCINumberFromReal(
#endif // OCI_EXPORT
    OCIError*       err,
    CONST dvoid*    rnum,
    uword           rnum_length,
    OCINumber*      number
);

OCI_API sword 
#ifdef OCI_EXPORT
OCINumberFromInt( 
#else
DCINumberFromInt(
#endif // OCI_EXPORT    
    OCIError*       err,
    CONST dvoid*    inum,
    uword           inum_length,
    uword           inum_s_flag,
    OCINumber*      number
);

OCI_API sword
#ifdef OCI_EXPORT
OCINumberFromText( 
#else
DCINumberFromText(
#endif // OCI_EXPORT
    OCIError*       err,
    CONST oratext*  str, 
    ub4             str_length, 
    CONST oratext*  fmt, 
    ub4             fmt_length, 
    CONST oratext*  nls_params, 
    ub4             nls_p_length, 
    OCINumber*      number    
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberToInt( 
#else
DCINumberToInt(
#endif // OCI_EXPORT
	OCIError*       err, 
	CONST OCINumber*    number,
	uword           rsl_length, 
	uword           rsl_flag, 
	dvoid*          rsl
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCINumberToReal( 
#else
DCINumberToReal(
#endif // OCI_EXPORT
	OCIError        *err, 
	CONST OCINumber *number,
	uword           rsl_length, 
	dvoid           *rsl
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberToText( 
#else
DCINumberToText(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number, 
    const OraText*          fmt, 
    ub4                     fmt_length,
    const OraText*          nls_params, 
    ub4                     nls_p_length,
    ub4*                    buf_size, 
    OraText*                buf 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberMod( 
#else
DCINumberMod(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number1, 
    const OCINumber*        number2,
    OCINumber*              result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberDiv( 
#else
DCINumberDiv(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number1, 
    const OCINumber*        number2,
    OCINumber*              result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberMul( 
#else
DCINumberMul(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number1, 
    const OCINumber*        number2,
    OCINumber*              result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberSub( 
#else
DCINumberSub(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number1, 
    const OCINumber*        number2,
    OCINumber*              result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberAdd( 
#else
DCINumberAdd(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number1, 
    const OCINumber*        number2,
    OCINumber*              result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberDec( 
#else
DCINumberDec(
#endif // OCI_EXPORT
    OCIError*               err,
    OCINumber*              number
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberInc( 
#else
DCINumberInc(
#endif // OCI_EXPORT
    OCIError*               err,
    OCINumber*              number
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberNeg( 
#else
DCINumberNeg(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number,
    OCINumber*              result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberAbs( 
#else
DCINumberAbs(
#endif // OCI_EXPORT
    OCIError*               err,
    const OCINumber*        number,
    OCINumber*              result
);

OCI_API 
ub1* 
#ifdef OCI_EXPORT
OCIRawPtr( 
#else
DCIRawPtr(
#endif // OCI_EXPORT    
    OCIEnv*         envhp, 
    const OCIRaw*   raw
);

OCI_API
ub4
#ifdef OCI_EXPORT
OCIRawSize(
#else
DCIRawSize(
#endif  //OCI_EXPORT
    OCIEnv*         envhp,
    const OCIRaw*   raw
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIRawAllocSize(
#else
DCIRawAllocSize(
#endif  //OCI_EXPORT
    OCIEnv*             envhp,
    OCIError*           errhp,
    const OCIRaw*       raw,
    ub4*                allocsize 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIRawAssignBytes( 
#else
DCIRawAssignBytes(
#endif // OCI_EXPORT   
    OCIEnv*             envhp,
    OCIError*           errhp, 
    const ub1*          source,
    ub4                 source_len,
    OCIRaw**            target 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIRawResize(
#else
DCIRawResize(
#endif   
    OCIEnv*             envhp, 
    OCIError*           errhp,
    ub2                 new_size, 
    OCIRaw**            raw 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIRawAssignRaw(
#else
DCIRawAssignRaw(
#endif   
    OCIEnv*             envhp,
    OCIError*           errhp, 
    const OCIRaw*       rhs, 
    OCIRaw**            lhs
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCILobLoadFromFile( 
#else
DCILobLoadFromFile(
#endif // OCI_EXPORT
    OCISvcCtx*          svchp, 
    OCIError*           errhp, 
    OCILobLocator*      dst_locp, 
    OCILobLocator*      src_locp, 
    ub4                 amount, 
    ub4                 dst_offset, 
    ub4                 src_offset 
);

OCI_API 
sword
#ifdef OCI_EXPORT
OCILobFileOpen( 
#else
DCILobFileOpen( 
#endif  //OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCILobLocator*  filep,
    ub1             mode 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobFileClose(
#else
DCILobFileClose(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCILobLocator*  filep
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobFileIsOpen(  
#else
DCILobFileIsOpen(
#endif // OCI_EXPORT
    OCISvcCtx*      svchp,
    OCIError*       errhp,
    OCILobLocator*  filep,
    boolean*        flag
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobCreateTemporary(  
#else
DCILobCreateTemporary(
#endif // OCI_EXPORT
    OCISvcCtx       *svchp, 
    OCIError        *errhp, 
    OCILobLocator   *locp,  
    ub2             csid, 
    ub1             csfrm,
    ub1             lobtype,
    boolean         cache,
    OCIDuration     duration
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobFreeTemporary(  
#else
DCILobFreeTemporary(
#endif // OCI_EXPORT
    OCISvcCtx       *svchp, 
    OCIError        *errhp, 
    OCILobLocator   *locp   
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateTimeToText(
#else
DCIDateTimeToText( 
#endif  
    void                *hndl,
    OCIError            *err,
    const OCIDateTime   *date,
    const OraText       *fmt,
    ub1                 fmt_length,
    ub1                 fsprec,
    const OraText       *lang_name,
    size_t              lang_length,
    ub4                 *buf_size,
    OraText             *buf 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateTimeFromText(
#else
DCIDateTimeFromText(
#endif  
    void            *hndl,
    OCIError        *err,
    const OraText   *date_str,
    size_t          d_str_length,
    const OraText   *fmt,
    ub1             fmt_length,
    const OraText   *lang_name,
    size_t          lang_length,
    OCIDateTime     *date 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateAddMonths(
#else
DCIDateAddMonths(
#endif // OCI_EXPORT
    OCIError        *err,
    const OCIDate   *date,
    sb4             num_months,
    OCIDate         *result 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateAddDays(
#else
DCIDateAddDays(
#endif // OCI_EXPORT
    OCIError        *err,
    const OCIDate   *date,
    sb4             num_days,
    OCIDate         *result
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateNextDay(
#else
DCIDateNextDay(
#endif // OCI_EXPORT
    OCIError        *err,
    const OCIDate   *date,
    const OraText   *day,
    ub4             day_length,
    OCIDate         *next_day 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateFromText(
#else
DCIDateFromText(
#endif // OCI_EXPORT
    OCIError        *err,
    const OraText   *date_str,
    ub4             d_str_length,
    const OraText   *fmt,
    ub1             fmt_length,
    const OraText   *lang_name,
    ub4             lang_length,
    OCIDate         *date 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateToText(
#else
DCIDateToText(
#endif // OCI_EXPORT
    OCIError        *err,
    const OCIDate   *date,
    const OraText   *fmt,
    ub1             fmt_length,
    const OraText   *lang_name,
    ub4             lang_length,
    ub4             *buf_size,
    OraText         *buf 
);
 
OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateCompare(
#else
DCIDateCompare(
#endif // OCI_EXPORT
    OCIError *err,
    const OCIDate *date1,
    const OCIDate *date2,
    sword *result 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateCheck(
#else
DCIDateCheck(
#endif // OCI_EXPORT
    OCIError*       err,
    const OCIDate*  date,
    uword*          valid 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateDaysBetween(
#else
DCIDateDaysBetween(
#endif // OCI_EXPORT
    OCIError        *err,
    const OCIDate   *date1,
    const OCIDate   *date2,
    sb4             *num_days 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateLastDay(
#else
DCIDateLastDay(
#endif // OCI_EXPORT
    OCIError        *err,
    const OCIDate   *date,
    OCIDate         *last_day 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateSysDate(
#else
DCIDateSysDate(
#endif // OCI_EXPORT
    OCIError*       err,
    OCIDate*        sys_date
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINlsNumericInfoGet(
#else
DCINlsNumericInfoGet(
#endif // OCI_EXPORT
    void*           hndl,
    OCIError*       errhp,
    sb4*            val,
    ub2             item
);


OCI_API 
sword   
#ifdef OCI_EXPORT
OCIObjectFree(
#else
DCIObjectFree( 
#endif
    OCIEnv      *env, 
    OCIError    *err, 
    void        *instance, 
    ub2         flags   
);


OCI_API 
sword   
#ifdef OCI_EXPORT
OCICollSize(
#else
DCICollSize( 
#endif
    OCIEnv          *env, 
    OCIError        *err, 
    const OCIColl   *coll, 
    sb4             *size 
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCICollTrim(
#else
DCICollTrim( 
#endif
    OCIEnv      *env, 
    OCIError    *err, 
    sb4         trim_num, 
    OCIColl     *coll    
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCICollAppend(
#else
DCICollAppend( 
#endif 
    OCIEnv      *env, 
    OCIError    *err, 
    const void  *elem, 
    const void  *elemind, 
    OCIColl     *coll    
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCICollGetElem(
#else
DCICollGetElem( 
#endif 
    OCIEnv          *env, 
    OCIError        *err, 
    const OCIColl   *coll, 
    sb4             index, 
    boolean         *exists, 
    void            **elem, 
    void            **elemind    
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCIObjectPin(
#else
DCIObjectPin( 
#endif
    OCIEnv              *env, 
    OCIError            *err, 
    OCIRef              *object_ref,
    OCIComplexObject    *corhdl,
    OCIPinOpt           pin_option, 
    OCIDuration         pin_duration, 
    OCILockOpt          lock_option,
    void                **object 
);

OCI_API 
text * 
#ifdef OCI_EXPORT
OCIStringPtr( 
#else
DCIStringPtr(
#endif // OCI_EXPORT    
    OCIEnv*             envhp, 
    const OCIString*    vs
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCIObjectNew(
#else
DCIObjectNew( 
#endif
    OCIEnv          *env, 
    OCIError        *err, 
    const OCISvcCtx *svc,
    OCITypeCode     typecode, 
    OCIType         *tdo, 
    void            *table, 
    OCIDuration     duration, 
    boolean         value, 
    void            **instance    
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCIBindObject(
#else
DCIBindObject( 
#endif
    OCIBind         *bindp, 
    OCIError        *errhp, 
    const OCIType   *type, 
    void            **pgvpp, 
    ub4             *pvszsp, 
    void            **indpp, 
    ub4             *indszp
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCIDefineObject(
#else
DCIDefineObject( 
#endif
    OCIDefine       *defnp, 
    OCIError        *errhp, 
    const OCIType   *type, 
    void            **pgvpp, 
    ub4             *pvszsp, 
    void            **indpp, 
    ub4             *indszp
);
/*--------------------end--------------------*/

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeGetDate(
#else
DCIDateTimeGetDate(
#endif // OCI_EXPORT
    dvoid       *hndl, 
    OCIError    *err,  
    CONST OCIDateTime *date, 
    sb2         *yr, 
    ub1         *mnth, 
    ub1         *dy
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeGetTime(
#else
DCIDateTimeGetTime(
#endif // OCI_EXPORT
    dvoid       *hndl, 
    OCIError    *err,
    OCIDateTime *datetime, 
    ub1         *hr,
    ub1         *mm,
    ub1         *ss,
    ub4         *fsec
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateTimeAssign ( 
#else
DCIDateTimeAssign(
#endif // OCI_EXPORT
    void                *hndl, 
    OCIError            *err,
    const OCIDateTime   *from,
    OCIDateTime         *to
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeGetTimeZoneOffset(
#else
DCIDateTimeGetTimeZoneOffset(
#endif  
    void               *hndl, 
    OCIError           *err, 
    const OCIDateTime  *datetime, 
    sb1                *hour,
    sb1                *min
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeGetTimeZoneName(
#else
DCIDateTimeGetTimeZoneName(
#endif // OCI_EXPORT
    dvoid*              hndl, 
    OCIError*           err,  
    CONST OCIDateTime*  date,
    ub1*                buf,
    ub4*                buflen
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadMutexInit(
#else
DCIThreadMutexInit(
#endif  
    void*               hndl,
    OCIError*           err, 
    OCIThreadMutex**    mutex 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadMutexAcquire(
#else
DCIThreadMutexAcquire(
#endif  
    void*               hndl,
    OCIError*           err, 
    OCIThreadMutex*     mutex 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadMutexRelease(
#else
DCIThreadMutexRelease(
#endif  
    void*               hndl,
    OCIError*           err, 
    OCIThreadMutex*     mutex 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadMutexDestroy(
#else
DCIThreadMutexDestroy(
#endif  
    void*               hndl,
    OCIError*           err, 
    OCIThreadMutex**    mutex 
);

OCI_API 
sword
#ifdef OCI_EXPORT
OCILobLocatorAssign(
#else
DCILobLocatorAssign(
#endif // OCI_EXPORT
    OCISvcCtx*              svchp, 
    OCIError*               errhp, 
    CONST OCILobLocator*    src_locp, 
    OCILobLocator**         dst_locpp
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobIsOpen(  
#else
DCILobIsOpen(
#endif // OCI_EXPORT
    OCISvcCtx*          svchp,
    OCIError*           errhp, 
    OCILobLocator*      locp, 
    boolean*            flag
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateTimeConstruct(
#else
DCIDateTimeConstruct(
#endif // OCI_EXPORT
	dvoid       *hndl,
	OCIError    *err,
	OCIDateTime *datetime,
	sb2         yr,
	ub1         mnth,
	ub1         dy,
	ub1         hr,
	ub1         mm,
	ub1         ss,
	ub4         fsec,
    OraText     *timezone,
	size_t      timezone_length
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIObjectCopy(
#else
DCIObjectCopy(
#endif // OCI_EXPORT
    OCIEnv              *env,
    OCIError            *err, 
    const OCISvcCtx     *svc,
    void                *source, 
    void                *null_source, 
    void                *target, 
    void                *null_target, 
    OCIType             *tdo,
    OCIDuration         duration, 
    ub1                 option 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIRefAssign(
#else
DCIRefAssign( 
#endif // OCI_EXPORT
    OCIEnv             *env, 
    OCIError           *err, 
    const OCIRef       *source, 
    OCIRef             **target 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIObjectGetObjectRef(
#else
DCIObjectGetObjectRef( 
#endif // OCI_EXPORT  
    OCIEnv        *env, 
    OCIError      *err,
    void          *object, 
    OCIRef        *object_ref 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCISessionPoolDestroy(
#else
DCISessionPoolDestroy( 
#endif // OCI_EXPORT   
    OCISPool     *spoolhp, 
    OCIError     *errhp,
    ub4          mode 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCISessionPoolCreate(
#else
DCISessionPoolCreate( 
#endif // OCI_EXPORT    
    OCIEnv           *envhp,
    OCIError         *errhp, 
    OCISPool         *spoolhp,
    OraText          **poolName,
    ub4              *poolNameLen,
    const OraText    *connStr,
    ub4              connStrLen,
    ub4              sessMin, 
    ub4              sessMax, 
    ub4              sessIncr,
    OraText          *userid,
    ub4              useridLen,
    OraText          *password,
    ub4              passwordLen,
    ub4              mode 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIConnectionPoolCreate(
#else
DCIConnectionPoolCreate(
#endif // OCI_EXPORT
    OCIEnv*             envhp,
    OCIError*           errhp,
    OCICPool*           poolhp,
    OraText**           poolName,
    sb4*                poolNameLen,
    const OraText*      dblink,
    sb4                 dblinkLen,
    ub4                 connMin,
    ub4                 connMax,
    ub4                 connIncr,
    const OraText*      poolUsername,
    sb4                 poolUserLen,
    const OraText*      poolPassword,
    sb4                 poolPassLen,
    ub4                 mode
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIConnectionPoolDestroy(
#else
DCIConnectionPoolDestroy(
#endif // OCI_EXPORT
    OCICPool*       poolhp,
    OCIError*       errhp,
    ub4             mode
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCICollAssign(
#else
DCICollAssign( 
#endif // OCI_EXPORT      
    OCIEnv*                     env,
    OCIError*                   err,
    const OCIColl*              rhs,
    OCIColl*                    lhs
); 

OCI_API
sb4 
#ifdef OCI_EXPORT
OCICollMax(
#else
DCICollMax( 
#endif // OCI_EXPORT 
    OCIEnv           *env,
    const OCIColl    *coll 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCICollAssignElem(
#else
DCICollAssignElem( 
#endif // OCI_EXPORT 
    OCIEnv           *env, 
    OCIError         *err, 
    sb4              index, 
    const void       *elem, 
    const void       *elemind, 
    OCIColl          *coll 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCISessionGet(
#else
DCISessionGet( 
#endif // OCI_EXPORT 
    OCIEnv            *envhp,
    OCIError          *errhp,
    OCISvcCtx         **svchp,
    OCIAuthInfo       *authInfop,
    OraText           *dbName,
    ub4               dbName_len,
    const OraText     *tagInfo,
    ub4               tagInfo_len,
    OraText           **retTagInfo,
    ub4               *retTagInfo_len,
    boolean           *found,
    ub4               mode 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCISessionRelease(
#else
DCISessionRelease( 
#endif // OCI_EXPORT 
    OCISvcCtx       *svchp,
    OCIError        *errhp,
    OraText         *tag,
    ub4             tag_len,
    ub4             mode 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIPing(
#else
DCIPing( 
#endif // OCI_EXPORT 
    OCISvcCtx     *svchp,
    OCIError      *errhp,
    ub4           mode 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateZoneToZone(
#else
DCIDateZoneToZone( 
#endif // OCI_EXPORT   
    OCIError           *err, 
    const OCIDate      *date1, 
    const OraText      *zon1,
    ub4                zon1_length, 
    const OraText      *zon2, 
    ub4                zon2_length, 
    OCIDate            *date2 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIAQListen(
#else
DCIAQListen( 
#endif // OCI_EXPORT   
    OCISvcCtx      *svchp, 
    OCIError       *errhp,
    OCIAQAgent     **agent_list, 
    ub4            num_agents,
    sb4            wait, 
    OCIAQAgent     **agent,
    ub4            flags
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIAQDeq(
#else
DCIAQDeq( 
#endif // OCI_EXPORT   
    OCISvcCtx           *svch,
    OCIError            *errh,
    OraText             *queue_name,
    OCIAQDeqOptions     *dequeue_options,
    OCIAQMsgProperties  *message_properties,
    OCIType             *payload_tdo,
    void                **payload,
    void                **payload_ind,
    OCIRaw              **msgid,
    ub4                 flags 
);

OCI_API
ub4
#ifdef OCI_EXPORT
OCISubscriptionRegister(
#else
DCISubscriptionRegister(
#endif // OCI_EXPORT   
    OCISvcCtx         *svchp,
    OCISubscription   **subscrhpp,
    ub2               count,
    OCIError          *errhp,
    ub4               mode 
);

OCI_API 
ub4
#ifdef OCI_EXPORT
OCISubscriptionUnRegister(
#else
DCISubscriptionUnRegister(
#endif // OCI_EXPORT   
    OCISvcCtx         *svchp,
    OCISubscription   *subscrhp,
    OCIError          *errhp,
    ub4               mode 
); 

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIAQEnq( 
#else
DCIAQEnq(
#endif // OCI_EXPORT  
    OCISvcCtx           *svch,
    OCIError            *errh,
    OraText             *queue_name,
    OCIAQEnqOptions     *enqueue_options,
    OCIAQMsgProperties  *message_properties,
    OCIType             *payload_tdo,
    void                **payload,
    void                **payload_ind,
    OCIRaw              **msgid,
    ub4                 flags 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCILobGetLength2( 
#else
DCILobGetLength2(
#endif // OCI_EXPORT   
    OCISvcCtx      *svchp,
    OCIError       *errhp,
    OCILobLocator  *locp,
    oraub8         *lenp 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIIterCreate( 
#else
DCIIterCreate(
#endif // OCI_EXPORT  
    OCIEnv               *env, 
    OCIError             *err, 
    const OCIColl        *coll, 
    OCIIter              **itr 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIIterDelete( 
#else
DCIIterDelete(
#endif // OCI_EXPORT  
    OCIEnv           *env, 
    OCIError         *err, 
    OCIIter          **itr 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIIterNext( 
#else
DCIIterNext(
#endif // OCI_EXPORT 
    OCIEnv            *env,
    OCIError          *err, 
    OCIIter           *itr, 
    void              **elem,
    void              **elemind,
    boolean           *eoc
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIIterPrev( 
#else
DCIIterPrev(
#endif // OCI_EXPORT 
    OCIEnv            *env, 
    OCIError          *err, 
    OCIIter           *itr, 
    void              **elem, 
    void              **elemind,
    boolean           *boc 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadInit(
#else
DCIThreadInit(
#endif  
    void*       hndl,
    OCIError*   err 
);

OCI_API
void
#ifdef OCI_EXPORT
OCIThreadProcessInit(
#else
DCIThreadProcessInit(
#endif   
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadTerm(
#else
DCIThreadTerm(
#endif 
    void*       hndl, 
    OCIError*   err 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDBStartup(
#else
DCIDBStartup(
#endif  
    OCISvcCtx     *svchp,
    OCIError      *errhp,
    OCIAdmin      *admhp,
    ub4           mode,
    ub4           flags
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDBShutdown(
#else
DCIDBShutdown(
#endif  
    OCISvcCtx     *svchp,
    OCIError      *errhp,
    OCIAdmin      *admhp,
    ub4           mode
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobTrim2(
#else
DCILobTrim2(
#endif  
    OCISvcCtx       *svchp,
    OCIError        *errhp,
    OCILobLocator   *locp,
    oraub8          newlen 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobWrite2(
#else
DCILobWrite2(
#endif  
    OCISvcCtx       *svchp,
    OCIError        *errhp,
    OCILobLocator   *locp,
    oraub8          *byte_amtp,
    oraub8          *char_amtp,
    oraub8          offset,
    void            *bufp, 
    oraub8          buflen,
    ub1             piece,
    void            *ctxp, 
    sb4            (*cbfp)
    (
    void     *ctxp,
    void     *bufp,
    oraub8   *lenp,
    ub1      *piecep,
    void     **changed_bufpp,
    oraub8   *changed_lenp
    ) ,
    ub2             csid,
    ub1             csfrm 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobErase(
#else
DCILobErase(
#endif  
    OCISvcCtx       *svchp,
    OCIError        *errhp,
    OCILobLocator   *locp,
    ub4             *amount,
    ub4             offset 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobErase2(
#else
DCILobErase2(
#endif   
    OCISvcCtx       *svchp,
    OCIError        *errhp,
    OCILobLocator   *locp,
    oraub8          *amount,
    oraub8          offset
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobGetChunkSize(
#else
DCILobGetChunkSize(
#endif  
	OCISvcCtx       *svchp,
    OCIError        *errhp,
    OCILobLocator   *locp,
    ub4             *chunk_size 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobCopy(
#else
DCILobCopy(
#endif   
    OCISvcCtx        *svchp,
    OCIError         *errhp,
    OCILobLocator    *dst_locp,
    OCILobLocator    *src_locp,
    ub4              amount,
    ub4              dst_offset,
    ub4              src_offset
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobCopy2(
#else
DCILobCopy2(
#endif   
    OCISvcCtx        *svchp,
    OCIError         *errhp,
    OCILobLocator    *dst_locp,
    OCILobLocator    *src_locp,
    oraub8           amount,
    oraub8           dst_offset,
    oraub8           src_offset 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobLoadFromFile2(
#else
DCILobLoadFromFile2(
#endif    
    OCISvcCtx        *svchp, 
    OCIError         *errhp, 
    OCILobLocator    *dst_locp, 
    OCILobLocator    *src_locp, 
    oraub8           amount, 
    oraub8           dst_offset, 
    oraub8           src_offset 
); 

OCI_API
sword
#ifdef OCI_EXPORT
OCILobWriteAppend(
#else
DCILobWriteAppend(
#endif    
    OCISvcCtx *svchp,
    OCIError *errhp,
    OCILobLocator *locp,
    ub4 *amtp,
    void  *bufp, 
    ub4 buflen, 
    ub1 piece, 
    void  *ctxp, 
    sb4   (*cbfp)
    (
    void     *ctxp,
    void     *bufp,
    ub4      *lenp,
    ub1      *piecep
    ) ,
    ub2 csid, 
    ub1 csfrm 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobWriteAppend2(
#else
DCILobWriteAppend2(
#endif   
    OCISvcCtx           *svchp,
    OCIError            *errhp,
    OCILobLocator       *locp,
    oraub8              *byte_amtp,
    oraub8              *char_amtp,
    void                *bufp, 
    oraub8              buflen, 
    ub1                 piece, 
    void                *ctxp, 
    sb4                 (*cbfp)
    (
    void     *ctxp,
    void     *bufp,
    oraub8   *lenp,
    ub1      *piecep,
    void     **changed_bufpp,
    oraub8   *changed_lenp
    ) ,
    ub2 csid, 
    ub1 csfrm
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobIsTemporary(
#else
DCILobIsTemporary(
#endif    
    OCIEnv            *envhp,
    OCIError          *errhp,
    OCILobLocator     *locp,
    boolean           *is_temporary
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobOpen(
#else
DCILobOpen(
#endif    
    OCISvcCtx        *svchp,
    OCIError         *errhp, 
    OCILobLocator    *locp, 
    ub1              mode 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobClose(
#else
DCILobClose(
#endif     
    OCISvcCtx      *svchp,
    OCIError       *errhp, 
    OCILobLocator  *locp 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobGetStorageLimit(
#else
DCILobGetStorageLimit(
#endif    
    OCISvcCtx      *svchp,
    OCIError       *errhp,
    OCILobLocator  *locp,
    oraub8         *limitp 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIArrayDescriptorAlloc(
#else
DCIArrayDescriptorAlloc(
#endif    
    const  void   *parenth,
    void          **descpp, 
    const ub4     type,
    ub4           array_size,
    const size_t  xtramem_sz,
    void          **usrmempp
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIArrayDescriptorFree(
#else
DCIArrayDescriptorFree(
#endif    
    void       **descp,
    const ub4  type 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCILobFlushBuffer(
#else
DCILobFlushBuffer(
#endif 
    OCISvcCtx       *svchp, 
    OCIError        *errhp, 
    OCILobLocator   *locp,
    ub4             flag 
); 

OCI_API
sword
#ifdef OCI_EXPORT
OCILobDisableBuffering(
#else
DCILobDisableBuffering(
#endif  
    OCISvcCtx      *svchp, 
    OCIError       *errhp, 
    OCILobLocator  *locp 
); 

OCI_API
sword
#ifdef OCI_EXPORT
OCILobEnableBuffering(
#else
DCILobEnableBuffering(
#endif   
    OCISvcCtx      *svchp, 
    OCIError       *errhp, 
    OCILobLocator  *locp 
); 

OCI_API
sword
#ifdef OCI_EXPORT
OCITypeByName(
#else
DCITypeByName(
#endif  
    OCIEnv               *env,
    OCIError             *err, 
    const OCISvcCtx      *svc, 
    const OraText        *schema_name,
    ub4                  s_length, 
    const OraText        *type_name, 
    ub4                  t_length, 
    const OraText        *version_name,
    ub4                  v_length,
    OCIDuration          pin_duration,
    OCITypeGetOpt        get_option,
    OCIType              **tdo 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateTimeIntervalAdd(
#else
DCIDateTimeIntervalAdd(
#endif // OCI_EXPORT
    dvoid*              hndl, 
    OCIError*           err, 
    OCIDateTime*        addend1, 
    OCIInterval*        addend2, 
    OCIDateTime*        result 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateTimeIntervalSub(
#else
DCIDateTimeIntervalSub(
#endif // OCI_EXPORT
    dvoid*              hndl, 
    OCIError*           err, 
    OCIDateTime*        addend1, 
    OCIInterval*        addend2, 
    OCIDateTime*        result 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIObjectGetProperty( 
#else
DCIObjectGetProperty(
#endif // OCI_EXPORT 
    OCIEnv *envh,
    OCIError *errh,
    const void *obj,
    OCIObjectPropId propertyId,
    void *property,
    ub4 *size 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIObjectGetInd( 
#else
DCIObjectGetInd(
#endif // OCI_EXPORT  
    OCIEnv        *env, 
    OCIError      *err, 
    void          *instance, 
    void          **null_struct 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIObjectUnpin( 
#else
DCIObjectUnpin(
#endif // OCI_EXPORT   
    OCIEnv        *env,
    OCIError      *err, 
    void          *object 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCITransPrepare( 
#else
DCITransPrepare(
#endif // OCI_EXPORT   
    OCISvcCtx    *svchp, 
    OCIError     *errhp,
    ub4          flags 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCITransForget( 
#else
DCITransForget(
#endif // OCI_EXPORT   
    OCISvcCtx     *svchp, 
    OCIError      *errhp,
    ub4           flags 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeSubtract( 
#else
DCIDateTimeSubtract(
#endif // OCI_EXPORT 
    void         *hndl, 
    OCIError     *err,
    OCIDateTime  *indate1,
    OCIDateTime  *indate2, 
    OCIInterval  *inter 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeSysTimeStamp( 
#else
DCIDateTimeSysTimeStamp(
#endif // OCI_EXPORT  
    void           *hndl,
    OCIError       *err, 
    OCIDateTime    *sys_date 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeConvert( 
#else
DCIDateTimeConvert(
#endif // OCI_EXPORT  
    void         *hndl,
    OCIError     *err, 
    OCIDateTime  *indate, 
    OCIDateTime  *outdate 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeCheck( 
#else
DCIDateTimeCheck(
#endif // OCI_EXPORT  
    void                *hndl,
    OCIError            *err, 
    const OCIDateTime   *date, 
    ub4                 *valid 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeCompare( 
#else
DCIDateTimeCompare(
#endif // OCI_EXPORT  
    void               *hndl,
    OCIError           *err,
    const OCIDateTime  *date1, 
    const OCIDateTime  *date2,
    sword              *result 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadIdInit( 
#else
DCIThreadIdInit(
#endif // OCI_EXPORT   
    void*           hndl,
    OCIError*       err, 
    OCIThreadId**   tid 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadHndInit( 
#else
DCIThreadHndInit(
#endif // OCI_EXPORT  
    void*               hndl, 
    OCIError*           err,
    OCIThreadHandle**   thnd 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadIdDestroy( 
#else
DCIThreadIdDestroy(
#endif // OCI_EXPORT  
    void*               hndl,
    OCIError*           err,
    OCIThreadId**       tid 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadHndDestroy( 
#else
DCIThreadHndDestroy(
#endif // OCI_EXPORT   
    void*               hndl,
    OCIError*           err,
    OCIThreadHandle**   thnd 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadClose( 
#else
DCIThreadClose(
#endif // OCI_EXPORT 
    void*               hndl, 
    OCIError*           err, 
    OCIThreadHandle*    tHnd 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadCreate( 
#else
DCIThreadCreate(
#endif // OCI_EXPORT 
    void*               hndl, 
    OCIError*           err, 
    void                (*start)(void*),
    void*               arg, 
    OCIThreadId*        tid, 
    OCIThreadHandle*    tHnd 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadJoin( 
#else
DCIThreadJoin(
#endif // OCI_EXPORT 
    void*               hndl,
    OCIError*           err, 
    OCIThreadHandle*    tHnd 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadKeyInit( 
#else
DCIThreadKeyInit(
#endif // OCI_EXPORT  
    void*                   hndl, 
    OCIError*               err,
    OCIThreadKey**          key,
    OCIThreadKeyDestFunc    destFn 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadKeyDestroy( 
#else
DCIThreadKeyDestroy(
#endif // OCI_EXPORT  
    void*               hndl,
    OCIError*           err, 
    OCIThreadKey**      key 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadKeyGet( 
#else
DCIThreadKeyGet(
#endif // OCI_EXPORT  
    void*           hndl, 
    OCIError*       err, 
    OCIThreadKey*   key, 
    void**          pValue 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIThreadKeySet( 
#else
DCIThreadKeySet(
#endif // OCI_EXPORT 
    void*           hndl,
    OCIError*       err, 
    OCIThreadKey*   key,
    void*           value 
);

OCI_API
void
#ifdef OCI_EXPORT
OCIRefClear( 
#else
DCIRefClear(
#endif // OCI_EXPORT  
    OCIEnv        *env,
    OCIRef        *ref
);

OCI_API
boolean 
#ifdef OCI_EXPORT
OCIRefIsNull( 
#else
DCIRefIsNull(
#endif // OCI_EXPORT  
    OCIEnv           *env,
    const OCIRef     *ref 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIRefToHex( 
#else
DCIRefToHex(
#endif // OCI_EXPORT  
    OCIEnv            *env,
    OCIError          *err, 
    const OCIRef      *ref, 
    OraText           *hex, 
    ub4               *hex_length
);

OCI_API
ub4
#ifdef OCI_EXPORT
OCIRefHexSize( 
#else
DCIRefHexSize(
#endif // OCI_EXPORT  
    OCIEnv            *env,
    const OCIRef      *ref 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIStmtRelease( 
#else
DCIStmtRelease(
#endif // OCI_EXPORT  
    OCIStmt        *stmthp,  
    OCIError       *errhp,
    const OraText  *key,
    ub4            keylen,
    ub4            mode 
);  

OCI_API
sword 
#ifdef OCI_EXPORT
OCIStmtPrepare2( 
#else
DCIStmtPrepare2(
#endif // OCI_EXPORT   
    OCISvcCtx      *svchp,
    OCIStmt        **stmthp,
    OCIError       *errhp,
    const OraText  *stmttext,
    ub4            stmt_len,
    const OraText  *key,
    ub4            keylen,
    ub4            language,
    ub4            mode 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCILobAppend( 
#else
DCILobAppend(
#endif // OCI_EXPORT  
    OCISvcCtx        *svchp,
    OCIError         *errhp,
    OCILobLocator    *dst_locp,
    OCILobLocator    *src_locp 
);

/*--------------------end--------------------*/

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberCmp( 
#else
DCINumberCmp(
#endif // OCI_EXPORT 
    OCIError            *err,
    const OCINumber     *number1, 
    const OCINumber     *number2,
    sword               *result
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINumberIsInt( 
#else
DCINumberIsInt(
#endif // OCI_EXPORT 
    OCIError*           err, 
    const OCINumber*    number,
    boolean*            result
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCILogon2(
#else
DCILogon2(
#endif // OCI_EXPORT
    OCIEnv *envhp, 
    OCIError *errhp, 
    OCISvcCtx **svchp, 
    CONST OraText *username, 
    ub4 uname_len, 
    CONST OraText *password, 
    ub4 passwd_len, 
    CONST OraText *dbname, 
    ub4 dbname_len,
    ub4 mode 
);

OCI_API 
sword
#ifdef OCI_EXPORT
OCILobCharSetId(
#else
DCILobCharSetId(
#endif // OCI_EXPORT
    OCIEnv*                 envhp, 
    OCIError*               errhp, 
    const OCILobLocator*    locp, 
    ub2*                    csid
);

OCI_API 
sword
#ifdef OCI_EXPORT
OCIDirPathColArrayRowGet(
#else
DCIDirPathColArrayRowGet(
#endif // OCI_EXPORT
    OCIDirPathColArray  *dpca,
    OCIError            *errhp,
    ub4                 rownum,
    ub1                 ***cvalppp,
    ub4                 **clenpp,
    ub1                 **cflgpp 
);

OCI_API 
sword
#ifdef OCI_EXPORT
OCIDurationBegin(
#else
DCIDurationBegin(
#endif // OCI_EXPORT 
    OCIEnv*             env,
    OCIError*           err,
    const OCISvcCtx     *svc, 
    OCIDuration         parent,
    OCIDuration         *duration 
); 

OCI_API 
sword
#ifdef OCI_EXPORT
OCIDurationEnd(
#else
DCIDurationEnd(
#endif // OCI_EXPORT  
    OCIEnv             *env, 
    OCIError           *err, 
    const OCISvcCtx    *svc,
    OCIDuration        duration 
);

OCI_API
ub4
#ifdef OCI_EXPORT
OCIStringSize(
#else
DCIStringSize(
#endif  //OCI_EXPORT
    OCIEnv*             env,
    const OCIString*    vs
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIStringAssignText( 
#else
DCIStringAssignText(
#endif // OCI_EXPORT   
    OCIEnv*                 envhp,
    OCIError*               errhp, 
    const OraText*          rhs,
    ub2                     rhs_len,
    OCIString**             lhs
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIRowidToChar(
#else
DCIRowidToChar(
#endif 
    OCIRowid      *rowidDesc,
    OraText       *outbfp,
    ub2           *outbflp,
    OCIError      *errhp 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCINlsEnvironmentVariableGet(
#else
DCINlsEnvironmentVariableGet(
#endif 
    void       *val,
    size_t     size,
    ub2        item,
    ub2        charset, 
    size_t     *rsize
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIStringAllocSize( 
#else
DCIStringAllocSize(
#endif // OCI_EXPORT  
    OCIEnv*             env,
    OCIError*           err, 
    const OCIString*    vs,
    ub4*                allocsize 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIStringAssign( 
#else
DCIStringAssign(
#endif // OCI_EXPORT  
    OCIEnv*             env, 
    OCIError*           err, 
    const OCIString*    rhs, 
    OCIString**         lhs 
);

OCI_API 
sword 
#ifdef OCI_EXPORT
OCIStringResize( 
#else
DCIStringResize(
#endif // OCI_EXPORT  
    OCIEnv*         env,
    OCIError*       err,
    ub4             new_size,
    OCIString**     str 
);

OCI_API
sword 
#ifdef OCI_EXPORT
OCIDateAssign(
#else
DCIDateAssign(
#endif // OCI_EXPORT
    OCIError*       err,
    const OCIDate*  from,
    OCIDate*        to 
);

OCI_API 
sword   
#ifdef OCI_EXPORT
OCIDefineDynamic(
#else
DCIDefineDynamic(
#endif // OCI_EXPORT
    OCIDefine     *definep, 
    OCIError    *errhp, 
    void        *octxp, 
    OCICallbackDefine       ocbfp 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIStmtGetBindInfo(
#else
DCIStmtGetBindInfo(
#endif // OCI_EXPORT 
    OCIStmt      *stmtp,
    OCIError     *errhp,
    ub4          size,
    ub4          startloc,
    sb4          *found,
    OraText      *bvnp[],
    ub1          bvnl[],
    OraText      *invp[],
    ub1          inpl[],
    ub1          dupl[],
    OCIBind      *hndl[] 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeToArray(
#else
DCIDateTimeToArray(
#endif  
    void               *hndl,
    OCIError           *err, 
    const OCIDateTime  *datetime, 
    const OCIInterval  *reftz,
    ub1                *outarray, 
    ub4                *len, 
    ub1                fsprec 
);

OCI_API
sword
#ifdef OCI_EXPORT
OCIDateTimeFromArray(
#else
DCIDateTimeFromArray(
#endif  
    void               *hndl,
    OCIError           *err, 
    const ub1          *inarray,
    ub4                *len,
    ub1                type,
    OCIDateTime        *datetime,
    const OCIInterval  *reftz,
    ub1                fsprec 
);


OCI_API
sword
#ifdef OCI_EXPORT
OCITerminate(
#else
DCITerminate(
#endif 
    ub4    mode
);

OCI_API 
size_t
#ifdef OCI_EXPORT
OCIMultiByteStrCaseConversion( 
#else 
DCIMultiByteStrCaseConversion(
#endif // OCI_EXPORT    
    void*           hndl, 
    OraText*        dststr, 
    const OraText*  srcstr, 
    ub4             flag 
);

OCI_API 
sword
#ifdef OCI_EXPORT
OCIClientVersion(
#else
DCIClientVersion(
#endif // OCI_EXPORT
    sword*              major_version,
    sword*              minor_version,
    sword*              update_num,
    sword*              patch_num,
    sword*              port_update_num
);

OCI_API
sword
#ifdef OCI_EXPORT
obndrn(
#else
dbndrn(
#endif // OCI_EXPORT
    Cda_Def*                cursor,
    sword                   sqlvn,
    ub1*                    progv,
    sword                   progvl,
    sword                   ftype,
    sword                   scale,
    sb2*                    indp,
    text*                   fmt,
    sword                   fmtl,
    sword                   fmtt
);

OCI_API
sword
#ifdef OCI_EXPORT
obndrv(
#else
dbndrv(
#endif // OCI_EXPORT
    Cda_Def*                cursor,
    text*                   sqlvar,
    sword                   sqlvl,
    ub1*                    progv,
    sword                   progvl,
    sword                   ftype,
    sword                   scale,
    sb2*                    indp,
    text*                   fmt,
    sword                   fmtl,
    sword                   fmtt
);

OCI_API
sword
#ifdef OCI_EXPORT
oclose(
#else
dclose(
#endif // OCI_EXPORT
    Cda_Def*                cursor
);

OCI_API
sword
#ifdef OCI_EXPORT
ocof(
#else
dcof(
#endif // OCI_EXPORT
    Lda_Def*                lda
);

OCI_API
sword
#ifdef OCI_EXPORT
ocon(
#else
dcon(
#endif // OCI_EXPORT
    Lda_Def*                lda
);

OCI_API
sword
#ifdef OCI_EXPORT
odefin(
#else
ddefin(
#endif // OCI_EXPORT
    Cda_Def*                cursor,
    sword                   pos,
    ub1*                    buf,
    sword                   bufl,
    sword                   ftype,
    sword                   scale,
    sb2*                    indp,
    text*                   fmt,
    sword                   fmtl,
    sword                   fmtt,
    ub2*                    rlen,
    ub2*                    rcode
);

OCI_API
sword
#ifdef OCI_EXPORT
oerhms(
#else
derhms(
#endif // OCI_EXPORT
    Lda_Def*                lda,
    sb2                     rcode,
    text*                   buf,
    sword                   bufsiz
);

OCI_API
sword
#ifdef OCI_EXPORT
oexec(
#else
dexec(
#endif // OCI_EXPORT
    Cda_Def*                cursor
);

OCI_API
sword
#ifdef OCI_EXPORT
ofetch(
#else
dfetch(
#endif // OCI_EXPORT
    Cda_Def*                cursor
);

OCI_API
sword
#ifdef OCI_EXPORT
olog(
#else
dlog(
#endif // OCI_EXPORT
    Lda_Def*            lda,
    ub1*                hda,
    text*               uid,
    sword               uidl,
    text*               pswd,
    sword               pswdl,
    text*               conn,
    sword               connl,
    ub4                 mode
);

OCI_API
sword
#ifdef OCI_EXPORT
ologof(
#else
dlogof(
#endif // OCI_EXPORT
    Lda_Def*                lda
);

OCI_API
sword
#ifdef OCI_EXPORT
oopen(
#else
dopen(
#endif // OCI_EXPORT
    Cda_Def*                cursor,
    Lda_Def*                lda,
    text*                   dbn,
    sword                   dbnl,
    sword                   arsize,
    text*                   uid,
    sword                   uidl
);

OCI_API
sword
#ifdef OCI_EXPORT
oparse(
#else
dparse(
#endif // OCI_EXPORT
    Cda_Def*                cursor,
    text*                   sqlstm,
    sb4                     sqll,
    sword                   defflg,
    ub4                     lngflg
);

OCI_API
void
#ifdef OCI_EXPORT
    OCIDateSetTime(
#else
    DCIDateSetTime(
#endif
    OCIDate*                date,
    ub1                     hour,
    ub1                     min,
    ub1                     sec
);

OCI_API
void
#ifdef OCI_EXPORT
    OCIDateSetDate(
#else
    DCIDateSetDate(
#endif
    OCIDate*                date,
    sb2                     year,
    ub1                     month,
    ub1                     day
);

#ifdef __cplusplus
}
#endif

#endif
