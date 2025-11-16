# Tema PA

## Descriere generala
Am incercat sa structurez programul intr-o forma mai usor de inteles asa ca l-am impartit in mai multe biblioteci: General.h (contine bibliotecile necesare rularii intregului program, contine declararile de structuri, pe cea de enumeratie si cateva functii care nu sunt dependente de un anumit tip de date), Coada.h (contine functiile necesare pentru a folosi coada si pentru rezolvarea pasului 1), BST.h (contine functiile necesare pentru a folosi un BST si pentru rezolvarea pasilor 2 si 3), Heap.h (contine functiile pentru utilizarea unui Heap si pentru rezolvarea pasilor 4,5 si 6) si Graf.h (contine functiile pentru utilizarea unui graf si pentru rezolvarea pasului 7). Structura pentru noduri utilizeaza union pentru a putea fi folosita atat pentru coada, cat si pentru graf.


## Descrierea functiilor create si utilizate
### In General.h
Avem urmatoarele functii:
- FILE *DeschidereFisier(char numeFisier[], char modDeschidere[]) - deschide un fisier cu numele numeFisier, in modul descris de modDeschidere, daca nu se poate deschide respectivul fisier, functia va afisa o eroare si va opri programul

- void EliberareMemorieNume(char **nume) - elibereaza memoria alocata unui sir de caractere

- Informatii CopieProfunda(Informatii participant) - realizeaza o copie profunda a lui participant pentru a permite utilizarea datelor din acesta in continuare, sa nu se schimbe in momentul in care se modifica participant

- char *TransfLitereMici(char cuv[]) - transforma un sir de caractere cu litere de diferite marimi in unul cu litere mici, util in prelucrarea statutului. Complexitate temporala O(n), spatiala O(1)

- void CitireNume(char aux[],FILE **fisierInf) - citeste caracter cu caracter numele participantului din fisier si il formateaza cum este precizat in cerinta. Complexitate temporala O(n), spatiala O(1)

- Informatii CitireInf(FILE **fisierInf) - citeste informatiile dintr-un fisier dat. Aceasta este folosita doar in pasul 1, dar se foloseste de niste tipuri de date generale, asa ca am introdus-o aici. Functia transforma statutul social primit in litere mici si il compara cu cele 3 stiute: lord, aventurier, cavaler, astfel incat sa stim ce statut are respectivul participant. Complexitatea temporala este O(n), din cauza functiilor de citire nume si de transformare in litere mici, iar complexitatea spatiala este O(1)

### In Coada.h
- Coada *CreareCoada() - aloca memorie pentru coada (in cazul in care nu se poate afiseaza o eroare si se opreste programul) si initializeaza primul si ultimul element cu NULL

- Nod *CreareNod() - aloca memorie pentru un nod (in cazul in care nu se poate afiseaza o eroare si se opreste programul)

- void AdaugareCoada(Coada *date,Informatii participant) - realizeaza o copie profunda a structurii paricipant, pe care o adauga intr-un nod, apoi se verifica daca coada mai are elemente. Daca coada nu mai are elemente, nodul va fi adaugat atat ca primul, cat si ca ultimul element. In cazul in care mai are elemente se modifica doar ultimul element

- int CoadaGoala(Coada *date) - verifica daca coada e goala si returneaza 1 daca este, altfel returneaza 0

- Informatii ScoatereCoada(Coada *date) - verifica daca coada e goala. Daca este goala, afiseaza ca este, altfel copiaza informatiile din primul nod in alta variabila, modifica primul nod si sterge anteriorul prim nod. La final returneaza valoare din nod

- void StergereCoada(Coada **date,FILE **fisierInf) - elibereaza memoria alocata cozii

- void AfisareCoada(Coada *date,FILE **fisierInf,BST **lorzi,BST **cavaleriAventurieri) - afiseaza informatiile stocate in coada. Scoate pe rand fiecare participant din coada, ii verifica statutul cu un switch() si il trimitie, in functie de statut, in arborele binar corespunzator (necesar pentru pasii urmatori), si afiseaza informatiile despre participant. Complexitatea temporala este O(n<sup>2</sup>), deoarece se executa blocul while() pentru toate elementele si se adauga in BST, iar temporala este O(n), deoarece functia de adaugare in BST este recursiva si se poate apela pana adauga elementul ca frunza

