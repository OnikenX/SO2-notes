SOURCEFILES=src\ficha1.cpp \
src\ficha2.cpp \
src\ficha3.cpp \
src\ficha4.cpp \
src\ficha5.cpp \
src\main.cpp \
src\Source.cpp

PRODUTOR_EXE=Release\Produtor.exe
PRODUTOR_SRC=src\Ficha6\Produtor\main.cpp

CONSUMIDOR_EXE=Release\Consumidor.exe
CONSUMIDOR_SRC=src\Ficha6\Consumidor\main.cpp

all: ficha6 #build

ficha6: ficha6_compile

ficha6_compile: $(CONSUMIDOR_EXE) $(PRODUTOR_EXE)

$(CONSUMIDOR_EXE): $(CONSUMIDOR_SRC)
	cl.exe /DUNICODE /D_UNICODE /EHsc $(CONSUMIDOR_SRC) /Fe:$(CONSUMIDOR_EXE) /utf-8

$(PRODUTOR_EXE): $(PRODUTOR_SRC)
	cl.exe /DUNICODE /D_UNICODE /EHsc $(PRODUTOR_SRC) /Fe:$(PRODUTOR_EXE) /utf-8


build:
	mkdir -p Release
	cl.exe /DUNICODE /D_UNICODE /EHsc $(SOURCEFILES) /Fe:./Release/SO-notes.exe /utf-8


clean: delete_trash
	rm Release

delete_trash:
	rm *.obj

