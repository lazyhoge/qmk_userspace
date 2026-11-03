{
  description = "自分用の QMK キーマップ（7sKB）。Cornix（ZMK）に寄せてある";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      # qmk の CLI と、AVR（7sKB の Pro Micro）向けのコンパイラと書き込みツール
      devShells.${system}.default = pkgs.mkShell {
        # qmk_firmware の置き場所（qmk の既定は ~/qmk_firmware）
        shellHook = ''
          export QMK_HOME="''${QMK_HOME:-$HOME/src/qmk_firmware}"
        '';
        packages = [
          pkgs.qmk
          pkgs.pkgsCross.avr.buildPackages.gcc
          pkgs.avrdude
          pkgs.gnumake
          pkgs.git
        ];
      };
    };
}
