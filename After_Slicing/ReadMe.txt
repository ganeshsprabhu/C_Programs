Slicing command used:
frama-c -load-module slicing Poc_Program.c -main p -slice-value p:output -then-on 'Slicing export' -print -ocode Poc_Program_Sliced.c 
frama-c -load-module slicing Poc_Program.c -main p -slice-value p:output -slicing-level 3 -then-on 'Slicing export' -print -ocode Poc_Program_Sliced.c

Slicing based on pragma:
frama-c -load-module slicing Poc_Program_2.c -main p -slice-pragma p -then-on 'Slicing export' -print -ocode Poc_Program_2_Sliced.c
