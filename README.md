# RoundRobinScheduling-simulation
Aplicație care are posibilitatea introducerii în ordine cronologică a unor procese, caracterizate prin timpul de start și timpul de execuție. Vom presupune că primul proces începe la momentul 0 de timp. Execuția acestora va fi planificată cu ajutorul algoritmului Round-Robin. 
  Ce este algoritmul Round-Robin?
Este unul dintre cei mai vechi algoritmi de planificare. Fiecărui proces i se atribuie un interval de timp (cuantă) în care procesul se poate executa.
Dacă procesorul nu-și termină execuția până la expirarea cuantei de timp alocate, el va fi întrerupt iar procesorul este alocat altui proces. Dacă procesul își termină execuția înainte de expirarea cuantei, se va planifica alt proces fără a se aștepta expirarea cuantei.
