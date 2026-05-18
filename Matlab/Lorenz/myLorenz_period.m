function myLorenz_period(rho,N)

%% Introduzione

% myLorenz_period restituisce il periodo dell'orbita per il valore scelto
% di rho. Se l'orbita non è periodica stampa un opportuno messaggio di
% avviso. La funzione, inoltre, mostra un grafico rappresentante la forma 
% dell'orbita periodica, e, infine, chiama un'altra funzione che restitusce 
% un grafico rappresentante l'andamento della soluzione del sistema di
% Lorenz e un altro che mostra la forma di tutta l'orbita.

%% Inizializzazione di tutti i parametri utili

% Si sono scelti questi valori per t1 e t2 in modo che il calcolo del
% periodo sia meno influenzato dal transiente iniziale.

t1 = floor(N/2)+1;
t2 = N;

sigma = 10;
beta = 8/3;
eta = sqrt(beta*(rho-1));
A = [ -beta    0     eta
         0  -sigma   sigma 
      -eta   rho    -1  ];

yc = [rho-1 eta eta];
y0 = yc + [0 0 3];

%% Risoluzione del sistema di Lorenz

opts = odeset('events',@lorenzgstop,'reltol',1.e-10,'abstol',1.e-15);
[t,y,te,ye] = ode113(@lorenzeqn, [0 t2], y0, opts, A);

k = t>t1;

y = y(k,:);
ke = te>t1;
te = te(ke);
ye = ye(ke,:);

% A questo punto la funzione lorenzgstop ha trovato i valori dei massimi
% locali di norm(y(t)) (gli ye). Un massimo è "identificato" quando tutte 
% tre le componenti di y sono praticamente uguali; un periodo completo ne 
% contiene diversi di questi massimi locali. Il tempo che intercorre tra
% questi distinti massimi è proprio il periodo.

%% Calcolo dei periodi

yenorm = sqrt(sum(ye.*ye,2));
m = yenorm == max(yenorm);
yem = ye(m,:);
n = length(te);
e = sum(abs(ye - yem(ones(n,1),:)),2);

k = e < 1.e-5*yenorm;

d = diff(te(k)); % vettore contenente i vari periodi

%% Controllo su rho

if rho > 1 && rho < 24.284785963
    
    fprintf('\n-) The orbit cannot be periodic because it collapses on the equilibrium point. \n\n');

else

%% Controllo sui periodi

% Se il vettore te(k) contiene meno di 3 elemnti o se il vettore dei
% periodi d contiene elementi diversi tra loro più di un certo valore
% scelto come tolleranza allora l'orbita non è considerata periodica

    if length(d) < 2 || (max(d)-min(d))/max(d) > .999

        fprintf('\n-) The orbit is not periodic for the chosen value of rho (in the considered time interval,\n   dependent on the length N of the signature).\n\n');

    else
        
%% Periodo

        period = mean(d);
        fprintf('\n-) The orbit is periodic for the chosen value of rho (in the considered time interval,\n   dependent on the length N of the signature), and the period is: \n\n\t\t P = %f.\n\n',period);
        
        figure('Name', 'Representation of the periodic orbit')
        plot3(y(:,1),y(:,2),y(:,3),'-',ye(:,1),ye(:,2),ye(:,3),'.');
        line(yem(1),yem(2),yem(3),'marker','.','markersize',18,'color',[2/3 0 0]);
        line(yc(1),yc(2),yc(3),'marker','o','color',[0 2/3 0]);
        line(yc(1),-yc(2),-yc(3),'marker','o','color',[0 2/3 0]);
    end
end

myLorenz_plot(rho,0,N);
 

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
