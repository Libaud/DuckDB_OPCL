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
// Logical Type Interface
//===--------------------------------------------------------------------===//

{
Creates a `TDDBLogicalType` from a standard primitive type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

This should not be used with `DUCKDB_TYPE_DECIMAL`.

* type: The primitive type to create.
* returns: The logical type.
}
{$ifdef STATIC_CALL}function duckdb_create_logical_type{$else}Tduckdb_create_logical_type = function{$endif} (aType: TDDBType): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a list type from its child type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* type: The child type of list type to create.
* returns: The logical type.
}
{$ifdef STATIC_CALL}function duckdb_create_list_type{$else}Tduckdb_create_list_type = function{$endif} (aChildType: TDDBLogicalType): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a map type from its key type and value type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* type: The key type and value type of map type to create.
* returns: The logical type.
}
{$ifdef STATIC_CALL}function duckdb_create_map_type{$else}Tduckdb_create_map_type = function{$endif} (aKeyType, aValueType: TDDBLogicalType): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a UNION type from the passed types array
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* types: The array of types that the union should consist of.
* type_amount: The size of the types array.
* returns: The logical type.
}
{$ifdef STATIC_CALL}function duckdb_create_union_type{$else}Tduckdb_create_union_type = function{$endif} (aMemberTypes: TDDBLogicalType; aMemberNames: PPAnsiChar; aMemberCount: TIDX): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a STRUCT type from the passed member name and type arrays.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* member_types: The array of types that the struct should consist of.
* member_names: The array of names that the struct should consist of.
* member_count: The number of members that were specified for both arrays.
* returns: The logical type.
}
{$ifdef STATIC_CALL}function duckdb_create_struct_type{$else}Tduckdb_create_struct_type = function{$endif} (aMemberTypes: PDDBLogicalType; aMemberNames: PPAnsiChar; aMemberCount: TIDX): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a `TDDBLogicalType` of type decimal with the specified width and scale
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* width: The width of the decimal type
* scale: The scale of the decimal type
* returns: The logical type.
}
{$ifdef STATIC_CALL}function duckdb_create_decimal_type{$else}Tduckdb_create_decimal_type = function{$endif} (aWidth, aScale: uint8): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the type class of a `TDDBLogicalType`.

* type: The logical type object
* returns: The type id
}
{$ifdef STATIC_CALL}function duckdb_get_type_id{$else}Tduckdb_get_type_id = function{$endif} (aType: TDDBLogicalType): TDDBType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the width of a decimal type.

* type: The logical type object
* returns: The width of the decimal type
}
{$ifdef STATIC_CALL}function duckdb_decimal_width{$else}Tduckdb_decimal_width = function{$endif} (aType: TDDBLogicalType): uint8; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the scale of a decimal type.

* type: The logical type object
* returns: The scale of the decimal type
}
{$ifdef STATIC_CALL}function duckdb_decimal_scale{$else}Tduckdb_decimal_scale = function{$endif} (aType: TDDBLogicalType): uint8; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the internal storage type of a decimal type.

* type: The logical type object
* returns: The internal type of the decimal type
}
{$ifdef STATIC_CALL}function duckdb_decimal_internal_type{$else}Tduckdb_decimal_internal_type = function{$endif} (aType: TDDBLogicalType): TDDBType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the internal storage type of an enum type.

* type: The logical type object
* returns: The internal type of the enum type
}
{$ifdef STATIC_CALL}function duckdb_enum_internal_type{$else}Tduckdb_enum_internal_type = function{$endif} (aType: TDDBLogicalType): TDDBType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the dictionary size of the enum type

* type: The logical type object
* returns: The dictionary size of the enum type
}
{$ifdef STATIC_CALL}function duckdb_enum_dictionary_size{$else}Tduckdb_enum_dictionary_size = function{$endif} (aType: TDDBLogicalType): uint32; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the dictionary value at the specified position from the enum.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The index in the dictionary
* returns: The string value of the enum type. Must be freed with `duckdb_free`.
}
{$ifdef STATIC_CALL}function duckdb_enum_dictionary_value{$else}Tduckdb_enum_dictionary_value = function{$endif} (aType: TDDBLogicalType; aIndex: TIDX): PAnsiChar; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the child type of the given list type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The child type of the list type. Must be destroyed with `duckdb_destroy_logical_type`.
}
{$ifdef STATIC_CALL}function duckdb_list_type_child_type{$else}Tduckdb_list_type_child_type = function{$endif} (aType: TDDBLogicalType): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the key type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The key type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.
}
{$ifdef STATIC_CALL}function duckdb_map_type_key_type{$else}Tduckdb_map_type_key_type = function{$endif} (aType: TDDBLogicalType): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the value type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The value type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.
}
{$ifdef STATIC_CALL}function duckdb_map_type_value_type{$else}Tduckdb_map_type_value_type = function{$endif} (aType: TDDBLogicalType): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Returns the number of children of a struct type.

* type: The logical type object
* returns: The number of children of a struct type.
}
{$ifdef STATIC_CALL}function duckdb_struct_type_child_count{$else}Tduckdb_struct_type_child_count = function{$endif} (aType: TDDBLogicalType): TIDX; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the name of the struct child.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The child index
* returns: The name of the struct type. Must be freed with `duckdb_free`.
}
{$ifdef STATIC_CALL}function duckdb_struct_type_child_name{$else}Tduckdb_struct_type_child_name = function{$endif} (aType: TDDBLogicalType; aIndex: TIDX): PAnsiChar; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the child type of the given struct type at the specified index.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* index: The child index
* returns: The child type of the struct type. Must be destroyed with `duckdb_destroy_logical_type`.
}
{$ifdef STATIC_CALL}function duckdb_struct_type_child_type{$else}Tduckdb_struct_type_child_type = function{$endif} (aType: TDDBLogicalType; aIndex: TIDX): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Returns the number of members that the union type has.

* type: The logical type (union) object
* returns: The number of members of a union type.
}
{$ifdef STATIC_CALL}function duckdb_union_type_member_count{$else}Tduckdb_union_type_member_count = function{$endif} (aType: TDDBLogicalType): TIDX; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the name of the union member.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The child index
* returns: The name of the union member. Must be freed with `duckdb_free`.
}
{$ifdef STATIC_CALL}function duckdb_union_type_member_name{$else}Tduckdb_union_type_member_name = function{$endif} (aType: TDDBLogicalType; aIndex: TIDX): PAnsiChar; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Retrieves the child type of the given union member at the specified index.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* index: The child index
* returns: The child type of the union member. Must be destroyed with `duckdb_destroy_logical_type`.
}
{$ifdef STATIC_CALL}function duckdb_union_type_member_type{$else}Tduckdb_union_type_member_type = function{$endif} (aType: TDDBLogicalType; aIndex: TIDX): TDDBLogicalType; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Destroys the logical type and de-allocates all memory allocated for that type.

* type: The logical type to destroy.
}
{$ifdef STATIC_CALL}procedure duckdb_destroy_logical_type{$else}Tduckdb_destroy_logical_type = procedure{$endif} (var vType: TDDBLogicalType); {$ifdef STATIC_CALL}external LIBDDB;{$endif}

