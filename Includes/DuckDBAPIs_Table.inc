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
// Table Functions
//===--------------------------------------------------------------------===//

{
Creates a new empty table function.

The return value should be destroyed with `duckdb_destroy_table_function`.

* returns: The table function object.
}
{$ifdef STATIC}function duckdb_create_table_function{$else}Tduckdb_create_table_function = function{$endif} : TDDBTableFunction; {$ifdef STATIC}external LIBDDB;{$endif}

{
Destroys the given table function object.

* table_function: The table function to destroy
}
{$ifdef STATIC}procedure duckdb_destroy_table_function{$else}Tduckdb_destroy_table_function = procedure{$endif} (var vTableFunction: TDDBTableFunction); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the name of the given table function.

* table_function: The table function
* name: The name of the table function
}
{$ifdef STATIC}procedure duckdb_table_function_set_name{$else}Tduckdb_table_function_set_name = procedure{$endif} (aTableFunction: TDDBTableFunction; aName: PAnsiChar); {$ifdef STATIC}external LIBDDB;{$endif}

{
Adds a parameter to the table function.

* table_function: The table function
* type: The type of the parameter to add.
}
{$ifdef STATIC}procedure duckdb_table_function_add_parameter{$else}Tduckdb_table_function_add_parameter = procedure{$endif} (aTableFunction: TDDBTableFunction; aTypeParam: TDDBLogicalType); {$ifdef STATIC}external LIBDDB;{$endif}

{
Adds a named parameter to the table function.

* table_function: The table function
* name: The name of the parameter
* type: The type of the parameter to add.
}
{$ifdef STATIC}procedure duckdb_table_function_add_named_parameter{$else}Tduckdb_table_function_add_named_parameter = procedure{$endif} (aTableFunction: TDDBTableFunction; aName: PAnsiChar; aTypeParam: TDDBLogicalType); {$ifdef STATIC}external LIBDDB;{$endif}

{
Assigns extra information to the table function that can be fetched during binding, etc.

* table_function: The table function
* extra_info: The extra information
* destroy: The callback that will be called to destroy the bind data (if any)
}
{$ifdef STATIC}procedure duckdb_table_function_set_extra_info{$else}Tduckdb_table_function_set_extra_info = procedure{$endif} (aTableFunction: TDDBTableFunction; aExtraInfo: Pointer; aDestroy: TDDBDeleteCallback); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the bind function of the table function

* table_function: The table function
* bind: The bind function
}
{$ifdef STATIC}procedure duckdb_table_function_set_bind{$else}Tduckdb_table_function_set_bind = procedure{$endif} (aTableFunction: TDDBTableFunction; aBind: TDDBTableFunctionBind); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the init function of the table function

* table_function: The table function
* init: The init function
}
{$ifdef STATIC}procedure duckdb_table_function_set_init{$else}Tduckdb_table_function_set_init = procedure{$endif} (aTableFunction: TDDBTableFunction; aInit: TDDBTableFunctionInit); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the thread-local init function of the table function

* table_function: The table function
* init: The init function
}
{$ifdef STATIC}procedure duckdb_table_function_set_local_init{$else}Tduckdb_table_function_set_local_init = procedure{$endif} (aTableFunction: TDDBTableFunction; aInit: TDDBTableFunctionInit); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the main function of the table function

* table_function: The table function
* function: The function
}
{$ifdef STATIC}procedure duckdb_table_function_set_function{$else}Tduckdb_table_function_set_function = procedure{$endif} (aTableFunction: TDDBTableFunction; aFunctionProc: TDDBMainTableFunction); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets whether or not the given table function supports projection pushdown.

If this is set to true, the system will provide a list of all required columns in the `init` stage through
the `duckdb_init_get_column_count` and `duckdb_init_get_column_index` functions.
If this is set to false (the default), the system will expect all columns to be projected.

