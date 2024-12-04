# TCP-ClientServer
Progetto Client-Server per la generazione di una password in varie modalità

    n: password numerica (solo cifre)
    a: password alfabetica (solo lettere minuscole)
    m: password mista (lettere minuscole e numeri)
    s: password sicura (lettere maiuscole, minuscole, numeri e simboli)

La richiesta viene effettuata scrivendo "[modalità][spazio][numero(6-32)]"
Se si invia "q" il client cesserà di funzionare.


MODULARIZZAZIONE:

●	Codice sorgente nella cartella src/:

    ○	client.c: main del client.
    ○	connection.c e connection.h: gestiscono le connessioni.
    ○	protocol.h: specifica le regole di comunicazione (comuni per client e server).
    ○	utils.c e utils.h: funzioni di utilità generali.
    
●	Codice sorgente nella cartella src/:

    ○	server.c: main del server.
    ○	connection.c e connection.h: gestiscono le connessioni.
    ○	password.c e password.h: gestiscono generazione password..
    ○	protocol.h: specifica le regole di comunicazione (comuni per client e server).
    ○	utils.c e utils.h: funzioni di utilità generali.

