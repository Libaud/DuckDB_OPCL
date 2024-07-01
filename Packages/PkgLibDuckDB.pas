{ This file was automatically created by Lazarus or Typhon IDE. Do not edit!
  This source is only used to compile and install the package.
 }

unit PkgLibDuckDB;

{$warn 5023 off : no warning about unused units}
interface

uses
  DuckDBAPI, TyphonPackageIntf;

implementation

procedure Register;
begin
end;

initialization
  RegisterPackage('PkgLibDuckDB', @Register);
end.
