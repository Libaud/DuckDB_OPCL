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

{$i DuckDBAPI.inc}

interface

uses
  Classes, SysUtils
  {$ifdef FPC}, CTypes{$endif}
  {$ifdef WINDOWS}, Windows{$endif};

{$i DuckDBLib.inc}

{$i DuckDBTypes.inc}

{$i DuckDBAPIs.inc}

{$ifdef DYNAMIC}
  {$i DuckDBAPIDynamic.inc}
{$endif}

implementation

uses
  DuckDBAPIExceptions, DuckDBAPIRessources;

{$ifdef DYNAMIC}
  {$i DynamicDuckDB.inc}
{$else}
  {$i StaticDuckDB.inc}
{$endif}

end.

