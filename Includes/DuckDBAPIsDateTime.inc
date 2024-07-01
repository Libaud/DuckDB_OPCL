{========================================================================================
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
// Date/Time/Timestamp Helpers
//===--------------------------------------------------------------------===//
{
Decompose a `TDDBDate` object into year, month and date (stored as `TDDBDateStruct`).

* date: The date object, as obtained from a `DUCKDB_TYPE_DATE` column.
* returns: The `TDDBDateStruct` with the decomposed elements.
}
{$ifdef STATIC_CALL}function duckdb_from_date
             {$else}Tduckdb_from_date = function{$endif} (aDate: TDDBDate): TDDBDateStruct;
                                        {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Re-compose a `TDDBDate` from year, month and date (`TDDBDateStruct`).

* date: The year, month and date stored in a `TDDBDateStruct`.
* returns: The `TDDBDate` element.
}
{$ifdef STATIC_CALL}function duckdb_to_date
             {$else}Tduckdb_to_date = function{$endif} (aDate: TDDBDateStruct): TDDBDate;
                                      {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Decompose a `TDDBTime` object into hour, minute, second and microsecond (stored as `TDDBTimeStruct`).

* time: The time object, as obtained from a `DUCKDB_TYPE_TIME` column.
* returns: The `TDDBTimeStruct` with the decomposed elements.
}
{$ifdef STATIC_CALL}function duckdb_from_time
             {$else}Tduckdb_from_time = function{$endif} (aTime: TDDBTime): TDDBTimeStruct;
                                        {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Re-compose a `TDDBTime` from hour, minute, second and microsecond (`TDDBTimeStruct`).

* time: The hour, minute, second and microsecond in a `TDDBTimeStruct`.
* returns: The `TDDBTime` element.
}
{$ifdef STATIC_CALL}function duckdb_to_time
             {$else}Tduckdb_to_time = function{$endif} (aTime: TDDBTimeStruct): TDDBTime;
                                      {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Decompose a `TDDBTimestamp` object into a `TDDBTimestampStruct`.

* ts: The ts object, as obtained from a `DUCKDB_TYPE_TIMESTAMP` column.
* returns: The `TDDBTimestampStruct` with the decomposed elements.
}
{$ifdef STATIC_CALL}function duckdb_from_timestamp
             {$else}Tduckdb_from_timestamp = function{$endif} (aTS: TDDBTimestamp): TDDBTimestampStruct;
                                             {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Re-compose a `TDDBTimestamp` from a TDDBTimestampStruct.

* ts: The de-composed elements in a `TDDBTimestampStruct`.
* returns: The `TDDBTimestamp` element.
}
{$ifdef STATIC_CALL}function duckdb_to_timestamp
             {$else}Tduckdb_to_timestamp = function{$endif} (aTS: TDDBTimestampStruct): TDDBTimestamp;
                                           {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{ end of include file }

