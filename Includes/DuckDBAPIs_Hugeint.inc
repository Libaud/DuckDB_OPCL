
//===--------------------------------------------------------------------===//
// Hugeint Helpers
//===--------------------------------------------------------------------===//
{
Converts a TDDBHugeint object (as obtained from a `DUCKDB_TYPE_HUGEINT` column) into a double.

* val: The hugeint value.
* returns: The converted `double` element.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_hugeint_to_double(aVal: TDDBHugeint): Double; {$ifdef STATIC}external LIBDDB;{$endif}

{
Converts a double value to a TDDBHugeint object.

If the conversion fails because the double value is too big the result will be 0.

* val: The double value.
* returns: The converted `TDDBHugeint` element.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_double_to_hugeint(aVal: Double): TDDBHugeint; {$ifdef STATIC}external LIBDDB;{$endif}

{
Converts a double value to a TDDBDecimal object.

If the conversion fails because the double value is too big, or the width/scale are invalid the result will be 0.

* val: The double value.
* returns: The converted `TDDBDecimal` element.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_double_to_decimal(aVal: Double; aWidth, aScale: UInt8): TDDBDecimal; {$ifdef STATIC}external LIBDDB;{$endif}


