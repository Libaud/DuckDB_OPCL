{========================================================================================
  Include : DynamicDuckDB
  Description : Dynamic load of duckdb lib
  Author : Frédéric Libaud
  **************************************************************************************
  History
  --------------------------------------------------------------------------------------
  2024-06-21 Migration of duckdb.h
========================================================================================}

{$ifdef DYNAMIC_LOAD}
const
  NilHandle = 0;

var
  DDDBLibraryHandle: TLibHandle;
  DDBDefaultLibraryName: String = LIBDDB;
  DDBLoadedLibraryName: UnicodeString;
  DDBLibRefCount: Integer;
{$endif}

{$ifdef DYNAMIC_CALL}
procedure LoadAddresses(aLibHandle: TLibHandle);
begin
  pointer(duckdb_open):= GetProcedureAddress(aLibHandle, 'duckdb_open');
  pointer(duckdb_open_ext):= GetProcedureAddress(aLibHandle, 'duckdb_open_ext');
  pointer(duckdb_close):= GetProcedureAddress(aLibHandle, 'duckdb_close');
  pointer(duckdb_connect):= GetProcedureAddress(aLibHandle, 'duckdb_connect');
  pointer(duckdb_disconnect):= GetProcedureAddress(aLibHandle, 'duckdb_disconnect');
  pointer(duckdb_library_version):= GetProcedureAddress(aLibHandle, 'duckdb_library_version');
  pointer(duckdb_create_config):= GetProcedureAddress(aLibHandle, 'duckdb_create_config');
  pointer(duckdb_config_count):= GetProcedureAddress(aLibHandle, 'duckdb_config_count');
  pointer(duckdb_get_config_flag):= GetProcedureAddress(aLibHandle, 'duckdb_get_config_flag');
  pointer(duckdb_set_config):= GetProcedureAddress(aLibHandle, 'duckdb_set_config');
  pointer(duckdb_destroy_config):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_config');
  pointer(duckdb_query):= GetProcedureAddress(aLibHandle, 'duckdb_query');
  pointer(duckdb_destroy_result):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_result');
  pointer(duckdb_column_name):= GetProcedureAddress(aLibHandle, 'duckdb_column_name');
  pointer(duckdb_column_type):= GetProcedureAddress(aLibHandle, 'duckdb_column_type');
  pointer(duckdb_column_logical_type):= GetProcedureAddress(aLibHandle, 'duckdb_column_logical_type');
  pointer(duckdb_column_count):= GetProcedureAddress(aLibHandle, 'duckdb_column_count');
  pointer(duckdb_row_count):= GetProcedureAddress(aLibHandle, 'duckdb_row_count');
  pointer(duckdb_rows_changed):= GetProcedureAddress(aLibHandle, 'duckdb_rows_changed');
  pointer(duckdb_column_data):= GetProcedureAddress(aLibHandle, 'duckdb_column_data');
  pointer(duckdb_nullmask_data):= GetProcedureAddress(aLibHandle, 'duckdb_nullmask_data');
  pointer(duckdb_result_error):= GetProcedureAddress(aLibHandle, 'duckdb_result_error');
  pointer(duckdb_result_get_chunk):= GetProcedureAddress(aLibHandle, 'duckdb_result_get_chunk');
  pointer(duckdb_result_is_streaming):= GetProcedureAddress(aLibHandle, 'duckdb_result_is_streaming');
  pointer(duckdb_result_chunk_count):= GetProcedureAddress(aLibHandle, 'duckdb_result_chunk_count');
  pointer(duckdb_value_boolean):= GetProcedureAddress(aLibHandle, 'duckdb_value_boolean');
  pointer(duckdb_value_int8):= GetProcedureAddress(aLibHandle, 'duckdb_value_int8');
  pointer(duckdb_value_int16):= GetProcedureAddress(aLibHandle, 'duckdb_value_int16');
  pointer(duckdb_value_int32):= GetProcedureAddress(aLibHandle, 'duckdb_value_int32');
  pointer(duckdb_value_int64):= GetProcedureAddress(aLibHandle, 'duckdb_value_int64');
  pointer(duckdb_value_hugeint):= GetProcedureAddress(aLibHandle, 'duckdb_value_hugeint');
  pointer(duckdb_value_decimal):= GetProcedureAddress(aLibHandle, 'duckdb_value_decimal');
  pointer(duckdb_value_uint8):= GetProcedureAddress(aLibHandle, 'duckdb_value_uint8');
  pointer(duckdb_value_uint16):= GetProcedureAddress(aLibHandle, 'duckdb_value_uint16');
  pointer(duckdb_value_uint32):= GetProcedureAddress(aLibHandle, 'duckdb_value_uint32');
  pointer(duckdb_value_uint64):= GetProcedureAddress(aLibHandle, 'duckdb_value_uint64');
  pointer(duckdb_value_float):= GetProcedureAddress(aLibHandle, 'duckdb_value_float');
  pointer(duckdb_value_double):= GetProcedureAddress(aLibHandle, 'duckdb_value_double');
  pointer(duckdb_value_date):= GetProcedureAddress(aLibHandle, 'duckdb_value_date');
  pointer(duckdb_value_time):= GetProcedureAddress(aLibHandle, 'duckdb_value_time');
  pointer(duckdb_value_timestamp):= GetProcedureAddress(aLibHandle, 'duckdb_value_timestamp');
  pointer(duckdb_value_interval):= GetProcedureAddress(aLibHandle, 'duckdb_value_interval');
  pointer(duckdb_value_varchar):= GetProcedureAddress(aLibHandle, 'duckdb_value_varchar');
  pointer(duckdb_value_string):= GetProcedureAddress(aLibHandle, 'duckdb_value_string');
  pointer(duckdb_value_varchar_internal):= GetProcedureAddress(aLibHandle, 'duckdb_value_varchar_internal');
  pointer(duckdb_value_string_internal):= GetProcedureAddress(aLibHandle, 'duckdb_value_string_internal');
  pointer(duckdb_value_blob):= GetProcedureAddress(aLibHandle, 'duckdb_value_blob');
  pointer(duckdb_value_is_null):= GetProcedureAddress(aLibHandle, 'duckdb_value_is_null');
  pointer(duckdb_malloc):= GetProcedureAddress(aLibHandle, 'duckdb_malloc');
  pointer(duckdb_free):= GetProcedureAddress(aLibHandle, 'duckdb_free');
  pointer(duckdb_vector_size):= GetProcedureAddress(aLibHandle, 'duckdb_vector_size');
  pointer(duckdb_string_is_inlined):= GetProcedureAddress(aLibHandle, 'duckdb_string_is_inlined');
  pointer(duckdb_from_date):= GetProcedureAddress(aLibHandle, 'duckdb_from_date');
  pointer(duckdb_to_date):= GetProcedureAddress(aLibHandle, 'duckdb_to_date');
  pointer(duckdb_from_time):= GetProcedureAddress(aLibHandle, 'duckdb_from_time');
  pointer(duckdb_to_time):= GetProcedureAddress(aLibHandle, 'duckdb_to_time');
  pointer(duckdb_from_timestamp):= GetProcedureAddress(aLibHandle, 'duckdb_from_timestamp');
  pointer(duckdb_to_timestamp):= GetProcedureAddress(aLibHandle, 'duckdb_to_timestamp');
  pointer(duckdb_hugeint_to_double):= GetProcedureAddress(aLibHandle, 'duckdb_hugeint_to_double');
  pointer(duckdb_double_to_hugeint):= GetProcedureAddress(aLibHandle, 'duckdb_double_to_hugeint');
  pointer(duckdb_double_to_decimal):= GetProcedureAddress(aLibHandle, 'duckdb_double_to_decimal');
  pointer(duckdb_decimal_to_double):= GetProcedureAddress(aLibHandle, 'duckdb_decimal_to_double');
  pointer(duckdb_prepare):= GetProcedureAddress(aLibHandle, 'duckdb_prepare');
  pointer(duckdb_destroy_prepare):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_prepare');
  pointer(duckdb_prepare_error):= GetProcedureAddress(aLibHandle, 'duckdb_prepare_error');
  pointer(duckdb_nparams):= GetProcedureAddress(aLibHandle, 'duckdb_nparams');
  pointer(duckdb_param_type):= GetProcedureAddress(aLibHandle, 'duckdb_param_type');
  pointer(duckdb_clear_bindings):= GetProcedureAddress(aLibHandle, 'duckdb_clear_bindings');
  pointer(duckdb_bind_boolean):= GetProcedureAddress(aLibHandle, 'duckdb_bind_boolean');
  pointer(duckdb_bind_int8):= GetProcedureAddress(aLibHandle, 'duckdb_bind_int8');
  pointer(duckdb_bind_int16):= GetProcedureAddress(aLibHandle, 'duckdb_bind_int16');
  pointer(duckdb_bind_int32):= GetProcedureAddress(aLibHandle, 'duckdb_bind_int32');
  pointer(duckdb_bind_int64):= GetProcedureAddress(aLibHandle, 'duckdb_bind_int64');
  pointer(duckdb_bind_hugeint):= GetProcedureAddress(aLibHandle, 'duckdb_bind_hugeint');
  pointer(duckdb_bind_decimal):= GetProcedureAddress(aLibHandle, 'duckdb_bind_decimal');
  pointer(duckdb_bind_uint8):= GetProcedureAddress(aLibHandle, 'duckdb_bind_uint8');
  pointer(duckdb_bind_uint16):= GetProcedureAddress(aLibHandle, 'duckdb_bind_uint16');
  pointer(duckdb_bind_uint32):= GetProcedureAddress(aLibHandle, 'duckdb_bind_uint32');
  pointer(duckdb_bind_uint64):= GetProcedureAddress(aLibHandle, 'duckdb_bind_uint64');
  pointer(duckdb_bind_float):= GetProcedureAddress(aLibHandle, 'duckdb_bind_float');
  pointer(duckdb_bind_double):= GetProcedureAddress(aLibHandle, 'duckdb_bind_double');
  pointer(duckdb_bind_date):= GetProcedureAddress(aLibHandle, 'duckdb_bind_date');
  pointer(duckdb_bind_time):= GetProcedureAddress(aLibHandle, 'duckdb_bind_time');
  pointer(duckdb_bind_interval):= GetProcedureAddress(aLibHandle, 'duckdb_bind_interval');
  pointer(duckdb_bind_varchar):= GetProcedureAddress(aLibHandle, 'duckdb_bind_varchar');
  pointer(duckdb_bind_varchar_length):= GetProcedureAddress(aLibHandle, 'duckdb_bind_varchar_length');
  pointer(duckdb_bind_blob):= GetProcedureAddress(aLibHandle, 'duckdb_bind_blob');
  pointer(duckdb_bind_null):= GetProcedureAddress(aLibHandle, 'duckdb_bind_null');
  pointer(duckdb_execute_prepared):= GetProcedureAddress(aLibHandle, 'duckdb_execute_prepared');
  pointer(duckdb_execute_prepared_arrow):= GetProcedureAddress(aLibHandle, 'duckdb_execute_prepared_arrow');
  pointer(duckdb_extract_statements):= GetProcedureAddress(aLibHandle, 'duckdb_extract_statements');
  pointer(duckdb_prepare_extracted_statement):= GetProcedureAddress(aLibHandle, 'duckdb_prepare_extracted_statement');
  pointer(duckdb_extract_statements_error):= GetProcedureAddress(aLibHandle, 'duckdb_extract_statements_error');
  pointer(duckdb_destroy_extracted):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_extracted');
  pointer(duckdb_pending_prepared):= GetProcedureAddress(aLibHandle, 'duckdb_pending_prepared');
  pointer(duckdb_pending_prepared_streaming):= GetProcedureAddress(aLibHandle, 'duckdb_pending_prepared_streaming');
  pointer(duckdb_destroy_pending):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_pending');
  pointer(duckdb_pending_error):= GetProcedureAddress(aLibHandle, 'duckdb_pending_error');
  pointer(duckdb_pending_execute_task):= GetProcedureAddress(aLibHandle, 'duckdb_pending_execute_task');
  pointer(duckdb_execute_pending):= GetProcedureAddress(aLibHandle, 'duckdb_execute_pending');
  pointer(duckdb_destroy_value):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_value');
  pointer(duckdb_create_varchar):= GetProcedureAddress(aLibHandle, 'duckdb_create_varchar');
  pointer(duckdb_create_varchar_length):= GetProcedureAddress(aLibHandle, 'duckdb_create_varchar_length');
  pointer(duckdb_create_int64):= GetProcedureAddress(aLibHandle, 'duckdb_create_int64');
  pointer(duckdb_get_varchar):= GetProcedureAddress(aLibHandle, 'duckdb_get_varchar');
  pointer(duckdb_get_int64):= GetProcedureAddress(aLibHandle, 'duckdb_get_int64');
  pointer(duckdb_create_logical_type):= GetProcedureAddress(aLibHandle, 'duckdb_create_logical_type');
  pointer(duckdb_create_list_type):= GetProcedureAddress(aLibHandle, 'duckdb_create_list_type');
  pointer(duckdb_create_map_type):= GetProcedureAddress(aLibHandle, 'duckdb_create_map_type');
  pointer(duckdb_create_union_type):= GetProcedureAddress(aLibHandle, 'duckdb_create_union_type');
  pointer(duckdb_create_decimal_type):= GetProcedureAddress(aLibHandle, 'duckdb_create_decimal_type');
  pointer(duckdb_get_type_id):= GetProcedureAddress(aLibHandle, 'duckdb_get_type_id');
  pointer(duckdb_decimal_width):= GetProcedureAddress(aLibHandle, 'duckdb_decimal_width');
  pointer(duckdb_decimal_scale):= GetProcedureAddress(aLibHandle, 'duckdb_decimal_scale');
  pointer(duckdb_decimal_internal_type):= GetProcedureAddress(aLibHandle, 'duckdb_decimal_internal_type');
  pointer(duckdb_enum_internal_type):= GetProcedureAddress(aLibHandle, 'duckdb_enum_internal_type');
  pointer(duckdb_enum_dictionary_size):= GetProcedureAddress(aLibHandle, 'duckdb_enum_dictionary_size');
  pointer(duckdb_enum_dictionary_value):= GetProcedureAddress(aLibHandle, 'duckdb_enum_dictionary_value');
  pointer(duckdb_list_type_child_type):= GetProcedureAddress(aLibHandle, 'duckdb_list_type_child_type');
  pointer(duckdb_map_type_key_type):= GetProcedureAddress(aLibHandle, 'duckdb_map_type_key_type');
  pointer(duckdb_map_type_value_type):= GetProcedureAddress(aLibHandle, 'duckdb_map_type_value_type');
  pointer(duckdb_struct_type_child_count):= GetProcedureAddress(aLibHandle, 'duckdb_struct_type_child_count');
  pointer(duckdb_struct_type_child_name):= GetProcedureAddress(aLibHandle, 'duckdb_struct_type_child_name');
  pointer(duckdb_struct_type_child_type):= GetProcedureAddress(aLibHandle, 'duckdb_struct_type_child_type');
  pointer(duckdb_union_type_member_count):= GetProcedureAddress(aLibHandle, 'duckdb_union_type_member_count');
  pointer(duckdb_union_type_member_name):= GetProcedureAddress(aLibHandle, 'duckdb_union_type_member_name');
  pointer(duckdb_union_type_member_type):= GetProcedureAddress(aLibHandle, 'duckdb_union_type_member_type');
  pointer(duckdb_destroy_logical_type):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_logical_type');
  pointer(duckdb_create_data_chunk):= GetProcedureAddress(aLibHandle, 'duckdb_create_data_chunk');
  pointer(duckdb_destroy_data_chunk):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_data_chunk');
  pointer(duckdb_data_Chunk_reset):= GetProcedureAddress(aLibHandle, 'duckdb_data_Chunk_reset');
  pointer(duckdb_data_chunk_get_column_count):= GetProcedureAddress(aLibHandle, 'duckdb_data_chunk_get_column_count');
  pointer(duckdb_data_chunk_get_vector):= GetProcedureAddress(aLibHandle, 'duckdb_data_chunk_get_vector');
  pointer(duckdb_data_chunk_get_size):= GetProcedureAddress(aLibHandle, 'duckdb_data_chunk_get_size');
  pointer(duckdb_data_chunk_set_size):= GetProcedureAddress(aLibHandle, 'duckdb_data_chunk_set_size');
  pointer(duckdb_vector_get_column_type):= GetProcedureAddress(aLibHandle, 'duckdb_vector_get_column_type');
  pointer(duckdb_vector_get_data):= GetProcedureAddress(aLibHandle, 'duckdb_vector_get_data');
  pointer(duckdb_vector_get_validity):= GetProcedureAddress(aLibHandle, 'duckdb_vector_get_validity');
  pointer(duckdb_vector_ensure_validity_writable):= GetProcedureAddress(aLibHandle, 'duckdb_vector_ensure_validity_writable');
  pointer(duckdb_vector_assign_string_element):= GetProcedureAddress(aLibHandle, 'duckdb_vector_assign_string_element');
  pointer(duckdb_vector_assign_string_element_len):= GetProcedureAddress(aLibHandle, 'duckdb_vector_assign_string_element_len');
  pointer(duckdb_list_vector_get_child):= GetProcedureAddress(aLibHandle, 'duckdb_list_vector_get_child');
  pointer(duckdb_list_vector_get_size):= GetProcedureAddress(aLibHandle, 'duckdb_list_vector_get_size');
  pointer(duckdb_list_vector_reserve):= GetProcedureAddress(aLibHandle, 'duckdb_list_vector_reserve');
  pointer(duckdb_struct_vector_get_child):= GetProcedureAddress(aLibHandle, 'duckdb_struct_vector_get_child');
  pointer(duckdb_validity_row_is_valid):= GetProcedureAddress(aLibHandle, 'duckdb_validity_row_is_valid');
  pointer(duckdb_validity_set_row_validity):= GetProcedureAddress(aLibHandle, 'duckdb_validity_set_row_validity');
  pointer(duckdb_validity_set_row_invalid):= GetProcedureAddress(aLibHandle, 'duckdb_validity_set_row_invalid');
  pointer(duckdb_validity_set_row_valid):= GetProcedureAddress(aLibHandle, 'duckdb_validity_set_row_valid');
  pointer(duckdb_create_table_function):= GetProcedureAddress(aLibHandle, 'duckdb_create_table_function');
  pointer(duckdb_destroy_table_function):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_table_function');
  pointer(duckdb_table_function_set_name):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_set_name');
  pointer(duckdb_table_function_add_parameter):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_add_parameter');
  pointer(duckdb_table_function_add_named_parameter):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_add_named_parameter');
  pointer(duckdb_table_function_set_extra_info):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_set_extra_info');
  pointer(duckdb_table_function_set_bind):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_set_bind');
  pointer(duckdb_table_function_set_init):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_set_init');
  pointer(duckdb_table_function_set_local_init):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_set_local_init');
  pointer(duckdb_table_function_set_function):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_set_function');
  pointer(duckdb_table_function_supports_projection_pushdown):= GetProcedureAddress(aLibHandle, 'duckdb_table_function_supports_projection_pushdown');
  pointer(duckdb_register_table_function):= GetProcedureAddress(aLibHandle, 'duckdb_register_table_function');
  pointer(duckdb_bind_get_extra_info):= GetProcedureAddress(aLibHandle, 'duckdb_bind_get_extra_info');
  pointer(duckdb_bind_add_result_column):= GetProcedureAddress(aLibHandle, 'duckdb_bind_add_result_column');
  pointer(duckdb_bind_get_parameter_count):= GetProcedureAddress(aLibHandle, 'duckdb_bind_get_parameter_count');
  pointer(duckdb_bind_get_parameter):= GetProcedureAddress(aLibHandle, 'duckdb_bind_get_parameter');
  pointer(duckdb_bind_get_named_parameter):= GetProcedureAddress(aLibHandle, 'duckdb_bind_get_named_parameter');
  pointer(duckdb_bind_set_bind_data):= GetProcedureAddress(aLibHandle, 'duckdb_bind_set_bind_data');
  pointer(duckdb_bind_set_cardinality):= GetProcedureAddress(aLibHandle, 'duckdb_bind_set_cardinality');
  pointer(duckdb_bind_set_error):= GetProcedureAddress(aLibHandle, 'duckdb_bind_set_error');
  pointer(duckdb_init_get_extra_info):= GetProcedureAddress(aLibHandle, 'duckdb_init_get_extra_info');
  pointer(duckdb_init_get_bind_data):= GetProcedureAddress(aLibHandle, 'duckdb_init_get_bind_data');
  pointer(duckdb_init_set_init_data):= GetProcedureAddress(aLibHandle, 'duckdb_init_set_init_data');
  pointer(duckdb_init_get_column_count):= GetProcedureAddress(aLibHandle, 'duckdb_init_get_column_count');
  pointer(duckdb_init_get_column_index):= GetProcedureAddress(aLibHandle, 'duckdb_init_get_column_index');
  pointer(duckdb_init_set_max_threads):= GetProcedureAddress(aLibHandle, 'duckdb_init_set_max_threads');
  pointer(duckdb_init_set_error):= GetProcedureAddress(aLibHandle, 'duckdb_init_set_error');
  pointer(duckdb_function_get_extra_info):= GetProcedureAddress(aLibHandle, 'duckdb_function_get_extra_info');
  pointer(duckdb_function_get_bind_data):= GetProcedureAddress(aLibHandle, 'duckdb_function_get_bind_data');
  pointer(duckdb_function_get_init_data):= GetProcedureAddress(aLibHandle, 'duckdb_function_get_init_data');
  pointer(duckdb_function_get_local_init_data):= GetProcedureAddress(aLibHandle, 'duckdb_function_get_local_init_data');
  pointer(duckdb_function_set_error):= GetProcedureAddress(aLibHandle, 'duckdb_function_set_error');
  pointer(duckdb_add_replacement_scan):= GetProcedureAddress(aLibHandle, 'duckdb_add_replacement_scan');
  pointer(duckdb_replacement_scan_set_function_name):= GetProcedureAddress(aLibHandle, 'duckdb_replacement_scan_set_function_name');
  pointer(duckdb_replacement_scan_add_parameter):= GetProcedureAddress(aLibHandle, 'duckdb_replacement_scan_add_parameter');
  pointer(duckdb_replacement_scan_set_error):= GetProcedureAddress(aLibHandle, 'duckdb_replacement_scan_set_error');
  pointer(duckdb_appender_create):= GetProcedureAddress(aLibHandle, 'duckdb_appender_create');
  pointer(duckdb_appender_error):= GetProcedureAddress(aLibHandle, 'duckdb_appender_error');
  pointer(duckdb_appender_flush):= GetProcedureAddress(aLibHandle, 'duckdb_appender_flush');
  pointer(duckdb_appender_close):= GetProcedureAddress(aLibHandle, 'duckdb_appender_close');
  pointer(duckdb_appender_destroy):= GetProcedureAddress(aLibHandle, 'duckdb_appender_destroy');
  pointer(duckdb_appender_begin_row):= GetProcedureAddress(aLibHandle, 'duckdb_appender_begin_row');
  pointer(duckdb_appender_end_row):= GetProcedureAddress(aLibHandle, 'duckdb_appender_end_row');
  pointer(duckdb_append_bool):= GetProcedureAddress(aLibHandle, 'duckdb_append_bool');
  pointer(duckdb_append_int8):= GetProcedureAddress(aLibHandle, 'duckdb_append_int8');
  pointer(duckdb_append_int16):= GetProcedureAddress(aLibHandle, 'duckdb_append_int16');
  pointer(duckdb_append_int32):= GetProcedureAddress(aLibHandle, 'duckdb_append_int32');
  pointer(duckdb_append_int64):= GetProcedureAddress(aLibHandle, 'duckdb_append_int64');
  pointer(duckdb_append_hugeint):= GetProcedureAddress(aLibHandle, 'duckdb_append_hugeint');
  pointer(duckdb_append_uint16):= GetProcedureAddress(aLibHandle, 'duckdb_append_uint16');
  pointer(duckdb_append_uint32):= GetProcedureAddress(aLibHandle, 'duckdb_append_uint32');
  pointer(duckdb_append_uint64):= GetProcedureAddress(aLibHandle, 'duckdb_append_uint64');
  pointer(duckdb_append_float):= GetProcedureAddress(aLibHandle, 'duckdb_append_float');
  pointer(duckdb_append_double):= GetProcedureAddress(aLibHandle, 'duckdb_append_double');
  pointer(duckdb_append_date):= GetProcedureAddress(aLibHandle, 'duckdb_append_date');
  pointer(duckdb_append_time):= GetProcedureAddress(aLibHandle, 'duckdb_append_time');
  pointer(duckdb_append_timestamp):= GetProcedureAddress(aLibHandle, 'duckdb_append_timestamp');
  pointer(duckdb_append_interval):= GetProcedureAddress(aLibHandle, 'duckdb_append_interval');
  pointer(duckdb_append_varchar):= GetProcedureAddress(aLibHandle, 'duckdb_append_varchar');
  pointer(duckdb_append_varchar_length):= GetProcedureAddress(aLibHandle, 'duckdb_append_varchar_length');
  pointer(duckdb_append_blob):= GetProcedureAddress(aLibHandle, 'duckdb_append_blob');
  pointer(duckdb_append_null):= GetProcedureAddress(aLibHandle, 'duckdb_append_null');
  pointer(duckdb_append_data_chunk):= GetProcedureAddress(aLibHandle, 'duckdb_append_data_chunk');
  pointer(duckdb_query_arrow):= GetProcedureAddress(aLibHandle, 'duckdb_query_arrow');
  pointer(duckdb_query_arrow_schema):= GetProcedureAddress(aLibHandle, 'duckdb_query_arrow_schema');
  pointer(duckdb_query_arrow_array):= GetProcedureAddress(aLibHandle, 'duckdb_query_arrow_array');
  pointer(duckdb_arrow_column_count):= GetProcedureAddress(aLibHandle, 'duckdb_arrow_column_count');
  pointer(duckdb_arrow_row_count):= GetProcedureAddress(aLibHandle, 'duckdb_arrow_row_count');
  pointer(duckdb_arrow_rows_changed):= GetProcedureAddress(aLibHandle, 'duckdb_arrow_rows_changed');
  pointer(duckdb_query_arrow_error):= GetProcedureAddress(aLibHandle, 'duckdb_query_arrow_error');
  pointer(duckdb_destroy_arrow):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_arrow');
  pointer(duckdb_execute_tasks):= GetProcedureAddress(aLibHandle, 'duckdb_execute_tasks');
  pointer(duckdb_create_task_state):= GetProcedureAddress(aLibHandle, 'duckdb_create_task_state');
  pointer(duckdb_execute_tasks_state):= GetProcedureAddress(aLibHandle, 'duckdb_execute_tasks_state');
  pointer(duckdb_execute_n_tasks_state):= GetProcedureAddress(aLibHandle, 'duckdb_execute_n_tasks_state');
  pointer(duckdb_finish_execution):= GetProcedureAddress(aLibHandle, 'duckdb_finish_execution');
  pointer(duckdb_task_state_is_finished):= GetProcedureAddress(aLibHandle, 'duckdb_task_state_is_finished');
  pointer(duckdb_destroy_task_state):= GetProcedureAddress(aLibHandle, 'duckdb_destroy_task_state');
  pointer(duckdb_execution_is_finished):= GetProcedureAddress(aLibHandle, 'duckdb_execution_is_finished');
  pointer(duckdb_stream_fetch_chunk):= GetProcedureAddress(aLibHandle, 'duckdb_stream_fetch_chunk');
