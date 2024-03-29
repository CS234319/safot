# ShellTestFramework:
<ol>
  <li><a href="#summary">Summary</a>  </li>
  <li><a href="#prerequisites">Prerequisites</a></li>
  <li><a href="#installation">Installation</a></li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#api">API</a></li>
  <li><a href="#tests">Tests</a></li>
    <ul>
        <li><a href="#unit">Unit</a></li>
        <li><a href="#flows">Flows</a></li>
         <li><a href="#evaluate">Evaluate validation</a></li>
         <li><a href="#evaluateonevaluate">Evaluate on Evaluate</a></li>
    </ul>
  <li><a href="#status">Current status</a></li>
</ol>

## Summary
ShellTestFramework main purpose is to validate the C implementation of Mini-Lisp
and the Mini-Lisp book - especially all the Lisp functions of Evaluate - the semantic 
part of the Mini-Lisp compilation.<br>

ShellTestFramework includes a new Python package, API which allows communicating
(Inter-process communication) with the executable of the mini-lisp shell.

It is also contains complex flow tests to validate the C implementation and the Mini-Lisp book - 
using this Python package.<br>
Both flows are non-trivial (!) flows, which requires generates inputs from the book, generates inputs string for feeding the shell, 
and a real time communicating with process. This package allows to load Mini-Lisp functions and continue feeding the shell via Python,
without compiling everything again and again.

## Prerequisites
Python3 need to be installed, along with pip3 and pytest package.<br>
The operating system must be any Linux distribution, there is no support for Windows/Mac.<br>

## Installation
You can install all the prerequisites manually:
* **Python3 + pip3**:<br>
`sudo apt-get install python python3-pip`
* **pytest**:<br>
`pip3 install pytest`

Install everything automatically via Makefile:
* **Makefile**:<br>
`make install -C ./build`

Add the Python package to PYTHONPATH:
* **PYTHONPATH**:<br>
  ```bash
  SHELL_TEST_FRAMEWORK_PATH=`realpath ./Mini-Lisp.ShellTestFramework/`
  export PYTHONPATH="${PYTHONPATH}:${SHELL_TEST_FRAMEWORK_PATH}"
  ```
* **Automatically**:<br>
  ```bash
  source ./Mini-Lisp.ShellTestFramework/build/env.sh
  ```

## Usage
ShellTestFramework has 2 main scripts:<br>
- **./bin/run_all_tests.sh \[unit|flow|all\]**<br>
  Run all the python unit-tests and flow-tests in ShellTestFramework.<br>
  - _unit_ - Run all the unit-tests - tests of the Python package.<br>
  - _flow_ - Run all the flow-tests - tests of Evaluate validation and Evaluate on Evaluate.<br>
  - _all_ - Run both all the unit and flow tests.<br>

