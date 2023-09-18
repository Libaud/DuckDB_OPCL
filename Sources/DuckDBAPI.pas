{========================================================================================
  Module : DuckDBApi
  Description : DuckDB client implementation for Object Pascal
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2023-09-16 Migration of duckdb.h
 ========================================================================================}
unit DuckDBAPI;

{$ifdef FPC}
  {$mode objfpc}{$H+}
{$endif}

{$i DuckDBAPI.inc}

interface

uses
  Classes, SysUtils, CTypes;

const
  {$ifdef LINUX}
  LIBDDB = 'libduckdb.so';
  {$endif}

  {$ifdef WINDOWS}
  LIBDDB = 'duckdb.dll';
  {$endif}

  {$ifdef DARWIN}
  LIBDDB = 'libduckdb.dylib';
  {$endif}

type
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
  	      // duckdb_date
  	      DUCKDB_TYPE_DATE,
  	      // duckdb_time
  	      DUCKDB_TYPE_TIME,
  	      // TDDBInterval
  	      DUCKDB_TYPE_INTERVAL,
  	      // TDDBHugeint
  	      DUCKDB_TYPE_HUGEINT,
  	      // const char*
  	      DUCKDB_TYPE_VARCHAR,
  	      // duckdb_blob
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

  TDuckDBTimeStruct = record
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
    time: TDuckDBTimeStruct;
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
  {$ifdef DUCKDB_API_VERSION < DUCKDB_API_0_3_2}
    _data: pointer;
    _nullmask: PBoolean;
    _type: TDDBType;
    _name: PChar;
  {$else}
    // deprecated, use duckdb_column_data
    __deprecated_data: pointer;
    // deprecated, use duckdb_nullmask_data
    __deprecated_nullmask: PBoolean;
    // deprecated, use duckdb_column_type
    __deprecated_type: TDuckDBType;
    // deprecated, use duckdb_column_name
    __deprecated_name: PChar;
  {$endif}
    _internal_data: pointer;
  end;

  PDDBResult = ^TDDBResult;

  TDDBResult = record
  {$ifdef DUCKDB_API_VERSION < DUCKDB_API_0_3_2}
    column_count: TIDX;
    row_count: TIDX;
    rows_changed: TIDX;
    columns: pDDBColumn;
    error_message: PChar;
  {$else}
    // deprecated, use duckdb_column_count
    __deprecated_column_count: TIDX;
    // deprecated, use duckdb_row_count
    __deprecated_row_count: TIDX;
    // deprecated, use duckdb_rows_changed
    __deprecated_rows_changed: TIDX;
    // deprecated, use duckdb_column_ family of functions
    __deprecated_columns: PDuckDBColumn;
    // deprecated, use TDuckDBResult_error
    __deprecated_error_message: PChar;
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

  PDDBConfig = ^TDDBConfig;

  TDDBConfig = record
    __cnfg: pointer;
  end;

  PDDBArrowSchema = ^TDDBArrowSchema;

  TDDBArrowSchema = record
    __arrs: pointer;
  end;

  PDDBArrowArray = ^TDuckDBArrowArray;

  TDuckDBArrowArray = record
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


//===--------------------------------------------------------------------===//
// Open/Connect
//===--------------------------------------------------------------------===//

