
//===--------------------------------------------------------------------===//
// Replacement Scans
//===--------------------------------------------------------------------===//
type
  TDDBReplacementScanInfo = Pointer;

  TDDBReplacementCallback = procedure(aInfo: TDDBReplacementScanInfo;
                                      aTableName: PAnsiChar;
                                      aData: Pointer); cdecl;

{
Add a replacement scan definition to the specified database

* db: The database object to add the replacement scan to
* replacement: The replacement scan callback
* extra_data: Extra data that is passed back into the specified callback
* delete_callback: The delete callback to call on the extra data, if any
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_add_replacement_scan(aDB: TDDBDatabase;
                                                                       aReplacement: TDDBReplacementCallback;
                                                                       aExtraData: Pointer;
                                                                       aDeleteCallback: TDDBDeleteCallback); {$ifdef STATIC}external LIBDDB;{$endif}

{
Sets the replacement function name to use. If this function is called in the replacement callback,
 the replacement scan is performed. If it is not called, the replacement callback is not performed.

* info: The info object
* function_name: The function name to substitute.
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_replacement_scan_set_function_name(aInfo: TDDBReplacementScanInfo;
                                                                                     aFunctionName: PAnsiChar); cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Adds a parameter to the replacement scan function.

* info: The info object
* parameter: The parameter to add.
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_replacement_scan_add_parameter(aInfo: TDDBReplacementScanInfo;
                                                                                 aParameter: TDDBValue); cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Report that an error has occurred while executing the replacement scan.

* info: The info object
* error: The error message
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_replacement_scan_set_error(aInfo: TDDBReplacementScanInfo;
                                                                             aError: PAnsiChar); cdecl; {$ifdef STATIC}external LIBDDB;{$endif}


