
//===--------------------------------------------------------------------===//
// Value Interface
//===--------------------------------------------------------------------===//
{
Destroys the value and de-allocates all memory allocated for that type.

* value: The value to destroy.
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_destroy_value(var vValue: PDDBValue); {$ifdef STATIC}external LIBDDB;{$endif}

{
Creates a value from a null-terminated string

* value: The null-terminated string
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_create_varchar(aText: PAnsiChar): TDDBValue; {$ifdef STATIC}external LIBDDB;{$endif}

{
Creates a value from a string

* value: The text
* length: The length of the text
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_create_varchar_length(aText: PAnsiChar; aLength: TIDX): TDDBValue; {$ifdef STATIC}external LIBDDB;{$endif}

{
Creates a value from an int64

* value: The bigint value
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_create_int64(aVal: int64): TDDBValue ; {$ifdef STATIC}external LIBDDB;{$endif}

{
Obtains a string representation of the given value.
The result must be destroyed with `duckdb_free`.

* value: The value
* returns: The string value. This must be destroyed with `duckdb_free`.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_get_varchar(aValue: TDDBValue): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}

{
Obtains an int64 of the given value.

* value: The value
* returns: The int64 value, or 0 if no conversion is possible
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_get_int64(aValue: TDDBValue): int64; {$ifdef STATIC}external LIBDDB;{$endif}

