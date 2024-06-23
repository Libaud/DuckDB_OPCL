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
// Data Chunk Interface
//===--------------------------------------------------------------------===//
{
Creates an empty DataChunk with the specified set of types.

* types: An array of types of the data chunk.
* column_count: The number of columns.
* returns: The data chunk.
}
{$ifdef STATIC}function duckdb_create_data_chunk{$else}Tduckdb_create_data_chunk = function{$endif} (aTypes: PDDBLogicalType; aColumnCount: TIDX): TDDBDataChunk; {$ifdef STATIC}external LIBDDB;{$endif}

{
Destroys the data chunk and de-allocates all memory allocated for that chunk.

* chunk: The data chunk to destroy.
}
{$ifdef STATIC}procedure duckdb_destroy_data_chunk{$else}Tduckdb_destroy_data_chunk = procedure{$endif} (var vChunk: TDDBDataChunk); {$ifdef STATIC}external LIBDDB;{$endif}

{
Resets a data chunk, clearing the validity masks and setting the cardinality of the data chunk to 0.

* chunk: The data chunk to reset.
}
{$ifdef STATIC}procedure duckdb_data_chunk_reset{$else}Tduckdb_data_chunk_reset = procedure{$endif} (aChunk: TDDBDataChunk); {$ifdef STATIC}external LIBDDB;{$endif}

{
Retrieves the number of columns in a data chunk.

* chunk: The data chunk to get the data from
* returns: The number of columns in the data chunk
}
{$ifdef STATIC}function duckdb_data_chunk_get_column_count{$else}Tduckdb_data_chunk_get_column_count = function{$endif} (aChunk: TDDBDataChunk): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Retrieves the vector at the specified column index in the data chunk.

The pointer to the vector is valid for as long as the chunk is alive.
It does NOT need to be destroyed.

* chunk: The data chunk to get the data from
* returns: The vector
}
{$ifdef STATIC}function duckdb_data_chunk_get_vector{$else}Tduckdb_data_chunk_get_vector = function{$endif} (aChunk: TDDBDataChunk; aColIdx: TIDX): TDDBVector; {$ifdef STATIC}external LIBDDB;{$endif}

{
Retrieves the current number of tuples in a data chunk.

* chunk: The data chunk to get the data from
* returns: The number of tuples in the data chunk
}
{$ifdef STATIC}function duckdb_data_chunk_get_size{$else}Tduckdb_data_chunk_get_size = function{$endif} (aChunk: TDDBDataChunk): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the current number of tuples in a data chunk.

* chunk: The data chunk to set the size in
* size: The number of tuples in the data chunk
}
{$ifdef STATIC}procedure duckdb_data_chunk_set_size{$else}Tduckdb_data_chunk_set_size = procedure{$endif} (aChunk: TDDBDataChunk; aSize: TIDX); {$ifdef STATIC}external LIBDDB;{$endif}


