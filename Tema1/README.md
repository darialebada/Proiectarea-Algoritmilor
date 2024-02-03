### Lebada Daria-Cristiana - 323CA
# Proiectarea Algoritmilor - tema1


### Task1 - Feribot
- Metoda divide et impera cu greedy

Pentru rezolvarea acestei probleme am ales o metoda asemanatoare cautarii binare.
Prima data calculez cele doua limite (greutatile minime, respectiv maxime posibile
pe un feribot). Astfel, notez left greutatea maxima a unei masini din sir si right
suma tuturor greutatilor masinilor din sir. Caut o valoare din intervalul
[left, right] care sa fie solutia cautata.
Functia check_solution verifica validitatea solutiei gasite. La fiecare pas calculez
suma greutatilor de pe fiecare feribot (adaug masini pe feribot pana ajung la o greutate
mai mare decat solutia mea curenta). Daca sunt necesare mai mult de k feriboturi,
solutia curenta nu este corecta si este nevoie de o greutate mai mare. Daca am gasit
o solutie valida, continui sa caut daca exista o valoare mai mica care indeplineste
conditiile.

- Complexitatea algoritmului este O(n*logn), unde n este numarul de masini.


### Task2 - Nostory
- Metoda Greedy

2.1 Avand la dispozitie un numar nelimitat de mutari, este suficient sa concatenez
cei 2 vectori si sa sortez noua lista obtinuta. Voi adauga in suma ultimele n numere
din vectorul concatenat.

2.2 Folosesc 2 vectori: added - retine valorile maxime din perechile de numere de pe
aceleasi pozitii din A si B, si not_added - retine valorile minime din perechi. Sortez
acesti vectori crescator, respectiv descrescator, apoi calculez suma. Voi adauga elementele
din vectorul added in suma, cu exceptia a maxim k mutari: inlocuiesc primele k valori minime
din vectorul added cu primele k valori maxime din not_added.

- Rezolvarile ambelor taskuri au complexitatea O(n*logn); functia sort din STL are aceeasi
complexitate.


### Task3 - Sushi
- Programare dinamica

3.1 Am creat un vector in care am adaugat suma notelor pentru fiecare tip de sushi (un fel
de rating). Am ales o rezolvare asemanatoare unei probleme clasice: problema rucsacului (implementata
dupa demo-ul din laboratorul 3). Stiu suma maxima max_money de bani pe care vor sa o cheltuiasca
prietenii, asa ca imi creez o tabela in care caut solutiile de la 1 la max_money (in tabela pun 0 pe
linia, respectiv coloana 0 - cazul de baza) si in care voi adauga notele. Am 2 cazuri: aleg platoul curent
sau nu.
Adaug solutia precendenta, apoi, daca pretul tipului de sushi curent este mai mic decat solutia curenta,
caut ratingul maxim pe care l-as putea obtine (adica verific daca merita ales platoul curent).
In final, voi avea in ultimul element din tabela valoarea cautata (suma maxima posibila a notelor).

3.2 Dublez tipurile de sushi si apelez functia de la task 3.1.

- Complexitatea ambilor algoritmi este O(M * S), unde M reprezinta numarul de tipuri de sushi si S reprezinta
suma maxima pe care vor sa o plateasca.

3.3 Dublez tipurile de sushi. Folosesc o tabela dp de forma [tip sushi][cost maxim curent][numar platouri alese].
Rezolvarea este asemanatoare cu task1, doar ca tin evidenta si numarului de platouri alese (maxim k). Atunci cand
am de decis daca sa aleg si platoul curent, trebuie sa am in vedere si numarul de platouri alese: daca pentru cost
trebuie sa ma asigur ca pot cumpara inainte maxim cost_total - cost_sushi_curent, ma asigur si sa fi ocupat anterior
maxim numar_maxim_platouri - 1;

- Complexitatea algoritmului este O(M * S * K), unde M reprezinta numarul de tipuri de sushi, S reprezinta suma
maxima pe care vor sa o plateasca, iar K reprezinta numarul maxim de platouri (numarul de prieteni).


### Task4 - Semnale

- Algoritmul pentru calculul combinarilor foloseste formula: C(n, k) = (n * (n - 1) * ... * (n - k + 1)) / (k!).
Datorita simetriei, ii pot da lui k valoarea minima dintre k si n - k. Deoarece nu pot aplica modulo pe
impartire, ma folosesc de proprietatea ca (a / b) % MOD = (a * inv(b)) % MOD, unde b * inv(b) = 1. Daca ma
folosesc de un modulo prim (cum este 10^9 + 7), pot calcula usor inversul modular cu formula:
inv(i) = MOD - (MOD / i) * inv(MOD % i) % MOD. Am adaugat la referinta site-urile unde am gasit aceste informatii.
- Complexitatea algoritmului pentru calculul combinarilor este O(n + k).

4.1 Numarul de combinari posibile este egal cu combinari de numar zerouri + 1 luate cate numar de 1.
Explicatie: pentru 2 zerouri avem un numar de forma _0_0_, deci avem 3 posibilitati de a pune valorile
de 1. Complexitate: O(n + k).
4.2 Am mai multe cazuri pe care trebuie sa le iau in calcul. Prima data iau cazul de la taskul anterior
(unde nu am valori consecutive de 1). Apoi voi adauga cate un grup de 11. De exemplu, pentru y valori de
1 voi lua pe rand 1, 2... y / 2 grupari de 11. Daca am in total num grupari de 1 si 11, calculez numarul de
combinari in care pot pune aceste grupari printre zerouri (_0_0_0...) drept combinari de num luate cate x + 1,
unde x reprezinta numarul de zerouri. Apoi trebuie sa vad unde pot aseza gruparile de 11, deci inmultesc
rezultatul anterior cu combinari de num luate cate grupari de 11 am. Complexitate: O(y * (n + k)), unde y
este numarul de 1.


### Bonus - BadGPT
Numarul de combinari posibile pentru o grupare cu n sau u se poate calcula cu ajutorul sirului
lui Fibonacci. Iau fiecare aparitie a unei litere n sau u, calculez numarul de combinari si
inmultesc rezultatele.
Am rezolvat Fibonacci prin metoda exponentierii matricei in timp logaritmic. Stim ca:
{[1 1] [1 0]} ^ 2 = {[F_n+1 F_n] [F_n F_n-1]}. Ridicarea la puterea n a matricei se face eficient
tinand cont de urmatoarele proprietati:
    1. A^(2k+1) = A * A^(2k)
    2. A^(2k) = A^k * A^k

- Complexitate O(logn) pentru Fibonacci, unde n reprezinta al n-lea termen din sirul lui Fibonacci.
Algoritmul se repeta pentru fiecare aparitie in sir a unei litere "n" sau "u".


### Referinte
Task3:
- https://www.javatpoint.com/0-1-knapsack-problem -> explicatii problema rucsacului
Task4:
- https://cp-algorithms.com/algebra/module-inverse.html#finding-the-modular-inverse-using-euclidean-division
-> algoritmul lui euclid extins cu inversa modulara
- https://en.wikipedia.org/wiki/Binomial_coefficient#In_programming_languages -> coeficientul binomial
- https://www.geeksforgeeks.org/binomial-coefficient-dp-9/ -> informatii despre
calculul combinarilor
Task5:
- https://brilliant.org/wiki/fast-fibonacci-transform/ -> fibonacci cu matrice
- https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/ -> exponentierea matricei
