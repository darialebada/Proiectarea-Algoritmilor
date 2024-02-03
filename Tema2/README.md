## Lebada Daria-Cristiana, 323CA
# PA - Tema2 - Gigel, mereu ocupat -

## Task 1 - Supercomputer
Pentru rezolvarea problemei am pornit de la algoritmul lui Khan de sortare topologica
(l-am implementat dupa rezolvarea laboratorului 6 oferita de catre echipa de PA).
Folosec un vector in_degree in care memorez gradele interne ale fiecarui nod. Folosesc
2 cozi auxiliare in care retin nodurile ce pot fi adaugate la sortare in acel moment
(cele cu grad intern 0, deoarece nu mai exista alte noduri care trebuie sa apara inaintea lor).
Voi realiza 2 sortari topologice: cand incep cu un element din setul de date 1, respectiv
setul de date 2. Raspunsul final este minimul de context switch-uri necesare dintre cele 2
sortari obtinute anterior.
Folosesc o variabila auxiliara type in care retin setul de date pe care vreau sa il adaug.
De exemplu, daca vreau sa adaug un nod care foloseste setul de date 1, adaug un nod din coada 1,
apoi ii vizitez vecinii. Adaug noduri din coada 1 pana se goleste, apoi schimp valoarea lui type
si incep sa adaug elemente din coada 2. La final calculez numarul de context switch-uri.
- Complexitatea temporala: O(E + V), unde E reprezinta numarul de muchii, iar V numarul de noduri.

## Task 4 - Magazin
Dupa ce citesc datele de la intrare, retin intr-un vector ordinea dupa dfs. Algoritmul de dfs este
implementat dupa rezolvarea laboratorului 6 si dupa pseudocodul de pe ocw (partea cu timestamp),
dar fara a verifica daca un vecin a mai fost vizitat (in cerinta se spune ca fiecare depozit poate
primi colet de la un singur depozit, deci voi avea un arbore). Pentru fiecare nod retin pozitia din
care incepe subarborele, respectiv unde se termina.
Pentru fiecare intrebare verific daca lungimea subarborelui unde vreau sa realizez livrarea este mai
mare decat numarul de expedieri dorite. Daca se poate raspunde la intrebare, returnez depozitul cautat.
- Complexitate temporala DFS: O(E + V), unde E reprezinta numarul de muchii, iar V numarul de noduri.
