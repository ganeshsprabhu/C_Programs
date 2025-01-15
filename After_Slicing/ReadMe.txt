Slicing command used:
frama-c -load-module slicing Poc_Program.c -main p -slice-value p:output -then-on 'Slicing export' -print -ocode Poc_Program_Sliced.c 
frama-c -load-module slicing Poc_Program.c -main p -slice-value p:output -slicing-level 3 -then-on 'Slicing export' -print -ocode Poc_Program_Sliced.c

Slicing based on pragma:
frama-c -load-module slicing Poc_Program_2.c -main p -slice-pragma p -then-on 'Slicing export' -print -ocode Poc_Program_2_Sliced.c


Slicing based on assert:
frama-c -load-module slicing Poc_Program_3.c -main p -slice-assert p -print -ocode Poc_Program_3_Sliced.c 


Installation Steps:
sudo apt-get install opam
opam init
eval $(opam env --switch=default)
opam install frama-c
sudo apt install ocaml-dune
eval $(opam env)
Source : https://frama-c.com/html/get-frama-c.html

Slicing command used: frama-c sample_prg1.c -slice-value temperature  -then-on 'Slicing export' -print -ocode slice.c
doc: https://frama-c.com/fc-plugins/slicing.html

