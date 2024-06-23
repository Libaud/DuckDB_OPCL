{========================================================================================
  Include :
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

{$ifdef DYNAMIC_CALL}type{$endif}

//===--------------------------------------------------------------------===//
// Threading Information
//===--------------------------------------------------------------------===//

{
Execute DuckDB tasks on this thread.

Will return after `max_tasks` have been executed, or if there are no more tasks present.

* database: The database object to execute tasks for
* max_tasks: The maximum amount of tasks to execute
}
{$ifdef STATIC_CALL}procedure duckdb_execute_tasks{$else}Tduckdb_execute_tasks = procedure{$endif} (aDatabase: TDDBDatabase; aMaxTasks: TIDX); cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Creates a task state that can be used with duckdb_execute_tasks_state to execute tasks until
 duckdb_finish_execution is called on the state.

duckdb_destroy_state should be called on the result in order to free memory.

* database: The database object to create the task state for
* returns: The task state that can be used with duckdb_execute_tasks_state.
}
{$ifdef STATIC_CALL}function duckdb_create_task_state{$else}Tduckdb_create_task_state = function{$endif} (aDatabase: TDDBDatabase): TDDBTaskState; cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks forever, until duckdb_finish_execution is called on the state.
Multiple threads can share the same TDDBTaskState.

* state: The task state of the executor
}
{$ifdef STATIC_CALL}procedure duckdb_execute_tasks_state{$else}Tduckdb_execute_tasks_state = procedure{$endif} (aState: TDDBTaskState); cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks until either duckdb_finish_execution is called on the state,
max_tasks tasks have been executed or there are no more tasks to be executed.

Multiple threads can share the same TDDBTaskState.

* state: The task state of the executor
* max_tasks: The maximum amount of tasks to execute
* returns: The amount of tasks that have actually been executed
}
{$ifdef STATIC_CALL}function duckdb_execute_n_tasks_state{$else}Tduckdb_execute_n_tasks_state = function{$endif} (aState: TDDBTaskState; aMaxTasks: TIDX): TIDX; cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Finish execution on a specific task.

* state: The task state to finish execution
}
{$ifdef STATIC_CALL}procedure duckdb_finish_execution{$else}Tduckdb_finish_execution = procedure{$endif} (aState: TDDBTaskState); cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Check if the provided TDDBTaskState has finished execution

* state: The task state to inspect
* returns: Whether or not duckdb_finish_execution has been called on the task state
}
{$ifdef STATIC_CALL}function duckdb_task_state_is_finished{$else}Tduckdb_task_state_is_finished = function{$endif} (aState: TDDBTaskState): Boolean; cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Destroys the task state returned from duckdb_create_task_state.

Note that this should not be called while there is an active duckdb_execute_tasks_state running
on the task state.

* state: The task state to clean up
}
{$ifdef STATIC_CALL}procedure duckdb_destroy_task_state{$else}Tduckdb_destroy_task_state = procedure{$endif} (aState: TDDBTaskState); cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}

{
Returns true if execution of the current query is finished.

* con: The connection on which to check
}
{$ifdef STATIC_CALL}function duckdb_execution_is_finished{$else}Tduckdb_execution_is_finished = function{$endif} (aCon: TDDBConnection): Boolean; cdecl; {$ifdef STATIC_CALL}external LIBDDB;{$endif}


