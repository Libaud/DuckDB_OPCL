{========================================================================================
  Include : DuckDBTypes
  Description : Duck DB API'S types declaration
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2023-09-16 Migration of duckdb.h
  2024-06-27 Upgrading for DuckDB 1.0 support
========================================================================================}

type
  {$ifdef DCC}
    csize_t = UIntPtr;
    {$ifdef CPU64BITS}
    size_t = UInt64;
    {$else}
    size_t = UInt32;
    {$endif}
  {$else}
    {$ifdef CPUX64}
    size_t = UInt64;
    {$else}
    size_t = UInt;
    {$endif}
  {$endif}

  //===--------------------------------------------------------------------===//
  // Enums
  //===--------------------------------------------------------------------===//

  TDDBType = (DUCKDB_TYPE_INVALID = 0,
  	      // bool
  	      DUCKDB_TYPE_BOOLEAN = 1,
  	      // int8_t
  	      DUCKDB_TYPE_TINYINT = 2,
  	      // int16_t
  	      DUCKDB_TYPE_SMALLINT = 3,
  	      // int32_t
  	      DUCKDB_TYPE_INTEGER = 4,
  	      // int64_t
  	      DUCKDB_TYPE_BIGINT = 5,
  	      // UInt8
  	      DUCKDB_TYPE_UTINYINT = 6,
  	      // UInt16
  	      DUCKDB_TYPE_USMALLINT = 7,
  	      // UInt32
  	      DUCKDB_TYPE_UINTEGER = 8,
  	      // uint64_t
  	      DUCKDB_TYPE_UBIGINT = 9,
  	      // float
  	      DUCKDB_TYPE_FLOAT = 10,
  	      // double
  	      DUCKDB_TYPE_DOUBLE = 11,
  	      // TDDBTimestamp, in microseconds
  	      DUCKDB_TYPE_TIMESTAMP = 12,
  	      // TDDBDate
  	      DUCKDB_TYPE_DATE = 13,
  	      // TDDBTime
  	      DUCKDB_TYPE_TIME = 14,
  	      // TDDBInterval
  	      DUCKDB_TYPE_INTERVAL = 15,
  	      // TDDBHugeint
  	      DUCKDB_TYPE_HUGEINT = 16,
              // TDDBUHugeint
              DUCKDB_TYPE_UHUGEINT = 32,
  	      // const char*
  	      DUCKDB_TYPE_VARCHAR = 17,
  	      // TDDBBlob
  	      DUCKDB_TYPE_BLOB = 18,
  	      // decimal
  	      DUCKDB_TYPE_DECIMAL = 19,
  	      // TDDBTimestamp, in seconds
  	      DUCKDB_TYPE_TIMESTAMP_S = 20,
  	      // TDDBTimestamp, in milliseconds
  	      DUCKDB_TYPE_TIMESTAMP_MS = 21,
  	      // TDDBTimestamp, in nanoseconds
  	      DUCKDB_TYPE_TIMESTAMP_NS = 22,
  	      // enum type, only useful as logical type
  	      DUCKDB_TYPE_ENUM = 23,
  	      // list type, only useful as logical type
  	      DUCKDB_TYPE_LIST = 24,
  	      // struct type, only useful as logical type
  	      DUCKDB_TYPE_STRUCT = 25,
  	      // map type, only useful as logical type
  	      DUCKDB_TYPE_MAP = 26,
              // TDDBTypeArray
              DUCKDB_TYPE_ARRAY = 33,
  	      // TDDBHugeint
  	      DUCKDB_TYPE_UUID = 27,
  	      // union type, only useful as logical type
  	      DUCKDB_TYPE_UNION = 28,
  	      // duckdb_bit
  	      DUCKDB_TYPE_BIT = 29,
              // TDUCKDBTypeTimeTZ
              DUCKDB_TYPE_TIME_TZ = 30,
              // TDuckDBTypeTimestampTZ
              DUCKDB_TYPE_TIMESTAMP_TZ = 31);

  TDDBState = (DDBSUCCESS = 0, DDBERROR = 1);

  TDDBPendingState = (DUCKDBPENDINGRESULTREADY = 0,
  	              DUCKDBPENDINGRESULTNOTREADY = 1,
  	              DUCKDBPENDINGERROR = 2,
                      DUCKDBPENDINGNOTASKSAVAILABLE = 3);

  TDDBStatementType = (DUCKDB_STATEMENT_TYPE_INVALID = 0,
	               DUCKDB_STATEMENT_TYPE_SELECT = 1,
	               DUCKDB_STATEMENT_TYPE_INSERT = 2,
	               DUCKDB_STATEMENT_TYPE_UPDATE = 3,
	               DUCKDB_STATEMENT_TYPE_EXPLAIN = 4,
	               DUCKDB_STATEMENT_TYPE_DELETE = 5,
	               DUCKDB_STATEMENT_TYPE_PREPARE = 6,
	               DUCKDB_STATEMENT_TYPE_CREATE = 7,
	               DUCKDB_STATEMENT_TYPE_EXECUTE = 8,
	               DUCKDB_STATEMENT_TYPE_ALTER = 9,
	               DUCKDB_STATEMENT_TYPE_TRANSACTION = 10,
	               DUCKDB_STATEMENT_TYPE_COPY = 11,
	               DUCKDB_STATEMENT_TYPE_ANALYZE = 12,
	               DUCKDB_STATEMENT_TYPE_VARIABLE_SET = 13,
	               DUCKDB_STATEMENT_TYPE_CREATE_FUNC = 14,
	               DUCKDB_STATEMENT_TYPE_DROP = 15,
	               DUCKDB_STATEMENT_TYPE_EXPORT = 16,
	               DUCKDB_STATEMENT_TYPE_PRAGMA = 17,
	               DUCKDB_STATEMENT_TYPE_VACUUM = 18,
	               DUCKDB_STATEMENT_TYPE_CALL = 19,
	               DUCKDB_STATEMENT_TYPE_SET = 20,
	               DUCKDB_STATEMENT_TYPE_LOAD = 21,
	               DUCKDB_STATEMENT_TYPE_RELATION = 22,
	               DUCKDB_STATEMENT_TYPE_EXTENSION = 23,
	               DUCKDB_STATEMENT_TYPE_LOGICAL_PLAN = 24,
	               DUCKDB_STATEMENT_TYPE_ATTACH = 25,
	               DUCKDB_STATEMENT_TYPE_DETACH = 26,
	               DUCKDB_STATEMENT_TYPE_MULTI = 27);

  //===--------------------------------------------------------------------===//
  // General type definitions
  //===--------------------------------------------------------------------===//

  TIDX = UInt64;

  TDDBDeleteCallback = procedure (aData: Pointer);

  TDDBTaskState = Pointer;

  //! Days are stored as days since 1970-01-01
  //! Use the duckdb_from_date/duckdb_to_date function to extract individual information
  TDDBDate = record
    days: Int32;
  end;

  TDDBDateStruct = record
    year: Int32;
    month: Int8;
    day: Int8;
  end;

  //! Time is stored as microseconds since 00:00:00
  //! Use the duckdb_from_time/duckdb_to_time function to extract individual information
  TDDBTime = record
    micros: Int64;
  end;

  TDDBTimeStruct = record
    hour: Int8;
    min: Int8;
    sec: Int8;
    micros: Int32;
  end;

  TDDBTimeTZ = record
    bits: UInt64;
  end;

  //! TIME_TZ is stored as 40 bits for int64_t micros, and 24 bits for int32_t offset
  TDDBTimeTZStruct = record
    time: TDDBTimeStruct;
    offset: Int32;
  end;

  //! Timestamps are stored as microseconds since 1970-01-01
  //! Use the duckdb_from_timestamp/duckdb_to_timestamp function to extract individual information
  TDDBTimestamp = record
    micros: Int64;
  end;

  TDDBTimestampStruct = record
    date: TDDBDateStruct;
    time: TDDBTimeStruct;
  end;

  TDDBInterval = record
    months: Int32;
    days: Int32;
    micros: Int64;
  end;

  //! Hugeints are composed in a (lower, upper) component
  //! The value of the hugeint is upper * 2^64 + lower
  //! For easy usage, the functions duckdb_hugeint_to_double/duckdb_double_to_hugeint are recommended
  TDDBHugeint = record
    lower: UInt64;
    upper: Int64;
  end;

  TDDBUHugeint = record
    lower: UInt64;
    upper: Int64;
  end;

  TDDBDecimal = record
    width: UInt8;
    scale: UInt8;
    value: TDDBHugeint;
  end;

  //! A type holding information about the query execution progress
  TDDBQueryProgressType = record
    percentage: double;
    rows_processed: UInt64;
    total_rows_to_process: UInt64;
  end;

  {
      The internal data representation of a VARCHAR/BLOB column
  }
  TDDBStringA = record
    length: UInt32;
    prefix: array [0..3] of char;
    ptr: PChar;
  end;

  TDDBStringB = record
    length: UInt32;
    inlined: array [0..11] of char;
  end;

  TDDBStringT = packed record
     case byte of
       1: (_ValueA: TDDBStringA);
       2: (_ValueB: TDDBStringB);
  end;

  TDDBListEntry = record
    offset: UInt64;
    length: UInt64;
  end;

  //===--------------------------------------------------------------------===//
  // Types (explicit freeing/destroying)
  //===--------------------------------------------------------------------===//

  //! Strings are composed of a char pointer and a size. You must free string.data
  //! with `duckdb_free`.
  TDDBString = record
    data: PChar;
    size: TIDX;
  end;

  //! BLOBs are composed of a byte pointer and a size. You must free blob.data
  //! with `duckdb_free`.
  TDDBBlob = record
    data: pointer;
    size: TIDX;
  end;

  pDDBColumn = ^TDDBColumn;

  TDDBColumn = record
  {$ifdef DUCKDB_API_VERSION >= DUCKDB_API_0_3_2}
  // deprecated, use duckdb_column_data
  __deprecated_data: pointer;
  // deprecated, use duckdb_nullmask_data
  __deprecated_nullmask: PBoolean;
  // deprecated, use duckdb_column_type
  __deprecated_type: TDDBType;
  // deprecated, use duckdb_column_name
  __deprecated_name: PChar;
  {$else}
  _data: pointer;
  _nullmask: PBoolean;
  _type: TDDBType;
  _name: PChar;
  {$endif}
    _internal_data: pointer;
  end;

  PDDBResult = ^TDDBResult;

  TDDBResult = record
  {$ifdef DUCKDB_API_VERSION >= DUCKDB_API_0_3_2}
  // deprecated, use duckdb_column_count
  __deprecated_column_count: TIDX;
  // deprecated, use duckdb_row_count
  __deprecated_row_count: TIDX;
  // deprecated, use duckdb_rows_changed
  __deprecated_rows_changed: TIDX;
  // deprecated, use duckdb_column_ family of functions
  __deprecated_columns: PDDBColumn;
  // deprecated, use TDuckDBResult_error
  __deprecated_error_message: PChar;
  {$else}
  column_count: TIDX;
  row_count: TIDX;
  rows_changed: TIDX;
  columns: pDDBColumn;
  error_message: PChar;
  {$endif}
    internal_data: pointer;
  end;

  PDDBDatabase = ^TDDBDatabase;

  TDDBDatabase = record
    __db: pointer;
  end;

  PDDBConnection = ^TDDBConnection;

  TDDBConnection = record
    __conn: pointer;
  end;

  //PPDDBPreparedStatement = ^PDDBPreparedStatement;

  PDDBPreparedStatement = ^TDDBPreparedStatement;

  TDDBPreparedStatement = record
    __prep: pointer;
  end;

  PDDBExtractedStatements = ^TDDBExtractedStatements;

  TDDBExtractedStatements = record
    __extrac: pointer;
  end;

  PDDBPendingResult = ^TDDBPendingResult;

  TDDBPendingResult = record
    __pend: pointer;
  end;

  PDDBAppender = ^TDDBAppender;

  TDDBAppender = record
    __appn: pointer;
  end;

  PDDBArrow = ^TDDBArrow;

  TDDBArrow = record
    __arrw: pointer;
  end;

  PDDBArrowStream = ^TDDBArrowStream;

  TDDBArrowStream = record
    __arrwstr: pointer;
  end;

  PDDBConfig = ^TDDBConfig;

  TDDBConfig = record
    __cnfg: pointer;
  end;

  PDDBArrowSchema = ^TDDBArrowSchema;

  TDDBArrowSchema = record
    __arrs: pointer;
  end;

  PDDBArrowArray = ^TDDBArrowArray;

  TDDBArrowArray = record
    __arra: pointer;
  end;

  PDDBLogicalType = ^TDDBLogicalType;

  TDDBLogicalType = record
    __lglt: pointer;
  end;

  PDDBDataChunk = ^TDDBDataChunk;

  TDDBDataChunk = record
    __dtck: pointer;
  end;

  PDDBVector = ^TDDBVector;

  TDDBVector = record
    __vctr: pointer;
  end;

  PDDBValue = ^TDDBValue;

  TDDBValue = record
    __val: pointer;
  end;


  //===--------------------------------------------------------------------===//
  // Replacement Scans
  //===--------------------------------------------------------------------===//

  TDDBReplacementScanInfo = Pointer;

  TDDBReplacementCallback = procedure(aInfo: TDDBReplacementScanInfo;
                                      aTableName: PAnsiChar;
                                      aData: Pointer); cdecl;

  //===--------------------------------------------------------------------===//
  // Table Functions
  //===--------------------------------------------------------------------===//

  {$ifndef DDB_NO_EXTENSION_FUNCTIONS}
    TDDBTableFunction = Pointer;
    TDDBBindInfo = Pointer;
    TDDBInitInfo = Pointer;
    TDDBFunctionInfo = Pointer;

    TDDBTableFunctionBind = procedure (aInfo: TDDBBindInfo);
    TDDBTableFunctionInit = procedure (aInfo: TDDBInitInfo);
    TDDBMainTableFunction = procedure (aInfo: TDDBFunctionInfo; aOutput: TDDBDataChunk);
  {$endif}

{ end of include file }

