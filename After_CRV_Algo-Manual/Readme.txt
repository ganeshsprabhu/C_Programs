CMBC command used:
cbmc --unwind 20  poc_program.c

Result obtained:
** Results:
poc_program.c function main
[main.assertion.1] line 82 CRV Result for x => if,SUCCESS then its not a CRV and if FAILURE then its a CRV!: FAILURE
[main.assertion.2] line 85 CRV Result for y => if,SUCCESS then its not a CRV and if FAILURE then its a CRV!: SUCCESS

** 1 of 2 failed (2 iterations)
VERIFICATION FAILED


cbmc poc_program3.c --unwind 20 --trace  | grep -i Vio
[analyze_crv.assertion.1] line 80 Violation due to x: FAILURE
[analyze_crv.assertion.2] line 81 Violation due to y: SUCCESS
Violation due to X: Original X=9, Flipped X=13, Bit Position=2

cbmc poc_program3.c --unwind 20 
poc_program3.c function analyze_crv
[analyze_crv.assertion.1] line 80 Violation due to x: FAILURE
[analyze_crv.assertion.2] line 81 Violation due to y: SUCCESS
