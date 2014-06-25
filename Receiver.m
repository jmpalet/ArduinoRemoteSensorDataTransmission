clear all; close all; clc;
numSec=5000;
t=[];
v=[];
 
%s1 = serial('/dev/cu.usbmodem411');            % define serial port
s1 = serial('COM8');
s1.BaudRate=9600;               % define baud rate
set(s1, 'terminator', 'LF');    % define the terminator for println
fopen(s1);
 
try                             % use try catch to ensure fclose
                                % signal the arduino to start collection
w=fscanf(s1,'%s');              % must define the input % d or %s, etc.
if (w=='A')
    display(['Collecting data']);
    fprintf(s1,'%s\n','A');     % establishContact just wants 
                                % something in the buffer
end
 
i=0;
t0=tic;
while (i<numSec)
    if(~isnan(fscanf(s1, '%d')))
        i = i+1;
    
        t(i)=toc(t0);
        t(i)=t(i)-t(1);
        v(i)=fscanf(s1,'%d');       % must define the input % d or %s, etc.
        v(i) = v(i)-4;
        disp(v(i));
        set(gcf, 'color', 'white');
        drawnow;
        if i>20
            tprint=t(i-20:i);
            vprint=v(i-20:i);
            plot(tprint,vprint);
            %ylim([0 60]);
            axis([tprint(1) tprint(21) 0 60]);
        else
            plot(t,v);
            %ylim([0 60]);
            axis([0 6.8153 0 60]);
           % xLim([0 20]);
        end

        grid on;
        title('V Test');
        xlabel('Time');
        ylabel('Input');
        
    end
end
 
catch me
    disp(me);
    fclose(s1);
end   