Slicing command used:
frama-c -load-module slicing Poc_Program.c -main p -slice-value p:output -then-on 'Slicing export' -print -ocode Poc_Program_Sliced.c 