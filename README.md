# Liliczby

Liliczba (ang. nunumber) to rekurencyjna reprezentacja nieujemnej liczby całkowitej za pomocą ciągu cyfr, które również są liliczbami. Reprezentacja ta, sformułowana w nieco inny ale równoważny sposób, była rozważana przez Donalda Knutha.  

Wartością liliczby jest suma potęg dwójki o wykładnikach będących wartościami cyfr tej liliczby. Powiemy, że liliczba jest znormalizowana, jeśli jej cyfry są znormalizowanymi liliczbami i są uporządkowane rosnąco według wartości.  

Tekstowym zapisem liliczby jest słowo języka z poniższą gramatyką w rozszerzonej notacji BNF:  
liliczba ::= { "Y" cyfra } "Z"  
cyfra ::= liliczba   

W uproszczeniu:
Y oznacza '2^(', a Z ')'. Jeśli wewnątrz nawias jest pusty, to jego wartością jest 0. Dwa sąsiednie wyrażenia 2^(...)2^(...) należy zsumować. Ponadto liliczba, którą otrzymuje program, jest zakończona dodatkowym Z.

Program wczytuje dwie, niekoniecznie znormalizowane liliczby zapisane na wejściu i wypisuje ich iloczyn jako znormalizowaną liliczbę.

Zdecydowanie najciekawszy program, jaki napisałem na studiach. Pozwala liczyć iloczyn liczb, których zapis binarny miałby więcej bitów, niż jest atomów na Ziemi.

Przykłady znormalizowanych liliczb w formacie wartość | liliczba:  
0 Z  
1 YZZ  
2 YYZZZ  
3 YZYYZZZ  
4 YYYZZZZ  
8 YYZYYZZZZ  
16 YYYYZZZZZ  
64 YYYZZYYYZZZZZ  
128 YYZYYZZYYYZZZZZ  
256 YYYZYYZZZZZ  
1024 YYYZZYYZYYZZZZZ  
