
//===--------------------------------------------------------------------===//
// Query Execution
//===--------------------------------------------------------------------===//
{
Executes a SQL query within a connection and stores the full (materialized) result in the out_result pointer.
If the query fails to execute, DuckDBError is returned and the error message can be retrieved by calling
`duckdb_result_error`.

Note that after running `duckdb_query`, `duckdb_destroy_result` must be called on the result object even if the
query fails, otherwise the error stored within the result will not be freed correctly.

* connection: The connection to perform the query in.
* query: The SQL query to run.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_query(aConnection: TDDBConnection; aQuery: PAnsiChar; var vResult: TDDBResult): TDDBState; {$ifdef STATIC}external LIBDDB;{$endif}

{
Closes the result and de-allocates all memory allocated for that connection.

* result: The result to destroy.
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_destroy_result(var vResult: TDDBResult); {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the column name of the specified column. The result should not need be freed; the column names will
automatically be destroyed when the result is destroyed.

Returns `NULL` if the column is out of range.

* result: The result object to fetch the column name from.
* col: The column index.
* returns: The column name of the specified column.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_column_name(aResult: TDDBResult; aCol: TIDX): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the column type of the specified column.

Returns `DUCKDB_TYPE_INVALID` if the column is out of range.

* result: The result object to fetch the column type from.
* col: The column index.
* returns: The column type of the specified column.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_column_type(aResult: TDDBResult; aCol: TIDX): TDDBType; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the logical column type of the specified column.

The return type of this call should be destroyed with `duckdb_destroy_logical_type`.

Returns `NULL` if the column is out of range.

* result: The result object to fetch the column type from.
* col: The column index.
* returns: The logical column type of the specified column.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_column_logical_type(aResult: TDDBResult; aCol: TIDX): TDDBLogicalType; {$ifdef STATIC}external LIBDDB;{$endif}


{
Returns the number of columns present in a the result object.

* result: The result object.
* returns: The number of columns present in the result object.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_column_count(aResult: TDDBResult): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the number of rows present in a the result object.

* result: The result object.
* returns: The number of rows present in the result object.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_row_count(aResult: TDDBResult): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns the number of rows changed by the query stored in the result. This is relevant only for INSERT/UPDATE/DELETE
queries. For other queries the rows_changed will be 0.

* result: The result object.
* returns: The number of rows changed.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_rows_changed(aResult: TDDBResult): TIDX; {$ifdef STATIC}external LIBDDB;{$endif}

{
**DEPRECATED**: Prefer using `duckdb_result_get_chunk` instead.

Returns the data of a specific column of a result in columnar format.

The function returns a dense array which contains the result data. The exact type stored in the array depends on the
corresponding TDDBType (as provided by `duckdb_column_type`). For the exact type by which the data should be
accessed, see the comments in [the types section](types) or the `TDDBType` enum.

For example, for a column of type `DUCKDB_TYPE_INTEGER`, rows can be accessed in the following manner:
```c
int32_t *data = (int32_t *) duckdb_column_data(&result, 0);
printf("Data for row %d: %d\n", row, data[row]);
```

* result: The result object to fetch the column data from.
* col: The column index.
* returns: The column data of the specified column.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_column_data(aResult: TDDBResult; aCol: TIDX): Pointer; {$ifdef STATIC}external LIBDDB;{$endif}

{
**DEPRECATED**: Prefer using `duckdb_result_get_chunk` instead.

Returns the nullmask of a specific column of a result in columnar format. The nullmask indicates for every row
whether or not the corresponding row is `NULL`. If a row is `NULL`, the values present in the array provided
by `duckdb_column_data` are undefined.

```c
int32_t *data = (int32_t *) duckdb_column_data(&result, 0);
bool *nullmask = duckdb_nullmask_data(&result, 0);
if (nullmask[row]) {
    printf("Data for row %d: NULL\n", row);
} else {
    printf("Data for row %d: %d\n", row, data[row]);
}
```

* result: The result object to fetch the nullmask from.
* col: The column index.
* returns: The nullmask of the specified column.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_nullmask_data(aResult: TDDBResult; aCol: TIDX): PBoolean; {$ifdef STATIC}external LIBDDB;{$endif} deprecated;

{
Returns the error message contained within the result. The error is only set if `duckdb_query` returns `DuckDBError`.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_result` is called.

* result: The result object to fetch the error from.
* returns: The error of the result.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_result_error(aResult: TDDBResult): PAnsiChar; {$ifdef STATIC}external LIBDDB;{$endif}


