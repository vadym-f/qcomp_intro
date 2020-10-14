/* Vadym Fedyukovych 2020
 * You are free to Share and Adapt Under the following terms: Attribution.
 * Attribution 4.0 International (CC BY 4.0)
 *
 * Decide X or I 2x2 matrix
 * Introduced at Codeforces/Microsoft contest warmup 2020
 * https://codeforces.com/contest/1356  A1
 * https://codeforces.com/blog/entry/77614
 * Implemented with Intel-QS
 * https://github.com/iqusoft/intel-qs
 */

#include <iostream>
#include "qureg.hpp"

typedef std::complex<double> TypeC;
typedef qhipster::TinyMatrix<TypeC, 2, 2, 32> TypeM2x2;

bool Solve(const TypeM2x2 &u) {
  std::cout << "gate1: " << u(0, 0) <<  u(0, 1) << std::endl;
  std::cout << "gate2: " << u(1, 0) <<  u(1, 1) << std::endl;

  QubitRegister<TypeC> probe(1, "base", 0);
  probe.Apply1QubitGate(0, u);
  double probability = probe.GetProbability(0);
  std::cout << "prob: " << probability << std::endl;

  bool decision;
  if(probability == 0)
    decision = true; // \ket{0} stays \ket{0} => I
  else
    decision = false; // \ket{0} flips into \ket{1} => X

  return decision;
}

int main() {
  TypeM2x2 pX, pI;
  pX(0, 0) = TypeC(0., 0.);  pX(0, 1) = TypeC(1., 0.);
  pX(1, 0) = TypeC(1., 0.);  pX(1, 1) = TypeC(0., 0.);

  pI(0, 0) = TypeC(1., 0.);  pI(0, 1) = TypeC(0., 0.);
  pI(1, 0) = TypeC(0., 0.);  pI(1, 1) = TypeC(1., 0.);

  std::cout << "gateX1: " << pX(0, 0) <<  pX(0, 1) << std::endl;
  std::cout << "gateX2: " << pX(1, 0) <<  pX(1, 1) << std::endl;

  std::cout << "gateI1: " << pI(0, 0) <<  pI(0, 1) << std::endl;
  std::cout << "gateI2: " << pI(1, 0) <<  pI(1, 1) << std::endl;

  bool responseX = Solve(pX);
  bool responseI = Solve(pI);

  std::cout << "Solution X: " << responseX << std::endl;
  std::cout << "Solution I: " << responseI << std::endl;
  return 0;
}

/* Codeforces/Microsoft contest
   solution of june 13th

operation Solve (unitary : (Qubit => Unit is Adj+Ctl)) : Int {
        // your code here
        body (...) {
        mutable mres = false; // X, 1
        using (probe = Qubit()) {  // default= \ket{0}
            unitary(probe);  // either 0 (for I) or 1 (for X)
            if (M(probe) == Zero) {
                set mres = true;  // I, 0
            }
        }
        if (mres) {
            return 0;  // I gate
        }
        return 1;  // X gate
        }  // body
    }
*/

/* from src/qureg_apply1qubitgate.cpp

template <class Type>
void QubitRegister<Type>::ApplyPauliX(unsigned const qubit)
{
  qhipster::TinyMatrix<Type, 2, 2, 32> px;
  px(0, 0) = Type(0., 0.);
  px(0, 1) = Type(1., 0.);
  px(1, 0) = Type(1., 0.);
  px(1, 1) = Type(0., 0.);
  Apply1QubitGate(qubit, px);
}
*/
