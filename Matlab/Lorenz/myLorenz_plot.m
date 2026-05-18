function myLorenz_plot(rho,t1,t2)

%% Introduzione

% myLorenz_plot restituisce due grafici: uno rappresenta tutta la forma (e
% quindi è una raffigurazione grafica di tutta la segnatura) dell'orbita 
% dal punto iniziale y0 e dal tempo iniziale t1 fino al punto finale e al
% tempo finale t2; il secondo grafico, invece, mostra l'andamento della
% soluzione del sistema di Lorenz.

%% Inizializzazione di tutti i parametri utili

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
t = t(k);
y = y(k,:);

ke = te>t1;
te = te(ke);
ye = ye(ke,:);

yenorm = sqrt(sum(ye.*ye,2));
m = yenorm == max(yenorm);
yem = ye(m,:);
n = length(te);
e = sum(abs(ye - yem(ones(n,1),:)),2);
k = e < 1.e-5*yenorm;

%% Plot

figure('Name', 'Representation of all the signature')
plot3(y(:,1),y(:,2),y(:,3),'-',ye(:,1),ye(:,2),ye(:,3),'.');
line(yem(1),yem(2),yem(3),'marker','.','markersize',18,'color',[2/3 0 0]);
line(yc(1),yc(2),yc(3),'marker','o','color',[0 2/3 0])
line(yc(1),-yc(2),-yc(3),'marker','o','color',[0 2/3 0])

figure('Name', 'Solution behavior')
plot(t,y(:,2),'.-',te,ye(:,2),'.',te(k),ye(k,2),'*');

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