- **./bin/run_flow.sh \[expected dir\] \[lisp files\]**<br>
Run all the given lisp files, and compare the results with the expected.<br>
Returns 1 if all the output files are equal to expected files,<br>
else will print the diffs and return 0.<br>
For example:
  - _./bin/run_flow.sh ./expected_files/ ./test/inputs/examples/*_<br>

**Note:**<br>
The executable path of mini-lisp should be defined in the environment variable: `MINI_LISP_SHELL`.<br>
**Currently**, the default value of `MINI_LISP_SHELL` is: _\`realpath safot/Mini-Lisp.ChicDor/mini-lisp`_

## API
In order to use the Python package, you must define the PYTHONPATH as described in the installation part.<br>
After you did that, run python3 and the following command must not raise ModuleNotFoundError: 
```python
import framework.lib
```
ShellTestFramework Python package has 2 main API:
**MiniLispShell**<br>
This class represents a mini-lisp shell - it can feed the shell, and get the output from it in real-time.<br>
The IPC (Inter-process communication) with the mini-lisp executable done here.
The class supports the `with` statement for convenience.<br>

**Unit Tests:**<br> ./test/unit/test_mini_lisp_shell.py <br>
**Usage example:**<br>
  ```bash
  cd ./safot
  python3
  ```
  ```python
  from framework.lib.mini_lisp_shell import MiniLispShell
  
  with MiniLispShell("./Mini-Lisp.ChicDor/mini-lisp") as shell:
      out1 = shell.feed("(defun zcar(x) (cond ((atom x) x) (t (car x))))")
      out2 = shell.feed("(zcar '(a b))")
      out3 = shell.feed("(zcar '(a b c))")
      print(out1)
      print(out2)
      print(out3)
  ```
  ```text
  ZCAR
  A
  A
  ```
  
* **FlowTestFramework**<br>
This class represents a test framework to run Mini-Lisp files, using the
MiniLispShell API. Feed the shell (the REPL loop) with huge input files 
with a lot of s-expressions, and dump an output file for each
of the input file that were fed into the shell.<br>
The main advantage of this API, is the ability to compile a lot of functions,
and after that run s-expressions with there new functions, without the need of 
each time creating 1 input file with everything and compiling all again.<br>
**Unit Tests:**<br> ./test/unit/test_shell_test_framework.py <br>
**Usage example:**<br>
  ```bash
  cd ./safot
  python3
  ```
  ```python
  from pathlib import Path
  from framework.lib.flow_test_framework import FlowTestFramework
  
  # Define paths:
  executable     = "./Mini-Lisp.ChicDor/mini-lisp"
  input_dir      = "./Mini-Lisp.ShellTestFramework/test/inputs/examples"
  functions_file = f"{input_dir}/fun.lisp"       # file with 2 functions definitions: exists, defun
  input_file     = f"{input_dir}/lisp01.lisp"    # file with 3 s-expression, using these 2 functions
  
  # Create an instance of FlowTestFramework:
  flow = FlowTestFramework(executable)
  
  # Run:
  flow.injecFil(functions_file)        # Compile the functions
  out_file = flow.run_s_expr_file(input_file)    # Run the s-expression + generate out_file
  print(Path(out_file).read_text())	       # Print it
  ```
  ```text
  T
  T
  A
  ```

## Tests
ShellTestFramework has 2 kinds of tests:<br>
* Unit-test: Python tests, using pytest for the API. 
* Flow-tests: Evaluate + Evaluate on Evaluate

### Unit
**MiniLispShell** unit-tests:<br>
  * _./test/unit/test_mini_lisp_shell.py_<br>

**FlowTestFramework** unit-tests:<br>
  * _./test/unit/test_shell_test_framework.py_<br>

**Run**:<br>
  * _./bin/run_all_tests.sh unit_

### Flows
The main goal of the flow tests is to validate the C implementation of Mini-Lisp and 
the Mini-Lisp book.<br>
**Note**:<br>
The tests **are not** unit-tests for the C implementation, but more like:<br> 
`./mini-lisp < input.lisp > output.lisp && diff output.lisp expected.lisp`<br>
There are cons and pros to run the flow tests with this framework, as described in issue-436 by Yossi Gil:<br>
The nice thing about the framework is that you do not have to compile anything 
to add more tests. This will save much time and effort. The down side is that time and effort should be invested to implement this.<br> 

### Evaluate
The flow tests of Lisp Evaluate done for each of the Mini-lisp's evaluate functions.<br>
* **Inputs + Expected files**: ./test/flow/book_evaluate/<br>
* **Test**: ./test/flow/test_book_evaluate.py
* **Flow steps**:<br>
Each of the flow tests, done by the following steps:
  * Generate the latest lisp files from the book.
  * Open communication with the mini-lisp executable in Mini-Lisp.ChicDor .
  * Feed the shell with all the files from the book.
  * Feed the shell with the input file.
  * Communicate with the mini-lisp process and write all the outputs from the shell to out file.
  * Compare out file with expected file.
  * If the files are identical then the test passed, else failed and show diffs.
* **Run**:
  * _./bin/run_all_tests.sh flow_<br>
    (running all the flow tests may take around ~5 minutes)

### EvaluateOnEvaluate
The flow tests of Lisp Evaluate On Lisp Evaluate are based on the test: ./test/input/test_evaluate.in.lisp.
The idea here is to run each s-expression from this test, but in a different way:
applied the Lisp evaluate function using the Lisp evaluate function.<br>

**For example**:
* Original test: `(evaluate 'a '(a.x t.t nil.nil))`<br>
* New test: `(evaluate '(evaluate (quote a) (quote (a.x t.t nil.nil))) '(environment))`<br>
Where `environment` includes all the definitions used by the inner evaluate, means the alist:<br>
(t.t nil.nil apply.(lambda ...) evaluate.(lambda ...) quote.(nlambda ...) ...)<br>

In summary, the inner evaluate defined (includes all the Lisp evaluate functions) in `env`,
the outer evaluate defined in the C alist, and the inner use its own alist to evaluate it's s-expression.

**Test**: ./test/flow/test_evaluate_on_evaluate.py<br>

**Flow steps**:
1. Generate the latest lisp files from the Mini-lisp book.
2. Open communication with the mini-lisp executable in Mini-Lisp.ChicDor.
3. Feed the shell with all the files from the book. (create our `executable alist`)
4. Feed the shell with the lisp function `generate_alist` which will generate an alist with all the evaluate functions (plus nil, t, qoute, etc.)
5. Set the identifier `env`, with the value of the alist. 
6. Set the identifier `inner`,  with the value of `env` **plus** the relevant pairs for the specific s-expression. 
7. Set the identifier `outer`,  with the value of `env` **plus** the pair `inner` and it's value, so the outer evaluate can evaluate `inner`. 
8. Feed the shell with the input file with all the s-expressions (each of them have different inner and outer alists).
9. Communicate with the mini-lisp process.
10. Compare our output with expected.
11. If the strings are identical then the test passed, else failed and show diffs.

**Environments**:<br>
1. `executable alist` - our "real" alist from the C code, includes all the functions
that will be fed from the book (step 3) and contains all the definitions for the outer evaluate.
2. `outer alist` - our alist for the inner evaluate function, includes all the functions
that will be fed from the book (step 4) and contains all the definitions for the inner evaluate.
3. `inner alist` - used by the inner evaluate, to evaluate its own s-expression, equal to the outer alist.
* **Run**:
  * _./bin/run_all_tests.sh flow_<br>
  (running all the flow tests may take around ~5 minutes)

## Status
Status of the tests:<br>
**Lisp Evaluate**:<br>️
All the flow tests of Lisp Evaluate passed.<br>
✔ apply_atomic<br>
✔ apply_decomposed_lambda<br>
✔ apply_eager_atomic<br>
✔ apply<br>
✔ apply_trivial_atomic<br>
✔ bind<br>
✔ evaluate_atomic<br>
✔ evaluate_cond<br>
✔ evaluate<br>
✔ evaluate_list<br>
✔ exists<br>
✔ is_atomic<br>
✔ lookup<br>

**Lisp Evaluate on Lisp Evaluate**:<br>
All the flow tests of Lisp Evaluate on Lisp Evaluate passed.<br>
✔ Evaluate atoms<br>
✔ Evaluate atomic functions with one arguments<br>
✔ Evaluate atomic functions with two arguments<br>
✔ Evaluate errors<br>
✔ Evaluate cond<br>
✔ Evaluate lambda/nlambda functions<br>

**Update:**<br>
All the tests will pass **only if** you compile the mini-lisp
with the workaround environment variable:
```bash
export WORK_AROUND=1
make all -C ./Mini-Lisp.ChicDor/
```
(this is done automatically in _./bin/run_all_tests.sh_)<br> 
Because the current memory infrastructure of the C implementation of Mini-Lisp
has no Garbage Collector yet, there are not enough memory when running these flow tests,
so there is a temporary workaround that increase the memory, by setting the basic word integer
from int32 to int64.<br>
According to Yossi Gil, this workaround must not (!) be part of the Mini-Lisp
implementation (and of course not part of the production) and thus can only be use 
temporary with this environment variable, in order to successfully run the flow tests without 
out of memory errors.<br>
It must be deleted after the garbage collector will be implemented in the
memory infrastructure in the future.<br>
