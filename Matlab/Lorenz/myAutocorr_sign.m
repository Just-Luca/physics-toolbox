function myAutocorr_sign(y)

% myAutocorr_sign calcola, attraverso la funzione di MATLAB corrcoef, la
% matrice dei coefficienti di correlazione di una matrice "figlia" del 
% vettore 1D inserito come input. In seguito mostra un grafico 
% rappresentante l'andamento dell'autocorrelazione tra gli elementi del 
% vettore inserito come input che, nel nostro caso, sarà la segnatura 
% dell'orbita.
 
n = numel(y);
I = 2:n;
nI = length(I);

Y = [y zeros(n,nI)];
for j = 1:nI
    Y(:,j+1) = y([I(j):n 1:I(j)-1]);
end
[R,~,~,~] = corrcoef(Y);

if isnan(R)
    fprintf('\n-) It makes no sense to calculate the autocorrelation because the signature is composed of only zeros (or ones), \n   and therefore the correlation coefficients are all NaN. \n');
else
    figure('Name', 'Autocorrelation of the signature')
    plot(1:n,abs(R(1,:)));
end