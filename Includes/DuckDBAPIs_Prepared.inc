{========================================================================================
  Include :
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

{$ifdef DYNAMIC}type{$endif}

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
{$ifdef STATIC}function duckdb_prepare {$else} Tduckdb_prepare = function {$endif} (aConnection: TDDBConnection;
                                                         const aQuery: PAnsiChar;
                                                         aPreparedStatement: PDDBPreparedStatement): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Closes the prepared statement and de-allocates all memory allocated for the statement.

* prepared_statement: The prepared statement to destroy.
}
{$ifdef STATIC}procedure duckdb_destroy_prepare {$else} Tduckdb_destroy_prepare = procedure{$endif} (var vPreparedStatement: TDDBPreparedStatement); {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the error message associated with the given prepared statement.
If the prepared statement has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_prepare` is called.

* prepared_statement: The prepared statement to obtain the error from.
* returns: The error message, or `nullptr` if there is none.
}
{$ifdef STATIC}function duckdb_prepare_error {$else} Tduckdb_prepare_error = function {$endif} (aPreparedStatement: TDDBPreparedStatement): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the number of parameters that can be provided to the given prepared statement.

Returns 0 if the query was not successfully prepared.

* prepared_statement: The prepared statement to obtain the number of parameters for.
}
{$ifdef STATIC}function duckdb_nparams{$else} Tduckdb_nparams = function {$endif} (aPreparedStatement: TDDBPreparedStatement): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the name used to identify the parameter
The returned string should be freed using `duckdb_free`.

Returns NULL if the index is out of range for the provided prepared statement.

* prepared_statement: The prepared statement for which to get the parameter name from.
}
{$ifdef STATIC}function duckdb_parameter_name {$else} Tduckdb_parameter_name = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aIndex: TIDX): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the parameter type for the parameter at the given index.

Returns `DUCKDB_TYPE_INVALID` if the parameter index is out of range or the statement was not successfully prepared.

* prepared_statement: The prepared statement.
* param_idx: The parameter index.
* returns: The parameter type
}
{$ifdef STATIC}function duckdb_param_type {$else} Tduckdb_param_type = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX): TDDBType; {$ifdef STATIC}external LIBDDB;{$endif}

{
Clear the params bind to the prepared statement.
}
{$ifdef STATIC}function duckdb_clear_bindings {$else} Tduckdb_clear_bindings = function {$endif} (aPreparedStatement: TDDBPreparedStatement): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_value {$else} Tduckdb_bind_value = function {$endif} (aPreparedStatement: TDDBPreparedStatement;
                                                            aParamIdx: TIDX;
                                                            aVal: TDDBValue): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Retrieve the index of the parameter for the prepared statement, identified by name
}
{$ifdef STATIC}function duckdb_bind_parameter_index {$else} Tduckdb_bind_parameter_index = function {$endif} (aPreparedStatement: TDDBPreparedStatement;
                                                                      var vParamIdx: TIDX;
                                                                      aName: PAnsiChar): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a bool value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_boolean {$else} Tduckdb_bind_boolean = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: Boolean): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an int8_t value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_int8 {$else} Tduckdb_bind_int8 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: Int8): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an int16_t value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_int16 {$else} Tduckdb_bind_int16 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: Int16): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an int32_t value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_int32 {$else} Tduckdb_bind_int32 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: Int32): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an int64_t value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_int64 {$else} Tduckdb_bind_int64 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: Int64): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an TDDBHugeint value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_hugeint {$else} Tduckdb_bind_hugeint = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: TDDBHugeint): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a TDDBDecimal value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_decimal {$else} Tduckdb_bind_decimal = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: TDDBDecimal): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an uint8 value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_uint8 {$else} Tduckdb_bind_uint8 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx:  TIDX; aVal: UInt8): TDDBState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an uint16_t value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_uint16 {$else} Tduckdb_bind_uint16 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: UInt16): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an uint32 value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_uint32 {$else} Tduckdb_bind_uint32 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: UInt32): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an uint64_t value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_uint64 {$else} Tduckdb_bind_uint64 = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: UInt64): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an float value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_float {$else} Tduckdb_bind_float = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: Single): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds an double value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_double {$else} Tduckdb_bind_double = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: Double): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a TDDBDate value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_date {$else} Tduckdb_bind_date = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: TDDBDate): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a TDDBTime value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_time {$else} Tduckdb_bind_time = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: TDDBTime): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a TDDBTimestamp value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_timestamp {$else} Tduckdb_bind_timestamp = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: TDDBTimestamp): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a TDDBInterval value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_interval {$else} Tduckdb_bind_interval = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: TDDBInterval): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a null-terminated varchar value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_varchar {$else} Tduckdb_bind_varchar = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: PAnsiChar): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a varchar value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_varchar_length {$else} Tduckdb_bind_varchar_length = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aVal: PAnsiChar; length: TIDX): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a blob value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_blob {$else} Tduckdb_bind_blob = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX; aData: Pointer; aLength: TIDX): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Binds a NULL value to the prepared statement at the specified index.
}
{$ifdef STATIC}function duckdb_bind_null {$else} Tduckdb_bind_null = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aParamIdx: TIDX): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Executes the prepared statement with the given bound parameters, and returns a materialized query result.

This method can be called multiple times for each prepared statement, and the parameters can be modified
between calls to this function.

* prepared_statement: The prepared statement to execute.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_execute_prepared {$else} Tduckdb_execute_prepared = function {$endif} (aPreparedStatement: TDDBPreparedStatement; aResult: PDDBResult): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Executes the prepared statement with the given bound parameters, and returns an arrow query result.

* prepared_statement: The prepared statement to execute.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_execute_prepared_arrow {$else} Tduckdb_execute_prepared_arrow = function{$endif} (aPreparedStatement: TDDBPreparedStatement; aResult: PDDBArrow): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Scans the Arrow stream and creates a view with the given name.

* connection: The connection on which to execute the scan.
* table_name: Name of the temporary view to create.
* arrow: Arrow stream wrapper.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_arrow_scan {$else} Tduckdb_arrow_scan = function {$endif} (aConnection: TDDBConnection; aTableName: PAnsiChar; aArrow: TDDBArrowStream): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Scans the Arrow array and creates a view with the given name.

* connection: The connection on which to execute the scan.
* table_name: Name of the temporary view to create.
* arrow_schema: Arrow schema wrapper.
* arrow_array: Arrow array wrapper.
* out_stream: Output array stream that wraps around the passed schema, for releasing/deleting once done.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_arrow_array_scan {$else} Tduckdb_arrow_array_scan = function {$endif} (aConnection: TDDBConnection; aTableName: PAnsiChar;
                                                                  aArrowSchema: TDDBArrowSchema; aArrowArray: TDDBArrowArray;
                                                                  aStream: PDDBArrowStream): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}


