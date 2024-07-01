{========================================================================================
  Include : DuckDBLib
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

const
  DUCKDB_API_LATEST = 2;

  {$ifdef LINUX}
  LIBDDB = 'libduckdb.so';
  {$endif}

  {$ifdef MSWINDOWS}
  LIBDDB = 'duckdb.dll';
  {$endif}

  {$ifdef DARWIN}
  LIBDDB = 'libduckdb.dylib';
  {$endif}

{ end of include file }