end;
{$endif}

{$ifdef DYNAMIC_LOAD}

function TryInitializeDDBLibrary(const aLibraryName: UnicodeString): integer;
var
  N: UnicodeString;
begin
  N:= aLibraryName;
  if (N = '') then
    N:= DDBDefaultLibraryName;
  result:= InterlockedIncrement(DDBLibRefCount);
  if result  = 1 then
  begin
    DDDBLibraryHandle := LoadLibrary(N);
    if (DDDBLibraryHandle = NilHandle) then
    begin
      DDBLibRefCount := 0;
      Exit(-1);
    end;
    DDBLoadedLibraryName := N;
    {$ifdef DYNAMIC_CALL}
    LoadAddresses(DDDBLibraryHandle);
    {$endif}
  end;
end;

function InitializeDDBLibrary(const aLibraryName: UnicodeString): integer;
begin
  if (aLibraryName<>'') and (DDBLoadedLibraryName <> '') and (DDBLoadedLibraryName <> aLibraryName) then
    raise EDuckDBAPI.CreateFmt(SErrAlreadyLoaded, [DDBLoadedLibraryName]);
  result:= TryInitializeDDBLibrary(aLibraryName);
  if result= -1 then
    if aLibraryName = '' then
      raise EDuckDBAPI.CreateFmt(SErrLoadFailed, [DDBDefaultLibraryName])
    else
      raise EDuckDBAPI.CreateFmt(SErrLoadFailed, [aLibraryName]);
end;

function InitializeDDBLibraryANSI(const aLibraryName: AnsiString): integer;
begin
  Result:= InitializeDDBLibrary(aLibraryName);
end;

function InitializeDDBLibrary: integer;
begin
  Result:= InitializeDDBLibrary(DDBDefaultLibraryName);
end;

procedure ReleaseDDBLibrary;
begin
  if InterlockedDecrement(DDBLibRefCount) <= 0 then
  begin
    if DDDBLibraryHandle <> NilHandle then
      UnloadLibrary(DDDBLibraryHandle);
    DDDBLibraryHandle := NilHandle;
    DDBDefaultLibraryName := '';
    DDBLibRefCount := 0;
  end;
end;

{$endif}

