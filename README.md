# Assignment 2 — CO2 | Report and execution guide

Name: **Sahhanaa Shree T**  
Register number: **192511283**  
Compiler: g++ 14.2.0 (validation environment; replace with your local version)  
Repository: **(https://github.com/sahhanaa44/DSA0101-192511283A-Assignment2)**  
Due: 31 October 2026

## Q1 — Hostel fee concessions (6 marks)
**Prediction to write down before executing:** Provided change/bigger/show example prints:
```
1 12 13
1 100
16 13 6
```
`a` is a value copy, `b` aliases the caller, and `c` points at the caller's integer. `bigger(a,c)` returns the variable `c` as an assignable reference, so it becomes 100. `show(1)` uses 5,10; `show(1,2)` uses 10; `show(1,2,3)` uses no defaults.

**Complete-the-code prediction:**
```
after call by value   : 45000
after call by reference: 40500
```
The local value parameter is a separate `long long`, so its modification does not persist. The reference parameter is an alias for the original fee. The pointer holds the original address and must be checked for null before dereferencing. A `const Student&` is preferable when a large object must only be read, avoiding a potentially expensive copy and preventing mutation.

**Design:** Prefer a function returning the new fee for calculations that must be auditable and composed, e.g. `long long discounted(long long fee,int p){return fee-fee*p/100;}` and `fee=discounted(fee,10);`. Applying multiple discounts sequentially compounds them (10% then 15% is not simply 25%). Alternatively, a mutating reference is appropriate for explicitly named state updates. All three scalar approaches are O(1) time and O(1) extra space. Passing a large Student by value copies O(S) bytes and takes O(S) copy time; reference or const reference copies only a fixed-size reference/address (O(1)). A pointer likewise copies an address and may be null.

## Q2 — Return by reference (4 marks)
`highest` returns an lvalue referring to the actual array element; `highest(marks,4)+=2` changes 91 to 93. A `const int&` allows reading but disallows modification through that reference; returning `int` copies the value. The bad local reference triggers a compiler warning such as `reference to local variable ... returned`. Its lifetime ends on return; using the dangling reference is **undefined behavior**, not a predictable output.

Alternative: `marks[highestIndex(marks,4)]+=2;` or `*highestPointer(marks,4)+=2;`. Each searches O(n) and uses O(1) auxiliary space. A vector reallocation invalidates references, pointers and iterators; a saved numeric index can remain useful if elements are not inserted/erased before it and the index remains in range. The code deliberately retains an index across `reserve()` rather than retaining an invalidated reference.

## Q3 — Courier overloads (6 marks)
The original `charge(double)`, `charge(double,bool)` and `charge(double,bool=false,bool=false)` create ambiguous viable candidates for calls with one or two arguments. The redesign has distinct `int`, `float`, `double` with defaults, and `Parcel` overloads.

**Predicted selections, in call order:** `charge(2)` -> int grams; `charge(2.0f)` -> float kg; `charge(2.0)` -> double kg; `charge(2.0,true)` -> double kg; `charge(2.0,true,true)` -> double kg; `charge(Parcel{...})` -> Parcel. The explicit float overload prevents the ambiguous float-to-int vs float-to-double conversions. Exact match outranks promotion, which outranks conversion; overload ranking also considers other rules. Default arguments must be trailing because omitted arguments can only come from the right. Resolution is compile-time (no runtime search), with O(1) computation and O(1) scalar argument storage. A Parcel parameter passed by value copies O(sizeof(Parcel)) bytes; `const Parcel&` avoids copying and is easy to extend with new fields. Templates could generalize numeric weights but need explicit unit semantics to avoid mistakes.

## Q4 — SavingsAccount (6 marks)
Private account number, balance, 10-element transaction array, and count protect invariants. `deposit` is inside the class; `withdraw` and `miniStatement` are defined outside with `SavingsAccount::`. The 11th transaction shifts entries left, discarding the oldest, then appends. Shift costs O(k) per addition and O(k) space for k stored transactions. A circular buffer overwrites at `start`, increments start modulo k, and adds in O(1), using O(k) space. `std::deque` with `push_back`/`pop_front` offers O(1) end operations and O(k) space, with container allocation overhead. For 50 entries, a circular buffer parameterized by capacity avoids shifting and requires only changing the capacity configuration; a deque offers more flexible resizing. For tiny fixed k, a shifting array is simple and easy to inspect.

## Q5 — BusTicket (7 marks)
**Prediction for Token:** `101 103 104 4`. Static `next` is initialized once to 100 outside the class; the three array elements plus `extra` run the constructor four times. Static `issued` is shared by every ticket and defined once as `int BusTicket::issued=0;` outside the class. A static member function has no `this`, so it cannot directly access instance fields. The array of four tickets receives seats 1–3, then a waiting ticket. Creating further tickets in a function called twice does not reset the counter, and object destruction does not decrement it in this design.

**Complete-the-code expected output:**
```
Asha: Seat 1
Bala: Seat 2
Chitra: Seat 3
Dev: Waiting
Issued: 3
```
Global count and static count each use O(1) time and one shared integer, but global state has weaker encapsulation. A separate `TicketOffice` instance can track capacity per bus, enabling multiple buses with independent counts. A static counter tied to `BusTicket` cannot independently count two buses unless redesigned with separate per-bus state.

## Q6 — Train journey planner (8 marks)
**Complete-the-code expected output:** `205 false`. The two times are 09:45 (585 minutes) and 13:10 (790 minutes), a difference of 205. `earlier(arrival,departure)` is false. Equal times have difference zero and `earlier` false. 09:45 vs 12:00 differs by 135 minutes.

A non-member friend compares two operands symmetrically and can read private `h,m`; a member call looks like `a.minutesTo(b)` and can read private fields of both Time objects. Public getters permit nonfriend functions without exposing mutable data; making the fields public loses invariant enforcement and representation hiding. `inline` allows multiple identical definitions across translation units and suggests inlining but does not guarantee substitution; compilers may inline ordinary functions at `-O2` too. O(1) time and space per comparison for all three designs. Prefer friend functions for a symmetric comparison API when internal access is justified; getters or members offer tighter control of access for general consumers. Compare measured `-O0` and `-O2` runs; benchmark results are hardware/compiler dependent and the optimizer may change or eliminate work, so timings are illustrative, not definitive.

## Q7 — Diagnose, redesign, validate (13 marks)
**A. Diagnosis:** Q4 shifts up to k-1 transaction values every time the history is full, so increasing k from 10 to 50 or more raises work per insertion. `Task07/main.cpp` contains both implementations and reproducible measurements.

**B. Objective:** Reduce insertion cost from O(k) to O(1) independent of the retained-history capacity, while preserving the exact chronological last-k values after 100,000 additions.

**C. Revised design:** `RingHistory` stores `vector<int> data`, `capacity`, `start`, `count`. When not full, write at `(start+count)%capacity`; when full, overwrite `data[start]` and advance `start=(start+1)%capacity`. `snapshot()` reads from start in chronological order. Insertion O(1), snapshot O(k), storage O(k). Modulo arithmetic and more complex indexing are the trade-offs.

**D. Prediction before execution:** Ring insertion will become relatively faster as k increases (especially k=10,000), whereas shifting takes O(k) once full. Both retain identical last-k data.

**E. Validation:** Run both implementations with 100,000 insertions for k=10, 50, 1000, 10000; verify size, first, last, and measured microseconds. The same test inputs and measurement method are used for both. See `Task07/observed.txt` for results from the validation environment; repeat on your own machine and take screenshots.

**F. Defense:** The ring meets the asymptotic O(1) insertion objective; shifting can still be preferable for tiny capacities because it is simpler and can have good locality. A ring adds indexing complexity and preserves a fixed capacity; dynamic resizing requires further logic. Timings may vary by machine.

## GitHub submission checklist
1. Rename repository to `DSA01-<RegisterNumber>-Assignment2` and enter personal information above.
2. Make your **own** predictions before executing each prediction task, and document any discrepancy.
3. Run all programs in each folder; add actual output screenshots and compiler warning screenshots.
4. Record `g++ --version`, compilation commands, your own timing runs at `-O0` and `-O2`, and evidence of Q7 validation.
5. Make at least one **real progressive commit per task**; do not fabricate or rewrite history to suggest work was done earlier.
6. Push to GitHub and share the repository with faculty; paste the link on the report cover.
