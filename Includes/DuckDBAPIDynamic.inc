{========================================================================================
  Include : DuckDDBAPIDynamic
  Description : Duck DB API'S
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

{$ifdef DYNAMIC_CALL}
var
  // Appender
  duckdb_appender_create: Tduckdb_appender_create;
  duckdb_appender_error: Tduckdb_appender_error;
  duckdb_appender_flush: Tduckdb_appender_flush;
  duckdb_appender_close: Tduckdb_appender_close;
  duckdb_appender_destroy: Tduckdb_appender_destroy;
  duckdb_appender_begin_row: Tduckdb_appender_begin_row;
  duckdb_appender_end_row: Tduckdb_appender_end_row;
  duckdb_append_bool: Tduckdb_append_bool;
  duckdb_append_int8: Tduckdb_append_int8;
  duckdb_append_int16: Tduckdb_append_int16;
  duckdb_append_int32: Tduckdb_append_int32;
  duckdb_append_int64: Tduckdb_append_int64;
  duckdb_append_hugeint: Tduckdb_append_hugeint;
  duckdb_append_uint16: Tduckdb_append_uint16;
  duckdb_append_uint32: Tduckdb_append_uint32;
  duckdb_append_uint64: Tduckdb_append_uint64;
  duckdb_append_float: Tduckdb_append_float;
  duckdb_append_double: Tduckdb_append_double;
  duckdb_append_date: Tduckdb_append_date;
  duckdb_append_time: Tduckdb_append_time;
  duckdb_append_timestamp: Tduckdb_append_timestamp;
  duckdb_append_interval: Tduckdb_append_interval;
  duckdb_append_varchar: Tduckdb_append_varchar;
  duckdb_append_varchar_length: Tduckdb_append_varchar_length;
  duckdb_append_blob: Tduckdb_append_blob;
  duckdb_append_null: Tduckdb_append_null;
  duckdb_append_data_chunk: Tduckdb_append_data_chunk;
  // Arrow Interface
  duckdb_query_arrow: Tduckdb_query_arrow {$ifdef FPC};{$endif} deprecated;
  duckdb_query_arrow_schema: Tduckdb_query_arrow_schema;
  duckdb_prepared_arrow_schema: Tduckdb_prepared_arrow_schema;
  duckdb_query_arrow_array: Tduckdb_query_arrow_array;
  duckdb_arrow_column_count: Tduckdb_arrow_column_count;
  duckdb_arrow_row_count: Tduckdb_arrow_row_count;
  duckdb_arrow_rows_changed: Tduckdb_arrow_rows_changed;
  duckdb_query_arrow_error: Tduckdb_query_arrow_error;
  duckdb_destroy_arrow: Tduckdb_destroy_arrow;
  // Configuration
  duckdb_create_config: Tduckdb_create_config;
  duckdb_config_count: Tduckdb_config_count;
  duckdb_get_config_flag: Tduckdb_get_config_flag;
  duckdb_set_config: Tduckdb_set_config;
  duckdb_destroy_config: Tduckdb_destroy_config;
  // Data Chunk Interface
  duckdb_create_data_chunk: Tduckdb_create_data_chunk;
  duckdb_destroy_data_chunk: Tduckdb_destroy_data_chunk;
  duckdb_data_chunk_reset: Tduckdb_data_chunk_reset;
  duckdb_data_chunk_get_column_count: Tduckdb_data_chunk_get_column_count;
  duckdb_data_chunk_get_vector: Tduckdb_data_chunk_get_vector;
  duckdb_data_chunk_get_size: Tduckdb_data_chunk_get_size;
  duckdb_data_chunk_set_size: Tduckdb_data_chunk_set_size;
  // Date/Time/Timestamp Helpers
  duckdb_from_date: Tduckdb_from_date;
  duckdb_to_date: Tduckdb_to_date;
  duckdb_from_time: Tduckdb_from_time;
  duckdb_to_time: Tduckdb_to_time;
  duckdb_from_timestamp: Tduckdb_from_timestamp;
  duckdb_to_timestamp: Tduckdb_to_timestamp;
  // Decimal Helpers
  duckdb_decimal_to_double: Tduckdb_decimal_to_double;
  // Extract Statements
  duckdb_extract_statements: Tduckdb_extract_statements;
  duckdb_prepare_extracted_statement: Tduckdb_prepare_extracted_statement;
  duckdb_extract_statements_error: Tduckdb_extract_statements_error;
  duckdb_destroy_extracted: Tduckdb_destroy_extracted;
  // Helpers
  duckdb_malloc: Tduckdb_malloc;
  duckdb_free: Tduckdb_free;
  duckdb_vector_size: Tduckdb_vector_size;
  duckdb_string_is_inlined: Tduckdb_string_is_inlined;
  // Hugeint Helpers
  duckdb_hugeint_to_double: Tduckdb_hugeint_to_double;
  duckdb_double_to_hugeint: Tduckdb_double_to_hugeint;
  duckdb_double_to_decimal: Tduckdb_double_to_decimal;
  // Logical Type Interface
  duckdb_create_logical_type: Tduckdb_create_logical_type;
  duckdb_create_list_type: Tduckdb_create_list_type;
  duckdb_create_map_type: Tduckdb_create_map_type;
  duckdb_create_union_type: Tduckdb_create_union_type;
  duckdb_create_struct_type: Tduckdb_create_struct_type;
  duckdb_create_decimal_type: Tduckdb_create_decimal_type;
  duckdb_get_type_id: Tduckdb_get_type_id;
  duckdb_decimal_width: Tduckdb_decimal_width;
  duckdb_decimal_scale: Tduckdb_decimal_scale;
  duckdb_decimal_internal_type: Tduckdb_decimal_internal_type;
  duckdb_enum_internal_type: Tduckdb_enum_internal_type;
  duckdb_enum_dictionary_size: Tduckdb_enum_dictionary_size;
  duckdb_enum_dictionary_value: Tduckdb_enum_dictionary_value;
  duckdb_list_type_child_type: Tduckdb_list_type_child_type;
  duckdb_map_type_key_type: Tduckdb_map_type_key_type;
  duckdb_map_type_value_type: Tduckdb_map_type_value_type;
  duckdb_struct_type_child_count: Tduckdb_struct_type_child_count;
  duckdb_struct_type_child_name: Tduckdb_struct_type_child_name;
  duckdb_struct_type_child_type: Tduckdb_struct_type_child_type;
  duckdb_union_type_member_count: Tduckdb_union_type_member_count;
  duckdb_union_type_member_name: Tduckdb_union_type_member_name;
  duckdb_union_type_member_type: Tduckdb_union_type_member_type;
  duckdb_destroy_logical_type: Tduckdb_destroy_logical_type;
  // Open/Connect
  duckdb_open: Tduckdb_open;
  duckdb_open_ext: Tduckdb_open_ext;
  duckdb_close: Tduckdb_close;
  duckdb_connect: Tduckdb_connect;
  duckdb_interrupt: Tduckdb_interrupt;
  duckdb_query_progress: Tduckdb_query_progress;
  duckdb_disconnect: Tduckdb_disconnect;
  duckdb_library_version: Tduckdb_library_version;
  // Pending Result Interface
  duckdb_pending_prepared: Tduckdb_pending_prepared;
  duckdb_pending_prepared_streaming: Tduckdb_pending_prepared_streaming;
  duckdb_destroy_pending: Tduckdb_destroy_pending;
  duckdb_pending_error: Tduckdb_pending_error;
  duckdb_pending_execute_task: Tduckdb_pending_execute_task;
  duckdb_execute_pending: Tduckdb_execute_pending;
  duckdb_pending_execution_is_finished: Tduckdb_pending_execution_is_finished;
  // Prepared Statements
  duckdb_prepare: Tduckdb_prepare;
  duckdb_destroy_prepare: Tduckdb_destroy_prepare;
  duckdb_prepare_error: Tduckdb_prepare_error;
  duckdb_nparams: Tduckdb_nparams;
  duckdb_parameter_name: Tduckdb_parameter_name;
  duckdb_param_type: Tduckdb_param_type;
  duckdb_clear_bindings: Tduckdb_clear_bindings;
  duckdb_bind_value: Tduckdb_bind_value;
  duckdb_bind_parameter_index: Tduckdb_bind_parameter_index;
  duckdb_bind_boolean: Tduckdb_bind_boolean;
  duckdb_bind_int8: Tduckdb_bind_int8;
  duckdb_bind_int16: Tduckdb_bind_int16;
  duckdb_bind_int32: Tduckdb_bind_int32;
  duckdb_bind_int64: Tduckdb_bind_int64;
  duckdb_bind_hugeint: Tduckdb_bind_hugeint;
  duckdb_bind_decimal: Tduckdb_bind_decimal;
  duckdb_bind_uint8: Tduckdb_bind_uint8;
  duckdb_bind_uint16: Tduckdb_bind_uint16;
  duckdb_bind_uint32: Tduckdb_bind_uint32;
  duckdb_bind_uint64: Tduckdb_bind_uint64;
  duckdb_bind_float: Tduckdb_bind_float;
  duckdb_bind_double: Tduckdb_bind_double;
  duckdb_bind_date: Tduckdb_bind_date;
  duckdb_bind_time: Tduckdb_bind_time;
  duckdb_bind_timestamp: Tduckdb_bind_timestamp;
  duckdb_bind_interval: Tduckdb_bind_interval;
  duckdb_bind_varchar: Tduckdb_bind_varchar;
  duckdb_bind_varchar_length: Tduckdb_bind_varchar_length;
  duckdb_bind_blob: Tduckdb_bind_blob;
  duckdb_bind_null: Tduckdb_bind_null;
  duckdb_execute_prepared: Tduckdb_execute_prepared;
  duckdb_execute_prepared_arrow: Tduckdb_execute_prepared_arrow;
  duckdb_arrow_scan: Tduckdb_arrow_scan;
  duckdb_arrow_array_scan: Tduckdb_arrow_array_scan;
  // Query Execution
  duckdb_query: Tduckdb_query;
  duckdb_destroy_result: Tduckdb_destroy_result;
  duckdb_column_name: Tduckdb_column_name;
  duckdb_column_type: Tduckdb_column_type;
  duckdb_column_logical_type: Tduckdb_column_logical_type;
  duckdb_column_count: Tduckdb_column_count;
  duckdb_row_count: Tduckdb_row_count;
  duckdb_rows_changed: Tduckdb_rows_changed;
  duckdb_column_data: Tduckdb_column_data;
  duckdb_nullmask_data: Tduckdb_nullmask_data;
  duckdb_result_error: Tduckdb_result_error;
  // Replacement Scans
  duckdb_add_replacement_scan: Tduckdb_add_replacement_scan;
  duckdb_replacement_scan_set_function_name: Tduckdb_replacement_scan_set_function_name;
  duckdb_replacement_scan_add_parameter: Tduckdb_replacement_scan_add_parameter;
  duckdb_replacement_scan_set_error: Tduckdb_replacement_scan_set_error;
  // Result Functions
  duckdb_result_get_chunk: Tduckdb_result_get_chunk;
  duckdb_result_is_streaming: Tduckdb_result_is_streaming;
  duckdb_result_chunk_count: Tduckdb_result_chunk_count;
  duckdb_value_boolean: Tduckdb_value_boolean;
  duckdb_value_int8: Tduckdb_value_int8;
  duckdb_value_int16: Tduckdb_value_int16;
  duckdb_value_int32: Tduckdb_value_int32;
  duckdb_value_int64: Tduckdb_value_int64;
  duckdb_value_hugeint: Tduckdb_value_hugeint;
  duckdb_value_decimal: Tduckdb_value_decimal;
  duckdb_value_uint8: Tduckdb_value_uint8;
  duckdb_value_uint16: Tduckdb_value_uint16;
  duckdb_value_uint32: Tduckdb_value_uint32;
  duckdb_value_uint64: Tduckdb_value_uint64;
  duckdb_value_float: Tduckdb_value_float;
  duckdb_value_double: Tduckdb_value_double;
  duckdb_value_date: Tduckdb_value_date;
  duckdb_value_time: Tduckdb_value_time;
  duckdb_value_timestamp: Tduckdb_value_timestamp;
  duckdb_value_interval: Tduckdb_value_interval;
  duckdb_value_varchar: Tduckdb_value_varchar;
  duckdb_value_string: Tduckdb_value_string;
  duckdb_value_varchar_internal: Tduckdb_value_varchar_internal;
  duckdb_value_string_internal: Tduckdb_value_string_internal;
  duckdb_value_blob: Tduckdb_value_blob;
  duckdb_value_is_null: Tduckdb_value_is_null;
  // Streaming Result Interface
  duckdb_stream_fetch_chunk: Tduckdb_stream_fetch_chunk;
  // Table Functions
  duckdb_create_table_function: Tduckdb_create_table_function;
  duckdb_destroy_table_function: Tduckdb_destroy_table_function;
  duckdb_table_function_set_name: Tduckdb_table_function_set_name;
  duckdb_table_function_add_parameter: Tduckdb_table_function_add_parameter;
  duckdb_table_function_add_named_parameter: Tduckdb_table_function_add_named_parameter;
  duckdb_table_function_set_extra_info: Tduckdb_table_function_set_extra_info;
  duckdb_table_function_set_bind: Tduckdb_table_function_set_bind;
  duckdb_table_function_set_init: Tduckdb_table_function_set_init;
  duckdb_table_function_set_local_init: Tduckdb_table_function_set_local_init;
  duckdb_table_function_set_function: Tduckdb_table_function_set_function;
  duckdb_table_function_supports_projection_pushdown: Tduckdb_table_function_supports_projection_pushdown;
  duckdb_register_table_function: Tduckdb_register_table_function;
  duckdb_bind_get_extra_info: Tduckdb_bind_get_extra_info;
  duckdb_bind_add_result_column: Tduckdb_bind_add_result_column;
  duckdb_bind_get_parameter_count: Tduckdb_bind_get_parameter_count;
  duckdb_bind_get_parameter: Tduckdb_bind_get_parameter;
  duckdb_bind_get_named_parameter: Tduckdb_bind_get_named_parameter;
  duckdb_bind_set_bind_data: Tduckdb_bind_set_bind_data;
  duckdb_bind_set_cardinality: Tduckdb_bind_set_cardinality;
  duckdb_bind_set_error: Tduckdb_bind_set_error;
  duckdb_init_get_extra_info: Tduckdb_init_get_extra_info;
  duckdb_init_get_bind_data: Tduckdb_init_get_bind_data;
  duckdb_init_set_init_data: Tduckdb_init_set_init_data;
  duckdb_init_get_column_count: Tduckdb_init_get_column_count;
  duckdb_init_get_column_index: Tduckdb_init_get_column_index;
  duckdb_init_set_max_threads: Tduckdb_init_set_max_threads;
  duckdb_init_set_error: Tduckdb_init_set_error;
  duckdb_function_get_extra_info: Tduckdb_function_get_extra_info;
  duckdb_function_get_bind_data: Tduckdb_function_get_bind_data;
  duckdb_function_get_init_data: Tduckdb_function_get_init_data;
  duckdb_function_get_local_init_data: Tduckdb_function_get_local_init_data;
  duckdb_function_set_error: Tduckdb_function_set_error;
  // Threading Information
  duckdb_execute_tasks: Tduckdb_execute_tasks;
  duckdb_create_task_state: Tduckdb_create_task_state;
  duckdb_execute_tasks_state: Tduckdb_execute_tasks_state;
  duckdb_execute_n_tasks_state: Tduckdb_execute_n_tasks_state;
  duckdb_finish_execution: Tduckdb_finish_execution;
  duckdb_task_state_is_finished: Tduckdb_task_state_is_finished;
  duckdb_destroy_task_state: Tduckdb_destroy_task_state;
  duckdb_execution_is_finished: Tduckdb_execution_is_finished;
  duckdb_validity_row_is_valid: Tduckdb_validity_row_is_valid;
  duckdb_validity_set_row_validity: Tduckdb_validity_set_row_validity;
  duckdb_validity_set_row_invalid: Tduckdb_validity_set_row_invalid;
  duckdb_validity_set_row_valid: Tduckdb_validity_set_row_valid;
  // Value Interface
  duckdb_destroy_value: Tduckdb_destroy_value;
  duckdb_create_varchar: Tduckdb_create_varchar;
  duckdb_create_varchar_length: Tduckdb_create_varchar_length;
  duckdb_create_int64: Tduckdb_create_int64;
  duckdb_get_varchar: Tduckdb_get_varchar;
  duckdb_get_int64: Tduckdb_get_int64;
  // Vector Interface
  duckdb_vector_get_column_type: Tduckdb_vector_get_column_type;
  duckdb_vector_get_data: Tduckdb_vector_get_data;
  duckdb_vector_get_validity: Tduckdb_vector_get_validity;
  duckdb_vector_ensure_validity_writable: Tduckdb_vector_ensure_validity_writable;
  duckdb_vector_assign_string_element: Tduckdb_vector_assign_string_element;
  duckdb_vector_assign_string_element_len: Tduckdb_vector_assign_string_element_len;
  duckdb_list_vector_get_child: Tduckdb_list_vector_get_child;
  duckdb_list_vector_get_size: Tduckdb_list_vector_get_size;
  duckdb_list_vector_set_size: Tduckdb_list_vector_set_size;
  duckdb_list_vector_reserve: Tduckdb_list_vector_reserve;
  duckdb_struct_vector_get_child: Tduckdb_struct_vector_get_child;
{$endif}

{ end of include file }

