You are given an operation that implements a single-qubit unitary transformation:
either the identity (I gate) or the X gate.
Your task is to perform necessary operations and measurements to figure out
which unitary it was and to return
0 if it was the I gate or
1 if it was the X gate.

https://codeforces.com/contest/1356

namespace Solution {
  open Microsoft.Quantum.Intrinsic;
  open Microsoft.Quantum.Canon;

  operation Solve (unitary : (Qubit => Unit is Adj+Ctl)) : Int {
    // your code here
    body (...) {
      mutable mres = false;  // X, 1
      using (probe = Qubit()) {  // default= \ket{0}
        unitary(probe);  // either 0 (for I) or 1 (for X)
        if (M(probe) == Zero) {
          set mres = true;  // I, 0
        }
	Reset(probe);
      }
      if (mres) {
        return 0;  // I gate
      }
      return 1;  // X gate
    } // body
  }
  operation RunQsharp () : Bool {
    Message("RunQsharp called");
    return true;
  }
}
