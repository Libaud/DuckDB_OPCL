{========================================================================================
  Include :
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

{$ifdef DYNAMIC_CALL}type{$endif}

//===--------------------------------------------------------------------===//
// Streaming Result Interface
//===--------------------------------------------------------------------===//

{
Fetches a data chunk from the (streaming) TDDBResult. This function should be called repeatedly until the result is
exhausted.

The result must be destroyed with `duckdb_destroy_data_chunk`.

This function can only be used on duckdb_results created with 'duckdb_pending_prepared_streaming'

If this function is used, none of the other result functions can be used and vice versa (i.e. this function cannot be
mixed with the legacy result functions or the materialized result functions).

It is not known beforehand how many chunks will be returned by this result.

* result: The result object to fetch the data chunk from.
* returns: The resulting data chunk. Returns `NULL` if the result has an error.
}
{$ifdef STATIC_CALL}function duckdb_stream_fetch_chunk{$else}Tduckdb_stream_fetch_chunk = function{$endif} (aResult: TDDBResult): TDDBDataChunk; cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}


