#Makefile projeto Reconhecimento de Fala
#Edielson Prevato Frigieri
#Atualização: 30/07/07

CC=gcc 
#CC=/media/sda4/projetos/arm/atmel/buildroot-v23434/build_arm/staging_dir/usr/bin/arm-linux-gcc-4.2.4 
CFLAGS= -g -pg -c -Wall -Werror
LDFLAGS= -ldl -g -pg -lasound
#LDFLAGS=

SOURCES=main.c gravaoss.c calcdelta.c energia.c lpc.c mel.c preProc.c calcpar.c fft.c perfil.c wav.c loadconfig.c loadUtterances.c saveGMM.c mixture.c mixture2.c b.c loadGMM.c showgmm.c update_s.c update_p.c update_m.c aposteriori.c lbg.c testgmm.c 

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=oss

all: $(SOURCES) $(EXECUTABLE)
	rm -rf *o
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -lm -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE)
         
