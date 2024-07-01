{========================================================================================
  Module : DuckDBApi
  Description : DuckDB client implementation for Object Pascal
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2023-09-16 Migration of duckdb.h
  2024-06-21 Code adjonction, correcting
 ========================================================================================}
unit DuckDBAPI;

{$ifdef FPC}
  {$mode objfpc}{$H+}
{$endif}

{$I *.inc}

interface

uses
  Classes, SysUtils
  {$ifdef WINDOWS}, Windows{$endif};

{$i DuckDBLib.inc}

{$i DuckDBTypes.inc}

{$i DuckDBAPIs.inc}

{$i DuckDBAPIDynamic.inc}

implementation

uses
  DuckDBAPIExceptions, DuckDBAPIRessources;

{$i DynamicDuckDB.inc}
{$i StaticDuckDB.inc}

end.

