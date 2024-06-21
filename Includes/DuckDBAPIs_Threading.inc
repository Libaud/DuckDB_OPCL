
//===--------------------------------------------------------------------===//
// Threading Information
//===--------------------------------------------------------------------===//
type
  TDDBTaskState = Pointer;

{
Execute DuckDB tasks on this thread.

Will return after `max_tasks` have been executed, or if there are no more tasks present.

* database: The database object to execute tasks for
* max_tasks: The maximum amount of tasks to execute
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_execute_tasks(aDatabase: TDDBDatabase; aMaxTasks: TIDX); cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Creates a task state that can be used with duckdb_execute_tasks_state to execute tasks until
 duckdb_finish_execution is called on the state.

duckdb_destroy_state should be called on the result in order to free memory.

* database: The database object to create the task state for
* returns: The task state that can be used with duckdb_execute_tasks_state.
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_create_task_state(aDatabase: TDDBDatabase): TDDBTaskState; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks forever, until duckdb_finish_execution is called on the state.
Multiple threads can share the same TDDBTaskState.

* state: The task state of the executor
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_execute_tasks_state(aState: TDDBTaskState); cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks until either duckdb_finish_execution is called on the state,
max_tasks tasks have been executed or there are no more tasks to be executed.

Multiple threads can share the same TDDBTaskState.

* state: The task state of the executor
* max_tasks: The maximum amount of tasks to execute
* returns: The amount of tasks that have actually been executed
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_execute_n_tasks_state(aState: TDDBTaskState; aMaxTasks: TIDX): TIDX; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Finish execution on a specific task.

* state: The task state to finish execution
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_finish_execution(aState: TDDBTaskState); cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Check if the provided TDDBTaskState has finished execution

* state: The task state to inspect
* returns: Whether or not duckdb_finish_execution has been called on the task state
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_task_state_is_finished(aState: TDDBTaskState): Boolean; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Destroys the task state returned from duckdb_create_task_state.

Note that this should not be called while there is an active duckdb_execute_tasks_state running
on the task state.

* state: The task state to clean up
}
{$ifdef STATIC}procedure{$else}var{$endif} duckdb_destroy_task_state(aState: TDDBTaskState); cdecl; {$ifdef STATIC}external LIBDDB;{$endif}

{
Returns true if execution of the current query is finished.

* con: The connection on which to check
}
{$ifdef STATIC}function{$else}var{$endif} duckdb_execution_is_finished(aCon: TDDBConnection): Boolean; cdecl; {$ifdef STATIC}external LIBDDB;{$endif}