- void Pasul1() - incepe cu pasul 1 si se opreste dupa realizarea pasului 6, deoarece apeleaza functia Pasul2() care la randul ei apeleaza functii care rezolva urmatorii pasi. Aici este declarata, modificata si stearsa coada, este declarat FILE *fisierInf, unde este deschis fisierul de citire a participantilor in coada, apoi inchis si deschis din nou, de data asta pentru a scrie coada in test_1.csv. Sunt declarati si arborii binari de cautare lorzi si cavaleriAventurieri care primesc concurentii in ei cand sunt scosi din coada si care vor fi utilizati la urmatorii pasi. Coada va fi stearsa, iar programul va continua cu pasul 2. Complexitatea temporala este O(n<sup>2</sup>), datorata functiei CitireInf(), iar cea spatiala este datorata de parcurgerea cozii pentru a fi afisata si de adaugarea in BST, deci este in general O(n\*h) sau O(n<sup>2</sup>) in cazul unui arbore degenerat 

### In BST.h
- BST *CreareNodBST(Informatii participant) - copiaza informatia din participant intr-un nod pe care il va adauga in arbore

- BST *AdaugareBST(BST *nod,Informatii participant) - ii cauta pozitia participantului in arbore si ii creaza un nod pe pozitia lui. Daca valoarea experientei este mai mare sau egala cu cea din nod, va merge in dreapta, altfel merge in stanga. Complexitatea temporala este O(h), in general, daca arborele este degenerat este O(n), iar cea spatiala este O(h), in general, pentru arbore degenerat este tot O(n)

- void DRS(BST *nod,FILE **fisier) - parcurge arborele dreapta-radacina-stanga, pentru a afisa informatiile din BST in ordine descrescatoare. Functia se apeleaza pana ajunge la cel mai din dreapta element (cel mai mare) pe care il va afisa in fisier (pentru asta se va verifica statutul pe care il are), iar dupa se va duce in stanga, de unde o sa se duca din nou in dreapta. Complexitatea temporala este O(h), in general, daca arborele este degenerat este O(n), iar cea spatiala este O(h), in general, pentru arbore degenerat este tot O(n)

- void AfisareBST(BST *nod,FILE **fisier) - afiseaza primul rand din fisier si apeleaza functia DRS()

- BST *NodValoareMinima(BST *nod) - cauta cea mai mica valoare dintr-un subarbore. Complexitatea temporala este O(h), in general, daca arborele este degenerat este O(n), iar cea spatiala este O(1)

- BST *StergereNodBST(BST *radacina,Informatii persoana) - acesta functie se imparte pe mai multe cazuri: daca nodul de sters e frunza, daca are un subarbore doar in stanga sau in dreapta sau daca are 2 subarbori, unul in stanga si unul in dreapta. Nodul este cautat in stanga daca experenta persoanei cautate este mai mica decat cea din radacina subarborelui sau este cautat in dreapta daca experienta este mai mare sau egal si numele persoanelor difera. Daca experienta nodului si a persoanei sunt egale si numele este acelasi, se verifica daca are subarbore stang si daca nu are se va sterge nodul respectiv, iar nodul anterior celui sters se va conecta la nodul din dreapta celui sters (daca e frunza intra tot aici pentru ca nu are nici subarbore stang si nici drept, iar asta este prima conditie care se verifica). Daca nodul are subarbore stang se va verifica daca are si subarbore drept. Daca nu are, se va sterge nodul, iar nodul anterior se va conecta la nodul din stanga. Daca are atat subarbore stang, cat si drept, se va cauta valoarea minima din subarborele drept si se va adauga in locul celei sterse. Acum va fi cautata in subarborele drept valoarea cea mai mica pentru a fi stearsa si a nu aparea de 2 ori in arbore. Complexitatea temporala este O(h), in general, daca arborele este degenerat este O(n), iar cea spatiala este O(h), in general, pentru arbore degenerat este tot O(n)

- BST *StergereBST(BST *radacina) - cat timp exista o radacina, o va sterge

- void Pasul2(BST **lorzi,BST **cavaleriAventurieri) - se vor afisa arborii in fisierele pentru lorzi si cavaleri si aventurieri, apoi fisierLorzi va fi deschis pentru a citi contestatiile. Cat timp exista contestaii, se vor citi intr-o variabila concurentii care trebuie sa fie stersi si se va apela functia de StergereNodBST pentru a sterge respectiva persoana. La final se va afisa noul arbore, se va popula Heap-ul conform cerintei si se vor sterge arborii utilizati.

