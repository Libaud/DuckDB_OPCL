{========================================================================================
  Include :
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
  2024-06-27 Upgrading for DuckDB 1.0 support
========================================================================================}

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
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC_CALL}function duckdb_query_arrow
             {$else}Tduckdb_query_arrow = function{$endif} (aConnection: TDDBConnection; aQuery: PAnsiChar; aResult: PDDBArrow): TDDBState; cdecl;
                                          {$ifdef STATIC_CALL}external LIBDDB{$ifdef FPC}; {$ENDIF}deprecated;{$endif}

{
Fetch the internal arrow schema from the arrow result.

* result: The result to fetch the schema from.
* out_schema: The output schema.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC_CALL}function duckdb_query_arrow_schema
             {$else}Tduckdb_query_arrow_schema = function{$endif} (aResult: TDDBArrow; aSchema: PDDBArrowSchema): TDDBState; cdecl;
                                                 {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Fetch the internal arrow schema from the prepared statement.

* result: The prepared statement to fetch the schema from.
* out_schema: The output schema.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC_CALL}function duckdb_prepared_arrow_schema
             {$else}Tduckdb_prepared_arrow_schema = function{$endif} (aPrepared: TDDBPreparedStatement; aSchema: PDDBArrowSchema): TDDBState; cdecl;
                                                    {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Fetch an internal arrow array from the arrow result.

This function can be called multiple time to get next chunks, which will free the previous out_array.
So consume the out_array before calling this function again.

* result: The result to fetch the array from.
* out_array: The output array.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC_CALL}function duckdb_query_arrow_array
             {$else}Tduckdb_query_arrow_array = function{$endif} (aResult: TDDBArrow; aArray: PDDBArrowArray): TDDBState; cdecl;
                                                {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Returns the number of columns present in a the arrow result object.

* result: The result object.
* returns: The number of columns present in the result object.
}
{$ifdef STATIC_CALL}function duckdb_arrow_column_count
             {$else}Tduckdb_arrow_column_count = function{$endif} (aResult: TDDBArrow): TIDX;
                                                 {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Returns the number of rows present in a the arrow result object.

* result: The result object.
* returns: The number of rows present in the result object.
}
{$ifdef STATIC_CALL}function duckdb_arrow_row_count
             {$else}Tduckdb_arrow_row_count = function{$endif} (aResult: TDDBArrow): TIDX;
                                              {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Returns the number of rows changed by the query stored in the arrow result. This is relevant only for
INSERT/UPDATE/DELETE queries. For other queries the rows_changed will be 0.

* result: The result object.
* returns: The number of rows changed.
}
{$ifdef STATIC_CALL}function duckdb_arrow_rows_changed
             {$else}Tduckdb_arrow_rows_changed = function{$endif} (aResult: TDDBArrow): TIDX;
                                                 {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Returns the error message contained within the result. The error is only set if `duckdb_query_arrow` returns
`DuckDBError`.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_arrow` is called.

* result: The result object to fetch the nullmask from.
* returns: The error of the result.
}
{$ifdef STATIC_CALL}function duckdb_query_arrow_error
             {$else}Tduckdb_query_arrow_error = function{$endif} (aResult: TDDBArrow): PAnsiChar;
                                                {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Closes the result and de-allocates all memory allocated for the arrow result.

* result: The result to destroy.
}
{$ifdef STATIC_CALL}procedure duckdb_destroy_arrow
             {$else}Tduckdb_destroy_arrow = procedure{$endif} (aResult: PDDBArrow);
                                            {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{ end of include file }

