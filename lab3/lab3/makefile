CC=CC
EXE1 = prob1
EXE2 = prob2
EXE3 = prob3

all: prob1 prob2 prob3

prob1:
	gcc cscd340_f12_lab3prob1.c -o $(EXE1) 

prob2:
	gcc cscd340_f12_lab3prob2.c -o $(EXE2) 

prob3:
	gcc cscd340_f12_lab3prob3.c -o $(EXE3) 

clean:
	if test -f $(EXE1); then rm $(EXE1); fi
	if test -f $(EXE2); then rm $(EXE2); fi
	if test -f $(EXE3); then rm $(EXE3); fi