{ Creates a new database or opens an existing database file stored at the the given path.
If no path is given a new in-memory database is created instead.
The instantiated database should be closed with 'duckdb_close'

* path: Path to the database file on disk, or `nullptr` or `:memory:` to open an in-memory database.
* out_database: The result database object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_open(const aPath: PChar; var vDatabase: PDDBDatabase): TDDBState; cdecl; external LIBDDB;

{ Extended version of duckdb_open. Creates a new database or opens an existing database file stored at the the given path.

* path: Path to the database file on disk, or `nullptr` or `:memory:` to open an in-memory database.
* out_database: The result database object.
* config: (Optional) configuration used to start up the database system.
* out_error: If set and the function returns DuckDBError, this will contain the reason why the start-up failed.
Note that the error must be freed using `duckdb_free`.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_open_ext(const aPath: PChar; var vDatabase: PDDBDatabase; aConfig: TDDBConfig; var vError: PChar): TDDBState;  cdecl; external LIBDDB;

{ Closes the specified database and de-allocates all memory allocated for that database.
This should be called after you are done with any database allocated through `duckdb_open`.
Note that failing to call `duckdb_close` (in case of e.g. a program crash) will not cause data corruption.
Still it is recommended to always correctly close a database object after you are done with it.

* database: The database object to shut down.
}
procedure duckdb_close(aDatabase: PDDBDatabase); cdecl; external LIBDDB;

{
Opens a connection to a database. Connections are required to query the database, and store transactional state
associated with the connection.
The instantiated connection should be closed using 'duckdb_disconnect'

* database: The database file to connect to.
* out_connection: The result connection object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_connect(aDatabase: TDDBDatabase; var vConnection: PDDBConnection): TDDBState; cdecl; external LIBDDB;

{
Closes the specified connection and de-allocates all memory allocated for that connection.

* connection: The connection to close.
}
procedure duckdb_disconnect(aConnection: PDDBConnection); cdecl; external LIBDDB;

{
Returns the version of the linked DuckDB, with a version postfix for dev versions

Usually used for developing C extensions that must return this for a compatibility check.
}
function duckdb_library_version(): PChar; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Configuration
//===--------------------------------------------------------------------===//
{
Initializes an empty configuration object that can be used to provide start-up options for the DuckDB instance
through `duckdb_open_ext`.

This will always succeed unless there is a malloc failure.

* out_config: The result configuration object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_create_config(var vConfig: PDDBConfig): TDDBState; cdecl; external LIBDDB;

{
This returns the total amount of configuration options available for usage with `duckdb_get_config_flag`.

This should not be called in a loop as it internally loops over all the options.

* returns: The amount of config options available.
}
function duckdb_config_count(): csize_t; cdecl; external LIBDDB;

{
Obtains a human-readable name and description of a specific configuration option. This can be used to e.g.
display configuration options. This will succeed unless `index` is out of range (i.e. `>= TDuckDBConfig_count`).

The result name or description MUST NOT be freed.

* index: The index of the configuration option (between 0 and `TDuckDBConfig_count`)
* out_name: A name of the configuration flag.
* out_description: A description of the configuration flag.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_get_config_flag(aIndex: csize_t; const vName: PPChar; const vDescription: PPChar): TDDBState; cdecl; external LIBDDB;

{
Sets the specified option for the specified configuration. The configuration option is indicated by name.
To obtain a list of config options, see `duckdb_get_config_flag`.

In the source code, configuration options are defined in `config.cpp`.

This can fail if either the name is invalid, or if the value provided for the option is invalid.

* TDuckDBConfig: The configuration object to set the option on.
* name: The name of the configuration flag to set.
* option: The value to set the configuration flag to.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_set_config(aConfig: TDDBConfig; const aName: PChar; const aOption: PChar): TDDBState; cdecl; external LIBDDB;

{
Destroys the specified configuration option and de-allocates all memory allocated for the object.

* config: The configuration object to destroy.
}
procedure duckdb_destroy_config(aConfig: PDDBConfig); cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Query Execution
//===--------------------------------------------------------------------===//
{
Executes a SQL query within a connection and stores the full (materialized) result in the out_result pointer.
If the query fails to execute, DuckDBError is returned and the error message can be retrieved by calling
`TDuckDBResult_error`.

Note that after running `duckdb_query`, `duckdb_destroy_result` must be called on the result object even if the
query fails, otherwise the error stored within the result will not be freed correctly.

* connection: The connection to perform the query in.
* query: The SQL query to run.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_query(aConnection: TDDBConnection; const aQuery: PChar; var vResult: PDDBResult): TDDBState; cdecl; external LIBDDB;

{
Closes the result and de-allocates all memory allocated for that connection.

* result: The result to destroy.
}
procedure duckdb_destroy_result(aResult: PDDBResult); cdecl; external LIBDDB;

{
Returns the column name of the specified column. The result should not need be freed; the column names will
automatically be destroyed when the result is destroyed.

Returns `NULL` if the column is out of range.

* result: The result object to fetch the column name from.
* col: The column index.
* returns: The column name of the specified column.
}
function duckdb_column_name(aResult: PDDBResult; aCol: TIDX): PChar; cdecl; external LIBDDB;

{
Returns the column type of the specified column.

Returns `DUCKDB_TYPE_INVALID` if the column is out of range.

* result: The result object to fetch the column type from.
* col: The column index.
* returns: The column type of the specified column.
}
function duckdb_column_type(aResult: PDDBResult; aCol: TIDX): TDDBType; cdecl; external LIBDDB;

{
Returns the logical column type of the specified column.

The return type of this call should be destroyed with `duckdb_destroy_logical_type`.

Returns `NULL` if the column is out of range.

* result: The result object to fetch the column type from.
* col: The column index.
* returns: The logical column type of the specified column.
}
function duckdb_column_logical_type(aResult: PDDBResult; aCol: TIDX): TDDBLogicalType; cdecl; external LIBDDB;

{
Returns the number of columns present in a the result object.

* result: The result object.
* returns: The number of columns present in the result object.
}
function duckdb_column_count(aResult: PDDBResult): TIDX; cdecl; external LIBDDB;

{
Returns the number of rows present in a the result object.

* result: The result object.
* returns: The number of rows present in the result object.
}
function duckdb_row_count(aResult: PDDBResult): TIDX; cdecl; external LIBDDB;

{
Returns the number of rows changed by the query stored in the result. This is relevant only for INSERT/UPDATE/DELETE
queries. For other queries the rows_changed will be 0.

* result: The result object.
* returns: The number of rows changed.
}
function duckdb_rows_changed(aResult: PDDBResult): TIDX; cdecl; external LIBDDB;

{
**DEPRECATED**: Prefer using `TDuckDBResult_get_chunk` instead.

Returns the data of a specific column of a result in columnar format.

The function returns a dense array which contains the result data. The exact type stored in the array depends on the
corresponding TDuckDBType (as provided by `duckdb_column_type`). For the exact type by which the data should be
accessed, see the comments in [the types section](types) or the `TDuckDBType` enum.

For example, for a column of type `TDuckDBType_INTEGER`, rows can be accessed in the following manner:
```c
int32_t *data = (int32_t *) duckdb_column_data(&result, 0);
printf("Data for row %d: %d\n", row, data[row]);
```

* result: The result object to fetch the column data from.
* col: The column index.
* returns: The column data of the specified column.
}
procedure duckdb_column_data(aResult: PDDBResult; col: TIDX); cdecl; external LIBDDB;

{
**DEPRECATED**: Prefer using `TDuckDBResult_get_chunk` instead.

Returns the nullmask of a specific column of a result in columnar format. The nullmask indicates for every row
whether or not the corresponding row is `NULL`. If a row is `NULL`, the values present in the array provided
by `duckdb_column_data` are undefined.

// ```c
// int32_t *data = (int32_t *) duckdb_column_data(&result, 0);
// bool *nullmask = duckdb_nullmask_data(&result, 0);
// if (nullmask[row]) {
//    printf("Data for row %d: NULL\n", row);
// } else {
//    printf("Data for row %d: %d\n", row, data[row]);
// }
// ```

* result: The result object to fetch the nullmask from.
* col: The column index.
* returns: The nullmask of the specified column.
}
function duckdb_nullmask_data(aResult: PDDBResult; aCol: TIDX): PBoolean; cdecl; external LIBDDB;

{
Returns the error message contained within the result. The error is only set if `duckdb_query` returns `DuckDBError`.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_result` is called.

* aResult: The result object to fetch the error from.
* returns: The error of the result.
}
function TDuckDBResult_error(aResult: PDDBResult): PChar; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Result Functions
//===--------------------------------------------------------------------===//

{
Fetches a data chunk from the TDuckDBResult. This function should be called repeatedly until the result is exhausted.

The result must be destroyed with `duckdb_destroy_data_chunk`.

This function supersedes all `duckdb_value` functions, as well as the `duckdb_column_data` and `duckdb_nullmask_data`
functions. It results in significantly better performance, and should be preferred in newer code-bases.

If this function is used, none of the other result functions can be used and vice versa (i.e. this function cannot be
mixed with the legacy result functions).

Use `TDuckDBResult_chunk_count` to figure out how many chunks there are in the result.

* aResult: The result object to fetch the data chunk from.
* chunk_index: The chunk index to fetch from.
* returns: The resulting data chunk. Returns `NULL` if the chunk index is out of bounds.
}
function TDuckDBResult_get_chunk(aResult: TDDBResult; chunk_index: TIDX): TDDBDataChunk; cdecl; external LIBDDB;

{
Checks if the type of the internal result is StreamQueryResult.

* aResult: The result object to check.
* returns: Whether or not the result object is of the type StreamQueryResult
}
function TDuckDBResult_is_streaming(aResult: TDDBResult): boolean; cdecl; external LIBDDB;

{
Returns the number of data chunks present in the result.

* aResult: The result object
* returns: Number of data chunks present in the result.
}
function TDuckDBResult_chunk_count(aResult: TDDBResult): TIDX; cdecl; external LIBDDB;

// Safe fetch functions
// These functions will perform conversions if necessary.
// On failure (e.g. if conversion cannot be performed or if the value is NULL) a default value is returned.
// Note that these functions are slow since they perform bounds checking and conversion
// For fast access of values prefer using `TDuckDBResult_get_chunk`

{
 * returns: The boolean value at the specified location, or false if the value cannot be converted.
 }
function duckdb_value_boolean(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): boolean; cdecl; external LIBDDB;

{
 * returns: The aValue: Int8 at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_int8(aResult: PDDBResult; col: TIDX; aRow: TIDX): Int8; cdecl; external LIBDDB;

{
 * returns: The aValue: Int16 at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_int16(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): Int16; cdecl; external LIBDDB;

{
 * returns: The aValue: Int32 at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_int32(aResult: PDDBResult; col: TIDX; aRow: TIDX): Int32; cdecl; external LIBDDB;

{
 * returns: The aValue: Int64 at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_int64(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): Int64; cdecl; external LIBDDB;

{
 * returns: The aValue: TDuckDBHhugeint at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_hugeint(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): TDDBHugeint; cdecl; external LIBDDB;

{
 * returns: The TDuckDBDecimal value at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_decimal(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): TDDBDecimal;  cdecl; external LIBDDB;

{
 * returns: The UInt8 value at the specified location, or 0 if the value cannot be converted.
 }

function duckdb_value_uint8(aResult: PDDBResult; aCol: TIDX;  aRow: TIDX): UInt8;  cdecl; external LIBDDB;

{
 * returns: The UInt16 value at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_uint16(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): UInt16; cdecl; external LIBDDB;

{
 * returns: The UInt32 value at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_uint32(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): UInt32; cdecl; external LIBDDB;

{
 * returns: The UInt64 value at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_uint64(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): UInt64; cdecl; external LIBDDB;

{
 * returns: The float value at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_float(aResult: PDDBResult; aCol: TIDX;  aRow: TIDX): Extended; cdecl; external LIBDDB;

{
 * returns: The aValue: double at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_double(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): double; cdecl;  external LIBDDB;

{
 * returns: The duckdb_date value at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_date(aResult: PDDBResult; aCol: TIDX; aRow: TIDX):  TDDBDate; cdecl; external LIBDDB;

{
 * returns: The aValue: TDuckDBTime at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_time(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): TDDBTime; cdecl; external LIBDDB;

{
 * returns: The aValue: TDuckDBTimestamp at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_timestamp(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): TDDBTimestamp; cdecl; external LIBDDB;

{
 * returns: The aValue: TDuckDBInterval at the specified location, or 0 if the value cannot be converted.
 }
function duckdb_value_interval(aResult: PDDBResult; aCol: TIDX; aRow: TIDX):  TDDBInterval; cdecl; external LIBDDB;

{
* DEPRECATED: use duckdb_value_string instead. This function does not work correctly if the string contains null bytes.
* returns: The text value at the specified location as a null-terminated string, or nullptr if the value cannot be
converted. The result must be freed with `duckdb_free`.
}
function duckdb_value_varchar(aResult: PDDBResult; aCol: TIDX; aRow: TIDX):  PChar; cdecl; external LIBDDB;

{s
* returns: The string value at the specified location.
The result must be freed with `duckdb_free`.
}
function duckdb_value_string(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): TDDBString; cdecl; external LIBDDB;

{
* DEPRECATED: use duckdb_value_string_internal instead. This function does not work correctly if the string contains
null bytes.
* returns: The char* value at the specified location. ONLY works on VARCHAR columns and does not auto-cast.
If the column is NOT a VARCHAR column this function will return NULL.

The result must NOT be freed.
}
function duckdb_value_varchar_internal(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): PChar; cdecl; external LIBDDB;

{
* DEPRECATED: use duckdb_value_string_internal instead. This function does not work correctly if the string contains
null bytes.
* returns: The char* value at the specified location. ONLY works on VARCHAR columns and does not auto-cast.
If the column is NOT a VARCHAR column this function will return NULL.

The result must NOT be freed.
}
function duckdb_value_string_internal(aResult: PDDBResult; aCol: TIDX;  aRow: TIDX): TDDBString; cdecl; external LIBDDB;

{
* returns: The duckdb_blob value at the specified location. Returns a blob with blob.data set to nullptr if the
value cannot be converted. The resulting "blob.data" must be freed with `duckdb_free.`
}
function duckdb_value_blob(aResult: PDDBResult; aCol: TIDX; aRow: TIDX): TDDBBlob; cdecl; external LIBDDB;

{
 * returns: Returns true if the value at the specified index is NULL, and false otherwise.
 }
function duckdb_value_is_null(aResult: PDDBResult; aCol: TIDX; aRow: TIDX):  boolean; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Helpers
//===--------------------------------------------------------------------===//
{
Allocate `size` bytes of memory using the duckdb internal malloc function. Any memory allocated in this manner
should be freed using `duckdb_free`.

* size: The number of bytes to allocate.
* returns: A pointer to the allocated memory region.
}
procedure duckdb_malloc(size: csize_t); cdecl; external LIBDDB;

{
Free a value returned from `duckdb_malloc`, `duckdb_value_varchar` or `duckdb_value_blob`.

* ptr: The memory region to de-allocate.
}
procedure duckdb_free(ptr: pointer); cdecl; external LIBDDB;

{
The internal vector size used by DuckDB.
This is the amount of tuples that will fit into a data chunk created by `duckdb_create_data_chunk`.

* returns: The vector size.
}
function duckdb_vector_size():  TIDX;  cdecl; external LIBDDB;

{
Whether or not the duckdb_string_t value is inlined.
This means that the data of the string does not have a separate allocation.

}
function duckdb_string_is_inlined(duckdb_string_t: string): boolean;  cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Date/Time/Timestamp Helpers
//===--------------------------------------------------------------------===//
{
Decompose a `TDuckDBDate` object into year, month and date (stored as `TDuckDBDate_struct`).

* date: The date object, as obtained from a `TDuckDBType_DATE` column.
* returns: The `TDuckDBDate_struct` with the decomposed elements.
}
function duckdb_from_date(date: TDDBDate):  TDDBDateStruct; cdecl; external LIBDDB;

{
Re-compose a `TDuckDBDate` from year, month and date (`TDuckDBDate_struct`).

* date: The year, month and date stored in a `TDuckDBDate_struct`.
* returns: The `TDuckDBDate` element.
}
function duckdb_to_date(date: TDDBDateStruct): TDDBDate; cdecl; external LIBDDB;

{
Decompose a `duckdb_time` object into hour, minute, second and microsecond (stored as `duckdb_time_struct`).

* time: The time object, as obtained from a `TDuckDBType_TIME` column.
* returns: The `duckdb_time_struct` with the decomposed elements.
}
function duckdb_from_time(time: TDDBTime): TDuckDBTimeStruct; cdecl; external LIBDDB;

{
Re-compose a `duckdb_time` from hour, minute, second and microsecond (`duckdb_time_struct`).

* time: The hour, minute, second and microsecond in a `duckdb_time_struct`.
* returns: The `duckdb_time` element.
}
function duckdb_to_time(time: TDuckDBTimeStruct): TDDBTime; cdecl; external LIBDDB;

{
Decompose a `TDuckDBTimestamp` object into a `duckdb_timestamp_struct`.

* ts: The ts object, as obtained from a `TDuckDBType_TIMESTAMP` column.
* returns: The `duckdb_timestamp_struct` with the decomposed elements.
}
function duckdb_from_timestamp(ts: TDDBTimestamp): TDDBTimestampStruct; cdecl; external LIBDDB;

{
Re-compose a `TDuckDBTimestamp` from a duckdb_timestamp_struct.

* ts: The de-composed elements in a `duckdb_timestamp_struct`.
* returns: The `TDuckDBTimestamp` element.
}
function duckdb_to_timestamp(ts: TDDBTimestampStruct): TDDBTimestamp; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Hugeint Helpers
//===--------------------------------------------------------------------===//
{
Converts a TDuckDBHugeint object (as obtained from a `TDuckDBType_HUGEINT` column) into a double.

* val: The hugeint value.
* returns: The converted `double` element.
}
function duckdb_hugeint_to_double(val: TDDBHugeint): double; cdecl;  external LIBDDB;

{
Converts a aValue: double to a TDuckDBHugeint object.

If the conversion fails because the aValue: double is too big the result will be 0.

* val: The aValue: double.
* returns: The converted `TDuckDBHugeint` element.
}
function duckdb_double_to_hugeint(val: double): TDDBHugeint; cdecl; external LIBDDB;

{
Converts a aValue: double to a TDuckDBDecimal object.

If the conversion fails because the aValue: double is too big, or the width/scale are invalid the result will be 0.

* val: The aValue: double.
* returns: The converted `TDuckDBDecimal` element.
}
function duckdb_double_to_decimal(val: double; width: UInt8; scale: UInt8): TDDBDecimal; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Decimal Helpers
//===--------------------------------------------------------------------===//
{
Converts a TDuckDBDecimal object (as obtained from a `TDuckDBType_DECIMAL` column) into a double.

* val: The decimal value.
* returns: The converted `double` element.
}
function duckdb_decimal_to_double(val: TDDBDecimal): double; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Prepared Statements
//===--------------------------------------------------------------------===//
// A prepared statement is a parameterized query that allows you to bind parameters to it.
// * This is useful to easily supply parameters to functions and avoid SQL injection attacks.
// * This is useful to speed up queries that you will execute several times with different parameters.
// Because the query will only be parsed, bound, optimized and planned once during the prepare stage,
// rather than once per execution.
// For example:
//   SELECT * FROM tbl WHERE id=?
// Or a query with multiple parameters:
//   SELECT * FROM tbl WHERE id=$1 OR name=$2

{
Create a prepared statement object from a query.

Note that after calling `duckdb_prepare`, the prepared statement should always be destroyed using
`duckdb_destroy_prepare`, even if the prepare fails.

If the prepare fails, `duckdb_prepare_error` can be called to obtain the reason why the prepare failed.

* connection: The connection object
* query: The SQL query to prepare
* out_prepared_statement: The resulting prepared statement object
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_prepare(connection: TDDBConnection; const query: PChar;
                                       out_prepared_statement: PDDBPreparedStatement): TDDBState; cdecl; external LIBDDB;

{
Closes the prepared statement and de-allocates all memory allocated for the statement.

* prepared_statement: The prepared statement to destroy.
}
procedure duckdb_destroy_prepare(aPreparedStatement: PDDBPreparedStatement); cdecl; external LIBDDB;

{
Returns the error message associated with the given prepared statement.
If the prepared statement has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_prepare` is called.

* prepared_statement: The prepared statement to obtain the error from.
* returns: The error message, or `nullptr` if there is none.
}
function duckdb_prepare_error(aPreparedStatement: TDDBPreparedStatement): PChar; cdecl; external LIBDDB;

{
Returns the number of parameters that can be provided to the given prepared statement.

Returns 0 if the query was not successfully prepared.

* prepared_statement: The prepared statement to obtain the number of parameters for.
}
function duckdb_nparams(aPreparedStatement: TDDBPreparedStatement): TIDX; cdecl; external LIBDDB;

{
Returns the parameter type for the parameter at the given index.

Returns `TDuckDBType_INVALID` if the parameter index is out of range or the statement was not successfully prepared.

* prepared_statement: The prepared statement.
* param_idx: The parameter index.
* returns: The parameter type
}
function duckdb_param_type(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX): TDDBType; cdecl; external LIBDDB;

{
Clear the params bind to the prepared statement.
}
function duckdb_clear_bindings(aPreparedStatement: TDDBPreparedStatement): TDDBState; cdecl; external LIBDDB;

{
Binds a aValue: boolean to the prepared statement at the specified index.
}
function duckdb_bind_boolean(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: boolean): TDDBState; cdecl; external LIBDDB;

{
Binds an aValue: Int8 to the prepared statement at the specified index.
}
function duckdb_bind_int8(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: Int8): TDDBState; cdecl; external LIBDDB;

{
Binds an aValue: Int16 to the prepared statement at the specified index.
}
function duckdb_bind_int16(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: Int16): TDDBState; cdecl; external LIBDDB;

{
Binds an aValue: Int32 to the prepared statement at the specified index.
}
function duckdb_bind_int32(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: Int32): TDDBState; cdecl; external LIBDDB;

{
Binds an aValue: Int64 to the prepared statement at the specified index.
}
function duckdb_bind_int64( aPreparedStatement: TDDBPreparedStatement; aParam_idx: TIDX; aVal: Int64): TDDBState; cdecl; external LIBDDB;

{
Binds an aValue: TDuckDBHhugeint to the prepared statement at the specified index.
}
function duckdb_bind_hugeint(aPreparedStatement: TDDBPreparedStatement;  aParamIDX: TIDX;  val: TDDBHugeint): TDDBState; cdecl; external LIBDDB;
{
Binds a TDuckDBDecimal value to the prepared statement at the specified index.
}
function duckdb_bind_decimal(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: TDDBDecimal): TDDBState; cdecl; external LIBDDB;

{
Binds an UInt8 value to the prepared statement at the specified index.
}
function duckdb_bind_uint8(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: UInt8): TDDBState; cdecl; external LIBDDB;

{
Binds an UInt16 value to the prepared statement at the specified index.
}
function duckdb_bind_uint16(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: UInt16): TDDBState; cdecl;  external LIBDDB;

{
Binds an UInt32 value to the prepared statement at the specified index.
}
function duckdb_bind_uint32(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: UInt32): TDDBState; cdecl; external LIBDDB;

{
Binds an UInt64 value to the prepared statement at the specified index.
}
function duckdb_bind_uint64(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: UInt64): TDDBState; cdecl; external LIBDDB;

{
Binds an float value to the prepared statement at the specified index.
}
function duckdb_bind_float(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: Extended): TDDBState; cdecl; external LIBDDB;

{
Binds an aValue: double to the prepared statement at the specified index.
}
function duckdb_bind_double(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: double): TDDBState; cdecl; external LIBDDB;

{
Binds a aValue: TDuckDBDate to the prepared statement at the specified index.
}
function duckdb_bind_date(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: TDDBDate): TDDBState; cdecl; external LIBDDB;

{
Binds a duckdb_time value to the prepared statement at the specified index.
}
function duckdb_bind_time(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: TDDBTime): TDDBState; cdecl; external LIBDDB;

{
Binds a aValue: TDuckDBTimestamp to the prepared statement at the specified index.
}
function duckdb_bind_timestamp(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: TDDBTimestamp): TDDBState; cdecl; external LIBDDB;

{
Binds a aValue: TDuckDBInterval to the prepared statement at the specified index.
}
function duckdb_bind_interval(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; aVal: TDDBInterval): TDDBState; cdecl;  external LIBDDB;

{
Binds a null-terminated varchar value to the prepared statement at the specified index.
}
function duckdb_bind_varchar(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; const aVal: PChar): TDDBState; cdecl; external LIBDDB;

{
Binds a varchar value to the prepared statement at the specified index.
}
function duckdb_bind_varchar_length(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; const PCharval, aLength: TIDX): TDDBState; cdecl; external LIBDDB;

{
Binds a blob value to the prepared statement at the specified index.
}
function duckdb_bind_blob(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX; const pointerdata, aLength: TIDX): TDDBState; cdecl; external LIBDDB;

{
Binds a NULL value to the prepared statement at the specified index.
}
function duckdb_bind_null(aPreparedStatement: TDDBPreparedStatement; aParamIDX: TIDX): TDDBState; cdecl; external LIBDDB;

{
Executes the prepared statement with the given bound parameters, and returns a materialized query result.

This method can be called multiple times for each prepared statement, and the parameters can be modified
between calls to this function.

* prepared_statement: The prepared statement to execute.
* out_aResult: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_execute_prepared(aPreparedStatement: TDDBPreparedStatement; var vResult: PDDBResult): TDDBState; cdecl; external LIBDDB;

{
Executes the prepared statement with the given bound parameters, and returns an arrow query result.

* prepared_statement: The prepared statement to execute.
* out_aResult: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_execute_prepared_arrow(aPreparedStatement: TDDBPreparedStatement; var vResult: PDDBArrow): TDDBState; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Extract Statements
//===--------------------------------------------------------------------===//
// A query string can be extracted into multiple SQL statements. Each statement can be prepared and executed separately.

{
Extract all statements from a query.
Note that after calling `duckdb_extract_statements`, the extracted statements should always be destroyed using
`duckdb_destroy_extracted`, even if no statements were extracted.
If the extract fails, `duckdb_extract_statements_error` can be called to obtain the reason why the extract failed.
* connection: The connection object
* query: The SQL query to extract
* out_extracted_statements: The resulting extracted statements object
* returns: The number of extracted statements or 0 on failure.
}
function duckdb_extract_statements(aConnection: TDDBConnection; const aQuery: PChar; var vExtractedStatements: PDDBExtractedStatements):  TIDX; cdecl; external LIBDDB;

{
Prepare an extracted statement.
Note that after calling `duckdb_prepare_extracted_statement`, the prepared statement should always be destroyed using
`duckdb_destroy_prepare`, even if the prepare fails.
If the prepare fails, `duckdb_prepare_error` can be called to obtain the reason why the prepare failed.
* connection: The connection object
* extracted_statements: The extracted statements object
* index: The index of the extracted statement to prepare
* out_prepared_statement: The resulting prepared statement object
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_prepare_extracted_statement(aConnection: TDDBConnection; aExtractedStatements: TDDBExtractedStatements;
                                            aIndex: TIDX; var vPreparedStatement: PDDBPreparedStatement): TDDBState; cdecl; external LIBDDB;
{
Returns the error message contained within the extracted statements.
The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_extracted` is called.
* aResult: The extracted statements to fetch the error from.
* returns: The error of the extracted statements.
}
function duckdb_extract_statements_error(aExtractedStatements: TDDBExtractedStatements): PChar; cdecl; external LIBDDB;

{
De-allocates all memory allocated for the extracted statements.
* extracted_statements: The extracted statements to destroy.
}
procedure duckdb_destroy_extracted(aExtractedStatements: PDDBExtractedStatements); cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Pending Result Interface
//===--------------------------------------------------------------------===//
{
Executes the prepared statement with the given bound parameters, and returns a pending result.
The pending result represents an intermediate structure for a query that is not yet fully executed.
The pending result can be used to incrementally execute a query, returning control to the client between tasks.

Note that after calling `duckdb_pending_prepared`, the pending result should always be destroyed using
`duckdb_destroy_pending`, even if this function returns DuckDBError.

* prepared_statement: The prepared statement to execute.
* out_aResult: The pending query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_pending_prepared(aPreparedStatement: TDDBPreparedStatement; var vResult: PDDBPendingResult): TDDBState; cdecl; external LIBDDB;

{
Executes the prepared statement with the given bound parameters, and returns a pending result.
This pending result will create a streaming TDuckDBResult when executed.
The pending result represents an intermediate structure for a query that is not yet fully executed.

Note that after calling `duckdb_pending_prepared_streaming`, the pending result should always be destroyed using
`duckdb_destroy_pending`, even if this function returns DuckDBError.

* prepared_statement: The prepared statement to execute.
* out_aResult: The pending query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_pending_prepared_streaming(aPreparedStatement: TDDBPreparedStatement; var vResult: PDDBPendingResult): TDDBState; cdecl; external LIBDDB;

{
Closes the pending result and de-allocates all memory allocated for the result.

* pending_aResult: The pending result to destroy.
}
procedure duckdb_destroy_pending(aPendingResult: PDDBPendingResult); cdecl; external LIBDDB;

{
Returns the error message contained within the pending result.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_pending` is called.

* aResult: The pending result to fetch the error from.
* returns: The error of the pending result.
}
function duckdb_pending_error(aPendingResult: TDDBPendingResult): PChar; cdecl; external LIBDDB;

{
Executes a single task within the query, returning whether or not the query is ready.

If this returns DUCKDB_PENDING_RESULT_READY, the duckdb_execute_pending function can be called to obtain the result.
If this returns DUCKDB_PENDING_RESULT_NOT_READY, the duckdb_pending_execute_task function should be called again.
If this returns DUCKDB_PENDING_ERROR, an error occurred during execution.

The error message can be obtained by calling duckdb_pending_error on the pending_result.

* pending_aResult: The pending result to execute a task within..
* returns: The state of the pending result after the execution.
}
function duckdb_pending_execute_task(aPendingResult: TDDBPendingResult): TDDBPendingState; cdecl; external LIBDDB;

{
Fully execute a pending query result, returning the final query result.

If duckdb_pending_execute_task has been called until DUCKDB_PENDING_RESULT_READY was returned, this will return fast.
Otherwise, all remaining tasks must be executed first.

* pending_aResult: The pending result to execute.
* out_aResult: The result object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_execute_pending(aPendingResult: TDDBPendingResult; var vResult: PDDBResult): TDDBState; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Value Interface
//===--------------------------------------------------------------------===//
{
Destroys the value and de-allocates all memory allocated for that type.

* value: The value to destroy.
}
procedure duckdb_destroy_value(aValue: PDDBValue); cdecl; external LIBDDB;

{
Creates a value from a null-terminated string

* value: The null-terminated string
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
function duckdb_create_varchar(const aText: PChar): TDDBValue; cdecl; external LIBDDB;

{
Creates a value from a string

* value: The text
* length: The length of the text
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
function duckdb_create_varchar_length(const atext: PChar; aLength: TIDX): TDDBValue; cdecl; external LIBDDB;

{
Creates a value from an int64

* value: The bigint value
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
function duckdb_create_int64(aVal: Int64): TDDBValue; cdecl; external LIBDDB;

{
Obtains a string representation of the given value.
The result must be destroyed with `duckdb_free`.

* value: The value
* returns: The string value. This must be destroyed with `duckdb_free`.
}
function duckdb_get_varchar(aValue: TDDBValue): PChar; cdecl; external LIBDDB;

{
Obtains an int64 of the given value.

* value: The value
* returns: The int64 value, or 0 if no conversion is possible
}
function duckdb_get_int64(Value: TDDBValue): Int64; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Logical Type Interface
//===--------------------------------------------------------------------===//

{
Creates a `TDuckDBLogicalType` from a standard primitive type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

This should not be used with `TDuckDBType_DECIMAL`.

* type: The primitive type to create.
* returns: The logical type.
}
function duckdb_create_logical_type(aType: TDDBType): TDDBLogicalType; cdecl; external LIBDDB;

{
Creates a list type from its child type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* type: The child type of list type to create.
* returns: The logical type.
}
function duckdb_create_list_type(aType: TDDBLogicalType): TDDBLogicalType; cdecl; external LIBDDB;

{
Creates a map type from its key type and value type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* type: The key type and value type of map type to create.
* returns: The logical type.
}
function duckdb_create_map_type(aKeyType: TDDBLogicalType; aValueType: TDDBLogicalType): TDDBLogicalType; cdecl; external LIBDDB;

{
Creates a UNION type from the passed types array
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* types: The array of types that the union should consist of.
* type_amount: The size of the types array.
* returns: The logical type.
}
function duckdb_create_union_type(aMemberTypes: TDDBLogicalType; const aMemberNames: PPChar; aMemberCount: TIDX): TDDBLogicalType; cdecl; external LIBDDB;

{
Creates a `TDuckDBLogicalType` of type decimal with the specified width and scale
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* width: The width of the decimal type
* scale: The scale of the decimal type
* returns: The logical type.
}
function duckdb_create_decimal_type(aWidth: UInt8; aScale: UInt8): TDDBLogicalType; cdecl; external LIBDDB;

{
Retrieves the type class of a `TDuckDBLogicalType`.

* type: The logical type object
* returns: The type id
}
function duckdb_get_type_id(aType: TDDBLogicalType): TDDBType; cdecl; external LIBDDB;

{
Retrieves the width of a decimal type.

* type: The logical type object
* returns: The width of the decimal type
}
function duckdb_decimal_width(aType: TDDBLogicalType): UInt8; cdecl; external LIBDDB;

{
Retrieves the scale of a decimal type.

* type: The logical type object
* returns: The scale of the decimal type
}
function duckdb_decimal_scale(aType: TDDBLogicalType): UInt8; cdecl; external LIBDDB;

{
Retrieves the internal storage type of a decimal type.

* type: The logical type object
* returns: The internal type of the decimal type
}
function duckdb_decimal_internal_type(aType: TDDBLogicalType): TDDBType; cdecl; external LIBDDB;

{
Retrieves the internal storage type of an enum type.

* type: The logical type object
* returns: The internal type of the enum type
}
function duckdb_enum_internal_type(aType: TDDBLogicalType): TDDBType; cdecl; external LIBDDB;

{
Retrieves the dictionary size of the enum type

* type: The logical type object
* returns: The dictionary size of the enum type
}
function duckdb_enum_dictionary_size(aType: TDDBLogicalType): UInt32; cdecl; external LIBDDB;

{
Retrieves the dictionary value at the specified position from the enum.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The index in the dictionary
* returns: The string value of the enum type. Must be freed with `duckdb_free`.
}
function duckdb_enum_dictionary_value(aType: TDDBLogicalType; aIndex: TIDX): PChar; cdecl; external LIBDDB;

{
Retrieves the child type of the given list type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The child type of the list type. Must be destroyed with `duckdb_destroy_logical_type`.
}
function duckdb_list_type_child_type(aType: TDDBLogicalType): TDDBLogicalType; cdecl; external LIBDDB;

{
Retrieves the key type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The key type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.
}
function duckdb_map_type_key_type(aType: TDDBLogicalType): TDDBLogicalType; cdecl; external LIBDDB;

{
Retrieves the value type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The value type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.
}
function duckdb_map_type_value_type(aType: TDDBLogicalType): TDDBLogicalType; cdecl; external LIBDDB;

{
Returns the number of children of a struct type.

* type: The logical type object
* returns: The number of children of a struct type.
}
function duckdb_struct_type_child_count(aType: TDDBLogicalType): TIDX; cdecl; external LIBDDB;

{
Retrieves the name of the struct child.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The child index
* returns: The name of the struct type. Must be freed with `duckdb_free`.
}
function duckdb_struct_type_child_name(aType: TDDBLogicalType; aIndex: TIDX):  PChar; cdecl; external LIBDDB;

{
Retrieves the child type of the given struct type at the specified index.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* index: The child index
* returns: The child type of the struct type. Must be destroyed with `duckdb_destroy_logical_type`.
}
function duckdb_struct_type_child_type(aType: TDDBLogicalType; aIndex: TIDX): TDDBLogicalType; cdecl; external LIBDDB;

{
Returns the number of members that the union type has.

* type: The logical type (union) object
* returns: The number of members of a union type.
}
function duckdb_union_type_member_count(aType: TDDBLogicalType): TIDX; cdecl; external LIBDDB;

{
Retrieves the name of the union member.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The child index
* returns: The name of the union member. Must be freed with `duckdb_free`.
}
function duckdb_union_type_member_name(aType: TDDBLogicalType; aIndex: TIDX): PChar; cdecl; external LIBDDB;

{
Retrieves the child type of the given union member at the specified index.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* index: The child index
* returns: The child type of the union member. Must be destroyed with `duckdb_destroy_logical_type`.
}
function duckdb_union_type_member_type(aType: TDDBLogicalType; aIndex: TIDX): TDDBLogicalType; cdecl; external LIBDDB;

{
Destroys the logical type and de-allocates all memory allocated for that type.

* type: The logical type to destroy.
}
procedure duckdb_destroy_logical_type(aType: PDDBLogicalType); cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Data Chunk Interface
//===--------------------------------------------------------------------===//
{
Creates an empty DataChunk with the specified set of types.

* types: An array of types of the data chunk.
* column_count: The number of columns.
* returns: The data chunk.
}
function duckdb_create_data_chunk(aTypes: TDDBLogicalType; aColumnCount: TIDX): TDDBDataChunk; cdecl; external LIBDDB;

{
Destroys the data chunk and de-allocates all memory allocated for that chunk.

* chunk: The data chunk to destroy.
}
procedure duckdb_destroy_data_chunk(aChunk: PDDBDataChunk); cdecl; external LIBDDB;

{
Resets a data chunk, clearing the validity masks and setting the cardinality of the data chunk to 0.

* chunk: The data chunk to reset.
}
procedure TDuckDBDataChunk_reset(aChunk: TDDBDataChunk); cdecl; external LIBDDB;

{
Retrieves the number of columns in a data chunk.

* chunk: The data chunk to get the data from
* returns: The number of columns in the data chunk
}
function duckdb_data_chunk_get_column_count(aChunk: TDDBDataChunk): TIDX; cdecl; external LIBDDB;

{
Retrieves the vector at the specified column index in the data chunk.

The pointer to the vector is valid for as long as the chunk is alive.
It does NOT need to be destroyed.

* chunk: The data chunk to get the data from
* returns: The vector
}
function TDuckDBDataChunk_get_vector(aChunk: TDDBDataChunk; aColIDX: TIDX): TDDBVector; cdecl; external LIBDDB;

{
Retrieves the current number of tuples in a data chunk.

* chunk: The data chunk to get the data from
* returns: The number of tuples in the data chunk
}
function duckdb_data_chunk_get_size(aChunk: TDDBDataChunk): TIDX; cdecl; external LIBDDB;

{
Sets the current number of tuples in a data chunk.

* chunk: The data chunk to set the size in
* size: The number of tuples in the data chunk
}
procedure duckdb_data_chunk_set_size(aChunk: TDDBDataChunk; aSize: TIDX); cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Vector Interface
//===--------------------------------------------------------------------===//
{
Retrieves the column type of the specified vector.

The result must be destroyed with `duckdb_destroy_logical_type`.

* vector: The vector get the data from
* returns: The type of the vector
}
function duckdb_vector_get_column_type(aVector: TDDBVector): TDDBLogicalType; cdecl; external LIBDDB;

{
Retrieves the data pointer of the vector.

The data pointer can be used to read or write values from the vector.
How to read or write values depends on the type of the vector.

* vector: The vector to get the data from
* returns: The data pointer
}
procedure duckdb_vector_get_data(aVector: TDDBVector); cdecl; external LIBDDB;

{
Retrieves the validity mask pointer of the specified vector.

If all values are valid, this function MIGHT return NULL!

The validity mask is a bitset that signifies null-ness within the data chunk.
It is a series of UInt64 values, where each UInt64 value contains validity for 64 tuples.
The bit is set to 1 if the value is valid (i.e. not NULL) or 0 if the value is invalid (i.e. NULL).

Validity of a specific value can be obtained like this:

TIDX entry_idx = row_idx / 64;
TIDX idx_in_entry = row_idx % 64;
bool is_valid = validity_mask[entry_idx] & (1 << idx_in_entry);

Alternatively, the (slower) duckdb_validity_row_is_valid function can be used.

* vector: The vector to get the data from
* returns: The pointer to the validity mask, or NULL if no validity mask is present
}
function duckdb_vector_get_validity(aVector: TDDBVector): PUInt64; cdecl; external LIBDDB;

{
Ensures the validity mask is writable by allocating it.

After this function is called, `duckdb_vector_get_validity` will ALWAYS return non-NULL.
This allows null values to be written to the vector, regardless of whether a validity mask was present before.

* vector: The vector to alter
}
procedure duckdb_vector_ensure_validity_writable(aVector: TDDBVector); cdecl; external LIBDDB;

{
Assigns a string element in the vector at the specified location.

* vector: The vector to alter
* index: The row position in the vector to assign the string to
* str: The null-terminated string
}
procedure duckdb_vector_assign_string_element(aVector: TDDBVector; aIndex: TIDX; const aStr: PChar); cdecl; external LIBDDB;

{
Assigns a string element in the vector at the specified location.

* vector: The vector to alter
* index: The row position in the vector to assign the string to
* str: The string
* str_len: The length of the string (in bytes)
}
procedure duckdb_vector_assign_string_element_len(aVector: TDDBVector; aIndex: TIDX; const aStr: PChar ; aStrLen: TIDX); cdecl; external LIBDDB;

{
Retrieves the child vector of a list vector.

The resulting vector is valid as long as the parent vector is valid.

* vector: The vector
* returns: The child vector
}
function duckdb_list_vector_get_child(aVector: TDDBVector): TDDBVector; cdecl; external LIBDDB;

{
Returns the size of the child vector of the list

* vector: The vector
* returns: The size of the child list
}
function duckdb_list_vector_get_size(aVector: TDDBVector): TIDX; cdecl; external LIBDDB;

{
Sets the total size of the underlying child-vector of a list vector.

* vector: The list vector.
* size: The size of the child list.
* returns: The duckdb state. Returns DuckDBError if the vector is nullptr.
}
function duckdb_list_vector_set_size(aVector: TDDBVector; aSize: TIDX): TDDBState; cdecl; external LIBDDB;

{
Sets the total capacity of the underlying child-vector of a list.

* vector: The list vector.
* required_capacity: the total capacity to reserve.
* return: The duckdb state. Returns DuckDBError if the vector is nullptr.
}
function duckdb_list_vector_reserve(aVector: TDDBVector; aRequiredCapacity: TIDX): TDDBState; cdecl; external LIBDDB;

{
Retrieves the child vector of a struct vector.

The resulting vector is valid as long as the parent vector is valid.

* vector: The vector
* index: The child index
* returns: The child vector
}
function  duckdb_struct_vector_get_child(aVector: TDDBVector; aIndex: TIDX): TDDBVector; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Validity Mask Functions
//===--------------------------------------------------------------------===//
{
Returns whether or not a row is valid (i.e. not NULL) in the given validity mask.

* validity: The validity mask, as obtained through `duckdb_data_chunk_get_validity`
* row: The row index
* returns: true if the row is valid, false otherwise
}
function duckdb_validity_row_is_valid(aValidity: PUInt64; aRow: TIDX):  boolean; cdecl; external LIBDDB;

{
In a validity mask, sets a specific row to either valid or invalid.

Note that `duckdb_data_chunk_ensure_validity_writable` should be called before calling `duckdb_data_chunk_get_validity`,
to ensure that there is a validity mask to write to.

* validity: The validity mask, as obtained through `duckdb_data_chunk_get_validity`.
* row: The row index
* valid: Whether or not to set the row to valid, or invalid
}
procedure duckdb_validity_set_row_validity(aValidity: PUInt64; aRow: TIDX; aValid: boolean); cdecl; external LIBDDB;

{
In a validity mask, sets a specific row to invalid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to false.

* validity: The validity mask
* row: The row index
}
procedure duckdb_validity_set_row_invalid(aValidity: PUInt64; aRow: TIDX); cdecl; external LIBDDB;

{
In a validity mask, sets a specific row to valid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to true.

* validity: The validity mask
* row: The row index
}
procedure duckdb_validity_set_row_valid(aValidity: PUInt64; aRow: TIDX); external LIBDDB;

{===--------------------------------------------------------------------===
 Table Functions
 ===--------------------------------------------------------------------===}
type
  PDuckDBTableFunction = ^TDuckDBTableFunction;
  TDuckDBTableFunction = pointer;
  TDuckDBBindInfo = pointer;
  TDuckDBInitInfo = pointer;
  TDuckDBFunctionInfo = pointer;

  // Callbacks
  TDuckDBTableCallbackBind = procedure (aInfo: TDuckDBBindInfo);
  TDuckDBTableCallbackInit = procedure (aInfo: TDuckDBInitInfo);
  TDuckDBTableCallback = procedure (aInfo: TDuckDBFunctionInfo; aOutput: TDDBDataChunk);
  TDuckDBDeleteCallback = procedure (aData: pointer);

{
Creates a new empty table function.

The return value should be destroyed with `duckdb_destroy_table_function`.

* returns: The table function object.
}
function duckdb_create_table_function(): TDuckDBTableFunction; cdecl; external LIBDDB;

{
Destroys the given table function object.

* table_function: The table function to destroy
}
procedure duckdb_destroy_table_function(aTableFunction: PDuckDBTableFunction); cdecl; external LIBDDB;

{
Sets the name of the given table function.

* table_function: The table function
* name: The name of the table function
}
procedure duckdb_table_function_set_name(aTableFunction: TDuckDBTableFunction; const aName: PChar); cdecl; external LIBDDB;

{
Adds a parameter to the table function.

* table_function: The table function
* type: The type of the parameter to add.
}
procedure duckdb_table_function_add_parameter(aTableFunction: TDuckDBTableFunction; aType: TDDBLogicalType); cdecl; external LIBDDB;

{
Adds a named parameter to the table function.

* table_function: The table function
* name: The name of the parameter
* type: The type of the parameter to add.
}
procedure duckdb_table_function_add_named_parameter(aTableFunction: TDuckDBTableFunction; const aName: PChar; aType: TDDBLogicalType); cdecl; external LIBDDB;

{
Assigns extra information to the table function that can be fetched during binding, etc.

* table_function: The table function
* extra_info: The extra information
* destroy: The callback that will be called to destroy the bind data (if any)
}
procedure duckdb_table_function_set_extra_info(aTableFunction: TDuckDBTableFunction; aExtra_info: pointer; aDestroy: TDuckDBDeleteCallback); cdecl; external LIBDDB;

{
Sets the bind function of the table function

* table_function: The table function
* bind: The bind function
}
procedure duckdb_table_function_set_bind(aTableFunction: TDuckDBTableFunction; aBind: TDuckDBTableCallbackBind); cdecl; external LIBDDB;

{
Sets the init function of the table function

* table_function: The table function
* init: The init function
}
procedure duckdb_table_function_set_init(aTableFunction: TDuckDBTableFunction; aInit: TDuckDBTableCallbackInit); cdecl; external LIBDDB;

{
Sets the thread-local init function of the table function

* table_function: The table function
* init: The init function
}
procedure duckdb_table_function_set_local_init(aTableFunction: TDuckDBTableFunction; aInit: TDuckDBTableCallbackInit); cdecl;  external LIBDDB;

{
Sets the main function of the table function

* table_function: The table function
* function: The function
}
procedure duckdb_table_function_set_function(aTableFunction: TDuckDBTableFunction; aFunction: TDuckDBTableCallback); cdecl; external LIBDDB;

{
Sets whether or not the given table function supports projection pushdown.

If this is set to true, the system will provide a list of all required columns in the `init` stage through
the `duckdb_init_get_column_count` and `duckdb_init_get_column_index` functions.
If this is set to false (the default), the system will expect all columns to be projected.

* table_function: The table function
* pushdown: True if the table function supports projection pushdown, false otherwise.
}
procedure duckdb_table_function_supports_projection_pushdown(aTableFunction: TDuckDBTableFunction; aPushdown: boolean); cdecl; external LIBDDB;

{
Register the table function object within the given connection.

The function requires at least a name, a bind function, an init function and a main function.

If the function is incomplete or a function with this name already exists DuckDBError is returned.

* con: The connection to register it in.
* function: The function pointer
* returns: Whether or not the registration was successful.
}
function duckdb_register_table_function(aCon: TDDBConnection; aFunction: TDuckDBTableCallback): TDDBState; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Table Function Bind
//===--------------------------------------------------------------------===//
{
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
}
procedure duckdb_bind_get_extra_info(aInfo: TDuckDBBindInfo); cdecl;  external LIBDDB;

{
Adds a result column to the output of the table function.

* info: The info object
* name: The name of the column
* type: The logical type of the column
}
procedure duckdb_bind_add_result_column(ainfo: TDuckDBBindInfo; const aName: PChar; aType: TDDBLogicalType); cdecl; external LIBDDB;

{
Retrieves the number of regular (non-named) parameters to the function.

* info: The info object
* returns: The number of parameters
}
function duckdb_bind_get_parameter_count(aInfo: TDuckDBBindInfo): TIDX; cdecl; external LIBDDB;

{
Retrieves the parameter at the given index.

The result must be destroyed with `duckdb_destroy_value`.

* info: The info object
* index: The index of the parameter to get
* returns: The value of the parameter. Must be destroyed with `duckdb_destroy_value`.
}
function duckdb_bind_get_parameter(aInfo: TDuckDBBindInfo; aIndex: TIDX): TDDBValue; cdecl; external LIBDDB;

{
Retrieves a named parameter with the given name.

The result must be destroyed with `duckdb_destroy_value`.

* info: The info object
* name: The name of the parameter
* returns: The value of the parameter. Must be destroyed with `duckdb_destroy_value`.
}
function duckdb_bind_get_named_parameter(aInfo: TDuckDBBindInfo; const aName: PChar): TDDBValue; cdecl; external LIBDDB;

{
Sets the user-provided bind data in the bind object. This object can be retrieved again during execution.

* info: The info object
* extra_data: The bind data object.
* destroy: The callback that will be called to destroy the bind data (if any)
}
procedure duckdb_bind_set_bind_data(aInfo: TDuckDBBindInfo; aBindData: pointer; aDestroy: TDuckDBDeleteCallback); cdecl; external LIBDDB;

{
Sets the cardinality estimate for the table function, used for optimization.

* info: The bind data object.
* is_exact: Whether or not the cardinality estimate is exact, or an approximation
}
procedure duckdb_bind_set_cardinality(aInfo: TDuckDBBindInfo; aCardinality: TIDX; aIsExact: boolean); cdecl; external LIBDDB;

{
Report that an error has occurred while calling bind.

* info: The info object
* error: The error message
}
procedure duckdb_bind_set_error(aInfo: TDuckDBBindInfo; const aError: PChar); cdecl;  external LIBDDB;

//===--------------------------------------------------------------------===//
// Table Function Init
//===--------------------------------------------------------------------===//

{
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
}
procedure duckdb_init_get_extra_info(aInfo: TDuckDBInitInfo); cdecl; external LIBDDB;

{
Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.
For tracking state, use the init data instead.

* info: The info object
* returns: The bind data object
}
procedure duckdb_init_get_bind_data(aInfo: TDuckDBInitInfo); cdecl; external LIBDDB;

{
Sets the user-provided init data in the init object. This object can be retrieved again during execution.

* info: The info object
* extra_data: The init data object.
* destroy: The callback that will be called to destroy the init data (if any)
}
procedure duckdb_init_set_init_data(aInfo: TDuckDBInitInfo; aInitData: pointer; aDestroy: TDuckDBDeleteCallback); cdecl; external LIBDDB;

{
Returns the number of projected columns.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

* info: The info object
* returns: The number of projected columns.
}
function duckdb_init_get_column_count(aInfo: TDuckDBInitInfo): TIDX; cdecl; external LIBDDB;

{
Returns the column index of the projected column at the specified position.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

* info: The info object
* column_index: The index at which to get the projected column index, from 0..duckdb_init_get_column_count(info)
* returns: The column index of the projected column.
}
function duckdb_init_get_column_index(aInfo: TDuckDBInitInfo; aColumnIndex: TIDX): TIDX; cdecl; external LIBDDB;

{
Sets how many threads can process this table function in parallel (default: 1)

* info: The info object
* max_threads: The maximum amount of threads that can process this table function
}
procedure duckdb_init_set_max_threads(aInfo: TDuckDBInitInfo; aMaxThreads: TIDX); cdecl; external LIBDDB;

{
Report that an error has occurred while calling init.

* info: The info object
* error: The error message
}
procedure duckdb_init_set_error(aInfo: TDuckDBInitInfo; const aError: PChar); cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Table Function
//===--------------------------------------------------------------------===//

{
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
}
procedure duckdb_function_get_extra_info(aInfo: TDuckDBFunctionInfo); cdecl; external LIBDDB;
{
Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.
For tracking state, use the init data instead.

* info: The info object
* returns: The bind data object
}
procedure duckdb_function_get_bind_data(aInfo: TDuckDBFunctionInfo); cdecl; external LIBDDB;

{
Gets the init data set by `duckdb_init_set_init_data` during the init.

* info: The info object
* returns: The init data object
}
procedure duckdb_function_get_init_data(aInfo: TDuckDBFunctionInfo); cdecl; external LIBDDB;

{
Gets the thread-local init data set by `duckdb_init_set_init_data` during the local_init.

* info: The info object
* returns: The init data object
}
procedure duckdb_function_get_local_init_data(aInfo: TDuckDBFunctionInfo); cdecl; external LIBDDB;

{
Report that an error has occurred while executing the function.

* info: The info object
* error: The error message
}
procedure duckdb_function_set_error(aInfo: TDuckDBFunctionInfo; const aError: PChar); cdecl;  external LIBDDB;

//===--------------------------------------------------------------------===//
// Replacement Scans
//===--------------------------------------------------------------------===//
type
  TDuckDBReplacementScanInfo = pointer;

  // Callback
  TDuckDBReplacementCallback = procedure (aInfo: TDuckDBReplacementScanInfo; const aTableName: PChar; aData: pointer);

{
Add a replacement scan definition to the specified database

* db: The database object to add the replacement scan to
* replacement: The replacement scan callback
* extra_data: Extra data that is passed back into the specified callback
* delete_callback: The delete callback to call on the extra data, if any
}
procedure duckdb_add_replacement_scan(aDB: TDDBDatabase; aReplacement: TDuckDBReplacementCallback;
                                      aExtraData: pointer; aDeleteCallback: TDuckDBDeleteCallback); cdecl; external LIBDDB;

{
Sets the replacement function name to use. If this function is called in the replacement callback,
 the replacement scan is performed. If it is not called, the replacement callback is not performed.

* info: The info object
* function_name: The function name to substitute.
}
procedure duckdb_replacement_scan_set_function_name(aInfo: TDuckDBReplacementScanInfo; const aFunctionName: PChar); cdecl; external LIBDDB;

{
Adds a parameter to the replacement scan function.

* info: The info object
* parameter: The parameter to add.
}
procedure duckdb_replacement_scan_add_parameter(aInfo: TDuckDBReplacementScanInfo; aParameter: TDDBValue); cdecl; external LIBDDB;

{
Report that an error has occurred while executing the replacement scan.

* info: The info object
* error: The error message
}
procedure duckdb_replacement_scan_set_error(aInfo: TDuckDBReplacementScanInfo; const aError: PChar); cdecl;  external LIBDDB;

//===--------------------------------------------------------------------===//
// Appender
//===--------------------------------------------------------------------===//

// Appenders are the most efficient way of loading data into DuckDB from within the C interface, and are recommended for
// fast data loading. The appender is much faster than using prepared statements or individual `INSERT INTO` statements.

// Appends are made in row-wise format. For every column, a `duckdb_append_[type]` call should be made, after which
// the row should be finished by calling `duckdb_appender_end_row`. After all rows have been appended,
// `duckdb_appender_destroy` should be used to finalize the appender and clean up the resulting memory.

// Note that `duckdb_appender_destroy` should always be called on the resulting appender, even if the function returns
// `DuckDBError`.

{
Creates an appender object.

* connection: The connection context to create the appender in.
* schema: The schema of the table to append to, or `nullptr` for the default schema.
* table: The table name to append to.
* out_appender: The resulting appender object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_appender_create(aConnection: TDDBConnection; const aSchema: PChar; const aTable: PChar;
                                var vAppender: PDDBAppender):  TDDBState; cdecl; external LIBDDB;

{
Returns the error message associated with the given appender.
If the appender has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_appender_destroy` is called.

* appender: The appender to get the error from.
* returns: The error message, or `nullptr` if there is none.
}
function duckdb_appender_error(aAppender: TDDBAppender): PChar; cdecl; external LIBDDB;

{
Flush the appender to the table, forcing the cache of the appender to be cleared and the data to be appended to the
base table.

This should generally not be used unless you know what you are doing. Instead, call `duckdb_appender_destroy` when you
are done with the appender.

* appender: The appender to flush.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_appender_flush(aAppender: TDDBAppender): TDDBState; cdecl; external LIBDDB;

{
Close the appender, flushing all intermediate state in the appender to the table and closing it for further appends.

This is generally not necessary. Call `duckdb_appender_destroy` instead.

* appender: The appender to flush and close.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_appender_close(aAppender: TDDBAppender): TDDBState; cdecl; external LIBDDB;

{
Close the appender and destroy it. Flushing all intermediate state in the appender to the table, and de-allocating
all memory associated with the appender.

* appender: The appender to flush, close and destroy.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_appender_destroy(aAppender: PDDBAppender): TDDBState; cdecl; external LIBDDB;

{
A nop function, provided for backwards compatibility reasons. Does nothing. Only `duckdb_appender_end_row` is required.
}
function duckdb_appender_begin_row(aAppender: TDDBAppender): TDDBState; cdecl; external LIBDDB;

{
Finish the current row of appends. After end_row is called, the next row can be appended.

* appender: The appender.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_appender_end_row(aAppender: TDDBAppender): TDDBState; cdecl; external LIBDDB;

{
Append a aValue: boolean to the appender.
}
function duckdb_append_bool(aAppender: TDDBAppender; aValue: boolean): TDDBState; cdecl; external LIBDDB;

{
Append an aValue: Int8 to the appender.
}
function duckdb_append_int8(aAppender: TDDBAppender; aValue: Int8): TDDBState; cdecl; external LIBDDB;
{
Append an aValue: Int16 to the appender.
}
function duckdb_append_int16(aAppender: TDDBAppender; aValue: Int16): TDDBState; cdecl; external LIBDDB;
{
Append an aValue: Int32 to the appender.
}
function duckdb_append_int32(aAppender: TDDBAppender; aValue: Int32): TDDBState; cdecl; external LIBDDB;
{
Append an aValue: Int64 to the appender.
}
function duckdb_append_int64(aAppender: TDDBAppender; aValue: Int64): TDDBState; cdecl; external LIBDDB;
{
Append a aValue: TDuckDBHhugeint to the appender.
}
function duckdb_append_hugeint(aAppender: TDDBAppender; aValue: TDDBHugeint): TDDBState; cdecl; external LIBDDB;

{
Append a UInt8 value to the appender.
}
function duckdb_append_uint8(aAppender: TDDBAppender; aValue: UInt8): TDDBState; cdecl; external LIBDDB;
{
Append a UInt16 value to the appender.
}
function duckdb_append_uint16(aAppender: TDDBAppender; aValue: UInt16): TDDBState; cdecl; external LIBDDB;
{
Append a UInt32 value to the appender.
}
function duckdb_append_uint32(aAppender: TDDBAppender; aValue: UInt32): TDDBState; cdecl; external LIBDDB;
{
Append a UInt64 value to the appender.
}
function duckdb_append_uint64(aAppender: TDDBAppender; aValue: UInt64): TDDBState; cdecl; external LIBDDB;

{
Append a float value to the appender.
}
function duckdb_append_float(aAppender: TDDBAppender; aValue: Extended): TDDBState; cdecl; external LIBDDB;
{
Append a aValue: double to the appender.
}
function duckdb_append_double(aAppender: TDDBAppender; aValue: double): TDDBState; cdecl; external LIBDDB;

{
Append a aValue: TDuckDBDate to the appender.
}
function duckdb_append_date(aAppender: TDDBAppender; aValue: TDDBDate): TDDBState; cdecl; external LIBDDB;
{
Append a duckdb_time value to the appender.
}
function duckdb_append_time(aAppender: TDDBAppender; aValue: TDDBTime):  TDDBState; cdecl; external LIBDDB;
{
Append a aValue: TDuckDBTimestamp to the appender.
}
function duckdb_append_timestamp(aAppender: TDDBAppender; aValue: TDDBTimestamp): TDDBState; cdecl; external LIBDDB;
{
Append a aValue: TDuckDBInterval to the appender.
}
function duckdb_append_interval(aAppender: TDDBAppender; aValue: TDDBInterval): TDDBState; cdecl; external LIBDDB;

{
Append a varchar value to the appender.
}
function duckdb_append_varchar(aAppender: TDDBAppender; const PCharval): TDDBState; cdecl; external LIBDDB;
{
Append a varchar value to the appender.
}
function duckdb_append_varchar_length(aAppender: TDDBAppender; const PCharval, aLength: TIDX): TDDBState; cdecl; external LIBDDB;
{
Append a blob value to the appender.
}
function duckdb_append_blob(aAppender: TDDBAppender; const aData: pointer; aLength: TIDX): TDDBState; cdecl; external LIBDDB;
{
Append a NULL value to the appender (of any type).
}
function duckdb_append_null(aAppender: TDDBAppender): TDDBState; cdecl; external LIBDDB;

{
Appends a pre-filled data chunk to the specified appender.

The types of the data chunk must exactly match the types of the table, no casting is performed.
If the types do not match or the appender is in an invalid state, DuckDBError is returned.
If the append is successful, DuckDBSuccess is returned.

* appender: The appender to append to.
* chunk: The data chunk to append.
* returns: The return state.
}
function duckdb_append_data_chunk(aAppender: TDDBAppender; aChunk: TDDBDataChunk): TDDBState; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Arrow Interface
//===--------------------------------------------------------------------===//
{
Executes a SQL query within a connection and stores the full (materialized) result in an arrow structure.
If the query fails to execute, DuckDBError is returned and the error message can be retrieved by calling
`duckdb_query_arrow_error`.

Note that after running `duckdb_query_arrow`, `duckdb_destroy_arrow` must be called on the result object even if the
query fails, otherwise the error stored within the result will not be freed correctly.

* connection: The connection to perform the query in.
* query: The SQL query to run.
* out_aResult: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_query_arrow(aConnection: TDDBConnection; const aQuery: PChar; var vResult: PDDBArrow): TDDBState; cdecl; external LIBDDB;

{
Fetch the internal arrow schema from the arrow result.

* aResult: The result to fetch the schema from.
* out_schema: The output schema.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_query_arrow_schema(aResult: TDDBArrow; var vSchema: PDDBArrowSchema): TDDBState; cdecl; external LIBDDB;

{
Fetch an internal arrow array from the arrow result.

This function can be called multiple time to get next chunks, which will free the previous out_array.
So consume the out_array before calling this function again.

* aResult: The result to fetch the array from.
* out_array: The output array.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
function duckdb_query_arrow_array(aResult: TDDBArrow; vArray: PDDBArrowArray): TDDBState; cdecl; external LIBDDB;

{
Returns the number of columns present in a the arrow result object.

* aResult: The result object.
* returns: The number of columns present in the result object.
}
function duckdb_arrow_column_count(aResult: TDDBArrow): TIDX; cdecl; external LIBDDB;

{
Returns the number of rows present in a the arrow result object.

* aResult: The result object.
* returns: The number of rows present in the result object.
}
function duckdb_arrow_row_count(aResult: TDDBArrow): TIDX; cdecl; external LIBDDB;

{
Returns the number of rows changed by the query stored in the arrow result. This is relevant only for
INSERT/UPDATE/DELETE queries. For other queries the rows_changed will be 0.

* aResult: The result object.
* returns: The number of rows changed.
}
function duckdb_arrow_rows_changed(aResult: TDDBArrow): TIDX; cdecl; external LIBDDB;

{
Returns the error message contained within the result. The error is only set if `duckdb_query_arrow` returns
`DuckDBError`.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_arrow` is called.

* aResult: The result object to fetch the nullmask from.
* returns: The error of the result.
}
function duckdb_query_arrow_error(aResult: TDDBArrow): PChar; cdecl; external LIBDDB;

{
Closes the result and de-allocates all memory allocated for the arrow result.

* aResult: The result to destroy.
}
procedure duckdb_destroy_arrow(aResult: PDDBArrow); cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Threading Information
//===--------------------------------------------------------------------===//
type
  TDuckDBTaskState = pointer;

{
Execute DuckDB tasks on this thread.

Will return after `max_tasks` have been executed, or if there are no more tasks present.

* database: The database object to execute tasks for
* max_tasks: The maximum amount of tasks to execute
}
procedure duckdb_execute_tasks(aDatabase: TDDBDatabase; aMaxTasks: TIDX); cdecl; external LIBDDB;

{
Creates a task state that can be used with duckdb_execute_tasks_state to execute tasks until
 duckdb_finish_execution is called on the state.

duckdb_destroy_state should be called on the result in order to free memory.

* database: The database object to create the task state for
* returns: The task state that can be used with duckdb_execute_tasks_state.
}
function duckdb_create_task_state(aDatabase: TDDBDatabase): TDuckDBTaskState; cdecl; external LIBDDB;

{
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks forever, until duckdb_finish_execution is called on the state.
Multiple threads can share the same TDuckDBTaskState.

* state: The task state of the executor
}
procedure duckdb_execute_tasks_state(aState: TDuckDBTaskState); cdecl; external LIBDDB;

{
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks until either duckdb_finish_execution is called on the state,
max_tasks tasks have been executed or there are no more tasks to be executed.

Multiple threads can share the same TDuckDBTaskState.

* state: The task state of the executor
* max_tasks: The maximum amount of tasks to execute
* returns: The amount of tasks that have actually been executed
}
function duckdb_execute_n_tasks_state(aState: TDuckDBTaskState; aMaxTasks: TIDX): TIDX; cdecl; external LIBDDB;

{
Finish execution on a specific task.

* state: The task state to finish execution
}
procedure duckdb_finish_execution(aState: TDuckDBTaskState); cdecl; external LIBDDB;

{
Check if the provided TDuckDBTaskState has finished execution

* state: The task state to inspect
* returns: Whether or not duckdb_finish_execution has been called on the task state
}
function TDuckDBTaskState_is_finished(aState: TDuckDBTaskState): boolean; cdecl; external LIBDDB;

{
Destroys the task state returned from duckdb_create_task_state.

Note that this should not be called while there is an active duckdb_execute_tasks_state running
on the task state.

* state: The task state to clean up
}
procedure duckdb_destroy_task_state(aState: TDuckDBTaskState); cdecl; external LIBDDB;

{
Returns true if execution of the current query is finished.

* con: The connection on which to check
}
function duckdb_execution_is_finished(aCon: TDDBConnection): boolean; cdecl; external LIBDDB;

//===--------------------------------------------------------------------===//
// Streaming Result Interface
//===--------------------------------------------------------------------===//

{ Fetches a data chunk from the (streaming) TDuckDBResult. This function should be called repeatedly until the result is
exhausted.

The result must be destroyed with `duckdb_destroy_data_chunk`.

This function can only be used on TDuckDBResults created with 'duckdb_pending_prepared_streaming'

If this function is used, none of the other result functions can be used and vice versa (i.e. this function cannot be
mixed with the legacy result functions or the materialized result functions).

It is not known beforehand how many chunks will be returned by this result.

* aResult: The result object to fetch the data chunk from.
* returns: The resulting data chunk. Returns `NULL` if the result has an error.
}
function duckdb_stream_fetch_chunk(aResult: TDDBResult): TDDBDataChunk; cdecl; external LIBDDB;

implementation

end.

