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
// Pending Result Interface
//===--------------------------------------------------------------------===//
{
Executes the prepared statement with the given bound parameters, and returns a pending result.
The pending result represents an intermediate structure for a query that is not yet fully executed.
The pending result can be used to incrementally execute a query, returning control to the client between tasks.

Note that after calling `duckdb_pending_prepared`, the pending result should always be destroyed using
`duckdb_destroy_pending`, even if this function returns DuckDBError.

* prepared_statement: The prepared statement to execute.
* out_result: The pending query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_pending_prepared {$else} Tduckdb_pending_prepared = function {$endif} (aPreparedStatement: TDDBPreparedStatement;
                                                                  vResult: PDDBPendingResult): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Executes the prepared statement with the given bound parameters, and returns a pending result.
This pending result will create a streaming TDDBResult when executed.
The pending result represents an intermediate structure for a query that is not yet fully executed.

Note that after calling `duckdb_pending_prepared_streaming`, the pending result should always be destroyed using
`duckdb_destroy_pending`, even if this function returns DuckDBError.

* prepared_statement: The prepared statement to execute.
* out_result: The pending query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_pending_prepared_streaming {$else} Tduckdb_pending_prepared_streaming = function {$endif} (aPreparedStatement: TDDBPreparedStatement;
                                                                            aResult: PDDBPendingResult): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Closes the pending result and de-allocates all memory allocated for the result.

* pending_result: The pending result to destroy.
}
{$ifdef STATIC}procedure duckdb_destroy_pending {$else} Tduckdb_destroy_pending = procedure {$endif} (var vPendingResult: PDDBPendingResult); {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the error message contained within the pending result.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_pending` is called.

* result: The pending result to fetch the error from.
* returns: The error of the pending result.
}
{$ifdef STATIC}function duckdb_pending_error {$else} Tduckdb_pending_error = function {$endif} (aPendingResult: TDDBPendingResult): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}

{
Executes a single task within the query, returning whether or not the query is ready.

If this returns DUCKDB_PENDING_RESULT_READY, the duckdb_execute_pending function can be called to obtain the result.
If this returns DUCKDB_PENDING_RESULT_NOT_READY, the duckdb_pending_execute_task function should be called again.
If this returns DUCKDB_PENDING_ERROR, an error occurred during execution.

The error message can be obtained by calling duckdb_pending_error on the pending_result.

* pending_result: The pending result to execute a task within..
* returns: The state of the pending result after the execution.
}
{$ifdef STATIC}function duckdb_pending_execute_task {$else} Tduckdb_pending_execute_task = function {$endif} (aPendingResult: TDDBPendingResult): TDDBPendingState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Fully execute a pending query result, returning the final query result.

If duckdb_pending_execute_task has been called until DUCKDB_PENDING_RESULT_READY was returned, this will return fast.
Otherwise, all remaining tasks must be executed first.

* pending_result: The pending result to execute.
* out_result: The result object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_execute_pending {$else} Tduckdb_execute_pending = function {$endif} (aPendingResult: TDDBPendingResult; aResult: PDDBResult): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns whether a TDDBPendingState is finished executing. For example if `pending_state` is
DUCKDB_PENDING_RESULT_READY, this function will return true.

* pending_state: The pending state on which to decide whether to finish execution.
* returns: Boolean indicating pending execution should be considered finished.
}
{$ifdef STATIC}function duckdb_pending_execution_is_finished {$else} Tduckdb_pending_execution_is_finished = function {$endif} (aPendingState: TDDBPendingState): Boolean; {$ifdef STATIC}external LIBDDB;{$endif}


