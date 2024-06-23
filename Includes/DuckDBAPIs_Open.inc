{========================================================================================
  Include :
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

{$ifdef DYNAMIC}type{$endif}

//===--------------------------------------------------------------------===//
// Open/Connect
//===--------------------------------------------------------------------===//

{
Creates a new database or opens an existing database file stored at the the given path.
If no path is given a new in-memory database is created instead.
The instantiated database should be closed with 'duckdb_close'

* path: Path to the database file on disk, or `nullptr` or `:memory:` to open an in-memory database.
* out_database: The result database object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC} function duckdb_open {$else} Tduckdb_open = function {$endif}(aPath: PAnsiChar; var vDatabase: TDDBDatabase): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}
{
Extended version of duckdb_open. Creates a new database or opens an existing database file stored at the the given path.

* path: Path to the database file on disk, or `nullptr` or `:memory:` to open an in-memory database.
* out_database: The result database object.
* config: (Optional) configuration used to start up the database system.
* out_error: If set and the function returns DuckDBError, this will contain the reason why the start-up failed.
Note that the error must be freed using `duckdb_free`.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC} function duckdb_open_ext {$else} Tduckdb_open_ext = function {$endif} (aPath: PAnsiChar; var vDatabase: TDDBDatabase; aConfig: TDDBConfig;
                                                          var vError: PPAnsiChar): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}


{
Closes the specified database and de-allocates all memory allocated for that database.
This should be called after you are done with any database allocated through `duckdb_open`.
Note that failing to call `duckdb_close` (in case of e.g. a program crash) will not cause data corruption.
Still it is recommended to always correctly close a database object after you are done with it.

* database: The database object to shut down.
}
{$ifdef STATIC}procedure duckdb_close {$else} Tduckdb_close = procedure {$endif} (var vDatabase: TDDBDatabase); {$ifdef STATIC}external LIBDDB;{$endif}

{
Opens a connection to a database. Connections are required to query the database, and store transactional state
associated with the connection.
The instantiated connection should be closed using 'duckdb_disconnect'

* database: The database file to connect to.
* out_connection: The result connection object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function duckdb_connect {$else} Tduckdb_connect = function {$endif} (aDatabase: TDDBDatabase; var vConnection: TDDBConnection): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Interrupt running query

* connection: The connection to interruot
}
{$ifdef STATIC}procedure duckdb_interrupt {$else} Tduckdb_interrupt = procedure {$endif} (aConnection: TDDBConnection); {$ifdef STATIC}external LIBDDB;{$endif}

{
Get progress of the running query

* connection: The working connection
* returns: -1 if no progress or a percentage of the progress
}
{$ifdef STATIC}function duckdb_query_progress {$else} Tduckdb_query_progress = function {$endif} (aConnection: TDDBConnection): Double; {$ifdef STATIC}external LIBDDB;{$endif}

{
Closes the specified connection and de-allocates all memory allocated for that connection.

* connection: The connection to close.
}
{$ifdef STATIC}procedure duckdb_disconnect {$else} Tduckdb_disconnect = procedure {$endif} (var vConnection: TDDBConnection); {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the version of the linked DuckDB, with a version postfix for dev versions

Usually used for developing C extensions that must return this for a compatibility check.
}
{$ifdef STATIC}function duckdb_library_version {$else} Tduckdb_library_version = function {$endif} : PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}


