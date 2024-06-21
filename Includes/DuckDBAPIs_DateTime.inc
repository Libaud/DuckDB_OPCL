
//===--------------------------------------------------------------------===//
// Date/Time/Timestamp Helpers
//===--------------------------------------------------------------------===//
{
Decompose a `TDDBDate` object into year, month and date (stored as `TDDBDateStruct`).

* date: The date object, as obtained from a `DUCKDB_TYPE_DATE` column.
* returns: The `TDDBDateStruct` with the decomposed elements.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_from_date(aDate: TDDBDate): TDDBDateStruct; {$ifdef STATIC}external LIBDDB;{$endif}

{
Re-compose a `TDDBDate` from year, month and date (`TDDBDateStruct`).

* date: The year, month and date stored in a `TDDBDateStruct`.
* returns: The `TDDBDate` element.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_to_date(aDate: TDDBDateStruct): TDDBDate; {$ifdef STATIC}external LIBDDB;{$endif}

{
Decompose a `TDDBTime` object into hour, minute, second and microsecond (stored as `TDDBTimeStruct`).

* time: The time object, as obtained from a `DUCKDB_TYPE_TIME` column.
* returns: The `TDDBTimeStruct` with the decomposed elements.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_from_time(aTime: TDDBTime): TDDBTimeStruct; {$ifdef STATIC}external LIBDDB;{$endif}

{
Re-compose a `TDDBTime` from hour, minute, second and microsecond (`TDDBTimeStruct`).

* time: The hour, minute, second and microsecond in a `TDDBTimeStruct`.
* returns: The `TDDBTime` element.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_to_time(aTime: TDDBTimeStruct): TDDBTime; {$ifdef STATIC}external LIBDDB;{$endif}

{
Decompose a `TDDBTimestamp` object into a `TDDBTimestampStruct`.

* ts: The ts object, as obtained from a `DUCKDB_TYPE_TIMESTAMP` column.
* returns: The `TDDBTimestampStruct` with the decomposed elements.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_from_timestamp(aTS: TDDBTimestamp): TDDBTimestampStruct; {$ifdef STATIC}external LIBDDB;{$endif}

{
Re-compose a `TDDBTimestamp` from a TDDBTimestampStruct.

* ts: The de-composed elements in a `TDDBTimestampStruct`.
* returns: The `TDDBTimestamp` element.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_to_timestamp(aTS: TDDBTimestampStruct): TDDBTimestamp; {$ifdef STATIC}external LIBDDB;{$endif}


