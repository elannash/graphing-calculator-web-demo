# Work Report

## Name: <ins> Elan Nash </ins>

## Demonstration:
[![](https://img.youtube.com/vi/_3SSteiAhVM/0.jpg)](https://www.youtube.com/watch?v=_3SSteiAhVM)

## Features:

- Not Implemented:
  - grid lines & thicker axes
  - better way to delete functions from sidebar
  - zoom into mouse point rather than origin

<br><br>

- Implemented:
  - menu
  - interactive sidebar
  - save/load functionality
  - zoom/pan
  - all the functions I could think of

<br><br>

- Bugs
  - zooming out to a very large domain results in very odd behavior with the graph & axes, which I still do not completely understand.
    > doesn't seem to be an issue with zooming in
  - unary operator will not work inside two arg functions I.e MAX(X, -2). RPN will view this as MAX(X-2).
    > could fix in a very non-elegant way, but I don't want to gunk up my tokenizer ever more

<br><br>

# testB.cpp output:

<pre>
----------running testB.cpp---------


[==========] Running 5 tests from 5 test suites.
[----------] Global test environment set-up.
[----------] 1 test from TEST_RPN
[ RUN      ] TEST_RPN.TestRpn
RPN SUCCESSFULLY EVALUATED INPUTS.
[       OK ] TEST_RPN.TestRpn (0 ms)
[----------] 1 test from TEST_RPN (0 ms total)

[----------] 1 test from TEST_SHUNTING_YARD
[ RUN      ] TEST_SHUNTING_YARD.TestShuntingYard
SHUNTING YARD SUCCESSFULLY TRANSLATED TO POSTFIX.
[       OK ] TEST_SHUNTING_YARD.TestShuntingYard (0 ms)
[----------] 1 test from TEST_SHUNTING_YARD (0 ms total)

[----------] 1 test from TEST_TOKENIZER
[ RUN      ] TEST_TOKENIZER.TestTokenizer
X^2-SIN(X*MAX(2,X))
TOKENIZER SUCCESSFULLY TOKENIZED STRING.
[       OK ] TEST_TOKENIZER.TestTokenizer (0 ms)
[----------] 1 test from TEST_TOKENIZER (0 ms total)

[----------] 1 test from TEST_TRANSLATOR
[ RUN      ] TEST_TRANSLATOR.TestTranslator
TRANSLATOR SUCCESSFULLY TRANSLATED POINTS.
[       OK ] TEST_TRANSLATOR.TestTranslator (0 ms)
[----------] 1 test from TEST_TRANSLATOR (0 ms total)

[----------] 1 test from TEST_PLOTTER
[ RUN      ] TEST_PLOTTER.TestPlotter
[       OK ] TEST_PLOTTER.TestPlotter (0 ms)
[----------] 1 test from TEST_PLOTTER (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 5 test suites ran. (7 ms total)
[  PASSED  ] 5 tests.
</pre>