* table_function: The table function
* pushdown: True if the table function supports projection pushdown, false otherwise.
}
{$ifdef STATIC}procedure duckdb_table_function_supports_projection_pushdown{$else}Tduckdb_table_function_supports_projection_pushdown = procedure{$endif} (aTableFunction: TDDBTableFunction; aPushdown: Boolean); {$ifdef STATIC}external LIBDDB;{$endif}

{
Register the table function object within the given connection.

The function requires at least a name, a bind function, an init function and a main function.

If the function is incomplete or a function with this name already exists DuckDBError is returned.

* con: The connection to register it in.
* function: The function pointer
* returns: Whether or not the registration was successful.
}
{$ifdef STATIC}function duckdb_register_table_function{$else}Tduckdb_register_table_function = function{$endif} (aCon: TDDBConnection; aFunctionTable: TDDBTableFunction): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

//===--------------------------------------------------------------------===//
// Table Function Bind
//===--------------------------------------------------------------------===//
{
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
}
{$ifdef STATIC}function duckdb_bind_get_extra_info{$else}Tduckdb_bind_get_extra_info = function{$endif} (aInfo: TDDBBindInfo): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Adds a result column to the output of the table function.

* info: The info object
* name: The name of the column
* type: The logical type of the column
}
{$ifdef STATIC}procedure duckdb_bind_add_result_column{$else}Tduckdb_bind_add_result_column = procedure{$endif} (aInfo: TDDBBindInfo; aName: PAnsiChar; aType_param: TDDBLogicalType); {$ifdef STATIC}external LIBDDB;{$endif}

{
Retrieves the number of regular (non-named) parameters to the function.

* info: The info object
* returns: The number of parameters
}
{$ifdef STATIC}function duckdb_bind_get_parameter_count{$else}Tduckdb_bind_get_parameter_count = function{$endif} (aInfo: TDDBBindInfo): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Retrieves the parameter at the given index.

The result must be destroyed with `duckdb_destroy_value`.

* info: The info object
* index: The index of the parameter to get
* returns: The value of the parameter. Must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC}function duckdb_bind_get_parameter{$else}Tduckdb_bind_get_parameter = function{$endif} (aInfo: TDDBBindInfo; index: TIDX): TDDBValue; {$ifdef STATIC}external LIBDDB;{$endif}

{
Retrieves a named parameter with the given name.

The result must be destroyed with `duckdb_destroy_value`.

* info: The info object
* name: The name of the parameter
* returns: The value of the parameter. Must be destroyed with `duckdb_destroy_value`.
}
{$ifdef STATIC}function duckdb_bind_get_named_parameter{$else}Tduckdb_bind_get_named_parameter = function{$endif} (aInfo: TDDBBindInfo; aName: PAnsiChar): TDDBValue; {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the user-provided bind data in the bind object. This object can be retrieved again during execution.

* info: The info object
* extra_data: The bind data object.
* destroy: The callback that will be called to destroy the bind data (if any)
}
{$ifdef STATIC}procedure duckdb_bind_set_bind_data{$else}Tduckdb_bind_set_bind_data = procedure{$endif} (aInfo: TDDBBindInfo; aBindData: Pointer; aDestroy: TDDBDeleteCallback); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the cardinality estimate for the table function, used for optimization.

* info: The bind data object.
* is_exact: Whether or not the cardinality estimate is exact, or an approximation
}
{$ifdef STATIC}procedure duckdb_bind_set_cardinality{$else}Tduckdb_bind_set_cardinality = procedure{$endif} (aInfo: TDDBBindInfo; aCardinality: TIDX; aIsExact: Boolean); {$ifdef STATIC}external LIBDDB;{$endif}

{
Report that an error has occurred while calling bind.

* info: The info object
* error: The error message
}
{$ifdef STATIC}procedure duckdb_bind_set_error{$else}Tduckdb_bind_set_error = procedure{$endif} (aInfo: TDDBBindInfo; aError: PAnsiChar); {$ifdef STATIC}external LIBDDB;{$endif}

