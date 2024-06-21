
const
  DUCKDB_API_LATEST = 2;

  {$ifdef LINUX}
  LIBDDB = 'libduckdb.so';
  {$endif}

  {$ifdef MSWINDOWS}
  LIBDDB = 'duckdb.dll';
  {$endif}

  {$ifdef DARWIN}
  LIBDDB = 'libduckdb.dylib';
  {$endif}


