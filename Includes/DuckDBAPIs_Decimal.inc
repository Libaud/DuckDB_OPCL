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
// Decimal Helpers
//===--------------------------------------------------------------------===//
{
Converts a TDDBDecimal object (as obtained from a `DUCKDB_TYPE_DECIMAL` column) into a double.

* val: The decimal value.
* returns: The converted `double` element.
}
{$ifdef STATIC_CALL}function duckdb_decimal_to_double{$else}Tduckdb_decimal_to_double = function{$endif} (aVal: TDDBDecimal): Double; {$ifdef STATIC_CALL}external LIBDDB;{$endif}


