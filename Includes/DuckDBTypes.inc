{========================================================================================
  Include : DuckDBTypes
  Description : Duck DB API'S types declaration
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2023-09-16 Migration of duckdb.h
========================================================================================}

type
  {$ifdef DCC}
  csize_t = UIntPtr;
  {$endif}

  {$ifdef CPUX64}
  size_t = UInt64;
  {$else}
  size_t = UInt;
  {$endif}

  TIDX = UInt64;

  TDDBType = (DUCKDB_TYPE_INVALID = 0,
  	      // bool
  	      DUCKDB_TYPE_BOOLEAN,
  	      // int8_t
  	      DUCKDB_TYPE_TINYINT,
  	      // int16_t
  	      DUCKDB_TYPE_SMALLINT,
  	      // int32_t
  	      DUCKDB_TYPE_INTEGER,
  	      // int64_t
  	      DUCKDB_TYPE_BIGINT,
  	      // UInt8
  	      DUCKDB_TYPE_UTINYINT,
  	      // UInt16
  	      DUCKDB_TYPE_USMALLINT,
  	      // UInt32
  	      DUCKDB_TYPE_UINTEGER,
  	      // uint64_t
  	      DUCKDB_TYPE_UBIGINT,
  	      // float
  	      DUCKDB_TYPE_FLOAT,
  	      // double
  	      DUCKDB_TYPE_DOUBLE,
  	      // TDDBTimestamp, in microseconds
  	      DUCKDB_TYPE_TIMESTAMP,
  	      // TDDBDate
  	      DUCKDB_TYPE_DATE,
  	      // TDDBTime
  	      DUCKDB_TYPE_TIME,
  	      // TDDBInterval
  	      DUCKDB_TYPE_INTERVAL,
  	      // TDDBHugeint
  	      DUCKDB_TYPE_HUGEINT,
  	      // const char*
  	      DUCKDB_TYPE_VARCHAR,
  	      // TDDBBlob
  	      DUCKDB_TYPE_BLOB,
  	      // decimal
  	      DUCKDB_TYPE_DECIMAL,
  	      // TDDBTimestamp, in seconds
  	      DUCKDB_TYPE_TIMESTAMP_S,
  	      // TDDBTimestamp, in milliseconds
  	      DUCKDB_TYPE_TIMESTAMP_MS,
  	      // TDDBTimestamp, in nanoseconds
  	      DUCKDB_TYPE_TIMESTAMP_NS,
  	      // enum type, only useful as logical type
  	      DUCKDB_TYPE_ENUM,
  	      // list type, only useful as logical type
  	      DUCKDB_TYPE_LIST,
  	      // struct type, only useful as logical type
  	      DUCKDB_TYPE_STRUCT,
  	      // map type, only useful as logical type
  	      DUCKDB_TYPE_MAP,
  	      // TDDBHugeint
  	      DUCKDB_TYPE_UUID,
  	      // union type, only useful as logical type
  	      DUCKDB_TYPE_UNION,
  	      // duckdb_bit
  	      DUCKDB_TYPE_BIT);

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

  TDDBDecimal = record
    width: UInt8;
    scale: UInt8;
    value: TDDBHugeint;
  end;

  TDDBString = record
    data: PChar;
    size: TIDX;
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

  TDDBBlob = record
    data: pointer;
    size: TIDX;
  end;

  TDDBListEntry = record
    offset: UInt64;
    length: UInt64;
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

  TDDBState = (DDBSUCCESS = 0, DDBERROR = 1);

  TDDBPendingState = (DUCKDBPENDINGRESULTREADY = 0,
  	              DUCKDBPENDINGRESULTNOTREADY = 1,
  	              DUCKDBPENDINGERROR = 2);



