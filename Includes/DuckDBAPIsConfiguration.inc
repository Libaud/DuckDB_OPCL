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
// Configuration
//===--------------------------------------------------------------------===//
{
Initializes an empty configuration object that can be used to provide start-up options for the DuckDB instance
through `duckdb_open_ext`.

This will always succeed unless there is a malloc failure.

* out_config: The result configuration object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC_CALL}function duckdb_create_config
             {$else}Tduckdb_create_config = function{$endif} (var vConfig: TDDBConfig): TDDBState;
                                            {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
This returns the total amount of configuration options available for usage with `duckdb_get_config_flag`.

This should not be called in a loop as it internally loops over all the options.

* returns: The amount of config options available.
}
{$ifdef STATIC_CALL}function duckdb_config_count
             {$else}Tduckdb_config_count = function{$endif} : Size_t;
                                           {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Obtains a human-readable name and description of a specific configuration option. This can be used to e.g.
display configuration options. This will succeed unless `index` is out of range (i.e. `>= duckdb_config_count`).

The result name or description MUST NOT be freed.

* index: The index of the configuration option (between 0 and `duckdb_config_count`)
* out_name: A name of the configuration flag.
* out_description: A description of the configuration flag.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC_CALL}function duckdb_get_config_flag
             {$else}Tduckdb_get_config_flag = function{$endif} (aIndex: Size_t; var vName, vDescription: PAnsiChar): TDDBState;
                                              {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Sets the specified option for the specified configuration. The configuration option is indicated by name.
To obtain a list of config options, see `duckdb_get_config_flag`.

In the source code, configuration options are defined in `config.cpp`.

This can fail if either the name is invalid, or if the value provided for the option is invalid.

* TDDBConfig: The configuration object to set the option on.
* name: The name of the configuration flag to set.
* option: The value to set the configuration flag to.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC_CALL}function duckdb_set_config
             {$else}Tduckdb_set_config = function{$endif} (aConfig: TDDBConfig; aName: PAnsiChar; aOption: PAnsiChar): TDDBState;
                                         {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{
Destroys the specified configuration option and de-allocates all memory allocated for the object.

* config: The configuration object to destroy.
}
{$ifdef STATIC_CALL}procedure duckdb_destroy_config
             {$else}Tduckdb_destroy_config = procedure{$endif} (var vConfig: TDDBConfig);
                                             {$ifdef STATIC_CALL}cdecl; external LIBDDB;{$endif}

{ end of include file }

