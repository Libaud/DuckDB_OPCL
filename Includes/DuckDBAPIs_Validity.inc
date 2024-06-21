
//===--------------------------------------------------------------------===//
// Validity Mask Functions
//===--------------------------------------------------------------------===//
{
Returns whether or not a row is valid (i.e. not NULL) in the given validity mask.

* validity: The validity mask, as obtained through `duckdb_data_chunk_get_validity`
* row: The row index
* returns: true if the row is valid, false otherwise
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_validity_row_is_valid(aValidity: PUInt64; aRow: TIDX): Boolean; {$ifdef STATIC}external LIBDDB;{$endif}

{
In a validity mask, sets a specific row to either valid or invalid.

Note that `duckdb_data_chunk_ensure_validity_writable` should be called before calling `duckdb_data_chunk_get_validity`,
to ensure that there is a validity mask to write to.

* validity: The validity mask, as obtained through `duckdb_data_chunk_get_validity`.
* row: The row index
* valid: Whether or not to set the row to valid, or invalid
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_validity_set_row_validity(aValidity: PUInt64; aRow: TIDX; aValid: Boolean); {$ifdef STATIC}external LIBDDB;{$endif}

{
In a validity mask, sets a specific row to invalid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to false.

* validity: The validity mask
* row: The row index
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_validity_set_row_invalid(aValidity: PUInt64; aRow: TIDX); {$ifdef STATIC}external LIBDDB;{$endif}

{
In a validity mask, sets a specific row to valid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to true.

* validity: The validity mask
* row: The row index
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_validity_set_row_valid(aValidity: PUInt64; aRow: TIDX); {$ifdef STATIC}external LIBDDB;{$endif}


