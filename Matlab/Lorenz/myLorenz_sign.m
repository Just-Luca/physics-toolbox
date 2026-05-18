function sign = myLorenz_sign(rho,N)

%% Introduzione

% La funzione myLorenz_sign restituisce un vettore logico di dimensioni (Nx1)
% contenente la segnatura di un'orbita, soluzione delle equazioni di Lorenz, 
% avente punto di partenza y0 = yc + [0 0 3] , dove yc = [rho-1 eta eta].
% La segnatura di un'orbita non è altro che una sequenza di due simboli 
% (0/1 o +/-), dove lo "0" (o il "+") indica che l'orbita ha compiuto un
% "giro" attorno ad uno dei due punti di equilibrio; il simbolo "1" 
% (o il "-"), al contrario, sta ad indicare un "giro" intorno all'altro 
% punto di equilibrio. Nel caso che l'orbita sia periodica, ovviamente,
% anche la segnatura lo sarà. Interessante è provare diversi valori di rho,
% e osservare cosa cambia nella segnatura e nel periodo al variare di esso.
% Si può verificare, infatti, che esistono intervalli di valori del 
% parametro rho per cui l'orbita assume differenti comportamenti; e in 
% particolare: 
%
% a) per 0 < rho <= 1 l'orbita collassa sull'origine (rho = 1 è un punto di
%    biforcazione); (source: https://en.wikipedia.org/wiki/Lorenz_system)
% b) per 1 < rho < 24.285 (24.284785963...) l'orbita collassa su un punto
%    di equilibrio;
% c) per 99.097 < rho < 100.795 , 142.703 < rho < 166.062 e rho > 198.373 
%    l'orbita è periodica;
% d) per tutti gli altri valori di rho l'orbita non è periodica (diverge,
%    nel tempo, all'infinito).
%
% N.B.: i valori di rho indicati ai punti b) e c) sono stati ottenuti
% considerando, al massimo, N = 10000; è possibile, quindi, che per N
% maggiori di questa grandezza si trovino dei valori di rho, per cui  
% l'orbita è periodica, diversi da quelli considerati sopra (per N > 10000 
% il tempo computazionale inizia a diventare elevato).
%
% myLorenz_sign, poi, mostra l'autocorrelazione presente nella segnatura; 
% mostra, cioè, attraverso un grafico, in che modo un valore della 
% segnatura dipende da quello precedente. Inoltre calcola il periodo 
% dell'orbita (se periodica) per quel determinato valore di rho. Da notare 
% è che l'orbita può risultare non periodica anche per una scelta di un 
% valore "notevole" di rho, in quanto la funzione usata per calcolare il 
% periodo dipende dalla scelta della lunghezza della segnatura ("N"), e 
% quindi dal tempo stesso che l'orbita impiega a compiere N giri attorno ai
% punti di equilibrio. Per N piccoli, quindi, l'orbita non risulterà 
% periodica (anche se la segnatura dovesse esserlo) poichè non avrà 
% raggiunto la sua stabilità, e il calcolo sarà fortemente influenzato dal 
% transiente iniziale.


%% Controllo sul valore di rho

% Scegliere un rho < 1 comporta il presentarsi di un errore nell'odesolver,
% mentre se rho = 1 non esiste segnatura poichè l'orbita collassa subito
% sull'origine.

if rho < 1 
        
    error('When rho < 1 all orbits converge to the origin, which is a global attractor');
       
elseif rho == 1
        
    myLorenz_plot(rho,0,N);
    error('When rho = 1 a pitchfork bifurcation occurs, and the orbits converge to the origin');
end

%% Inizializzazione di tutti i parametri utili

t1 = 0;
t2 = N;

sigma = 10;
beta = 8/3;
eta = sqrt(beta*(rho-1));

A = [ -beta    0     eta
         0  -sigma   sigma 
      -eta   rho    -1  ];

yc = [rho-1 eta eta];
y0 = yc + [0 0 3];

%% Doppio controllo su rho e N

% Si effettua questo doppio controllo per evitare il presentarsi di un
% errore nel codice.