### In Heap.h
- Heap *CreareHeap() - se aloca memorie pentru heap si se initializeaza capacitatea cu 8 si numarul participantilor introdusi in heap cu 0. Se aloca si vectorul in care vor fi stocati participanti (se foloseste calloc pentru a avea initial toate valorile NULL)

- Informatii ValoareMaxima(BST **radacina) - cauta valoarea maxima din BST, cand o gaseste o copiaza in alta variabiala pe care o va returna la finalul functiei pentru a fi adaugata in heap. Nodul cu valoarea maxima va fi sters. Complexitate temporala O(h), in general, O(n) daca arborele este degenerat, iar complexitatea spatiala e O(1)

- void Adaugare(Vanatoare *deInlocuit,Vanatoare *inlocuitor,int ok) - da ok din functia CernereInSus este 1 inseamna ca trebuie intai eliberat spatiul ocupat de vechile informatii, apoi introdu-se cele noi. Dupa se continua la fel indiferent de ok, se copiaza datele de trebuie adaugate pe pozitia lor si se elibereaza memoria din variabila inlocuitor

- void CernereInSus(Heap *h,Vanatoare detalii,int i) - mentine proprietatea de heap, mutand elementul cu experienta mai mare pe pozitia lui. La inceput presupun ca elementul din detalii este unul care nu se gaseste deja in heap, dupa verifica daca asa e. In cazul in care nu se gaseste ok ramane 1, altfel ok=0. Dupa compar experienta persoanei care trebuie introdusa cu cele de exista deja in heap si cat timp aceasta este mai mare voi muta valoarea mai mica mai jos in heap si urc un nivel. La final adaug persoana pe pozitia ei. Complexitatea temporala este O(log n), iar spatiala O(1)

- void InserareHeap(Heap *h,Vanatoare detalii) - actualizeaza numarul participantilor din heap si apeleaza CernereInSus() pentru a mentine conditia de coada cu prioritata. Complexitatea temporala este O(log n), iar spatiala O(1)

- void AfisareRepartitieTrasee(Heap *h,FILE **fisier) - afiseaza prima linie cu structura fisierului, apoi afiseaza toti participanti din heap in ordinea in care au fost adaugati. Complexitatea temporala este O(n)

- void ExtragereParticipant(Heap *vanatoareaRegala,BST **arbore,FILE **trasee) - extrage participantul cu valoare maxima din arbore dat ca parametru, ii atribuie un traseu (care va si stocat ca un sir de caractere) si il introduce in heap

- void UmplereHeap(BST **lorzi,BST **cavaleriAventurieri) - creeaza heap-ul, deschide fisierul cu traseele (din care se va citi in ExtragerePartcipant()). Cat timp heap-ul nu a ajuns la numarul maxim de participanti, se vor extrage pe rand, un lord si un cavaler/aventurier. Dupa se vor afisa repartitiile, se va actualiza experienta participantilor si se vor afisa primii 3 concurenti. La final se sterge heap-ul.

- Heap *StergereHeap(Heap *h) - ia fiecare element si ii elibereaza numele si padurea pe care o are atribuita, dupa este eliberat vectorul. La final este eliberat heap-ul.

- void ModificareExperienta(Heap *h) - ia fiecare participant si ii modifica experienta adunand la experienta actuala numarul padurilor in care a avut voie sa vaneze. Pentru a aduna fiecare numar al padurilor voi parcurge sirul de caractere si voi transforma fiecare numar din sir de caractere intr-un numar intreg. De fiecare data cand obtin un numar il adaug la experienta.

- void AfisareTop3(Heap *h) - functia afiseaza prima persoana, elibereaza memoria din numele persoanei si din padurile pe care le strabate, inlocuieste persoana pe care am afisat-o cu ultima persoana din heap, iar apoi apeleaza functia de CernereInJos() pentru a reface proprietatea de max heap. Complexitate spatiala si temporala este O(nlog n), dar cum heap-ul are mereu 8 elemnte, complexitatea spatiala si temporala devine O(1)

- int CopilStanga(Heap *h,int i) - verifica daca pozitia din heap are copil in stanga. Daca are returneaza pozitia pe care se afla, altfel, daca nu are, returneaza -1

