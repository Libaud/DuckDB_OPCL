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
// Vector Interface
//===--------------------------------------------------------------------===//
{
Retrieves the column type of the specified vector.

The result must be destroyed with `duckdb_destroy_logical_type`.

* vector: The vector get the data from
* returns: The type of the vector
}
{$ifdef STATIC_CALL}function duckdb_vector_get_column_type{$else}Tduckdb_vector_get_column_type = function{$endif} (aVector: TDDBVector): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the data pointer of the vector.

The data pointer can be used to read or write values from the vector.
How to read or write values depends on the type of the vector.

* vector: The vector to get the data from
* returns: The data pointer
}
{$ifdef STATIC_CALL}function duckdb_vector_get_data{$else}Tduckdb_vector_get_data = function{$endif} (aVector: TDDBVector): Pointer; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the validity mask pointer of the specified vector.

If all values are valid, this function MIGHT return NULL!

The validity mask is a bitset that signifies null-ness within the data chunk.
It is a series of uint64_t values, where each uint64_t value contains validity for 64 tuples.
The bit is set to 1 if the value is valid (i.e. not NULL) or 0 if the value is invalid (i.e. NULL).

Validity of a specific value can be obtained like this:

TIDX entry_idx = row_idx / 64;
TIDX idx_in_entry = row_idx % 64;
bool is_valid = validity_mask[entry_idx] & (1 << idx_in_entry);

Alternatively, the (slower) duckdb_validity_row_is_valid function can be used.

* vector: The vector to get the data from
* returns: The pointer to the validity mask, or NULL if no validity mask is present
}
{$ifdef STATIC_CALL}function duckdb_vector_get_validity{$else}Tduckdb_vector_get_validity = function{$endif} (aVector: TDDBVector): PUInt64; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Ensures the validity mask is writable by allocating it.

After this function is called, `duckdb_vector_get_validity` will ALWAYS return non-NULL.
This allows null values to be written to the vector, regardless of whether a validity mask was present before.

* vector: The vector to alter
}
{$ifdef STATIC_CALL}procedure duckdb_vector_ensure_validity_writable{$else}Tduckdb_vector_ensure_validity_writable = procedure{$endif} (aVector: TDDBVector); {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Assigns a string element in the vector at the specified location.

* vector: The vector to alter
* index: The row position in the vector to assign the string to
* str: The null-terminated string
}
{$ifdef STATIC_CALL}procedure duckdb_vector_assign_string_element{$else}Tduckdb_vector_assign_string_element = procedure {$endif} (aVector: TDDBVector; aIndex: TIDX; aStr: PAnsiChar); {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Assigns a string element in the vector at the specified location.

* vector: The vector to alter
* index: The row position in the vector to assign the string to
* str: The string
* str_len: The length of the string (in bytes)
}
{$ifdef STATIC_CALL}procedure duckdb_vector_assign_string_element_len{$else}Tduckdb_vector_assign_string_element_len = procedure{$endif} (aVector: TDDBVector; aStr: String; aStrLen: TIDX); {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the child vector of a list vector.

The resulting vector is valid as long as the parent vector is valid.

* vector: The vector
* returns: The child vector
}
{$ifdef STATIC_CALL}function duckdb_list_vector_get_child{$else}Tduckdb_list_vector_get_child = function{$endif} (aVector: TDDBVector): TDDBVector; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Returns the size of the child vector of the list

* vector: The vector
* returns: The size of the child list
}
{$ifdef STATIC_CALL}function duckdb_list_vector_get_size{$else}Tduckdb_list_vector_get_size = function{$endif} (aVector: TDDBVector): TIDX; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Sets the total size of the underlying child-vector of a list vector.

* vector: The list vector.
* size: The size of the child list.
* returns: The duckdb state. Returns DuckDBError if the vector is nullptr.
}
{$ifdef STATIC_CALL}function duckdb_list_vector_set_size{$else}Tduckdb_list_vector_set_size = function{$endif} (aVector: TDDBVector; aSize: TIDX): TDDBState; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Sets the total capacity of the underlying child-vector of a list.

* vector: The list vector.
* required_capacity: the total capacity to reserve.
* return: The duckdb state. Returns DuckDBError if the vector is nullptr.
}
{$ifdef STATIC_CALL}function duckdb_list_vector_reserve{$else}Tduckdb_list_vector_reserve= function{$endif} (aVector: TDDBVector; aRequiredCapacity: TIDX): TDDBState; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the child vector of a struct vector.

The resulting vector is valid as long as the parent vector is valid.

* vector: The vector
* index: The child index
* returns: The child vector
}
{$ifdef STATIC_CALL}function duckdb_struct_vector_get_child{$else}Tduckdb_struct_vector_get_child = function{$endif} (aVector: TDDBVector; aIndex: TIDX): TDDBVector; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

