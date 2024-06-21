
//===--------------------------------------------------------------------===//
// Extract Statements
//===--------------------------------------------------------------------===//
// A query string can be extracted into multiple SQL statements. Each statement can be prepared and executed separately.

{
Extract all statements from a query.
Note that after calling `duckdb_extract_statements`, the extracted statements should always be destroyed using
`duckdb_destroy_extracted`, even if no statements were extracted.
If the extract fails, `duckdb_extract_statements_error` can be called to obtain the reason why the extract failed.
* connection: The connection object
* query: The SQL query to extract
* out_extracted_statements: The resulting extracted statements object
* returns: The number of extracted statements or 0 on failure.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_extract_statements(aConnection: TDDBConnection;
                                                                    aQuery: PAnsiChar;
                                                                    vExtractedStatements: PDDBExtractedStatements): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Prepare an extracted statement.
Note that after calling `duckdb_prepare_extracted_statement`, the prepared statement should always be destroyed using
`duckdb_destroy_prepare`, even if the prepare fails.
If the prepare fails, `duckdb_prepare_error` can be called to obtain the reason why the prepare failed.
* connection: The connection object
* extracted_statements: The extracted statements object
* index: The index of the extracted statement to prepare
* out_prepared_statement: The resulting prepared statement object
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_prepare_extracted_statement(aConnection: TDDBConnection;
                                                                             aExtracted_statements: TDDBExtractedStatements;
                                                                             aIndex: TIDX;
                                                                             vPreparedStatement: PDDBPreparedStatement): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the error message contained within the extracted statements.
The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_extracted` is called.
* result: The extracted statements to fetch the error from.
* returns: The error of the extracted statements.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_extract_statements_error(aExtractedStatements: TDDBExtractedStatements): PChar; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
De-allocates all memory allocated for the extracted statements.
* extracted_statements: The extracted statements to destroy.
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_destroy_extracted(var vExtractedStatements: PDDBExtractedStatements); {$ifdef STATIC}external LIBDDB;{$endif}