- int CopilDreapta(Heap *h,int i) - verifica daca pozitia din heap are copil in dreapta. Daca are returneaza pozitia,altfel returneaza -1

- Vanatoare CopieProfundaVanatoare(Vanatoare *concurent) - functia realizeaza o copie pentru variabilele de tip Vanatoare. Aceasta realizeaza mai intai o copie profunda pentru structura participant din structura vanatoare, adauga padurile si codul de identificare a acestora, sterge datele pe care le primeste ca parametru si returneaza copia efectuata

- void CernereInJos(Heap *h,int i) - functia verifica daca are valoarea de pe pozitia i are copil stanga si/sau dreapta. In cazul in care nu are inseamna ca pozitia i este frunza pentru heap. Daca am copil stanga sau dreapta, compar valoarea cu valoarea maxima actuala din heap. La final functia verifica daca pozitia maximului este diferita de pozitia valorii initiale. In cazul in care este, se realizeaza interschimbarea valorilor cu ajutorul unui aux si a functiei de CopieProfundaVanatoare() si continua cernerea pana cand ajunge la o frunza. Complexitate spatiala si temporala O(log n), dar cum heap-ul are mereu 8 elemente, complexitatea spatiala si temporala devine O(1)

### In Graf.h
- Graf *CreareGraf() - aloca spatiu pentru graf, dupa ii specifica numarul de paduri (varfuri, care sunt intotdeauna 11), ii aloca spatiu cu calloc pentru vectorul de noduri, creeaza un nod pentru fiecare element din vector (sunt atribuite valorile varfurilor din grafic fiecarui indice din vector) si initializea numarul de muchii cu 0. Dupa deschide fisierul in care se afla muchiile grafului, le citeste si adauga nodurile in lista de adiacenta.

- void AdaugareGraf(Graf *g,int varf1,int varf2) - parcurge lista de adiacenta a varfului 1 pana la ultimul element. Aici adauga varful 2 la finalul listei de adiacenta, rezultand ca varfurile sunt conectate si se actualizeaza numarul de muchii.

- Graf *StergereGraf(Graf *g) - sterge fiecare elemente al listei de adiacenta, dupa sterge vectorul de noduri si la final sterge tot graful

- int VerificareGradIntrare(Graf *g,int varf) - verific daca in varf intra o muchie. In cazul in care gasesc varful in lista altui element returnez 0 pt ca nu poate fi folosit ca varf pentru drum, altfel returnez 1. Complexitatea temporala este O(v \* m), dar cum v=11 mereu, complexitatea temporala devine O(1)

- int VerificareGradIesire(Graf *g,int varf) - returnez 1 daca gradul de iesire este 0 si returnez 0 in caz contrar

- void GasireTrasee(Graf *g,int varf,FILE **fisier,int *nrDrum,int lungimeDrum,int *drum) - adaug varful primit ca parametru in drum (vectorul in care stochez drumul) si apelez recursiv functia pana cand nu mai am varfuri adiacente cu cel primit ca parametru, la fiecare apel actualizand lungimea drumului. Cand ajung la un nod cu gradul de iesire 0 afisez drumul gasit si actualizez numarul de drumuri. La finalul functiei, varful dat ca paramtru va fi sters din vectorul drumului. Complexitatea spatiala si temporala este O(m) (unde m este numarul de muchii al unui varf), dar cum graful are mereu 11 noduri, complexitatea spatiala si temporala devine O(1)

### Functia int main()
Apelez Pasul1() (cu acest apel se vor rezolva pasii 1-6). Dupa incep rezolvarea pasului 7, creez graful, deschid fisierul in care voi adauga traseele create si initializez numarul drumului si aloc memorie pentru a stoca drumul gasit. Iau fiecare varf si verific sa aiba gradul de intrare egal cu 0. Cand gasesc un astfel de varf, voi initializa lungimea drumului cu 0 si voi cauta trasee care pleaca din el. La final sterg graful. Complexitea temporala este, in cazul in care nu se cunoaste numarul de noduri, O(v<sup>2</sup> \* m<sup>2</sup>) si cea spatiala O(m), dar cum v=11 si m este maxim (11\*10), complexitatea temporala devine O(1), deci complexitatea va fi aceeasi cu cea a functiei Pasul1()