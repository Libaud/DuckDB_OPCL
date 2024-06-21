
//===--------------------------------------------------------------------===//
// Helpers
//===--------------------------------------------------------------------===//
{
Allocate `size` bytes of memory using the duckdb internal malloc function. Any memory allocated in this manner
should be freed using `duckdb_free`.

* size: The number of bytes to allocate.
* returns: A pointer to the allocated memory region.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_malloc(aSize: size_t): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Free a value returned from `duckdb_malloc`, `duckdb_value_varchar` or `duckdb_value_blob`.

* ptr: The memory region to de-allocate.
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_free(aPtr: Pointer); {$ifdef STATIC}external LIBDDB;{$endif}

{
The internal vector size used by DuckDB.
This is the amount of tuples that will fit into a data chunk created by `duckdb_create_data_chunk`.

* returns: The vector size.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_vector_size(): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Whether or not the TDDBString value is inlined.
This means that the data of the string does not have a separate allocation.

}
{$ifdef STATIC}function{$else}var{$endif} duckdb_string_is_inlined(aString: TDDBString): Boolean; {$ifdef STATIC}external LIBDDB;{$endif}


