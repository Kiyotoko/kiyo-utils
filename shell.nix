{ pkgs ? import <nixpkgs>{} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    # Build tools
    valgrind
    cmake
  ];
}