if rho < 10 && N < 55
    
    t2 = 55;
    
    opts = odeset('events',@lorenzgstop,'reltol',1.e-10,'abstol',1.e-15);
    [~,~,te,ye] = ode113(@lorenzeqn, [0 t2], y0, opts, A);

    ke = te>t1;
    ye = ye(ke,:);
    
    fprintf('\n SIGNATURE: \n');
    
    fprintf('\n The signature (0/1) is: ');
    
    
% n è un vettore logico: si scorrono gli elementi di ye (gli eventi 
% definiti dalla funzione lorenzgstop) e li compara con 0; se sono minori 
% di 0 vuol dire che sono nei pressi del punto di equilibrio definito 
% negativo, e quindi il relativo componente di n sarà 1.
    
    n = ye(1:N,2) < 0; 
    
%% Stampa della segnatura

    n_ch = (int2str(n))';
    fprintf('%s\n',n_ch);
    
    fprintf('\n The signature (+/-) is: ');

    for w = 1:N

        if n(w) == 1
            fprintf('-');
        else
            fprintf('+');
        end
    end
    
    fprintf('\n');
    
%% Segnatura
    
    sign = ye(1:N,2) < 0;
    
%% Proprietà dell'orbita
    
% Si chiamano le funzioni che danno informazioni sull'autocorrelazione e
% sul periodo.

    fprintf('\n PROPERTIES: \n');
    
    myAutocorr_sign(sign);
    myLorenz_period(rho,N);
    
   
else    
%% N > 55: 

    opts = odeset('events',@lorenzgstop,'reltol',1.e-10,'abstol',1.e-15);
    [~,~,te,ye] = ode113(@lorenzeqn, [0 t2], y0, opts, A);

    ke = te>t1;
    ye = ye(ke,:);   

%% Stampa della segnatura    
    
    z = floor(N/100);
    R = mod(N,100);

    j = [];
    j(1) = 1;

    fprintf('\n SIGNATURE: \n');

    fprintf('\n The signature (0/1) is: \n\n');

    if z < 1

        s = ye(1:N,2) < 0;
        s_ch = (int2str(s))';
        fprintf('%s\n',s_ch);
    else

        for i=1:z 

            j(i+1) = (i*100)+1; 
            S = ye(j(i):i*100,2) < 0;
            S_ch = (int2str(S))';
            fprintf('%s\n',S_ch);
        end

        rest = ye(((z*100)+1):N,2) < 0;
        rest_ch = (int2str(rest))';
        fprintf('%s\n',rest_ch);
    end

    fprintf('\n The signature (+/-) is: \n\n');

    if z < 1

        s = ye(1:N,2) < 0;

        for w = 1:N

            if s(w) == 1
                fprintf('-');
            else
                fprintf('+');
            end
        end

        fprintf('\n');

    else

        for i=1:z 

            j(i+1) = (i*100)+1; 
            S = ye(j(i):i*100,2) < 0;

                for g = 1:100

                    if S(g) == 1
                        fprintf('-');
                    else
                        fprintf('+');
                    end
                end

                fprintf('\n');
        end

        rest = ye(((z*100)+1):N,2) < 0;

        for a = 1:R

            if rest(a) == 1
                fprintf('-');
            else
                fprintf('+');
            end
        end
        fprintf('\n');   
    end

%% Segnatura

    sign = ye(1:N,2) < 0;

%% Proprietà dell'orbita

    fprintf('\n PROPERTIES: \n');

    myAutocorr_sign(sign);
    myLorenz_period(rho,N);

end


%% ------------------------------------------------------------------------

function ydot = lorenzeqn(~,y,A)
%LORENZEQN  Equation of the Lorenz chaotic attractor.
%   ydot = lorenzeqn(t,y,A).
%   The differential equation is written in almost linear form.
%      ydot = A*y
%   where
%      A = [ -beta    0     y(2)
%               0  -sigma   sigma 
%            -y(2)   rho    -1  ];

A(1,3) = y(2);
A(3,1) = -y(2);
ydot = A*y;

%% ------------------------------------------------------------------------

function [gstop,isterm,direct] = lorenzgstop(~,y,A)
%LORENZSTOP  Find local maxima of norm(y).
%  d/dt(norm(y)^2) = d/dt(y'*y) = 2*ydot'*y

A(1,3) = y(2);
A(3,1) = -y(2);
ydot = A*y;
gstop = ydot'*y;
isterm = 0;
direct = -1;
