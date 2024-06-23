{========================================================================================
  Include :
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

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
{$ifdef STATIC}function duckdb_appender_create{$else}Tduckdb_appender_create = function{$endif} (aConnection: TDDBConnection;
                                                                 aSchema: PAnsiChar;
                                                                 aTable: PAnsiChar;
                                                                 var aAppender: TDDBAppender): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the error message associated with the given appender.
If the appender has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_appender_destroy` is called.

* appender: The appender to get the error from.
* returns: The error message, or `nullptr` if there is none.
}
{$ifdef STATIC}function duckdb_appender_error{$else}Tduckdb_appender_error = function{$endif} (aAppender: TDDBAppender): PAnsiChar; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Flush the appender to the table, forcing the cache of the appender to be cleared and the data to be appended to the
base table.

This should generally not be used unless you know what you are doing. Instead, call `duckdb_appender_destroy` when you
are done with the appender.

* appender: The appender to flush.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_appender_flush{$else}Tduckdb_appender_flush = function{$endif} (aAppender: TDDBAppender): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Close the appender, flushing all intermediate state in the appender to the table and closing it for further appends.

This is generally not necessary. Call `duckdb_appender_destroy` instead.

* appender: The appender to flush and close.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_appender_close{$else}Tduckdb_appender_close = function{$endif} (aAppender: TDDBAppender): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Close the appender and destroy it. Flushing all intermediate state in the appender to the table, and de-allocating
all memory associated with the appender.

* appender: The appender to flush, close and destroy.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_appender_destroy{$else}Tduckdb_appender_destroy = function{$endif} (var vAppender: TDDBAppender): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
A nop function, provided for backwards compatibility reasons. Does nothing. Only `duckdb_appender_end_row` is required.
}
{$ifdef STATIC}function duckdb_appender_begin_row{$else}Tduckdb_appender_begin_row = function{$endif} (aAppender: TDDBAppender): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Finish the current row of appends. After end_row is called, the next row can be appended.

* appender: The appender.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_appender_end_row{$else}Tduckdb_appender_end_row = function{$endif} (aAppender: TDDBAppender): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a bool value to the appender.
}
{$ifdef STATIC}function duckdb_append_bool{$else}Tduckdb_append_bool = function{$endif} (aAppender: TDDBAppender; aValue: Boolean): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append an int8_t value to the appender.
}
{$ifdef STATIC}function duckdb_append_int8{$else}Tduckdb_append_int8 = function{$endif} (aAppender: TDDBAppender; aValue: Int8): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append an int16_t value to the appender.
}
{$ifdef STATIC}function duckdb_append_int16{$else}Tduckdb_append_int16 = function{$endif} (aAppender: TDDBAppender; aValue: Int16): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append an int32_t value to the appender.
}
{$ifdef STATIC}function duckdb_append_int32{$else}Tduckdb_append_int32 = function{$endif} (aAppender: TDDBAppender; aValue: Int32): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append an int64_t value to the appender.
}
{$ifdef STATIC}function duckdb_append_int64{$else}Tduckdb_append_int64 = function{$endif} (aAppender: TDDBAppender; aValue: Int64): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a TDDBHugeint value to the appender.
}
{$ifdef STATIC}function duckdb_append_hugeint{$else}Tduckdb_append_hugeint = function{$endif} (aAppender: TDDBAppender; aValue: TDDBHugeint): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a uint8 value to the appender.
}
{$ifdef STATIC}function duckdb_append_uint8{$else}Tduckdb_append_uint8 = function{$endif} (aAppender: TDDBAppender; aValue: UInt8): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a uint16_t value to the appender.
}
{$ifdef STATIC}function duckdb_append_uint16{$else}Tduckdb_append_uint16 = function{$endif} (aAppender: TDDBAppender; aValue: UInt16): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a uint32 value to the appender.
}
{$ifdef STATIC}function duckdb_append_uint32{$else}Tduckdb_append_uint32 = function{$endif} (aAppender: TDDBAppender; aValue: UInt32): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a uint64_t value to the appender.
}
{$ifdef STATIC}function duckdb_append_uint64{$else}Tduckdb_append_uint64 = function{$endif} (aAppender: TDDBAppender; aValue: UInt64): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a float value to the appender.
}
{$ifdef STATIC}function duckdb_append_float{$else}Tduckdb_append_float = function{$endif} (aAppender: TDDBAppender; aValue: Single): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a double value to the appender.
}
{$ifdef STATIC}function duckdb_append_double{$else}Tduckdb_append_double = function{$endif} (aAppender: TDDBAppender; aValue: Double): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a TDDBDate value to the appender.
}
{$ifdef STATIC}function duckdb_append_date{$else}Tduckdb_append_date = function{$endif} (aAppender: TDDBAppender; aValue: TDDBDate): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a TDDBTime value to the appender.
}
{$ifdef STATIC}function duckdb_append_time{$else}Tduckdb_append_time = function{$endif} (aAppender: TDDBAppender; aValue: TDDBTime): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a TDDBTimestamp value to the appender.
}
{$ifdef STATIC}function duckdb_append_timestamp{$else}Tduckdb_append_timestamp = function{$endif} (aAppender: TDDBAppender; aValue: TDDBTimestamp): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a TDDBInterval value to the appender.
}
{$ifdef STATIC}function duckdb_append_interval{$else}Tduckdb_append_interval = function{$endif} (aAppender: TDDBAppender; aValue: TDDBInterval): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a varchar value to the appender.
}
{$ifdef STATIC}function duckdb_append_varchar{$else}Tduckdb_append_varchar = function{$endif} (aAppender: TDDBAppender; aVal: PAnsiChar): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a varchar value to the appender.
}
{$ifdef STATIC}function duckdb_append_varchar_length{$else}Tduckdb_append_varchar_length = function{$endif} (aAppender: TDDBAppender; aVal: PAnsiChar; aLength: TIDX): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a blob value to the appender.
}
{$ifdef STATIC}function duckdb_append_blob{$else}Tduckdb_append_blob = function{$endif} (aAppender: TDDBAppender; aData: Pointer; aLength: TIDX): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Append a NULL value to the appender (of any type).
}
{$ifdef STATIC}function duckdb_append_null{$else}Tduckdb_append_null = function{$endif} (aAppender: TDDBAppender): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Appends a pre-filled data chunk to the specified appender.

The types of the data chunk must exactly match the types of the table, no casting is performed.
If the types do not match or the appender is in an invalid state, DuckDBError is returned.
If the append is successful, DuckDBSuccess is returned.

* appender: The appender to append to.
* chunk: The data chunk to append.
* returns: The return state.
}
{$ifdef STATIC}function duckdb_append_data_chunk{$else}Tduckdb_append_data_chunk = function{$endif} (aAppender: TDDBAppender; aChunk: TDDBDataChunk): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}


