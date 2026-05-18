function out = brownian1D

%il programma richiama il randomwalk classico o il randomwalk modificato
%appositamente per studiare la situazione fisica in esame
%aprire il file myrandomwalk.m per le considerazioni e i commenti sullo
%stesso
    
    prompt = 'Cosa si vuol fare: Brownian (1) o Randomwalk (2)? ';
    c = input(prompt);
    
if c==1
        in = myrandomwalk;
        out = myrandomwalk(in);
        return;   
end
    
    
    if c==2 
        in = randomwalk;
        out = randomwalk(in);
        return;
          
        
    else 
        
        disp('Wrong answer');
       return;
    end
end

%LOGICA DELLA SOLUZIONE

%Il programma di randomwalk � stato modificato in modo da poter studiare la
%situazione fisica proposta dal docente. Abbiamo modificato le equazioni
%differenziali proprie del randomwalk 2-dimensionale in modo da poter
%simulare un moto Browniano monodimensionale nello spazio delle fasi,
%inserendo un termine di drift dovuto all'attrito viscoso del fluido in cui
%le particelle sono immerse e dal campo gravitazonale terrestre. 
%Inoltre si � prestata particolare attenzione alla positura di opportune
%condizioni al contorno nel piano z=0,simulando un regime di collisioni 
%elastiche con la parete. In particolare, queste condizioni impongono che
%la velocit� di ogni singola particella vari da v a -v al bordo, questo
%provoca una riflessione lungo le ordinate dopo l'urto con la parete. 
%Dalla teoria sappiamo che l'evoluzione temporale del moto di particelle
%browniane raggiunge un equilibrio statistico dopo un determinato tempo t.
%L'equilibrio statistico viene raggiunto quando la distribuzione delle
%velocit� delle particelle � la distribuzione di Maxwell-Boltzmann.
%L'equilibrio non dipender� dalla distribuzione iniziale delle particelle e
%dal coefficiente di attrito gamma; solo il tempo impiegato per
%raggiungerlo dipender� da questi parametri.
%Plottiamo quindi la distribuzione finale delle velocit� delle particelle e 
%la compariamo con la distribuzione di Maxwell-Boltzmann. Possiamo
%osservare che, dopo un opportuno intervallo di tempo, le due
%distribuzioni sono molto simili. 
%Notiamo che quando si raggiunge l'equilibrio statistico, il valor medio
%della distribuzione delle velocità tende a quello previsto teoricamente
%dalla maxwelliana. Si vede facilmente che all'aumentare di h, il tempo
%previsto � maggiore, mentre al contrario, aumentando il coefficiente di
%attrito viscoso, il tempo diminuisce. 
%� possibile quindi modificare i parametri per avere una stima numerica,
%sebbene molto approssimativa, del tempo necessario alle particelle per
%raggiungere l'equilibrio statistico.
%Possiamo notare che per valori di gamma superiori al 10, il tempo � molto
%piccolo, anche aumentando di molto il valore di h; lo studio quindi �
%interessante per valori compresi tra 1 e 10. 



















