time.c :

Ne peut pas etre appelée car ne possede pas de fonction main(). 
Prend en paramètre l'heure passée par l'utilisateur dans le format (int hours,int mins).
Vérifie si l'heure donnée est valide.
Attend jusqu'a l'heure demandée.

time_test.c :

Permet de tester le programme time.c.
Demande l'heure a l'utilisateur.
Attend jusqu'a l'heure passée.

Signal2.c :

Demande a l'utilisateur quelle fonction appeler.
Appel la fonction demandée.
Reboucle au début du programme.

Raspberry.c :

Reçoit les parametres du clients dans un fd.
Renvoit dans le fd "not_ok" tant que le café n'est pas fini.
Appel la fonction de lancement du café.
Renvoit dans le fd "ok" quand le café est fini.