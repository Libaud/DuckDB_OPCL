
//===--------------------------------------------------------------------===//
// Decimal Helpers
//===--------------------------------------------------------------------===//
{
Converts a TDDBDecimal object (as obtained from a `DUCKDB_TYPE_DECIMAL` column) into a double.

* val: The decimal value.
* returns: The converted `double` element.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_decimal_to_double(aVal: TDDBDecimal): Double; {$ifdef STATIC}external LIBDDB;{$endif}