//===--------------------------------------------------------------------===//
// Table Function Init
//===--------------------------------------------------------------------===//

{
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
}
{$ifdef STATIC}function duckdb_init_get_extra_info{$else}Tduckdb_init_get_extra_info = function{$endif} (aInfo: TDDBInitInfo): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.
For tracking state, use the init data instead.

* info: The info object
* returns: The bind data object
}
{$ifdef STATIC}function duckdb_init_get_bind_data{$else}Tduckdb_init_get_bind_data = function{$endif} (aInfo: TDDBInitInfo): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the user-provided init data in the init object. This object can be retrieved again during execution.

* info: The info object
* extra_data: The init data object.
* destroy: The callback that will be called to destroy the init data (if any)
}
{$ifdef STATIC}procedure duckdb_init_set_init_data{$else}Tduckdb_init_set_init_data = procedure{$endif} (aInfo: TDDBInitInfo; aInitData: Pointer; aDestroy: TDDBDeleteCallback); {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the number of projected columns.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

* info: The info object
* returns: The number of projected columns.
}
{$ifdef STATIC}function duckdb_init_get_column_count{$else}Tduckdb_init_get_column_count = function{$endif} (aInfo: TDDBInitInfo): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the column index of the projected column at the specified position.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

* info: The info object
* column_index: The index at which to get the projected column index, from 0..duckdb_init_get_column_count(info)
* returns: The column index of the projected column.
}
{$ifdef STATIC}function duckdb_init_get_column_index{$else}Tduckdb_init_get_column_index = function{$endif} (aInfo: TDDBInitInfo; aColumnIndex: TIDX): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets how many threads can process this table function in parallel (default: 1)

* info: The info object
* max_threads: The maximum amount of threads that can process this table function
}
{$ifdef STATIC}procedure duckdb_init_set_max_threads{$else}Tduckdb_init_set_max_threads = procedure{$endif} (aInfo: TDDBInitInfo; aMax_Threads: TIDX); {$ifdef STATIC}external LIBDDB;{$endif}

{
Report that an error has occurred while calling init.

* info: The info object
* error: The error message
}
{$ifdef STATIC}procedure duckdb_init_set_error{$else}Tduckdb_init_set_error = procedure{$endif} (aInfo: TDDBInitInfo; aError: PAnsiChar); {$ifdef STATIC}external LIBDDB;{$endif}

//===--------------------------------------------------------------------===//
// Table Function
//===--------------------------------------------------------------------===//

{
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
}
{$ifdef STATIC}function duckdb_function_get_extra_info{$else}Tduckdb_function_get_extra_info = function{$endif} (aInfo: TDDBFunctionInfo): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.
For tracking state, use the init data instead.

* info: The info object
* returns: The bind data object
}
{$ifdef STATIC}function duckdb_function_get_bind_data{$else}Tduckdb_function_get_bind_data = function{$endif} (aInfo: TDDBFunctionInfo): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Gets the init data set by `duckdb_init_set_init_data` during the init.

* info: The info object
* returns: The init data object
}
{$ifdef STATIC}function duckdb_function_get_init_data{$else}Tduckdb_function_get_init_data = function{$endif} (aInfo: TDDBFunctionInfo): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Gets the thread-local init data set by `duckdb_init_set_init_data` during the local_init.

* info: The info object
* returns: The init data object
}
{$ifdef STATIC}function duckdb_function_get_local_init_data{$else}Tduckdb_function_get_local_init_data = function{$endif} (aInfo: TDDBFunctionInfo): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
Report that an error has occurred while executing the function.

* info: The info object
* error: The error message
}
{$ifdef STATIC}procedure duckdb_function_set_error{$else}Tduckdb_function_set_error = procedure{$endif} (aInfo: TDDBFunctionInfo; aError: PAnsiChar); {$ifdef STATIC}external LIBDDB;{$endif}


