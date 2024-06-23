{========================================================================================
  Include : DuckDBAPI
  Description : Duck DB API's configuration
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2023-09-16 Migration of duckdb.h
========================================================================================}

{$ifdef FPC}
  {$MACRO ON}
{$endif}

{$ifdef STATIC_CALL and DYNAMIC_LOAD}
{$else}
  {$ifdef DYNAMIC_LOAD or LOAD_DYNAMICALLY}
  {$else}
  {$endif}
{$endif}


{$DEFINE DUCKDB_API_0_3_1 = 1}
{$DEFINE DUCKDB_API_0_3_2 = 2}
{$DEFINE DUCKDB_API_LATEST = DUCKDB_API_0_3_2}
{$DEFINE DUCKDB_API_VERSION = DUCKDB_API_LATEST}

