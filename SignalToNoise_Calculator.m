x = [0 1 3 5 7 9 11 13 15 17 19 21];
y = [121 132 180 220 311 421 555 633 720 750 801 822];

xx = linspace(0,21,1000);
yy = spline(x,y,xx);
figure()
plot(x,y,'o',xx,yy);
S = std(yy);
Avg = mean(y);
SignalToNoise_Ratio = S/Avg;

disp(SignalToNoise_Ratio);