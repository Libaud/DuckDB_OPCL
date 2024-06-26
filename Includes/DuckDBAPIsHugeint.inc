﻿{========================================================================================
  Include :
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
  2024-06-27 Upgrading for DuckDB 1.0 support
========================================================================================}

{$ifdef DYNAMIC_CALL}type{$endif}

//===--------------------------------------------------------------------===//
// Hugeint Helpers
//===--------------------------------------------------------------------===//
{
Converts a TDDBHugeint object (as obtained from a `DUCKDB_TYPE_HUGEINT` column) into a double.

* val: The hugeint value.
* returns: The converted `double` element.
}
{$ifdef STATIC_CALL}function duckdb_hugeint_to_double
             {$else}Tduckdb_hugeint_to_double = function{$endif} (aVal: TDDBHugeint): Double;
                                                {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Converts a double value to a TDDBHugeint object.

If the conversion fails because the double value is too big the result will be 0.

* val: The double value.
* returns: The converted `TDDBHugeint` element.
}
{$ifdef STATIC_CALL}function duckdb_double_to_hugeint
             {$else}Tduckdb_double_to_hugeint = function{$endif} (aVal: Double): TDDBHugeint;
                                                {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Converts a double value to a TDDBDecimal object.

If the conversion fails because the double value is too big, or the width/scale are invalid the result will be 0.

* val: The double value.
* returns: The converted `TDDBDecimal` element.
}
{$ifdef STATIC_CALL}function duckdb_double_to_decimal
             {$else}Tduckdb_double_to_decimal = function{$endif} (aVal: Double; aWidth, aScale: UInt8): TDDBDecimal;
                                                {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{ end of include file }

