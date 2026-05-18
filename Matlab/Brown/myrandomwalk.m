function out = myrandomwalk(in)


narginchk(0,1);


dfltb.number_of_particles = 50000;
dfltb.viewbox_size= [0 6 -5 5];
dfltb.boundary_conditions = [1 0];
dfltb.initial_positions = @(N)10*rand(N,1);
dfltb.initial_velocities = @(N) zeros(N,1);
dfltb.acceleration_field= @(t,x) -ones(size(x));
dfltb.friction_coeff= 1;
dfltb.kT_over_mass = 1;
dfltb.random_kicks = @(t,x)randn(size(x));
dfltb.time_step = 0.001;
dfltb.step_tolerance = 0.001;
dfltb.time_span = 30;
dfltb.step_algorithm = 'rk4';
dfltb.plotframe_skips = 20;



if nargin == 0
        
        out = dfltb;
        return;
        
end

%set dei field mancanti dalla struttura dfltb 
    
    for fname = fieldnames(dfltb)
        if ~isfield(in,fname)
            in.(fname) = dflbt.(fname);
        end
    end

%rinominazione di alcune variabili

box = in.viewbox_size;
dim = length(box)/2;
bc = zeros(1,2*dim); 
bc(1:length(in.boundary_conditions)) = in.boundary_conditions;

N = in.number_of_particles;
x = in.initial_positions(N);
v = in.initial_velocities(N);

% valori iniziali di velocità e posizioni

in.initial_values = @(N)[x(N),v(N)];
x = [x,v];

if isscalar(x)
   x = x*ones(N,1); 
end

%controllo delle dimensioni delle posizioni e delle
%velocità inziali 

if size(x,1) ~= N
    error(['size mismatch between number of particles ' ...
        'and initial positions'])
end



rk = in.random_kicks;
dt = in.time_step;
nt = round(in.time_span/dt);

%controllo per evitare il plot in dimensioni superiori a una

if dim ~= 2
    skip = inf; 
else
    skip = in.plotframe_skips;
end


%set del grafico
if skip < nt     %plotta solo in due dimensioni
    shg
    clf
    set(gcf,'numbertitle','off','name','One-dimensional Brownian Motion')
    if dim == 2
        h = plot(x(:,1),x(:,2),'.');
    else
       disp('Dimensioni errate');
    end
    
%grafico nello spazio delle fasi: (posizione,velocità)
    axis(box)
    axis square
    axis on
    ylabel('Velocità')
    xlabel('Posizione')
    ttl = title(sprintf('t = %-8.1f',0));
    stop = uicontrol('style','toggle','string','stop',...
        'units','normalized','position',[.10 .01 .1 .05]);
end

%settaggio del campo di drift dovuto all'attrito del fluido 
%e del campo di accelerazione dovuto alla gravità

gamma = in.friction_coeff;
g = in.acceleration_field;

% Dalla teoria sappiamo che il sistema di equazioni differenziali del moto browniano
%in una dimensione è analogo di un randomwalk in due dimensioni con
% opportuni drift
% nel caso in esame è dato da 

in.drift_field = @(t,x)[x(:,2),-gamma*x(:,2)+g(t,x(:,1))];
B = in.drift_field;

% coefficienti di diffusione D : dalla teoria sappiamo che il
%tensore di diffusione(matrice 2x2) ha entrate tutte nulle, ecccetto
%l'entrata D_{2,2}.
%corrispondente al coefficiente di diffusione sulle velocità ovvero
%D_{2,2} = D*\gamma^2 = \gamma*kT/m con k = costante di Boltzmann, T la temperatura e m la
%massa della particella

D = gamma * in.kT_over_mass;
in.random_jumps =@(t,x)[zeros(size(x,1),1),sqrt(2*D)*rk(t,x(:,2))];
rj = in.random_jumps;
jt = 0;

while jt < nt
    t = jt*dt;
    xnew = feval(in.step_algorithm,B,t,x,dt);
    x = xnew + sqrt(dt)*rj(t,x);

% consideriamo urti tra il piano z = 0 e le particelle
% come urti elastici: la velocità di ogni particella passerà da v (prima
% dell'urto) a -v (dopo l'urto)

    jdim = 1;
        jo = dim-1;
        je = dim;
        
%traduciamo dunque questa condizione come un riflessione sull'asse delle 
%velocità una volta che la particella si trova sul piano

        if bc(jo)
            I = x(:,jdim) < box(jo);
            x(I,jdim) = -x(I,jdim) + 2*box(jo);
            x(I,2)= -x(I,2);
        end
        if bc(je)
            I = x(:,jdim) > box(je);
            x(I,jdim) = -x(I,jdim) + 2*box(je);
            x(I,2)= -x(I,2);
        end
        
     if mod(jt+1,skip+1) == 0
        h.XData = x(:,1);
        h.YData = x(:,2);
     end
        ttl.String = sprintf('t = %-8.1f',jt*dt);
        drawnow
        
 
%Per valutare il tempo di raggiungimento dell'equilibrio,
%verifichiamo quando il valor medio delle velocità si trova in un
%intorno di raggio r=0.1 di quello della maxwelliana. Imponiamo dunque una
% condizione di uscita dal calcolo come 
        
        if t>0.2 && mean(x(:,2))>=-0.1 && mean(x(:,2))<=0.1 
            figure;
            set(gcf,'numbertitle','off','name','Distribution of Position and Velocities at time t')
            histogram2(x(:,1),x(:,2))
             figure;
            set(gcf,'numbertitle','off','name','Comparison with Maxwell-Boltzmann distribution')
            hold on
          
           histogram(x(:,2), 'Normalization','pdf');
           
           b = max(x(:,2)); 
           a = -b:0.01:b;
           plot(a,1/(sqrt(2*pi))*exp(-a.^2/2)); 
           
            
            break
        end
        
        if get(stop,'value')
            
            
% Una volta che viene premuto il tasto di stop nella finestra di
% evoluzione temporale del moto browniano, verranno plottati un istogramma
% che mostra posizioni e velocità finali delle particelle

            figure;
            set(gcf,'numbertitle','off','name','Distribution of Position and Velocities at time t')
            histogram2(x(:,1),x(:,2))
            
%viene inoltre plottato un istogramma che mostra la distribuzione di velocità
%delle particelle al tempo finale 
%dalla teoria sappiamo che in situazione di equilibrio statistico, la
%distribuzione cercata è la distribuzione di Maxwell-Boltzmann
%plottando nella stessa finestra la maxwelliana aspettata, possiamo
%compararla con la distribuzione di velocità al tempo t

            figure;
            set(gcf,'numbertitle','off','name','Comparison with Maxwell-Boltzmann distribution')
            hold on
          
           histogram(x(:,2), 'Normalization','pdf');
           
           b = max(x(:,2)); 
           a = -b:0.01:b;
           plot(a,1/(sqrt(2*pi))*exp(-a.^2/2)); 
           
          mean(x(:,2))
            break
        end
   
    jt = jt+1;
end   

out.final_positions = x;
out.in = in;

if skip < nt
    set(stop,'string','close','value',0,'callback','close(gcf)')
end

end

function yp = rk4(F,t,y,h) 
    s1 = F(t,y);
    s2 = F(t+h/2,y+h/2*s1);
    s3 = F(t+h/2,y+h/2*s2);
    s4 = F(t+h,y+h*s3);
    yp = y + h*(s1 + 2*s2 + 2*s3 + s4)/6;
end
