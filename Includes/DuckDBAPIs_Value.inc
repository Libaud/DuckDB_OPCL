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
// Value Interface
//===--------------------------------------------------------------------===//
{
Destroys the value and de-allocates all memory allocated for that type.

* value: The value to destroy.
}
{$ifdef STATIC_CALL}procedure duckdb_destroy_value{$else}Tduckdb_destroy_value = procedure{$endif} (var vValue: PDDBValue); {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a value from a null-terminated string

* value: The null-terminated string
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC_CALL}function duckdb_create_varchar{$else}Tduckdb_create_varchar = function{$endif} (aText: PAnsiChar): TDDBValue; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a value from a string

* value: The text
* length: The length of the text
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC_CALL}function duckdb_create_varchar_length{$else}Tduckdb_create_varchar_length = function{$endif} (aText: PAnsiChar; aLength: TIDX): TDDBValue; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a value from an int64

* value: The bigint value
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC_CALL}function duckdb_create_int64{$else}Tduckdb_create_int64 = function{$endif} (aVal: int64): TDDBValue ; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Obtains a string representation of the given value.
The result must be destroyed with `duckdb_free`.

* value: The value
* returns: The string value. This must be destroyed with `duckdb_free`.
}
{$ifdef STATIC_CALL}function duckdb_get_varchar{$else}Tduckdb_get_varchar = function{$endif} (aValue: TDDBValue): PAnsiChar; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Obtains an int64 of the given value.

* value: The value
* returns: The int64 value, or 0 if no conversion is possible
}
{$ifdef STATIC_CALL}function duckdb_get_int64{$else}Tduckdb_get_int64 = function{$endif} (aValue: TDDBValue): int64; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

