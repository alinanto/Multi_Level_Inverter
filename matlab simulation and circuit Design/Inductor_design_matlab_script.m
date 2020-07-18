clc;

L=2.5e-3;
I=2.4;
Ac=1.5e-4; 
Bmax=0.2;

N  = (L*I)/(Bmax*Ac)
Lg = ((4*pi*(10^-7))*(N^2)*Ac)/L
Lg_mil =Lg * 1000

