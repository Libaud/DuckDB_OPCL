
//===--------------------------------------------------------------------===//
// Result Functions
//===--------------------------------------------------------------------===//

{
Fetches a data chunk from the TDDBResult. This function should be called repeatedly until the result is exhausted.

The result must be destroyed with `duckdb_destroy_data_chunk`.

This function supersedes all `TDDBValue` functions, as well as the `duckdb_column_data` and `duckdb_nullmask_data`
functions. It results in significantly better performance, and should be preferred in newer code-bases.

If this function is used, none of the other result functions can be used and vice versa (i.e. this function cannot be
mixed with the legacy result functions).

Use `duckdb_result_chunk_count` to figure out how many chunks there are in the result.

* result: The result object to fetch the data chunk from.
* chunk_index: The chunk index to fetch from.
* returns: The resulting data chunk. Returns `NULL` if the chunk index is out of bounds.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_result_get_chunk(aResult: TDDBResult; aChunkIndex: TIDX): TDDBDataChunk; {$ifdef STATIC}external LIBDDB;{$endif}

{
Checks if the type of the internal result is StreamQueryResult.

* result: The result object to check.
* returns: Whether or not the result object is of the type StreamQueryResult
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_result_is_streaming(aResult: TDDBResult): Boolean; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the number of data chunks present in the result.

* result: The result object
* returns: Number of data chunks present in the result.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_result_chunk_count(aResult: TDDBResult): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

// Safe fetch functions
// These functions will perform conversions if necessary.
// On failure (e.g. if conversion cannot be performed or if the value is NULL) a default value is returned.
// Note that these functions are slow since they perform bounds checking and conversion
// For fast access of values prefer using `duckdb_result_get_chunk`

{
 * returns: The boolean value at the specified location, or false if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_boolean(aResult: TDDBResult; aCol, aRow: TIDX): Boolean; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The int8_t value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_int8(aResult: TDDBResult; aCol, aRow: TIDX): Int8; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The int16_t value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_int16(aResult: TDDBResult; aCol, aRow: TIDX): Int16; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The int32_t value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_int32(aResult: TDDBResult; aCol, aRow: TIDX): Int32; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The int64_t value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_int64(aResult: TDDBResult; aCol, aRow: TIDX): Int64; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The TDDBHugeint value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_hugeint(aResult: TDDBResult; aCol, aRow: TIDX): TDDBHugeint; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The TDDBDecimal value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_decimal(result: TDDBResult; col, row: TIDX): TDDBDecimal; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The uint8 value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_uint8(aResult: TDDBResult; aCol, aRow: TIDX): UInt8; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The uint16_t value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_uint16(aResult: TDDBResult; aCol, aRow: TIDX): UInt16; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The uint32 value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_uint32(aResult: TDDBResult; aCol, aRow: TIDX): UInt32; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The uint64_t value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_uint64(aResult: TDDBResult; aCol, aRow: TIDX): UInt64; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The float value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_float(aResult: TDDBResult; aCol, aRow: TIDX): Single; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The double value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_double(aResult: TDDBResult; aCol, aRow: TIDX): Double; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The TDDBDate value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_date(aResult: TDDBResult; aCol, aRow: TIDX): TDDBDate; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The TDDBTime value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_time(aResult: TDDBResult; aCol, aRow: TIDX): TDDBTime; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The TDDBTimestamp value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_timestamp(aResult: TDDBResult; aCol, aRow: TIDX): TDDBTimestamp; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: The TDDBInterval value at the specified location, or 0 if the value cannot be converted.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_interval(aResult: TDDBResult; aCol, aRow: TIDX): TDDBInterval; {$ifdef STATIC}external LIBDDB;{$endif}

{
* DEPRECATED: use duckdb_value_string instead. This function does not work correctly if the string contains null bytes.
* returns: The text value at the specified location as a null-terminated string, or nullptr if the value cannot be
converted. The result must be freed with `duckdb_free`.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_varchar(aResult: TDDBResult; aCol, aRow: TIDX): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}

{s
* returns: The string value at the specified location.
The result must be freed with `duckdb_free`.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_string(aResult: TDDBResult; aCol, aRow: TIDX): TDDBString; {$ifdef STATIC}external LIBDDB;{$endif}

{
* DEPRECATED: use duckdb_value_string_internal instead. This function does not work correctly if the string contains
null bytes.
* returns: The char* value at the specified location. ONLY works on VARCHAR columns and does not auto-cast.
If the column is NOT a VARCHAR column this function will return NULL.

The result must NOT be freed.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_varchar_internal(aResult: TDDBResult; aCol, aRow: TIDX): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}

{
* DEPRECATED: use duckdb_value_string_internal instead. This function does not work correctly if the string contains
null bytes.
* returns: The char* value at the specified location. ONLY works on VARCHAR columns and does not auto-cast.
If the column is NOT a VARCHAR column this function will return NULL.

The result must NOT be freed.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_string_internal(aResult: TDDBResult; aCol, aRow: TIDX): TDDBString; {$ifdef STATIC}external LIBDDB;{$endif}

{
* returns: The TDDBBlob value at the specified location. Returns a blob with blob.data set to nullptr if the
value cannot be converted. The resulting "blob.data" must be freed with `duckdb_free.`
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_blob(aResult: TDDBResult; aCol, aRow: TIDX): TDDBBlob; {$ifdef STATIC}external LIBDDB;{$endif}

{
 * returns: Returns true if the value at the specified index is NULL, and false otherwise.
 }
{$ifdef STATIC}function{$else}var{$endif} duckdb_value_is_null(aResult: TDDBResult; aCol, aRow: TIDX): Boolean; {$ifdef STATIC}external LIBDDB;{$endif}

