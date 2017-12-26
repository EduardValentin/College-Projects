    * Input:  => O lista de puncte 2D ce reprezinta centrurile unor cercuri de raza 1 si un punct P.
    * Output: => Pozitia lui P fata de acoperirea convexa a cercurilor.
    * Idee:   => Se determina acoperirea convexa a punctelor ce reprezinta centrurile cercurilor folosint algoritmul Graham Scan.
                 Propozitie : Daca un punct se intersecteaza cu acoperirea convexa a centrurilor cercurilor, atunci el este in interiorul acoperirii convexe a cercurilor.
                 Ramane de rezolvat cazul in care P nu se intersecteaza cu acoperirea convexa a centrurilor cercurilor, trebuie verificata distanta minima a lui P fata de acoperirea convexa a centrurilor.
                 Idee pt problema de mai sus => acoperirea convexa a centrurilor ne da un poligon convex, rezulta ca varfurile poligonului au o relatie de ordine,si ca poligonul are "forma buna", adica nu are fete ce se intersecteaza;
                                                Deci putem alege un punct in interiorul poligonului,O astfel incat putem triangula poligonul trasand linii ce pleaca din O catre fiecare punct al poligonului.
                                                Apoi cautam binar 2 puncte v1,v2 din acoperirea convexa astfel incat P sa fie intre v1 si v2 , apoi determinam pozitia lui fata de segmentul [v1v2]
                                                Daca P e la stanga lui [v1v2] in parcurgerea trigonometrica,inseamna ca e in interiorul acoperirii convexe si am terminat
                                                Daca P e la dreapta lui [v1v2] in parcurgerea trigonometrica,inseamna ca e in exteriorul acoperirii convexe a centrurilor dar ramane sa calculam daca distanta lui fata de acoperire e <= 1.Facem acest lucru calculand distanta minima de la punctul P la linia ce trece prin cele 2 puncte v1 si v2

    * Complexitate timp: O(n*log(n) + log(n))
                         Graham scan => O(n*log(n))
                         Cautarea binara a celor 2 puncte => O(log(n))
