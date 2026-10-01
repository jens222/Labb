#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

typedef set<char> Set;

const Set U = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

Set unite(const Set& a, const Set& b) {          // A ∪ B
    Set r;
    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(r, r.begin()));
    return r;
}

Set inter(const Set& a, const Set& b) {          // A ∩ B
    Set r;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(r, r.begin()));
    return r;
}

Set diff(const Set& a, const Set& b) {           // A \ B
    Set r;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(r, r.begin()));
    return r;
}

Set complement(const Set& a) { return diff(U, a); }                  // A'
Set sym_diff(const Set& a, const Set& b) { return unite(diff(a, b), diff(b, a)); }  // A Δ B

void print(const string& name, const Set& s) {
    cout << name << " = { ";
    if (s.empty()) cout << "∅ ";
    for (auto it = s.begin(); it != s.end(); ++it)
        cout << *it << (next(it) != s.end() ? ", " : " ");
    cout << "}" << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    Set A = {'a', 'b', 'c', 'g'};
    Set B = {'c', 'd', 'e'};
    Set C = {'e', 'f', 'g'};

    // ===== Завдання 1 =====
    cout << "===== Завдання 1 =====" << endl;
    print("A", A); print("B", B); print("C", C); print("U", U);

    cout << "\nа) (A∪C)∩B" << endl;
    Set AC = unite(A, C);
    print("   A∪C", AC);                          // {a, b, c, e, f, g}
    print("   (A∪C)∩B", inter(AC, B));            // {c, e}

    cout << "\nб) A∖(BΔC)" << endl;
    Set BC = sym_diff(B, C);
    print("   BΔC", BC);                          // {c, d, f, g}
    print("   A∖(BΔC)", diff(A, BC));             // {a, b}

    // ===== Завдання 2 =====
    cout << "\n===== Завдання 2 =====" << endl;
    Set C1 = complement(C);
    print("C'", C1);                              // {a, b, c, d}
    Set BuC1 = unite(B, C1);
    print("B∪C'", BuC1);                          // {a, b, c, d, e}
    Set BuC1c = complement(BuC1);
    print("(B∪C')'", BuC1c);                      // {f, g}
    Set M = inter(A, BuC1c);
    print("M = A∩(B∪C')'", M);                    // {g}

   string m(M.begin(), M.end());           // для доступу за індексом
    int n = m.size(), amount = 1 << n;
    cout << "|M| = " << n << endl;

    cout << "P(M) = { ";
    for (int mask = 0; mask < amount; mask++) {
        cout << "{";
        bool first = true;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) {
                cout << (first ? "" : ", ") << m[i];
                first = false;
            }
        if (mask == 0) cout << "∅";
        cout << "}" << (mask + 1 < amount ? ", " : " ");
    }
    cout << "}" << endl;
    cout << "Потужність P(M) = 2^" << n << " = " << amount << endl;

    // ===== Завдання 7 =====
    cout << "\n===== Завдання 7 =====" << endl;
    cout << "Спростити вираз: (A∖B)∪(A∩B)" << endl;
    cout << "1. (A∖B)∪(A∩B)" << endl;
    cout << "2. (A∩B')∪(A∩B)          // A∖B = A∩B'" << endl;
    cout << "3. A∩(B'∪B)              // дистрибутивний закон" << endl;
    cout << "4. A∩U                   // B'∪B = U" << endl;
    cout << "5. A                     // A∩U = A" << endl;

    Set left = unite(diff(A, B), inter(A, B));
    print("\n(A∖B)∪(A∩B)", left);
    print("A", A);
    cout << (left == A ? "Перевірка: рівність виконується → вираз = A"
                       : "Помилка: результати не збігаються!") << endl;

    return 0;
}
